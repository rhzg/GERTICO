/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** TimeClient.h
**
*******************************************************************************/


// -*- C++ -*-
//
// $Id: TimeClient.h,v 1.25 2010/05/17 08:13:53 mul Exp $

#ifndef TimeClient_H_
#define TimeClient_H_

#include "ace/Synch.h"
// SISA RCI Socket
#include "EventMarket/EventHandler.h"
#include "GeRtiTime/TimeServiceClient.h"

namespace GERTICO
{
  class TimeClient : public virtual TimeServiceClient
  {
//    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::GeRtiFedTime *logicalTime;

  public:
    EventHandler *eventHandler;
    GERTICO::GeRtiFedTime *nextSaveTime;
    bool saveInProgress;
    bool saveRequested;
    std::wstring nextSaveName;

    //Constructor
//    TimeClient(GERTICO::FederatesHolder &theFederatesHolder, GERTICO::GeRtiFedTimeFactory *theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory *theGeRtiLogicalTimeIntervalFactory);
    TimeClient(GERTICO::GeRtiFedTimeFactory *theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory *theGeRtiLogicalTimeIntervalFactory);

    //Destructor
    virtual ~TimeClient(void);

    void timeConstrainedEnabled(const GeRtiFactory::GeRtiHandle &theFederate, const GERTICO::GeRtiFedTime &theGeRtiFedTime);

    // Callback from primary time master.
    // Get status of save request from primary time master client.
    void getSaveValues(bool &theSave, GERTICO::GeRtiFedTime &theTime);

    // Used by primary time master client.
    void initiateFederateSave(void);

    virtual void peerTimeConstrainedEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime);

    virtual void peerTimeRegulationEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime);

    // Callback from time master.
    // Get smallest available timestamp order from the client application.
    GERTICO::GeRtiFedTime *smallestAvailableTSO(GeRtiFactory::GeRtiHandle const &theFederate);

    void requestRetraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theHandle);

    // Callback from time master.
    // Time advance grant to the client application.
    void timeAdvanceGrant(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::GeRtiFedTime &theTime, GERTICO::GeRtiFedTime &theGaltTime);

    // Callback from time master.
    // Time regulation enabled to the client application.
    void timeRegulationEnabled(const GeRtiFactory::GeRtiHandle &theFederate, const GERTICO::GeRtiFedTime &theTime);
  };
};

#endif /* TimeClient_H_  */
