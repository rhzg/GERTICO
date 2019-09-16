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
Revision 1.14  2010/07/22 11:14:21  mul
Delete unused values.

Revision 1.13  2010/05/17 08:02:01  mul
Add logical time interval.

Revision 1.12  2010/03/16 15:26:15  mul
Minor changes.

Revision 1.11  2010/03/05 13:09:03  mul
Changes for single evoke call.

Revision 1.10  2010/02/25 07:34:34  mul
Changes for single callbacks.

Revision 1.9  2009/09/03 07:08:24  mul
Move some time management logic to correct module.

Revision 1.8  2009/06/02 12:12:13  mul
Fix problems with retraction handle.

Revision 1.7  2009/05/07 12:27:08  mul
Changes for removing token logic in time management.

Revision 1.6  2009/01/26 09:26:06  mul
Changes to data caching logic.

Revision 1.5  2008/11/19 14:08:29  mul
Changes for logging.

Revision 1.4  2008/08/07 09:36:31  mul
changes in event channel.

Revision 1.3  2007/09/05 15:39:28  mul
Changes for ieee1516.

Revision 1.2  2007/06/28 10:15:14  mul
Minor changes.

Revision 1.1  2007/06/26 08:25:26  mul
New files for ieee1516.


**
*******************************************************************************/

#ifndef EventHandler_HEADER
#define EventHandler_HEADER

#include <map>
#include <set>
#include <string>
#include <vector>

