/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** DataDistributionManagement.h
**
*******************************************************************************/

#ifndef DataDistributionManagement_H_
#define DataDistributionManagement_H_

#include "GeRti/DeclarationManagementRTI.h"

namespace GERTICO
{
  class DataDistributionManagement
  {
    ACE_Thread_Mutex &pm;
    GERTICO::DeclarationManagementRTI &declarationManagement;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::JobHolder &federationJobs;
    GERTICO::NextHandle &idHandler;
    GERTICO::ObjectManagement &objectManagement;
    GERTICO::ObjectModel &objectModel;
    GERTICO::RunTimeObjectDB &runTimeObjectDB;
    GeRtiFactory::GeRtiHandle privilegeToDeleteId;

    void addSubscribeDiscoverObjects(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClassId, GERTICO::HandleSetMap &theAttRegMap);
    void addToHandleSetSetMap(GERTICO::HandleSetSetMap &theFedObjsAtts, const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute);
    void addTurnOnForObjectInstance (const unsigned long &theObject, const unsigned long &theFederate, GERTICO::HandleSet &attributeSet);
    bool checkUnowned(GERTICO::RegisteredObject &theRegisteredObject, GERTICO::HandleSetMap &theAttRegMap);
    void filterSubscribeDiscoverObjects(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::Federate &theFed, const GeRtiFactory::GeRtiHandle &theClassId, GERTICO::HandleSetMap &theAttRegMap, const GeRtiFactory::GeRtiHandle &theRegion);
    void getObjectAttributesInScope(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::RegisteredObject &theRegisteredObject, GERTICO::HandleSetMap &theFederateAttributes);
    void getRequestUpdateFedObjsAtts(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, const GERTICO::HandleSet &theAttributes, GERTICO::Region &theRegion, GERTICO::HandleSetSetMap &theFedObjsAtts);
    bool isRegionSubscribed (const GeRtiFactory::GeRtiHandle &, const GeRtiFactory::GeRtiHandle &);
    void reMap(GERTICO::HandleSetMap &theRegAttMap, GERTICO::HandleSetMap &theAttRegMap);

    // Whether the attribute is subscribed with region.
    bool testIntersectionSets(GERTICO::HandleSet &theAttributes, GERTICO::HandleSet &theTestAttributes);
    bool testIntersection(GERTICO::HandleSetMap &theAttRegMap, GERTICO::HandleSet &theTestAttributes);
    void updateScopeFlags(const GeRtiFactory::GeRtiHandle &theRegion, GERTICO::HandleSet &theRegionsBefore);

  public:
    DataDistributionManagement (GERTICO::DeclarationManagementRTI &theDeclarationManagement, GERTICO::ObjectManagement &theObjectManagement, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::FederatesHolder &theFederatesHolder, GERTICO::ObjectModel &theObjectModel, GERTICO::NextHandle &theIdHandler, GERTICO::JobHolder &theFederationJobs, ACE_Thread_Mutex &thePm);
    virtual ~DataDistributionManagement (void);

    void associateRegionsForUpdates(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, GERTICO::HandleSetMap &theAttributeRegions);

    // Param: federate id, space id, number of extents
    GeRtiFactory::GeRtiHandle createRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theSpace, const CORBA::ULong &numberOfExtents, const GERTICO::HandleSet & theDimensions);

    void deleteRegion (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion);

    void modifyRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::Extents &theExtents);

    GeRtiFactory::GeRtiHandle registerObjectInstanceWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSetMap &theAttributeRegions);
    GeRtiFactory::GeRtiHandle registerObjectInstanceWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, const std::wstring &theObjectName, GERTICO::HandleSetMap &theAttributeRegions);

    void requestAttributeValueUpdateWithRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, const GERTICO::HandleSetMap &theAttributeRegions, const GeRtiFactory::UserSuppliedTag &theTag);
    void subscribeInteractionClass (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theInteraction, const CORBA::Boolean &theActive, const GERTICO::HandleSet &theRegions);
    void subscribeObjectClassAttributesWithRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::HandleSetMap &theAttRegMap, const CORBA::Boolean &theActive);
    void unassociateRegionForUpdates (const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::GeRtiHandle &theObject);
    void unassociateRegionsForUpdates(const GeRtiFactory::GeRtiHandle &theFederate, const GERTICO::HandleSetMap &theAttributeRegions, const GeRtiFactory::GeRtiHandle &theObject);
    void unsubscribeInteractionClassWithRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theInteraction, const GERTICO::HandleSet &theRegions);
    void unsubscribeObjectClassWithRegion(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theRegion);
    void unsubscribeObjectClassWithRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GERTICO::HandleSetMap &theAttributeRegions);
  };
};

#endif /* DataDistributionManagement_H_  */
