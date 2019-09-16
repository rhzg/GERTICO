/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GeRtiFactoryI.cpp
**
*******************************************************************************/

#include <vector>
#include "ace/Thread_Manager.h"
#include "GeRtiFactoryI.h"
#include "Util/GeRtiOrb.h"
#include "Util/Mapper.h"
#include "Util/NextHandle.h"

/********************************* Gal begin *********************************/
#ifdef GalDebug
#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

static class Repository_l *FM=(Repository::getSingleInstance())->getRepository_l("GeRtiFM.res","GeRtiFM");

static class Event *GeRti_FM_feds_i=FM->getRefEvent("GeRti_FM_feds_i");
static class Event *GeRti_FM_d=FM->getRefEvent("GeRti_FM_d");
static class Event *GeRti_FM_e=FM->getRefEvent("GeRti_FM_e");
static class Event *GeRti_FM_w=FM->getRefEvent("GeRti_FM_w");
#endif
/*********************************** Gal end *********************************/

#define MAX_TXT 1024
static char galMsg[MAX_TXT];

ACE_Semaphore *psClean;
bool cleanRunning = false;
static unsigned int GERTICO_POA_counter = 0;

ACE_Thread_Mutex GeRtiFactory_Factory_i::spm;
EventHubMap GeRtiFactory_Factory_i::eventHubs;
FederationManagementMap GeRtiFactory_Factory_i::fedMan;

std::vector <GeRtiFactory_FederationManagement_i *>deleteVector;

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *clean_up(void *arg)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "clean_up", "Enter");
                           #endif   // inserted by Gal converter
  GeRtiFactory_FederationManagement_i *currFederation;
  size_t size;
  std::vector <GeRtiFactory_FederationManagement_i *>::iterator it;

  while (1)
  {
    if (psClean->acquire() == -1)
    {
      // Do not have the semaphore: error.
      ACE_OS::sleep(1);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_e, "clean_up", "semaphore problem");
                           #endif   // inserted by Gal converter
      return NULL;
    }

    GeRtiFactory_Factory_i::spm.acquire();
    for (it = deleteVector.begin(); it != deleteVector.end(); it = deleteVector.begin())
    {
      size = deleteVector.size();
      if (size < 11)
      {
        // Slow garbage collection - leave last ten federations time to finish their cleanup.
        break;
      }
      currFederation = *it;
      deleteVector.erase(it);
      GeRtiFactory_Factory_i::spm.release();
      currFederation->deactivateObject();
      ACE_OS::sleep(ACE_Time_Value(0,100000));
      delete currFederation;
      GeRtiFactory_Factory_i::spm.acquire();
    }
    GeRtiFactory_Factory_i::spm.release();
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "clean_up", "Leave");
                           #endif   // inserted by Gal converter
  return NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *fed_worker(void *arg)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "fed_worker", "Enter");
                           #endif   // inserted by Gal converter
  GeRtiFactory_FederationManagement_i *geRtiFactory_FederationManagement_i = (GeRtiFactory_FederationManagement_i *) arg;

  while (geRtiFactory_FederationManagement_i->federationManagement->notDone)
  {
    if (geRtiFactory_FederationManagement_i->federationManagement->process())
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_e, "fed_worker", "process error");
                           #endif   // inserted by Gal converter
    }
    geRtiFactory_FederationManagement_i->garbageCollection();
  }

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "fed_worker", "Leave");
                           #endif   // inserted by Gal converter
  return NULL;
}

// ---------------------------------------------------------------------------
// A thread to process work on a regular one second granularity wall clock
// time. eg. thread to watch for time management inactivity or mom management.
// ---------------------------------------------------------------------------
void *wallClockWorker(void *arg)
{
  GERTICO::FederationManagement *federationManagement = (GERTICO::FederationManagement *) arg;

  while (federationManagement->notDone)
  {
    federationManagement->wallClockWorker();
    federationManagement->ps->release();

    // Granularity of one second.
    ACE_OS::sleep(1);
  }

  return NULL;
}

// ---------------------------------------------------------------------------
// Implementation skeleton constructor
// ---------------------------------------------------------------------------
GeRtiFactory_FederationManagement_i::GeRtiFactory_FederationManagement_i
(
  GERTICO::GeRtiOrb &theGeRtiOrb,
  std::wstring const &theFedName,
  std::wstring const &theFedFile,
  GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory
) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory), myGeRtiOrb(theGeRtiOrb)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "GeRtiFactory_FederationManagement_i", "Enter");
                           #endif   // inserted by Gal converter
  CORBA::PolicyList policyListBestEffort;
  CORBA::PolicyList policyListReceiver;
  CORBA::PolicyList policyListSender;
  char tmpName[64];
  active = true;

  // Set up a nil poa manager reference.
  nilMgr = PortableServer::POAManager::_nil();

  // Create policy lists for child poas.
  policyListBestEffort.length(2);
  policyListBestEffort[0] = myGeRtiOrb.poaRootSenderBestEffort->create_implicit_activation_policy(PortableServer::IMPLICIT_ACTIVATION);
  policyListBestEffort[1] = myGeRtiOrb.poaRootSenderBestEffort->create_thread_policy(PortableServer::SINGLE_THREAD_MODEL);

  policyListReceiver.length(2);
  policyListReceiver[0] = myGeRtiOrb.poaRootReceiver->create_implicit_activation_policy(PortableServer::IMPLICIT_ACTIVATION);
  policyListReceiver[1] = myGeRtiOrb.poaRootReceiver->create_thread_policy(PortableServer::SINGLE_THREAD_MODEL);

  policyListSender.length(2);
  policyListSender[0] = myGeRtiOrb.poaRootReceiver->create_implicit_activation_policy(PortableServer::IMPLICIT_ACTIVATION);
  policyListSender[1] = myGeRtiOrb.poaRootReceiver->create_thread_policy(PortableServer::SINGLE_THREAD_MODEL);

  // Create and activate child poas.
  sprintf(tmpName, "POA%ud", GERTICO_POA_counter++);
  myPOA = myGeRtiOrb.poaRootReceiver->create_POA(tmpName, nilMgr, policyListReceiver);
  myPoaReceiverMgr = myPOA->the_POAManager();
  myPoaReceiverMgr->activate();

  sprintf(tmpName, "POA%ud", GERTICO_POA_counter++);
  myPoaBestEffort = myGeRtiOrb.poaRootSenderBestEffort->create_POA(tmpName, nilMgr, policyListBestEffort);
  myPoaBestEffortMgr = myPoaBestEffort->the_POAManager();
  myPoaBestEffortMgr->activate();

  sprintf(tmpName, "POA%ud", GERTICO_POA_counter++);
  myPoaSender = myGeRtiOrb.poaRootSenderReliable->create_POA(tmpName, nilMgr, policyListSender);
  myPoaSenderMgr = myPoaSender->the_POAManager();
  myPoaSenderMgr->activate();

  myName = theFedName;
  federationManagement = new GERTICO::FederationManagement(myGeRtiOrb, myPOA, myPoaBestEffort, myPoaSender, theFedName, theFedFile, idHandler, theGERTICOconf, geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);

  if (cleanRunning == false)
  {
    psClean = new ACE_Semaphore(0);
    ACE_Thread_Manager::instance()->spawn(ACE_reinterpret_cast(ACE_THR_FUNC, &clean_up), NULL);
    cleanRunning = true;
  }

  tid0 = ACE_Thread_Manager::instance()->spawn(ACE_reinterpret_cast(ACE_THR_FUNC, &fed_worker), this);

  tid2 = ACE_Thread_Manager::instance()->spawn(ACE_reinterpret_cast(ACE_THR_FUNC, &wallClockWorker), federationManagement, THR_NEW_LWP | THR_JOINABLE);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "GeRtiFactory_FederationManagement_i", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Implementation skeleton destructor
