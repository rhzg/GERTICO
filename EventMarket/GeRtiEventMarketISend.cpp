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

#include "GeRtiEventMarketISend.h"

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
GeRtiEventMarket_ProxyPushSupplier_i::GeRtiEventMarket_ProxyPushSupplier_i(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, bool const &theReliable) : geRtiOrb(theGeRtiOrb)
{
  connected = true;
  myPOA = PortableServer::POA::_duplicate(thePOA);
  pSupplier = _this ();
  reliableFlag = theReliable;
}

// Implementation skeleton destructor
GeRtiEventMarket_ProxyPushSupplier_i::~GeRtiEventMarket_ProxyPushSupplier_i (void)
{
  PortableServer::ObjectId_var objectId = myPOA->servant_to_id(this);
  myPOA->deactivate_object(objectId.in());
}

PortableServer::POA_ptr GeRtiEventMarket_ProxyPushSupplier_i::_default_POA (void)
{
  return PortableServer::POA::_duplicate(myPOA);
}

void GeRtiEventMarket_ProxyPushSupplier_i::connect_push_consumer
(
  GeRtiFactory::PushConsumer_ptr consumer
)
throw
(
  CORBA::SystemException
)
{
//  std::cout << "ce" << std::endl;
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "ce");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  CORBA::Object_var new_ior;

  connected = true;
  pushConsumerVar = GeRtiFactory::PushConsumer::_duplicate (consumer);
  // remarshal / demarshal
  CORBA::String_var cbstr = geRtiOrb.orbReceiver->object_to_string(pushConsumerVar.in());
  if (reliableFlag)
  {
    new_ior = geRtiOrb.orbSenderReliable->string_to_object(cbstr.in());
  }
  else
  {
    new_ior = geRtiOrb.orbSenderBestEffort->string_to_object(cbstr.in());
  }
  pushConsumerVar = GeRtiFactory::PushConsumer::_narrow(new_ior.in());

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "cl");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
//  std::cout << "cl" << std::endl;
}

void GeRtiEventMarket_ProxyPushSupplier_i::disconnect (
)
throw
(
  CORBA::SystemException
)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "GeRtiEventMarket_ProxyPushSupplier_i disconnect enter");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  connected = false;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "GeRtiEventMarket_ProxyPushSupplier_i disconnect leave");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
}

void GeRtiEventMarket_ProxyPushSupplier_i::disconnect_push_supplier (
)
throw
(
  CORBA::SystemException
)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "GeRtiEventMarket_ProxyPushConsumer_i disconnect_push_supplier enter");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  connected = false;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              E1mEnd(GeRti_EC_d, "GeRtiEventMarket_ProxyPushConsumer_i disconnect_push_supplier leave");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
}
