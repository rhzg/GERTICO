/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** TimeServiceClient.h
**
*******************************************************************************/

#ifndef TimeServiceClient_H_
#define TimeServiceClient_H_

#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiFedTime.h"

class TimeServiceClient
{
public:
  GERTICO::GeRtiFedTimeFactory *geRtiFedTimeFactory;
  GERTICO::GeRtiLogicalTimeIntervalFactory *geRtiLogicalTimeIntervalFactory;

  virtual ~TimeServiceClient () { ; };

  virtual void timeConstrainedEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &theGeRtiFedTime) = 0;

  virtual void getSaveValues(bool &theSave, GERTICO::GeRtiFedTime &theTime) { ; };

  virtual void peerTimeConstrainedEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime) = 0;

  virtual void peerTimeRegulationEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime) = 0;

  virtual GERTICO::GeRtiFedTime *smallestAvailableTSO(GeRtiFactory::GeRtiHandle const &theFederate) = 0;

  virtual void requestRetraction(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theHandle) = 0;

  virtual void timeAdvanceGrant(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime, GERTICO::GeRtiFedTime &theGaltGeRtiFedTime) = 0;

  virtual void timeRegulationEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &theGeRtiFedTime) = 0;
};

#endif /* TimeServiceClient_H_  */
