/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GeRtiEventMarketI.h
**
*******************************************************************************/

#ifndef GERTIEVENTMARKETI_H_
#define GERTIEVENTMARKETI_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
//#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <map>
#include "EventMarket/EventHandler.h"
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiOrb.h"
#include "Util/GeRtiTypes.h"

#include "ace/Synch.h"

#ifdef _WIN32
#if defined (BUILDING_EVENT_MARKET)
#define EVENT_MARKET_EXPORT __declspec(dllexport)
#else
#define EVENT_MARKET_EXPORT __declspec(dllimport)
#endif
#else
#define EVENT_MARKET_EXPORT
#endif

//Class GeRtiEventMarket_ProxyPushConsumer_i
class EVENT_MARKET_EXPORT GeRtiEventMarket_ProxyPushConsumer_i : public virtual POA_GeRtiFactory::ProxyPushConsumer
{
  GERTICO::GeRtiOrb &geRtiOrb;
  PortableServer::POA_var myPOA;
  GeRtiFactory::PushSupplier_var pSupplier;

public:
  GeRtiFactory::ProxyPushConsumer_var pConsumer;
  bool connected;

  //Constructor
  GeRtiEventMarket_ProxyPushConsumer_i(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, GERTICO::EventHandler &theEventHandler);

  //Destructor
  virtual ~GeRtiEventMarket_ProxyPushConsumer_i (void);

  PortableServer::POA_ptr _default_POA (void);

  GERTICO::EventHandler &eventHandler;

  virtual void connect_push_supplier (
    GeRtiFactory::PushSupplier_ptr supplier
  )
  throw (
    CORBA::SystemException
  );

  virtual void disconnect (
  )
  throw (
    CORBA::SystemException
  );

  virtual void push (
    const GeRtiFactory::GertiPushEvent &gertiPushEvent
  )
  throw (
    CORBA::SystemException
  );

  virtual void disconnect_push_consumer (
  )
  throw (
    CORBA::SystemException
  );

};

//Class GeRtiEventMarket_MarketSupplierAdmin_i
class EVENT_MARKET_EXPORT GeRtiEventMarket_MarketSupplierAdmin_i : public virtual POA_GeRtiFactory::SupplierAdmin
{
  GERTICO::GeRtiOrb &geRtiOrb;
  PortableServer::POA_var myPOA;
  GeRtiEventMarket_ProxyPushConsumer_i *proxyPushConsumer;

public:
  GeRtiFactory::SupplierAdmin_var supplierAdminVar;
  GERTICO::EventHandler &eventHandler;

  //Constructor
  GeRtiEventMarket_MarketSupplierAdmin_i(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, GERTICO::EventHandler &theEventHandler);

  //Destructor
  virtual ~GeRtiEventMarket_MarketSupplierAdmin_i (void);

  PortableServer::POA_ptr _default_POA (void);

  virtual GeRtiFactory::ProxyPushConsumer_ptr obtain_push_consumer(GeRtiFactory::GeRtiHandle sourceType, GeRtiFactory::GeRtiHandle sourceId, const CORBA::WChar *sourceName)
  throw (
    CORBA::SystemException
  );

};

//Class GeRtiEventMarket_MarketConsumerAdmin_i
class EVENT_MARKET_EXPORT GeRtiEventMarket_MarketConsumerAdmin_i : public virtual POA_GeRtiFactory::ConsumerAdmin
{
  GERTICO::GeRtiOrb &geRtiOrb;
  PortableServer::POA_var myPOA;
  PortableServer::POA_var myPOABestEffort;
  bool reliableFlag;

public:
  GeRtiFactory::ConsumerAdmin_var consumerAdminVar;

  //Constructor
  GeRtiEventMarket_MarketConsumerAdmin_i(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, PortableServer::POA_ptr thePOABestEffort, GERTICO::EventHandler &theEventHandler);

  //Destructor
  virtual ~GeRtiEventMarket_MarketConsumerAdmin_i (void);

  PortableServer::POA_ptr _default_POA (void);

  GERTICO::EventHandler &eventHandler;

virtual GeRtiFactory::ProxyPushSupplier_ptr obtain_push_supplier (
  GeRtiFactory::GeRtiHandle sourceType,
  GeRtiFactory::GeRtiHandle sourceId,
  CORBA::WChar const *sourceName,
	CORBA::Boolean reliableFlag
  )
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    CORBA::SystemException
  );
};

class EVENT_MARKET_EXPORT GeRtiFactory_EventChannel_i : public virtual POA_GeRtiFactory::EventChannel
{
  GeRtiEventMarket_MarketConsumerAdmin_i *consumerAdmin;
  GeRtiEventMarket_MarketSupplierAdmin_i *supplierAdminBestEffort;
  GeRtiEventMarket_MarketSupplierAdmin_i *supplierAdminReliable;

public:
  GeRtiFactory::EventChannel_var eventChannelVar;

  GeRtiFactory_EventChannel_i(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOAReceiver, PortableServer::POA_ptr thePoaBestEffort, GERTICO::EventHandler *theEventHandler);
  virtual ~GeRtiFactory_EventChannel_i(void);

  GeRtiFactory::ConsumerAdmin_ptr for_consumers(void);
  GeRtiFactory::SupplierAdmin_ptr for_suppliers(void);
  void destroy(void);
};

#endif /* GERTIEVENTMARKETI_H_  */
