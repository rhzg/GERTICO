/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: EventHandler.h,v $
Revision 1.55  2010/07/22 11:11:58  mul
Changes for single tick call.

Revision 1.54  2010/05/17 07:58:16  mul
Add logical time interval.

Revision 1.53  2010/03/18 08:47:22  mul
Changes for single callback processing.

Revision 1.52  2009/09/03 07:05:46  mul
Move some time management logic to correct module.

Revision 1.51  2009/08/17 10:09:09  mul
Minor changes.

Revision 1.50  2009/05/27 13:23:00  mul
Changes to fix problems in level four test cases.

Revision 1.49  2009/05/27 11:32:49  mul
Fix problems found in level four tests.

Revision 1.48  2009/05/07 12:24:17  mul
Changes for removing token logic in time management.

Revision 1.47  2007/09/05 15:44:49  mul
Changes for ieee1516.

Revision 1.46  2007/06/25 15:12:39  mul
Changes for ieee1516.

Revision 1.45  2007/06/08 12:06:49  mul
Changes for ieee1516.

Revision 1.44  2007/05/15 13:19:55  mul
Changes for combined 1.3 and 1516 logic.

Revision 1.43  2007/05/09 13:13:49  mul
Use generic time.

Revision 1.42  2007/03/12 13:09:28  mul
Changed string to wstring.

Revision 1.41  2006/10/30 09:25:51  mul
Add init method.

Revision 1.40  2006/10/12 13:55:17  mul
Fix federate state.

Revision 1.39  2006/09/04 15:02:13  mul
Changes for phase 1 testcases.

Revision 1.38  2006/08/30 11:44:26  mul
Chnages for phase 1 testcases.

Revision 1.37  2006/08/10 14:08:28  hzg
cleanup data structures and fixed removeWithTime

Revision 1.36  2006/08/08 14:14:16  mul
Deliver timed events in advancing state for tar before grant.

Revision 1.35  2006/08/01 11:30:00  mul
Changes for mom.

Revision 1.34  2006/07/06 11:30:02  mul
Minor changes.

Revision 1.33  2006/04/19 14:59:18  mul
Change map type.

Revision 1.32  2006/02/09 15:38:25  mul
Add new maps and methods.

Revision 1.31  2005/11/22 10:17:49  mul
Fix a memory leak.

Revision 1.30  2005/11/11 10:56:07  mul
Change some logic to track missing events.

Revision 1.29  2005/10/31 11:25:43  mul
Add logging for mutex acquire and release.

Revision 1.28  2005/10/11 10:22:33  mul
Remove multi map.

Revision 1.27  2005/09/07 12:34:29  mul
Change name scoping.

Revision 1.26  2005/08/22 14:33:53  mul
Changes for various order types.

Revision 1.25  2005/08/03 13:04:05  mul
Add restore functions.

Revision 1.24  2005/06/24 13:00:36  mul
Add restore logic.

Revision 1.23  2005/05/03 15:20:30  mul
Add save logic.

Revision 1.22  2005/04/08 13:01:55  mul
Fix logic for save with time.

Revision 1.21  2005/03/03 09:39:19  mul
Fix delivery of events when timeRegulated enabled after timeConstrained.

Revision 1.20  2005/02/21 08:37:22  mul
Fix logic when timeAdvance may be granted.

Revision 1.19  2005/02/07 10:33:26  mul
Changes due to test cases.

Revision 1.18  2004/12/14 13:41:34  mul
Fix federate save logic.

Revision 1.17  2004/09/24 08:30:27  mul
Changes for save federation.

Revision 1.16  2004/08/19 09:59:56  mul
Changes due to save/restore logic.

Revision 1.15  2004/07/16 11:57:37  mul
Changes due to verfication test.

Revision 1.14  2004/05/27 12:22:05  mul
Fix problems found in conformance test.

Revision 1.13  2004/03/17 14:17:08  mul
Add event retraction.

Revision 1.12  2003/08/29 07:50:27  mul
Split a complex method into several parts.

Revision 1.11  2003/08/26 14:51:39  mul
Fix time regulation.

Revision 1.10  2003/08/07 12:07:26  mul
Make mapper a static/global function.

Revision 1.9  2003/07/16 08:00:10  mul
Changes for RTI::FedTime.

Revision 1.8  2003/05/28 06:40:25  mul
Use include paths starting in $GERTICO.

Revision 1.7  2003/04/29 06:26:13  hzg
Portierung auf Windows

Revision 1.6  2003/04/10 12:41:42  mul
Add mom counters.

