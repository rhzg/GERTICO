/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** EventMarket.cpp
**
*******************************************************************************/

#include "tao/Messaging/Messaging.h"
#include <tao/TAO_Internal.h>
#include "Util/Mapper.h"
#include "EventMarket.h"

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
/********************************** Gal end ***************************************/

// ---------------------------------------------------------------------------
// Implementation skeleton constructor
// ---------------------------------------------------------------------------
GERTICO::GeRti_PushSupplier_i::GeRti_PushSupplier_i(PortableServer::POA_ptr thePOA, std::string const &theSyncScope, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), syncScope(theSyncScope)
{
  myPOA = PortableServer::POA::_duplicate(thePOA);
}

// ---------------------------------------------------------------------------
// Implementation skeleton destructor
// ---------------------------------------------------------------------------
GERTICO::GeRti_PushSupplier_i::~GeRti_PushSupplier_i(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
PortableServer::POA_ptr GERTICO::GeRti_PushSupplier_i::_default_POA(void)
{
  return PortableServer::POA::_duplicate(myPOA);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::GeRti_PushSupplier_i::disconnect_push_supplier
(
)
throw
(
  CORBA::SystemException
)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::cPushSupplier::cPushSupplier(PortableServer::POA_ptr thePOA, const GeRtiFactory::GeRtiHandle &theFederate, std::string const &theSyncScope, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, bool const &theReliable) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), syncScope(theSyncScope), reliable(theReliable)
{
  federate = theFederate;
  lengthInd = 0;
  myPOA = PortableServer::POA::_duplicate(thePOA);
  pushSupplier = new GERTICO::GeRti_PushSupplier_i(myPOA, theSyncScope, geRtiFedTimeFactory);
  pSupplier = pushSupplier->_this();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::cPushSupplier::~cPushSupplier()
{
  PortableServer::ObjectId_var objectId = myPOA->servant_to_id(pushSupplier);
  myPOA->deactivate_object(objectId.in());
// Does not work!
  delete pushSupplier;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::cPushSupplier::addInteractionEvent(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::HandleValues &theAttributes, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::GeRtiHandle &theRegion, GERTICO::AttributeDatum &interactionDatum)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "cPushSupplieraddInteractionEvent", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::HandleSet::const_iterator itHandleSet;
  GeRtiFactory::GeRtiEvent geRtiEvent;

  geRtiEvent.type = GeRtiFactory::interaction;
  geRtiEvent.source = federate;
  geRtiEvent.theSerialNumber = 0;
  geRtiEvent.timestamp.length(0);
  geRtiEvent.data = theAttributes;
  geRtiEvent.theTag = theTag;
  geRtiEvent.obj = theClass;
  if (theClass == 0)
  {
    std::cout << "theClass = 0" << std::endl;
  }
  geRtiEvent.reg = theRegion;
  geRtiEvent._cxx_class = theClass;
  geRtiEvent.bestEffort = interactionDatum.theTransportationType;
  geRtiEvent.tso = interactionDatum.theOrderType;

  gertiPushEvent.e.length(lengthInd + 1);
  gertiPushEvent.e[lengthInd].e(geRtiEvent);
  lengthInd += 1;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "cPushSupplieraddInteractionEvent", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::cPushSupplier::addInteractionEvent(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::HandleValues &theAttributes, const GERTICO::GeRtiFedTime &t, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::GeRtiHandle &theSerialNumber, GERTICO::AttributeDatum &interactionDatum)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "cPushSupplieraddInteractionEventTimed", "Enter");
                           #endif   // inserted by Gal converter
  GeRtiFactory::GeRtiEvent geRtiEvent;

  geRtiEvent.type = GeRtiFactory::interaction;
  geRtiEvent.source = federate;
  geRtiEvent.theSerialNumber = theSerialNumber;
  GERTICO::ConvertTime::mapIt(geRtiEvent.timestamp, t);
  geRtiEvent.data = theAttributes;
  geRtiEvent.theTag = theTag;
  geRtiEvent.obj = theClass;
  geRtiEvent.reg = theRegion;
  geRtiEvent._cxx_class = theClass;
  geRtiEvent.bestEffort = interactionDatum.theTransportationType;
  geRtiEvent.tso = interactionDatum.theOrderType;

  gertiPushEvent.e.length(lengthInd + 1);
  gertiPushEvent.e[lengthInd].e(geRtiEvent);
  lengthInd += 1;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "cPushSupplieraddInteractionEventTimed", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::cPushSupplier::addObjectEvent(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::HandleValues &theAttributes, const GeRtiFactory::UserSuppliedTag &theTag, CORBA::ULong const &theNumber, bool const &theReliable)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "cPushSupplieraddObjectEvent", "Enter");
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong length;
  GeRtiFactory::GeRtiEvent geRtiEvent;

  geRtiEvent.type = GeRtiFactory::obj;
  geRtiEvent.source = federate;
  geRtiEvent.theSerialNumber = 0;
  geRtiEvent.timestamp.length(0);
  geRtiEvent.data.length(theNumber);
  length = theAttributes.length();
  for (i = 0, j = 0; i < length; i++)
  {
    if (theReliable)
    {
      if (theAttributes[i].bestEffort == 0)
      {
        geRtiEvent.data[j] = theAttributes[i];
        j += 1;
      }
    }
    else
    {
      if (theAttributes[i].bestEffort)
      {
        geRtiEvent.data[j] = theAttributes[i];
        j += 1;
      }
    }
  }
  geRtiEvent.theTag = theTag;
  geRtiEvent.obj = theObject;
  geRtiEvent.reg = 0;
  geRtiEvent._cxx_class = theClass;
  if (theReliable)
  {
    geRtiEvent.bestEffort = 0;
  }
  else
  {
    geRtiEvent.bestEffort = 1;
  }
  geRtiEvent.tso = 0;

  gertiPushEvent.e.length(lengthInd + 1);
  gertiPushEvent.e[lengthInd].e(geRtiEvent);
  lengthInd += 1;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "cPushSupplieraddObjectEvent", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::cPushSupplier::addObjectEvent(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::HandleValues const &theAttributes, GERTICO::GeRtiFedTime const &t, GeRtiFactory::UserSuppliedTag const &theTag, GeRtiFactory::GeRtiHandle const &theSerialNumber, CORBA::ULong const &theNumber, bool const &theReliable)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "cPushSupplieraddObjectEventTimed", "Enter");
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong length;
  GeRtiFactory::GeRtiEvent geRtiEvent;

  geRtiEvent.type = GeRtiFactory::obj;
  geRtiEvent.source = federate;
  geRtiEvent.theSerialNumber = theSerialNumber;
  GERTICO::ConvertTime::mapIt(geRtiEvent.timestamp, t);
  geRtiEvent.data.length(theNumber);
  length = theAttributes.length();
  for (i = 0, j = 0; i < length; i++)
  {
    if (theReliable)
    {
      if (theAttributes[i].bestEffort == 0)
      {
        geRtiEvent.data[j] = theAttributes[i];
        j += 1;
      }
    }
    else
    {
      if (theAttributes[i].bestEffort)
      {
        geRtiEvent.data[j] = theAttributes[i];
        j += 1;
      }
    }
  }
  geRtiEvent.theTag = theTag;
  geRtiEvent.obj = theObject;
  geRtiEvent.reg = 0;
  geRtiEvent._cxx_class = theClass;
  if (theReliable)
  {
    geRtiEvent.bestEffort = 0;
  }
  else
  {
    geRtiEvent.bestEffort = 1;
  }
  geRtiEvent.tso = 0;

  gertiPushEvent.e.length(lengthInd + 1);
  gertiPushEvent.e[lengthInd].e(geRtiEvent);
  lengthInd += 1;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "cPushSupplieraddObjectEventTimed", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::cPushSupplier::addDmEvent(GeRtiFactory::GertiDmEvent const &theGertiDmEvent)
{
  gertiPushEvent.e.length(lengthInd + 1);
  gertiPushEvent.e[lengthInd].dmEvent(theGertiDmEvent);
  lengthInd += 1;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::cPushSupplier::addDdmEvent(GeRtiFactory::GertiDdmEvent const &theGertiDdmEvent)
{
  gertiPushEvent.e.length(lengthInd + 1);
  gertiPushEvent.e[lengthInd].ddmEvent(theGertiDdmEvent);
  lengthInd += 1;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::cPushSupplier::addFmEvent(GeRtiFactory::GertiFmEvent const &theGertiFmEvent)
{
  gertiPushEvent.e.length(lengthInd + 1);
  gertiPushEvent.e[lengthInd].fmEvent(theGertiFmEvent);
  lengthInd += 1;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::cPushSupplier::addTmEvent(GeRtiFactory::GertiTmEvent const &theGertiTmEvent)
{
  gertiPushEvent.e.length(lengthInd + 1);
  gertiPushEvent.e[lengthInd].tmEvent(theGertiTmEvent);
  lengthInd += 1;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::cPushSupplier::reset()
{
  lengthInd = 0;
  gertiPushEvent.e.length(lengthInd);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::cPushSupplier::sendEvents()
{
  CORBA::Long d;
  CORBA::ULong length;
  char galMsg[1024];
  bool b = true;

  length = gertiPushEvent.e.length();
  if (length == 0)
  {
    return;
  }

  while (b)
  {
    try
    {
#ifdef GeRtiEventMarketDEBUG
cout << "Out before push" << endl;
cout << "Out e[0].source: " << e[0].source << endl;
cout << "Out e[0].timestamp: " << e[0].timestamp << endl;
cout << "Out e[0].type: " << e[0].type << endl;
#endif
                           #ifdef GalDebug   // inserted by Gal converter
                            CORBA::ULong len;

                            len = gertiPushEvent.e.length();
                            unsigned int indd;
                            unsigned int indItem;
                            unsigned long lenItems;
                            unsigned long ul;
                            unsigned long ul1;
                            unsigned long ul2;

                            sprintf(galMsg, "numberOfEvents=%lu", len);
                            E2(GeRti_EC_d, "sendEvents", galMsg);
                            for (indd = 0; indd < len; indd++)
                            {
                              d = gertiPushEvent.e[indd]._d();
	                            if (d == 0)
	                            {
                                ul = gertiPushEvent.e[indd].e().source;
                                ul1 = gertiPushEvent.e[indd].e()._cxx_class;
                                ul2 = gertiPushEvent.e[indd].e().obj;
                                if (gertiPushEvent.e[indd].e().type == GeRtiFactory::obj)
                                {
                                  sprintf(galMsg, "source=%lu,class=%lu,object=%lu,update", ul, ul1, ul2);
                                }
                                else
                                {
                                  sprintf(galMsg, "source=%lu,class=%lu,interaction", ul, ul1);
                                }
                                E2(GeRti_EC_d, "sendEvents", galMsg);
                                lenItems = gertiPushEvent.e[indd].e().data.length();
                                for (indItem = 0; indItem < lenItems; indItem++)
                                {
                                  GERTICO::Mapper::printAttributeHandleValue("pushData=", galMsg, gertiPushEvent.e[indd].e().data[indItem]);
                                  E2(GeRti_EC_d, "sendEvents", galMsg);
                                }
                              }
                            }

                            for (indd = 0; indd < len; indd++)
                            {
                              d = gertiPushEvent.e[indd]._d();
	                            if (d == 0)
	                            {
                                ul = gertiPushEvent.e[indd].e().source;
                                ul1 = gertiPushEvent.e[indd].e()._cxx_class;
                                if (ul1 == 0)
                                {
                                  std::cout << "push got ZERO - source: " << ul << " " << len << std::endl;
                                }
                              }
                            }
                           #endif   // inserted by Gal converter
      // 2 == federate
      gertiPushEvent.sourceType = 2;
      gertiPushEvent.reliableFlag = reliable;
      proxyConsumer->push(gertiPushEvent);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "cPushSupplierpush", "After");
                           #endif   // inserted by Gal converter
      lengthInd = 0;
      gertiPushEvent.e.length(lengthInd);
    }
    catch(CORBA::SystemException &sysex)
    {
      ACE_PRINT_EXCEPTION(sysex, "CORBA::SystemException in GERTICO::EventSender::f_sendEvents()");
      if (sysex.completed() == CORBA::COMPLETED_NO)
      {
        continue;
      }
      else
      {
//        ACE_PRINT_EXCEPTION(sysex, "sendEvents ");
        throw;
      }
    }

    b = false;
  }

  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::GeRtiFedTime *GERTICO::cPushSupplier::smallestAvailableTSO(void)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::GeRtiFedTime *d = NULL;
  std::auto_ptr<GERTICO::GeRtiFedTime> dd;

  len = gertiPushEvent.e.length();
  for (i = 0; i < len; i++)
  {
    GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, dd, gertiPushEvent.e[i].e().timestamp);
    if (dd.get())
    {
      if (d)
      {
        if (*dd < *d)
        {
          *d = *dd;
        }
      }
      else
      {
        d = geRtiFedTimeFactory.makeZero();
        *d = *dd;
      }
    }
  }

  return d;
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventMarket::EventMarket(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), federate(theFederate)
{
  gerticoConf = NULL;
  interactionsSent = 0;
  lenDataSenderBestEffort = 0;
  lenDataSenderReliable = 0;
  pm.acquire();
  pm.release();
  pushSupplierBestEffort = NULL;
  pushSupplierReliable = NULL;
  updatesSent = 0;
  myPOAbestEffort = NULL;
  myPOAReceiver = NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventMarket::~EventMarket()
{
  clear();

  if (pushSupplierBestEffort)
  {
    pushSupplierBestEffort->proxyConsumer->disconnect();
    delete pushSupplierBestEffort;
  }
  if (pushSupplierReliable)
  {
    pushSupplierReliable->proxyConsumer->disconnect();
    delete pushSupplierReliable;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::addPushSuppliers(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::GeRtiOrb &theGeRtiOrb)
{
  CORBA::Object_var new_ior;
  CORBA::String_var cbstr;
  GeRtiFactory::GeRtiHandle sourceType = 2;

  // Reliable
  pushSupplierReliable = new cPushSupplier(myPOAReceiver, theFederate, gerticoConf->syncScope, geRtiFedTimeFactory, true);
  pushSupplierReliable->proxyConsumer = supplierAdminReceiverVar->obtain_push_consumer(sourceType, federate, eventHub.c_str());
  // remarshal / demarshal
  cbstr = theGeRtiOrb.orbReceiver->object_to_string(pushSupplierReliable->proxyConsumer.in());
  new_ior = theGeRtiOrb.orbSenderReliable->string_to_object(cbstr.in());
  pushSupplierReliable->proxyConsumer = GeRtiFactory::ProxyPushConsumer::_narrow(new_ior.in());
  pushSupplierReliable->proxyConsumer->connect_push_supplier(pushSupplierReliable->pSupplier);

  // BestEffort
  pushSupplierBestEffort = new cPushSupplier(myPOAbestEffort, theFederate, gerticoConf->syncScope, geRtiFedTimeFactory, false);
  pushSupplierBestEffort->proxyConsumer = supplierAdminBestEffortVar->obtain_push_consumer(sourceType, federate, eventHub.c_str());
  // remarshal / demarshal
  cbstr = theGeRtiOrb.orbReceiver->object_to_string(pushSupplierBestEffort->proxyConsumer.in());
  new_ior = theGeRtiOrb.orbSenderBestEffort->string_to_object(cbstr.in());
  pushSupplierBestEffort->proxyConsumer = GeRtiFactory::ProxyPushConsumer::_narrow(new_ior.in());
  pushSupplierBestEffort->proxyConsumer->connect_push_supplier(pushSupplierBestEffort->pSupplier);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::addPushSupplierInteraction(const GeRtiFactory::GeRtiHandle &theInteraction, const GeRtiFactory::HandleValues &theParameters, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::GeRtiHandle &theRegion, GERTICO::AttributeDatum &interactionDatum)
{
  CORBA::ULong i;
  CORBA::ULong len;
  // An interaction may have no parameters, need a small length to show that there
  // is some data to send.
  CORBA::ULong lenData = 1;

  len = theParameters.length();
  for (i = 0; i < len; i++)
  {
    lenData += theParameters[i].value.length();
  }

  pm.acquire();
  if (interactionDatum.theTransportationType)
  {
    pushSupplierBestEffort->addInteractionEvent(theInteraction, theParameters, theTag, theRegion, interactionDatum);
  }
  else
  {
    pushSupplierReliable->addInteractionEvent(theInteraction, theParameters, theTag, theRegion, interactionDatum);
  }
  interactionsSent += 1;
  pm.release();

  if (interactionDatum.theTransportationType)
  {
    if (lenDataSenderBestEffort + lenData >= gerticoConf->dataLength)
    {
      sendEventsBestEffort();
    }
    else
    {
      lenDataSenderBestEffort += lenData;
    }
  }
  else
  {
    if (lenDataSenderReliable + lenData >= gerticoConf->dataLength)
    {
      sendEventsReliable();
    }
    else
    {
      lenDataSenderReliable += lenData;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::addPushSupplierInteraction(const GeRtiFactory::GeRtiHandle &theInteraction, const GeRtiFactory::HandleValues &theParameters,  const GERTICO::GeRtiFedTime &theTime, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::GeRtiHandle &theRegion, const GeRtiFactory::GeRtiHandle &theSerialNumber, GERTICO::AttributeDatum &interactionDatum)
{
  CORBA::ULong i;
  CORBA::ULong len;
  // An interaction may have no parameters, need a small length to show that there
  // is some data to send.
  CORBA::ULong lenData = 1;

  len = theParameters.length();
  for (i = 0; i < len; i++)
  {
    lenData += theParameters[i].value.length();
  }

  pm.acquire();
  if (interactionDatum.theTransportationType)
  {
    pushSupplierBestEffort->addInteractionEvent(theInteraction, theParameters, theTime, theTag, theRegion, theSerialNumber, interactionDatum);
  }
  else
  {
    pushSupplierReliable->addInteractionEvent(theInteraction, theParameters, theTime, theTag, theRegion, theSerialNumber, interactionDatum);
  }
  interactionsSent += 1;
  pm.release();

  if (interactionDatum.theTransportationType)
  {
    if (lenDataSenderBestEffort + lenData >= gerticoConf->dataLength)
    {
      sendEventsBestEffort();
    }
    else
    {
      lenDataSenderBestEffort += lenData;
    }
  }
  else
  {
    if (lenDataSenderReliable + lenData >= gerticoConf->dataLength)
    {
      sendEventsReliable();
    }
    else
    {
      lenDataSenderReliable += lenData;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::addPushSupplierObject(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::HandleValues &theAttributes, const GeRtiFactory::UserSuppliedTag &theTag)
{
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::ULong lenDataBestEffort = 0;
  CORBA::ULong lenDataReliable = 0;
  CORBA::ULong numberBestEffort = 0;
  CORBA::ULong numberReliable = 0;
  GERTICO::HandleSet::iterator its;

  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    if (theAttributes[i].bestEffort)
    {
      lenDataBestEffort += theAttributes[i].value.length();
      numberBestEffort += 1;
    }
    else
    {
      lenDataReliable += theAttributes[i].value.length();
      numberReliable += 1;
    }
  }

  pm.acquire();
  if (numberReliable)
  {
    pushSupplierReliable->addObjectEvent(theObject, theClass, theAttributes, theTag, numberReliable, true);
  }
  if (numberBestEffort)
  {
    pushSupplierBestEffort->addObjectEvent(theObject, theClass, theAttributes, theTag, numberBestEffort, false);
  }
  its = objectsUpdated.find(theObject);
  if (its == objectsUpdated.end())
  {
    objectsUpdated.insert(theObject);
  }
  updatesSent += 1;
  pm.release();

  if (lenDataSenderBestEffort + lenDataBestEffort > gerticoConf->dataLength)
  {
    sendEventsBestEffort();
  }
  else
  {
    lenDataSenderBestEffort += lenDataBestEffort;
  }
  if (lenDataSenderReliable + lenDataReliable > gerticoConf->dataLength)
  {
    sendEventsReliable();
  }
  else
  {
    lenDataSenderReliable += lenDataReliable;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::addPushSupplierObject(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::HandleValues &theAttributes, const GERTICO::GeRtiFedTime &theTime, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::GeRtiHandle &theSerialNumber)
{
  CORBA::ULong i;
  CORBA::ULong len;
  CORBA::ULong lenDataBestEffort = 0;
  CORBA::ULong lenDataReliable = 0;
  CORBA::ULong numberBestEffort = 0;
  CORBA::ULong numberReliable = 0;
  CORBA::WChar *wChar = L"";
  GERTICO::HandleSet::iterator its;

  len = theAttributes.length();
  for (i = 0; i < len; i++)
  {
    if (theAttributes[i].bestEffort)
    {
      lenDataBestEffort += theAttributes[i].value.length();
      numberBestEffort += 1;
    }
    else
    {
      lenDataReliable += theAttributes[i].value.length();
      numberReliable += 1;
    }
  }

  pm.acquire();
  if (numberReliable)
  {
    pushSupplierReliable->addObjectEvent(theObject, theClass, theAttributes, theTime, theTag, theSerialNumber, numberReliable, true);
  }
  if (numberBestEffort)
  {
    pushSupplierBestEffort->addObjectEvent(theObject, theClass, theAttributes, theTime, theTag, theSerialNumber, numberBestEffort, false);
  }
  its = objectsUpdated.find(theObject);
  if (its == objectsUpdated.end())
  {
    objectsUpdated.insert(theObject);
  }
  updatesSent += 1;
  pm.release();

  if (lenDataSenderBestEffort + lenDataBestEffort > gerticoConf->dataLength)
  {
    sendEventsBestEffort();
  }
  else
  {
    lenDataSenderBestEffort += lenDataBestEffort;
  }
  if (lenDataSenderReliable + lenDataReliable > gerticoConf->dataLength)
  {
    sendEventsReliable();
  }
  else
  {
    lenDataSenderReliable += lenDataReliable;
  }
}

// ---------------------------------------------------------------------------
// DM should only use reliable transport.
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::addDmEvent(GeRtiFactory::GertiDmEvent const &theGertiDmEvent)
{
  pushSupplierReliable->addDmEvent(theGertiDmEvent);
  sendEventsReliable();
}

// ---------------------------------------------------------------------------
// DDM should only use reliable transport.
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::addDdmEvent(GeRtiFactory::GertiDdmEvent const &theGertiDdmEvent)
{
  pushSupplierReliable->addDdmEvent(theGertiDdmEvent);
  sendEventsReliable();
}

// ---------------------------------------------------------------------------
// FM should only use reliable transport.
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::addFmEvent(GeRtiFactory::GertiFmEvent const &theGertiFmEvent)
{
  pushSupplierReliable->addFmEvent(theGertiFmEvent);
  sendEventsReliable();
}

// ---------------------------------------------------------------------------
// TM should only use reliable transport.
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::addTmEvent(GeRtiFactory::GertiTmEvent const &theGertiTmEvent)
{
  pushSupplierReliable->addTmEvent(theGertiTmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::clear(void)
{
  pm.acquire();
  interactionsSent = 0;
  lenDataSenderBestEffort = 0;
  lenDataSenderReliable = 0;
  if (pushSupplierBestEffort)
  {
    pushSupplierBestEffort->reset();
  }
  if (pushSupplierReliable)
  {
    pushSupplierReliable->reset();
  }
  objectsUpdated.clear();
  updatesSent = 0;
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::EventMarket::getInteractionsSent(void)
{
  return interactionsSent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::EventMarket::getObjectsUpdated(void)
{
  CORBA::ULong ret;
  size_t size;

  size = objectsUpdated.size();
  GERTICO::Mapper::mapULongSizet(ret, size);
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::EventMarket::getUpdatesSent(void)
{
  return updatesSent;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::sendEvents(void)
{
  sendEventsBestEffort();
  sendEventsReliable();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::sendEventsBestEffort(void)
{
  pm.acquire();
  pushSupplierBestEffort->sendEvents();
  lenDataSenderBestEffort = 0;
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::sendEventsReliable(void)
{
  pm.acquire();
  pushSupplierReliable->sendEvents();
  lenDataSenderReliable = 0;
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::setGERTICOconf(GERTICOconf *theGERTICOconf)
{
  gerticoConf = theGERTICOconf;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventMarket::setPOA(PortableServer::POA_ptr thePOA, PortableServer::POA_ptr thePOABestEffort)
{
  myPOAReceiver = PortableServer::POA::_duplicate(thePOA);
  myPOAbestEffort = PortableServer::POA::_duplicate(thePOABestEffort);
}