#include "RTI/1516.h"
#include "GeRtiTime/TimeService.h"
#include "idl/GeRtiFactoryS.h"
#include "LRC/OwnershipManagementLRC.h"
#include "Util/GeRtiTypes.h"
#include "Util/RunTimeObjectDB.h"
#include "LRC/HLA1516/Mapper1516.h"
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
  typedef std::multimap <GERTICO::GeRtiFedTime *, GeRtiFactory::ERHandle, ltFedTime> TimeErMultimap;

  class EventHolder
  {
  public:
    EventHolder(GeRtiFactory::GeRtiEvent const &theEvent, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory);
    EventHolder(GeRtiFactory::GeRtiEvent const &theEvent, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory, int const &theGrouping, bool const &theBestEffort);
    virtual ~EventHolder(void);

    std::auto_ptr<GERTICO::GeRtiFedTime> timestamp;
    GeRtiFactory::GEventType type;
    GeRtiFactory::UserSuppliedTag userSuppliedTag;
    bool bestEffort;
    std::auto_ptr<RTI::LogicalTime> rtiTimestamp;
    GeRtiFactory::ERHandle retractionHandle;
    GeRtiFactory::HandleValues hvps;
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
    GeRtiFactory::GeRtiHandle objectId;
    GeRtiFactory::UserSuppliedTag myTag;
    bool sendOrderTso;

    Remove(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theUserSuppliedTag, bool const &theSendOrderTso);
    virtual ~Remove(void);
  };

  class RemoveWithTime
  {
    GERTICO::GeRtiFedTimeFactory &fedTimeFactory;
  public:
    GERTICO::GeRtiFedTime *myTime;
    GeRtiFactory::GeRtiHandle objectId;
    GeRtiFactory::ERHandle retractionHandle;
    GeRtiFactory::UserSuppliedTag myTag;
    bool sendOrderTso;

    RemoveWithTime(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theUserSuppliedTag, bool const &theSendOrderTso, GERTICO::GeRtiFedTime &theTime, GeRtiFactory::ERHandle const &theERHandle, GERTICO::GeRtiFedTimeFactory &theFedTimeFactory);
    virtual ~RemoveWithTime(void);
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

  class EventHandler1516
  {
    ACE_Mutex pm;
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
    // When a flushQueueRequest is called, the timestamps/MessageRetractionHandles are
    // stored until a TAG is received -> older timstamps are deleted OR
    // a retract is received -> one particular timestamp will be deleted.
    GERTICO::TimeErMultimap timeErMultimap;

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
    RTI::FederateAmbassador* federateAmbassador;

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

    void addHandleMap(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleMap &theHandleMap);

    // Announce save
    bool gotAnnounceFederateSave;

    // Restore
    bool gotConfirmFederationRestorationRequest;
    bool stateRestore;
    bool confirmRestoreSuccess;
    std::wstring restoreLabel;

    // Save
    bool gotInitiateFederateSave;
    bool stateSave;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::RestoreFailureReason restoreFailureReason;
    GeRtiFactory::SaveFailureReason saveFailureReason;
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

    void addERHandle(GeRtiFactory::ERHandle const &theMessageRetractionHandle, GERTICO::GeRtiFedTime const &theFedTime);
    void delERHandle(GeRtiFactory::ERHandle const &theERHandle);
    void addFlushERHandle(GeRtiFactory::ERHandle const &theERHandle, GERTICO::GeRtiFedTime *);
    void delFlushERHandle(void);

    // TSO messages.
    EventHolderMap eventsTimedMap;
    RemoveWithTimeMultimap removeObjectsWithTime;

    // RO messages.
    std::vector <EventHolder *> events;
    std::vector <Remove *> removeObjects;

    void init(void);
    void getSubscribedAttributes(RTI::AttributeHandleValueMap &theAttributeHandleValueMap, EventHolder &currEventHolder);
    bool processEventRoInteraction(EventHolder &currEventHolder);
    bool processEventRoObject(EventHolder &currEventHolder);
    bool processEventTso(bool const &enableRegulation);
    bool processEventTsoInteraction(EventHolder &currEventHolder);
    bool processEventTsoObject(EventHolder &currEventHolder);
    bool processRemove(void);
    bool processRemoveWithTime(bool const &enableRegulation);
    void processRetraction(GeRtiFactory::ERHandle const &theERHandle);
    void processRetractionDelete(GERTICO::GeRtiFedTime *, GeRtiFactory::ERHandle const &theERHandle);
    bool processRetractionFlushed(GERTICO::GeRtiFedTime *, GeRtiFactory::ERHandle const &theERHandle);
    void removeRetractionHandle(GERTICO::GeRtiFedTime const &theFedTime);

  public:
    GERTICO::TimeManagementLRC *timeManagementLRC;
    EventHandler1516(bool &theAsynchronousDelivery);
    virtual ~EventHandler1516(void);

    void addEventHolder(GeRtiFactory::GeRtiEvent const &theEvent, unsigned int &numberRO, unsigned int &numberTSO);
    void addInitiateFederateSave(std::wstring const &theLabel);
    void addInitiateFederateSaveWithTime(std::wstring const &theLabel, GERTICO::GeRtiFedTime const &theTime);
    void addRemove(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theUserSuppliedTag, bool const &theSendOrderTso);
    void addRemoveWithTime(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::UserSuppliedTag const &, std::auto_ptr<GERTICO::GeRtiFedTime> &, GeRtiFactory::ERHandle const &);
    void addRetractionHandle(GeRtiFactory::ERHandle const &theERHandle, GERTICO::GeRtiFedTime const &theFedTime);
    void addTimeAdvanceGrant(GERTICO::GeRtiFedTime &theFedTime);
    void addTimeAdvanceGrantGalt(GERTICO::GeRtiFedTime const &theFedTime, GERTICO::GeRtiFedTime const &theGaltFedTime);
    void addTimeAdvanceGrantIntermediate(GERTICO::GeRtiFedTime const &theFedTime);

    void checkRetractionHandle(GeRtiFactory::ERHandle const &theERHandle);
    void deleteRetractionHandle(GeRtiFactory::ERHandle const &theERHandle);
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
    long getROlength(void);
    long getReflectionsReceived(void);
    void getReflectionsReceivedBestEffort(GERTICO::HandleMap &theReflections);
    void getReflectionsReceivedReliable(GERTICO::HandleMap &theReflections);
    long getTSOlength(void);

    // Save/Restore.
    void restore(DOMElement &theDOMElement);
    void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);

    void clear(void);

    // True means more events to be processed.
    void processConfirmFederationRestorationRequest(std::wstring const &theLabel, bool const &myReason);
    bool processTimedEvent(void);
    bool processEventRo(bool const &enableRegulation);
    void processFederationRestored(bool const &theSuccess, GeRtiFactory::RestoreFailureReason const &theFailureReason);
    void processFederationRestoreBegun(void);
    void processFederationSaved(bool const &theSuccess, GeRtiFactory::SaveFailureReason const &theFailureReason);
    void processInitiateFederateRestore(std::wstring const &theLabel, GeRtiFactory::GeRtiHandle const &theFederate);
    bool processInitiateFederateSave(void);
    void processRequestRetraction(GeRtiFactory::ERHandle const &theHandle);
    void processTimeConEnabled(GERTICO::GeRtiFedTime const &theFedTime);
    int processTimeRegEnabled(GERTICO::GeRtiFedTime const &theFedTime);
    void setDisableTimeConstrainedd(void);
    void setDisableTimeRegulation(void);
    void setFederate(GeRtiFactory::GeRtiHandle const &theFederate);
    void setFederateAmbassador(RTI::FederateAmbassador *theFederateAmbassador);
    void setGeRtiAmVar(GeRtiFactory::GeRtiAmbassador_var const &theGeRtiAmVar);
    void setFlushQueueRequest(void);
    void setNextEventRequest(bool const &avail);
    void setRunTimeObjectDB(GERTICO::RunTimeObjectDB *theRunTimeObjectDB);
    void setTimeAdvanceRequest(bool const &avail);
    void setTimeService(GERTICO::TimeManagementLRC *theTimeManagementLRC);
    GERTICO::GeRtiFedTime *smallestAvailableTSO(void);
    void subscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theRegion, GERTICO::HandleSet const &theAttributes);
    void unsubscribeObjectClass(GeRtiFactory::GeRtiHandle const &theClass);
    void unsubscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes);
    void unsubscribeObjectClassWithRegions(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap);
  };
};

#endif
