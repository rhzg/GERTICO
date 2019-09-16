/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** DeclarationManagementLRC.h
**
*******************************************************************************/

#ifndef DeclarationManagementLRC_H_
#define DeclarationManagementLRC_H_

#include "idl/GeRtiFactoryS.h"

#include "Util/GeRtiTypes.h"
#include "Util/RunTimeObjectDB.h"
#ifdef IEEE_1516
#include "LRC/HLA1516/EventHandler.h"
#else
#include "LRC/HLASpec/EventHandler.h"
#endif
#include "LRC/SupportingServicesLRC.h"

namespace GERTICO
{
  class DeclarationManagementLRC
  {
#ifdef IEEE_1516
    GERTICO::EventHandler1516 &eventHandler;
#else
    GERTICO::EventHandler &eventHandler;
#endif
    GERTICO::HandleSet interactionTurnedOnOSet;

    // Keep track of published interations.
    GERTICO::HandleSet &interactionHandleSet;
    GERTICO::RunTimeObjectDB &runTimeObjectDB;
    GERTICO::SupportingServicesLRC &supportingServicesLRC;
    GeRtiFactory::GeRtiAmbassador_var GeRtiAmb_var;
    GeRtiFactory::GeRtiHandle &federate;
    GERTICO::HandleBoolMap startMap;
    const bool &joined;

    void mapIt(GERTICO::HandleSet &theAttributeSet, GeRtiFactory::Handles const &theAttributes);
	  void publishObjectClassReceiver(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet const &attributeList);
    void unpublishObjectClassAttributesReceiver(GeRtiFactory::GeRtiHandle const & theClass, GeRtiFactory::Handles const &theAttributes);
	  void unpublishObjectClassReceiver(GeRtiFactory::GeRtiHandle const &theClass);

  public:
    GERTICO::HandleSet publishInteractionClassSet;
    GERTICO::EventMarket *eventMarket;
#ifdef IEEE_1516
    GERTICO::HandleSetMap publishObjectClassSet;
    DeclarationManagementLRC(GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmbassador_var, GeRtiFactory::GeRtiHandle &theFederate, bool const &theJoined, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::HandleSet &theInteractionHandleSet, GERTICO::EventHandler1516 &theEventHandler, GERTICO::SupportingServicesLRC &theSupportingServicesLRC);
#else
    GERTICO::HandleSet publishObjectClassSet;
    DeclarationManagementLRC(GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmbassador_var, GeRtiFactory::GeRtiHandle &theFederate, bool const &theJoined, GERTICO::RunTimeObjectDB &theRunTimeObjectDB, GERTICO::HandleSet &theInteractionHandleSet, GERTICO::EventHandler &theEventHandler, GERTICO::SupportingServicesLRC &theSupportingServicesLRC);
#endif
    virtual ~DeclarationManagementLRC(void);

    void checkPublishing(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes);
    void getPublishedAttributes(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &theAttributeSet);
    bool isPublishingInteraction(GeRtiFactory::GeRtiHandle const &theClass);
	  void publishInteractionClass(GeRtiFactory::GeRtiHandle &theInteraction);
	  void publishObjectClass(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &attributeList);
	  void remoteUnsubscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction);
	  void subscribeInteractionClass(GeRtiFactory::GeRtiHandle const &theClass, CORBA::Boolean const &theActive);
	  void subscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSet &thePubAttributeSet, CORBA::Boolean const &theActive);
    void subscribeObjectClassAttributesReceiver(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap);
    bool testInteractionSubscribers(GeRtiFactory::GeRtiHandle const &theInteraction);
    void turnInteractionsOff(GeRtiFactory::GeRtiHandle const &theInteraction);
    void turnInteractionsOn(GeRtiFactory::GeRtiHandle const &theInteraction);
	  void unpublishInteractionClass(GeRtiFactory::GeRtiHandle &theInteraction);
	  void unpublishObjectClass(GeRtiFactory::GeRtiHandle const &theClass);
    void unpublishObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes);
	  void unsubscribeInteractionClass(GeRtiFactory::GeRtiHandle &theInteraction);
	  void unsubscribeObjectClass(GeRtiFactory::GeRtiHandle const &theClass);
	  void unsubscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes);
  };
};

#endif /* DeclarationManagementLRC_H_  */
