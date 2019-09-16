/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GeRtiEventMarketI.cpp
**
*******************************************************************************/

//#define GalDebug

#include "Util/GeRtiOrb.h"
#include "Util/Mapper.h"
#include "Util/RunTimeObjectDB.h"

#include "GeRtiEventMarketI.h"
#include "EventHandler.h"

/********************************** Gal begin ***************************************/

#ifdef GalDebug

#include "Gal/StdAfx.h"
#include "Gal/repository.h"
#include "Gal/event.h"

static class Repository_l *r=(Repository::getSingleInstance())->getRepository_l("GeRtiEC.res","GeRtiEC");

static class Event *GeRti_EC_d=r->getRefEvent("GeRti_EC_d");
static class Event *GeRti_EC_e=r->getRefEvent("GeRti_EC_e");
static class Event *GeRti_EC_i=r->getRefEvent("GeRti_EC_i");
static class Event *GeRti_EC_w=r->getRefEvent("GeRti_EC_w");

#endif

#define MAX_TXT 1024
static char galMsg[MAX_TXT];

/********************************** Gal end ***************************************/

// Implementation skeleton constructor
GeRtiEventMarket_ProxyPushConsumer_i::GeRtiEventMarket_ProxyPushConsumer_i(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, GERTICO::EventHandler &theEventHandler) : geRtiOrb(theGeRtiOrb), eventHandler(theEventHandler)
{
  connected = true;
  myPOA = PortableServer::POA::_duplicate(thePOA);
  pConsumer = _this ();
}

// Implementation skeleton destructor
GeRtiEventMarket_ProxyPushConsumer_i::~GeRtiEventMarket_ProxyPushConsumer_i (void)
{
  PortableServer::ObjectId_var objectId = myPOA->servant_to_id(this);
  myPOA->deactivate_object(objectId.in());
}

PortableServer::POA_ptr GeRtiEventMarket_ProxyPushConsumer_i::_default_POA (void)
{
  return PortableServer::POA::_duplicate(myPOA);
}

void GeRtiEventMarket_ProxyPushConsumer_i::connect_push_supplier (
  GeRtiFactory::PushSupplier_ptr supplier
)
throw
(
  CORBA::SystemException
)

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "se");
                            }
                           #endif   // inserted by Gal converter

  connected = true;
  pSupplier = GeRtiFactory::PushSupplier::_duplicate(supplier);
  CORBA::String_var cbstr = geRtiOrb.orbReceiver->object_to_string(pSupplier.in());
  CORBA::Object_var new_ior = geRtiOrb.orbSenderReliable->string_to_object(cbstr.in());
  pSupplier = GeRtiFactory::PushSupplier::_narrow(new_ior.in());

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "sl");
                            }
                           #endif   // inserted by Gal converter
}

void GeRtiEventMarket_ProxyPushConsumer_i::disconnect (
)
throw
(
  CORBA::SystemException
)

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "GeRtiEventMarket_ProxyPushConsumer_i disconnect enter");
                            }
                           #endif   // inserted by Gal converter

  connected = false;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "GeRtiEventMarket_ProxyPushConsumer_i disconnect leave");
                            }
                           #endif   // inserted by Gal converter
}

