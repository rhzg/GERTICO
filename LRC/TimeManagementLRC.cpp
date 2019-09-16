/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** TimeManagementLRC.cpp
**
*******************************************************************************/

#include "LRC/TimeManagementLRC.h"
#include "iostream"

// insert Gal file .init here
/********************************* Gal begin *********************************/   // inserted by Gal converter
   // inserted by Gal converter
// Version: 1.1   // inserted by Gal converter
// Date/Time: Wed May 21 10:11:21 2003   // inserted by Gal converter
   // inserted by Gal converter
#ifdef GalDebug   // inserted by Gal converter
#include "Gal/StdAfx.h"   // inserted by Gal converter
#include "Gal/repository_l.h"   // inserted by Gal converter
#include "Gal/event.h"   // inserted by Gal converter

#define MAX_TXT 1024

static class Repository_l *TM=(Repository::getSingleInstance())->getRepository_l("GeRtiTM.res","GeRtiTM");

static class Event *GeRti_TM_d=TM->getRefEvent("GeRti_TM_d");
static class Event *GeRti_TM_e=TM->getRefEvent("GeRti_TM_e");
static class Event *GeRti_TM_i=TM->getRefEvent("GeRti_TM_i");
static class Event *GeRti_TM_w=TM->getRefEvent("GeRti_TM_w");
static class Event *GeRti_TM_mu_d=TM->getRefEvent("GeRti_TM_mu_d");

static char galMsg[MAX_TXT];

#endif   // inserted by Gal converter
/*********************************** Gal end *********************************/   // inserted by Gal converter

