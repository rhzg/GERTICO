/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** FederationManagement.cpp
**
*******************************************************************************/

#include "FederationManagement.h"

#include <ace/OS.h>

#include "Util/GERTICOconf.h"
#include "Util/ConvertTime.h"
#include "Util/XercesInclude.h"
#include "Util/HLAparseErrorHandler.h"
#include "Util/Mapper.h"
#include "Util/PrintFilter.h"
#include "Util/PrintErrorHandler.h"

// ---------------------------------------------------------------------------
//  Local data
//
//  gOutputEncoding
//      The encoding we are to output in. If not set on the command line,
//      then it is defaults to the encoding of the input XML file.
//
//  gMyEOLSequence
//      The end of line sequence we are to output.
//
//  gSplitCdataSections
//      Indicates whether split-cdata-sections is to be enabled or not.
//
//  gDiscardDefaultContent
//      Indicates whether default content is discarded or not.
//
//  gUseFilter
//      Indicates if user wants to plug in the PrintFilter.
//
//  gValScheme
//      Indicates what validation scheme to use. It defaults to 'auto', but
//      can be set via the -v= command.
//
// ---------------------------------------------------------------------------

static char*                    goutputfile            = 0;
// options for DOMWriter's features
static XMLCh*             gOutputEncoding        = 0;
static XMLCh*             gMyEOLSequence         = 0;

static bool                     gSplitCdataSections    = true;
static bool                     gDiscardDefaultContent = true;
static bool                     gUseFilter             = false;
static bool                     gFormatPrettyPrint     = false;
static bool                     gWriteBOM              = false;

//static XercesDOMParser::ValSchemes    gValScheme       = XercesDOMParser::Val_Auto;

