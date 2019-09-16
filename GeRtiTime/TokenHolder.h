/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** TokenHolder.h
**
*******************************************************************************/

#ifndef TokenHolder_H_
#define TokenHolder_H_

#include <map>
#include <vector>

//#include "Util/XercesInclude.h"
#include "Util/HLAparseErrorHandler.h"

#include "idl/GeRtiFactoryS.h"
#include "Util/ConvertTime.h"
#include "Util/GeRtiTypes.h"

#include "TimeService.h"
#include "TimeServiceClient.h"

void *token_worker(void *arg);
void *watchDog(void *arg);

namespace GERTICO
{
  class QueryData
  {
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
  public:
    std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> actualLookahead;
    std::auto_ptr<GERTICO::GeRtiFedTime> galt;

    QueryData(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory);
    virtual ~QueryData(void);
  };

  class TimeData
  {
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;

  public:
    TimeData(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory);
    virtual ~TimeData(void);

    CORBA::ULong numberOfPeerHubsReply;
    std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> actualLookahead;
    std::auto_ptr<GERTICO::GeRtiFedTime> lbts;
    std::auto_ptr<GERTICO::GeRtiFedTime> logicalTime;
    std::auto_ptr<GERTICO::GeRtiFedTime> oldLogicalTime;
    std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> requestedLookahead;
    // Fictitious grant time during tar or tara.
    std::auto_ptr<GERTICO::GeRtiFedTime> timeIntermediateGrant;
    std::auto_ptr<GERTICO::GeRtiFedTime> timeRequested;
    GERTICO::TimeServiceFlag timeServiceFlag;
    bool firstEnableTimeRegulation;
    bool lbtsf;
    bool lbtsg;
    bool localFederate;
    bool timeAdvancingState;
    bool timeConstrained;
    bool timeConstrainedPending;
    bool timeConstrainedPendingHubAnswerPeer;
    bool timeConstrainedPendingHubReplies;
    bool timePastFlag;
    bool timeRegulation;
    bool timeRegulationPending;
    bool timeRegulationPendingHubAnswerPeer;
    bool timeRegulationPendingHubReplies;
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::QueryData *> QueryDataMap;
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::TimeData *> TimeDataMap;
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::GeRtiFedTime *> GeRtiFedTimeMap;

  class TokenHolder : public virtual TimeService
  {
    // General mutex to lock access to time data.
    ACE_Thread_Mutex pm;
    // Mutex to lock access to time galt data.
    ACE_Thread_Mutex pmQuery;
    CORBA::ULong numberOfPeerHubs;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
    GERTICO::HandleSet enableTimeConstrainedIds;
    GERTICO::HandleSet enableTimeRegulationIds;
    // Holds galt data.
    // Locked by pmQuery mutex.
    GERTICO::QueryDataMap queryDataMap;
    // All currently joined federates.
    GERTICO::TimeDataMap timeDataMap;
    // Last few resigned federates.
    GERTICO::TimeDataMap timeDataInactiveMap;
    TimeServiceClient &timeServiceClient;
    static std::string actualLookaheadStr;
    static std::string advancingStateStr;
    static std::string firstEnableTimeRegulationStr;
    static std::string flushQueueRequestFlagStr;
    static std::string idleFlagStr;
    static std::string idStr;
    static std::string lbtsStr;
    static std::string lbtsfStr;
    static std::string lbtsgStr;
    static std::string logicalTimeStr;
    static std::string lookaheadTimeStr;
    static std::string nextEventFlagStr;
    static std::string nextEventAvailableFlagStr;
    static std::string oldLogicalTimeStr;
    static std::string saveTimeStr;
    static std::string timeAdvanceFlagStr;
    static std::string timeAdvanceAvailableFlagStr;
    static std::string timeConstrainedStr;
    static std::string timeConstrainedPendingStr;
    static std::string timeFederateStr;
    static std::string timeFederatesStr;
    static std::string timePastFlagStr;
    static std::string timeRegulationStr;
    static std::string timeRegulationPendingStr;
    static std::string timeRequestedStr;
    static std::string timeServiceStr;
    static std::string timeValueStr;

    // NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
    void calcTokenValues(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData const &theTimeData, GERTICO::GeRtiFedTime &lbts, bool &lbtsg);
    // NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
    bool checkGrantCondition(GeRtiFactory::GeRtiHandle const theFederate, GERTICO::TimeData &theTimeData, GERTICO::GeRtiFedTime &theGrantTime);
    void clear(void);
    void flushCalc(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData const &timeData, GERTICO::GeRtiFedTimeMap &theAdvancers);
    // NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
    bool g1Condition(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &tg);
    // NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
    bool g2Condition(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &tg);
    void garbageCollection(void);
    void getActualLookahead(GERTICO::TimeData const &theTimeData, GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval);
    // NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
    void getMaxTimeConstrained(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theFedTime);
    void getQueryGaltParams(bool const &theFirstEnableTimeRegulation, GERTICO::TimeData const &theTimeData, GERTICO::GeRtiFedTime &theLbts, GERTICO::GeRtiFedTime &theMinLogicalTime, GERTICO::GeRtiLogicalTimeInterval &theMinLookahead, GERTICO::GeRtiFedTime &theMinAdvancingTime, GERTICO::GeRtiFedTime &theMinNotAdvancingTime, bool &theGuaranteedTime);
    void nextEventCalc(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData const &timeData, bool const &available, GERTICO::GeRtiFedTimeMap &theAdvancers);
    void nextEventRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime, bool const &avail);
    void print(void);
    void processGrant(void);
    void processTimeConstrained(void);
    void processTimeRegulation(void);
    void queryActualLookahead(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval &theTime);
    void queryGALTprivate(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime);
    void setActualLookahead(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData &theTimeData, GERTICO::GeRtiLogicalTimeInterval const &theGeRtiFedTimeInterval);
    void setLogicalTime(GERTICO::TimeData &theTimeData, GERTICO::GeRtiFedTime const &theGeRtiFedTime);
    void setTimeRequested(GERTICO::TimeData &theTimeData, GERTICO::GeRtiFedTime const &theFedTime);
    void subtractLookahead(GERTICO::TimeData const &theTimeData, GERTICO::GeRtiFedTime &theFedTime);
    void timeAdvanceCalc(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData const &timeData, bool const &available, GERTICO::GeRtiFedTimeMap &theAdvancers);
    void timeAdvanceGrant(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime);
    void timeAdvanceRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime, bool const &);
    void timeConstrainedEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData &theTimeData, GERTICO::GeRtiFedTime &theFedTime);
    void timeRegulationEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData &theTimeData, GERTICO::GeRtiFedTime &theFedTime);

  public:
    bool notDone;

    TokenHolder(TimeServiceClient &theTimeServiceClient, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory);
    virtual ~TokenHolder(void);

    void disableTimeConstrained(GeRtiFactory::GeRtiHandle const &theFederate);
    void disableTimeRegulation(GeRtiFactory::GeRtiHandle const &theFederate);
    void enableTimeConstrained(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theSourceType);
#ifdef IEEE_1516
    void enableTimeRegulation(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval &theLookahead, GeRtiFactory::GeRtiHandle const &theSourceType);
#else
    void enableTimeRegulation(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &theFederateTime, GERTICO::GeRtiLogicalTimeInterval &theLookahead, GeRtiFactory::GeRtiHandle const &theSourceType);
#endif
    void flushQueueRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime);
    void joinFederationExecution(GeRtiFactory::GeRtiHandle const &theFederate);
    void modifyLookahead(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval &theGeRtiFedTime)
         throw(GeRtiFactory::TimeAdvanceAlreadyInProgress,
               GeRtiFactory::InvalidLookahead);
    void nextEventRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime);
    void nextEventRequestAvailable(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime);
    void numberOfHubs(CORBA::ULong const &theNumberOfHubs);
    void process(void);
    void queryGALT(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime);
    void queryLITS(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime);
    void queryLogicalTime(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime);
    void queryLookahead(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval& theTime);
    void reset(void);
    void resignFederationExecution(GeRtiFactory::GeRtiHandle const &theFederate);
    void restore(DOMElement &theDOMElement);
    void retract(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theHandle);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    void terminate(void);
    void timeAdvanceRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime);
    void timeAdvanceRequestAvailable(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime);
    void timeConstrainedPeerEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theTime);
    void timeRegulationPeerEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theTime);
  };
};

#endif /* TokenHolder_H_  */
