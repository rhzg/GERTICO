/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** SupportingServicesEC.cpp
**
*******************************************************************************/

#include "SupportingServicesEC.h"
#include <iostream>

/********************************** Gal begin ***************************************/

#ifdef GalDebug

#include "Gal/StdAfx.h"
#include "Gal/repository.h"
#include "Gal/event.h"

static class Repository_l *SS=(Repository::getSingleInstance())->getRepository_l("GeRtiSS.res","GeRtiSS");

static class Event *GeRti_SS_d=SS->getRefEvent("GeRti_SS_d");
static class Event *GeRti_SS_e=SS->getRefEvent("GeRti_SS_e");
static class Event *GeRti_SS_i=SS->getRefEvent("GeRti_SS_i");
static class Event *GeRti_SS_w=SS->getRefEvent("GeRti_SS_w");

#endif
/********************************** Gal end ***************************************/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SupportingServicesEC::SupportingServicesEC(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::SupportingServicesEC::~SupportingServicesEC(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesEC::clear(void)
{
  parentsInteraction.clear();
  parentsObject.clear();
  childrenInteraction.clear();
  childrenObjectClass.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesEC::fillInteractionParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theParents)
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
  len = theParents.length();
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
void GERTICO::SupportingServicesEC::fillObjectParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theParents)
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
  len = theParents.length();
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
void GERTICO::SupportingServicesEC::getInteractionChildren(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theChildren)
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
void GERTICO::SupportingServicesEC::getInteractionParents(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles &thePparents)
{
  CORBA::ULong iClass;
  CORBA::ULong ind = 0;
  CORBA::ULong length;

  // Just get some useful memory for faster filling.
  length = 16;
  thePparents.length(length);
  length = 0;
  thePparents.length(length);

  iClass = theClass;
  for (iClass = getInteractionParent(iClass); iClass != 0; iClass = getInteractionParent(iClass), ind++)
  {
    thePparents.length(ind + 1);
    thePparents[ind] = iClass;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::SupportingServicesEC::getObjectClassChildren(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theChildren)
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
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesEC::getInteractionParent(GeRtiFactory::GeRtiHandle const &theClass)
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
GeRtiFactory::GeRtiHandle GERTICO::SupportingServicesEC::getObjectParent(GeRtiFactory::GeRtiHandle const &theClass)
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
bool GERTICO::SupportingServicesEC::isDerivedInteractionClass(GeRtiFactory::GeRtiHandle const &theDerivedClass, GeRtiFactory::GeRtiHandle const &theBaseClass)
{
  GERTICO::HandleMap::iterator itHandleMap;
  bool ret = false;

  // Easy to answer!
  if (theDerivedClass == theBaseClass)
  {
    return true;
  }

  for (itHandleMap = parentsInteraction.find(theDerivedClass); itHandleMap != parentsInteraction.end(); itHandleMap++)
  {
    if (itHandleMap->second == theBaseClass)
    {
      ret = true;
      break;
    }
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::SupportingServicesEC::isDerivedObjectClass(GeRtiFactory::GeRtiHandle const &theDerivedClass, GeRtiFactory::GeRtiHandle const &theBaseClass)
{
  GERTICO::HandleMap::iterator itHandleMap;
  bool ret = false;

  // Easy to answer!
  if (theDerivedClass == theBaseClass)
  {
    return true;
  }

  for (itHandleMap = parentsObject.find(theDerivedClass); itHandleMap != parentsObject.end(); itHandleMap++)
  {
    if (itHandleMap->second == theBaseClass)
    {
      ret = true;
      break;
    }
  }

  return ret;
}
