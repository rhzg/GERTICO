/*******************************************************************************
**
** Copyright (c) Fraunhofer IOBB
** All rights reserved.
**
** TimeClient.cpp
**
*******************************************************************************/

#include "TimeClient.h"

// ---------------------------------------------------------------------------
//
// This is only a minimum implementation of a class to allow
// a test of the callback logic.
// ---------------------------------------------------------------------------
//GERTICO::TimeClient::TimeClient(GERTICO::FederatesHolder &theFederatesHolder, GERTICO::GeRtiFedTimeFactory *theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory *theGeRtiLogicalTimeIntervalFactory) : federatesHolder(theFederatesHolder)
GERTICO::TimeClient::TimeClient(GERTICO::GeRtiFedTimeFactory *theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory *theGeRtiLogicalTimeIntervalFactory)
{
  eventHandler = NULL;
  nextSaveTime = NULL;
  saveInProgress = false;
  saveRequested = false;
  logicalTime = NULL;

  geRtiFedTimeFactory = theGeRtiFedTimeFactory;
  geRtiLogicalTimeIntervalFactory = theGeRtiLogicalTimeIntervalFactory;

  logicalTime = geRtiFedTimeFactory->makeZero();
}

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
GERTICO::TimeClient::~TimeClient ()
{
  if (nextSaveTime)
  {
    delete nextSaveTime;
    nextSaveTime = NULL;
  }
  if (logicalTime)
  {
    delete logicalTime;
    logicalTime = NULL;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeClient::peerTimeConstrainedEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime)
{
  eventHandler->peerTimeConstrainedEnabled(theFederate, theGaltGeRtiFedTime);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeClient::peerTimeRegulationEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime)
{
  eventHandler->peerTimeRegulationEnabled(theFederate, theGaltGeRtiFedTime);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeClient::getSaveValues(bool &theSave, GERTICO::GeRtiFedTime &theTime)
{
  if (saveInProgress || saveRequested)
  {
    theSave = true;
  }
  else
  {
    theSave = false;
  }

  if (nextSaveTime)
  {
    theTime = *nextSaveTime;
  }
  else
  {
    theTime.setPositiveInfinity();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeClient::initiateFederateSave(void)
{
  saveInProgress = true;
  saveRequested = false;
}

// ---------------------------------------------------------------------------
// Gerti events are all incoming/outgoing.
// ---------------------------------------------------------------------------
GERTICO::GeRtiFedTime *GERTICO::TimeClient::smallestAvailableTSO(GeRtiFactory::GeRtiHandle const &theFederate)
{
  GERTICO::GeRtiFedTime *d = geRtiFedTimeFactory->makeZero();
  GERTICO::GeRtiFedTime *smallestFedTime = geRtiFedTimeFactory->makeZero();

  smallestFedTime->setPositiveInfinity();

  if (eventHandler)
  {
    eventHandler->getMinTimeStamp(theFederate, *d);
  }

  if (*d < *smallestFedTime)
  {
    *smallestFedTime = *d;
  }

  if (nextSaveTime)
  {
    if (*nextSaveTime < *smallestFedTime)
    {
      *smallestFedTime = *nextSaveTime;
    }
  }

  if (smallestFedTime->isPositiveInfinity())
  {
    delete smallestFedTime;
    smallestFedTime = NULL;
  }

  if (d)
  {
    delete d;
  }

  return smallestFedTime;
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::TimeClient::requestRetraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theHandle)
{
  eventHandler->requestRetraction(theFederate, theHandle);
}

// ---------------------------------------------------------------------------
// This is only a minimum implementation of this method.
// ---------------------------------------------------------------------------
void GERTICO::TimeClient::timeAdvanceGrant(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::GeRtiFedTime &theTime, GERTICO::GeRtiFedTime &theGaltTime)
{
//  GERTICO::Federate *currFederate;

//  currFederate = federatesHolder.getFederate(theFederate);
//  if (currFederate)
//  {
    eventHandler->timeAdvanceGrant(theFederate, theTime, theGaltTime);
//    currFederate->setAlive();
//  }
}

// ---------------------------------------------------------------------------
// This is only a minimum implementation of this method.
// ---------------------------------------------------------------------------
void GERTICO::TimeClient::timeConstrainedEnabled(const GeRtiFactory::GeRtiHandle &theFederate, const GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
//  GERTICO::Federate *currFederate;

//  currFederate = federatesHolder.getFederate(theFederate);
//  if (currFederate)
//  {
    eventHandler->timeConstrainedEnabled(theFederate, theGeRtiFedTime);
//    currFederate->setAlive();
//  }
}

// ---------------------------------------------------------------------------
// This is only a minimum implementation of this method.
// ---------------------------------------------------------------------------
void GERTICO::TimeClient::timeRegulationEnabled(const GeRtiFactory::GeRtiHandle &theFederate, const GERTICO::GeRtiFedTime &theTime)
{
//  GERTICO::Federate *currFederate;

//  currFederate = federatesHolder.getFederate(theFederate);
//  if (currFederate)
//  {
    eventHandler->timeRegulationEnabled(theFederate, theTime);
//    currFederate->setAlive();
//  }
}


