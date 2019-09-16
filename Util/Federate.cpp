/*********************************************************************************
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** Federate.cpp
**
*******************************************************************************/

#include "Federate.h"
#include "Util/ConvertTime.h"
#include "Util/Mapper.h"

// Static strings for save/restore.
std::string GERTICO::FedRegionsHolder::activeStr("active");
std::string GERTICO::FedRegionsHolder::attributeStr("attribute");
std::string GERTICO::FedRegionsHolder::attributesStr("attributes");
std::string GERTICO::FedRegionsHolder::idStr("id");
std::string GERTICO::FedRegionsHolder::regionStr("region");

std::string GERTICO::Federate::activeStr("active");
std::string GERTICO::Federate::attributeStr("attribute");
std::string GERTICO::Federate::attributesStr("attributes");
std::string GERTICO::Federate::classStr("class");
std::string GERTICO::Federate::dataStr("data");
std::string GERTICO::Federate::federateStr("federate");
std::string GERTICO::Federate::idStr("id");
std::string GERTICO::Federate::inScopeStr("inScope");
std::string GERTICO::Federate::knownObjectStr("knownObject");
std::string GERTICO::Federate::knownObjectsStr("knownObjects");
std::string GERTICO::Federate::lrcDataStr("lrcData");
std::string GERTICO::Federate::publishedInteractionsStr("publishedInteractions");
std::string GERTICO::Federate::publishedObjectClassesStr("publishedObjectClasses");
std::string GERTICO::Federate::publishingStr("publishing");
std::string GERTICO::Federate::regionStr("region");
std::string GERTICO::Federate::regionsStr("regions");
std::string GERTICO::Federate::startedStr("started");
std::string GERTICO::Federate::subscribedInteractionsStr("subscribedInteractions");
std::string GERTICO::Federate::subscribedObjectClassesStr("subscribedObjectClasses");
std::string GERTICO::Federate::turnedOnStr("turnedOn");

/********************************* Gal begin *********************************/   // inserted by Gal converter
#ifdef GalDebug   // inserted by Gal converter
#include "Gal/StdAfx.h"   // inserted by Gal converter
#include "Gal/repository_l.h"   // inserted by Gal converter
#include "Gal/event.h"   // inserted by Gal converter

static class Repository_l *DM=(Repository::getSingleInstance())->getRepository_l("GeRtiDM.res","GeRtiDM");

static class Event *GeRti_DM_d=DM->getRefEvent("GeRti_DM_d");
static class Event *GeRti_DM_e=DM->getRefEvent("GeRti_DM_e");
static class Event *GeRti_DM_i=DM->getRefEvent("GeRti_DM_i");
static class Event *GeRti_DM_w=DM->getRefEvent("GeRti_DM_w");

static class Repository_l *FM=(Repository::getSingleInstance())->getRepository_l("GeRtiFM.res","GeRtiFM");

static class Event *GeRti_FM_d=FM->getRefEvent("GeRti_FM_d");
static class Event *GeRti_FM_e=FM->getRefEvent("GeRti_FM_e");
static class Event *GeRti_FM_feds_i=FM->getRefEvent("GeRti_FM_feds_i");
static class Event *GeRti_FM_i=FM->getRefEvent("GeRti_FM_i");
static class Event *GeRti_FM_w=FM->getRefEvent("GeRti_FM_w");

static class Repository_l *OM=(Repository::getSingleInstance())->getRepository_l("GeRtiOM.res","GeRtiOM");

static class Event *GeRti_OM_d=OM->getRefEvent("GeRti_OM_d");
static class Event *GeRti_OM_e=OM->getRefEvent("GeRti_OM_e");
static class Event *GeRti_OM_i=OM->getRefEvent("GeRti_OM_i");
static class Event *GeRti_OM_w=OM->getRefEvent("GeRti_OM_w");

static class Repository_l *r=(Repository::getSingleInstance())->getRepository_l("GeRtiOWM.res","GeRtiOWM");

static class Event *GeRti_OWM_d=r->getRefEvent("GeRti_OWM_d");
static class Event *GeRti_OWM_e=r->getRefEvent("GeRti_OWM_e");
static class Event *GeRti_OWM_i=r->getRefEvent("GeRti_OWM_i");
static class Event *GeRti_OWM_w=r->getRefEvent("GeRti_OWM_w");

static class Repository_l *TM=(Repository::getSingleInstance())->getRepository_l("GeRtiTM.res","GeRtiTM");

static class Event *GeRti_TM_d=TM->getRefEvent("GeRti_TM_d");
static class Event *GeRti_TM_e=TM->getRefEvent("GeRti_TM_e");
static class Event *GeRti_TM_i=TM->getRefEvent("GeRti_TM_i");
static class Event *GeRti_TM_w=TM->getRefEvent("GeRti_TM_w");
static class Event *GeRti_TM_mu_d=TM->getRefEvent("GeRti_TM_mu_d");

#endif   // inserted by Gal converter

static char galMsg[512];

