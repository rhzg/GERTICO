/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** TokenHolder.cpp
**
*******************************************************************************/

#include "TokenHolder.h"

#include "ace/Thread.h"
#include "Util/GeRtiTypes.h"
#include "Util/GeRtiFedTimeI.h"

/********************************* Gal begin *********************************/   // inserted by Gal converter

#ifdef GalDebug   // inserted by Gal converter
#include "Gal/StdAfx.h"   // inserted by Gal converter
#include "Gal/repository_l.h"   // inserted by Gal converter
#include "Gal/event.h"   // inserted by Gal converter

static class Repository_l *TM=(Repository::getSingleInstance())->getRepository_l("GeRtiTM.res","GeRtiTM");

static class Event *GeRti_TM_d=TM->getRefEvent("GeRti_TM_d");
static class Event *GeRti_TM_e=TM->getRefEvent("GeRti_TM_e");
static class Event *GeRti_TM_i=TM->getRefEvent("GeRti_TM_i");
static class Event *GeRti_TM_mu_d=TM->getRefEvent("GeRti_TM_mu_d");
static class Event *GeRti_TM_w=TM->getRefEvent("GeRti_TM_w");

static char buff[1024];

#endif   // inserted by Gal converter
/*********************************** Gal end *********************************/   // inserted by Gal converter

std::string GERTICO::TokenHolder::actualLookaheadStr("actualLookahead");
std::string GERTICO::TokenHolder::advancingStateStr("advancingState");
std::string GERTICO::TokenHolder::firstEnableTimeRegulationStr("firstEnableTimeRegulation");
std::string GERTICO::TokenHolder::flushQueueRequestFlagStr("flushQueueRequestFlag");
std::string GERTICO::TokenHolder::idleFlagStr("idleFlag");
std::string GERTICO::TokenHolder::idStr("id");
std::string GERTICO::TokenHolder::lbtsStr("lbts");
std::string GERTICO::TokenHolder::lbtsfStr("lbtsf");
std::string GERTICO::TokenHolder::lbtsgStr("lbtsg");
std::string GERTICO::TokenHolder::logicalTimeStr("logicalTime");
std::string GERTICO::TokenHolder::lookaheadTimeStr("lookaheadTime");
std::string GERTICO::TokenHolder::nextEventFlagStr("nextEventFlag");
std::string GERTICO::TokenHolder::nextEventAvailableFlagStr("nextEventAvailableFlag");
std::string GERTICO::TokenHolder::oldLogicalTimeStr("oldLogicalTime");
std::string GERTICO::TokenHolder::saveTimeStr("saveTime");
std::string GERTICO::TokenHolder::timeAdvanceFlagStr("timeAdvanceFlag");
std::string GERTICO::TokenHolder::timeAdvanceAvailableFlagStr("timeAdvanceAvailableFlag");
std::string GERTICO::TokenHolder::timeConstrainedStr("timeConstrained");
std::string GERTICO::TokenHolder::timeConstrainedPendingStr("timeConstrainedPending");
std::string GERTICO::TokenHolder::timeValueStr("timeValue");
std::string GERTICO::TokenHolder::timeFederateStr("timeFederate");
std::string GERTICO::TokenHolder::timeFederatesStr("timeFederates");
std::string GERTICO::TokenHolder::timePastFlagStr("timePastFlag");
std::string GERTICO::TokenHolder::timeRegulationStr("timeRegulation");
std::string GERTICO::TokenHolder::timeRegulationPendingStr("timeRegulationPending");
std::string GERTICO::TokenHolder::timeRequestedStr("timeRequested");
std::string GERTICO::TokenHolder::timeServiceStr("timeService");

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::QueryData::QueryData(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory)
{
  actualLookahead.reset(geRtiLogicalTimeIntervalFactory.makeZero());
  galt.reset(geRtiFedTimeFactory.makeZero());
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::QueryData::~QueryData(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TimeData::TimeData(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory)
{
  firstEnableTimeRegulation = false;
  lbtsf = false;
  lbtsg = false;
  numberOfPeerHubsReply = 0;
  timeAdvancingState = false;
  timeConstrained = false;
  timeConstrainedPending = false;
  timeConstrainedPendingHubAnswerPeer = false;
  timeConstrainedPendingHubReplies = false;
  timePastFlag = false;
  timeRegulation = false;
  timeServiceFlag = idleFlag;
  timeRegulationPending = false;
  timeRegulationPendingHubAnswerPeer = false;
  timeRegulationPendingHubReplies = false;

  actualLookahead.reset(geRtiLogicalTimeIntervalFactory.makeZero());
  lbts.reset(geRtiFedTimeFactory.makeZero());
  logicalTime.reset(geRtiFedTimeFactory.makeZero());
  oldLogicalTime.reset(geRtiFedTimeFactory.makeZero());
  requestedLookahead.reset(geRtiLogicalTimeIntervalFactory.makeZero());
  timeIntermediateGrant.reset(geRtiFedTimeFactory.makeZero());
  timeRequested.reset(geRtiFedTimeFactory.makeZero());
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TimeData::~TimeData(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TokenHolder::TokenHolder(TimeServiceClient &theTimeServiceClient, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory) : geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory), timeServiceClient(theTimeServiceClient)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder", "Enter");
                           #endif   // inserted by Gal converter
  // Set default values.
  notDone = true;
  numberOfPeerHubs = 0;
  psToken = NULL;

  // Set initial values.
  psToken = new ACE_Semaphore (0);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TokenHolder::~TokenHolder(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "~TokenHolder", "Enter");
                           #endif   // inserted by Gal converter
  clear();

  if (psToken)
  {
    delete psToken;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "~TokenHolder", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
// NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::calcTokenValues(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData const &theTimeData, GERTICO::GeRtiFedTime &lbts, bool &lbtsg)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::calcTokenValues", "Enter");
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> tmpFedTime(geRtiFedTimeFactory.makeZero());
  lbtsg = false;

  switch(theTimeData.timeServiceFlag)
  {
    case idleFlag:
    {
      *tmpFedTime = *theTimeData.logicalTime;
      *tmpFedTime += *theTimeData.actualLookahead;
      lbts = *tmpFedTime;
      lbtsg = false;
      break;
    }
    case nextEventFlag:
    {
      if (theTimeData.timeAdvancingState)
      {
        std::auto_ptr<GERTICO::GeRtiFedTime> smallestAvailableTSO(timeServiceClient.smallestAvailableTSO(theFederate));

        lbts = *theTimeData.timeRequested;
        if (smallestAvailableTSO.get())
        {
          if (*smallestAvailableTSO < *theTimeData.timeRequested)
          {
            lbts = *smallestAvailableTSO;
          }
        }
      }
      else
      {
        lbts = *theTimeData.logicalTime;
      }
      if (theTimeData.actualLookahead->isZero())
      {
        std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> epsilonFedTime(geRtiLogicalTimeIntervalFactory.epsilon());

        if (!theTimeData.firstEnableTimeRegulation) lbts += *epsilonFedTime;
      }
      else
      {
        lbts += *theTimeData.actualLookahead;
      }
      lbtsg = false;
      break;
    }
    case flushQueueRequestFlag:
    case nextEventAvailableFlag:
    {
      if (theTimeData.timeAdvancingState)
      {
        *tmpFedTime = *theTimeData.timeRequested;
      }
      else
      {
        *tmpFedTime = *theTimeData.logicalTime;
      }
      *tmpFedTime += *theTimeData.actualLookahead;
      lbts = *tmpFedTime;
      lbtsg = false;
      break;
    }
    case timeAdvanceFlag:
    {
      if (theTimeData.actualLookahead->isZero())
      {
        std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> epsilonFedTime(geRtiLogicalTimeIntervalFactory.epsilon());

        if (theTimeData.timeAdvancingState)
        {
          lbts = *theTimeData.timeRequested;
        }
        else
        {
          lbts = *theTimeData.logicalTime;
        }
        if (!theTimeData.firstEnableTimeRegulation) lbts += *epsilonFedTime;
      }
      else
      {
        if (theTimeData.timeAdvancingState)
        {
          *tmpFedTime = *theTimeData.timeRequested;
        }
        else
        {
          *tmpFedTime = *theTimeData.logicalTime;
        }
        *tmpFedTime += *theTimeData.actualLookahead;
        lbts = *tmpFedTime;
      }
      lbtsg = true;
      break;
    }
    case timeAdvanceAvailableFlag:
    {
      if (theTimeData.timeAdvancingState)
      {
        *tmpFedTime = *theTimeData.timeRequested;
      }
      else
      {
        *tmpFedTime = *theTimeData.logicalTime;
      }
      *tmpFedTime += *theTimeData.actualLookahead;
      lbts = *tmpFedTime;
      lbtsg = true;
      break;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::calcTokenValues", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
// ---------------------------------------------------------------------------
bool GERTICO::TokenHolder::checkGrantCondition(GeRtiFactory::GeRtiHandle const theFederate, GERTICO::TimeData &theTimeData, GERTICO::GeRtiFedTime &theGrantTime)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> testTime(geRtiFedTimeFactory.makeZero());
  GERTICO::TimeDataMap::iterator itTimeDataMap;

  if (theTimeData.timeRegulation == false)
  {
    return false;
  }

  if (theTimeData.actualLookahead->isZero())
  {
    for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
    {
      if (itTimeDataMap->first == theFederate)
      {
        continue;
      }
      if (itTimeDataMap->second->timeRegulation == false)
      {
        continue;
      }
      if (itTimeDataMap->second->actualLookahead->isZero())
      {
        if (*itTimeDataMap->second->logicalTime < theGrantTime)
        {
          if (itTimeDataMap->second->timeAdvancingState == false)
          {
            return true;
          }
        }
      }
    }
  }
  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
  {
    if (itTimeDataMap->first == theFederate)
    {
      continue;
    }
    if (itTimeDataMap->second->timeRegulation == false)
    {
      continue;
    }
    if (theTimeData.timeServiceFlag == timeAdvanceFlag || theTimeData.timeServiceFlag == nextEventFlag)
    {
      if (itTimeDataMap->second->timeAdvancingState)
      {
        *testTime = *itTimeDataMap->second->timeRequested;
        *testTime += *itTimeDataMap->second->actualLookahead;
        if (itTimeDataMap->second->timeServiceFlag == timeAdvanceFlag || itTimeDataMap->second->timeServiceFlag == nextEventFlag)
        {
          if (*testTime < theGrantTime)
          {
            return true;
          }
        }
        else
        {
          if (*testTime <= theGrantTime)
          {
            return true;
          }
        }
      }
      else
      {
        *testTime = *itTimeDataMap->second->logicalTime;
        *testTime += *itTimeDataMap->second->actualLookahead;
        if (*testTime <= theGrantTime)
        {
          return true;
        }
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::clear(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::clear", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::QueryData *queryData;
  GERTICO::QueryDataMap::iterator itQueryDataMap;
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "cleara", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "clearaa", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  enableTimeConstrainedIds.clear();
  enableTimeRegulationIds.clear();

  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap = timeDataMap.begin())
  {
    timeData = itTimeDataMap->second;
    timeDataMap.erase(itTimeDataMap);
    delete timeData;
  }
  for (itTimeDataMap = timeDataInactiveMap.begin(); itTimeDataMap != timeDataInactiveMap.end(); itTimeDataMap = timeDataInactiveMap.begin())
  {
    timeData = itTimeDataMap->second;
    timeDataInactiveMap.erase(itTimeDataMap);
    delete timeData;
  }
  pmQuery.acquire();
  for (itQueryDataMap = queryDataMap.begin(); itQueryDataMap != queryDataMap.end(); itQueryDataMap = queryDataMap.begin())
  {
    queryData = itQueryDataMap->second;
    queryDataMap.erase(itQueryDataMap);
    delete queryData;
  }
  pmQuery.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "clearr", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "clearrr", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::clear", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Unset the timeConstrained flag.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::disableTimeConstrained(GeRtiFactory::GeRtiHandle const &theFederate)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg,"Federate=%lu", f);
                              E2(GeRti_TM_i,"TokenHolder::disableTimeConstrained", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"disableTimeConstrained";
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "dtca", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "dtcaa", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "dtcer", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "dtcerr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::RTIinternalError(wChar);
  }
  timeData = itTimeDataMap->second;

  if (timeData->timeConstrained == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "dtcerrr", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "dtceerrrr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeConstrainedWasNotEnabled(wChar);
  }

  timeData->timeConstrained = false;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "dtcr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  psToken->release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::disableTimeConstrained", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::disableTimeRegulation(GeRtiFactory::GeRtiHandle const &theFederate)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg,"Federate=%lu", f);
                              E2(GeRti_TM_i,"TokenHolder::disableTimeRegulation", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"disableTimeRegulation";
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "dtra", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "dtraa", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "dtre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::RTIinternalError(wChar);
  }
  timeData = itTimeDataMap->second;

  if (timeData->timeRegulation == false)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "dtree", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeRegulationWasNotEnabled(wChar);
  }

  timeData->timeRegulation = false;
  timeData->firstEnableTimeRegulation = false;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "dtrr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  psToken->release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::disableTimeRegulation", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Set the timeConstrained flag.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::enableTimeConstrained(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theSourceType)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg,"Federate=%lu", f);
                              E2(GeRti_TM_i,"TokenHolder::enableTimeConstrained", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"enableTimeConstrained";
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etca", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etcaa", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etce", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::RTIinternalError(wChar);
  }
  timeData = itTimeDataMap->second;

  // Test Parameters
  // Not allowed in time advancing state.
  if (timeData->timeAdvancingState)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etcee", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeAdvanceAlreadyInProgress(wChar);
  }

  if (timeData->timeConstrainedPending)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etceee", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::EnableTimeConstrainedPending(wChar);
  }

  // Not allowed when already enabled.
  if (timeData->timeConstrained)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etce", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeConstrainedAlreadyEnabled(wChar);
  }

  timeData->timeConstrainedPending = true;
  timeData->timeConstrainedPendingHubReplies = false;
  if (numberOfPeerHubs > 1)
  {
    if (theSourceType == 1)
    {
      // Only for remote federate
      timeData->timeConstrainedPendingHubAnswerPeer = true;
    }
    if (theSourceType == 2)
    {
      // Only for local federate
      timeData->timeConstrainedPendingHubReplies = true;
      timeData->localFederate = true;
    }
    else
    {
      timeData->localFederate = false;
    }
  }
  enableTimeConstrainedIds.insert(theFederate);
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etcr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  psToken->release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::enableTimeConstrained", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
#ifdef IEEE_1516
void GERTICO::TokenHolder::enableTimeRegulation(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval &theLookahead, GeRtiFactory::GeRtiHandle const &theSourceType)
#else
void GERTICO::TokenHolder::enableTimeRegulation(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &theFederateTime, GERTICO::GeRtiLogicalTimeInterval &theLookahead, GeRtiFactory::GeRtiHandle const &theSourceType)
#endif
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              theLookahead.getPrintableString(buff);
                              sprintf(galMsg,"Federate=%lu,lookahead=%s", f, buff);
                              E2(GeRti_TM_i,"TokenHolder::enableTimeRegulation", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"enableTimeRegulation";
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> zeroTime(geRtiLogicalTimeIntervalFactory.makeZero());
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etra", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etraa", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::RTIinternalError(wChar);
  }
  timeData = itTimeDataMap->second;

  // Test Parameters
  // Not allowed in time advancing state.
  if (timeData->timeAdvancingState)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeAdvanceAlreadyInProgress(wChar);
  }

#ifndef IEEE_1516
  if (timeData->timeConstrained)
  {
    if (!(theFederateTime == *timeData->logicalTime))
    {
      pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      throw GeRtiFactory::InvalidFederationTime(wChar);
    }
  }
#endif

  if (timeData->timeRegulationPending)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::EnableTimeRegulationPending(wChar);
  }

  if (timeData->timeRegulation)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeRegulationAlreadyEnabled(wChar);
  }

