/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** EventHandler.cpp
**
*******************************************************************************/

#include "EventHandler.h"
#include "GeRtiEventMarketI.h"
#include "Util/GeRtiTypes.h"
#include "Util/Mapper.h"

/********************************** Gal begin ***************************************/

#ifdef GalDebug

#include "Gal/StdAfx.h"
#include "Gal/repository.h"
#include "Gal/event.h"

static class Repository_l *DM=(Repository::getSingleInstance())->getRepository_l("GeRtiDM.res","GeRtiDM");

static class Event *GeRti_DM_d=DM->getRefEvent("GeRti_DM_d");
static class Event *GeRti_DM_e=DM->getRefEvent("GeRti_DM_e");
static class Event *GeRti_DM_i=DM->getRefEvent("GeRti_DM_i");
static class Event *GeRti_DM_w=DM->getRefEvent("GeRti_DM_w");

static class Repository_l *r=(Repository::getSingleInstance())->getRepository_l("GeRtiEC.res","GeRtiEC");

static class Event *GeRti_EC_d=r->getRefEvent("GeRti_EC_d");
static class Event *GeRti_EC_e=r->getRefEvent("GeRti_EC_e");
static class Event *GeRti_EC_i=r->getRefEvent("GeRti_EC_i");
static class Event *GeRti_EC_w=r->getRefEvent("GeRti_EC_w");

static class Repository_l *FM=(Repository::getSingleInstance())->getRepository_l("GeRtiFM.res","GeRtiFM");

static class Event *GeRti_FM_d=FM->getRefEvent("GeRti_FM_d");
static class Event *GeRti_FM_e=FM->getRefEvent("GeRti_FM_e");
static class Event *GeRti_FM_feds_i=FM->getRefEvent("GeRti_FM_feds_i");
static class Event *GeRti_FM_i=FM->getRefEvent("GeRti_FM_i");
static class Event *GeRti_FM_save_restore_i=FM->getRefEvent("GeRti_FM_save_restore_i");
static class Event *GeRti_FM_sync_i=FM->getRefEvent("GeRti_FM_sync_i");
static class Event *GeRti_FM_w=FM->getRefEvent("GeRti_FM_w");

#endif

/********************************** Gal end ***************************************/

