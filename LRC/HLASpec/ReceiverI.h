/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** ReceiverI.h
**
*******************************************************************************/

#ifndef ReceiverI_HEADER
#define ReceiverI_HEADER

#include <map>
#include <string>
#include <vector>

#include "RTI.hh"

#include "LRC/FederateDB.h"
#include "LRC/MomLRC.h"
#include "LRC/ReceiverLRC.h"
#include "LRC/HLASpec/EventHandler.h"

namespace GERTICO
{
  class AnSynPt : public virtual GERTICO::Job
  {
    GeRtiFactory::UserSuppliedTag *tag;
    RTI::FederateAmbassador &fedAmb;
    bool &joined;
    std::wstring label;

    // Save/restore.
    static std::string announceSynchronizationPointStr;
    static std::string labelStr;
    static std::string rtiInitiatedServiceStr;
    static std::string tagStr;

  public:
    AnSynPt(const std::wstring &theLabel, const GeRtiFactory::UserSuppliedTag &theTag, RTI::FederateAmbassador &theFedAmb, bool &theJoined);
    virtual ~AnSynPt(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class AttributeScope : public virtual GERTICO::Job
  {
    GeRtiFactory::GeRtiHandle myObject;
    GeRtiFactory::Handles myAttributes;
    RTI::FederateAmbassador &fedAmb;
    bool inScope;
    bool &joined;

    // Save/restore.
    static std::string attributeScopeStr;
    static std::string attributeStr;
    static std::string attributesStr;
    static std::string inScopeStr;
    static std::string rtiInitiatedServiceStr;
    static std::string objectStr;

  public:
    AttributeScope(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes, const bool &theIn, RTI::FederateAmbassador &theFedAmb, bool &theJoined);
    virtual ~AttributeScope(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class CoSynPt : public virtual GERTICO::Job
  {
    RTI::FederateAmbassador &fedAmb;
    bool &joined;
    bool success;
    std::wstring label;

    // Save/restore.
    static std::string confirmSychronizationPointRegistrationStr;
    static std::string labelStr;
    static std::string rtiInitiatedServiceStr;
    static std::string successStr;

  public:
    CoSynPt(const std::wstring &theLabel, const bool &, RTI::FederateAmbassador &theFedAmb, bool &theJoined);
    virtual ~CoSynPt(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class Discover : public virtual GERTICO::Job
  {
    GERTICO::ObjectManagementLRC &objectManagementLRC;
    RTI::FederateAmbassador &fedAmb;
    bool &joined;
    std::wstring name;
    unsigned long objectId;
    unsigned long classId;

    // Save/restore.
    static std::string classStr;
    static std::string discoverObjectInstanceStr;
    static std::string nameStr;
    static std::string objectStr;
    static std::string rtiInitiatedServiceStr;

  public:
    Discover(const std::wstring &myName, const unsigned long myObjectId, const unsigned long myClassId, GERTICO::ObjectManagementLRC &theObjectManagementLRC, RTI::FederateAmbassador &theFedAmb, bool &theJoined);
    virtual ~Discover(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

class FedSync : public virtual GERTICO::Job
  {
    RTI::FederateAmbassador &fedAmb;
    bool &joined;
    std::wstring label;

    // Save/restore.
    static std::string federationSynchronizedStr;
    static std::string labelStr;
    static std::string rtiInitiatedServiceStr;

  public:
    FedSync(const std::wstring &theLabel, RTI::FederateAmbassador &theFedAmb, bool &theJoined);
    virtual ~FedSync(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class ObjPubOff : public virtual GERTICO::Job
  {
    GeRtiFactory::Handles attributeList;
    RTI::FederateAmbassador &fedAmb;
    bool &joined;
    unsigned long classId;

    // Save/restore.
    static std::string attributeStr;
    static std::string attributesStr;
    static std::string classStr;
    static std::string rtiInitiatedServiceStr;
    static std::string turnUpdatesOffForObjectInstanceStr;

  public:
    ObjPubOff(const unsigned long &, const GeRtiFactory::Handles &, RTI::FederateAmbassador &theFedAmb, bool &theJoined);
    virtual ~ObjPubOff(void);
    void printIt(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class ObjPubOn : public virtual GERTICO::Job
  {
    GeRtiFactory::Handles attributeList;
    RTI::FederateAmbassador &fedAmb;
    bool &joined;
    unsigned long classId;

    // Save/restore.
    static std::string attributeStr;
    static std::string attributesStr;
    static std::string classStr;
    static std::string rtiInitiatedServiceStr;
    static std::string turnUpdatesOnForObjectInstanceStr;

  public:
    ObjPubOn(const unsigned long &, const GeRtiFactory::Handles &, RTI::FederateAmbassador &theFedAmb, bool &theJoined);
    virtual ~ObjPubOn(void);
    void printIt(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class Provide : public virtual GERTICO::Job
  {
    GeRtiFactory::Handles attributeHandles;
    RTI::FederateAmbassador &fedAmb;
    bool &joined;
    unsigned long objectId;

    // Save/restore.
    static std::string attributeStr;
    static std::string attributesStr;
    static std::string objectStr;
    static std::string provideAttributeValueUpdateStr;
    static std::string rtiInitiatedServiceStr;

  public:
    Provide(const unsigned long &, const GeRtiFactory::Handles &, RTI::FederateAmbassador &theFedAmb, bool &theJoined);
    virtual ~Provide(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class PublishTurnOn : public virtual GERTICO::Job
  {
    GERTICO::SupportingServicesLRC &supportingServicesLRC;
    RTI::FederateAmbassador &fedAmb;
    bool &joined;
    bool on;
    unsigned long classId;

    // Save/restore.
    static std::string classStr;
    static std::string onStr;
    static std::string rtiInitiatedServiceStr;
    static std::string turnInteractionsOnStr;

  public:
    PublishTurnOn(const unsigned long &, const bool &, RTI::FederateAmbassador &theFedAmb, bool &theJoined, GERTICO::SupportingServicesLRC &theSupportingServicesLRC);
    virtual ~PublishTurnOn(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class StReg : public virtual GERTICO::Job
  {
    RTI::FederateAmbassador &fedAmb;
    bool &joined;
    bool start;
    unsigned long classId;

    // Save/restore.
    static std::string classStr;
    static std::string rtiInitiatedServiceStr;
    static std::string startStr;
    static std::string stRegistrationForObjectClass;

  public:
    StReg(unsigned long id, const bool &theStart, RTI::FederateAmbassador &theFedAmb, bool &theJoined);
    virtual ~StReg(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class ConfirmFederationRestorationRequestJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    bool &joined;
    bool reason;
    std::wstring label;

  public:
    ConfirmFederationRestorationRequestJob(GERTICO::EventHandler &theEventHandler, std::wstring const &theLabel, bool const &myReason, bool &theJoined);
    virtual ~ConfirmFederationRestorationRequestJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class EventRoJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    bool &joined;
    unsigned int numberOfJobs;

  public:
    EventRoJob(GERTICO::EventHandler &theEventHandler, unsigned int const &theNumberOfJobs, bool &theJoined);
    virtual ~EventRoJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class FederationRestoreBegunJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    bool &joined;

  public:
    FederationRestoreBegunJob(GERTICO::EventHandler &theEventHandler, bool &theJoined);
    virtual ~FederationRestoreBegunJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class FederationRestoredLrcJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    GeRtiFactory::RestoreFailureReason failureReason;
    bool joined;
    bool success;

  public:
    FederationRestoredLrcJob(GERTICO::EventHandler &theEventHandler, bool const &theSuccess, GeRtiFactory::RestoreFailureReason const &theFailureReason, bool &theJoined);
    virtual ~FederationRestoredLrcJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class FederationSavedLrcJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    GeRtiFactory::SaveFailureReason failureReason;
    bool joined;
    bool success;

  public:
    FederationSavedLrcJob(GERTICO::EventHandler &theEventHandler, bool const &theSuccess, GeRtiFactory::SaveFailureReason const &theFailureReason, bool &theJoined);
    virtual ~FederationSavedLrcJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class InitiateFederateRestoreJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    GeRtiFactory::GeRtiHandle federate;
    bool &joined;
    std::wstring label;

  public:
    InitiateFederateRestoreJob(GERTICO::EventHandler &theEventHandler, std::wstring const &theLabel, GeRtiFactory::GeRtiHandle const &theFederate, bool &theJoined);
    virtual ~InitiateFederateRestoreJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class InitiateFederateSaveJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    bool &joined;

  public:
    InitiateFederateSaveJob(GERTICO::EventHandler &theEventHandler, bool &theJoined);
    virtual ~InitiateFederateSaveJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class RequestRetractionJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    GeRtiFactory::ERHandle erHandle;
    bool &joined;

  public:
    RequestRetractionJob(GERTICO::EventHandler &theEventHandler, GeRtiFactory::ERHandle const &theHandle, bool &theJoined);
    virtual ~RequestRetractionJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class TimedConstrainedEnabledJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    std::auto_ptr<GERTICO::GeRtiFedTime> myConstrainedTime;
    bool &joined;

  public:
    TimedConstrainedEnabledJob(GERTICO::EventHandler &theEventHandler, GERTICO::GeRtiFedTime const &theFedTime, bool &theJoined, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);
    virtual ~TimedConstrainedEnabledJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class TimeRegulationEnabledJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    std::auto_ptr<GERTICO::GeRtiFedTime> myRegulationTime;
    bool &joined;

  public:
    TimeRegulationEnabledJob(GERTICO::EventHandler &theEventHandler, GERTICO::GeRtiFedTime const &theFedTime, bool &theJoined, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);
    virtual ~TimeRegulationEnabledJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class TimedEventJob : public virtual GERTICO::Job
  {
    GERTICO::EventHandler &eventHandler;
    bool &joined;
    unsigned int numberOfJobs;

  public:
    TimedEventJob(GERTICO::EventHandler &theEventHandler, unsigned int const &theNumberOfJobs, bool &theJoined);
    virtual ~TimedEventJob(void);

    JobStatus execute(void);
    JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
  };

  class ReceiverI : public virtual GERTICO::ReceiverLRC
  {
  ACE_Mutex pm;
  GERTICO::MomLRC *momLRC;
  RTI::FederateAmbassador *myFedAmb;
  static std::string rtiInitiatedServicesStr;
  GERTICO::JobHolder rtiInitiatedServiceJobs;

  bool asynchronousDelivery;

  void doDm(GeRtiFactory::GertiDmEvent const &theGertiDmEvent);
  void doTm(GeRtiFactory::GertiTmEvent const &theGertiTmEvent);
public:
  ReceiverI(void);
  virtual ~ReceiverI (void);

  void addAnnounceSynchronizationPoint(std::wstring const &theLabel, GeRtiFactory::UserSuppliedTag const &theTag);
  void addAttributeIsNotOwned(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute);
  void addAttributeOwnedByRTI(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute);
  void addAttributeOwnershipAcquisitionNotification(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &securedAttributes, GeRtiFactory::UserSuppliedTag const &theTag);
  void addAttributeOwnershipDivestitureNotification(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &releasedAttributes);
  void addAttributeOwnershipUnavailable(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes);
  void addAttributesInScope (GeRtiFactory::GeRtiHandle &,GeRtiFactory::Handles const &);
  void addAttributesOutOfScope (GeRtiFactory::GeRtiHandle &,GeRtiFactory::Handles const &);
  void addConfirmAttributeOwnershipAcquisitionCancellation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes);
  void addConfirmFederationRestorationRequest(std::wstring const &theLabel, bool const &theSuccess);
  void addConfirmSynchronizationPointRegistration(std::wstring const &theLabel, bool const &theSuccess, GeRtiFactory::SynchronizationPointFailureReason const &theReason);
  void addDiscover(std::wstring const &theObjectName, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theObjectClass);
  void addEventHolder(GeRtiFactory::GertiPushEvent const &theGertiPushEvent);
  void addFederationRestoreBegun (void);
  void addFederationRestoreStatusResponse(GeRtiFactory::RestoreStatusPairSeq const &theFederateStatusVector);
  void addFederationRestored(bool const &theSuccess, GeRtiFactory::RestoreFailureReason const &theFailureReason);
  void addFederationSaveStatusResponse(GeRtiFactory::SaveStatusPairSeq const &theFederateStatusVector);
  void addFederationSaved(bool const &theSuccess, GeRtiFactory::SaveFailureReason const &theFailureReason);
  void addFederationSynchronized(std::wstring const &theLabel);
  void addInformAttributeOwnership(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute, GeRtiFactory::GeRtiHandle const &theOwner);
  void addInterPubOff (GeRtiFactory::GeRtiHandle const &theInteraction);
  void addInterPubOn (GeRtiFactory::GeRtiHandle const &theInteraction);
  void addInitiateFederateRestore(std::wstring const &theLabel, GeRtiFactory::GeRtiHandle const &theFederate);
  void addInitiateFederateSave(std::wstring const &theLabel);
  void addInitiateFederateSaveWithTime(std::wstring const &theLabel, GERTICO::GeRtiFedTime const &theTime);
  void addObjectInstanceNameReservationFailed(std::wstring const &theObjectInstanceName);
  void addObjectInstanceNameReservationSucceeded(std::wstring const &theObjectInstanceName);
  void addObjPubOff(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers);
  void addObjPubOn(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers);
  void addProvideAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag);
  void addRemove (GeRtiFactory::GeRtiHandle const &, GeRtiFactory::UserSuppliedTag const &);
  void addRemoveWithTime (GeRtiFactory::GeRtiHandle const &, GeRtiFactory::UserSuppliedTag const &, std::auto_ptr<GERTICO::GeRtiFedTime> &, GeRtiFactory::ERHandle const &);
  void addRequestAttributeOwnershipAssumption(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &offeredAttributes, GeRtiFactory::UserSuppliedTag const &theTag);
  void addRequestAttributeOwnershipRelease(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &candidateAttributes, GeRtiFactory::UserSuppliedTag const &theTag);
  void addRequestDivestitureConfirmation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &releasedAttributes);
  void addRequestRetraction (GeRtiFactory::ERHandle const & theHandle);
  void addRetractionHandle(GeRtiFactory::ERHandle const &theERHandle, GERTICO::GeRtiFedTime const &theFedTime);
  void addStartRegistrationForObjectClass (GeRtiFactory::GeRtiHandle const &);
  void addStopRegistrationForObjectClass (GeRtiFactory::GeRtiHandle const &);
  void addTimeAdvanceGrant(GERTICO::GeRtiFedTime &theGeRtiFedTime);
  void addTimeAdvanceGrantGalt(GERTICO::GeRtiFedTime const &theTime, GERTICO::GeRtiFedTime const &theGaltTime);
  void addTimeAdvanceGrantIntermediate(GERTICO::GeRtiFedTime const &theGeRtiFedTime);
  void addTimeConstrainedEnabled(GERTICO::GeRtiFedTime const &);
  void addTimeRegulationEnabled(GERTICO::GeRtiFedTime const &);
  bool getAsynchronousDelivery(void);
  void getFederateState(GERTICO::FederateState &theFederateState);
  bool getRestoreInProgress(void);
  bool getSaveInProgress(void);

  // For Time Management
  void queryMinNextEventTime(GERTICO::GeRtiFedTime &theTime);

  // For Mom.
  void doMomRequest(GeRtiFactory::GeRtiHandle theRequest, GeRtiFactory::HandleValues const & data);
  long getInteractionsReceived(void);
  void getInteractionsReceivedBestEffort(GERTICO::HandleMap &theInteractions);
  void getInteractionsReceivedReliable(GERTICO::HandleMap &theInteractions);
  void getMomData(GeRtiFactory::GeRtiHandle theRequest, GeRtiFactory::Handles const & theAttributes, GeRtiFactory::HandleValues_out data);
  long getROlength(void);
  long getReflectionsReceived (void);
  void getReflectionsReceivedBestEffort(GERTICO::HandleMap &theReflections);
  void getReflectionsReceivedReliable(GERTICO::HandleMap &theReflections);
  long getTSOlength(void);
  void setMomLRC(GERTICO::MomLRC *theMomLRC);

  // Process queues.
  void reset(void);
  bool process(bool const &processAll);

  // Save / Restore
  void federateSaveBegun(void);
  void restore(DOMElement &theDOMElement);
  void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);

  // Set values.
  void initiate(RTI::FederateAmbassador *theFederateAmbassador);
  void setAsynchronousDelivery(bool const &theAsynchronousDelivery);
  void setDisableTimeConstrained(void);
  void setDisableTimeRegulation(void);
  void setFlushQueueRequest(void);
  void setGeRtiAmVar(GeRtiFactory::GeRtiAmbassador_var const &theGeRtiAmVar);
  void setNextEventRequest(bool const &avail);
  void setTimeAdvanceRequest(bool const &avail);

  void publishObjectClass(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &attributeList);
  void setTimeService(GERTICO::TimeManagementLRC *theTimeManagementLRC);
  GERTICO::GeRtiFedTime *smallestAvailableTSO (void);
  void subscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap);
  void unsubscribeObjectClassWithRegionReceiver(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theRegion);
  void unsubscribeObjectClassWithRegionsReceiver(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap);
};
};

#endif
