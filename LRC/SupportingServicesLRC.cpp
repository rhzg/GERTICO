/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** SupportingServicesLRC.cpp
**
*******************************************************************************/

#include "SupportingServicesLRC.h"
#include <iostream>

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SupportingServicesLRC::SupportingServicesLRC(GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmbassador_var)
{
  // Default switch settings.
  attributeRelevanceAdvisorySwitch = false;
  attributeScopeAdvisorySwitch = false;
  classRelevanceAdvisorySwitch = true;
  interactionRelevanceAdvisorySwitch = true;

  GeRtiAmbVar = GeRtiFactory::GeRtiAmbassador::_duplicate(theGeRtiAmbassador_var);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SupportingServicesLRC::~SupportingServicesLRC(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::addCacheObjectNameAttribute(GeRtiFactory::GeRtiHandle const &theObjectClass, GeRtiFactory::GeRtiHandle const &theAttribute, std::wstring const &theName)
{
  GERTICO::HandleWstringHandleMap::iterator itCacheObjectNameAttribute;
#ifndef IEEE_1516
  std::wstring lowercase(theName);
#endif


  itCacheObjectNameAttribute = cacheObjectNameAttribute.find(theObjectClass);
  if (itCacheObjectNameAttribute == cacheObjectNameAttribute.end())
  {
    GERTICO::WstringHandleMap nameHandle;
#ifdef IEEE_1516
    nameHandle[theName] = theAttribute;
#else
    GERTICO::Mapper::nameToLower(lowercase);
    nameHandle[lowercase] = theAttribute;
#endif
    cacheObjectNameAttribute[theObjectClass] = nameHandle;
  }
  else
  {
    GERTICO::WstringHandleMap *nameAttributePtr;
    GERTICO::WstringHandleMap::iterator itNameAttribute;

    nameAttributePtr = &itCacheObjectNameAttribute->second;
#ifdef IEEE_1516
    itNameAttribute = nameAttributePtr->find(theName);
#else
    itNameAttribute = nameAttributePtr->find(lowercase);
#endif
    if (itNameAttribute == nameAttributePtr->end())
    {
#ifdef IEEE_1516
      (*nameAttributePtr)[theName] = theAttribute;
#else
      (*nameAttributePtr)[lowercase] = theAttribute;
#endif
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::addCacheObjectAttributeData(GeRtiFactory::GeRtiHandle const &theObjectClass, GeRtiFactory::GeRtiHandle const &theAttribute, std::wstring const &theName, GeRtiFactory::GeRtiHandle const &theOrderType, GeRtiFactory::GeRtiHandle const &theTransportationType, GeRtiFactory::Handles theDimensions)
{
  GERTICO::AttributeDataMap::iterator itCacheObjectAttributeName;

  GERTICO::AttributeDatum attributeDatum;
  attributeDatum.name = theName;
  GERTICO::Mapper::mapHandleSet(attributeDatum.theDimensions, theDimensions);
  attributeDatum.theOrderType = theOrderType;
  attributeDatum.theTransportationType = theTransportationType;

  itCacheObjectAttributeName = cacheObjectAttributeData.find(theObjectClass);
  if (itCacheObjectAttributeName == cacheObjectAttributeData.end())
  {
    GERTICO::AttributeDatumMap attributeDatumMap;

    attributeDatumMap[theAttribute] = attributeDatum;
    cacheObjectAttributeData[theObjectClass] = attributeDatumMap;
  }
  else
  {
    GERTICO::AttributeDatumMap *attributeDatumPtr;
    GERTICO::AttributeDatumMap::iterator itAttributeDatumMap;

    attributeDatumPtr = &itCacheObjectAttributeName->second;
    itAttributeDatumMap = attributeDatumPtr->find(theAttribute);
    if (itAttributeDatumMap == attributeDatumPtr->end())
    {
      (*attributeDatumPtr)[theAttribute] = attributeDatum;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::checkAttributeNotDefined(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len = theAttributes.length();
  std::wstring ws;

  for (i = 0; i < len; i++)
  {
    ws = getAttributeName(theAttributes[i], theClass);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::checkAttributeNotDefined(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttributes)
{
  GERTICO::HandleSetMap::iterator itHandleSetMap;
  std::wstring ws;

  for (itHandleSetMap = theAttributes.begin(); itHandleSetMap != theAttributes.end(); itHandleSetMap++)
  {
    ws = getAttributeName(itHandleSetMap->first, theClass);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::clear(void)
{
  cacheInteractionClassInteractionData.clear();
  cacheNameInteractionClass.clear();
  cacheInteractionNameParameter.clear();
  cacheInteractionParameterName.clear();

  cacheObjectClassName.clear();
  cacheNameObjectClass.clear();
  cacheObjectNameAttribute.clear();
  cacheObjectAttributeData.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::disableAttributeRelevanceAdvisorySwitch(void)
{
  CORBA::WChar *buff = L"disableAttributeRelevanceAdvisorySwitch";

#ifdef IEEE_1516
  if (attributeRelevanceAdvisorySwitch == false)
  {
    throw GeRtiFactory::AttributeRelevanceAdvisorySwitchIsOff(buff);
  }
#endif

  attributeRelevanceAdvisorySwitch = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::disableAttributeScopeAdvisorySwitch(void)
{
  attributeScopeAdvisorySwitch = false;
  GeRtiAmbVar->disableAttributeScopeAdvisorySwitch();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::disableClassRelevanceAdvisorySwitch(void)
{
  classRelevanceAdvisorySwitch = false;
  GeRtiAmbVar->disableClassRelevanceAdvisorySwitch();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::disableInteractionRelevanceAdvisorySwitch(void)
{
  interactionRelevanceAdvisorySwitch = false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::enableAttributeRelevanceAdvisorySwitch(void)
{
  CORBA::WChar *buff = L"enableAttributeRelevanceAdvisorySwitch";

#ifdef IEEE_1516
  if (attributeRelevanceAdvisorySwitch)
  {
    throw GeRtiFactory::AttributeRelevanceAdvisorySwitchIsOn(buff);
  }
#endif

  attributeRelevanceAdvisorySwitch = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::enableAttributeScopeAdvisorySwitch(void)
{
  attributeScopeAdvisorySwitch = true;
  GeRtiAmbVar->enableAttributeScopeAdvisorySwitch();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::enableClassRelevanceAdvisorySwitch(void)
{
  classRelevanceAdvisorySwitch = true;
  GeRtiAmbVar->enableClassRelevanceAdvisorySwitch();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::enableInteractionRelevanceAdvisorySwitch(void)
{
  interactionRelevanceAdvisorySwitch = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SupportingServicesLRC::getAttributeRelevanceAdvisorySwitch(void)
{
  return attributeRelevanceAdvisorySwitch;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SupportingServicesLRC::getAttributeScopeAdvisorySwitch(void)
{
  return attributeScopeAdvisorySwitch;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SupportingServicesLRC::getClassRelevanceAdvisorySwitch(void)
{
  return classRelevanceAdvisorySwitch;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SupportingServicesLRC::getInteractionRelevanceAdvisorySwitch(void)
{
  return interactionRelevanceAdvisorySwitch;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::fillInteractionParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles_var &theParents)
{
  CORBA::ULong childClass;
  CORBA::ULong currClass;
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong len;
  GERTICO::HandleSet dummyHandleSet;
  GERTICO::HandleMap::iterator itHandleMap;
  GERTICO::HandleSetMap::iterator itHandleSetSetMap;

  // Build a chain of classes to interaction root class.
  currClass = theClass;
  len = theParents->length();
  for (i = 0; i < len; i++)
  {
    itHandleMap = parentsInteraction.find(currClass);
    if (itHandleMap == parentsInteraction.end())
    {
      parentsInteraction[currClass] = theParents[i];
      currClass = theParents[i];
    }
    itHandleSetSetMap = childrenInteraction.find(currClass);
    if (itHandleSetSetMap == childrenInteraction.end())
    {
      childrenInteraction[currClass] = dummyHandleSet;
    }
  }

  // For each object class add all known sub-classes.
  for (i = 0; i < len; i++)
  {
    childClass = theClass;
    currClass = theParents[i];
    itHandleSetSetMap = childrenInteraction.find(currClass);
    if (itHandleSetSetMap != childrenInteraction.end())
    {
      for (j = 0; j < i + 1; j++)
      {
        itHandleSetSetMap->second.insert(childClass);
        childClass = theParents[j];
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::fillObjectParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles_var &theParents)
{
  CORBA::ULong childClass;
  CORBA::ULong currClass;
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong len;
  GERTICO::HandleSet dummyHandleSet;
  GERTICO::HandleMap::iterator itHandleMap;
  GERTICO::HandleSetMap::iterator itHandleSetSetMap;

  currClass = theClass;
  len = theParents->length();
  for (i = 0; i < len; i++)
  {
    itHandleMap = parentsObject.find(currClass);
    if (itHandleMap == parentsObject.end())
    {
      parentsObject[currClass] = theParents[i];
      currClass = theParents[i];
    }
    itHandleSetSetMap = childrenObjectClass.find(currClass);
    if (itHandleSetSetMap == childrenObjectClass.end())
    {
      childrenObjectClass[currClass] = dummyHandleSet;
    }
  }

  // For each interaction class add all known sub-classes.
  for (i = 0; i < len; i++)
  {
    childClass = theClass;
    currClass = theParents[i];
    itHandleSetSetMap = childrenObjectClass.find(currClass);
    if (itHandleSetSetMap != childrenObjectClass.end())
    {
      for (j = 0; j < i + 1; j++)
      {
        itHandleSetSetMap->second.insert(childClass);
        childClass = theParents[j];
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getAttributeHandle(std::wstring const &theName, GeRtiFactory::GeRtiHandle const &whichClass)
{
  CORBA::WChar *name;
  GERTICO::HandleWstringHandleMap::iterator itCacheObjectNameAttribute;
  GeRtiFactory::GeRtiHandle ret = 0;
#ifndef IEEE_1516
  std::wstring lowercase(theName);
  GERTICO::Mapper::nameToLower(lowercase);
#endif

  itCacheObjectNameAttribute = cacheObjectNameAttribute.find(whichClass);
  if (itCacheObjectNameAttribute != cacheObjectNameAttribute.end())
  {
    GERTICO::WstringHandleMap *nameAttributePtr;
    GERTICO::WstringHandleMap::iterator itNameAttribute;

    nameAttributePtr = &itCacheObjectNameAttribute->second;
#ifdef IEEE_1516
    itNameAttribute = nameAttributePtr->find(theName);
#else
    itNameAttribute = nameAttributePtr->find(lowercase);
#endif
    if (itNameAttribute != nameAttributePtr->end())
    {
      ret = itNameAttribute->second;
    }
    else
    {
      GERTICO::Mapper::mapWcharFromWstring(&name, theName);
      ret = GeRtiAmbVar->getAttributeHandle(name, whichClass);
      CORBA::wstring_free(name);
#ifdef IEEE_1516
      (*nameAttributePtr)[theName] = ret;
#else
      (*nameAttributePtr)[lowercase] = ret;
#endif
    }
  }
  else
  {
    GERTICO::Mapper::mapWcharFromWstring(&name, theName);
    ret = GeRtiAmbVar->getAttributeHandle(name, whichClass);
    CORBA::wstring_free(name);
    GERTICO::WstringHandleMap nameHandle;
#ifdef IEEE_1516
    nameHandle[theName] = ret;
#else
    nameHandle[lowercase] = ret;
#endif
    cacheObjectNameAttribute[whichClass] = nameHandle;
  }

#ifdef IEEE_1516
  GERTICO::AttributeDataMap::iterator itCacheObjectAttributeName;

  itCacheObjectAttributeName = cacheObjectAttributeData.find(whichClass);
  if (itCacheObjectAttributeName != cacheObjectAttributeData.end())
  {
    GERTICO::AttributeDatumMap *attributeNamePtr;
    GERTICO::AttributeDatumMap::iterator itHandleWstring;

    attributeNamePtr = &itCacheObjectAttributeName->second;
    itHandleWstring = attributeNamePtr->find(ret);
    if (itHandleWstring == attributeNamePtr->end())
    {
      GeRtiFactory::GeRtiHandle objectClassHandle;
      std::wstring objectClassName;

      objectClassName = getObjectClassName(whichClass);
      objectClassHandle = getObjectClassHandle(objectClassName);
    }
  }
  else
  {
    GeRtiFactory::GeRtiHandle objectClassHandle;
    std::wstring objectClassName;

    objectClassName = getObjectClassName(whichClass);
    objectClassHandle = getObjectClassHandle(objectClassName);
  }
#endif

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::SupportingServicesLRC::getAttributeName(GeRtiFactory::GeRtiHandle const &theHandle, GeRtiFactory::GeRtiHandle const &whichClass)
{
  CORBA::WChar *name;
  GERTICO::AttributeDataMap::iterator itCacheObjectAttributeName;
  std::wstring ret;
  std::wstring ws;

  ws = getObjectClassName(whichClass);

  itCacheObjectAttributeName = cacheObjectAttributeData.find(whichClass);
  if (itCacheObjectAttributeName != cacheObjectAttributeData.end())
  {
    GERTICO::AttributeDatumMap::iterator itHandleWstring;
    GERTICO::AttributeDatumMap *attributeNamePtr;
    attributeNamePtr = &itCacheObjectAttributeName->second;
    itHandleWstring = attributeNamePtr->find(theHandle);
    if (itHandleWstring != attributeNamePtr->end())
    {
      ret = itHandleWstring->second.name;
    }
    else
    {
      GeRtiFactory::GeRtiHandle objectClassHandle;
      std::wstring objectClassName;
      
      name = GeRtiAmbVar->getAttributeName(theHandle, whichClass);
      GERTICO::Mapper::mapWstringFromWchar(ret, name);

      objectClassName = getObjectClassName(whichClass);
      objectClassHandle = getObjectClassHandle(objectClassName);
    }
  }
  else
  {
    GeRtiFactory::GeRtiHandle objectClassHandle;
    std::wstring objectClassName;
      
    name = GeRtiAmbVar->getAttributeName(theHandle, whichClass);
    GERTICO::Mapper::mapWstringFromWchar(ret, name);

    objectClassName = getObjectClassName(whichClass);
    objectClassHandle = getObjectClassHandle(objectClassName);
  }

#ifndef IEEE_1516
  GERTICO::HandleWstringHandleMap::iterator itCacheObjectNameAttribute;
  std::wstring lowercase(ret);

  GERTICO::Mapper::nameToLower(lowercase);
  itCacheObjectNameAttribute = cacheObjectNameAttribute.find(whichClass);
  if (itCacheObjectNameAttribute != cacheObjectNameAttribute.end())
  {
    GERTICO::WstringHandleMap *nameAttributePtr;
    GERTICO::WstringHandleMap::iterator itNameAttribute;

    nameAttributePtr = &itCacheObjectNameAttribute->second;
    itNameAttribute = nameAttributePtr->find(lowercase);
    if (itNameAttribute == nameAttributePtr->end())
    {
      (*nameAttributePtr)[lowercase] = theHandle;
    }
  }
  else
  {
    GERTICO::WstringHandleMap nameHandle;
    nameHandle[lowercase] = theHandle;
    cacheObjectNameAttribute[whichClass] = nameHandle;
  }
#endif

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getAttributeRoutingSpaceHandle(GeRtiFactory::GeRtiHandle const &theHandle, GeRtiFactory::GeRtiHandle const &whichClass)
{
  GeRtiFactory::GeRtiHandle ret;

  ret = GeRtiAmbVar->getAttributeRoutingSpaceHandle(theHandle, whichClass);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::getAvailableDimensionsForClassAttribute(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theAttribute, GeRtiFactory::Handles &theDimensions)
{
  GeRtiFactory::Handles *handlesPtr;

  handlesPtr = GeRtiAmbVar->getAvailableDimensionsForClassAttribute(theClass, theAttribute);

  theDimensions = *handlesPtr;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::getAvailableDimensionsForInteractionClass(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles &theDimensions)
{
  GeRtiFactory::Handles *handlesPtr;

  handlesPtr = GeRtiAmbVar->getAvailableDimensionsForInteractionClass(theClass);

  theDimensions = *handlesPtr;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getDimensionHandle(std::wstring const &theName, GeRtiFactory::GeRtiHandle const &whichSpace)
{
  CORBA::WChar *name;
  GeRtiFactory::GeRtiHandle ret = 0;

  GERTICO::Mapper::mapWcharFromWstring(&name, theName);
  ret = GeRtiAmbVar->getDimensionHandle(name, whichSpace);
  CORBA::wstring_free(name);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::getDimensionHandleSet(GeRtiFactory::GeRtiHandle const &theRegionHandle, GeRtiFactory::Handles &theDimensions)
{
  GeRtiFactory::Handles *handlesPtr;

  handlesPtr = GeRtiAmbVar->getDimensionHandleSet(theRegionHandle);

  theDimensions = *handlesPtr;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::SupportingServicesLRC::getDimensionName(GeRtiFactory::GeRtiHandle const &theHandle, GeRtiFactory::GeRtiHandle const &whichSpace)
{
  CORBA::WChar *name;
  std::wstring ret;

  name = GeRtiAmbVar->getDimensionName(theHandle, whichSpace);
  GERTICO::Mapper::mapWstringFromWchar(ret, name);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getDimensionUpperBound(GeRtiFactory::GeRtiHandle const &theHandle)
{
  GeRtiFactory::GeRtiHandle ret = 0;

  ret = GeRtiAmbVar->getDimensionUpperBound(theHandle);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SupportingServicesLRC::getInteractionAttributeDatum(GeRtiFactory::GeRtiHandle const &whichClass, GERTICO::AttributeDatum &parameterDatum)
{
  GERTICO::AttributeDatumMap::iterator itCacheInteractionClassInteractionData;

  std::wstring dummy = getInteractionClassName(whichClass);

  itCacheInteractionClassInteractionData = cacheInteractionClassInteractionData.find(whichClass);
  if (itCacheInteractionClassInteractionData != cacheInteractionClassInteractionData.end())
  {
    parameterDatum = itCacheInteractionClassInteractionData->second;
    return false;
  }

  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::getInteractionChildren(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theChildren)
{
  GERTICO::HandleSetMap::iterator itHandleSetMap;

  itHandleSetMap = childrenInteraction.find(theClass);
  if (itHandleSetMap != childrenInteraction.end())
  {
    theChildren = itHandleSetMap->second;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::getInteractionParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles &theParents)
{
  CORBA::ULong iClass;
  CORBA::ULong ind = 0;
  CORBA::ULong length;

  // Just get some useful memory for faster filling.
  length = 16;
  theParents.length(length);
  length = 0;
  theParents.length(length);

  iClass = theClass;
  for (iClass = getInteractionParent(iClass); iClass != 0; iClass = getInteractionParent(iClass), ind++)
  {
    theParents.length(ind + 1);
    theParents[ind] = iClass;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::getObjectClassChildren(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theChildren)
{
  GERTICO::HandleSetMap::iterator itHandleSetMap;

  itHandleSetMap = childrenObjectClass.find(theClass);
  if (itHandleSetMap != childrenObjectClass.end())
  {
    theChildren = itHandleSetMap->second;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::getObjectClassParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles &theParents)
{
  CORBA::ULong iClass;
  CORBA::ULong ind = 0;
  CORBA::ULong length;

  // Just get some useful memory for faster filling.
  length = 16;
  theParents.length(length);
  length = 0;
  theParents.length(length);

  iClass = theClass;
  for (iClass = getObjectParent(iClass); iClass != 0; iClass = getObjectParent(iClass), ind++)
  {
    theParents.length(ind + 1);
    theParents[ind] = iClass;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getInteractionClassHandle(std::wstring const &theName)
{
  CORBA::ULong i;
  CORBA::ULong length;
  CORBA::WChar *name;
  GERTICO::AttributeDatum attributeDatum;
  GERTICO::HandleHandleWstringMap::iterator itHandleHandleWstringMap;
  GERTICO::HandleWstringHandleMap::iterator itHandleWstringHandleMap;
  GERTICO::HandleWstringMap handleWstringMap;
  GERTICO::WstringHandleMap wstringHandleMap;
  GERTICO::WstringHandleMap::iterator itCacheNameInteraction;
  GeRtiFactory::GeRtiHandle ret = 0;
  GeRtiFactory::Handles_var parents;
  GeRtiFactory::InteractionClassData_var interactionData;
  GeRtiFactory::ParametersClassData_var parameterData;
#ifdef IEEE_1516
  std::wstring root(L"HLAinteractionRoot.");
#else
  std::wstring root(L"interactionRoot.");
#endif
  std::wstring s;
  size_t size;

  size = root.size();
#ifdef IEEE_1516
  if (theName.compare(0, size, root) == 0)
  {
    s = theName;
  }
  else
  {
    s = root;
    s.append(theName);
  }
  itCacheNameInteraction = cacheNameInteractionClass.find(s);
#else
  std::wstring lowercase(theName);
  GERTICO::Mapper::nameToLower(lowercase);
  if (lowercase.compare(0, size, root) == 0)
  {
    s = lowercase;
  }
  else
  {
    s = root;
    s.append(lowercase);
  }
  itCacheNameInteraction = cacheNameInteractionClass.find(s);
#endif
  if (itCacheNameInteraction != cacheNameInteractionClass.end())
  {
    ret = itCacheNameInteraction->second;
  }
  else
  {
    GERTICO::Mapper::mapWcharFromWstring(&name, s);
    ret = GeRtiAmbVar->getInteractionClassHandle(name, parents, interactionData, parameterData);
    CORBA::wstring_free(name);
    fillInteractionParents(ret, parents);
    attributeDatum.name = interactionData->name;
    attributeDatum.theOrderType = interactionData->theOrderType;
    attributeDatum.theTransportationType = interactionData->theTransportationType;
    GERTICO::Mapper::mapHandleSet(attributeDatum.theDimensions, interactionData->theDimensions);
    cacheInteractionClassInteractionData[ret] = attributeDatum;
    itHandleWstringHandleMap = cacheInteractionNameParameter.find(ret);
    if (itHandleWstringHandleMap == cacheInteractionNameParameter.end())
    {
      length = parameterData->length();
      for (i = 0; i < length; i++)
      {
        s = parameterData[i].name;
#ifndef IEEE_1516
        GERTICO::Mapper::nameToLower(s);
#endif
        wstringHandleMap[s] = parameterData[i].theId;
      }
      cacheInteractionNameParameter[ret] = wstringHandleMap;
    }
    itHandleHandleWstringMap = cacheInteractionParameterName.find(ret);
    if (itHandleHandleWstringMap == cacheInteractionParameterName.end())
    {
      length = parameterData->length();
      for (i = 0; i < length; i++)
      {
        handleWstringMap[parameterData[i].theId] = parameterData[i].name;
      }
      cacheInteractionParameterName[ret] = handleWstringMap;
    }
    cacheNameInteractionClass[s] = ret;
//    std::cout << "id " << interactionData->theId << std::endl;
//    s = interactionData->name;
//    std::wcout << L"name " << s << std::endl;
//    std::cout << "theOrderType " << interactionData->theOrderType << std::endl;
//    std::cout << "theTransportationType " << interactionData->theTransportationType << std::endl;
//    length = interactionData->theDimensions.length();
//    for (i = 0; i < length; i++)
//    {
//      std::cout << "dimension " << interactionData->theDimensions[i] << std::endl;
//    }
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::SupportingServicesLRC::getInteractionClassName(GeRtiFactory::GeRtiHandle const &theHandle)
{
  CORBA::ULong i;
  CORBA::ULong length;
  CORBA::WChar *name;
  GERTICO::AttributeDatum *ptrAttributeDatum;
  GERTICO::HandleHandleWstringMap::iterator itHandleHandleWstringMap;
  GERTICO::HandleWstringHandleMap::iterator itHandleWstringHandleMap;
  GERTICO::HandleWstringMap handleWstringMap;
  GERTICO::WstringHandleMap wstringHandleMap;
  GeRtiFactory::Handles_var parents;
  GeRtiFactory::InteractionClassData_var interactionData;
  GeRtiFactory::ParametersClassData_var parameterData;
  GERTICO::AttributeDatumMap::iterator itCacheInteractionDatum;
  std::wstring ret;
  std::wstring s;

  itCacheInteractionDatum = cacheInteractionClassInteractionData.find(theHandle);
  if (itCacheInteractionDatum != cacheInteractionClassInteractionData.end())
  {
    ptrAttributeDatum = &itCacheInteractionDatum->second;
    ret = ptrAttributeDatum->name;
  }
  else
  {
    GERTICO::AttributeDatum attributeDatum;
    name = GeRtiAmbVar->getInteractionClassName(theHandle, parents, interactionData, parameterData);
    GERTICO::Mapper::mapWstringFromWchar(ret, name);
    fillInteractionParents(theHandle, parents);
    attributeDatum.name = interactionData->name;
    attributeDatum.theOrderType = interactionData->theOrderType;
    attributeDatum.theTransportationType = interactionData->theTransportationType;
    GERTICO::Mapper::mapHandleSet(attributeDatum.theDimensions, interactionData->theDimensions);
    cacheInteractionClassInteractionData[theHandle] = attributeDatum;
    itHandleWstringHandleMap = cacheInteractionNameParameter.find(theHandle);
    if (itHandleWstringHandleMap == cacheInteractionNameParameter.end())
    {
      length = parameterData->length();
      for (i = 0; i < length; i++)
      {
        s = parameterData[i].name;
#ifndef IEEE_1516
        GERTICO::Mapper::nameToLower(s);
#endif
        wstringHandleMap[s] = parameterData[i].theId;
      }
      cacheInteractionNameParameter[theHandle] = wstringHandleMap;
    }
    itHandleHandleWstringMap = cacheInteractionParameterName.find(theHandle);
    if (itHandleHandleWstringMap == cacheInteractionParameterName.end())
    {
      length = parameterData->length();
      for (i = 0; i < length; i++)
      {
        handleWstringMap[parameterData[i].theId] = parameterData[i].name;
      }
      cacheInteractionParameterName[theHandle] = handleWstringMap;
    }
#ifdef IEEE_1516
    cacheNameInteractionClass[ret] = theHandle;
#else
    GERTICO::WstringHandleMap::iterator itCacheNameInteraction;
    std::wstring lowercase(ret);

    GERTICO::Mapper::nameToLower(lowercase);
    itCacheNameInteraction = cacheNameInteractionClass.find(lowercase);
    if (itCacheNameInteraction == cacheNameInteractionClass.end())
    {
      cacheNameInteractionClass[lowercase] = theHandle;
    }
#endif
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getInteractionRoutingSpaceHandle(GeRtiFactory::GeRtiHandle const &theHandle)
{
  GeRtiFactory::GeRtiHandle ret = 0;

  ret = GeRtiAmbVar->getInteractionRoutingSpaceHandle(theHandle);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getObjectClass(GeRtiFactory::GeRtiHandle const &theObject)
{
  GeRtiFactory::GeRtiHandle ret = 0;

  ret = GeRtiAmbVar->getObjectClass(theObject);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getObjectClassHandle(std::wstring const &theName)
{
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::WChar *name;
  GERTICO::WstringHandleMap::iterator itCacheNameObject;
  GeRtiFactory::GeRtiHandle ret = 0;
  GeRtiFactory::Handles_var parents;
  GeRtiFactory::ItemsClassData_var attributes;
#ifdef IEEE_1516
  std::wstring root(L"HLAobjectRoot.");
#else
  std::wstring root(L"objectRoot.");
#endif
  std::wstring s;
  size_t size;

  size = root.size();
#ifdef IEEE_1516
  if (theName.compare(0, size, root) == 0)
  {
    s = theName;
  }
  else
  {
    s = root;
    s.append(theName);
  }
  itCacheNameObject = cacheNameObjectClass.find(s);
#else
  std::wstring lowercase(theName);
  GERTICO::Mapper::nameToLower(lowercase);
  if (lowercase.compare(0, size, root) == 0)
  {
    s = lowercase;
  }
  else
  {
    s = root;
    s.append(lowercase);
  }
  itCacheNameObject = cacheNameObjectClass.find(lowercase);
#endif
  if (itCacheNameObject != cacheNameObjectClass.end())
  {
    ret = itCacheNameObject->second;
  }
  else
  {
    GERTICO::Mapper::mapWcharFromWstring(&name, s);
    ret = GeRtiAmbVar->getObjectClassHandle(name, parents, attributes);
    CORBA::wstring_free(name);
    cacheNameObjectClass[s] = ret;
#ifdef IEEE_1516
    cacheObjectClassName[ret] = s;
#endif
    fillObjectParents(ret, parents);
    len = attributes->length();
    for (i = 0; i < len; i++)
    {
      s = attributes[i].name;
      addCacheObjectNameAttribute(ret, attributes[i].theId, s);
      addCacheObjectAttributeData(ret, attributes[i].theId, s, attributes[i].theOrderType, attributes[i].theTransportationType, attributes[i].theDimensions);

//      std::cout << "id " << attributes[i].theId << std::endl;
//      s = attributes[i].name;
//      std::wcout << L"name " << s << std::endl;
//      std::cout << "theOrderType " << attributes[i].theOrderType << std::endl;
//      std::cout << "theTransportationType " << attributes[i].theTransportationType << std::endl;
//      lenj = attributes[i].theDimensions.length();
//      for (j = 0; j < lenj; j++)
//      {
//        std::cout << "dimension " << attributes[i].theDimensions[j] << std::endl;
//      }
    }
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::SupportingServicesLRC::getObjectClassName(GeRtiFactory::GeRtiHandle const &theHandle)
{
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::WChar *name;
  GERTICO::HandleWstringMap::iterator itCacheObjectName;
  GeRtiFactory::Handles_var parents;
  GeRtiFactory::ItemsClassData_var attributes;
  std::wstring ret;
  std::wstring s;

  itCacheObjectName = cacheObjectClassName.find(theHandle);
  if (itCacheObjectName != cacheObjectClassName.end())
  {
    ret = itCacheObjectName->second;
  }
  else
  {
    name = GeRtiAmbVar->getObjectClassName(theHandle, parents, attributes);
    GERTICO::Mapper::mapWstringFromWchar(ret, name);
    cacheObjectClassName[theHandle] = ret;
#ifdef IEEE_1516
    cacheNameObjectClass[ret] = theHandle;
#else
    GERTICO::WstringHandleMap::iterator itCacheNameObject;
    std::wstring lowercase(ret);

    GERTICO::Mapper::nameToLower(lowercase);
    itCacheNameObject = cacheNameObjectClass.find(lowercase);
    if (itCacheNameObject == cacheNameObjectClass.end())
    {
      cacheNameObjectClass[lowercase] = theHandle;
    }
#endif
    fillObjectParents(theHandle, parents);
    len = attributes->length();
    for (i = 0; i < len; i++)
    {
      s = attributes[i].name;
      addCacheObjectNameAttribute(theHandle, attributes[i].theId, s);
      addCacheObjectAttributeData(theHandle, attributes[i].theId, s, attributes[i].theOrderType, attributes[i].theTransportationType, attributes[i].theDimensions);

//      std::cout << "id " << attributes[i].theId << std::endl;
//      s = attributes[i].name;
//      std::wcout << L"name " << s << std::endl;
//      std::cout << "theOrderType " << attributes[i].theOrderType << std::endl;
//      std::cout << "theTransportationType " << attributes[i].theTransportationType << std::endl;
//      lenj = attributes[i].theDimensions.length();
//      for (j = 0; j < lenj; j++)
//      {
//        std::cout << "dimension " << attributes[i].theDimensions[j] << std::endl;
//      }
    }
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::getObjectClassAttributeDataMap(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::AttributeDatumMap &theAttributeDatumMap)
{
  GERTICO::AttributeDataMap::iterator itAttributeDataMap;
  GERTICO::HandleSet::iterator itHandleSet;

  itAttributeDataMap = cacheObjectAttributeData.find(theClass);
  if (itAttributeDataMap != cacheObjectAttributeData.end())
  {
    theAttributeDatumMap = itAttributeDataMap->second;
  }
  else
  {
    theAttributeDatumMap.clear();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getObjectInstanceHandle(std::wstring const &theName)
{
  CORBA::WChar *name;
  GeRtiFactory::GeRtiHandle ret = 0;

  GERTICO::Mapper::mapWcharFromWstring(&name, theName);
  ret = GeRtiAmbVar->getObjectInstanceHandle(name);
  CORBA::wstring_free(name);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::SupportingServicesLRC::getObjectInstanceName(GeRtiFactory::GeRtiHandle const &theHandle)
{
  CORBA::WChar *name = NULL;
  std::wstring ret;

  name = GeRtiAmbVar->getObjectInstanceName(theHandle);
  GERTICO::Mapper::mapWstringFromWchar(ret, name);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getParameterHandle(std::wstring const &theName, GeRtiFactory::GeRtiHandle const &whichClass)
{
  CORBA::WChar *name;
  GERTICO::HandleWstringHandleMap::iterator itCacheInteractionNameParameter;
  GeRtiFactory::GeRtiHandle ret = 0;
#ifndef IEEE_1516
  std::wstring lowercase(theName);
  GERTICO::Mapper::nameToLower(lowercase);
#endif

  std::wstring dummy = getInteractionClassName(whichClass);

  itCacheInteractionNameParameter = cacheInteractionNameParameter.find(whichClass);
  if (itCacheInteractionNameParameter != cacheInteractionNameParameter.end())
  {
    GERTICO::WstringHandleMap *nameParameterPtr;
    GERTICO::WstringHandleMap::iterator itNameParameter;

    nameParameterPtr = &itCacheInteractionNameParameter->second;
#ifdef IEEE_1516
    itNameParameter = nameParameterPtr->find(theName);
#else
    itNameParameter = nameParameterPtr->find(lowercase);
#endif
    if (itNameParameter != nameParameterPtr->end())
    {
      ret = itNameParameter->second;
    }
    else
    {
      GERTICO::Mapper::mapWcharFromWstring(&name, theName);
      ret = GeRtiAmbVar->getParameterHandle(name, whichClass);
      CORBA::wstring_free(name);
#ifdef IEEE_1516
      (*nameParameterPtr)[theName] = ret;
#else
      (*nameParameterPtr)[lowercase] = ret;
#endif
    }
  }
  else
  {
    GERTICO::Mapper::mapWcharFromWstring(&name, theName);
    ret = GeRtiAmbVar->getParameterHandle(name, whichClass);
    CORBA::wstring_free(name);
    GERTICO::WstringHandleMap nameHandle;
#ifdef IEEE_1516
    nameHandle[theName] = ret;
#else
    nameHandle[lowercase] = ret;
#endif
    cacheInteractionNameParameter[whichClass] = nameHandle;
  }

#ifdef IEEE_1516
  GERTICO::HandleHandleWstringMap::iterator itCacheInteractionParameterName;

  itCacheInteractionParameterName = cacheInteractionParameterName.find(whichClass);
  if (itCacheInteractionParameterName != cacheInteractionParameterName.end())
  {
    GERTICO::HandleWstringMap *parameterNamePtr;
    GERTICO::HandleWstringMap::iterator itHandleWstring;

    parameterNamePtr = &itCacheInteractionParameterName->second;
    itHandleWstring = parameterNamePtr->find(ret);
    if (itHandleWstring == parameterNamePtr->end())
    {
      (*parameterNamePtr)[ret] = theName;
    }
  }
  else
  {
    GERTICO::HandleWstringMap handleName;
    handleName[ret] = theName;
    cacheInteractionParameterName[whichClass] = handleName;
  }
#endif

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::SupportingServicesLRC::getParameterName(GeRtiFactory::GeRtiHandle const &theHandle, GeRtiFactory::GeRtiHandle const &whichClass)
{
  CORBA::WChar *name = NULL;
  GERTICO::HandleWstringMap::iterator itParameterName;
  GERTICO::HandleHandleWstringMap::iterator itCacheInteractionParameterName;
  std::wstring ret;

  std::wstring dummy = getInteractionClassName(whichClass);

  itCacheInteractionParameterName = cacheInteractionParameterName.find(whichClass);
  if (itCacheInteractionParameterName != cacheInteractionParameterName.end())
  {
    GERTICO::HandleWstringMap *parameterNamePtr;
    parameterNamePtr = &itCacheInteractionParameterName->second;
    itParameterName = parameterNamePtr->find(theHandle);
    if (itParameterName != parameterNamePtr->end())
    {
      ret = itParameterName->second;
    }
    else
    {
      name = GeRtiAmbVar->getParameterName(theHandle, whichClass);
      GERTICO::Mapper::mapWstringFromWchar(ret, name);
      (*parameterNamePtr)[theHandle] = ret;
    }
  }
  else
  {
    name = GeRtiAmbVar->getParameterName(theHandle, whichClass);
    GERTICO::Mapper::mapWstringFromWchar(ret, name);
    GERTICO::HandleWstringMap handleName;
    handleName[theHandle] = ret;
    cacheInteractionParameterName[whichClass] = handleName;
  }

#ifndef IEEE_1516
  GERTICO::HandleWstringHandleMap::iterator itCacheInteractionNameParameter;
  std::wstring lowercase(ret);

  GERTICO::Mapper::nameToLower(lowercase);
  itCacheInteractionNameParameter = cacheInteractionNameParameter.find(whichClass);
  if (itCacheInteractionNameParameter != cacheInteractionNameParameter.end())
  {
    GERTICO::WstringHandleMap *wstringHandlePtr;
    GERTICO::WstringHandleMap::iterator itNameParameter;

    wstringHandlePtr = &itCacheInteractionNameParameter->second;
    itNameParameter = wstringHandlePtr->find(lowercase);
    if (itNameParameter == wstringHandlePtr->end())
    {
      (*wstringHandlePtr)[lowercase] = theHandle;
    }
  }
  else
  {
    GERTICO::WstringHandleMap nameHandle;
    nameHandle[lowercase] = theHandle;
    cacheInteractionNameParameter[whichClass] = nameHandle;
  }
#endif

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getInteractionParent(GeRtiFactory::GeRtiHandle const &theClass)
{
  GERTICO::HandleMap::iterator itHandleMap;

  itHandleMap = parentsInteraction.find(theClass);
  if (itHandleMap == parentsInteraction.end())
  {
    GeRtiFactory::GeRtiHandle zero = 0;
    return zero;
  }
  else
  {
    return itHandleMap->second;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getObjectParent(GeRtiFactory::GeRtiHandle const &theClass)
{
  GERTICO::HandleMap::iterator itHandleMap;

  itHandleMap = parentsObject.find(theClass);
  if (itHandleMap == parentsObject.end())
  {
    GeRtiFactory::GeRtiHandle zero = 0;
    return zero;
  }
  else
  {
    return itHandleMap->second;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::getRangeBounds(GeRtiFactory::GeRtiHandle const &theRegionHandle, GeRtiFactory::GeRtiHandle const &theDimensionHandle, GeRtiFactory::Handles &theRangeBounds)
{
  GeRtiFactory::Handles *handlesPtr;

  handlesPtr = GeRtiAmbVar->getRangeBounds(theRegionHandle, theDimensionHandle);

  theRangeBounds = *handlesPtr;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesLRC::getRoutingSpaceHandle(std::wstring const &theName)
{
  CORBA::WChar *name = NULL;
  GeRtiFactory::GeRtiHandle ret = 0;

  GERTICO::Mapper::mapWcharFromWstring(&name, theName);
  ret = GeRtiAmbVar->getRoutingSpaceHandle(name);
  CORBA::wstring_free(name);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::SupportingServicesLRC::getRoutingSpaceName(GeRtiFactory::GeRtiHandle const &theHandle)
{
  CORBA::WChar *name = NULL;
  std::wstring ret;

  name = GeRtiAmbVar->getRoutingSpaceName(theHandle);
  GERTICO::Mapper::mapWstringFromWchar(ret, name);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesLRC::setRangeBounds(GeRtiFactory::GeRtiHandle const &theRegionHandle, GeRtiFactory::GeRtiHandle const &theDimensionHandle, GeRtiFactory::GeRtiHandle theLowerBound, GeRtiFactory::GeRtiHandle theUpperBound)
{
  GeRtiAmbVar->setRangeBounds(theRegionHandle, theDimensionHandle, theLowerBound, theUpperBound);
}

// ---------------------------------------------------------------------------
// True means dimension not valid.
// ---------------------------------------------------------------------------
bool GERTICO::SupportingServicesLRC::testDimensionAttributes(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theHandleSet)
{
#ifdef IEEE_1516
  GERTICO::AttributeDataMap::iterator itAttributeDataMap;
  GERTICO::AttributeDatumMap *attributeDatumMapPtr;
  GERTICO::AttributeDatumMap::iterator itAttributeDatumMap;
  GERTICO::HandleSet::iterator itHandleSet;

  itAttributeDataMap = cacheObjectAttributeData.find(theClass);
  if (itAttributeDataMap != cacheObjectAttributeData.end())
  {
    for (itHandleSet = theHandleSet.begin(); itHandleSet != theHandleSet.end(); itHandleSet++)
    {
      attributeDatumMapPtr = &itAttributeDataMap->second;
      itAttributeDatumMap = attributeDatumMapPtr->find(*itHandleSet);
      if (itAttributeDatumMap != attributeDatumMapPtr->end())
      {
        if (itAttributeDatumMap->second.theDimensions.size() == 0)
        {
          return true;
        }
      }
    }
  }
#endif

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SupportingServicesLRC::testDimensionInteraction(GeRtiFactory::GeRtiHandle const &theClass)
{
#ifdef IEEE_1516
#endif

  return false;
}