// Save / Restore strings
std::string GERTICO::FederationManagement::countStr("count");
std::string GERTICO::FederationManagement::federateStr("federate");
std::string GERTICO::FederationManagement::federateTypeStr("federateType");
std::string GERTICO::FederationManagement::federateTypesStr("federateTypes");
std::string GERTICO::FederationManagement::federateIdsStr("federateIds");
std::string GERTICO::FederationManagement::federatesStr("federates");
std::string GERTICO::FederationManagement::federationTimeStr("federationTime");
std::string GERTICO::FederationManagement::idStr("id");
std::string GERTICO::FederationManagement::typeStr("type");

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationManagement::FederationManagement(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, PortableServer::POA_ptr thePoaBestEffort, PortableServer::POA_ptr thePoaSender, std::wstring const &theFederationName, std::wstring const &theFedFile, GERTICO::NextHandle &theIdHandler, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory), gerticoConf(theGERTICOconf), idHandler(theIdHandler)
{
  // Various varibles
  ACE_stat ace_stat;
  char buf[1024];
  CosNaming::Name bindName;
  EventHandler *eventHandler;
  GeRtiFactory::GeRtiHandle privilegeToDeleteId;
  std::string hubName;
  std::string hubsName;
  std::string name;
  std::wstring myEventHub = L"builtInHub";

  consumerAdmin = NULL;
  dataDistributionManagement = NULL;
  declarationManagementRTI = NULL;
  eventHandler = NULL;
  federationManagementEC = NULL;
  nextSaveTime = NULL;
  objectManagement = NULL;
  objectModel = NULL;
  ownershipMaster = NULL;
  parser = NULL;
  registeredObjectsHolder = NULL;
  runTimeObjectDB = NULL;
  supplierAdmin = NULL;
  supplierAdminBestEffort = NULL;
  supportingServices = NULL;
  syncPointHandler = NULL;

  concurrencyFlag = false;
  gotPreviousTime = false;
  notDone = true;
  restoreInProgress = false;
  saveInProgress = false;
  saveRequested = false;
  saveTimeReachedFlag = false;

  federationName = theFederationName;
  fedFile = theFedFile;

  myPOA = PortableServer::POA::_duplicate(thePOA);
  myPOAbestEffort = PortableServer::POA::_duplicate(thePoaBestEffort);
  myPoaSender = PortableServer::POA::_duplicate(thePoaSender);
  ps = new ACE_Semaphore(1);

  federationState = "federationState";

  // read OMT File
  bool found = false;
  std::wstring dot(L".");
  std::string s;
  std::wstring ws;
  GERTICOconf::_resetPath();
  while (GERTICOconf::_hasMorePath())
  {
    char *st = GERTICOconf::_nextPath();
    if (parseEnv(buf, st))
    {
      continue;
    }
    std::wstring fedFilePath;
    GERTICO::Mapper::mapWstringFromChar(fedFilePath, buf);
    delete [] st;
    if (fedFilePath == dot)
    {
      fedFilePath = theFedFile;
    }
    else
    {
#ifdef _WIN32
      fedFilePath.append(L"\\");
#else
      fedFilePath.append(L"/");
#endif
      fedFilePath.append(theFedFile);
    }

    try
    {
      if (ACE_OS::stat(fedFilePath.c_str(), &ace_stat))
      {
        continue;
      }
      objectModel = GERTICO::ObjectModelFactory::createObjectModel (fedFilePath, theIdHandler);
      found = true;
      break;
    }
    catch (GERTICO::CouldNotOpenFED &)
    {
      continue;
    }
    catch (GERTICO::ErrorReadingFED &ex)
    {
      ex.getError (s);
      GERTICO::Mapper::mapWstringFromChar(ws, s.c_str());
      throw GeRtiFactory::ErrorReadingFED(ws.c_str());
    }
  }

  if (found == false)
  {
    throw GeRtiFactory::CouldNotOpenFED(theFedFile.c_str());
  }

  federatesHolder = new GERTICO::FederatesHolder(geRtiFedTimeFactory);
  syncPointHandler = new GERTICO::SyncPointHandler(*federatesHolder);

  // create RunTimeDB
  registeredObjectsHolder = new GERTICO::RegisteredObjectsHolder();
  runTimeObjectDB = new RunTimeObjectDB(*registeredObjectsHolder, regionsHolder);
  runTimeObjectDB->setModel(objectModel);
  runTimeObjectDB->addRoutingSpace(objectModel->allFedSpaces);
#ifdef IEEE_1516
  runTimeObjectDB->addDimensions(objectModel->fedDimensionMap);
#endif

  addXmlObjectClass(0, objectModel->getRootClass());
  addXmlInteractionClass(0, objectModel->getRootInteraction());

  // Object Management.
  objectManagement = new ObjectManagement(*registeredObjectsHolder, *runTimeObjectDB, *federatesHolder, *objectModel, theIdHandler, federationJobs, pm, *ps, geRtiFedTimeFactory);

  // Ownership
  ownershipMaster = new GERTICO::GeRtiOwnershipMasterI(*runTimeObjectDB, *objectManagement);
  ownershipMaster->setFederatesHolder(federatesHolder);

  // Supporting Services
  supportingServices = new GERTICO::SupportingServices(*objectManagement, *runTimeObjectDB, objectRoot, interactionRoot, *federatesHolder);
  privilegeToDeleteId = runTimeObjectDB->getPrivilegeToDeleteId();

  //federationManagementEC = new GERTICO::FederationManagementEC(myEventHub, theGeRtiOrb, theGeRtiOrb.poaRootReceiver, theGeRtiOrb.poaRootSenderBestEffort, theGeRtiOrb.poaRootSenderReliable, theFederationName, theFedFile, idHandler, theGERTICOconf, geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory, privilegeToDeleteId);
  // Event channel
  //eventHandler = new EventHandler(*ps, gerticoConf, geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory, *supportingServices);
  //eventHandler->timeServiceFac = new GERTICO::TimeServiceFacI(*timeClient);
  //eventHandler->timeService = eventHandler->timeServiceFac->createTimeService();
  //eventHandler->geRti_TimeManagement_i = new GeRti_TimeManagement_i(thePOA, *eventHandler->timeService, &geRtiFedTimeFactory, &geRtiLogicalTimeIntervalFactory);
  //eventHandler->timeManagementVar = eventHandler->geRti_TimeManagement_i->_this();
  // Declaration Management
  declarationManagementRTI = new DeclarationManagementRTI(*objectManagement, *ownershipMaster, *runTimeObjectDB, interactionRoot, *federatesHolder, federationJobs, pm);

  // Data Distribution Management.
  dataDistributionManagement = new DataDistributionManagement(*declarationManagementRTI, *objectManagement, *runTimeObjectDB, *federatesHolder, *objectModel, theIdHandler, federationJobs, pm);

//  timeClient->eventHandler = federationManagementEC->eventHandler;

  // MOM
  if (federationManagementEC)
  {
    eventHandler = federationManagementEC->eventHandler;
  }
  managementObjectModel = new GERTICO::ManagementObjectModel(*declarationManagementRTI, *objectManagement, *ownershipMaster, *supportingServices, eventHandler, interactionRoot, objectRoot, *federatesHolder, federationJobs, *ps);
  managementObjectModel->setFederationFile(theFedFile);
  managementObjectModel->setFederationName(theFederationName);
  GeRtiFactory::GeRtiHandle momManagerInteractionRoot;
  managementObjectModel->getMomManagerInteractionRoot(momManagerInteractionRoot);
  //eventHandler->declarationManagementEC->interactionHolder->setMomManagerInteractionRoot(momManagerInteractionRoot);
#ifndef IEEE_1516
  std::auto_ptr<GERTICO::GeRtiFedTime> nextSaveTime(geRtiFedTimeFactory.makeZero());
  char buff[256];
  nextSaveTime->getPrintableString(buff);
  zeroTimeStr = buff;
  // Special logic.
  managementObjectModel->setNextSaveTime(zeroTimeStr);
#endif
  managementObjectModel->setNextSaveName(ws);
  // End special logic.
  //federationManagementEC->eventHandler->setMom(managementObjectModel);

  //consumerAdmin = new GeRtiEventMarket_MarketConsumerAdmin_i(theGeRtiOrb, myPOA, myPOAbestEffort, *federationManagementEC->eventHandler);
  //supplierAdmin = new GeRtiEventMarket_MarketSupplierAdmin_i(theGeRtiOrb, myPOA, *federationManagementEC->eventHandler);
  //supplierAdminBestEffort = new GeRtiEventMarket_MarketSupplierAdmin_i(theGeRtiOrb, myPOA, *federationManagementEC->eventHandler);

  /*
  try
  {
    name = theGERTICOconf.ns->rootEntry;
    hubName = "EventHub";
    hubsName = "EventHubs";

    CORBA::Object_ptr objectConsumerAdmin = consumerAdmin->_this();
    CORBA::Object_ptr objectSupplierAdminBestEffort = supplierAdminBestEffort->_this();
    CORBA::Object_ptr objectSupplierAdminReliable = supplierAdmin->_this();

    bindName.length(2);
    bindName[0].id = CORBA::string_dup(name.c_str());
    bindName[0].kind = CORBA::string_dup("");
    bindName[1].id = CORBA::string_dup(hubsName.c_str());
    bindName[1].kind = CORBA::string_dup("");
    if (addNsDirectory(theGeRtiOrb, bindName))
    {
      return;
    }

    bindName.length(3);
    bindName[2].id = CORBA::string_dup(hubName.c_str());
    bindName[2].kind = CORBA::string_dup("");
    if (addNsDirectory(theGeRtiOrb, bindName))
    {
      return;
    }

    bindName.length(4);
    bindName[3].id = CORBA::string_dup("ConsumerAdmin");
    bindName[3].kind = CORBA::string_dup("");
    theGeRtiOrb.getRootContext()->rebind(bindName, objectConsumerAdmin);
    bindName[3].id = CORBA::string_dup("SupplierAdminBestEffort");
    theGeRtiOrb.getRootContext()->rebind(bindName, objectSupplierAdminBestEffort);
    bindName[3].id = CORBA::string_dup("SupplierAdminReliable");
    theGeRtiOrb.getRootContext()->rebind(bindName, objectSupplierAdminReliable);
    bindName[3].id = CORBA::string_dup("TimeManagement");
    theGeRtiOrb.getRootContext()->rebind(bindName, eventHandler->timeManagementVar);
  }
  catch(CosNaming::NamingContext::NotFound ex)
  {
//    ACE_ERROR_RETURN((LM_ERROR, "Unable to bind %s NotFound\n", name.c_str()), -1);
    return;
  }
  catch(CosNaming::NamingContext::InvalidName ex)
  {
//    ACE_ERROR_RETURN((LM_ERROR, "Unable to bind %s InvalidName \n", name.c_str()), -1);
    return;
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception");
    return;
  }
  catch(CORBA::UserException &userex)
  {
    ACE_PRINT_EXCEPTION(userex, "User Exception");
    return;
  }
  catch(...)
  {
    return;
  }
  */
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationManagement::~FederationManagement (void)
{
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;

  // Make sure any active federates are deleted.
  federatesHolder->getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    federatesHolder->deleteFederate(*itFederate);
  }

  if (parser)
  {
    delete parser;
  }

  // Reverse order of creation!
  if (supplierAdmin)
  {
    delete supplierAdmin;
  }

  if (supplierAdminBestEffort)
  {
    delete supplierAdminBestEffort;
  }

  if (consumerAdmin)
  {
    delete consumerAdmin;
  }

  if (supportingServices)
  {
    delete supportingServices;
  }

  if (dataDistributionManagement)
  {
    delete dataDistributionManagement;
  }

  if (objectManagement)
  {
    delete objectManagement;
  }

  // Ownership
  if (ownershipMaster)
  {
    delete ownershipMaster;
  }

  if (runTimeObjectDB)
  {
    delete runTimeObjectDB;
  }

  if (registeredObjectsHolder)
  {
    delete registeredObjectsHolder;
  }

  if (objectModel != NULL)
  {
    delete objectModel;
  }

  if (syncPointHandler)
  {
    delete syncPointHandler;
  }

  if (federatesHolder)
  {
    delete federatesHolder;
    federatesHolder = NULL;
  }

  delete ps;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagement::addNsDirectory(GERTICO::GeRtiOrb &theGeRtiOrb, CosNaming::Name const &theDirectoryName)
{
  try
  {
    gertiObj = theGeRtiOrb.getRootContext()->resolve(theDirectoryName);
  }
  catch(CosNaming::NamingContext::NotFound ex)
  {
    try
    {
      gertiObj = theGeRtiOrb.getRootContext()->bind_new_context(theDirectoryName);
    }
    catch(...)
    {
      return true;
    }
  }
  catch(...)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::addXmlInteractionClass(GERTICO::ClassDescr* parent, GERTICO::InteractionClass* child)
{
  GERTICO::ClassDescr *newClass;
  GERTICO::HandleSet dimensions;
  GeRtiFactory::GeRtiHandle handle;

  if (parent != 0)
  {
    // Space at class level.
    handle = getSpaceHandle(child->getSpace());
    child->getDimensions(dimensions);
    newClass = new  GERTICO::ClassDescr(child->getName(), child->getId(), handle, child->getOrdering(), child->getTransportation(), child->getSharing(), dimensions, parent);
  }
  else
  {
    // Does root have a space?
    child->getDimensions(dimensions);
    newClass = new  GERTICO::ClassDescr(child->getName(), child->getId(), 0, child->getOrdering(), child->getTransportation(), child->getSharing(), dimensions);
    interactionRoot.classDescr = newClass;
  }

  std::map <unsigned long, GERTICO::Parameter*> ::iterator iParameter;
  iParameter = child->parameters.begin();
  while (iParameter != child->parameters.end())
  {
    // Space at class level.
    dimensions.clear();
    newClass->addItem(iParameter->second->getName(), iParameter->second->getId(), 0, 0, 0, dimensions);
    iParameter++;
  }

  std::map <unsigned long, GERTICO::InteractionClass*> ::iterator iInteraction;
  iInteraction = child->childInteractions.begin();
  while (iInteraction != child->childInteractions.end())
  {
    addXmlInteractionClass (newClass, iInteraction->second);
    iInteraction++;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::addXmlObjectClass(GERTICO::ClassDescr* parent, GERTICO::ObjectClass* child)
{
  GERTICO::ClassDescr *newClass;
  GERTICO::HandleSet dimensions;
  GeRtiFactory::GeRtiHandle handle;

  if (parent != 0)
  {
    // Space at attribute level.
    dimensions.clear();
    newClass = new  GERTICO::ClassDescr(child->getName(), child->getId(), 0, 0, 0, child->getSharing(), dimensions, parent);
  }
  else
  {
    // Root also has no space.
    dimensions.clear();
    newClass = new  GERTICO::ClassDescr(child->getName(), child->getId(), 0, 0, 0, child->getSharing(), dimensions);
    objectRoot.classDescr = newClass;
    runTimeObjectDB->addObjectRoot(&objectRoot);
  }

  std::map <unsigned long, GERTICO::Attribute*> ::iterator iAttribute;
  iAttribute = child->attributes.begin();
  while (iAttribute != child->attributes.end())
  {
    // Space at attribute level.
    handle = getSpaceHandle(iAttribute->second->getSpace());
    iAttribute->second->getDimensions(dimensions);
    newClass->addItem(iAttribute->second->getName(), iAttribute->second->getId(), handle, iAttribute->second->getOrdering(), iAttribute->second->getTransportation(), dimensions);
    iAttribute++;
  }

  std::map <unsigned long, GERTICO::ObjectClass*> ::iterator iClass;
  iClass = child->childClasses.begin();
  while (iClass != child->childClasses.end())
  {
    addXmlObjectClass(newClass, iClass->second);
    iClass++;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::joinFederationExecution(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theFedType, GeRtiFactory::FederateAmbassador_ptr theFederateAmbassador_ptr, GeRtiFactory::GeRtiRestore_ptr theGeRtiRestore_ptr)
{
  FedCounts::iterator itFC;

  // Check save/restore status and possibly throw an exception.
  checkSaveRestore ();

  // Create a new federate attribute entry.
  federatesHolder->addFederate(theFederate, theFedType, *registeredObjectsHolder, theFederateAmbassador_ptr, theGeRtiRestore_ptr, objectRoot);

  itFC = fedCounts.find (theFedType);
  if (itFC != fedCounts.end ())
  {
    itFC->second += 1;
  }
  else
  {
    fedCounts[theFedType] = 1;
  }

  syncPointHandler->addFederate (theFederate);
//  federationManagementEC->eventHandler->timeService->joinFederationExecution(theFederate);

//  managementObjectModel->joinFederationExecutionMom(theFederate);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::joinFederationExecutionFinished(GeRtiFactory::GeRtiHandle theFederate)
{
  GERTICO::Federate *federate;

  federate = federatesHolder->getFederate(theFederate);
  if (federate != NULL)
  {
    federate->joinFederationExecutionFinished();
  }

  managementObjectModel->joinFederationExecutionMom(theFederate);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagement::checkFederationCounts(void)
{
  DOMNode* child;
  FedCounts tmpFedCounts;
  char *tmpChar;
  std::wstring tmpWstring;
  unsigned long tmpUL;

  for (child = domElement->getFirstChild (); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString (child->getNodeName (),XMLString::transcode (federationState.c_str ())) == 0)
      {
        DOMNode* subChild;
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (federateTypesStr.c_str ())) == 0)
            {
              DOMNode* subSubChild;
              for (subSubChild = subChild->getFirstChild(); subSubChild != 0; subSubChild = subSubChild->getNextSibling())
              {
                if (subSubChild->getNodeType() == DOMNode::ELEMENT_NODE)
                {
                  if (XMLString::compareString(subSubChild->getNodeName(),XMLString::transcode (federateTypeStr.c_str ())) == 0)
                  {
                    tmpChar = XMLString::transcode (((DOMElement*)subSubChild)->getAttribute (XMLString::transcode (countStr.c_str ())));
                    sscanf (tmpChar, "%lu", &tmpUL);
                    tmpChar = XMLString::transcode (((DOMElement*)subSubChild)->getAttribute (XMLString::transcode (typeStr.c_str ())));
                    GERTICO::Mapper::mapWstringFromChar(tmpWstring, tmpChar);
                    tmpFedCounts[tmpWstring] = tmpUL;
                  }
                }
              }
            }
          }
        }

        // Compare with the current values.
        if (compareFederationCounts (tmpFedCounts))
        {
          return true;
        }
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::checkSaveRestore (void)
{
  CORBA::WChar *wChar = L"";
  pm.acquire ();
  if (concurrencyFlag)
  {
    pm.release ();
    throw GeRtiFactory::ConcurrentAccessAttempted(wChar);
  }

  if (saveInProgress)
  {
    pm.release ();
    throw GeRtiFactory::SaveInProgress(wChar);
  }

  if (restoreInProgress)
  {
    pm.release ();
    throw GeRtiFactory::RestoreInProgress(wChar);
  }
  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::clear (void)
{
  GERTICO::Federate *currFed;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  GeRtiFactory::GeRtiRestore_var geRtiRestoreVar;

  if (federationManagementEC)
  {
    federationManagementEC->eventHandler->clearFederates();
  }

  federatesHolder->getFederates(federates);
  for (itFederate = federates.begin (); itFederate != federates.end (); itFederate++)
  {
    currFed = federatesHolder->getFederate(*itFederate);
    if (currFed == NULL)
    {
      continue;
    }
    geRtiRestoreVar = currFed->getGeRtiRestore();
    try
    {
      geRtiRestoreVar->resetLRC();
    }
    catch (CORBA::SystemException &)
    {
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagement::compareFederationCounts (FedCounts &theFedCounts)
{
  FedCounts::iterator itFC;
  FedCounts::iterator itTheFC;
  size_t iFC;
  size_t iTheFC;

  // Check number of different federate types.
  iFC = fedCounts.size ();
  iTheFC = theFedCounts.size ();
  if (iFC != iTheFC)
  {
    return true;
  }

  // For each type check quantity.
  for (itTheFC = theFedCounts.begin (); itTheFC != theFedCounts.end (); itTheFC++)
  {
    itFC = fedCounts.find (itTheFC->first);
    if (itFC != fedCounts.end ())
    {
      if (itFC->second != itTheFC->second)
      {
        return true;
      }
    }
  }

  // No error.
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::federateSaveBegun (const GeRtiFactory::GeRtiHandle &theFederate)
{
  CORBA::WChar *wChar = L"federateSaveBegun";
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;

  if (restoreInProgress)
  {
    throw GeRtiFactory::RestoreInProgress(wChar);
  }

  currFederate = federatesHolder->getFederate (theFederate);
  if (currFederate == NULL)
  {
    throw GeRtiFactory::RTIinternalError (L"FederationManagement::could not find federate");
  }

  if (currFederate->saveInitiated == false)
  {
    throw GeRtiFactory::SaveNotInitiated(wChar);
  }

  currFederate->federateSaveBegun ();
  currFederate->setAlive();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::federateRestoreComplete(const GeRtiFactory::GeRtiHandle &theFederate, const bool &theSuccess)
{
  CORBA::WChar *wChar = L"";
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet feds;
  GERTICO::HandleSet::iterator itFed;
  GeRtiFactory::RestoreFailureReason failureReason = rtiUnableToRestore;
  bool allComplete = true;
  bool allSuccess = true;

  if (getSaveInProgress())
  {
    throw GeRtiFactory::SaveInProgress(wChar);
  }

  if (getRestoreInProgress() == false)
  {
    throw GeRtiFactory::RestoreNotRequested(wChar);
  }

  currFederate = federatesHolder->getFederate(theFederate);
  if (currFederate == NULL)
  {
    throw GeRtiFactory::RTIinternalError(L"FederationManagement::could not find federate");
  }

  currFederate->federateRestoreComplete(theSuccess);
  currFederate->setAlive();

  // Check all restore complete flags.
  federatesHolder->getFederates(feds);
  for (itFed = feds.begin(); itFed != feds.end(); itFed++)
  {
    currFederate = federatesHolder->getFederate(*itFed);
    if (currFederate->restoreComplete == false)
    {
      allComplete = false;
    }
    if (currFederate->restoreSuccess == false)
    {
      allSuccess = false;
    }
  }

  // All federates in federation have restored their state.
  if (allComplete)
  {
    federationRestored(allSuccess, failureReason);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::federateSaveComplete(const GeRtiFactory::GeRtiHandle &theFederate, const bool &theSuccess, const std::string &theSaveData)
{
  CORBA::WChar *wChar = L"";
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet feds;
  GERTICO::HandleSet::iterator itFed;
  GeRtiFactory::SaveFailureReason failureReason = GeRtiFactory::rtiUnableToSave;
  bool allComplete = true;
  bool allSuccess = true;

  if (getRestoreInProgress())
  {
    throw GeRtiFactory::RestoreInProgress(wChar);
  }

  if (getSaveInProgress() == false)
  {
    throw GeRtiFactory::SaveNotInitiated(wChar);
  }


  pm.acquire();

  currFederate = federatesHolder->getFederate(theFederate);
  if (currFederate == NULL)
  {
    pm.release();
    throw GeRtiFactory::RTIinternalError(L"FederationManagement::could not find federate");
  }

  if (currFederate->saveBegun == false)
  {
    pm.release();
    throw GeRtiFactory::SaveNotInitiated(wChar);
  }

  // Set save complete flag for the current federate.
  currFederate->federateSaveComplete(theSuccess, theSaveData);
  currFederate->setAlive();

  // Check all save complete flags.
  federatesHolder->getFederates(feds);
  for (itFed = feds.begin(); itFed != feds.end(); itFed++)
  {
    currFederate = federatesHolder->getFederate(*itFed);
    if (currFederate->saveComplete == false)
    {
      allComplete = false;
    }
    if (currFederate->saveSuccess == false)
    {
      allSuccess = false;
    }
  }

  // All federates in federation have saved their state.
  if (allComplete)
  {
    federationSaved(allSuccess, failureReason);
  }

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::federationRestored(const bool &allSuccess, const GeRtiFactory::RestoreFailureReason &theFailureReason)
{
  GERTICO::FederationRestoredJob *newFederationRestoredJob;

  if (allSuccess)
  {
    restoree();
  }

  newFederationRestoredJob = new GERTICO::FederationRestoredJob(*federatesHolder, restoreInProgress, allSuccess, theFailureReason, concurrencyFlag);
  federationJobs.add (newFederationRestoredJob);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::federationSaved(const bool &allSuccess, const GeRtiFactory::SaveFailureReason &theFailureReason)
{
  GERTICO::FederationSavedJob *newFederationSavedJob;
  std::wstring ws;

  if (allSuccess)
  {
    savee();
  }

  newFederationSavedJob = new GERTICO::FederationSavedJob(*federatesHolder, saveInProgress, allSuccess, theFailureReason, concurrencyFlag);
  federationJobs.add (newFederationSavedJob);

  managementObjectModel->setNextSaveName(ws);
#ifdef IEEE_1516
  std::auto_ptr<GERTICO::GeRtiFedTime> noTime;
  managementObjectModel->setNextSaveTime(noTime);
#else
  managementObjectModel->setNextSaveTime(zeroTimeStr);
#endif
  if (nextSaveTime != NULL)
  {
    delete nextSaveTime;
    nextSaveTime = NULL;
  }

  saveRequested = false;
  saveInProgress = false;
  saveTimeReachedFlag = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::getNextSaveTime (std::string &theNextSaveTime)
{
  if (nextSaveTime)
  {
    char buf[512];
    nextSaveTime->getPrintableString (buf);
    theNextSaveTime = buf;
  }
  else
  {
    theNextSaveTime = "";
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::getSaveRequestedTime(GERTICO::GeRtiFedTime &theFedTime)
{
  if (nextSaveTime)
  {
    theFedTime = *nextSaveTime;
  }
  else
  {
    theFedTime.setPositiveInfinity();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::getNextSaveName(std::wstring &theNextSaveName)
{
  theNextSaveName = nextSaveName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::FederationManagement::getRegionSpace(const GeRtiFactory::GeRtiHandle &theRegion)
{
  GeRtiFactory::GeRtiHandle ret;

  ret = runTimeObjectDB->getRegionSpace(theRegion);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagement::getRestoreInProgress (void)
{
  return restoreInProgress;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagement::getSaveInProgress (void)
{
  return saveInProgress;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagement::gotSaveRequested(void)
{
  bool ret = false;

  if (saveInProgress || saveRequested)
  {
    ret = true;
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::FederationManagement::getSpaceHandle(const std::wstring &theSpace)
{
  GeRtiFactory::GeRtiHandle ret;

  ret = runTimeObjectDB->getRoutingSpaceHandle(theSpace);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::initiateFederateSave(void)
{
  saveInProgress = true;
  saveRequested = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::initialize (void)
{
  // check if allready initialized
  if (parser != 0)
  {
    return;
  }

  // Initialize the XML4C system
  try
  {
    XMLPlatformUtils::Initialize();
  }

  catch (const XMLException &)
  {
//    std::cerr << "Error during initialization! :\n"
//         << StrX(toCatch.getMessage()) << std::endl;
  }

  // Instantiate the DOM parser.
  parser = new XercesDOMParser;
  parser->setValidationScheme(XercesDOMParser::Val_Auto);

  // And create our error handler and install it
  parser->setErrorHandler(HLAparseErrorHandler::getErrorHandler());
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagement::parseEnv(char *out, char *in)
{
  bool gotClosing = false;
  bool gotEnv = false;
  bool ret = false;
  char *b;
  char env[128];
  size_t i;
  size_t j;
  size_t k;
  size_t l;
  size_t len;

  len = strlen(in);

  for (i = 0, l = 0; i < len; i++, l++)
  {
    if (in[i] == '$' && in[i + 1] == '(')
    {
      gotClosing = false;
      for (j = i + 2, k = 0; j < len; j++, k++)
      {
        if (in[j] == ')')
        {
          gotClosing = true;
          gotEnv = true;
          env[k] = '\0';
          b = getenv(env);
          if (b)
          {
            strcpy(&out[l], b);
            l += strlen(b) - 1;
            i = j;
          }
          else
          {
            std::cout << "Missing environment variable " << env << std::endl;
            ret = true;
            strncpy(&out[l], &in[i], j - i + 1);
            out[l + j - i + 1] = '\0';
            l += j - i;
            i = j;
          }
          break;
        }
        env[k] = in[j];
      }
      if (gotClosing == false)
      {
        std::cout << "Missing closing bracket" << std::endl;
        ret = true;
      }
    }
    if (gotEnv)
    {
      gotEnv = false;
      continue;
    }
    out[l] = in[i];
  }
  out[l] = '\0';

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederationManagement::parseFromFile (void)
{
  DOMDocument *doc;
  std::string fedSaveLabel;
  std::string s;
  std::string t;
  std::wstring fedName;

  managementObjectModel->getFederationName(fedName);
  GERTICO::Mapper::mapStringFromWstring(s, fedName);
  s.append("_");
  GERTICO::Mapper::mapStringFromWstring(fedSaveLabel, federationSaveLabel);
  s.append(fedSaveLabel);
  s.append(".xml");

  initialize ();

#ifdef _WIN32
  if ((_access (s.c_str (), 0)) == -1)
#else
  if ((access (s.c_str (), 0)) == -1)
#endif
  {
    t = "Cannot read saved file ";
    t.append (s);
    // Error.
    return true;
//    throw GeRtiFactory::RTIinternalError (t.c_str ());
  }

  parser->parse (s.c_str());
  doc = parser->getDocument();
  if (doc != 0)
  {
    domElement = doc->getDocumentElement();
    if (domElement != 0)
    {
      if (checkFederationCounts ())
      {
        // Error.
        return true;
      }
    }
    else
    {
      t = "Invalid xml file ";
      t.append (s);
      // Error.
      return true;
    }
  }

  // No error.
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::performDeleteObjects(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator itHS;
  GeRtiFactory::UserSuppliedTag userSuppliedTag;

  pm.acquire();

  // Get a list of object ids for any owned attributes of theFederate
  objectManagement->getOwnedObjectIds(theFederate, objects);

  pm.release();

  for (itHS = objects.begin(); itHS != objects.end(); itHS++)
  {
    // Since we are in resignFederationExecution, ignore exceptions.
    try
    {
      objectManagement->deleteObjectInstance(theFederate, *itHS, userSuppliedTag);
    }
    catch(...)
    {
      continue;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::performReleaseAttributes(const GeRtiFactory::GeRtiHandle &theFederate)
{
  CORBA::ULong i;
  CORBA::ULong length;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator itObject;
  GERTICO::HandleSet::iterator itHS;
  GeRtiFactory::Handles attributes;
  size_t len;

  pm.acquire();

  registeredObjectsHolder->getObjectIds(objects);
  for (itObject = objects.begin(); itObject != objects.end(); itObject++)
  {
    GERTICO::HandleSet theAttributes;
    runTimeObjectDB->getOwnedObjectAttributes(*itObject, theFederate, theAttributes, true);

    len = theAttributes.size();
    if (len == 0)
    {
      // The federate owns no object instance attributes.
      continue;
    }
//
//    itHS = theAttributes.find(runTimeObjectDB->getPrivilegeToDeleteId());
//    if (itHS != theAttributes.end())
//    {
//      // The federate owns privilege to delete.
//      continue;
//    }
//
    // Convert to CORBA SEQUENCE.
    GERTICO::Mapper::mapULongSizet(length, len);
    attributes.length(length);
    for (itHS = theAttributes.begin(), i = 0; itHS != theAttributes.end(); itHS++, i++)
    {
      attributes[i] = *itHS;
    }

    // Since we are in resignFederationExecution, ignore exceptions.
    try
    {
      ownershipMaster->unconditionalAttributeOwnershipDivestiture(theFederate, *itObject, attributes);
    }
    catch(GeRtiFactory::ObjectNotKnown)
    {
      continue;
    }
    catch(GeRtiFactory::AttributeNotDefined)
    {
      continue;
    }
    catch(GeRtiFactory::AttributeNotOwned)
    {
      continue;
    }
    catch(GeRtiFactory::FederateNotExecutionMember)
    {
      continue;
    }
    catch(GeRtiFactory::ConcurrentAccessAttempted)
    {
      continue;
    }
    catch(GeRtiFactory::SaveInProgress)
    {
      continue;
    }
    catch(GeRtiFactory::RestoreInProgress)
    {
      continue;
    }
    catch(GeRtiFactory::RTIinternalError)
    {
      continue;
    }
  }

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
int GERTICO::FederationManagement::process (void)
{
  bool ret;

  if (ps->acquire () == -1)
  {
    // Do not have the semaphore: try again.
    ACE_OS::sleep(1);
    return 0;
  }

  if (notDone == false)
  {
    return 0;
  }

  if (syncPointHandler->process ())
  {
    return 1;
  }

  ret = federationJobs.performJobs(true);

  // Process events.
  if (federationManagementEC)
  {
    federationManagementEC->eventHandler->process();
  }

  std::auto_ptr<GERTICO::GeRtiFedTime> galt(geRtiFedTimeFactory.makeZero());
  if (federationManagementEC)
  {
    federationManagementEC->eventHandler->timeService->queryGALT(0, *galt);
  }
  objectManagement->process(*galt);

  return 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::processLive(void)
{
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  Federate *currFederate;
  GeRtiFactory::ResignAction resignAction;
  double diffTime;
  double doubleCurrentTime;

  // Delete any federates which have previously resigned.
  federatesHolder->pruneResignedFederates();

  // Get current time.
  ACE_Time_Value currentTime = ACE_OS::gettimeofday();

  doubleCurrentTime = currentTime.sec() + currentTime.usec() / 1000000.0;

  if (gotPreviousTime == false)
  {
    doublePreviousTime = doubleCurrentTime;
    gotPreviousTime = true;
    return;
  }

  diffTime = doubleCurrentTime - doublePreviousTime;

  if (diffTime < 1.0)
  {
    return;
  }

  doublePreviousTime = doubleCurrentTime;

  federatesHolder->getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    currFederate = federatesHolder->getFederate(*itFederate);
    if (currFederate)
    {
      if (currFederate->isJoinedFinished() == false)
      {
        continue;
      }
      if (currFederate->testAlive())
      {
        currFederate->resetAlive();
      }
      else
      {
        try
        {
          currFederate->ping();
        }
        catch (CORBA::SystemException &)
        {
          std::cout << "Federate not alive" << std::endl;
          switch(gerticoConf.resignAction)
          {
            case 0:
            {
              resignAction = GeRtiFactory::unconditionallyDivestAttributes;
              break;
            }
            case 1:
            {
              resignAction = GeRtiFactory::deleteObjects;
              break;
            }
            case 2:
            {
              resignAction = GeRtiFactory::cancelPendingOwnershipAquisitions;
              break;
            }
            case 3:
            {
              resignAction = GeRtiFactory::deleteObjectsThenDivest;
              break;
            }
            case 4:
            {
              resignAction = GeRtiFactory::cancelThenDeleteThenDivest;
              break;
            }
            case 5:
            {
              resignAction = GeRtiFactory::noAction;
              break;
            }
            default:
            {
#ifdef IEEE_1516
              resignAction = GeRtiFactory::cancelThenDeleteThenDivest;
#else
              resignAction = GeRtiFactory::deleteObjectsThenDivest;
#endif
              break;
            }
          }
          resignFederationExecution(resignAction, currFederate->getId());
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::registerSynchronizationPoint (const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theLabel, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::Handles &designators)
{
  // Check save/restore status and possibly throw an exception.
  checkSaveRestore ();

  syncPointHandler->registerSynchronizationPoint (theLabel, theTag, designators, theFederate);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::requestFederationRestore (const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theFederationSaveLabel)
{
  GERTICO::BeginFederationRestoreJob *newBeginFederationRestoreJob;
  bool success = true;

  // Check save/restore status and possibly throw an exception.
  checkSaveRestore ();

  pm.acquire ();
  federationSaveLabel = theFederationSaveLabel;
  if (parseFromFile ())
  {
    success = false;
  }

  restoreInProgress = true;
  pm.release ();

  newBeginFederationRestoreJob = new GERTICO::BeginFederationRestoreJob(*federatesHolder, theFederate, theFederationSaveLabel, success, restoreInProgress);
  federationJobs.add (newBeginFederationRestoreJob);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::requestFederationSave(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theLabel)
{
  CORBA::WChar *wChar = L"";
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  bool b = true;

  // Check save/restore status and possibly throw an exception.
  checkSaveRestore ();
  if (saveTimeReachedFlag)
  {
    throw GeRtiFactory::SaveInProgress(wChar);
  }

  pm.acquire ();

  // Overwrite any previous save which has not been initiated.
  federatesHolder->getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    currFederate = federatesHolder->getFederate(*itFederate);
    if (currFederate)
    {
      if (*itFederate == theFederate)
      {
        b = false;
      }
      else
      {
        b = true;
      }
      currFederate->initiateFederateSave(theLabel, b);
      currFederate->setAlive();
    }
  }

  nextSaveName.assign (theLabel);
  managementObjectModel->setNextSaveName(theLabel);
  if (nextSaveTime != NULL)
  {
    delete nextSaveTime;
  }
  nextSaveTime = NULL;
#ifdef IEEE_1516
  std::auto_ptr<GERTICO::GeRtiFedTime> noTime;
  managementObjectModel->setNextSaveTime(noTime);
#else
  managementObjectModel->setNextSaveTime(zeroTimeStr);
#endif

  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::requestFederationSave(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theLabel, GERTICO::GeRtiFedTime &theTime)
{
  CORBA::WChar *wChar = L"requestFederationSave";
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  bool b = true;
#ifndef IEEE_1516
  char buff[256];
#endif
  std::string s;

  // Check save/restore status and possibly throw an exception.
  checkSaveRestore ();
  if (saveTimeReachedFlag)
  {
    throw GeRtiFactory::SaveInProgress(wChar);
  }
  saveRequested = true;

  pm.acquire ();

  nextSaveName.assign(theLabel);
  managementObjectModel->setNextSaveName(theLabel);
  nextSaveTime = geRtiFedTimeFactory.makeZero();
  *nextSaveTime = theTime;
#ifdef IEEE_1516
  std::auto_ptr<GERTICO::GeRtiFedTime> geRtiFedTime(geRtiFedTimeFactory.makeZero());
  *geRtiFedTime = theTime;
  managementObjectModel->setNextSaveTime(geRtiFedTime);
#else
  nextSaveTime->getPrintableString(buff);
  s = buff;
  managementObjectModel->setNextSaveTime(s);
#endif

  // Overwrite any previous save which has not been initiated.
  federatesHolder->getFederates(federates);
  for (itFederate = federates.begin (); itFederate != federates.end (); itFederate++)
  {
    currFederate = federatesHolder->getFederate(*itFederate);
    if (currFederate)
    {
      if (*itFederate == theFederate)
      {
        b = false;
      }
      else
      {
        b = true;
      }
      currFederate->initiateFederateSaveWithTime(theLabel, theTime, *nextSaveTime, b);
      currFederate->setAlive();
    }
  }

  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::requestFederateSaveStart(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theLabel, const GeRtiFactory::Time &theTime, const bool &theBool)
{
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::GeRtiFedTime *fedTime = NULL;
  bool nonConstrainedAllowed = true;

  if (theLabel != nextSaveName)
  {
    throw GeRtiFactory::StartNotAllowed(L"requestFederateSaveStart");
  }

  if (theBool)
  {
    GERTICO::ConvertTime::mapItGeRtiFedTime(geRtiFedTimeFactory, &fedTime, theTime);
    if (!(*fedTime == *nextSaveTime))
    {
      delete fedTime;
      throw GeRtiFactory::StartNotAllowed(L"requestFederateSaveStart");
    }
  }
  delete fedTime;

  federatesHolder->getFederates(federates);
  for (itFederate = federates.begin (); itFederate != federates.end (); itFederate++)
  {
    currFederate = federatesHolder->getFederate(*itFederate);
    if (currFederate)
    {
      if (currFederate->getTimeConstrained())
      {
        if (currFederate->saveInitiated == false)
        {
          nonConstrainedAllowed = false;
        }
      }
    }
  }

  currFederate = federatesHolder->getFederate(theFederate);
  if (currFederate)
  {
    if (currFederate->getTimeConstrained() == false)
    {
      if (nonConstrainedAllowed == false)
      {
        throw GeRtiFactory::StartNotAllowed(L"not all time-constrained initiated");
      }
    }
    currFederate->saveInitiated = true;
  }

  initiateFederateSave();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::resignFed(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theFedType)
{
  FedCounts::iterator itFC;

  itFC = fedCounts.find (theFedType);
  if (itFC != fedCounts.end ())
  {
    itFC->second -= 1;
    if (itFC->second == 0)
    {
      fedCounts.erase (itFC);
    }
  }

  syncPointHandler->resignFed (theFederate);

  // NEED MORE LOGIC! XXXXX
  saveInProgress = false;
  saveRequested = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::resignFederationExecution(const GeRtiFactory::ResignAction &theResignAction, const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::Federate *currFed;
  GERTICO::HandleSet pubObjects;
  GERTICO::HandleSet objects;
  GERTICO::HandleSetMap acquiringFedObjects;
  GERTICO::HandleSetMap subObjectsMap;
  GeRtiFactory::RestoreFailureReason restoreFailureReason = federateResignedDuringRestore;
  GeRtiFactory::SaveFailureReason saveFailureReason = federateResignedDuringSave;
  GeRtiFactory::UserSuppliedTag theTag;

  // Check if save in progress.
  if (getSaveInProgress())
  {
    federationSaved(false, saveFailureReason);
  }

  // Check if restore in progress.
  if (getRestoreInProgress())
  {
    federationRestored(false, restoreFailureReason);
  }

/*
  enum ResignAction {
    unconditionallyDivestAttributes,
    deleteObjects,
    cancelPendingOwnershipAquisitions,
    deleteObjectsThenDivest,
    cancelThenDeleteThenDivest,
    noAction
  };
*/
  switch (theResignAction)
  {
    case GeRtiFactory::unconditionallyDivestAttributes:
    {
      performReleaseAttributes(theFederate);
      break;
    }
    case GeRtiFactory::deleteObjects:
    {
      if (registeredObjectsHolder->ownsAnyAttributeInstancesNoPriv(theFederate, runTimeObjectDB->getPrivilegeToDeleteId()))
      {
        throw GeRtiFactory::FederateOwnsAttributes(L"resignClient");
      }
      performDeleteObjects(theFederate);
      break;
    }
#ifdef IEEE_1516
    case GeRtiFactory::cancelPendingOwnershipAquisitions:
    {
//      performCancel(theFederate);
      break;
    }
#endif
    case GeRtiFactory::deleteObjectsThenDivest:
    {
      performDeleteObjects(theFederate);
      performReleaseAttributes(theFederate);
      break;
    }
#ifdef IEEE_1516
    case GeRtiFactory::cancelThenDeleteThenDivest:
    {
//      performCancel(theFederate);
      performDeleteObjects(theFederate);
      performReleaseAttributes(theFederate);
      break;
    }
#endif
    case GeRtiFactory::noAction:
    {
      if (registeredObjectsHolder->ownsAnyAttributeInstances(theFederate))
      {
        throw GeRtiFactory::FederateOwnsAttributes(L"resignClient");
      }
      break;
    }
    default:
    {
      throw GeRtiFactory::InvalidResignAction(L"unknownValue");
    }
  }

  pm.acquire();

  // Get the federate.
  currFed = federatesHolder->getFederate(theFederate);
  if (currFed)
  {
    GERTICO::HandleSet objects;

    // Unset acquiring flags for this federate.
    currFed->getKnownObjects(objects);
    registeredObjectsHolder->cancelPendingAcquisitions(theFederate, objects);

    // Get publisher/subscriber information from federate.
    currFed->getPublishedObjectClasses(pubObjects);
    currFed->getMaps(subObjectsMap);

    // Delete information and inactivate any publishers/subscribers.
    declarationManagementRTI->delFedInteractions(theFederate, pubObjects, subObjectsMap);

//    federationManagementEC->eventHandler->timeService->resignFederationExecution(theFederate);

    // Delete entry from map.
    federatesHolder->deleteFederate(theFederate);
    resignFed(theFederate, currFed->federateType);
  }

  pm.release ();

  managementObjectModel->resignFederationExecutionMom(theFederate);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::restoree(void)
{
  GERTICO::Federate *federate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::Region *region;
  DOMNode* child;

  // Restore using XML data.
  for (child = domElement->getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode(federationState.c_str())) == 0)
      {
        restore(*((DOMElement*) child));
      }

      if (XMLString::compareString(child->getNodeName(),XMLString::transcode("interactions")) == 0)
      {
        declarationManagementRTI->restore(*((DOMElement*) child));
      }

      if (XMLString::compareString(child->getNodeName(),XMLString::transcode("runTimeObjectDB")) == 0)
      {
        runTimeObjectDB->restore(*((DOMElement*) child));
      }
    }
  }

  // Update some federate data.
  federatesHolder->getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    federate = federatesHolder->getFederate(*itFederate);
    if (federate)
    {
      CORBA::ULong length;
      size_t len;
      runTimeObjectDB->getFederateRegions(*itFederate, regions);
      for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
      {
        GeRtiFactory::Extents extents;
        region = runTimeObjectDB->getRegion(*itRegion);
        if (region)
        {
          CORBA::ULong ind;
          GERTICO::Extent *extent;
          GERTICO::ExtentMap *extentMap;
          GERTICO::ExtentMap::iterator itExtent;
          GERTICO::Range *range;
          GERTICO::RangeMap *rangeMap;
          GERTICO::RangeMap::iterator itRangeMap;
          size_t lengthRanges;

          extentMap = region->getExtents();
          len = extentMap->size();
          GERTICO::Mapper::mapULongSizet(length, len);
          extents.length(length);
          for (itExtent = extentMap->begin (), ind = 0; itExtent != extentMap->end (); itExtent++, ind++)
          {
            CORBA::ULong j;

            extent = &itExtent->second;
            rangeMap = extent->getRangeMap();
            lengthRanges = rangeMap->size();
            GERTICO::Mapper::mapULongSizet(length, lengthRanges);
            extents[ind].length(length);
            for (itRangeMap = rangeMap->begin(), j = 0; itRangeMap != rangeMap->end(); itRangeMap++, j++)
            {
              range = &itRangeMap->second;
              extents[ind][j].dimension = range->dimension;
              extents[ind][j].lower = range->lower;
              extents[ind][j].upper = range->upper;
            }
          }

          federate->loadRegion(region->getSpace(), *itRegion, extents);
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::restore (DOMElement &theDOMElement)
{
  DOMNode* child;
  GERTICO::Federate *currFederate;
  char *tmpChar;
  FedTypes fedTypes;
  std::string tmpString;
  std::wstring tmpWstring;
  unsigned long tmpUL;

  clear ();

  for (child = theDOMElement.getFirstChild (); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (federateIdsStr.c_str ())) == 0)
      {
        DOMNode* subChild;
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (federateStr.c_str ())) == 0)
            {
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpUL);
              tmpString = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (typeStr.c_str ())));
              GERTICO::Mapper::mapWstringFromChar(tmpWstring, tmpString.c_str());
              fedTypes[tmpUL] = tmpWstring;
            }
          }
        }
      }
    }
  }

  federatesHolder->rehashFederateIds(fedTypes);

  for (child = theDOMElement.getFirstChild (); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (federatesStr.c_str ())) == 0)
      {
        DOMNode* subChild;
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (federateStr.c_str ())) == 0)
            {
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpUL);
              currFederate = federatesHolder->getFederate(tmpUL);
              if (currFederate)
              {
                currFederate->restore (*((DOMElement *)subChild));
              }
            }
          }
        }
      }
    }
  }

  // Restore Time Management
  for (child = theDOMElement.getFirstChild (); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (federationTimeStr.c_str ())) == 0)
      {
        if (federationManagementEC)
        {
          federationManagementEC->eventHandler->timeService->restore(*((DOMElement*) child));
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::savee(void)
{
  DOMElement* elemLevel0;
  std::string federationName;
  std::string s;
  std::string saveName;
  std::wstring ws;

  // Initialize the XML4C2 system
  try
  {
    XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();
  }

  catch(const XERCES_CPP_NAMESPACE::XMLException &toCatch)
  {
    std::string s = "Error during Xerces-c Initialization: ";
    std::string t = StrX(toCatch.getMessage()).localForm();
    s.append(t);
    GERTICO::Mapper::mapWstringFromChar(ws, s.c_str());
    throw GeRtiFactory::RTIinternalError(ws.c_str());
  }

  PrintFilter   *myFilter = 0;

  try
  {
    // get a serializer, an instance of DOMWriter
    XMLCh tempStr[100];
    XMLString::transcode("LS", tempStr, 99);
    DOMImplementation *impl          = DOMImplementationRegistry::getDOMImplementation(tempStr);
    DOMWriter         *theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

    // set user specified end of line sequence and output encoding
    theSerializer->setNewLine(gMyEOLSequence);
    theSerializer->setEncoding(gOutputEncoding);

    // plug in user's own filter
    if (gUseFilter)
    {
      // even we say to show attribute, but the DOMWriter
      // will not show attribute nodes to the filter as
      // the specs explicitly says that DOMWriter shall
      // NOT show attributes to DOMWriterFilter.
      //
      // so DOMNodeFilter::SHOW_ATTRIBUTE has no effect.
      // same DOMNodeFilter::SHOW_DOCUMENT_TYPE, no effect.
      //
      myFilter = new PrintFilter(DOMNodeFilter::SHOW_ELEMENT   |
                                    DOMNodeFilter::SHOW_ATTRIBUTE |
                                    DOMNodeFilter::SHOW_DOCUMENT_TYPE);
      theSerializer->setFilter(myFilter);
    }

    // plug in user's own error handler
    DOMErrorHandler *myErrorHandler = new PrintErrorHandler();
    theSerializer->setErrorHandler(myErrorHandler);

    // set feature if the serializer supports the feature/mode
    if (theSerializer->canSetFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections))
    {
      theSerializer->setFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections);
    }

    if (theSerializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent))
    {
      theSerializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent);
    }

    if (theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint))
    {
      theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint);
    }

    if (theSerializer->canSetFeature(XMLUni::fgDOMWRTBOM, gWriteBOM))
    {
      theSerializer->setFeature(XMLUni::fgDOMWRTBOM, gWriteBOM);
    }

    //
    // Plug in a format target to receive the resultant
    // XML stream from the serializer.
    //
    // StdOutFormatTarget prints the resultant XML stream
    // to stdout once it receives any thing from the serializer.
    //
    XMLFormatTarget *myFormTarget;
    std::wstring ws;
    managementObjectModel->getFederationName(ws);
    GERTICO::Mapper::mapStringFromWstring(s, ws);
    s.append("_");
    getNextSaveName(nextSaveName);
    GERTICO::Mapper::mapStringFromWstring(saveName, nextSaveName);
    s.append(saveName);
    s.append(".xml");
    goutputfile = ACE_OS::strdup(s.c_str());
    if (goutputfile)
    {
      myFormTarget = new LocalFileFormatTarget(goutputfile);
    }
    else
    {
      myFormTarget = new StdOutFormatTarget();
    }

    // get the DOM representation
    XMLString::transcode("saveFederation", tempStr, 99);
    DOMDocument                     *doc = impl->createDocument(
            0,                    // root element namespace URI.
            tempStr,         // root element name
            0);

    DOMElement* rootElem = doc->getDocumentElement();

    // Federate type and count.
    save(*doc, *rootElem);

    // Interactions
    declarationManagementRTI->save(*doc, *rootElem);

    // runTimeObjectDB
    XMLString::transcode("runTimeObjectDB", tempStr, 99);
    elemLevel0 = doc->createElement(tempStr);
    rootElem->appendChild(elemLevel0);
    runTimeObjectDB->save(*doc, *elemLevel0);

    // do the serialization through DOMWriter::writeNode();
    //
    theSerializer->writeNode(myFormTarget, *doc);

    delete theSerializer;

    //
    // Filter, formatTarget and error handler
    // are NOT owned by the serializer.
    //
    delete myFormTarget;
    delete myErrorHandler;

    if (gUseFilter)
    {
      delete myFilter;
    }
  }
  catch(XMLException& e)
  {
    std::string s = "Error occurred during creation of output transcoder: ";
    std::string t = StrX(e.getMessage()).localForm();
    s.append(t);
    GERTICO::Mapper::mapWstringFromChar(ws, s.c_str ());
    throw GeRtiFactory::RTIinternalError(ws.c_str());
  }


  // And call the termination method
  XMLPlatformUtils::Terminate();

  delete gOutputEncoding;        // const problems.
  delete gMyEOLSequence;         // const problems.
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::save (DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  FedCounts::iterator itFC;
  GERTICO::Federate *currFederate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  std::string s;

  XMLString::transcode(federationState.c_str (), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(federateTypesStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  for (itFC = fedCounts.begin (); itFC != fedCounts.end (); itFC++)
  {
    XMLString::transcode(federateTypeStr.c_str (), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    XMLString::transcode(typeStr.c_str (), tempStr, 99);
    GERTICO::Mapper::mapStringFromWstring(s, itFC->first);
    XMLString::transcode(s.c_str (), tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    XMLString::transcode(countStr.c_str (), tempStr, 99);
    sprintf (buf, "%lu", itFC->second);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  XMLString::transcode(federateIdsStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  // Need to know the specific id to type for each federate.
  federatesHolder->getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    currFederate = federatesHolder->getFederate(*itFederate);
    if (currFederate == NULL)
    {
      continue;
    }
    XMLString::transcode(federateStr.c_str (), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    XMLString::transcode(typeStr.c_str (), tempStr, 99);
    GERTICO::Mapper::mapStringFromWstring(s, currFederate->federateType);
    XMLString::transcode(s.c_str (), tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    XMLString::transcode(idStr.c_str (), tempStr, 99);
    sprintf (buf, "%lu", currFederate->getId ());
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  XMLString::transcode(federatesStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  // Need to know the specific id to type for each federate.
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    currFederate = federatesHolder->getFederate(*itFederate);
    if (currFederate)
    {
      currFederate->save (theDOMDocument, *elemLevel1);
    }
  }

  // Save Primary Time Master data
  XMLString::transcode(federationTimeStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  if (federationManagementEC)
  {
    federationManagementEC->eventHandler->timeService->save(theDOMDocument, *elemLevel1);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::saveTimeReached(void)
{
  saveTimeReachedFlag = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::setAlive(GeRtiFactory::GeRtiHandle const &theandle)
{
  GERTICO::Federate *federate;

  federate = federatesHolder->getFederate(theandle);
  if (federate != NULL)
  {
    federate->setAlive();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::synchronizationPointAchieved(const std::wstring &theLabel, const GeRtiFactory::GeRtiHandle &theFederate)
{
  // Check save/restore status and possibly throw an exception.
  checkSaveRestore ();

  syncPointHandler->synchronizationPointAchieved (theLabel, theFederate);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::terminate (void)
{
  notDone = false;
  if (federationManagementEC)
  {
    federationManagementEC->eventHandler->timeService->terminate();
  }
  ps->release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederationManagement::wallClockWorker(void)
{
  processLive();
  managementObjectModel->wallClockWorker();
}
