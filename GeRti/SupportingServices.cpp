/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** SupportingServices.cpp
**
*******************************************************************************/

#include "SupportingServices.h"
#include "Util/Mapper.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SupportingServices::SupportingServices(GERTICO::ObjectManagement &theObjectManagement, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::ClassDescrHolder &theObjectRoot, GERTICO::ClassDescrHolder &theInteractionRoot, GERTICO::FederatesHolder &theFederatesHolder) : interactionRoot(theInteractionRoot), objectRoot(theObjectRoot), federatesHolder(theFederatesHolder), objectManagement(theObjectManagement), runTimeObjectDB(theRunTimeObjectDB)
{

}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SupportingServices::~SupportingServices(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::disableAttributeScopeAdvisorySwitch(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::Federate *currFederate;

  currFederate = federatesHolder.getFederate(theFederate);
  if (currFederate)
  {
    currFederate->disableAttributeScopeAdvisorySwitch();
    currFederate->setAlive();
  }
  else
  {
    throw GeRtiFactory::RTIinternalError(L"SupportingServices::could not find federate");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::disableClassRelevanceAdvisorySwitch(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::Federate *currFederate;

  currFederate = federatesHolder.getFederate(theFederate);
  if (currFederate)
  {
    currFederate->disableClassRelevanceAdvisorySwitch();
    currFederate->setAlive();
  }
  else
  {
    throw GeRtiFactory::RTIinternalError(L"SupportingServices::could not find federate");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::enableAttributeScopeAdvisorySwitch(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::Federate *currFederate;

  currFederate = federatesHolder.getFederate(theFederate);
  if (currFederate)
  {
    currFederate->enableAttributeScopeAdvisorySwitch();
    currFederate->setAlive();
  }
  else
  {
    throw GeRtiFactory::RTIinternalError(L"SupportingServices::could not find federate");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::enableClassRelevanceAdvisorySwitch(const GeRtiFactory::GeRtiHandle &theFederate)
{
  GERTICO::Federate *currFederate;

  currFederate = federatesHolder.getFederate(theFederate);
  if (currFederate)
  {
    currFederate->enableClassRelevanceAdvisorySwitch();
    currFederate->setAlive();
  }
  else
  {
    throw GeRtiFactory::RTIinternalError(L"SupportingServices::could not find federate");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::SupportingServices::findInteractionName(const GeRtiFactory::GeRtiHandle &theClassHandle, GERTICO::AttributeDatum &theParameterDatum)
{
  GERTICO::ClassDescr *ptrClassDescr;
  std::wstring ret;
#ifdef IEEE_1516
  std::wstring root(L"HLAinteractionRoot.");
#else
  std::wstring root(L"interactionRoot.");
#endif
  unsigned long ul;

  if (theClassHandle == interactionRoot.classDescr->getId())
  {
    theParameterDatum.name = interactionRoot.classDescr->getNameFull();
    interactionRoot.classDescr->getOrdering(ul);
    theParameterDatum.theOrderType = ul;
    interactionRoot.classDescr->getTransportation(ul);
    theParameterDatum.theTransportationType = ul;
#ifdef IEEE_1516
    ret = L"HLAinteractionRoot";
#else
    ret = L"interactionRoot";
#endif
    return ret;
  }

  ptrClassDescr = interactionRoot.getClassDescr(theClassHandle);
  if (ptrClassDescr)
  {
    ret = ptrClassDescr->getNameFull();
    root.append(ret);
    theParameterDatum.name = root;
    ptrClassDescr->getOrdering(ul);
    theParameterDatum.theOrderType = ul;
    ptrClassDescr->getTransportation(ul);
    theParameterDatum.theTransportationType = ul;
    ptrClassDescr->getDimensions(theParameterDatum.theDimensions);
    return root;
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::SupportingServices::findObjectClassName(const GeRtiFactory::GeRtiHandle &theHandle)
{
  std::wstring ret;
#ifdef IEEE_1516
  std::wstring root(L"HLAobjectRoot.");
#else
  std::wstring root(L"objectRoot.");
#endif

  if (theHandle == objectRoot.classDescr->getId())
  {
    std::wstring ws = L"objectRoot";
    return ws;
  }
  
  ret = objectRoot.findClassName(theHandle);
  root.append(ret);

  return root;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServices::findObjectClassHandle(const std::wstring &theName)
{
  GeRtiFactory::GeRtiHandle ret = 0;
  string s;
  GERTICO::Mapper::mapStringFromWstring(s, objectRoot.classDescr->getNameLower());
  if (objectRoot.classDescr->getNameLower() == theName)
  {
    return objectRoot.classDescr->getId ();
  }

  ret = objectRoot.findHandle(theName);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::getAttributeRoutingSpaceHandle(const GeRtiFactory::GeRtiHandle &theAttribute, const GeRtiFactory::GeRtiHandle &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound, bool &theAttributeFound)
{
  runTimeObjectDB.getAttributeRoutingSpaceHandle(theAttribute, theClass, theSpace, theClassFound, theAttributeFound);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServices::getDimensionHandle(
    const std::wstring &theName,
    const GeRtiFactory::GeRtiHandle &whichSpace
  )
{
  GeRtiFactory::GeRtiHandle ret;

  ret = runTimeObjectDB.getDimensionHandle(theName, whichSpace);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::getDimensionName(
    std::wstring &theName,
    const GeRtiFactory::GeRtiHandle &theHandle,
    const GeRtiFactory::GeRtiHandle &whichSpace
  )
{
  runTimeObjectDB.getDimensionName(theName, theHandle, whichSpace);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServices::getInteractionClassHandle(const std::wstring &theName)
{
  GeRtiFactory::GeRtiHandle ret;
  std::wstring buff;
  std::wstring name;

  name = theName;
#ifdef IEEE_1516
  unsigned int pos = 19;
  std::wstring firstPart(name, 0, pos);
  std::wstring interactionroot = L"HLAinteractionRoot.";
#else
  unsigned int pos = 16;
  GERTICO::Mapper::nameToLower(name);
  std::wstring firstPart(name, 0, pos);
  std::wstring interactionroot = L"interactionroot.";
#endif

  if (firstPart == interactionroot)
  {
    std::wstring tmp(name, pos, std::wstring::npos);
    buff = tmp;
  }
  else
  {
    buff = name;
  }

  if (interactionRoot.classDescr->getNameLower() == buff)
  {
    return interactionRoot.classDescr->getId();
  }

  ret = interactionRoot.findHandle(buff);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::getParameterHandle(const std::wstring &theName, const GeRtiFactory::GeRtiHandle &theClass, GeRtiFactory::GeRtiHandle &retId, bool &boolFoundItem, bool &boolFoundClass)
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::Item *currItem;
  std::wstring name;

  classDescr = interactionRoot.classDescr->getClassDescr(theClass);
  if (classDescr == NULL)
  {
    // error
    return;
  }
  boolFoundClass = true;

  name = theName;
  GERTICO::Mapper::nameToLower(name);
  currItem = classDescr->getClassItemByName(name);
  if (currItem)
  {
    boolFoundItem = true;
    retId = currItem->getId ();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::getParameterName(const GeRtiFactory::GeRtiHandle &theId, const GeRtiFactory::GeRtiHandle &theClass, std::wstring &retName, bool &boolFoundItem, bool &boolFoundClass)
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::Item *currItem;

  retName = L"";
  classDescr = interactionRoot.classDescr->getClassDescr(theClass);
  if (classDescr == NULL)
  {
    // error
    return;
  }
  boolFoundClass = true;

  currItem = classDescr->getClassItem (theId);
  if (currItem)
  {
    boolFoundItem = true;
    retName = currItem->myName;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegisteredObject *GERTICO::SupportingServices::getObjectById(const GeRtiFactory::GeRtiHandle &theObjectId)
{
  GERTICO::RegisteredObject *currObject = runTimeObjectDB.getObject(theObjectId);

  return currObject;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegisteredObject *GERTICO::SupportingServices::getObjectByName(const std::wstring &theObjectName)
{
  GERTICO::RegisteredObject *currObject = objectManagement.getObjectByName(theObjectName);

  return currObject;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServices::getObjectClass(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject)
{
  GERTICO::Federate *currFederate;
  GeRtiFactory::GeRtiHandle ret = 0;

  currFederate = federatesHolder.getFederate(theFederate);
  if (currFederate)
  {
    ret = currFederate->getObjectClass(theObject);
    currFederate->setAlive();
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::getLRCattributeFlags(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::LRCattributeFlagsMap &theLRCattributeFlagsMap)
{
  objectRoot.getLRCattributeFlags(theClass, theLRCattributeFlagsMap);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SupportingServices::getLRCparameterFlags(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::LRCparameterFlagsMap &theLRCparameterFlagsMap)
{
  return interactionRoot.getLRCparameterFlags(theClass, theLRCparameterFlagsMap);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::getObjectClassItem(const std::wstring &theName, const GeRtiFactory::GeRtiHandle &theClass, GeRtiFactory::GeRtiHandle &retId, bool &boolFoundItem, bool &boolFoundClass)
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::Item *currItem;
  std::wstring tmpName(theName);

  classDescr = objectRoot.getClassDescr(theClass);
  if (classDescr == NULL)
  {
    // error
    return;
  }
  boolFoundClass = true;

  GERTICO::Mapper::nameToLower(tmpName);
  currItem = classDescr->getClassItemByName(tmpName.c_str());
  if (currItem)
  {
    boolFoundItem = true;
    retId = currItem->getId ();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::getObjectClassItem(const GeRtiFactory::GeRtiHandle &theId, const GeRtiFactory::GeRtiHandle &theClass, std::wstring &retName, bool &boolFoundItem, bool &boolFoundClass)
{
  GERTICO::ClassDescr *classDescr;
  GERTICO::Item *currItem;

  retName = L"";
  classDescr = objectRoot.getClassDescr (theClass);
  if (classDescr == NULL)
  {
    // error
    return;
  }
  boolFoundClass = true;

  currItem = classDescr->getClassItem (theId);
  if (currItem)
  {
    boolFoundItem = true;
    retName = currItem->myName;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServices::getInteractionParent(const GeRtiFactory::GeRtiHandle &theHandle)
{
  GERTICO::ClassDescr *classDescr;

  classDescr = interactionRoot.getClassDescr(theHandle);
  classDescr = classDescr->parent;
  if (classDescr == NULL)
  {
    GeRtiFactory::GeRtiHandle zero = 0;
    return zero;
  }
  return classDescr->getId();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServices::getObjectParent(const GeRtiFactory::GeRtiHandle &theHandle)
{
  GERTICO::ClassDescr *classDescr;

  classDescr = objectRoot.getClassDescr(theHandle);
  classDescr = classDescr->parent;
  if (classDescr == NULL)
  {
    GeRtiFactory::GeRtiHandle zero = 0;
    return zero;
  }
  return classDescr->getId();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServices::getRoutingSpaceHandle(const std::wstring &theName)
{
  return runTimeObjectDB.getRoutingSpaceHandle(theName);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::SupportingServices::getRoutingSpaceName(const GeRtiFactory::GeRtiHandle &theHandle)
{
  return runTimeObjectDB.getRoutingSpaceName(theHandle);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServices::setRangeBounds(GeRtiFactory::GeRtiHandle const &theRegionHandle, GeRtiFactory::GeRtiHandle const &theDimensionHandle, GeRtiFactory::GeRtiHandle const &theLowerBound, GeRtiFactory::GeRtiHandle const &theUpperBound)
{
  runTimeObjectDB.setRangeBounds(theRegionHandle, theDimensionHandle, theLowerBound, theUpperBound);
}
