/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
********************************************************************************
**
** MODULE
** Sender - Sender implementation for GERTICO
**
*******************************************************************************/

#ifndef Sender_HEADER
#define Sender_HEADER

// C++ standard library
#include <string>

#include <ace/OS.h>

// SISA RCI Socket
// project include files
#include "Util/GERTICOconf.h"
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiOrb.h"
#include "Util/GeRtiTypes.h"
#include "GeRtiEventMarketI.h"
#include <orbsvcs/CosNamingC.h>
#include "GeRtiAmbassadorI.h"
#include "GeRtiRestoreI.h"
#include "GeRtiEventMarketI.h"
#include "EventMarket.h"
#include "GeRtiSender.h"
#include "DeclarationManagementLRC.h"
#include "ManagementObjectModelLRC.h"
// Gal includes
#include "Gal/StdAfx.h"
#include "Gal/repository.h"

namespace NAMESPACE
{
  /*
   * Argument for timed thread.
   */
  class TimedArg
  {
  public:
    TimedArg(void);
    virtual ~TimedArg(void);
    ACE_Barrier *barrier;
    ACE_Semaphore *ps;
    GERTICO::EventMarket *eventMarket;
    GERTICO::FederateDB *federateDB;
    bool toContinue;
  };

  class TransmissionArg
  {
  public:
    TransmissionArg(void);
    virtual ~TransmissionArg(void);
    ACE_Barrier *barrier;
    ACE_Semaphore *ps;
    GERTICOconf *conf;
    GERTICO::EventMarket *eventMarket;
    GERTICO::FederateDB *federateDB;
    bool toContinue;
  };

  /*
   * @memo GERTICO RTI implementation
   */
  class Sender : public virtual GERTICO::GeRtiSender
  {
    ACE_Thread_Mutex pm;
    CORBA::PolicyList policyListBestEffort;
    CORBA::PolicyList policyListReceiver;
    GERTICOconf *conf;
    GERTICO::FederateDB federateDB;
    PortableServer::POA_var myPOA;
    PortableServer::POA_var myPOAbestEffort;
    PortableServer::POAManager_var myPOAMgr;
    PortableServer::POAManager_var myPOAbestEffortMgr;
    PortableServer::POAManager_var nilMgr;
    Repository *repository;
    TimedArg timedArg;
    TransmissionArg transmissionArg;
    std::wstring eventHubNameStr;

    // Thread variables,
    ACE_Barrier *barrier;
    ACE_thread_t tid;
    ACE_thread_t tid0;
    ACE_thread_t tid1;
    ACE_thread_t tid2;

    CosNaming::NamingContext_var gerti_context;
    CosNaming::NamingContext_var federationContextVar;
    GERTICO::GeRtiOrb *myGeRtiOrb;

    // Keep track of interactions and spaces - cache.
    GERTICO::HandleMap interactionHandleMap;
    // Keep track of published interactions.
    GERTICO::HandleSet interactionHandleSet;
    GERTICO::EventMarket *eventMarket;
    GERTICO::ManagementObjectModelLRC *managementObjectModelLRC;
    // DO NOT DELETE: memory does not belong to Sender
    GERTICO::ReceiverLRC *receiver;

    bool gotFactory;
    std::wstring joinedExecutionName;
    std::string gertiName;
    GeRtiFactory::GeRtiHandle retractionHandleCounter;

    GERTICO::GeRtiFactory_FederateAmbassador_i *fedAm;
    GERTICO::GeRtiFactory_GeRtiRestore_i *geRtiRestore;

    GeRtiFactory::FederateAmbassador_var fedAmbassadorReferenceVar;
    GeRtiFactory::GeRtiRestore_var geRtiRestoreVar;
    GeRtiFactory::EventHubFederation_var eventHubFederationVar;
    GeRtiFactory::TheFactory_var theFactoryVar;
    GeRtiFactory::FederationManagement_var fedManVar;
    GeRtiFactory::GeRtiAmbassador_var GeRtiAmb;
    GeRtiFactory::ConsumerAdmin_var consumerAdminVar;
    GeRtiFactory::TimeManagement_var timeManagementVar;
    GERTICO::cPushConsumer *pushConsumer;
    GERTICO::cPushConsumer *pushConsumerBestEffort;

    // hide defaults
    Sender(Sender const & s);
    Sender& operator = (Sender const & s);

