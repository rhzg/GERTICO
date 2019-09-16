/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: DataDistributionManagement.cpp,v $
Revision 1.46  2009/09/23 08:03:27  mul
Add class description holder.

Revision 1.45  2009/08/17 10:30:44  mul
Minor changes.

Revision 1.44  2009/06/12 13:02:40  mul
Use thread mutex.

Revision 1.43  2009/01/26 10:52:51  mul
Changed names of some variables.

Revision 1.42  2007/09/25 08:44:14  mul
Changes for ddm.

Revision 1.41  2007/09/06 09:09:43  mul
Changes for ieee1516.

Revision 1.40  2007/06/28 10:19:52  mul
Remove some functions.

Revision 1.39  2007/06/26 08:38:44  mul
Changes for ieee1516.

Revision 1.38  2007/06/08 12:43:55  mul
Changes for ieee1516.

Revision 1.37  2007/05/03 15:09:27  mul
Add wchar parameter to exception constructor.

Revision 1.36  2007/03/12 13:39:18  mul
Changed string to wstring.

Revision 1.35  2007/03/06 09:31:23  mul
Changes for ieee conversion.

Revision 1.34  2006/12/18 10:15:12  mul
Minor changes.

Revision 1.33  2006/11/30 11:14:22  mul
Changes for testcases.

Revision 1.32  2006/11/29 11:26:24  mul
Fix for testcases.

Revision 1.31  2006/11/28 16:03:27  mul
Use object management.

Revision 1.30  2006/11/15 11:15:49  mul
Minor changes.

Revision 1.29  2006/10/31 13:55:28  mul
Add more checks.

Revision 1.28  2006/10/16 14:38:21  mul
Fix associate region for updates logic.

Revision 1.27  2006/10/12 14:00:23  mul
Fix scope logic.

Revision 1.26  2006/09/12 11:42:53  mul
Changes for phase 5 testcases.

Revision 1.25  2006/08/30 11:54:30  mul
Add federates holder.

Revision 1.24  2006/08/25 08:49:57  mul
Changes for phase 4 testcases.

Revision 1.23  2006/08/23 11:19:27  mul
Changes for phase 4 testcases.

Revision 1.22  2006/08/22 08:50:14  mul
Changes for phase 4 testcases.

Revision 1.21  2006/08/21 07:07:04  mul
Changes for phase 4 testcases.

Revision 1.20  2006/08/18 13:02:48  mul
Changes for phase 4 testcases.

Revision 1.19  2006/08/15 12:56:38  mul
Changes for phase 4 tests.

Revision 1.18  2006/07/07 07:00:05  mul
Add one parameter to method.

Revision 1.17  2006/07/05 09:23:57  mul
Fix mutex problem.

Revision 1.16  2006/07/03 13:53:30  mul
Fix logic for turn on/off.

Revision 1.15  2006/06/28 14:24:53  mul
Fix in/out scope logic.

Revision 1.14  2006/06/27 14:31:16  mul
Fix turn-on logic.

Revision 1.13  2006/06/27 07:10:55  mul
Fix region logic.

Revision 1.12  2006/06/23 14:14:25  mul
Changes for in-scope.

Revision 1.11  2006/06/12 09:10:52  mul
Fix default parameter for linux.

Revision 1.10  2006/05/17 06:34:48  mul
Set assignment of turn-on responsibility to object management.

Revision 1.9  2006/03/17 12:19:10  mul
Fix logic for data distribution.

Revision 1.8  2006/02/28 08:25:13  mul
Add check whether federate knows the object.

Revision 1.7  2006/02/27 14:43:41  mul
Fix region handling.

Revision 1.6  2005/10/05 10:07:43  mul
Remove provide handler.

Revision 1.5  2005/09/27 11:57:34  mul
Changes for standardized callback logic.

Revision 1.4  2005/09/22 14:00:07  mul
Move some code from run time object database.

Revision 1.3  2005/09/20 14:47:45  mul
Reorganize some code from run time object dictionary.

Revision 1.2  2005/09/19 08:11:20  mul
Fix some memory handling problems.

Revision 1.1  2005/09/09 11:54:59  mul
Files from EventMarket directory.


**
*******************************************************************************/