void GeRtiEventMarket_ProxyPushConsumer_i::push
(
  const GeRtiFactory::GertiPushEvent &gertiPushEvent
)
throw
(
  CORBA::SystemException
)
{
  CORBA::Long d;
  CORBA::ULong ind;
  CORBA::ULong len;

  len = gertiPushEvent.e.length();
                           #ifdef GalDebug   // inserted by Gal converter
                            unsigned int indItem;
                            unsigned long lenItems;
                            unsigned long ul;
                            unsigned long ul1;
                            unsigned long ul2;
                            unsigned long ul3;

                            E1mBegin(GeRti_EC_d)
                            {
                              sprintf(galMsg, "push::length=%lu,sourceType=%lu", len, gertiPushEvent.sourceType);
                              E2(GeRti_EC_i, "GeRtiEventMarket_ProxyPushConsumer_i", galMsg);
//                              E1mEnd(GeRti_EC_i, "GeRtiEventMarket_ProxyPushConsumer_i push");
                            }
                            for (ind = 0; ind < len; ind++)
                            {
                              d = gertiPushEvent.e[ind]._d();
                              switch(d)
                              {
                                case 0:
                                {
                                  ul = gertiPushEvent.e[ind].e().source;
                                  ul1 = gertiPushEvent.e[ind].e().type;
                                  ul2 = gertiPushEvent.e[ind].e()._cxx_class;
                                  ul3 = gertiPushEvent.e[ind].e().data.length();
                                  sprintf(galMsg, "source=%lu,type=%lu,class=%lu,dataLength=%lu", ul, ul1, ul2, ul3);
                                  E2(GeRti_EC_d, "push", galMsg);
                                  lenItems = gertiPushEvent.e[ind].e().data.length();
                                  for (indItem = 0; indItem < lenItems; indItem++)
                                  {
                                    GERTICO::Mapper::printAttributeHandleValue("data=", galMsg, gertiPushEvent.e[ind].e().data[indItem]);
                                    E2(GeRti_EC_d, "push", galMsg);
                                  }
                                }
                                case 1:
                                {
                                  sprintf(galMsg, "EventType=%lu", d);
                                  E2(GeRti_EC_d, "push", galMsg);
                                }
                                default:
                                {
                                  sprintf(galMsg, "EventType=%lu", d);
                                  E2(GeRti_EC_d, "push", galMsg);
                                }
                              }
                            }
                           #endif   // inserted by Gal converter

  // Add event to a linked list.
  eventHandler.addEvent(gertiPushEvent);

  // Allow other thread to continue;
  eventHandler.ps.release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "GeRtiEventMarket_ProxyPushConsumer_i_pushOw", "leave");
                           #endif   // inserted by Gal converter
}

void GeRtiEventMarket_ProxyPushConsumer_i::disconnect_push_consumer (
)
throw
(
  CORBA::SystemException
)

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "GeRtiEventMarket_ProxyPushConsumer_i disconnect_push_consumer enter");
                            }
                           #endif   // inserted by Gal converter

  connected = false;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "GeRtiEventMarket_ProxyPushConsumer_i disconnect_push_consumer leave");
                            }
                           #endif   // inserted by Gal converter
}

// Implementation skeleton constructor
GeRtiEventMarket_MarketSupplierAdmin_i::GeRtiEventMarket_MarketSupplierAdmin_i(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, GERTICO::EventHandler &theEventHandler) : geRtiOrb(theGeRtiOrb), eventHandler(theEventHandler)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "GeRtiEventMarket_MarketSupplierAdmin_i", "Enter");
                           #endif   // inserted by Gal converter
  proxyPushConsumer = NULL;
  myPOA = PortableServer::POA::_duplicate(thePOA);
  supplierAdminVar = _this ();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "GeRtiEventMarket_MarketSupplierAdmin_i", "Leave");
                           #endif   // inserted by Gal converter
}

// Implementation skeleton destructor
GeRtiEventMarket_MarketSupplierAdmin_i::~GeRtiEventMarket_MarketSupplierAdmin_i (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "~GeRtiEventMarket_MarketSupplierAdmin_i", "Enter");
                           #endif   // inserted by Gal converter
  if (proxyPushConsumer)
  {
    delete proxyPushConsumer;
  }
  PortableServer::ObjectId_var objectId = myPOA->servant_to_id(this);
  myPOA->deactivate_object(objectId.in());
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "~GeRtiEventMarket_MarketSupplierAdmin_i", "Leave");
                           #endif   // inserted by Gal converter
}

PortableServer::POA_ptr GeRtiEventMarket_MarketSupplierAdmin_i::_default_POA (void)
{
  return PortableServer::POA::_duplicate(myPOA);
}

GeRtiFactory::ProxyPushConsumer_ptr GeRtiEventMarket_MarketSupplierAdmin_i::obtain_push_consumer(GeRtiFactory::GeRtiHandle sourceType, GeRtiFactory::GeRtiHandle sourceId, const CORBA::WChar *sourceName)
throw
(
  CORBA::SystemException
)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "obtain_push_consumer", "Enter");
                           #endif   // inserted by Gal converter
  proxyPushConsumer = new GeRtiEventMarket_ProxyPushConsumer_i(geRtiOrb, myPOA, eventHandler);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "obtain_push_consumer", "Leave");
                           #endif   // inserted by Gal converter
  return GeRtiFactory::ProxyPushConsumer::_duplicate (proxyPushConsumer->pConsumer);
}