#ifndef IEEE_1516
  if (theFederateTime < *timeData->logicalTime)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::InvalidFederationTime(wChar);
  }
#endif

  if (theLookahead < *zeroTime)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::InvalidLookahead(wChar);
  }

#ifndef IEEE_1516
  *timeData->logicalTime = theFederateTime;
#endif

  setActualLookahead(theFederate, *timeData, theLookahead);

  *timeData->requestedLookahead = theLookahead;

  // flag to be considered for lbts definition while in timeRegulationPending phase
  timeData->firstEnableTimeRegulation = true;

  enableTimeRegulationIds.insert(theFederate);

  timeData->timeRegulationPending = true;
  timeData->timeRegulationPendingHubReplies = false;
  if (numberOfPeerHubs > 1)
  {
    if (theSourceType == 1)
    {
      // Only for remote federate
      timeData->timeRegulationPendingHubAnswerPeer = true;
    }
    if (theSourceType == 2)
    {
      // Only if local federate
      timeData->timeRegulationPendingHubReplies = true;
      timeData->localFederate = true;
    }
    else
    {
      timeData->localFederate = false;
    }
  }
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "etrr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  psToken->release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::enableTimeRegulation", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::flushCalc(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData const &timeData, GERTICO::GeRtiFedTimeMap &theAdvancers)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::flushCalc", "Enter");
                           #endif   // inserted by Gal converter
  if (timeData.timeConstrained)
  {
    // Time advance dependent on other time masters.
    std::auto_ptr<GERTICO::GeRtiFedTime> galt(geRtiFedTimeFactory.makeZero());
    std::auto_ptr<GERTICO::GeRtiFedTime> grantTime(geRtiFedTimeFactory.makeZero());

    // First approximation on grant time.
    *grantTime = *timeData.timeRequested;

#ifdef IEEE_1516
    std::auto_ptr<GERTICO::GeRtiFedTime> tsoTime(timeServiceClient.smallestAvailableTSO(theFederate));
    if (tsoTime.get())
    {
      if (*tsoTime < *grantTime)
      {
        *grantTime = *tsoTime;
      }
    }
#endif

    // Get galt.
    queryGALTprivate(theFederate, *galt);
    if (*galt < *grantTime)
    {
      *grantTime = *galt;
    }

    if (g2Condition(theFederate, *grantTime))
    {
      GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
      *tmpTime = *grantTime;
      theAdvancers[theFederate] = tmpTime;
//      timeAdvanceGrant(theFederate, *grantTime);
    }
    else
    {
      queryGALTprivate(theFederate, *galt);
      if (galt->isPositiveInfinity())
      {
        // No limit on time advance.
        GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
        *tmpTime = *grantTime;
        theAdvancers[theFederate] = tmpTime;
//        timeAdvanceGrant(theFederate, *grantTime);
      }
    }
  }
  else
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> tsoTime(timeServiceClient.smallestAvailableTSO(theFederate));
    if (tsoTime.get() == NULL)
    {
        GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
        *tmpTime = *timeData.timeRequested;
        theAdvancers[theFederate] = tmpTime;
//      timeAdvanceGrant(theFederate, *timeData.timeRequested);
    }
    else
    {
        GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
        *tmpTime = *tsoTime;
        theAdvancers[theFederate] = tmpTime;
//      timeAdvanceGrant(theFederate, *tsoTime);
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::flushCalc", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::flushQueueRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              theGeRtiFedTime.getPrintableString(buff);
                              sprintf(galMsg,"Federate=%lu,fedTime=%s", f, buff);
                              E2(GeRti_TM_i,"TokenHolder::flushQueueRequest", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"flushQueueRequest";
  std::auto_ptr<GERTICO::GeRtiFedTime> qlt(geRtiFedTimeFactory.makeZero());
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "fqra", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "fqraa", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "fqre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::RTIinternalError(wChar);
  }
  timeData = itTimeDataMap->second;

  // Test Parameters
  // Not allowed in time advancing state.
  if (timeData->timeAdvancingState == true)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "fqre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeAdvanceAlreadyInProgress(wChar);
  }

  *qlt = *timeData->logicalTime;
  // Time must be equal to or greater than logical time.
  if (qlt.get())
  {
    if (theGeRtiFedTime > *qlt)
    {
      timeData->timePastFlag = false;
    }

    if (theGeRtiFedTime < *qlt)
    {
      pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "fqre", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      throw GeRtiFactory::FederationTimeAlreadyPassed(wChar);
    }
  }

  // Execute function
  setTimeRequested(*timeData, theGeRtiFedTime);

  timeData->timeAdvancingState = true;

  timeData->timeServiceFlag = flushQueueRequestFlag;
  timeData->firstEnableTimeRegulation = false;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "fqrr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  psToken->release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::flushQueueRequest", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Keep a maximum of 10 old TimeData entries.
