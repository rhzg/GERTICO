/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GeRtiEventMarketI.h
**
*******************************************************************************/

#ifndef GERTIEVENTMARKETISEND_H_
#define GERTIEVENTMARKETISEND_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
//#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <map>
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

//Class GeRtiEventMarket_ProxyPushSupplier_i
class EVENT_MARKET_EXPORT GeRtiEventMarket_ProxyPushSupplier_i : public virtual POA_GeRtiFactory::ProxyPushSupplier
{
  GERTICO::GeRtiOrb &geRtiOrb;
  PortableServer::POA_var myPOA;
  bool reliableFlag;

public:
  GeRtiFactory::ProxyPushSupplier_var pSupplier;
  bool connected;

  //Constructor
  GeRtiEventMarket_ProxyPushSupplier_i(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, bool const &theReliable);

  //Destructor
  virtual ~GeRtiEventMarket_ProxyPushSupplier_i (void);

  PortableServer::POA_ptr _default_POA (void);

  GeRtiFactory::PushConsumer_var pushConsumerVar;
  GeRtiFactory::GeRtiHandle vFederate;

  virtual void connect_push_consumer
  (
    GeRtiFactory::PushConsumer_ptr consumer
  )
  throw
  (
    CORBA::SystemException
  );

  virtual void disconnect (
  )
  throw (
    CORBA::SystemException
  );

  virtual void disconnect_push_supplier (
  )
  throw (
    CORBA::SystemException
  );

};

#endif /* GERTIEVENTMARKETISEND_H_  */