#include "DataDistributionManagement.h"
#include "EventMarket/Jobs.h"
#include "Util/Mapper.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DataDistributionManagement::DataDistributionManagement(GERTICO::DeclarationManagementRTI &theDeclarationManagement, GERTICO::ObjectManagement &theObjectManagement, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::FederatesHolder &theFederatesHolder, GERTICO::ObjectModel &theObjectModel, GERTICO::NextHandle &theIdHandler, GERTICO::JobHolder &theFederationJobs, ACE_Thread_Mutex &thePm) : pm (thePm), declarationManagement (theDeclarationManagement), federatesHolder(theFederatesHolder), federationJobs (theFederationJobs), idHandler (theIdHandler), objectManagement(theObjectManagement), objectModel (theObjectModel), runTimeObjectDB (theRunTimeObjectDB)
{
  // Get privilege to delete id.
  privilegeToDeleteId = runTimeObjectDB.getPrivilegeToDeleteId();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::DataDistributionManagement::~DataDistributionManagement (void)
{
}

// ---------------------------------------------------------------------------
// For all objects below this object class level.
// Find any objects which may generate events and
// send a discover object to this federate.
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::addSubscribeDiscoverObjects(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClassId, GERTICO::HandleSetMap &theAttRegMap)
{
  GERTICO::Federate *federate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet feds;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet regionIntersections;
  GERTICO::HandleSet::iterator ito;
  GERTICO::HandleSet::iterator itr;
  GERTICO::HandleSet::iterator itRegions;
  GERTICO::HandleSet::iterator itRegionsIn;
  GERTICO::HandleSetMap::iterator itAttRegMap;
  GERTICO::Region *currRegion;

  std::string oName;

  // Get the federate attributes for this fed.
  federate = federatesHolder.getFederate(theFederate);
  if (federate == NULL)
  {
    return;
  }

  federate->setAlive();

  for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
  {
    for (itRegionsIn = itAttRegMap->second.begin(); itRegionsIn != itAttRegMap->second.end(); itRegionsIn++)
    {
      itRegions = regions.find(*itRegionsIn);
      if (itRegions == regions.end())
      {
        regions.insert(*itRegionsIn);
      }
    }
  }

  for (itRegions = regions.begin(); itRegions != regions.end(); itRegions++)
  {
    // Get region information.
    currRegion = runTimeObjectDB.getRegion(*itRegions);
    if (currRegion == NULL)
    {
      continue;
    }

    // Get all region intersections with other regions.
    currRegion->getIntersectionSet(regionIntersections);
    if (regionIntersections.size() == 0)
    {
      continue;
    }

    // For the specified region
    // Get the objects in the intersections to other regions.
    for (itr = regionIntersections.begin(); itr != regionIntersections.end(); itr++)
    {
      filterSubscribeDiscoverObjects(theFederate, *federate, theClassId, theAttRegMap, *itr);
    }
  }

  // For the default region
  filterSubscribeDiscoverObjects(theFederate, *federate, theClassId, theAttRegMap, 0);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::addToHandleSetSetMap(GERTICO::HandleSetSetMap &theFedObjsAtts, const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute)
{
  GERTICO::HandleSetSetMap::iterator itFedObjsAtts;

  itFedObjsAtts = theFedObjsAtts.find(theFederate);
  if (itFedObjsAtts != theFedObjsAtts.end())
  {
    GERTICO::HandleSetMap *objectAttsPtr;
    GERTICO::HandleSetMap::iterator itObject;

    objectAttsPtr = &itFedObjsAtts->second;
    itObject = objectAttsPtr->find(theObject);
    if (itObject != objectAttsPtr->end())
    {
      GERTICO::HandleSet *attributePtr;
      GERTICO::HandleSet::iterator itAttribute;

      attributePtr = &itObject->second;
      itAttribute = attributePtr->find(theAttribute);
      if (itAttribute == attributePtr->end())
      {
        attributePtr->insert(theAttribute);
      }
    }
    else
    {
      GERTICO::HandleSet attributes;

      attributes.insert(theAttribute);
      (*objectAttsPtr)[theObject] = attributes;
    }
  }
  else
  {
    GERTICO::HandleSet attributes;
    GERTICO::HandleSetMap objects;

    attributes.insert(theAttribute);
    objects[theObject] = attributes;
    theFedObjsAtts[theFederate] = objects;
  }
}

// ---------------------------------------------------------------------------
// Add attribute/region pairs to the object.
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::associateRegionsForUpdates(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSetMap &theAttributeRegions)
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *federate;
  GERTICO::HandleSetMap federateAttributesBefore;
  GERTICO::HandleSetMap::iterator itAttributeReg;
  GERTICO::Item *item;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle knownClass;

  // Get object.
  registeredObject = objectManagement.getObject(theObject);

  // Find the desired federate.
  federate = federatesHolder.getFederate(theFederate);
  // Check if object is known.
  knownClass = federate->getObjectClass(theObject);

#ifdef IEEE_1516
  // Atomic test.
  runTimeObjectDB.testRegionDimensions(knownClass, theAttributeRegions);
#endif

  classDescr = runTimeObjectDB.getObjectClassDescr(knownClass);

  // Check if attributes are available at the known class.
  for (itAttributeReg = theAttributeRegions.begin(); itAttributeReg != theAttributeRegions.end(); itAttributeReg++)
  {
    item = classDescr->getClassItem(itAttributeReg->first);
    if (item == NULL)
    {
      throw GeRtiFactory::AttributeNotDefined(L"associateRegionForUpdates");
    }
  }

  // Update the object data base.
  pm.acquire();
  try
  {
    getObjectAttributesInScope(theFederate, *registeredObject, federateAttributesBefore);
    runTimeObjectDB.associateRegionForUpdates(theFederate, theObject, theAttributeRegions);
  }
  catch(...)
  {
    pm.release();
    throw;
  }

  federate->print();
  federate->associateRegionForUpdates(theObject, theAttributeRegions);
  federate->setAlive();
  federate->print();

  // Do discover.
  objectManagement.doDiscoverObject(theFederate, theObject);

  // Do any in/out of scope.
  objectManagement.doScopeAssociate(theFederate, *registeredObject, federateAttributesBefore);

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::DataDistributionManagement::checkUnowned(GERTICO::RegisteredObject &theRegisteredObject, GERTICO::HandleSetMap &theAttRegMap)
{
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::HandleSetMap::iterator itAttRegMap;

  for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
  {
    try
    {
      attributeInfo = theRegisteredObject.getAttribute(itAttRegMap->first);
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
GeRtiFactory::GeRtiHandle GERTICO::DataDistributionManagement::createRegion (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theSpace, const CORBA::ULong &numberOfExtents, const GERTICO::HandleSet & theDimensions)
{
  GeRtiFactory::GeRtiHandle id;

  pm.acquire ();
  try
  {
    id = idHandler.nextHandle();
    runTimeObjectDB.createRegion(theFederate, theSpace, numberOfExtents, theDimensions, id);
  }
  catch (...)
  {
    pm.release ();
    throw;
  }
  pm.release ();

  return id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::deleteRegion (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion)
{
  CORBA::WChar *wChar = L"deleteRegion";
  GERTICO::Federate *federate;

  // Find the desired federate.
  federate = federatesHolder.getFederate(theFederate);
  if (federate)
  {
    federate->setAlive();
    // Check if any object instance attribute is subscribed in the region.
    if (isRegionSubscribed (theFederate, theRegion))
    {
      throw GeRtiFactory::RegionInUse(wChar);
    }
  }

  pm.acquire ();

  try
  {
    runTimeObjectDB.deleteRegion (theRegion);
  }
  catch (...)
  {
    pm.release ();
    throw;
  }

  pm.release ();
}

// ---------------------------------------------------------------------------
// For each object in the given class, send a discover object request to
// each federate ambassador except to the owner federate ambassador.
// ---------------------------------------------------------------------------
/*
void GERTICO::DataDistributionManagement::doDiscoverRegister(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSetMap &theAttRegMap)
{
  GERTICO::HandleSet otherRegions;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap regAttMap;
  GERTICO::HandleSetMap::iterator itFederateRegions;
  GERTICO::Region *otherRegionPtr;
  GERTICO::Region *regionPtr;

  // Map attributes to regions, instead of regions to attributes.
  reMap(regAttMap, theAttRegMap);

  // Loop over regions.
  for (itFederateRegions = regAttMap.begin(); itFederateRegions != regAttMap.end(); itFederateRegions++)
  {
    if (itFederateRegions->first == 0)
    {
      // Default region.
      otherRegions.clear();
      otherRegions.insert(0);
    }
    else
    {
      // Get adjoining regions.
      regionPtr = runTimeObjectDB.getRegion(itFederateRegions->first);
      regionPtr->getIntersectionSet(otherRegions);
    }

    // Loop over adjoining regions.
    for (itRegion = otherRegions.begin(); itRegion != otherRegions.end(); itRegion++)
    {
      if (*itRegion == 0)
      {
        GERTICO::HandleSet tmpFederates;
        GERTICO::HandleSet::iterator itTmpFederate;

        getFederates(tmpFederates);
        for (itTmpFederate = tmpFederates.begin(); itTmpFederate != tmpFederates.end(); itTmpFederate++)
        {
          doFederateDiscover(*itTmpFederate, theObject, 0, itFederateRegions->second);
        }
      }
      else
      {
        otherRegionPtr = runTimeObjectDB.getRegion(*itRegion);
        doFederateDiscover(otherRegionPtr->getFederateId(), theObject, *itRegion, itFederateRegions->second);
      }
    }
  }
}
*/

/*
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::doFederateDiscover(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theRegion, GERTICO::HandleSet &theAttributes)
{
  AttributeInfo *attributeInfoPtr;
  GERTICO::HandleSet ownedAttributes;
  GERTICO::DiscoverObjectJob *newDiscoverObject;
  GERTICO::Federate *federate;
  GERTICO::RegisteredObject *currObject;
  GeRtiFactory::GeRtiHandle objectClass;
  GeRtiFactory::GeRtiHandle ownerFederate;
  bool found = false;
  std::string objectName;
  unsigned long testClass;

  federate = getFederate(theFederate);

  // Federate already knows the object.
  if (federate->knowObject(theObject))
  {
    return;
  }

  // Get object attributes.
  currObject = runTimeObjectDB.getObject(theObject);
  if (currObject)
  {
    objectClass = currObject->getClassId();
    currObject->getName(objectName);
    attributeInfoPtr = currObject->getAttribute(privilegeToDeleteId);
    ownerFederate = attributeInfoPtr->getFederate();
    currObject->getOwnedAttributes(ownerFederate, privilegeToDeleteId, ownedAttributes, true);
  }
  else
  {
    return;
  }

  testClass = objectClass;
  for (;;)
  {
    // This is a check if the federate subscribes to any class attribute.
    if (federate->isSubscribedToObjectClassAttributes(testClass, theRegion, theAttributes))
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
    GERTICO::HandleSet attributes;
    GERTICO::HandleSet subscribedAttributes;
    GERTICO::HandleSet::iterator itAttribute;
    GERTICO::HandleSet::iterator itOwnedAttribute;
    GERTICO::HandleSet::iterator itSubscribedAttribute;
    GERTICO::HandleSet regions;
    GERTICO::HandleSet::iterator itRegions;
    newDiscoverObject = new GERTICO::DiscoverObjectJob(testClass, federate->getId(), theObject, federateMap, objectName, pm);
    federationJobs.add(newDiscoverObject);
    federate->getSubscribedRegions(testClass, regions);
    for (itRegions = regions.begin(); itRegions != regions.end(); itRegions++)
    {
      federate->getSubscribedRegionAttributes(testClass, *itRegions, subscribedAttributes);
      for (itSubscribedAttribute = subscribedAttributes.begin(); itSubscribedAttribute != subscribedAttributes.end(); itSubscribedAttribute++)
      {
        itOwnedAttribute = ownedAttributes.find(*itSubscribedAttribute);
        if (itOwnedAttribute != ownedAttributes.end())
        {
          itAttribute = attributes.find(*itSubscribedAttribute);
          if (itAttribute == attributes.end())
          {
            attributes.insert(*itSubscribedAttribute);
          }
        }
      }
    }
    federate->addKnownObject(theObject, testClass, ownedAttributes);
  }
}
*/
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::filterSubscribeDiscoverObjects(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::Federate &theFed, const GeRtiFactory::GeRtiHandle &theClassId, GERTICO::HandleSetMap &theAttRegMap, const GeRtiFactory::GeRtiHandle &theRegion)
{
  GERTICO::DiscoverObjectJob *newDiscoverObject;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator ito;
  GERTICO::Region *otherRegion;
  GERTICO::RegisteredObject *currObject;
  std::wstring oName;

  // For a specified region or default region
  if (theRegion)
  {
    otherRegion = runTimeObjectDB.getRegion(theRegion);
    otherRegion->getObjects(objects);
  }
  else
  {
    runTimeObjectDB.getObjectIdsForClass(theClassId, objects);
  }

  for (ito = objects.begin(); ito != objects.end(); ito++)
  {
    // Federate already knows the object.
    if (theFed.knowObject(*ito))
    {
      continue;
    }

    // Get the object
    try
    {
      currObject = objectManagement.getObject(*ito);
    }
    catch(...)
    {
      continue;
    }

    // Do not discover unowned objects testcase 6-11-3
    if (checkUnowned(*currObject, theAttRegMap))
    {
      continue;
    }

    // Test if the federate has a subscription at a lower level.
    // If yes, do not do discover!!
    // see testcase 6-2-2-3
    if (declarationManagement.testFederateLowerSubscription(theFed, currObject->getClassId(), theClassId))
    {
      continue;
    }

    // Get the object
    if (currObject)
    {
      if (theRegion)
      {
        currObject->getFederateObjectAttributes(otherRegion->getFederateId(), attributes, theRegion);
        if (testIntersection(theAttRegMap, attributes))
        {
          currObject->getName(oName);
          // NB. use the class id known to the subscriber!
          newDiscoverObject = new GERTICO::DiscoverObjectJob(theClassId, theFed.getId(), *ito, federatesHolder, oName);
          federationJobs.add(newDiscoverObject);
          theFed.addKnownObject(*ito, theClassId, attributes);
        }
      }
      else
      {
        GERTICO::HandleSet otherAttributes;
        theFed.getSubscribedAttributes(theClassId, attributes);
//        currObject->getFederateObjectAttributes(theFederate, otherAttributes, theRegion);
        currObject->getNotFederateObjectAttributes(theFederate, otherAttributes);
        if (testIntersectionSets(otherAttributes, attributes))
        {
          currObject->getName(oName);
          // NB. use the class id known to the subscriber!
          newDiscoverObject = new GERTICO::DiscoverObjectJob(theClassId, theFed.getId(), *ito, federatesHolder, oName);
          federationJobs.add(newDiscoverObject);
          theFed.addKnownObject(*ito, theClassId, attributes);
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::getObjectAttributesInScope(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::RegisteredObject &theRegisteredObject, GERTICO::HandleSetMap &theFederateAttributes)
{
  GERTICO::Federate *federate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  GeRtiFactory::GeRtiHandle objectId = theRegisteredObject.getId();

  federatesHolder.getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    // Do not take the current federate.
    if (*itFederate == theFederate)
    {
      continue;
    }

    // Cycle through the other federates.
    federate = federatesHolder.getFederate(*itFederate);
    federate->getInScope(objectId, attributes);
    federate->setAlive();
    if (attributes.size())
    {
      theFederateAttributes[*itFederate] = attributes;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::getRequestUpdateFedObjsAtts(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, const GERTICO::HandleSet &theAttributes, GERTICO::Region &theRegion, GERTICO::HandleSetSetMap &theFedObjsAtts)
{
  GERTICO::AttributeInfo *currAttributeInfoPtr;
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::const_iterator itTheAttribute;
  GERTICO::HandleSet::iterator itObject;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::Region *currRegionPtr;
  GERTICO::RegisteredObject *currRegisteredObjectPtr;
  GeRtiFactory::GeRtiHandle federate;
  GeRtiFactory::GeRtiHandle objectClass;

  // GeRtiHandle attributes which are in the ajoining regions.
  theRegion.getIntersectionSet(regions);

  regions.insert(theRegion.getId());
  for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
  {
    currRegionPtr = runTimeObjectDB.getRegion(*itRegion);
    federate = currRegionPtr->getFederateId();
    currRegionPtr->getObjects(objects);
    for (itObject = objects.begin(); itObject != objects.end(); itObject++)
    {
      try
      {
        currRegisteredObjectPtr = objectManagement.getObject(*itObject);
      }
      catch(...)
      {
        continue;
      }
      currRegisteredObjectPtr->getFedRegionOwnedAtts(federate, *itRegion, attributes);
      for (itTheAttribute = theAttributes.begin(); itTheAttribute != theAttributes.end(); itTheAttribute++)
      {
        itAttribute = attributes.find(*itTheAttribute);
        if (itAttribute != attributes.end())
        {
          addToHandleSetSetMap(theFedObjsAtts, federate, *itObject, *itAttribute);
        }
      }
    }
  }

  // GeRtiHandle attributes which are in the default region.
  objectManagement.getObjectIds(objects);
  for (itObject = objects.begin(); itObject != objects.end(); itObject++)
  {
    try
    {
      currRegisteredObjectPtr = objectManagement.getObject(*itObject);
    }
    catch(...)
    {
      continue;
    }
    objectClass = currRegisteredObjectPtr->getClassId();
    classDescr = runTimeObjectDB.getObjectClassDescr(objectClass);
    if (classDescr->isDerivedClass(theClass) == false)
    {
      continue;
    }
    currRegisteredObjectPtr->getDefaultRegionAtts(attributes);
    for (itTheAttribute = theAttributes.begin(); itTheAttribute != theAttributes.end(); itTheAttribute++)
    {
      itAttribute = attributes.find(*itTheAttribute);
      if (itAttribute != attributes.end())
      {
        currAttributeInfoPtr = currRegisteredObjectPtr->getAttribute(*itAttribute);
        addToHandleSetSetMap(theFedObjsAtts, currAttributeInfoPtr->getFederate(), *itObject, *itAttribute);
      }
    }
  }
}

// ---------------------------------------------------------------------------
// Check whether an object instance attribute is subscribed for any object in
// the given region.
// ---------------------------------------------------------------------------
bool GERTICO::DataDistributionManagement::isRegionSubscribed (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion)
{
  if (runTimeObjectDB.isRegionSubscribed (theFederate, theRegion))
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::modifyRegion (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::Extents &theExtents)
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::DiscoverObjectJob *newDiscoverObject;
  GERTICO::Federate *federate;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet attributeIds;
  GERTICO::HandleSet inScopeSubscribers;
  GERTICO::HandleSet objectSet;
  GERTICO::HandleSet outScopeSubscribers;
  GERTICO::HandleSet regionsBefore;
  GERTICO::HandleSet regionsAfter;
  GERTICO::HandleSet subscribersAfter;
  GERTICO::HandleSet subscribersBefore;
  GERTICO::HandleSet subscribedRegions;
  GERTICO::HandleSet::iterator itAttributeId;
  GERTICO::HandleSet::iterator itHSatt;
  GERTICO::HandleSet::iterator itHSobj;
  GERTICO::HandleSet::iterator itHSreg;
  GERTICO::HandleSetMap objectAttributes;
  GERTICO::Region *currRegion;
  GERTICO::Region *tmpRegion;
  GERTICO::RegisteredObject *currObject;
  GeRtiFactory::GeRtiHandle object;
  GeRtiFactory::GeRtiHandle region;
  std::wstring sName;
  unsigned int found;
  unsigned long ulClass;
  pm.acquire ();

  // Get the region
  currRegion = runTimeObjectDB.getRegion(theRegion);
  if (currRegion == NULL)
  {
    pm.release ();
    throw GeRtiFactory::RegionNotKnown(L"modifyRegion");
  }

  currRegion->getIntersectionSet(regionsBefore);
  updateScopeFlags(theRegion, regionsBefore);

  // Change the database information.
  runTimeObjectDB.modifyRegion (theFederate, theRegion, theExtents);
  currRegion->getIntersectionSet(regionsAfter);

  // Find the federate - do any discover object for other federates.
  federate = federatesHolder.getFederate(theFederate);
  if (federate)
  {
    // Get all objects for this federate.
    objectManagement.getOwnedObjectIds(theFederate, objectSet);
    // Loop through all the federate's objects.
    for (itHSobj = objectSet.begin (); itHSobj != objectSet.end (); itHSobj++)
    {
      object = *itHSobj;
      objectManagement.doDiscoverObject(theFederate, object);
    }
  }

  // Check if the current federate has to discover any objects.
  for (itHSreg = regionsAfter.begin(); itHSreg != regionsAfter.end(); itHSreg++)
  {
    region = *itHSreg;
    tmpRegion = runTimeObjectDB.getRegion(region);
    tmpRegion->getObjects(objectSet);
    for (itHSobj = objectSet.begin(); itHSobj != objectSet.end(); itHSobj++)
    {
      object = *itHSobj;
      if (federate->knowObject(object))
      {
        continue;
      }
      try
      {
        found = 0;
        currObject = objectManagement.getObject(object);
        ulClass = currObject->getClassId();
        currObject->getAttributeIds(attributeIds);
        classDescr = runTimeObjectDB.getObjectClassDescr(ulClass);
        while (classDescr)
        {
          ulClass = classDescr->getId();
          for (itAttributeId = attributeIds.begin(); itAttributeId != attributeIds.end(); itAttributeId++)
          {
            if (federate->isSubscribedToObjectClassRegionAttribute(ulClass, theRegion, *itAttributeId))
            {
              currObject->getName(sName);
              newDiscoverObject = new GERTICO::DiscoverObjectJob(ulClass, federate->getId(), object, federatesHolder, sName);
              federationJobs.add(newDiscoverObject);
              federate->getSubscribedRegionAttributes(ulClass, theRegion, attributes);
              federate->addKnownObject(currObject->getId(), ulClass, attributes);
              found = 1;
              break;
            }
          }
          if (found)
          {
            break;
          }
          classDescr = classDescr->parent;
        }
      }
      catch(...)
      {
        continue;
      }
    }
  }

  // Check if regions now overlap
  // Send in scope
  //
  // Check if regions no longer overlap.
  // Send out of scope
  objectManagement.doScopeModify(theFederate, theRegion, regionsBefore, regionsAfter);

  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::DataDistributionManagement::registerObjectInstanceWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSetMap &theAttributeRegions)
{
  GeRtiFactory::GeRtiHandle objId;
  char name[64];
  std::wstring sName;
  unsigned long ul;

  objId = idHandler.nextHandle ();

  ul = objId;
  sprintf (name, "HLA%lu", ul);
  GERTICO::Mapper::mapWstringFromChar(sName, name);

  objectManagement.addObjectInstance(theFederate, theClass, objId, sName, theAttributeRegions);

  return objId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::DataDistributionManagement::registerObjectInstanceWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, const std::wstring &theObjectName, GERTICO::HandleSetMap &theAttributeRegions)
{
  GERTICO::HandleSetMap attRegMap;
  GeRtiFactory::GeRtiHandle objId;

  objId = idHandler.nextHandle ();

  objectManagement.addObjectInstance(theFederate, theClass, objId, theObjectName, theAttributeRegions);

  return objId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::reMap(GERTICO::HandleSetMap &theRegAttMap, GERTICO::HandleSetMap &theAttRegMap)
{
  GERTICO::HandleSet *regionsPtr;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSetMap::iterator itAttRegMap;
  GERTICO::HandleSetMap::iterator itRegMAttap;

  // For all in attribute-regions.
  for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
  {
    // For all in regions.
    regionsPtr = &itAttRegMap->second;
    for (itRegion = regionsPtr->begin(); itRegion != regionsPtr->end(); itRegion++)
    {
      itRegMAttap = theRegAttMap.find(*itRegion);
      if (itRegMAttap == theRegAttMap.end())
      {
        GERTICO::HandleSet tmpAttributes;
        tmpAttributes.insert(itAttRegMap->first);
        theRegAttMap[*itRegion] = tmpAttributes;
      }
      else
      {
        GERTICO::HandleSet *tmpAttributesPtr;
        tmpAttributesPtr = &itRegMAttap->second;
        tmpAttributesPtr->insert(itAttRegMap->first);
      }
    }
  }
}

// ---------------------------------------------------------------------------
// What logic can be used to find the region overlaps?
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::requestAttributeValueUpdateWithRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, const GERTICO::HandleSetMap &theAttributeRegions, const GeRtiFactory::UserSuppliedTag &theTag)
{
  GERTICO::HandleSetMap *objectsPtr;
  GERTICO::HandleSetMap regionAttributes;
  GERTICO::HandleSetMap::iterator itObjects;
  GERTICO::HandleSetMap::iterator itRegionAttributes;
  GERTICO::HandleSetSetMap fedObjsAtts;
  GERTICO::HandleSetSetMap::iterator itFedObjsAtts;
  GERTICO::ProvideUpdateJob *newProvideUpdate;
  GERTICO::Region *currRegion;
  GeRtiFactory::GeRtiHandle regionSpace;

#ifdef IEEE_1516
  // Atomic test.
  runTimeObjectDB.testRegionDimensions(theClass, theAttributeRegions);
#endif

  GERTICO::Mapper::mapHandleSetMapInvert(regionAttributes, theAttributeRegions);

  for (itRegionAttributes = regionAttributes.begin(); itRegionAttributes != regionAttributes.end(); itRegionAttributes++)
  {
    // The region narrows the possible federates.
    currRegion = runTimeObjectDB.getRegion(itRegionAttributes->first);
    if (currRegion == NULL)
    {
      throw GeRtiFactory::RegionNotKnown(L"invalid region");
    }

    // testcase 9-9-6
    // Check if attribute in space.
    regionSpace = currRegion->getSpace();
    runTimeObjectDB.checkAttributesInSpace(regionSpace, theClass, itRegionAttributes->second);

    getRequestUpdateFedObjsAtts(theFederate, theClass, itRegionAttributes->second, *currRegion, fedObjsAtts);
  }

  pm.acquire();

  for (itFedObjsAtts = fedObjsAtts.begin(); itFedObjsAtts != fedObjsAtts.end(); itFedObjsAtts++)
  {
#ifdef IEEE_1516
    // Do not send to the same federate.
    if (itFedObjsAtts->first == theFederate)
    {
      continue;
    }
#endif
    objectsPtr = &itFedObjsAtts->second;
    for (itObjects = objectsPtr->begin(); itObjects != objectsPtr->end(); itObjects++)
    {
      newProvideUpdate = new GERTICO::ProvideUpdateJob(itObjects->first, itObjects->second, theTag, itFedObjsAtts->first, federatesHolder);
      federationJobs.add(newProvideUpdate);
    }
  }

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::subscribeInteractionClass(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theInteraction, const CORBA::Boolean &theActive, const GERTICO::HandleSet &theRegions)
{
  declarationManagement.subscribeInteractionClass(theFederate, theInteraction, theActive, theRegions);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::subscribeObjectClassAttributesWithRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSetMap &theAttRegMap, const CORBA::Boolean &theActive)
{
  CORBA::ULong i;
  GERTICO::Federate *federate;
  GERTICO::HandleSet inAttributes;
  GERTICO::HandleSetMap::iterator itAttRegMap;

  if (theActive != 0 && theActive != 1)
  {
    throw GeRtiFactory::RTIinternalError(L"invalid active boolean");
  }

#ifdef IEEE_1516
  // Atomic test.
  runTimeObjectDB.testRegionDimensions(theObjectClass, theAttRegMap);
#endif

  pm.acquire();

  // Store the subscription information.
  try
  {
    runTimeObjectDB.subscribeObjectClassAttributesWithRegion(theFederate, theObjectClass, theAttRegMap, theActive);
  }
  catch(...)
  {
    pm.release();
    throw;
  }

  // Find federate attribute entry.
  federate = federatesHolder.getFederate(theFederate);
  if (federate == NULL)
  {
    pm.release();
    return;
  }

  // Add to federate information.
  federate->addSubscribeObjectClassRegion(theObjectClass, theAttRegMap, theActive);

  for (i = 0, itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); i++, itAttRegMap++)
  {
    inAttributes.insert(itAttRegMap->first); 
  }
  if (theActive)
  {
    // Logic to start registration for object class.
    declarationManagement.objectClassSubStartRegistration(theFederate, inAttributes, theObjectClass);
  }

  // Discover any objects on this or lower levels.
  addSubscribeDiscoverObjects(theFederate, theObjectClass, theAttRegMap);

  // Send in scope if required.
  objectManagement.doScopeSubscribe(theFederate, theObjectClass, true);

  if (theActive)
  {
    objectManagement.doTurnOnForSubscribedClass(*federate, theObjectClass, theAttRegMap);

    objectManagement.doTurnOffForSubscribedClass(*federate, theObjectClass);
  }
  else
  {
    objectManagement.doTurnOffForSubscribedClass(*federate, theObjectClass);

    // Logic to stop registration for object class.
//    declarationManagement.objectClassSubStopRegistration(theFederate, theObjectClass);
  }

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::DataDistributionManagement::testIntersectionSets(GERTICO::HandleSet &theAttributes, GERTICO::HandleSet &theTestAttributes)
{
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itTest;
  bool ret = false;

  for (itAttribute = theAttributes.begin(); itAttribute != theAttributes.end(); itAttribute++)
  {
    itTest = theTestAttributes.find(*itAttribute);
    if (itTest != theTestAttributes.end())
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::DataDistributionManagement::testIntersection(GERTICO::HandleSetMap &theAttRegMap, GERTICO::HandleSet &theTestAttributes)
{
  GERTICO::HandleSet::iterator itTest;
  GERTICO::HandleSetMap::iterator itAttRegMap;
  bool ret = false;

  for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
  {
    itTest = theTestAttributes.find(itAttRegMap->first);
    if (itTest != theTestAttributes.end())
    {
      return true;
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::unassociateRegionForUpdates (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::GeRtiHandle &theObject)
{
  GERTICO::Federate *federate;
  GERTICO::HandleSetMap federateAttributesBefore;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle objectClass;

  federate = federatesHolder.getFederate(theFederate);;
  if (federate)
  {
    objectClass = federate->getObjectClass(theObject);
    federate->unassociateRegionForUpdates(theObject, theRegion);
  }

  // Get object.
  registeredObject = objectManagement.getObject(theObject);

  getObjectAttributesInScope(theFederate, *registeredObject, federateAttributesBefore);
  runTimeObjectDB.unassociateRegionForUpdates (theFederate, theRegion, theObject);

  objectManagement.doDiscoverObject(theFederate, theObject);

  // Do any in/out of scope.
  objectManagement.doScopeAssociate(theFederate, *registeredObject, theRegion, federateAttributesBefore);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::unassociateRegionsForUpdates(const GeRtiFactory::GeRtiHandle &theFederate, const GERTICO::HandleSetMap &theAttributeRegions, const GeRtiFactory::GeRtiHandle &theObject)
{
  GERTICO::Federate *federate;
  GERTICO::HandleSetMap federateAttributesBefore;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle objectClass;

  federate = federatesHolder.getFederate(theFederate);;
  if (federate)
  {
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle knownClass;

    // Atomic test.
    knownClass = federate->getObjectClass(theObject);
    runTimeObjectDB.testRegionDimensions(knownClass, theAttributeRegions);
#endif

    objectClass = federate->getObjectClass(theObject);
    federate->unassociateRegionsForUpdates(theObject, theAttributeRegions);
  }

  // Get object.
  registeredObject = objectManagement.getObject(theObject);

  getObjectAttributesInScope(theFederate, *registeredObject, federateAttributesBefore);
  runTimeObjectDB.unassociateRegionsForUpdates(theFederate, theAttributeRegions, theObject);

  objectManagement.doDiscoverObject(theFederate, theObject);

  // Do any in/out of scope.
  objectManagement.doScopeAssociate(theFederate, *registeredObject, federateAttributesBefore);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::unsubscribeInteractionClassWithRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theInteraction, const GERTICO::HandleSet &theRegions)
{
  declarationManagement.unsubscribeInteractionClass(theFederate, theInteraction, theRegions);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::unsubscribeObjectClassWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theRegion)
{
  CORBA::WChar *wChar = L"unsubscribeObjectClassWithRegion";
  GERTICO::Federate *federatePtr;
  GERTICO::HandleSet regions;

  pm.acquire ();
  regions.insert(theRegion);
  try
  {
    // Delete from federate.
    federatePtr = federatesHolder.getFederate(theFederate);
    if (federatePtr)
    {
      federatePtr->unsubscribeObjectClassWithRegion(theObjectClass, regions);
    }

    runTimeObjectDB.unsubscribeObjectClass (theFederate, theObjectClass, regions);

    objectManagement.doScopeUnsubscribe(theFederate, theObjectClass);

    // Logic to stop registration for object class.
//    declarationManagement.objectClassSubStopRegistration(theFederate, theObjectClass);

//    declarationManagement.eventHandler->removeProxyPushSupplier(theFederate, theObjectClass);
  }
  catch(GeRtiFactory::RegionNotKnown &)
  {
    pm.release();
    //Testcase 9-6-19
    throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
  }
  catch(GeRtiFactory::ObjectClassNotSubscribed &)
  {
    pm.release();
    throw;
  }
  catch(...)
  {
    pm.release();
    return;
  }
  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::unsubscribeObjectClassWithRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GERTICO::HandleSetMap &theAttributeRegions)
{
  CORBA::WChar *wChar = L"unsubscribeObjectClassWithRegions";
  GERTICO::Federate *federatePtr;
#ifndef IEEE_1516
  GERTICO::HandleSet regions;
  GERTICO::HandleSetMap regionAttributes;
  GERTICO::HandleSetMap::iterator itRegionAttributes;
#endif

  pm.acquire ();
  try
  {
    // Delete from federate.
    federatePtr = federatesHolder.getFederate(theFederate);
    if (federatePtr)
    {
      federatePtr->unsubscribeObjectClassWithRegions(theObjectClass, theAttributeRegions);
    }

#ifdef IEEE_1516
    runTimeObjectDB.unsubscribeObjectClassWithAttributeRegions(theFederate, theObjectClass, theAttributeRegions);
#else
    GERTICO::Mapper::mapHandleSetMapInvert(regionAttributes, theAttributeRegions);
    for (itRegionAttributes = regionAttributes.begin(); itRegionAttributes != regionAttributes.end(); itRegionAttributes++)
    {
      regions.insert(itRegionAttributes->first);
    }
    runTimeObjectDB.unsubscribeObjectClass(theFederate, theObjectClass, regions);
#endif

    objectManagement.doScopeUnsubscribe(theFederate, theObjectClass);

    // Logic to stop registration for object class.
//    declarationManagement.objectClassSubStopRegistration(theFederate, theObjectClass);

//    declarationManagement.eventHandler->removeProxyPushSupplier(theFederate, theObjectClass);
  }
  catch(GeRtiFactory::RegionNotKnown &)
  {
    pm.release();
    //Testcase 9-6-19
    throw GeRtiFactory::ObjectClassNotSubscribed(wChar);
  }
  catch(GeRtiFactory::ObjectClassNotSubscribed &)
  {
    pm.release();
    throw;
  }
  catch(...)
  {
    pm.release();
    return;
  }
  pm.release ();
}

// ---------------------------------------------------------------------------
// For each object check if the federate has a region-subscription.
// If yes, turn on the scope flags.
// NB: this function is a trick designed to correct scope flags
//     normally the logic shound be done when a federate turns on
//     the enableAttributeScopeAdvisorySwitch.
// ---------------------------------------------------------------------------
void GERTICO::DataDistributionManagement::updateScopeFlags(const GeRtiFactory::GeRtiHandle &theRegion, GERTICO::HandleSet &theRegionsBefore)
{
  GERTICO::Federate *federatePtr;
  GERTICO::Federate *otherFederatePtr;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet subscribedAttributes;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itSubscribedAttribute;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::HandleSet::iterator itObject;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSet::iterator itRegionBefore;
  GERTICO::Region *currRegion;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle federate;
  GeRtiFactory::GeRtiHandle objectClass;
  GeRtiFactory::GeRtiHandle otherFederate;

  // Get information on the modify region federate.
  currRegion = runTimeObjectDB.getRegion(theRegion);
  currRegion->getObjects(objects);
  federate = currRegion->getFederateId();
  federatePtr = federatesHolder.getFederate(federate);

  // Get the other federates.
  federatesHolder.getFederates(federates);

  // Perform logic where this federate is publishing attributes.
  // For all objects, all federates update scope flag.
  for (itObject = objects.begin(); itObject != objects.end(); itObject++)
  {
    try
    {
      registeredObject = objectManagement.getObject(*itObject);
    }
    catch(...)
    {
      continue;
    }
    registeredObject->getFedRegionOwnedAtts(federate, theRegion, attributes);
    for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
    {
      otherFederatePtr = federatesHolder.getFederate(*itFederate);
      if (otherFederatePtr->knowObject(*itObject) == false)
      {
        continue;
      }
      objectClass = otherFederatePtr->getObjectClass(*itObject);
      otherFederatePtr->getSubscribedRegions(objectClass, regions);
      for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
      {
        if (otherFederatePtr->isSubscribedToObjectClassAttributes(objectClass, *itRegion, attributes))
        {
          otherFederatePtr->getSubscribedRegionAttributes(objectClass, *itRegion, subscribedAttributes);
          for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
          {
            itSubscribedAttribute = subscribedAttributes.find(*itAttribute);
            if (itSubscribedAttribute != subscribedAttributes.end())
            {
              otherFederatePtr->setInScope(*itObject, *itSubscribedAttribute);
            }
          }
        }
      }
    }
  }

  // Perform logic where this federate is subscribing attributes.
  // For all objects, all federates update scope flag.
  for (itRegionBefore = theRegionsBefore.begin(); itRegionBefore != theRegionsBefore.end(); itRegionBefore++)
  {
    currRegion = runTimeObjectDB.getRegion(*itRegionBefore);
    if (currRegion == NULL)
    {
      continue;
    }
    currRegion->getObjects(objects);
    otherFederate = currRegion->getFederateId();

    for (itObject = objects.begin(); itObject != objects.end(); itObject++)
    {
      try
      {
        registeredObject = objectManagement.getObject(*itObject);
      }
      catch(...)
      {
        continue;
      }
      registeredObject->getFedRegionOwnedAtts(otherFederate, *itRegionBefore, attributes);
      if (federatePtr->knowObject(*itObject) == false)
      {
        continue;
      }
      objectClass = federatePtr->getObjectClass(*itObject);
      federatePtr->getSubscribedRegions(objectClass, regions);
      for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
      {
        if (federatePtr->isSubscribedToObjectClassAttributes(objectClass, *itRegion, attributes))
        {
          federatePtr->getSubscribedRegionAttributes(objectClass, *itRegion, subscribedAttributes);
          for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
          {
            itSubscribedAttribute = subscribedAttributes.find(*itAttribute);
            if (itSubscribedAttribute != subscribedAttributes.end())
            {
              federatePtr->setInScope(*itObject, *itSubscribedAttribute);
            }
          }
        }
      }
    }
  }
}
