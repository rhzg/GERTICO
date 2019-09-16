/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** Region.cpp
**
*******************************************************************************/

#include "Util/Mapper.h"
#include "Region.h"

// ---------------------------------------------------------------------------
// Implementation constructor
// ---------------------------------------------------------------------------
GERTICO::Extent::Extent (void)
{
  dimensionStr = "dimension";
  lowerStr = "lower";
  rangeStr = "range";
  rangesStr = "ranges";
  upperStr = "upper";
}

// ---------------------------------------------------------------------------
// Implementation destructor
// ---------------------------------------------------------------------------
GERTICO::Extent::~Extent (void)
{
}

// ---------------------------------------------------------------------------
// GERTICO::Extent::add: add to ranges.
// ---------------------------------------------------------------------------
void GERTICO::Extent::add (const GeRtiFactory::Ranges &ranges)
{
  CORBA::ULong i;
  CORBA::ULong length;
  GERTICO::Range range;

  length = ranges.length ();
  for (i = 0; i < length; i++)
  {
    range.dimension = ranges[i].dimension;
    range.lower = ranges[i].lower;
    range.upper = ranges[i].upper;
    theRanges[ranges[i].dimension] = range;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Extent::clear (void)
{
  theRanges.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RangeMap *GERTICO::Extent::getRangeMap (void)
{
  return &theRanges;
}

void GERTICO::Extent::print(void)
{
/*
  GERTICO::RangeMap::iterator itRangeMap;

  for (itRangeMap = theRanges.begin(); itRangeMap != theRanges.end(); itRangeMap++)
  {
    std::cout << "dimension " << itRangeMap->second.dimension << std::endl;
    std::cout << "lower " << itRangeMap->second.lower << std::endl;
    std::cout << "upper " << itRangeMap->second.upper << std::endl;
  }
*/
}

// ---------------------------------------------------------------------------
// GERTICO::Extent::getRangeMap: remove from ranges.
// ---------------------------------------------------------------------------
void GERTICO::Extent::remove (void)
{
  theRanges.clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Extent::restore (DOMElement &theDOMElement)
{
  DOMNode* child;
  DOMNode* subChild;
  Range range;
  char *tmpChar;
  unsigned long tmpUL;

  clear ();

  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (rangesStr.c_str ())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (rangeStr.c_str ())) == 0)
            {
              tmpChar = XMLString::transcode (((DOMElement *)subChild)->getAttribute (XMLString::transcode (dimensionStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpUL);
              range.dimension = tmpUL;
              tmpChar = XMLString::transcode (((DOMElement *)subChild)->getAttribute (XMLString::transcode (lowerStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpUL);
              range.lower = tmpUL;
              tmpChar = XMLString::transcode (((DOMElement *)subChild)->getAttribute (XMLString::transcode (upperStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpUL);
              range.upper = tmpUL;
              theRanges[range.dimension] = range;
            }
          }
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Extent::save (DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  RangeMap::iterator itRM;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  unsigned long ul;

  XMLString::transcode(rangesStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  for (itRM = theRanges.begin (); itRM != theRanges.end (); itRM++)
  {
    XMLString::transcode(rangeStr.c_str (), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    XMLString::transcode(dimensionStr.c_str (), tempStr, 99);
    ul = itRM->second.dimension;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    XMLString::transcode(lowerStr.c_str (), tempStr, 99);
    ul = itRM->second.lower;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    XMLString::transcode(upperStr.c_str (), tempStr, 99);
    ul = itRM->second.upper;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }
}

// ---------------------------------------------------------------------------
// Implementation constructor - use in restore only
// ---------------------------------------------------------------------------
GERTICO::Region::Region (const GeRtiFactory::GeRtiHandle &theId)
{
  regionId = theId;
  federateId = 0;
  spaceId = 0;
  numberOfExtents = 0;
  init ();
}

// ---------------------------------------------------------------------------
// Implementation constructor
// ---------------------------------------------------------------------------
GERTICO::Region::Region (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theSpace, const CORBA::ULong &theNumberOfExtents, const GERTICO::HandleSet &theDimensions, const GeRtiFactory::GeRtiHandle &theRegion)
{
  CORBA::ULong i;
  GERTICO::Extent extent;
  GERTICO::HandleSet::const_iterator itDimension;

#ifdef IEEE_1516
  GERTICO::Range range;
  GERTICO::RangeMap *rangeMap;

  range.lower = ULONG_MAX;
  range.upper = ULONG_MAX;
  rangeMap = extent.getRangeMap();
  for (itDimension = theDimensions.begin(); itDimension != theDimensions.end(); itDimension++)
  {
    range.dimension = *itDimension;
    (*rangeMap)[*itDimension] = range;
  }
#endif
  pm.acquire();
  regionId = theRegion;
  federateId = theFederate;
  spaceId = theSpace;
  numberOfExtents = theNumberOfExtents;
  for (i = 0; i < numberOfExtents; i++)
  {
    extents[i] = extent; 
  }
  pm.release ();
  init ();
}

// ---------------------------------------------------------------------------
// Implementation destructor
// ---------------------------------------------------------------------------
GERTICO::Region::~Region (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::addObject(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject)
{
  CORBA::WChar *wChar = L"";
  HandleSet::iterator itH;

  if (theFederate != federateId)
  {
    throw GeRtiFactory::RegionNotKnown(wChar);
  }

  pm.acquire ();
  itH = objectInstances.find (theObject);
  if (itH == objectInstances.end ())
  {
    objectInstances.insert (theObject);
  }
  pm.release ();
}

// ---------------------------------------------------------------------------
// Remove specified intersection.
// ---------------------------------------------------------------------------
void GERTICO::Region::delIntersection (const GeRtiFactory::GeRtiHandle &theRegion)
{
  HandleSet::iterator itHS;

  pm.acquire ();
  itHS = intersectionSet.find (theRegion);
  if (itHS != intersectionSet.end ())
  {
    intersectionSet.erase (itHS);
  }
  pm.release ();
}

// ---------------------------------------------------------------------------
// Clear all intersections.
// ---------------------------------------------------------------------------
void GERTICO::Region::delIntersection (void)
{
  pm.acquire ();
  intersectionSet.clear ();
  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::delObject (const GeRtiFactory::GeRtiHandle &theObject)
{
  HandleSet::iterator itH;

//  pm.acquire ();
  itH = objectInstances.find (theObject);
  if (itH != objectInstances.end ())
  {
    objectInstances.erase (theObject);
  }
//  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ExtentMap *GERTICO::Region::getExtents (void)
{
  return &extents;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::getExtents(GeRtiFactory::Extents &theExtents)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong length;
  GERTICO::ExtentMap::iterator itE;
  GERTICO::RangeMap *rangeMap;
  GERTICO::RangeMap::iterator itRangeMap;
  size_t size;
  theExtents.length(numberOfExtents);

  for (itE = extents.begin (), i = 0; itE != extents.end (); itE++, i++)
  {
    rangeMap = itE->second.getRangeMap();
    size = rangeMap->size();
    GERTICO::Mapper::mapULongSizet(length, size);
    theExtents[i].length(length);
    for (itRangeMap = rangeMap->begin(), j = 0; itRangeMap != rangeMap->end(); itRangeMap++, j++)
    {
      theExtents[i][j].dimension = itRangeMap->second.dimension;
      theExtents[i][j].lower = itRangeMap->second.lower;
      theExtents[i][j].upper = itRangeMap->second.upper;
    }
  }
}

// ---------------------------------------------------------------------------
//  GERTICO::Region::getFed: return federate id.
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::Region::getFederateId (void) const
{
  return federateId;
}

// ---------------------------------------------------------------------------
//  GERTICO::Region::getId: return region id.
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::Region::getId (void) const
{
  return regionId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::getObjects(GERTICO::HandleSet &theObjects)
{
  size_t size = objectInstances.size();
  theObjects = objectInstances;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::getObjectAttributes(GERTICO::HandleSetMap &objectAttributes, GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder)
{
  GERTICO::HandleSet currAttributes;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::RegisteredObject *currObject;

  for (itHS = objectInstances.begin (); itHS != objectInstances.end (); itHS++)
  {
    try
    {
      currObject = theRegisteredObjectsHolder.getObject(*itHS);
      currObject->getFederateObjectAttributes(federateId, currAttributes, regionId);
      objectAttributes[*itHS] = currAttributes;
      currAttributes.clear ();
    }
    catch(...)
    {
    }
  }
}

// ---------------------------------------------------------------------------
//  GERTICO::Region::getSpace: return space id.
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GERTICO::Region::getSpace (void) const
{
  return spaceId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::getIntersectionSet(GERTICO::HandleSet &theRegions)
{
  theRegions = intersectionSet;
}

// ---------------------------------------------------------------------------
//  GERTICO::Region::gotIntersection: true means have an intersection.
// ---------------------------------------------------------------------------
bool GERTICO::Region::gotIntersection (const GeRtiFactory::GeRtiHandle &theRegion)
{
  HandleSet::iterator itH;

  // Default region always intersects.
  if (theRegion == 0)
  {
    return true;
  }

  pm.acquire ();
  itH = intersectionSet.find (theRegion);
  if (itH != intersectionSet.end ())
  {
    pm.release ();
    return true;
  }
  pm.release ();

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::init (void)
{
  extentStr = "extent";
  extentsStr = "extents";
  federateStr = "federate";
  idStr = "id";
  intersectionStr = "intersection";
  intersectionsStr = "intersections";
  numberOfExtentsStr = "numberOfExtents";
  objectStr = "object";
  objectsStr = "objects";
  regionStr = "region";
  spaceIdStr = "spaceId";
}

    
// ---------------------------------------------------------------------------
//  GERTICO::Region::modify: replace any existing extents.
// ---------------------------------------------------------------------------
void GERTICO::Region::modify (const GeRtiFactory::Extents &theExtents)
{
  CORBA::ULong ind;
  CORBA::ULong len;
  CORBA::WChar *wChar = L"";
  Extent *currExtent;
  ExtentMap::iterator itE;
  const GeRtiFactory::Ranges *currRanges;
  
  pm.acquire ();

  len = theExtents.length ();
  pm.release ();

  if (len != numberOfExtents)
  {
    throw GeRtiFactory::InvalidExtents(wChar);
  }

  pm.acquire ();
  ind = 0;
  for (itE = extents.begin (); itE != extents.end (); itE++, ind++)
  {
    currRanges = &theExtents[ind];
    currExtent = &itE->second;
    currExtent->remove ();
    currExtent->add (*currRanges);
  }

  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::print(void)
{
/*
  GERTICO::ExtentMap::iterator itExtentMap;
  GERTICO::HandleSet::iterator itHandleSet;
  std::cout << std::endl;
  std::cout << "Region id " << regionId << std::endl;
  for (itExtentMap = extents.begin(); itExtentMap != extents.end(); itExtentMap++)
  {
    itExtentMap->second.print();
  }
  for (itHandleSet = intersectionSet.begin(); itHandleSet != intersectionSet.end(); itHandleSet++)
  {
    std::cout << "Intersection set " << *itHandleSet << std::endl;
  }
*/
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::restore (DOMElement &theDOMElement)
{
  DOMNode *child;
  DOMNode *subChild;
  Extent extent;
  char *tmpChar;
  unsigned long tmpFED;
  unsigned long tmpID;
  unsigned long tmpREGION;
  unsigned long tmpUL;

  tmpChar = XMLString::transcode (theDOMElement.getAttribute (XMLString::transcode (federateStr.c_str ())));
  sscanf (tmpChar, "%lu", &tmpFED);
  federateId = tmpFED;

  tmpChar = XMLString::transcode (theDOMElement.getAttribute (XMLString::transcode (numberOfExtentsStr.c_str ())));
  sscanf (tmpChar, "%lu", &tmpUL);
  numberOfExtents = tmpUL;

  tmpChar = XMLString::transcode (theDOMElement.getAttribute (XMLString::transcode (spaceIdStr.c_str ())));
  sscanf (tmpChar, "%lu", &tmpUL);
  spaceId = tmpUL;

  // Restore the published classes,
  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (extentsStr.c_str ())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (extentStr.c_str ())) == 0)
            {
              tmpChar = XMLString::transcode (((DOMElement *)subChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpID);
              extent.restore (*((DOMElement *)subChild));
              extents[tmpID] = extent;
            }
          }
        }
      }
    }
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (intersectionsStr.c_str ())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (intersectionStr.c_str ())) == 0)
            {
              tmpChar = XMLString::transcode (((DOMElement *)subChild)->getAttribute (XMLString::transcode (regionStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpREGION);
              intersectionSet.insert (tmpREGION);
            }
          }
        }
      }
    }
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode (objectsStr.c_str ())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode (objectStr.c_str ())) == 0)
            {
              tmpChar = XMLString::transcode (((DOMElement *)subChild)->getAttribute (XMLString::transcode (idStr.c_str ())));
              sscanf (tmpChar, "%lu", &tmpID);
              objectInstances.insert (tmpID);
            }
          }
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::save (DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  ExtentMap::iterator itEM;
  HandleSet::iterator itHS;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  unsigned long ul;

  XMLString::transcode(idStr.c_str (), tempStr, 99);
  ul = regionId;
  sprintf (buf, "%lu", ul);
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  XMLString::transcode(numberOfExtentsStr.c_str (), tempStr, 99);
  ul = numberOfExtents;
  sprintf (buf, "%lu", ul);
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  XMLString::transcode(federateStr.c_str (), tempStr, 99);
  ul = federateId;
  sprintf (buf, "%lu", ul);
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  XMLString::transcode(spaceIdStr.c_str (), tempStr, 99);
  ul = spaceId;
  sprintf (buf, "%lu", ul);
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  XMLString::transcode(extentsStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  for (itEM = extents.begin (); itEM != extents.end (); itEM++)
  {
    XMLString::transcode(extentStr.c_str (), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    XMLString::transcode(idStr.c_str (), tempStr, 99);
    ul = itEM->first;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    itEM->second.save (theDOMDocument, *elemLevel2);
  }

  XMLString::transcode(intersectionsStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  for (itHS = intersectionSet.begin (); itHS != intersectionSet.end (); itHS++)
  {
    XMLString::transcode(intersectionStr.c_str (), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    XMLString::transcode("region", tempStr, 99);
    ul = *itHS;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  XMLString::transcode(objectsStr.c_str (), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  for (itHS = objectInstances.begin (); itHS != objectInstances.end (); itHS++)
  {
    XMLString::transcode(objectStr.c_str (), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    XMLString::transcode(idStr.c_str (), tempStr, 99);
    ul = *itHS;
    sprintf (buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::Region::regionInUse (void)
{
  size_t length;

  length = objectInstances.size ();
  if (length)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::testDimensions(GERTICO::HandleSet const &theDimensions)
{
  CORBA::WChar *wChar = L"testDimensions";
  GERTICO::ExtentMap::iterator itExtentMap;
  GERTICO::HandleSet::const_iterator itDimension;
  GERTICO::RangeMap *rangeMap;
  GERTICO::RangeMap::iterator itRangeMap;

  for (itDimension = theDimensions.begin(); itDimension != theDimensions.end(); itDimension++)
  {
    for (itExtentMap = extents.begin(); itExtentMap != extents.end(); itExtentMap++)
    {
      rangeMap = itExtentMap->second.getRangeMap();
      itRangeMap = rangeMap->find(*itDimension);
      if (itRangeMap == rangeMap->end())
      {
        throw GeRtiFactory::InvalidRegionContext(wChar);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//  GERTICO::Region::tryAddIntersection: add intersection if extents overlap.
// ---------------------------------------------------------------------------
void GERTICO::Region::tryAddIntersection(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion, ExtentMap &theExtents)
{
  Extent *currExtent;
  Extent *myCurrExtent;
  ExtentMap::iterator itE;
  ExtentMap::iterator myItE;
  Range *a;
  Range *b;
  RangeMap *rangeMap;
  RangeMap *myRangeMap;
  RangeMap::iterator itR;
  RangeMap::iterator myItR;

  if (theFederate == federateId)
  {
    return;
  }

  if (theRegion == regionId)
  {
    return;
  }

  pm.acquire ();

  // For every extent in my region
  for (myItE = extents.begin (); myItE != extents.end (); myItE++)
  {
    myCurrExtent = &myItE->second;
    myRangeMap = myCurrExtent->getRangeMap ();
    
    // For every extent in the other region
    for (itE = theExtents.begin (); itE != theExtents.end (); itE++)
    {
      bool gotIntersection = true;
      currExtent = &itE->second;
      rangeMap = currExtent->getRangeMap ();

      // If size is zero then the region has not been initiated.
      if (rangeMap->size() == 0)
      {
        gotIntersection = false;
        break;
      }
      if (myRangeMap->size() == 0)
      {
        gotIntersection = false;
        break;
      }


      for (itR = rangeMap->begin (), myItR = myRangeMap->begin ();
           itR != rangeMap->end () && myItR != myRangeMap->end ();
           itR++, myItR++)
      {
        a = &itR->second;
        b = &myItR->second;

        if (a->dimension != b->dimension)
        {
          gotIntersection = false;
          break;
        }

#ifdef IEEE_1516
        // A flag that shows the ranges were not initiated.
        if (a->lower == ULONG_MAX || a->upper == ULONG_MAX)
        {
          gotIntersection = false;
          break;
        }

        if (b->lower == ULONG_MAX || b->upper == ULONG_MAX)
        {
          gotIntersection = false;
          break;
        }
#endif

        // See logic in the standard.
        if (a->lower == b->lower)
        {
          continue;
        }

        // See logic in the standard.
        if (a->lower < b->upper &&
            b->lower < a->upper)
        {
          continue;
        }

        // No intersection.
        gotIntersection = false;
        break;
      }
      if (gotIntersection)
      {
        intersectionSet.insert (theRegion);
        break;
      }
    }
  }

  pm.release ();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Region::unassociateRegionForUpdates(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject)
{
  CORBA::WChar *wChar = L"";
  HandleSet::iterator itHS;

  if (theFederate != federateId)
  {
    throw GeRtiFactory::RegionNotKnown(wChar);
  }

  itHS = objectInstances.find(theObject);
  if (itHS != objectInstances.end())
  {
    objectInstances.erase(itHS);
  }
  else
  {
#ifndef IEEE_1516
    throw GeRtiFactory::InvalidRegionContext(wChar);
#endif
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegionsHolder::RegionsHolder(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RegionsHolder::~RegionsHolder(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Region *GERTICO::RegionsHolder::getRegion(const GeRtiFactory::GeRtiHandle &regionId)
{
  GERTICO::Region *currRegion = NULL;
  GERTICO::RegionMap::iterator itRI;

  itRI = regionMap.find(regionId);
  if (itRI != regionMap.end())
  {
    currRegion = itRI->second;
  }

  return currRegion;
}
