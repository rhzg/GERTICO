/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** FedEventSender.h
**
*******************************************************************************/

#ifndef FedEventSender_H_
#define FedEventSender_H_

#include <map>

#include "GeRti/Mom.h"
#include "GeRtiTime/TimeManagementI.h"
#include "GeRtiTime/TimeService.h"
#include "GeRtiTime/TimeServiceFacI.h"
#include "Util/ConvertTime.h"
#include "Util/DataModel.h"
#include "Util/Federate.h"
#include "Util/GERTICOconf.h"
#include "Util/GeRtiFedTime.h"
#include "Util/Subscriber.h"

#include "GeRtiEventMarketISend.h"

#include "ace/Synch.h"

struct cmpGeRtiTime
{
  bool operator()(const GERTICO::GeRtiFedTime *s1, const GERTICO::GeRtiFedTime *s2) const
  {
    bool b = *s1 < *s2;

    return b;
  }
};

namespace GERTICO
{
  typedef std::vector <GERTICO::GeRtiFedTime *> GeRtiTimeVector;

  typedef std::map <GERTICO::GeRtiFedTime *, unsigned int, cmpGeRtiTime> GeRtiTimeMap;

  class RtiHubEvent
  {
  public:
    RtiHubEvent(GeRtiFactory::GeRtiHandle const &theSourceType);
    virtual ~RtiHubEvent(void);

    GeRtiFactory::GeRtiHandle sourceType;
    GeRtiFactory::PushEvent *pushEvent;
  };

  typedef std::vector <GERTICO::RtiHubEvent *> RtiHubEventVector;
  typedef std::vector <GeRtiFactory::GertiPushEvent *> GeRtiPushEventVector;

  class Interaction
  {
    GeRtiFactory::GeRtiHandle myInteractionId;
    // Key is federate.
    SubscriberMap fedInteractionSubscribers;

    static std::string federateStr;
    static std::string publisherStr;
    static std::string publishersStr;
    static std::string subscriberStr;
    static std::string subscribersStr;

  public:
    Interaction(GeRtiFactory::GeRtiHandle const &theInteraction);
    virtual ~Interaction(void);

    void addSubInteraction(GeRtiFactory::GeRtiHandle const &theFederate, CORBA::Boolean const &theActive, GeRtiFactory::GeRtiHandle const &theRegion);
    bool checkActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate);
    bool checkSubscriber(GeRtiFactory::GeRtiHandle const &theFederate);
    void delSubInteraction(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::GeRtiHandle const &);
    void delSubscribedRegions(GeRtiFactory::GeRtiHandle const &theFederate);
    void getActiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theSubscribers);
    void getPassiveSubscribers(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleSet &theSubscribers);
    GeRtiFactory::GeRtiHandle getId(void);
    void getFederateRegions(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::HandleBoolMap &theRegions);
    bool isEmpty(void);
    bool isRegionSubscribed(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theRegion);
    void restore(DOMElement &theDOMElement, GERTICO::HandleBoolMap &theFedInteractionRelevanceAdvisorySwitchMap);
    void save(DOMDocument &, DOMElement &);
  };

  // Key is Interaction class, second interaction information.
  typedef std::map <GeRtiFactory::GeRtiHandle, Interaction *> InteractionMap;

  class FedEventSender
  {
    ACE_Semaphore &ps;
    ACE_Thread_Mutex pm;
    GeRtiEventMarket_ProxyPushSupplier_i *proxyPushSupplierReliable;
    GeRtiEventMarket_ProxyPushSupplier_i *proxyPushSupplierBestEffort;
    // Reliable events.
    GERTICO::RtiHubEventVector eVector[2];
    //  GeRtiFactory::Events e[2];
    // Best-Effort (corba oneway) events.
    GERTICO::RtiHubEventVector eVectorBestEffort[2];
    GeRtiFactory::GeRtiHandle federate;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::InteractionMap &interactionMap;
    const GERTICOconf &GERTICOconfRef;
    // For each federate, a list of time stamps is kept.
    // For each time stamp, the count of events for this time stamp within gerti
    // is kept. As each event leaves gerti the count is reduced.
    // The time stamps are kept until the count of messages for this time stamp
    // is zero and a TAG with a time greater than the time stamp for this federate
    // is received.
    GeRtiTimeMap times;
    bool deleted;
    bool firstESender;
    bool haveOverload;

    // Add new events to existing events.
    void addTime(GeRtiFactory::Time const &theTime);
    void checkOverload(void);
    void delMinTimeStamp(GERTICO::GeRtiFedTime const &theGeRtiFedTime);
    CORBA::ULong fillEvent(GeRtiFactory::PushEvent &theGeRtiEventOut, GeRtiFactory::GeRtiEvent const &theGeRtiEvent, GERTICO::HandleSet &theDesiredAttributes);
    void getFederateRegions(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theInteraction, GERTICO::HandleBoolMap &theRegions);

    // Get pointer to current events to send.
    GERTICO::RtiHubEventVector *f_getEvents(bool const &isSender, bool const &theReliable);
    void printTimeStamp(void);
    // Send the events.
    void sendEvents(GERTICO::RtiHubEventVector &theGeRtiEventVector, bool const &theReliable);
    // Change the firstESender value.
    void toggleFirstESender(void);

    bool wantAttribute(CORBA::ULong const &theEventAttribute, GERTICO::HandleSet const &theSubscriberAttributes);

  public:
    FedEventSender(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::InteractionMap &theInteractionMap, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, ACE_Semaphore &thePs);
    ~FedEventSender(void);

    void addDmEvent(GeRtiFactory::GertiDmEvent const &event);
    // Add new events to existing subscribers.
    void addEvent(GeRtiFactory::GeRtiEvent const &theGeRtiEvent, GeRtiFactory::GeRtiHandle const &theSourceType, GERTICO::HandleSet &theDesiredAttributes);
    void addProxyPushSupplier(GeRtiEventMarket_ProxyPushSupplier_i *pps, bool const &theReliableFlag);
    void addTmEvent(GeRtiFactory::GertiTmEvent const &theGertiTmEvent);
    void clear(void);
    void getMinTimeStamp(GERTICO::GeRtiFedTime &theGeRtiFedTime);
    bool isDeleted(void);
    void processEvents(void);
    void print(void);
    void requestRetraction(GeRtiFactory::GeRtiHandle const &theHandle);
    void setDeleted(void);
    void timeAdvanceGrant(GERTICO::GeRtiFedTime &theGeRtiFedTime, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime);
    void timeConstrainedEnabled(GERTICO::GeRtiFedTime const &theGeRtiFedTime);
    void timeRegulationEnabled(GERTICO::GeRtiFedTime const &theGeRtiFedTime);
  };

  // Key is federate.
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::FedEventSender *> FedEventSenderMap;
};

#endif /* FedEventSender_H_  */