Revision 1.5  2002/12/19 13:32:46  hzg
*** empty log message ***

Revision 1.4  2002/10/02 10:39:06  mul
Fix logic for tags in updates.

Revision 1.3  2002/09/23 12:13:09  mul
Add logic to only deliver the subscribed attributes to the application.

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen


**
*******************************************************************************/


#ifndef EventHandler_HEADER
#define EventHandler_HEADER

#include <map>
#include <set>
#include <string>
#include <vector>

#include "include/RTI_1.3/RTI.hh"
#include "idl/GeRtiFactoryS.h"
#include "LRC/OwnershipManagementLRC.h"
#include "Util/GeRtiTypes.h"
#include "Util/RunTimeObjectDB.h"
#include "LRC/TimeManagementLRC.h"

namespace GERTICO
{
// Key serial number
typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::GeRtiFedTime *, cmpHandle> ERHandleTimeMap;

// Key federate id
typedef std::map <GeRtiFactory::GeRtiHandle, ERHandleTimeMap, cmpHandle> HandleErMap;

struct ltFedTime
{
  bool operator()(const GERTICO::GeRtiFedTime *s1, const GERTICO::GeRtiFedTime *s2) const
  {
    return *s1 < *s2;
  }
};

// Key event timestamp
typedef std::multimap <const GERTICO::GeRtiFedTime *, RTI::EventRetractionHandle, ltFedTime> TimeErMultimap;

class EventHolder
{
public:
  EventHolder (const GeRtiFactory::GeRtiEvent &theEvent, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory);
  EventHolder (const GeRtiFactory::GeRtiEvent &theEvent, const int &theGrouping, const bool theBestEffort, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory);
  virtual ~EventHolder (void);

  GeRtiFactory::GEventType type;
  RTI::AttributeHandleValuePairSet *ahvps;
  RTI::ParameterHandleValuePairSet *phvps;
  char *tag;
  std::auto_ptr<GERTICO::GeRtiFedTime> timestamp;
  RTI::EventRetractionHandle retractionHandle;
  bool bestEffort;
  unsigned long objectId;
  unsigned long classId;
  unsigned long region;

  unsigned long getLength(void);
};

typedef std::map <GERTICO::GeRtiFedTime *, std::vector <EventHolder *>, ltFedTime> EventHolderMap;

struct rwtFedTime
{
  bool operator()(const GERTICO::GeRtiFedTime *s1, const GERTICO::GeRtiFedTime *s2) const
  {
    return *s1 < *s2;
  }
};

class Remove
{
public:
  GeRtiFactory::UserSuppliedTag *myTag;
  unsigned long objectId;

  Remove (const unsigned long &, const GeRtiFactory::UserSuppliedTag &);
  virtual ~Remove (void);
};

class RemoveWithTime
{
  GERTICO::GeRtiFedTimeFactory &fedTimeFactory;
public:
  RTI::EventRetractionHandle retractionHandle;
  GeRtiFactory::UserSuppliedTag myTag;
  GERTICO::GeRtiFedTime *myTime;
  GeRtiFactory::GeRtiHandle objectId;

  RemoveWithTime (const GeRtiFactory::GeRtiHandle &, const GeRtiFactory::UserSuppliedTag &, GERTICO::GeRtiFedTime &, const RTI::EventRetractionHandle &, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory);
  virtual ~RemoveWithTime (void);
};

typedef std::multimap<const GERTICO::GeRtiFedTime *, RemoveWithTime *, rwtFedTime> RemoveWithTimeMultimap;

enum EHRequest
{
  EHNone,
  EHTar,
  EHNer,
  EHFlush
};

// Key is federate time, second is serial number.
// Use this map to delete from the ERHandleTimeMap.
typedef std::map <GERTICO::GeRtiFedTime *, GERTICO::HandleSet, ltFedTime> TimeERHandleMap;

class EventHandler
{
  ACE_Thread_Mutex pm;
  GeRtiFactory::GeRtiHandle federateId;
  FederateState federateState;

  // Key federate id, data: map of event retraction handles.
  // Holds all current events plus any flushed future events.
  // Will be deleted when event is delivered to the federate (NOT flushed future events) OR
  // when requestRetraction is called OR
  // flushed events are stale (less than TAG time).
  GERTICO::HandleErMap handleErMap;

  // Key event timestamp, data: event retraction handle.
  // Only timestamps in the future.
  // When a flushQueueRequest is called, the timestamps/eventRetractionHandles are
  // stored until a TAG is received -> older timstamps are deleted OR
  // a retract is received -> one particular timestamp will be deleted.
  GERTICO::TimeErMultimap timeErMultimap;