std::string GERTICO::TimeManagementLRC::actualLookaheadStr("actualLookahead");
std::string GERTICO::TimeManagementLRC::flushQueueRequestFlagStr("flushQueueRequestFlag");
std::string GERTICO::TimeManagementLRC::idleFlagStr("idleFlag");
std::string GERTICO::TimeManagementLRC::logicalTimeStr("logicalTime");
std::string GERTICO::TimeManagementLRC::nextEventFlagStr("nextEventFlag");
std::string GERTICO::TimeManagementLRC::nextEventAvailableFlagStr("nextEventAvailableFlag");
std::string GERTICO::TimeManagementLRC::requestedLookaheadStr("requestedLookahead");
std::string GERTICO::TimeManagementLRC::timeAdvanceFlagStr("timeAdvanceFlag");
std::string GERTICO::TimeManagementLRC::timeAdvanceAvailableFlagStr("timeAdvanceAvailableFlag");
std::string GERTICO::TimeManagementLRC::timeAdvancingStr("timeAdvancing");
std::string GERTICO::TimeManagementLRC::timeConstrainedStr("timeConstrained");
std::string GERTICO::TimeManagementLRC::timeConstrainedPendingStr("timeConstrainedPending");
std::string GERTICO::TimeManagementLRC::timeFlagStr("timeFlag");
std::string GERTICO::TimeManagementLRC::timePastFlagStr("timePastFlag");
std::string GERTICO::TimeManagementLRC::timeRequestedStr("timeRequested");
std::string GERTICO::TimeManagementLRC::timeRegulationStr("timeRegulation");
std::string GERTICO::TimeManagementLRC::timeRegulationPendingStr("timeRegulationPending");
std::string GERTICO::TimeManagementLRC::timeServiceStr("timeService");
std::string GERTICO::TimeManagementLRC::timeTagStr("timeTag");

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TimeManagementLRC::TimeManagementLRC(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, GeRtiFactory::TimeManagement_ptr theTimeManagementPtr) : federate(theFederate), geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TimeManagementLRC", "enter");
                           #endif   // inserted by Gal converter
  clear();
  timeManagementVar = GeRtiFactory::TimeManagement::_duplicate(theTimeManagementPtr);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TimeManagementLRC", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TimeManagementLRC::~TimeManagementLRC()
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "~TimeManagementLRC", "EnterLeave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Called from gerti
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::addTimeAdvanceGrant(GERTICO::GeRtiFedTime const &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "addTimeAdvanceGrant", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  *myTimeTag = theFedTime;
  *myTimeTarGalt = theFedTime;
  gotTimeAdvanceGrant = true;
  gotTimeAdvanceGrantIntermediate = false;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "addTimeAdvanceGrant", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Called from gerti
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::addTimeAdvanceGrantGalt(GERTICO::GeRtiFedTime const &theFedTime, GERTICO::GeRtiFedTime const &theGaltFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "addTimeAdvanceGrantGalt", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  char buff[1024];
  char cuff[1024];
  *myTimeTag = theFedTime;
  myTimeTag->getPrintableString(buff);
  *myTimeTarGalt = theGaltFedTime;
  myTimeTarGalt->getPrintableString(cuff);
  gotTimeAdvanceGrant = true;
  gotTimeAdvanceGrantIntermediate = true;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "addTimeAdvanceGrantGalt", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Called from gerti
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::addTimeAdvanceGrantIntermediate(GERTICO::GeRtiFedTime const &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "addTimeAdvanceGrantIntermediate", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  char buff[1024];
  *myTimeTarGalt = theFedTime;
  myTimeTarGalt->getPrintableString(buff);
  gotTimeAdvanceGrant = false;
  gotTimeAdvanceGrantIntermediate = true;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "addTimeAdvanceGrantIntermediate", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::TimeManagementLRC::isTimeConstrained()
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_d)
                            {
                              if (timeConstrained)
                              {
                                strcpy(galMsg,"true");
                              }
                              else
                              {
                                strcpy(galMsg,"false");
                              }
                              E2(GeRti_TM_d, "isTimeConstrained", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return timeConstrained;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::checkAdvanceValues(CORBA::WChar *theWChar, GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
  // HLA check
  if (timeAdvancing)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "checkAdvanceValues", "TimeAdvanceAlreadyInProgress");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeAdvanceAlreadyInProgress(theWChar);
  }

  // HLA check
  if (timeRegulationPending)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "checkAdvanceValues", "EnableTimeRegulationPending");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::EnableTimeRegulationPending(theWChar);
  }

  // HLA check
  if (timeConstrainedPending)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "checkAdvanceValues", "EnableTimeConstrainedPending");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::EnableTimeConstrainedPending(theWChar);
  }

  if (theGeRtiFedTime < *myLogicalTime)
  {
#ifdef IEEE_1516
    throw GeRtiFactory::InvalidFederationTime(theWChar);
#else
    throw GeRtiFactory::FederationTimeAlreadyPassed(theWChar);
#endif
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::clear(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "clear", "enter");
                           #endif   // inserted by Gal converter
  timeServiceFlag = idleFlag;

  gotAnnounceFederateSaveWithTime = false;
  gotTimeAdvanceGrant = false;
  gotTimeAdvanceGrantIntermediate = false;
  lookaheadChanging = false;
  timeAdvancing = false;
  timeConstrained = false;
  timeConstrainedPending = false;
  timePastFlag = false;
  timeRegulation = false;
  timeRegulationPending = false;

  myActualLookahead.reset(geRtiLogicalTimeIntervalFactory.makeZero());
  myLogicalTime.reset(geRtiFedTimeFactory.makeZero());
  myRequestedLookahead.reset(geRtiLogicalTimeIntervalFactory.makeZero());
  myTimeRequested.reset(geRtiFedTimeFactory.makeZero());
  myTimeTag.reset(geRtiFedTimeFactory.makeZero());
  myTimeTarGalt.reset(geRtiFedTimeFactory.makeZero());
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "clear", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::disableTimeConstrained(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "disableTimeConstrained", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"disableTimeConstrained";

  // HLA check
  if (timeConstrained == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "disableTimeConstrained", "TimeConstrainedWasNotEnabled");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeConstrainedWasNotEnabled(wChar);
  }
  timeConstrained = false;

  timeManagementVar->disableTimeConstrained(federate);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "disableTimeConstrained", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::disableTimeRegulation(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "disableTimeRegulation", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"disableTimeRegulation";

  // HLA check
  if (timeRegulation == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "disableTimeRegulation", "TimeRegulationWasNotEnabled");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeRegulationWasNotEnabled(wChar);
  }
  timeRegulation = false;

  timeManagementVar->disableTimeRegulation(federate);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "disableTimeRegulation", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::enableTimeConstrained(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "enableTimeConstrained", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"enableTimeConstrained";
  GeRtiFactory::GertiTmEvent gertiTmEvent;

  // HLA check
  if (timeConstrained)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "enableTimeConstrained", "TimeConstrainedAlreadyEnabled");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeConstrainedAlreadyEnabled(wChar);
  }

  // HLA check
  if (timeConstrainedPending)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "enableTimeConstrained", "EnableTimeConstrainedPending");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::EnableTimeConstrainedPending(wChar);
  }

  // HLA check
  if (timeAdvancing)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "enableTimeConstrained", "TimeAdvanceAlreadyInProgress");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeAdvanceAlreadyInProgress(wChar);
  }

  gertiTmEvent.service = 3;
  gertiTmEvent.sourceId = federate;
  eventMarket->addTmEvent(gertiTmEvent);
