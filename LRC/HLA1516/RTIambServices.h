/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/RTIambassador.h
***********************************************************************/

// This interface is used to access the services of the RTI.

#ifndef RTI_RTIambServices_h
#define RTI_RTIambServices_h

#include "RTI/1516.h"
#include "LRC/Sender.h"
#include "LRC/HLA1516/ReceiverI.h"

namespace GERTICO
{
  class RegionI
  {
    GeRtiFactory::GeRtiHandle id;
  public:
    GERTICO::BoundsMap boundsMap;

    RegionI(GeRtiFactory::GeRtiHandle const &theId);
    ~RegionI(void);
    void getId(GeRtiFactory::GeRtiHandle &theId);
  };

  // Key is region id.
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::RegionI *> RegionIMap;

  class RTI_EXPORT RTIambServices : public virtual RTI::RTIambassador
  {
    GERTICO::ReceiverI1516 *receiverI;
    RegionIMap regionIMap;
    NAMESPACE::Sender *sender;
    GERTICO::GeRtiFedTimeFactory *myLogicalTimeFactory;
    GERTICO::GeRtiLogicalTimeIntervalFactory *myLogicalTimeIntervalFactory;
  public:
#if _MSC_VER == 1200
    RTIambServices(void);
#else
    RTIambServices(void)
       throw();
#endif

    virtual
#if _MSC_VER == 1200
      ~RTIambServices(void);
#else
      ~RTIambServices(void)
       throw();
#endif

    // 4.2
    void createFederationExecution
    (std::wstring const & federationExecutionName,
     std::wstring const & fullPathNameToTheFDDfile)
      throw (RTI::FederationExecutionAlreadyExists,
             RTI::CouldNotOpenFDD,
             RTI::ErrorReadingFDD,
             RTI::RTIinternalError);

    // 4.3
    void destroyFederationExecution
    (std::wstring const & federationExecutionName)
      throw (RTI::FederatesCurrentlyJoined,
             RTI::FederationExecutionDoesNotExist,
             RTI::RTIinternalError);