  // Key Federate id, data map of serial numbers.
  // Each retract request will be processed.
  GERTICO::HandleSetMap retractRequests;

  // Take the serial number from an ERHandle and use it as key,
  // second is the corresponding federate time
  ERHandleTimeMap eRHandleTimeMap;
  // When a time has passed, use this map to find all the ERHandles which are
  // to be deleted.
  TimeERHandleMap timeERHandleMap;

  // Key is region, second is (key is object class, second is attribute set)
  HandleSetSetMap regionClassAttMap;

  GERTICO::RunTimeObjectDB *runTimeObjectDB;
  GeRtiFactory::GeRtiAmbassador_var geRtiAmVar;
  RTI::FederateAmbassador* receiver;

  bool &asynchronousDelivery;
  bool available;
  bool gotTimeConstrainedEnabled;
  bool gotTimeConstrainedEnabledFlag;
  bool gotTimeRegulationEnabled;
  bool gotTimeRegulationEnabledFlag;

  EHRequest ehRequest;

  std::auto_ptr<GERTICO::GeRtiFedTime> myConstrainedTime;
  std::auto_ptr<GERTICO::GeRtiFedTime> myRegulationTime;

  // Mom.
  long interactionsReceived;
  GERTICO::HandleMap interactionsReceivedBestEffort;
  GERTICO::HandleMap interactionsReceivedReliable;
  long reflectionsReceived;
  GERTICO::HandleMap reflectionsReceivedBestEffort;
  GERTICO::HandleMap reflectionsReceivedReliable;

  void addHandleMap(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleMap &theHandleMap);

  // Announce save
  bool gotAnnounceFederateSave;

  // Restore
  bool gotConfirmFederationRestorationRequest;
  bool stateRestore;
  bool confirmRestoreSuccess;
  std::wstring restoreLabel;

  // Save
  bool gotInitiateFederateSave;
  bool gotSaveTime;
  bool stateSave;
  RTI::Handle federate;
  std::wstring saveLabel;

  // Save/Restore.
  static std::string classStr;
  static std::string eventStr;
  static std::string eventHandlerStr;
  static std::string idStr;
  static std::string objectStr;
  static std::string regionStr;
  static std::string removeObjectsWithTimeStr;
  static std::string retractHandleStr;
  static std::string retractHandlesStr;
  static std::string sendingFederateStr;
  static std::string tagStr;
  static std::string theSerialNumberStr;
  static std::string timeStr;
  static std::string timestampStr;
  static std::string tsoEventsStr;
  static std::string typeStr;
  static std::string userTagStr;
  static std::string valueStr;
  static std::string valuePairStr;
  static std::string valuePairsStr;

  void addERHandle (const RTI::EventRetractionHandle &, const GERTICO::GeRtiFedTime &);
  void delERHandle (const RTI::EventRetractionHandle &);
  void addFlushERHandle (const RTI::EventRetractionHandle &, const GERTICO::GeRtiFedTime *);
  void delFlushERHandle (void);

  // TSO messages.
  EventHolderMap eventsTimedMap;
  RemoveWithTimeMultimap removeObjectsWithTime;

  // RO messages.
  std::vector <EventHolder *> events;
  std::vector <Remove *> removeObjects;

  void init(void);
  void getSubscribedAttributes (EventHolder &currEventHolder, RTI::AttributeHandleValuePairSet **);
  bool processEventRoInteraction(EventHolder &currEventHolder);
  bool processEventRoObject (EventHolder &currEventHolder);
  bool processEventTso(bool const &enableRegulation);
  bool processEventTsoInteraction(EventHolder &currEventHolder);
  bool processEventTsoObject(EventHolder &currEventHolder);
  bool processRemove(void);
  bool processRemoveWithTime(bool const &enableRegulation);
  void processRetraction (const RTI::EventRetractionHandle &theEventRetractionHandle);
  void processRetractionDelete (GERTICO::GeRtiFedTime *, const RTI::EventRetractionHandle &theEventRetractionHandle);
  bool processRetractionFlushed (GERTICO::GeRtiFedTime *, const RTI::EventRetractionHandle &theEventRetractionHandle);
  void removeRetractionHandle(const GERTICO::GeRtiFedTime &theFedTime);

public:
  GERTICO::TimeManagementLRC *timeManagementLRC;
  EventHandler(bool &theAsynchronousDelivery);
  virtual ~EventHandler (void);