//  GeRtiAmbVar->enableTimeConstrained();

  timeConstrainedPending = true;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "enableTimeConstrained", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
#ifdef IEEE_1516
void GERTICO::TimeManagementLRC::enableTimeRegulation(GERTICO::GeRtiLogicalTimeInterval const &theLookahead)
#else
void GERTICO::TimeManagementLRC::enableTimeRegulation(GERTICO::GeRtiFedTime const &theFederateTime, GERTICO::GeRtiLogicalTimeInterval const &theLookahead)
#endif
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "enableTimeRegulation", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"enableTimeRegulation";
  GeRtiFactory::GertiTmEvent gertiTmEvent;
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> zeroTime(geRtiLogicalTimeIntervalFactory.makeZero());

  // HLA check
  if (timeRegulation)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "enableTimeRegulation", "TimeRegulationAlreadyEnabled");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeRegulationAlreadyEnabled(wChar);
  }

  // HLA check
  if (timeRegulationPending)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "enableTimeRegulation", "EnableTimeRegulationPending");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::EnableTimeRegulationPending(wChar);
  }

  // HLA check
  if (timeAdvancing)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "enableTimeRegulation", "TimeAdvanceAlreadyInProgress");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeAdvanceAlreadyInProgress(wChar);
  }

#ifndef IEEE_1516
  if (timeConstrained)
  {
    if (!(theFederateTime == *myLogicalTime))
    {
      pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = federate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      throw GeRtiFactory::InvalidFederationTime(wChar);
    }
  }
#endif

#ifndef IEEE_1516
  if (theFederateTime < *myLogicalTime)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "enableTimeRegulation", "InvalidFederationTime");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::InvalidFederationTime(wChar);
  }
#endif

  if (theLookahead < *zeroTime)
  {
    throw GeRtiFactory::InvalidLookahead(wChar);
  }

  gertiTmEvent.service = 0;
  GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(gertiTmEvent.timestampTwo, theLookahead);
  gertiTmEvent.sourceId = federate;

#ifdef IEEE_1516
  eventMarket->addTmEvent(gertiTmEvent);
//  GeRtiAmbVar->enableTimeRegulation1516(gertiTmEvent.timestampTwo);
#else
  GERTICO::ConvertTime::mapIt(gertiTmEvent.timestamp, theFederateTime);
  eventMarket->addTmEvent(gertiTmEvent);
