/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: EventHandler.cpp,v $
Revision 1.22  2010/07/22 11:14:20  mul
Delete unused values.

Revision 1.21  2010/06/28 13:37:06  mul
Add mutex locks to avoid data conflicts.

Revision 1.20  2010/05/17 08:02:28  mul
Add logical time interval.

Revision 1.19  2010/03/22 12:56:26  mul
Changes for single callbacks.

Revision 1.18  2010/03/16 15:28:53  mul
Change gal events.

Revision 1.17  2010/03/11 10:44:14  mul
Fix mutex blocking on linux.

Revision 1.16  2010/03/05 13:10:49  mul
Changes for single evoke call.

Revision 1.15  2010/02/25 07:37:44  mul
Changes for single callbacks.

Revision 1.14  2010/02/08 12:41:08  mul
Changes to increase performance.

Revision 1.13  2009/10/20 09:19:41  mul
Check for time violations for incoming events.

Revision 1.12  2009/09/23 06:59:02  mul
Add some logging.

Revision 1.11  2009/09/03 07:08:24  mul
Move some time management logic to correct module.

Revision 1.10  2009/06/02 12:12:13  mul
Fix problems with retraction handle.

Revision 1.9  2009/05/07 12:27:08  mul
Changes for removing token logic in time management.

Revision 1.8  2009/03/19 09:02:21  mul
Changes to limit output of event logging.

Revision 1.7  2009/01/26 09:33:07  mul
Changes to allow asynchrous sending of events.

Revision 1.6  2008/11/19 14:09:24  mul
Changes for logging.

Revision 1.5  2008/08/07 09:36:02  mul
Changes in event channel.

Revision 1.4  2008/01/30 10:53:59  mul
Changes for ieee1516.

Revision 1.3  2007/10/08 07:55:50  mul
Minor change.

Revision 1.2  2007/09/05 15:39:29  mul
Changes for ieee1516.

Revision 1.1  2007/06/26 08:25:26  mul
New files for ieee1516.

Revision 1.92  2007/03/29 09:09:05  mul
Add logging.

Revision 1.91  2007/03/12 13:10:12  mul
Changed string to wstring.

Revision 1.90  2007/02/07 09:34:19  mul
Use an auto ptr template.

Revision 1.89  2006/12/15 08:47:03  mul
Remove some logging.

Revision 1.88  2006/12/12 14:13:37  mul
Add logging. Fix memory leaks.

Revision 1.87  2006/11/28 15:39:37  mul
Minor error fix.

Revision 1.86  2006/11/15 11:17:37  mul
Changes for testcases.

Revision 1.85  2006/10/30 09:25:51  mul
Add init method.

Revision 1.84  2006/10/12 13:55:17  mul
Fix federate state.

Revision 1.83  2006/09/26 07:27:08  mul
Correct maximum time for message delivered.

Revision 1.82  2006/09/12 11:30:23  mul
Changes for phase 5 testcases.

Revision 1.81  2006/09/04 15:02:57  mul
Changes for phase 1 testcases.

Revision 1.80  2006/08/30 11:44:25  mul
Chnages for phase 1 testcases.

Revision 1.79  2006/08/25 08:47:39  mul
Deliver messages when federation time allows delivery of events before TAG.

Revision 1.78  2006/08/15 12:41:09  mul
Changes for phase 4 tests.

Revision 1.77  2006/08/10 14:08:27  hzg
cleanup data structures and fixed removeWithTime

Revision 1.76  2006/08/08 14:14:15  mul
Deliver timed events in advancing state for tar before grant.

Revision 1.75  2006/08/01 11:29:59  mul
Changes for mom.

Revision 1.74  2006/07/06 11:30:01  mul
Minor changes.

Revision 1.73  2006/05/16 08:26:07  mul
Fix remove with time logic.

Revision 1.72  2006/04/19 15:00:01  mul
Changes for MOM.

Revision 1.71  2006/02/09 15:38:51  mul
Add new maps and methods.

Revision 1.70  2006/02/08 14:12:19  mul
Fix remove object logic when not enabled.

Revision 1.69  2006/01/02 14:28:47  mul
Change sequence of list deletion and object deletion.

Revision 1.68  2005/12/21 11:27:15  mul
Change mutex locks.

Revision 1.67  2005/12/20 09:12:15  mul
Changes to reduce compiler warnings.

Revision 1.66  2005/11/23 10:24:51  mul
Fix deadlock on mutex and map.

Revision 1.65  2005/11/22 10:12:29  mul
Clean up some memory leaks.

Revision 1.64  2005/11/14 10:30:55  mul
Fix problem with timed events.

Revision 1.63  2005/11/11 10:56:07  mul
Change some logic to track missing events.

Revision 1.62  2005/10/31 11:25:42  mul
Add logging for mutex acquire and release.

Revision 1.61  2005/10/20 08:00:43  mul
Changed some method names.

Revision 1.60  2005/10/11 10:25:24  mul
Fix memory leak.

Revision 1.59  2005/10/10 07:45:40  mul
Minor changes.

Revision 1.58  2005/10/10 07:43:48  mul
Some some memory leaks.

Revision 1.57  2005/09/07 12:34:29  mul
Change name scoping.

Revision 1.56  2005/08/22 14:33:53  mul
Changes for various order types.

Revision 1.55  2005/08/03 13:04:38  mul
Add restore functions.

Revision 1.54  2005/07/19 12:25:58  mul
Change logging text.

Revision 1.53  2005/07/14 12:41:39  mul
Fix handling of timed events before grant given to federate ambassador.

Revision 1.52  2005/07/06 15:16:57  mul
Add gal logging.

Revision 1.51  2005/07/04 13:33:09  mul
Remove some output lines.

Revision 1.50  2005/06/24 13:00:59  mul
Add restore logic.

Revision 1.49  2005/06/15 11:48:02  mul
Add mutex to object map.

Revision 1.48  2005/06/02 11:26:51  mul
Sequence of mutex aquire/release instead one long transaction.

Revision 1.47  2005/05/24 08:59:41  mul
Remove double logic for interaction timestamp.

Revision 1.46  2005/05/19 12:00:12  mul
Minor changes.

Revision 1.45  2005/05/04 10:06:23  mul
Add save logic.

Revision 1.43  2005/04/08 13:01:24  mul
Fix logic for save with time.

Revision 1.42  2005/03/15 14:55:22  mul
Fix a null pointer problem.

Revision 1.41  2005/03/03 09:39:19  mul
Fix delivery of events when timeRegulated enabled after timeConstrained.

Revision 1.40  2005/03/02 08:11:08  mul
Fix segmentation fault error.

Revision 1.39  2005/02/21 08:37:21  mul
Fix logic when timeAdvance may be granted.

Revision 1.38  2005/02/16 08:00:37  mul
Test for Linux 9.1 problem.

Revision 1.37  2005/02/11 14:54:04  mul
Minor changes

Revision 1.36  2005/02/11 14:49:52  mul
Add scoping.

Revision 1.35  2005/02/09 07:39:23  mul
Scoping added for std.

Revision 1.34  2005/02/07 10:33:25  mul
Changes due to test cases.

Revision 1.33  2005/01/28 08:42:34  hzg
merging gertico_0_16b_fix into main thread

Revision 1.32  2004/12/14 13:40:48  mul
Fix federate save logic.

Revision 1.31.2.1  2005/01/27 10:22:25  hzg
bug fix concerning include and std usage
requred for using ACE-5.4+TAO-1.4

Revision 1.31  2004/09/24 08:30:27  mul
Changes for save federation.

Revision 1.30  2004/08/20 08:16:31  mul
Remove unused variable.

Revision 1.29  2004/08/19 09:59:56  mul
Changes due to save/restore logic.

Revision 1.28  2004/07/16 11:57:37  mul
Changes due to verfication test.

Revision 1.27  2004/05/27 12:22:05  mul
Fix problems found in conformance test.

Revision 1.26  2004/03/17 14:16:40  mul
Add event retraction.

Revision 1.25  2004/03/02 09:35:38  mul
Fix timestamp logic.

Revision 1.24  2003/10/15 11:56:31  mul
Only deliver events in time advancing state.

Revision 1.23  2003/09/24 09:17:53  mul
Clear map in destructor.

Revision 1.22  2003/09/23 14:25:06  mul
Clean up memory leak.

Revision 1.21  2003/08/29 08:08:08  mul
Split a complex method into several parts.

Revision 1.20  2003/08/26 14:52:38  mul
Fixed time regulation and a memory leak.

Revision 1.19  2003/08/20 08:45:36  hzg
name of gal resource changed

Revision 1.18  2003/08/07 12:07:43  mul
Make mapper a static/global function.

Revision 1.17  2003/07/16 07:59:01  mul
Changes for RTI::FedTime.

Revision 1.16  2003/05/28 06:40:48  mul
Use include paths starting in $GERTICO.

Revision 1.15  2003/05/21 11:59:25  hzg
Debug.h removed

Revision 1.14  2003/04/29 06:26:13  hzg
Portierung auf Windows

Revision 1.13  2003/04/10 12:43:49  mul
Add mom counters.

Revision 1.12  2003/02/18 09:55:09  mul
Fix unsubscribe logic.

Revision 1.11  2003/02/10 14:59:04  ba
FedAm interface logged by Gal.

Revision 1.10  2003/02/10 11:26:21  hzg
Gal converter

Revision 1.9  2003/01/31 12:49:53  mul
Do not reflect zero length attribute or parameter values.

Revision 1.8  2003/01/10 14:08:13  ba
Fehler in Parser behoben

Revision 1.7  2002/10/10 07:37:37  mul
Fix removeWithTime logic and add DebugHLASpec.h file for HLASpec module.

Revision 1.6  2002/10/02 10:39:06  mul
Fix logic for tags in updates.

Revision 1.5  2002/09/23 12:13:09  mul
Add logic to only deliver the subscribed attributes to the application.

Revision 1.4  2002/09/18 14:50:17  mul
Add/complete usage of exceptions.

Revision 1.3  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen


**
*******************************************************************************/

#include "EventHandler.h"
#include "Util/ConvertTime.h"
#include "Util/Mapper.h"
#include "LRC/HLA1516/Mapper1516.h"

// Static strings for save/restore.
std::string GERTICO::EventHandler1516::classStr("class");
std::string GERTICO::EventHandler1516::eventStr("event");
std::string GERTICO::EventHandler1516::eventHandlerStr("eventHandler");
std::string GERTICO::EventHandler1516::idStr("id");
std::string GERTICO::EventHandler1516::objectStr("object");
std::string GERTICO::EventHandler1516::regionStr("region");
std::string GERTICO::EventHandler1516::removeObjectsWithTimeStr("removeObjectsWithTime");
std::string GERTICO::EventHandler1516::retractHandleStr("retractHandle");
std::string GERTICO::EventHandler1516::retractHandlesStr("retractHandles");
std::string GERTICO::EventHandler1516::sendingFederateStr("sendingFederate");
std::string GERTICO::EventHandler1516::tagStr("tag");
std::string GERTICO::EventHandler1516::theSerialNumberStr("theSerialNumber");
std::string GERTICO::EventHandler1516::timeStr("time");
std::string GERTICO::EventHandler1516::timestampStr("timestamp");
std::string GERTICO::EventHandler1516::tsoEventsStr("tsoEvents");
std::string GERTICO::EventHandler1516::typeStr("type");
std::string GERTICO::EventHandler1516::userTagStr("userTag");
std::string GERTICO::EventHandler1516::valueStr("value");
std::string GERTICO::EventHandler1516::valuePairStr("valuePair");
std::string GERTICO::EventHandler1516::valuePairsStr("valuePairs");

// insert Gal file .init here
#ifdef GalDebug

/********************************* Gal begin *********************************/
#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"
#define MAX_TXT 1024

static class Repository_l *FM=(Repository::getSingleInstance())->getRepository_l("GeRtiFM.res","GeRtiFM");

static class Event *GeRti_FM_d=FM->getRefEvent("GeRti_FM_d");
static class Event *GeRti_FM_e=FM->getRefEvent("GeRti_FM_e");
static class Event *GeRti_FM_feds_i=FM->getRefEvent("GeRti_FM_feds_i");
static class Event *GeRti_FM_i=FM->getRefEvent("GeRti_FM_i");
static class Event *GeRti_FM_save_restore_i=FM->getRefEvent("GeRti_FM_save_restore_i");
static class Event *GeRti_FM_sync_i=FM->getRefEvent("GeRti_FM_sync_i");
static class Event *GeRti_FM_w=FM->getRefEvent("GeRti_FM_w");

static class Repository_l *OM=(Repository::getSingleInstance())->getRepository_l("GeRtiOM.res","GeRtiOM");

static class Event *GeRti_OM_d=OM->getRefEvent("GeRti_OM_d");
static class Event *GeRti_OM_e=OM->getRefEvent("GeRti_OM_e");
static class Event *GeRti_OM_i=OM->getRefEvent("GeRti_OM_i");
static class Event *GeRti_OM_w=OM->getRefEvent("GeRti_OM_w");

static class Repository_l *TM=(Repository::getSingleInstance())->getRepository_l("GeRtiTM.res","GeRtiTM");

static class Event *GeRti_TM_d=TM->getRefEvent("GeRti_TM_d");
static class Event *GeRti_TM_e=TM->getRefEvent("GeRti_TM_e");
static class Event *GeRti_TM_i=TM->getRefEvent("GeRti_TM_i");
static class Event *GeRti_TM_w=TM->getRefEvent("GeRti_TM_w");
static class Event *GeRti_TM_mu_d=TM->getRefEvent("GeRti_TM_mu_d");

#include "Gal/StdAfx.h"   // inserted by Gal converter
#include "Gal/repository_l.h"   // inserted by Gal converter
#include "Gal/event.h"   // inserted by Gal converter

