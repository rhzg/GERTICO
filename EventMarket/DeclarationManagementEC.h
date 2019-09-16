/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** DeclarationManagementEC.h
**
*******************************************************************************/

#ifndef DeclarationManagementEC_H_
#define DeclarationManagementEC_H_

#include "idl/GeRtiFactoryS.h"

#include "Util/Federate.h"
#include "Util/RunTimeObjectDB.h"

#include "FedEventSender.h"
#include "Interaction.h"

namespace GERTICO
{
    // Key is federate id.
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::ClassRegionsHolderMap> FedClassRegionsHolderMap;

  class DeclarationManagementEC
  {
    ACE_Thread_Mutex pm;
    ACE_Thread_Mutex &pmFed;
    // Key is federate.
    GERTICO::FedEventSenderMap &fedEventSenderMap;
    // Key is Interaction class.
    GERTICO::InteractionMap &interactionMap;
    GERTICO::RegionsHolder regionsHolder;
    GeRtiFactory::GeRtiHandle privilegeToDeleteId;
    GERTICO::SupportingServicesEC &supportingServicesEC;

    // Publishers
    GERTICO::PublisherHolder publisherObjectClassHolder;

    // Subscribers
    GERTICO::SubscribedClassHolder subscribedClassHolder;

    // Key is federate id.
    GERTICO::FedClassRegionsHolderMap fedSubscribedClassMap;

    void addSubscribeObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttSet, CORBA::Boolean const &theActive);
    void delObjectClassSub(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass);
    void getFederateRegions(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theRegions);
    void getPublishedAttributesPrivate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theAttributeSet);
    PublishedClass* getPublishedClass(GeRtiFactory::GeRtiHandle const &classId) throw (GeRtiFactory::ObjectClassNotPublished);
    GERTICO::Region *getRegion(GeRtiFactory::GeRtiHandle const &theRegion);
    bool getStarted(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass);
    void getSubscribedAttributeRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theAttribute, GERTICO::HandleSet &theRegions, bool const &onlyActiveSubscriptions);
    void objectClassPubStartRegistration(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes);
    void setStarted(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, bool const &theStarted);
    void subscribeObjectClassAttributesPrivate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes, CORBA::Boolean const &theActive);
    void unsubscribeObjectClassPrivate(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GeRtiFactory::GeRtiHandle const &theRegion);

  public:
    GERTICO::InteractionHolder *interactionHolder;

    DeclarationManagementEC(GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId, GERTICO::InteractionMap &theInteractionMap, GERTICO::FedEventSenderMap &theFedEventSenderMap, GERTICO::SupportingServicesEC &theSupportingServicesEC, ACE_Thread_Mutex &theFedPm);
    virtual ~DeclarationManagementEC(void);

    void clear(void);
    void delFedInteractions(GeRtiFactory::GeRtiHandle const &, HandleSet &, HandleSet &, HandleSetMap &, HandleSetMap &);
    void getDesiredAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClassId, GERTICO::HandleSet const &theEventAttributes, GERTICO::HandleSet &theDesiredAttributes);
    void getFederatesForInteraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet &theFederates);
    void objectClassSubStartRegistration(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, GeRtiFactory::GeRtiHandle const &theObjectClass);
    void objectClassSubStartRegistrationFind(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theAttributes, GeRtiFactory::GeRtiHandle const &theObjectClass);
    void objectClassSubStopRegistration(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass);
    void publishInteractionClass(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &);
    void publishObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes);
    void resignFederationExecution(GeRtiFactory::GeRtiHandle const &theFederate);
    void restore(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    void subscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, CORBA::Boolean const &theActive, GERTICO::HandleSet const &theRegions);
    void subscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet &theAttributes, CORBA::Boolean const &theActive);
    bool testFederateLowerSubscription(GERTICO::Federate &theFederate, const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::GeRtiHandle &theSubscribedClass);
    void unpublishInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction);
    void unpublishObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass);
    void unpublishObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet const &attributeSet);
    void unsubscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions);
    void unsubscribeObjectClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObjectClass, GERTICO::HandleSet const &theAttributes);
  };
};

#endif /* DeclarationManagementEC_H_  */