// Implementation skeleton constructor
GeRtiEventMarket_MarketConsumerAdmin_i::GeRtiEventMarket_MarketConsumerAdmin_i(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, PortableServer::POA_ptr thePOABestEffort, GERTICO::EventHandler &theEventHandler) : geRtiOrb(theGeRtiOrb), eventHandler(theEventHandler)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "GeRtiEventMarket_MarketConsumerAdmin_i", "Enter");
                           #endif   // inserted by Gal converter
  myPOA = PortableServer::POA::_duplicate(thePOA);
  myPOABestEffort = PortableServer::POA::_duplicate(thePOABestEffort);
  consumerAdminVar = _this ();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "GeRtiEventMarket_MarketConsumerAdmin_i", "Leave");
                           #endif   // inserted by Gal converter
}

// Implementation skeleton destructor
GeRtiEventMarket_MarketConsumerAdmin_i::~GeRtiEventMarket_MarketConsumerAdmin_i (void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "~GeRtiEventMarket_MarketConsumerAdmin_i", "Enter");
                           #endif   // inserted by Gal converter
  PortableServer::ObjectId_var objectId = myPOA->servant_to_id(this);
  myPOA->deactivate_object(objectId.in());
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "~GeRtiEventMarket_MarketConsumerAdmin_i", "Leave");
                           #endif   // inserted by Gal converter
}

PortableServer::POA_ptr GeRtiEventMarket_MarketConsumerAdmin_i::_default_POA (void)
{
  return PortableServer::POA::_duplicate(myPOA);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::ProxyPushSupplier_ptr GeRtiEventMarket_MarketConsumerAdmin_i::obtain_push_supplier
(
  GeRtiFactory::GeRtiHandle sourceType,
  GeRtiFactory::GeRtiHandle sourceId,
  CORBA::WChar const *sourceName,
  CORBA::Boolean reliableFlag
)
throw
(
  GeRtiFactory::ObjectClassNotDefined,
  CORBA::SystemException
)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "obtain_push_supplier", "Enter");
                           #endif   // inserted by Gal converter
  GeRtiEventMarket_ProxyPushSupplier_i *proxyPushSupplier;

  if (reliableFlag)
  {
    proxyPushSupplier = new GeRtiEventMarket_ProxyPushSupplier_i(geRtiOrb, myPOA, true);
  }
  else
  {
    proxyPushSupplier = new GeRtiEventMarket_ProxyPushSupplier_i(geRtiOrb, myPOABestEffort, false);
  }

  try
  {
    eventHandler.addProxyPushSupplier(sourceId, proxyPushSupplier, reliableFlag);
  }
  catch(...)
  {
    printf("ERROR obtain_push_supplier\n");
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "obtain_push_supplier", "Leave");
                           #endif   // inserted by Gal converter
  return GeRtiFactory::ProxyPushSupplier::_duplicate (proxyPushSupplier->pSupplier);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory_EventChannel_i::GeRtiFactory_EventChannel_i(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOAReceiver, PortableServer::POA_ptr thePoaBestEffort, GERTICO::EventHandler *theEventHandler)
{
  consumerAdmin = NULL;
  supplierAdminBestEffort = NULL;
  supplierAdminReliable = NULL;

  consumerAdmin = new GeRtiEventMarket_MarketConsumerAdmin_i(theGeRtiOrb, thePOAReceiver, thePoaBestEffort, *theEventHandler);
  supplierAdminBestEffort = new GeRtiEventMarket_MarketSupplierAdmin_i(theGeRtiOrb, thePOAReceiver, *theEventHandler);
  supplierAdminReliable = new GeRtiEventMarket_MarketSupplierAdmin_i(theGeRtiOrb, thePOAReceiver, *theEventHandler);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory_EventChannel_i::~GeRtiFactory_EventChannel_i(void)
{
  if (consumerAdmin)
  {
    delete consumerAdmin;
  }

  if (supplierAdminBestEffort)
  {
    delete supplierAdminBestEffort;
  }

  if (supplierAdminReliable)
  {
    delete supplierAdminReliable;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::ConsumerAdmin_ptr GeRtiFactory_EventChannel_i::for_consumers(void)
{
  return GeRtiFactory::ConsumerAdmin::_duplicate(consumerAdmin->consumerAdminVar);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::SupplierAdmin_ptr GeRtiFactory_EventChannel_i::for_suppliers(void)
{
  return GeRtiFactory::SupplierAdmin::_duplicate(supplierAdminReliable->supplierAdminVar);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_EventChannel_i::destroy(void)
{
}
