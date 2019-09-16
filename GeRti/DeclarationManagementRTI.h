/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** DeclarationManagementRTI.h
**
*******************************************************************************/

#ifndef DeclarationManagementRTI_H_
#define DeclarationManagementRTI_H_

#include "idl/GeRtiFactoryS.h"

#include "Util/Federate.h"
#include "Util/RunTimeObjectDB.h"

#include "EventMarket/EventHandler.h"
#include "EventMarket/Interaction.h"

#include "EventMarket/ObjectManagement.h"
#include "GeRti/GeRtiOwnershipMasterI.h"

namespace GERTICO
{
  class DeclarationManagementRTI
  {
    ACE_Thread_Mutex &pm;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::JobHolder &federationJobs;
    GERTICO::ObjectManagement &objectManagement;
    GERTICO::GeRtiOwnershipMasterI &ownershipMaster;
    GERTICO::RunTimeObjectDB &runTimeObjectDB;
    GeRtiFactory::GeRtiHandle privilegeToDeleteId;

    void addDiscoverObjects(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClassId, GERTICO::HandleSet const &theAttributeList);
    bool addFederateDiscoverObject(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::Federate &theMyFederate, GeRtiFactory::GeRtiHandle const &theOtherFederate, GeRtiFactory::GeRtiHandle const &theClassId, GeRtiFactory::GeRtiHandle const &theObject, std::wstring const &theObjectName);
    // Param: class id
    ClassDescr *getInteractionClassDescr(GeRtiFactory::GeRtiHandle const &);
//    void objectClassPubStartRegistration(GERTICO::Federate &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes);
    void unsubscribeObjectClassPrivate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GeRtiFactory::GeRtiHandle const &theRegion);

  public:
    DeclarationManagementRTI(GERTICO::ObjectManagement &theObjectManagement, GERTICO::GeRtiOwnershipMasterI &theGeRtiOwnershipMasterI, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::ClassDescrHolder &theInteractionRoot, GERTICO::FederatesHolder &theFederatesHolder, GERTICO::JobHolder &theFederationJobs, ACE_Thread_Mutex &thePm);
    virtual ~DeclarationManagementRTI(void);

    void delFedInteractions(GeRtiFactory::GeRtiHandle const &, HandleSet &, HandleSetMap &);
    void getInteractionRoutingSpaceHandle(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle &theSpace, bool &theClassFound);
    void objectClassSubStartRegistration(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, GeRtiFactory::GeRtiHandle const &theObjectClass);
    void publishObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes);
    void restore(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    void subscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, CORBA::Boolean const &theActive, GERTICO::HandleSet const &theRegions);
    void subscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes, CORBA::Boolean const &theActive);
    bool testFederateLowerSubscription(GERTICO::Federate &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GeRtiFactory::GeRtiHandle const &theSubscribedClass);
//    void unpublishInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction);
    void unpublishObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass);
    void unpublishObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet const &attributeSet);
    void unsubscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions);
    void unsubscribeObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet const &theAttributes);
  };
};

#endif /* DeclarationManagementRTI_H_  */
