/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** FedEventSender.cpp
**
*******************************************************************************/

#include "FedEventSender.h"
#include "Util/GeRtiTypes.h"
#include "Util/Mapper.h"
#include <iostream>

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

#define MAX_TXT 2048
static char galMsg[MAX_TXT];

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RtiHubEvent::RtiHubEvent(GeRtiFactory::GeRtiHandle const &theSourceType)
{
  pushEvent = NULL;
  sourceType = theSourceType;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RtiHubEvent::~RtiHubEvent(void)
{
  if (pushEvent == NULL)
  {
    delete pushEvent;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FedEventSender::FedEventSender(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::InteractionMap &theInteractionMap, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, ACE_Semaphore &thePs) : ps(thePs), geRtiFedTimeFactory(theGeRtiFedTimeFactory), interactionMap(theInteractionMap), GERTICOconfRef(theGERTICOconf)
{
  deleted = false;
  firstESender = true;
  haveOverload = false;
  federate = theFederate;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FedEventSender::~FedEventSender(void)
{
  GERTICO::GeRtiTimeMap::iterator itm;
  GERTICO::GeRtiTimeVector geRtiTimeVector;
  GERTICO::RtiHubEvent *geRtiEvent;
  GERTICO::RtiHubEventVector *eventPtr;
  GERTICO::RtiHubEventVector::iterator itGeRtiEventVector;

  eventPtr = f_getEvents(true, true);
  for (itGeRtiEventVector = eventPtr->begin(); itGeRtiEventVector != eventPtr->end(); itGeRtiEventVector = eventPtr->begin())
  {
    geRtiEvent = *itGeRtiEventVector;
    eventPtr->erase(itGeRtiEventVector);
  }
  eventPtr = f_getEvents(true, false);
  for (itGeRtiEventVector = eventPtr->begin(); itGeRtiEventVector != eventPtr->end(); itGeRtiEventVector = eventPtr->begin())
  {
    geRtiEvent = *itGeRtiEventVector;
    eventPtr->erase(itGeRtiEventVector);
  }
  toggleFirstESender();
  eventPtr = f_getEvents(true, true);
  for (itGeRtiEventVector = eventPtr->begin(); itGeRtiEventVector != eventPtr->end(); itGeRtiEventVector = eventPtr->begin())
  {
    geRtiEvent = *itGeRtiEventVector;
    eventPtr->erase(itGeRtiEventVector);
  }
  eventPtr = f_getEvents(true, false);
  for (itGeRtiEventVector = eventPtr->begin(); itGeRtiEventVector != eventPtr->end(); itGeRtiEventVector = eventPtr->begin())
  {
    geRtiEvent = *itGeRtiEventVector;
    eventPtr->erase(itGeRtiEventVector);
  }
  delete proxyPushSupplierReliable;

  pm.acquire();
  for (itm = times.begin(); itm != times.end(); itm = times.begin())
  {
    GERTICO::GeRtiFedTime *geRtiFedTimePtr;
    geRtiFedTimePtr = itm->first;
    times.erase(itm);
    delete geRtiFedTimePtr;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::addEvent(GeRtiFactory::GeRtiEvent const &theGeRtiEvent, GeRtiFactory::GeRtiHandle const &theSourceType, GERTICO::HandleSet &theDesiredAttributes)
{
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::RtiHubEventVector *eventPtr;
  bool reliableFlag;
  unsigned long numberOfItems;

  if (theGeRtiEvent.bestEffort)
  {
    reliableFlag = false;
  }
  else
  {
    reliableFlag = true;
  }

  // The first "e" is sender, the second will get new event.
  eventPtr = f_getEvents(false, reliableFlag);

  // Add the event at the end of the vector.
  GERTICO::RtiHubEvent *newEvent = new GERTICO::RtiHubEvent(theSourceType);
  newEvent->pushEvent = new GeRtiFactory::PushEvent();
  numberOfItems = fillEvent(*newEvent->pushEvent, theGeRtiEvent, theDesiredAttributes);
  if (numberOfItems == 0)
  {
    // Zero parameter count is allowed for Interactions.
    if (theGeRtiEvent.type == GeRtiFactory::obj)
    {
      // Do not want event.
      delete newEvent;
      return;
    }
  }
  eventPtr->push_back(newEvent);
//                           #ifdef GalDebug   // inserted by Gal converter
//                            E1mBegin(GeRti_EC_w)
//                            {
//                              sprintf(galMsg, "Event_vector_size:=%lu", eventPtr->size());
//                              E2(GeRti_EC_w, "addEvent", galMsg);
//                            }
//                           #endif   // inserted by Gal converter
  checkOverload();
  if (eventPtr->size() > 100)
  {
     ACE_Thread::yield();
//     ACE_OS::sleep(ACE_Time_Value(0,1000));
  }
  if (eventPtr->size() > 200)
  {
     ACE_Thread::yield();
//     ACE_OS::sleep(ACE_Time_Value(0,4000));
  }

  addTime(theGeRtiEvent.timestamp);
}

// ---------------------------------------------------------------------------
// Fill event.
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::FedEventSender::fillEvent(GeRtiFactory::PushEvent &theGeRtiEventOut, GeRtiFactory::GeRtiEvent const &theGeRtiEvent, GERTICO::HandleSet &theDesiredAttributes)
{
  GeRtiFactory::GeRtiEvent e;
  CORBA::ULong indData;
  CORBA::ULong j;
  CORBA::ULong k;
  CORBA::ULong lengthj;
  CORBA::ULong lengthk;

  e.type = theGeRtiEvent.type;
  e.source = theGeRtiEvent.source;
  e.theSerialNumber = theGeRtiEvent.theSerialNumber;
  e.timestamp.length(theGeRtiEvent.timestamp.length());
  e.timestamp = theGeRtiEvent.timestamp;
  lengthj = theGeRtiEvent.data.length();
  // Set maximum buffer length.
  e.data.length(lengthj);
  // Reset maximum buffer length.
  e.data.length(0);
  for (j = 0, indData = 0; j < lengthj; j++)
  {
    if (theGeRtiEvent.type == GeRtiFactory::obj)
    {
      if (theGeRtiEvent.obj)
      {
        if (wantAttribute(theGeRtiEvent.data[j].id, theDesiredAttributes) == false)
        {
          continue;
        }
      }
    }
    // Set used buffer length.
    e.data.length(indData + 1);
    e.data[indData].id = theGeRtiEvent.data[j].id;
    e.data[indData].timestampOrder = theGeRtiEvent.data[j].timestampOrder;
    e.data[indData].bestEffort = theGeRtiEvent.data[j].bestEffort;
    lengthk = theGeRtiEvent.data[j].value.length();
    e.data[indData].value.length(lengthk);
    for (k = 0; k < lengthk; k++)
    {
      e.data[indData].value[k] = theGeRtiEvent.data[j].value[k];
    }
    indData += 1;
  }
  e.theTag = theGeRtiEvent.theTag;
  e.obj = theGeRtiEvent.obj;
  e.reg = theGeRtiEvent.reg;
  e._cxx_class = theGeRtiEvent._cxx_class;
  e.bestEffort = theGeRtiEvent.bestEffort;
  theGeRtiEventOut.e(e);

  return indData;
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FedEventSender::wantAttribute(CORBA::ULong const &theEventAttribute, GERTICO::HandleSet const &theSubscriberAttributes)
{
  GERTICO::HandleSet::const_iterator itSubscriberAttribute;
  bool ret = false;

  itSubscriberAttribute = theSubscriberAttributes.find(theEventAttribute);
  if (itSubscriberAttribute != theSubscriberAttributes.end())
  {
    ret = true;
  }

  return ret;
}

// ---------------------------------------------------------------------------
// Logic to keep track of the timestamps of each event in the
// sequence.
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::addTime(GeRtiFactory::Time const &theTime)
{
  GERTICO::GeRtiFedTime *tmpFedTime = NULL;
  GeRtiTimeMap::iterator ita;
  unsigned int dummy = 1;

  // Do not have a timestamp: ignore!
  if (theTime.length() == 0)
  {
    return;
  }

  GERTICO::ConvertTime::mapItGeRtiFedTime(geRtiFedTimeFactory, &tmpFedTime, theTime);
  pm.acquire();
  ita = times.find(tmpFedTime);
  if (ita != times.end())
  {
    ita->second++;
  }
  else
  {
    times[tmpFedTime] = dummy;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::addDmEvent(GeRtiFactory::GertiDmEvent const &theGertiDmEvent)
{
  GERTICO::RtiHubEventVector *eventPtr;
  GeRtiFactory::GeRtiHandle sourceType = 1;
  GeRtiFactory::GertiTmEvent gertiTmEvent;

  // The first "e" is sender, the second will get new event.
  eventPtr = f_getEvents(false, true);

  // Add the event at the end of the vector.
  GERTICO::RtiHubEvent *newEvent = new GERTICO::RtiHubEvent(sourceType);
  newEvent->pushEvent = new GeRtiFactory::PushEvent();
  newEvent->pushEvent->dmEvent(theGertiDmEvent);
  eventPtr->push_back(newEvent);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::addTmEvent(GeRtiFactory::GertiTmEvent const &theGertiTmEvent)
{
  GERTICO::RtiHubEventVector *eventPtr;
  GeRtiFactory::GeRtiHandle sourceType = 1;
  GeRtiFactory::GertiTmEvent gertiTmEvent;

  // The first "e" is sender, the second will get new event.
  eventPtr = f_getEvents(false, true);

  // Add the event at the end of the vector.
  GERTICO::RtiHubEvent *newEvent = new GERTICO::RtiHubEvent(sourceType);
  newEvent->pushEvent = new GeRtiFactory::PushEvent();
  newEvent->pushEvent->tmEvent(theGertiTmEvent);
  eventPtr->push_back(newEvent);
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::checkOverload(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_w)
                            {
  size_t size0;
  size_t size1;

  size0 = eVector[0].size();
  size1 = eVector[1].size();
  if (size0 > 100 || size1 > 100)
  {
    if (haveOverload == false)
    {
                              strcpy(galMsg, "Overload_true");
                              E2(GeRti_EC_w, "checkOverload", galMsg);
      haveOverload = true;
    }
  }
  else
  {
    if (haveOverload)
    {
                              strcpy(galMsg, "Overload_false");
                              E2(GeRti_EC_w, "checkOverload", galMsg);   // inserted by Gal converter
      haveOverload = false;
    }
  }
                            }
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::clear(void)
{
  firstESender = true;
  haveOverload = false;
}

// ---------------------------------------------------------------------------
//Return a pointer to the current event sequence to send.
// ---------------------------------------------------------------------------
GERTICO::RtiHubEventVector *GERTICO::FedEventSender::f_getEvents(bool const &isSender, bool const &theReliable)
{
  GERTICO::RtiHubEventVector *eventPtr;

  pm.acquire();
  if (theReliable)
  {
    if (firstESender)
    {
      if (isSender)
      {
        eventPtr = &eVector[1];
      }
      else
      {
        eventPtr = &eVector[0];
      }
    }
    else
    {
      if (isSender)
      {
        eventPtr = &eVector[0];
      }
      else
      {
        eventPtr = &eVector[1];
      }
    }
  }
  else
  {
    if (firstESender)
    {
      if (isSender)
      {
        eventPtr = &eVectorBestEffort[1];
      }
      else
      {
        eventPtr = &eVectorBestEffort[0];
      }
    }
    else
    {
      if (isSender)
      {
        eventPtr = &eVectorBestEffort[0];
      }
      else
      {
        eventPtr = &eVectorBestEffort[1];
      }
    }
  }
  pm.release();

  return eventPtr;
}

// ---------------------------------------------------------------------------
// Send the event sequence.
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::sendEvents(GERTICO::RtiHubEventVector &theGeRtiEventVector, bool const &theReliable)
{
  CORBA::Long d;
  CORBA::ULong length;
  GERTICO::RtiHubEventVector::iterator itGeRtiEventVector;
  GERTICO::RtiHubEventVector::iterator itGeRtiEventTestVector;
  GeRtiFactory::GertiPushEvent gertiPushEvent;
  GERTICO::RtiHubEvent *geRtiEventPtr;
  bool gotEnough = false;
  size_t size;
  unsigned long i;
  unsigned long indx = 0;
  unsigned long lenData;
  unsigned long sendLength = 0;
  unsigned long testLength;

  size = theGeRtiEventVector.size();
  GERTICO::Mapper::mapULongSizet(length, size);
  if (length == 0)
  {
    // No event to send.
    return;
  }
  gertiPushEvent.e.length(length);
  gertiPushEvent.e.length(0);

  // Make sure to process all events.
  for (itGeRtiEventVector = theGeRtiEventVector.begin(); itGeRtiEventVector != theGeRtiEventVector.end(); itGeRtiEventVector = theGeRtiEventVector.begin())
  {
    // Have a conditional loop until enough length found - have built-in lookahead logic.
    for (itGeRtiEventTestVector = theGeRtiEventVector.begin(); itGeRtiEventTestVector != theGeRtiEventVector.end(); itGeRtiEventTestVector = theGeRtiEventVector.begin())
    {
      geRtiEventPtr = *itGeRtiEventTestVector;
      d = geRtiEventPtr->pushEvent->_d();
      switch(d)
      {
        case 0:
        {
          testLength = 0;
          lenData = geRtiEventPtr->pushEvent->e().data.length();

          for (i = 0; i < lenData; i++)
          {
            testLength += geRtiEventPtr->pushEvent->e().data[i].value.length();
          }
          if (GERTICOconfRef.dataLength != 0 && GERTICOconfRef.dataLength != 1)
          {
            if (sendLength + testLength < GERTICOconfRef.dataLength)
            {
              // Have more capacity, try for more.
              gertiPushEvent.e.length(indx + 1);
              gertiPushEvent.e[indx] = *geRtiEventPtr->pushEvent;
              indx += 1;
              theGeRtiEventVector.erase(itGeRtiEventTestVector);
              delete geRtiEventPtr;
              sendLength += testLength;
              continue;
            }
          }
          gotEnough = true;
          sendLength += testLength;
          break;
        }
        case 1:
        {
          // Take the event eg. as piggyback.
          break;
        }
        case 2:
        {
          // Take the event eg. as piggyback.
          break;
        }
        case 3:
        {
          // Take the event eg. as piggyback.
          break;
        }
        case 4:
        {
          // Take the event eg. as piggyback.
          break;
        }
      }
      gertiPushEvent.e.length(indx + 1);
      gertiPushEvent.e[indx] = *geRtiEventPtr->pushEvent;
      indx += 1;
      theGeRtiEventVector.erase(itGeRtiEventTestVector);
      delete geRtiEventPtr;
      if (gotEnough)
      {
        break;
      }
    }

    try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_d)
                            {
                              unsigned int ind;
                              unsigned int indItem;
                              unsigned long lenItems;
                              unsigned long ul;
                              unsigned long ul1;
                              unsigned long ul2;

                              sprintf(galMsg, "numberOfEvents=%lu", length);
                              E2(GeRti_EC_d, "sendEvents", galMsg);
                              for (ind = 0; ind < length; ind++)
                              {
								                d = gertiPushEvent.e[ind]._d();
								                switch(d)
								                {
								                  case 0:
								                  {
                                    ul = gertiPushEvent.e[ind].e().source;
                                    ul1 = gertiPushEvent.e[ind].e()._cxx_class;
                                    ul2 = gertiPushEvent.e[ind].e().obj;
                                    if (gertiPushEvent.e[ind].e().type == GeRtiFactory::obj)
                                    {
                                      sprintf(galMsg, "source=%lu,class=%lu,object=%lu,update", ul, ul1, ul2);
                                    }
                                    else
                                    {
                                      sprintf(galMsg, "source=%lu,class=%lu,interaction", ul, ul1);
                                    }
                                    E2(GeRti_EC_d, "sendEvents", galMsg);   // inserted by Gal converter
                                    lenItems = gertiPushEvent.e[ind].e().data.length();
                                    for (indItem = 0; indItem < lenItems; indItem++)
                                    {
                                      GERTICO::Mapper::printAttributeHandleValue("pushData=", galMsg, gertiPushEvent.e[ind].e().data[indItem]);
                                      E2(GeRti_EC_d, "sendEvents", galMsg);   // inserted by Gal converter
                                    }
                                    break;
                                  }
								                  case 1:
								                  {
                                    long l;

                                    l = gertiPushEvent.e[ind].tmEvent().service;
                                    break;
                                  }
								                }
                              }
                            }
                           #endif   // inserted by Gal converter

      if (theReliable)
      {
        gertiPushEvent.reliableFlag = 1;
        proxyPushSupplierReliable->pushConsumerVar->push(gertiPushEvent);
      }
      else
      {
        gertiPushEvent.reliableFlag = 0;
        proxyPushSupplierBestEffort->pushConsumerVar->push(gertiPushEvent);
      }

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_EC_d, "sendEvents", "AfterPush");
                           #endif   // inserted by Gal converter
    }
    catch(CORBA::SystemException& e)
    {
      ACE_PRINT_EXCEPTION(e, "CORBA::SystemException in GERTICO::EventSender::sendEvents()");
    }

    // Reset important flags.
    gotEnough = false;
    indx = 0;
    sendLength = 0;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::toggleFirstESender()
{
  if (firstESender)
  {
    firstESender = false;
  }
  else
  {
    firstESender = true;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::addProxyPushSupplier(GeRtiEventMarket_ProxyPushSupplier_i *pps, bool const &theReliableFlag)
{
  if (theReliableFlag)
  {
    proxyPushSupplierReliable = pps;
  }
  else
  {
    proxyPushSupplierBestEffort = pps;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::delMinTimeStamp(GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
  GERTICO::GeRtiFedTime *geRtiFedTimePtr;
  GERTICO::GeRtiTimeMap::iterator itm;

  pm.acquire();
  for (itm = times.begin(); itm != times.end(); itm = times.begin())
  {
    if (*itm->first > theGeRtiFedTime)
    {
      break;
    }

    geRtiFedTimePtr = itm->first;
    times.erase(itm);
    delete geRtiFedTimePtr;
  }
  pm.release();

  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::getFederateRegions(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theInteraction, GERTICO::HandleBoolMap &theRegions)
{
  GERTICO::Interaction *currInteraction;
  GERTICO::InteractionMap::iterator itInteraction;

  // Check if interactions already administered.
  itInteraction = interactionMap.find(theInteraction);
  if (itInteraction != interactionMap.end())
  {
    // Have an interaction.
    currInteraction = itInteraction->second;
    currInteraction->getFederateRegions(theFederate, theRegions);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::getMinTimeStamp(GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
  GERTICO::GeRtiTimeMap::iterator itm;

  pm.acquire();
  itm = times.begin();
  if (itm != times.end())
  {
    theGeRtiFedTime = *itm->first;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FedEventSender::isDeleted(void)
{
  return deleted;
}

// ---------------------------------------------------------------------------
// NB: caller must secure the mutex lock.
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::printTimeStamp(void)
{
  GERTICO::GeRtiTimeMap::iterator itm;
  size_t size;
  char buff[1024];

  size = times.size();
  for (itm = times.begin(); itm != times.end(); itm++)
  {
    itm->first->getPrintableString(buff);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::print(void)
{
  GERTICO::RtiHubEventVector itGeRtiEventVector;
  size_t size;
  size_t i;

  for (i = 0; i < 2; i++)
  {
    size = eVector[i].size();
//    std::cout << "FedEventSender::print::reliable " << size << " " << federate << std::endl;
  }
  for (i = 0; i < 2; i++)
  {
    size = eVectorBestEffort[i].size();
//    std::cout << "FedEventSender::print::best_effort " << size << " " << federate << std::endl;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::processEvents(void)
{
  HandleSet::iterator itHS;
  GERTICO::RtiHubEventVector *eventPtr;
  GERTICO::GeRtiTimeVector geRtiTimeVector;

  eventPtr = f_getEvents(true, true);
  pm.acquire();
  sendEvents(*eventPtr, true);
  pm.release();

  eventPtr = f_getEvents(true, false);
  pm.acquire();
  sendEvents(*eventPtr, false);
  pm.release();

  pm.acquire();
  toggleFirstESender();
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::requestRetraction(GeRtiFactory::GeRtiHandle const &theHandle)
{
  GeRtiFactory::GertiTmEvent gertiTmEvent;

  gertiTmEvent.service = 14;
  gertiTmEvent.sourceId = federate;
  gertiTmEvent.theHandle = theHandle;
  addTmEvent(gertiTmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::setDeleted(void)
{
  deleted = true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::timeAdvanceGrant(GERTICO::GeRtiFedTime &theGeRtiFedTime, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime)
{
  char buf[128];
  GeRtiFactory::GertiTmEvent gertiTmEvent;
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_EC_i)
                            {
                              unsigned long f;

                              f = federate;
                              theGeRtiFedTime.getPrintableString(buf);
                              sprintf(galMsg,"Federate=%lu,fedTime=%s", f, buf);
                              E2(GeRti_EC_i,"Federate::timeAdvanceGrant", galMsg);
                            }
                           #endif   // inserted by Gal converter
theGeRtiFedTime.getPrintableString(buf);
theGaltGeRtiFedTime.getPrintableString(buf);
  gertiTmEvent.service = 11;
  if (!(theGeRtiFedTime.isPositiveInfinity()))
  {
    ConvertTime::mapIt(gertiTmEvent.timestamp, theGeRtiFedTime);
  }
  if (!(theGaltGeRtiFedTime.isPositiveInfinity()))
  {
    ConvertTime::mapIt(gertiTmEvent.timestampTwo, theGaltGeRtiFedTime);
  }
  gertiTmEvent.sourceId = federate;
  addTmEvent(gertiTmEvent);
  delMinTimeStamp(theGaltGeRtiFedTime);
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_i, "Federate::timeAdvanceGrant", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::timeConstrainedEnabled(const GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
  GeRtiFactory::GertiTmEvent gertiTmEvent;

  gertiTmEvent.service = 4;
  GERTICO::ConvertTime::mapIt(gertiTmEvent.timestamp, theGeRtiFedTime);
  gertiTmEvent.sourceId = federate;
  addTmEvent(gertiTmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FedEventSender::timeRegulationEnabled(const GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
  GeRtiFactory::GertiTmEvent gertiTmEvent;

  gertiTmEvent.service = 1;
  GERTICO::ConvertTime::mapIt(gertiTmEvent.timestamp, theGeRtiFedTime);
  gertiTmEvent.sourceId = federate;
  addTmEvent(gertiTmEvent);
}
