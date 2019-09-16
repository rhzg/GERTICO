/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Region.h,v $
Revision 1.15  2009/06/12 12:08:12  mul
Use thread mutex.

Revision 1.14  2007/09/25 08:02:05  mul
Changes for ddm.

Revision 1.13  2007/09/05 15:13:04  mul
Changes for ieee1516.

Revision 1.12  2007/05/15 13:12:29  mul
Changes for combined 1.3 and 1516 logic.

Revision 1.11  2006/09/13 06:49:08  mul
Minor changes.

Revision 1.10  2006/08/22 08:45:30  mul
Changes for phase 4 testcases.

Revision 1.9  2006/06/23 13:00:40  mul
Refine region logic.

Revision 1.8  2006/03/17 11:27:33  mul
Fix scope logic for data distribution.

Revision 1.7  2006/02/27 14:29:35  mul
Change handling of attribute/region pairs.

Revision 1.6  2005/09/07 12:24:03  mul
Changes in name scoping.

Revision 1.5  2005/05/03 14:54:23  mul
Xerces interface in one file.

Revision 1.4  2005/03/15 14:35:53  mul
Fix region overlap logic.

Revision 1.3  2004/08/19 09:37:25  mul
Changes for save/restore logic.

Revision 1.2  2004/05/28 11:20:13  mul
Fix include paths.

Revision 1.1  2004/05/27 10:32:24  mul
Integrate subscriber management.

 
**
*******************************************************************************/

/* -*- C++ -*- $Id: Region.h,v 1.15 2009/06/12 12:08:12 mul Exp $ */

#ifndef REGION_H_
#define REGION_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
//#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <map>
#include "XercesInclude.h"
#include "HLAparseErrorHandler.h"
#include "idl/GeRtiFactoryS.h"
#include "GeRtiTypes.h"
#include "RegisteredObject.h"

#include "Space.h"

namespace GERTICO
{
  struct Range
  {
    GeRtiFactory::GeRtiHandle dimension;
    CORBA::ULong lower;
    CORBA::ULong upper;
  };

  // Key is dimension
  typedef std::map <GeRtiFactory::GeRtiHandle, Range> RangeMap;

  class Extent
  {
    RangeMap theRanges;

    void clear (void);

    // Strings for save/restore.
    std::string dimensionStr;
    std::string lowerStr;
    std::string rangeStr;
    std::string rangesStr;
    std::string upperStr;

  public:
    Extent (void);
    virtual ~Extent (void);

    void add (const GeRtiFactory::Ranges &);
    RangeMap *getRangeMap (void);
    void print(void);
    void remove (void);
    void restore (DOMElement &theDOMElement);
    void save (DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, Extent> ExtentMap;

  class Region
  {
    ACE_Thread_Mutex pm;
    CORBA::ULong numberOfExtents;
    // Key is 0, 1, 2 ... (numberOfExtents - 1)
    ExtentMap extents;
    GeRtiFactory::GeRtiHandle federateId;
    GeRtiFactory::GeRtiHandle regionId;
    GeRtiFactory::GeRtiHandle spaceId;
    HandleSet intersectionSet;
    HandleSet objectInstances;

    // Strings for save/restore.
    std::string extentStr;
    std::string extentsStr;
    std::string federateStr;
    std::string idStr;
    std::string intersectionStr;
    std::string intersectionsStr;
    std::string numberOfExtentsStr;
    std::string objectStr;
    std::string objectsStr;
    std::string regionStr;
    std::string spaceIdStr;

    void init (void);

  public:

    // Only for restore
    Region (const GeRtiFactory::GeRtiHandle &theId);

    // Normal use
    Region (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theSpace, const CORBA::ULong &theNumberOfExtents, const GERTICO::HandleSet &theDimensions, const GeRtiFactory::GeRtiHandle &theRegion);
    virtual ~Region (void);

    ExtentMap *getExtents (void);
    void getExtents(GeRtiFactory::Extents &theExtents);
    GeRtiFactory::GeRtiHandle getId (void) const;

    void addObject(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject);
    void delIntersection (const GeRtiFactory::GeRtiHandle &);
    void delIntersection (void);
    void delObject (const GeRtiFactory::GeRtiHandle &);
    GeRtiFactory::GeRtiHandle getFederateId (void) const;
    void getObjects(GERTICO::HandleSet &theObjects);
    void getObjectAttributes(GERTICO::HandleSetMap &objectAttributes, GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder);
    GeRtiFactory::GeRtiHandle getSpace (void) const;
    void getIntersectionSet(GERTICO::HandleSet &theRegions);
    bool gotIntersection (const GeRtiFactory::GeRtiHandle &);
    void modify (const GeRtiFactory::Extents &);
    void print(void);
    void restore (DOMElement &theDOMElement);
    void save (DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    bool regionInUse (void);
    void testDimensions(GERTICO::HandleSet const &theDimensions);
    void tryAddIntersection(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion, ExtentMap &theExtents);
    void tryRemoveIntersection (const GeRtiFactory::GeRtiHandle &);
    void unassociateRegionForUpdates(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject);
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, Region *> RegionMap;

  class RegionsHolder
  {
  public:
    GERTICO::RegionMap regionMap;

    RegionsHolder(void);
    virtual ~RegionsHolder(void);
    GERTICO::Region *getRegion (const GeRtiFactory::GeRtiHandle &theRegion);
  };
};

#endif