//  GeRtiAmbVar->enableTimeRegulation(t, gertiTmEvent.timestampTwo);
#endif

  *myActualLookahead = theLookahead;
  *myRequestedLookahead = theLookahead;

  timeRegulationPending = true;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "enableTimeRegulation", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::flushQueueRequest(GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "flushQueueRequest", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"flushQueueRequest";
  GeRtiFactory::GertiTmEvent gertiTmEvent;
  GeRtiFactory::Time fedTime;

  checkAdvanceValues(wChar, theGeRtiFedTime);

  if (theGeRtiFedTime > *myLogicalTime)
  {
    timePastFlag = false;
  }

  gertiTmEvent.service = 10;
  GERTICO::ConvertTime::mapIt(gertiTmEvent.timestamp, theGeRtiFedTime);
  gertiTmEvent.sourceId = federate;
  eventMarket->addTmEvent(gertiTmEvent);
//  GeRtiAmbVar->flushQueueRequest(fedTime);
  *myTimeRequested = theGeRtiFedTime;
  timeServiceFlag = flushQueueRequestFlag;
  timeAdvancing = true;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "flushQueueRequest", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::TimeManagementLRC::isTimeAdvancing(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_d)
                            {
                              if (timeAdvancing)
                              {
                                strcpy(galMsg,"true");
                              }
                              else
                              {
                                strcpy(galMsg,"false");
                              }
                              E2(GeRti_TM_d, "isTimeAdvancing", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return timeAdvancing;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::TimeManagementLRC::isTimeRegulation(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_d)
                            {
                              if (timeRegulation)
                              {
                                strcpy(galMsg,"true");
                              }
                              else
                              {
                                strcpy(galMsg,"false");
                              }
                              E2(GeRti_TM_d, "isTimeRegulation", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return timeRegulation;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::modifyLookahead(GERTICO::GeRtiLogicalTimeInterval const &theLogicalTimeInterval)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "modifyLookahead", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"modifyLookahead";
  GeRtiFactory::GertiTmEvent gertiTmEvent;
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> zeroTime(geRtiLogicalTimeIntervalFactory.makeZero());

  // Not allowed in time advancing state.
  if (timeAdvancing == true)
  {
    throw GeRtiFactory::TimeAdvanceAlreadyInProgress(wChar);
  }

  // Negative time interval not allowed.
  if (theLogicalTimeInterval < *zeroTime)
  {
    throw GeRtiFactory::InvalidLookahead(wChar);
  }

  gertiTmEvent.service = 12;
  GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(gertiTmEvent.timestamp, theLogicalTimeInterval);
  gertiTmEvent.sourceId = federate;
  eventMarket->addTmEvent(gertiTmEvent);
  *myRequestedLookahead = theLogicalTimeInterval;
  if (*myActualLookahead < theLogicalTimeInterval)
  {
    *myActualLookahead = theLogicalTimeInterval;
  }
  else
  {
    lookaheadChanging = true;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "modifyLookahead", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::nextEventRequest(GERTICO::GeRtiFedTime const &theGeRtiFedTime, bool const &theBool)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "nextEventRequest", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"nextEventRequest";
  GeRtiFactory::GertiTmEvent gertiTmEvent;
  GeRtiFactory::Time fedTime;
  bool localAvail = theBool;

  checkAdvanceValues(wChar, theGeRtiFedTime);

  pm.acquire();
  if (theGeRtiFedTime > *myLogicalTime)
  {
    timePastFlag = false;
  }

  if (localAvail && timePastFlag)
  {
    localAvail = false;
  }

//  GERTICO::ConvertTime::mapIt(fedTime, theGeRtiFedTime);
  GERTICO::ConvertTime::mapIt(gertiTmEvent.timestamp, theGeRtiFedTime);
  if (localAvail)
  {
  gertiTmEvent.service = 9;
//    GeRtiAmbVar->nextEventRequestAvailable(fedTime);
    timeServiceFlag = nextEventAvailableFlag;
  }
  else
  {
  gertiTmEvent.service = 8;
//    GeRtiAmbVar->nextEventRequest(fedTime);
    timeServiceFlag = nextEventFlag;
  }
  gertiTmEvent.sourceId = federate;
  eventMarket->addTmEvent(gertiTmEvent);
  *myTimeRequested = theGeRtiFedTime;
  timeAdvancing = true;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "nextEventRequest", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::queryGALT(GERTICO::GeRtiFedTime& theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "queryGALT", "enter");
                           #endif   // inserted by Gal converter
  GERTICO::GeRtiFedTime *theFedTimePtr = NULL;
  GeRtiFactory::Time_var t;

  timeManagementVar->queryGALT(federate, t);
  GERTICO::ConvertTime::mapItGeRtiFedTime(geRtiFedTimeFactory, &theFedTimePtr, t);
  theTime = *theFedTimePtr;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "queryGALT", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::queryLITS(GERTICO::GeRtiFedTime& theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "queryLITS", "enter");
                           #endif   // inserted by Gal converter
  GERTICO::GeRtiFedTime *theFedTimePtr = NULL;
  GeRtiFactory::Time_var t;

  timeManagementVar->queryLITS(federate, t);
  GERTICO::ConvertTime::mapItGeRtiFedTime(geRtiFedTimeFactory, &theFedTimePtr, t);
  theTime = *theFedTimePtr;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "queryLITS", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::queryLogicalTime(GERTICO::GeRtiFedTime& theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "queryLogicalTime", "enter");
                           #endif   // inserted by Gal converter
  theTime = *myLogicalTime;
                           #ifdef GalDebug   // inserted by Gal converter
char buf[1024];
theTime.getPrintableString(buf);
                             E2(GeRti_TM_d, "queryLogicalTime", buf);
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::queryLookahead(GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "queryLookahead", "enter");
                           #endif   // inserted by Gal converter
  if (lookaheadChanging)
  {
    std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> logicalTimeInterval(geRtiLogicalTimeIntervalFactory.makeZero());
    GeRtiFactory::Time_var t;

    timeManagementVar->queryLookahead(federate, t);
    GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(geRtiLogicalTimeIntervalFactory, *logicalTimeInterval, t);
    theLogicalTimeInterval = *logicalTimeInterval;
    if (*logicalTimeInterval == *myRequestedLookahead)
    {
      lookaheadChanging = false;
    }
  }
  else
  {
    theLogicalTimeInterval = *myRequestedLookahead;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "queryLookahead", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::restore(DOMElement &theDOMElement)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "restore", "enter");
                           #endif   // inserted by Gal converter
  char *tmpChar;

  clear();

  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(actualLookaheadStr.c_str())));
  GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(geRtiLogicalTimeIntervalFactory, *myActualLookahead, tmpChar);
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(logicalTimeStr.c_str())));
  GERTICO::ConvertTime::mapGeRtiFedTime(geRtiFedTimeFactory, *myLogicalTime, tmpChar);
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(requestedLookaheadStr.c_str())));
  GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(geRtiLogicalTimeIntervalFactory, *myRequestedLookahead, tmpChar);
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(timeRequestedStr.c_str())));
  GERTICO::ConvertTime::mapGeRtiFedTime(geRtiFedTimeFactory, *myTimeRequested, tmpChar);
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(timeTagStr.c_str())));
  GERTICO::ConvertTime::mapGeRtiFedTime(geRtiFedTimeFactory, *myTimeTag, tmpChar);
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(timeFlagStr.c_str())));
  if (strcmp (tmpChar, "0") == 0)
  {
    gotTimeAdvanceGrant = false;
  }
  else
  {
    gotTimeAdvanceGrant = true;
  }
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(timeAdvancingStr.c_str())));
  if (strcmp(tmpChar, "1") == 0)
  {
    timeAdvancing = true;
  }
  else
  {
    timeAdvancing = false;
  }
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(timeConstrainedStr.c_str())));
  if (strcmp(tmpChar, "1") == 0)
  {
    timeConstrained = true;
  }
  else
  {
    timeConstrained = false;
  }
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(timeConstrainedPendingStr.c_str())));
  if (strcmp(tmpChar, "1") == 0)
  {
    timeConstrainedPending = true;
  }
  else
  {
    timeConstrainedPending = false;
  }
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(timePastFlagStr.c_str())));
  if (strcmp(tmpChar, "1") == 0)
  {
    timePastFlag = true;
  }
  else
  {
    timePastFlag = false;
  }
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(timeRegulationStr.c_str())));
  if (strcmp(tmpChar, "1") == 0)
  {
    timeRegulation = true;
  }
  else
  {
    timeRegulation = false;
  }
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(timeRegulationPendingStr.c_str())));
  if (strcmp(tmpChar, "1") == 0)
  {
    timeRegulationPending = true;
  }
  else
  {
    timeRegulationPending = false;
  }
  tmpChar = XMLString::transcode(theDOMElement.getAttribute(XMLString::transcode(timeServiceStr.c_str())));
  if (strcmp(tmpChar, idleFlagStr.c_str()) == 0)
  {
    timeServiceFlag = GERTICO::idleFlag;
  }
  else if (strcmp(tmpChar, nextEventFlagStr.c_str()) == 0)
  {
    timeServiceFlag = GERTICO::nextEventFlag;
  }
  else if (strcmp(tmpChar, nextEventAvailableFlagStr.c_str()) == 0)
  {
    timeServiceFlag = GERTICO::nextEventAvailableFlag;
  }
  else if (strcmp(tmpChar, timeAdvanceFlagStr.c_str()) == 0)
  {
    timeServiceFlag = GERTICO::timeAdvanceFlag;
  }
  else if (strcmp(tmpChar, timeAdvanceAvailableFlagStr.c_str()) == 0)
  {
    timeServiceFlag = GERTICO::timeAdvanceAvailableFlag;
  }
  else if (strcmp(tmpChar, flushQueueRequestFlagStr.c_str()) == 0)
  {
    timeServiceFlag = GERTICO::flushQueueRequestFlag;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "restore", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::retract(GeRtiFactory::ERHandle const &theERHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "retract", "enter");
                           #endif   // inserted by Gal converter
  GeRtiFactory::GertiTmEvent gertiTmEvent;

  gertiTmEvent.service = 13;
  gertiTmEvent.sourceId = federate;
  gertiTmEvent.theHandle = theERHandle.theSerialNumber;
  eventMarket->addTmEvent(gertiTmEvent);
//  GeRtiAmbVar->retract(theERHandle);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "retract", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "save", "enter");
                           #endif   // inserted by Gal converter
  XMLCh tempStr[128];
  XMLCh tempStr1[128];
  char buf[128];

  // Actual lookahead attribute
  XMLString::transcode(actualLookaheadStr.c_str(), tempStr, 99);
  GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(buf, *myActualLookahead);
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Logical time attribute
  XMLString::transcode(logicalTimeStr.c_str(), tempStr, 99);
  GERTICO::ConvertTime::mapGeRtiFedTime(buf, *myLogicalTime);
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Requested lookahead attribute
  XMLString::transcode(requestedLookaheadStr.c_str(), tempStr, 99);
  GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(buf, *myRequestedLookahead);
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Time requested attribute
  XMLString::transcode(timeRequestedStr.c_str(), tempStr, 99);
  GERTICO::ConvertTime::mapGeRtiFedTime(buf, *myTimeRequested);
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Time advance grant
  XMLString::transcode(timeTagStr.c_str(), tempStr, 99);
  GERTICO::ConvertTime::mapGeRtiFedTime(buf, *myTimeTag);
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Got time advance grant.
  XMLString::transcode(timeFlagStr.c_str(), tempStr, 99);
  if (gotTimeAdvanceGrant)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Time advancing state
  XMLString::transcode(timeAdvancingStr.c_str(), tempStr, 99);
  if (timeAdvancing)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Time constrained
  XMLString::transcode(timeConstrainedStr.c_str(), tempStr, 99);
  if (timeConstrained)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Time constrained pending
  XMLString::transcode(timeConstrainedPendingStr.c_str(), tempStr, 99);
  if (timeConstrainedPending)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Time past flag
  XMLString::transcode(timePastFlagStr.c_str(), tempStr, 99);
  if (timePastFlag)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Time regulation
  XMLString::transcode(timeRegulationStr.c_str(), tempStr, 99);
  if (timeRegulation)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Time regulation pending
  XMLString::transcode(timeRegulationPendingStr.c_str(), tempStr, 99);
  if (timeRegulationPending)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);

  // Time service flag
  XMLString::transcode(timeServiceStr.c_str(), tempStr, 99);
  switch (timeServiceFlag)
  {
    case GERTICO::nextEventFlag:
    {
      strcpy(buf, nextEventFlagStr.c_str());
      break;
    }
    case GERTICO::nextEventAvailableFlag:
    {
      strcpy(buf, nextEventAvailableFlagStr.c_str());
      break;
    }
    case GERTICO::timeAdvanceFlag:
    {
      strcpy(buf, timeAdvanceFlagStr.c_str());
      break;
    }
    case GERTICO::timeAdvanceAvailableFlag:
    {
      strcpy(buf, timeAdvanceAvailableFlagStr.c_str());
      break;
    }
    case GERTICO::flushQueueRequestFlag:
    {
      strcpy(buf, flushQueueRequestFlagStr.c_str());
      break;
    }
    default:
    {
      strcpy(buf, idleFlagStr.c_str());
      break;
    }
  }
  XMLString::transcode(buf, tempStr1, 99);
  theDOMElement.setAttribute(tempStr, tempStr1);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "save", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::setGeRtiAmbassador(GeRtiFactory::GeRtiAmbassador_var theGeRtiAmbassador_var)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "setGeRtiAmbassador", "enter");
                           #endif   // inserted by Gal converter
  GeRtiAmbVar = GeRtiFactory::GeRtiAmbassador::_duplicate(theGeRtiAmbassador_var);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "setGeRtiAmbassador", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::testRequestTime(GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "testRequestTime", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"testRequestTime";
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> lh(geRtiLogicalTimeIntervalFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> tr(geRtiFedTimeFactory.makeZero());

  *tr = *myTimeRequested;
  *lh = *myActualLookahead;
  *tr += *lh;
  if (theGeRtiFedTime < *tr)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "testRequestTime", "FederationTimeAlreadyPassed");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::FederationTimeAlreadyPassed(wChar);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "testRequestTime", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::testSendTime(GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "testSendTime", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"testSendTime";
  std::auto_ptr<GERTICO::GeRtiFedTime> tr(geRtiFedTimeFactory.makeZero());

  if (timeRegulation == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "testSendTime", "notTimeRegulation");
                           #endif   // inserted by Gal converter
    return;
  }

  if (timeAdvancing)
  {
    *tr = *myTimeRequested;
    *tr += *myActualLookahead;
  }
  else
  {
    *tr = *myLogicalTime;
    *tr += *myActualLookahead;
  }

  if (theGeRtiFedTime == *myLogicalTime)
  {
    if (timePastFlag)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "testSendTime", "InvalidFederationTime");
                           #endif   // inserted by Gal converter
      throw GeRtiFactory::InvalidFederationTime(L"testSendTime::sameTimeInvalid");
    }
  }

  if (myActualLookahead->isZero())
  {
    if (timeServiceFlag == nextEventAvailableFlag ||
        timeServiceFlag == timeAdvanceAvailableFlag ||
        timeServiceFlag == flushQueueRequestFlag)
    {
      if (theGeRtiFedTime < *tr)
      {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "testSendTime", "InvalidFederationTime");
                           #endif   // inserted by Gal converter
        throw GeRtiFactory::InvalidFederationTime(L"testSendTime::timePast");
      }
    }
    else
    {
      if (theGeRtiFedTime <= *tr)
      {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "testSendTime", "InvalidFederationTime");
                           #endif   // inserted by Gal converter
        throw GeRtiFactory::InvalidFederationTime(wChar);
      }
    }
  }
  else
  {
    if (theGeRtiFedTime < *tr)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "testSendTime", "InvalidFederationTime");
                           #endif   // inserted by Gal converter
      throw GeRtiFactory::InvalidFederationTime(wChar);
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "testSendTime", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// This function only sets the corresponding values. The real grant is done
// the the event handler.
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::timeAdvanceGrant(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "timeAdvanceGrant", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"timeAdvanceGrant";
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> a(geRtiLogicalTimeIntervalFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> tmpTime(geRtiLogicalTimeIntervalFactory.makeZero());

  // HLA check
  if (timeAdvancing == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "timeAdvanceGrant", "JoinedFederateIsNotInTimeAdvancingState");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::JoinedFederateIsNotInTimeAdvancingState(wChar);
  }

  timeAdvancing = false;

  // Slowly adapt the actualLookahead to requestedLookahead.
  *a = *myActualLookahead;
  if (*myRequestedLookahead < *a)
  {
    tmpTime = *myTimeTag - *myLogicalTime;
    if (*a < *tmpTime)
    {
      *myActualLookahead = *myRequestedLookahead;
    }
    else
    {
      *a -= *tmpTime;
      // Do not go below the requested requestedLookahead.
      if (*a < *myRequestedLookahead)
      {
        *a = *myRequestedLookahead;
      }
      *myActualLookahead = *a;
    }
  }

  switch(timeServiceFlag)
  {
    case nextEventFlag:
    {
      timePastFlag = true;
      break;
    }
    case timeAdvanceFlag:
    {
      timePastFlag = true;
      break;
    }
  }

  // Now change logical time.
  *myLogicalTime = *myTimeTag;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "timeAdvanceGrant", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::timeAdvanceRequest(GERTICO::GeRtiFedTime const &theGeRtiFedTime, bool const &theBool)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "timeAdvanceRequest", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"LRC";
  GeRtiFactory::GertiTmEvent gertiTmEvent;

  checkAdvanceValues(wChar, theGeRtiFedTime);

  pm.acquire();
  if (theGeRtiFedTime > *myLogicalTime)
  {
    timePastFlag = false;
  }

  // Be careful where this is set / unset!
  timeAdvancing = true;

  if (gotAnnounceFederateSaveWithTime == false || (gotAnnounceFederateSaveWithTime && theGeRtiFedTime < *myTimeSave))
  {
    // Check if local time advance grant is possible.
    if (gotTimeAdvanceGrantIntermediate)
    {
      // Only if less than galt time!
      if (theGeRtiFedTime < *myTimeTarGalt)
      {
        // Local time advance: special optimization.
        // GALT in gerti is no longer correct for other federates!
        *myTimeTag = theGeRtiFedTime;
        gotTimeAdvanceGrant = true;
        pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "timeAdvanceRequest", "gotLocalTAG");
                           #endif   // inserted by Gal converter
        return;
      }
      else
      {
        gotTimeAdvanceGrantIntermediate = false;
      }
    }
  }

  // Remote call