    // 4.4
    RTI::FederateHandle joinFederationExecution
    (std::wstring const & federateType,
     std::wstring const & federationExecutionName,
     RTI::FederateAmbassador & federateAmbassador,
     RTI::LogicalTimeFactory & logicalTimeFactory,
     RTI::LogicalTimeIntervalFactory & logicalTimeIntervalFactory)
      throw (RTI::FederateAlreadyExecutionMember,
             RTI::FederationExecutionDoesNotExist,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 4.5
    void resignFederationExecution
    (RTI::ResignAction resignAction)
      throw (RTI::OwnershipAcquisitionPending,
             RTI::FederateOwnsAttributes,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 4.6
    void registerFederationSynchronizationPoint
    (std::wstring const & label,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    void registerFederationSynchronizationPoint
    (std::wstring const & label,
     RTI::UserSuppliedTag const & theUserSuppliedTag,
     RTI::FederateHandleSet const & syncSet)
      throw (RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 4.9
    void synchronizationPointAchieved
    (std::wstring const & label)
      throw (RTI::SynchronizationPointLabelNotAnnounced,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 4.11
    void requestFederationSave
    (std::wstring const & label)
      throw (RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    void requestFederationSave
    (std::wstring const & label,
     RTI::LogicalTime const & theTime)
      throw (RTI::LogicalTimeAlreadyPassed,
             RTI::InvalidLogicalTime,
             RTI::FederateUnableToUseTime,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 4.13
    void federateSaveBegun ()
      throw (RTI::SaveNotInitiated,
             RTI::FederateNotExecutionMember,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 4.14
    void federateSaveComplete ()
      throw (RTI::FederateHasNotBegunSave,
             RTI::FederateNotExecutionMember,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    void federateSaveNotComplete()
      throw (RTI::FederateHasNotBegunSave,
             RTI::FederateNotExecutionMember,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 4.16
    void queryFederationSaveStatus ()
      throw (RTI::FederateNotExecutionMember,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 4.18
    void requestFederationRestore
    (std::wstring const & label)
      throw (RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 4.22
    void federateRestoreComplete ()
      throw (RTI::RestoreNotRequested,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RTIinternalError);

    void federateRestoreNotComplete ()
      throw (RTI::RestoreNotRequested,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RTIinternalError);

    // 4.24
    void queryFederationRestoreStatus ()
      throw (RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RTIinternalError);

    /////////////////////////////////////
    // Declaration Management Services //
    /////////////////////////////////////

    // 5.2
    void publishObjectClassAttributes
    (RTI::ObjectClassHandle  const & theClass,
     RTI::AttributeHandleSet const & attributeList)
      throw (RTI::ObjectClassNotDefined,
             RTI::AttributeNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 5.3
    void unpublishObjectClass
    (RTI::ObjectClassHandle const & theClass)
      throw (RTI::ObjectClassNotDefined,
             RTI::OwnershipAcquisitionPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    void unpublishObjectClassAttributes
    (RTI::ObjectClassHandle  const & theClass,
     RTI::AttributeHandleSet const & attributeList)
      throw (RTI::ObjectClassNotDefined,
             RTI::AttributeNotDefined,
             RTI::OwnershipAcquisitionPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 5.4
    void publishInteractionClass
    (RTI::InteractionClassHandle const & theInteraction)
      throw (RTI::InteractionClassNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 5.5
    void unpublishInteractionClass
    (RTI::InteractionClassHandle const & theInteraction)
      throw (RTI::InteractionClassNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 5.6
    void subscribeObjectClassAttributes
    (RTI::ObjectClassHandle  const & theClass,
     RTI::AttributeHandleSet const & attributeList,
     bool active = true)
      throw (RTI::ObjectClassNotDefined,
             RTI::AttributeNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 5.7
    void unsubscribeObjectClass
    (RTI::ObjectClassHandle const & theClass)
      throw (RTI::ObjectClassNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    void unsubscribeObjectClassAttributes
    (RTI::ObjectClassHandle  const & theClass,
     RTI::AttributeHandleSet const & attributeList)
      throw (RTI::ObjectClassNotDefined,
             RTI::AttributeNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 5.8
    void subscribeInteractionClass
    (RTI::InteractionClassHandle const & theClass,
     bool active = true)
      throw (RTI::InteractionClassNotDefined,
             RTI::FederateServiceInvocationsAreBeingReportedViaMOM,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 5.9
    void unsubscribeInteractionClass
    (RTI::InteractionClassHandle const & theClass)
      throw (RTI::InteractionClassNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    ////////////////////////////////
    // Object Management Services //
    ////////////////////////////////

    // 6.2
    void reserveObjectInstanceName
    (std::wstring const & theObjectInstanceName)
      throw (RTI::IllegalName,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 6.4
    RTI::ObjectInstanceHandle registerObjectInstance
    (RTI::ObjectClassHandle const & theClass)
      throw (RTI::ObjectClassNotDefined,
             RTI::ObjectClassNotPublished,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    RTI::ObjectInstanceHandle registerObjectInstance
    (RTI::ObjectClassHandle const & theClass,
     std::wstring const & theObjectInstanceName)
      throw (RTI::ObjectClassNotDefined,
             RTI::ObjectClassNotPublished,
             RTI::ObjectInstanceNameNotReserved,
             RTI::ObjectInstanceNameInUse,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 6.6
    void updateAttributeValues
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleValueMap const & theAttributeValues,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::AttributeNotOwned,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    std::auto_ptr< RTI::MessageRetractionHandle > updateAttributeValues
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleValueMap const & theAttributeValues,
     RTI::UserSuppliedTag const & theUserSuppliedTag,
     RTI::LogicalTime const & theTime)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::AttributeNotOwned,
             RTI::InvalidLogicalTime,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 6.8
    void sendInteraction
    (RTI::InteractionClassHandle  const & theInteraction,
     RTI::ParameterHandleValueMap const & theParameterValues,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::InteractionClassNotPublished,
             RTI::InteractionClassNotDefined,
             RTI::InteractionParameterNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    std::auto_ptr< RTI::MessageRetractionHandle >  sendInteraction
    (RTI::InteractionClassHandle  const & theInteraction,
     RTI::ParameterHandleValueMap const & theParameterValues,
     RTI::UserSuppliedTag const & theUserSuppliedTag,
     RTI::LogicalTime const & theTime)
      throw (RTI::InteractionClassNotPublished,
             RTI::InteractionClassNotDefined,
             RTI::InteractionParameterNotDefined,
             RTI::InvalidLogicalTime,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 6.10
    void deleteObjectInstance
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::DeletePrivilegeNotHeld,
             RTI::ObjectInstanceNotKnown,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    std::auto_ptr< RTI::MessageRetractionHandle >  deleteObjectInstance
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::UserSuppliedTag const & theUserSuppliedTag,
     RTI::LogicalTime  const & theTime)
      throw (RTI::DeletePrivilegeNotHeld,
             RTI::ObjectInstanceNotKnown,
             RTI::InvalidLogicalTime,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 6.12
    void localDeleteObjectInstance
    (RTI::ObjectInstanceHandle const & theObject)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::FederateOwnsAttributes,
             RTI::OwnershipAcquisitionPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 6.13
    void changeAttributeTransportationType
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes,
     RTI::TransportationType const & theType)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::AttributeNotOwned,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 6.14
    void changeInteractionTransportationType
    (RTI::InteractionClassHandle const & theClass,
     RTI::TransportationType const & theType)
      throw (RTI::InteractionClassNotDefined,
             RTI::InteractionClassNotPublished,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 6.17
    void requestAttributeValueUpdate
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    void requestAttributeValueUpdate
    (RTI::ObjectClassHandle const & theClass,
     RTI::AttributeHandleSet const & theAttributes,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::ObjectClassNotDefined,
             RTI::AttributeNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    ///////////////////////////////////
    // Ownership Management Services //
    ///////////////////////////////////
    // 7.2
    void unconditionalAttributeOwnershipDivestiture
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::AttributeNotOwned,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 7.3
    void negotiatedAttributeOwnershipDivestiture
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::AttributeNotOwned,
             RTI::AttributeAlreadyBeingDivested,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 7.6
    void confirmDivestiture
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & confirmedAttributes,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::AttributeNotOwned,
             RTI::AttributeDivestitureWasNotRequested,
             RTI::NoAcquisitionPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 7.8
    void attributeOwnershipAcquisition
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & desiredAttributes,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::ObjectClassNotPublished,
             RTI::AttributeNotDefined,
             RTI::AttributeNotPublished,
             RTI::FederateOwnsAttributes,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 7.9
    void attributeOwnershipAcquisitionIfAvailable
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & desiredAttributes)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::ObjectClassNotPublished,
             RTI::AttributeNotDefined,
             RTI::AttributeNotPublished,
             RTI::FederateOwnsAttributes,
             RTI::AttributeAlreadyBeingAcquired,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 7.12
    std::auto_ptr< RTI::AttributeHandleSet >
    attributeOwnershipDivestitureIfWanted
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::AttributeNotOwned,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 7.13
    void cancelNegotiatedAttributeOwnershipDivestiture
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::AttributeNotOwned,
             RTI::AttributeDivestitureWasNotRequested,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 7.14
    void cancelAttributeOwnershipAcquisition
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::AttributeAlreadyOwned,
             RTI::AttributeAcquisitionWasNotRequested,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 7.16
    void queryAttributeOwnership
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandle const & theAttribute)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 7.18
    bool isAttributeOwnedByFederate
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandle const & theAttribute)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    //////////////////////////////
    // Time Management Services //
    //////////////////////////////

    // 8.2
    void enableTimeRegulation
    (RTI::LogicalTimeInterval const & theLookahead)
      throw (RTI::TimeRegulationAlreadyEnabled,
             RTI::InvalidLookahead,
             RTI::InTimeAdvancingState,
             RTI::RequestForTimeRegulationPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.4
    void disableTimeRegulation ()
      throw (RTI::TimeRegulationIsNotEnabled,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.5
    void enableTimeConstrained ()
      throw (RTI::TimeConstrainedAlreadyEnabled,
             RTI::InTimeAdvancingState,
             RTI::RequestForTimeConstrainedPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.7
    void disableTimeConstrained ()
      throw (RTI::TimeConstrainedIsNotEnabled,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.8
    void timeAdvanceRequest
    (RTI::LogicalTime const & theTime)
      throw (RTI::InvalidLogicalTime,
             RTI::LogicalTimeAlreadyPassed,
             RTI::InTimeAdvancingState,
             RTI::RequestForTimeRegulationPending,
             RTI::RequestForTimeConstrainedPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.9
    void timeAdvanceRequestAvailable
    (RTI::LogicalTime const & theTime)
      throw (RTI::InvalidLogicalTime,
             RTI::LogicalTimeAlreadyPassed,
             RTI::InTimeAdvancingState,
             RTI::RequestForTimeRegulationPending,
             RTI::RequestForTimeConstrainedPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.10
    void nextMessageRequest
    (RTI::LogicalTime const & theTime)
      throw (RTI::InvalidLogicalTime,
             RTI::LogicalTimeAlreadyPassed,
             RTI::InTimeAdvancingState,
             RTI::RequestForTimeRegulationPending,
             RTI::RequestForTimeConstrainedPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.11
    void nextMessageRequestAvailable
    (RTI::LogicalTime const & theTime)
      throw (RTI::InvalidLogicalTime,
             RTI::LogicalTimeAlreadyPassed,
             RTI::InTimeAdvancingState,
             RTI::RequestForTimeRegulationPending,
             RTI::RequestForTimeConstrainedPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.12
    void flushQueueRequest
    (RTI::LogicalTime const & theTime)
      throw (RTI::InvalidLogicalTime,
             RTI::LogicalTimeAlreadyPassed,
             RTI::InTimeAdvancingState,
             RTI::RequestForTimeRegulationPending,
             RTI::RequestForTimeConstrainedPending,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.14
    void enableAsynchronousDelivery ()
      throw (RTI::AsynchronousDeliveryAlreadyEnabled,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.15
    void disableAsynchronousDelivery ()
      throw (RTI::AsynchronousDeliveryAlreadyDisabled,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.16
    std::auto_ptr< RTI::LogicalTime > queryGALT ()
      throw (RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.17
    std::auto_ptr< RTI::LogicalTime > queryLogicalTime ()
      throw (RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.18
    std::auto_ptr< RTI::LogicalTime > queryLITS ()
      throw (RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.19
    void modifyLookahead
    (RTI::LogicalTimeInterval const & theLookahead)
      throw (RTI::TimeRegulationIsNotEnabled,
             RTI::InvalidLookahead,
             RTI::InTimeAdvancingState,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.20
    std::auto_ptr< RTI::LogicalTimeInterval >  queryLookahead ()
      throw (RTI::TimeRegulationIsNotEnabled,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.21
    void retract
    (RTI::MessageRetractionHandle const & theHandle)
      throw (RTI::InvalidRetractionHandle,
             RTI::TimeRegulationIsNotEnabled,
             RTI::MessageCanNoLongerBeRetracted,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.23
    void changeAttributeOrderType
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes,
     RTI::OrderType const & theType)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::AttributeNotOwned,
             RTI::FederateNotExecutionMember,
             RTI::InvalidOrderType,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 8.24
    void changeInteractionOrderType
    (RTI::InteractionClassHandle const & theClass,
     RTI::OrderType const & theType)
      throw (RTI::InteractionClassNotDefined,
             RTI::InteractionClassNotPublished,
             RTI::FederateNotExecutionMember,
             RTI::InvalidOrderType,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    //////////////////////////////////
    // Data Distribution Management //
    //////////////////////////////////

    // 9.2
    RTI::RegionHandle createRegion
    (RTI::DimensionHandleSet const & theDimensions)
      throw (RTI::InvalidDimensionHandle,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.3
    void commitRegionModifications
    (RTI::RegionHandleSet const & theRegionHandleSet)
      throw (RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.4
    void deleteRegion
    (RTI::RegionHandle theRegion)
      throw (RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::RegionInUseForUpdateOrSubscription,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.5
    RTI::ObjectInstanceHandle registerObjectInstanceWithRegions
    (RTI::ObjectClassHandle const & theClass,
     RTI::AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector)
      throw (RTI::ObjectClassNotDefined,
             RTI::ObjectClassNotPublished,
             RTI::AttributeNotDefined,
             RTI::AttributeNotPublished,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::InvalidRegionContext,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    RTI::ObjectInstanceHandle registerObjectInstanceWithRegions
    (RTI::ObjectClassHandle const & theClass,
     RTI::AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector,
     std::wstring const & theObjectInstanceName)
      throw (RTI::ObjectClassNotDefined,
             RTI::ObjectClassNotPublished,
             RTI::AttributeNotDefined,
             RTI::AttributeNotPublished,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::InvalidRegionContext,
             RTI::ObjectInstanceNameNotReserved,
             RTI::ObjectInstanceNameInUse,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.6
    void associateRegionsForUpdates
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::InvalidRegionContext,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.7
    void unassociateRegionsForUpdates
    (RTI::ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::AttributeNotDefined,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.8
    void subscribeObjectClassAttributesWithRegions
    (RTI::ObjectClassHandle const & theClass,
     RTI::AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector,
     bool active = true)
      throw (RTI::ObjectClassNotDefined,
             RTI::AttributeNotDefined,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::InvalidRegionContext,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.9
    void unsubscribeObjectClassAttributesWithRegions
    (RTI::ObjectClassHandle const & theClass,
     RTI::AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector)
      throw (RTI::ObjectClassNotDefined,
             RTI::AttributeNotDefined,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.10
    void subscribeInteractionClassWithRegions
    (RTI::InteractionClassHandle const & theClass,
     RTI::RegionHandleSet const & theRegionHandleSet,
     bool active = true)
      throw (RTI::InteractionClassNotDefined,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::InvalidRegionContext,
             RTI::FederateServiceInvocationsAreBeingReportedViaMOM,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.11
    void unsubscribeInteractionClassWithRegions
    (RTI::InteractionClassHandle const & theClass,
     RTI::RegionHandleSet const & theRegionHandleSet)
      throw (RTI::InteractionClassNotDefined,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.12
    void sendInteractionWithRegions
    (RTI::InteractionClassHandle  const & theInteraction,
     RTI::ParameterHandleValueMap const & theParameterValues,
     RTI::RegionHandleSet const & theRegionHandleSet,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::InteractionClassNotDefined,
             RTI::InteractionClassNotPublished,
             RTI::InteractionParameterNotDefined,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::InvalidRegionContext,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    std::auto_ptr< RTI::MessageRetractionHandle >  sendInteractionWithRegions
    (RTI::InteractionClassHandle  const & theInteraction,
     RTI::ParameterHandleValueMap const & theParameterValues,
     RTI::RegionHandleSet const & theRegionHandleSet,
     RTI::UserSuppliedTag const & theUserSuppliedTag,
     RTI::LogicalTime const & theTime)
      throw (RTI::InteractionClassNotDefined,
             RTI::InteractionClassNotPublished,
             RTI::InteractionParameterNotDefined,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::InvalidRegionContext,
             RTI::InvalidLogicalTime,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 9.13
    void requestAttributeValueUpdateWithRegions
    (RTI::ObjectClassHandle const & theClass,
     RTI::AttributeHandleSetRegionHandleSetPairVector const & theSet,
     RTI::UserSuppliedTag const & theUserSuppliedTag)
      throw (RTI::ObjectClassNotDefined,
             RTI::AttributeNotDefined,
             RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::InvalidRegionContext,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    //////////////////////////
    // RTI Support Services //
    //////////////////////////

    // 10.2
    RTI::ObjectClassHandle getObjectClassHandle
    (std::wstring const & theName)
      throw (RTI::NameNotFound,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.3
    std::wstring getObjectClassName
    (RTI::ObjectClassHandle const & theHandle)
      throw (RTI::InvalidObjectClassHandle,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.4
    RTI::AttributeHandle getAttributeHandle
    (RTI::ObjectClassHandle const & whichClass,
     std::wstring const & theAttributeName)
      throw (RTI::InvalidObjectClassHandle,
             RTI::NameNotFound,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.5
    std::wstring getAttributeName
    (RTI::ObjectClassHandle const & whichClass,
     RTI::AttributeHandle const & theHandle)
      throw (RTI::InvalidObjectClassHandle,
             RTI::InvalidAttributeHandle,
             RTI::AttributeNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.6
    RTI::InteractionClassHandle getInteractionClassHandle
    (std::wstring const & theName)
      throw (RTI::NameNotFound,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.7
    std::wstring getInteractionClassName
    (RTI::InteractionClassHandle const & theHandle)
      throw (RTI::InvalidInteractionClassHandle,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.8
    RTI::ParameterHandle getParameterHandle
    (RTI::InteractionClassHandle const & whichClass,
     std::wstring const & theName)
      throw (RTI::InvalidInteractionClassHandle,
             RTI::NameNotFound,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.9
    std::wstring getParameterName
    (RTI::InteractionClassHandle const & whichClass,
     RTI::ParameterHandle const & theHandle)
      throw (RTI::InvalidInteractionClassHandle,
             RTI::InvalidParameterHandle,
             RTI::InteractionParameterNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.10
    RTI::ObjectInstanceHandle getObjectInstanceHandle
    (std::wstring const & theName)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.11
    std::wstring getObjectInstanceName
    (RTI::ObjectInstanceHandle const & theHandle)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.12
    RTI::DimensionHandle getDimensionHandle
    (std::wstring const & theName)
      throw (RTI::NameNotFound,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.13
    std::wstring getDimensionName
    (RTI::DimensionHandle const & theHandle)
      throw (RTI::InvalidDimensionHandle,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.14
    unsigned long getDimensionUpperBound
    (RTI::DimensionHandle const & theHandle)
      throw (RTI::InvalidDimensionHandle,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.15
    RTI::DimensionHandleSet getAvailableDimensionsForClassAttribute
    (RTI::ObjectClassHandle const & theClass,
     RTI::AttributeHandle const & theHandle)
      throw (RTI::InvalidObjectClassHandle,
             RTI::InvalidAttributeHandle,
             RTI::AttributeNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.16
    RTI::ObjectClassHandle getKnownObjectClassHandle
    (RTI::ObjectInstanceHandle const & theObject)
      throw (RTI::ObjectInstanceNotKnown,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.17
    RTI::DimensionHandleSet getAvailableDimensionsForInteractionClass
    (RTI::InteractionClassHandle const & theClass)
      throw (RTI::InvalidInteractionClassHandle,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.18
    RTI::TransportationType getTransportationType
    (std::wstring const & transportationName)
      throw (RTI::InvalidTransportationName,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.19
    std::wstring getTransportationName
    (RTI::TransportationType const & transportationType)
      throw (RTI::InvalidTransportationType,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.20
    RTI::OrderType getOrderType
    (std::wstring const & orderName)
      throw (RTI::InvalidOrderName,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.21
    std::wstring getOrderName
    (RTI::OrderType const & orderType)
      throw (RTI::InvalidOrderType,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.22
    void enableObjectClassRelevanceAdvisorySwitch ()
      throw (RTI::ObjectClassRelevanceAdvisorySwitchIsOn,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.23
    void disableObjectClassRelevanceAdvisorySwitch ()
      throw (RTI::ObjectClassRelevanceAdvisorySwitchIsOff,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.24
    void enableAttributeRelevanceAdvisorySwitch ()
      throw (RTI::AttributeRelevanceAdvisorySwitchIsOn,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.25
    void disableAttributeRelevanceAdvisorySwitch ()
      throw (RTI::AttributeRelevanceAdvisorySwitchIsOff,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.26
    void enableAttributeScopeAdvisorySwitch ()
      throw (RTI::AttributeScopeAdvisorySwitchIsOn,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.27
    void disableAttributeScopeAdvisorySwitch ()
      throw (RTI::AttributeScopeAdvisorySwitchIsOff,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.28
    void enableInteractionRelevanceAdvisorySwitch ()
      throw (RTI::InteractionRelevanceAdvisorySwitchIsOn,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.29
    void disableInteractionRelevanceAdvisorySwitch ()
      throw (RTI::InteractionRelevanceAdvisorySwitchIsOff,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.30
    RTI::DimensionHandleSet getDimensionHandleSet
    (RTI::RegionHandle const & theRegionHandle)
      throw (RTI::InvalidRegion,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.31
    RTI::RangeBounds getRangeBounds
    (RTI::RegionHandle    const & theRegionHandle,
     RTI::DimensionHandle const & theDimensionHandle)
      throw (RTI::InvalidRegion,
             RTI::RegionDoesNotContainSpecifiedDimension,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.32
    void setRangeBounds
    (RTI::RegionHandle    const & theRegionHandle,
     RTI::DimensionHandle const & theDimensionHandle,
     RTI::RangeBounds     const & theRangeBounds)
      throw (RTI::InvalidRegion,
             RTI::RegionNotCreatedByThisFederate,
             RTI::RegionDoesNotContainSpecifiedDimension,
             RTI::InvalidRangeBound,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.33
    unsigned long normalizeFederateHandle
    (RTI::FederateHandle const & theFederateHandle)
      throw (RTI::InvalidFederateHandle,
             RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.34
    unsigned long normalizeServiceGroup
    (RTI::ServiceGroupIndicator const & theServiceGroup)
      throw (RTI::FederateNotExecutionMember,
             RTI::InvalidServiceGroup,
             RTI::RTIinternalError);

    // 10.37
    bool evokeCallback(double approximateMinimumTimeInSeconds)
      throw (RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.38
    bool evokeMultipleCallbacks(double approximateMinimumTimeInSeconds,
                                        double approximateMaximumTimeInSeconds)
      throw (RTI::FederateNotExecutionMember,
             RTI::RTIinternalError);

    // 10.39
    void enableCallbacks ()
      throw (RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);

    // 10.40
    void disableCallbacks ()
      throw (RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError);
  };
}

#endif // RTI_RTIambServices_h
