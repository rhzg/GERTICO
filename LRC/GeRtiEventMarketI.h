/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
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

#include "LRC/ReceiverLRC.h"
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiOrb.h"
#include "Util/ConvertTime.h"
#include "config.h"

namespace GERTICO
{

  //Class GeRtiEventMarket_PushConsumer_i
  class  GeRtiEventMarket_PushConsumer_i : public virtual POA_GeRtiFactory::PushConsumer
  {
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    PortableServer::POA_var myPOA;
    GERTICO::ReceiverLRC &receiverLRC;

  public:

    //Constructor
    GeRtiEventMarket_PushConsumer_i(PortableServer::POA_ptr thePOA, GERTICO::ReceiverLRC &theReceiverLRC, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);

    //Destructor
    virtual ~GeRtiEventMarket_PushConsumer_i (void);

    PortableServer::POA_ptr _default_POA (void);

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

  class cPushConsumer
  {
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    PortableServer::POA_var myPOA;
    GeRtiEventMarket_PushConsumer_i *pushConsumer;

  public:

    cPushConsumer(PortableServer::POA_ptr thePOA, GERTICO::ReceiverLRC &theReceiverLRC, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);
    virtual ~cPushConsumer (void);

    GeRtiFactory::PushConsumer_var pConsumer;
    GeRtiFactory::ProxyPushSupplier_var proxySupplier;
  };

} // namespace

#endif /* GERTIEVENTMARKETI_H_  */