static class Repository_l *rpGalH=(Repository::getSingleInstance())->getRepository_l("HLAServices.res","HLAServices");
static class Event *pIFS_i0=rpGalH->getRefEvent("pIFS_i0");
static class Event *pIFS_ts=rpGalH->getRefEvent("pIFS_ts");
static class Event *pFS_i0=rpGalH->getRefEvent("pIF_i0");
static class Event *pFS_ts=rpGalH->getRefEvent("pIF_ts");
static class Event *pCFRR_i0=rpGalH->getRefEvent("pCFRR_i0");
static class Event *pCFRR_i1=rpGalH->getRefEvent("pCFRR_i1");
static class Event *pCFRR_ts=rpGalH->getRefEvent("pCFRR_ts");
static class Event *pFRB_i0=rpGalH->getRefEvent("pFRB_i0");
static class Event *pFRB_ts=rpGalH->getRefEvent("pFRB_ts");
static class Event *pIFR_i0=rpGalH->getRefEvent("pIFR_i0");
static class Event *pIFR_ts=rpGalH->getRefEvent("pIFR_ts");
static class Event *pFR_i0=rpGalH->getRefEvent("pFR_i0");
static class Event *pTO_i0=rpGalH->getRefEvent("pTO_i0");
static class Event *pERO_i0=rpGalH->getRefEvent("pERO_i0");
static class Event *pERO_ta=rpGalH->getRefEvent("pERO_ta");
static class Event *pERO_ts=rpGalH->getRefEvent("pERO_ts");
static class Event *pETO_i0=rpGalH->getRefEvent("pETO_i0");
static class Event *pETO_ta=rpGalH->getRefEvent("pETO_ta");
static class Event *pETO_ts=rpGalH->getRefEvent("pETO_ts");
static class Event *pERI_i0=rpGalH->getRefEvent("pERI_i0");
static class Event *pERI_ta=rpGalH->getRefEvent("pERI_ta");
static class Event *pERI_ts=rpGalH->getRefEvent("pERI_ts");
static class Event *pRWT_i0=rpGalH->getRefEvent("pRWT_i0");
static class Event *pRWT_ta=rpGalH->getRefEvent("pRWT_ta");
static class Event *pRWT_ts=rpGalH->getRefEvent("pRWT_ts");
static class Event *pTRE_i0=rpGalH->getRefEvent("pTRE_i0");
static class Event *pTRE_ta=rpGalH->getRefEvent("pTRE_ta");
static class Event *pTRE_ts=rpGalH->getRefEvent("pTRE_ts");
static class Event *pTCE_i0=rpGalH->getRefEvent("pTCE_i0");
static class Event *pTCE_ta=rpGalH->getRefEvent("pTCE_ta");
static class Event *pTCE_ts=rpGalH->getRefEvent("pTCE_ts");
static class Event *pT_i0=rpGalH->getRefEvent("pT_i0");
static class Event *pT_ta=rpGalH->getRefEvent("pT_ta");
static class Event *pT_ts=rpGalH->getRefEvent("pT_ts");
static class Event *rAOA_i0=rpGalH->getRefEvent("rAOA_i0");
static class Event *pETI_i0=rpGalH->getRefEvent("pETI_i0");
static class Event *pETI_ta=rpGalH->getRefEvent("pETI_ta");
static class Event *pETI_ts=rpGalH->getRefEvent("pETI_ts");
static class Event *pR_i0=rpGalH->getRefEvent("pR_i0");
static class Event *pR_ta=rpGalH->getRefEvent("pR_ta");
static class Event *pR_ts=rpGalH->getRefEvent("pR_ts");
static class Event *pRF_i0=rpGalH->getRefEvent("pRF_i0");

static char galMsg[MAX_TXT];

#endif

