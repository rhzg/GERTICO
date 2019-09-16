/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** EventMarket.h
**
*******************************************************************************/

#ifndef EventMarket_HEADER
#define EventMarket_HEADER

// C++ standard library
#include <map>
#include <string>

#include "ace/Synch.h"

// RTI C++ language mapping
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiTypes.h"
#include "config.h"
#include "Util/ConvertTime.h"
#include "Util/GERTICOconf.h"
#include "Util/GeRtiOrb.h"

namespace GERTICO
{
  class  GeRti_PushSupplier_i : public virtual POA_GeRtiFactory::PushSupplier
  {
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    PortableServer::POA_var myPOA;
    std::string syncScope;
  public:
    //Constructor
    GeRti_PushSupplier_i(PortableServer::POA_ptr thePOA, std::string const &theSyncScope, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);

    //Destructor
    virtual ~GeRti_PushSupplier_i(void);

    PortableServer::POA_ptr _default_POA(void);

    virtual void disconnect_push_supplier(
    )
    throw(
      CORBA::SystemException
    );

  };

  class cPushSupplier
  {
    CORBA::ULong lengthInd;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    PortableServer::POA_var myPOA;
    GeRtiFactory::GertiPushEvent gertiPushEvent;
    GeRti_PushSupplier_i *pushSupplier;
    GeRtiFactory::GeRtiHandle federate;
    const bool reliable;
    std::string syncScope;

  public:
    GeRtiFactory::PushSupplier_var pSupplier;
    GeRtiFactory::ProxyPushConsumer_var proxyConsumer;

    // In parameter: class/interaction handle.
    cPushSupplier(PortableServer::POA_ptr thePOA, GeRtiFactory::GeRtiHandle const &theFederate, std::string const &theSyncScope, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, bool const &theReliable);
    virtual ~cPushSupplier(void);

    // Add interaction event.
    void addInteractionEvent(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::HandleValues const &, GeRtiFactory::UserSuppliedTag const &, GeRtiFactory::GeRtiHandle const &, GERTICO::AttributeDatum &interactionDatum);

    // Add interaction event.
    void addInteractionEvent(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::HandleValues const &, GERTICO::GeRtiFedTime const &, GeRtiFactory::UserSuppliedTag const &, GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &, GERTICO::AttributeDatum &interactionDatum);

    // Add object event.
    void addObjectEvent(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::HandleValues const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag, CORBA::ULong const &theNumber, bool const &theReliable);

    // Add object event.
    void addObjectEvent(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::HandleValues const &theAttributes, GERTICO::GeRtiFedTime const &t, GeRtiFactory::UserSuppliedTag const &theTag, GeRtiFactory::GeRtiHandle const &theSerialNumber, CORBA::ULong const &theNumber, bool const &theReliable);

    // Add declaration management event.
    void addDmEvent(GeRtiFactory::GertiDmEvent const &theGertiDmEvent);

    // Add data distribution management event.
    void addDdmEvent(GeRtiFactory::GertiDdmEvent const &theGertiDdmEvent);

    // Add federation management event.
    void addFmEvent(GeRtiFactory::GertiFmEvent const &theGertiFmEvent);

    // Add time management event.
    void addTmEvent(GeRtiFactory::GertiTmEvent const &theGertiTmEvent);

    void reset(void);

    // Send any events.
    void sendEvents(void);

    // Send any events.
    GERTICO::GeRtiFedTime *smallestAvailableTSO(void);
  };

  class EventMarket
  {
    ACE_Mutex pm;
    CORBA::ULong lenDataSenderBestEffort;
    CORBA::ULong lenDataSenderReliable;
    PortableServer::POA_var myPOAbestEffort;
    PortableServer::POA_var myPOAReceiver;
    GERTICOconf *gerticoConf;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    CORBA::ULong interactionsSent;
    CORBA::ULong updatesSent;
    cPushSupplier *pushSupplierBestEffort;
    cPushSupplier *pushSupplierReliable;
    GERTICO::HandleSet objectsUpdated;
    const GeRtiFactory::GeRtiHandle &federate;
    std::wstring eventHub;

    void sendEventsBestEffort(void);
    void sendEventsReliable(void);
  public:
    GeRtiFactory::SupplierAdmin_var supplierAdminBestEffortVar;
    GeRtiFactory::SupplierAdmin_var supplierAdminReceiverVar;

    EventMarket(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);
    ~EventMarket(void);

    void addPushSuppliers(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiOrb &theGeRtiOrb);
    void addPushSupplierInteraction(GeRtiFactory::GeRtiHandle const &theInteraction, GeRtiFactory::HandleValues const &theParameters, GeRtiFactory::UserSuppliedTag const &theTag, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::AttributeDatum &interactionDatum);
    void addPushSupplierInteraction(GeRtiFactory::GeRtiHandle const &theInteraction, GeRtiFactory::HandleValues const &theParameters, GERTICO::GeRtiFedTime const &theTime, GeRtiFactory::UserSuppliedTag const &theTag, GeRtiFactory::GeRtiHandle const &theRegion, GeRtiFactory::GeRtiHandle const &theSerialNumber, GERTICO::AttributeDatum &interactionDatum);
    void addPushSupplierObject(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::HandleValues const &, GeRtiFactory::UserSuppliedTag const &);
    void addPushSupplierObject(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::HandleValues const &, GERTICO::GeRtiFedTime const &, GeRtiFactory::UserSuppliedTag const &, GeRtiFactory::GeRtiHandle const &);
    void addDmEvent(GeRtiFactory::GertiDmEvent const &theGertiDmEvent);
    void addDdmEvent(GeRtiFactory::GertiDdmEvent const &theGertiDdmEvent);
    void addFmEvent(GeRtiFactory::GertiFmEvent const &theGertiFmEvent);
    void addTmEvent(GeRtiFactory::GertiTmEvent const &theGertiTmEvent);
    void clear(void);
    CORBA::ULong getInteractionsSent(void);
    CORBA::ULong getObjectsUpdated(void);
    CORBA::ULong getUpdatesSent(void);
    void sendEvents(void);
    void setGERTICOconf(GERTICOconf *theGERTICOconf);
    void setPOA(PortableServer::POA_ptr thePOA, PortableServer::POA_ptr thePOABestEffort);
  };
} // namespace

#endif // EventMarket_HEADER
