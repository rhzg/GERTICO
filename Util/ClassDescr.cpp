/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: ClassDescr.cpp,v $
Revision 1.14  2010/06/28 13:36:08  mul
Bundle attribute information.

Revision 1.13  2009/09/23 06:50:52  mul
Add class description holder.

Revision 1.12  2009/06/12 12:13:37  mul
Use thread mutex.

Revision 1.11  2007/09/25 08:05:29  mul
Changes for ddm.

Revision 1.10  2007/09/05 14:55:50  mul
Changes for ieee1516.

Revision 1.9  2007/03/12 13:00:07  mul
Changed string to wstring.

Revision 1.8  2006/06/23 12:58:32  mul
New method to check for derived classes.

Revision 1.7  2005/11/17 10:10:33  mul
Fix memory leak.

Revision 1.6  2005/03/15 14:32:54  mul
Add get interaction space function.

Revision 1.5  2005/02/07 10:34:01  mul
Changes due to test cases.

Revision 1.4  2004/12/13 15:37:22  mul
Add additional access fuctionality to the class tree.

Revision 1.3  2004/09/23 14:50:07  mul
Add logic to get set of derived classes.

Revision 1.2  2004/07/16 11:16:59  mul
Changes due to verfication test.

Revision 1.1  2004/05/10 07:46:39  mul
Changes due to integrating object management with ownership.


**
*******************************************************************************/