/*********************************** Gal end *********************************/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Remove::Remove(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theUserSuppliedTag, bool const &theSendOrderTso)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "Remove::Remove", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  objectId = theObject;
  myTag = theUserSuppliedTag;
  sendOrderTso = theSendOrderTso;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "Remove::Remove", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Remove::~Remove(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "Remove::~Remove", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RemoveWithTime::RemoveWithTime(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theUserSuppliedTag, bool const &theSendOrderTso, GERTICO::GeRtiFedTime &theTime, GeRtiFactory::ERHandle const &theERHandle, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory) : fedTimeFactory(theFedTimeFactory)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "RemoveWithTime::RemoveWithTime", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  objectId = theObject;
  myTag = theUserSuppliedTag;
  myTime = fedTimeFactory.makeZero();
  *myTime = theTime;
  retractionHandle = theERHandle;
  sendOrderTso = theSendOrderTso;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "RemoveWithTime::RemoveWithTime", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RemoveWithTime::~RemoveWithTime(void)
{
                           #ifdef GalHLA   // inserted by Gal converter
                             E2(GeRti_OM_d, "RemoveWithTime::~RemoveWithTime", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHolder::EventHolder(GeRtiFactory::GeRtiEvent const &theEvent, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory)
{
                           #ifdef GalHLA   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::~EventHolder", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  RTI::EncodedLogicalTime *encodedLogicalTime = NULL;

  type = theEvent.type;
  timestamp.reset(theFedTimeFactory.makeZero());
  GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(theFedTimeFactory, timestamp, theEvent.timestamp);
  if (timestamp.get())
  {
    GERTICO::Mapper1516::mapEncodedLogicalTime(&encodedLogicalTime, *timestamp);
    rtiTimestamp = theFedTimeFactory.logicalTimeFactory.decode(*encodedLogicalTime);
    delete encodedLogicalTime;
    encodedLogicalTime = NULL;
  }
  else
  {
    rtiTimestamp = theFedTimeFactory.logicalTimeFactory.makeInitial();
  }
  retractionHandle.sendingFederate = theEvent.source;
  retractionHandle.theSerialNumber = theEvent.theSerialNumber;

  if (type == GeRtiFactory::interaction)
  {
    hvps = theEvent.data;
    userSuppliedTag = theEvent.theTag;
    objectId = theEvent.obj;
    classId = theEvent._cxx_class;
    region = theEvent.reg;

    if (theEvent.bestEffort)
    {
      bestEffort = true;
    }
    else
    {
      bestEffort = false;
    }
  }
                           #ifdef GalHLA   // inserted by Gal converter
                             E0(EH_l);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHolder::EventHolder(GeRtiFactory::GeRtiEvent const &theEvent, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory, int const &theGrouping, bool const &theBestEffort)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::EventHolder", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  type = theEvent.type;
  timestamp.reset(theFedTimeFactory.makeZero());
  GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(theFedTimeFactory, timestamp, theEvent.timestamp);
  if (timestamp.get())
  {
    RTI::EncodedLogicalTime *encodedLogicalTime = NULL;

    GERTICO::Mapper1516::mapEncodedLogicalTime(&encodedLogicalTime, *timestamp);
    rtiTimestamp = theFedTimeFactory.logicalTimeFactory.decode(*encodedLogicalTime);
    delete encodedLogicalTime;
    encodedLogicalTime = NULL;
  }
  else
  {
    rtiTimestamp = theFedTimeFactory.logicalTimeFactory.makeInitial();
  }
  retractionHandle.sendingFederate = theEvent.source;
  retractionHandle.theSerialNumber = theEvent.theSerialNumber;

  if (type != GeRtiFactory::interaction)
  {
    GERTICO::Mapper1516::mapAttributeHandleValueMap(hvps, theEvent.data, theGrouping, theBestEffort);
    userSuppliedTag = theEvent.theTag;
    objectId = theEvent.obj;
    classId = theEvent._cxx_class;
    region = theEvent.reg;

    if (theBestEffort)
    {
      bestEffort = true;
    }
    else
    {
      bestEffort = false;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::EventHolder", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHolder::~EventHolder(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::~EventHolder", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHolder::~EventHolder", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
unsigned long GERTICO::EventHolder::getLength(void)
{
                             E2(GeRti_OM_d, "EventHolder::getLength", "enterLeave");   // inserted by Gal converter
  return hvps.length();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHandler1516::EventHandler1516(bool &theAsynchronousDelivery) : asynchronousDelivery(theAsynchronousDelivery)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::EventHandler1516", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  timeManagementLRC = NULL;
  init();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::EventHandler1516", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::init(void)
{
  pm.acquire();
  ehRequest = EHNone;

  // Save / Restore
  federateState = Running;
  gotAnnounceFederateSave = false;
  gotConfirmFederationRestorationRequest = false;
  gotInitiateFederateSave = false;

  confirmRestoreSuccess = true;
  gotTimeConstrainedEnabled = false;
  gotTimeConstrainedEnabledFlag = false;
  gotTimeRegulationEnabled = false;
  gotTimeRegulationEnabledFlag = false;
  interactionsReceived = 0;
  reflectionsReceived = 0;
  restoreLabel = L"";
  saveLabel = L"";
  stateRestore = false;
  stateSave = false;

  // Time
  available = false;
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventHandler1516::~EventHandler1516(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::~EventHandler1516", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  clear();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::~EventHandler1516", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addERHandle(GeRtiFactory::ERHandle const &theMessageRetractionHandle, GERTICO::GeRtiFedTime const &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addERHandle", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::HandleErMap::iterator itHEM;
  std::auto_ptr<GERTICO::GeRtiFedTime> tmpFedTime(timeManagementLRC->geRtiFedTimeFactory.makeZero());

  *tmpFedTime = theFedTime;
  itHEM = handleErMap.find(theMessageRetractionHandle.sendingFederate);
  if (itHEM != handleErMap.end())
  {
    // Got an entry for the federate.
    GERTICO::ERHandleTimeMap *currERHandleTimeMap;
    currERHandleTimeMap = &itHEM->second;
    (*currERHandleTimeMap)[theMessageRetractionHandle.theSerialNumber] = tmpFedTime.release();
  }
  else
  {
    // Create an entry for the federate.
    GERTICO::ERHandleTimeMap newERHandleTimeMap;
    newERHandleTimeMap[theMessageRetractionHandle.theSerialNumber] = tmpFedTime.release();
    handleErMap[theMessageRetractionHandle.sendingFederate] = newERHandleTimeMap;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addERHandle", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addEventHolder(GeRtiFactory::GeRtiEvent const &theEvent, unsigned int &numberRO, unsigned int &numberTSO)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addEventHolder", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  EventHolder *newEventHolderRoBestEffort = NULL;
  EventHolder *newEventHolderRoReliable = NULL;
  EventHolder *newEventHolderTsoBestEffort = NULL;
  EventHolder *newEventHolderTsoReliable = NULL;

  numberRO = 0;
  numberTSO = 0;

  pm.acquire();

  // Only when the application has received the enabled call.
  if (gotTimeConstrainedEnabled == true && gotTimeConstrainedEnabledFlag == false)
  {
    if (theEvent.type == GeRtiFactory::interaction)
    {
      if (theEvent.timestamp.length())
      {
        // Events TSO based on timestamp and preferred type.
        if (theEvent.bestEffort)
        {
          newEventHolderTsoBestEffort = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory);
        }
        else
        {
          newEventHolderTsoReliable = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory);
        }
        // NB. zero length is allowed
      }
      else
      {
        // Events are RO.
        if (theEvent.bestEffort)
        {
          newEventHolderRoBestEffort = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory);
        }
        else
        {
          newEventHolderRoReliable = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory);
        }
        // NB. zero length is allowed
      }
    }
    else
    {
      if (theEvent.timestamp.length())
      {
        // Events are RO and/or TSO based on preferred type.
        newEventHolderRoBestEffort = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory, 0, true);
        if (newEventHolderRoBestEffort->getLength() == 0)
        {
          delete newEventHolderRoBestEffort;
          newEventHolderRoBestEffort = NULL;
        }
        newEventHolderRoReliable = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory, 0, false);
        if (newEventHolderRoReliable->getLength() == 0)
        {
          delete newEventHolderRoReliable;
          newEventHolderRoReliable = NULL;
        }
        newEventHolderTsoBestEffort = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory, 1, true);
        if (newEventHolderTsoBestEffort->getLength() == 0)
        {
          delete newEventHolderTsoBestEffort;
          newEventHolderTsoBestEffort = NULL;
        }
        newEventHolderTsoReliable = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory, 1, false);
        if (newEventHolderTsoReliable->getLength() == 0)
        {
          delete newEventHolderTsoReliable;
          newEventHolderTsoReliable = NULL;
        }
      }
      else
      {
        // Events are RO.
        newEventHolderRoBestEffort = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory, 2, true);
        newEventHolderRoReliable = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory, 2, false);
        // NB. zero length is allowed
      }
    }
  }
  else
  {
    if (theEvent.type == GeRtiFactory::interaction)
    {
      // Events are RO.
      if (theEvent.bestEffort)
      {
        newEventHolderRoBestEffort = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory);
      }
      else
      {
        newEventHolderRoReliable = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory);
      }
      // NB. zero length is allowed
    }
    else
    {
      // All events are made RO.
      newEventHolderRoBestEffort = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory, 2, true);
      newEventHolderRoReliable = new EventHolder(theEvent, timeManagementLRC->geRtiFedTimeFactory, 2, false);
    }
  }
  if (newEventHolderTsoBestEffort)
  {
    // Got a TSO event.
    if (*newEventHolderTsoBestEffort->timestamp < *myRegulationTime)
    {
      newEventHolderTsoBestEffort->timestamp.release();
      newEventHolderRoBestEffort = newEventHolderTsoBestEffort;
      newEventHolderTsoBestEffort = NULL;
    }
  }

  if (newEventHolderTsoBestEffort)
  {
    if (*newEventHolderTsoBestEffort->timestamp < *timeManagementLRC->myLogicalTime)
    {
      char *b = "EventHandler1516::addEventHolder: timestamp < logicalTime";
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addEventHolder", "error_1");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      delete newEventHolderTsoBestEffort;
      newEventHolderTsoBestEffort = NULL;
    }
    if (newEventHolderTsoBestEffort)
    {
      EventHolderMap::iterator itEHM;
      std::vector <EventHolder *> *currEventHolderVector;
      std::vector <EventHolder *> newEventHolder;

      itEHM = eventsTimedMap.find(newEventHolderTsoBestEffort->timestamp.get());
      if (itEHM != eventsTimedMap.end())
      {
        currEventHolderVector = &itEHM->second;
        currEventHolderVector->push_back(newEventHolderTsoBestEffort);
      }
      else
      {
        GERTICO::GeRtiFedTime *tempTime;
        newEventHolder.push_back(newEventHolderTsoBestEffort);
        tempTime = timeManagementLRC->geRtiFedTimeFactory.makeZero();
        *tempTime = *newEventHolderTsoBestEffort->timestamp;
        eventsTimedMap[tempTime] = newEventHolder;
      }
      numberTSO += 1;
      addERHandle(newEventHolderTsoBestEffort->retractionHandle, *newEventHolderTsoBestEffort->timestamp);
    }
  }
  if (newEventHolderTsoReliable)
  {
    if (*newEventHolderTsoReliable->timestamp < *myRegulationTime)
    {
      newEventHolderTsoReliable->timestamp.release();
      newEventHolderRoReliable = newEventHolderTsoReliable;
      newEventHolderTsoReliable = NULL;
    }
  }

  if (newEventHolderTsoReliable)
  {
    // Got a TSO event: check time stamp.
    if (*newEventHolderTsoReliable->timestamp < *timeManagementLRC->myLogicalTime)
    {
      char *b = "EventHandler1516::addEventHolder: timestamp < logicalTime";
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addEventHolder", "error_2");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      delete newEventHolderTsoReliable;
      newEventHolderTsoReliable = NULL;
    }
    if (newEventHolderTsoReliable)
    {
      EventHolderMap::iterator itEHM;
      std::vector <EventHolder *> *currEventHolderVector;
      std::vector <EventHolder *> newEventHolder;

      itEHM = eventsTimedMap.find(newEventHolderTsoReliable->timestamp.get());
      if (itEHM != eventsTimedMap.end())
      {
        currEventHolderVector = &itEHM->second;
        currEventHolderVector->push_back(newEventHolderTsoReliable);
      }
      else
      {
        GERTICO::GeRtiFedTime *tempTime;
        newEventHolder.push_back(newEventHolderTsoReliable);
        tempTime = timeManagementLRC->geRtiFedTimeFactory.makeZero();
        *tempTime = *newEventHolderTsoReliable->timestamp;
        eventsTimedMap[tempTime] = newEventHolder;
      }
      numberTSO += 1;
      addERHandle(newEventHolderTsoReliable->retractionHandle, *newEventHolderTsoReliable->timestamp);
    }
  }
  if (newEventHolderRoBestEffort)
  {
    // Got an RO event.
    events.push_back(newEventHolderRoBestEffort);
    numberRO += 1;
  }
  if (newEventHolderRoReliable)
  {
    // Got an RO event.
    events.push_back(newEventHolderRoReliable);
    numberRO += 1;
  }

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addEventHolder", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addFlushERHandle(GeRtiFactory::ERHandle const &theERHandle, GERTICO::GeRtiFedTime *theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addFlushERHandle", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  timeErMultimap.insert(std::pair<GERTICO::GeRtiFedTime *, GeRtiFactory::ERHandle>(theFedTime, theERHandle));
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addFlushERHandle", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addHandleMap(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleMap &theHandleMap)
{
  GERTICO::HandleMap::iterator itHandleMap;

  itHandleMap = theHandleMap.find(theClass);
  if (itHandleMap != theHandleMap.end())
  {
    itHandleMap->second += 1;
  }
  else
  {
    GeRtiFactory::GeRtiHandle count = 1;

    theHandleMap[theClass] = count;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addInitiateFederateSave(std::wstring const &theLabel)
{
  gotAnnounceFederateSave = true;
  timeManagementLRC->gotAnnounceFederateSaveWithTime = false;
  saveLabel = theLabel;
  federateState = SavePending;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addInitiateFederateSaveWithTime(std::wstring const &theLabel, GERTICO::GeRtiFedTime const &theTime)
{
  char buff[256];
  *timeManagementLRC->myTimeSave = theTime;
  timeManagementLRC->myTimeSave->getPrintableString(buff);
  gotAnnounceFederateSave = false;
  timeManagementLRC->gotAnnounceFederateSaveWithTime = true;
  saveLabel = theLabel;
  federateState = SavePending;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addRemove(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theUserSuppliedTag, bool const &theSendOrderTso)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addRemove", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::Remove *newRemove = new GERTICO::Remove(theObject, theUserSuppliedTag, theSendOrderTso);

  pm.acquire();
  removeObjects.push_back(newRemove);
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addRemove", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addRemoveWithTime(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &tag, std::auto_ptr<GERTICO::GeRtiFedTime> &theTime, GeRtiFactory::ERHandle const &theERHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addRemoveWithTime", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter

  if (gotTimeConstrainedEnabled)
  {
    RemoveWithTime *newRemoveWithTime = new RemoveWithTime(theObject, tag, true, *theTime, theERHandle, timeManagementLRC->geRtiFedTimeFactory);
    pm.acquire();
    removeObjectsWithTime.insert(std::pair<const GERTICO::GeRtiFedTime *, RemoveWithTime *>(newRemoveWithTime->myTime, newRemoveWithTime));

    addERHandle(theERHandle, *theTime);
    pm.release();
  }
  else
  {
    try
    {
      // get object only for test if known
      runTimeObjectDB->getObject(theObject);
      addRemove(theObject, tag, true);
    }
    catch(GeRtiFactory::ObjectNotKnown&)
    {
      // object is not known - no delete required
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::addRemoveWithTime", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addRetractionHandle(GeRtiFactory::ERHandle const &theERHandle, GERTICO::GeRtiFedTime const &theFedTime)
{
  ERHandleTimeMap::iterator itERHTM;
  TimeERHandleMap::iterator itTERHM;

  itERHTM = eRHandleTimeMap.find(theERHandle.theSerialNumber);
  if (itERHTM == eRHandleTimeMap.end())
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> fedTime(timeManagementLRC->geRtiFedTimeFactory.makeZero());
    *fedTime = theFedTime;
    itTERHM = timeERHandleMap.find(fedTime.get());
    if (itTERHM != timeERHandleMap.end())
    {
      GERTICO::HandleSet *handleSetPtr;
      handleSetPtr = &itTERHM->second;
      handleSetPtr->insert(theERHandle.theSerialNumber);
    }
    else
    {
      GERTICO::HandleSet handleSet;
      handleSet.insert(theERHandle.theSerialNumber);
      timeERHandleMap[fedTime.get()] = handleSet;
    }
    eRHandleTimeMap[theERHandle.theSerialNumber] = fedTime.release();
  }
  else
  {
    // XXX Gal error message: duplicate retraction handle
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addTimeAdvanceGrant(GERTICO::GeRtiFedTime &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_TM_d)
                            {
                              char buf[512];
                              theFedTime.getPrintableString(buf);
                              E2(GeRti_TM_d, "EventHandler1516::addTimeAdvanceGrant_enter", buf);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  timeManagementLRC->addTimeAdvanceGrant(theFedTime);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::addTimeAdvanceGrant", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addTimeAdvanceGrantGalt(GERTICO::GeRtiFedTime const &theFedTime, GERTICO::GeRtiFedTime const &theGaltFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::addTimeAdvanceGrantGalt", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  timeManagementLRC->addTimeAdvanceGrantGalt(theFedTime, theGaltFedTime);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::addTimeAdvanceGrantGalt", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::addTimeAdvanceGrantIntermediate(GERTICO::GeRtiFedTime const &theFedTime)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::addTimeAdvanceGrantIntermediate", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  timeManagementLRC->addTimeAdvanceGrantIntermediate(theFedTime);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::addTimeAdvanceGrantIntermediate", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::checkRetractionHandle(GeRtiFactory::ERHandle const &theERHandle)
{
  ERHandleTimeMap::iterator itERHTM;

  itERHTM = eRHandleTimeMap.find(theERHandle.theSerialNumber);
  if (itERHTM != eRHandleTimeMap.end())
  {
    return;
  }
  else
  {
    throw GeRtiFactory::InvalidRetractionHandle(L"checkRetractionHandle");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::deleteRetractionHandle(GeRtiFactory::ERHandle const &theERHandle)
{
  ERHandleTimeMap::iterator itERHTM;
  GERTICO::GeRtiFedTime *fedTime;

  itERHTM = eRHandleTimeMap.find(theERHandle.theSerialNumber);
  if (itERHTM != eRHandleTimeMap.end())
  {
    fedTime = itERHTM->second;
    eRHandleTimeMap.erase(itERHTM);
    delete fedTime;
    return;
  }
  else
  {
    throw GeRtiFactory::InvalidRetractionHandle(L"deleteRetractionHandle");
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::clear(void)
{
  EventHolder *currEventHolder;
  EventHolderMap::iterator itEHM;
  GERTICO::ERHandleTimeMap *currERHandleTimeMap;
  GERTICO::ERHandleTimeMap::iterator itERHTM;
  GERTICO::HandleErMap::iterator itHEM;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetSetMap::iterator itRCA;
  GERTICO::TimeERHandleMap::iterator itTERHM;
  GERTICO::TimeErMultimap::iterator itTEM;
  GERTICO::Remove *currRemove;
  RemoveWithTime *currRemoveWithTime;
  RemoveWithTimeMultimap::iterator itRWT;
  GERTICO::GeRtiFedTime *fedTime;
  std::vector <EventHolder *> *currEventHolderVector;
  std::vector <EventHolder *>::iterator itEH;
  std::vector <GERTICO::Remove *>::iterator itR;

  pm.acquire();
  gotAnnounceFederateSave = false;
  for (itEH = events.begin(); itEH != events.end(); itEH = events.begin())
  {
    currEventHolder = *itEH;
    events.erase(itEH);
    delete currEventHolder;
  }

  for (itEHM = eventsTimedMap.begin(); itEHM != eventsTimedMap.end(); itEHM = eventsTimedMap.begin())
  {
    currEventHolderVector = &itEHM->second;
    for (itEH = currEventHolderVector->begin(); itEH != currEventHolderVector->end(); itEH = currEventHolderVector->begin())
    {
      currEventHolder = *itEH;
      currEventHolderVector->erase(itEH);
      delete currEventHolder;
    }
    fedTime = itEHM->first;
    eventsTimedMap.erase(itEHM);
    delete fedTime;
  }

  for (itRWT = removeObjectsWithTime.begin(); itRWT !=  removeObjectsWithTime.end(); itRWT = removeObjectsWithTime.begin())
  {
    currRemoveWithTime = itRWT->second;
    removeObjectsWithTime.erase(itRWT);
    delete currRemoveWithTime;
  }

  for (itR = removeObjects.begin(); itR !=  removeObjects.end(); itR = removeObjects.begin())
  {
    currRemove = *itR;
    removeObjects.erase(itR);
    delete currRemove;
  }

  for (itTERHM = timeERHandleMap.begin(); itTERHM != timeERHandleMap.end(); itTERHM = timeERHandleMap.begin())
  {
    timeERHandleMap.erase(itTERHM);
  }

  for (itERHTM = eRHandleTimeMap.begin(); itERHTM != eRHandleTimeMap.end(); itERHTM = eRHandleTimeMap.begin())
  {
    fedTime = itERHTM->second;
    eRHandleTimeMap.erase(itERHTM);
    delete fedTime;
  }

  for (itHEM = handleErMap.begin(); itHEM != handleErMap.end(); itHEM = handleErMap.begin())
  {
    currERHandleTimeMap = &itHEM->second;
    for (itERHTM = currERHandleTimeMap->begin(); itERHTM != currERHandleTimeMap->end(); itERHTM = currERHandleTimeMap->begin())
    {
      fedTime = itERHTM->second;
      currERHandleTimeMap->erase(itERHTM);
      delete fedTime;
    }
    handleErMap.erase(itHEM);
  }

  for (itRCA = regionClassAttMap.begin(); itRCA != regionClassAttMap.end(); itRCA = regionClassAttMap.begin())
  {
    for (itHSM = itRCA->second.begin(); itHSM != itRCA->second.end(); itHSM = itRCA->second.begin())
    {
      itRCA->second.erase(itHSM);
    }

    regionClassAttMap.erase(itRCA);
  }

  for (itTEM = timeErMultimap.begin(); itTEM !=  timeErMultimap.end(); itTEM = timeErMultimap.begin())
  {
    GERTICO::GeRtiFedTime *ptr;
    ptr = itTEM->first;
    timeErMultimap.erase(itTEM);
    delete ptr;
  }

  interactionsReceivedBestEffort.clear();
  interactionsReceivedReliable.clear();
  reflectionsReceivedBestEffort.clear();
  reflectionsReceivedReliable.clear();

  federateState = Running;

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::delERHandle(GeRtiFactory::ERHandle const &theERHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::delERHandle", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::ERHandleTimeMap *currERHandleTimeMap;
  GERTICO::ERHandleTimeMap::iterator itErH;
  GERTICO::HandleErMap::iterator itHEM;
  GERTICO::GeRtiFedTime *tmpFedTime;
  GERTICO::GeRtiFedTime *tmpFedTime1;

  itHEM = handleErMap.find(theERHandle.sendingFederate);
  if (itHEM != handleErMap.end())
  {
    currERHandleTimeMap = &itHEM->second;
    itErH = currERHandleTimeMap->find(theERHandle.theSerialNumber);
    if (itErH != currERHandleTimeMap->end())
    {
      tmpFedTime = itErH->second;
      if (*tmpFedTime <= *timeManagementLRC->myTimeTag)
      {
        // Events are consumed according to time management and cannot be retracted.
        currERHandleTimeMap->erase(itErH);
        delete tmpFedTime;
      }
      else
      {
        // Events are in the future and may be retracted.
        // Save the time stamp until a TAG with a time stamp greater than or equal to
        // the event time consumes the event.
        tmpFedTime1 = timeManagementLRC->geRtiFedTimeFactory.makeZero();
        *tmpFedTime1 = *tmpFedTime;
        addFlushERHandle(theERHandle, tmpFedTime1);
      }
    }
    if (currERHandleTimeMap->size() == 0)
    {
      handleErMap.erase(itHEM);
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::delERHandle", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// Delete all timestamps that are less than or equal to TAG timestamp.
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::delFlushERHandle(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::delFlushERHandle", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::ERHandleTimeMap *currERHandleTimeMap;
  GERTICO::ERHandleTimeMap::iterator itErH;
  GERTICO::HandleErMap::iterator itHEM;
  GERTICO::TimeErMultimap::iterator itTEM;
  GERTICO::GeRtiFedTime *tmpFedTime;
  GERTICO::GeRtiFedTime *tmpFedTime1;
  char buff[1024];

  for (itTEM = timeErMultimap.begin(); itTEM !=  timeErMultimap.end(); itTEM = timeErMultimap.begin())
  {
    (*itTEM->first).encode(buff);
    tmpFedTime1 = timeManagementLRC->geRtiFedTimeFactory.decode(buff);
    if (*tmpFedTime1 <= *timeManagementLRC->myTimeTag)
    {
      // Have a timestamp that is passed.
      itHEM = handleErMap.find(itTEM->second.sendingFederate);
      if (itHEM != handleErMap.end())
      {
        // Found the sending federate.
        currERHandleTimeMap = &itHEM->second;
        itErH = currERHandleTimeMap->find(itTEM->second.theSerialNumber);
        if (itErH != currERHandleTimeMap->end())
        {
          // Erase the event.
          tmpFedTime = itErH->second;
          currERHandleTimeMap->erase(itErH);
          delete tmpFedTime;
        }
      }
      // Erase the ERHandle.
      GERTICO::GeRtiFedTime *ptr;
      ptr = itTEM->first;
      timeErMultimap.erase(itTEM);
      delete ptr;
    }
    else
    {
      // Remaining timestamps are greater.
      break;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::delFlushERHandle", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::federateSaveBegun(void)
{
  federateState = Saving;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::getFederateState(GERTICO::FederateState &theFederateState)
{
  theFederateState = federateState;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::EventHandler1516::getInteractionsReceived(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::getInteractionsReceived", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return interactionsReceived;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::getInteractionsReceivedBestEffort(GERTICO::HandleMap &theInteractions)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::getInteractionsReceivedBestEffort", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  theInteractions = interactionsReceivedBestEffort;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::getInteractionsReceivedReliable(GERTICO::HandleMap &theInteractions)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::getInteractionsReceivedReliable", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  theInteractions = interactionsReceivedReliable;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::GeRtiFedTime *GERTICO::EventHandler1516::getLITS(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::getLITS", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  EventHolderMap::iterator it;

  pm.acquire();
  it = eventsTimedMap.begin();
  if (it !=  eventsTimedMap.end())
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::getLITS", "leave_1");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    pm.release();
    return it->first;
  }
  pm.release();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::getLITS", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::EventHandler1516::getROlength(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::getROlength", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return events.size();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::EventHandler1516::getReflectionsReceived(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::getReflectionsReceived", "enterLeave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return reflectionsReceived;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::getReflectionsReceivedBestEffort(GERTICO::HandleMap &theReflections)
{
  theReflections = reflectionsReceivedBestEffort;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::getReflectionsReceivedReliable(GERTICO::HandleMap &theReflections)
{
  theReflections = reflectionsReceivedReliable;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::getRestoreInProgress(void)
{
  if (federateState == Restoring || federateState == RestorePending)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::getSaveInProgress(void)
{
  if (federateState == Saving)
  {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::EventHandler1516::getTSOlength(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::getTSOlength", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  EventHolderMap::iterator itEHM;
  long l = 0;
  std::vector <EventHolder *> *currEventHolderVector;
  std::vector <EventHolder *>::iterator itEH;

  pm.acquire();
  for (itEHM = eventsTimedMap.begin(); itEHM != eventsTimedMap.end(); itEHM++)
  {
    currEventHolderVector = &itEHM->second;
    for (itEH = currEventHolderVector->begin(); itEH != currEventHolderVector->end(); itEH++)
    {
      l += 1;
    }
  }
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::getTSOlength", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return l;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::restore(DOMElement &theDOMElement)
{
/*
  DOMNode* child;
  char *tmpChar;
*/

  clear();

//std::cout << "GERTICO::EventHandler::restore not completely programmed" << std::endl;
/*
  for (child = theDOMElement.getFirstChild(); child != 0; child = child->getNextSibling())
  {
    if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      if (XMLString::compareString(child->getNodeName(),XMLString::transcode(eventHandlerStr.c_str())) == 0)
      {
      }
    }
  }
*/
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  EventHolder *currEventHolder;
  EventHolderMap::iterator itEHM;
  GeRtiFactory::Time tmpTime;
  RemoveWithTime *currRemoveWithTime;
  RemoveWithTimeMultimap::iterator itRWTM;
  TimeErMultimap::iterator itTEM;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[10000];
  int cint;
  std::vector <EventHolder *> *currEventHolderVector;
  std::vector <EventHolder *>::iterator itEH;
  unsigned int ui;
  unsigned long i;
  unsigned long ind;
  unsigned long j;
  unsigned long length;
  unsigned long lengthInd;
  unsigned long ul;
  unsigned long valueLength;

  pm.acquire();
  // Event Handler save values.
  XMLString::transcode(eventHandlerStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  // Transform remove object with time to XML.
  XMLString::transcode(removeObjectsWithTimeStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  for (itRWTM = removeObjectsWithTime.begin(); itRWTM != removeObjectsWithTime.end(); itRWTM++)
  {
    currRemoveWithTime = itRWTM->second;

    // Object.
    XMLString::transcode(objectStr.c_str(), tempStr, 99);
    elemLevel1 = theDOMDocument.createElement(tempStr);
    elemLevel0->appendChild(elemLevel1);

    // Retraction handle.
    XMLString::transcode(retractHandleStr.c_str(), tempStr, 99);
    elemLevel2 = theDOMDocument.createElement(tempStr);
    elemLevel1->appendChild(elemLevel2);
    XMLString::transcode(theSerialNumberStr.c_str(), tempStr, 99);
    ul = currRemoveWithTime->retractionHandle.theSerialNumber;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
    XMLString::transcode(sendingFederateStr.c_str(), tempStr, 99);
    ul = currRemoveWithTime->retractionHandle.sendingFederate;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);

    // Tag.
    XMLString::transcode(userTagStr.c_str(), tempStr, 99);
    length = currRemoveWithTime->myTag.length();
    for (i = 0; i < length; i++)
    {
      ui = currRemoveWithTime->myTag[i];
      sprintf(&buf[2 * i], "%02x", ui);
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);

    // Time.
    XMLString::transcode(timeStr.c_str(), tempStr, 99);
    GERTICO::ConvertTime::mapIt(tmpTime, *currRemoveWithTime->myTime);
    length = tmpTime.length();
    for (i = 0; i < length; i++)
    {
      sprintf(&buf[2 * i], "%02x", tmpTime[i]);
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);

    // Id.
    XMLString::transcode(idStr.c_str(), tempStr, 99);
    ul = currRemoveWithTime->objectId;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);
  }

  // Transform events with time to XML.
  XMLString::transcode(tsoEventsStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  for (itEHM = eventsTimedMap.begin(); itEHM != eventsTimedMap.end(); itEHM++)
  {
    currEventHolderVector = &itEHM->second;

    for (itEH = currEventHolderVector->begin(); itEH != currEventHolderVector->end(); itEH++)
    {
      currEventHolder = *itEH;

      // Event.
      XMLString::transcode(eventStr.c_str(), tempStr, 99);
      elemLevel1 = theDOMDocument.createElement(tempStr);
      elemLevel0->appendChild(elemLevel1);

      // Type.
      XMLString::transcode(typeStr.c_str(), tempStr, 99);
      switch(currEventHolder->type)
      {
        case GeRtiFactory::interaction:
        {
          strcpy(buf, "interaction");
          break;
        }
        case GeRtiFactory::obj:
        {
          strcpy(buf, "object");
          break;
        }
      }
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);

      // Value pairs.
      XMLString::transcode(valuePairsStr.c_str(), tempStr, 99);
      elemLevel1 = theDOMDocument.createElement(tempStr);
      elemLevel0->appendChild(elemLevel1);

      switch(currEventHolder->type)
      {
        case GeRtiFactory::interaction:
        {
          lengthInd = currEventHolder->hvps.length();
          for (ind = 0; ind < lengthInd; ind++)
          {
            // Value pair.
            XMLString::transcode(valuePairStr.c_str(), tempStr, 99);
            elemLevel2 = theDOMDocument.createElement(tempStr);
            elemLevel1->appendChild(elemLevel2);

            XMLString::transcode(idStr.c_str(), tempStr, 99);
            ul = currEventHolder->hvps[ind].id;
            sprintf(buf, "%lu", ul);
            XMLString::transcode(buf, tempStr1, 99);
            elemLevel2->setAttribute(tempStr, tempStr1);

            XMLString::transcode(valueStr.c_str(), tempStr, 99);
            valueLength = currEventHolder->hvps[ind].value.length();
            for (j = 0; j < valueLength; j++)
            {
              cint = currEventHolder->hvps[ind].value[j];
              sprintf(&buf[2 * j], "%02x", cint);
            }
            XMLString::transcode(buf, tempStr1, 99);
            elemLevel2->setAttribute(tempStr, tempStr1);
          }
          break;
        }
        case GeRtiFactory::obj:
        {
          lengthInd = currEventHolder->hvps.length();
          for (ind = 0; ind < lengthInd; ind++)
          {
            // Value pair.
            XMLString::transcode(valuePairStr.c_str(), tempStr, 99);
            elemLevel2 = theDOMDocument.createElement(tempStr);
            elemLevel1->appendChild(elemLevel2);

            XMLString::transcode(idStr.c_str(), tempStr, 99);
            ul = currEventHolder->hvps[ind].id;
            sprintf(buf, "%lu", ul);
            XMLString::transcode(buf, tempStr1, 99);
            elemLevel2->setAttribute(tempStr, tempStr1);

            XMLString::transcode(valueStr.c_str(), tempStr, 99);
            valueLength = currEventHolder->hvps[ind].value.length();
            for (j = 0; j < valueLength; j++)
            {
              cint = currEventHolder->hvps[ind].value[j];
              sprintf(&buf[2 * j], "%02x", cint);
            }
            XMLString::transcode(buf, tempStr1, 99);
            elemLevel2->setAttribute(tempStr, tempStr1);
          }
          break;
        }
      }


      // Tag.
      XMLString::transcode(tagStr.c_str(), tempStr, 99);
      length = currEventHolder->userSuppliedTag.length();
      for (j = 0; j < length; j++)
      {
        cint = currEventHolder->userSuppliedTag[j];
        sprintf(&buf[2 * j], "%02x", cint);
      }
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);

      // Timestamp.
      XMLString::transcode(timestampStr.c_str(), tempStr, 99);
      GERTICO::ConvertTime::mapIt(tmpTime, *currEventHolder->timestamp);
      length = tmpTime.length();
      for (i = 0; i < length; i++)
      {
        sprintf(&buf[2 * i], "%02x", tmpTime[i]);
      }
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);

      // Retraction handle.
      XMLString::transcode(retractHandleStr.c_str(), tempStr, 99);
      elemLevel2 = theDOMDocument.createElement(tempStr);
      elemLevel1->appendChild(elemLevel2);
      XMLString::transcode(theSerialNumberStr.c_str(), tempStr, 99);
      ul = currEventHolder->retractionHandle.theSerialNumber;
      sprintf(buf, "%lu", ul);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel2->setAttribute(tempStr, tempStr1);
      XMLString::transcode(sendingFederateStr.c_str(), tempStr, 99);
      ul = currEventHolder->retractionHandle.sendingFederate;
      sprintf(buf, "%lu", ul);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel2->setAttribute(tempStr, tempStr1);

      // Object id.
      XMLString::transcode(objectStr.c_str(), tempStr, 99);
      sprintf(buf, "%lu", currEventHolder->objectId);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);

      // Class id.
      XMLString::transcode(classStr.c_str(), tempStr, 99);
      sprintf(buf, "%lu", currEventHolder->classId);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);

      // Region id.
      XMLString::transcode(regionStr.c_str(), tempStr, 99);
      sprintf(buf, "%lu", currEventHolder->region);
      XMLString::transcode(buf, tempStr1, 99);
      elemLevel1->setAttribute(tempStr, tempStr1);
    }
  }

  // Transform retract handles to XML.
  XMLString::transcode(retractHandlesStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  for (itTEM = timeErMultimap.begin(); itTEM != timeErMultimap.end(); itTEM++)
  {
    GeRtiFactory::ERHandle *messageRetractionHandle;
    messageRetractionHandle = &itTEM->second;

    // Retraction handle.
    XMLString::transcode(retractHandleStr.c_str(), tempStr, 99);
    elemLevel1 = theDOMDocument.createElement(tempStr);
    elemLevel0->appendChild(elemLevel1);
    XMLString::transcode(theSerialNumberStr.c_str(), tempStr, 99);
    ul = messageRetractionHandle->theSerialNumber;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);
    XMLString::transcode(sendingFederateStr.c_str(), tempStr, 99);
    ul = messageRetractionHandle->sendingFederate;
    sprintf(buf, "%lu", ul);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);

    // Time.
    XMLString::transcode(timeStr.c_str(), tempStr, 99);
    GERTICO::ConvertTime::mapIt(tmpTime, *itTEM->first);
    length = tmpTime.length();
    for (i = 0; i < length; i++)
    {
      sprintf(&buf[2 * i], "%02x", tmpTime[i]);
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel1->setAttribute(tempStr, tempStr1);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::setDisableTimeConstrainedd(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::setDisableTimeConstrainedd", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  gotTimeConstrainedEnabled = false;
  gotTimeConstrainedEnabledFlag = false;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::setDisableTimeConstrainedd", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::setDisableTimeRegulation(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::setDisableTimeRegulation", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  gotTimeRegulationEnabled = false;
  gotTimeRegulationEnabledFlag = false;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::setDisableTimeRegulation", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::setRunTimeObjectDB(GERTICO::RunTimeObjectDB *theRunTimeObjectDB)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::setRunTimeObjectDB", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  runTimeObjectDB = theRunTimeObjectDB;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::setRunTimeObjectDB", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::setFederate(GeRtiFactory::GeRtiHandle const &theFederate)
{
  federateId = theFederate;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::setFederateAmbassador(RTI::FederateAmbassador *theFederateAmbassador)
{
  clear();
  init();
  federateAmbassador = theFederateAmbassador;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::setFlushQueueRequest(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::setFlushQueueRequest", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  ehRequest = EHFlush;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::setFlushQueueRequest", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::setTimeService(GERTICO::TimeManagementLRC *theTimeManagementLRC)
{
  timeManagementLRC = theTimeManagementLRC;
  myConstrainedTime.reset(timeManagementLRC->geRtiFedTimeFactory.makeZero());
  myRegulationTime.reset(timeManagementLRC->geRtiFedTimeFactory.makeZero());
  timeManagementLRC->myTimeSave.reset(timeManagementLRC->geRtiFedTimeFactory.makeZero());
  timeManagementLRC->myTimeSave->setPositiveInfinity();
}

// ---------------------------------------------------------------------------
// Process receive ordered messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processEventRo(bool const &enableRegulation)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::processEventRo", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  EventHolder *currEventHolder;
  std::vector <EventHolder *>::iterator it;
  bool ret = false;

  if (enableRegulation == false)
  {
    if (gotTimeConstrainedEnabled)
    {
      if (asynchronousDelivery == false)
      {
        // Only in time advancing state.
        if (ehRequest == EHNone)
        {
                           {   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::processEventRo", "leave_1");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
          return ret;
                           }   // inserted by Gal converter
        }
      }
    }
  }

  pm.acquire();
  // RO messages.
  it = events.begin();
  if (it != events.end())
  {
    currEventHolder = *it;

    events.erase(it);

    switch(currEventHolder->type)
    {
      case GeRtiFactory::interaction:
      {
        if (processEventRoInteraction(*currEventHolder))
        {
          ret = true;
        }
        break;
      }
      case GeRtiFactory::obj:
      {
        if (processEventRoObject(*currEventHolder))
        {
          ret = true;
        }
        break;
      }
      default:
      {
        break;
      }
    }
    delete currEventHolder;
  }
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::processEventRo", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
// Process receive ordered interaction messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processEventRoInteraction(EventHolder &currEventHolder)
{
  RTI::InteractionClassHandle interactionClassHandle;
  RTI::UserSuppliedTag userSuppliedTag;
  std::auto_ptr<RTI::ParameterHandleValueMap> phvps(new RTI::ParameterHandleValueMap());
  std::string s = "receive";
  std::string t = "reliable";
  bool ret = false;

  GERTICO::Mapper1516::mapInteractionClassHandle(interactionClassHandle, currEventHolder.classId);

  GERTICO::Mapper1516::mapParameterHandleValueMap(*phvps, currEventHolder.hvps);

  GERTICO::Mapper1516::mapUserSuppliedTag(userSuppliedTag, currEventHolder.userSuppliedTag);

  RTI::OrderType sentOrder(RTI::OrderType::receive());
  if (currEventHolder.timestamp.get())
  {
    s = "timestamp";
    sentOrder = RTI::OrderType::timestamp();
  }

  RTI::TransportationType transportationType(RTI::TransportationType::reliable());
  if (currEventHolder.bestEffort)
  {
    t = "best_effort";
    transportationType = RTI::TransportationType::bestEffort();
  }

  ret = true;
  try
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pERI_i0)
                            {
                              unsigned int indItem;
                              unsigned long lenItems;
                              unsigned long ul;

                              ul = currEventHolder.classId;
                              sprintf(galMsg, "interaction=%lu,order=%s,transportation=%s", ul, s.c_str(), t.c_str());
                              lenItems = currEventHolder.hvps.length();
                              for (indItem = 0; indItem < lenItems; indItem++)
                              {
                                GERTICO::Mapper::printAttributeHandleValue("data=", galMsg, currEventHolder.hvps[indItem]);
                                E1mEnd(pERI_i0,galMsg);
                              }
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, currEventHolder.userSuppliedTag);
                              E1mEnd(pERI_i0,galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    federateAmbassador->receiveInteraction(interactionClassHandle, phvps, userSuppliedTag, sentOrder, transportationType);
    interactionsReceived += 1;
    if (currEventHolder.bestEffort)
    {
      addHandleMap(currEventHolder.classId, interactionsReceivedBestEffort);
    }
    else
    {
      addHandleMap(currEventHolder.classId, interactionsReceivedReliable);
    }
  }
  catch(RTI::InteractionClassNotRecognized)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pERI_ta,"InteractionClassNotRecognized");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::InteractionParameterNotRecognized)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pERI_ta,"InteractionParameterNotRecognized");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::InteractionClassNotSubscribed)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pERI_ta,"InteractionClassNotSubscribed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::FederateInternalError)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pERI_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::getSubscribedAttributes(RTI::AttributeHandleValueMap &theAttributeHandleValueMap, EventHolder &theEventHolder)
{
  GERTICO::HandleSet hs;
  GERTICO::HandleSet *phs = NULL;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetMap *classAttributes = NULL;
  GERTICO::HandleSetSetMap::iterator itRCA;
  GERTICO::RegisteredObject *objPtr;
  GeRtiFactory::GeRtiHandle attribute;
  GeRtiFactory::GeRtiHandle classId;
  RTI::AttributeHandle attributeHandle;
  size_t s;
  unsigned long lenj;
  unsigned long ul;
  unsigned long size;

  size = theEventHolder.hvps.length();
  if (size == 0)
  {
    return;
  }

  // Find the known class.
  try
  {
    objPtr = runTimeObjectDB->getObject(theEventHolder.objectId);
    classId = objPtr->getClassId();
  }
  catch(...)
  {
    return;
  }

  // Process the attributes.
  for (ul = 0; ul < size; ul++)
  {
    attribute = theEventHolder.hvps[ul].id;

    // Search the regions.
    for (itRCA = regionClassAttMap.begin(); itRCA != regionClassAttMap.end(); itRCA++)
    {
      classAttributes = &itRCA->second;

      itHSM = classAttributes->find(classId);
      if (itHSM != classAttributes->end())
      {
        phs = &itHSM->second;
        itHS = phs->find(attribute);
        if (itHS != phs->end())
        {
          hs.insert(attribute);
        }
      }
    }
  }

  s = hs.size();
  if (s == 0)
  {
    return;
  }

  for (itHS = hs.begin(); itHS != hs.end(); itHS++)
  {
    for (ul = 0; ul < s; ul++)
    {
      if (theEventHolder.hvps[ul].id == *itHS)
      {
        GERTICO::Mapper1516::mapAttributeHandle(attributeHandle, *itHS);

        // Copy the attribute value.
        lenj = theEventHolder.hvps[ul].value.length();
        RTI::AttributeValue attributeValue((const void *)&theEventHolder.hvps[ul].value[0], lenj);
        theAttributeHandleValueMap[attributeHandle] = attributeValue;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::queryMinNextEventTime(GERTICO::GeRtiFedTime &theTime)
{
  EventHolderMap::iterator itEHM;

  pm.acquire();
  itEHM = eventsTimedMap.begin();
  if (itEHM != eventsTimedMap.end())
  {
    theTime = *itEHM->first;
  }
  else
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> t(timeManagementLRC->geRtiFedTimeFactory.makeZero());
    t->setPositiveInfinity();
    theTime = *t;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::processConfirmFederationRestorationRequest(std::wstring const &theLabel, bool const &myReason)
{
  restoreLabel = theLabel;
  if (myReason)
  {
    confirmRestoreSuccess = true;
  }
  else
  {
    confirmRestoreSuccess = false;
  }

  gotConfirmFederationRestorationRequest = true;

  pm.acquire();
  if (gotConfirmFederationRestorationRequest)
  {
    try
    {
      if (confirmRestoreSuccess)
      {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pCFRR_i0)
                            {
//                              sprintf(galMsg,"label=%s",restoreLabel.c_str());
//                              E1mEnd(pCFRR_i0,galMsg);
                            }
                          #endif   // inserted by Gal converter
        federateAmbassador->requestFederationRestoreSucceeded(restoreLabel);
        stateRestore = true;
      }
      else
      {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pCFRR_i1)
                            {
//                              sprintf(galMsg,"label=%s",restoreLabel.c_str());
//                              E1mEnd(pCFRR_i1,galMsg);
                            }
                           #endif   // inserted by Gal converter
        federateAmbassador->requestFederationRestoreFailed(restoreLabel);
        stateRestore = false;
      }
    }
    catch(...)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pCFRR_ts, "FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

    gotConfirmFederationRestorationRequest = false;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
// Process receive ordered object messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processEventRoObject(EventHolder &currEventHolder)
{
  RTI::ObjectInstanceHandle objectHandle;
  RTI::UserSuppliedTag userSuppliedTag;
  std::auto_ptr<RTI::AttributeHandleValueMap> tmp(new RTI::AttributeHandleValueMap());

  std::auto_ptr<RTI::AttributeHandleValueMap> attributeHandleValueMapAutoPtr(new RTI::AttributeHandleValueMap);
  bool ret = false;

  try
  {
    // Deliver reflect only if object known
    runTimeObjectDB->getObject(currEventHolder.objectId);
  }
  catch(GeRtiFactory::ObjectNotKnown&)
  {
    ret = true;
    return ret;
  }

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, currEventHolder.objectId);

  getSubscribedAttributes(*attributeHandleValueMapAutoPtr, currEventHolder);

  if (attributeHandleValueMapAutoPtr->size() == 0)
  {
    ret = true;
    return ret;
  }

  GERTICO::Mapper1516::mapUserSuppliedTag(userSuppliedTag, currEventHolder.userSuppliedTag);

  RTI::OrderType sentOrder(RTI::OrderType::receive());
  if (currEventHolder.timestamp.get())
  {
    sentOrder = RTI::OrderType::timestamp();
  }

  RTI::TransportationType transportationType(RTI::TransportationType::reliable());
  if (currEventHolder.bestEffort)
  {
    transportationType = RTI::TransportationType::bestEffort();
  }

  ret = true;
  try
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pERO_i0)
                            {
                              unsigned int indItem;
                              unsigned long lenItems;
                              unsigned long ul;

                              ul = currEventHolder.objectId;
                              sprintf(galMsg, "object=%lu", ul);
                              E1mEnd(pERO_i0,galMsg);
                              lenItems = currEventHolder.hvps.length();
                              for (indItem = 0; indItem < lenItems; indItem++)
                              {
                                GERTICO::Mapper::printAttributeHandleValue("data=", galMsg, currEventHolder.hvps[indItem]);
                                E1mEnd(pERO_i0,galMsg);
                              }
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, currEventHolder.userSuppliedTag);
                              E1mEnd(pERO_i0,galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    federateAmbassador->reflectAttributeValues(objectHandle, attributeHandleValueMapAutoPtr, userSuppliedTag, sentOrder, transportationType);
    reflectionsReceived += 1;
    if (currEventHolder.bestEffort)
    {
      addHandleMap(currEventHolder.classId, reflectionsReceivedBestEffort);
    }
    else
    {
      addHandleMap(currEventHolder.classId, reflectionsReceivedReliable);
    }
  }
  catch(RTI::ObjectInstanceNotKnown)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pERO_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::AttributeNotRecognized)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pERO_ta,"AttributeNotRecognized");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::AttributeNotSubscribed)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pERO_ta,"AttributeNotSubscribed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::FederateInternalError)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pERO_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  return ret;
}

// ---------------------------------------------------------------------------
// Process time stamp ordered messages
// This function must have pm.acquire() before and pm.release() after function
// call
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processEventTso(bool const &enableRegulation)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::processEventTso", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  EventHolder *currEventHolder;
  EventHolderMap::iterator itEHM;
  std::vector <EventHolder *> *currEventHolderVector;
  std::vector <EventHolder *>::iterator itEH;
  bool ret = false;

  // Condition for delivery of events.
  if (enableRegulation == false)
  {
    if (gotTimeConstrainedEnabled)
    {
      if (timeManagementLRC->gotTimeAdvanceGrant == false)
      {
        if (ehRequest == EHTar)
        {
          if (timeManagementLRC->gotTimeAdvanceGrantIntermediate == false)
          {
            return ret;
          }
        }
        else
        {
          return ret;
        }
      }
    }
  }

  // TSO messages.
  itEHM = eventsTimedMap.begin();
  if (itEHM != eventsTimedMap.end())
  {
    if (gotTimeConstrainedEnabled)
    {
      // A flush queue request means process all events.
      if (ehRequest != EHFlush)
      {
          if (timeManagementLRC->gotAnnounceFederateSaveWithTime)
          {
            // Limit on the events processed is save time.
            if (*itEHM->first > *timeManagementLRC->myTimeSave)
            {
              return ret;
            }
          }

        // Limit on the events processed is grant time.
        if (timeManagementLRC->gotTimeAdvanceGrant || enableRegulation)
        {
          char buff[1024];
          timeManagementLRC->myTimeTag->getPrintableString(buff);
          itEHM->first->getPrintableString(buff);
          if (*itEHM->first > *timeManagementLRC->myTimeTag)
          {
            return ret;
          }
        }
        else
        {
          if (ehRequest == EHTar)
          {
            char buff[1024];
            timeManagementLRC->myTimeTarGalt->getPrintableString(buff);
            itEHM->first->getPrintableString(buff);
            if (*itEHM->first > *timeManagementLRC->myTimeTarGalt)
            {
              return ret;
            }
          }
          else
          {
            return ret;
          }
        }
      }
    }

    currEventHolderVector = &itEHM->second;

    itEH = currEventHolderVector->begin();
    if (itEH != currEventHolderVector->end())
    {
      currEventHolder = *itEH;
      currEventHolderVector->erase(itEH);

      delERHandle(currEventHolder->retractionHandle);
      switch(currEventHolder->type)
      {
        case GeRtiFactory::interaction:
        {
          if (gotTimeConstrainedEnabled)
          {
            if (processEventTsoInteraction(*currEventHolder))
            {
              ret = true;
            }
          }
          else
          {
            if (processEventRoInteraction(*currEventHolder))
            {
              ret = true;
            }
          }
          break;
        }
        case GeRtiFactory::obj:
        {
          if (gotTimeConstrainedEnabled)
          {
            if (processEventTsoObject(*currEventHolder))
            {
              ret = true;
            }
          }
          else
          {
            if (processEventRoObject(*currEventHolder))
            {
              ret = true;
            }
          }
          break;
        }
        default:
        {
          break;
        }
      }
      delete currEventHolder;
    }
    if (currEventHolderVector->size() == 0)
    {
      GERTICO::GeRtiFedTime *fedTime;
      fedTime = itEHM->first;
      eventsTimedMap.erase(itEHM);
      delete fedTime;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_d, "EventHandler1516::processEventTso", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
// Process time stamp ordered interaction messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processEventTsoInteraction(EventHolder &currEventHolder)
{
  RTI::InteractionClassHandle interactionClassHandle;
  RTI::MessageRetractionHandle *messageRetractionHandle = new RTI::MessageRetractionHandle();
  RTI::UserSuppliedTag userSuppliedTag;
  std::auto_ptr<RTI::ParameterHandleValueMap> phvps(new RTI::ParameterHandleValueMap());

  GERTICO::Mapper1516::mapInteractionClassHandle(interactionClassHandle, currEventHolder.classId);

  GERTICO::Mapper1516::mapParameterHandleValueMap(*phvps, currEventHolder.hvps);

  GERTICO::Mapper1516::mapUserSuppliedTag(userSuppliedTag, currEventHolder.userSuppliedTag);
  bool ret = false;

  RTI::OrderType sentOrder(RTI::OrderType::receive());
  if (currEventHolder.timestamp.get())
  {
    sentOrder = RTI::OrderType::timestamp();
  }

  RTI::TransportationType transportationType(RTI::TransportationType::reliable());
  if (currEventHolder.bestEffort)
  {
    transportationType = RTI::TransportationType::bestEffort();
  }

  RTI::OrderType receiveOrder(RTI::OrderType::receive());
  if (currEventHolder.timestamp.get())
  {
    receiveOrder = RTI::OrderType::timestamp();
  }

  GERTICO::Mapper1516::mapMessageRetractionHandle(*messageRetractionHandle, currEventHolder.retractionHandle);

  ret = true;
  try
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pETI_i0)
                            {
                              char buff[512];

                              currEventHolder.timestamp->getPrintableString(buff);
                              sprintf(galMsg,"interaction=%lu,time=%s,sendingFederate=%lu",
                                currEventHolder.classId,buff,currEventHolder.retractionHandle);
                              E1mEnd(pERI_i0,galMsg);   // inserted by Gal converter
//                              ut::printParameterHandleValuePairSet(galMsg,*(currEventHolder.phvps));
//                              E1mEnd(pETI_i0,galMsg);
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, currEventHolder.userSuppliedTag);
                              E1mEnd(pERI_i0,galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    federateAmbassador->receiveInteraction(interactionClassHandle, phvps, userSuppliedTag, sentOrder, transportationType, *currEventHolder.rtiTimestamp, receiveOrder, *messageRetractionHandle);
    interactionsReceived += 1;
    if (currEventHolder.bestEffort)
    {
      addHandleMap(currEventHolder.classId, interactionsReceivedBestEffort);
    }
    else
    {
      addHandleMap(currEventHolder.classId, interactionsReceivedReliable);
    }
  }
  catch(RTI::InteractionClassNotRecognized)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pETI_ta,"InteractionClassNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::InteractionParameterNotRecognized)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pETI_ta,"InteractionParameterNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::InteractionClassNotSubscribed)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pETI_ta,"InteractionClassNotSubscribed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::InvalidLogicalTime)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pETI_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::FederateInternalError)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pETI_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  return ret;
}

// ---------------------------------------------------------------------------
// Process time stamp ordered object messages
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processEventTsoObject(EventHolder &currEventHolder)
{
  RTI::MessageRetractionHandle *messageRetractionHandle = new RTI::MessageRetractionHandle();
  RTI::ObjectInstanceHandle objectHandle;
  RTI::UserSuppliedTag userSuppliedTag;
  std::string s = "receive";
  std::string t = "reliable";

  std::auto_ptr<RTI::AttributeHandleValueMap> attributeHandleValueMapAutoPtr(new RTI::AttributeHandleValueMap);
  bool ret = false;

  try
  {
    // Deliver reflect only if object known
    runTimeObjectDB->getObject(currEventHolder.objectId);
  }
  catch(GeRtiFactory::ObjectNotKnown&)
  {
    return ret;
  }

  GERTICO::Mapper1516::mapObjectInstanceHandle(objectHandle, currEventHolder.objectId);

  getSubscribedAttributes(*attributeHandleValueMapAutoPtr, currEventHolder);

  if (attributeHandleValueMapAutoPtr->size() == 0)
  {
    return ret;
  }

  GERTICO::Mapper1516::mapUserSuppliedTag(userSuppliedTag, currEventHolder.userSuppliedTag);

  RTI::OrderType sentOrder(RTI::OrderType::receive());
  if (currEventHolder.timestamp.get())
  {
    s = "timestamp";
    sentOrder = RTI::OrderType::timestamp();
  }

  RTI::TransportationType transportationType(RTI::TransportationType::reliable());
  if (currEventHolder.bestEffort)
  {
    t = "best_effort";
    transportationType = RTI::TransportationType::bestEffort();
  }

  RTI::OrderType receiveOrder(RTI::OrderType::receive());
  if (currEventHolder.timestamp.get())
  {
    receiveOrder = RTI::OrderType::timestamp();
  }

  GERTICO::Mapper1516::mapMessageRetractionHandle(*messageRetractionHandle, currEventHolder.retractionHandle);

  ret = true;
  try
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pETO_i0)
                            {
                              char buf[512];
                              unsigned int indItem;
                              unsigned long lenItems;
                              unsigned long ul;

                              ul = currEventHolder.objectId;
                              currEventHolder.timestamp->getPrintableString(buf);
                              sprintf(galMsg, "object=%lu,order=%s,transport=%s,time=%s,sendingFederate=%lu", ul, s.c_str(), t.c_str(), buf, currEventHolder.retractionHandle);
                              E1mEnd(pETO_i0,galMsg);
                              lenItems = currEventHolder.hvps.length();
                              for (indItem = 0; indItem < lenItems; indItem++)
                              {
                                GERTICO::Mapper::printAttributeHandleValue("data=", galMsg, currEventHolder.hvps[indItem]);
                                E1mEnd(pETO_i0,galMsg);
                              }
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, currEventHolder.userSuppliedTag);
                              E1mEnd(pETO_i0,galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
    federateAmbassador->reflectAttributeValues(objectHandle, attributeHandleValueMapAutoPtr, userSuppliedTag, sentOrder, transportationType, *currEventHolder.rtiTimestamp, receiveOrder, *messageRetractionHandle);
    reflectionsReceived += 1;
    if (currEventHolder.bestEffort)
    {
      addHandleMap(currEventHolder.classId, reflectionsReceivedBestEffort);
    }
    else
    {
      addHandleMap(currEventHolder.classId, reflectionsReceivedReliable);
    }
  }
  catch(RTI::ObjectInstanceNotKnown)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pETO_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::AttributeNotRecognized)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pETO_ta,"AttributeNotRecognized");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::AttributeNotSubscribed)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pETO_ta,"AttributeNotSubscribed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::InvalidLogicalTime)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pETO_ta,"InvalidLogicalTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::FederateInternalError)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pETO_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::processFederationRestoreBegun(void)
{
  federateState = RestorePending;

  pm.acquire();
    try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E0(pFRB_i0);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
      federateAmbassador->federationRestoreBegun();
    }
    catch(...)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pFRB_i0,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

  pm.release();
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::processFederationSaved(bool const &theSuccess, GeRtiFactory::SaveFailureReason const &theFailureReason)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::processFederationSaved", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  federateState = Running;
  saveFailureReason = theFailureReason;

  pm.acquire();
    try
    {
      if (theSuccess)
      {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pFS_i0,"Saved");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
        federateAmbassador->federationSaved();
      }
      else
      {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pFS_i0,"Not Saved");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
        switch (saveFailureReason)
        {
          case GeRtiFactory::rtiUnableToSave:
          {
            RTI::SaveFailureReason saveFailureReason(RTI::SaveFailureReason::rtiUnableToSave());

            federateAmbassador->federationNotSaved(saveFailureReason);
            break;
          }
          case GeRtiFactory::federateReportedFailureDuringSave:
          {
            RTI::SaveFailureReason saveFailureReason(RTI::SaveFailureReason::federateReportedFailureDuringSave());

            federateAmbassador->federationNotSaved(saveFailureReason);
            break;
          }
          case GeRtiFactory::federateResignedDuringSave:
          {
            RTI::SaveFailureReason saveFailureReason(RTI::SaveFailureReason::federateResignedDuringSave());

            federateAmbassador->federationNotSaved(saveFailureReason);
            break;
          }
          case GeRtiFactory::rtiDetectedFailureDuringSave:
          {
            RTI::SaveFailureReason saveFailureReason(RTI::SaveFailureReason::rtiDetectedFailureDuringSave());

            federateAmbassador->federationNotSaved(saveFailureReason);
            break;
          }
          case GeRtiFactory::saveTimeCannotBeHonored:
          {
            RTI::SaveFailureReason saveFailureReason(RTI::SaveFailureReason::saveTimeCannotBeHonored());

            federateAmbassador->federationNotSaved(saveFailureReason);
            break;
          }
        }
      }
    }
    catch(...)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pFS_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    gotAnnounceFederateSave = false;
    timeManagementLRC->gotAnnounceFederateSaveWithTime = false;
    stateSave = false;
    timeManagementLRC->myTimeSave->setPositiveInfinity();

  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_d, "EventHandler1516::processFederationSaved", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::processInitiateFederateRestore(std::wstring const &theLabel, GeRtiFactory::GeRtiHandle const &theFederate)
{
  restoreLabel = theLabel;
  federate = theFederate;
  federateState = Restoring;

  pm.acquire();
    RTI::FederateHandle fedHandle;

    GERTICO::Mapper1516::mapFederateHandle(fedHandle, federate);
    try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pIFR_i0)
                            {
                              sprintf(galMsg, "label=%s,handle=%lu", restoreLabel.c_str(), federate);
                              E1mEnd(pIFR_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      federateAmbassador->initiateFederateRestore(restoreLabel, fedHandle);
    }
    catch(...)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pIFR_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::processFederationRestored(bool const &theSuccess, GeRtiFactory::RestoreFailureReason const &theFailureReason)
{
  federateState = Running;
  restoreFailureReason = theFailureReason;

  pm.acquire();
    try
    {
      if (theSuccess)
      {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pFR_i0,"Succeeded");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
        federateAmbassador->federationRestored();
      }
      else
      {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pFR_i0,"Failed");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
        switch (restoreFailureReason)
        {
          case GeRtiFactory::rtiUnableToRestore:
          {
            RTI::RestoreFailureReason restoreFailureReason(RTI::RestoreFailureReason::rtiUnableToRestore());

            federateAmbassador->federationNotRestored(restoreFailureReason);
            break;
          }
          case GeRtiFactory::federateReportedFailureDuringRestore:
          {
            RTI::RestoreFailureReason restoreFailureReason(RTI::RestoreFailureReason::federateReportedFailureDuringRestore());

            federateAmbassador->federationNotRestored(restoreFailureReason);
            break;
          }
          case GeRtiFactory::federateResignedDuringRestore:
          {
            RTI::RestoreFailureReason restoreFailureReason(RTI::RestoreFailureReason::federateResignedDuringRestore());

            federateAmbassador->federationNotRestored(restoreFailureReason);
            break;
          }
          case GeRtiFactory::rtiDetectedFailureDuringRestore:
          {
            RTI::RestoreFailureReason restoreFailureReason(RTI::RestoreFailureReason::rtiDetectedFailureDuringRestore());

            federateAmbassador->federationNotRestored(restoreFailureReason);
            break;
          }
        }
      }
    }
    catch(...)
    {
    }

    stateRestore = false;

  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processInitiateFederateSave(void)
{
  CORBA::Boolean fedTimeBoolean = 0;
  CORBA::WChar *l;
  GeRtiFactory::Time fedTime;
  std::auto_ptr<GERTICO::GeRtiFedTime> galt(timeManagementLRC->geRtiFedTimeFactory.makeZero());
  bool ret = false;

  federateState = SavePending;
  // Block TSO events.
//  stateSave = true;

  pm.acquire();
  if (gotAnnounceFederateSave || timeManagementLRC->gotAnnounceFederateSaveWithTime)
  {
    if (gotTimeConstrainedEnabled)
    {
      if (timeManagementLRC->gotAnnounceFederateSaveWithTime)
      {
        if (*timeManagementLRC->myTimeSave > *timeManagementLRC->myTimeRequested)
        {
          pm.release();
          return ret;
        }
        if (timeManagementLRC)
        {
          timeManagementLRC->queryGALT(*galt);
        }
        if (*timeManagementLRC->myTimeSave >= *galt)
        {
          pm.release();
          return ret;
        }
      }
    }

    // Test case 4623 - initiateFederateSave only in advancing state
    if (gotTimeConstrainedEnabled)
    {
      if (ehRequest == EHNone)
      {
        pm.release();
        return ret;
      }
    }

    try
    {
      if (timeManagementLRC->gotAnnounceFederateSaveWithTime)
      {
        fedTimeBoolean = 1;
      }
      GERTICO::ConvertTime::mapIt(fedTime, *timeManagementLRC->myTimeSave);
      GERTICO::Mapper::mapWcharFromWstring(&l, saveLabel);
      geRtiAmVar->requestFederateSaveStart(l, fedTime, fedTimeBoolean);
    }
    catch(GeRtiFactory::StartNotAllowed &)
    {
      CORBA::wstring_free(l);
      pm.release();
      return ret;
    }
    catch(...)
    {
      CORBA::wstring_free(l);
      pm.release();
      return ret;
    }

    gotAnnounceFederateSave = false;

    try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pIFS_i0)
                            {
//                              sprintf(galMsg,"label=%s",saveLabel.c_str());
//                              E1mEnd(pIFS_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
#ifdef IEEE_1516
      if (timeManagementLRC->gotAnnounceFederateSaveWithTime)
      {
        RTI::EncodedLogicalTime *encodedLogicalTime;
        std::auto_ptr<RTI::LogicalTime> logicalTime = timeManagementLRC->geRtiFedTimeFactory.logicalTimeFactory.makeInitial();
        GERTICO::Mapper1516::mapEncodedLogicalTime(&encodedLogicalTime, *timeManagementLRC->myTimeSave);
        logicalTime = timeManagementLRC->geRtiFedTimeFactory.logicalTimeFactory.decode(*encodedLogicalTime);
        federateAmbassador->initiateFederateSave(saveLabel, *logicalTime);
      }
      else
      {
        federateAmbassador->initiateFederateSave(saveLabel);
      }
#else
      federateAmbassador->initiateFederateSave(saveLabel);
#endif
      ret = true;
      stateSave = true;
      federateState = Saving;
    }
    catch(...)
    {
//Test for ut.cpp on Linux 9.1
//pm.release();
//throw;
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pIFS_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
  }
  pm.release();
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processRemove(void)
{
  GERTICO::Remove *currRemove;
  RTI::ObjectInstanceHandle objectInstanceHandle;
  RTI::UserSuppliedTag userSuppliedTag;
  std::vector <GERTICO::Remove *>::iterator it;
  bool ret = false;

  if (gotTimeConstrainedEnabled)
  {
    if (asynchronousDelivery == false)
    {
      // Only in time advancing state.
      if (ehRequest == EHNone)
      {
        return ret;
      }
    }
  }

  RTI::OrderType sentOrder(RTI::OrderType::receive());

  pm.acquire();
  ret = true;
  // Get begin () until all processed.
  it = removeObjects.begin();
  if (it !=  removeObjects.end())
  {
    currRemove = *it;
    removeObjects.erase(it);

    GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, currRemove->objectId);
    GERTICO::Mapper1516::mapUserSuppliedTag(userSuppliedTag, currRemove->myTag);
    if (currRemove->sendOrderTso)
    {
      sentOrder = RTI::OrderType::timestamp();
    }
    else
    {
      sentOrder = RTI::OrderType::receive();
    }

    try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pR_i0)
                            {
                              sprintf(galMsg, "object=%lu", currRemove->objectId);
                              E1mEnd(pR_i0,galMsg);
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, currRemove->myTag);
                              E1mEnd(pR_i0,galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      federateAmbassador->removeObjectInstance(objectInstanceHandle, userSuppliedTag, sentOrder);
    }
    catch(RTI::ObjectInstanceNotKnown)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pR_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::FederateInternalError)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pR_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

    try
    {
      runTimeObjectDB->removeObjectInstance(currRemove->objectId);
    }
    catch(GeRtiFactory::ObjectClassNotPublished)
    {
    }

    delete currRemove;
  }
  pm.release();
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processRemoveWithTime(bool const &enableRegulation)
{
  RemoveWithTime *currRemoveWithTime;
  RemoveWithTimeMultimap::iterator it;
  std::auto_ptr< RTI::MessageRetractionHandle > messageRetractionHandle;
  RTI::ObjectInstanceHandle objectInstanceHandle;
  RTI::UserSuppliedTag userSuppliedTag;
  std::auto_ptr<RTI::LogicalTime> logicalTime = timeManagementLRC->geRtiFedTimeFactory.logicalTimeFactory.makeInitial();
  bool ret = false;

  if (enableRegulation == false)
  {
    if (gotTimeConstrainedEnabled)
    {
      if (timeManagementLRC->gotTimeAdvanceGrant == false)
      {
        return ret;
      }
    }
  }

  // Get begin () until all processed.
  it = removeObjectsWithTime.begin();
  if (it !=  removeObjectsWithTime.end())
  {
    currRemoveWithTime = it->second;

    if (gotTimeConstrainedEnabled)
    {
      // A flush queue request means process all events.
      if (ehRequest != EHFlush)
      {
        // Limit on the events processed.
          if (gotAnnounceFederateSave)
          {
            if (*currRemoveWithTime->myTime > *timeManagementLRC->myTimeSave)
            {
              return ret;
            }
          }

        if (*currRemoveWithTime->myTime > *timeManagementLRC->myTimeTag)
        {
          return ret;
        }
      }
    }

    removeObjectsWithTime.erase(it);

//    pm.acquire();
    delERHandle(currRemoveWithTime->retractionHandle);
//    pm.release();

    try
    {
      // get object only for test if known
      // runTimeObjectDB->getObject(currRemoveWithTime->objectId);

      GERTICO::Mapper1516::mapObjectInstanceHandle(objectInstanceHandle, currRemoveWithTime->objectId);
      GERTICO::Mapper1516::mapUserSuppliedTag(userSuppliedTag, currRemoveWithTime->myTag);

      RTI::OrderType sentOrder(RTI::OrderType::receive());
      if (currRemoveWithTime->sendOrderTso)
      {
        sentOrder = RTI::OrderType::timestamp();
      }

      ret = true;
      if (gotTimeConstrainedEnabled)
      {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pRWT_i0)
                            {
                              char buf[512];
                              unsigned long ul;
                              unsigned long ul1;

                              ul = currRemoveWithTime->objectId;
                              ul1 = currRemoveWithTime->retractionHandle.sendingFederate;
                              currRemoveWithTime->myTime->getPrintableString(buf);
                              sprintf(galMsg, "object=%lu,time=%s,sendingFederate=%lu", ul, buf, ul1);
                              E1mEnd(pRWT_i0,galMsg);
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, currRemoveWithTime->myTag);
                              E1mEnd(pRWT_i0,galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
        RTI::MessageRetractionHandle *messageRetractionHandlePtr = new RTI::MessageRetractionHandle();
        std::auto_ptr<GERTICO::GeRtiFedTime> fedTime(timeManagementLRC->geRtiFedTimeFactory.makeZero());
        RTI::EncodedLogicalTime *encodedLogicalTime;
        *fedTime = *currRemoveWithTime->myTime;
        GERTICO::Mapper1516::mapEncodedLogicalTime(&encodedLogicalTime, *fedTime);
        logicalTime = timeManagementLRC->geRtiFedTimeFactory.logicalTimeFactory.decode(*encodedLogicalTime);
        GERTICO::Mapper1516::mapMessageRetractionHandle(*messageRetractionHandlePtr, currRemoveWithTime->retractionHandle);
        std::auto_ptr<RTI::MessageRetractionHandle> tmp(messageRetractionHandlePtr);
        messageRetractionHandle = tmp;

        RTI::OrderType receiveOrder(RTI::OrderType::receive());
        if (currRemoveWithTime->myTime)
        {
          receiveOrder = RTI::OrderType::timestamp();
        }

        federateAmbassador->removeObjectInstance(objectInstanceHandle, userSuppliedTag, sentOrder, *logicalTime, receiveOrder, *messageRetractionHandle);
      }
      else
      {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pRWT_i0)
                            {
                              unsigned long ul;

                              ul = currRemoveWithTime->objectId;
                              sprintf(galMsg, "object=%lu", ul);
                              E1mEnd(pRWT_i0,galMsg);
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, currRemoveWithTime->myTag);
                              E1mEnd(pRWT_i0,galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
        federateAmbassador->removeObjectInstance(objectInstanceHandle, userSuppliedTag, sentOrder);
      }
    }
    catch(RTI::ObjectInstanceNotKnown)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pRWT_ta,"ObjectInstanceNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::InvalidLogicalTime)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pRWT_ta,"InvalidLogicalTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::FederateInternalError)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pRWT_ta,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

    try
    {
      runTimeObjectDB->removeObjectInstance(currRemoveWithTime->objectId);
    }
    catch(GeRtiFactory::ObjectNotKnown&)
    {
      // object is not known - no delete required
    }

    delete currRemoveWithTime;
  }
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::processRequestRetraction(GeRtiFactory::ERHandle const &theHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::processRequestRetraction", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  pm.acquire();
  processRetraction(theHandle);
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::processRequestRetraction", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::processRetraction(GeRtiFactory::ERHandle const &theERHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::processRetraction", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::ERHandleTimeMap *currERHandleTimeMap;
  GERTICO::ERHandleTimeMap::iterator itERH;
  GERTICO::HandleErMap::iterator itHEM;

  // Get event retraction handle map for this federate.
  itHEM = handleErMap.find(theERHandle.sendingFederate);
  if (itHEM != handleErMap.end())
  {
    currERHandleTimeMap = &itHEM->second;
    // Find event retraction handle.
    itERH = currERHandleTimeMap->find(theERHandle.theSerialNumber);
    if (itERH != currERHandleTimeMap->end())
    {
      if (processRetractionFlushed(itERH->second, theERHandle) == false)
      {
        processRetractionDelete(itERH->second, theERHandle);
      }
      currERHandleTimeMap->erase(itERH);
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::processRetraction", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::processRetractionDelete(GERTICO::GeRtiFedTime *theFedTime, GeRtiFactory::ERHandle const &theERHandle)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::processRetractionDelete", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::EventHolder *currEventHolder;
  GERTICO::EventHolderMap::iterator itEHM;
  GERTICO::RemoveWithTime *currRemoveWithTime;
  GERTICO::RemoveWithTimeMultimap::iterator itRWTM;
  std::vector <EventHolder *> *currEventHolderVector;
  std::vector <EventHolder *>::iterator itEH;
  GERTICO::GeRtiFedTime *tmpFedTime1;
  char buff[128];

  // Check in TSO events.
  for (itEHM = eventsTimedMap.begin(); itEHM != eventsTimedMap.end(); )
  {
    if (*itEHM->first > *theFedTime)
    {
      // Exceed the possible time in the sorted-by-time map.
      break;
    }
    currEventHolderVector = &itEHM->second;
    for (itEH = currEventHolderVector->begin(); itEH != currEventHolderVector->end(); itEH++)
    {
      currEventHolder = *itEH;
      if (currEventHolder->retractionHandle.sendingFederate == theERHandle.sendingFederate)
      {
        if (currEventHolder->retractionHandle.sendingFederate == theERHandle.sendingFederate)
        {
          // Got the event.
          currEventHolderVector->erase(itEH);
          delete currEventHolder;
          break;
        }
      }
    }
    if (currEventHolderVector->size() == 0)
    {
      GERTICO::GeRtiFedTime *fedTime;
      fedTime = itEHM->first;
      eventsTimedMap.erase(itEHM);
      delete fedTime;
      itEHM = eventsTimedMap.begin();
    }
    else
    {
      itEHM++;
    }
  }

  // Check in TSO removes.
  for (itRWTM = removeObjectsWithTime.begin(); itRWTM != removeObjectsWithTime.end(); itRWTM++)
  {
    (*itRWTM->first).encode(buff);
    tmpFedTime1 = timeManagementLRC->geRtiFedTimeFactory.decode(buff);
    if (*tmpFedTime1 > *theFedTime)
    {
      // Exceed the possible time in the sorted-by-time multimap.
      break;
    }
    currRemoveWithTime = itRWTM->second;
    if (currRemoveWithTime->retractionHandle.sendingFederate == theERHandle.sendingFederate)
    {
      if (currRemoveWithTime->retractionHandle.sendingFederate == theERHandle.sendingFederate)
      {
        // Got the event.
        removeObjectsWithTime.erase(itRWTM);
                           {   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::processRetractionDelete", "leave_1");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
        return;
                           }   // inserted by Gal converter
      }
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::processRetractionDelete", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processRetractionFlushed(GERTICO::GeRtiFedTime *theFedTime, GeRtiFactory::ERHandle const &theERHandle)
{
  GERTICO::TimeErMultimap::iterator itTEM;
  GeRtiFactory::ERHandle *messageRetractionHandle;
  std::auto_ptr<RTI::MessageRetractionHandle> retractionHandle;
  GERTICO::GeRtiFedTime *tmpFedTime1;
  char buff[128];

  // Search whether event was delivered to the federate ambassador.
  for (itTEM = timeErMultimap.begin(); itTEM != timeErMultimap.end(); itTEM++)
  {
    (*itTEM->first).encode(buff);
    tmpFedTime1 = timeManagementLRC->geRtiFedTimeFactory.decode(buff);
    // Check timestamps.
    if (*tmpFedTime1 > *theFedTime)
    {
      // Did not find in the sorted-by-time multimap.
      break;
    }

    // Got a possible entry.
    messageRetractionHandle = &itTEM->second;
    if (messageRetractionHandle->sendingFederate == theERHandle.sendingFederate)
    {
      // Got the federate.
      if (messageRetractionHandle->theSerialNumber == theERHandle.theSerialNumber)
      {
        // Got the serial number.
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pRF_i0)
                            {
                              unsigned long ul;

                              ul = theERHandle.sendingFederate;
                              sprintf(galMsg, "sendingFederate=%lu", ul);
                              E1mEnd(pRF_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
        RTI::MessageRetractionHandle *messageRetractionHandlePtr = new RTI::MessageRetractionHandle();
        GERTICO::Mapper1516::mapMessageRetractionHandle(*messageRetractionHandlePtr, theERHandle);
        std::auto_ptr<RTI::MessageRetractionHandle> tmp(messageRetractionHandlePtr);
        retractionHandle = tmp;
        federateAmbassador->requestRetraction(*retractionHandle);

        GERTICO::GeRtiFedTime *ptr;
        ptr = itTEM->first;
        timeErMultimap.erase(itTEM);
        delete ptr;

        return true;
      }
    }
  }

  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::EventHandler1516::processTimedEvent(void)
{
  bool ret = false;
  bool workOutstanding = false;

  if (stateRestore || stateSave)
  {
    return ret;
  }

  if (gotAnnounceFederateSave)
  {
    if (*timeManagementLRC->myTimeTag >= *timeManagementLRC->myTimeSave)
    {
      return ret;
    }
  }

  // NB. The save status is important.
  if (eventsTimedMap.size())
  {
    pm.acquire();
    if (processEventTso(false))
    {
      pm.release();
      return true;
    }
    pm.release();
    workOutstanding = true;
  }

  if (removeObjects.size())
  {
    if (processRemove())
    {
      ret = true;
      return ret;
    }
    workOutstanding = true;
  }

  // NB. The save status is important.
  if (removeObjectsWithTime.size())
  {
    pm.acquire();
    if (processRemoveWithTime(false))
    {
      ret = true;
      pm.release();
      return ret;
    }
    pm.release();
    workOutstanding = true;
  }

  if (timeManagementLRC->gotAnnounceFederateSaveWithTime)
  {
    if (processInitiateFederateSave())
    {
      ret = true;
      return ret;
    }
    workOutstanding = true;
  }

  pm.acquire();
  if (timeManagementLRC->gotTimeAdvanceGrant)
  {
    ret = true;
    ehRequest = EHNone;
    timeManagementLRC->gotTimeAdvanceGrant = false;
    delFlushERHandle();
    removeRetractionHandle(*timeManagementLRC->myTimeTag);
    try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pT_i0)
                            {
                              char buf[512];

                              timeManagementLRC->myTimeTag->getPrintableString(buf);
                              sprintf(galMsg, "time=%s", buf);
                              E1mEnd(pT_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      RTI::EncodedLogicalTime *encodedLogicalTime;
      std::auto_ptr<RTI::LogicalTime> logicalTime = timeManagementLRC->geRtiFedTimeFactory.logicalTimeFactory.makeInitial();
      GERTICO::Mapper1516::mapEncodedLogicalTime(&encodedLogicalTime, *timeManagementLRC->myTimeTag);
      logicalTime = timeManagementLRC->geRtiFedTimeFactory.logicalTimeFactory.decode(*encodedLogicalTime);
      timeManagementLRC->timeAdvanceGrant();
      federateAmbassador->timeAdvanceGrant(*logicalTime);
    }
    catch(RTI::InvalidLogicalTime)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pT_ta,"InvalidFederationTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::JoinedFederateIsNotInTimeAdvancingState)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pT_ta,"TimeAdvanceWasNotInProgress");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::FederateInternalError)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pT_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
  }
  pm.release();
  if (workOutstanding == false)
  {
    // Nothing to do.
    // Stop the time event job.
    ret = true;
  }
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::processTimeConEnabled(GERTICO::GeRtiFedTime const &theTime)
{
  *myConstrainedTime = theTime;
  gotTimeConstrainedEnabledFlag = true;

  pm.acquire();
  if (gotTimeConstrainedEnabledFlag)
  {
    RTI::EncodedLogicalTime *encodedLogicalTime;
    std::auto_ptr<RTI::LogicalTime> logicalTime = timeManagementLRC->geRtiFedTimeFactory.logicalTimeFactory.makeInitial();
    GERTICO::Mapper1516::mapEncodedLogicalTime(&encodedLogicalTime, *myConstrainedTime);
    logicalTime = timeManagementLRC->geRtiFedTimeFactory.logicalTimeFactory.decode(*encodedLogicalTime);

    try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pTCE_i0)
                            {
                              char buf[512];

                              timeManagementLRC->myLogicalTime->getPrintableString(buf);
                              sprintf(galMsg, "time=%s", buf);
                              E1mEnd(pTCE_i0,galMsg);
                            }
                          #endif   // inserted by Gal converter
      federateAmbassador->timeConstrainedEnabled(*logicalTime);
      timeManagementLRC->timeConstrainedEnabled(*myConstrainedTime);
      gotTimeConstrainedEnabled = true;
    }
    catch(RTI::InvalidLogicalTime)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pTCE_ta,"InvalidLogicalTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::NoRequestToEnableTimeConstrainedWasPending)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pTCE_ta,"NoRequestToEnableTimeConstrainedWasPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::FederateInternalError)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pTCE_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    gotTimeConstrainedEnabledFlag = false;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
int GERTICO::EventHandler1516::processTimeRegEnabled(GERTICO::GeRtiFedTime const &theTime)
{
  int ret = 0;

  *myRegulationTime = theTime;
  gotTimeRegulationEnabledFlag = true;

  if (gotTimeRegulationEnabledFlag)
  {
    RTI::EncodedLogicalTime *encodedLogicalTime;
    std::auto_ptr<RTI::LogicalTime> logicalTime = timeManagementLRC->geRtiFedTimeFactory.logicalTimeFactory.makeInitial();
    GERTICO::Mapper1516::mapEncodedLogicalTime(&encodedLogicalTime, *myRegulationTime);
    logicalTime = timeManagementLRC->geRtiFedTimeFactory.logicalTimeFactory.decode(*encodedLogicalTime);

    try
    {
      // If already constrained, deliver
      if (gotTimeConstrainedEnabled)
      {
        if (processEventRo(true))
        {
          return 2;
        }
        pm.acquire();
        *timeManagementLRC->myTimeTag = *myRegulationTime;
        if (processEventTso(true))
        {
          pm.release();
          return 2;
        }
        pm.release();
      }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(pTRE_i0)
                            {
                              char buf[512];

                              timeManagementLRC->myLogicalTime->getPrintableString(buf);
                              sprintf(galMsg, "time=%s", buf);
                              E1mEnd(pTRE_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      ret = 1;
      federateAmbassador->timeRegulationEnabled(*logicalTime);
      timeManagementLRC->timeRegulationEnabled(*myRegulationTime);
    }
    catch(RTI::InvalidLogicalTime)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pTRE_ta,"InvalidLogicalTime");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::NoRequestToEnableTimeRegulationWasPending)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pTRE_ta,"NoRequestToEnableTimeRegulationWasPending");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }
    catch(RTI::FederateInternalError)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(pTRE_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    }

    gotTimeRegulationEnabledFlag = false;
  }
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::removeRetractionHandle(GERTICO::GeRtiFedTime const &theFedTime)
{
  ERHandleTimeMap::iterator itERHTM;
  GERTICO::HandleSet *handleSetPtr;
  GERTICO::HandleSet::iterator itHS;
  GERTICO::GeRtiFedTime *fedTime;
  TimeERHandleMap::iterator itTERHM;

  for (itTERHM = timeERHandleMap.begin(); itTERHM != timeERHandleMap.end(); itTERHM = timeERHandleMap.begin())
  {
    fedTime = itTERHM->first;
    if (*fedTime > theFedTime)
    {
      break;
    }

    handleSetPtr = &itTERHM->second;
    for (itHS = handleSetPtr->begin(); itHS != handleSetPtr->end(); itHS++)
    {
      itERHTM = eRHandleTimeMap.find(*itHS);
      if (itERHTM != eRHandleTimeMap.end())
      {
        fedTime = itERHTM->second;
        eRHandleTimeMap.erase(itERHTM);
        delete fedTime;
      }
    }
    timeERHandleMap.erase(itTERHM);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::setGeRtiAmVar(GeRtiFactory::GeRtiAmbassador_var const &theGeRtiAmVar)
{
  geRtiAmVar = GeRtiFactory::GeRtiAmbassador::_duplicate(theGeRtiAmVar);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::setNextEventRequest(bool const &avail)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::setNextEventRequest", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  available = avail;

  ehRequest = EHNer;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::setNextEventRequest", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::setTimeAdvanceRequest(bool const &avail)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::setTimeAdvanceRequest", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  available = avail;

  ehRequest = EHTar;
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::setTimeAdvanceRequest", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::GeRtiFedTime *GERTICO::EventHandler1516::smallestAvailableTSO(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::smallestAvailableTSO", "enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::GeRtiFedTime *tso = NULL;
  EventHolderMap::iterator it;

  pm.acquire();
  it = eventsTimedMap.begin();
  if (it !=  eventsTimedMap.end())
  {
    tso = timeManagementLRC->geRtiFedTimeFactory.makeZero();
    *tso = *it->first;
  }
  pm.release();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_TM_d, "EventHandler1516::smallestAvailableTSO", "leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return tso;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::subscribeObjectClassAttributes(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theRegion, const GERTICO::HandleSet &theAttributes)
{
  GERTICO::HandleSet attributes;
  GERTICO::HandleSetMap classAttributes;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetSetMap::iterator itRCA;
  size_t size;

  pm.acquire();
  // Find or create the region key.
  itRCA = regionClassAttMap.find(theRegion);
  if (itRCA != regionClassAttMap.end())
  {
    // Delete any class information.
    itHSM = itRCA->second.find(theClass);
    if (itHSM != itRCA->second.end())
    {
      itRCA->second.erase(itHSM);
    }
  }
  else
  {
    regionClassAttMap[theRegion] = classAttributes;
  }

  // Check the length.
  size = theAttributes.size();

  // Unsubscribe.
  if (size == 0)
  {
    pm.release();
    return;
  }

  // Copy the attributes.
  attributes = theAttributes;

  // Fill class information.
  itRCA = regionClassAttMap.find(theRegion);
  if (itRCA != regionClassAttMap.end())
  {
    itRCA->second[theClass] = attributes;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::unsubscribeObjectClass(const GeRtiFactory::GeRtiHandle &theClass)
{
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetSetMap::iterator itRCA;
  GeRtiFactory::GeRtiHandle region = 0;

  pm.acquire();
  // Delete the region key.
  itRCA = regionClassAttMap.find(region);
  if (itRCA != regionClassAttMap.end())
  {
    // Delete any class information.
    itHSM = itRCA->second.find(theClass);
    if (itHSM != itRCA->second.end())
    {
      itRCA->second.erase(itHSM);
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::unsubscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes)
{
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::HandleSet *handleSetPtr;
  GERTICO::HandleSet::iterator itHandleSet;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetSetMap::iterator itRCA;
  GeRtiFactory::GeRtiHandle region = 0;

  len = theAttributes.length();

  pm.acquire();
  // Delete the region key.
  itRCA = regionClassAttMap.find(region);
  if (itRCA != regionClassAttMap.end())
  {
    // Delete any class information.
    itHSM = itRCA->second.find(theClass);
    if (itHSM != itRCA->second.end())
    {
      handleSetPtr = &itHSM->second;
      for (i = 0; i < len; i++)
      {
        itHandleSet = handleSetPtr->find(theAttributes[i]);
        if (itHandleSet != handleSetPtr->end())
        {
          handleSetPtr->erase(itHandleSet);
        }
      }
    }
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::EventHandler1516::unsubscribeObjectClassWithRegions(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap)
{
  GERTICO::HandleSet *handleSetPtr;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSet::iterator itHandleSet;
  GERTICO::HandleSetMap regAttMap;
  GERTICO::HandleSetMap::iterator itHSM;
  GERTICO::HandleSetMap::iterator itRegAttMap;
  GERTICO::HandleSetSetMap::iterator itRCA;

  GERTICO::Mapper::mapHandleSetMapInvert(regAttMap, theAttRegMap);

  pm.acquire();
  for (itRegAttMap = regAttMap.begin(); itRegAttMap != regAttMap.end(); itRegAttMap++)
  {
    itRCA = regionClassAttMap.find(itRegAttMap->first);
    if (itRCA != regionClassAttMap.end())
    {
      // Delete any class information.
      itHSM = itRCA->second.find(theClass);
      if (itHSM != itRCA->second.end())
      {
        handleSetPtr = &itHSM->second;
        for (itAttribute = itRegAttMap->second.begin(); itAttribute != itRegAttMap->second.end(); itAttribute++)
        {
          itHandleSet = handleSetPtr->find(*itAttribute);
          if (itHandleSet != handleSetPtr->end())
          {
            handleSetPtr->erase(itHandleSet);
          }
        }
      }
    }
  }
  pm.release();
}