// ---------------------------------------------------------------------------
GeRtiFactory_FederationManagement_i::~GeRtiFactory_FederationManagement_i(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "~GeRtiFactory_FederationManagement_i", "Enter");
                           #endif   // inserted by Gal converter
  GeRtiFactory_GeRtiAmbassador_i *currFederate;
  FederatesMap::iterator it;
  delete federationManagement;
  pm.acquire();
  for (it = federates.begin(); it != federates.end(); it = federates.begin())
  {
    currFederate = it->second;
    federates.erase(it);
    delete currFederate;
  }
  for (it = federatesDeleted.begin(); it != federatesDeleted.end(); it = federatesDeleted.begin())
  {
    currFederate = it->second;
    federatesDeleted.erase(it);
    delete currFederate;
  }
  pm.release();
// Global semaphore: NO NOT DELETE!
//  delete psClean;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "~GeRtiFactory_FederationManagement_i", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GeRtiFactory_FederationManagement_i::isActive(void)
{
  return active;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::activateObject(void)
{
  FederationManagementVar = _this();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::deactivateObject(void)
{
  PortableServer::ObjectId_var objectId = myPOA->servant_to_id(this);
  myPOA->deactivate_object(objectId.in());
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
PortableServer::POA_ptr GeRtiFactory_FederationManagement_i::_default_POA(void)
{
  return PortableServer::POA::_duplicate(myPOA);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::Term(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "Term", "Enter");
                           #endif   // inserted by Gal converter
  federationManagement->terminate();
  ACE_Thread_Manager::instance()->wait_grp(tid0);
  ACE_Thread_Manager::instance()->wait_grp(tid2);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "Term", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::getEventHubCreateData(CORBA::ULong &theMomInteractionRoot, CORBA::ULong &theMomObjectRoot, CORBA::ULong &theInteractionRoot, CORBA::ULong &theObjectRoot, CORBA::ULong &thePrivilegeToDeleteId)
{
  // TODO
  // Manager
  std::wstring ws;
  
#ifdef IEEE_1516
  ws = L"HLAmanager";
  theMomInteractionRoot = federationManagement->supportingServices->getInteractionClassHandle(ws);
  
  ws = L"HLAmanager";
  theMomObjectRoot = federationManagement->supportingServices->findObjectClassHandle(ws);

  ws = L"HLAinteractionRoot";
  theInteractionRoot = federationManagement->supportingServices->getInteractionClassHandle(ws);
  
  ws = L"HLAobjectRoot";
  theObjectRoot = federationManagement->supportingServices->findObjectClassHandle(ws);

  ws = L"HLAobjectRoot.HLAprivilegeToDeleteObject";
//  thePrivilegeToDeleteId = federationManagement->supportingServices->
#else
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_FederationManagement_i::joinFederationExecution(const CORBA::WChar *theFederateType, const CORBA::WChar *eventHubName, GeRtiFactory::FederateAmbassador_ptr theFederateAmbassador_ptr, GeRtiFactory::GeRtiRestore_ptr geRtiRestoreReference, GeRtiFactory::EventHubFederation_out myEventHubFederation)
throw
(
  GeRtiFactory::FederateAlreadyExecutionMember,
  GeRtiFactory::FederationExecutionDoesNotExist,
  GeRtiFactory::CouldNotOpenFED,
  GeRtiFactory::ErrorReadingFED,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError,
  CORBA::SystemException
)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_feds_i)
                            {
                              sprintf(galMsg,"federateType=%ls", theFederateType);
                              E2(GeRti_FM_feds_i, "joinFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::FederateAmbassador_var federateAmbassador_var;
  GeRtiFactory::GeRtiRestore_var geRtiRestore_var;
  EventHubMap::iterator itEventHub;
  FederationReferencesMap::iterator itFederationReferencesMap;

  if (active == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                              sprintf(galMsg,"FederationExecutionDoesNotExist:federateType=%ls", theFederateType);
                              E2(GeRti_FM_w, "joinFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::FederationExecutionDoesNotExist(L"joinFederationExecution: federation destroyed");
  }

  federationManagement->checkSaveRestore();

  std::wstring s(theFederateType);

  GeRtiFactory_GeRtiAmbassador_i *newFederateData = new GeRtiFactory_GeRtiAmbassador_i(myPOA, *federationManagement, idHandler, geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);

  GeRtiFactory::GeRtiHandle id = newFederateData->getId();

  pm.acquire();
  federates[id] = newFederateData;
  pm.release();

  federateAmbassador_var = GeRtiFactory::FederateAmbassador::_duplicate(theFederateAmbassador_ptr);
  // remarshal / demarshal
  CORBA::String_var cbstr = myGeRtiOrb.orbReceiver->object_to_string(federateAmbassador_var.in());
  CORBA::Object_var new_ior = myGeRtiOrb.orbSenderReliable->string_to_object(cbstr.in());
  federateAmbassador_var = GeRtiFactory::FederateAmbassador::_narrow(new_ior.in());

  geRtiRestore_var = GeRtiFactory::GeRtiRestore::_duplicate(geRtiRestoreReference);
  // remarshal / demarshal
  cbstr = myGeRtiOrb.orbReceiver->object_to_string(geRtiRestore_var.in());
  new_ior = myGeRtiOrb.orbSenderReliable->string_to_object(cbstr.in());
  geRtiRestore_var = GeRtiFactory::GeRtiRestore::_narrow(new_ior.in());
  federationManagement->joinFederationExecution(id, s, federateAmbassador_var, geRtiRestore_var);
  itEventHub = GeRtiFactory_Factory_i::eventHubs.find(eventHubName);
  if (itEventHub != GeRtiFactory_Factory_i::eventHubs.end())
  {
    itFederationReferencesMap = itEventHub->second->federationReferencesMap.find(myName);
    if (itFederationReferencesMap != itEventHub->second->federationReferencesMap.end())
    {
      myEventHubFederation = GeRtiFactory::EventHubFederation::_duplicate(itFederationReferencesMap->second->eventHubFederationVar);
    }
  }
  else
  {
    federationManagement->ps->release();
    throw GeRtiFactory::RTIinternalError(L"joinFederationExecution: event hub not found");
  }

  // Allow other thread to continue;
  federationManagement->ps->release();

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_feds_i)
                            {
                              unsigned long ul;

                              ul = id;
                              sprintf(galMsg, "federate:%lu", ul);
                              E2(GeRti_FM_feds_i, "joinFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
  return id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::getMom(
    GeRtiFactory::Handles_out momHandles
  )
  throw(
    CORBA::SystemException,
    GeRtiFactory::ErrorReadingFED
  )
{
  std::wstring ws;

  momHandles = new GeRtiFactory::Handles();

#ifdef IEEE_1516
  // MOM Objects.
  // Manager object class.
  momHandles->length(122);
  (*momHandles)[0] = federationManagement->managementObjectModel->managerObject;
  (*momHandles)[1] = federationManagement->managementObjectModel->managerFederateObject;
  (*momHandles)[2] = federationManagement->managementObjectModel->managerFederateFederateHandle;
  (*momHandles)[3] = federationManagement->managementObjectModel->managerFederateFederateType;
  (*momHandles)[4] = federationManagement->managementObjectModel->managerFederateFederateHost;
  (*momHandles)[5] = federationManagement->managementObjectModel->managerFederateRTIversion;
  (*momHandles)[6] = federationManagement->managementObjectModel->managerFederateFDDid;
  (*momHandles)[7] = federationManagement->managementObjectModel->managerFederateTimeConstrained;
  (*momHandles)[8] = federationManagement->managementObjectModel->managerFederateTimeRegulating;
  (*momHandles)[9] = federationManagement->managementObjectModel->managerFederateAsynchronousDelivery;
  (*momHandles)[10] = federationManagement->managementObjectModel->managerFederateFederateState;
  (*momHandles)[11] = federationManagement->managementObjectModel->managerFederateTimeManagerState;
  (*momHandles)[12] = federationManagement->managementObjectModel->managerFederateLogicalTime;
  (*momHandles)[13] = federationManagement->managementObjectModel->managerFederateLookahead;
  (*momHandles)[14] = federationManagement->managementObjectModel->managerFederateGALT;
  (*momHandles)[15] = federationManagement->managementObjectModel->managerFederateLITS;
  (*momHandles)[16] = federationManagement->managementObjectModel->managerFederateROlength;
  (*momHandles)[17] = federationManagement->managementObjectModel->managerFederateTSOlength;
  (*momHandles)[18] = federationManagement->managementObjectModel->managerFederateReflectionsReceived;
  (*momHandles)[19] = federationManagement->managementObjectModel->managerFederateUpdatesSent;
  (*momHandles)[20] = federationManagement->managementObjectModel->managerFederateInteractionsReceived;
  (*momHandles)[21] = federationManagement->managementObjectModel->managerFederateInteractionsSent;
  (*momHandles)[22] = federationManagement->managementObjectModel->managerFederateObjectInstancesThatCanBeDeleted;
  (*momHandles)[23] = federationManagement->managementObjectModel->managerFederateObjectInstancesUpdated;
  (*momHandles)[24] = federationManagement->managementObjectModel->managerFederateObjectInstancesReflected;
  (*momHandles)[25] = federationManagement->managementObjectModel->managerFederateObjectInstancesDeleted;
  (*momHandles)[26] = federationManagement->managementObjectModel->managerFederateObjectInstancesRemoved;
  (*momHandles)[27] = federationManagement->managementObjectModel->managerFederateObjectInstancesRegistered;
  (*momHandles)[28] = federationManagement->managementObjectModel->managerFederateObjectInstancesDiscovered;
  (*momHandles)[29] = federationManagement->managementObjectModel->managerInteractionFederate;
  (*momHandles)[30] = federationManagement->managementObjectModel->managerInteractionFederateFederate;
  (*momHandles)[31] = federationManagement->managementObjectModel->managerFederateAdjustSetTiming;
  (*momHandles)[32] = federationManagement->managementObjectModel->managerFederateAdjustModifyAttributeState;
  (*momHandles)[33] = federationManagement->managementObjectModel->managerFederateAdjustModifyAttributeStateObjectInstance;
  (*momHandles)[34] = federationManagement->managementObjectModel->managerFederateAdjustModifyAttributeStateAttribute;
  (*momHandles)[35] = federationManagement->managementObjectModel->managerFederateAdjustModifyAttributeStateAttributeState;
  (*momHandles)[36] = federationManagement->managementObjectModel->managerFederateAdjustSetServiceReporting;
  (*momHandles)[37] = federationManagement->managementObjectModel->managerFederateAdjustSetServiceReportingState;
  (*momHandles)[38] = federationManagement->managementObjectModel->managerFederateAdjustSetExceptionReporting;
  (*momHandles)[39] = federationManagement->managementObjectModel->managerFederateReportReflectionsReceived;
  (*momHandles)[40] = federationManagement->managementObjectModel->managerFederateReportReflectionsReceivedTransportationType;
  (*momHandles)[41] = federationManagement->managementObjectModel->managerFederateReportReflectionsReceivedReflectCounts;
  (*momHandles)[42] = federationManagement->managementObjectModel->managerFederateReportInteractionsReceived;
  (*momHandles)[43] = federationManagement->managementObjectModel->managerFederateReportInteractionsReceivedTransportationType;
  (*momHandles)[44] = federationManagement->managementObjectModel->managerFederateReportInteractionsReceivedInteractionCounts;
  (*momHandles)[45] = federationManagement->managementObjectModel->managerFederateReportException;
  (*momHandles)[46] = federationManagement->managementObjectModel->managerFederateReportExceptionService;
  (*momHandles)[47] = federationManagement->managementObjectModel->managerFederateReportExceptionException;
  (*momHandles)[48] = federationManagement->managementObjectModel->managerFederateReportServiceInvocation;
  (*momHandles)[49] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationService;
  (*momHandles)[50] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationSuccessIndicator;
  (*momHandles)[51] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationSuppliedArguments;
  (*momHandles)[52] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationReturnedArguments;
  (*momHandles)[53] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationException;
  (*momHandles)[54] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationSerialNumber;
  (*momHandles)[55] = federationManagement->managementObjectModel->managerFederateServiceResignFederationExecution;
  (*momHandles)[56] = federationManagement->managementObjectModel->managerFederateServiceResignFederationExecutionResignAction;
  (*momHandles)[57] = federationManagement->managementObjectModel->managerFederateServiceSynchronizationPointAchieved;
  (*momHandles)[58] = federationManagement->managementObjectModel->managerFederateServiceSynchronizationPointAchievedLabel;
  (*momHandles)[59] = federationManagement->managementObjectModel->managerFederateServiceFederateSaveBegun;
  (*momHandles)[60] = federationManagement->managementObjectModel->managerFederateServiceFederateSaveComplete;
  (*momHandles)[61] = federationManagement->managementObjectModel->managerFederateServiceFederateSaveCompleteSuccessIndicator;
  (*momHandles)[62] = federationManagement->managementObjectModel->managerFederateServiceFederateRestoreComplete;
  (*momHandles)[63] = federationManagement->managementObjectModel->managerFederateServiceFederateRestoreCompleteSuccessIndicator;
  (*momHandles)[64] = federationManagement->managementObjectModel->managerFederateServicePublishObjectClassAttributes;
  (*momHandles)[65] = federationManagement->managementObjectModel->managerFederateServicePublishObjectClassObjectClass;
  (*momHandles)[66] = federationManagement->managementObjectModel->managerFederateServicePublishObjectClassAttributeList;
  (*momHandles)[67] = federationManagement->managementObjectModel->managerFederateServiceUnpublishObjectClassAttributes;
  (*momHandles)[68] = federationManagement->managementObjectModel->managerFederateServiceUnpublishObjectClassObjectClass;
  (*momHandles)[69] = federationManagement->managementObjectModel->managerFederateServicePublishInteractionClass;
  (*momHandles)[70] = federationManagement->managementObjectModel->managerFederateServicePublishInteractionClassInteractionClass;
  (*momHandles)[71] = federationManagement->managementObjectModel->managerFederateServiceUnpublishInteractionClass;
  (*momHandles)[72] = federationManagement->managementObjectModel->managerFederateServiceUnpublishInteractionClassInteractionClass;
  (*momHandles)[73] = federationManagement->managementObjectModel->managerFederateServiceSubscribeObjectClassAttributes;
  (*momHandles)[74] = federationManagement->managementObjectModel->managerFederateServiceSubscribeObjectClassAttributesObjectClass;
  (*momHandles)[75] = federationManagement->managementObjectModel->managerFederateServiceSubscribeObjectClassAttributesAttributeList;
  (*momHandles)[76] = federationManagement->managementObjectModel->managerFederateServiceSubscribeObjectClassAttributesActive;
  (*momHandles)[77] = federationManagement->managementObjectModel->managerFederateServiceUnsubscribeObjectClassAttributes;
  (*momHandles)[78] = federationManagement->managementObjectModel->managerFederateServiceUnsubscribeObjectClassObjectClass;
  (*momHandles)[79] = federationManagement->managementObjectModel->managerFederateServiceSubscribeInteractionClass;
  (*momHandles)[80] = federationManagement->managementObjectModel->managerFederateServiceSubscribeInteractionClassInteractionClass;
  (*momHandles)[81] = federationManagement->managementObjectModel->managerFederateServiceSubscribeInteractionClassActive;
  (*momHandles)[82] = federationManagement->managementObjectModel->managerFederateServiceUnsubscribeInteractionClass;
  (*momHandles)[83] = federationManagement->managementObjectModel->managerFederateServiceUnsubscribeInteractionClassInteractionClass;
  (*momHandles)[84] = federationManagement->managementObjectModel->managerFederateServiceDeleteObjectInstance;
  (*momHandles)[85] = federationManagement->managementObjectModel->managerFederateServiceDeleteObjectInstanceObjectInstance;
  (*momHandles)[86] = federationManagement->managementObjectModel->managerFederateServiceDeleteObjectInstanceTag;
  (*momHandles)[87] = federationManagement->managementObjectModel->managerFederateServiceDeleteObjectInstanceTimeStamp;
  (*momHandles)[88] = federationManagement->managementObjectModel->managerFederateServiceLocalDeleteObjectInstance;
  (*momHandles)[89] = federationManagement->managementObjectModel->managerFederateServiceLocalDeleteObjectInstanceObjectInstance;
  (*momHandles)[90] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeTransportationType;
  (*momHandles)[91] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeTransportationTypeObjectInstance;
  (*momHandles)[92] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeTransportationTypeAttributeList;
  (*momHandles)[93] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeTransportationTypeTransportationType;
  (*momHandles)[94] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeOrderType;
  (*momHandles)[95] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeOrderTypeObjectInstance;
  (*momHandles)[96] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeOrderTypeAttributeList;
  (*momHandles)[97] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeOrderTypeOrderingType;
  (*momHandles)[98] = federationManagement->managementObjectModel->managerFederateServiceChangeInteractionTransportationType;
  (*momHandles)[99] = federationManagement->managementObjectModel->managerFederateServiceChangeInteractionOrderType;
  (*momHandles)[100] = federationManagement->managementObjectModel->managerFederateServiceUnconditionalAttributeOwnershipDivestiture;
  (*momHandles)[101] = federationManagement->managementObjectModel->managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance;
  (*momHandles)[102] = federationManagement->managementObjectModel->managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList;
  (*momHandles)[103] = federationManagement->managementObjectModel->managerFederateServiceEnableTimeRegulation;
  (*momHandles)[104] = federationManagement->managementObjectModel->managerFederateServiceEnableTimeRegulationLookahead;
  (*momHandles)[105] = federationManagement->managementObjectModel->managerFederateServiceDisableTimeRegulation;
  (*momHandles)[106] = federationManagement->managementObjectModel->managerFederateServiceEnableTimeConstrained;
  (*momHandles)[107] = federationManagement->managementObjectModel->managerFederateServiceDisableTimeConstrained;
  (*momHandles)[108] = federationManagement->managementObjectModel->managerFederateServiceEnableAsynchronousDelivery;
  (*momHandles)[109] = federationManagement->managementObjectModel->managerFederateServiceDisableAsynchronousDelivery;
  (*momHandles)[110] = federationManagement->managementObjectModel->managerFederateServiceModifyLookahead;
  (*momHandles)[111] = federationManagement->managementObjectModel->managerFederateServiceModifyLookaheadLookahead;
  (*momHandles)[112] = federationManagement->managementObjectModel->managerFederateServiceTimeAdvanceRequest;
  (*momHandles)[113] = federationManagement->managementObjectModel->managerFederateServiceTimeAdvanceRequestTimeStamp;
  (*momHandles)[114] = federationManagement->managementObjectModel->managerFederateServiceTimeAdvanceRequestAvailable;
  (*momHandles)[115] = federationManagement->managementObjectModel->managerFederateServiceTimeAdvanceRequestAvailableTimeStamp;
  (*momHandles)[116] = federationManagement->managementObjectModel->managerFederateServiceNextMessageRequest;
  (*momHandles)[117] = federationManagement->managementObjectModel->managerFederateServiceNextMessageRequestTimeStamp;
  (*momHandles)[118] = federationManagement->managementObjectModel->managerFederateServiceNextMessageRequestAvailable;
  (*momHandles)[119] = federationManagement->managementObjectModel->managerFederateServiceNextMessageRequestAvailableTimeStamp;
  (*momHandles)[120] = federationManagement->managementObjectModel->managerFederateServiceFlushQueueRequest;
  (*momHandles)[121] = federationManagement->managementObjectModel->managerFederateServiceFlushQueueRequestTimeStamp;
#else
  // MOM Objects.
  // Manager object class.
  momHandles->length(125);
  (*momHandles)[0] = federationManagement->managementObjectModel->managerObject;
  (*momHandles)[1] = federationManagement->managementObjectModel->managerFederateObjectClass;
  (*momHandles)[2] = federationManagement->managementObjectModel->managerFederateFederateHandle;
  (*momHandles)[3] = federationManagement->managementObjectModel->managerFederateFederateType;
  (*momHandles)[4] = federationManagement->managementObjectModel->managerFederateFederateHost;
  (*momHandles)[5] = federationManagement->managementObjectModel->managerFederateRTIversion;
  (*momHandles)[6] = federationManagement->managementObjectModel->managerFederateFEDid;
  (*momHandles)[7] = federationManagement->managementObjectModel->managerFederateTimeConstrained;
  (*momHandles)[8] = federationManagement->managementObjectModel->managerFederateTimeRegulating;
  (*momHandles)[9] = federationManagement->managementObjectModel->managerFederateAsynchronousDelivery;
  (*momHandles)[10] = federationManagement->managementObjectModel->managerFederateFederateState;
  (*momHandles)[11] = federationManagement->managementObjectModel->managerFederateTimeManagerState;
  (*momHandles)[12] = federationManagement->managementObjectModel->managerFederateFederateTime;
  (*momHandles)[13] = federationManagement->managementObjectModel->managerFederateLookahead;
  (*momHandles)[14] = federationManagement->managementObjectModel->managerFederateLBTS;
  (*momHandles)[15] = federationManagement->managementObjectModel->managerFederateMinNextEventTime;
  (*momHandles)[16] = federationManagement->managementObjectModel->managerFederateROlength;
  (*momHandles)[17] = federationManagement->managementObjectModel->managerFederateTSOlength;
  (*momHandles)[18] = federationManagement->managementObjectModel->managerFederateReflectionsReceived;
  (*momHandles)[19] = federationManagement->managementObjectModel->managerFederateUpdatesSent;
  (*momHandles)[20] = federationManagement->managementObjectModel->managerFederateInteractionsReceived;
  (*momHandles)[21] = federationManagement->managementObjectModel->managerFederateInteractionsSent;
  (*momHandles)[22] = federationManagement->managementObjectModel->managerFederateObjectsOwned;
  (*momHandles)[23] = federationManagement->managementObjectModel->managerFederateObjectsUpdated;
  (*momHandles)[24] = federationManagement->managementObjectModel->managerFederateObjectsReflected;
  (*momHandles)[25] = federationManagement->managementObjectModel->managerInteractionFederate;
  (*momHandles)[26] = federationManagement->managementObjectModel->managerInteractionFederateFederate;
  (*momHandles)[27] = federationManagement->managementObjectModel->managerFederateAdjustSetTiming;
  (*momHandles)[28] = federationManagement->managementObjectModel->managerFederateAdjustModifyAttributeState;
  (*momHandles)[29] = federationManagement->managementObjectModel->managerFederateAdjustModifyAttributeStateObjectInstance;
  (*momHandles)[30] = federationManagement->managementObjectModel->managerFederateAdjustModifyAttributeStateAttribute;
  (*momHandles)[31] = federationManagement->managementObjectModel->managerFederateAdjustModifyAttributeStateAttributeState;
  (*momHandles)[32] = federationManagement->managementObjectModel->managerFederateAdjustSetServiceReporting;
  (*momHandles)[33] = federationManagement->managementObjectModel->managerFederateAdjustSetServiceReportingState;
  (*momHandles)[34] = federationManagement->managementObjectModel->managerFederateAdjustSetExceptionLogging;
  (*momHandles)[35] = federationManagement->managementObjectModel->managerFederateReportReflectionsReceived;
  (*momHandles)[36] = federationManagement->managementObjectModel->managerFederateReportReflectionsReceivedTransportationType;
  (*momHandles)[37] = federationManagement->managementObjectModel->managerFederateReportReflectionsReceivedReflectCounts;
  (*momHandles)[38] = federationManagement->managementObjectModel->managerFederateReportInteractionsReceived;
  (*momHandles)[39] = federationManagement->managementObjectModel->managerFederateReportInteractionsReceivedTransportationType;
  (*momHandles)[40] = federationManagement->managementObjectModel->managerFederateReportInteractionsReceivedInteractionCounts;
  (*momHandles)[41] = federationManagement->managementObjectModel->managerFederateReportAlert;
  (*momHandles)[42] = federationManagement->managementObjectModel->managerFederateReportAlertAlertSeverity;
  (*momHandles)[43] = federationManagement->managementObjectModel->managerFederateReportAlertAlertDescription;
  (*momHandles)[44] = federationManagement->managementObjectModel->managerFederateReportAlertAlertID;
  (*momHandles)[45] = federationManagement->managementObjectModel->managerFederateReportServiceInvocation;
  (*momHandles)[46] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationService;
  (*momHandles)[47] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationInitiator;
  (*momHandles)[48] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationSuccessIndicator;
  (*momHandles)[49] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationSuppliedArgument1;
  (*momHandles)[50] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationSuppliedArgument2;
  (*momHandles)[51] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationSuppliedArgument3;
  (*momHandles)[52] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationSuppliedArgument4;
  (*momHandles)[53] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationSuppliedArgument5;
  (*momHandles)[54] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationReturnedArgument;
  (*momHandles)[55] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationExceptionDescription;
  (*momHandles)[56] = federationManagement->managementObjectModel->managerFederateReportServiceInvocationExceptionID;
  (*momHandles)[57] = federationManagement->managementObjectModel->managerFederateServiceResignFederationExecution;
  (*momHandles)[58] = federationManagement->managementObjectModel->managerFederateServiceResignFederationExecutionResignAction;
  (*momHandles)[59] = federationManagement->managementObjectModel->managerFederateServiceSynchronizationPointAchieved;
  (*momHandles)[60] = federationManagement->managementObjectModel->managerFederateServiceSynchronizationPointAchievedLabel;
  (*momHandles)[61] = federationManagement->managementObjectModel->managerFederateServiceFederateSaveBegun;
  (*momHandles)[62] = federationManagement->managementObjectModel->managerFederateServiceFederateSaveComplete;
  (*momHandles)[63] = federationManagement->managementObjectModel->managerFederateServiceFederateSaveCompleteSuccessIndicator;
  (*momHandles)[64] = federationManagement->managementObjectModel->managerFederateServiceFederateRestoreComplete;
  (*momHandles)[65] = federationManagement->managementObjectModel->managerFederateServiceFederateRestoreCompleteSuccessIndicator;
  (*momHandles)[66] = federationManagement->managementObjectModel->managerFederateServicePublishObjectClass;
  (*momHandles)[67] = federationManagement->managementObjectModel->managerFederateServicePublishObjectClassObjectClass;
  (*momHandles)[68] = federationManagement->managementObjectModel->managerFederateServicePublishObjectClassAttributeList;
  (*momHandles)[69] = federationManagement->managementObjectModel->managerFederateServiceUnpublishObjectClass;
  (*momHandles)[70] = federationManagement->managementObjectModel->managerFederateServiceUnpublishObjectClassObjectClass;
  (*momHandles)[71] = federationManagement->managementObjectModel->managerFederateServicePublishInteractionClass;
  (*momHandles)[72] = federationManagement->managementObjectModel->managerFederateServicePublishInteractionClassInteractionClass;
  (*momHandles)[73] = federationManagement->managementObjectModel->managerFederateServiceUnpublishInteractionClass;
  (*momHandles)[74] = federationManagement->managementObjectModel->managerFederateServiceUnpublishInteractionClassInteractionClass;
  (*momHandles)[75] = federationManagement->managementObjectModel->managerFederateServiceSubscribeObjectClassAttributes;
  (*momHandles)[76] = federationManagement->managementObjectModel->managerFederateServiceSubscribeObjectClassAttributesObjectClass;
  (*momHandles)[77] = federationManagement->managementObjectModel->managerFederateServiceSubscribeObjectClassAttributesAttributeList;
  (*momHandles)[78] = federationManagement->managementObjectModel->managerFederateServiceSubscribeObjectClassAttributesActive;
  (*momHandles)[79] = federationManagement->managementObjectModel->managerFederateServiceUnsubscribeObjectClass;
  (*momHandles)[80] = federationManagement->managementObjectModel->managerFederateServiceUnsubscribeObjectClassObjectClass;
  (*momHandles)[81] = federationManagement->managementObjectModel->managerFederateServiceSubscribeInteractionClass;
  (*momHandles)[82] = federationManagement->managementObjectModel->managerFederateServiceSubscribeInteractionClassInteractionClass;
  (*momHandles)[83] = federationManagement->managementObjectModel->managerFederateServiceSubscribeInteractionClassActive;
  (*momHandles)[84] = federationManagement->managementObjectModel->managerFederateServiceUnsubscribeInteractionClass;
  (*momHandles)[85] = federationManagement->managementObjectModel->managerFederateServiceUnsubscribeInteractionClassInteractionClass;
  (*momHandles)[86] = federationManagement->managementObjectModel->managerFederateServiceDeleteObjectInstance;
  (*momHandles)[87] = federationManagement->managementObjectModel->managerFederateServiceDeleteObjectInstanceObjectInstance;
  (*momHandles)[88] = federationManagement->managementObjectModel->managerFederateServiceDeleteObjectInstanceTag;
  (*momHandles)[89] = federationManagement->managementObjectModel->managerFederateServiceDeleteObjectInstanceFederationTime;
  (*momHandles)[90] = federationManagement->managementObjectModel->managerFederateServiceLocalDeleteObjectInstance;
  (*momHandles)[91] = federationManagement->managementObjectModel->managerFederateServiceLocalDeleteObjectInstanceObjectInstance;
  (*momHandles)[92] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeTransportationType;
  (*momHandles)[93] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeTransportationTypeObjectInstance;
  (*momHandles)[94] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeTransportationTypeAttributeList;
  (*momHandles)[95] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeTransportationTypeTransportationType;
  (*momHandles)[96] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeOrderType;
  (*momHandles)[97] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeOrderTypeObjectInstance;
  (*momHandles)[98] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeOrderTypeAttributeList;
  (*momHandles)[99] = federationManagement->managementObjectModel->managerFederateServiceChangeAttributeOrderTypeOrderingType;
  (*momHandles)[100] = federationManagement->managementObjectModel->managerFederateServiceChangeInteractionTransportationType;
  (*momHandles)[101] = federationManagement->managementObjectModel->managerFederateServiceChangeInteractionOrderType;
  (*momHandles)[102] = federationManagement->managementObjectModel->managerFederateServiceUnconditionalAttributeOwnershipDivestiture;
  (*momHandles)[103] = federationManagement->managementObjectModel->managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance;
  (*momHandles)[104] = federationManagement->managementObjectModel->managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList;
  (*momHandles)[105] = federationManagement->managementObjectModel->managerFederateServiceEnableTimeRegulation;
  (*momHandles)[106] = federationManagement->managementObjectModel->managerFederateServiceEnableTimeRegulationFederationTime;
  (*momHandles)[107] = federationManagement->managementObjectModel->managerFederateServiceEnableTimeRegulationLookahead;
  (*momHandles)[108] = federationManagement->managementObjectModel->managerFederateServiceDisableTimeRegulation;
  (*momHandles)[109] = federationManagement->managementObjectModel->managerFederateServiceEnableTimeConstrained;
  (*momHandles)[110] = federationManagement->managementObjectModel->managerFederateServiceDisableTimeConstrained;
  (*momHandles)[111] = federationManagement->managementObjectModel->managerFederateServiceEnableAsynchronousDelivery;
  (*momHandles)[112] = federationManagement->managementObjectModel->managerFederateServiceDisableAsynchronousDelivery;
  (*momHandles)[113] = federationManagement->managementObjectModel->managerFederateServiceModifyLookahead;
  (*momHandles)[114] = federationManagement->managementObjectModel->managerFederateServiceModifyLookaheadLookahead;
  (*momHandles)[115] = federationManagement->managementObjectModel->managerFederateServiceTimeAdvanceRequest;
  (*momHandles)[116] = federationManagement->managementObjectModel->managerFederateServiceTimeAdvanceRequestFederationTime;
  (*momHandles)[117] = federationManagement->managementObjectModel->managerFederateServiceTimeAdvanceRequestAvailable;
  (*momHandles)[118] = federationManagement->managementObjectModel->managerFederateServiceTimeAdvanceRequestAvailableFederationTime;
  (*momHandles)[119] = federationManagement->managementObjectModel->managerFederateServiceNextEventRequest;
  (*momHandles)[120] = federationManagement->managementObjectModel->managerFederateServiceNextEventRequestFederationTime;
  (*momHandles)[121] = federationManagement->managementObjectModel->managerFederateServiceNextEventRequestAvailable;
  (*momHandles)[122] = federationManagement->managementObjectModel->managerFederateServiceNextEventRequestAvailableFederationTime;
  (*momHandles)[123] = federationManagement->managementObjectModel->managerFederateServiceFlushQueueRequest;
  (*momHandles)[124] = federationManagement->managementObjectModel->managerFederateServiceFlushQueueRequestFederationTime;
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::joinFederationExecutionFinished(
    GeRtiFactory::GeRtiHandle federate
  )
  throw(
    CORBA::SystemException
  )
{
  federationManagement->joinFederationExecutionFinished(federate);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiAmbassador_ptr GeRtiFactory_FederationManagement_i::getGeRtiAmbassador(
    GeRtiFactory::GeRtiHandle theHandle
  )
  throw(
    CORBA::SystemException
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_d)
                            {
                              unsigned long ul;

                              ul = theHandle;
                              sprintf(galMsg, "%lu", ul);
                              E2(GeRti_FM_d, "getGeRtiAmbassador", galMsg);
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
  FederatesMap::iterator it = federates.find(theHandle);
  if (it != federates.end())
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "getGeRtiAmbassador", "Leave");
                           #endif   // inserted by Gal converter
    pm.release();
    return GeRtiFactory::GeRtiAmbassador::_duplicate(it->second->GeRtiAmVar);
  }
  pm.release();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_e, "getGeRtiAmbassador", "federate not found");
                           #endif   // inserted by Gal converter
  return 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::resignFederationExecution(
    GeRtiFactory::ResignAction resignAction,
    GeRtiFactory::GeRtiHandle federate
  )
  throw(
    GeRtiFactory::FederateOwnsAttributes,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::InvalidResignAction,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError,
    CORBA::SystemException
  )

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_feds_i)
                            {
                              unsigned long ul;

                              ul = federate;
                              sprintf(galMsg, "%lu", ul);
                              E2(GeRti_FM_feds_i, "resignFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"";

  if (active == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                              unsigned long ul;

                              ul = federate;
                              sprintf(galMsg, "FederateNotExecutionMember:%lu", ul);
                              E2(GeRti_FM_w, "resignFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::FederateNotExecutionMember(wChar);
  }

  GeRtiFactory_GeRtiAmbassador_i *currGeRtiAmbassador;

  federationManagement->resignFederationExecution(resignAction, federate);

  pm.acquire();
  FederatesMap::iterator it = federates.find(federate);
  if (it != federates.end())
  {
    currGeRtiAmbassador = it->second;
    federates.erase(federate);
    currGeRtiAmbassador->deactivateObject();
    federatesDeleted[federate] = currGeRtiAmbassador;
//    delete currGeRtiAmbassador;
  }
  pm.release();

  // Allow other thread to continue;
  federationManagement->ps->release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_feds_i, "resignFederationExecution", "done");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::destroyFederationExecution(const CORBA::WChar *fedName)
throw
(
  CORBA::SystemException,
  GeRtiFactory::FederationExecutionDoesNotExist,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::FederatesCurrentlyJoined,
  GeRtiFactory::RTIinternalError
)
{
  CORBA::WChar *wChar = L"";
  std::string fedNameString;
  std::wstring fedNameWstring;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromWchar(fedNameWstring, fedName);
  GERTICO::Mapper::mapStringFromWstring(fedNameString, fedNameWstring);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_feds_i)
                            {
                              sprintf(galMsg,"federation=%ls", fedName);
                              E2(GeRti_FM_feds_i, "destroyFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter

  GeRtiFactory_FederationManagement_i *currFederation;
  size_t size;

  GeRtiFactory_Factory_i::spm.acquire();
  size = GeRtiFactory_Factory_i::fedMan.size();
  FederationManagementMap::iterator it = GeRtiFactory_Factory_i::fedMan.find(fedNameWstring);

  if (it != GeRtiFactory_Factory_i::fedMan.end())
  {
    currFederation = it->second;

    if (currFederation->isActive() == false)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                              sprintf(galMsg,"DoesNotExist:federation=%ls", fedName);
                              E2(GeRti_FM_w, "destroyFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
      GeRtiFactory_Factory_i::spm.release();
      GERTICO::Mapper::mapWstringFromChar(ws, fedNameString.c_str());
      throw GeRtiFactory::FederationExecutionDoesNotExist(ws.c_str());
    }

    if (currFederation->federates.size() == 0)
    {
      // No federates are joined, schedule delete job.
      currFederation->active = false;

      GeRtiFactory_Factory_i::fedMan.erase(it);
      size = GeRtiFactory_Factory_i::fedMan.size();

      GeRtiFactory_Factory_i::spm.release();
      currFederation->Term();
      doEventHubDestroyFederation(fedName);
      deleteVector.push_back(currFederation);
      psClean->release();
                           #ifdef GalDebug   // inserted by Gal converter
                              sprintf(galMsg,"leave:federation=%ls", fedName);
                              E2(GeRti_FM_feds_i, "destroyFederationExecution", galMsg);
                           #endif   // inserted by Gal converter
      return;
    }
    else
    {
      // Federates currently joined.
      GeRtiFactory_Factory_i::spm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                              sprintf(galMsg,"FederatesCurrentlyJoined:federation=%ls", fedName);
                              E2(GeRti_FM_w, "destroyFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
      throw GeRtiFactory::FederatesCurrentlyJoined(wChar);
    }
  }
  else
  {
    GeRtiFactory_Factory_i::spm.release();
    GERTICO::Mapper::mapWstringFromChar(ws, fedNameString.c_str());
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                              sprintf(galMsg,"FederationExecutionDoesNotExist:federation=%ls", fedName);
                              E2(GeRti_FM_w, "destroyFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::FederationExecutionDoesNotExist(ws.c_str());
  }
  GeRtiFactory_Factory_i::spm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_feds_i, "destroyFederationExecution", "done");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::doEventHubDestroyFederation(const CORBA::WChar *fedNameWstring)
{
  EventHubMap::iterator itEventHub;

  for (itEventHub = GeRtiFactory_Factory_i::eventHubs.begin(); itEventHub != GeRtiFactory_Factory_i::eventHubs.end(); itEventHub++)
  {
    itEventHub->second->theEventHubFederationFactoryPtr->destroyFederationExecution(fedNameWstring);
  }
}

// ---------------------------------------------------------------------------
// Keep a maximum of 10 old Federate entries.
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::garbageCollection(void)
{
  GeRtiFactory_GeRtiAmbassador_i *currFederate;
  FederatesMap::iterator itFederatesMap;
  size_t size;

  pm.acquire();
  size = federatesDeleted.size();
  if (size < 11)
  {
    pm.release();
    return;
  }
  size -= 10;
  for (itFederatesMap = federatesDeleted.begin(); itFederatesMap != federatesDeleted.end(); itFederatesMap = federatesDeleted.begin())
  {
    currFederate = itFederatesMap->second;
    federatesDeleted.erase(itFederatesMap);
    delete currFederate;
    size -= 1;
    if (size == 0)
    {
      break;
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_FederationManagement_i::terminate(
  )
  throw(
    CORBA::SystemException
  )

  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "terminate", "Enter");
                           #endif   // inserted by Gal converter
    //Add your implementation here
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "terminate", "Leave");
                           #endif   // inserted by Gal converter
  }

// ---------------------------------------------------------------------------
// Implementation skeleton constructor
// ---------------------------------------------------------------------------
GeRtiFactory_Factory_i::GeRtiFactory_Factory_i(GERTICO::GeRtiOrb &theGeRtiOrb, CosNaming::NamingContext_var &namingContext, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory), myGeRtiOrb(theGeRtiOrb), conf(theGERTICOconf)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "GeRtiFactory_Factory_i", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::StringSet::const_iterator itStringSet;
  std::wstring hubName = L"defaultHub";

  theEventHubFederationFactory = NULL;
  createInProgress = false;
  myNamingContext = CosNaming::NamingContext::_duplicate(namingContext);
  itStringSet = theGERTICOconf.configuredHubs.find("defaultHub");
  if (itStringSet != theGERTICOconf.configuredHubs.end())
  {
    theEventHubFederationFactory = new GeRtiFactory_TheEventHubFederationFactoryEC_i(hubName, theGeRtiOrb, theGERTICOconf, geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
    theEventHubFederationFactoryVar = theEventHubFederationFactory->_this();

    registerEventHubFactory(hubName.c_str(), theEventHubFederationFactoryVar);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "GeRtiFactory_Factory_i", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Implementation skeleton destructor
// ---------------------------------------------------------------------------
GeRtiFactory_Factory_i::~GeRtiFactory_Factory_i(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "~GeRtiFactory_Factory_i", "Enter");
                           #endif   // inserted by Gal converter
  if (theEventHubFederationFactory)
  {
    delete theEventHubFederationFactory;
    theEventHubFederationFactory = NULL;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "~GeRtiFactory_Factory_i", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_Factory_i::createFederationExecution(const CORBA::WChar *fedName, const CORBA::WChar *fedFile)
throw
(
  GeRtiFactory::FederationExecutionAlreadyExists,
  GeRtiFactory::CouldNotOpenFED,
  GeRtiFactory::ErrorReadingFED,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError,
  CORBA::SystemException
)
{
  char name[1024];
  std::string fedNameString;
  std::wstring fedNameWstring;
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_feds_i)
                            {
                              sprintf(galMsg,"federateName=%ls,fedFile=%ls", fedName, fedFile);
                              E2(GeRti_FM_feds_i, "createFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter

  GERTICO::Mapper::mapWstringFromWchar(fedNameWstring, fedName);
  GERTICO::Mapper::mapStringFromWstring(fedNameString, fedNameWstring);

  if (eventHubs.size() != conf.configuredHubs.size())
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                             E2(GeRti_FM_w, "createFederationExecution", "Not all hubs attached");
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::RTIinternalError(L"createFederationExecution: Not all hubs attached");
  }

  name[0] = '\0';
  sscanf(fedNameString.c_str(), "%s", name);
  if (name[0] == '\0')
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                              sprintf(galMsg,"federationNameMissing");
                              E2(GeRti_FM_w, "createFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::RTIinternalError(L"createFederationExecution: federation name missing");
  }

  spm.acquire();
  if (createInProgress == true)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                             E2(GeRti_FM_w, "createFederationExecution", "ConcurrentAccessAttempted");
                            }
                           #endif   // inserted by Gal converter
    spm.release();
    throw GeRtiFactory::ConcurrentAccessAttempted(L"createFederationExecution");
  }
  createInProgress = true;
  spm.release();

  try
  {
    // Allocate new federation and read fed file.
    std::wstring ff;
    GERTICO::Mapper::mapWstringFromWchar(ff, fedFile);
    allocFederation(fedNameWstring, ff);
    doEventHubCreateFederation(fedNameWstring);
  }
  catch(...)
  {
    spm.acquire();
    createInProgress = false;
    spm.release();
    throw;
  }

  spm.acquire();
  createInProgress = false;
  spm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_feds_i, "createFederationExecution", "done");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_Factory_i::allocFederation(std::wstring const &theFedName, std::wstring const &theFedFile)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "allocFederation", "Enter");
                           #endif   // inserted by Gal converter

  CORBA::Object_var namingVar;
  CORBA::WChar *wChar = L"";
  CosNaming::NamingContext_var namingContext;
  GeRtiFactory_FederationManagement_i *currFederationManagement;
  FederationManagementMap::iterator i;
  size_t size;

  spm.acquire();
  size = fedMan.size();
  i = fedMan.find(theFedName);
  if (i != fedMan.end())
  {
    currFederationManagement = i->second;
    if (currFederationManagement->isActive())
    {
      spm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                             sprintf(galMsg,"FederationExecutionAlreadyExists:federateName=%ls,fedFile=%ls", theFedName.c_str(), theFedFile.c_str());
                             E2(GeRti_FM_w, "createFederationExecution", galMsg);
                            }
                           #endif   // inserted by Gal converter
      throw GeRtiFactory::FederationExecutionAlreadyExists(wChar);
    }
    // Allow old federation to be removed.
    ACE_OS::sleep(1);
  }
  spm.release();

  GeRtiFactory_FederationManagement_i *fedNew = new GeRtiFactory_FederationManagement_i(myGeRtiOrb, theFedName, theFedFile, conf, geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
  fedNew->activateObject();

  // Into the vector.
  spm.acquire();
  fedMan[theFedName] = fedNew;
  spm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "allocFederation", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Create the federation data on each event hub and connect the event channels
// between each event hub pair.
// ---------------------------------------------------------------------------
void GeRtiFactory_Factory_i::doEventHubCreateFederation(std::wstring const &fedNameWstring)
{
  CORBA::ULong i;
  CORBA::ULong momInteractionRoot;
  CORBA::ULong momObjectRoot;
  CORBA::ULong interactionRoot;
  CORBA::ULong length;
  CORBA::ULong objectRoot;
  CORBA::ULong privilegeToDeleteId;
  CORBA::WChar *fedNameWChar;
  CORBA::WChar *wChar = L"doEventHubCreateFederation: my event hub not found";
  EventHubMap::iterator itEventHub;
  FederationManagementMap::iterator itFederationManagementMap;
  FederationReferencesMap::iterator itFederationReferencesMap;
  GeRtiFactory::EventChannel_var eventChannelVar;
  GeRtiFactory::EventHubFederation_var eventHubFederationVar;
  GeRtiFactory::HubEventChannelDataSeq hubEventChannelDataSeq;
  HubFederationReferences *hubFederationReferences;
  size_t size;

  size = eventHubs.size();
  GERTICO::Mapper::mapULongSizet(length, size);

  // Get the data for the specified federation.
  itFederationManagementMap = fedMan.find(fedNameWstring);
  if (itFederationManagementMap != fedMan.end())
  {
    itFederationManagementMap->second->getEventHubCreateData(momInteractionRoot, momObjectRoot, interactionRoot, objectRoot, privilegeToDeleteId);
  }

  // Create and configure federation data on each event hub
  GERTICO::Mapper::mapWcharFromWstring(&fedNameWChar, fedNameWstring);
  for (itEventHub = eventHubs.begin(); itEventHub != eventHubs.end(); itEventHub++)
  {
    hubFederationReferences = new HubFederationReferences();
    itEventHub->second->theEventHubFederationFactoryPtr->createFederationExecution(fedNameWChar, momInteractionRoot, momObjectRoot, interactionRoot, objectRoot, privilegeToDeleteId, eventHubFederationVar, eventChannelVar);
    hubFederationReferences->eventHubFederationVar = GeRtiFactory::EventHubFederation::_duplicate(eventHubFederationVar);
    hubFederationReferences->eventChannelVar = GeRtiFactory::EventChannel::_duplicate(eventChannelVar);
    itFederationReferencesMap = itEventHub->second->federationReferencesMap.find(fedNameWstring);
    if (itFederationReferencesMap != itEventHub->second->federationReferencesMap.end())
    {
      HubFederationReferences *hubFederationReferencesTmp;
      hubFederationReferencesTmp = itFederationReferencesMap->second;
      itEventHub->second->federationReferencesMap.erase(itFederationReferencesMap);
      delete hubFederationReferencesTmp;
    }
    itEventHub->second->federationReferencesMap[fedNameWstring] = hubFederationReferences;
  }

  // Get the event channel for federation within each event hub.
  hubEventChannelDataSeq.length(length);
  for (i = 0, itEventHub = eventHubs.begin(); itEventHub != eventHubs.end(); i++, itEventHub++)
  {
    itFederationReferencesMap = itEventHub->second->federationReferencesMap.find(fedNameWstring);
    if (itFederationReferencesMap != itEventHub->second->federationReferencesMap.end())
    {
      hubEventChannelDataSeq[i].eventChannelReference = GeRtiFactory::EventChannel::_duplicate(itFederationReferencesMap->second->eventChannelVar);
      hubEventChannelDataSeq[i].name = itEventHub->first.c_str();
    }
  }

  if (size < 2)
  {
    // Cannot connect less than two hubs.
    return;
  }

  // Establish event channels between each event hub pair.
  for (itEventHub = eventHubs.begin(); itEventHub != eventHubs.end(); itEventHub++)
  {
    itFederationReferencesMap = itEventHub->second->federationReferencesMap.find(fedNameWstring);
    if (itFederationReferencesMap != itEventHub->second->federationReferencesMap.end())
    {
      itFederationReferencesMap->second->eventHubFederationVar->makeEventHubChannels(hubEventChannelDataSeq);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::FederationManagement_ptr GeRtiFactory_Factory_i::getFederationManagement(const CORBA::WChar *fedName)
throw
(
  CORBA::SystemException,
  GeRtiFactory::FederationExecutionDoesNotExist,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError
)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_d)
                            {
                              sprintf(galMsg,"federateName=%ls", fedName);
                              E2(GeRti_FM_d, "getFederationManagement", galMsg);
                            }
                           #endif   // inserted by Gal converter

  GeRtiFactory_FederationManagement_i *currFederationManagement;
  FederationManagementMap::iterator itFederationManagementMap;
  std::wstring theFedName;

  GERTICO::Mapper::mapWstringFromWchar(theFedName, fedName);
  itFederationManagementMap = fedMan.find(theFedName);
  if (itFederationManagementMap != fedMan.end())
  {
    currFederationManagement = itFederationManagementMap->second;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "getFederationManagement", "Leave");
                           #endif   // inserted by Gal converter
    return GeRtiFactory::FederationManagement::_duplicate(currFederationManagement->FederationManagementVar);
  }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_w)
                            {
                              sprintf(galMsg,"FederationExecutionDoesNotExist:federateName=%ls", fedName);
                              E2(GeRti_FM_w, "getFederationManagement", galMsg);
                            }
                           #endif   // inserted by Gal converter
  throw GeRtiFactory::FederationExecutionDoesNotExist(L"federation name not found");
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_Factory_i::registerEventHubFactory(
  const CORBA::WChar * hubName,
  GeRtiFactory::TheEventHubFederationFactory_ptr geRtiEventHubFactory
)
throw(
  CORBA::SystemException,
  GeRtiFactory::EventHubAlreadyExists,
  GeRtiFactory::RTIinternalError
)
{
  EventHubMap::iterator itEventHubMap;
  HubReferences *hubReferences;
  GERTICO::StringSet::const_iterator itStringSet;
  std::string s;
  std::wstring ws(hubName);

  GERTICO::Mapper::mapStringFromWstring(s, ws);

  itStringSet = conf.configuredHubs.find(s);
  if (itStringSet == conf.configuredHubs.end())
  {
    std::wstring ws = L"registerEventHubFactory: federation name invalid ";
    ws.append(ws);
    throw GeRtiFactory::RTIinternalError(ws.c_str());
  }

  itEventHubMap = eventHubs.find(ws);
  if (itEventHubMap != eventHubs.end())
  {
    std::wstring ws = L"registerEventHubFactory: hub name ";
    ws.append(ws);
    throw GeRtiFactory::EventHubAlreadyExists(ws.c_str());
  }
  else
  {
    hubReferences = new HubReferences();
    hubReferences->theEventHubFederationFactoryPtr = GeRtiFactory::TheEventHubFederationFactory::_duplicate(geRtiEventHubFactory);
    eventHubs[ws] = hubReferences;
  }
}