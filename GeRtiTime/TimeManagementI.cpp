/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** TimeManagementI.cpp
**
*******************************************************************************/

#include "TimeManagementI.h"
#include "Util/ConvertTime.h"

/********************************* Gal begin ************************************/

#ifdef GalDebug

#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

static class Repository_l *TM=(Repository::getSingleInstance())->getRepository_l("GeRtiTM.res","GeRtiTM");

static class Event *GeRti_TM_d=TM->getRefEvent("GeRti_TM_d");
static class Event *GeRti_TM_e=TM->getRefEvent("GeRti_TM_e");
static class Event *GeRti_TM_i=TM->getRefEvent("GeRti_TM_i");
static class Event *GeRti_TM_w=TM->getRefEvent("GeRti_TM_w");

#endif

/********************************* Gal end ************************************/

static char galMsg[512];

//******************************************************
//
GeRti_TimeManagement_i::GeRti_TimeManagement_i(PortableServer::POA_ptr thePOA, GERTICO::TimeService &theTimeService, GERTICO::GeRtiFedTimeFactory *theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory *theGeRtiLogicalTimeIntervalFactory) : timeService(theTimeService)
{
  myPOA = PortableServer::POA::_duplicate(thePOA);
  geRtiFedTimeFactory = theGeRtiFedTimeFactory;
  geRtiLogicalTimeIntervalFactory = theGeRtiLogicalTimeIntervalFactory;
}

//******************************************************
//
GeRti_TimeManagement_i::~GeRti_TimeManagement_i()
{
}

PortableServer::POA_ptr GeRti_TimeManagement_i::_default_POA (void)
{
  return PortableServer::POA::_duplicate(myPOA);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRti_TimeManagement_i::disableTimeConstrained (
  GeRtiFactory::GeRtiHandle theFederate)
throw (
  CORBA::SystemException,
  GeRtiFactory::TimeConstrainedWasNotEnabled,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError,
  GeRtiFactory::ConcurrentAccessAttempted
)
{
  timeService.disableTimeConstrained(theFederate);
  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRti_TimeManagement_i::disableTimeRegulation(GeRtiFactory::GeRtiHandle theFederate)
throw (
  CORBA::SystemException,
  GeRtiFactory::TimeRegulationIsNotEnabled,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
  timeService.disableTimeRegulation(theFederate);
  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRti_TimeManagement_i::queryGALT (
  GeRtiFactory::GeRtiHandle theFederate,
  GeRtiFactory::Time_out theTime
)
throw (
  CORBA::SystemException,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> fedTime(geRtiFedTimeFactory->makeZero());

  timeService.queryGALT(theFederate, *fedTime);
  theTime = new GeRtiFactory::Time();
  GERTICO::ConvertTime::mapIt(*theTime, *fedTime);
  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRti_TimeManagement_i::queryLITS (
  GeRtiFactory::GeRtiHandle theFederate,
  GeRtiFactory::Time_out theTime
)
throw (
  CORBA::SystemException,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
  std::auto_ptr<GERTICO::GeRtiFedTime> fedTime(geRtiFedTimeFactory->makeZero());

  timeService.queryLITS(theFederate, *fedTime);
  theTime = new GeRtiFactory::Time();
  GERTICO::ConvertTime::mapIt(*theTime, *fedTime);
  return;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRti_TimeManagement_i::queryLookahead (
  GeRtiFactory::GeRtiHandle theFederate,
  GeRtiFactory::Time_out theTime
)
throw (
  CORBA::SystemException,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> logicalTimeInterval(geRtiLogicalTimeIntervalFactory->makeZero());

  timeService.queryLookahead(theFederate, *logicalTimeInterval);
  theTime = new GeRtiFactory::Time();
  GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(*theTime, *logicalTimeInterval);
  return;
}
