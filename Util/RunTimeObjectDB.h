/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** RunTimeObjectDB.h
**
*******************************************************************************/

#ifndef RunTimeObjectDB_H
#define RunTimeObjectDB_H

#include <map>
#include <string>
#include <vector>

#include "XercesInclude.h"
#include "HLAparseErrorHandler.h"

#include "ClassDescr.h"
#include "GeRtiTypes.h"
#include "GeRtiOrb.h"
#include "idl/GeRtiFactoryC.h"
#include "DataModel.h"
#include "Federate.h"
#include "Publisher.h"
#include "RegisteredObject.h"
#include "Region.h"
#include "Subscriber.h"

namespace GERTICO
{
  //
  //****************************************************


  class RunTimeObjectDB
  {
    // Class tree
    GERTICO::ClassDescrHolder *pObjectRoot;

    // registered objects
    GERTICO::RegisteredObjectsHolder &registeredObjectsHolder;

    // Published classes
    PublisherHolder publishedClassMap;

    // Key is object class, second subscribed class information.
    SubscribedClassHolder subscribedClassHolder;

    // Regions.
    GERTICO::RegionsHolder &regionsHolder;

    // Spaces.
    GERTICO::RoutingSpaceMap allSpaces;
#ifdef IEEE_1516
    GERTICO::FedDimensionMap allDimensions;
#endif

    // static model information
    ObjectModel* model;
    // privilegeToDelete attribute handle
    GeRtiFactory::GeRtiHandle privilegeToDeleteId;

    SubscribedClass* getSubscribedClass (const GeRtiFactory::GeRtiHandle &classId) 
      throw (GeRtiFactory::ObjectClassNotSubscribed);

    void getSubscribers(GERTICO::HandleSet &currSubscribers, GERTICO::HandleSet &subscribedRegions);

    void restorePublishedClasses (DOMElement &theDOMElement);
    void restoreRegions (DOMElement &theDOMElement);

    // Strings for save/restore.
    std::string idStr;
    std::string objectsStr;
    std::string publishedClassesStr;
    std::string regionStr;
    std::string regionsStr;
    std::string subscribedClassesStr;

  public:
    bool isGerti;

    RunTimeObjectDB(GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GERTICO::RegionsHolder &theRegionsHolder);

    virtual ~RunTimeObjectDB (void);

#ifdef IEEE_1516
    void addDimensions(GERTICO::FedDimensionMap &theFedDimensionMap);
#endif

    void addObjAttRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSetMap &theAttRegMap);

    void addObjectRoot(GERTICO::ClassDescrHolder *theClassDescr);

    void addRoutingSpace(GERTICO::FedSpaceMap &theSpaces);

    void associateRegionForUpdates(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSetMap &theAttributeRegions);

    bool checkActiveObjectClassSubscribers(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClassId, GERTICO::HandleSet &theAttributes);

    void testIfRequestedToRelease(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes);
    bool checkAttRegSpace(const GeRtiFactory::GeRtiHandle &theClass, const GERTICO::HandleSetMap &theAttRegMap);
    void checkAttributesInSpace(const GeRtiFactory::GeRtiHandle &theSpace, const GeRtiFactory::GeRtiHandle &theClass, const GERTICO::HandleSet &theAttributes);
    void checkClassAttributes (const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes);
    void checkPublishing(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::Handles &theAttributes);

    void clear (void);