/*********************************** Gal end *********************************/   // inserted by Gal converter

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AttributeInstanceKnown::AttributeInstanceKnown (void)
{
  inScope = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AttributeInstanceKnown::~AttributeInstanceKnown (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::AttributeInstanceKnown::getId (void)
{
  return id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::AttributeInstanceKnown::getInScope (void)
{
  return inScope;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::AttributeInstanceKnown::setId (const GeRtiFactory::GeRtiHandle &theId)
{
  id = theId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::AttributeInstanceKnown::setScope(const bool &theScope)
{
  inScope = theScope;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectKnown::ObjectKnown (const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::AttributeInstanceKnown attributeInstanceKnown;
  GERTICO::HandleSet::iterator itAttribute;

  classId = theObjectClass;
  objectId = theObject;

  for (itAttribute = theAttributes.begin(); itAttribute != theAttributes.end(); itAttribute++)
  {
    attributeInstanceKnown.setId(*itAttribute);
    atts[*itAttribute] = attributeInstanceKnown;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectKnown::~ObjectKnown (void)
{
  clear();
}

// ---------------------------------------------------------------------------
// Useful in destructor to deallocate structures.
// ---------------------------------------------------------------------------
void GERTICO::ObjectKnown::clear(void)
{
  AttributeInstanceKnownMap::iterator itAIKM;

  for (itAIKM = atts.begin(); itAIKM != atts.end(); itAIKM = atts.begin())
  {
    atts.erase(itAIKM);
  }
}
void GERTICO::ObjectKnown::print(void)
{
/*
  AttributeInstanceKnownMap::iterator itAIKM;
unsigned long ul;
  for (itAIKM = atts.begin(); itAIKM != atts.end(); itAIKM++)
  {
    ul = itAIKM->first;
    if (itAIKM->second.getInScope())
    {
      std::cout << "ObjectKnown::print att in scope " << ul << std::endl;
    }
    else
    {
      std::cout << "ObjectKnown::print att out of scope " << ul << std::endl;
    }
  }
*/
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ObjectKnown::getClassId (void)
{
  return classId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ObjectKnown::getObjectId (void)
{
  return objectId;
}

// ---------------------------------------------------------------------------
// The attributes are the published/owned attributes of the federate calling
// register object instance.
// ---------------------------------------------------------------------------
void GERTICO::ObjectKnown::setInScope(GERTICO::HandleSet &theAttributes)
{
  GERTICO::HandleSet::iterator itHS;
  GERTICO::AttributeInstanceKnown *attributeInstanceKnown;
  GERTICO::AttributeInstanceKnownMap::iterator itAttributeInstanceKnownMap;

  for (itHS = theAttributes.begin (); itHS != theAttributes.end (); itHS++)
  {
    itAttributeInstanceKnownMap = atts.find(*itHS);
    if (itAttributeInstanceKnownMap != atts.end())
    {
      attributeInstanceKnown = &itAttributeInstanceKnownMap->second;
      attributeInstanceKnown->setScope(true);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegionAttributes::RegionAttributes (void)
{
  myActive = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegionAttributes::~RegionAttributes (void)
{
  attributes.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FedRegionsHolder::FedRegionsHolder (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FedRegionsHolder::~FedRegionsHolder (void)
{
  regionAttributesMap.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedRegionsHolder::restore (DOMElement &theDOMElement)
{
  DOMNode* child;
  DOMNode* subChild;
  DOMNode* subSubChild;
  char *tmpChar;
  unsigned long tmpATT;
  unsigned long tmpREGION;
  unsigned long tmpUL;

  for (child = theDOMElement.getFirstChild (); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (regionStr.c_str ())) == 0)
      {
        RegionAttributes regionAttributes;
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute (XMLString::transcode (activeStr.c_str ())));
        sscanf (tmpChar, "%lu", &tmpUL);
        regionAttributes.myActive = tmpUL;
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute (XMLString::transcode (idStr.c_str ())));
        sscanf (tmpChar, "%lu", &tmpREGION);
        for (subChild = child->getFirstChild (); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (attributesStr.c_str ())) == 0)
            {
              for (subSubChild = subChild->getFirstChild (); subSubChild != 0; subSubChild = subSubChild->getNextSibling())
              {
                if (subSubChild->getNodeType() == DOMNode::ELEMENT_NODE)
                {
                  if (XMLString::compareString(subSubChild->getNodeName(),XMLString::transcode (attributeStr.c_str ())) == 0)
                  {
                    tmpChar = XMLString::transcode (((DOMElement*)subSubChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
                    sscanf (tmpChar, "%lu", &tmpATT);
                    regionAttributes.attributes.insert (tmpATT);
                  }
                }
              }
            }
          }
        }
        regionAttributesMap[tmpREGION] = regionAttributes;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedRegionsHolder::save (DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  DOMElement* elemLevel3;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::RegionAttributesMap::iterator itRA;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  unsigned long ul;

  for (itRA = regionAttributesMap.begin (); itRA != regionAttributesMap.end (); itRA++)
  {
    XMLString::transcode(regionStr.c_str (), tempStr, 99);
    elemLevel1 = theDOMDocument.createElement(tempStr);
    theDOMElement.appendChild(elemLevel1);

    XMLString::transcode(idStr.c_str (), tempStr, 99);
    ul = itRA->first;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);

    XMLString::transcode(activeStr.c_str (), tempStr, 99);
    if (itRA->second.myActive)
    {
      XMLString::transcode("1", tempStr1, 99);
    }
    else
    {
      XMLString::transcode("0", tempStr1, 99);
    }
    elemLevel1->setAttribute(tempStr, tempStr1);

    XMLString::transcode(attributesStr.c_str (), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    for (itHS = itRA->second.attributes.begin(); itHS != itRA->second.attributes.end(); itHS++)
    {
      XMLString::transcode(attributeStr.c_str (), tempStr, 99);
      elemLevel3 = theDOMDocument.createElement(tempStr);
      elemLevel2->appendChild(elemLevel3);

      XMLString::transcode(idStr.c_str (), tempStr, 99);
      ul = *itHS;
      sprintf (buf, "%lu", ul);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel3->setAttribute(tempStr, tempStr1);
    }
  }
}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
GERTICO::PublishObjectClassFlagsRTI::PublishObjectClassFlagsRTI(void)
{
  started = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublishObjectClassFlagsRTI::~PublishObjectClassFlagsRTI(void)
{
  attributes.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::PublishObjectClassFlagsRTI::getStarted (void)
{
  return started;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PublishObjectClassFlagsRTI::setStarted (const bool &theStarted)
{
  started = theStarted;
}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
GERTICO::Federate::Federate(const GeRtiFactory::GeRtiHandle &v_id, const std::wstring &theFederateType, GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GERTICO::ClassDescrHolder &theObjectClassDescr, GeRtiFactory::FederateAmbassador_ptr theFederateAmbassadorPtr, GeRtiFactory::GeRtiRestore_ptr theGeRtiRestorePtr, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory) : pObjectRoot(theObjectClassDescr), registeredObjectsHolder(theRegisteredObjectsHolder), geRtiFedTimeFactory(theGeRtiFedTimeFactory), federateType(theFederateType)
{
  // Corba references,
  fedAm = GeRtiFactory::FederateAmbassador::_duplicate(theFederateAmbassadorPtr);
  geRtiRestoreVar = GeRtiFactory::GeRtiRestore::_duplicate(theGeRtiRestorePtr);

  // Federate id.
  id = v_id;

  // Boolean flags.
  confirmed = false;
  joinedFinished = false;
  restoreBegun = false;
  restoreComplete = false;
  restoreInitiated = false;
  restoreSuccess = false;
  saveBegun = false;
  saveComplete = false;
  saveInitiated = false;
  saveInitiatedWithTime = false;
  saveSuccess = false;
  stillAlive = false;

  // Default switch settings.
  attributeScopeAdvisorySwitch = false;
  classRelevanceAdvisorySwitch = true;
  timeConstrained = false;
  nextSaveTime = geRtiFedTimeFactory.makeZero();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Federate::~Federate (void)
{
  if (nextSaveTime)
  {
    delete nextSaveTime;
  }
  clear ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::addKnownObject(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_d)
                            {
                              unsigned long f;
                              unsigned long ul;
                              unsigned long ul1;

                              f = id;
                              ul = theObject;
                              ul1 = theObjectClass;
                              sprintf(galMsg, "Federate=%lu,Object=%lu,Class=%lu", f, ul, ul1);
                              E2(GeRti_OM_d, "addKnownObject", galMsg);
                              GERTICO::Mapper::printHandleSet("attributes=", galMsg, theAttributes);
                              E2(GeRti_OM_d, "addKnownObject", galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet attributes;
  GERTICO::ObjectKnown *objectKnown;
  GERTICO::ObjectKnownMap::iterator itOK;

  classDescr = pObjectRoot.getClassDescr(theObjectClass);
  classDescr->getAttributes(attributes);

  objectKnown = new GERTICO::ObjectKnown(theObject, theObjectClass, attributes);
  attributes.clear();
  getSubscribedAttributes(theObjectClass, attributes, theAttributes);

  itOK = knownObjects.find(theObject);
  if (itOK == knownObjects.end ())
  {
    knownObjects[theObject] = objectKnown;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OM_d, "addKnownObject", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::addSubscribeObjectClass(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttSet, const CORBA::Boolean &theActive)
{
  RegionAttributes regionAttributes;
  GERTICO::HandleSet::iterator itAttSet;
  GERTICO::HandleSet::iterator itRegionsIn;
  GERTICO::RegionAttributesMap::iterator itRA;
  GERTICO::FedRegionsHolder *currRegionsHolder;
  GERTICO::FedRegionsHolder newRegionsHolder;
  ClassRegionsHolderMap::iterator itCRH;

#ifndef IEEE_1516
  itCRH = subObjectClassMap.find (theObjectClass);
  if (itCRH != subObjectClassMap.end ())
  {
    // Replace all values -> delete old values first.
    for (itAttSet = theAttSet.begin(); itAttSet != theAttSet.end(); itAttSet++)
    {
      try
      {
        delObjectClassSub(theObjectClass);
      }
      catch(...)
      {
      }
    }
  }
#endif

  print();
  itCRH = subObjectClassMap.find (theObjectClass);
  if (itCRH == subObjectClassMap.end ())
  {
    // Add empty value entry if necessary.
    subObjectClassMap[theObjectClass] = newRegionsHolder;
  }

  // Position on entry.
  itCRH = subObjectClassMap.find (theObjectClass);
  if (itCRH != subObjectClassMap.end ())
  {
    currRegionsHolder = &itCRH->second;
    itRA = currRegionsHolder->regionAttributesMap.find(0);
    if (itRA != currRegionsHolder->regionAttributesMap.end())
    {
      currRegionsHolder->regionAttributesMap.erase(itRA);
    }
  }
  else
  {
    throw GeRtiFactory::RTIinternalError (L"Federate::addSubscribeObjectClass: map inconsistent");
  }

  // Fill new atrributes.
  regionAttributes.attributes.clear();
  for (itAttSet = theAttSet.begin(); itAttSet != theAttSet.end(); itAttSet++)
  {
    regionAttributes.attributes.insert(*itAttSet);
  }
  regionAttributes.myActive = theActive;

  currRegionsHolder->regionAttributesMap[0] = regionAttributes;
  print();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::addSubscribeObjectClassRegion(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSetMap &theAttRegMap, const CORBA::Boolean &theActive)
{
  RegionAttributes regionAttributes;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet *regionsPtr;
  GERTICO::HandleSet::iterator itRegions;
  GERTICO::HandleSet::iterator itRegionsIn;
  GERTICO::HandleSetMap::iterator itAttRegMap;
  GERTICO::RegionAttributesMap::iterator itRA;
  GERTICO::FedRegionsHolder *currRegionsHolder;
  GERTICO::FedRegionsHolder newRegionsHolder;
  ClassRegionsHolderMap::iterator itCRH;

#ifndef IEEE_1516
  itCRH = subObjectClassMap.find (theObjectClass);
  if (itCRH != subObjectClassMap.end ())
  {
    // Replace all values -> delete old values first.
    try
    {
      unsubscribeObjectClassWithRegions(theObjectClass, theAttRegMap);
    }
    catch(...)
    {
    }
  }
#endif

  itCRH = subObjectClassMap.find (theObjectClass);
  if (itCRH == subObjectClassMap.end ())
  {
    // Add empty value entry if necessary.
    subObjectClassMap[theObjectClass] = newRegionsHolder;
  }

  // Position on entry.
  itCRH = subObjectClassMap.find (theObjectClass);
  if (itCRH != subObjectClassMap.end ())
  {
    currRegionsHolder = &itCRH->second;
  }
  else
  {
    throw GeRtiFactory::RTIinternalError (L"Federate::addSubscribeObjectClassRegion: map inconsistent");
  }

  // Delete any old class/region pair.
  for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
  {
    regionsPtr = &itAttRegMap->second;
    for (itRegionsIn = regionsPtr->begin(); itRegionsIn != regionsPtr->end(); itRegionsIn++)
    {
      itRegions = regions.find(*itRegionsIn);
      if (itRegions == regions.end())
      {
        regions.insert(*itRegionsIn);
      }
      itRA = currRegionsHolder->regionAttributesMap.find(*itRegionsIn);
      if (itRA != currRegionsHolder->regionAttributesMap.end ())
      {
        currRegionsHolder->regionAttributesMap.erase (itRA);
      }
    }
  }

  // Fill new atrributes.
  for (itRegions = regions.begin(); itRegions != regions.end(); itRegions++)
  {
    regionAttributes.attributes.clear();
    for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
    {
      regionsPtr = &itAttRegMap->second;
      for (itRegionsIn = regionsPtr->begin(); itRegionsIn != regionsPtr->end(); itRegionsIn++)
      {
        if (*itRegionsIn == *itRegions)
        {
          regionAttributes.attributes.insert(itAttRegMap->first);
        }
      }
    }
    regionAttributes.myActive = theActive;

    currRegionsHolder->regionAttributesMap[*itRegions] = regionAttributes;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::announceSynchronizationPoint(const std::wstring &theLabel, const GeRtiFactory::UserSuppliedTag &tag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              sprintf(galMsg, "Federate=%lu,Label=%ls", f, theLabel.c_str());
                              E2(GeRti_FM_i, "announceSynchronizationPoint", galMsg);
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E2(GeRti_FM_i, "announceSynchronizationPoint", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *label;
  int maxExceptions;

  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      fedAm->announceSynchronizationPoint(label, tag);
      stillAlive = true;
      CORBA::wstring_free(label);
      break;
    }
    catch(CORBA::SystemException &sysex)
    {
      CORBA::wstring_free(label);
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 3)
        {
          ACE_OS::sleep(ACE_Time_Value(0,500));
          continue;
        }
      }
      throw;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::associateRegionForUpdates(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSetMap &theAttributeRegions)
{
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap::iterator itAttribute;
  GERTICO::HandleSetMap::iterator itAttributeRegions;
  GERTICO::HandleSetSetMap::iterator itObjectAttributesRegions;
unsigned long ul;

  itObjectAttributesRegions = objectAttributesRegions.find(theObject);
  if (itObjectAttributesRegions != objectAttributesRegions.end())
  {
    GERTICO::HandleSetMap *attributeRegionsPtr;
    attributeRegionsPtr = &itObjectAttributesRegions->second;
    for (itAttributeRegions = theAttributeRegions.begin(); itAttributeRegions != theAttributeRegions.end(); itAttributeRegions++)
    {
      itAttribute = attributeRegionsPtr->find(itAttributeRegions->first);
      if (itAttribute != attributeRegionsPtr->end())
      {
        GERTICO::HandleSet *regions;
        regions = &itAttribute->second;
        for (itRegion = itAttributeRegions->second.begin(); itRegion != itAttributeRegions->second.end(); itRegion++)
        {
          regions->insert(*itRegion);
        }
      }
      else
      {
        GERTICO::HandleSet regions;
        for (itRegion = itAttributeRegions->second.begin(); itRegion != itAttributeRegions->second.end(); itRegion++)
        {
          regions.insert(*itRegion);
        }
        (*attributeRegionsPtr)[itAttributeRegions->first] = regions;
      }
    }
  }
  else
  {
    GERTICO::HandleSetMap attributeRegions;

    for (itAttributeRegions = theAttributeRegions.begin(); itAttributeRegions != theAttributeRegions.end(); itAttributeRegions++)
    {
      GERTICO::HandleSet regions;
      ul = itAttributeRegions->first;
      for (itRegion = itAttributeRegions->second.begin(); itRegion != itAttributeRegions->second.end(); itRegion++)
      {
        ul = *itRegion;
        regions.insert(*itRegion);
      }
      attributeRegions[itAttributeRegions->first] = regions;
    }
    objectAttributesRegions[theObject] = attributeRegions;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::checkPublishedAttributes(const GeRtiFactory::GeRtiHandle &theClass, const GERTICO::HandleSetMap &theAttRegMap)
{
  GERTICO::HandleSetMap::const_iterator itAttRegMap;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::PublishObjectClassFlagsRTI *currPublishObjectClassFlags;
  GERTICO::PublishObjectClassFlagsRTIMap::iterator itPOCFM;

  itPOCFM = pubObjectClassMap.find(theClass);
  if (itPOCFM == pubObjectClassMap.end())
  {
    throw GeRtiFactory::RTIinternalError(L"class not found");
  }

  currPublishObjectClassFlags = &itPOCFM->second;

  for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
  {
    itHS = currPublishObjectClassFlags->attributes.find(itAttRegMap->first);
    if (itHS == currPublishObjectClassFlags->attributes.end())
    {
      throw GeRtiFactory::AttributeNotPublished(L"checkPublishedAttributes");
    }
  }
}

// ---------------------------------------------------------------------------
// The idea is to clear out user data before a restore is made
// NB. may be useful in destructor to deallocate these structures as well.
// ---------------------------------------------------------------------------
void GERTICO::Federate::clear (void)
{
  GERTICO::ObjectKnown *currObjectKnown;
  GERTICO::ObjectKnownMap::iterator itOK;

//  pubInteractionMap.clear ();
  pubObjectClassMap.clear ();
//  subInteractionMap.clear ();
  subObjectClassMap.clear ();

  for (itOK = knownObjects.begin (); itOK != knownObjects.end (); itOK = knownObjects.begin ())
  {
    currObjectKnown = itOK->second;
    knownObjects.erase (itOK);
    delete currObjectKnown;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::confirmFederationRestorationRequest(const std::wstring &theLabel, const bool &success)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              if (success)
                              {
                                sprintf(galMsg,"Federate=%lu,name=%ls,success=true", f, theLabel.c_str());
                              }
                              else
                              {
                                sprintf(galMsg,"Federate=%lu,name=%ls,success=false", f, theLabel.c_str());
                              }
                              E2(GeRti_FM_i, "confirmFederationRestorationRequest", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *label;
  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);

  try
  {
    fedAm->confirmFederationRestorationRequest(label, success);
    stillAlive = true;
    CORBA::wstring_free(label);
  }
  catch (CORBA::SystemException &)
  {
    CORBA::wstring_free(label);
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "confirmFederationRestorationRequest", "SystemException");
                           #endif   // inserted by Gal converter
  }
  catch (...)
  {
    CORBA::wstring_free(label);
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "confirmFederationRestorationRequest", "Exception...");
                           #endif   // inserted by Gal converter
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "confirmFederationRestorationRequest", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::confirmSynchronizationPointRegistration(const std::wstring &theLabel, const CORBA::Boolean &success, const GeRtiFactory::SynchronizationPointFailureReason &theReason)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              if (success)
                              {
                                sprintf(galMsg,"Federate=%lu,name=%ls,success=true", f, theLabel.c_str());
                              }
                              else
                              {
                                sprintf(galMsg,"Federate=%lu,name=%ls,success=false", f, theLabel.c_str());
                              }
                              E2(GeRti_FM_i, "confirmSynchronizationPointRegistration", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *label;
  int maxExceptions;

  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      fedAm->confirmSynchronizationPointRegistration(label, success, theReason);
      stillAlive = true;
      CORBA::wstring_free(label);
      break;
    }
    catch(CORBA::SystemException &sysex)
    {
      CORBA::wstring_free(label);
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 2)
        {
          ACE_OS::sleep(ACE_Time_Value(0,500));
          continue;
        }
      }
      throw GeRtiFactory::RTIinternalError(L"confirmSynchronizationPointRegistration");
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "confirmSynchronizationPointRegistration", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::delObject (const GeRtiFactory::GeRtiHandle &obj)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = id;
                              ul = obj;
                              sprintf(galMsg, "Federate=%lu,Object=%lu", f, ul);
                              E2(GeRti_OM_i, "delObject", galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::ObjectKnown *currObjectKnown;
  GERTICO::ObjectKnownMap::iterator itOK;

  itOK = knownObjects.find (obj);
  if (itOK != knownObjects.end ())
  {
    currObjectKnown = itOK->second;
    knownObjects.erase (itOK);
    delete currObjectKnown;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OM_i, "delObject", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::delObjectClassRegionPub (const GeRtiFactory::GeRtiHandle &theObjectClass)
{
  GERTICO::PublishObjectClassFlagsRTIMap::iterator itHSM;

  itHSM = pubObjectClassMap.find (theObjectClass);
  if (itHSM != pubObjectClassMap.end ())
  {
    pubObjectClassMap.erase (itHSM);
  }
}

// ---------------------------------------------------------------------------
// NB. default region is 0, thus general logic applies for any specific
// region value.
// ---------------------------------------------------------------------------
void GERTICO::Federate::delObjectClassSub(const GeRtiFactory::GeRtiHandle &theObjectClass)
{
  CORBA::WChar *wChar = L"";
  ClassRegionsHolderMap::iterator itCRH;
  GERTICO::RegionAttributesMap::iterator itRA;
  GERTICO::FedRegionsHolder *currRegionsHolder;

  itCRH = subObjectClassMap.find (theObjectClass);
  if (itCRH != subObjectClassMap.end ())
  {
    currRegionsHolder = &itCRH->second;
    // Erase old attribute values for this object class and region.
    itRA = currRegionsHolder->regionAttributesMap.find(0);
    if (itRA != currRegionsHolder->regionAttributesMap.end ())
    {
      currRegionsHolder->regionAttributesMap.erase (itRA);
    }
    else
    {
      throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
    }

    if (currRegionsHolder->regionAttributesMap.size() == 0)
    {
      subObjectClassMap.erase(itCRH);
    }
  }
  else
  {
    throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
  }
}

// ---------------------------------------------------------------------------
// Delete all attribute / region specific pairs.
// NB. default region is 0, thus general logic applies for any specific
// region value.
// ---------------------------------------------------------------------------
void GERTICO::Federate::unsubscribeObjectClassWithRegion(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theRegions)
{
  CORBA::WChar *wChar = L"";
  ClassRegionsHolderMap::iterator itCRH;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::RegionAttributesMap::iterator itRA;
  GERTICO::FedRegionsHolder *currRegionsHolder;

  itCRH = subObjectClassMap.find (theObjectClass);
  if (itCRH != subObjectClassMap.end ())
  {
    currRegionsHolder = &itCRH->second;
    for (itRegion = theRegions.begin(); itRegion != theRegions.end(); itRegion++)
    {
      // Erase old attribute values for this object class and region.
      itRA = currRegionsHolder->regionAttributesMap.find(*itRegion);
      if (itRA != currRegionsHolder->regionAttributesMap.end ())
      {
        currRegionsHolder->regionAttributesMap.erase (itRA);
      }
      else
      {
        if (*itRegion)
        {
          throw GeRtiFactory::RegionNotKnown(wChar);
        }
        else
        {
          throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
        }
      }
    }

    if (currRegionsHolder->regionAttributesMap.size() == 0)
    {
      subObjectClassMap.erase(itCRH);
    }
  }
  else
  {
    throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
  }
}

// ---------------------------------------------------------------------------
// Delete all attribute / region specific pairs.
// NB. default region is 0, thus general logic applies for any specific
// region value.
// ---------------------------------------------------------------------------
void GERTICO::Federate::unsubscribeObjectClassWithRegions(const GeRtiFactory::GeRtiHandle &theObjectClass, const GERTICO::HandleSetMap &theAttributeRegions)
{
#ifndef IEEE_1516
  CORBA::WChar *wChar = L"unsubscribeObjectClassWithRegions";
#endif
  ClassRegionsHolderMap::iterator itCRH;
#ifdef IEEE_1516
  GERTICO::HandleSet *attributes;
#endif
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itAttributeDB;
  GERTICO::HandleSetMap regionAttributes;
  GERTICO::HandleSetMap::iterator itRegionMap;
#ifdef IEEE_1516
  GERTICO::RegionAttributes *regionAttributesPtr;
#endif
  GERTICO::RegionAttributesMap::iterator itRA;
  GERTICO::FedRegionsHolder *currRegionsHolder;

  GERTICO::Mapper::mapHandleSetMapInvert(regionAttributes, theAttributeRegions);
  itCRH = subObjectClassMap.find (theObjectClass);
  if (itCRH != subObjectClassMap.end ())
  {
    currRegionsHolder = &itCRH->second;
    for (itRegionMap = regionAttributes.begin(); itRegionMap != regionAttributes.end(); itRegionMap++)
    {
      // Erase old attribute values for this object class and region.
      itRA = currRegionsHolder->regionAttributesMap.find(itRegionMap->first);
      if (itRA != currRegionsHolder->regionAttributesMap.end ())
      {
#ifdef IEEE_1516
        attributes = &itRegionMap->second;
        for (itAttribute = attributes->begin(); itAttribute != attributes->end(); itAttribute++)
        {
          regionAttributesPtr = &itRA->second;
          itAttributeDB = regionAttributesPtr->attributes.find(*itAttribute);
          if (itAttributeDB != regionAttributesPtr->attributes.end())
          {
            regionAttributesPtr->attributes.erase(itAttributeDB);
          }
        }
#else
        currRegionsHolder->regionAttributesMap.erase (itRA);
#endif
      }
      else
      {
#ifndef IEEE_1516
        if (itRegionMap->first)
        {
          throw GeRtiFactory::RegionNotKnown(wChar);
        }
        else
        {
          throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
        }
#endif
      }
    }

    if (currRegionsHolder->regionAttributesMap.size() == 0)
    {
      subObjectClassMap.erase(itCRH);
    }
  }
#ifndef IEEE_1516
  else
  {
    throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
  }
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::disableAttributeScopeAdvisorySwitch (void)
{
  attributeScopeAdvisorySwitch = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::disableClassRelevanceAdvisorySwitch (void)
{
  classRelevanceAdvisorySwitch = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::attributeOwnershipDivestitureNotification(const GeRtiFactory::GeRtiHandle &theObject, GeRtiFactory::Handles &theDivestedAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itRegion;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_i)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"Federate::attributeOwnershipDivestitureNotification(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",releasedAttributes=", &galMsg[strlen(galMsg)], theDivestedAttributes);
                              strcat(galMsg, ") enter");
                              E1mEnd(GeRti_OWM_i, galMsg);
                            }
                           #endif   // inserted by Gal converter

  fedAm->attributeOwnershipDivestitureNotification(theObject, theDivestedAttributes);
  len = theDivestedAttributes.length();
  for (i = 0; i < len; i++)
  {
    getObjectAttributeRegions(theObject, theDivestedAttributes[i], regions);

    for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
    {
      unassociateAttributeRegionForUpdates(theObject, theDivestedAttributes[i], *itRegion);
    }
  }

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OWM_i, "Federate::attributeOwnershipDivestitureNotification", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Should only be called in a separate thread.
// ---------------------------------------------------------------------------
void GERTICO::Federate::attributesInScope(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes)
{
  CORBA::ULong i;
  CORBA::ULong ind = 0;
  CORBA::ULong len;
  CORBA::ULong ul;
  GERTICO::AttributeInstanceKnown *attributeInstanceKnown;
  GERTICO::AttributeInstanceKnownMap::iterator itAttribute;
  GERTICO::HandleSet::iterator iti;
  GERTICO::ObjectKnown *objectKnown;
  GERTICO::ObjectKnownMap::iterator itObject;
  GeRtiFactory::Handles attributes;

  // Only do in-scope when it is out-of-scope.
  GERTICO::Mapper::mapULongSizet(ul, theAttributes.size());
  attributes.length(ul);
  ul = 0;
  attributes.length(ul);
  itObject = knownObjects.find(theObject);
  if (itObject != knownObjects.end())
  {
    objectKnown = itObject->second;
    for (iti = theAttributes.begin(); iti != theAttributes.end(); iti++)
    {
      itAttribute = objectKnown->atts.find(*iti);
      if (itAttribute != objectKnown->atts.end())
      {
        attributeInstanceKnown = &itAttribute->second;
        if (attributeInstanceKnown->getInScope() == false)
        {
          attributes.length(ind + 1);
          attributes[ind++] = *iti;
        }
      }
    }
  }

  theAttributes.clear();

  // Set flags in any case.
  len = attributes.length();
  for (i = 0; i < len; i++)
  {
    itAttribute = objectKnown->atts.find(attributes[i]);
    if (itAttribute != objectKnown->atts.end())
    {
      attributeInstanceKnown = &itAttribute->second;
      attributeInstanceKnown->setScope(true);
    }
    theAttributes.insert(attributes[i]);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::attributesInScopeRemote(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_d)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = id;
                              ul = theObject;
                              sprintf(galMsg, "Federate=%lu,Object=%lu", f, ul);
                              E2(GeRti_OM_d, "attributesInScopeRemote", galMsg);
                              GERTICO::Mapper::printHandleSet("attributes=", galMsg, theAttributes);
                              E2(GeRti_OM_d, "attributesInScopeRemote", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::ULong ind = 0;
  CORBA::ULong len;
  CORBA::ULong ul;
  GERTICO::AttributeInstanceKnownMap::iterator itAttribute;
  GERTICO::HandleSet::iterator iti;
  GERTICO::ObjectKnownMap::iterator itObject;
  GeRtiFactory::Handles attributes;
  int maxExceptions;

  // Only do in-scope when it is out-of-scope.
  GERTICO::Mapper::mapULongSizet(ul, theAttributes.size());
  attributes.length(ul);
  ul = 0;
  attributes.length(ul);
  for (iti = theAttributes.begin(); iti != theAttributes.end(); iti++)
  {
    attributes.length(ind + 1);
    attributes[ind++] = *iti;
  }

  len = attributes.length();
  if (len)
  {
    // Only if advisory switch is true.
    if (getAttributeScopeAdvisorySwitch())
    {
      for (maxExceptions = 0;;maxExceptions++)
      {
        try
        {
          fedAm->attributesInScope(theObject, attributes);
          stillAlive = true;
          break;
        }
        catch(CORBA::SystemException &sysex)
        {
          if (sysex.minor() == 0)
          {
            maxExceptions += 1;
            if (maxExceptions < 2)
            {
              ACE_OS::sleep(ACE_Time_Value(0,500));
              continue;
            }
          }
         throw GeRtiFactory::RTIinternalError(L"attributesInScope");
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::attributeIsNotOwned(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_i)
                            {
                              char galMsg[512];
                              unsigned long ul;
                              unsigned long ul1;

                              ul = theObject;
                              ul1 = theAttribute;
                              sprintf(galMsg,"Federate::attributeIsNotOwned(object=%lu,attribute=%lu) enter", ul, ul1);
                              E1mEnd(GeRti_OWM_i, galMsg);
                            }
                           #endif   // inserted by Gal converter

  fedAm->attributeIsNotOwned(theObject, theAttribute);

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OWM_i, "Federate::attributeIsNotOwned", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::attributeOwnedByRTI(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_i)
                            {
                              char galMsg[512];
                              unsigned long ul;
                              unsigned long ul1;

                              ul = theObject;
                              ul1 = theAttribute;
                              sprintf(galMsg,"GeRtiFactory_FederateAmbassador_i::attributeOwnedByRTI(object=%lu,attribute=%lu) enter", ul, ul1);
                              E1mEnd(GeRti_OWM_i, galMsg);
                            }
                           #endif   // inserted by Gal converter

  fedAm->attributeOwnedByRTI(theObject, theAttribute);

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OWM_i, "GeRtiFactory_FederateAmbassador_i::attributeOwnedByRTI", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::attributeOwnershipAcquisitionNotification(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &securedAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_i)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"Federate::attributeOwnershipAcquisitionNotification(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",securedAttributes=", &galMsg[strlen(galMsg)], securedAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], theTag);
                              strcat(galMsg, ") enter");
                              E1mEnd(GeRti_OWM_i, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  fedAm->attributeOwnershipAcquisitionNotification(theObject, securedAttributes, theTag);

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OWM_i, "Federate::attributeOwnershipAcquisitionNotification", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::attributeOwnershipUnavailable(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_i)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"Federate::attributeOwnershipUnavailable(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              strcat(galMsg, ") enter");
                              E1mEnd(GeRti_OWM_i, galMsg);
                            }
                           #endif   // inserted by Gal converter

  fedAm->attributeOwnershipUnavailable(theObject, theAttributes);

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OWM_i, "Federate::attributeOwnershipUnavailable", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::confirmAttributeOwnershipAcquisitionCancellation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_i)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"GeRtiFactory_FederateAmbassador_i::confirmAttributeOwnershipAcquisitionCancellation(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              strcat(galMsg, ") enter");
                              E1mEnd(GeRti_OWM_i, galMsg);
                            }
                           #endif   // inserted by Gal converter

  fedAm->confirmAttributeOwnershipAcquisitionCancellation(theObject, theAttributes);

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OWM_i, "GeRtiFactory_FederateAmbassador_i::confirmAttributeOwnershipAcquisitionCancellation", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::informAttributeOwnership(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute, GeRtiFactory::GeRtiHandle const &theOwner)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_i)
                            {
                              char galMsg[512];
                              unsigned long ul;
                              unsigned long ul1;
                              unsigned long ul2;

                              ul = theObject;
                              ul1 = theAttribute;
                              ul2 = theOwner;
                              sprintf(galMsg,"GFederate::informAttributeOwnership(object=%lu,attribute=%lu,owner=%lu) enter", ul, ul1, ul2);
                              E1mEnd(GeRti_OWM_i, galMsg);
                            }
                           #endif   // inserted by Gal converter

  fedAm->informAttributeOwnership(theObject, theAttribute, theOwner);

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OWM_i, "Federate::informAttributeOwnership", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::requestAttributeOwnershipAssumption(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &offeredAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_i)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"Federate::requestAttributeOwnershipAssumption(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], offeredAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], theTag);
                              strcat(galMsg, ") enter");
                              E1mEnd(GeRti_OWM_i, galMsg);
                            }
                           #endif   // inserted by Gal converter

  fedAm->requestAttributeOwnershipAssumption(theObject, offeredAttributes, theTag);

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              E2(GeRti_OWM_i, "Federate::requestAttributeOwnershipAssumption", "leave");
                            }
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::requestAttributeOwnershipRelease(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &candidateAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_i)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"Federate::requestAttributeOwnershipRelease(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",candidateAttributes=", &galMsg[strlen(galMsg)], candidateAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], theTag);
                              strcat(galMsg, ") enter");
                              E1mEnd(GeRti_OWM_i, galMsg);
                            }
                           #endif   // inserted by Gal converter

  fedAm->requestAttributeOwnershipRelease(theObject, candidateAttributes, theTag);

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OWM_i, "Federate::requestAttributeOwnershipRelease", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::requestDivestitureConfirmation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &releasedAttributes)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_i)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"Federate::requestDivestitureConfirmation(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",releasedAttributes=", &galMsg[strlen(galMsg)], releasedAttributes);
                              strcat(galMsg, ") enter");
                              E1mEnd(GeRti_OWM_i, galMsg);
                            }
                           #endif   // inserted by Gal converter

  fedAm->requestDivestitureConfirmation(theObject, releasedAttributes);

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              E2(GeRti_OWM_i, "Federate::requestDivestitureConfirmation", "leave");
                            }
#endif
}

// ---------------------------------------------------------------------------
// Should only be called in a separate thread.
// ---------------------------------------------------------------------------
void GERTICO::Federate::attributesOutOfScope(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes)
{
  CORBA::ULong i = 0;
  CORBA::ULong ind = 0;
  CORBA::ULong length = 0;
  CORBA::ULong ul;
  GERTICO::AttributeInstanceKnown *attributeInstanceKnown;
  GERTICO::AttributeInstanceKnownMap::iterator itAttribute;
  GERTICO::HandleSet::iterator iti;
  GERTICO::ObjectKnown *objectKnown;
  GERTICO::ObjectKnownMap::iterator itObject;
  GeRtiFactory::Handles attributes;

  // Only do out-of-scope when it is in-scope.
  GERTICO::Mapper::mapULongSizet(ul, theAttributes.size());
  attributes.length(ul);
  ul = 0;
  attributes.length(ul);
  // Find the object.
  itObject = knownObjects.find(theObject);
  if (itObject != knownObjects.end())
  {
    objectKnown = itObject->second;
    for (iti = theAttributes.begin(); iti != theAttributes.end(); iti++)
    {
      itAttribute = objectKnown->atts.find(*iti);

      // Check the attribute.
      if (itAttribute != objectKnown->atts.end())
      {
        attributeInstanceKnown = &itAttribute->second;
        if (attributeInstanceKnown->getInScope())
        {
          attributes.length(ind + 1);
          attributes[ind++] = *iti;
        }
      }
    }
  }

  theAttributes.clear();

  // Set flags in any case.
  length = attributes.length();
  for (i = 0; i < length; i++)
  {
    itAttribute = objectKnown->atts.find(attributes[i]);
    if (itAttribute != objectKnown->atts.end())
    {
      attributeInstanceKnown = &itAttribute->second;
      attributeInstanceKnown->setScope(false);
    }
    theAttributes.insert(attributes[i]);
  }
}

// ---------------------------------------------------------------------------
// Should only be called in a separate thread.
// ---------------------------------------------------------------------------
void GERTICO::Federate::attributesOutOfScopeRemote(const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSet &theAttributes, const bool &theSendFlag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_d)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = id;
                              ul = theObject;
                              sprintf(galMsg, "Federate=%lu,Object=%lu", f, ul);
                              E2(GeRti_OM_d, "attributesOutOfScopeRemote", galMsg);
                              GERTICO::Mapper::printHandleSet("attributes=", galMsg, theAttributes);
                              E2(GeRti_OM_d, "attributesOutOfScopeRemote", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::ULong ind = 0;
  CORBA::ULong length = 0;
  CORBA::ULong ul;
  GERTICO::AttributeInstanceKnownMap::iterator itAttribute;
  GERTICO::HandleSet::iterator iti;
  GERTICO::ObjectKnownMap::iterator itObject;
  GeRtiFactory::Handles attributes;
  int maxExceptions;

  if (theSendFlag == false)
  {
    return;
  }

  GERTICO::Mapper::mapULongSizet(ul, theAttributes.size());
  attributes.length(ul);
  ul = 0;
  attributes.length(ul);
  for (iti = theAttributes.begin(); iti != theAttributes.end(); iti++)
  {
    attributes.length(ind + 1);
    attributes[ind++] = *iti;
  }

  length = attributes.length();
  if (length)
  {
    // Only if advisory switch is true.
    if (attributeScopeAdvisorySwitch)
    {
      for (maxExceptions = 0;;maxExceptions++)
      {
        try
        {
          fedAm->attributesOutOfScope(theObject, attributes);
          stillAlive = true;
          break;
        }
        catch(CORBA::SystemException &sysex)
        {
          if (sysex.minor() == 0)
          {
            maxExceptions += 1;
            if (maxExceptions < 2)
            {
              ACE_OS::sleep(ACE_Time_Value(0,500));
              continue;
            }
          }
          throw GeRtiFactory::RTIinternalError(L"attributesOutOfScope");
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::announceObjectInstance(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theClass, const std::wstring &theName, GERTICO::HandleSet &theAttributes)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long f;
                              unsigned long ul;
                              unsigned long ul1;

                              f = id;
                              ul = theObject;
                              ul1 = theClass;
                              sprintf(galMsg, "Federate=%lu,Object=%lu,Class=%lu,Name=%ls", f, ul, ul1, theName.c_str());
                              E2(GeRti_OM_i, "announceObjectInstance", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wName;
  GeRtiFactory::Handles attributes;
  int maxExceptions;

  GERTICO::Mapper::mapWcharFromWstring(&wName, theName);

  GERTICO::Mapper::mapHandleSet(attributes, theAttributes);

  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      fedAm->announceObjectInstance(theObject, theClass, attributes, wName);
      stillAlive = true;
      CORBA::wstring_free(wName);
      break;
    }
    catch(CORBA::SystemException &sysex)
    {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 2)
        {
          ACE_OS::sleep(ACE_Time_Value(0,500));
          continue;
        }
      }
      CORBA::wstring_free(wName);
      throw GeRtiFactory::RTIinternalError(L"announceObjectInstance");
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::discoverObjectInstance(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theClass, const std::wstring &theName)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long f;
                              unsigned long ul;
                              unsigned long ul1;

                              f = id;
                              ul = theObject;
                              ul1 = theClass;
                              sprintf(galMsg, "Federate=%lu,Object=%lu,Class=%lu,Name=%ls", f, ul, ul1, theName.c_str());
                              E2(GeRti_OM_i, "discoverObjectInstance", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wName;
  int maxExceptions;

  GERTICO::Mapper::mapWcharFromWstring(&wName, theName);

  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      fedAm->discoverObjectInstance(theObject, theClass, wName);
      stillAlive = true;
      CORBA::wstring_free(wName);
      break;
    }
    catch(CORBA::SystemException &sysex)
    {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 2)
        {
          ACE_OS::sleep(ACE_Time_Value(0,500));
          continue;
        }
      }
      CORBA::wstring_free(wName);
      throw GeRtiFactory::RTIinternalError(L"discoverObjectInstance");
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::doMomRequest(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::HandleValues & data)
{
  try
  {
    fedAm->doMomRequest(theRequest, data);
    stillAlive = true;
  }
  catch (CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "doMomRequest");
  }
  catch (...)
  {
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::enableAttributeScopeAdvisorySwitch (void)
{
  attributeScopeAdvisorySwitch = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::enableClassRelevanceAdvisorySwitch (void)
{
  classRelevanceAdvisorySwitch = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::federateRestoreComplete (const bool &success)
{
  restoreComplete = true;
  restoreSuccess = success;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::federateSaveBegun (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              sprintf(galMsg, "Federate=%lu", f);
                              E2(GeRti_FM_i, "federateSaveBegun", galMsg);
                            }
                           #endif   // inserted by Gal converter
  saveBegun = true;
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federateSaveBegun", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::federateSaveComplete (const bool &theSuccess, const std::string &theSaveData)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              if (theSuccess)
                              {
                                sprintf(galMsg,"Federate=%lu,success=true", f);
                              }
                              else
                              {
                                sprintf(galMsg,"Federate=%lu,success=false", f);
                              }
                              E2(GeRti_FM_i, "federateSaveComplete", galMsg);
                            }
                           #endif   // inserted by Gal converter
  saveComplete = true;
  saveSuccess = theSuccess;
  saveData = theSaveData;
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federateSaveComplete", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::federationRestored(const bool &theSuccess, const GeRtiFactory::RestoreFailureReason &theFailureReason)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              if (theSuccess)
                              {
                                sprintf(galMsg,"Federate=%lu,success=true", f);
                              }
                              else
                              {
                                sprintf(galMsg,"Federate=%lu,success=false", f);
                              }
                              E2(GeRti_FM_i, "federationRestored", galMsg);
                            }
                           #endif   // inserted by Gal converter
  restoreComplete = false;
  restoreBegun = false;
  restoreInitiated = false;

  try
  {
    fedAm->federationRestored(theSuccess, theFailureReason);
    stillAlive = true;
  }
  catch (CORBA::SystemException &sysex)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federationRestored", "SystemException");
                           #endif   // inserted by Gal converter
      ACE_PRINT_EXCEPTION(sysex, "federationRestored");
  }
  catch (...)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federationRestored", "Exception...");
                           #endif   // inserted by Gal converter
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federationRestored", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::federationRestoreBegun (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              sprintf(galMsg, "Federate=%lu", f);
                              E2(GeRti_FM_i, "federationRestoreBegun", galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    fedAm->federationRestoreBegun ();
    stillAlive = true;
  }
  catch (CORBA::SystemException &)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federationRestoreBegun", "SystemException");
                           #endif   // inserted by Gal converter
  }
  catch (...)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federationRestoreBegun", "Exception...");
                           #endif   // inserted by Gal converter
  }

  restoreBegun = true;
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federationRestoreBegun", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::federationSaved(const bool &theSuccess, const GeRtiFactory::SaveFailureReason &theFailureReason)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              if (theSuccess)
                              {
                                sprintf(galMsg,"Federate=%lu,success=true", f);
                              }
                              else
                              {
                                sprintf(galMsg,"Federate=%lu,success=false", f);
                              }
                              E2(GeRti_FM_i, "federationSaved", galMsg);
                            }
                           #endif   // inserted by Gal converter
  try
  {
    fedAm->federationSaved(theSuccess, theFailureReason);
    stillAlive = true;
  }
  catch (CORBA::SystemException &sysex)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federationSaved", "SystemException");
                           #endif   // inserted by Gal converter
      ACE_PRINT_EXCEPTION (sysex, "federationSaved");
  }
  catch (...)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federationSaved", "Exception...");
                           #endif   // inserted by Gal converter
  }
  unsetFederateSave ();
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "federationSaved", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::federationSynchronized(const std::wstring &theLabel)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              sprintf(galMsg,"Federate=%lu,label=%ls", f, theLabel.c_str());
                              E2(GeRti_FM_i, "federationSynchronized", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *label;
  int maxExceptions;

  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      fedAm->federationSynchronized(label);
      stillAlive = true;
      CORBA::wstring_free(label);
      break;
    }
    catch(CORBA::SystemException &sysex)
    {
      CORBA::wstring_free(label);
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 2)
        {
          ACE_OS::sleep(ACE_Time_Value(0,500));
          continue;
        }
      }
      throw GeRtiFactory::RTIinternalError(L"federationSynchronized");
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiRestore_ptr GERTICO::Federate::getGeRtiRestore (void)
{
  return GeRtiFactory::GeRtiRestore::_duplicate(geRtiRestoreVar);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::getAttributeScopeAdvisorySwitch (void)
{
  return attributeScopeAdvisorySwitch;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::getClassRelevanceAdvisorySwitch (void)
{
  return classRelevanceAdvisorySwitch;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::Federate::getId (void)
{
  return id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getInScope(const unsigned long &theObject, GERTICO::HandleSet &theAttributes)
{
  GERTICO::AttributeInstanceKnown *currAttributeInstanceKnown;
  GERTICO::AttributeInstanceKnownMap::iterator itAIK;
  GERTICO::ObjectKnown *objectKnown;
  GERTICO::ObjectKnownMap::iterator itOK;

  theAttributes.clear();
  itOK = knownObjects.find(theObject);
  if (itOK != knownObjects.end())
  {
    objectKnown = itOK->second;
    for (itAIK = objectKnown->atts.begin(); itAIK != objectKnown->atts.end(); itAIK++)
    {
      currAttributeInstanceKnown = &itAIK->second;
      if (currAttributeInstanceKnown->getInScope())
      {
        theAttributes.insert(itAIK->first);
      }
    }
    return;
  }

  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::getInScope (const unsigned long &theObject, GERTICO::HandleSet &theOutAttributes, GERTICO::HandleSet &theInAttributes)
{
  GERTICO::HandleSet::iterator itHS;
  GERTICO::AttributeInstanceKnown *currAttributeInstanceKnown;
  GERTICO::AttributeInstanceKnownMap::iterator itAIK;
  GERTICO::ObjectKnown *currObjectKnown;
  GERTICO::ObjectKnownMap::iterator itOK;
  bool gotOne = false;

  if (attributeScopeAdvisorySwitch == false)
  {
    return false;
  }

  itOK = knownObjects.find(theObject);
  if (itOK != knownObjects.end ())
  {
    currObjectKnown = itOK->second;
    for (itHS = theInAttributes.begin (); itHS != theInAttributes.end (); itHS++)
    {
      itAIK = currObjectKnown->atts.find (*itHS);
      if (itAIK != currObjectKnown->atts.end ())
      {
        currAttributeInstanceKnown = &itAIK->second;
        if (currAttributeInstanceKnown->getInScope () == false)
        {
          theOutAttributes.insert (*itHS);
          gotOne = true;
        }
      }
    }
    return gotOne;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getKnownObjects(GERTICO::HandleSet &theObjects)
{
  GERTICO::ObjectKnownMap::iterator itOK;

  for (itOK = knownObjects.begin(); itOK != knownObjects.end(); itOK++)
  {
    theObjects.insert(itOK->first);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getKnownObjects(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theObjects)
{
  GERTICO::ObjectKnown *currObjectKnown;
  GERTICO::ObjectKnownMap::iterator itOK;

  for (itOK = knownObjects.begin(); itOK != knownObjects.end(); itOK++)
  {
    currObjectKnown = itOK->second;
    if (currObjectKnown->getClassId() == theClass)
    {
      theObjects.insert(itOK->first);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getMaps(HandleSetMap &theSubObjectsMap)
{
  ClassRegionsHolderMap::iterator itCRH;
  HandleSet newHandleSet;
  HandleSet *currHandleSet;
  HandleSetMap::iterator itHSM;
  GERTICO::RegionAttributesMap::iterator itRA;
  GERTICO::FedRegionsHolder *currRegionsHolder;

  for (itCRH = subObjectClassMap.begin (); itCRH != subObjectClassMap.end (); itCRH++)
  {
    currRegionsHolder = &itCRH->second;
    newHandleSet.clear ();
    theSubObjectsMap[itCRH->first] = newHandleSet;
    itHSM = theSubObjectsMap.find (itCRH->first);
    if (itHSM != theSubObjectsMap.end ())
    {
      currHandleSet = &itHSM->second;
      for (itRA = currRegionsHolder->regionAttributesMap.begin (); itRA != currRegionsHolder->regionAttributesMap.end (); itRA++)
      {
        currHandleSet->insert (itRA->first);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::getMomData(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::Handles & theAttributes, GeRtiFactory::HandleValues_out data)
{
  try
  {
    fedAm->getMomData(theRequest, theAttributes, data);
    stillAlive = true;
  }
  catch (CORBA::SystemException &sysex)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "getMomData", "SystemException");
                           #endif   // inserted by Gal converter
      ACE_PRINT_EXCEPTION(sysex, "getMomData");
      return true;
  }
  catch (...)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "getMomData", "Exception...");
                           #endif   // inserted by Gal converter
      return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getObjectAttributeRegions(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute, GERTICO::HandleSet &theRegions)
{
  GERTICO::HandleSetMap::iterator itAttribute;
  GERTICO::HandleSetMap::iterator itAttributeRegions;
  GERTICO::HandleSetMap::iterator itTheAttribute;
  GERTICO::HandleSetSetMap::iterator itObjectAttributesRegions;

  itObjectAttributesRegions = objectAttributesRegions.find(theObject);
  if (itObjectAttributesRegions != objectAttributesRegions.end())
  {
    GERTICO::HandleSetMap *attributeRegionsPtr;
    attributeRegionsPtr = &itObjectAttributesRegions->second;
    itAttribute = attributeRegionsPtr->find(theAttribute);
    if (itAttribute != attributeRegionsPtr->end())
    {
      theRegions = itAttribute->second;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::Federate::getObjectClass (const GeRtiFactory::GeRtiHandle &theObject)
{
  GERTICO::ObjectKnownMap::iterator itOK;
  GeRtiFactory::GeRtiHandle ret = 0;

  itOK = knownObjects.find (theObject);
  if (itOK != knownObjects.end ())
  {
    ret = itOK->second->getClassId ();
  }
  else
  {
    throw GeRtiFactory::ObjectNotKnown(L"getObjectClass");
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::print(const GeRtiFactory::GeRtiHandle &theObject)
{
  GERTICO::ObjectKnownMap::iterator itOK;

  itOK = knownObjects.find (theObject);
  if (itOK != knownObjects.end ())
  {
    itOK->second->print();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::getOutScope (const unsigned long &theObj, GERTICO::HandleSet &outAttributes, GERTICO::HandleSet &theAttributes)
{
  GERTICO::HandleSet::iterator itHS;
  GERTICO::AttributeInstanceKnown *currAttributeInstanceKnown;
  GERTICO::AttributeInstanceKnownMap::iterator itAIK;
  GERTICO::ObjectKnown *currObjectKnown;
  GERTICO::ObjectKnownMap::iterator itOK;
  bool gotOne = false;
  if (attributeScopeAdvisorySwitch == false)
  {
    return false;
  }

  itOK = knownObjects.find (theObj);
  if (itOK != knownObjects.end ())
  {
    currObjectKnown = itOK->second;
    for (itHS = theAttributes.begin (); itHS != theAttributes.end (); itHS++)
    {
      itAIK = currObjectKnown->atts.find (*itHS);
      if (itAIK != currObjectKnown->atts.end ())
      {
        currAttributeInstanceKnown = &itAIK->second;
        if (currAttributeInstanceKnown->getInScope ())
        {
          outAttributes.insert (*itHS);
          gotOne = true;
        }
      }
    }
    return gotOne;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getPublishedAttributes(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributeSet)
{
  GERTICO::PublishObjectClassFlagsRTI *publishObjectClassFlags;
  GERTICO::PublishObjectClassFlagsRTIMap::iterator itPOCF;

  itPOCF = pubObjectClassMap.find(theClass);
  if (itPOCF != pubObjectClassMap.end())
  {
    publishObjectClassFlags = &itPOCF->second;
    theAttributeSet = publishObjectClassFlags->attributes;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getPublishedObjectClasses(GERTICO::HandleSet &thePublishedClasses)
{
  GERTICO::PublishObjectClassFlagsRTIMap::iterator itPOCF;

  for (itPOCF = pubObjectClassMap.begin(); itPOCF != pubObjectClassMap.end(); itPOCF++)
  {
    thePublishedClasses.insert(itPOCF->first);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
/*
bool GERTICO::Federate::getStarted (const GeRtiFactory::GeRtiHandle &theClass)
{
  GERTICO::PublishObjectClassFlagsRTIMap::iterator itPOCF;
  bool ret = false;

  itPOCF = pubObjectClassMap.find (theClass);
  if (itPOCF != pubObjectClassMap.end ())
  {
    ret = itPOCF->second.getStarted ();
  }

  return ret;
}
*/

// ---------------------------------------------------------------------------
// Use ONLY when the the publisher is publishing in the default region!!!!
// ---------------------------------------------------------------------------
void GERTICO::Federate::getSubscribedAttributes(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes)
{
  ClassRegionsHolderMap::iterator itCRHM;
  HandleSet::iterator itAttribute;
  HandleSet::iterator itHS;
  GERTICO::FedRegionsHolder *regionsHolder;
  RegionAttributes *regionAttributes;
  GERTICO::RegionAttributesMap::iterator itRAM;

  theAttributes.clear();

  itCRHM = subObjectClassMap.find(theClass);
  if (itCRHM != subObjectClassMap.end())
  {
    regionsHolder = &itCRHM->second;
    for (itRAM = regionsHolder->regionAttributesMap.begin(); itRAM != regionsHolder->regionAttributesMap.end(); itRAM++)
    {
      regionAttributes = &itRAM->second;
      for (itHS = regionAttributes->attributes.begin(); itHS != regionAttributes->attributes.end(); itHS++)
      {
        itAttribute = theAttributes.find(*itHS);
        if (itAttribute == theAttributes.end())
        {
          theAttributes.insert(*itHS);
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getSubscribedAttributes(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributesOut, GERTICO::HandleSet &theAttributesIn)
{
  GERTICO::ClassRegionsHolderMap::iterator itCRHM;
  GeRtiFactory::GeRtiHandle region;
  GERTICO::HandleSet::iterator itAttributesIn;
  GERTICO::HandleSet::iterator itAttributesRegion;
  GERTICO::FedRegionsHolder *regionsHolder;
  GERTICO::RegionAttributes *regionAttributes;
  GERTICO::RegionAttributesMap::iterator itRAM;

  theAttributesOut.clear();

  itCRHM = subObjectClassMap.find(theObjectClass);
  if (itCRHM != subObjectClassMap.end())
  {
    regionsHolder = &itCRHM->second;

    region = 0;
    itRAM = regionsHolder->regionAttributesMap.find(region);
    if (itRAM != regionsHolder->regionAttributesMap.end())
    {
      regionAttributes = &itRAM->second;
      for (itAttributesIn = theAttributesIn.begin(); itAttributesIn != theAttributesIn.end(); itAttributesIn++)
      {
        itAttributesRegion = regionAttributes->attributes.find(*itAttributesIn);
        if (itAttributesRegion != regionAttributes->attributes.end())
        {
          theAttributesOut.insert(*itAttributesIn);
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getSubscribedAttributeRegions(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theAttribute, GERTICO::HandleSet &theRegions, const bool &onlyActiveSubscriptions)
{
  ClassRegionsHolderMap::iterator itCRHM;
  HandleSet::iterator itAttribute;
  HandleSet::iterator itRegion;
  GERTICO::FedRegionsHolder *regionsHolder;
  RegionAttributes *regionAttributes;
  GERTICO::RegionAttributesMap::iterator itRAM;

  theRegions.clear();

  itCRHM = subObjectClassMap.find(theClass);
  if (itCRHM != subObjectClassMap.end())
  {
    regionsHolder = &itCRHM->second;

    for (itRAM = regionsHolder->regionAttributesMap.begin(); itRAM != regionsHolder->regionAttributesMap.end(); itRAM++)
    {
      regionAttributes = &itRAM->second;
      if (onlyActiveSubscriptions)
      {
        if (regionAttributes->myActive == false)
        {
          continue;
        }
      }
      itAttribute = regionAttributes->attributes.find(theAttribute);
      if (itAttribute != regionAttributes->attributes.end())
      {
        itRegion = theRegions.find(itRAM->first);
        if (itRegion == theRegions.end())
        {
          theRegions.insert(itRAM->first);
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getSubscribedObjectClasses(GERTICO::HandleSet &theSubscribedObjectClasses)
{
  ClassRegionsHolderMap::iterator itCRH;

  for (itCRH = subObjectClassMap.begin(); itCRH != subObjectClassMap.end(); itCRH++)
  {
    theSubscribedObjectClasses.insert(itCRH->first);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getSubscribedRegionAttributes(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theRegion, GERTICO::HandleSet &theAttributes)
{
  ClassRegionsHolderMap::iterator itCRHM;
  HandleSet::iterator itHS;
  GERTICO::FedRegionsHolder *regionsHolder;
  RegionAttributes *regionAttributes;
  GERTICO::RegionAttributesMap::iterator itRAM;

  theAttributes.clear();

  itCRHM = subObjectClassMap.find(theClass);
  if (itCRHM != subObjectClassMap.end())
  {
    regionsHolder = &itCRHM->second;

    itRAM = regionsHolder->regionAttributesMap.find(theRegion);
    if (itRAM != regionsHolder->regionAttributesMap.end())
    {
      regionAttributes = &itRAM->second;
      for (itHS = regionAttributes->attributes.begin(); itHS != regionAttributes->attributes.end(); itHS++)
      {
        theAttributes.insert(*itHS);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::getSubscribedRegions(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theRegions)
{
  ClassRegionsHolderMap::iterator itCRHM;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::RegionAttributesMap::iterator itRAM;
  GERTICO::FedRegionsHolder *regionsHolder;

  theRegions.clear();

  itCRHM = subObjectClassMap.find(theClass);
  if (itCRHM != subObjectClassMap.end())
  {
    regionsHolder = &itCRHM->second;

    for (itRAM = regionsHolder->regionAttributesMap.begin(); itRAM != regionsHolder->regionAttributesMap.end(); itRAM++)
    {
      itHS = theRegions.find(itRAM->first);
      if (itHS == theRegions.end())
      {
        theRegions.insert(itRAM->first);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::getTimeConstrained (void)
{
  return timeConstrained;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::initiateFederateRestore(const std::wstring &theLabel, const GeRtiFactory::GeRtiHandle &h)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = id;
                              ul = h;
                              sprintf(galMsg, "Federate=%lu,label=%ls,Handle=%lu", f, theLabel.c_str(), ul);
                              E2(GeRti_FM_i, "initiateFederateRestore", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *label;

  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
  try
  {
    fedAm->initiateFederateRestore(label, h);
    stillAlive = true;
    CORBA::wstring_free(label);
  }
  catch (CORBA::SystemException &)
  {
    CORBA::wstring_free(label);
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "initiateFederateRestore", "SystemException");
                           #endif   // inserted by Gal converter
  }
  catch (...)
  {
    CORBA::wstring_free(label);
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "initiateFederateRestore", "Exception...");
                           #endif   // inserted by Gal converter
  }

  restoreInitiated = true;
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "initiateFederateRestore", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::initiateFederateSave(const std::wstring &theLabel, const bool &theCorbaCall)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              if (theCorbaCall)
                              {
                                sprintf(galMsg,"Federate=%lu,Label=%ls,corbaCall=true", f, theLabel.c_str());
                              }
                              else
                              {
                                sprintf(galMsg,"Federate=%lu,Label=%ls,corbaCall=false", f, theLabel.c_str());
                              }
                              E2(GeRti_FM_i, "initiateFederateSave", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *label;

  if (saveInitiated == true)
  {
    if (theLabel == saveLabel)
    {
      return;
    }
  }

  if (saveBegun == true)
  {
    return;
  }

  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
  try
  {
    if (theCorbaCall)
    {
      fedAm->initiateFederateSave(label);
      stillAlive = true;
    }

    CORBA::wstring_free(label);
    saveInitiated = true;
    saveInitiatedWithTime = false;
    saveLabel = theLabel;
  }
  catch (CORBA::SystemException &sysex)
  {
    CORBA::wstring_free(label);
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "initiateFederateSave", "SystemException");
                           #endif   // inserted by Gal converter
    ACE_PRINT_EXCEPTION(sysex, "initiateFederateSave");
  }
  catch (GeRtiFactory::UnableToPerformSave &)
  {
    CORBA::wstring_free(label);
    saveInitiated = false;
    saveInitiatedWithTime = false;
    saveLabel = L"";
  }
  catch (GeRtiFactory::FederateInternalError &)
  {
    CORBA::wstring_free(label);
    saveInitiated = false;
    saveInitiatedWithTime = false;
    saveLabel = L"";
  }
  catch (...)
  {
    CORBA::wstring_free(label);
    saveInitiated = false;
    saveInitiatedWithTime = false;
    saveLabel = L"";
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "initiateFederateSave", "Exception...");
                           #endif   // inserted by Gal converter
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "initiateFederateSave", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::initiateFederateSaveWithTime(const std::wstring &theLabel, const GERTICO::GeRtiFedTime &theFedTime, const GERTICO::GeRtiFedTime &theRtiFedTime, const bool &theCorbaCall)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              unsigned long f;

                              f = id;
                              if (theCorbaCall)
                              {
                                sprintf(galMsg,"Federate=%lu,Label=%ls,corbaCall=true", f, theLabel.c_str());
                              }
                              else
                              {
                                sprintf(galMsg,"Federate=%lu,Label=%ls,corbaCall=false", f, theLabel.c_str());
                              }
                              E2(GeRti_FM_i, "initiateFederateSaveWithTime", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *label;
  if (saveInitiatedWithTime == true)
  {
    if (theLabel == saveLabel)
    {
      if (theRtiFedTime == *nextSaveTime)
      {
        return;
      }
    }
  }

  if (saveBegun == true)
  {
    return;
  }

  *nextSaveTime = theRtiFedTime;

  GERTICO::Mapper::mapWcharFromWstring(&label, theLabel);
  try
  {
    if (theCorbaCall)
    {
      GeRtiFactory::Time myTime;
      ConvertTime::mapIt(myTime, theFedTime);
      fedAm->initiateFederateSaveWithTime(label, myTime);
      stillAlive = true;
    }

    saveInitiatedWithTime = true;
    saveInitiated = false;
    saveLabel = theLabel;
  }
  catch (CORBA::SystemException &sysex)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "initiateFederateSaveWithTime", "SystemException");
                           #endif   // inserted by Gal converter
    ACE_PRINT_EXCEPTION(sysex, "initiateFederateSaveWithTime");
  }
  catch (GeRtiFactory::UnableToPerformSave &)
  {
    saveInitiated = false;
    saveInitiatedWithTime = false;
    saveLabel = L"";
  }
  catch (GeRtiFactory::FederateInternalError &)
  {
    saveInitiated = false;
    saveInitiatedWithTime = false;
    saveLabel = L"";
  }
  catch (...)
  {
    saveInitiated = false;
    saveInitiatedWithTime = false;
    saveLabel = L"";
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "initiateFederateSaveWithTime", "Exception...");
                           #endif   // inserted by Gal converter
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_i, "initiateFederateSaveWithTime", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::isJoinedFinished(void)
{
  return joinedFinished;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::isInScope(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute)
{
  GERTICO::AttributeInstanceKnown *attributePtr;
  GERTICO::AttributeInstanceKnownMap::iterator itAttribute;
  GERTICO::ObjectKnown *objectPtr;
  GERTICO::ObjectKnownMap::iterator itObject;

  itObject = knownObjects.find(theObject);
  if (itObject != knownObjects.end())
  {
    objectPtr = itObject->second;
    itAttribute = objectPtr->atts.find(theAttribute);
    if (itAttribute != objectPtr->atts.end())
    {
      attributePtr = &itAttribute->second;
      return attributePtr->getInScope();
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::isPublishingObjectClassAttribute(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theAttribute)
{
  GERTICO::PublishObjectClassFlagsRTIMap::iterator itPublishObjectClassFlagsMap;

  itPublishObjectClassFlagsMap = pubObjectClassMap.find(theObjectClass);
  if (itPublishObjectClassFlagsMap != pubObjectClassMap.end())
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::isSubscribedToObjectClass(const GeRtiFactory::GeRtiHandle &theObjectClass)
{
  ClassRegionsHolderMap::iterator itCRH;

  itCRH = subObjectClassMap.find(theObjectClass);
  if (itCRH != subObjectClassMap.end())
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::isSubscribedToObjectClassAttribute(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theAttribute, const bool &onlyActiveSubscriptions)
{
  ClassRegionsHolderMap::iterator itCRH;
  HandleSet::iterator itHS;
  RegionAttributes *regionAttributes;
  GERTICO::FedRegionsHolder *currRegionsHolder;
  GERTICO::RegionAttributesMap::iterator itRA;

  itCRH = subObjectClassMap.find(theObjectClass);
  if (itCRH != subObjectClassMap.end())
  {
    currRegionsHolder = &itCRH->second;
    for (itRA = currRegionsHolder->regionAttributesMap.begin(); itRA != currRegionsHolder->regionAttributesMap.end(); itRA++)
    {
      regionAttributes = &itRA->second;
      if (onlyActiveSubscriptions)
      {
        if (regionAttributes->myActive == false)
        {
          continue;
        }
      }
      itHS = regionAttributes->attributes.find(theAttribute);
      if (itHS != regionAttributes->attributes.end())
      {
        return true;
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::isSubscribedToObjectClassRegionAttribute(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::GeRtiHandle &theAttribute)
{
  ClassRegionsHolderMap::iterator itCRH;
  HandleSet::iterator itHS;
  RegionAttributes *currRegionAttributes;
  GERTICO::FedRegionsHolder *currRegionsHolder;
  GERTICO::RegionAttributesMap::iterator itRA;

  itCRH = subObjectClassMap.find(theObjectClass);
  if (itCRH != subObjectClassMap.end())
  {
    currRegionsHolder = &itCRH->second;
    itRA = currRegionsHolder->regionAttributesMap.find(theRegion);
    if (itRA != currRegionsHolder->regionAttributesMap.end())
    {
      currRegionAttributes = &itRA->second;
      itHS = currRegionAttributes->attributes.find(theAttribute);
      if (itHS != currRegionAttributes->attributes.end())
      {
        return true;
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::isSubscribedToObjectClassAttributes(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theRegion, GERTICO::HandleSet &theAttributes)
{
  ClassRegionsHolderMap::iterator itCRH;
  HandleSet::iterator itAttribute;
  HandleSet::iterator itHS;
  RegionAttributes *currRegionAttributes;
  GERTICO::FedRegionsHolder *currRegionsHolder;
  GERTICO::RegionAttributesMap::iterator itRA;

  itCRH = subObjectClassMap.find(theObjectClass);
  if (itCRH != subObjectClassMap.end())
  {
    currRegionsHolder = &itCRH->second;
    itRA = currRegionsHolder->regionAttributesMap.find(theRegion);
    if (itRA != currRegionsHolder->regionAttributesMap.end())
    {
      currRegionAttributes = &itRA->second;
      for (itAttribute = theAttributes.begin(); itAttribute != theAttributes.end(); itAttribute++)
      {
        itHS = currRegionAttributes->attributes.find(*itAttribute);
        if (itHS != currRegionAttributes->attributes.end())
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
void GERTICO::Federate::joinFederationExecutionFinished(void)
{
  joinedFinished = true;
  stillAlive = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::localDeleteObjectInstance (const GeRtiFactory::GeRtiHandle &theObject)
{
  CORBA::WChar *wChar = L"";
  GERTICO::ObjectKnownMap::iterator itOK;
  bool knowBool = false;

  itOK = knownObjects.find (theObject);
  if (itOK != knownObjects.end ())
  {
    knowBool = true;
  }
  else
  {
    throw GeRtiFactory::ObjectNotKnown(wChar);
  }

  if (knowBool)
  {
    knownObjects.erase (itOK);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::objectInstanceNameReservationSucceeded(std::wstring const &theObjectInstanceName)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long f;

                              f = id;
                              sprintf(galMsg, "Federate=%lu,Name=%ls", f, theObjectInstanceName.c_str());
                              E2(GeRti_OM_i, "objectInstanceNameReservationSucceeded", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *objectName;
  GERTICO::Mapper::mapWcharFromWstring(&objectName, theObjectInstanceName);

  try
  {
    fedAm->objectInstanceNameReservationSucceeded(objectName);
    stillAlive = true;
  }
  catch(CORBA::SystemException &)
  {
    CORBA::wstring_free(objectName);
    throw GeRtiFactory::RTIinternalError(L"objectInstanceNameReservationSucceeded");
  }

  CORBA::wstring_free(objectName);
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::ping(void)
{
  fedAm->ping();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::print (void)
{
/*
  GERTICO::ClassRegionsHolderMap::iterator itOA;
  GERTICO::HandleSet::iterator itR;
  GERTICO::FedRegionsHolder *regionsHolder;
  GERTICO::RegionAttributes *currRegionSet;
  GERTICO::RegionAttributesMap::iterator itA;

std::cout << "Federate " << id << std::endl;
  for (itOA = subObjectClassMap.begin(); itOA != subObjectClassMap.end(); itOA++)
  {
    regionsHolder = &itOA->second;
std::cout << "Class " << itOA->first << std::endl;

    // Print the region for each attribute.
    for (itA = regionsHolder->regionAttributesMap.begin (); itA != regionsHolder->regionAttributesMap.end (); itA++)
    {
      currRegionSet = &itA->second;
std::cout << "Region " << itA->first << std::endl;
      for (itR = currRegionSet->attributes.begin (); itR != currRegionSet->attributes.end (); itR++)
      {
        GeRtiFactory::GeRtiHandle h;
        h = *itR;
std::cout << "Attribute " << *itR << std::endl;
      }
    }
  }
std::cout << std::endl;

  GERTICO::AttributeInstanceKnown *attributePtr;
  GERTICO::AttributeInstanceKnownMap::iterator itAttribute;
  GERTICO::ObjectKnown *objectPtr;
  GERTICO::ObjectKnownMap::iterator itObject;
  unsigned long ul;

  for (itObject = knownObjects.begin(); itObject != knownObjects.end(); itObject++)
  {
    ul = itObject->first;
std::cout << "Object " << ul << std::endl;
    objectPtr = itObject->second;
    for (itAttribute = objectPtr->atts.begin(); itAttribute != objectPtr->atts.end(); itAttribute++)
    {
      ul = itAttribute->first;
std::cout << "Attribute " << ul << std::endl;
      attributePtr = &itAttribute->second;
      if (attributePtr->getInScope())
      {
std::cout << "In scope " << std::endl;
      }
      else
      {
std::cout << "Out of scope " << std::endl;
      }
    }
  }

  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap::iterator itAttributeRegions;
  GERTICO::HandleSetSetMap::iterator itObjectAttributesRegions;

std::cout << "objectAttributesRegions " << std::endl;
  for (itObjectAttributesRegions = objectAttributesRegions.begin(); itObjectAttributesRegions != objectAttributesRegions.end(); itObjectAttributesRegions++)
  {
ul = itObjectAttributesRegions->first;
std::cout << "Object " << ul << std::endl;
    for (itAttributeRegions = itObjectAttributesRegions->second.begin(); itAttributeRegions != itObjectAttributesRegions->second.end(); itAttributeRegions++)
    {
ul = itAttributeRegions->first;
std::cout << "Attribute " << ul << std::endl;
      for (itRegion = itAttributeRegions->second.begin(); itRegion != itAttributeRegions->second.end(); itRegion++)
      {
ul = *itRegion;
std::cout << "Region " << ul << std::endl;
      }
    }
  }
*/
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::provideAttributeValueUpdate(const GeRtiFactory::GeRtiHandle &theObject, GeRtiFactory::Handles &theAttributes, const GeRtiFactory::UserSuppliedTag &theTag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = id;
                              ul = theObject;
                              sprintf(galMsg, "Federate=%lu,Object=%lu", f, ul);
                              E2(GeRti_OM_i, "provideAttributeValueUpdate", galMsg);
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theAttributes);
                              E2(GeRti_OM_i, "provideAttributeValueUpdate", galMsg);
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                              E2(GeRti_OM_i, "provideAttributeValueUpdate", galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions;

  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      fedAm->provideAttributeValueUpdate(theObject, theAttributes, theTag);
      stillAlive = true;
      break;
    }
    catch(CORBA::SystemException &sysex)
    {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 2)
        {
          ACE_OS::sleep(ACE_Time_Value(0,500));
          continue;
        }
      }
      throw GeRtiFactory::RTIinternalError(L"provideAttributeValueUpdate");
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::publishObjectClass (const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::PublishObjectClassFlagsRTI publishObjectClassFlags;
  GERTICO::PublishObjectClassFlagsRTIMap::iterator itPOCF;

  itPOCF = pubObjectClassMap.find (theObjectClass);
  if (itPOCF != pubObjectClassMap.end ())
  {
    itPOCF->second.attributes.clear ();
    itPOCF->second.attributes = theAttributes;
  }
  else
  {
    publishObjectClassFlags.attributes = theAttributes;
    pubObjectClassMap[theObjectClass] = publishObjectClassFlags;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::removeObjectInstance(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::UserSuppliedTag &theTag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = id;
                              ul = theObject;
                              sprintf(galMsg, "Federate=%lu,Object=%lu", f, ul);
                              E2(GeRti_OM_i, "removeObjectInstance", galMsg);
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                              E2(GeRti_OM_i, "removeObjectInstance", galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions;

  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      fedAm->removeObjectInstance(theObject, theTag);
      stillAlive = true;
      break;
    }
    catch(CORBA::SystemException &sysex)
    {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 2)
        {
          ACE_OS::sleep(ACE_Time_Value(0,500));
          continue;
        }
      }
      throw GeRtiFactory::RTIinternalError(L"removeObjectInstance");
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::removeObjectInstanceWithTime(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::Time &theTime, const GeRtiFactory::ERHandle &theERHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = id;
                              ul = theObject;
                              sprintf(galMsg, "Federate=%lu,Object=%lu", f, ul);
                              E2(GeRti_OM_i, "removeObjectInstanceWithTime", galMsg);
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                              E2(GeRti_OM_i, "removeObjectInstanceWithTime", galMsg);
                            }
                           #endif   // inserted by Gal converter
  int maxExceptions;

  for (maxExceptions = 0;;maxExceptions++)
  {
    try
    {
      fedAm->removeObjectInstanceWithTime(theObject, theTag, theTime, theERHandle);
      stillAlive = true;
      break;
    }
    catch(CORBA::SystemException &sysex)
    {
      if (sysex.minor() == 0)
      {
        maxExceptions += 1;
        if (maxExceptions < 2)
        {
          ACE_OS::sleep(ACE_Time_Value(0,500));
          continue;
        }
      }
      throw GeRtiFactory::RTIinternalError(L"removeObjectInstanceWithTime");
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::resetAlive(void)
{
  stillAlive = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::restore (DOMElement &theDOMElement)
{
  CORBA::ULong ul;
  DOMNode* child;
  DOMNode* subChild;
  GERTICO::HandleSet::iterator itHS;
  GeRtiFactory::Handles attributeList;
//  PublishInteractionFlags publishInteractionFlags;
  GERTICO::PublishObjectClassFlagsRTI publishObjectClassFlags;
  GERTICO::RegionAttributesMap::iterator itRA;
  RegisteredObject *currRegisteredObject;
  bool b;
  char *tmpChar;
  std::string tmpString;
  unsigned long i;
  unsigned long tmpATT;
  unsigned long tmpCLASS;
  unsigned long tmpID;
  unsigned long tmpOBJECT;
//  unsigned long tmpREGION;
  unsigned long tmpUL;

  clear ();

  for (child = theDOMElement.getFirstChild (); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (publishedInteractionsStr.c_str ())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (classStr.c_str ())) == 0)
            {
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpID);
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (turnedOnStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpUL);
              if (tmpUL)
              {
                b = true;
              }
              else
              {
                b = false;
              }
//              publishInteractionFlags.setTurnedOn (b);
//              pubInteractionMap[tmpID] = publishInteractionFlags;
              try
              {
                geRtiRestoreVar->publishInteractionClass(tmpID);
              }
              catch (CORBA::SystemException &)
              {
              }
              catch (GeRtiFactory::InteractionClassNotDefined &)
              {
              }
              catch (GeRtiFactory::RTIinternalError &)
              {
              }
            }
          }
        }
      }
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (publishedObjectClassesStr.c_str ())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (classStr.c_str ())) == 0)
            {
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpID);
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (startedStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpUL);
              if (tmpUL)
              {
                b = true;
              }
              else
              {
                b = false;
              }
              publishObjectClassFlags.setStarted (b);

              for (DOMNode* subSubChild = subChild->getFirstChild(); subSubChild != 0; subSubChild = subSubChild->getNextSibling())
              {
                if (subSubChild->getNodeType() == DOMNode::ELEMENT_NODE)
                {
                  if (XMLString::compareString(subSubChild->getNodeName(),XMLString::transcode (attributesStr.c_str ())) == 0)
                  {
                    for (DOMNode* subSubSubChild = subSubChild->getFirstChild(); subSubSubChild != 0; subSubSubChild = subSubSubChild->getNextSibling())
                    {
                      if (subSubSubChild->getNodeType() == DOMNode::ELEMENT_NODE)
                      {
                        if (XMLString::compareString(subSubSubChild->getNodeName(),XMLString::transcode (attributeStr.c_str ())) == 0)
                        {
                          tmpChar = XMLString::transcode (((DOMElement*)subSubSubChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
                          sscanf (tmpChar, "%lu", &tmpATT);
                          publishObjectClassFlags.attributes.insert (tmpATT);
                        }
                      }
                    }
                  }
                }
              }
              pubObjectClassMap[tmpID] = publishObjectClassFlags;
              GERTICO::Mapper::mapULongSizet(ul, publishObjectClassFlags.attributes.size());
              attributeList.length (ul);
              for (i = 0, itHS = publishObjectClassFlags.attributes.begin(); itHS != publishObjectClassFlags.attributes.end(); i++, itHS++)
              {
                unsigned int ui;
                ui = *itHS;
                attributeList[i] = *itHS;
              }
              try
              {
                geRtiRestoreVar->publishObjectClass(tmpID, attributeList);
              }
              catch (CORBA::SystemException &)
              {
              }
              catch (GeRtiFactory::ObjectClassNotDefined &)
              {
              }
              catch (GeRtiFactory::AttributeNotDefined &)
              {
              }
              catch (GeRtiFactory::RTIinternalError &)
              {
              }
            }
          }
        }
      }
      /*
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (subscribedInteractionsStr.c_str ())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (classStr.c_str ())) == 0)
            {
              CORBA::Boolean myActive;
              SubInteractionFlagMap subInteractionFlagMap;
              bool theActive;
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpCLASS);
              for (DOMNode* subSubChild = subChild->getFirstChild(); subSubChild != 0; subSubChild = subSubChild->getNextSibling())
              {
                if (subSubChild->getNodeType() == DOMNode::ELEMENT_NODE)
                {
                  if (XMLString::compareString(subSubChild->getNodeName(),XMLString::transcode (regionsStr.c_str ())) == 0)
                  {
                    for (DOMNode* subSubSubChild = subSubChild->getFirstChild(); subSubSubChild != 0; subSubSubChild = subSubSubChild->getNextSibling())
                    {
                      if (subSubSubChild->getNodeType() == DOMNode::ELEMENT_NODE)
                      {
                        if (XMLString::compareString(subSubSubChild->getNodeName(),XMLString::transcode (regionStr.c_str ())) == 0)
                        {
                          tmpChar = XMLString::transcode (((DOMElement*)subSubSubChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
                          sscanf (tmpChar, "%lu", &tmpREGION);
                          tmpChar = XMLString::transcode (((DOMElement*)subSubSubChild)->getAttribute (XMLString::transcode (activeStr.c_str ())));
                          sscanf (tmpChar, "%lu", &tmpUL);
                          if (tmpUL)
                          {
                            theActive = true;
                          }
                          else
                          {
                            theActive = false;
                          }
                          subInteractionFlagMap[tmpREGION] = theActive;
                        }
                      }
                    }
                  }
                }
              }
              subInteractionMap[tmpCLASS] = subInteractionFlagMap;

              try
              {
                if (theActive)
                {
                  myActive = 1;
                }
                if (tmpREGION)
                {
                  geRtiRestoreVar->subscribeInteractionClassWithRegion (tmpCLASS, myActive, tmpREGION);
                }
                else
                {
                  geRtiRestoreVar->subscribeInteractionClass (tmpCLASS, myActive);
                }
              }
              catch (CORBA::SystemException &)
              {
              }
              catch (GeRtiFactory::InteractionClassNotDefined &)
              {
              }
              catch (GeRtiFactory::RegionNotKnown &)
              {
              }
              catch (GeRtiFactory::RTIinternalError &)
              {
              }
            }
          }
        }
      }
      */
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (subscribedObjectClassesStr.c_str ())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (classStr.c_str ())) == 0)
            {
              GERTICO::FedRegionsHolder regionsHolder;
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpCLASS);
              for (DOMNode* subSubChild = subChild->getFirstChild(); subSubChild != 0; subSubChild = subSubChild->getNextSibling())
              {
                if (subSubChild->getNodeType() == DOMNode::ELEMENT_NODE)
                {
                  if (XMLString::compareString(subSubChild->getNodeName(),XMLString::transcode (regionsStr.c_str ())) == 0)
                  {
                    regionsHolder.restore (*((DOMElement *)subSubChild));
                  }
                }
              }
              subObjectClassMap[tmpCLASS] = regionsHolder;
              for (itRA = regionsHolder.regionAttributesMap.begin(); itRA != regionsHolder.regionAttributesMap.end(); itRA++)
              {
                HandleSet::iterator itHS;
                RegionAttributes *currRegionAttributes;
                unsigned int region;

                region = itRA->first;
                currRegionAttributes = &itRA->second;
                GERTICO::Mapper::mapULongSizet(ul, currRegionAttributes->attributes.size());
                attributeList.length (ul);
                for (i = 0, itHS = currRegionAttributes->attributes.begin (); itHS != currRegionAttributes->attributes.end (); i++, itHS++)
                {
                  attributeList[i] = *itHS;
                }
                try
                {
                  if (region)
                  {
                    geRtiRestoreVar->subscribeObjectClassAttributesWithRegion(tmpCLASS, attributeList, currRegionAttributes->myActive, region);
                  }
                  else
                  {
                    geRtiRestoreVar->subscribeObjectClassAttributes(tmpCLASS, attributeList, currRegionAttributes->myActive);
                  }
                }
                catch (CORBA::SystemException &)
                {
                }
                catch (GeRtiFactory::ObjectClassNotDefined &)
                {
                }
                catch (GeRtiFactory::AttributeNotDefined &)
                {
                }
                catch (GeRtiFactory::RegionNotKnown &)
                {
                }
                catch (GeRtiFactory::RTIinternalError &)
                {
                }
              }
            }
          }
        }
      }
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (knownObjectsStr.c_str ())) == 0)
      {
        GERTICO::ClassDescr *classDescr;
        GERTICO::HandleSet attributes;

        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (knownObjectStr.c_str ())) == 0)
            {
              AttributeInstanceKnown attributeInstanceKnown;
              AttributeInstanceKnownMap attributeInstanceKnownMap;
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpOBJECT);
              tmpChar = XMLString::transcode (((DOMElement*)subChild)->getAttribute (XMLString::transcode (classStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpCLASS);
              classDescr = pObjectRoot.getClassDescr(tmpCLASS);
              attributes.clear();
              classDescr->getAttributes(attributes);
              ObjectKnown *objectKnown = new ObjectKnown (tmpOBJECT, tmpCLASS, attributes);
              for (DOMNode* subSubChild = subChild->getFirstChild(); subSubChild != 0; subSubChild = subSubChild->getNextSibling())
              {
                if (subSubChild->getNodeType() == DOMNode::ELEMENT_NODE)
                {
                  if (XMLString::compareString(subSubChild->getNodeName(),XMLString::transcode (attributesStr.c_str ())) == 0)
                  {
                    for (DOMNode* subSubSubChild = subSubChild->getFirstChild(); subSubSubChild != 0; subSubSubChild = subSubSubChild->getNextSibling())
                    {
                      if (subSubSubChild->getNodeType() == DOMNode::ELEMENT_NODE)
                      {
                        tmpChar = XMLString::transcode (((DOMElement*)subSubSubChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
                        sscanf (tmpChar, "%lu", &tmpATT);
                        attributeInstanceKnown.setId (tmpATT);
                        tmpChar = XMLString::transcode (((DOMElement*)subSubSubChild)->getAttribute (XMLString::transcode (inScopeStr.c_str ())));
                        sscanf (tmpChar, "%lu", &tmpUL);
                        attributeInstanceKnown.setScope(tmpUL);
                        objectKnown->atts[tmpATT] = attributeInstanceKnown;
                      }
                    }
                  }
                }
              }
              knownObjects[tmpOBJECT] = objectKnown;
              try
              {
                currRegisteredObject = registeredObjectsHolder.getObject(tmpOBJECT);
                std::wstring name;
                AttributeInfo *attributeInfo;
                GERTICO::HandleSet attributes;
                GERTICO::HandleSet regions;
                GERTICO::HandleSet::iterator itAttribute;
                CORBA::ULong i;
                CORBA::ULong j;
                size_t len;
                GERTICO::HandleSet::iterator itRegion;
                GeRtiFactory::AttData attData;
                GeRtiFactory::AttributesData attributesData;
                currRegisteredObject->getName (name);
                currRegisteredObject->getAttributeIds(attributes);
                GERTICO::Mapper::mapULongSizet(ul, attributes.size());
                attributesData.length(ul);
                for (i = 0, itAttribute = attributes.begin (); itAttribute != attributes.end (); i++, itAttribute++)
                {
                  try
                  {
                    attributeInfo = currRegisteredObject->getAttribute(*itAttribute);
                  }
                  catch(...)
                  {
                    continue;
                  }
                  attData.theId = *itAttribute;
                  attData.theFederate = attributeInfo->getFederate();
// XXX                  attData.theAcquiringFederate = attributeInfo->acquiringFederate;
                  attributeInfo->getAllRegions(regions);
                  len = regions.size();
                  GERTICO::Mapper::mapULongSizet(ul, len);
                  attData.theRegions.length(ul);
                  for (j = 0, itRegion = regions.begin(); itRegion != regions.end(); j++, itRegion++)
                  {
                    attData.theRegions[j] = *itRegion;
                  }
                  attData.theStatus = attributeInfo->getStatus();
                  attData.theOrderType = attributeInfo->getOrderType();
                  attData.theTransportationType = attributeInfo->getTransportationType();
                  attributesData[i] = attData;
                }
                try
                {
                  geRtiRestoreVar->loadObject(tmpOBJECT, name.c_str (), tmpCLASS, attributesData);
                }
                catch (CORBA::SystemException &)
                {
                }
                catch (GeRtiFactory::ObjectClassNotDefined &)
                {
                }
                catch (GeRtiFactory::AttributeNotDefined &)
                {
                }
                catch (GeRtiFactory::RegionNotKnown &)
                {
                }
                catch (GeRtiFactory::RTIinternalError &)
                {
                }
              }
              catch(...)
              {
              }
            }
          }
        }
      }
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (lrcDataStr.c_str ())) == 0)
      {
        tmpChar = XMLString::transcode (((DOMElement*)child)->getAttribute (XMLString::transcode (dataStr.c_str ())));
        try
        {
          geRtiRestoreVar->loadLRC(tmpChar);
        }
        catch (CORBA::SystemException &)
        {
        }
        catch (GeRtiFactory::RTIinternalError &)
        {
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::save (DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  AttributeInstanceKnownMap::iterator itAIK;
  ClassRegionsHolderMap::iterator itCRH;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  DOMElement* elemLevel3;
  DOMElement* elemLevel4;
  DOMElement* elemLevel5;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::ObjectKnownMap::iterator itOK;
//  PublishInteractionFlagsMap::iterator itPIF;
  GERTICO::PublishObjectClassFlagsRTIMap::iterator itPOCF;
//  SubInteractionFlagMap::iterator itSI;
//  SubInteractionFlagsMap::iterator itSIF;
  XMLCh tempStr[100];
  XMLCh tempStr1[10000];
  unsigned long ul;

  XMLString::transcode(federateStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  XMLString::transcode(idStr.c_str (), tempStr, 99);
  sprintf (buf, "%lu", id);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(publishedInteractionsStr.c_str (), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  /*
  for (itPIF = pubInteractionMap.begin (); itPIF != pubInteractionMap.end (); itPIF++)
  {
    XMLString::transcode(classStr.c_str (), tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode(idStr.c_str (), tempStr, 99);
    ul = itPIF->first;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    XMLString::transcode(turnedOnStr.c_str (), tempStr, 99);
    ul = itPIF->second.getTurnedOn ();
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);
  }
  */

  XMLString::transcode(publishedObjectClassesStr.c_str (), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  for (itPOCF = pubObjectClassMap.begin (); itPOCF != pubObjectClassMap.end (); itPOCF++)
  {
    XMLString::transcode(classStr.c_str (), tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode(idStr.c_str (), tempStr, 99);
    ul = itPOCF->first;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    XMLString::transcode(startedStr.c_str (), tempStr, 99);
    ul = itPOCF->second.getStarted ();
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    XMLString::transcode(attributesStr.c_str (), tempStr, 99);
    elemLevel4 = theDOMDocument.createElement(tempStr);
    elemLevel3->appendChild(elemLevel4);

    for (itHS = itPOCF->second.attributes.begin (); itHS != itPOCF->second.attributes.end (); itHS++)
    {
      XMLString::transcode(attributeStr.c_str (), tempStr, 99);
      elemLevel5 = theDOMDocument.createElement(tempStr);
      elemLevel4->appendChild(elemLevel5);

      XMLString::transcode(idStr.c_str (), tempStr, 99);
      ul = *itHS;
      sprintf (buf, "%lu", ul);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel5->setAttribute(tempStr, tempStr1);
    }
  }

  XMLString::transcode(subscribedInteractionsStr.c_str (), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  /*
  for (itSIF = subInteractionMap.begin (); itSIF != subInteractionMap.end (); itSIF++)
  {
    XMLString::transcode(classStr.c_str (), tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode(idStr.c_str (), tempStr, 99);
    ul = itSIF->first;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    XMLString::transcode(regionsStr.c_str (), tempStr, 99);
    elemLevel4 = theDOMDocument.createElement(tempStr);
    elemLevel3->appendChild(elemLevel4);

    for (itSI = itSIF->second.begin (); itSI != itSIF->second.end (); itSI++)
    {
      XMLString::transcode(regionStr.c_str (), tempStr, 99);
      elemLevel5 = theDOMDocument.createElement(tempStr);
      elemLevel4->appendChild(elemLevel5);

      XMLString::transcode(activeStr.c_str (), tempStr, 99);
      if (itSI->second)
      {
        strcpy (buf, "1");
      }
      else
      {
        strcpy (buf, "0");
      }
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel5->setAttribute(tempStr, tempStr1);


      XMLString::transcode(idStr.c_str (), tempStr, 99);
      ul = itSI->first;
      sprintf (buf, "%lu", ul);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel5->setAttribute(tempStr, tempStr1);
    }
  }
  */

  XMLString::transcode(subscribedObjectClassesStr.c_str (), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  for (itCRH = subObjectClassMap.begin (); itCRH != subObjectClassMap.end (); itCRH++)
  {
    XMLString::transcode(classStr.c_str (), tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode(idStr.c_str (), tempStr, 99);
    ul = itCRH->first;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    XMLString::transcode(regionsStr.c_str (), tempStr, 99);
    elemLevel4 = theDOMDocument.createElement(tempStr);
    elemLevel3->appendChild(elemLevel4);

    itCRH->second.save (theDOMDocument, *elemLevel4);
  }

  XMLString::transcode(knownObjectsStr.c_str (), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  for (itOK = knownObjects.begin (); itOK != knownObjects.end (); itOK++)
  {
    XMLString::transcode(knownObjectStr.c_str (), tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode(idStr.c_str (), tempStr, 99);
    ul = itOK->first;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    XMLString::transcode(classStr.c_str (), tempStr, 99);
    ul = itOK->second->getClassId ();
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    XMLString::transcode(attributesStr.c_str (), tempStr, 99);
    elemLevel4 = theDOMDocument.createElement(tempStr);
    elemLevel3->appendChild(elemLevel4);

    for (itAIK = itOK->second->atts.begin (); itAIK != itOK->second->atts.end (); itAIK++)
    {
      XMLString::transcode(attributeStr.c_str (), tempStr, 99);
      elemLevel5 = theDOMDocument.createElement(tempStr);
      elemLevel4->appendChild(elemLevel5);

      XMLString::transcode(idStr.c_str (), tempStr, 99);
      ul = itAIK->first;
      sprintf (buf, "%lu", ul);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel5->setAttribute(tempStr, tempStr1);

      XMLString::transcode(inScopeStr.c_str (), tempStr, 99);
      ul = itAIK->second.getInScope ();
      sprintf (buf, "%lu", ul);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel5->setAttribute(tempStr, tempStr1);
    }
  }

  XMLString::transcode(lrcDataStr.c_str (), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  XMLString::transcode(dataStr.c_str (), tempStr, 99);
  XMLString::transcode(saveData.c_str (), tempStr1, 9999);
  elemLevel2->setAttribute(tempStr, tempStr1);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::setAlive(void)
{
  stillAlive = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::setId (const GeRtiFactory::GeRtiHandle &theFederateId)
{
  id = theFederateId;
  geRtiRestoreVar->setLRCFederate (id);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::setInScope(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute)
{
  GERTICO::AttributeInstanceKnown *currAttributeInstanceKnown;
  GERTICO::AttributeInstanceKnownMap::iterator itAIK;
  GERTICO::ObjectKnown *currObjectKnown;
  GERTICO::ObjectKnownMap::iterator itKO;

  itKO = knownObjects.find(theObject);
  if (itKO != knownObjects.end())
  {
    currObjectKnown = itKO->second;
    itAIK = currObjectKnown->atts.find(theAttribute);
    if (itAIK != currObjectKnown->atts.end())
    {
      currAttributeInstanceKnown = &itAIK->second;
      if (currAttributeInstanceKnown->getInScope() == false)
      {
        currAttributeInstanceKnown->setScope(true);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::setOutScope(const GeRtiFactory::GeRtiHandle &theObject, GeRtiFactory::Handles &theAttributes)
{
  GERTICO::AttributeInstanceKnown *currAttributeInstanceKnown;
  GERTICO::AttributeInstanceKnownMap::iterator itAIK;
  GERTICO::ObjectKnown *currObjectKnown;
  GERTICO::ObjectKnownMap::iterator itKO;
  unsigned long i;
  unsigned long length;

  length = theAttributes.length();

  itKO = knownObjects.find(theObject);
  if (itKO != knownObjects.end())
  {
    currObjectKnown = itKO->second;
    for (i = 0; i < length; i++)
    {
      itAIK = currObjectKnown->atts.find(theAttributes[i]);
      if (itAIK != currObjectKnown->atts.end())
      {
        currAttributeInstanceKnown = &itAIK->second;
        if (currAttributeInstanceKnown->getInScope())
        {
          currAttributeInstanceKnown->setScope(false);
        }
      }
    }
  }
}

/*
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::setPublishingInteraction (const GeRtiFactory::GeRtiHandle &theInteraction, const bool &thePublishing)
{
  PublishInteractionFlagsMap::iterator itPIF;

  itPIF = pubInteractionMap.find (theInteraction);
  if (itPIF != pubInteractionMap.end ())
  {
    itPIF->second.setTurnedOn (thePublishing);
  }
}
*/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
/*
void GERTICO::Federate::setStarted (const GeRtiFactory::GeRtiHandle &theClass, const bool &theStarted)
{
  GERTICO::PublishObjectClassFlagsRTIMap::iterator itPOCF;

  itPOCF = pubObjectClassMap.find (theClass);
  if (itPOCF != pubObjectClassMap.end ())
  {
    itPOCF->second.setStarted (theStarted);
  }
}
*/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::testAlive(void)
{
  return stillAlive;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::testTurnedOn(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute)
{
  GERTICO::HandleSet *subscribers;
  GERTICO::HandleSet::iterator itSubscriber;
  GERTICO::HandleSetMap *attributes;
  GERTICO::HandleSetMap::iterator itAttribute;
  GERTICO::HandleSetSetMap::iterator itTurnOnUpdates;

  itTurnOnUpdates = turnOnUpdates.find(theObject);
  if (itTurnOnUpdates != turnOnUpdates.end())
  {
    attributes = &itTurnOnUpdates->second;
    itAttribute = attributes->find(theAttribute);
    if (itAttribute != attributes->end())
    {
      subscribers = &itAttribute->second;
      if (subscribers->size())
      {
        return true;
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::testTurnedOn(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute, const GeRtiFactory::GeRtiHandle &theSubscriber)
{
  GERTICO::HandleSet *subscribers;
  GERTICO::HandleSet::iterator itSubscriber;
  GERTICO::HandleSetMap *attributes;
  GERTICO::HandleSetMap::iterator itAttribute;
  GERTICO::HandleSetSetMap::iterator itTurnOnUpdates;

  itTurnOnUpdates = turnOnUpdates.find(theObject);
  if (itTurnOnUpdates != turnOnUpdates.end())
  {
    attributes = &itTurnOnUpdates->second;
    itAttribute = attributes->find(theAttribute);
    if (itAttribute != attributes->end())
    {
      subscribers = &itAttribute->second;
      itSubscriber = subscribers->find(theSubscriber);
      if (itSubscriber != subscribers->end())
      {
        return true;
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::turnUpdatesOffForObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers)
{
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::HandleSet::const_iterator itSubscriber;
  GERTICO::HandleSetMap::iterator itAttributes;
  GERTICO::HandleSetMap::const_iterator itAttributesSubscriber;
  GERTICO::HandleSetSetMap::iterator itTurnOnUpdates;

  itTurnOnUpdates = turnOnUpdates.find(theObject);
  if (itTurnOnUpdates != turnOnUpdates.end())
  {
    for (itAttributesSubscriber = theAttributeSubscribers.begin(); itAttributesSubscriber != theAttributeSubscribers.end(); itAttributesSubscriber++)
    {
      itAttributes = itTurnOnUpdates->second.find(itAttributesSubscriber->first);
      if (itAttributes != itTurnOnUpdates->second.end())
      {
        for (itSubscriber = itAttributesSubscriber->second.begin(); itSubscriber != itAttributesSubscriber->second.end(); itSubscriber++)
        {
          itFederate = itAttributes->second.find(*itSubscriber);
          if (itFederate != itAttributes->second.end())
          {
            itAttributes->second.erase(itFederate);
          }
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::turnUpdatesOffForObjectInstanceRemote(const GeRtiFactory::GeRtiHandle &theObject, const GERTICO::HandleSetMap &theAttributeSubscribers)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = id;
                              ul = theObject;
                              sprintf(galMsg, "Federate=%lu,Object=%lu", f, ul);
                              E2(GeRti_OM_i, "turnUpdatesOffForObjectInstanceRemote", galMsg);
//                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theHandles);
                              E2(GeRti_OM_i, "turnUpdatesOffForObjectInstanceRemote", galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::AttributeSubscribersSeq attributeSubscribers;
  int maxExceptions;

//    static void mapAttributeSubscribersSeqFromHandleSetMap(GeRtiFactory::AttributeSubscribersSeq &out, GERTICO::HandleSetMap const &in);
  GERTICO::Mapper::mapAttributeSubscribersSeqFromHandleSetMap(attributeSubscribers, theAttributeSubscribers);

    for (maxExceptions = 0;;maxExceptions++)
    {
      try
      {
        fedAm->turnUpdatesOffForObjectInstance(theObject, attributeSubscribers);
        stillAlive = true;
        break;
      }
      catch(CORBA::SystemException &sysex)
      {
        if (sysex.minor() == 0)
        {
          maxExceptions += 1;
          if (maxExceptions < 2)
          {
            ACE_OS::sleep(ACE_Time_Value(0,500));
            continue;
          }
        }
        throw GeRtiFactory::RTIinternalError(L"turnUpdatesOffForObjectInstance");
      }
    }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::turnUpdatesOnForObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers)
{
  GERTICO::HandleSet::const_iterator itSubscriber;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::HandleSetMap::iterator itAttributes;
  GERTICO::HandleSetMap::const_iterator itAttributeSubscriber;
  GERTICO::HandleSetMap objectAttributeSubscribers;
  GERTICO::HandleSetSetMap::iterator itTurnOnUpdates;

  itTurnOnUpdates = turnOnUpdates.find(theObject);
  if (itTurnOnUpdates == turnOnUpdates.end())
  {
    turnOnUpdates[theObject] = objectAttributeSubscribers;
  }
    
  itTurnOnUpdates = turnOnUpdates.find(theObject);
  if (itTurnOnUpdates != turnOnUpdates.end())
  {
    for (itAttributeSubscriber = theAttributeSubscribers.begin(); itAttributeSubscriber != theAttributeSubscribers.end(); itAttributeSubscriber++)
    {
      itAttributes = itTurnOnUpdates->second.find(itAttributeSubscriber->first);
      if (itAttributes != itTurnOnUpdates->second.end())
      {
        for (itSubscriber = itAttributeSubscriber->second.begin(); itSubscriber != itAttributeSubscriber->second.end(); itSubscriber++)
        {
          itFederate = itAttributes->second.find(*itSubscriber);
          if (itFederate == itAttributes->second.end())
          {
            itAttributes->second.insert(*itSubscriber);
          }
        }
      }
      else
      {
        itTurnOnUpdates->second[itAttributeSubscriber->first] = itAttributeSubscriber->second;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::turnUpdatesOnForObjectInstanceRemote(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = id;
                              ul = theObject;
                              sprintf(galMsg, "Federate=%lu,Object=%lu", f, ul);
                              E2(GeRti_OM_i, "turnUpdatesOnForObjectInstanceRemote", galMsg);
//                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theHandles);
                              E2(GeRti_OM_i, "turnUpdatesOnForObjectInstanceRemote", galMsg);
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::AttributeSubscribersSeq attributeSubscribers;
  int maxExceptions;

  GERTICO::Mapper::mapAttributeSubscribersSeqFromHandleSetMap(attributeSubscribers, theAttributeSubscribers);

    for (maxExceptions = 0;;maxExceptions++)
    {
      try
      {
        fedAm->turnUpdatesOnForObjectInstance(theObject, attributeSubscribers);
        stillAlive = true;
        break;
      }
      catch(CORBA::SystemException &sysex)
      {
        if (sysex.minor() == 0)
        {
          maxExceptions += 1;
          if (maxExceptions < 2)
          {
            ACE_OS::sleep(ACE_Time_Value(0,500));
            continue;
          }
        }
        throw GeRtiFactory::RTIinternalError(L"turnUpdatesOnForObjectInstance");
      }
    }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Federate::knowObject (const GeRtiFactory::GeRtiHandle &obj)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_d)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = id;
                              ul = obj;
                              sprintf(galMsg,"Federate=%lu,Object=%lu", f, ul);
                              E2(GeRti_OM_d, "knowObject", galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::ObjectKnownMap::iterator itOK;

  itOK = knownObjects.find (obj);
  if (itOK != knownObjects.end ())
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OM_d, "knowObject", "Known");
                           #endif   // inserted by Gal converter
    return true;
  }
                           {   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_OM_d, "knowObject", "NotKnown");
                           #endif   // inserted by Gal converter
  return false;
                           }   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::loadRegion(const GeRtiFactory::GeRtiHandle &theSpace, const GeRtiFactory::GeRtiHandle &theRegion, GeRtiFactory::Extents &theExtents)
{
  try
  {
    geRtiRestoreVar->loadRegion(theSpace, theRegion, theExtents);
  }
  catch(...)
  {
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::unassociateAttributeRegionForUpdates(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute, const GeRtiFactory::GeRtiHandle &theRegion)
{
  GERTICO::HandleSet *regionsPtr;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap::iterator itAttribute;
  GERTICO::HandleSetMap::iterator itAttributeRegions;
  GERTICO::HandleSetMap::iterator itTheAttribute;
  GERTICO::HandleSetSetMap::iterator itObjectAttributesRegions;

  itObjectAttributesRegions = objectAttributesRegions.find(theObject);
  if (itObjectAttributesRegions != objectAttributesRegions.end())
  {
    GERTICO::HandleSetMap *attributeRegionsPtr;
    attributeRegionsPtr = &itObjectAttributesRegions->second;

    itAttribute = attributeRegionsPtr->find(theAttribute);
    if (itAttribute != attributeRegionsPtr->end())
    {
      regionsPtr = &itAttribute->second;
      itRegion = regionsPtr->find(theRegion);
      if (itRegion != regionsPtr->end())
      {
        regionsPtr->erase(itRegion);
      }
    }
    for (itAttribute = attributeRegionsPtr->begin(); itAttribute != attributeRegionsPtr->end(); )
    {
      regionsPtr = &itAttribute->second;
      if (regionsPtr->size() == 0)
      {
        attributeRegionsPtr->erase(itAttribute);
        itAttribute = attributeRegionsPtr->begin();
      }
      else
      {
        itAttribute++;
      }
    }
    if (attributeRegionsPtr->size() == 0)
    {
      objectAttributesRegions.erase(itObjectAttributesRegions);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::unassociateRegionForUpdates(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theRegion)
{
  GERTICO::HandleSet *regionsPtr;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap::iterator itAttribute;
  GERTICO::HandleSetMap::iterator itAttributesRegions;
  GERTICO::HandleSetMap::iterator itTheAttribute;
  GERTICO::HandleSetSetMap::iterator itObjectAttributesRegions;

  itObjectAttributesRegions = objectAttributesRegions.find(theObject);
  if (itObjectAttributesRegions != objectAttributesRegions.end())
  {
    GERTICO::HandleSetMap *attributesRegionsPtr;
    attributesRegionsPtr = &itObjectAttributesRegions->second;

    for (itAttribute = attributesRegionsPtr->begin(); itAttribute != attributesRegionsPtr->end(); itAttribute++)
    {
      regionsPtr = &itAttribute->second;
      itRegion = regionsPtr->find(theRegion);
      if (itRegion != regionsPtr->end())
      {
        regionsPtr->erase(itRegion);
      }
    }
    for (itAttribute = attributesRegionsPtr->begin(); itAttribute != attributesRegionsPtr->end(); )
    {
      regionsPtr = &itAttribute->second;
      if (regionsPtr->size() == 0)
      {
        attributesRegionsPtr->erase(itAttribute);
        itAttribute = attributesRegionsPtr->begin();
      }
      else
      {
        itAttribute++;
      }
    }
    if (attributesRegionsPtr->size() == 0)
    {
      objectAttributesRegions.erase(itObjectAttributesRegions);
    }
  }
  else
  {
    throw GeRtiFactory::InvalidRegionContext(L"No object/region pair");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::unassociateRegionsForUpdates(const GeRtiFactory::GeRtiHandle &theObject, const GERTICO::HandleSetMap &theAttributeRegions)
{
  GERTICO::HandleSet *regionsPtr;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap regionAttributes;
  GERTICO::HandleSetMap::iterator itAttribute;
  GERTICO::HandleSetMap::iterator itTheAttribute;
  GERTICO::HandleSetMap::iterator itRegionAttributes;
  GERTICO::HandleSetSetMap::iterator itObjectAttributesRegions;

  GERTICO::Mapper::mapHandleSetMapInvert(regionAttributes, theAttributeRegions);
  itObjectAttributesRegions = objectAttributesRegions.find(theObject);
  if (itObjectAttributesRegions != objectAttributesRegions.end())
  {
    GERTICO::HandleSetMap *attributeRegionsPtr;
    attributeRegionsPtr = &itObjectAttributesRegions->second;

    for (itAttribute = attributeRegionsPtr->begin(); itAttribute != attributeRegionsPtr->end(); itAttribute++)
    {
      regionsPtr = &itAttribute->second;
      for (itRegionAttributes = regionAttributes.begin(); itRegionAttributes != regionAttributes.end(); itRegionAttributes++)
      {
        itRegion = regionsPtr->find(itRegionAttributes->first);
        if (itRegion != regionsPtr->end())
        {
          regionsPtr->erase(itRegion);
        }
      }
    }
    for (itAttribute = attributeRegionsPtr->begin(); itAttribute != attributeRegionsPtr->end(); )
    {
      regionsPtr = &itAttribute->second;
      if (regionsPtr->size() == 0)
      {
        attributeRegionsPtr->erase(itAttribute);
        itAttribute = attributeRegionsPtr->begin();
      }
      else
      {
        itAttribute++;
      }
    }
    if (attributeRegionsPtr->size() == 0)
    {
      objectAttributesRegions.erase(itObjectAttributesRegions);
    }
  }
  else
  {
    throw GeRtiFactory::InvalidRegionContext(L"No object/region pair");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Federate::unsetFederateSave (void)
{
  saveBegun = false;
  saveComplete = false;
  saveInitiated = false;
  saveInitiatedWithTime = false;
  saveLabel = L"";
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederatesHolder::FederatesHolder(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory) : geRtiFedTimeFactory(theGeRtiFedTimeFactory)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederatesHolder::~FederatesHolder(void)
{
  GERTICO::Federate *federate;
  std::vector <Federate *>::iterator itFederate;

  pm.acquire();
  // Make sure any inactive federates are deleted.
  for (itFederate = resignedFederates.begin(); itFederate != resignedFederates.end(); itFederate = resignedFederates.begin())
  {
    federate = *itFederate;
    resignedFederates.erase(itFederate);
    delete federate;
  }
  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederatesHolder::addFederate(const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theFedType, GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GeRtiFactory::FederateAmbassador_ptr theFederateAmbassadorPtr, GeRtiFactory::GeRtiRestore_ptr theGeRtiRestorePtr, GERTICO::ClassDescrHolder &theObjectRoot)
{
  GERTICO::Federate *newFed;

  pm.acquire ();
  newFed = new GERTICO::Federate(theFederate, theFedType, theRegisteredObjectsHolder, theObjectRoot, theFederateAmbassadorPtr, theGeRtiRestorePtr, geRtiFedTimeFactory);
  federateMap[theFederate] = newFed;
  pm.release ();
}

// ---------------------------------------------------------------------------
// Only remove from the
// ---------------------------------------------------------------------------
void GERTICO::FederatesHolder::deleteFederate(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::Federate *federate;
  GERTICO::FederateMap::iterator itFederate;

  pm.acquire();
  itFederate = federateMap.find(theFederate);
  if (itFederate != federateMap.end())
  {
    federate = itFederate->second;
    federateMap.erase(itFederate);

    // Add federate to a vector to be deleted later.
    resignedFederates.push_back(federate);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Federate *GERTICO::FederatesHolder::getFederate(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::Federate *myFed;
  GERTICO::FederateMap::iterator itFed;

  pm.acquire();
  itFed = federateMap.find(theFederate);
  if (itFed != federateMap.end())
  {
    myFed = itFed->second;
    pm.release();
    return myFed;
  }
  pm.release();

  return NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederatesHolder::getFederates(GERTICO::HandleSet &theFederates)
{
  GERTICO::FederateMap::iterator itHS;

  pm.acquire();
  for (itHS = federateMap.begin(); itHS != federateMap.end(); itHS++)
  {
    theFederates.insert(itHS->first);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederatesHolder::getNewFederates(GERTICO::HandleSet &theNewFederates, GERTICO::HandleSet const &theOldFederates, GERTICO::HandleSet &theAllFederates)
{
  GERTICO::HandleSet::iterator itAll;
  GERTICO::HandleSet::const_iterator itOld;

  theNewFederates.clear();

  getFederates(theAllFederates);

  for (itAll = theAllFederates.begin(); itAll != theAllFederates.end();  itAll++)
  {
    itOld = theOldFederates.find(*itAll);
    if (itOld == theOldFederates.end())
    {
      theNewFederates.insert(*itAll);
    }
  }
}

// ---------------------------------------------------------------------------
// Slowly remove old federates - let any other processes finish their work.
// ---------------------------------------------------------------------------
void GERTICO::FederatesHolder::pruneResignedFederates(void)
{
  Federate *currFederate;
  std::vector <Federate *>::iterator itF;
  size_t ul;

  pm.acquire();
  for (itF = resignedFederates.begin(); itF != resignedFederates.end(); itF = resignedFederates.begin())
  {
    ul = resignedFederates.size();
    if (ul < 10)
    {
      break;
    }
    currFederate = *itF;
    resignedFederates.erase(itF);
    delete currFederate;
  }
  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederatesHolder::rehashFederateIds(FedTypes &theFedTypes)
{
  FedTypes::iterator itFT;
  GERTICO::Federate *currFederate;
  GERTICO::FederateMap tmpFederateMap;
  GERTICO::FederateMap::iterator itF;

  pm.acquire();
  tmpFederateMap = federateMap;
  federateMap.clear();

  for (itFT = theFedTypes.begin(); itFT != theFedTypes.end(); itFT++)
  {
    for (itF = tmpFederateMap.begin(); itF != tmpFederateMap.end(); itF++)
    {
      currFederate = itF->second;
      if (currFederate->federateType == itFT->second)
      {
        currFederate->setId(itFT->first);
        federateMap[itFT->first] = currFederate;
        tmpFederateMap.erase(itF);
        break;
      }
    }
  }
  pm.release();
}