//  GERTICO::ConvertTime::mapIt(fedTime, theGeRtiFedTime);
  GERTICO::ConvertTime::mapIt(gertiTmEvent.timestamp, theGeRtiFedTime);
  std::auto_ptr<GERTICO::GeRtiFedTime> tr(geRtiFedTimeFactory.makeZero());
  char buff[512];
  *tr = theGeRtiFedTime;
  tr->getPrintableString(buff);
  try
  {
  if (theBool)
  {
  gertiTmEvent.service = 7;
//    GeRtiAmbVar->timeAdvanceRequestAvailable(fedTime);
    timeServiceFlag = timeAdvanceAvailableFlag;
  }
  else
  {
  gertiTmEvent.service = 6;
//    GeRtiAmbVar->timeAdvanceRequest(fedTime);
    timeServiceFlag = timeAdvanceFlag;
  }
  gertiTmEvent.sourceId = federate;
  eventMarket->addTmEvent(gertiTmEvent);
  }
  catch(...)
  {
    timeAdvancing = false;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "timeAdvanceRequest", "catch(...)");
                           #endif   // inserted by Gal converter
    pm.release();
    throw;
  }
  *myTimeRequested = theGeRtiFedTime;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "timeAdvanceRequest", "leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Only to keep track of flags.
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::timeConstrainedEnabled(GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "timeConstrainedEnabled", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"timeConstrainedEnabled";

  // HLA check
  if (timeConstrainedPending == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "timeConstrainedEnabled", "NoRequestToEnableTimeConstrainedWasPending");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::NoRequestToEnableTimeConstrainedWasPending(wChar);
  }

  *myLogicalTime = theGeRtiFedTime;
  timeConstrained = true;
  timeConstrainedPending = false;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "timeConstrainedEnabled", "leave");
                           #endif   // inserted by Gal converter
}
// ---------------------------------------------------------------------------
// Only to keep track of flags.
// ---------------------------------------------------------------------------
void GERTICO::TimeManagementLRC::timeRegulationEnabled(GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "timeRegulationEnabled", "enter");
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"timeRegulationEnabled";

  // HLA check
  if (timeRegulationPending == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_w, "timeRegulationEnabled", "NoRequestToEnableTimeRegulationWasPending");
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::NoRequestToEnableTimeRegulationWasPending(wChar);
  }

  *myLogicalTime = theGeRtiFedTime;
  timeRegulation = true;
  timeRegulationPending = false;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "timeRegulationEnabled", "leave");
                           #endif   // inserted by Gal converter
}
