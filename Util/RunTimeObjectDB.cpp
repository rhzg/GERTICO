/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** RunTimeObjectDB.cpp
**
*******************************************************************************/

#include "RunTimeObjectDB.h" 
#include <iostream>
#include "Util/Mapper.h"

#define privilegeToDelete L"privilegeToDelete"
#define privilegeToDeleteIEEE L"HLAprivilegeToDeleteObject"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RunTimeObjectDB::RunTimeObjectDB(GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GERTICO::RegionsHolder &theRegionsHolder) : registeredObjectsHolder(theRegisteredObjectsHolder), regionsHolder(theRegionsHolder)
{
  isGerti = true;
  model = 0;
  pObjectRoot = NULL;
  privilegeToDeleteId = 0;

  // Strings for save/restore.
  idStr = "id";
  objectsStr = "objects";
  publishedClassesStr = "publishedClasses";
  regionStr = "region";
  regionsStr = "regions";
  subscribedClassesStr = "subscribedClasses";
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RunTimeObjectDB::~RunTimeObjectDB ()
{
  GERTICO::RoutingSpace *currRoutingSpace;
  GERTICO::RoutingSpaceMap::iterator itRSM;

  clear ();

  for (itRSM = allSpaces.begin (); itRSM != allSpaces.end (); itRSM = allSpaces.begin ())
  {
    currRoutingSpace = itRSM->second;
    allSpaces.erase (itRSM);
    delete currRoutingSpace;
  }
}

#ifdef IEEE_1516
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::addDimensions(GERTICO::FedDimensionMap &theFedDimensionMap)
{
  allDimensions = theFedDimensionMap;
  theFedDimensionMap.clear();
}
#endif

// ---------------------------------------------------------------------------
// Check if object already registered, if not register object.
// Add attribute/region pairs to the object.
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::addObjAttRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSetMap &theAttRegMap)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSet::iterator itRegions;
  GERTICO::HandleSetMap::iterator itAttRegMap;
  GERTICO::Region *currRegion;
  GERTICO::RegionMap::iterator itRI;

  // Get a Region.
  for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
  {
    for (itRegions = itAttRegMap->second.begin(); itRegions != itAttRegMap->second.end(); itRegions++)
    {
      // We do not manage default region in this map.
      if (*itRegions == 0)
      {
        continue;
      }

      itRI = regionsHolder.regionMap.find(*itRegions);
      if (itRI == regionsHolder.regionMap.end ())
      {
        throw GeRtiFactory::RegionNotKnown(wChar);
      }

      // Add the new object/region relationship.
      currRegion = itRI->second;
      currRegion->addObject(theFederate, theObject);
    }
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::addObjectRoot(GERTICO::ClassDescrHolder *theClassDescr)
{
  pObjectRoot = theClassDescr;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::addRoutingSpace(GERTICO::FedSpaceMap &theSpaces)
{
  GERTICO::FedDimension *currFedDimension;
  GERTICO::FedSpace *currFedSpace;
  std::map <unsigned long, GERTICO::FedDimension *>::iterator itFD;
  FedSpaceMap::iterator itFS;
  GERTICO::Dimension *currDimension;
  GERTICO::RoutingSpace *currRoutingSpace;

  for (itFS = theSpaces.begin ();
       itFS != theSpaces.end ();
       itFS++)
  {
    currFedSpace = itFS->second;
    currRoutingSpace = new GERTICO::RoutingSpace (currFedSpace->getName (), currFedSpace->getId ());
    allSpaces[currRoutingSpace->getId ()] = currRoutingSpace;
    for (itFD = currFedSpace->dimensions.begin ();
         itFD != currFedSpace->dimensions.end ();
         itFD++)
    {
      currFedDimension = itFD->second;
      currDimension = new GERTICO::Dimension (currFedDimension->getName (), currFedDimension->getId ());
      currRoutingSpace->dimensions[currDimension->getId ()] = currDimension;
    }
  }
}


// ---------------------------------------------------------------------------
// Check if object already registered, if not register object.
// Add attribute/region pairs to the object.
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::associateRegionForUpdates(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSetMap &theAttributeRegions)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSetMap regionAttributes;
  GERTICO::HandleSetMap::iterator itAttributeRegions;
  GERTICO::HandleSetMap::iterator itRegionAttributes;
  GERTICO::RegisteredObject *currObject;
  GERTICO::Region *currRegion;
  GERTICO::RegionMap::iterator itRI;

  GERTICO::Mapper::mapHandleSetMapInvert(regionAttributes, theAttributeRegions);
  for (itAttributeRegions = regionAttributes.begin(); itAttributeRegions != regionAttributes.end(); itAttributeRegions++)
  {
    // Get the Region.
    itRI = regionsHolder.regionMap.find(itAttributeRegions->first);
    if (itRI == regionsHolder.regionMap.end ())
    {
      throw GeRtiFactory::RegionNotKnown(wChar);
    }

    // Add the new object/region relationship.
    currRegion = itRI->second;
    currRegion->addObject(theFederate, theObject);
  }

  // Get the Object.
  try
  {
    currObject = registeredObjectsHolder.getObject(theObject);

    // Check if attribute space is the same as region space.
    if (checkAttRegSpace (currObject->getClassId (), theAttributeRegions) == false)
    {
      throw GeRtiFactory::InvalidRegionContext(wChar);
    }

    // Add the new attribute/region relationships.
    for (itRegionAttributes = regionAttributes.begin(); itRegionAttributes != regionAttributes.end(); itRegionAttributes++)
    {
      currObject->addAttributesRegion(theFederate, itRegionAttributes->second, itRegionAttributes->first);
    }
  }
  catch (GeRtiFactory::ObjectNotKnown &)
  {
    throw;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::testIfRequestedToRelease(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes)
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
    if (!attributeInfo->testRequested())
    {
      throw GeRtiFactory::FederateWasNotAskedToReleaseAttribute(wChar);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::RunTimeObjectDB::checkAttRegSpace (const GeRtiFactory::GeRtiHandle &theClass, const GERTICO::HandleSetMap &theAttRegMap)
{
  CORBA::ULong itemSpace;
  CORBA::ULong regionSpace;
  GERTICO::ClassDescr *currClassDescr;
  GERTICO::ClassDescr *theClassDescr;
  GERTICO::HandleSet::const_iterator itRegions;
  GERTICO::HandleSetMap::const_iterator itAttRegMap;
  Item *currItem;
  ItemMap::iterator itI;

  // Get the class description for the given class.
  theClassDescr = getObjectClassDescr (theClass);

  // Check attribute / region values.
  for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
  {
    // If no region specified, do not check.
    if (itAttRegMap->second.size() == 0)
    {
      continue;
    }

    // Find the space associated to the attribute.
    currClassDescr = theClassDescr;
    while (currClassDescr)
    {
      itI = currClassDescr->items.find(itAttRegMap->first);
      if (itI == currClassDescr->items.end ())
      {
        currClassDescr = currClassDescr->parent;
        continue;
      }
      currItem = itI->second;
      itemSpace = currItem->getSpace ();
      break;
    }

    for (itRegions = itAttRegMap->second.begin(); itRegions != itAttRegMap->second.end(); itRegions++)
    {
      // Find the space associated to the region.
      regionSpace = getRegionSpace(*itRegions);

      // Compare spaces.
      if (itemSpace != regionSpace)
      {
        return false;
      }
    }
  }

  return true;
}


// ---------------------------------------------------------------------------
// Special logic to find publishers which do not have active subscribers.
// ---------------------------------------------------------------------------
bool GERTICO::RunTimeObjectDB::checkActiveObjectClassSubscribers (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClassId, GERTICO::HandleSet &theAttributes)
{
  SubscribedClass *subscribedClass;
  
  try
  {
    subscribedClass = getSubscribedClass (theClassId);
  }
  catch (GeRtiFactory::ObjectClassNotSubscribed &)
  {
    return false;
  }

  return subscribedClass->checkActiveSubscribers (theFederate, theAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::checkAttributesInSpace(const GeRtiFactory::GeRtiHandle &theSpace, const GeRtiFactory::GeRtiHandle &theClass, const GERTICO::HandleSet &theAttributes)
{
  GERTICO::Item *item;
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet::const_iterator itAttribute;
  unsigned long space;

  classDescr = pObjectRoot->getClassDescr(theClass);
  if (classDescr == NULL)
  {
    throw GeRtiFactory::ObjectClassNotDefined(L"checkAttributesInSpace");
  }

  for (itAttribute = theAttributes.begin(); itAttribute != theAttributes.end(); itAttribute++)
  {
    item = classDescr->getClassItem(*itAttribute);
    if (item)
    {
      space = item->getSpace();
      if (space != theSpace)
      {
        throw GeRtiFactory::RegionNotKnown(L"checkAttributesInSpace");
      }
    }
    else
    {
      throw GeRtiFactory::AttributeNotDefined(L"checkAttributesInSpace");
    }
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::checkClassAttributes (const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes)
{
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::Item *currItem;

  classDescr = pObjectRoot->getClassDescr (theObjectClass);
  if (classDescr == NULL)
  {
    throw GeRtiFactory::ObjectClassNotDefined(wChar);
  }

  for (itHS = theAttributes.begin (); itHS != theAttributes.end (); itHS++)
  {
    currItem = classDescr->getClassItem (*itHS);
    if (currItem == NULL)
    {
      throw GeRtiFactory::AttributeNotDefined(wChar);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::checkPublishing(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::Handles &theAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Item *item;

  if (isGerti)
  {
    classDescr = getObjectClassDescr(theClass);
    len = theAttributes.length();
    for (i = 0; i < len; i++)
    {
      item = classDescr->getClassItem(theAttributes[i]);
      if (item == NULL)
      {
        throw GeRtiFactory::AttributeNotDefined(L"checkPublishing");
      }
    }
  }

  publishedClassMap.checkPublishing(theFederate, theClass, theAttributes, privilegeToDeleteId);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::clear (void)
{
  GERTICO::Region *currRegion;
  GERTICO::RegionMap::iterator itR;

  publishedClassMap.clear();

  subscribedClassHolder.clear();

  registeredObjectsHolder.clear();

  for (itR = regionsHolder.regionMap.begin ();
       itR != regionsHolder.regionMap.end ();
       itR = regionsHolder.regionMap.begin ())
  {
    currRegion = itR->second;
    regionsHolder.regionMap.erase (itR);
    delete currRegion;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::createRegion (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theSpace, const CORBA::ULong &numberOfExtents, const GERTICO::HandleSet &theDimensions, const GeRtiFactory::GeRtiHandle &theRegion)
{
  GERTICO::RoutingSpaceMap::iterator itRS;

#ifndef IEEE_1516
  itRS = allSpaces.find (theSpace);
  if (itRS == allSpaces.end ())
  {
    if (isGerti)
    {
      throw GeRtiFactory::SpaceNotDefined(L"createRegion");
    }
  }
#endif

  GERTICO::Region *newRegion = new GERTICO::Region(theFederate, theSpace, numberOfExtents, theDimensions, theRegion);
  regionsHolder.regionMap[theRegion] = newRegion;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::printRegions(void)
{
  GERTICO::Region *region;
  GERTICO::RegionMap::iterator itRI;
  for (itRI = regionsHolder.regionMap.begin(); itRI != regionsHolder.regionMap.end(); itRI++)
  {
    region = itRI->second;
    region->print();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::deleteObjectInstance(GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle theFederate)
  throw (GeRtiFactory::ObjectNotKnown, GeRtiFactory::DeletePrivilegeNotHeld)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::RegisteredObject *registeredObject;
  Region *currRegion;
  RegionMap::iterator itRI;
  GeRtiFactory::GeRtiHandle myClass;
  GERTICO::PublishedClass *publishedClass;

  // remove object with all registered attributes
  registeredObject = registeredObjectsHolder.getObject(theObject);
    AttributeInfo* info;
    // test if theFederate owns privilige to delete attribute
    try
    {
      info = registeredObject->getAttribute(privilegeToDeleteId);
    }
    catch (GeRtiFactory::AttributeNotDefined &)
    {
      // AttributeNotDefined is semantically equivalent to DeletePrivilegeNotHeld.
      throw GeRtiFactory::DeletePrivilegeNotHeld(wChar);
    }

    if ((info->getStatus() != owned) ||
        (info->getFederate () != theFederate))
    {
      throw GeRtiFactory::DeletePrivilegeNotHeld(wChar);
    }  
    // remove object 
    myClass = registeredObject->getClassId ();
    registeredObject->getAllRegions(regions);
    for (itHS = regions.begin(); itHS != regions.end(); itHS++)
    {
      itRI = regionsHolder.regionMap.find(*itHS);
      if (itRI != regionsHolder.regionMap.end())
      {
        currRegion = itRI->second;
        currRegion->delObject(theObject);
      }
    }
    publishedClass = getPublishedClass (myClass);
    if (publishedClass)
    {
      publishedClass->delObject (theObject);
    }
    registeredObjectsHolder.delObject(theObject);
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::deleteRegion (const GeRtiFactory::GeRtiHandle &theRegion)
{
  CORBA::WChar *wChar = L"";
  Region *currRegion;
  RegionMap::iterator itRI;

  itRI = regionsHolder.regionMap.find (theRegion);
  if (itRI != regionsHolder.regionMap.end ())
  {
    currRegion = itRI->second;
    if (currRegion->regionInUse ())
    {
      throw GeRtiFactory::RegionInUse(wChar);
    }
    regionsHolder.regionMap.erase (itRI);
  }
  else
  {
    throw GeRtiFactory::RegionNotKnown(wChar);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::removeObjectInstance(GeRtiFactory::GeRtiHandle theObject)
{
  GeRtiFactory::GeRtiHandle classId;
  GERTICO::PublishedClass *currPublishedClass;
  GERTICO::RegisteredObject *registeredObject;
  ObjByNameMap::iterator itOBN;
  ObjectMap::iterator iO;

  // remove object with all registered attributes
  registeredObject = registeredObjectsHolder.getObject(theObject);
  classId = registeredObject->getClassId();
  currPublishedClass = getPublishedClass(classId);
  if (currPublishedClass)
  {
    currPublishedClass->delObject(theObject);
  }
  registeredObjectsHolder.delObject(theObject);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::getAttributeRoutingSpaceHandle (const GeRtiFactory::GeRtiHandle &theAttribute, const GeRtiFactory::GeRtiHandle &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound, bool &theAttributeFound)
{
  pObjectRoot->getAttributeRoutingSpaceHandle(theAttribute, theClass, theSpace, theClassFound, theAttributeFound);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::RunTimeObjectDB::getDimensionHandle (const std::wstring &theName, const GeRtiFactory::GeRtiHandle &whichSpace)
{
  CORBA::WChar *wChar = L"";

#ifdef IEEE_1516
  GERTICO::FedDimensionMap::iterator itFedDimensionMap;
  for (itFedDimensionMap = allDimensions.begin(); itFedDimensionMap != allDimensions.end(); itFedDimensionMap++)
  {
    if (itFedDimensionMap->second->getName() == theName)
    {
      return itFedDimensionMap->second->getId();
    }
  }
#else
  GERTICO::Dimension *currDimension;
  GERTICO::DimensionMap::iterator itDim;
  GERTICO::RoutingSpace *currRoutingSpace;
  GERTICO::RoutingSpaceMap::iterator itRS;
  std::wstring tmpName(theName);
  std::wstring tmpName1;

  itRS = allSpaces.find (whichSpace);
  if (itRS == allSpaces.end ())
  {
    throw GeRtiFactory::SpaceNotDefined(wChar);
  }
  currRoutingSpace = itRS->second;

  GERTICO::Mapper::nameToLower(tmpName);

  for (itDim = currRoutingSpace->dimensions.begin ();
       itDim != currRoutingSpace->dimensions.end ();
       itDim++)
  {
    currDimension = itDim->second;
    currDimension->getNameLower (tmpName1);
    if (tmpName == tmpName1)
    {
      return currDimension->getId ();
    }
  }
#endif

  throw GeRtiFactory::NameNotFound(wChar);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::getDimensionName(std::wstring &theName, const GeRtiFactory::GeRtiHandle &theHandle, const GeRtiFactory::GeRtiHandle &whichSpace)
{
  CORBA::WChar *wChar = L"";
  GERTICO::Dimension *currDimension;
  GERTICO::DimensionMap::iterator itDim;
  GERTICO::RoutingSpace *currRoutingSpace;
  GERTICO::RoutingSpaceMap::iterator itRS;
  std::wstring tmpName;

  itRS = allSpaces.find (whichSpace);
  if (itRS == allSpaces.end ())
  {
    throw GeRtiFactory::SpaceNotDefined(wChar);
  }
  currRoutingSpace = itRS->second;

  itDim = currRoutingSpace->dimensions.find (theHandle);
  if (itDim == currRoutingSpace->dimensions.end ())
  {
    throw GeRtiFactory::DimensionNotDefined(wChar);
  }

  currDimension = itDim->second;
  currDimension->getName (tmpName);
  theName = tmpName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::getPublishedAttributes(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributeSet)
{
  publishedClassMap.getPublishedAttributes(theFederate, theClass, theAttributeSet, privilegeToDeleteId);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::registerObjectInstance(GERTICO::ClassDescr &theClassDescr, const GeRtiFactory::GeRtiHandle &theObjectId)
{
  GERTICO::PublishedClass *currPublishedClass;

  currPublishedClass = getPublishedClass(theClassDescr.getId());
  if (currPublishedClass)
  {
    currPublishedClass->addObject (theObjectId);
  }
  else
  {
    throw GeRtiFactory::ObjectClassNotPublished(L"registerObjectInstance");
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublishedClass* GERTICO::RunTimeObjectDB::getPublishedClass (const GeRtiFactory::GeRtiHandle &classId)
  throw (GeRtiFactory::ObjectClassNotPublished)
{
  return publishedClassMap.getPublishedClass(classId);
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SubscribedClass* GERTICO::RunTimeObjectDB::getSubscribedClass (const GeRtiFactory::GeRtiHandle &classId)
  throw (GeRtiFactory::ObjectClassNotSubscribed)
{
  GERTICO::SubscribedClass *subscribedClassPtr;

  subscribedClassPtr = subscribedClassHolder.getSubscribedClass(classId);
  return subscribedClassPtr;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegisteredObject* GERTICO::RunTimeObjectDB::getObject (GeRtiFactory::GeRtiHandle objId)  
  throw (GeRtiFactory::ObjectNotKnown)
{
  return registeredObjectsHolder.getObject(objId);
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ClassDescr *GERTICO::RunTimeObjectDB::getObjectClassDescr (const GeRtiFactory::GeRtiHandle &theClassId)
{
  GERTICO::ClassDescr *ret;

  ret = pObjectRoot->getClassDescr (theClassId);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::RunTimeObjectDB::getPrivilegeToDeleteId () 
{
  if (privilegeToDeleteId == 0)
  {
    try
    {
      privilegeToDeleteId = model->getAttributeId (model->getRootClass()->getId(), privilegeToDelete);
    }
    catch (AttributeNotDefined &)
    {
      privilegeToDeleteId = model->getAttributeId (model->getRootClass()->getId(), privilegeToDeleteIEEE);
    }
 }
  return privilegeToDeleteId;  
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AttributeInfo* GERTICO::RunTimeObjectDB::getObjectAttributeInfo (GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle theAttribute)
    throw (GeRtiFactory::ObjectNotKnown, GeRtiFactory::AttributeNotDefined)
{
  GERTICO::RegisteredObject* o = getObject (theObject);
  return o->getAttribute(theAttribute);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Region *GERTICO::RunTimeObjectDB::getRegion (const GeRtiFactory::GeRtiHandle &regionId)
{
  Region *currRegion = NULL;

  currRegion = regionsHolder.getRegion(regionId);

  return currRegion;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::getFederateRegions(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSet &theRegions)
{
  RegionMap::iterator itRegion;

  theRegions.clear();
  for (itRegion = regionsHolder.regionMap.begin(); itRegion != regionsHolder.regionMap.end(); itRegion++)
  {
    theRegions.insert(itRegion->first);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::RunTimeObjectDB::getRegionSpace (const GeRtiFactory::GeRtiHandle &theRegion)
{
  Region *currRegion;
  RegionMap::iterator itR;

  itR = regionsHolder.regionMap.find (theRegion);
  if (itR != regionsHolder.regionMap.end ())
  {
    currRegion = itR->second;
    return currRegion->getSpace ();
  }

  return 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::RunTimeObjectDB::getRoutingSpaceHandle (const std::wstring &theSpace)
{
  CORBA::WChar *wChar = L"";
  GERTICO::RoutingSpace *currRoutingSpace;
  GERTICO::RoutingSpaceMap::iterator itRS;
  std::wstring tmpName0(theSpace);
  std::wstring tmpName1;

  if (theSpace.size() == 0)
  {
    return 0;
  }

  GERTICO::Mapper::nameToLower(tmpName0);

  for (itRS = allSpaces.begin (); itRS != allSpaces.end (); itRS++)
  {
    currRoutingSpace = itRS->second;
    currRoutingSpace->getNameLower (tmpName1);
    if (tmpName0 == tmpName1)
    {
      return currRoutingSpace->getId ();
    }
  }

  throw GeRtiFactory::NameNotFound(wChar);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::RunTimeObjectDB::getRoutingSpaceName (
    const GeRtiFactory::GeRtiHandle &theHandle
  )
{
  CORBA::WChar *wChar = L"";
  GERTICO::RoutingSpace *currRoutingSpace;
  GERTICO::RoutingSpaceMap::iterator itRS;
  std::wstring tmpName;

  itRS = allSpaces.find (theHandle);
  if (itRS == allSpaces.end ())
  {
    throw GeRtiFactory::SpaceNotDefined(wChar);
  }
  currRoutingSpace = itRS->second;

  currRoutingSpace->getName (tmpName);

  return tmpName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::getScopeSubscribers (GERTICO::HandleSet &inScopeSubscribers, GERTICO::HandleSet &outScopeSubscribers, GERTICO::HandleSet &subscribersBefore, GERTICO::HandleSet &subscribersAfter)
{
  GERTICO::HandleSet::iterator itHSA;
  GERTICO::HandleSet::iterator itHSB;

  // List of those which are no longer in scope.
  for (itHSB = subscribersBefore.begin (); itHSB != subscribersBefore.end (); itHSB++)
  {
    itHSA = subscribersAfter.find (*itHSB);
    if (itHSA == subscribersAfter.end ())
    {
      outScopeSubscribers.insert (*itHSB);
    }
  }

  // List of those which are now in scope.
  for (itHSA = subscribersAfter.begin (); itHSA != subscribersAfter.end (); itHSA++)
  {
    itHSB = subscribersBefore.find (*itHSA);
    if (itHSB == subscribersBefore.end ())
    {
      inScopeSubscribers.insert (*itHSA);
    }
  }
}

// ---------------------------------------------------------------------------
// Convert region to federate id.
// NB: Assume that the region belongs to ONE federate only.
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::getSubscribers (GERTICO::HandleSet &currSubscribers, GERTICO::HandleSet &subscribedRegions)
{
  GeRtiFactory::GeRtiHandle fed;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::Region *currRegion;
  GERTICO::RegionMap::iterator itR;

  for (itHS = subscribedRegions.begin (); itHS != subscribedRegions.end (); itHS++)
  {
    itR = regionsHolder.regionMap.find (*itHS);
    if (itR != regionsHolder.regionMap.end ())
    {
      currRegion = itR->second;
      fed = currRegion->getFederateId ();
      currSubscribers.insert (fed);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::modifyRegion (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::Extents &theExtents)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet inScopeSubscribers;
  GERTICO::HandleSet objectSet;
  GERTICO::HandleSet outScopeSubscribers;
  GERTICO::HandleSet subscribersAfter;
  GERTICO::HandleSet subscribersBefore;
  GERTICO::HandleSet subscribedRegions;
  GERTICO::HandleSetMap objectAttributes;
  GeRtiFactory::Handles theAttributes;
  GeRtiFactory::Handles theRegions;
  Region *currRegion;
  RegionMap::iterator itR;
  std::string theObjectName;

  itR = regionsHolder.regionMap.find (theRegion);
  if (itR == regionsHolder.regionMap.end ())
  {
    throw GeRtiFactory::RegionNotKnown(wChar);
  }
  currRegion = itR->second;
#ifndef IEEE_1516
  // Update the extents.
  currRegion->modify (theExtents);
#endif
  // Get the current subscribed federates.
  currRegion->getIntersectionSet(subscribedRegions);
  getSubscribers (subscribersBefore, subscribedRegions);
  // Get the current object/attributes.
  currRegion->getObjectAttributes(objectAttributes, registeredObjectsHolder);
  // Clear any old intersection.
  currRegion->delIntersection ();
  // Build new intersections.
  for (itR = regionsHolder.regionMap.begin (); itR != regionsHolder.regionMap.end (); itR++)
  {
    if (itR->first == theRegion)
    {
      continue;
    }
    if (itR->second->getFederateId() == theFederate)
    {
      continue;
    }
    if (currRegion->getSpace() != itR->second->getSpace())
    {
      continue;
    }
    // Clear only the intersection pertaining to this region.
    itR->second->delIntersection (theRegion);
    // Check overlap and add intersections.
    currRegion->tryAddIntersection(itR->second->getFederateId(), itR->second->getId (), *itR->second->getExtents ());
    itR->second->tryAddIntersection(theFederate, theRegion, *currRegion->getExtents ());
  }
  // Get the current subscribed federates.
  currRegion->getIntersectionSet(subscribedRegions);
  getSubscribers (subscribersAfter, subscribedRegions);

  // Get the changed subscribers.
  getScopeSubscribers (inScopeSubscribers, outScopeSubscribers, subscribersBefore, subscribersAfter);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::print ()
{
/*
  std::cout << "Class Structure" << std::endl;
  GERTICO::PublishedClassMap::iterator iClass;
  for (iClass = publishedClassMap.begin(); iClass != publishedClassMap.end(); iClass++)
  {
    std::cout << "Class " << iClass->first << std::endl;
    iClass->second->print();
  }  
*/

/*
  std::cout << "Object Structure" << std::endl;
  ObjectMap::iterator iObject;
  for (iObject = registeredObjectsHolder.objects.begin(); iObject != registeredObjectsHolder.objects.end(); iObject++)
  {
    std::cout << "Object " << iObject->first << std::endl;
    iObject->second->print();
  } 
*/

/*
  std::cout << "Subscribed Class Structure" << std::endl;
  SubscribedClass *subscribedClass;
  SubscribedClassMap::iterator itSubscribedClassMap;
  unsigned long ul;

  for (itSubscribedClassMap = subscribedClassMap.begin(); itSubscribedClassMap != subscribedClassMap.end(); itSubscribedClassMap++)
  {
    ul = itSubscribedClassMap->first;
    std::cout << "  Subscribed Class " << ul << std::endl;
    subscribedClass = itSubscribedClassMap->second;
    subscribedClass->print();
  }
*/
}

// ---------------------------------------------------------------------------
// Use for publish and unpublish.
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::publishObjectClass (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::PublishedClass *currPublishedClass;

  // Check if attributes belong to the object class: known only in gerti!
  if (isGerti)
  {
    checkClassAttributes (theObjectClass, theAttributes);
  }

  // Check if object class already administered.
  currPublishedClass = getPublishedClass (theObjectClass);
  if (currPublishedClass == NULL)
  {
    // Create an object class.
    currPublishedClass = publishedClassMap.createClass(theObjectClass);
    currPublishedClass->sharingStatus = Publish;
  }

  // Have an object class.
  currPublishedClass->addPubAttributes (theFederate, theAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::restore (DOMElement &theDOMElement)
{
  DOMNode* child;

  clear ();

  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (publishedClassesStr.c_str ())) == 0)
      {
        restorePublishedClasses (*((DOMElement *)child));
      }
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (subscribedClassesStr.c_str ())) == 0)
      {
        subscribedClassHolder.restoreSubscribedClasses (*((DOMElement *)child));
      }
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (objectsStr.c_str ())) == 0)
      {
        registeredObjectsHolder.restore(*((DOMElement *)child));
      }
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (regionsStr.c_str ())) == 0)
      {
        restoreRegions (*((DOMElement *)child));
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::restorePublishedClasses (DOMElement &theDOMElement)
{
  publishedClassMap.restorePublishedClasses(theDOMElement);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::restoreRegions (DOMElement &theDOMElement)
{
  DOMNode *child;
  Region *region;
  char *tmpChar;
  unsigned long tmpID;

  // Restore the published classes,
  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (regionStr.c_str ())) == 0)
      {
        tmpChar = XMLString::transcode (((DOMElement *)child)->getAttribute (XMLString::transcode (idStr.c_str ())));
        sscanf (tmpChar, "%lu", &tmpID);
        region = new Region (tmpID);
        region->restore (*((DOMElement *)child));
        regionsHolder.regionMap[tmpID] = region;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::save (DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  GERTICO::PublishedClassMap::iterator itP;
  GERTICO::SubscribedClassMap::iterator itS;
  RegionMap::iterator itRM;
  XMLCh tempStr[100];

  // Published classes.
  publishedClassMap.save(theDOMDocument, theDOMElement);

  // Subscribed classes.
  subscribedClassHolder.save(theDOMDocument, theDOMElement);

  XMLString::transcode(objectsStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  registeredObjectsHolder.save(theDOMDocument, *elemLevel1);

  // Regions
  XMLString::transcode(regionsStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);
  for (itRM = regionsHolder.regionMap.begin (); itRM != regionsHolder.regionMap.end (); itRM++)
  {
    XMLString::transcode(regionStr.c_str (), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    itRM->second->save (theDOMDocument, *elemLevel2);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::setRangeBounds(GeRtiFactory::GeRtiHandle const &theRegionHandle, GeRtiFactory::GeRtiHandle const &theDimensionHandle, GeRtiFactory::GeRtiHandle const &theLowerBound, GeRtiFactory::GeRtiHandle const &theUpperBound)
{
  GERTICO::ExtentMap *extentMap;
  GERTICO::ExtentMap::iterator itExtentMap;
  GERTICO::RangeMap *rangeMap;
  GERTICO::RangeMap::iterator itRangeMap;
  GERTICO::Region *currRegion;
  GERTICO::RegionMap::iterator itR;

  itR = regionsHolder.regionMap.find(theRegionHandle);
  if (itR != regionsHolder.regionMap.end())
  {
    currRegion = itR->second;
    extentMap = currRegion->getExtents();
    itExtentMap = extentMap->find(0);
    if (itExtentMap != extentMap->end())
    {
      rangeMap = itExtentMap->second.getRangeMap();
      itRangeMap = rangeMap->find(theDimensionHandle);
      if (itRangeMap != rangeMap->end())
      {
        itRangeMap->second.lower = theLowerBound;
        itRangeMap->second.upper = theUpperBound;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::RunTimeObjectDB::subscribedToAttribute (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::SubscribedClass *currSubscribedClass;

  try
  {
    currSubscribedClass = getSubscribedClass (theClass);
  }
  catch (GeRtiFactory::ObjectClassNotSubscribed &)
  {
    return false;
  }

  if (currSubscribedClass->subscribedToAttribute (theFederate, theAttributes))
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::RunTimeObjectDB::subscribedToAttributeActive(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes)
{
  GERTICO::SubscribedClass *currSubscribedClass;

  try
  {
    currSubscribedClass = getSubscribedClass(theClass);
  }
  catch(GeRtiFactory::ObjectClassNotSubscribed &)
  {
    return false;
  }

  if (currSubscribedClass->subscribedToAttributeActive(theFederate, theAttributes))
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
// Check if any attribute is subscribed (passive or active).
// ---------------------------------------------------------------------------
bool GERTICO::RunTimeObjectDB::subscribedToAttributeWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSetMap &theAttributeRegions)
{
  GERTICO::SubscribedClass *currSubscribedClass;
 
  try
  {
    currSubscribedClass = getSubscribedClass (theClass);
  }
  catch (GeRtiFactory::ObjectClassNotSubscribed &)
  {
    return false;
  }

  if (currSubscribedClass->subscribedToAttribute(theFederate, theAttributeRegions, regionsHolder.regionMap))
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::subscribeObjectClassAttributes(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes, const CORBA::Boolean &theActive)
{
  CORBA::WChar *wChar = L"subscribeObjectClassAttributes";
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator itAttributes;
  GERTICO::HandleSet::iterator itHS;

  // Test if attributes belong to the class
  classDescr = pObjectRoot->getClassDescr(theObjectClass);
  classDescr->getAttributes(attributes);
  for (itAttributes = theAttributes.begin(); itAttributes != theAttributes.end(); itAttributes++)
  {
    itHS = attributes.find(*itAttributes);
    if (itHS == attributes.end())
    {
      throw GeRtiFactory::AttributeNotDefined(wChar);
    }
  }

  getObjectIdsForClass(theObjectClass, objects);

  subscribedClassHolder.subscribeObjectClassAttributes(theFederate, theObjectClass, theAttributes, theActive);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::subscribeObjectClassAttributesWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSetMap &theAttributeRegions, const CORBA::Boolean &theActive)
{
  CORBA::WChar *wChar = L"";
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet objects;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::HandleSetMap::iterator itAttributeRegions;

  // Test if attributes belong to the class
  classDescr = pObjectRoot->getClassDescr(theObjectClass);
  classDescr->getAttributes(attributes);
  for (itAttributeRegions = theAttributeRegions.begin(); itAttributeRegions != theAttributeRegions.end(); itAttributeRegions++)
  {
    itHS = attributes.find(itAttributeRegions->first);
    if (itHS == attributes.end())
    {
      throw GeRtiFactory::AttributeNotDefined(wChar);
    }
  }

  // Check if attribute space is the same as region space.
  if (checkAttRegSpace (theObjectClass, theAttributeRegions) == false)
  {
    throw GeRtiFactory::InvalidRegionContext(wChar);
  }

  getObjectIdsForClass (theObjectClass, objects);

  subscribedClassHolder.subscribeObjectClassAttributesWithRegion(theFederate, theObjectClass, theAttributeRegions, theActive);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::RunTimeObjectDB::testIntersection (const GeRtiFactory::GeRtiHandle &regionFirst, const GeRtiFactory::GeRtiHandle &regionSecond)
{
  Region *currRegion;
  RegionMap::iterator itR;

  itR = regionsHolder.regionMap.find (regionFirst);
  if (itR != regionsHolder.regionMap.end ())
  {
    currRegion = itR->second;
    return currRegion->gotIntersection (regionSecond);
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::testRegionDimensions(GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSetMap const &theAttRegMap)
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::Item *item;
  GERTICO::HandleSet dimensions;
  const GERTICO::HandleSet *regionsPtr;
  GERTICO::HandleSet::const_iterator itRegion;
  GERTICO::HandleSetMap::const_iterator itAttRegMap;
  GERTICO::Region *region;

  classDescr = getObjectClassDescr(theObjectClass);
  for (itAttRegMap = theAttRegMap.begin(); itAttRegMap != theAttRegMap.end(); itAttRegMap++)
  {
    item = classDescr->getClassItem(itAttRegMap->first);
    if (item == NULL)
    {
      continue;
    }
    item->getDimensions(dimensions);
    regionsPtr = &itAttRegMap->second;
    for (itRegion = regionsPtr->begin(); itRegion != regionsPtr->end(); itRegion++)
    {
      region = getRegion(*itRegion);
      region->testDimensions(dimensions);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::unassociateRegionForUpdates (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::GeRtiHandle &theObject)
{
  CORBA::WChar *wChar = L"";
  GERTICO::RegisteredObject *currObject;
  Region *currRegion;
  RegionMap::iterator itRI;

  itRI = regionsHolder.regionMap.find (theRegion);

  if (itRI != regionsHolder.regionMap.end ())
  {
    currRegion = itRI->second;
    currRegion->unassociateRegionForUpdates(theFederate, theObject);
  }
  else
  {
    throw GeRtiFactory::RegionNotKnown(wChar);
  }

  // Get the Object.
  currObject = getObject (theObject);
  // Remove the region relationship.
  currObject->clearRegion(theFederate, theRegion);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::unassociateRegionsForUpdates(const GeRtiFactory::GeRtiHandle &theFederate, const GERTICO::HandleSetMap &theAttributeRegions, const GeRtiFactory::GeRtiHandle &theObject)
{
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSetMap regionAttributes;
  GERTICO::HandleSetMap::iterator itRegionAttributes;
  GERTICO::RegisteredObject *currObject;
  Region *currRegion;
  RegionMap::iterator itRI;

  GERTICO::Mapper::mapHandleSetMapInvert(regionAttributes, theAttributeRegions);
  for (itRegionAttributes = regionAttributes.begin(); itRegionAttributes != regionAttributes.end(); itRegionAttributes++)
  {
    itRI = regionsHolder.regionMap.find(itRegionAttributes->first);
 
    if (itRI != regionsHolder.regionMap.end ())
    {
      currRegion = itRI->second;
      currRegion->unassociateRegionForUpdates(theFederate, theObject);
    }
    else
    {
      throw GeRtiFactory::RegionNotKnown(wChar);
    }

    // Get the Object.
    currObject = getObject (theObject);
    // Remove the region relationship.
    currObject->clearRegion(theFederate, itRegionAttributes->first);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::unpublishObjectClass(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass)
{
  GERTICO::PublishedClass *currPublishedClass;

  // Check if object class already administered.
  currPublishedClass = getPublishedClass(theObjectClass);
  if (currPublishedClass == NULL)
  {
#ifdef IEEE_1516
    return;
#else
    throw GeRtiFactory::ObjectClassNotPublished(L"unpublishObjectClass");
#endif
  }

  // Have an object class.
  currPublishedClass->delPubAttributes(theFederate);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::unpublishObjectClassAttributes(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::Handles &theAttributes)
{
  GERTICO::PublishedClass *currPublishedClass;

  // Check if object class already administered.
  currPublishedClass = getPublishedClass(theObjectClass);
  if (currPublishedClass == NULL)
  {
    throw GeRtiFactory::ObjectClassNotPublished(L"unpublishObjectClassAttributes");
  }

  // Have an object class.
  currPublishedClass->delPubAttributes(theFederate, theAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::unsubscribeObjectClass(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GERTICO::HandleSet &theRegions)
{
  subscribedClassHolder.unsubscribeObjectClass(theFederate, theObjectClass, theRegions);
}

#ifdef IEEE_1516
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::unsubscribeObjectClassWithAttributeRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GERTICO::HandleSetMap &theAttributeRegions)
{
  subscribedClassHolder.unsubscribeObjectClassWithAttributeRegions(theFederate, theObjectClass, theAttributeRegions);
}
#endif

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::getOwnedObjectAttributes(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSet &attributes, const bool &thePrivilegeToDeleteNeeded)
{
  GERTICO::RegisteredObject* o = getObject(theObject);
  o->getOwnedAttributes(theFederate, getPrivilegeToDeleteId(), attributes, thePrivilegeToDeleteNeeded);
}  


// ---------------------------------------------------------------------------
// get all objects for specified class including
// all child classes
// ---------------------------------------------------------------------------
void GERTICO::RunTimeObjectDB::getObjectIdsForClass (
  const GeRtiFactory::GeRtiHandle &theClass, 
  GERTICO::HandleSet &theObjects)
{
  std::vector<unsigned long> childrenIds;
  model->getChildrenIds (theClass, childrenIds);
  childrenIds.push_back (theClass);
  theObjects.clear();
  for (std::vector<unsigned long>::iterator iC = childrenIds.begin();
       iC != childrenIds.end();
       iC++)
  {
    GERTICO::PublishedClass *publishedClass;
    publishedClass = getPublishedClass (*iC);
    if (publishedClass == NULL)
    {
      continue;
    }
    publishedClass->getObjectIds(theObjects);
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::RunTimeObjectDB::isPrivilegeToDeleteId(const GeRtiFactory::GeRtiHandle &theAttribute)
{
  if (theAttribute == privilegeToDeleteId)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
// Check whether an object instance attribute is subscribed for any object in
// the given region.
// ---------------------------------------------------------------------------
bool GERTICO::RunTimeObjectDB::isRegionSubscribed (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion)
{
  bool ret;

  ret = subscribedClassHolder.isRegionSubscribed(theFederate, theRegion);
  return ret;
}