#include "ClassDescr.h"
#include "Item.h"
#include "Util/Mapper.h"
#include "NextHandle.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ClassDescrHolder::ClassDescrHolder(void)
{
  classDescr = NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ClassDescrHolder::~ClassDescrHolder(void)
{
  if (classDescr)
  {
    delete classDescr;
    classDescr = NULL;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::ClassDescrHolder::findClassName(GeRtiFactory::GeRtiHandle const &theClass)
{
  return findClassNamePrivate(theClass, classDescr);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ClassDescrHolder::findHandle(std::wstring const &theName)
{
  return findHandlePrivate(theName, *classDescr);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::ClassDescrHolder::findHandlePrivate(const std::wstring &theName, GERTICO::ClassDescr &c)
{
  GERTICO::ClassDescr *currClassDescr;
  std::wstring b(theName);
  std::wstring dot(L".");
  size_t p;

  int ret;
  std::map <unsigned long, GERTICO::ClassDescr *>::const_iterator itCD;

  p = b.find(dot);
  if (p != std::wstring::npos)
  {
    std::wstring q(b, p + 1, std::wstring::npos);
    std::wstring r(b, 0, p);

    for (itCD = c.classDescrs.begin (); itCD != c.classDescrs.end (); itCD++)
    {
      currClassDescr = itCD->second;
      if (r == currClassDescr->getNameLower())
      {
        ret = findHandlePrivate(q, *currClassDescr);
        if (ret)
        {
          return ret;
        }
      }
    }
  }
  else
  {
    for (itCD = c.classDescrs.begin (); itCD != c.classDescrs.end (); itCD++)
    {
      currClassDescr = itCD->second;
      if (b == currClassDescr->getNameLower())
      {
        return currClassDescr->getId ();
      }
    }
  }

  return 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::ClassDescrHolder::findClassNamePrivate(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::ClassDescr *theClassDescr)
{
  GERTICO::ClassDescr *currClassDescr;
  std::map <unsigned long, GERTICO::ClassDescr *>::const_iterator itCD = theClassDescr->classDescrs.begin ();
  std::wstring ret;

  while (itCD != theClassDescr->classDescrs.end ())
  {
    currClassDescr = itCD->second;
    if (theClass == currClassDescr->getId ())
    {
      ret = currClassDescr->getNameFull();
      return ret;
    }
    else
    {
      ret = findClassNamePrivate(theClass, currClassDescr);
      if (ret.size() != 0)
      {
        return ret;
      }
    }
    itCD++;
  }

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ClassDescr *GERTICO::ClassDescrHolder::getClassDescr(unsigned long const &theClass)
{
  ClassDescr *tmpClassDescr;

  pm.acquire();
  tmpClassDescr = classDescr->getClassDescr(theClass);
  pm.release();

  return tmpClassDescr;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ClassDescrHolder::getLRCattributeFlags(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::LRCattributeFlagsMap &theLRCattributeFlagsMap)
{
  GERTICO::ClassDescr *tmpClassDescr;
  GERTICO::HandleSet attributes;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::Item *item;
  GERTICO::LRCattributeFlags lrcAttributeFlags;

  pm.acquire();
  tmpClassDescr = classDescr->getClassDescr(theClass);
  pm.release();

  tmpClassDescr->getAttributes(attributes);
  for (itAttribute = attributes.begin(); itAttribute != attributes.end(); itAttribute++)
  {
    item = tmpClassDescr->getClassItem (*itAttribute);
    item->getDimensions(lrcAttributeFlags.dimensions);
    lrcAttributeFlags.name = item->myName;
    lrcAttributeFlags.ordering = item->getOrdering();
    lrcAttributeFlags.transportation = item->getTransportation();
    theLRCattributeFlagsMap[*itAttribute] = lrcAttributeFlags;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ClassDescrHolder::getLRCparameterFlags(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::LRCparameterFlagsMap &theLRCparameterFlagsMap)
{
  GERTICO::ClassDescr *tmpClassDescr;
  GERTICO::HandleSet parameters;
  GERTICO::HandleSet::iterator itParameter;
  GERTICO::Item *item;
  GERTICO::LRCparameterFlags lrcParameterFlags;

  pm.acquire();
  tmpClassDescr = classDescr->getClassDescr(theClass);
  pm.release();

  if (tmpClassDescr)
  {
    tmpClassDescr->getAttributes(parameters);
    for (itParameter = parameters.begin(); itParameter != parameters.end(); itParameter++)
    {
      item = tmpClassDescr->getClassItem (*itParameter);
      lrcParameterFlags.name = item->myName;
      theLRCparameterFlagsMap[*itParameter] = lrcParameterFlags;
    }
    return false;
  }

  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ClassDescrHolder::getRoutingSpaceHandle(const unsigned long &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound)
{
  pm.acquire();
  classDescr->getRoutingSpaceHandle(classDescr, theClass, theSpace, theClassFound);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ClassDescrHolder::getAttributeRoutingSpaceHandle(const GeRtiFactory::GeRtiHandle &theAttribute, const GeRtiFactory::GeRtiHandle &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound, bool &theAttributeFound)
{
  pm.acquire();
  classDescr->getRoutingSpaceHandle(classDescr, theAttribute, theClass, theSpace, theClassFound, theAttributeFound);
  pm.release();
}

GERTICO::ClassDescr::ClassDescr(std::wstring const &theName, unsigned long const &id, unsigned long const &theSpace, unsigned long const &theOrdering, unsigned long const &theTransportation, unsigned long const &theSharing, GERTICO::HandleSet const &theDimensions)
{
  name = theName;
  GERTICO::Mapper::nameToLower(name);

  dimensions = theDimensions;

  myId = id;
  ordering = theOrdering;
  space = theSpace;
  transportation = theTransportation;
  parent = NULL;
}

GERTICO::ClassDescr::ClassDescr(std::wstring const &theName, unsigned long const &id, unsigned long const &theSpace, unsigned long const &theOrdering, unsigned long const &theTransportation, unsigned long const &theSharing, GERTICO::HandleSet const &theDimensions, ClassDescr *d)
{
  std::wstring p;

  dimensions = theDimensions;
  name = theName;
  GERTICO::Mapper::nameToLower(name);

  p = d->getNameFull();
  if (p.size())
  {
    nameFull = p;
    nameFull.append(L".");
  }
  nameFull.append(theName);

  //myId = GeRti::NextHandle::nextHandle ();
  myId = id;
  ordering = theOrdering;
  space = theSpace;
  transportation = theTransportation;
  parent = d;
  d->classDescrs[myId] = this;
}

GERTICO::ClassDescr::~ClassDescr (void)
{
  ClassDescrMap::iterator itCD;
  GERTICO::ClassDescr *currClassDescr;
  GERTICO::Item *currItem;
  ItemMap::iterator itI;

  for (itI = items.begin (); itI != items.end (); itI = items.begin ())
  {
    currItem = itI->second;
    delete currItem;
    items.erase (itI);
  }

  for (itCD = classDescrs.begin (); itCD != classDescrs.end (); itCD = classDescrs.begin ())
  {
    currClassDescr = itCD->second;
    delete currClassDescr;
    classDescrs.erase (itCD);
  }
}

unsigned long GERTICO::ClassDescr::getId (void) const
{
  return myId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ClassDescr::getInteractionSpaceHandle(unsigned long &theSpaceHandle)
{
  theSpaceHandle = space;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
std::wstring GERTICO::ClassDescr::getNameLower(void)
{
  return name;
}

std::wstring GERTICO::ClassDescr::getNameFull (void)
{
  return nameFull;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ClassDescr::addItem(std::wstring const &theName, unsigned long const &id, unsigned long const &theSpace, unsigned long const &theOrdering, unsigned long const &theTransportation, GERTICO::HandleSet const &theDimensions)
{
  GERTICO::Item *newItem = new GERTICO::Item(theName, id, theSpace, theOrdering, theTransportation, theDimensions);

  items[newItem->getId ()] = newItem;
}

// ---------------------------------------------------------------------------
// Get all attributes for class including inherited attributes.
// ---------------------------------------------------------------------------
void GERTICO::ClassDescr::getAttributes(GERTICO::HandleSet &theAttributes)
{
  ItemMap::iterator itIM;

  for (itIM = items.begin(); itIM != items.end(); itIM++)
  {
    theAttributes.insert(itIM->first);
  }

  if (parent != NULL)
  {
    parent->getAttributes(theAttributes);
  }
}

// ---------------------------------------------------------------------------
// Get the ClassDescr by id.
// ---------------------------------------------------------------------------
GERTICO::ClassDescr *GERTICO::ClassDescr::getClassDescr(unsigned long const &id)
{
  ClassDescr *currClassDescr;
  ClassDescr *ret;

  // This class has the desired id.
  if (getId() == id)
  {
    return this;
  }

  // Check first level below class.
  ClassDescrMap::iterator itCD = classDescrs.find (id);
  if (itCD != classDescrs.end ())
  {
    return itCD->second;
  }
  else
  {
    for (itCD = classDescrs.begin (); itCD != classDescrs.end (); itCD++)
    {
      currClassDescr = itCD->second;
      ret = currClassDescr->getClassDescr (id);
      if (ret)
      {
        return ret;
      }
    }
  }

  return NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Item *GERTICO::ClassDescr::getClassItemByName(const std::wstring &theName)
{
  Item *currItem;
  ItemMap::iterator it;

  // Check on this level.
  for (it = items.begin (); it != items.end(); it++)
  {
    currItem = it->second;
    if (currItem->myNameLower == theName)
    {
      return currItem;
    }
  }

  // Name does not exist in this class.
  // Search in base classes.
  if (parent)
  {
    return parent->getClassItemByName(theName);
  }

  // Did not find class
  return NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Item *GERTICO::ClassDescr::getClassItem
(
  const unsigned long &v_item
)
{
  Item *currItem;
  ItemMap::iterator it;

  // Check on this level.
  it = items.find (v_item);
  if (it != items.end ())
  {
    currItem = it->second;
    return currItem;
  }

  // Item does not exist in this class.
  // Search in base classes.
  if (parent)
  {
    return parent->getClassItem (v_item);
  }

  // Did not find class
  return NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ClassDescr::getDimensions(GERTICO::HandleSet &theDimensions)
{
  theDimensions = dimensions;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ClassDescr::getOrdering(unsigned long &theOrdering)
{
  theOrdering = ordering;
}

// ---------------------------------------------------------------------------
// Used to get routing space handle for interactions.
// ---------------------------------------------------------------------------
void GERTICO::ClassDescr::getRoutingSpaceHandle (ClassDescr *theClassDescr, const unsigned long &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound)
{
  ClassDescr *currClassDescr;
  ClassDescrMap::iterator itCD;

  itCD = theClassDescr->classDescrs.find (theClass);
  if (itCD != theClassDescr->classDescrs.end ())
  {
    currClassDescr = itCD->second;
    theClassFound = true;
    theSpace = currClassDescr->space;
  }
  else
  {
    for (itCD = theClassDescr->classDescrs.begin (); itCD != theClassDescr->classDescrs.end (); itCD++)
    {
      getRoutingSpaceHandle (itCD->second, theClass, theSpace, theClassFound);
      if (theClassFound)
      {
        return;
      }
    }
  }
}

// ---------------------------------------------------------------------------
// Used to get routing space handle for object class attributes.
// ---------------------------------------------------------------------------
void GERTICO::ClassDescr::getRoutingSpaceHandle (ClassDescr *theClassDescr, const unsigned long &theAttribute, const unsigned long &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound, bool &theAttributeFound)
{
  ClassDescr *currClassDescr;
  ClassDescrMap::iterator itCD;
  GERTICO::Item *currItem;
  GERTICO::ItemMap::iterator itGI;

  // On the way down, check if the attribute is found
  itGI = theClassDescr->items.find (theAttribute);
  if (itGI != theClassDescr->items.end ())
  {
    theAttributeFound = true;
    currItem = itGI->second;
    theSpace = currItem->getSpace ();
  }

  // Search tree until the class is found.
  itCD = theClassDescr->classDescrs.find (theClass);
  if (itCD != theClassDescr->classDescrs.end ())
  {
    theClassFound = true;
    if (theAttributeFound == false)
    {
      currClassDescr = itCD->second;
      itGI = currClassDescr->items.find (theAttribute);
      if (itGI != currClassDescr->items.end ())
      {
        theAttributeFound = true;
        currItem = itGI->second;
        theSpace = currItem->getSpace ();
      }
    }

    return;
  }
  else
  {
    for (itCD = theClassDescr->classDescrs.begin (); itCD != theClassDescr->classDescrs.end (); itCD++)
    {
      getRoutingSpaceHandle (itCD->second, theAttribute, theClass, theSpace, theClassFound, theAttributeFound);
      if (theClassFound)
      {
        return;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ClassDescr::getTransportation(unsigned long &theTransportation)
{
  theTransportation = transportation;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ClassDescr::isDerivedClass(const unsigned long &theBaseClass)
{
  ClassDescr *currClassDescr;

  if (theBaseClass == myId)
  {
    return true;
  }

  currClassDescr = parent;
  if (parent)
  {
    return currClassDescr->isDerivedClass(theBaseClass);
  }

  return false;
}