#define MAX_TXT 2048
static char galMsg[MAX_TXT];

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PeerSender::PeerSender(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, std::wstring const &theEventHub, GeRtiFactory::EventChannel_ptr const theEventChannelPtr)
{
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "PeerSender::PeerSender", "enter");
                           #endif   // inserted by Gal converter
  CORBA::Boolean reliableBoolean;
  CORBA::ULong ul;
  GeRtiFactory::GeRtiHandle sourceId = 0;
  GeRtiFactory::GeRtiHandle sourceType = 1;
  GeRtiFactory::SupplierAdmin_var supplierAdminVar;
  bool reliableBool;

  // Generic initialisation.
  lengthBestEffort = 0;
  lengthReliable = 0;

  supplierAdminVar = theEventChannelPtr->for_suppliers();
  reliableBool = true;
  reliableBoolean = 1;
  proxyPushSupplierReliable = new GeRtiEventMarket_ProxyPushSupplier_i(theGeRtiOrb, thePOA, reliableBool);
  proxyPushSupplierReliable->pushConsumerVar = supplierAdminVar->obtain_push_consumer(sourceType, sourceId, theEventHub.c_str());

  reliableBool = false;
  reliableBoolean = 0;
  proxyPushSupplierBestEffort = new GeRtiEventMarket_ProxyPushSupplier_i(theGeRtiOrb, thePOA, reliableBool);
  proxyPushSupplierBestEffort->pushConsumerVar = supplierAdminVar->obtain_push_consumer(sourceType, sourceId, theEventHub.c_str());
  // Allocate initial max size.
  ul = 128;
  gertiPushEventBestEffort.e.length(ul);
  gertiPushEventReliable.e.length(ul);
  ul = 0;
  gertiPushEventBestEffort.e.length(ul);
  gertiPushEventReliable.e.length(ul);
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "PeerSender::PeerSender", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PeerSender::~PeerSender(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "PeerSender::~PeerSender", "enter");
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "PeerSender::~PeerSender", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::PeerSender::addEvent(GeRtiFactory::PushEvent const &e, bool const &reliable, bool const &theSendNow)
{
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_i, "PeerSender::addEvent", "enter");
                           #endif   // inserted by Gal converter
  // TODO - bundle events
  if (reliable)
  {
    lengthReliable++;
    gertiPushEventReliable.sourceType = 1;
    gertiPushEventReliable.e.length(lengthReliable);
    gertiPushEventReliable.e[lengthReliable - 1] = e;
    gertiPushEventReliable.reliableFlag = 1;
    if (theSendNow)
    {
      proxyPushSupplierReliable->pushConsumerVar->push(gertiPushEventReliable);
      lengthReliable = 0;
    }
  }
  else
  {
    lengthBestEffort++;
    gertiPushEventBestEffort.sourceType = 1;
    gertiPushEventBestEffort.e.length(lengthBestEffort);
    gertiPushEventBestEffort.e[lengthBestEffort - 1] = e;
    gertiPushEventBestEffort.reliableFlag = 0;
    if (theSendNow)
    {
      proxyPushSupplierBestEffort->pushConsumerVar->push(gertiPushEventBestEffort);
      lengthBestEffort = 0;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_i, "PeerSender::addEvent", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHandler::EventHandler(ACE_Semaphore &thePs, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId, std::wstring const &theEventHub) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory), ps(thePs), privilegeToDeleteId(thePrivilegeToDeleteId), GERTICOconfRef(theGERTICOconf), myEventHub(theEventHub)
{
  // Generic initialisation.
  declarationManagementEC = NULL;
  desiredDataLength = 0;
  firstESender = true;
  firstESenderLocal = true;
  firstESenderPeer = true;
  immediateSend = true;
  mom = NULL;
  notDone = true;
  psLocal = NULL;
  psPeer = NULL;
  supportingServicesEC = NULL;
  timeService = NULL;
  timeServiceFac = NULL;

  // Specific initialisation.
  psLocal = new ACE_Semaphore(1);
  psPeer = new ACE_Semaphore(0);

  // Derived initialisation.
  if (GERTICOconfRef.dataLength > 1)
  {
    immediateSend = false;
    desiredDataLength = GERTICOconfRef.dataLength;
  }

  // Supporting Services
  supportingServicesEC = new GERTICO::SupportingServicesEC();

  // Declaration Management
  declarationManagementEC = new DeclarationManagementEC(privilegeToDeleteId, interactionMap, fedEventSenders, *supportingServicesEC, pmFed);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHandler::~EventHandler()
{
  CORBA::ULong indVector;
  GERTICO::FedEventSenderMap::iterator itFES;
  GERTICO::FedEventSender *currFedEventSender;
  GERTICO::RtiHubEventVector::iterator itGeRtiEventVector;
  GERTICO::RtiHubEvent *rtiHubEvent;

  pm.acquire();
  if (declarationManagementEC)
  {
    delete declarationManagementEC;
    declarationManagementEC = NULL;
  }

  if (supportingServicesEC)
  {
    delete supportingServicesEC;
    supportingServicesEC = NULL;
  }

  if (timeService)
  {
    delete timeService;
    timeService = NULL;
  }

  if (timeServiceFac)
  {
    delete timeServiceFac;
    timeServiceFac = NULL;
  }
  pm.release();

  pmFed.acquire();
  for (itFES = fedEventSenders.begin(); itFES != fedEventSenders.end(); itFES = fedEventSenders.begin())
  {
    currFedEventSender = itFES->second;
    delete currFedEventSender;
    fedEventSenders.erase(itFES);
  }
  pmFed.release();

  pmPeer.acquire();
  for (indVector = 0; indVector < 2; indVector++)
  {
    for (itGeRtiEventVector = eVectorPeerReliable[indVector].begin(); itGeRtiEventVector != eVectorPeerReliable[indVector].end(); itGeRtiEventVector = eVectorPeerReliable[indVector].begin())
    {
      rtiHubEvent = *itGeRtiEventVector;
      eVectorPeerReliable[indVector].erase(itGeRtiEventVector);
      delete rtiHubEvent;
    }

    for (itGeRtiEventVector = eVectorPeerBestEffort[indVector].begin(); itGeRtiEventVector != eVectorPeerBestEffort[indVector].end(); itGeRtiEventVector = eVectorPeerBestEffort[indVector].begin())
    {
      rtiHubEvent = *itGeRtiEventVector;
      eVectorPeerBestEffort[indVector].erase(itGeRtiEventVector);
      delete rtiHubEvent;
    }
  }
  pmPeer.release();
}

// ---------------------------------------------------------------------------
// Add event to subscribed linked lists.
// 1. Have local events for this hub.
// 2. Have perr events for other hubs.
// 3. Have events for federates joined to this hub.
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addEvent(GeRtiFactory::GertiPushEvent const &e)
{
  CORBA::Long d;
  CORBA::ULong ind;
  CORBA::ULong indVector;
  CORBA::ULong len = 0;
  CORBA::ULong length;
  GERTICO::RtiHubEvent *rtiHubEvent;
  GERTICO::RtiHubEvent *rtiHubEventPeer;
  GeRtiFactory::GertiPushEvent *gertiPushEvent;
  bool gotLocal = false;
  bool gotPeerEvent = false;
  size_t size;

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::addEventOneArg", "enter");
                           #endif   // inserted by Gal converter

  // Need a copy of the const event.
  gertiPushEvent = new GeRtiFactory::GertiPushEvent(e);
  // Put local events into separate list.
  pmLocal.acquire();
  if (firstESenderLocal)
  {
    indVector = 1;
  }
  else
  {
    indVector = 0;
  }

  length = gertiPushEvent->e.length();
  getEventsLength(len, *gertiPushEvent);

  // Distribute events that are used by this hub.
  for (ind = 0; ind < length; ind++)
  {
    d = gertiPushEvent->e[ind]._d();
    if (d != 0)
    {
      rtiHubEvent = new GERTICO::RtiHubEvent(e.sourceType);
      rtiHubEvent->pushEvent = new GeRtiFactory::PushEvent(gertiPushEvent->e[ind]);
      eVectorLocal[indVector].push_back(rtiHubEvent);
      gotLocal = true;
    }
  }
  pmLocal.release();
  if (gotLocal)
  {
    psLocal->release();
  }

  // Only if any peer hub exists.
  size = peerSenderMap.size();
  if (size)
  {
    // Put peer events into a separate list.
    pmPeer.acquire();
    if (gertiPushEvent->sourceType != 1)
    {
      if (firstESenderPeer)
      {
        indVector = 1;
      }
      else
      {
        indVector = 0;
      }

      for (ind = 0; ind < length; ind++)
      {
        rtiHubEventPeer = new GERTICO::RtiHubEvent(e.sourceType);
        rtiHubEventPeer->pushEvent = new GeRtiFactory::PushEvent(gertiPushEvent->e[ind]);
        if (e.reliableFlag)
        {
          eVectorPeerReliable[indVector].push_back(rtiHubEventPeer);
        }
        else
        {
          eVectorPeerBestEffort[indVector].push_back(rtiHubEventPeer);
        }
        gotPeerEvent = true;
      }
    }
    pmPeer.release();
    if (gotPeerEvent)
    {
      psPeer->release();
    }
  }

  // Put joined federate events into a separate list.
  pm.acquire();

  if (firstESender)
  {
    indVector = 1;
  }
  else
  {
    indVector = 0;
  }

  if (e.reliableFlag)
  {
    eVectorReliable[indVector].push_back(gertiPushEvent);
  }
  else
  {
    eVectorBestEffort[indVector].push_back(gertiPushEvent);
  }

  pm.release();
  ps.release();

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::addEventOneArg", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Add event to subscribed linked list.
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addEvent(GeRtiFactory::PushEvent const &e, bool const &theReliableFlag, GeRtiFactory::GeRtiHandle const &theSourceType)
{
  CORBA::Long d;
  GERTICO::FedEventSender *currFES;
  GERTICO::HandleSet desiredAttributes;
  GERTICO::HandleSet eventAttributes;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  GeRtiFactory::PushEvent pushEvent(e);
  GERTICO::FedEventSenderMap::iterator it;
  GERTICO::PeerSenderMap::iterator itPeerSenderMap;
  unsigned long ul;

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::addEvent", "enter");
                           #endif   // inserted by Gal converter
  // Must lock the access to the list.
  pm.acquire();

  d = e._d();
  switch(d)
  {
    case 0:
    {
                           #ifdef GalDebug   // inserted by Gal converter
                           if (e.e().type)
                           {
                              E2(GeRti_EC_i, "EventHandler::addEvent", "update event");
                           }
                           else
                           {
                              E2(GeRti_EC_i, "EventHandler::addEvent", "interaction event");
                           }
                           #endif   // inserted by Gal converter
      ul = e.e()._cxx_class;
      if (ul == 0)
      {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_e, "EventHandler::addEvent", "Got a zero class");
                           #endif   // inserted by Gal converter
      }

      // May be a MOM interaction. Let MOM check all events.
      try
      {
        if (mom)
        {
          mom->doMomInteraction(pushEvent.e());
        }
      }
      catch(...)
      {
      }

      // Count the events sent by the sending federate.
      doSentCounts(pushEvent);

      // Find receiving federates.
      if (pushEvent.e().type == GeRtiFactory::obj)
      {
        getEventAttributes(pushEvent.e(), eventAttributes);
      }
      else
      {
        declarationManagementEC->getFederatesForInteraction(pushEvent.e().source, pushEvent.e()._cxx_class, federates);
      }

      for (it = fedEventSenders.begin(); it != fedEventSenders.end(); it++)
      {
        if (it->first == pushEvent.e().source)
        {
          continue;
        }

        if (pushEvent.e().type == GeRtiFactory::obj)
        {
          declarationManagementEC->getDesiredAttributes(it->first, pushEvent.e()._cxx_class, eventAttributes, desiredAttributes);
          if (desiredAttributes.size() == 0)
          {
            continue;
          }
        }
        else
        {
          itFederate = federates.find(it->first);
          if (itFederate == federates.end())
          {
            continue;
          }
        }

        currFES = it->second;

        currFES->addEvent(pushEvent.e(), theSourceType, desiredAttributes);
      }
      break;
    }
    case 1:
    {
      break;
    }
    case 2:
    {
      break;
    }
    case 4:
    {
      break;
    }
  }

  pm.release();
  ps.release();
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::addEvent", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addTmPeerEvent(GeRtiFactory::GertiTmEvent const &theGertiTmEvent)
{
  CORBA::ULong indVector;
  CORBA::ULong sourceType = 1;
  CORBA::ULong ul;
  GERTICO::RtiHubEvent *rtiHubEvent;

  pmPeer.acquire();

  rtiHubEvent = new GERTICO::RtiHubEvent(sourceType);
  rtiHubEvent->pushEvent = new GeRtiFactory::PushEvent();

  rtiHubEvent->pushEvent->tmEvent(theGertiTmEvent);
  if (firstESender)
  {
    indVector = 1;
  }
  else
  {
    indVector = 0;
  }

  ul = eVectorPeerReliable[indVector].size();
  std::cout << "addTmPeerEvent before " << ul << std::endl;
  eVectorPeerReliable[indVector].push_back(rtiHubEvent);
  ul = eVectorPeerReliable[indVector].size();
  std::cout << "addTmPeerEvent after " << ul << std::endl;

  pmPeer.release();
  psPeer->release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addHandleMapMap(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleMapMap &theHandleMapMap)
{
  GERTICO::HandleMapMap::iterator itHandleMapMap;

  itHandleMapMap = theHandleMapMap.find(theFederate);
  if (itHandleMapMap != theHandleMapMap.end())
  {
    GERTICO::HandleMap::iterator itHandleMap;

    itHandleMap = itHandleMapMap->second.find(theClass);
    if (itHandleMap != itHandleMapMap->second.end())
    {
      itHandleMap->second += 1;
    }
    else
    {
      GeRtiFactory::GeRtiHandle count = 1;
      itHandleMapMap->second[theClass] = count;
    }
  }
  else
  {
    GERTICO::HandleMap handleMap;
    GeRtiFactory::GeRtiHandle count = 1;

    handleMap[theClass] = count;
    theHandleMapMap[theFederate] = handleMap;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::addProxyPushSupplier(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiEventMarket_ProxyPushSupplier_i *pps, bool const &theReliableFlag)
{
  GERTICO::FedEventSender *currFedEventSender;
  GERTICO::FedEventSenderMap::iterator it;

  pmFed.acquire();
  it = fedEventSenders.find(theFederate);
  if (it == fedEventSenders.end())
  {
    currFedEventSender = new GERTICO::FedEventSender(theFederate, interactionMap, GERTICOconfRef, geRtiFedTimeFactory, ps);
    fedEventSenders[theFederate] = currFedEventSender;
  }
  else
  {
    currFedEventSender = it->second;
  }
  currFedEventSender->addProxyPushSupplier(pps, theReliableFlag);
  pmFed.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::clear(void)
{
  GERTICO::FedEventSender *fedEventSenderPtr;
  GERTICO::FedEventSenderMap::iterator itFedEventSenderMap;

  for (itFedEventSenderMap = fedEventSenders.begin(); itFedEventSenderMap != fedEventSenders.end(); itFedEventSenderMap = fedEventSenders.begin())
  {
    fedEventSenderPtr = itFedEventSenderMap->second;
    fedEventSenders.erase(itFedEventSenderMap);
    delete fedEventSenderPtr;
  }
  federateSentInteractionBestEffortCounts.clear();
  federateSentInteractionReliableCounts.clear();
  federateSentUpdateBestEffortCounts.clear();
  federateSentUpdateReliableCounts.clear();
  interactionMap.clear();
  supportingServicesEC->clear();
  declarationManagementEC->clear();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::clearFederates(void)
{
  GERTICO::FedEventSender *fedEventSenderPtr;
  GERTICO::FedEventSenderMap::iterator itFedEventSenderMap;

  for (itFedEventSenderMap = fedEventSenders.begin(); itFedEventSenderMap != fedEventSenders.end(); itFedEventSenderMap++)
  {
    fedEventSenderPtr = itFedEventSenderMap->second;
    fedEventSenderPtr->clear();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::distributeEvents(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::distributeEvents", "enter");
                           #endif   // inserted by Gal converter
  CORBA::ULong ind;
  CORBA::ULong indVector;
  CORBA::ULong len;
  GERTICO::GeRtiPushEventVector::iterator itGeRtiPushEventVector;
  GeRtiFactory::GertiPushEvent *gertiPushEvent;
  bool b;

  // Mutex held only as long as needed to check the iterator.
  pm.acquire();
  if (firstESender)
  {
    indVector = 0;
  }
  else
  {
    indVector = 1;
  }

  for (itGeRtiPushEventVector = eVectorReliable[indVector].begin(); itGeRtiPushEventVector != eVectorReliable[indVector].end(); itGeRtiPushEventVector = eVectorReliable[indVector].begin())
  {
    gertiPushEvent = *itGeRtiPushEventVector;
    eVectorReliable[indVector].erase(itGeRtiPushEventVector);
    // Minimal holding of the mutex.
    pm.release();
    b = true;
    len = gertiPushEvent->e.length();
    for (ind = 0; ind < len; ind++)
    {
      addEvent(gertiPushEvent->e[ind], b, gertiPushEvent->sourceType);
    }
    pm.acquire();
  }
  // At this point we are holding the mutex!
  for (itGeRtiPushEventVector = eVectorBestEffort[indVector].begin(); itGeRtiPushEventVector != eVectorBestEffort[indVector].end(); itGeRtiPushEventVector = eVectorBestEffort[indVector].begin())
  {
    gertiPushEvent = *itGeRtiPushEventVector;
    eVectorBestEffort[indVector].erase(itGeRtiPushEventVector);
    pm.release();
    b = false;
    len = gertiPushEvent->e.length();
    for (ind = 0; ind < len; ind++)
    {
      addEvent(gertiPushEvent->e[ind], b, gertiPushEvent->sourceType);
    }
    pm.acquire();
  }
  if (firstESender)
  {
    firstESender = false;
  }
  else
  {
    firstESender = true;
  }

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::distributeEvents", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::distributePeerEvents(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::distributePeerEvents", "enter");
                           #endif   // inserted by Gal converter
  CORBA::ULong indVector;
  CORBA::ULong len = 0;
  CORBA::ULong lenTest = 0;
  GERTICO::PeerSenderMap::iterator itPeerSenderMap;
  GERTICO::RtiHubEvent *rtiHubEvent;
  GERTICO::RtiHubEvent *rtiHubEventTest;
  GERTICO::RtiHubEventVector::iterator itPushEventVector;
  GERTICO::RtiHubEventVector::iterator itPushEventVectorTest;
  bool b;
  bool sendNow;

  // Do not need to acquire mutex since this is the only function where
  // the value is changed - at that point it must be acquired.
  if (firstESenderPeer)
  {
    indVector = 0;
  }
  else
  {
    indVector = 1;
  }

  for (itPushEventVector = eVectorPeerReliable[indVector].begin(); itPushEventVector != eVectorPeerReliable[indVector].end(); itPushEventVector = eVectorPeerReliable[indVector].begin())
  {
    rtiHubEvent = *itPushEventVector;
    b = true;
    if (immediateSend)
    {
      sendNow = true;
    }
    else
    {
      getEventLength(len, *rtiHubEvent->pushEvent);
      if (len < desiredDataLength)
      {
        if (itPushEventVector != eVectorPeerReliable[indVector].end())
        {
          itPushEventVectorTest = itPushEventVector;
          itPushEventVectorTest++;
          if (itPushEventVectorTest != eVectorPeerReliable[indVector].end())
          {
            rtiHubEventTest = *itPushEventVectorTest;
            lenTest = len;
            getEventLength(lenTest, *rtiHubEventTest->pushEvent);
            if (lenTest < desiredDataLength)
            {
              sendNow = false;
            }
            else
            {
              sendNow = true;
            }
          }
          else
          {
            sendNow = true;
          }
        }
        else
        {
          sendNow = true;
        }
      }
    }
    eVectorPeerReliable[indVector].erase(itPushEventVector);
    for (itPeerSenderMap = peerSenderMap.begin(); itPeerSenderMap != peerSenderMap.end(); itPeerSenderMap++)
    {
      itPeerSenderMap->second->addEvent(*rtiHubEvent->pushEvent, b, sendNow);
    }
    delete rtiHubEvent;
  }

  for (itPushEventVector = eVectorPeerBestEffort[indVector].begin(); itPushEventVector != eVectorPeerBestEffort[indVector].end(); itPushEventVector = eVectorPeerBestEffort[indVector].begin())
  {
    rtiHubEvent = *itPushEventVector;
    b = false;
    if (immediateSend)
    {
      sendNow = true;
    }
    else
    {
      getEventLength(len, *rtiHubEvent->pushEvent);
      if (len < desiredDataLength)
      {
        if (itPushEventVector != eVectorPeerBestEffort[indVector].end())
        {
          itPushEventVectorTest = itPushEventVector;
          itPushEventVectorTest++;
          if (itPushEventVectorTest != eVectorPeerBestEffort[indVector].end())
          {
            rtiHubEventTest = *itPushEventVectorTest;
            lenTest = len;
            getEventLength(lenTest, *rtiHubEventTest->pushEvent);
            if (lenTest < desiredDataLength)
            {
              sendNow = false;
            }
            else
            {
              sendNow = true;
            }
          }
          else
          {
            sendNow = true;
          }
        }
        else
        {
          sendNow = true;
        }
      }
    }
    eVectorPeerBestEffort[indVector].erase(itPushEventVector);
    getEventLength(len, *rtiHubEvent->pushEvent);
    if (len < desiredDataLength)
    {
      getEventLength(lenTest, *rtiHubEvent->pushEvent);
    }
    for (itPeerSenderMap = peerSenderMap.begin(); itPeerSenderMap != peerSenderMap.end(); itPeerSenderMap++)
    {
      itPeerSenderMap->second->addEvent(*rtiHubEvent->pushEvent, b, sendNow);
    }
    delete rtiHubEvent;
  }

  // Mutex held only as long as needed to change the flag.
  pmPeer.acquire();
  if (firstESenderPeer)
  {
    firstESenderPeer = false;
  }
  else
  {
    firstESenderPeer = true;
  }

  pmPeer.release();
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::distributePeerEvents", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::doHubEvent(GERTICO::RtiHubEvent const &theRtiHubEvent)
{
  CORBA::Long d;
  GERTICO::HandleSet desiredAttributes;
  GERTICO::HandleSet eventAttributes;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::FedEventSenderMap::iterator it;

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::doHubEvent", "enter");
                           #endif   // inserted by Gal converter
  // Must lock the access to the list.
//  pm.acquire();

  d = theRtiHubEvent.pushEvent->_d();
  switch(d)
  {
    case 0:
    {
      // Not used locally.
      break;
    }
    case 1:
    {
      long l;

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_i, "EventHandler::doHubEvent", "time management event");
                           #endif   // inserted by Gal converter
      l = theRtiHubEvent.pushEvent->tmEvent().service;
//  pm.release();
      doTm(theRtiHubEvent.pushEvent->tmEvent(), theRtiHubEvent.sourceType);
//  pm.acquire();
      break;
    }
    case 2:
    {
      long l;

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_i, "EventHandler::doHubEvent", "declaration management event");
                           #endif   // inserted by Gal converter
      l = theRtiHubEvent.pushEvent->dmEvent().service;
//  pm.release();
      doDm(theRtiHubEvent.pushEvent->dmEvent());
//  pm.acquire();
      break;
    }
    case 4:
    {
      long l;

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_i, "EventHandler::doHubEvent", "federation management event");
                           #endif   // inserted by Gal converter
      l = theRtiHubEvent.pushEvent->fmEvent().service;
//  pm.release();
      doFm(theRtiHubEvent.pushEvent->fmEvent());
//  pm.acquire();
      break;
    }
  }

//  pm.release();
  ps.release();
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_i, "EventHandler::doHubEvent", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::doSentCounts(GeRtiFactory::PushEvent const &thePushEvent)
{
  CORBA::Long d;
  CORBA::ULong j;
  CORBA::ULong lenData;

  // Only want updates and interactions.
  d = thePushEvent._d();
  if (d != 0)
  {
    return;
  }

  if (thePushEvent.e().type == GeRtiFactory::obj)
  {
    lenData = thePushEvent.e().data.length();
    for (j = 0; j < lenData; j++)
    {
      // Updates.
      if (thePushEvent.e().data[j].bestEffort)
      {
        addHandleMapMap(thePushEvent.e().source, thePushEvent.e()._cxx_class, federateSentUpdateBestEffortCounts);
      }
      else
      {
        addHandleMapMap(thePushEvent.e().source, thePushEvent.e()._cxx_class, federateSentUpdateReliableCounts);
      }
    }
  }
  else
  {
    // Interactions.
    if (thePushEvent.e().bestEffort)
    {
      addHandleMapMap(thePushEvent.e().source, thePushEvent.e()._cxx_class, federateSentInteractionBestEffortCounts);
    }
    else
    {
      addHandleMapMap(thePushEvent.e().source, thePushEvent.e()._cxx_class, federateSentInteractionReliableCounts);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::doDm(GeRtiFactory::GertiDmEvent const &theGertiDmEvent)
{
	/*
    service values:
		publishObjectClass == 0
		unpublishObjectClass == 1
		publishInteractionClass == 2
		unpublishInteractionClass == 3
		subscribeObjectClassAttributes == 4
		unsubscribeObjectClass == 5
		subscribeInteractionClass == 6
		unsubscribeInteractionClass == 7
		unpublishObjectClassAttributes == 8
		unsubscribeObjectClassAttributes == 9
		startRegistrationForObjectClass == 10
		stopRegistrationForObjectClass == 11
		turnInteractionsOn == 12
		turnInteractionsOff == 13

    long service;
    // Federate or event hub id.
		GeRtiFactory::GeRtiHandle sourceId;
    // Handle.
		GeRtiFactory::GeRtiHandle theHandle;
    // Handles.
		GeRtiFactory::Handles theHandles;
    // Active
    boolean theActive;
	*/
  switch(theGertiDmEvent.service)
  {
    case 0:
    {
      GERTICO::HandleSet attributeSet;
      GERTICO::HandleSet::iterator itAttribute;
      
      // publishObjectClass
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                             sprintf(galMsg, "federate=%lu, class=%lu", theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
                             E2(GeRti_DM_i, "publishObjectClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      GERTICO::Mapper::mapHandleSet(attributeSet, theGertiDmEvent.theHandles);
      // Implicitly published.
      itAttribute = attributeSet.find(privilegeToDeleteId);
      if (itAttribute == attributeSet.end())
      {
        attributeSet.insert(privilegeToDeleteId);
      }

      supportingServicesEC->fillObjectParents(theGertiDmEvent.theHandle, theGertiDmEvent.theBaseClassHandles);
      declarationManagementEC->publishObjectClass(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle, attributeSet);
      break;
    }
    case 1:
    {
      // unpublishObjectClass
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                             sprintf(galMsg, "federate=%lu, class=%lu", theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
                             E2(GeRti_DM_i, "unpublishObjectClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      declarationManagementEC->unpublishObjectClass(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
      break;
    }
    case 2:
    {
      // publishInteractionClass
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                             sprintf(galMsg, "federate=%lu, class=%lu", theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
                             E2(GeRti_DM_i, "publishInteractionClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      supportingServicesEC->fillInteractionParents(theGertiDmEvent.theHandle, theGertiDmEvent.theHandles);
      declarationManagementEC->publishInteractionClass(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
      timeService->psToken->release();
      break;
    }
    case 3:
    {
      // unpublishInteractionClass
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                             sprintf(galMsg, "federate=%lu, class=%lu", theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
                             E2(GeRti_DM_i, "unpublishInteractionClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      declarationManagementEC->interactionHolder->unpublishInteractionClass(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
      timeService->psToken->release();
      break;
    }
    case 4:
    {
      // subscribeObjectClassAttributes
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                             sprintf(galMsg, "federate=%lu, class=%lu", theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
                             E2(GeRti_DM_i, "subscribeObjectClassAttributes", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      GERTICO::HandleSet attSet;
      
      GERTICO::Mapper::mapHandleSet(attSet, theGertiDmEvent.theHandles);
      declarationManagementEC->subscribeObjectClassAttributes(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle, attSet, theGertiDmEvent.theActive);
      break;
    }
    case 5:
    {
      // unsubscribeObjectClass
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                             sprintf(galMsg, "federate=%lu, class=%lu", theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
                             E2(GeRti_DM_i, "unsubscribeObjectClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      // Empty set!
      GERTICO::HandleSet attributeSet;
      
      declarationManagementEC->unsubscribeObjectClass(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle, attributeSet);
      break;
    }
    case 6:
    {
      // subscribeInteractionClass
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                             sprintf(galMsg, "federate=%lu, class=%lu", theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
                             E2(GeRti_DM_i, "subscribeInteractionClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      GERTICO::HandleSet regions;
      bool active = false;

      if (theGertiDmEvent.theActive)
      {
        active = true;
      }
      // Default region denoted by an id of 0.
      regions.insert(0);
      declarationManagementEC->subscribeInteractionClass(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle, active, regions);
      timeService->psToken->release();
      break;
    }
    case 7:
    {
      // unsubscribeInteractionClass
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                             sprintf(galMsg, "federate=%lu, class=%lu", theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
                             E2(GeRti_DM_i, "unsubscribeInteractionClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      GeRtiFactory::GeRtiHandle region = 0;
      GERTICO::HandleSet regions;

      declarationManagementEC->interactionHolder->unsubscribeInteractionClass(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle, region, fedEventSenders);
      timeService->psToken->release();
      regions.insert(0);
      declarationManagementEC->interactionHolder->unsubscribeInteractionClassWithRegions(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle, regions);
      break;
    }
    case 8:
    {
		  // unpublishObjectClassAttributes
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                             sprintf(galMsg, "federate=%lu, class=%lu", theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
                             E2(GeRti_DM_i, "unpublishObjectClassAttributes", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      GERTICO::HandleSet attributeSet;

      GERTICO::Mapper::mapHandleSet(attributeSet, theGertiDmEvent.theHandles);
      declarationManagementEC->unpublishObjectClassAttributes(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle, attributeSet);
      break;
    }
    case 9:
    {
		  // unsubscribeObjectClassAttributes
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                             sprintf(galMsg, "federate=%lu, class=%lu", theGertiDmEvent.sourceId, theGertiDmEvent.theHandle);
                             E2(GeRti_DM_i, "unsubscribeObjectClassAttributes", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      GERTICO::HandleSet attributeSet;
      GERTICO::Mapper::mapHandleSet(attributeSet, theGertiDmEvent.theHandles);

      declarationManagementEC->unsubscribeObjectClass(theGertiDmEvent.sourceId, theGertiDmEvent.theHandle, attributeSet);
      break;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::doFm(GeRtiFactory::GertiFmEvent const &theGertiFmEvent)
{
  switch(theGertiFmEvent.service)
  {
    case 0:
    {
      // joinFederationExecution
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_feds_i, "GERTICO::EventHandler::doFm", "joinFederationExecution");
                           #endif   // inserted by Gal converter
      timeService->joinFederationExecution(theGertiFmEvent.sourceId);
      break;
    }
    case 1:
    {
      // resignFederationExecution
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_feds_i, "GERTICO::EventHandler::doFm", "resignFederationExecution");
                           #endif   // inserted by Gal converter
      GERTICO::FedEventSenderMap::iterator itFedEventSenderMap;

      declarationManagementEC->resignFederationExecution(theGertiFmEvent.sourceId);
      timeService->resignFederationExecution(theGertiFmEvent.sourceId);
      pmFed.acquire();
      itFedEventSenderMap = fedEventSenders.find(theGertiFmEvent.sourceId);
      if (itFedEventSenderMap != fedEventSenders.end())
      {
        fedEventSendersDead[theGertiFmEvent.sourceId] = itFedEventSenderMap->second;
        fedEventSenders.erase(itFedEventSenderMap);
      }
      pmFed.release();
      break;
    }
    default:
    {
                           #ifdef GalDebug   // inserted by Gal converter
                              char a[128];
                              sprintf(a, "unknown service %d", theGertiFmEvent.service);
                              E2(GeRti_EC_e, "GERTICO::EventHandler::doDm", a);
                           #endif   // inserted by Gal converter
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::doTm(GeRtiFactory::GertiTmEvent const &theGertiTmEvent, GeRtiFactory::GeRtiHandle const &theSourceType)
{
                           #ifdef GalDebug   // inserted by Gal converter
                              char a[128];
                              sprintf(a, "service %d", theGertiTmEvent.service);
                              E2(GeRti_EC_e, "GERTICO::EventHandler::doTm", a);
                           #endif   // inserted by Gal converter
  switch(theGertiTmEvent.service)
  {
    case 0:
    {
      // enableTimeRegulation
#ifdef IEEE_1516
      std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> logicalTimeInterval(geRtiLogicalTimeIntervalFactory.makeZero());
      GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(geRtiLogicalTimeIntervalFactory, *logicalTimeInterval, theGertiTmEvent.timestampTwo);
      timeService->enableTimeRegulation(theGertiTmEvent.sourceId, *logicalTimeInterval, theSourceType);
#else
      std::auto_ptr<GERTICO::GeRtiFedTime> fedTime;
      std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> logicalTimeInterval(geRtiLogicalTimeIntervalFactory.makeZero());
      GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, fedTime, theGertiTmEvent.timestamp);
      GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(geRtiLogicalTimeIntervalFactory, *logicalTimeInterval, theGertiTmEvent.timestampTwo);
      timeService->enableTimeRegulation(theGertiTmEvent.sourceId, *fedTime, *logicalTimeInterval, theSourceType);
#endif
      timeService->process();
//      timeService->psToken->release();
      break;
    }
    case 3:
    {
      // enableTimeConstrained
      timeService->enableTimeConstrained(theGertiTmEvent.sourceId, theSourceType);
      timeService->process();
//      timeService->psToken->release();
      break;
    }
    case 6:
    {
      // timeAdvanceRequest
      std::auto_ptr<GERTICO::GeRtiFedTime> fedTime;

      GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, fedTime, theGertiTmEvent.timestamp);
      timeService->timeAdvanceRequest(theGertiTmEvent.sourceId, *fedTime);
      timeService->process();
//      timeService->psToken->release();
      break;
    }
    case 7:
    {
      // timeAdvanceRequestAvailable
      std::auto_ptr<GERTICO::GeRtiFedTime> fedTime;

      GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, fedTime, theGertiTmEvent.timestamp);
      timeService->timeAdvanceRequestAvailable(theGertiTmEvent.sourceId, *fedTime);
      timeService->process();
//      timeService->psToken->release();
      break;
    }
    case 8:
    {
      // nextEventRequest
      std::auto_ptr<GERTICO::GeRtiFedTime> fedTime;

      GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, fedTime, theGertiTmEvent.timestamp);
      timeService->nextEventRequest(theGertiTmEvent.sourceId, *fedTime);
      timeService->process();
//      timeService->psToken->release();
      break;
    }
    case 9:
    {
      // nextEventRequestAvailable
      std::auto_ptr<GERTICO::GeRtiFedTime> fedTime;

      GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, fedTime, theGertiTmEvent.timestamp);
      timeService->nextEventRequestAvailable(theGertiTmEvent.sourceId, *fedTime);
      timeService->process();
//      timeService->psToken->release();
      break;
    }
    case 10:
    {
      // flushQueueRequest
      std::auto_ptr<GERTICO::GeRtiFedTime> fedTime;

      GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, fedTime, theGertiTmEvent.timestamp);
      timeService->flushQueueRequest(theGertiTmEvent.sourceId, *fedTime);
      timeService->process();
//      timeService->psToken->release();
      break;
    }
    case 12:
    {
      // modifyLookahead
      std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> logicalTimeInterval(geRtiLogicalTimeIntervalFactory.makeZero());

      GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(geRtiLogicalTimeIntervalFactory, *logicalTimeInterval, theGertiTmEvent.timestamp);
      timeService->modifyLookahead(theGertiTmEvent.sourceId, *logicalTimeInterval);
      timeService->process();
      break;
    }
    case 13:
    {
      // retract
      timeService->retract(theGertiTmEvent.sourceId, theGertiTmEvent.theHandle);
      timeService->process();
      break;
    }
    case 14:
    {
		  // requestRetraction
      break;
    }
    case 15:
    {
		  // timeRegulationPeerEnabled
      std::auto_ptr<GERTICO::GeRtiFedTime> fedTime;

      GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, fedTime, theGertiTmEvent.timestamp);
      timeService->timeRegulationPeerEnabled(theGertiTmEvent.sourceId, *fedTime);
      timeService->process();
      break;
    }
    case 16:
    {
		  // timeConstrainedPeerEnabled
      std::auto_ptr<GERTICO::GeRtiFedTime> fedTime;

      GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, fedTime, theGertiTmEvent.timestamp);
      timeService->timeConstrainedPeerEnabled(theGertiTmEvent.sourceId, *fedTime);
      timeService->process();
      break;
    }
    default:
    {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_e, "GERTICO::EventHandler::doTm", "unknown service");
                           #endif   // inserted by Gal converter
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_e, "GERTICO::EventHandler::doTm", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::findReceivingFederates(GERTICO::HandleSet &theFederates, GeRtiFactory::PushEvent &thePushEvent)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong numberOfAttributes;
  CORBA::ULong numberOfSubscribers;
  GERTICO::HandleSet::iterator itFederate;

  theFederates.empty();

  if (thePushEvent.e().type == GeRtiFactory::obj)
  {
    numberOfAttributes = thePushEvent.e().data.length();
    for (i = 0; i < numberOfAttributes; i++)
    {
      numberOfSubscribers = thePushEvent.e().data[i].theSubscribers.length();
      for (j = 0; j < numberOfSubscribers; j++)
      {
        itFederate = theFederates.find(thePushEvent.e().data[i].theSubscribers[j]);
        if (itFederate == theFederates.end())
        {
          theFederates.insert(thePushEvent.e().data[i].theSubscribers[j]);
        }
      }
    }
  }
  else
  {
    numberOfSubscribers = thePushEvent.e().theSubscribers.length();
    for (j = 0; j < numberOfSubscribers; j++)
    {
      itFederate = theFederates.find(thePushEvent.e().theSubscribers[j]);
      if (itFederate == theFederates.end())
      {
        theFederates.insert(thePushEvent.e().theSubscribers[j]);
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getEventAttributes(GeRtiFactory::GeRtiEvent const &theGeRtiEvent, GERTICO::HandleSet &theEventAttributes)
{
  CORBA::ULong i;
  CORBA::ULong length;

  // Make sure the set is empty.
  theEventAttributes.clear();

  length = theGeRtiEvent.data.length();
  for (i = 0; i < length; i++)
  {
    theEventAttributes.insert(theGeRtiEvent.data[i].id);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getEventLength(CORBA::ULong &theLength, GeRtiFactory::PushEvent &thePushEvent)
{
  CORBA::Long d;

  d = thePushEvent._d();
  switch(d)
  {
    case 0:
    {
      theLength += thePushEvent.e().data.length();
      break;
    }
    case 1:
    {
      theLength += sizeof(GeRtiFactory::GertiTmEvent);
      break;
    }
    case 2:
    {
      theLength += sizeof(GeRtiFactory::GertiDmEvent);
      break;
    }
    case 3:
    {
      theLength += sizeof(GeRtiFactory::GertiDdmEvent);
      break;
    }
    case 4:
    {
      theLength += sizeof(GeRtiFactory::GertiFmEvent);
      break;
    }
    default:
    {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_e, "EventHandler::getEventsLength", "length calculation not fully covered");
                           #endif   // inserted by Gal converter
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getEventsLength(CORBA::ULong &theLength, GeRtiFactory::GertiPushEvent &theGertiPushEvent)
{
  CORBA::ULong i;
  CORBA::ULong length;

  length = theGertiPushEvent.e.length();

  for (i = 0; i < length; i++)
  {
    getEventLength(theLength, theGertiPushEvent.e[i]);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getInteractionsSentCount(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleMap &theHandleMap, bool const &theBestEffort)
{
  GERTICO::HandleMapMap::iterator itHandleMapMap;

  if (theBestEffort)
  {
    itHandleMapMap = federateSentInteractionBestEffortCounts.find(theFederate);
    if (itHandleMapMap != federateSentInteractionBestEffortCounts.end())
    {
      theHandleMap = itHandleMapMap->second;
    }
  }
  else
  {
    itHandleMapMap = federateSentInteractionReliableCounts.find(theFederate);
    if (itHandleMapMap != federateSentInteractionReliableCounts.end())
    {
      theHandleMap = itHandleMapMap->second;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getInteractionsSentCount(GeRtiFactory::GeRtiHandle const &theFederate, char *theBuff, bool const &theBestEffort)
{
  GERTICO::HandleMap::iterator itHandleMap;
  GERTICO::HandleMapMap::iterator itHandleMapMap;
  size_t len;
  long l;
  long l1;

  theBuff[0] = '\0';
  if (theBestEffort)
  {
    itHandleMapMap = federateSentInteractionBestEffortCounts.find(theFederate);
    if (itHandleMapMap != federateSentInteractionBestEffortCounts.end())
    {
      for (itHandleMap = itHandleMapMap->second.begin(); itHandleMap != itHandleMapMap->second.end(); itHandleMap++)
      {
        len = strlen(theBuff);
        l = itHandleMap->first;
        l1 = itHandleMap->second;
        if (len)
        {
          sprintf(&theBuff[len], ",%ld/%ld", l, l1);
        }
        else
        {
          sprintf(&theBuff[len], "%ld/%ld", l, l1);
        }
      }
    }
  }
  else
  {
    itHandleMapMap = federateSentInteractionReliableCounts.find(theFederate);
    if (itHandleMapMap != federateSentInteractionReliableCounts.end())
    {
      for (itHandleMap = itHandleMapMap->second.begin(); itHandleMap != itHandleMapMap->second.end(); itHandleMap++)
      {
        len = strlen(theBuff);
        l = itHandleMap->first;
        l1 = itHandleMap->second;
        if (len)
        {
          sprintf(&theBuff[len], ",%ld/%ld", l, l1);
        }
        else
        {
          sprintf(&theBuff[len], "%ld/%ld", l, l1);
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getMinTimeStamp(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
  GERTICO::FedEventSenderMap::iterator itFedEventSender;
  std::auto_ptr<GERTICO::GeRtiFedTime> fedFedTime(geRtiFedTimeFactory.makeZero());

  pmFed.acquire();
  fedFedTime->setPositiveInfinity();
  itFedEventSender = fedEventSenders.find(theFederate);
  if (itFedEventSender != fedEventSenders.end())
  {
    itFedEventSender->second->getMinTimeStamp(*fedFedTime);
  }
  pmFed.release();

  theGeRtiFedTime = *fedFedTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getUpdatesSentCounts(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleMap &theHandleMap, bool const &theBestEffort)
{
  GERTICO::HandleMapMap::iterator itHandleMapMap;

  // Clean out map.
  theHandleMap.clear();

  if (theBestEffort)
  {
    itHandleMapMap = federateSentUpdateBestEffortCounts.find(theFederate);
    if (itHandleMapMap != federateSentUpdateBestEffortCounts.end())
    {
      theHandleMap = itHandleMapMap->second;
    }
  }
  else
  {
    itHandleMapMap = federateSentUpdateReliableCounts.find(theFederate);
    if (itHandleMapMap != federateSentUpdateReliableCounts.end())
    {
      theHandleMap = itHandleMapMap->second;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::getUpdatesSentCounts(GeRtiFactory::GeRtiHandle const &theFederate, char *theBuff, bool const &theBestEffort)
{
  GERTICO::HandleMap::iterator itHandleMap;
  GERTICO::HandleMapMap::iterator itHandleMapMap;
  size_t len;
  long l;
  long l1;

  theBuff[0] = '\0';
  if (theBestEffort)
  {
    itHandleMapMap = federateSentUpdateBestEffortCounts.find(theFederate);
    if (itHandleMapMap != federateSentUpdateBestEffortCounts.end())
    {
      for (itHandleMap = itHandleMapMap->second.begin(); itHandleMap != itHandleMapMap->second.end(); itHandleMap++)
      {
        len = strlen(theBuff);
        l = itHandleMap->first;
        l1 = itHandleMap->second;
        if (len)
        {
          sprintf(&theBuff[len], ",%ld/%ld", l, l1);
        }
        else
        {
          sprintf(&theBuff[len], "%ld/%ld", l, l1);
        }
      }
    }
  }
  else
  {
    itHandleMapMap = federateSentUpdateReliableCounts.find(theFederate);
    if (itHandleMapMap != federateSentUpdateReliableCounts.end())
    {
      for (itHandleMap = itHandleMapMap->second.begin(); itHandleMap != itHandleMapMap->second.end(); itHandleMap++)
      {
        len = strlen(theBuff);
        l = itHandleMap->first;
        l1 = itHandleMap->second;
        if (len)
        {
          sprintf(&theBuff[len], ",%ld/%ld", l, l1);
        }
        else
        {
          sprintf(&theBuff[len], "%ld/%ld", l, l1);
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::makeEventHubChannels(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOAReceiver, std::wstring const &theEventHub, GeRtiFactory::HubEventChannelDataSeq const &theHubEventChannelDataSeq)
{
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_i, "EventHandler::makeEventHubChannels", "enter");
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  CORBA::ULong length;
  GERTICO::PeerSender *peerSender;
  GERTICO::PeerSenderMap::iterator itPeerSender;
  std::wstring wstr;

  length = theHubEventChannelDataSeq.length();
  timeService->numberOfHubs(length);
  for (i = 0; i < length; i++)
  {
    wstr = theHubEventChannelDataSeq[i].name;
    if (wstr == myEventHub)
    {
      continue;
    }
    pmPeer.acquire();
    itPeerSender = peerSenderMap.find(wstr);
    if (itPeerSender != peerSenderMap.end())
    {
      peerSender = itPeerSender->second;
      peerSenderMap.erase(itPeerSender);
      delete peerSender;
    }
    peerSender = new GERTICO::PeerSender(theGeRtiOrb, thePOAReceiver, theEventHub, theHubEventChannelDataSeq[i].eventChannelReference);
    peerSenderMap[wstr] = peerSender;
    pmPeer.release();
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_i, "EventHandler::makeEventHubChannels", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::peerTimeConstrainedEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime)
{
  GeRtiFactory::GertiTmEvent gertiTmEvent;

  gertiTmEvent.service = 16;
  GERTICO::ConvertTime::mapIt(gertiTmEvent.timestamp, theGaltGeRtiFedTime);
  gertiTmEvent.sourceId = theFederate;

  addTmPeerEvent(gertiTmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::peerTimeRegulationEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime)
{
  GeRtiFactory::GertiTmEvent gertiTmEvent;

  gertiTmEvent.service = 15;
  GERTICO::ConvertTime::mapIt(gertiTmEvent.timestamp, theGaltGeRtiFedTime);
  gertiTmEvent.sourceId = theFederate;

  addTmPeerEvent(gertiTmEvent);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::print(std::string const &theString)
{
  GERTICO::FedEventSender *curr;
  GERTICO::FedEventSenderMap::iterator it;

                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::print", theString.c_str());
                           #endif   // inserted by Gal converter
  pmFed.acquire();
  for (it = fedEventSenders.begin(); it != fedEventSenders.end(); it++)
  {
    curr = it->second;
    curr->print();
  }
  pmFed.release();
}

/*
  if (gertiPushEvent.reliableFlag)
  {
    b = true;
  }
  else
  {
    b = false;
  }
  for (ind = 0; ind < len; ind++)
  {
    eventHandler.addEvent(gertiPushEvent.e[ind], b, gertiPushEvent.sourceType);
  }
*/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::process(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::process", "enter");
                           #endif   // inserted by Gal converter
  if (ps.acquire() == -1)
  {
    // Do not have the semaphore: try again.
    ACE_OS::sleep(1);
    return;
  }
//  psEvents->acquire();
  // Clear first buffer.
  distributeEvents();
  processFedEvents();
  // Clear second buffer.
  distributeEvents();
  processFedEvents();
  ACE_Thread::yield();
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_EC_d, "EventHandler::process", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processFedEvents(void)
{
  GERTICO::FedEventSender *curr;
  GERTICO::FedEventSenderMap::iterator it;
  std::string s;

//  psEvents->release();
  s = "before";
//  print(s);
  pmFed.acquire();

  for (it = fedEventSenders.begin(); it != fedEventSenders.end(); it++)
  {
    curr = it->second;
    if (curr->isDeleted())
    {
      continue;
    }

//    pmFed.release();
    curr->processEvents();
//    pmFed.acquire();
  }
  pmFed.release();

  pmFed.acquire();
  for (it = fedEventSenders.begin(); it != fedEventSenders.end();)
  {
    curr = it->second;
    if (curr->isDeleted())
    {
      fedEventSenders.erase(it);
      delete curr;
      it = fedEventSenders.begin();
    }
    else
    {
      it++;
    }
  }
  pmFed.release();
  s = "after";
//  print(s);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processLocalEvents(void)
{
  CORBA::ULong indVector;
  GERTICO::RtiHubEventVector::iterator itGeRtiEventVector;
  GERTICO::RtiHubEvent *rtiHubEvent;

  if (psLocal->acquire() == -1)
  {
    // Do not have the semaphore: try again.
    ACE_OS::sleep(1);
    return;
  }

  pmLocal.acquire();

  if (firstESenderLocal)
  {
    indVector = 0;
  }
  else
  {
    indVector = 1;
  }

  for (itGeRtiEventVector = eVectorLocal[indVector].begin(); itGeRtiEventVector != eVectorLocal[indVector].end(); itGeRtiEventVector = eVectorLocal[indVector].begin())
  {
    rtiHubEvent = *itGeRtiEventVector;
    eVectorLocal[indVector].erase(itGeRtiEventVector);
    pmLocal.release();
    doHubEvent(*rtiHubEvent);
    delete rtiHubEvent;
    pmLocal.acquire();
  }

  // Mutex is being held!

  if (firstESenderLocal)
  {
    firstESenderLocal = false;
  }
  else
  {
    firstESenderLocal = true;
  }

  if (firstESenderLocal)
  {
    indVector = 0;
  }
  else
  {
    indVector = 1;
  }

  for (itGeRtiEventVector = eVectorLocal[indVector].begin(); itGeRtiEventVector != eVectorLocal[indVector].end(); itGeRtiEventVector = eVectorLocal[indVector].begin())
  {
    rtiHubEvent = *itGeRtiEventVector;
    eVectorLocal[indVector].erase(itGeRtiEventVector);
    pmLocal.release();
    doHubEvent(*rtiHubEvent);
    delete rtiHubEvent;
    pmLocal.acquire();
  }

  if (firstESenderLocal)
  {
    firstESenderLocal = false;
  }
  else
  {
    firstESenderLocal = true;
  }
  pmLocal.release();
  ACE_Thread::yield();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::removeFederate(GeRtiFactory::GeRtiHandle const &theFederate)
{
  GERTICO::FedEventSender *currFedEventSender;
  GERTICO::FedEventSenderMap::iterator it;

  pmFed.acquire();
  it = fedEventSenders.find(theFederate);
  if (it != fedEventSenders.end())
  {
    currFedEventSender = it->second;
//    fedEventSenders.erase(it);
//    delete currFedEventSender;
    currFedEventSender->setDeleted();
  }
  pmFed.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::requestRetraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theHandle)
{
  GERTICO::FedEventSender *currFedEventSender;
  GERTICO::FedEventSenderMap::iterator it;

  pmFed.acquire();
  for (it = fedEventSenders.begin(); it != fedEventSenders.end(); it++)
  {
    currFedEventSender = it->second;
    if (it->first == theFederate)
    {
      continue;
    }
    currFedEventSender->requestRetraction(theHandle);
  }
  pmFed.release();
  ps.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::sendFederateEvents(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::processPeerEvents(void)
{
  // Separate into seconds and milli-seconds.
  long l = (long) (GERTICOconfRef.transmissionWait_ms / 1000);
  long m = GERTICOconfRef.transmissionWait_ms - l * 1000;

  if (psPeer->acquire() == -1)
  {
    // Do not have the semaphore: try again.
    ACE_OS::sleep(1);
    return;
  }

  // Once a send has been made wait, wait the specified time
  // NB. second parameter in micro-seconds
  if (GERTICOconfRef.dataLength > 1)
  {
    ACE_OS::sleep(ACE_Time_Value(l, m * 1000));
  }

  // Clear first buffer.
  distributePeerEvents();
  // Clear second buffer.
  distributePeerEvents();
  ACE_Thread::yield();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::setMom(GERTICO::Mom *theMom)
{
  mom = theMom;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::subscribeInteractionClassWithRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions)
{
//  pm.acquire();
  declarationManagementEC->interactionHolder->subscribeInteractionClassWithRegions(theFederate, theInteraction, theRegions);
//  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::timeAdvanceGrant(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime)
{
  GERTICO::FedEventSender *currFedEventSender;
  GERTICO::FedEventSenderMap::iterator it;

  pmFed.acquire();
  it = fedEventSenders.find(theFederate);
  if (it != fedEventSenders.end())
  {
    currFedEventSender = it->second;
    currFedEventSender->timeAdvanceGrant(theGeRtiFedTime, theGaltGeRtiFedTime);
  }
  pmFed.release();
  ps.release();
  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::timeConstrainedEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
  GERTICO::FedEventSender *currFedEventSender;
  GERTICO::FedEventSenderMap::iterator it;

  pmFed.acquire();
  it = fedEventSenders.find(theFederate);
  if (it != fedEventSenders.end())
  {
    currFedEventSender = it->second;
    currFedEventSender->timeConstrainedEnabled(theGeRtiFedTime);
  }
  pmFed.release();
  ps.release();
  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler::timeRegulationEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
  GERTICO::FedEventSender *currFedEventSender;
  GERTICO::FedEventSenderMap::iterator it;

  pmFed.acquire();
  it = fedEventSenders.find(theFederate);
  if (it != fedEventSenders.end())
  {
    currFedEventSender = it->second;
    currFedEventSender->timeRegulationEnabled(theGeRtiFedTime);
  }
  pmFed.release();
  ps.release();
  return true;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler::unsubscribeInteractionClassWithRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions)
{
//  pm.acquire();
  declarationManagementEC->interactionHolder->unsubscribeInteractionClassWithRegions(theFederate, theInteraction, theRegions);
//  pm.release();
}
