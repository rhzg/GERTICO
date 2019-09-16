/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: ObjectManagement.h,v $
Revision 1.35  2010/05/17 08:14:33  mul
Add logical time interval.

Revision 1.34  2009/06/12 12:56:54  mul
Use thread mutex.

Revision 1.33  2007/09/25 08:40:27  mul
Changes for ddm.

Revision 1.32  2007/09/06 09:13:41  mul
Changes for ieee1516.

Revision 1.31  2007/06/28 10:18:08  mul
Consolidate register object instance.

Revision 1.30  2007/06/26 08:36:16  mul
Changes for ieee1516.

Revision 1.29  2007/06/08 12:21:45  mul
Changes for ieee1516.

Revision 1.28  2007/05/09 13:29:31  mul
Use generic time.

Revision 1.27  2007/03/06 09:31:26  mul
Changes for ieee conversion.

Revision 1.26  2006/11/16 08:39:29  mul
Fix region testcase.

Revision 1.25  2006/11/15 11:13:44  mul
Clean up unused member.

Revision 1.24  2006/10/16 14:36:07  mul
Use federates holder.

Revision 1.23  2006/10/12 13:57:44  mul
Minor changes.

Revision 1.22  2006/08/30 11:51:23  mul
Add federates holder.

Revision 1.21  2006/08/23 11:15:38  mul
Changes for phase 4 testcases.

Revision 1.20  2006/08/22 08:50:50  mul
Changes for phase 4 testcases.

Revision 1.19  2006/08/18 12:59:24  mul
Changes for phase 4 testcases.

Revision 1.18  2006/08/15 12:54:21  mul
Changes for phase 4 tests.

Revision 1.17  2006/08/01 11:45:43  mul
Simplify some architecture.

Revision 1.16  2006/07/07 06:57:12  mul
Remove unused method.

Revision 1.15  2006/07/03 13:49:09  mul
Fix logic for turn on/off.

Revision 1.14  2006/06/27 14:28:48  mul
Change method arguments.

Revision 1.13  2006/06/12 09:10:52  mul
Fix default parameter for linux.

Revision 1.12  2006/05/24 10:28:41  mul
Fix inScope logic.

Revision 1.11  2006/05/23 14:36:55  hzg
dependencies changed between ownership and objectmanagement

Revision 1.10  2006/05/23 11:35:58  mul
Clean up some publish/unpublish logic.

Revision 1.9  2006/05/17 06:30:37  mul
Set assignment of turn-on responsibility to object management.

Revision 1.8  2006/04/26 10:05:40  mul
phase II corrections

Revision 1.7  2006/03/30 10:22:20  mul
Add additional method for discover object.

Revision 1.6  2006/02/27 14:35:49  mul
Change a type definition.

Revision 1.5  2005/10/05 10:03:47  mul
Remove provide handler.

Revision 1.4  2005/09/09 11:55:01  mul
Files from EventMarket directory.

Revision 1.3  2005/09/07 12:33:46  mul
Change name scoping. Remove some name service calls.

Revision 1.2  2005/08/22 14:30:18  mul
Restructure some program parts.

Revision 1.1  2005/04/11 09:24:41  mul
Files came from event channel.

Revision 1.2  2004/12/14 13:12:39  mul
Fix update logic.

Revision 1.1  2004/09/24 07:55:25  mul
Add object management.


**
*******************************************************************************/


#ifndef ObjectManagement_H_
#define ObjectManagement_H_

#include "idl/GeRtiFactoryS.h"
#include "Util/Federate.h"
#include "Util/RunTimeObjectDB.h"

namespace GERTICO
{
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::GeRtiFedTime *, cmpHandle> ObjectTimeMap;

  class ObjectManagement
  {
    ACE_Thread_Mutex &pm;
    ACE_Semaphore &ps;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::JobHolder &federationJobs;
    GERTICO::NextHandle &idHandler;
    GERTICO::ObjectModel &objectModel;
    GERTICO::ObjectTimeMap objectTimeMap;
    GERTICO::RegisteredObjectsHolder &registeredObjectsHolder;
    GERTICO::RunTimeObjectDB &runTimeObjectDB;
    GeRtiFactory::GeRtiHandle privilegeToDeleteId;

    void addDefaultRegionAttributes(GERTICO::Federate &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSetMap &theAttRegMap);
    void addObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObjectId, std::wstring const &theObjectName);

