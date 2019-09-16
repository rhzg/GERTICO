/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: TimeService.h,v $
Revision 1.27  2010/05/17 08:12:02  mul
Add logical time interval.

Revision 1.26  2009/05/07 12:46:13  mul
Changes for removing token logic in time management.

Revision 1.25  2007/09/06 09:05:02  mul
Changes for ieee1516.

Revision 1.24  2007/05/09 13:26:54  mul
use generic time.

Revision 1.23  2006/08/08 14:21:13  mul
Changes for mom testcases.

Revision 1.22  2006/04/19 14:20:01  mul
Extensions for MOM.

Revision 1.21  2006/02/08 14:15:36  mul
Remove some methods.

Revision 1.20  2005/09/07 12:28:10  mul
Remove name service. Change name scoping.

Revision 1.19  2005/05/03 14:25:34  mul
An external thread activates watchdog cyclically.

Revision 1.18  2005/04/08 09:37:47  mul
Functions to get times for constrained-only federates.

Revision 1.17  2005/02/07 10:32:54  mul
Changed time management structure.

Revision 1.16  2004/12/14 10:53:00  mul
Clean up.

Revision 1.15  2004/11/22 13:25:25  mul
Remove redundant function.

Revision 1.14  2004/09/24 07:37:08  mul
Minor changes.

Revision 1.13  2004/03/17 13:28:54  mul
Add flush queue request.

Revision 1.12  2003/10/10 13:31:36  mul
New ORB init logic.

Revision 1.11  2003/07/15 14:29:21  mul
Changes for RTI::FedTime.

Revision 1.10  2002/11/18 08:59:27  mul
Add some debugging information.

Revision 1.9  2002/10/21 13:05:01  mul
Change logic to clean up CORBA objects.

Revision 1.8  2002/07/16 08:57:21  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen


**
*******************************************************************************/


// -*- C++ -*-
//
// $Id: TimeService.h,v 1.27 2010/05/17 08:12:02 mul Exp $

#ifndef TimeService_H_
#define TimeService_H_

#include "ace/Synch.h"
#include "ace/Thread_Mutex.h"

#include "Util/GeRtiFedTime.h"
#include "Util/XercesInclude.h"
#include "Util/HLAparseErrorHandler.h"

namespace GERTICO
{
class TimeService
{
public:
  ACE_Semaphore *psToken;
  virtual ~TimeService () { ; };

  virtual void disableTimeConstrained(GeRtiFactory::GeRtiHandle const &theFederate) = 0;

  virtual void disableTimeRegulation(GeRtiFactory::GeRtiHandle const &theFederate) = 0;

  virtual void enableTimeConstrained(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theSourceType) = 0;

#ifdef IEEE_1516
  virtual void enableTimeRegulation(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval &theLookahead, GeRtiFactory::GeRtiHandle const &theSourceType) = 0;
#else
  virtual void enableTimeRegulation(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime const &theFederateTime, GERTICO::GeRtiLogicalTimeInterval &theLookahead, GeRtiFactory::GeRtiHandle const &theSourceType) = 0;
#endif

  virtual void flushQueueRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime) = 0;

  virtual void joinFederationExecution(GeRtiFactory::GeRtiHandle const &theFederate) = 0;

  virtual void modifyLookahead(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval &theGeRtiFedTime) = 0;

  virtual void nextEventRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime) = 0;

  virtual void nextEventRequestAvailable(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime) = 0;

  virtual void numberOfHubs(CORBA::ULong const &theNumberOfHubs) = 0;

  virtual void process(void) = 0;

  virtual void queryGALT(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime) = 0;

  virtual void queryLITS(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime) = 0;

  virtual void queryLogicalTime(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime& theTime) = 0;

  virtual void queryLookahead(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiLogicalTimeInterval &theTime) = 0;

  virtual void timeConstrainedPeerEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theTime) = 0;

  virtual void timeRegulationPeerEnabled(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theTime) = 0;

  virtual void reset(void) = 0;

  virtual void resignFederationExecution(GeRtiFactory::GeRtiHandle const &theFederate) = 0;

  virtual void restore(DOMElement &theDOMElement) = 0;

  virtual void retract(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theHandle) = 0;

  virtual void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement) = 0;

  virtual void terminate(void) = 0;

  virtual void timeAdvanceRequest(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime) = 0;

  virtual void timeAdvanceRequestAvailable(GeRtiFactory::GeRtiHandle const &theFederate, GERTICO::GeRtiFedTime &theGeRtiFedTime) = 0;
};
};

#endif /* TimeService_H_  */
