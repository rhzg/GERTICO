/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** ObjectManagement.cpp
**
*******************************************************************************/

#include "ObjectManagement.h"
#include "Util/ConvertTime.h"
#include "EventMarket/Jobs.h"
#include "Util/Mapper.h"

/********************************* Gal begin *********************************/

#ifdef GalDebug   // inserted by Gal converter

#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

static class Repository_l *OM=(Repository::getSingleInstance())->getRepository_l("GeRtiOM.res","GeRtiOM");

static class Event *GeRti_OM_d=OM->getRefEvent("GeRti_OM_d");
static class Event *GeRti_OM_e=OM->getRefEvent("GeRti_OM_e");
static class Event *GeRti_OM_i=OM->getRefEvent("GeRti_OM_i");
static class Event *GeRti_OM_w=OM->getRefEvent("GeRti_OM_w");

#endif   // inserted by Gal converter

/*********************************** Gal end *********************************/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectManagement::ObjectManagement(GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::FederatesHolder &theFederatesHolder, GERTICO::ObjectModel &theObjectModel, GERTICO::NextHandle &theIdHandler, GERTICO::JobHolder &theFederationJobs, ACE_Thread_Mutex &thePm, ACE_Semaphore &thePs, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory) : pm(thePm), ps(thePs), federatesHolder(theFederatesHolder), geRtiFedTimeFactory(theGeRtiFedTimeFactory), federationJobs(theFederationJobs), idHandler(theIdHandler), objectModel(theObjectModel), registeredObjectsHolder(theRegisteredObjectsHolder), runTimeObjectDB(theRunTimeObjectDB)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::ObjectManagement", "enter");
                           #endif   // inserted by Gal converter
  // Need to know privilegeToDeleteId.
  privilegeToDeleteId = runTimeObjectDB.getPrivilegeToDeleteId();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::ObjectManagement", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectManagement::~ObjectManagement(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::~ObjectManagement", "enter");
                           #endif   // inserted by Gal converter
  ObjectTimeMap::iterator itOTM;
  GERTICO::GeRtiFedTime *currFedTime;

  for (itOTM = objectTimeMap.begin(); itOTM != objectTimeMap.end(); itOTM = objectTimeMap.begin())
  {
    currFedTime = itOTM->second;
    objectTimeMap.erase(itOTM);
    delete currFedTime;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::~ObjectManagement", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::addDefaultRegionAttributes(GERTICO::Federate &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap)
{
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet::iterator itAttributes;
  GERTICO::HandleSetMap::const_iterator itAttRegMap;

  runTimeObjectDB.getPublishedAttributes(theFederate.getId(), theClass, attributes);
  for (itAttributes = attributes.begin(); itAttributes != attributes.end(); itAttributes++)
  {
    itAttRegMap = theAttRegMap.find(*itAttributes);
    if (itAttRegMap == theAttRegMap.end())
    {
      GERTICO::HandleSet tmpRegions;
      tmpRegions.insert(0);
      theAttRegMap[*itAttributes] = tmpRegions;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::addDiscoverObject(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSet &theAttributes)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::addDiscoverObject", "enter");
                           #endif   // inserted by Gal converter
  GERTICO::DiscoverObjectJob *newDiscoverObject;
  GERTICO::Federate *tmpFederate;
  GERTICO::RegisteredObject *registeredObject;
  std::wstring oName;

  registeredObject = registeredObjectsHolder.getObject(theObject);
  registeredObject->getName(oName);
  newDiscoverObject = new GERTICO::DiscoverObjectJob(theClass, theFederate, theObject, federatesHolder, oName.c_str());
  federationJobs.add(newDiscoverObject);
  tmpFederate = federatesHolder.getFederate(theFederate);
  if (tmpFederate)
  {
    tmpFederate->addKnownObject(theObject, theClass, theAttributes);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::addDiscoverObject", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::addObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObjectId, std::wstring const &theObjectName)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::addObjectInstance", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *federate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet attributePub;
  GERTICO::HandleSet feds;
  GERTICO::HandleSet::iterator itFed;
  GERTICO::RegisteredObject *registeredObject;
  bool found;
  unsigned long testClass;

  classDescr = runTimeObjectDB.getObjectClassDescr(theClass);
  if (classDescr == NULL)
  {
    throw GeRtiFactory::ObjectClassNotDefined(wChar);
  }

  // Check if class is published.
  GERTICO::PublishedClass *publishedClass = runTimeObjectDB.getPublishedClass(theClass);
  if (publishedClass == NULL)
  {
    throw GeRtiFactory::ObjectClassNotPublished(L"addObjectInstance");
  }

  pm.acquire();

  // Names are unique, duplicates are not allowed.
  registeredObject = registeredObjectsHolder.getObjectByName(theObjectName);
  if (registeredObject)
  {
    pm.release();
    throw GeRtiFactory::ObjectAlreadyRegistered(wChar);
  }

  // Register object.
  try
  {
    // Get set of attributes that are published.
    runTimeObjectDB.getPublishedAttributes(theFederate, classDescr->getId(), attributePub);

    registeredObjectsHolder.registerObjectInstance(theFederate, *classDescr, theObjectId, theObjectName, attributePub);
    registeredObject = registeredObjectsHolder.getObject(theObjectId);
    registeredObject->addAttributesDefaultRegion(theFederate, attributePub);

    runTimeObjectDB.registerObjectInstance(*classDescr, theObjectId);
  }
  catch(...)
  {
    pm.release();
    throw;
  }

  // Check if there are subscribers for the owned attributes.
  runTimeObjectDB.getOwnedObjectAttributes(theObjectId, theFederate, attributes, false);
  if (theFederate != 1)
  {
    federate = federatesHolder.getFederate(theFederate);
    if (federate)
    {
      federate->addKnownObject(theObjectId, theClass, attributes);
    }
  }
  found = false;
  federatesHolder.getFederates(feds);
  for (itFed = feds.begin(); itFed != feds.end(); itFed++)
  {
    federate = federatesHolder.getFederate(*itFed);
    if (federate == NULL)
    {
      continue;
    }
    if (federate->getId() != theFederate)
    {
      testClass = theClass;
      for (;;)
      {
        if (federate->isSubscribedToObjectClass(testClass))
        {
          if (runTimeObjectDB.subscribedToAttributeActive(federate->getId(), testClass, attributes))
          {
            found = true;
            break;
          }

          break;
        }

        // Get parent class.
        if (objectModel.getParentId(testClass, testClass) == false)
        {
          break;
        }
      }

      if (found)
      {
        break;
      }
    }
  }

  registeredObject = registeredObjectsHolder.getObject(theObjectId);
  for (itFed = feds.begin(); itFed != feds.end(); itFed++)
  {
    federate = federatesHolder.getFederate(*itFed);
    if (federate == NULL)
    {
      continue;
    }

    if (*itFed != theFederate)
    {
      doAnnounceObject(theFederate, *federate, theClass, *registeredObject, theObjectName, attributes);
    }
    doDiscover(theFederate, *federate, theClass, *registeredObject, theObjectName, attributes);
  }

  // Got a subscriber, turn on.
  if (found)
  {
    pm.release();
    doTurnOnForObjectInstance(theObjectId, theFederate, attributes, true);
    pm.acquire();
  }

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::addObjectInstance", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::addObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObject, std::wstring const &theObjectName, GERTICO::HandleSetMap &theAttRegMap)
{
  CORBA::WChar *wChar = L"addObjectInstance";
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *federate;
  GERTICO::Federate *otherFederate;
  GERTICO::HandleMap attributeRegions;
  GERTICO::HandleSet atts;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet attributePub;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFed;
  GERTICO::HandleSet *regionsPtr;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap::iterator itAttRegMap;
  GERTICO::RegisteredObject *registeredObject;
  bool found;
  std::wstring s(theObjectName);
  unsigned long testClass;

  classDescr = runTimeObjectDB.getObjectClassDescr(theClass);
  if (classDescr == NULL)
  {
    throw GeRtiFactory::ObjectClassNotDefined(wChar);
  }

  pm.acquire();

  // Check internal federate management.
  federate = federatesHolder.getFederate(theFederate);
  if (federate == NULL)
  {
    pm.release();
    throw GeRtiFactory::RTIinternalError(L"federate not found");
  }

  // Check supplied attributes for validity.
  try
  {
    federate->checkPublishedAttributes(theClass, theAttRegMap);
  }
  catch(...)
  {
    pm.release();
    throw;
  }

  // Check if attribute space is the same as region space.
  if (runTimeObjectDB.checkAttRegSpace(theClass, theAttRegMap) == false)
  {
    pm.release();
    throw GeRtiFactory::InvalidRegionContext(wChar);
  }

  addDefaultRegionAttributes(*federate, theClass, theAttRegMap);

  // Names are unique, duplicates are not allowed.
  registeredObject = getObjectByName(s);
  if (registeredObject)
  {
    pm.release();
    throw GeRtiFactory::ObjectAlreadyRegistered(wChar);
  }

  // Register object.
  try
  {
    // Get set of attributes that are published.
    runTimeObjectDB.getPublishedAttributes(theFederate, classDescr->getId(), attributePub);

    registeredObjectsHolder.registerObjectInstance(theFederate, *classDescr, theObject, theObjectName, attributePub);
    registeredObject = registeredObjectsHolder.getObject(theObject);
    registeredObject->addAttributesRegions(theFederate, theAttRegMap);

    runTimeObjectDB.registerObjectInstance(*classDescr, theObject);
  }
  catch(...)
  {
    pm.release();
    throw;
  }

  // Check if there are subscribers for the owned attributes.
  runTimeObjectDB.getOwnedObjectAttributes(theObject, theFederate, attributes, true);

  federate->addKnownObject(theObject, theClass, attributes);
  for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
  {
    regionsPtr = &itAttRegMap->second;
    for (itRegion = regionsPtr->begin(); itRegion != regionsPtr->end(); itRegion++)
    {
      if (*itRegion == 0)
      {
        continue;
      }
      atts.clear();
      atts.insert(itAttRegMap->first);
      federate->associateRegionForUpdates(theObject, theAttRegMap);
    }
  }

  // Get object.
  try
  {
    registeredObject = getObject(theObject);
  }
  catch(...)
  {
    pm.release();
    throw GeRtiFactory::RTIinternalError(wChar);
  }
  found = false;
  federatesHolder.getFederates(federates);
  for (itFed = federates.begin(); itFed != federates.end(); itFed++)
  {
    otherFederate = federatesHolder.getFederate(*itFed);
    if (otherFederate->getId() != theFederate)
    {
      testClass = theClass;
      for (;;)
      {
        otherFederate->getSubscribedRegions(testClass, regions);
        if (subscribedToAttributeWithRegion(theFederate, otherFederate->getId(), *registeredObject, testClass, attributes, regions))
        {
          found = true;
          break;
        }

        // Get parent class.
        if (objectModel.getParentId(testClass, testClass) == false)
        {
          break;
        }
      }

      if (found)
      {
        break;
      }
    }
  }

  // Got a subscriber, turn on.
  if (found)
  {
    for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
    {
      attributes.insert(itAttRegMap->first);
    }
    pm.release();
    doTurnOnForObjectInstance(theObject, theFederate, attributes, true);
    pm.acquire();
  }

  doDiscoverObject(theFederate, theObject);
  doScopeRegister(theFederate, *registeredObject);
  runTimeObjectDB.addObjAttRegions(theFederate, theObject, theAttRegMap);

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::changeAttributeOrderType(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &theOrderType)
{
  CORBA::ULong i;
  CORBA::ULong length;
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *federate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet::iterator itA;
  GERTICO::Item *item;
  GERTICO::RegisteredObject *currObject;
  GeRtiFactory::GeRtiHandle objClass;

  if (theOrderType != 0 && theOrderType != 1)
  {
    throw GeRtiFactory::InvalidOrderingHandle(wChar);
  }

  pm.acquire();

  try
  {
    currObject = registeredObjectsHolder.getObject(theObject);
  }
  catch(...)
  {
    pm.release();
    throw;
  }
  objClass = currObject->getClassId();
  classDescr = runTimeObjectDB.getObjectClassDescr(objClass);

  length = theAttributes.length();
  for (i = 0; i < length; i++)
  {
    item = classDescr->getClassItem(theAttributes[i]);
    if (item == NULL)
    {
      pm.release();
      throw GeRtiFactory::AttributeNotDefined(wChar);
    }
  }

  try
  {
    runTimeObjectDB.getOwnedObjectAttributes(theObject, theFederate, attributes, true);
  }
  catch(...)
  {
    pm.release();
  }

  // Find the desired federate.
  federate = federatesHolder.getFederate(theFederate);
  if (federate)
  {
    federate->setAlive();
    for (i = 0; i < length; i++)
    {
      itA = attributes.find(theAttributes[i]);
      if (itA == attributes.end())
      {
        pm.release();
        throw GeRtiFactory::AttributeNotOwned(wChar);
      }
    }
    currObject->changeAttributeOrderType(theAttributes, theOrderType);
  }

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::changeAttributeTransportationType(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::GeRtiHandle const &theTransportationType)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::changeAttributeTransportationType", "enter");
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  CORBA::ULong length;
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *federate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet::iterator itA;
  GERTICO::Item *item;
  GERTICO::RegisteredObject *currObject;
  GeRtiFactory::GeRtiHandle knownObjectClass;

  pm.acquire();

  try
  {
    runTimeObjectDB.getOwnedObjectAttributes(theObject, theFederate, attributes, true);
  }
  catch(...)
  {
    pm.release();
    throw;
  }

  length = theAttributes.length();

  // Find the desired federate.
  federate = federatesHolder.getFederate(theFederate);
  if (federate)
  {
    federate->setAlive();
    try
    {
      knownObjectClass = federate->getObjectClass(theObject);
    }
    catch(...)
    {
      pm.release();
      throw GeRtiFactory::ObjectNotKnown(wChar);
    }
    classDescr = runTimeObjectDB.getObjectClassDescr(knownObjectClass);
    if (classDescr == NULL)
    {
      pm.release();
      throw GeRtiFactory::RTIinternalError(wChar);
    }
    for (i = 0; i < length; i++)
    {
      item = classDescr->getClassItem(theAttributes[i]);
      if (item == NULL)
      {
        pm.release();
        throw GeRtiFactory::AttributeNotDefined(wChar);
      }
      itA = attributes.find(theAttributes[i]);
      if (itA == attributes.end())
      {
        pm.release();
        throw GeRtiFactory::AttributeNotOwned(wChar);
      }
    }
    currObject = registeredObjectsHolder.getObject(theObject);
    currObject->changeAttributeTransportationType(theAttributes, theTransportationType);
  }

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::changeAttributeTransportationType", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ObjectManagement::checkAnySubscriber(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theRegisteredObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
  GERTICO::AttributeInfo *ownedAttributeInfoPtr;
  GERTICO::Federate *subscriberFederatePtr;
  GERTICO::HandleSet subscriberFederates;
  GERTICO::HandleSet subscriberRegions;
  GERTICO::HandleSet publisherRegions;
  GERTICO::HandleSet::iterator itPublisherRegion;
  GERTICO::HandleSet::iterator itSubscriberFederate;
  GERTICO::HandleSet::iterator itSubscriberRegion;
  GERTICO::Region *publisherRegionPtr;
  GeRtiFactory::GeRtiHandle subscriberKnownClass;

  try
  {
    ownedAttributeInfoPtr = theRegisteredObject.getAttribute(theAttribute);
  }
  catch(...)
  {
    return false;
  }

  federatesHolder.getFederates(subscriberFederates);

  ownedAttributeInfoPtr->getFedRegions(theFederate, publisherRegions);
  for (itPublisherRegion = publisherRegions.begin(); itPublisherRegion != publisherRegions.end(); itPublisherRegion++)
  {
    publisherRegionPtr = NULL;
    if (*itPublisherRegion)
    {
      publisherRegionPtr = runTimeObjectDB.getRegion(*itPublisherRegion);

      if (publisherRegionPtr == NULL)
      {
        continue;
      }
    }

    // Loop through other federates.
    for (itSubscriberFederate = subscriberFederates.begin(); itSubscriberFederate != subscriberFederates.end(); itSubscriberFederate++)
    {
      // Do not take the calling federate
      if (*itSubscriberFederate == theFederate)
      {
        continue;
      }

      subscriberFederatePtr = federatesHolder.getFederate(*itSubscriberFederate);
      if (subscriberFederatePtr == NULL)
      {
        continue;
      }

      try
      {
        subscriberKnownClass = subscriberFederatePtr->getObjectClass(theRegisteredObject.getId());
        subscriberFederatePtr->getSubscribedAttributeRegions(subscriberKnownClass, theAttribute, subscriberRegions, false);
        for (itSubscriberRegion = subscriberRegions.begin(); itSubscriberRegion != subscriberRegions.end(); itSubscriberRegion++)
        {
          if (publisherRegionPtr)
          {
            if (publisherRegionPtr->gotIntersection(*itSubscriberRegion))
            {
              return true;
            }
          }
          else
          {
            return true;
          }
        }
      }
      catch(...)
      {
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::checkDivesting(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::RegisteredObject *registeredObject = getObject(theObject);

  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    attributeInfo = registeredObject->getAttribute(theAttributes[i]);
    if (attributeInfo->getStatus() != divesting && attributeInfo->getStatus() != divestConfirm)
    {
      throw GeRtiFactory::AttributeDivestitureWasNotRequested(L"checkDivesting");
    }
  }
}

// ---------------------------------------------------------------------------
// Check if a particular federate was acquiring the attributes
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::checkFedAcquiring(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::WChar *wChar = L"";
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::RegisteredObject *registeredObject = getObject(theObject);

  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    attributeInfo = registeredObject->getAttribute(theAttributes[i]);
    if (!attributeInfo->testIfFederateIsAcquiring(theFederate))
    {
      throw GeRtiFactory::AttributeAcquisitionWasNotRequested(wChar);
    }
    if ((attributeInfo->getStatus() != acquiring) && (attributeInfo->getStatus() != acquired))
    {
      throw GeRtiFactory::AttributeAcquisitionWasNotRequested(wChar);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ObjectManagement::checkFedSubscriber(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theRegisteredObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
  GERTICO::AttributeInfo *ownedAttributeInfoPtr;
  GERTICO::Federate *subscriberFederatePtr;
  GERTICO::HandleSet subscriberRegions;
  GERTICO::HandleSet publisherRegions;
  GERTICO::HandleSet::iterator itPublisherRegion;
  GERTICO::HandleSet::iterator itSubscriberRegion;
  GERTICO::Region *publisherRegionPtr;
  GeRtiFactory::GeRtiHandle subscriberKnownClass;

  try
  {
    ownedAttributeInfoPtr = theRegisteredObject.getAttribute(theAttribute);
  }
  catch(...)
  {
    return false;
  }

  ownedAttributeInfoPtr->getFedRegions(theFederate, publisherRegions);
  for (itPublisherRegion = publisherRegions.begin(); itPublisherRegion != publisherRegions.end(); itPublisherRegion++)
  {
    publisherRegionPtr = NULL;
    if (*itPublisherRegion)
    {
      publisherRegionPtr = runTimeObjectDB.getRegion(*itPublisherRegion);

      if (publisherRegionPtr == NULL)
      {
        continue;
      }
    }

      subscriberFederatePtr = federatesHolder.getFederate(theFederate);
      if (subscriberFederatePtr == NULL)
      {
        continue;
      }

      try
      {
        subscriberKnownClass = subscriberFederatePtr->getObjectClass(theRegisteredObject.getId());
        subscriberFederatePtr->getSubscribedAttributeRegions(subscriberKnownClass, theAttribute, subscriberRegions, false);
        for (itSubscriberRegion = subscriberRegions.begin(); itSubscriberRegion != subscriberRegions.end(); itSubscriberRegion++)
        {
          if (publisherRegionPtr)
          {
            if (publisherRegionPtr->gotIntersection(*itSubscriberRegion))
            {
              return true;
            }
          }
          else
          {
            return true;
          }
        }
      }
      catch(...)
      {
      }
  }

  return false;
}

// ---------------------------------------------------------------------------
// Assume checkNotOwned called first.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::checkNotAcquiring(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
  GERTICO::RegisteredObject *registeredObject = getObject(theObject);

  // check if federate is not acquiring attributes
  for (unsigned int i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo *info; 
    try
    {
      info = registeredObject->getAttribute(theAttributes[i]);
	    if ((info->getStatus() == acquired) || (info->getStatus() == acquiring))
      {
	      if (info->testIfFederateIsAcquiring(theFederate))
        {
          throw GeRtiFactory::AttributeAlreadyBeingAcquired(L"checkNotAcquiring");
        }
      }
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      // Check if the attribute simply not managed in the registered object.
      checkUnmanagedAttribute(*registeredObject, theAttributes[i]);
    }
  }
}

// ---------------------------------------------------------------------------
// Assume checkOwned called first.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::checkNotDivesting(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
  GERTICO::RegisteredObject *registeredObject = getObject(theObject);

  // check if divesting attributes are not being divested
  for (unsigned int i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo *info;
    try
    {
      info = registeredObject->getAttribute(theAttributes[i]);
	    if (info->getStatus() == divesting || info->getStatus() == divestConfirm)
      {
	      throw GeRtiFactory::AttributeAlreadyBeingDivested(L"checkNotDivesting");
      }
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      checkUnmanagedAttribute(*registeredObject, theAttributes[i]);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::checkNotOwned(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
  GERTICO::RegisteredObject *registeredObject = getObject(theObject);

  // check if attributes are not owned by federate
  for (unsigned int i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo *info;
    try
    {
      info = registeredObject->getAttribute(theAttributes[i]);
      if (info->getFederate() == theFederate)
      {
        throw GeRtiFactory::FederateOwnsAttributes(L"checkNotOwned");
      }
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      // Check if the attribute simply not managed in the registered object.
      checkUnmanagedAttribute(*registeredObject, theAttributes[i]);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::checkOwned(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::RegisteredObject *registeredObject = getObject(theObject);

  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    try
    {
      attributeInfo = registeredObject->getAttribute(theAttributes[i]);
      if (theFederate != attributeInfo->getFederate())
      {
        throw GeRtiFactory::AttributeNotOwned(L"checkOwnership");
      }
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      // Attribute may or may not be in the class since non-published attributes
      // are not managed.
      checkUnmanagedAttribute(*registeredObject, theAttributes[i]);
      throw GeRtiFactory::AttributeNotOwned(L"checkOwnership");
    }
  }
}

// ---------------------------------------------------------------------------
// Return only in the case the attribute is in the class
// else throws exceptions.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::checkUnmanagedAttribute(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
  GERTICO::RegisteredObject *registeredObject;

  // Get the object data.
  registeredObject = getObject(theObject);
  checkUnmanagedAttribute(*registeredObject, theAttribute);
}

// ---------------------------------------------------------------------------
// Return only in the case the attribute is in the class
// else throws exceptions.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::checkUnmanagedAttribute(GERTICO::RegisteredObject const &theRegisteredObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet::iterator itHS;
  GeRtiFactory::GeRtiHandle classId;

  try
  {
    // Get the "real" class id.
    classId = theRegisteredObject.getClassId();
    // Get the class data.
    classDescr = runTimeObjectDB.getObjectClassDescr(classId);
    // Get all attributes for the set including inherited attributes.
    classDescr->getAttributes(attributes);
    // Get if the attribute belongs to this class.
    itHS = attributes.find(theAttribute);
    if (itHS != attributes.end())
    {
      // Attribute belongs to the set, but is not managed thus it is unowned.
      return;
    }
    else
    {
      throw GeRtiFactory::AttributeNotDefined(wChar);
    }
  }
  catch(GeRtiFactory::ObjectNotKnown &)
  {
    throw GeRtiFactory::ObjectNotKnown(wChar);
  }
}

//-------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ObjectManagement::checkUnowned(GERTICO::RegisteredObject &theRegisteredObject, GERTICO::HandleSet const &theAttSet)
{
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::HandleSet::const_iterator itAttSet;

  for (itAttSet = theAttSet.begin(); itAttSet != theAttSet.end(); itAttSet++)
  {
    try
    {
      attributeInfo = theRegisteredObject.getAttribute(*itAttSet);
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      continue;
    }
    if (attributeInfo->ownedByFederate(0))
    {
      continue;
    }

    return false;
  }

  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::deleteObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theTag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::deleteObjectInstance", "enter");
                           #endif   // inserted by Gal converter
  GERTICO::Federate *federate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::RemoveObject *newRemoveObject;

  pm.acquire();

  try
  {
    runTimeObjectDB.deleteObjectInstance(theObject, theFederate);
  }
  catch(GeRtiFactory::DeletePrivilegeNotHeld &)
  {
    pm.release();
    throw;
  }

  // Notify the other federates.
  federatesHolder.getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    federate = federatesHolder.getFederate(*itFederate);
    if (federate == NULL)
    {
      continue;
    }
    if (*itFederate == theFederate)
    {
      federate->delObject(theObject);
      continue;
    }
    if (federate->knowObject(theObject))
    {
      newRemoveObject = new GERTICO::RemoveObject(theObject, *itFederate, federatesHolder, theTag);
      federationJobs.add(newRemoveObject);
      federate->delObject(theObject);
      federate->setAlive();
    }
  }

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::deleteObjectInstance", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::deleteObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Time const &theTime, GeRtiFactory::UserSuppliedTag const &theTag, GeRtiFactory::GeRtiHandle const &theSerialNumber)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::deleteObjectInstanceWithTime", "enter");
                           #endif   // inserted by Gal converter
  AttributeInfo *attributeInfo;
  GERTICO::Federate *federate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  GeRtiFactory::GeRtiHandle orderType;
  GeRtiFactory::ERHandle erHandle;
  RegisteredObject *object;
  GERTICO::RemoveObject *newRemoveObject;
  std::auto_ptr<GERTICO::GeRtiFedTime> tmpFedTime(geRtiFedTimeFactory.makeZero());

  // Test if time stamp desired.
  try
  {
    object = registeredObjectsHolder.getObject(theObject);
    attributeInfo = object->getAttribute(privilegeToDeleteId);
    orderType = attributeInfo->getOrderType();
    if (orderType == 0)
    {
      deleteObjectInstance(theFederate, theObject, theTag);
      return;
    }
  }
  catch(...)
  {
    throw;
  }

  pm.acquire();

  // DO NOT DELETE IMMEDIATELY!!
  // Set up map of objects and times.
  GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, tmpFedTime, theTime);
  objectTimeMap[theObject] = tmpFedTime.release();

  // Notify the other federates.
  federatesHolder.getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    federate = federatesHolder.getFederate(*itFederate);
    if (*itFederate == theFederate)
    {
      continue;
    }

    if (federate == NULL)
    {
      continue;
    }

    // Send to all other federates!
    erHandle.theSerialNumber = theSerialNumber;
    erHandle.sendingFederate = theFederate;
    newRemoveObject = new GERTICO::RemoveObject(theObject, *itFederate, federatesHolder, theTime, theTag, erHandle);
    federationJobs.add(newRemoveObject);
    federate->delObject(theObject);
    federate->setAlive();
  }

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::deleteObjectInstanceWithTime", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doAnnounceObject(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::Federate &theCurrFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::RegisteredObject &theObject, std::wstring const &sName, GERTICO::HandleSet &theAttributes)
{
  GERTICO::AnnounceObjectJob *newAnnounceObject;

  newAnnounceObject = new GERTICO::AnnounceObjectJob(theClass, theCurrFederate.getId(), theObject.getId(), federatesHolder, sName, theAttributes);
  federationJobs.add(newAnnounceObject);
}

// ---------------------------------------------------------------------------
// For each object in the given class, send a discover object request to
// each federate ambassador except to the owner federate ambassador.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doDiscover(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::Federate &theCurrFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::RegisteredObject &theObject, std::wstring const &sName, GERTICO::HandleSet &theAttributes)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::doDiscover", "enter");
                           #endif   // inserted by Gal converter
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::DiscoverObjectJob *newDiscoverObject;
  GERTICO::HandleSet items;
  GERTICO::HandleSet subscribedItems;
  GERTICO::HandleSet::iterator itA;
  GERTICO::HandleSet::iterator itSI;
  bool gotAttribute = false;
  unsigned long testClass;

  // Do not take the owner.
  if (theCurrFederate.getId() == theFederate)
  {
    return;
  }

  // Federate already knows the object.
  if (theCurrFederate.knowObject(theObject.getId()))
  {
    return;
  }

  // Check if some federate owns any attributes, else do not discover.
  for(itA = theAttributes.begin(); itA != theAttributes.end(); itA++)
  {
    if (*itA == privilegeToDeleteId)
    {
      continue;
    }
    try
    {
      attributeInfo = theObject.getAttribute(*itA);
      if (attributeInfo->getStatus() != unowned)
      {
        gotAttribute = true;
      }
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
    }
  }

  // No federate owns any of the attributes.
  if (gotAttribute == false)
  {
    return;
  }

  testClass = theClass;
  for (;;)
  {
    // Only check the first class found.
    if (theCurrFederate.isSubscribedToObjectClass(testClass))
    {
      // This is a check if the federate subscribes to any class attribute.
      if (runTimeObjectDB.subscribedToAttribute(theCurrFederate.getId(), testClass, theAttributes))
      {
        newDiscoverObject = new GERTICO::DiscoverObjectJob(testClass, theCurrFederate.getId(), theObject.getId(), federatesHolder, sName);
        federationJobs.add(newDiscoverObject);
        theCurrFederate.addKnownObject(theObject.getId(), testClass, theAttributes);
        break;
      }
    }

    // Get parent class.
    if (objectModel.getParentId(testClass, testClass) == false)
    {
      break;
    }
  }

  // Do scoping.
  theCurrFederate.getSubscribedAttributes(testClass, subscribedItems);
  for (itSI = subscribedItems.begin(); itSI != subscribedItems.end(); itSI++)
  {
    itA = theAttributes.find(*itSI);
    if (itA != theAttributes.end())
    {
      items.insert(*itSI);
    }
  }
  if (items.size())
  {
    GERTICO::IntoScopeJob *newIntoScopeJob;
    newIntoScopeJob = new IntoScopeJob(theCurrFederate.getId(), theObject.getId(), items, federatesHolder);
    federationJobs.add(newIntoScopeJob);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::doDiscover", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// For each object in the given class, send a discover object request to
// each federate ambassador except to the calling federate ambassador.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doDiscoverObject(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject)
{
  GERTICO::AttributeInfo *ownedAttributeInfo;
  GERTICO::DiscoverObjectJob *newDiscoverObject;
  GERTICO::Federate *federate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet ownedAttributes;
  GERTICO::HandleSet ownedRegions;
  GERTICO::HandleSet subscribedRegions;
  GERTICO::HandleSet ownerFederates;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::HandleSet::iterator itOwnedAttribute;
  GERTICO::HandleSet::iterator itOwnerFederate;
  GERTICO::HandleSet::iterator itOwnedRegion;
  GERTICO::HandleSet::iterator itSubscribedRegion;
  GERTICO::Region *ownedRegionPtr;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle objectClass;
  bool found = false;
  std::wstring objectName;
  unsigned long testClass;
  unsigned long ul;

  // Get object attributes.
  registeredObject = registeredObjectsHolder.getObject(theObject);
  if (registeredObject)
  {
    objectClass = registeredObject->getClassId();
    registeredObject->getName(objectName);
  }

  // Process list of owner federates.
  registeredObject->getOwners(ownerFederates);

  federatesHolder.getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
ul = *itFederate;
    // Do not take this federate.
    if (*itFederate == theFederate)
    {
      continue;
    }

    federate = federatesHolder.getFederate(*itFederate);
    if (federate == NULL)
    {
      continue;
    }

    // Federate already knows the object.
    if (federate->knowObject(theObject))
    {
      continue;
    }

    // Check subscribers.
    found = false;
    testClass = objectClass;
    for (;;)
    {
      for (itOwnerFederate = ownerFederates.begin(); itOwnerFederate != ownerFederates.end(); itOwnerFederate++)
      {
ul = *itOwnerFederate;
        if (*itOwnerFederate == *itFederate)
        {
          continue;
        }
        registeredObject->getOwnedAttributes(*itOwnerFederate, privilegeToDeleteId, ownedAttributes, false);
        for (itOwnedAttribute = ownedAttributes.begin(); itOwnedAttribute != ownedAttributes.end(); itOwnedAttribute++)
        {
ul = *itOwnedAttribute;
          ownedAttributeInfo = registeredObject->getAttribute(*itOwnedAttribute);
          try
          {
            ownedAttributeInfo->getFedRegions(*itOwnerFederate, ownedRegions);
          }
          catch(...)
          {
            continue;
          }

          for (itOwnedRegion = ownedRegions.begin(); itOwnedRegion != ownedRegions.end(); itOwnedRegion++)
          {
ul = *itOwnedRegion;
            if (*itOwnedRegion == 0)
            {
              if (federate->isSubscribedToObjectClass(testClass))
              {
                found = true;
                break;
              }
            }
            else
            {
              ownedRegionPtr = runTimeObjectDB.getRegion(*itOwnedRegion);

              // This is a check if the federate subscribes to any class attribute.
              federate->getSubscribedRegions(testClass, subscribedRegions);
              for (itSubscribedRegion = subscribedRegions.begin(); itSubscribedRegion != subscribedRegions.end(); itSubscribedRegion++)
              {
                if (ownedRegionPtr->gotIntersection(*itSubscribedRegion))
                {
                  found = true;
                  break;
                }
              }
            }
          }
          if (found)
          {
            break;
          }
        }
        if (found)
        {
          break;
        }
      }

      if (found)
      {
        break;
      }

      // Get parent class.
      if (objectModel.getParentId(testClass, testClass) == false)
      {
        break;
      }
    }

    if (found)
    {
      newDiscoverObject = new GERTICO::DiscoverObjectJob(testClass, federate->getId(), theObject, federatesHolder, objectName);
      federationJobs.add(newDiscoverObject);
      federate->addKnownObject(theObject, testClass, attributes);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doOwnershipAcquisitionNotification(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theObject, GERTICO::HandleSet &theAttributes, bool const &theAsynchronous)
{
  GERTICO::Federate *federate;
  GERTICO::HandleSet feds;
  GERTICO::HandleSet::iterator itFed;
  GeRtiFactory::GeRtiHandle objectClass;
  std::wstring objectName;

  doTurnOnForObjectInstance(theObject.getId(), theFederate, theAttributes, false);

  objectClass = theObject.getClassId();
  theObject.getName(objectName);
  federatesHolder.getFederates(feds);
  for (itFed = feds.begin(); itFed != feds.end(); itFed++)
  {
    federate = federatesHolder.getFederate(*itFed);
    if (federate == NULL)
    {
      continue;
    }

    doDiscover(theFederate, *federate, objectClass, theObject, objectName, theAttributes);
  }

  doScopeAcquisitionNotification(theObject, theAttributes, false);

  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScope(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClassId, GERTICO::HandleSet const &theAttributeList)
{
  GERTICO::Federate *federate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet feds;
  GERTICO::HandleSet items;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::const_iterator itAttributeIn;
  GERTICO::HandleSet::iterator itObject;
  GERTICO::RegisteredObject *currObject;

  // Get the federate attributes for this fed.
  federate = federatesHolder.getFederate(theFederate);
  if (federate == NULL)
  {
    return;
  }

  // Get all objects for this class.
  federate->getKnownObjects(theClassId, objects);
  for (itObject = objects.begin(); itObject != objects.end(); itObject++)
  {
    items.clear();

    // Get the object
    currObject = registeredObjectsHolder.getObject(*itObject);

    // Do not process unowned objects testcase 6113
    if (checkUnowned(*currObject, theAttributeList))
    {
      continue;
    }

    // Use only if some attribute(s) found.
    currObject->getUnownedObjectAttributes(theFederate, attributes);
    if (attributes.size() == 1)
    {
      GERTICO::HandleSet::iterator itHS;
      bool gotPrivilegeToDeleteId = false;

      for (itHS = attributes.begin(); itHS != attributes.end(); itHS++)
      {
        if (runTimeObjectDB.isPrivilegeToDeleteId(*itHS))
        {
          gotPrivilegeToDeleteId = true;
        }
      }
      if (gotPrivilegeToDeleteId)
      {
        continue;
      }
    }
    for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
    {
      itAttributeIn = theAttributeList.find(*itAttribute);
      if (itAttributeIn != theAttributeList.end())
      {
        if (federate->isInScope(*itObject, *itAttributeIn) == false)
        {
          items.insert(*itAttribute);
        }
      }
    }
    if (items.size())
    {
      GERTICO::IntoScopeJob *newIntoScopeJob;
      newIntoScopeJob = new IntoScopeJob(theFederate, *itObject, items, federatesHolder);
      federationJobs.add(newIntoScopeJob);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeAcquisitionNotification(GERTICO::RegisteredObject &theObject, GERTICO::HandleSet &theAttributes, bool const &theAsynchronous)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::doScopeAcquisitionNotification", "enter");
                           #endif   // inserted by Gal converter
  GERTICO::AttributeInfo *attributeInfoPtr;
  GERTICO::Federate *baseFederate;
  GERTICO::Federate *publisherFederate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet itemsInScope;
  GERTICO::HandleSet itemsOutOfScope;
  GERTICO::HandleSet publisherRegions;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itBaseFederate;
  GERTICO::HandleSet::iterator itPublisherFederate;
  GERTICO::HandleSet::iterator itPublisherRegion;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::Region *regionPtr;
  GeRtiFactory::GeRtiHandle knownObjectClass;
  GeRtiFactory::GeRtiHandle knownOtherObjectClass;
  bool inScope;

  pm.acquire();
  federatesHolder.getFederates(federates);
  for (itBaseFederate = federates.begin(); itBaseFederate != federates.end(); itBaseFederate++)
  {
    baseFederate = federatesHolder.getFederate(*itBaseFederate);
    if (baseFederate == NULL)
    {
      continue;
    }

    // Get the known class for the object.
    try
    {
      knownObjectClass = baseFederate->getObjectClass(theObject.getId());
    }
    catch(...)
    {
      continue;
    }

    itemsInScope.clear();
    itemsOutOfScope.clear();
    for (itAttribute = theAttributes.begin(); itAttribute != theAttributes.end(); itAttribute++)
    {
      attributeInfoPtr = theObject.getAttribute(*itAttribute);
      if (attributeInfoPtr->ownedByFederate(*itBaseFederate))
      {
        continue;
      }
      inScope = false;
      for (itPublisherFederate = federates.begin(); itPublisherFederate != federates.end(); itPublisherFederate++)
      {
        if (*itPublisherFederate == *itBaseFederate)
        {
          continue;
        }

        publisherFederate = federatesHolder.getFederate(*itBaseFederate);
        if (publisherFederate == NULL)
        {
          continue;
        }
        try
        {
          knownOtherObjectClass = publisherFederate->getObjectClass(theObject.getId());
        }
        catch(...)
        {
          continue;
        }
        if (attributeInfoPtr->ownedByFederate(*itPublisherFederate) == false)
        {
          continue;
        }

        attributeInfoPtr->getFedRegions(*itPublisherFederate, publisherRegions);
        for (itPublisherRegion = publisherRegions.begin(); itPublisherRegion != publisherRegions.end(); itPublisherRegion++)
        {
          if (*itPublisherRegion == 0)
          {
            if (baseFederate->isSubscribedToObjectClassAttribute(knownObjectClass, *itAttribute, false))
            {
              itemsInScope.insert(*itAttribute);
              inScope = true;
            }
          }
          else
          {
            baseFederate->getSubscribedAttributeRegions(knownObjectClass, *itAttribute, regions, false);
            for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
            {
              if (*itRegion == 0)
              {
                itemsInScope.insert(*itAttribute);
                inScope = true;
              }
              else
              {
                regionPtr = runTimeObjectDB.getRegion(*itRegion);
                if (regionPtr->gotIntersection(*itPublisherRegion))
                {
                  itemsInScope.insert(*itAttribute);
                  inScope = true;
                }
              }
            }
          }
        }
      }
      if (inScope == false)
      {
        itemsOutOfScope.insert(*itAttribute);
      }
    }
    if (itemsInScope.size())
    {
      GERTICO::IntoScopeJob *newIntoScopeJob;
      newIntoScopeJob = new IntoScopeJob(*itBaseFederate, theObject.getId(), itemsInScope, federatesHolder);
      if (theAsynchronous)
      {
        federationJobs.add(newIntoScopeJob);
      }
      else
      {
        pm.release();
        newIntoScopeJob->execute();
        delete newIntoScopeJob;
        pm.acquire();
      }
    }
    if (itemsOutOfScope.size())
    {
      GERTICO::OutOfScopeJob *newOutOfScopeJob;
      newOutOfScopeJob = new OutOfScopeJob(*itBaseFederate, theObject.getId(), itemsOutOfScope, federatesHolder, true);
      if (theAsynchronous)
      {
        federationJobs.add(newOutOfScopeJob);
      }
      else
      {
        pm.release();
        newOutOfScopeJob->execute();
        delete newOutOfScopeJob;
        pm.acquire();
      }
    }
  }
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::doScopeAcquisitionNotification", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeAssociate(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theObject, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSetMap &theFederateAttributesBefore)
{
  GERTICO::AttributeInfo *ownedAttributeInfoPtr;
  GERTICO::Federate *inScopeFederate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet ownedAttributes;
  GERTICO::HandleSet *otherAttributesPtr;
  GERTICO::HandleSet otherRegions;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itInScopeFederate;
  GERTICO::HandleSet::iterator itPubFederate;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap *objectAttributesPtr;
  GERTICO::HandleSetMap::iterator itFederateAttributesBefore;
  GERTICO::HandleSet::iterator itOtherRegion;
  GERTICO::HandleSetMap::iterator itObjectAttributes;
  GERTICO::HandleSetSetMap sendFedObjIntoScopeAttributes;
  GERTICO::HandleSetSetMap sendFedObjOutOfScopeAttributes;
  GERTICO::HandleSetSetMap::iterator itHSSM;
  GERTICO::Region *regionPtr;
  GeRtiFactory::GeRtiHandle objectId = theObject.getId();
  GeRtiFactory::GeRtiHandle knownClass;
  bool gotAttribute;
unsigned long ul;

  // For in-scope, only owned attributes are of interest.
  federatesHolder.getFederates(federates);
  theObject.getOwnedAttributes(theFederate, privilegeToDeleteId, ownedAttributes, false);
  for (itAttribute = ownedAttributes.begin(); itAttribute != ownedAttributes.end(); itAttribute++)
  {
    try
    {
      ownedAttributeInfoPtr = theObject.getAttribute(*itAttribute);
    }
    catch(...)
    {
      continue;
    }

    ownedAttributeInfoPtr->getFedRegions(theFederate, regions);
    for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
    {
      for (itInScopeFederate = federates.begin(); itInScopeFederate != federates.end(); itInScopeFederate++)
      {
        // Do not take the current federate.
        if (*itInScopeFederate == theFederate)
        {
          continue;
        }

        // Check if other federate has a subscription regardless of region.
        inScopeFederate = federatesHolder.getFederate(*itInScopeFederate);
        try
        {
          knownClass = inScopeFederate->getObjectClass(objectId);
        }
        catch(...)
        {
          continue;
        }
        if (*itRegion == 0)
        {
          // Any subscribe will work.
          if (inScopeFederate->isSubscribedToObjectClassAttribute(knownClass, *itAttribute, false))
          {
            fillFedObjAttributes(sendFedObjIntoScopeAttributes, *itInScopeFederate, objectId, *itAttribute);
          }
        }
        else
        {
          regionPtr = runTimeObjectDB.getRegion(*itRegion);

          // Must find a subscribe in the default region or some region overlap.
          inScopeFederate->getSubscribedRegions(knownClass, otherRegions);
          for (itOtherRegion = otherRegions.begin(); itOtherRegion != otherRegions.end(); itOtherRegion++)
          {
            if (*itOtherRegion == 0)
            {
              fillFedObjAttributes(sendFedObjIntoScopeAttributes, *itInScopeFederate, objectId, *itAttribute);
            }
            else
            {
              if (regionPtr->gotIntersection(*itOtherRegion))
              {
                fillFedObjAttributes(sendFedObjIntoScopeAttributes, *itInScopeFederate, objectId, *itAttribute);
              }
            }
          }
        }
      }
    }
  }

  // Send only one into scope for each object per federate.
  for (itHSSM = sendFedObjIntoScopeAttributes.begin(); itHSSM != sendFedObjIntoScopeAttributes.end(); itHSSM++)
  {
    objectAttributesPtr = &itHSSM->second;
    for (itObjectAttributes = objectAttributesPtr->begin(); itObjectAttributes != objectAttributesPtr->end(); itObjectAttributes++)
    {
      if (itObjectAttributes->second.size())
      {
        GERTICO::IntoScopeJob *newIntoScopeJob;
        newIntoScopeJob = new IntoScopeJob(itHSSM->first, itObjectAttributes->first, itObjectAttributes->second, federatesHolder);
        federationJobs.add(newIntoScopeJob);
      }
    }
  }

  // Do out-of scope logic.
  for (itFederateAttributesBefore = theFederateAttributesBefore.begin(); itFederateAttributesBefore != theFederateAttributesBefore.end(); itFederateAttributesBefore++)
  {
ul = itFederateAttributesBefore->first;
    inScopeFederate = federatesHolder.getFederate(itFederateAttributesBefore->first);
    if (inScopeFederate == NULL)
    {
      continue;
    }

    try
    {
      knownClass = inScopeFederate->getObjectClass(objectId);
    }
    catch(...)
    {
      continue;
    }

    otherAttributesPtr = &itFederateAttributesBefore->second;
    for (itAttribute = otherAttributesPtr->begin(); itAttribute != otherAttributesPtr->end(); itAttribute++)
    {
      gotAttribute = false;
      try
      {
        ownedAttributeInfoPtr = theObject.getAttribute(*itAttribute);
      }
      catch(...)
      {
        continue;
      }
      for (itPubFederate = federates.begin(); itPubFederate != federates.end(); itPubFederate++)
      {
        if (*itPubFederate == itFederateAttributesBefore->first)
        {
          continue;
        }
        ownedAttributeInfoPtr->getFedRegions(*itPubFederate, regions);
        inScopeFederate->getSubscribedAttributeRegions(knownClass, *itAttribute, otherRegions, false);
        for (itOtherRegion = otherRegions.begin(); itOtherRegion != otherRegions.end(); itOtherRegion++)
        {
          if (*itOtherRegion == 0)
          {
            gotAttribute = true;
          }
          else
          {
            for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
            {
              if (*itRegion == 0)
              {
                gotAttribute = true;
              }
              else
              {
                regionPtr = runTimeObjectDB.getRegion(*itRegion);
                if (regionPtr->gotIntersection(*itOtherRegion))
                {
                  gotAttribute = true;
                }
              }
            }
          }
        }
      }
      if (gotAttribute == false)
      {
        fillFedObjAttributes(sendFedObjOutOfScopeAttributes, itFederateAttributesBefore->first, objectId, *itAttribute);
      }
    }
  }

  // Send only one out-of scope for each object per federate.
  for (itHSSM = sendFedObjOutOfScopeAttributes.begin(); itHSSM != sendFedObjOutOfScopeAttributes.end(); itHSSM++)
  {
    objectAttributesPtr = &itHSSM->second;
    for (itObjectAttributes = objectAttributesPtr->begin(); itObjectAttributes != objectAttributesPtr->end(); itObjectAttributes++)
    {
      if (itObjectAttributes->second.size())
      {
        GERTICO::OutOfScopeJob *newOutOfScopeJob;
        newOutOfScopeJob = new OutOfScopeJob(itHSSM->first, itObjectAttributes->first, itObjectAttributes->second, federatesHolder, true);
        federationJobs.add(newOutOfScopeJob);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeAssociate(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theObject, GERTICO::HandleSetMap &theFederateAttributesBefore)
{
  GERTICO::AttributeInfo *ownedAttributeInfoPtr;
  GERTICO::Federate *inScopeFederate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet ownedAttributes;
  GERTICO::HandleSet *otherAttributesPtr;
  GERTICO::HandleSet otherRegions;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itInScopeFederate;
  GERTICO::HandleSet::iterator itPubFederate;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap *objectAttributesPtr;
  GERTICO::HandleSetMap::iterator itFederateAttributesBefore;
  GERTICO::HandleSet::iterator itOtherRegion;
  GERTICO::HandleSetMap::iterator itObjectAttributes;
  GERTICO::HandleSetSetMap sendFedObjIntoScopeAttributes;
  GERTICO::HandleSetSetMap sendFedObjOutOfScopeAttributes;
  GERTICO::HandleSetSetMap::iterator itHSSM;
  GERTICO::Region *regionPtr;
  GeRtiFactory::GeRtiHandle objectId = theObject.getId();
  GeRtiFactory::GeRtiHandle knownClass;
  bool gotAttribute;
unsigned long ul;

  // For in-scope, only owned attributes are of interest.
  federatesHolder.getFederates(federates);
  theObject.getOwnedAttributes(theFederate, privilegeToDeleteId, ownedAttributes, false);
  for (itAttribute = ownedAttributes.begin(); itAttribute != ownedAttributes.end(); itAttribute++)
  {
    try
    {
      ownedAttributeInfoPtr = theObject.getAttribute(*itAttribute);
    }
    catch(...)
    {
      continue;
    }

    ownedAttributeInfoPtr->getFedRegions(theFederate, regions);
    for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
    {
      for (itInScopeFederate = federates.begin(); itInScopeFederate != federates.end(); itInScopeFederate++)
      {
        // Do not take the current federate.
        if (*itInScopeFederate == theFederate)
        {
          continue;
        }

        // Check if other federate has a subscription regardless of region.
        inScopeFederate = federatesHolder.getFederate(*itInScopeFederate);
        try
        {
          knownClass = inScopeFederate->getObjectClass(objectId);
        }
        catch(...)
        {
          continue;
        }
        if (*itRegion == 0)
        {
          // Any subscribe will work.
          if (inScopeFederate->isSubscribedToObjectClassAttribute(knownClass, *itAttribute, false))
          {
            fillFedObjAttributes(sendFedObjIntoScopeAttributes, *itInScopeFederate, objectId, *itAttribute);
          }
        }
        else
        {
          regionPtr = runTimeObjectDB.getRegion(*itRegion);

          // Must find a subscribe in the default region or some region overlap.
          inScopeFederate->getSubscribedRegions(knownClass, otherRegions);
          for (itOtherRegion = otherRegions.begin(); itOtherRegion != otherRegions.end(); itOtherRegion++)
          {
            if (*itOtherRegion == 0)
            {
              fillFedObjAttributes(sendFedObjIntoScopeAttributes, *itInScopeFederate, objectId, *itAttribute);
            }
            else
            {
              if (regionPtr->gotIntersection(*itOtherRegion))
              {
                fillFedObjAttributes(sendFedObjIntoScopeAttributes, *itInScopeFederate, objectId, *itAttribute);
              }
            }
          }
        }
      }
    }
  }

  // Send only one into scope for each object per federate.
  for (itHSSM = sendFedObjIntoScopeAttributes.begin(); itHSSM != sendFedObjIntoScopeAttributes.end(); itHSSM++)
  {
    objectAttributesPtr = &itHSSM->second;
    for (itObjectAttributes = objectAttributesPtr->begin(); itObjectAttributes != objectAttributesPtr->end(); itObjectAttributes++)
    {
      if (itObjectAttributes->second.size())
      {
        GERTICO::IntoScopeJob *newIntoScopeJob;
        newIntoScopeJob = new IntoScopeJob(itHSSM->first, itObjectAttributes->first, itObjectAttributes->second, federatesHolder);
        federationJobs.add(newIntoScopeJob);
      }
    }
  }

  // Do out-of scope logic.
  for (itFederateAttributesBefore = theFederateAttributesBefore.begin(); itFederateAttributesBefore != theFederateAttributesBefore.end(); itFederateAttributesBefore++)
  {
ul = itFederateAttributesBefore->first;
    inScopeFederate = federatesHolder.getFederate(itFederateAttributesBefore->first);
    if (inScopeFederate == NULL)
    {
      continue;
    }

    try
    {
      knownClass = inScopeFederate->getObjectClass(objectId);
    }
    catch(...)
    {
      continue;
    }

    otherAttributesPtr = &itFederateAttributesBefore->second;
    for (itAttribute = otherAttributesPtr->begin(); itAttribute != otherAttributesPtr->end(); itAttribute++)
    {
      gotAttribute = false;
      try
      {
        ownedAttributeInfoPtr = theObject.getAttribute(*itAttribute);
      }
      catch(...)
      {
        continue;
      }
      for (itPubFederate = federates.begin(); itPubFederate != federates.end(); itPubFederate++)
      {
        if (*itPubFederate == itFederateAttributesBefore->first)
        {
          continue;
        }
        ownedAttributeInfoPtr->getFedRegions(*itPubFederate, regions);
        inScopeFederate->getSubscribedAttributeRegions(knownClass, *itAttribute, otherRegions, false);
        for (itOtherRegion = otherRegions.begin(); itOtherRegion != otherRegions.end(); itOtherRegion++)
        {
          if (*itOtherRegion == 0)
          {
            gotAttribute = true;
          }
          else
          {
            for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
            {
              if (*itRegion == 0)
              {
                gotAttribute = true;
              }
              else
              {
                regionPtr = runTimeObjectDB.getRegion(*itRegion);
                if (regionPtr->gotIntersection(*itOtherRegion))
                {
                  gotAttribute = true;
                }
              }
            }
          }
        }
      }
      if (gotAttribute == false)
      {
        fillFedObjAttributes(sendFedObjOutOfScopeAttributes, itFederateAttributesBefore->first, objectId, *itAttribute);
      }
    }
  }

  // Send only one out-of scope for each object per federate.
  for (itHSSM = sendFedObjOutOfScopeAttributes.begin(); itHSSM != sendFedObjOutOfScopeAttributes.end(); itHSSM++)
  {
    objectAttributesPtr = &itHSSM->second;
    for (itObjectAttributes = objectAttributesPtr->begin(); itObjectAttributes != objectAttributesPtr->end(); itObjectAttributes++)
    {
      if (itObjectAttributes->second.size())
      {
        GERTICO::OutOfScopeJob *newOutOfScopeJob;
        newOutOfScopeJob = new OutOfScopeJob(itHSSM->first, itObjectAttributes->first, itObjectAttributes->second, federatesHolder, true);
        federationJobs.add(newOutOfScopeJob);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeModify(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theRegionsBefore, GERTICO::HandleSet &theRegionsAfter)
{
  doScopeModifyOutPub(theFederate, theRegion, theRegionsBefore, theRegionsAfter);
  doScopeModifyOutSub(theFederate, theRegion, theRegionsBefore, theRegionsAfter);
  doScopeModifyInPub(theFederate, theRegion, theRegionsBefore, theRegionsAfter);
  doScopeModifyInSub(theFederate, theRegion, theRegionsBefore, theRegionsAfter);
}

// ---------------------------------------------------------------------------
// In this method, the federate modifying the region is a publisher of
// some object attributes in the region. the other federates will receive
// an in scope if the regions now overlap
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeModifyInPub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theRegionsBefore, GERTICO::HandleSet &theRegionsAfter)
{
  GERTICO::Federate *federatePtr;
  GERTICO::HandleSet *attributes;
  GERTICO::HandleSet::iterator itHSAtt;
  GERTICO::HandleSet::iterator itRegionAfter;
  GERTICO::HandleSet::iterator itRegionBefore;
  GERTICO::HandleSetMap objectAttributes;
  GERTICO::HandleSetMap *objectAttributesPtr;
  GERTICO::HandleSetMap::iterator itObjectAttributes;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetSetMap sendFedObjAttributes;
  GERTICO::HandleSetSetMap::iterator itHSSM;
  GERTICO::Region *thisRegion;
  GERTICO::Region *tmpRegion;
  GeRtiFactory::GeRtiHandle federate;
  GeRtiFactory::GeRtiHandle knownClass;

  thisRegion = runTimeObjectDB.getRegion(theRegion);
  thisRegion->getObjectAttributes(objectAttributes, registeredObjectsHolder);

  // Take care of subscribers to this federate's attributes.
  for (itRegionAfter = theRegionsAfter.begin(); itRegionAfter != theRegionsAfter.end(); itRegionAfter++)
  {
    itRegionBefore = theRegionsBefore.find(*itRegionAfter);
    if (itRegionBefore == theRegionsBefore.end())
    {
      // Send in scope
      tmpRegion = runTimeObjectDB.getRegion(*itRegionAfter);
      federate = tmpRegion->getFederateId();
      federatePtr = federatesHolder.getFederate(federate);
      for (itHSM = objectAttributes.begin(); itHSM != objectAttributes.end(); itHSM++)
      {
        attributes = &itHSM->second;
        try
        {
          // Federate may not know about the object.
          knownClass = federatePtr->getObjectClass(itHSM->first);
        }
        catch(GeRtiFactory::ObjectNotKnown &)
        {
          continue;
        }
        for (itHSAtt = attributes->begin(); itHSAtt != attributes->end(); itHSAtt++)
        {
          if (federatePtr->isSubscribedToObjectClassRegionAttribute(knownClass, *itRegionAfter, *itHSAtt))
          {
            fillFedObjAttributes(sendFedObjAttributes, federate, itHSM->first, *itHSAtt);
          }
        }
      }
    }
  }

  // Send only one into scope for each object per federate.
  for (itHSSM = sendFedObjAttributes.begin(); itHSSM != sendFedObjAttributes.end(); itHSSM++)
  {
    objectAttributesPtr = &itHSSM->second;
    for (itObjectAttributes = objectAttributesPtr->begin(); itObjectAttributes != objectAttributesPtr->end(); itObjectAttributes++)
    {
      GERTICO::IntoScopeJob *newIntoScopeJob;
      newIntoScopeJob = new IntoScopeJob(itHSSM->first, itObjectAttributes->first, itObjectAttributes->second, federatesHolder);
      federationJobs.add(newIntoScopeJob);
    }
  }
}

// ---------------------------------------------------------------------------
// In this method, the federate modifying the region is a subscriber of
// some object attributes in a region belonging to an other federate.
// This federate will receive an in scope if the regions now overlap.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeModifyInSub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theRegionsBefore, GERTICO::HandleSet &theRegionsAfter)
{
  GERTICO::Federate *federatePtr;
  GERTICO::HandleSet *attributes;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itHSAtt;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSet::iterator itRegionAfter;
  GERTICO::HandleSet::iterator itRegionBefore;
  GERTICO::HandleSetMap objectAttributes;
  GERTICO::HandleSetMap objectAttributesScope;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetMap::iterator itOAS;
  GERTICO::Region *otherRegion;
  GeRtiFactory::GeRtiHandle otherFederate;
  GeRtiFactory::GeRtiHandle knownClass;
  bool found = false;

  // Take care of this federate as subscriber
  federatePtr = federatesHolder.getFederate(theFederate);
  if (federatePtr == NULL)
  {
    return;
  }

  for (itRegionAfter = theRegionsAfter.begin(); itRegionAfter != theRegionsAfter.end(); itRegionAfter++)
  {
    itRegionBefore = theRegionsBefore.find(*itRegionAfter);
    if (itRegionBefore == theRegionsBefore.end())
    {
      // Send into scope
      otherRegion = runTimeObjectDB.getRegion(*itRegionAfter);
      otherFederate = otherRegion->getFederateId();
      otherRegion->getObjectAttributes(objectAttributes, registeredObjectsHolder);
      for (itHSM = objectAttributes.begin(); itHSM != objectAttributes.end(); itHSM++)
      {
        attributes = &itHSM->second;
        try
        {
          knownClass = federatePtr->getObjectClass(itHSM->first);
        }
        catch(...)
        {
          continue;
        }
        federatePtr->getSubscribedRegions(knownClass, regions);
        for (itHSAtt = attributes->begin(); itHSAtt != attributes->end(); itHSAtt++)
        {
          // Check default region.
          if (federatePtr->isSubscribedToObjectClassRegionAttribute(knownClass, 0, *itHSAtt))
          {
            continue;
          }
          // Check other regions.
          found = false;
          for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
          {
            if (*itRegion == theRegion)
            {
              continue;
            }
            if (federatePtr->isSubscribedToObjectClassRegionAttribute(knownClass, *itRegion, *itHSAtt))
            {
              found = true;
              break;
            }
          }
          if (found == false)
          {
            itOAS = objectAttributesScope.find(itHSM->first);
            if (itOAS != objectAttributesScope.end())
            {
              itOAS->second.insert(*itHSAtt);
            }
            else
            {
              GERTICO::HandleSet sendAttributes;
              sendAttributes.insert(*itHSAtt);
              objectAttributesScope[itHSM->first] = sendAttributes;
            }
          }
        }
      }
    }
  }
  // Send only one into scope per object.
  for (itOAS = objectAttributesScope.begin(); itOAS != objectAttributesScope.end(); itOAS++)
  {
    GERTICO::IntoScopeJob *newIntoScopeJob;
    newIntoScopeJob = new IntoScopeJob(theFederate, itOAS->first, itOAS->second, federatesHolder);
    federationJobs.add(newIntoScopeJob);
  }
}

// ---------------------------------------------------------------------------
// In this method, the federate modifying the region is a publisher of
// some object attributes in the region. the other federates will receive
// an out of scope if the regions no longer overlap
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeModifyOutPub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theRegionsBefore, GERTICO::HandleSet &theRegionsAfter)
{
  GERTICO::Federate *publisherPtr;
  GERTICO::Federate *subscriberPtr;
  GERTICO::HandleSet *attributes;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itHSAtt;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSet::iterator itRegionAfter;
  GERTICO::HandleSet::iterator itRegionBefore;
  GERTICO::HandleSetMap objectAttributes;
  GERTICO::HandleSetMap *objectAttributesPtr;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetMap::iterator itOAS;
  GERTICO::HandleSetMap::iterator itObjectAttributes;
  GERTICO::HandleSetSetMap sendFedObjAttributes;
  GERTICO::HandleSetSetMap::iterator itHSSM;
  GERTICO::Region *publisherRegion;
  GERTICO::Region *tmpRegion;
  GeRtiFactory::GeRtiHandle federate;
  GeRtiFactory::GeRtiHandle knownClass;
  bool found = false;

  publisherRegion = runTimeObjectDB.getRegion(theRegion);
  publisherRegion->getObjectAttributes(objectAttributes, registeredObjectsHolder);

  // Take care of subscribers to this federate's attributes.
  publisherPtr = federatesHolder.getFederate(theFederate);
  for (itRegionBefore = theRegionsBefore.begin(); itRegionBefore != theRegionsBefore.end(); itRegionBefore++)
  {
    itRegionAfter = theRegionsAfter.find(*itRegionBefore);
    if (itRegionAfter == theRegionsAfter.end())
    {
      // Send out of scope
      GERTICO::HandleSet sendAttributes;
      tmpRegion = runTimeObjectDB.getRegion(*itRegionBefore);
      federate = tmpRegion->getFederateId();
      if (federate == theFederate)
      {
        continue;
      }
      subscriberPtr = federatesHolder.getFederate(federate);
      for (itHSM = objectAttributes.begin(); itHSM != objectAttributes.end(); itHSM++)
      {
        attributes = &itHSM->second;
        knownClass = subscriberPtr->getObjectClass(itHSM->first);
        subscriberPtr->getSubscribedRegions(knownClass, regions);
        for (itHSAtt = attributes->begin(); itHSAtt != attributes->end(); itHSAtt++)
        {
          // Check default region.
          if (subscriberPtr->isSubscribedToObjectClassRegionAttribute(knownClass, 0, *itHSAtt))
          {
            continue;
          }
          // Check other regions.
          found = false;
          for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
          {
            if (*itRegion == theRegion)
            {
              continue;
            }
            if (publisherRegion->gotIntersection(*itRegion))
            {
              found = true;
              break;
            }
          }
          if (found == false)
          {
            fillFedObjAttributes(sendFedObjAttributes, federate, itHSM->first, *itHSAtt);
          }
        }
      }
    }
  }

  // Send only one out of scope for each object per federate.
  for (itHSSM = sendFedObjAttributes.begin(); itHSSM != sendFedObjAttributes.end(); itHSSM++)
  {
    objectAttributesPtr = &itHSSM->second;
    for (itObjectAttributes = objectAttributesPtr->begin(); itObjectAttributes != objectAttributesPtr->end(); itObjectAttributes++)
    {
      GERTICO::OutOfScopeJob *newOutOfScopeJob;
      newOutOfScopeJob = new OutOfScopeJob(itHSSM->first, itObjectAttributes->first, itObjectAttributes->second, federatesHolder, true);
      federationJobs.add(newOutOfScopeJob);
    }
  }
}

// ---------------------------------------------------------------------------
// In this method, the federate modifying the region is a subscriber of
// some object attributes in a region belonging to an other federate.
// This federate will receive an out of scope if the regions no longer
// overlap.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeModifyOutSub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theRegionsBefore, GERTICO::HandleSet &theRegionsAfter)
{
  GERTICO::Federate *federatePtr;
  GERTICO::HandleSet *attributes;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itHSAtt;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSet::iterator itRegionAfter;
  GERTICO::HandleSet::iterator itRegionBefore;
  GERTICO::HandleSetMap objectAttributes;
  GERTICO::HandleSetMap objectAttributesScope;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetMap::iterator itOAS;
  GERTICO::Region *tmpRegion;
  GeRtiFactory::GeRtiHandle federate;
  GeRtiFactory::GeRtiHandle knownClass;
  bool found = false;

  // Take care of this federate as subscriber
  federatePtr = federatesHolder.getFederate(theFederate);
  for (itRegionBefore = theRegionsBefore.begin(); itRegionBefore != theRegionsBefore.end(); itRegionBefore++)
  {
    itRegionAfter = theRegionsAfter.find(*itRegionBefore);
    if (itRegionAfter == theRegionsAfter.end())
    {
      // Send out of scope
      tmpRegion = runTimeObjectDB.getRegion(*itRegionBefore);
      tmpRegion->getObjectAttributes(objectAttributes, registeredObjectsHolder);
      federate = tmpRegion->getFederateId();
      for (itHSM = objectAttributes.begin(); itHSM != objectAttributes.end(); itHSM++)
      {
        attributes = &itHSM->second;
        knownClass = federatePtr->getObjectClass(itHSM->first);
        federatePtr->getSubscribedRegions(knownClass, regions);
        for (itHSAtt = attributes->begin(); itHSAtt != attributes->end(); itHSAtt++)
        {
          // Check default region.
          if (federatePtr->isSubscribedToObjectClassRegionAttribute(knownClass, 0, *itHSAtt))
          {
            continue;
          }
          // Check other regions.
          found = false;
          for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
          {
            if (*itRegion == theRegion)
            {
              continue;
            }
            if (federatePtr->isSubscribedToObjectClassRegionAttribute(knownClass, *itRegion, *itHSAtt))
            {
              found = true;
              break;
            }
          }
          if (found == false)
          {
            itOAS = objectAttributesScope.find(itHSM->first);
            if (itOAS != objectAttributesScope.end())
            {
              itOAS->second.insert(*itHSAtt);
            }
            else
            {
              GERTICO::HandleSet sendAttributes;
              sendAttributes.insert(*itHSAtt);
              objectAttributesScope[itHSM->first] = sendAttributes;
            }
          }
        }
      }
    }
  }

  // Send only one out of scope per object.
  for (itOAS = objectAttributesScope.begin(); itOAS != objectAttributesScope.end(); itOAS++)
  {
    GERTICO::OutOfScopeJob *newOutOfScopeJob;
    newOutOfScopeJob = new OutOfScopeJob(theFederate, itOAS->first, itOAS->second, federatesHolder, true);
    federationJobs.add(newOutOfScopeJob);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeRegister(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theObject)
{
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::Federate *subscriberFederate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet inScopeAttributes;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet subscriberFederates;
  GERTICO::HandleSet subscriberRegions;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSet::iterator itSubscriberFederate;
  GERTICO::HandleSet::iterator itSubscriberRegion;
  GERTICO::Region *currRegion;
  GeRtiFactory::GeRtiHandle knownClass;
unsigned long ul;

  theObject.getOwnedAttributes(theFederate, privilegeToDeleteId, attributes, true);

  federatesHolder.getFederates(subscriberFederates);
  for (itSubscriberFederate = subscriberFederates.begin(); itSubscriberFederate != subscriberFederates.end(); itSubscriberFederate++)
  {
    // Do not take calling federate.
    if (*itSubscriberFederate == theFederate)
    {
      continue;
    }

    subscriberFederate = federatesHolder.getFederate(*itSubscriberFederate);
    // Get known class if object is known.
    try
    {
      knownClass = subscriberFederate->getObjectClass(theObject.getId());
    }
    catch(...)
    {
      continue;
    }

    subscriberFederate->getSubscribedRegions(knownClass, subscriberRegions);
    if (subscriberRegions.size() == 0)
    {
      continue;
    }

    inScopeAttributes.clear();
    for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
    {
ul = *itAttribute;
      try
      {
        attributeInfo = theObject.getAttribute(*itAttribute);
      }
      catch(...)
      {
        continue;
      }
      subscriberFederate->getSubscribedAttributeRegions(knownClass, *itAttribute, subscriberRegions, false);
      attributeInfo->getFedRegions(theFederate, regions);
      for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
      {
        if (*itRegion == 0)
        {
          if (subscriberFederate->isSubscribedToObjectClassAttribute(knownClass, *itAttribute, false))
          {
            inScopeAttributes.insert(*itAttribute);
          }
        }
        else
        {
          currRegion = runTimeObjectDB.getRegion(*itRegion);
          if (currRegion)
          {
            for (itSubscriberRegion = subscriberRegions.begin(); itSubscriberRegion != subscriberRegions.end(); itSubscriberRegion++)
            {
              if (currRegion->gotIntersection(*itSubscriberRegion))
              {
                inScopeAttributes.insert(*itAttribute);
                break;
              }
            }
          }
        }
      }
    }
    if (inScopeAttributes.size())
    {
      GERTICO::IntoScopeJob *newIntoScopeJob;
      newIntoScopeJob = new IntoScopeJob(*itSubscriberFederate, theObject.getId(), inScopeAttributes, federatesHolder);
      federationJobs.add(newIntoScopeJob);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeSubscribe(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, bool const &theSendOutOfScope)
{
  GERTICO::AttributeInfo *ownedAttributeInfoPtr;
  GERTICO::ClassDescr *classDescr;
  GERTICO::ClassDescr *testClass;
  GERTICO::Federate *federatePtr;
  GERTICO::Federate *publisherFederatePtr;
  GERTICO::HandleSet *attributesPtr;
  GERTICO::HandleSet otherAttributes;
  GERTICO::HandleSet publisherObjects;
  GERTICO::HandleSet otherRegions;
  GERTICO::HandleSet publisherFederates;
  GERTICO::HandleSet subscribedRegions;
  GERTICO::HandleSet::iterator itOtherAttribute;
  GERTICO::HandleSet::iterator itPublisherObject;
  GERTICO::HandleSet::iterator itOtherRegion;
  GERTICO::HandleSet::iterator itPublisherFederate;
  GERTICO::HandleSet::iterator itSubscribedRegion;
  GERTICO::HandleSetMap objectAttributes;
  GERTICO::HandleSetMap objectInScopeAttributes;
  GERTICO::HandleSetMap objectOutOfScopeAttributes;
  GERTICO::HandleSetMap::iterator itObjectAttributes;
  GERTICO::Region *otherRegionPtr;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle otherObjectClassId;
  bool found;
unsigned long ul;

  // Get calling federate.
  federatePtr = federatesHolder.getFederate(theFederate);
  if (federatePtr == NULL)
  {
    return;
  }

  // Loop through publisher federates.
  federatesHolder.getFederates(publisherFederates);
  for (itPublisherFederate = publisherFederates.begin(); itPublisherFederate != publisherFederates.end(); itPublisherFederate++)
  {
    ul = *itPublisherFederate;
    // Do not take the calling federate
    if (*itPublisherFederate == theFederate)
    {
      continue;
    }

    publisherFederatePtr = federatesHolder.getFederate(*itPublisherFederate);

    // Go through publisher federate's objects.
    publisherFederatePtr->getKnownObjects(publisherObjects);
    for (itPublisherObject = publisherObjects.begin(); itPublisherObject != publisherObjects.end(); itPublisherObject++)
    {
      ul = *itPublisherObject;
      registeredObject = registeredObjectsHolder.getObject(*itPublisherObject);
      otherObjectClassId = registeredObject->getClassId();
      classDescr = runTimeObjectDB.getObjectClassDescr(otherObjectClassId);

      // Check class hierarchy.
      if (classDescr->isDerivedClass(theObjectClass) == false)
      {
        continue;
      }

      registeredObject->getOwnedAttributes(*itPublisherFederate, privilegeToDeleteId, otherAttributes, false);
      for (itOtherAttribute = otherAttributes.begin(); itOtherAttribute != otherAttributes.end(); itOtherAttribute++)
      {
        try
        {
          ownedAttributeInfoPtr = registeredObject->getAttribute(*itOtherAttribute);
        }
        catch(...)
        {
          continue;
        }

        fillHandleSetMap(objectAttributes, *itPublisherObject, *itOtherAttribute);
      }
    }
  }

  // Have a map of objects/attributes owned by other publishers.
  for (itObjectAttributes = objectAttributes.begin(); itObjectAttributes != objectAttributes.end(); itObjectAttributes++)
  {
    ul = itObjectAttributes->first;
    GeRtiFactory::GeRtiHandle owner;

    registeredObject = registeredObjectsHolder.getObject(itObjectAttributes->first);
    registeredObject->getOwner(owner, privilegeToDeleteId);
    classDescr = runTimeObjectDB.getObjectClassDescr(registeredObject->getClassId());

    attributesPtr = &itObjectAttributes->second;
    for (itOtherAttribute = attributesPtr->begin(); itOtherAttribute != attributesPtr->end(); itOtherAttribute++)
    {
      ul = *itOtherAttribute;
      found = false;
      try
      {
        ownedAttributeInfoPtr = registeredObject->getAttribute(*itOtherAttribute);
      }
      catch(...)
      {
        continue;
      }

      ownedAttributeInfoPtr->getFedRegions(owner, otherRegions);
      for (itOtherRegion = otherRegions.begin(); itOtherRegion != otherRegions.end(); itOtherRegion++)
      {
        ul = *itOtherRegion;
        if (*itOtherRegion == 0)
        {
          for (testClass = classDescr; testClass != NULL; testClass = testClass->parent)
          {
            if (federatePtr->isSubscribedToObjectClassAttribute(testClass->getId(), *itOtherAttribute, false))
            {
              if (federatePtr->isInScope(itObjectAttributes->first, *itOtherAttribute) == false)
              {
                fillHandleSetMap(objectInScopeAttributes, itObjectAttributes->first, *itOtherAttribute);
              }
              found = true;
            }
          }
        }
        else
        {
          otherRegionPtr = runTimeObjectDB.getRegion(*itOtherRegion);
          for (testClass = classDescr; testClass != NULL; testClass = testClass->parent)
          {
            federatePtr->getSubscribedAttributeRegions(testClass->getId(), *itOtherAttribute, subscribedRegions, false);
            for (itSubscribedRegion = subscribedRegions.begin(); itSubscribedRegion != subscribedRegions.end(); itSubscribedRegion++)
            {
              ul = *itSubscribedRegion;
              if (*itSubscribedRegion == 0)
              {
                if (federatePtr->isInScope(itObjectAttributes->first, *itOtherAttribute) == false)
                {
                  fillHandleSetMap(objectInScopeAttributes, itObjectAttributes->first, *itOtherAttribute);
                }
                found = true;
              }
              else
              {
                if (otherRegionPtr->gotIntersection(*itSubscribedRegion))
                {
                  if (federatePtr->isInScope(itObjectAttributes->first, *itOtherAttribute) == false)
                  {
                    fillHandleSetMap(objectInScopeAttributes, itObjectAttributes->first, *itOtherAttribute);
                  }
                 found = true;
                }
              }
            }
          }
        }
      }

      // No intersection found.
      if (found == false)
      {
        bool gotSubscriber = false;

        if (federatePtr->isInScope(itObjectAttributes->first, *itOtherAttribute))
        {
          for (testClass = classDescr; testClass != NULL; testClass = testClass->parent)
          {
            if (federatePtr->isSubscribedToObjectClassAttribute(testClass->getId(), *itOtherAttribute, false))
            {
              fillHandleSetMap(objectOutOfScopeAttributes, itObjectAttributes->first, *itOtherAttribute);
              gotSubscriber = true;
            }
          }

          if (gotSubscriber == false)
          {
            GeRtiFactory::Handles attributesOutOfScope;
            attributesOutOfScope.length(1);
            attributesOutOfScope[0] = *itOtherAttribute;
            federatePtr->setOutScope(itObjectAttributes->first, attributesOutOfScope);
          }
        }
      }
    }
  }

  for (itObjectAttributes = objectInScopeAttributes.begin(); itObjectAttributes != objectInScopeAttributes.end(); itObjectAttributes++)
  {
    GERTICO::IntoScopeJob *newIntoScopeJob;
    newIntoScopeJob = new IntoScopeJob(theFederate, itObjectAttributes->first, itObjectAttributes->second, federatesHolder);
    federationJobs.add(newIntoScopeJob);
  }

  for (itObjectAttributes = objectOutOfScopeAttributes.begin(); itObjectAttributes != objectOutOfScopeAttributes.end(); itObjectAttributes++)
  {
    GERTICO::OutOfScopeJob *newOutOfScopeJob;
    newOutOfScopeJob = new GERTICO::OutOfScopeJob(theFederate, itObjectAttributes->first, itObjectAttributes->second, federatesHolder, theSendOutOfScope);
    federationJobs.add(newOutOfScopeJob);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doScopeUnsubscribe(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass)
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *federatePtr;
  GERTICO::Federate *publisherFederatePtr;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet publisherAttributes;
  GERTICO::HandleSet publisherObjects;
  GERTICO::HandleSet subscribedRegions;
  GERTICO::HandleSet::iterator itPublisherAttribute;
  GERTICO::HandleSet::iterator itPublisherFederate;
  GERTICO::HandleSet::iterator itPublisherObject;
  GERTICO::HandleSet::iterator itSubscribedRegion;
  GERTICO::HandleSetMap objectOutScopeAttributes;
  GERTICO::HandleSetMap::iterator itObjectAttributes;
  GERTICO::RegisteredObject *publisherRegisteredObject;
  GeRtiFactory::GeRtiHandle publisherObjectClassId;

  // Get calling federate.
  federatePtr = federatesHolder.getFederate(theFederate);

  // Loop through other federates.
  federatesHolder.getFederates(federates);
  for (itPublisherFederate = federates.begin(); itPublisherFederate != federates.end(); itPublisherFederate++)
  {
    // Do not take the calling federate
    if (*itPublisherFederate == theFederate)
    {
      continue;
    }

    publisherFederatePtr = federatesHolder.getFederate(*itPublisherFederate);

    // Go through other federate's objects.
    publisherFederatePtr->getKnownObjects(publisherObjects);
    for (itPublisherObject = publisherObjects.begin(); itPublisherObject != publisherObjects.end(); itPublisherObject++)
    {
      publisherRegisteredObject = registeredObjectsHolder.getObject(*itPublisherObject);
      publisherObjectClassId = publisherRegisteredObject->getClassId();
      classDescr = runTimeObjectDB.getObjectClassDescr(publisherObjectClassId);

      // Check class hierarchy.
      if (classDescr->isDerivedClass(theObjectClass) == false)
      {
        continue;
      }

      publisherRegisteredObject->getOwnedAttributes(*itPublisherFederate, privilegeToDeleteId, publisherAttributes, false);
      for (itPublisherAttribute = publisherAttributes.begin(); itPublisherAttribute != publisherAttributes.end(); itPublisherAttribute++)
      {
        if (checkAnySubscriber(*itPublisherFederate, *publisherRegisteredObject, *itPublisherAttribute))
        {
          continue;
        }

        // No subscriber found - attribute goes out of scope
        fillHandleSetMap(objectOutScopeAttributes, *itPublisherObject, *itPublisherAttribute);
      }
    }
  }

  for (itObjectAttributes = objectOutScopeAttributes.begin(); itObjectAttributes != objectOutScopeAttributes.end(); itObjectAttributes++)
  {
    GERTICO::OutOfScopeJob *newOutOfScopeJob;
    newOutOfScopeJob = new OutOfScopeJob(theFederate, itObjectAttributes->first, itObjectAttributes->second, federatesHolder, false);
    federationJobs.add(newOutOfScopeJob);
  }
}

// ---------------------------------------------------------------------------
// NB: caller must secure the mutex lock.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doTurnOnForObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &attributeSet, bool asynchronous)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::doTurnOnForObjectInstance", "enter");
                           #endif   // inserted by Gal converter
  GERTICO::Federate *currFed;
  GERTICO::Federate *federatePublisher;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet federateSubscribers;
  GERTICO::HandleSet subscribers;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itAtt;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::HandleSetMap::iterator itSubscriber;
  GERTICO::HandleSetMap sendAttributeSubscribers;
  TurnOnForObjectInstance *newTurnOn;

  pm.acquire();
  federatesHolder.getFederates(federateSubscribers);
  // Get fed ambassador for this fed.
  federatePublisher = federatesHolder.getFederate(theFederate);
  if (federatePublisher)
  {
    GeRtiFactory::GeRtiHandle knownClass;

    attributes = attributeSet;
    for (itFederate = federateSubscribers.begin(); itFederate != federateSubscribers.end(); itFederate++)
    {
      currFed = federatesHolder.getFederate(*itFederate);
      if (currFed == NULL)
      {
        continue;
      }
      if (currFed->knowObject(theObject))
      {
        try
        {
          knownClass = currFed->getObjectClass(theObject);
        }
        catch(...)
        {
          continue;
        }
      }
      for (itAtt = attributes.begin(); itAtt != attributes.end(); itAtt++)
      {
        if (currFed->isSubscribedToObjectClassAttribute(knownClass, *itAtt, false))
        {
          if (*itFederate != theFederate)
          {
            if (federatePublisher->testTurnedOn(theObject, *itAtt) == false)
            {
              itSubscriber = sendAttributeSubscribers.find(*itAtt);
              if (itSubscriber != sendAttributeSubscribers.end())
              {
                GERTICO::HandleSet *subscribersPtr;
                subscribersPtr = &itSubscriber->second;
                subscribersPtr->insert(currFed->getId());
              }
              else
              {
                subscribers.insert(currFed->getId());
                sendAttributeSubscribers[*itAtt] = subscribers;
                subscribers.clear();
              }
            }
          }
        }
      }
    }
    if (sendAttributeSubscribers.size())
    {
      newTurnOn = new TurnOnForObjectInstance(theFederate, theObject, sendAttributeSubscribers, federatesHolder);
      if (asynchronous)
      {
        federationJobs.add(newTurnOn);
      }
      else
      {
        pm.release();
        newTurnOn->execute();
        delete newTurnOn;
        pm.acquire();
      }
    }
  }
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::doTurnOnForObjectInstance", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doTurnOnForSubscribedClass(GERTICO::Federate &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSetMap &theAttRegMap)
{
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::Federate *federatePublisherPtr;
  GERTICO::HandleSet federatePublishers;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet otherAttributes;
  GERTICO::HandleSet otherRegions;
  GERTICO::HandleSet *regions;
  GERTICO::HandleSet turnOnAttributes;
  GERTICO::HandleSet::iterator itFederatePublisher;
  GERTICO::HandleSet::iterator ito;
  GERTICO::HandleSet::iterator itOtherAttribute;
  GERTICO::HandleSet::iterator itOtherRegion;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap::iterator itAttRegMap;
  GERTICO::Region *region;
  GERTICO::RegisteredObject *registeredObject;
  bool gotAttribute = false;

  theFederate.getKnownObjects(theObjectClass, objects);

  // Turn on publishers who are not publishing.
  federatesHolder.getFederates(federatePublishers);
  for (itFederatePublisher = federatePublishers.begin(); itFederatePublisher != federatePublishers.end(); itFederatePublisher++)
  {
    if (*itFederatePublisher == theFederate.getId())
    {
      continue;
    }
    federatePublisherPtr = federatesHolder.getFederate(*itFederatePublisher);
    for (ito = objects.begin(); ito != objects.end(); ito++)
    {
      try
      {
        registeredObject = registeredObjectsHolder.getObject(*ito);
      }
      catch(...)
      {
        continue;
      }
      turnOnAttributes.clear();
      registeredObject->getOwnedAttributes(*itFederatePublisher, privilegeToDeleteId, otherAttributes, false);
      for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
      {
        gotAttribute = false;
        itOtherAttribute = otherAttributes.find(itAttRegMap->first);
        if (itOtherAttribute != otherAttributes.end())
        {
          try
          {
            attributeInfo = registeredObject->getAttribute(*itOtherAttribute);
          }
          catch(...)
          {
            continue;
          }
          attributeInfo->getFedRegions(*itFederatePublisher, otherRegions);

          regions = &itAttRegMap->second;
          for (itRegion = regions->begin(); itRegion != regions->end(); itRegion++)
          {
            region = runTimeObjectDB.getRegion(*itRegion);
            for (itOtherRegion = otherRegions.begin(); itOtherRegion != otherRegions.end(); itOtherRegion++)
            {
              if (*itOtherRegion == 0)
              {
                turnOnAttributes.insert(*itOtherAttribute);
                gotAttribute = true;
                break;
              }
              else
              {
                if (region->gotIntersection(*itOtherRegion))
                {
                  turnOnAttributes.insert(*itOtherAttribute);
                  gotAttribute = true;
                  break;
                }
              }
            }
            if (gotAttribute)
            {
              break;
            }
          }
        }
      }
      if (turnOnAttributes.size())
      {
        pm.release();
        doTurnOnForObjectInstance(*ito, federatePublisherPtr->getId(), turnOnAttributes, true);
        pm.acquire();
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doTurnOffForSubscribedClass(GERTICO::Federate &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass)
{
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::Federate *publisherFederate;
  GERTICO::Federate *subscriberFederate;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet publishedAttributes;
  GERTICO::HandleSet publishedRegions;
  GERTICO::HandleSet publishedClasses;
  GERTICO::HandleSet publisherFederates;
  GERTICO::HandleSet subscriberFederates;
  GERTICO::HandleSet subscribers;
  GERTICO::HandleSet subscribedRegions;
  GERTICO::HandleSet turnOffAttributes;
  GERTICO::HandleSet::iterator ito;
  GERTICO::HandleSet::iterator itOtherAttribute;
  GERTICO::HandleSet::iterator itPublishedClass;
  GERTICO::HandleSet::iterator itPublisherFederate;
  GERTICO::HandleSet::iterator itPublishedRegion;
  GERTICO::HandleSet::iterator itSubscriberFederate;
  GERTICO::HandleSet::iterator itSubscribedRegion;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap::iterator itAttRegMap;
  GERTICO::HandleSetMap::iterator itSubscriber;
  GERTICO::HandleSetMap sendAttributeSubscribers;
  GERTICO::Region *region;
  GERTICO::RegisteredObject *registeredObject;
  GERTICO::TurnOffForObjectInstance *turnOffForObjectInstance;
  GeRtiFactory::GeRtiHandle knownSubscriberClass;
  bool gotAttribute = false;

  // Turn off publishers who have no subscribers.
  federatesHolder.getFederates(publisherFederates);
  federatesHolder.getFederates(subscriberFederates);
  for (itPublisherFederate = publisherFederates.begin(); itPublisherFederate != publisherFederates.end(); itPublisherFederate++)
  {
    if (*itPublisherFederate == theFederate.getId())
    {
      continue;
    }
    publisherFederate = federatesHolder.getFederate(*itPublisherFederate);
    publisherFederate->getPublishedObjectClasses(publishedClasses);

    // For each published class.
    for (itPublishedClass = publishedClasses.begin(); itPublishedClass != publishedClasses.end(); itPublishedClass++)
    {
      publisherFederate->getKnownObjects(*itPublishedClass, objects);

      // For each published object.
      for (ito = objects.begin(); ito != objects.end(); ito++)
      {
        try
        {
          registeredObject = registeredObjectsHolder.getObject(*ito);
        }
        catch(...)
        {
          continue;
        }
        turnOffAttributes.clear();
        registeredObject->getOwnedAttributes(*itPublisherFederate, privilegeToDeleteId, publishedAttributes, false);
        for (itOtherAttribute = publishedAttributes.begin(); itOtherAttribute != publishedAttributes.end(); itOtherAttribute++)
        {
          gotAttribute = false;

          try
          {
            attributeInfo = registeredObject->getAttribute(*itOtherAttribute);
          }
          catch(...)
          {
            continue;
          }
          attributeInfo->getFedRegions(*itPublisherFederate, publishedRegions);

          for (itSubscriberFederate = subscriberFederates.begin(); itSubscriberFederate != subscriberFederates.end(); itSubscriberFederate++)
          {
            if (*itSubscriberFederate == *itPublisherFederate)
            {
              continue;
            }

            subscriberFederate = federatesHolder.getFederate(*itSubscriberFederate);
            if (subscriberFederate == NULL)
            {
              continue;
            }

            try
            {
              knownSubscriberClass = subscriberFederate->getObjectClass(*ito);
            }
            catch(...)
            {
              continue;
            }

            for (itPublishedRegion = publishedRegions.begin(); itPublishedRegion != publishedRegions.end(); itPublishedRegion++)
            {
              if (*itPublishedRegion == 0)
              {
                if (subscriberFederate->isSubscribedToObjectClassAttribute(knownSubscriberClass, *itOtherAttribute, true))
                {
                  gotAttribute = true;
                  break;
                }
              }
              else
              {
                region = runTimeObjectDB.getRegion(*itPublishedRegion);
                subscriberFederate->getSubscribedAttributeRegions(knownSubscriberClass, *itOtherAttribute, subscribedRegions, true);
                for (itSubscribedRegion = subscribedRegions.begin(); itSubscribedRegion != subscribedRegions.end(); itSubscribedRegion++)
                {
                  if (region->gotIntersection(*itSubscribedRegion))
                  {
                    gotAttribute = true;
                    break;
                  }
                }
              }
            }
            if (gotAttribute)
            {
              break;
            }

            // Not subscribed, check turned on flag.
            if (publisherFederate->testTurnedOn(*ito, *itOtherAttribute, subscriberFederate->getId()))
            {
              itSubscriber = sendAttributeSubscribers.find(*itOtherAttribute);
              if (itSubscriber != sendAttributeSubscribers.end())
              {
                GERTICO::HandleSet *subscribersPtr;
                subscribersPtr = &itSubscriber->second;
                subscribersPtr->insert(subscriberFederate->getId());
              }
              else
              {
                subscribers.insert(subscriberFederate->getId());
                sendAttributeSubscribers[*itOtherAttribute] = subscribers;
                subscribers.clear();
              }
            }
          }
          if (gotAttribute == false)
          {
            turnOffAttributes.insert(*itOtherAttribute);
          }
        }
        if (turnOffAttributes.size())
        {
//          pm.release();
//          doTurnOffForObjectInstanceXX(*ito, publisherFederate->getId(), turnOffAttributes, true);
//          pm.acquire();
          turnOffForObjectInstance = new TurnOffForObjectInstance(*itPublisherFederate, *ito, sendAttributeSubscribers, federatesHolder);
          federationJobs.add(turnOffForObjectInstance);
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
// NB. The search may be very slow for very large object class trees.
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::doTurnOffForObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::doTurnOffForObjectInstance", "enter");
                           #endif   // inserted by Gal converter
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::Federate *federate;
  GERTICO::Federate *federatePublisherPtr;
  GERTICO::Federate *workFed;
  GERTICO::HandleSet federatePublishers;
  GERTICO::HandleSet federateSubscribers;
  GERTICO::HandleSet otherAttributes;
  GERTICO::HandleSet otherObjects;
  GERTICO::HandleSet otherPublishedObjectClasses;
  GERTICO::HandleSet otherRegions;
  GERTICO::HandleSet subscribers;
  GERTICO::HandleSet workRegions;
  GERTICO::HandleSet::iterator itOtherAttribute;
  GERTICO::HandleSet::iterator itFederatePublisher;
  GERTICO::HandleSet::iterator itOtherObject;
  GERTICO::HandleSet::iterator itOtherPublishedObjectClass;
  GERTICO::HandleSet::iterator itOtherRegion;
  GERTICO::HandleSet::iterator itFederateSubscriberPtr;
  GERTICO::HandleSet::iterator itWorkRegion;
  GERTICO::HandleSetMap sendAttributeSubscribers;
  GERTICO::HandleSetSetMap turnOffAttributes;
  GERTICO::HandleSetMap::iterator itSubscriber;
  GERTICO::HandleSetSetMap::iterator itTurnOffAttributes;
  GERTICO::Region *workRegion;
  GERTICO::TurnOffForObjectInstance *turnOffForObjectInstance;
  GeRtiFactory::GeRtiHandle knownClass;
  GeRtiFactory::GeRtiHandle objectClass;
  GeRtiFactory::GeRtiHandle workKnownClass;
  bool gotAttributeSubscriber;

  federate = federatesHolder.getFederate(theFederate);
  if (federate == NULL)
  {
    return;
  }

  federatesHolder.getFederates(federatePublishers);
  federatesHolder.getFederates(federateSubscribers);
  for (itFederatePublisher = federatePublishers.begin(); itFederatePublisher != federatePublishers.end(); itFederatePublisher++)
  {
    if (*itFederatePublisher == theFederate)
    {
      continue;
    }
    federatePublisherPtr = federatesHolder.getFederate(*itFederatePublisher);
    if (federatePublisherPtr == NULL)
    {
      continue;
    }
    federatePublisherPtr->getPublishedObjectClasses(otherPublishedObjectClasses);
    for (itOtherPublishedObjectClass = otherPublishedObjectClasses.begin(); itOtherPublishedObjectClass != otherPublishedObjectClasses.end(); itOtherPublishedObjectClass++)
    {
      /*
      if (federatePublisherPtr->getStarted(*itOtherPublishedObjectClass) == false)
      {
        continue;
      }
      */

      turnOffAttributes.clear();
      federatePublisherPtr->getKnownObjects(*itOtherPublishedObjectClass, otherObjects);
      for (itOtherObject = otherObjects.begin(); itOtherObject != otherObjects.end(); itOtherObject++)
      {
        try
        {
          knownClass = federate->getObjectClass(*itOtherObject);
        }
        catch(...)
        {
          continue;
        }
        if (knownClass != theObjectClass)
        {
          continue;
        }
        runTimeObjectDB.getOwnedObjectAttributes(*itOtherObject, *itFederatePublisher, otherAttributes, false);
        for (itOtherAttribute = otherAttributes.begin(); itOtherAttribute != otherAttributes.end(); itOtherAttribute++)
        {
          try
          {
            attributeInfo = runTimeObjectDB.getObjectAttributeInfo(*itOtherObject, *itOtherAttribute);
          }
          catch(...)
          {
            continue;
          }

          if (federatePublisherPtr->testTurnedOn(*itOtherObject, *itOtherAttribute) == false)
          {
            continue;
          }

          gotAttributeSubscriber = false;
          for (itFederateSubscriberPtr = federateSubscribers.begin(); itFederateSubscriberPtr != federateSubscribers.end(); itFederateSubscriberPtr++)
          {
            if (*itFederateSubscriberPtr == *itFederatePublisher)
            {
              continue;
            }

            workFed = federatesHolder.getFederate(*itFederateSubscriberPtr);
            if (workFed == NULL)
            {
              continue;
            }

            try
            {
              workKnownClass = workFed->getObjectClass(*itOtherObject);
            }
            catch(...)
            {
              continue;
            }

            attributeInfo->getFedRegions(*itFederatePublisher, otherRegions);
            workFed->getSubscribedAttributeRegions(workKnownClass, *itOtherAttribute, workRegions, true);
            for (itWorkRegion = workRegions.begin(); itWorkRegion != workRegions.end(); itWorkRegion++)
            {
              if (*itWorkRegion == 0)
              {
                gotAttributeSubscriber = true;
                break;
              }
              else
              {
                workRegion = runTimeObjectDB.getRegion(*itWorkRegion);
                if (workRegion)
                {
                  for (itOtherRegion = otherRegions.begin(); itOtherRegion != otherRegions.end(); itOtherRegion++)
                  {
                    if (workRegion->gotIntersection(*itOtherRegion))
                    {
                      gotAttributeSubscriber = true;
                      break;
                    }
                  }
                }
              }
            }
            if (gotAttributeSubscriber)
            {
              // for work region loop
              break;
            }

            // Not subscribed, check turned on flag.
            if (federatePublisherPtr->testTurnedOn(*itOtherObject, *itOtherAttribute, workFed->getId()))
            {
              itTurnOffAttributes = turnOffAttributes.find(*itOtherObject);
              if (itTurnOffAttributes != turnOffAttributes.end())
              {
                GERTICO::HandleSetMap *attributeFederateLocalPtr;
                GERTICO::HandleSetMap::iterator itattributeFederateLocal;

                attributeFederateLocalPtr = &itTurnOffAttributes->second;
                itattributeFederateLocal = attributeFederateLocalPtr->find(*itOtherAttribute);
                if (itattributeFederateLocal != attributeFederateLocalPtr->end())
                {
                  GERTICO::HandleSet *federatesLocalPtr;
                  GERTICO::HandleSet::iterator itfederateLocal;

                  federatesLocalPtr = &itattributeFederateLocal->second;
                  itfederateLocal = federatesLocalPtr->find(workFed->getId());
                  if (itfederateLocal == federatesLocalPtr->end())
                  {
                    federatesLocalPtr->insert(workFed->getId());
                  }
                }
                else
                {
                  GERTICO::HandleSet federatesLocal;

                  federatesLocal.insert(workFed->getId());
                  (*attributeFederateLocalPtr)[*itOtherAttribute] = federatesLocal;
                }
              }
              else
              {
                GERTICO::HandleSet federatesLocal;
                GERTICO::HandleSetMap attributeFederateLocal;

                federatesLocal.insert(workFed->getId());
                attributeFederateLocal[*itOtherAttribute] = federatesLocal;
                turnOffAttributes[*itOtherObject] = attributeFederateLocal;
              }
              /*
              itSubscriber = sendAttributeSubscribers.find(*itOtherAttribute);
              if (itSubscriber != sendAttributeSubscribers.end())
              {
                GERTICO::HandleSet *subscribersPtr;
                subscribersPtr = &itSubscriber->second;
                subscribersPtr->insert(workFed->getId());
              }
              else
              {
                subscribers.insert(workFed->getId());
                sendAttributeSubscribers[*itOtherAttribute] = subscribers;
                subscribers.clear();
              }
              */
            }
          }
          /*
          if (gotAttributeSubscriber == false)
          {
            itTurnOffAttributes = turnOffAttributes.find(*itOtherObject);
            if (itTurnOffAttributes != turnOffAttributes.end())
            {
              itTurnOffAttributes->second.insert(*itOtherAttribute);
            }
            else
            {
              GERTICO::HandleSet localAttributes;
              localAttributes.insert(*itOtherAttribute);
              turnOffAttributes[*itOtherObject] = localAttributes;
            }
          }
          */
        }
      }
      for (itTurnOffAttributes = turnOffAttributes.begin(); itTurnOffAttributes != turnOffAttributes.end(); itTurnOffAttributes++)
      {
        objectClass = *itOtherPublishedObjectClass;
        turnOffForObjectInstance = new TurnOffForObjectInstance(*itFederatePublisher, itTurnOffAttributes->first, itTurnOffAttributes->second, federatesHolder);
        federationJobs.add(turnOffForObjectInstance);
      }
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::doTurnOffForObjectInstance", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::fillFedObjAttributes(GERTICO::HandleSetSetMap &theFedObjAttributes, GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
  GERTICO::HandleSet::iterator itSendAttributes;
  GERTICO::HandleSetMap *objectAttributesPtr;
  GERTICO::HandleSetMap::iterator itObjectAttributes;
  GERTICO::HandleSetSetMap::iterator itHSSM;

  itHSSM = theFedObjAttributes.find(theFederate);
  if (itHSSM != theFedObjAttributes.end())
  {
    objectAttributesPtr = &itHSSM->second;
    itObjectAttributes = objectAttributesPtr->find(theObject);
    if (itObjectAttributes != objectAttributesPtr->end())
    {
      GERTICO::HandleSet *sendAttributesPtr;
      sendAttributesPtr = &itObjectAttributes->second;
      itSendAttributes = sendAttributesPtr->find(theAttribute);
      if (itSendAttributes == sendAttributesPtr->end())
      {
        sendAttributesPtr->insert(theAttribute);
      }
    }
    else
    {
      GERTICO::HandleSet sendAttributes;
      sendAttributes.insert(theAttribute);
      (*objectAttributesPtr)[theObject] = sendAttributes;
    }
  }
  else
  {
    GERTICO::HandleSet sendAttributes;
    sendAttributes.insert(theAttribute);
    GERTICO::HandleSetMap sendObjectAttributes;
    sendObjectAttributes[theObject] = sendAttributes;
    theFedObjAttributes[theFederate] = sendObjectAttributes;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::fillHandleSetMap(GERTICO::HandleSetMap &theHandleSetMap, GeRtiFactory::GeRtiHandle const &theFirst, GeRtiFactory::GeRtiHandle const &theSecond)
{
  GERTICO::HandleSetMap::iterator itHandleSetMap;

  itHandleSetMap = theHandleSetMap.find(theFirst);
  if (itHandleSetMap != theHandleSetMap.end())
  {
    GERTICO::HandleSet *tmpHS;
    GERTICO::HandleSet::iterator itTmpHS;

    tmpHS = &itHandleSetMap->second;
    itTmpHS = tmpHS->find(theSecond);
    if (itTmpHS == tmpHS->end())
    {
      tmpHS->insert(theSecond);
    }
  }
  else
  {
    GERTICO::HandleSet tmpHS;
    tmpHS.insert(theSecond);
    theHandleSetMap[theFirst] = tmpHS;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegisteredObject *GERTICO::ObjectManagement::getObject(GeRtiFactory::GeRtiHandle const &objId)
{
  return registeredObjectsHolder.getObject(objId);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegisteredObject *GERTICO::ObjectManagement::getObjectByName(std::wstring const &theObjectName)
{
  GERTICO::RegisteredObject *ret = NULL;

  try
  {
    ret = registeredObjectsHolder.getObjectByName(theObjectName);
  }
  catch(...)
  {
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::getObjectIds(GERTICO::HandleSet &theObjects)
{
  registeredObjectsHolder.getObjectIds(theObjects);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::getOwnedObjectIds(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theObjects)
{
  registeredObjectsHolder.getOwnedObjectIds(theFederate, theObjects, privilegeToDeleteId);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ObjectManagement::getPrivilegeToDeleteId(void)
{
  return privilegeToDeleteId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::localDeleteObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::localDeleteObjectInstance", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"";
  GERTICO::Federate *federate;
  GERTICO::HandleSet attributes;
  GeRtiFactory::GeRtiHandle objectClass;
  GERTICO::RegisteredObject *registeredObject;
  std::wstring objectName;
  size_t size;

  pm.acquire();

  // Get the federate information.
  federate = federatesHolder.getFederate(theFederate);
  if (federate)
  {
    // Check if the federate owns any object attributes.
    try
    {
      runTimeObjectDB.getOwnedObjectAttributes(theObject, theFederate, attributes, true);
    }
    catch(...)
    {
      pm.release();
      throw;
    }
    size = attributes.size();
    if (size != 0)
    {
      pm.release();
      throw GeRtiFactory::FederateOwnsAttributes(wChar);
    }

    // Delete the known onject flag.
    try
    {
      federate->localDeleteObjectInstance(theObject);
    }
    catch(...)
    {
      pm.release();
      throw;
    }

    // May rediscover at same or different class.
    registeredObject = registeredObjectsHolder.getObject(theObject);
    registeredObject->getUnownedObjectAttributes(theFederate, attributes);
    objectClass = registeredObject->getClassId();
    registeredObject->getName(objectName);
    doDiscover(0, *federate, objectClass, *registeredObject, objectName, attributes);
  }

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::localDeleteObjectInstance", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::process(GERTICO::GeRtiFedTime const &theGalt)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::process", "enter");
                           #endif   // inserted by Gal converter
  ObjectTimeMap::iterator itOTM;
  GeRtiFactory::GeRtiHandle owner;
  RegisteredObject *object;
  GERTICO::GeRtiFedTime *currFedTime;

  for (itOTM = objectTimeMap.begin(); itOTM != objectTimeMap.end(); )
  {
    if (*itOTM->second <= theGalt)
    {
      try
      {
        object = registeredObjectsHolder.getObject(itOTM->first);
        object->getOwner(owner, privilegeToDeleteId);
        runTimeObjectDB.deleteObjectInstance(itOTM->first, owner);
      }
      catch(...)
      {
      }
      currFedTime = itOTM->second;
      objectTimeMap.erase(itOTM);
      delete currFedTime;
      itOTM = objectTimeMap.begin();
    }
    else
    {
      itOTM++;
    }
  }

  if (objectTimeMap.size())
  {
    ps.release();
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::process", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ObjectManagement::registerObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::registerObjectInstance", "enter");
                           #endif   // inserted by Gal converter
  GeRtiFactory::GeRtiHandle objId;
  char name[64];
  unsigned long ul;

  objId = idHandler.nextHandle();

  ul = objId;
  sprintf(name, "HLA%lu", ul);
  std::wstring sName;

  GERTICO::Mapper::mapWstringFromChar(sName, name);
  addObjectInstance(theFederate, theClass, objId, sName);

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::registerObjectInstance", "leave");
                           #endif   // inserted by Gal converter
  return objId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ObjectManagement::registerObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, std::wstring const &theObjectName)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::registerObjectInstanceWithName", "enter");
                           #endif   // inserted by Gal converter
  GeRtiFactory::GeRtiHandle objId;

  objId = idHandler.nextHandle();

  addObjectInstance(theFederate, theClass, objId, theObjectName);

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::registerObjectInstanceWithName", "leave");
                           #endif   // inserted by Gal converter
  return objId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::requestClassAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::requestClassAttributeValueUpdate", "enter");
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::Item *item;
  GERTICO::HandleSet feds;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator itFed;
  GERTICO::HandleSet::iterator ito;

  classDescr = runTimeObjectDB.getObjectClassDescr(theClass);
  if (classDescr == NULL)
  {
    throw GeRtiFactory::ObjectClassNotDefined(wChar);
  }

  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    item = classDescr->getClassItem(theAttributes[i]);
    if (item == NULL)
    {
      throw GeRtiFactory::AttributeNotDefined(wChar);
    }
  }

  pm.acquire();

  runTimeObjectDB.getObjectIdsForClass(theClass, objects);
  federatesHolder.getFederates(feds);
  for (itFed = feds.begin(); itFed != feds.end(); itFed++)
  {
#ifdef IEEE_1516
    if (*itFed == theFederate)
    {
      continue;
    }
#endif
    for (ito = objects.begin(); ito != objects.end(); ito++)
    {
      requestObjectAttributeValueUpdatePrivate(*itFed, *ito, theAttributes, theTag);
    }
  }

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::requestClassAttributeValueUpdate", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::requestObjectAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::requestClassAttributeValueUpdateObject", "enter");
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *federate;
  GERTICO::HandleSet feds;
  GERTICO::HandleSet::iterator itFed;
  GERTICO::Item *item;
  GeRtiFactory::GeRtiHandle myClassId;

  // Get the federate information.
  federate = federatesHolder.getFederate(theFederate);
  if (federate == NULL)
  {
    throw GeRtiFactory::RTIinternalError(wChar);
  }

  // Get the known object class handle.
  myClassId = federate->getObjectClass(theObject);

  // Get the object class information.
  classDescr = runTimeObjectDB.getObjectClassDescr(myClassId);

  // Check if object attribute is available at the known class.
  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    item = classDescr->getClassItem(theAttributes[i]);
    if (item == NULL)
    {
      // Attribute not defined.
      throw GeRtiFactory::AttributeNotDefined(wChar);
    }
  }

  pm.acquire();

  federatesHolder.getFederates(feds);
  for (itFed = feds.begin(); itFed != feds.end(); itFed++)
  {
#ifdef IEEE_1516
    if (*itFed == theFederate)
    {
      continue;
    }
#endif
    requestObjectAttributeValueUpdatePrivate(*itFed, theObject, theAttributes, theTag);
  }

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::requestClassAttributeValueUpdateObject", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::requestObjectAttributeValueUpdatePrivate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::requestObjectAttributeValueUpdatePrivate", "enter");
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::HandleSet attributesOwned;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet::iterator itAtt;
  GERTICO::ProvideUpdateJob *newProvideUpdate;

  runTimeObjectDB.getOwnedObjectAttributes(theObject, theFederate, attributesOwned, true);
  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    itAtt = attributesOwned.find(theAttributes[i]);
    if (itAtt != attributesOwned.end())
    {
      attributes.insert(theAttributes[i]);
    }
  }

  // Use only if some attribute(s) found.
  if (attributes.size())
  {
    newProvideUpdate = new GERTICO::ProvideUpdateJob(theObject, attributes, theTag, theFederate, federatesHolder);
    federationJobs.add(newProvideUpdate);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "ObjectManagement::requestObjectAttributeValueUpdatePrivate", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ObjectManagement::reserveObjectInstanceName(GeRtiFactory::GeRtiHandle const &theFederate, std::wstring const &theObjectInstanceName)
{
  GERTICO::ReserveObjectInstanceNameJob *reserveObjectInstanceNameJob = new GERTICO::ReserveObjectInstanceNameJob(federatesHolder, theFederate, theObjectInstanceName);
  registeredObjectsHolder.reserveObjectInstanceName(theObjectInstanceName);

  federationJobs.add(reserveObjectInstanceNameJob);
}

// ---------------------------------------------------------------------------
// Check if any attribute is subscribed (passive or active).
// ---------------------------------------------------------------------------
bool GERTICO::ObjectManagement::subscribedToAttributeWithRegion(GeRtiFactory::GeRtiHandle const &theCallingFederate, GeRtiFactory::GeRtiHandle const &theOtherFederate, GERTICO::RegisteredObject &theObject, GeRtiFactory::GeRtiHandle const &theTestClass, GERTICO::HandleSet &theAttributes, GERTICO::HandleSet &theRegions)
{
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet otherRegions;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap attributeRegions;
  bool ret;

  for (itAttribute = theAttributes.begin(); itAttribute != theAttributes.end(); itAttribute++)
  {
    attributes.clear();
    regions.clear();
    theObject.getFedAttRegions(theCallingFederate, *itAttribute, regions);
    for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
    {
      if (*itRegion == 0)
      {
        attributes.insert(*itAttribute);
        if (runTimeObjectDB.subscribedToAttribute(theOtherFederate, theTestClass, attributes))
        {
          return true;
        }
      }
    }
    otherRegions.clear();
    theObject.getFedAttRegions(theOtherFederate, *itAttribute, otherRegions);
    attributeRegions[*itAttribute] = otherRegions;
  }

  ret = runTimeObjectDB.subscribedToAttributeWithRegion(theOtherFederate, theTestClass, attributeRegions);

  return ret;
}