// ---------------------------------------------------------------------------
// NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::garbageCollection(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::garbageCollection", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;
  size_t size;

  size = timeDataInactiveMap.size();
  if (size < 11)
  {
    return;
  }
  size -= 10;
  for (itTimeDataMap = timeDataInactiveMap.begin(); itTimeDataMap != timeDataInactiveMap.end(); itTimeDataMap = timeDataInactiveMap.begin())
  {
    timeData = itTimeDataMap->second;
    timeDataInactiveMap.erase(itTimeDataMap);
    delete timeData;
    size -= 1;
    if (size == 0)
    {
      break;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::garbageCollection", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::getActualLookahead(GERTICO::TimeData const &theTimeData, GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::getActualLookahead", "Enter");
                           #endif   // inserted by Gal converter
  theLogicalTimeInterval = *theTimeData.actualLookahead;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::getActualLookahead", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Condition where no further messages will arrive for time tg.
// ---------------------------------------------------------------------------
// NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
// ---------------------------------------------------------------------------
bool GERTICO::TokenHolder::g1Condition(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &tg)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::g1Condition", "Enter");
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> bc(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> bo(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> tmp(geRtiFedTimeFactory.makeZero());
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

  bc->setPositiveInfinity();
  bo->setPositiveInfinity();

  // Search through token.
  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
  {
    timeData = itTimeDataMap->second;
    // Non-Time regulating federates are ignored.
    if (timeData->timeRegulation == false)
    {
      continue;
    }
    calcTokenValues(itTimeDataMap->first, *timeData, *timeData->lbts, timeData->lbtsg);

    // Ignore own value.
    if (itTimeDataMap->first != theFederate)
    {
      // Find minimum closed bound.
      if (timeData->lbtsf == false)
      {
        // Take minimum.
        if (*timeData->lbts < *bc)
        {
          *bc = *timeData->lbts;
        }
      }
      // Find minimum open bound.
      if (timeData->lbtsf)
      {
        // Take minimum.
        if (*timeData->lbts < *bo)
        {
          *bo = *itTimeDataMap->second->lbts;
        }
      }
    }
  }

  // Test values.
  bool ret = false;

  char bufftg[1024];
  char buffbo[1024];
  char buffbc[1024];

  tg.getPrintableString(bufftg);
  bo->getPrintableString(buffbo);
  bc->getPrintableString(buffbc);
  if (tg < *bo && tg <= *bc)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::g1Condition", "LeaveA");
                           #endif   // inserted by Gal converter
    itTimeDataMap = timeDataMap.find(theFederate);
    if (itTimeDataMap != timeDataMap.end())
    {
      if (checkGrantCondition(theFederate, *itTimeDataMap->second, tg))
      {
        return ret;
      }
    }

    ret = true;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::g1Condition", "Leave");
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
// Condition where further messages may still arrive for time tg.
// ---------------------------------------------------------------------------
// NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
// ---------------------------------------------------------------------------
bool GERTICO::TokenHolder::g2Condition(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &tg)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::g2Condition", "Enter");
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> b(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> tmpFedTime(geRtiFedTimeFactory.makeZero());
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

  b->setPositiveInfinity();

  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
  {
    // Non-Time regulating federates are ignored.
    if (itTimeDataMap->second->timeRegulation == false)
    {
      continue;
    }
    federates.insert(itTimeDataMap->first);
  }

  // Search through token.
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    itTimeDataMap = timeDataMap.find(*itFederate);
    if (itTimeDataMap == timeDataMap.end())
    {
      continue;
    }
    timeData = itTimeDataMap->second;
    calcTokenValues(*itFederate, *timeData, *timeData->lbts, timeData->lbtsg);

    // Ignore own value.
    if (*itFederate != theFederate)
    {
      // Take minimum.
      if (*timeData->lbts < *b)
      {
        *b = *timeData->lbts;
      }
    }
  }

  // Test values.
  bool ret = false;
  if (tg <= *b)
  {
    ret = true;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::g2Condition", "Enter");
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::getQueryGaltParams(bool const &theFirstEnableTimeRegulation, GERTICO::TimeData const &theTimeData, GERTICO::GeRtiFedTime &theLbts, GERTICO::GeRtiFedTime &theMinLogicalTime, GERTICO::GeRtiLogicalTimeInterval &theMinLookahead, GERTICO::GeRtiFedTime &theMinAdvancingTime, GERTICO::GeRtiFedTime &theMinNotAdvancingTime, bool &theGuaranteedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::getQueryGaltParams", "Enter");
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> tmpFedTime(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> epsilonTime(geRtiLogicalTimeIntervalFactory.epsilon());
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> tmpLookaheadTime(geRtiLogicalTimeIntervalFactory.makeZero());

  // Evaluate lookahead times.
  *tmpLookaheadTime = *theTimeData.actualLookahead;
  if (tmpLookaheadTime.get())
  {
    if (*tmpLookaheadTime < theMinLookahead)
    {
      theMinLookahead = *tmpLookaheadTime;
    }
  }

  // Evaluate logical times.
  *tmpFedTime = *theTimeData.logicalTime;
  if (tmpFedTime.get())
  {
    if (*tmpFedTime < theMinLogicalTime)
    {
      theMinLogicalTime = *tmpFedTime;
    }
  }

  // Check advancing state.
  if (theTimeData.timeAdvancingState)
  {
    // fed i waits for grant - relevant time is lbts
    if (theTimeData.lbtsg == false)
    {
      theGuaranteedTime = false;
    }
    *tmpFedTime = *theTimeData.lbts;
    if (tmpFedTime.get())
    {
      if (*tmpFedTime < theMinAdvancingTime)
      {
        theMinAdvancingTime = *tmpFedTime;
      }
    }
  }
  else
  {
    // fed i not advancing - relevant time is logical time
    *tmpFedTime = *theTimeData.logicalTime;
    if (tmpFedTime.get() && tmpLookaheadTime.get())
    {
      if ((tmpLookaheadTime->isZero()) && !theFirstEnableTimeRegulation)
      {
        // XX Is this correct?
        *tmpLookaheadTime = *epsilonTime;
      }
      *tmpFedTime += *tmpLookaheadTime;
    }
    if (tmpFedTime.get())
    {
      if (*tmpFedTime < theMinNotAdvancingTime)
      {
        theMinNotAdvancingTime = *tmpFedTime;
      }
    }
  }
  if (tmpFedTime.get())
  {
    if (*tmpFedTime < theLbts)
    {
      theLbts = *tmpFedTime;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::getQueryGaltParams", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Special logic: use when GALT is not defined and it is necessary to
// determine the logical time of the leading constrained-only partner.
// Returns either the maximum time of constrained-only partners or the logical
// time of this federate - whichever is higher.
// ---------------------------------------------------------------------------
// NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::getMaxTimeConstrained(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::getMaxTimeConstrained", "Enter");
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> maxTimeConstrained(geRtiFedTimeFactory.makeZero());
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

  // Default return value.
  theFedTime.setPositiveInfinity();

  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
  {
    // Non Time-Constrained-only federates are ignored.
    if ((itTimeDataMap->second->timeConstrained == false) && itTimeDataMap->second->timeRegulation)
    {
      continue;
    }

    federates.insert(itTimeDataMap->first);
  }

  // Check the token values.
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    itTimeDataMap = timeDataMap.find(*itFederate);
    if (itTimeDataMap == timeDataMap.end())
    {
      continue;
    }
    timeData = itTimeDataMap->second;

    // Evaluate logical times.
    if (*itFederate != theFederate)
    {
      if (*timeData->logicalTime > *maxTimeConstrained)
      {
        *maxTimeConstrained = *timeData->logicalTime;
      }
    }
  }

  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap != timeDataMap.end())
  {
    // Do not use a time below the logical time of this federate.
    if (*itTimeDataMap->second->logicalTime > *maxTimeConstrained)
    {
      *maxTimeConstrained = *itTimeDataMap->second->logicalTime;
    }
  }

  theFedTime = *maxTimeConstrained;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::getMaxTimeConstrained", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::joinFederationExecution(GeRtiFactory::GeRtiHandle const &theFederate)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::joinFederationExecution", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::QueryData *queryData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "jfea", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "jfeaa", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    GERTICO::TimeData *timeData;
    timeData = new GERTICO::TimeData(geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
    timeDataMap[theFederate] = timeData;
  }
  pmQuery.acquire();
  queryData = new GERTICO::QueryData(geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
  queryDataMap[theFederate] = queryData;
  pmQuery.release();
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "jfer", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::joinFederationExecution", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Logic for changing lookahead.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::modifyLookahead(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval &theGeRtiFedTime)
       throw (GeRtiFactory::TimeAdvanceAlreadyInProgress,
             GeRtiFactory::InvalidLookahead)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              theGeRtiFedTime.getPrintableString(buff);
                              sprintf(galMsg,"Federate=%lu,fedTime=%s", f, buff);
                              E2(GeRti_TM_i,"TokenHolder::modifyLookahead", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"modifyLookahead";
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> zeroTime(geRtiLogicalTimeIntervalFactory.makeZero());
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "mlha", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "mlhaa", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "mlhe", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::RTIinternalError(wChar);
  }
  timeData = itTimeDataMap->second;

  // Not allowed in time advancing state.
  if (timeData->timeAdvancingState == true)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "mlhe", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeAdvanceAlreadyInProgress(wChar);
  }

  if (theGeRtiFedTime < *zeroTime)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "mlhe", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::InvalidLookahead(wChar);
  }

  // Only have immediate change if theGeRtiFedTime greater than actual lookahead.
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> a(geRtiLogicalTimeIntervalFactory.makeZero());
  queryActualLookahead(theFederate, *a);
  if (a.get())
  {
    if (theGeRtiFedTime > *a)
    {
      setActualLookahead(theFederate, *timeData, theGeRtiFedTime);
    }
  }
  *timeData->requestedLookahead = theGeRtiFedTime;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "mlhr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::modifyLookahead", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::nextEventCalc(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData const &timeData, bool const &available, GERTICO::GeRtiFedTimeMap &theAdvancers)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::nextEventCalc", "Enter");
                           #endif   // inserted by Gal converter
  bool ret;

  if (timeData.timeConstrained)
  {
    // Time advance dependent on other time masters.
    std::auto_ptr<GERTICO::GeRtiFedTime> tsoTime(timeServiceClient.smallestAvailableTSO(theFederate));
    std::auto_ptr<GERTICO::GeRtiFedTime> grantTime(geRtiFedTimeFactory.makeZero());
    *grantTime = *timeData.timeRequested;
    if (tsoTime.get() == NULL)
    {
      tsoTime.reset(geRtiFedTimeFactory.makeZero());
      *tsoTime = *grantTime;
    }
    if (*tsoTime < *grantTime)
    {
      *grantTime = *tsoTime;
    }

    if (available)
    {
      ret = g2Condition(theFederate, *grantTime);
    }
    else
    {
      ret = g1Condition(theFederate, *grantTime);
    }
    if (ret)
    {
      GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
      *tmpTime = *grantTime;
      theAdvancers[theFederate] = tmpTime;
//      timeAdvanceGrant(theFederate, *grantTime);
    }
    else
    {
      std::auto_ptr<GERTICO::GeRtiFedTime> galt(geRtiFedTimeFactory.makeZero());
      queryGALTprivate(theFederate, *galt);

      if (galt->isPositiveInfinity())
      {
        // No limit on time advance.
        GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
        *tmpTime = *grantTime;
        theAdvancers[theFederate] = tmpTime;
//        timeAdvanceGrant(theFederate, *grantTime);
      }
    }
  }
  else
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> tsoTime(timeServiceClient.smallestAvailableTSO(theFederate));
    std::auto_ptr<GERTICO::GeRtiFedTime> qtr(geRtiFedTimeFactory.makeZero());
    *qtr = *timeData.timeRequested;
    if (tsoTime.get() == NULL)
    {
      GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
      *tmpTime = *qtr;
      theAdvancers[theFederate] = tmpTime;
//      timeAdvanceGrant(theFederate, *qtr);
    }
    else
    {
      GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
      *tmpTime = *tsoTime;
      theAdvancers[theFederate] = tmpTime;
//      timeAdvanceGrant(theFederate, *tsoTime);
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::nextEventCalc", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::nextEventRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
  nextEventRequest(theFederate, theGeRtiFedTime, false);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::nextEventRequestAvailable(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
  nextEventRequest(theFederate, theGeRtiFedTime, true);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::nextEventRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime, bool const &avail)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              theGeRtiFedTime.getPrintableString(buff);
                              sprintf(galMsg,"Federate=%lu,fedTime=%s", f, buff);
                              if (avail)
                              {
                                E2(GeRti_TM_i,"TokenHolder::nextEventRequestAvailable", galMsg);
                              }
                              else
                              {
                                E2(GeRti_TM_i,"TokenHolder::nextEventRequest", galMsg);
                              }
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"nextEventRequest";
  std::auto_ptr<GERTICO::GeRtiFedTime> lt(geRtiFedTimeFactory.makeZero());
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;
  bool localAvail = avail;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "nera", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "neraa", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "nere", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::RTIinternalError(wChar);
  }
  timeData = itTimeDataMap->second;

  // Test Parameters
  *lt = *timeData->logicalTime;
  // Time must be equal to or greater than logical time.
  if (lt.get())
  {
    if (theGeRtiFedTime > *lt)
    {
      timeData->timePastFlag = false;
    }

    if (theGeRtiFedTime < *lt)
    {
      pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "nere", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      throw GeRtiFactory::FederationTimeAlreadyPassed(wChar);
    }
  }

  // Not allowed in time advancing state.
  if (timeData->timeAdvancingState == true)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "nere", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::TimeAdvanceAlreadyInProgress(wChar);
  }

  if (avail)
  {
    if (timeData->timePastFlag)
    {
      localAvail = false;
    }
  }

  setTimeRequested(*timeData, theGeRtiFedTime);

  timeData->timeAdvancingState = true;

  if (localAvail)
  {
    timeData->timeServiceFlag = nextEventAvailableFlag;
  }
  else
  {
    timeData->timeServiceFlag = nextEventFlag;
  }
  timeData->firstEnableTimeRegulation = false;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "nerr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  psToken->release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::nextEventRequest", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::numberOfHubs(CORBA::ULong const &theNumberOfHubs)
{
  numberOfPeerHubs = theNumberOfHubs;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::print(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::print", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::TimeDataMap::iterator itTimeDataMap;

  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = itTimeDataMap->first;
                              sprintf(galMsg,"%lu", f);
                              E2(GeRti_TM_d,"Federate=", galMsg);
                              if (itTimeDataMap->second->firstEnableTimeRegulation)
                              {
                                strcpy(galMsg, "TRUE");
                              }
                              else
                              {
                                strcpy(galMsg, "FALSE");
                              }
                              E2(GeRti_TM_d,"firstEnableTimeRegulation", galMsg);
                              if (itTimeDataMap->second->lbtsf)
                              {
                                strcpy(galMsg, "TRUE");
                              }
                              else
                              {
                                strcpy(galMsg, "FALSE");
                              }
                              E2(GeRti_TM_d,"lbtsf", galMsg);
                              if (itTimeDataMap->second->lbtsg)
                              {
                                strcpy(galMsg, "TRUE");
                              }
                              else
                              {
                                strcpy(galMsg, "FALSE");
                              }
                              E2(GeRti_TM_d,"lbtsg", galMsg);
                              if (itTimeDataMap->second->timeAdvancingState)
                              {
                                strcpy(galMsg, "TRUE");
                              }
                              else
                              {
                                strcpy(galMsg, "FALSE");
                              }
                              E2(GeRti_TM_d,"timeAdvancingState", galMsg);
                              if (itTimeDataMap->second->timeConstrained)
                              {
                                strcpy(galMsg, "TRUE");
                              }
                              else
                              {
                                strcpy(galMsg, "FALSE");
                              }
                              E2(GeRti_TM_d,"timeConstrained", galMsg);
                              if (itTimeDataMap->second->timeConstrainedPending)
                              {
                                strcpy(galMsg, "TRUE");
                              }
                              else
                              {
                                strcpy(galMsg, "FALSE");
                              }
                              E2(GeRti_TM_d,"timeConstrainedPending", galMsg);
                              if (itTimeDataMap->second->timePastFlag)
                              {
                                strcpy(galMsg, "TRUE");
                              }
                              else
                              {
                                strcpy(galMsg, "FALSE");
                              }
                              E2(GeRti_TM_d,"timePastFlag", galMsg);
                              if (itTimeDataMap->second->timeRegulation)
                              {
                                strcpy(galMsg, "TRUE");
                              }
                              else
                              {
                                strcpy(galMsg, "FALSE");
                              }
                              E2(GeRti_TM_d,"timeRegulation", galMsg);
                              if (itTimeDataMap->second->timeRegulationPending)
                              {
                                strcpy(galMsg, "TRUE");
                              }
                              else
                              {
                                strcpy(galMsg, "FALSE");
                              }
                              E2(GeRti_TM_d,"timeRegulationPending", galMsg);
                              itTimeDataMap->second->actualLookahead->getPrintableString(galMsg);
                              E2(GeRti_TM_d,"actualLookahead", galMsg);
                              itTimeDataMap->second->lbts->getPrintableString(galMsg);
                              E2(GeRti_TM_d,"lbts", galMsg);
                              itTimeDataMap->second->logicalTime->getPrintableString(galMsg);
                              E2(GeRti_TM_d,"logicalTime", galMsg);
                              itTimeDataMap->second->oldLogicalTime->getPrintableString(galMsg);
                              E2(GeRti_TM_d,"oldLogicalTime", galMsg);
                              itTimeDataMap->second->requestedLookahead->getPrintableString(galMsg);
                              E2(GeRti_TM_d,"requestedLookahead", galMsg);
                              itTimeDataMap->second->timeIntermediateGrant->getPrintableString(galMsg);
                              E2(GeRti_TM_d,"timeIntermediateGrant", galMsg);
                              itTimeDataMap->second->timeRequested->getPrintableString(galMsg);
                              E2(GeRti_TM_d,"timeRequested", galMsg);
                            }
                           #endif   // inserted by Gal converter
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::print", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::process(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::process", "Enter");
                           #endif   // inserted by Gal converter
try
{
  processTimeConstrained();
  processTimeRegulation();
  processGrant();
}
catch(...)
{
//  std::cout << "EXCEPTION " << std::endl;
}
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::processMaster", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::processGrant(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::processGrant", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::GeRtiFedTime *tmpGaltTime;
  GERTICO::GeRtiFedTime *tmpTime;
  std::auto_ptr<GERTICO::GeRtiFedTime> galt(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> infiniteTime(geRtiFedTimeFactory.makeZero());
  GERTICO::GeRtiFedTimeMap advancers;
  GERTICO::GeRtiFedTimeMap intermediateadvancers;
  GERTICO::GeRtiFedTimeMap::iterator itAdvancer;
  GERTICO::GeRtiFedTimeMap::iterator itAdvancerIntermediate;
  GERTICO::QueryData *queryData;
  GERTICO::QueryDataMap::iterator itQueryDataMap;
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;
  bool gotAdvancing = false;
  bool gotZeroLookaheadCondition = true;

  if (notDone == false)
  {
    return;
  }
  infiniteTime->setPositiveInfinity();

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "pga", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "pgaa", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

print();

  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
  {
    timeData = itTimeDataMap->second;

    if (timeData->timeAdvancingState == false)
    {
      continue;
    }

    switch(timeData->timeServiceFlag)
    {
      case idleFlag:
      {
        break;
      }
      case flushQueueRequestFlag:
      {
        flushCalc(itTimeDataMap->first, *timeData, advancers);
        break;
      }
      case nextEventFlag:
      {
        nextEventCalc(itTimeDataMap->first, *timeData, false, advancers);
        break;
      }
      case nextEventAvailableFlag:
      {
        nextEventCalc(itTimeDataMap->first, *timeData, true, advancers);
        break;
      }
      case timeAdvanceFlag:
      {
        timeAdvanceCalc(itTimeDataMap->first, *timeData, false, advancers);
        break;
      }
      case timeAdvanceAvailableFlag:
      {
        timeAdvanceCalc(itTimeDataMap->first, *timeData, true, advancers);
        break;
      }
    }
  }
  pmQuery.acquire();
  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
  {
    // Update galt values.
    queryGALTprivate(itTimeDataMap->first, *galt);
    galt->getPrintableString(buff);
    itQueryDataMap = queryDataMap.find(itTimeDataMap->first);
    if (itQueryDataMap != queryDataMap.end())
    {
      queryData = itQueryDataMap->second;
      *queryData->galt = *galt;
    }
    if (timeData->timeConstrained == false)
    {
      continue;
    }
//    itAdvancer = advancers.find(itTimeDataMap->first);
//    if (itAdvancer == advancers.end())
//    {
//      // Federate gets an hla grant
//      continue;
//    }

    // Test if federate gets an intermediate grant.
    timeData = itTimeDataMap->second;
    if (timeData->timeConstrained)
    {
      if (timeData->timeAdvancingState)
      {
        if (timeData->timeServiceFlag == GERTICO::timeAdvanceFlag || timeData->timeServiceFlag == GERTICO::timeAdvanceAvailableFlag)
        {
          if (*galt > *timeData->timeIntermediateGrant)
          {
            GERTICO::GeRtiFedTime *intermediateTime = geRtiFedTimeFactory.makeZero();
            *intermediateTime = *galt;
            intermediateadvancers[itTimeDataMap->first] = intermediateTime;
          }
        }
      }
    }
  }
  pmQuery.release();
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "pgr", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  // NB: Map deletes first entry and then continues.
  for (itAdvancer = advancers.begin(); itAdvancer != advancers.end(); itAdvancer = advancers.begin())
  {
    tmpTime = itAdvancer->second;
    if (gotZeroLookaheadCondition)
    {
      itAdvancerIntermediate = intermediateadvancers.find(itAdvancer->first);
      if (itAdvancerIntermediate != intermediateadvancers.end())
      {
        tmpGaltTime = itAdvancerIntermediate->second;
        tmpGaltTime->getPrintableString(buff);
        if (tmpGaltTime->isPositiveInfinity())
        {
          timeAdvanceGrant(itAdvancer->first, *tmpTime, *infiniteTime);
        }
        else
        {
          timeAdvanceGrant(itAdvancer->first, *tmpTime, *tmpGaltTime);
        }
        intermediateadvancers.erase(itAdvancerIntermediate);
        delete tmpGaltTime;
      }
      else
      {
        timeAdvanceGrant(itAdvancer->first, *tmpTime, *infiniteTime);
      }
    }
    advancers.erase(itAdvancer);
    delete tmpTime;
  }
  // NB: Map deletes first entry and then continues.
  for (itAdvancerIntermediate = intermediateadvancers.begin(); itAdvancerIntermediate != intermediateadvancers.end(); itAdvancerIntermediate = intermediateadvancers.begin())
  {
    tmpGaltTime = itAdvancerIntermediate->second;
    timeAdvanceGrant(itAdvancerIntermediate->first, *infiniteTime, *tmpGaltTime);
    intermediateadvancers.erase(itAdvancerIntermediate);
    delete tmpGaltTime;
  }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "pga1", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "pgaa1", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
  {
    timeData = itTimeDataMap->second;

    if (timeData->timeAdvancingState)
    {
      gotAdvancing = true;
      break;
    }
  }
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "pgr1", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  if (gotAdvancing)
  {
    psToken->release();
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::processGrant", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::processTimeConstrained(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::processTimeConstrained", "Enter");
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> minLogicalTime(geRtiFedTimeFactory.makeZero());
  GERTICO::GeRtiFedTime *tmp;
  GERTICO::GeRtiFedTimeMap enableTimeConstraineds;
  GERTICO::GeRtiFedTimeMap::iterator itEnableTimeConstrained;
  GERTICO::HandleSet tmpEnableTimeConstrainedIds;
  GERTICO::HandleSet::iterator itEnableTimeConstrainedId;
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;
  GERTICO::TimeDataMap::iterator itTimeDataMinTime;

  if (notDone == false)
  {
    return;
  }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "ptca", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "ptcaa", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  for (itEnableTimeConstrainedId = enableTimeConstrainedIds.begin(); itEnableTimeConstrainedId != enableTimeConstrainedIds.end(); itEnableTimeConstrainedId++)
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> galt(geRtiFedTimeFactory.makeZero());

    itTimeDataMap = timeDataMap.find(*itEnableTimeConstrainedId);
    if (itTimeDataMap == timeDataMap.end())
    {
      timeData = new GERTICO::TimeData(geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
      timeDataMap[*itEnableTimeConstrainedId] = timeData;
      itTimeDataMap = timeDataMap.find(*itEnableTimeConstrainedId);
    }
    timeData = itTimeDataMap->second;

    queryGALTprivate(*itEnableTimeConstrainedId, *galt);
    if (galt->isPositiveInfinity() == false)
    {
      if (*galt < *timeData->logicalTime)
      {
        tmpEnableTimeConstrainedIds.insert(*itEnableTimeConstrainedId);
        continue;
      }
    }

    if (timeData->timeRegulation)
    {
      tmp = geRtiFedTimeFactory.makeZero();
      // Explicitly stated in RTI Version 1.3
      *tmp = *timeData->logicalTime;
      enableTimeConstraineds[*itEnableTimeConstrainedId] = tmp;
      timeConstrainedEnabled(*itEnableTimeConstrainedId, *timeData, *timeData->logicalTime);
      continue;
    }

    tmp = geRtiFedTimeFactory.makeZero();
    // Is this correct?
    *tmp = *timeData->logicalTime;
    enableTimeConstraineds[*itEnableTimeConstrainedId] = tmp;
    timeConstrainedEnabled(*itEnableTimeConstrainedId, *timeData, *timeData->logicalTime);
  }
  enableTimeConstrainedIds.clear();
  enableTimeConstrainedIds = tmpEnableTimeConstrainedIds;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "ptcr", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  for (itEnableTimeConstrained = enableTimeConstraineds.begin(); itEnableTimeConstrained != enableTimeConstraineds.end(); itEnableTimeConstrained++)
  {
    if (numberOfPeerHubs > 1)
    {
      itTimeDataMap = timeDataMap.find(itEnableTimeConstrained->first);
      if (itTimeDataMap != timeDataMap.end())
      {
        timeData = itTimeDataMap->second;
        if (!timeData->localFederate)
        {
          if (timeData->timeConstrainedPendingHubAnswerPeer)
          {
            timeServiceClient.peerTimeConstrainedEnabled(itEnableTimeConstrained->first, *itEnableTimeConstrained->second);
            timeData->timeConstrainedPendingHubAnswerPeer = false;
          }
        }
      }
    }
    else
    {
      timeServiceClient.timeConstrainedEnabled(itEnableTimeConstrained->first, *itEnableTimeConstrained->second);
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::processTimeConstrained", "L");
                           #endif   // inserted by Gal converter
  for (itEnableTimeConstrained = enableTimeConstraineds.begin(); itEnableTimeConstrained != enableTimeConstraineds.end(); itEnableTimeConstrained = enableTimeConstraineds.begin())
  {
    tmp = itEnableTimeConstrained->second;
    enableTimeConstraineds.erase(itEnableTimeConstrained);
    delete tmp;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::processTimeConstrained", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// NB. timeHandler.logicalTime contains requested time.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::processTimeRegulation(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::processTimeRegulation", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::GeRtiFedTime *tmp;
  GERTICO::GeRtiFedTimeMap enableTimeRegulations;
  GERTICO::GeRtiFedTimeMap::iterator itEnableTimeRegulation;
  GERTICO::HandleSet::iterator itEnableTimeRegulationId;
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

  if (notDone == false)
  {
    return;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "ptra", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "ptraa", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  for (itEnableTimeRegulationId = enableTimeRegulationIds.begin(); itEnableTimeRegulationId != enableTimeRegulationIds.end(); itEnableTimeRegulationId++)
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> galt(geRtiFedTimeFactory.makeZero());

    itTimeDataMap = timeDataMap.find(*itEnableTimeRegulationId);
    if (itTimeDataMap == timeDataMap.end())
    {
      continue;
    }

    queryGALTprivate(*itEnableTimeRegulationId, *galt);
    if (galt->isPositiveInfinity())
    {
      // If GALT is not defined, then we do not have any time master
      // partners which are time regulating. To capture a good maximum
      // constrained time we must pause the token and get values from
      // each time constrained federate.
      std::auto_ptr<GERTICO::GeRtiFedTime> maxTimeConstrained(geRtiFedTimeFactory.makeZero());

      getMaxTimeConstrained(*itEnableTimeRegulationId, *maxTimeConstrained);
      if (maxTimeConstrained->isPositiveInfinity())
      {
        GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
        *tmpTime = *itTimeDataMap->second->logicalTime;
        enableTimeRegulations[*itEnableTimeRegulationId] = tmpTime;
        timeRegulationEnabled(*itEnableTimeRegulationId, *itTimeDataMap->second, *itTimeDataMap->second->logicalTime);
      }
      else
      {
        // No time-regulating partners.
        if (*itTimeDataMap->second->logicalTime > *maxTimeConstrained)
        {
          *maxTimeConstrained = *itTimeDataMap->second->logicalTime;
        }
        GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
        *tmpTime = *maxTimeConstrained;
        enableTimeRegulations[*itEnableTimeRegulationId] = tmpTime;
        timeRegulationEnabled(*itEnableTimeRegulationId, *itTimeDataMap->second, *maxTimeConstrained);
      }
    }
    else
    {
      galt->getPrintableString(buff);
      // Time-regulating partners.
      if (*galt < *itTimeDataMap->second->logicalTime)
      {
        GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
        *tmpTime = *itTimeDataMap->second->logicalTime;
        enableTimeRegulations[*itEnableTimeRegulationId] = tmpTime;
        timeRegulationEnabled(*itEnableTimeRegulationId, *itTimeDataMap->second, *itTimeDataMap->second->logicalTime);
      }
      else
      {
        GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
        *tmpTime = *galt;
        subtractLookahead(*itTimeDataMap->second, *tmpTime);
        enableTimeRegulations[*itEnableTimeRegulationId] = tmpTime;
        timeRegulationEnabled(*itEnableTimeRegulationId, *itTimeDataMap->second, *tmpTime);
      }
    }
  }
  enableTimeRegulationIds.clear();
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                            E2(GeRti_TM_mu_d, "ptrr", "");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  for (itEnableTimeRegulation = enableTimeRegulations.begin(); itEnableTimeRegulation != enableTimeRegulations.end(); itEnableTimeRegulation = enableTimeRegulations.begin())
  {
    tmp = itEnableTimeRegulation->second;
    if (numberOfPeerHubs > 1)
    {
      itTimeDataMap = timeDataMap.find(itEnableTimeRegulation->first);
      if (itTimeDataMap != timeDataMap.end())
      {
        timeData = itTimeDataMap->second;
        if (!timeData->localFederate)
        {
          if (timeData->timeRegulationPendingHubAnswerPeer)
          {
            timeServiceClient.peerTimeRegulationEnabled(itEnableTimeRegulation->first, *itEnableTimeRegulation->second);
            timeData->timeRegulationPendingHubAnswerPeer = false;
          }
        }
      }
    }
    else
    {
      timeServiceClient.timeRegulationEnabled(itEnableTimeRegulation->first, *tmp);
    }
    enableTimeRegulations.erase(itEnableTimeRegulation);
    delete tmp;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::processTimeRegulation", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
// NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::queryActualLookahead(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval &theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::queryActualLookahead", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    timeData = new GERTICO::TimeData(geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
    timeDataMap[theFederate] = timeData;
    itTimeDataMap = timeDataMap.find(theFederate);
  }
  timeData = itTimeDataMap->second;

  theTime = *timeData->actualLookahead;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::queryActualLookahead", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::queryGALT(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
  if (theFederate)
  {
                             E2(GeRti_TM_i, "TokenHolder::queryGALT", "Enter");
  }
  else
  {
                             E2(GeRti_TM_d, "TokenHolder::queryGALT", "Enter");
  }
                           #endif   // inserted by Gal converter
  GERTICO::QueryData *queryData;
  GERTICO::QueryDataMap::iterator itQueryDataMap;

  pmQuery.acquire();
  if (theFederate)
  {
    itQueryDataMap = queryDataMap.find(theFederate);
    if (itQueryDataMap != queryDataMap.end())
    {
      queryData = itQueryDataMap->second;
      theTime = *queryData->galt;
    }
  }
  else
  {
    theTime.setPositiveInfinity();
    for (itQueryDataMap = queryDataMap.begin(); itQueryDataMap != queryDataMap.end(); itQueryDataMap++)
    {
      queryData = itQueryDataMap->second;
      if (*queryData->galt < theTime)
      {
        theTime = *queryData->galt;
      }
    }
  }
  pmQuery.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              theTime.getPrintableString(buff);
                              sprintf(galMsg,"Federate=%d,Lookahead=%s", theFederate, buff);
  if (theFederate)
  {
                              E2(GeRti_TM_i, "TokenHolder::queryGALT", galMsg);
  }
  else
  {
                              E2(GeRti_TM_d, "TokenHolder::queryGALT", galMsg);
  }
                            }
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Calculate GALT based on the values stored by the last
// token received.
// ---------------------------------------------------------------------------
// NB: MUST LOCK pm + pmQuery BEFORE CALLING THIS FUNCTION.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::queryGALTprivate(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg,"Federate=%lu", f);
                              E2(GeRti_TM_d,"TokenHolder::queryGALTprivate", galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> lbts(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> minAdvancingTime(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> minLogicalTime(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> minLookahead(geRtiLogicalTimeIntervalFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> minNotAdvancingTime(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> testLbts(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> tmpFedTime(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> epsilonTime(geRtiLogicalTimeIntervalFactory.epsilon());
  std::auto_ptr<GERTICO::GeRtiFedTime> tmp(geRtiFedTimeFactory.makeZero());
  GERTICO::TimeData *timeData;
  GERTICO::TimeData *timeDataFederate;
  GERTICO::TimeDataMap::iterator itTimeDataMap;
  bool b = false;
  bool firstLoop = true;
  bool guaranteedTime = true;

  // Set default.
  theTime.setPositiveInfinity();

  lbts->setPositiveInfinity();
  minLogicalTime->setPositiveInfinity();
  minAdvancingTime->setPositiveInfinity();
  minNotAdvancingTime->setPositiveInfinity();

  if (theFederate)
  {
    itTimeDataMap = timeDataMap.find(theFederate);
    {
      if (itTimeDataMap != timeDataMap.end())
      {
        timeDataFederate = itTimeDataMap->second;
        b = true;
      }
    }
  }
  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
  {
    timeData = itTimeDataMap->second;

    // Non-Time regulating federates are ignored.
    if (timeData->timeRegulation == false)
    {
      continue;
    }

    if (firstLoop)
    {
      *minLookahead = *timeData->actualLookahead;
minLookahead->getPrintableString(buff);
      firstLoop = false;
    }

    if (itTimeDataMap->first != theFederate)
    {
      if (b)
      {
        getQueryGaltParams(timeDataFederate->firstEnableTimeRegulation, *timeData, *lbts, *minLogicalTime, *minLookahead, *minAdvancingTime, *minNotAdvancingTime, guaranteedTime);
minLookahead->getPrintableString(buff);
firstLoop = false;
      }
      else
      {
        getQueryGaltParams(false, *timeData, *lbts, *minLogicalTime, *minLookahead, *minAdvancingTime, *minNotAdvancingTime, guaranteedTime);
minLookahead->getPrintableString(buff);
firstLoop = false;
      }
    }
  }

  if (theFederate != 0)
  {
    itTimeDataMap = timeDataMap.find(theFederate);
    if (itTimeDataMap == timeDataMap.end())
    {
      timeData = new GERTICO::TimeData(geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
      timeDataMap[theFederate] = timeData;
      itTimeDataMap = timeDataMap.find(theFederate);
    }
    timeData = itTimeDataMap->second;

    if (guaranteedTime == false)
    {
      if (minNotAdvancingTime->isPositiveInfinity())
      {
        if (minAdvancingTime->isPositiveInfinity())
        {
          *testLbts = *timeData->logicalTime;
        }
        else
        {
          if (timeData->timeRegulation)
          {
            *testLbts = *timeData->logicalTime;
          }
          else
          {
            *testLbts = *minLogicalTime;
          }
        }
        if (timeData->actualLookahead->isZero())
        {
          *testLbts += *epsilonTime;
        }
        else
        {
          *testLbts += *timeData->actualLookahead;
        }
        *testLbts += *minLookahead;
      }
      else
      {
        if (*timeData->logicalTime < *minNotAdvancingTime)
        {
          *testLbts = *minNotAdvancingTime;
        }
        else
        {
          *testLbts = *timeData->logicalTime;
        }
      }
      if (*testLbts < *lbts)
      {
        *lbts = *testLbts;
      }
    }
  }

  // Evaluate values.
  if (lbts->isPositiveInfinity())
  {
    // No value defined.
    theTime.setPositiveInfinity();
  }
  else
  {
    // Only lbts defined.
    theTime = *lbts;
  }
  theTime.getPrintableString(buff);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::queryGALTprivate", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Calculate LITS based on the values stored by the tokens received
// since the last call to this function.
// NB. reset saveLits before function returns.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::queryLITS(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg,"Federate=%lu", f);
                              E2(GeRti_TM_i,"TokenHolder::queryLITS", galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> galt(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> lits(geRtiFedTimeFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiFedTime> maxFedTime(geRtiFedTimeFactory.makeZero());
  maxFedTime->setPositiveInfinity();

  // Set default.
  theTime = *maxFedTime;

  // Get the timestamp of the local tso.
  lits.reset(timeServiceClient.smallestAvailableTSO(theFederate));

  queryGALTprivate(theFederate, *galt);

  // No value defined.
  if (lits.get() == NULL)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::queryLITS", "LeaveA");
                           #endif   // inserted by Gal converter
    theTime = *galt;
    return;
  }

  // LITS defined.
  if (*galt < *lits)
  {
    theTime = *galt;
  }
  else
  {
    theTime = *lits;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::queryLITS", "LeaveB");
                           #endif   // inserted by Gal converter
  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::queryLogicalTime(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg,"Federate=%lu", f);
                              E2(GeRti_TM_i,"TokenHolder::queryLogicalTime", galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "queryLogicala", galMsg);
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "queryLogicalaa", galMsg);
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    timeData = new GERTICO::TimeData(geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
    timeDataMap[theFederate] = timeData;
    itTimeDataMap = timeDataMap.find(theFederate);
  }
  timeData = itTimeDataMap->second;

  theTime = *timeData->logicalTime;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "queryLogicalr", galMsg);
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::queryLITS", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Return the actual lookahead time.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::queryLookahead(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval& theTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg,"Federate=%lu", f);
                              E2(GeRti_TM_i,"TokenHolder::queryLookahead", galMsg);
                            }
                           #endif   // inserted by Gal converter
  GERTICO::QueryData *queryData;
  GERTICO::QueryDataMap::iterator itQueryDataMap;

  pmQuery.acquire();
  itQueryDataMap = queryDataMap.find(theFederate);
  if (itQueryDataMap != queryDataMap.end())
  {
    queryData = itQueryDataMap->second;
    theTime = *queryData->actualLookahead;
  }
  pmQuery.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              theTime.getPrintableString(buff);
                              sprintf(galMsg,"Lookahead=%s", buff);
                              E2(GeRti_TM_i, "TokenHolder::queryLookahead", buff);
                            }
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::reset(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::resignFederationExecution(GeRtiFactory::GeRtiHandle const &theFederate)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::resignFederationExecution", "Enter");
                           #endif   // inserted by Gal converter
  GERTICO::GeRtiFedTimeMap::iterator itGeRtiFedTimeMap;
  GERTICO::QueryData *queryData;
  GERTICO::QueryDataMap::iterator itQueryDataMap;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "rfea", galMsg);
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "rfeaa", galMsg);
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap != timeDataMap.end())
  {
    timeDataInactiveMap[theFederate] = itTimeDataMap->second;
    timeDataMap.erase(itTimeDataMap);
  }
  garbageCollection();
  pmQuery.acquire();
  itQueryDataMap = queryDataMap.find(theFederate);
  if (itQueryDataMap != queryDataMap.end())
  {
    queryData = itQueryDataMap->second;
    queryDataMap.erase(itQueryDataMap);
    delete queryData;
  }
  pmQuery.release();
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "rfer", galMsg);
                            }
                           #endif   // inserted by Gal converter

  psToken->release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::resignFederationExecution", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::retract(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theHandle)
{
  timeServiceClient.requestRetraction(theFederate, theHandle);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::restore(DOMElement &theDOMElement)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::restore", "Enter");
                           #endif   // inserted by Gal converter
  DOMNode* child;
  DOMNode* subChild;
  GERTICO::TimeData *timeData;
  char *tmpChar;
  unsigned long tmpFederate;

  clear();

  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode(timeFederatesStr.c_str())) == 0)
      {
        for (subChild = child->getFirstChild(); subChild != 0; subChild = subChild->getNextSibling())
        {
          if (subChild->getNodeType() == DOMNode::ELEMENT_NODE)
          {
            if (XMLString::compareString(subChild->getNodeName(),XMLString::transcode(timeFederateStr.c_str())) == 0)
            {
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(idStr.c_str())));
              sscanf(tmpChar, "%lu", &tmpFederate);
              timeData = new GERTICO::TimeData(geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
              timeDataMap[tmpFederate] = timeData;
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(actualLookaheadStr.c_str())));
              GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(geRtiLogicalTimeIntervalFactory, *timeData->actualLookahead, tmpChar);
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(lbtsStr.c_str())));
              GERTICO::ConvertTime::mapGeRtiFedTime(geRtiFedTimeFactory, *timeData->lbts, tmpChar);
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(logicalTimeStr.c_str())));
              GERTICO::ConvertTime::mapGeRtiFedTime(geRtiFedTimeFactory, *timeData->logicalTime, tmpChar);
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(oldLogicalTimeStr.c_str())));
              GERTICO::ConvertTime::mapGeRtiFedTime(geRtiFedTimeFactory, *timeData->oldLogicalTime, tmpChar);
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(lookaheadTimeStr.c_str())));
              GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(geRtiLogicalTimeIntervalFactory, *timeData->requestedLookahead, tmpChar);
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(timeRequestedStr.c_str())));
              GERTICO::ConvertTime::mapGeRtiFedTime(geRtiFedTimeFactory, *timeData->timeRequested, tmpChar);
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(timeServiceStr.c_str())));
              if (strcmp(tmpChar, idleFlagStr.c_str()) == 0)
              {
                timeData->timeServiceFlag = GERTICO::idleFlag;
              }
              else if (strcmp(tmpChar, nextEventFlagStr.c_str()) == 0)
              {
                timeData->timeServiceFlag = GERTICO::nextEventFlag;
              }
              else if (strcmp(tmpChar, nextEventAvailableFlagStr.c_str()) == 0)
              {
                timeData->timeServiceFlag = GERTICO::nextEventAvailableFlag;
              }
              else if (strcmp(tmpChar, timeAdvanceFlagStr.c_str()) == 0)
              {
                timeData->timeServiceFlag = GERTICO::timeAdvanceFlag;
              }
              else if (strcmp(tmpChar, timeAdvanceAvailableFlagStr.c_str()) == 0)
              {
                timeData->timeServiceFlag = GERTICO::timeAdvanceAvailableFlag;
              }
              else if (strcmp(tmpChar, flushQueueRequestFlagStr.c_str()) == 0)
              {
                timeData->timeServiceFlag = GERTICO::flushQueueRequestFlag;
              }
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(firstEnableTimeRegulationStr.c_str())));
              if (strcmp(tmpChar, "1") == 0)
              {
                timeData->firstEnableTimeRegulation = true;
              }
              else
              {
                timeData->firstEnableTimeRegulation = false;
              }
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(lbtsfStr.c_str())));
              if (strcmp(tmpChar, "1") == 0)
              {
                timeData->lbtsf = true;
              }
              else
              {
                timeData->lbtsf = false;
              }
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(lbtsgStr.c_str())));
              if (strcmp(tmpChar, "1") == 0)
              {
                timeData->lbtsg = true;
              }
              else
              {
                timeData->lbtsg = false;
              }
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(advancingStateStr.c_str())));
              if (strcmp(tmpChar, "1") == 0)
              {
                timeData->timeAdvancingState = true;
              }
              else
              {
                timeData->timeAdvancingState = false;
              }
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(timeConstrainedStr.c_str())));
              if (strcmp(tmpChar, "1") == 0)
              {
                timeData->timeConstrained = true;
              }
              else
              {
                timeData->timeConstrained = false;
              }
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(timeConstrainedPendingStr.c_str())));
              if (strcmp(tmpChar, "1") == 0)
              {
                timeData->timeConstrainedPending = true;
              }
              else
              {
                timeData->timeConstrainedPending = false;
              }
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(timePastFlagStr.c_str())));
              if (strcmp(tmpChar, "1") == 0)
              {
                timeData->timePastFlag = true;
              }
              else
              {
                timeData->timePastFlag = false;
              }
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(timeRegulationStr.c_str())));
              if (strcmp(tmpChar, "1") == 0)
              {
                timeData->timeRegulation = true;
              }
              else
              {
                timeData->timeRegulation = false;
              }
              tmpChar = XMLString::transcode(((DOMElement*)subChild)->getAttribute(XMLString::transcode(timeRegulationPendingStr.c_str())));
              if (strcmp(tmpChar, "1") == 0)
              {
                timeData->timeRegulationPending = true;
              }
              else
              {
                timeData->timeRegulationPending = false;
              }
            }
          }
        }
      }
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::restore", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::save", "Enter");
                           #endif   // inserted by Gal converter
  DOMElement *elemLevel1;
  DOMElement* elemLevel2;
  GERTICO::TimeDataMap::iterator itTimeDataMap;
  XMLCh tempStr[128];
  XMLCh tempStr1[128];
  char buf[128];
  unsigned long ul;

  // Time Data
  XMLString::transcode(timeFederatesStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel1);

  for (itTimeDataMap = timeDataMap.begin(); itTimeDataMap != timeDataMap.end(); itTimeDataMap++)
  {
    // Federate Label
    XMLString::transcode(timeFederateStr.c_str(), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);

    // Federate id attribute
    XMLString::transcode(idStr.c_str(), tempStr, 99);
    ul = itTimeDataMap->first;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Actual Lookahead attribute
    XMLString::transcode(actualLookaheadStr.c_str(), tempStr, 99);
    GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(buf, *itTimeDataMap->second->actualLookahead);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Lbts attribute
    XMLString::transcode(lbtsStr.c_str(), tempStr, 99);
    GERTICO::ConvertTime::mapGeRtiFedTime(buf, *itTimeDataMap->second->lbts);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Logical Time attribute
    XMLString::transcode(logicalTimeStr.c_str(), tempStr, 99);
    GERTICO::ConvertTime::mapGeRtiFedTime(buf, *itTimeDataMap->second->logicalTime);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Old Logical Time attribute
    XMLString::transcode(oldLogicalTimeStr.c_str(), tempStr, 99);
    GERTICO::ConvertTime::mapGeRtiFedTime(buf, *itTimeDataMap->second->oldLogicalTime);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Lookahead attribute
    XMLString::transcode(lookaheadTimeStr.c_str(), tempStr, 99);
    GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(buf, *itTimeDataMap->second->requestedLookahead);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Lookahead attribute
    XMLString::transcode(timeRequestedStr.c_str(), tempStr, 99);
    GERTICO::ConvertTime::mapGeRtiFedTime(buf, *itTimeDataMap->second->timeRequested);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Time service flag attribute
    XMLString::transcode(timeServiceStr.c_str(), tempStr, 99);
    switch (itTimeDataMap->second->timeServiceFlag)
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
    elemLevel2->setAttribute(tempStr, tempStr1);

    // First enable time regulation attribute
    XMLString::transcode(firstEnableTimeRegulationStr.c_str(), tempStr, 99);
    if (itTimeDataMap->second->firstEnableTimeRegulation)
    {
      strcpy(buf, "1");
    }
    else
    {
      strcpy(buf, "0");
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Lbtsf attribute
    XMLString::transcode(lbtsfStr.c_str(), tempStr, 99);
    if (itTimeDataMap->second->lbtsf)
    {
      strcpy(buf, "1");
    }
    else
    {
      strcpy(buf, "0");
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Lbtsg attribute
    XMLString::transcode(lbtsgStr.c_str(), tempStr, 99);
    if (itTimeDataMap->second->lbtsg)
    {
      strcpy(buf, "1");
    }
    else
    {
      strcpy(buf, "0");
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Advancing attribute
    XMLString::transcode(advancingStateStr.c_str(), tempStr, 99);
    if (itTimeDataMap->second->timeAdvancingState)
    {
      strcpy(buf, "1");
    }
    else
    {
      strcpy(buf, "0");
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Federate constrained attribute
    XMLString::transcode(timeConstrainedStr.c_str(), tempStr, 99);
    if (itTimeDataMap->second->timeConstrained)
    {
      strcpy(buf, "1");
    }
    else
    {
      strcpy(buf, "0");
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Time constrained pending attribute
    XMLString::transcode(timeConstrainedPendingStr.c_str(), tempStr, 99);
    if (itTimeDataMap->second->timeConstrainedPending)
    {
      strcpy(buf, "1");
    }
    else
    {
      strcpy(buf, "0");
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Time past flag attribute
    XMLString::transcode(timePastFlagStr.c_str(), tempStr, 99);
    if (itTimeDataMap->second->timePastFlag)
    {
      strcpy(buf, "1");
    }
    else
    {
      strcpy(buf, "0");
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Time regulation attribute
    XMLString::transcode(timeRegulationStr.c_str(), tempStr, 99);
    if (itTimeDataMap->second->timeRegulation)
    {
      strcpy(buf, "1");
    }
    else
    {
      strcpy(buf, "0");
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Time regulation pending attribute
    XMLString::transcode(timeRegulationPendingStr.c_str(), tempStr, 99);
    if (itTimeDataMap->second->timeRegulationPending)
    {
      strcpy(buf, "1");
    }
    else
    {
      strcpy(buf, "0");
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::save", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::setActualLookahead(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData &theTimeData, GERTICO::GeRtiLogicalTimeInterval const &theGeRtiFedTimeInterval)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::setActualLookahead", "Enter");
                           #endif   // inserted by Gal converter
std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> tmpTime(geRtiLogicalTimeIntervalFactory.makeZero());
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> zeroTime(geRtiLogicalTimeIntervalFactory.makeZero());
  GERTICO::QueryData *queryData;
  GERTICO::QueryDataMap::iterator itQueryDataMap;

  if (theGeRtiFedTimeInterval < *zeroTime)
  {
    *theTimeData.actualLookahead = *zeroTime;
  }
  else
  {
    *theTimeData.actualLookahead = theGeRtiFedTimeInterval;
  }
theTimeData.actualLookahead->getPrintableString(buff);
char cuff[512];
*tmpTime = theGeRtiFedTimeInterval;
tmpTime->getPrintableString(cuff);
  pmQuery.acquire();
  itQueryDataMap = queryDataMap.find(theFederate);
  if (itQueryDataMap != queryDataMap.end())
  {
    queryData = itQueryDataMap->second;
    *queryData->actualLookahead = *theTimeData.actualLookahead;
  }
  pmQuery.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::setActualLookahead", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::setLogicalTime(GERTICO::TimeData &theTimeData, GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::setLogicalTime", "Enter");
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> zeroTime(geRtiFedTimeFactory.makeZero());

  if (theGeRtiFedTime < *zeroTime)
  {
    *theTimeData.logicalTime = *zeroTime;
  }
  else
  {
    *theTimeData.logicalTime = theGeRtiFedTime;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::setLogicalTime", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::setTimeRequested(GERTICO::TimeData &theTimeData, GERTICO::GeRtiFedTime const &l)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::setTimeRequested", "Enter");
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiFedTime> zeroTime(geRtiFedTimeFactory.makeZero());

  if (l < *zeroTime)
  {
    *theTimeData.timeRequested = *zeroTime;
  }
  else
  {
    *theTimeData.timeRequested = l;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::setTimeRequested", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::subtractLookahead(GERTICO::TimeData const &theTimeData, GERTICO::GeRtiFedTime &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::subtractLookahead", "Enter");
                           #endif   // inserted by Gal converter
char abuff[512];
char cbuff[512];
theTimeData.actualLookahead->getPrintableString(abuff);
  theFedTime -= *theTimeData.actualLookahead;

  if (theFedTime < *theTimeData.logicalTime)
  {
    theFedTime = *theTimeData.logicalTime;
  }
theFedTime.getPrintableString(cbuff);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::subtractLookahead", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::terminate(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::terminate", "Enter");
                           #endif   // inserted by Gal converter
  notDone = false;

  psToken->release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::terminate", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::timeAdvanceCalc(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData const &timeData, bool const &available, GERTICO::GeRtiFedTimeMap &theAdvancers)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::timeAdvanceCalc", "Enter");
                           #endif   // inserted by Gal converter
  bool ret;

  if (timeData.timeConstrained)
  {
    // Time advance dependent on other time masters.
    if (available)
    {
      ret = g2Condition(theFederate, *timeData.timeRequested);
    }
    else
    {
      ret = g1Condition(theFederate, *timeData.timeRequested);
    }
    if (ret)
    {
      GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
      *tmpTime = *timeData.timeRequested;
      theAdvancers[theFederate] = tmpTime;
      tmpTime->getPrintableString(buff);
//        timeAdvanceGrant(theFederate, *qtr);
    }
    else
    {
      std::auto_ptr<GERTICO::GeRtiFedTime> galt(geRtiFedTimeFactory.makeZero());
      queryGALTprivate(theFederate, *galt);
      if (galt->isPositiveInfinity())
      {
        // No limit on time advance.
        GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
        *tmpTime = *timeData.timeRequested;
        theAdvancers[theFederate] = tmpTime;
        tmpTime->getPrintableString(buff);
//          timeAdvanceGrant(theFederate, *qtr);
      }
    }
  }
  else
  {
    // No limit on time advance.
    GERTICO::GeRtiFedTime *tmpTime = geRtiFedTimeFactory.makeZero();
    *tmpTime = *timeData.timeRequested;
    theAdvancers[theFederate] = tmpTime;
    tmpTime->getPrintableString(buff);
//    timeAdvanceGrant(theFederate, *qtr);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "TokenHolder::timeAdvanceCalc", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::timeAdvanceGrant(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              theGeRtiFedTime.getPrintableString(buff);
                              sprintf(galMsg,"Federate=%lu,fedTime=%s", f, buff);
                              E2(GeRti_TM_i,"TokenHolder::timeAdvanceGrant", galMsg);
                            }
                           #endif   // inserted by Gal converter
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> tmpTime(geRtiLogicalTimeIntervalFactory.makeZero());
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "taga", galMsg);
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "tagaa", galMsg);
                            }
                           #endif   // inserted by Gal converter
  timeServiceClient.timeAdvanceGrant(theFederate, theGeRtiFedTime, theGaltGeRtiFedTime);

//  pm.acquire();
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    timeData = new GERTICO::TimeData(geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
    timeDataMap[theFederate] = timeData;
    itTimeDataMap = timeDataMap.find(theFederate);
  }
  timeData = itTimeDataMap->second;

  if (theGeRtiFedTime.isPositiveInfinity() == false)
  {
    setLogicalTime(*timeData, theGeRtiFedTime);
  }

  switch (timeData->timeServiceFlag)
  {
    case nextEventFlag:
    {
      timeData->timePastFlag = true;
      break;
    }
    case timeAdvanceFlag:
    {
      timeData->timePastFlag = true;
      break;
    }
  }

  if (theGeRtiFedTime.isPositiveInfinity() == false)
  {
    // Slowly adapt the actualLookahead to requestedLookahead.
    std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> a(geRtiLogicalTimeIntervalFactory.makeZero());
    queryActualLookahead(theFederate, *a);

    if (*timeData->requestedLookahead < *a)
    {
      tmpTime = theGeRtiFedTime - *timeData->oldLogicalTime;
      if (*a < *tmpTime)
      {
        setActualLookahead(theFederate, *timeData, *timeData->requestedLookahead);
      }
      else
      {
        *a -= *tmpTime;
        if (*a < *timeData->requestedLookahead)
        {
          *a = *timeData->requestedLookahead;
        }
        setActualLookahead(theFederate, *timeData, *a);
      }
    }
  }

#ifdef AdjustSleepTimeDEBUG
E1(tAG2,suggestSleepDelta);
#endif

  if (theGeRtiFedTime.isPositiveInfinity() == false)
  {
    *timeData->oldLogicalTime = theGeRtiFedTime;
    timeData->timeAdvancingState = false;
  }
  if (theGaltGeRtiFedTime.isPositiveInfinity() == false)
  {
    *timeData->timeIntermediateGrant = theGaltGeRtiFedTime;
  }
  timeData->firstEnableTimeRegulation = false;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "tagr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::timeAdvanceGrant", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::timeAdvanceRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
  timeAdvanceRequest(theFederate, theGeRtiFedTime, false);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::timeAdvanceRequestAvailable(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
  timeAdvanceRequest(theFederate, theGeRtiFedTime, true);
}

// ---------------------------------------------------------------------------
// Accept the call from the client within the client
// thread and store the values. The TAG will be answered
// by another thread so that the client will not be
// blocked by a callback in the client thread.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::timeAdvanceRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime, bool const &avail)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              theGeRtiFedTime.getPrintableString(buff);
                              sprintf(galMsg,"Federate=%lu,fedTime=%s", f, buff);
                              E2(GeRti_TM_i,"TokenHolder::timeAdvanceRequest", galMsg);
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *wChar = L"GeRti";
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;
  bool localAvail = avail;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "tara", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  pm.acquire();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "taraa", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap == timeDataMap.end())
  {
    timeData = new GERTICO::TimeData(geRtiFedTimeFactory, geRtiLogicalTimeIntervalFactory);
    timeDataMap[theFederate] = timeData;
    itTimeDataMap = timeDataMap.find(theFederate);
  }
  timeData = itTimeDataMap->second;

  // Not allowed in time advancing state.
//  if (timeData->timeAdvancingState == true)
//  {
//    pm.release();
//                           #ifdef GalDebug   // inserted by Gal converter
//                            E1mBegin(GeRti_TM_mu_d)
//                            {
//                              static char galMsg[512];
//                              unsigned long f;
//
//                              f = theFederate;
//                              sprintf(galMsg, "federate=%lu", f);
//                              E2(GeRti_TM_mu_d, "tare", galMsg);   // inserted by Gal converter
//                            }
//                           #endif   // inserted by Gal converter
//    throw GeRtiFactory::TimeAdvanceAlreadyInProgress(wChar);
//  }

  if (theGeRtiFedTime > *timeData->logicalTime)
  {
    timeData->timePastFlag = false;
  }

  if (theGeRtiFedTime < *timeData->logicalTime)
  {
    pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "tare", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
#ifdef IEEE_1516
    throw GeRtiFactory::InvalidFederationTime(wChar);
#else
    throw GeRtiFactory::FederationTimeAlreadyPassed(wChar);
#endif
  }

  if (localAvail && timeData->timePastFlag)
  {
    localAvail = false;
  }

  setTimeRequested(*timeData, theGeRtiFedTime);

  if (localAvail)
  {
    timeData->timeServiceFlag = timeAdvanceAvailableFlag;
  }
  else
  {
    timeData->timeServiceFlag = timeAdvanceFlag;
  }

  timeData->firstEnableTimeRegulation = false;

  timeData->timeAdvancingState = true;
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_mu_d)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              sprintf(galMsg, "federate=%lu", f);
                              E2(GeRti_TM_mu_d, "tarr", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  psToken->release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::timeAdvanceRequest", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
// NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::timeConstrainedEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData &theTimeData, GERTICO::GeRtiFedTime &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::timeConstrainedEnabled", "Enter");
                           #endif   // inserted by Gal converter
  theTimeData.timeConstrained = true;
  theTimeData.timeConstrainedPending = false;
  *theTimeData.oldLogicalTime = theFedTime;
  setLogicalTime(theTimeData, theFedTime);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::timeConstrainedEnabled", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
// NB: MUST LOCK pm BEFORE CALLING THIS FUNCTION.
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::timeRegulationEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::TimeData &theTimeData, GERTICO::GeRtiFedTime &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_i)
                            {
                              static char galMsg[512];
                              unsigned long f;

                              f = theFederate;
                              theFedTime.getPrintableString(buff);
                              sprintf(galMsg,"Federate=%lu,fedTime=%s", f, buff);
                              E2(GeRti_TM_i,"TokenHolder::timeRegulationEnabled", galMsg);
                            }
                           #endif   // inserted by Gal converter
  theTimeData.timeRegulation = true;
  theTimeData.timeRegulationPending = false;
  *theTimeData.oldLogicalTime = theFedTime;
  setLogicalTime(theTimeData, theFedTime);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_i, "TokenHolder::timeRegulationEnabled", "Leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::timeConstrainedPeerEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theTime)
{
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap != timeDataMap.end())
  {
    timeData = itTimeDataMap->second;
    if (theTime > *timeData->logicalTime)
    {
      setLogicalTime(*timeData, theTime);
    }
    timeData->numberOfPeerHubsReply++;
    if (timeData->numberOfPeerHubsReply == numberOfPeerHubs -1)
    {
      timeServiceClient.timeConstrainedEnabled(theFederate, *timeData->logicalTime);
      timeData->numberOfPeerHubsReply = 0;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TokenHolder::timeRegulationPeerEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theTime)
{
  GERTICO::TimeData *timeData;
  GERTICO::TimeDataMap::iterator itTimeDataMap;

  itTimeDataMap = timeDataMap.find(theFederate);
  if (itTimeDataMap != timeDataMap.end())
  {
    timeData = itTimeDataMap->second;
    if (theTime > *timeData->logicalTime)
    {
      setLogicalTime(*timeData, theTime);
    }
    timeData->numberOfPeerHubsReply++;
    if (timeData->numberOfPeerHubsReply == numberOfPeerHubs -1)
    {
      timeServiceClient.timeRegulationEnabled(theFederate, *timeData->logicalTime);
      timeData->numberOfPeerHubsReply = 0;
    }
  }
}