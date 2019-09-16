/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** TimeManagementLRC.h
**
*******************************************************************************/

#ifndef TimeManagementLRC_H_
#define TimeManagementLRC_H_

#include "ace/Synch.h"
#include "idl/GeRtiFactoryS.h"
#include "LRC/EventMarket.h"
#include "Util/ConvertTime.h"
#include "Util/GeRtiFedTime.h"
#include "Util/XercesInclude.h"
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include "Util/PrintErrorHandler.h"
#include "Util/PrintFilter.h"

namespace GERTICO
{
  class TimeManagementLRC
  {
    ACE_Thread_Mutex pm;
    std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> myRequestedLookahead;
    TimeServiceFlag timeServiceFlag;
    GeRtiFactory::GeRtiAmbassador_var GeRtiAmbVar;
    const GeRtiFactory::GeRtiHandle &federate;
    GeRtiFactory::TimeManagement_var timeManagementVar;
    bool lookaheadChanging;
    bool timeAdvancing;
    bool timeConstrained;
    bool timeConstrainedPending;
    bool timePastFlag;
    bool timeRegulation;
    bool timeRegulationPending;
    static std::string actualLookaheadStr;
    static std::string flushQueueRequestFlagStr;
    static std::string idleFlagStr;
    static std::string logicalTimeStr;
    static std::string nextEventFlagStr;
    static std::string nextEventAvailableFlagStr;
    static std::string requestedLookaheadStr;
    static std::string timeAdvanceFlagStr;
    static std::string timeAdvanceAvailableFlagStr;
    static std::string timeAdvancingStr;
    static std::string timeConstrainedStr;
    static std::string timeConstrainedPendingStr;
    static std::string timeFlagStr;
    static std::string timePastFlagStr;
    static std::string timeRequestedStr;
    static std::string timeRegulationStr;
    static std::string timeRegulationPendingStr;
    static std::string timeServiceStr;
    static std::string timeTagStr;

    void checkAdvanceValues(CORBA::WChar *theWChar, GERTICO::GeRtiFedTime const &theGeRtiFedTime);
  public:
    GERTICO::EventMarket *eventMarket;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
    std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> myActualLookahead;
    std::auto_ptr<GERTICO::GeRtiFedTime> myLogicalTime;
    std::auto_ptr<GERTICO::GeRtiFedTime> myTimeRequested;
    std::auto_ptr<GERTICO::GeRtiFedTime> myTimeSave;
    std::auto_ptr<GERTICO::GeRtiFedTime> myTimeTag;
    // Only valid when advancing TAR or TARA.
    std::auto_ptr<GERTICO::GeRtiFedTime> myTimeTarGalt;
    bool gotAnnounceFederateSaveWithTime;
    bool gotTimeAdvanceGrant;
    bool gotTimeAdvanceGrantIntermediate;

    //Constructor
    TimeManagementLRC(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, GeRtiFactory::TimeManagement_ptr theTimeManagement_ptr);

    //Destructor
    virtual ~TimeManagementLRC(void);

    // Called from gerti
    void addTimeAdvanceGrant(GERTICO::GeRtiFedTime const &theFedTime);
    // Called from gerti
    void addTimeAdvanceGrantGalt(GERTICO::GeRtiFedTime const &theFedTime, GERTICO::GeRtiFedTime const &theGaltFedTime);
    // Called from gerti
    void addTimeAdvanceGrantIntermediate(GERTICO::GeRtiFedTime const &theFedTime);
    void clear(void);
    void disableTimeConstrained(void);
    void disableTimeRegulation(void);
    void enableTimeConstrained(void);
#ifdef IEEE_1516
    void enableTimeRegulation(GERTICO::GeRtiLogicalTimeInterval const &theLookahead);
#else
    void enableTimeRegulation(GERTICO::GeRtiFedTime const &theFederateTime, GERTICO::GeRtiLogicalTimeInterval const &theLookahead);
#endif
    void flushQueueRequest(GERTICO::GeRtiFedTime const &theGeRtiFedTime);
    bool isTimeConstrained(void);
    bool isTimeAdvancing(void);
    bool isTimeRegulation(void);
    void modifyLookahead(GERTICO::GeRtiLogicalTimeInterval const &theLogicalTimeInterval);
    void nextEventRequest(GERTICO::GeRtiFedTime const &theGeRtiFedTime, bool const &theBool);
    void queryGALT(GERTICO::GeRtiFedTime& theTime);
    void queryLITS(GERTICO::GeRtiFedTime& theTime);
    void queryLogicalTime(GERTICO::GeRtiFedTime& theTime);
    void queryLookahead(GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval);
    void restore(DOMElement &theDOMElement);
    void retract(GeRtiFactory::ERHandle const &theERHandle);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
    void setGeRtiAmbassador(GeRtiFactory::GeRtiAmbassador_var theGeRtiAmbassador_var);
    void testRequestTime(GERTICO::GeRtiFedTime const &theGeRtiFedTime);
    void testSendTime(GERTICO::GeRtiFedTime const &theGeRtiFedTime);
    void timeAdvanceGrant(void);
    void timeAdvanceRequest(GERTICO::GeRtiFedTime const &theGeRtiFedTime, bool const &theBool);
    void timeConstrainedEnabled(GERTICO::GeRtiFedTime const &theGeRtiFedTime);
    void timeRegulationEnabled(GERTICO::GeRtiFedTime const &theGeRtiFedTime);
  };
} // namespace
#endif /* TimeManagementLRC_H_  */
