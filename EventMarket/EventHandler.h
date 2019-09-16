/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** EventHandler.h
**
*******************************************************************************/

#ifndef EventHandler_H_
#define EventHandler_H_

#include <map>

#include "DeclarationManagementEC.h"
#include "SupportingServicesEC.h"
#include "GeRti/Mom.h"
#include "GeRtiTime/TimeManagementI.h"
#include "GeRtiTime/TimeService.h"
#include "GeRtiTime/TimeServiceFacI.h"
#include "Util/ConvertTime.h"
#include "Util/DataModel.h"
#include "Util/GERTICOconf.h"
#include "Util/GeRtiFedTime.h"
#include "Util/RunTimeObjectDB.h"

//#include "GeRtiEventMarketI.h"

#include "ace/Synch.h"

namespace GERTICO
{
  class PeerSender
  {
    CORBA::ULong lengthBestEffort;
    CORBA::ULong lengthReliable;
    GeRtiEventMarket_ProxyPushSupplier_i *proxyPushSupplierBestEffort;
    GeRtiEventMarket_ProxyPushSupplier_i *proxyPushSupplierReliable;
    GeRtiFactory::GertiPushEvent gertiPushEventBestEffort;
    GeRtiFactory::GertiPushEvent gertiPushEventReliable;

  public:
    PeerSender(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, std::wstring const &theEventHub, GeRtiFactory::EventChannel_ptr const theEventChannelPtr);
    ~PeerSender(void);

    void addEvent(GeRtiFactory::PushEvent const &e, bool const &reliable, bool const &theSendNow);
  };

  // Key is hub name.
  typedef std::map <std::wstring, GERTICO::PeerSender *> PeerSenderMap;

  class EventHandler
  {
    ACE_Semaphore *psLocal;
    ACE_Semaphore *psPeer;
    ACE_Thread_Mutex pm;
    ACE_Thread_Mutex pmFed;
    ACE_Thread_Mutex pmLocal;
    ACE_Thread_Mutex pmPeer;

    // Declaration Management
    GERTICO::DeclarationManagementEC *declarationManagementEC;
    // Map: key federate handle.
    GERTICO::FedEventSenderMap fedEventSenders;
    GERTICO::FedEventSenderMap fedEventSendersDead;
    // Local events.
    GERTICO::RtiHubEventVector eVectorLocal[2];
    // Best-Effort (corba oneway) events.
    GERTICO::GeRtiPushEventVector eVectorBestEffort[2];
    // Reliable events.
    GERTICO::RtiHubEventVector eVectorPeerReliable[2];
    // Best-Effort (corba oneway) events.
    GERTICO::RtiHubEventVector eVectorPeerBestEffort[2];
    // Reliable events.
    GERTICO::GeRtiPushEventVector eVectorReliable[2];
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
    // Map::key federate handle.
    GERTICO::HandleMapMap federateSentInteractionBestEffortCounts;
    GERTICO::HandleMapMap federateSentInteractionReliableCounts;
    GERTICO::HandleMapMap federateSentUpdateBestEffortCounts;
    GERTICO::HandleMapMap federateSentUpdateReliableCounts;
    GERTICO::InteractionMap interactionMap;
    GERTICO::Mom *mom;
    GERTICO::PeerSenderMap peerSenderMap;
    // Supporting Services
    GERTICO::SupportingServicesEC *supportingServicesEC;
    bool firstESender;
    bool firstESenderLocal;
    bool firstESenderPeer;
    bool immediateSend;
    unsigned long desiredDataLength;

    const GERTICOconf &GERTICOconfRef;
    const GeRtiFactory::GeRtiHandle &privilegeToDeleteId;
    const std::wstring &myEventHub;

    void addTmPeerEvent(GeRtiFactory::GertiTmEvent const &theGertiTmEvent);
    void distributeEvents(void);
    void distributePeerEvents(void);
    void doDm(GeRtiFactory::GertiDmEvent const &theGertiDmEvent);
    void doFm(GeRtiFactory::GertiFmEvent const &theGertiFmEvent);
    void doHubEvent(GERTICO::RtiHubEvent const &theRtiHubEvent);
    void doTm(GeRtiFactory::GertiTmEvent const &theGertiTmEvent, GeRtiFactory::GeRtiHandle const &theSourceType);
    void addHandleMapMap(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleMapMap &theHandleMapMap);
    void getEventAttributes(GeRtiFactory::GeRtiEvent const &theGeRtiEvent, GERTICO::HandleSet &theEventAttributes);
    void getEventLength(CORBA::ULong &theLength, GeRtiFactory::PushEvent &thePushEvent);
    void getEventsLength(CORBA::ULong &theLength, GeRtiFactory::GertiPushEvent &theGertiPushEvent);
    void print(std::string const &theString);
    void processFedEvents(void);

  public:
    ACE_Semaphore &ps;
    GERTICO::TimeService *timeService;
    GERTICO::TimeServiceFac *timeServiceFac;
    bool notDone;

    EventHandler(ACE_Semaphore &thePs, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId, std::wstring const &theEventHub);
    virtual ~EventHandler(void);

    void addEvent(GeRtiFactory::GertiPushEvent const &e);
    void addEvent(GeRtiFactory::PushEvent const &e, bool const &theReliableFlag, GeRtiFactory::GeRtiHandle const &theSourceType);
    void addProxyPushSupplier(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiEventMarket_ProxyPushSupplier_i *pps, bool const &theReliableFlag);
    void clear(void);
    void clearFederates(void);
    void doSentCounts(GeRtiFactory::PushEvent const &thePushEvent);
    void findReceivingFederates(GERTICO::HandleSet &theFederates, GeRtiFactory::PushEvent &thePushEvent);
    void getInteractionsSentCount(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleMap &theHandleMap, bool const &theBestEffort);
    void getInteractionsSentCount(GeRtiFactory::GeRtiHandle const &theFederate, char *theBuff, bool const &theBestEffort);
    void getMinTimeStamp(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime);
    void getUpdatesSentCounts(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleMap &theHandleMap, bool const &theBestEffort);
    void getUpdatesSentCounts(GeRtiFactory::GeRtiHandle const &theFederate, char *theBuff, bool const &theBestEffort);
    void makeEventHubChannels(GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOA, std::wstring const &theEventHub, GeRtiFactory::HubEventChannelDataSeq const &theHubEventChannelDataSeq);
    void peerTimeConstrainedEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime);
    void peerTimeRegulationEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime);
    void process(void);
    void processLocalEvents(void);
    void processPeerEvents(void);
    void removeFederate(GeRtiFactory::GeRtiHandle const &theFederate);
    void requestRetraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theHandle);
    void sendFederateEvents(void);
    void setMom(GERTICO::Mom *theMom);
    void subscribeInteractionClassWithRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions);
    // Time management
    bool timeAdvanceGrant(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime);
    bool timeConstrainedEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &theGeRtiFedTime);
    bool timeRegulationEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &theGeRtiFedTime);

    void unsubscribeInteractionClassWithRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleSet const &theRegions);
  };
};

#endif /* EventHandler_H_  */