    // information required to check if federate is allowed
    // to aquire ownership for a specific object of class "theClass"
    void addPublishInfo (GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes);

    void addPushConsumers(const GeRtiFactory::GeRtiHandle &theFederate, GERTICO::GeRtiOrb &theGeRtiOrb, GERTICO::ReceiverLRC &receiverLRC, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);
    void checkAttributeNotDefined(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttributes);
    void checkAttributeNotDefined(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &theAttributes);
    void checkAttributeNotDefined(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::HandleValues const &theAttributeValues);
    void checkSaveRestore(void);
    void clear();
    void getFactory ();
    void getFactoryVars(std::wstring const &theExecutionName);
    void mapIt (GERTICO::HandleSet &theAttributeSet, GeRtiFactory::Handles const &theAttributes);

    // Save.
    void save(std::string &theBuffer);

    void sendEvents ();

  public:
    Sender(GERTICO::ReceiverLRC *theReceiverLRC) throw
    (
      GeRtiFactory::RTIinternalError
    );

    virtual ~Sender ();

    bool isJoined(void);
    bool checkReportServiceInvocation(void);

    // Mom services
#ifdef IEEE_1516
    void sendReportException(const GERTICO::MomException &theMomException);
#else
    void sendReportAlert(GERTICO::MomAlert const &theMomAlert);
#endif
    void sendReportServiceInvocation(GERTICO::MomReportServiceInvocation const &theMomReportServiceInvocation);

    // Hla services
    void createFederationExecution(std::wstring const &theExecutionName, std::wstring const &theFED);

    void destroyFederationExecution(std::wstring const &theExecutionName);

    GeRtiFactory::GeRtiHandle joinFederationExecution(std::wstring const &theYourName, std::wstring const &theExecutionName, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory);

    virtual bool tickWork(bool const &useTimers, double const &minimum, double const &maximum);

    void resignFederationExecution
    (
      GeRtiFactory::ResignAction theAction // supplied C1
    )
    throw
    (
      GeRtiFactory::FederateOwnsAttributes,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::InvalidResignAction,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::RTIinternalError
    );

    ////////////////////////////////////
    // Federation Management Services //
    ////////////////////////////////////

    // 4.6
    virtual void registerFederationSynchronizationPoint
    (
      std::wstring const &theLabel,
      GeRtiFactory::UserSuppliedTag const &theTag
    )
    throw
    (
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError
    );

    virtual void registerFederationSynchronizationPoint
    (
      std::wstring const &theLabel,
      GeRtiFactory::UserSuppliedTag const &theTag,
      GeRtiFactory::Handles const &syncSet
    )
    throw
    (
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError
    );