    bool checkAnySubscriber(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theRegisteredObject, GeRtiFactory::GeRtiHandle const &theAttribute);
    bool checkFedSubscriber(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theRegisteredObject, GeRtiFactory::GeRtiHandle const &theAttribute);
    void doAnnounceObject(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::Federate &theCurrFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::RegisteredObject &theObject, std::wstring const &sName, GERTICO::HandleSet &theAttributes);
    void doDiscover(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::Federate &theCurrFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::RegisteredObject &theObject, std::wstring const &sName, GERTICO::HandleSet &theAttributes);
    void doScopeAcquisitionNotification(GERTICO::RegisteredObject &theObject, GERTICO::HandleSet &theAttributes, bool const &theAsynchronous);
    void doScopeModifyInPub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theRegionsBefore, GERTICO::HandleSet &theRegionsAfter);
    void doScopeModifyInSub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theRegionsBefore, GERTICO::HandleSet &theRegionsAfter);
    void doScopeModifyOutPub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theRegionsBefore, GERTICO::HandleSet &theRegionsAfter);
    void doScopeModifyOutSub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theRegionsBefore, GERTICO::HandleSet &theRegionsAfter);

    void fillFedObjAttributes(GERTICO::HandleSetSetMap &theHandleSetMap, GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute);
    void fillHandleSetMap(GERTICO::HandleSetMap &theHandleSetMap, GeRtiFactory::GeRtiHandle const &theFirst, GeRtiFactory::GeRtiHandle const &theSecond);

    void requestObjectAttributeValueUpdatePrivate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag);

    bool subscribedToAttributeWithRegion(const GeRtiFactory::GeRtiHandle &theCallingFederate, const GeRtiFactory::GeRtiHandle &theOtherFederate, GERTICO::RegisteredObject &theObject, const GeRtiFactory::GeRtiHandle &theTestClass, GERTICO::HandleSet &theAttributes, GERTICO::HandleSet &theRegions);

  public:
    ObjectManagement(GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::FederatesHolder &theFederatesHolder, GERTICO::ObjectModel &theObjectModel, GERTICO::NextHandle &theIdHandler, GERTICO::JobHolder &theFederationJobs, ACE_Thread_Mutex &thePm, ACE_Semaphore &thePs, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);
    virtual ~ObjectManagement(void);

    void addDiscoverObject(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSet &theAttributes);
    void addObjectInstance(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theObjectId, const std::wstring &theObjectName, GERTICO::HandleSetMap &theAttRegMap);
    void changeAttributeOrderType(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &, GeRtiFactory::Handles const &, GeRtiFactory::GeRtiHandle const &);
    void changeAttributeTransportationType (GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &, GeRtiFactory::Handles const &, GeRtiFactory::GeRtiHandle const &);
    void checkDivesting(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes);
    void checkFedAcquiring(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes);
    void checkNotAcquiring(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes);
    void checkNotDivesting(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes);
    void checkNotOwned(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes);
    void checkOwned(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes);
    void checkUnmanagedAttribute(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theAttribute);
    void checkUnmanagedAttribute(const GERTICO::RegisteredObject &theRegisteredObject, const GeRtiFactory::GeRtiHandle &theAttribute);
    bool checkUnowned(GERTICO::RegisteredObject &theRegisteredObject, GERTICO::HandleSet const &theAttSet);

    void deleteObjectInstance(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &, GeRtiFactory::UserSuppliedTag const &);

    void deleteObjectInstance(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &, GeRtiFactory::Time const &, GeRtiFactory::UserSuppliedTag const &, GeRtiFactory::GeRtiHandle const &);

    void doDiscoverObject(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject);
    void doOwnershipAcquisitionNotification(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theObject, GERTICO::HandleSet &theAttributes, bool const &theAsynchronous);
    void doScope(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClassId, GERTICO::HandleSet const &theAttributeList);
    void doScopeAssociate(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theObject, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSetMap &theAttributeRegsBefore);
    void doScopeAssociate(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theObject, GERTICO::HandleSetMap &theAttributeRegsBefore);
    void doScopeModify(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet &theRegionsBefore, GERTICO::HandleSet &theRegionsAfter);
    void doScopeRegister(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::RegisteredObject &theObject);
    void doScopeSubscribe(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, bool const &theSendOutOfScope);
    void doScopeUnsubscribe(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass);
    void doTurnOffForObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass);
    void doTurnOffForSubscribedClass(GERTICO::Federate &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass);
    void doTurnOnForObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &attributeSet, bool asynchronous);
    void doTurnOnForSubscribedClass(GERTICO::Federate &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSetMap &theAttRegMap);
    GERTICO::RegisteredObject *getObject(GeRtiFactory::GeRtiHandle const &objId);
    GERTICO::RegisteredObject *getObjectByName(std::wstring const &theObjectName);
    void getObjectIds(GERTICO::HandleSet &theObjects);
    void getOwnedObjectIds(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theObjects);
    GeRtiFactory::GeRtiHandle getPrivilegeToDeleteId(void);

    void localDeleteObjectInstance(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &);

    void process(GERTICO::GeRtiFedTime const &theGalt);
    GeRtiFactory::GeRtiHandle registerObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass);

    GeRtiFactory::GeRtiHandle registerObjectInstance(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, std::wstring const &theObjectName);

    void requestClassAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag);

    void requestObjectAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag);
    void reserveObjectInstanceName(GeRtiFactory::GeRtiHandle const &theFederate, std::wstring const &theObjectInstanceName);
  };
};

#endif /* ObjectManagement_H_  */