  void addConfirmFederationRestorationRequest(const std::wstring &theLabel, const bool &myReason);
  void addEventHolder(GeRtiFactory::GeRtiEvent const &theEvent, unsigned int &numberRO, unsigned int &numberTSO);
  void addInitiateFederateSave(const std::wstring &theLabel);
  void addInitiateFederateSaveWithTime(const std::wstring &theLabel, const GERTICO::GeRtiFedTime &theTime);
  void addRemove (const unsigned long &, const GeRtiFactory::UserSuppliedTag &);
  void addRemoveWithTime (const GeRtiFactory::GeRtiHandle &, const GeRtiFactory::UserSuppliedTag &, std::auto_ptr<GERTICO::GeRtiFedTime> &, const GeRtiFactory::ERHandle &);
  void addRequestRetraction (const GeRtiFactory::ERHandle & theHandle);
  void addRetractionHandle(const GeRtiFactory::ERHandle &theERHandle, const GERTICO::GeRtiFedTime &theFedTime);
  void addTimeAdvanceGrant(GERTICO::GeRtiFedTime const &theFedTime);
  void addTimeAdvanceGrantGalt(GERTICO::GeRtiFedTime const &theFedTime, GERTICO::GeRtiFedTime const &theGaltFedTime);
  void addTimeAdvanceGrantIntermediate(GERTICO::GeRtiFedTime const &theFedTime);
  void checkRetractionHandle(const GeRtiFactory::ERHandle &theERHandle);
  void deleteRetractionHandle(const GeRtiFactory::ERHandle &theERHandle);
  void federateSaveBegun(void);
  void getFederateState(GERTICO::FederateState &theFederateState);
  bool getRestoreInProgress(void);
  bool getSaveInProgress(void);

  // For Time Management
  void queryMinNextEventTime(GERTICO::GeRtiFedTime &theTime);

  // For Mom.
  long getInteractionsReceived(void);
  void getInteractionsReceivedBestEffort(GERTICO::HandleMap &theInteractions);
  void getInteractionsReceivedReliable(GERTICO::HandleMap &theInteractions);
  GERTICO::GeRtiFedTime *getLITS(void);
  CORBA::ULong getROlength (void);
  long getReflectionsReceived(void);
  void getReflectionsReceivedBestEffort(GERTICO::HandleMap &theReflections);
  void getReflectionsReceivedReliable(GERTICO::HandleMap &theReflections);
  long getTSOlength (void);

  // Save/Restore.
  void restore(DOMElement &theDOMElement);
  void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);

  void clear (void);

  // True means more events to be processed.
  void processConfirmFederationRestorationRequest(std::wstring const &theLabel, bool const &myReason);
  bool processTimedEvent(void);
  bool processEventRo(const bool &enableRegulation);
  void processFederationRestored(bool const &theSuccess, GeRtiFactory::RestoreFailureReason const &theFailureReason);
  void processFederationRestoreBegun (void);
  void processFederationSaved(bool const &theSuccess, GeRtiFactory::SaveFailureReason const &theFailureReason);
  void processInitiateFederateRestore(std::wstring const &theLabel, GeRtiFactory::GeRtiHandle const &theFederate);
  bool processInitiateFederateSave(void);
  void processRequestRetraction(GeRtiFactory::ERHandle const &theHandle);
  void processTimeConEnabled(GERTICO::GeRtiFedTime const &theFedTime);
  int processTimeRegEnabled(GERTICO::GeRtiFedTime const &theFedTime);
  void setDisableTimeConstrainedd (void);
  void setDisableTimeRegulation (void);
  void setFederate(const GeRtiFactory::GeRtiHandle &theFederate);
  void setFederateAmbassador(RTI::FederateAmbassador *theFederateAmbassador);
  void setGeRtiAmVar(const GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmVar);
  void setFlushQueueRequest(void);
  void setNextEventRequest(bool const &avail);
  void setRunTimeObjectDB (GERTICO::RunTimeObjectDB *theRunTimeObjectDB);
  void setTimeAdvanceRequest(const bool &avail);
  void setTimeConstrainedEnabled (const GERTICO::GeRtiFedTime &);
  void setTimeRegulationEnabled (const GERTICO::GeRtiFedTime &);
  void setTimeService(GERTICO::TimeManagementLRC *theTimeManagementLRC);
  GERTICO::GeRtiFedTime *smallestAvailableTSO (void);
  void subscribeObjectClassAttributes (const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theRegion, const GERTICO::HandleSet &theAttributes);
  void unsubscribeObjectClassWithRegion(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::GeRtiHandle &theRegion);
};
};

#endif