    // Param: federate id, space id, number of extents
    void createRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theSpace, const CORBA::ULong &numberOfExtents, const GERTICO::HandleSet &theDimensions, const GeRtiFactory::GeRtiHandle &theRegion);
    void printRegions(void);
    void deleteObjectInstance(GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle federate)
      throw (GeRtiFactory::ObjectNotKnown, GeRtiFactory::DeletePrivilegeNotHeld);

    void deleteRegion (const GeRtiFactory::GeRtiHandle &theRegion);

    void getAttributeRoutingSpaceHandle (const GeRtiFactory::GeRtiHandle &theAttribute, const GeRtiFactory::GeRtiHandle &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound, bool &theAttributeFound);

    GeRtiFactory::GeRtiHandle getDimensionHandle (const std::wstring &theName, const GeRtiFactory::GeRtiHandle &whichSpace);

    void getDimensionName(std::wstring &theName, const GeRtiFactory::GeRtiHandle &theHandle, const GeRtiFactory::GeRtiHandle &whichSpace);

    RegisteredObject* getObject 
      (GeRtiFactory::GeRtiHandle objId) 
      throw (GeRtiFactory::ObjectNotKnown);

    AttributeInfo* getObjectAttributeInfo 
      (GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle theAttribute)
      throw (GeRtiFactory::ObjectNotKnown, GeRtiFactory::AttributeNotDefined);

    ClassDescr *getObjectClassDescr (const GeRtiFactory::GeRtiHandle &theClassId);

    GeRtiFactory::GeRtiHandle getPrivilegeToDeleteId (void);

    void getPublishedAttributes(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributeSet);
    PublishedClass* getPublishedClass(const GeRtiFactory::GeRtiHandle &classId) throw (GeRtiFactory::ObjectClassNotPublished);

    std::wstring getRoutingSpaceName(const GeRtiFactory::GeRtiHandle &);

    GeRtiFactory::GeRtiHandle getRoutingSpaceHandle(const std::wstring &);

    void getObjectIdsForClass(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theObjects);

    GERTICO::Region *getRegion (const GeRtiFactory::GeRtiHandle &theRegion);

    void getFederateRegions(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSet &theRegions);

    GeRtiFactory::GeRtiHandle getRegionSpace (const GeRtiFactory::GeRtiHandle &theRegion);

    void getOwnedObjectAttributes (const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::HandleSet &attributes, const bool &thePrivilegeToDeleteNeeded);

    void getScopeSubscribers (GERTICO::HandleSet &, GERTICO::HandleSet &, GERTICO::HandleSet &, GERTICO::HandleSet &);

    bool isPrivilegeToDeleteId(const GeRtiFactory::GeRtiHandle &theAttribute);

    bool isRegionSubscribed (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion);

    void modifyRegion (const GeRtiFactory::GeRtiHandle &, const GeRtiFactory::GeRtiHandle &, const GeRtiFactory::Extents &);

    void print (void);

    void publishObjectClass (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes);

    void registerObjectInstance(GERTICO::ClassDescr &theClassDescr, const GeRtiFactory::GeRtiHandle &theObjectId);

    void removeObjectInstance(GeRtiFactory::GeRtiHandle theObject);

    void restore (DOMElement &theDOMElement);
    void save (DOMDocument &theDOMDocument, DOMElement &theDOMElement);

    void setModel (ObjectModel* m) { model = m; };  

    void setPrivilegeToDeleteId (GeRtiFactory::GeRtiHandle attr) { privilegeToDeleteId = attr; };

    void setRangeBounds(GeRtiFactory::GeRtiHandle const &theRegionHandle, GeRtiFactory::GeRtiHandle const &theDimensionHandle, GeRtiFactory::GeRtiHandle const &theLowerBound, GeRtiFactory::GeRtiHandle const &theUpperBound);

    void subscribeObjectClassAttributes(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSet &theAttributes, const CORBA::Boolean &theActive);
    void subscribeObjectClassAttributesWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSetMap &theAttributeRegions, const CORBA::Boolean &theActive);

    bool subscribedToAttribute(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes);
    bool subscribedToAttributeActive(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes);
    bool subscribedToAttributeWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSetMap &theAttributeRegions);

    bool testIntersection (const GeRtiFactory::GeRtiHandle &, const GeRtiFactory::GeRtiHandle &);
    void testRegionDimensions(GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSetMap const &theAttRegMap);

    void unassociateRegionForUpdates (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::GeRtiHandle &theObject);
    void unassociateRegionsForUpdates(const GeRtiFactory::GeRtiHandle &theFederate, const GERTICO::HandleSetMap &theAttributeRegions, const GeRtiFactory::GeRtiHandle &theObject);
    void unpublishObjectClass(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass);
    void unpublishObjectClassAttributes(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::Handles &theAttributes);
    void unsubscribeObjectClass(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GERTICO::HandleSet &theRegions);
#ifdef IEEE_1516
    void unsubscribeObjectClassWithAttributeRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GERTICO::HandleSetMap &theAttributeRegions);
#endif
  };
};

#endif // RunTimeObjectDB_H