  // 4.9
  virtual void synchronizationPointAchieved (
    std::wstring const &theLabel)
  throw (
    GeRtiFactory::SynchronizationPointLabelWasNotAnnounced,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 4.11
  virtual void requestFederationSave (
    std::wstring const &theLabel,
    GERTICO::GeRtiFedTime const &theTime)
  throw (
    GeRtiFactory::FederationTimeAlreadyPassed,
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void requestFederationSave (
    std::wstring const &theLabel)
  throw (
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError);

  // 4.13
  virtual void federateSaveBegun ()
  throw (
    GeRtiFactory::SaveNotInitiated,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 4.14
  virtual void federateSaveComplete (
                CORBA::Boolean success)
  throw (
    GeRtiFactory::SaveNotInitiated,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void queryFederationSaveStatus()
  throw (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 4.16
  virtual void requestFederationRestore (
    std::wstring const &label)
  throw (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 4.20
  virtual void federateRestoreComplete (
                CORBA::Boolean success)
    throw (
      GeRtiFactory::RestoreNotRequested,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RTIinternalError);

  virtual void queryFederationRestoreStatus()
  throw
  (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RTIinternalError
  );

  /////////////////////////////////////
  // Declaration Management Services //
  /////////////////////////////////////

  // 5.2
  virtual void publishObjectClass (
    GeRtiFactory::GeRtiHandle theClass,      // supplied C1
    GeRtiFactory::Handles const &attributeList)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::OwnershipAcquisitionPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 5.3
  virtual void unpublishObjectClass (
    GeRtiFactory::GeRtiHandle theClass) // supplied C1
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::OwnershipAcquisitionPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void unpublishObjectClassAttributes(
    GeRtiFactory::GeRtiHandle const &theClass,
    GeRtiFactory::Handles const &theAttributes)
  throw(
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::OwnershipAcquisitionPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 5.4
  virtual void publishInteractionClass (
    GeRtiFactory::GeRtiHandle theInteraction) // supplied C1
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 5.5
  virtual void unpublishInteractionClass (
    GeRtiFactory::GeRtiHandle theInteraction) // supplied C1
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotPublished,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 5.6
  virtual void subscribeObjectClassAttributes (
    GeRtiFactory::GeRtiHandle theClass,                   // supplied C1
    GeRtiFactory::Handles const & attributeList,
    CORBA::Boolean active)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 5.7
  virtual void unsubscribeObjectClass (
    GeRtiFactory::GeRtiHandle const &theClass)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotSubscribed,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

    virtual void unsubscribeObjectClassAttributes(
      GeRtiFactory::GeRtiHandle const &theClass,
      GeRtiFactory::Handles const &theAttributes)
    throw(
      GeRtiFactory::ObjectClassNotDefined,
      GeRtiFactory::AttributeNotDefined,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError);

  // 5.8
  virtual void subscribeInteractionClass (
    GeRtiFactory::GeRtiHandle theClass,               // supplied C1
    CORBA::Boolean active)
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::FederateLoggingServiceCalls,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 5.9
  virtual void unsubscribeInteractionClass (
    GeRtiFactory::GeRtiHandle theClass) // supplied C1
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotSubscribed,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  ////////////////////////////////
  // Object Management Services //
  ////////////////////////////////

  virtual void reserveObjectInstanceName(
    std::wstring const &theObjectInstanceName)
  throw(
    GeRtiFactory::IllegalName,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 6.2
  virtual GeRtiFactory::GeRtiHandle
  registerObjectInstance (
    GeRtiFactory::GeRtiHandle  theClass,  // supplied C1
    std::wstring const &theObject)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::ObjectAlreadyRegistered,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual GeRtiFactory::GeRtiHandle
  registerObjectInstance (
          GeRtiFactory::GeRtiHandle theClass)  // supplied C1
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 6.4
  virtual GeRtiFactory::ERHandle
  updateAttributeValues (
    GeRtiFactory::GeRtiHandle const &theObject,
    GeRtiFactory::HandleValues &theAttributes,
    GERTICO::GeRtiFedTime const &theTime,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void updateAttributeValues (
    GeRtiFactory::GeRtiHandle const &theObject,     // supplied C1
    GeRtiFactory::HandleValues &theAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 6.6
  virtual GeRtiFactory::ERHandle
  sendInteraction (
          GeRtiFactory::GeRtiHandle const &theInteraction,
    GeRtiFactory::HandleValues const &theParameters,
    GERTICO::GeRtiFedTime const &theTime,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotPublished,
    GeRtiFactory::InteractionParameterNotDefined,
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void sendInteraction (
    GeRtiFactory::GeRtiHandle const &theInteraction, // supplied C1
    GeRtiFactory::HandleValues const &theParameters,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotPublished,
    GeRtiFactory::InteractionParameterNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 6.8
  virtual GeRtiFactory::ERHandle
  deleteObjectInstance (
          GeRtiFactory::GeRtiHandle theObject,
    GERTICO::GeRtiFedTime const &theTime,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::DeletePrivilegeNotHeld,
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void deleteObjectInstance (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::DeletePrivilegeNotHeld,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 6.10
  virtual void localDeleteObjectInstance (
    GeRtiFactory::GeRtiHandle    theObject)       // supplied C1
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::FederateOwnsAttributes,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 6.11
  virtual void changeAttributeTransportationType (
    GeRtiFactory::GeRtiHandle             theObject,
    GeRtiFactory::Handles const &      theAttributes,
    GeRtiFactory::GeRtiHandle     theType)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::InvalidTransportationHandle,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 6.12
  virtual void changeInteractionTransportationType (
    GeRtiFactory::GeRtiHandle theClass,
    GeRtiFactory::GeRtiHandle   theType)
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotPublished,
    GeRtiFactory::InvalidTransportationHandle,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 6.15
  virtual void requestObjectAttributeValueUpdate (
    GeRtiFactory::GeRtiHandle        theObject,
    GeRtiFactory::Handles const & theAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void requestClassAttributeValueUpdate (
    GeRtiFactory::GeRtiHandle   theClass,
    GeRtiFactory::Handles const & theAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  ///////////////////////////////////
  // Ownership Management Services //
  ///////////////////////////////////

  // 7.2
  virtual void unconditionalAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle                  theObject,     // supplied C1
    GeRtiFactory::Handles const &           theAttributes)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 7.3
  virtual void negotiatedAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle                  theObject,     // supplied C1
    GeRtiFactory::Handles const &           theAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::AttributeAlreadyBeingDivested,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 7.7
  virtual void attributeOwnershipAcquisition (
    GeRtiFactory::GeRtiHandle        theObject,
    GeRtiFactory::Handles const & desiredAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::FederateOwnsAttributes,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 7.8
  virtual void attributeOwnershipAcquisitionIfAvailable (
    GeRtiFactory::GeRtiHandle        theObject,         // supplied C1
    GeRtiFactory::Handles const & desiredAttributes)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::FederateOwnsAttributes,
    GeRtiFactory::AttributeAlreadyBeingAcquired,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void attributeOwnershipDivestitureIfWanted(
    GeRtiFactory::GeRtiHandle const &theObject,
    GeRtiFactory::Handles const &theAttributes,
    GeRtiFactory::Handles &theDivestedAttributes)
    throw(
      GeRtiFactory::ObjectNotKnown,
      GeRtiFactory::AttributeNotDefined,
      GeRtiFactory::AttributeNotOwned,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError);

  // 7.11
  virtual GeRtiFactory::Handles*
  confirmDivestiture(
    GeRtiFactory::GeRtiHandle theObject,
    GeRtiFactory::Handles const & theAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateWasNotAskedToReleaseAttribute,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 7.12
  virtual void cancelNegotiatedAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle        theObject,     // supplied C1
    GeRtiFactory::Handles const &theAttributes)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::AttributeDivestitureWasNotRequested,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 7.13
  virtual void cancelAttributeOwnershipAcquisition (
    GeRtiFactory::GeRtiHandle        theObject,     // supplied C1
    GeRtiFactory::Handles const & theAttributes)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeAcquisitionWasNotRequested,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 7.15
  virtual void queryAttributeOwnership (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute) // supplied C1
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 7.17
  virtual CORBA::Boolean
  isAttributeOwnedByFederate (
    GeRtiFactory::GeRtiHandle    theObject,     // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute)  // supplied C1
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  //////////////////////////////
  // Time Management Services //
  //////////////////////////////

  // 8.2
  virtual void enableTimeRegulation (
#ifndef IEEE_1516
    GERTICO::GeRtiFedTime const &theFederateTime,
#endif
    GERTICO::GeRtiLogicalTimeInterval const &theLookahead)
  throw (
    GeRtiFactory::TimeRegulationAlreadyEnabled,
    GeRtiFactory::EnableTimeRegulationPending,
    GeRtiFactory::TimeAdvanceAlreadyInProgress,
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::InvalidLookahead,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.4
  virtual void disableTimeRegulation ()
  throw (
    GeRtiFactory::TimeRegulationWasNotEnabled,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.5
  virtual void enableTimeConstrained ()
  throw (
    GeRtiFactory::TimeConstrainedAlreadyEnabled,
    GeRtiFactory::EnableTimeConstrainedPending,
    GeRtiFactory::TimeAdvanceAlreadyInProgress,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.7
  virtual void disableTimeConstrained ()
  throw (
    GeRtiFactory::TimeConstrainedWasNotEnabled,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.8
  virtual void timeAdvanceRequest (
    GERTICO::GeRtiFedTime const &theTime)
  throw (
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::FederationTimeAlreadyPassed,
    GeRtiFactory::TimeAdvanceAlreadyInProgress,
    GeRtiFactory::EnableTimeRegulationPending,
    GeRtiFactory::EnableTimeConstrainedPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.9
  virtual void timeAdvanceRequestAvailable (
    GERTICO::GeRtiFedTime const &theTime)
    throw (
      GeRtiFactory::InvalidFederationTime,
      GeRtiFactory::FederationTimeAlreadyPassed,
      GeRtiFactory::TimeAdvanceAlreadyInProgress,
      GeRtiFactory::EnableTimeRegulationPending,
      GeRtiFactory::EnableTimeConstrainedPending,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError);

  // 8.10
  virtual void nextEventRequest (
    GERTICO::GeRtiFedTime const &theTime)
  throw (
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::FederationTimeAlreadyPassed,
    GeRtiFactory::TimeAdvanceAlreadyInProgress,
    GeRtiFactory::EnableTimeRegulationPending,
    GeRtiFactory::EnableTimeConstrainedPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.11
  virtual void nextEventRequestAvailable (
    GERTICO::GeRtiFedTime const &theTime)
  throw (
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::FederationTimeAlreadyPassed,
    GeRtiFactory::TimeAdvanceAlreadyInProgress,
    GeRtiFactory::EnableTimeRegulationPending,
    GeRtiFactory::EnableTimeConstrainedPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.12
  virtual void flushQueueRequest (
    GERTICO::GeRtiFedTime const &theTime)
  throw (
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::FederationTimeAlreadyPassed,
    GeRtiFactory::TimeAdvanceAlreadyInProgress,
    GeRtiFactory::EnableTimeRegulationPending,
    GeRtiFactory::EnableTimeConstrainedPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.14
  virtual void enableAsynchronousDelivery()
    throw (
      GeRtiFactory::AsynchronousDeliveryAlreadyEnabled,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError);

  // 8.15
  virtual void disableAsynchronousDelivery()
    throw (
      GeRtiFactory::AsynchronousDeliveryAlreadyDisabled,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError);

  // 8.16
  virtual void queryLBTS (
    GERTICO::GeRtiFedTime& theTime)
  throw (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.17
  virtual void queryFederateTime (
    GERTICO::GeRtiFedTime& theTime)
  throw (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.18
  virtual void queryMinNextEventTime (
    GERTICO::GeRtiFedTime& theTime)
  throw (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.19
  virtual void modifyLookahead (
    GERTICO::GeRtiLogicalTimeInterval const &theLookahead)
  throw (
    GeRtiFactory::InvalidLookahead,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.20
  virtual void queryLookahead (
     GERTICO::GeRtiLogicalTimeInterval& theTime)
  throw (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.21
  virtual void retract (
    GeRtiFactory::ERHandle const &theERHandle) // supplied C1
  throw (
    GeRtiFactory::InvalidRetractionHandle,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.23
  virtual void changeAttributeOrderType (
    GeRtiFactory::GeRtiHandle        theObject,     // supplied C1
    GeRtiFactory::Handles const & theAttributes,
    GeRtiFactory::GeRtiHandle      theType)       // supplied C1
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::InvalidOrderingHandle,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 8.24
  virtual void changeInteractionOrderType (
    GeRtiFactory::GeRtiHandle theClass, // supplied C1
    GeRtiFactory::GeRtiHandle         theType)  // supplied C1
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotPublished,
    GeRtiFactory::InvalidOrderingHandle,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  //////////////////////////////////
  // Data Distribution Management //
  //////////////////////////////////

  // 9.2
  virtual GeRtiFactory::GeRtiHandle
  createRegion (
    GeRtiFactory::GeRtiHandle const &theSpace,
    CORBA::ULong const &numberOfExtents,
    GERTICO::HandleSet const &theDimensions)
  throw (
    GeRtiFactory::SpaceNotDefined,
    GeRtiFactory::InvalidExtents,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.3
  virtual void notifyAboutRegionModification (
    GeRtiFactory::GeRtiHandle const &theRegion,
    GeRtiFactory::Extents &theExtents)
  throw (
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidExtents,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.4
  virtual void deleteRegion (
    GeRtiFactory::GeRtiHandle const &theRegion)
  throw (
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::RegionInUse,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.5
  virtual GeRtiFactory::GeRtiHandle
  registerObjectInstanceWithRegion (
    GeRtiFactory::GeRtiHandle const &theClass,
    std::wstring const &theObject,
    GERTICO::HandleSetMap &theAttRegMap)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::ObjectAlreadyRegistered,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual GeRtiFactory::GeRtiHandle
  registerObjectInstanceWithRegion (
    GeRtiFactory::GeRtiHandle const &theClass,
    GERTICO::HandleSetMap &theAttRegMap)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.6
  virtual void associateRegionForUpdates (
          GeRtiFactory::GeRtiHandle  theObject,
    GERTICO::HandleSetMap &theAttRegMap)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.7
  virtual void unassociateRegionForUpdates (
    GeRtiFactory::GeRtiHandle       &theRegion,
    GeRtiFactory::GeRtiHandle  theObject)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void unassociateRegionsForUpdates (
    GeRtiFactory::GeRtiHandle  theObject,
    GERTICO::HandleSetMap &theAttRegMap)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.8
  virtual void subscribeObjectClassAttributesWithRegion (
    GeRtiFactory::GeRtiHandle theClass,
    GERTICO::HandleSetMap &theAttRegMap,
    bool const &active)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.9
  virtual void unsubscribeObjectClassWithRegion (
    GeRtiFactory::GeRtiHandle theClass,
    GeRtiFactory::GeRtiHandle &theRegion)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::ObjectClassNotSubscribed,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void unsubscribeObjectClassWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    GERTICO::HandleSetMap &theAttRegMap)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::ObjectClassNotSubscribed,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.10
  virtual void subscribeInteractionClassWithRegion (
    GeRtiFactory::GeRtiHandle theClass,
    GERTICO::HandleSet &theRegions,
    bool const &active)
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::FederateLoggingServiceCalls,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.11
  virtual void unsubscribeInteractionClassWithRegion (
    GeRtiFactory::GeRtiHandle theClass,
    GERTICO::HandleSet &theRegion)
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotSubscribed,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.12
  virtual GeRtiFactory::ERHandle
  sendInteractionWithRegion (
          GeRtiFactory::GeRtiHandle const &theInteraction,
    GeRtiFactory::HandleValues const &theParameters,
    GERTICO::GeRtiFedTime const &theTime,
    GeRtiFactory::UserSuppliedTag const &theTag,
    GERTICO::HandleSet const &theRegions)
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotPublished,
    GeRtiFactory::InteractionParameterNotDefined,
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void sendInteractionWithRegion (
          GeRtiFactory::GeRtiHandle const       &theInteraction,
    GeRtiFactory::HandleValues const &theParameters,
    GeRtiFactory::UserSuppliedTag const &theTag,
    GERTICO::HandleSet const &theRegions)
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotPublished,
    GeRtiFactory::InteractionParameterNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 9.13
  virtual void requestClassAttributeValueUpdateWithRegion (
    GeRtiFactory::GeRtiHandle   theClass,
    GERTICO::HandleSetMap &theAttRegMap,
    GeRtiFactory::UserSuppliedTag const &theTag)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void getExtents(GeRtiFactory::GeRtiHandle const &theRegion, GeRtiFactory::GeRtiHandle &theSpace, GeRtiFactory::Extents &theExtents)
  throw(
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::RTIinternalError);

  //////////////////////////
  // RTI Support Services //
  //////////////////////////

  // 10.2
  virtual GeRtiFactory::GeRtiHandle
  getObjectClassHandle (
    std::wstring const &theName)
  throw (
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.3
  virtual std::wstring
  getObjectClassName (
    GeRtiFactory::GeRtiHandle const &theHandle)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.4
  virtual GeRtiFactory::GeRtiHandle
  getAttributeHandle (
    std::wstring const &theName,
    GeRtiFactory::GeRtiHandle const &whichClass)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.5
  virtual std::wstring
  getAttributeName (
    GeRtiFactory::GeRtiHandle const &theHandle,
    GeRtiFactory::GeRtiHandle const &whichClass)
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.6
  virtual GeRtiFactory::GeRtiHandle
  getInteractionClassHandle (
    std::wstring const &theName)
  throw (
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.7
  virtual std::wstring
  getInteractionClassName (
    GeRtiFactory::GeRtiHandle const &theHandle) // supplied C1
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.8
  virtual GeRtiFactory::GeRtiHandle
  getParameterHandle (
    std::wstring const &theName,
    GeRtiFactory::GeRtiHandle const &whichClass)
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.9
  virtual std::wstring
  getParameterName (
    GeRtiFactory::GeRtiHandle const &theHandle,  // supplied C1
    GeRtiFactory::GeRtiHandle const &whichClass) // supplied C1
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionParameterNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.10
  virtual GeRtiFactory::GeRtiHandle
  getObjectInstanceHandle (
    std::wstring const &theName)
  throw (
      GeRtiFactory::ObjectNotKnown,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::RTIinternalError);

  // 10.11
  virtual std::wstring
  getObjectInstanceName (
    GeRtiFactory::GeRtiHandle const &theHandle)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.12
  virtual GeRtiFactory::GeRtiHandle
  getRoutingSpaceHandle (
    std::wstring const &theName)
  throw (
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.13
  virtual std::wstring
  getRoutingSpaceName (
     //
     // This const was removed for the RTI 1.3 NG to work around a limitation of
     // the Sun 4.2 C++ compiler regarding template instantiation.  The const
     // is unnecessary.
     //
     /* const */ GeRtiFactory::GeRtiHandle theHandle)
  throw (
    GeRtiFactory::SpaceNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.14
  virtual GeRtiFactory::GeRtiHandle
  getDimensionHandle (
    std::wstring const &theName,
    GeRtiFactory::GeRtiHandle const &whichSpace) // supplied C1
  throw (
    GeRtiFactory::SpaceNotDefined,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.15
  virtual std::wstring
  getDimensionName (
    GeRtiFactory::GeRtiHandle theHandle,  // supplied C1
    GeRtiFactory::GeRtiHandle     whichSpace) // supplied C1
  throw (
    GeRtiFactory::SpaceNotDefined,
    GeRtiFactory::DimensionNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  virtual GeRtiFactory::GeRtiHandle getDimensionUpperBound(
    GeRtiFactory::GeRtiHandle const &theHandle)
  throw(
    GeRtiFactory::DimensionNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError);

  virtual void getAvailableDimensionsForClassAttribute(
    GeRtiFactory::GeRtiHandle const & theClass,
    GeRtiFactory::GeRtiHandle const & theHandle,
    GeRtiFactory::Handles &theDimensions)
  throw(
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError);

  virtual void getAvailableDimensionsForInteractionClass(
    GeRtiFactory::GeRtiHandle const &theClass,
    GeRtiFactory::Handles &theDimensions)
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError);

  // 10.16
  virtual GeRtiFactory::GeRtiHandle
  getAttributeRoutingSpaceHandle (
    GeRtiFactory::GeRtiHandle   theHandle,   // supplied C1
    GeRtiFactory::GeRtiHandle whichClass)  // supplied C1
  throw (
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.17
  virtual GeRtiFactory::GeRtiHandle
  getObjectClass (
    GeRtiFactory::GeRtiHandle theObject)    // supplied C1
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  // 10.18
  virtual GeRtiFactory::GeRtiHandle
  getInteractionRoutingSpaceHandle (
    GeRtiFactory::GeRtiHandle   theHandle)   // supplied C1
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError);

  virtual void getDimensionHandleSet (
    GeRtiFactory::GeRtiHandle const &theRegionHandle,
    GeRtiFactory::Handles &theDimensions
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void getRangeBounds(
    GeRtiFactory::GeRtiHandle const &theRegionHandle,
    GeRtiFactory::GeRtiHandle const &theDimensionHandle,
    GeRtiFactory::Handles &theRangeBounds
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::RegionDoesNotContainSpecifiedDimension,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  virtual void setRangeBounds(
    GeRtiFactory::GeRtiHandle const &theRegionHandle,
    GeRtiFactory::GeRtiHandle const &theDimensionHandle,
    GeRtiFactory::GeRtiHandle theLowerBound,
    GeRtiFactory::GeRtiHandle theUpperBound
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::RegionNotCreatedByThisFederate,
    GeRtiFactory::RegionDoesNotContainSpecifiedDimension,
    GeRtiFactory::InvalidRangeBound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 10.23
  virtual void enableClassRelevanceAdvisorySwitch()
  throw(
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 10.24
  virtual void disableClassRelevanceAdvisorySwitch()
  throw(
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 10.25
  virtual void enableAttributeRelevanceAdvisorySwitch()
  throw(
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 10.26
  virtual void disableAttributeRelevanceAdvisorySwitch()
  throw(
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 10.27
  virtual void enableAttributeScopeAdvisorySwitch()
  throw (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 10.28
  virtual void disableAttributeScopeAdvisorySwitch()
  throw (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 10.29
  virtual void enableInteractionRelevanceAdvisorySwitch()
  throw (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 10.30
  virtual void disableInteractionRelevanceAdvisorySwitch()
  throw (
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  //
  virtual CORBA::Boolean tick();

  virtual CORBA::Boolean
  tick (
    double const &minimum,
    double const &maximum);
};

} // namespace

#endif // Sender_HEADER
