/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/RTIambassador.h
***********************************************************************/

// This interface is used to access the services of the RTI. 

#ifndef RTI_RTIambassador_h
#define RTI_RTIambassador_h

#include "RTI/FederateAmbassador.h"
#include "RTI/LogicalTime.h"
#include "RTI/LogicalTimeFactory.h"
#include "RTI/LogicalTimeInterval.h"
#include "RTI/LogicalTimeIntervalFactory.h"
#include "RTI/OrderType.h"
#include "RTI/RangeBounds.h"
#include "RTI/ResignAction.h"
#include "RTI/ServiceGroupIndicator.h"
#include "RTI/TransportationType.h"

/*
namespace RTI
{
  class FederateAmbassador;
  class LogicalTime;
  class LogicalTimeFactory;
  class LogicalTimeInterval;
  class LogicalTimeIntervalFactory;
  class OrderType;
  class RangeBounds;
  class ResignAction;
  class ServiceGroupIndicator;
  class TransportationType;
}
*/

/*
namespace std
{
  template <class T> class auto_ptr;
}
*/
 
#include <string>
#include <RTI/SpecificConfig.h>
#include <RTI/Typedefs.h>
#include <RTI/exception.h>

namespace RTI
{
  class RTI_EXPORT RTIambassador
  {
  protected:
    RTIambassador()
       throw ();

  public:
    virtual
      ~RTIambassador()
     throw ();

    // 4.2
    virtual void createFederationExecution
    (std::wstring const & federationExecutionName,
     std::wstring const & fullPathNameToTheFDDfile)
      throw (FederationExecutionAlreadyExists,
             CouldNotOpenFDD,
             ErrorReadingFDD,
             RTIinternalError) = 0;

    // 4.3
    virtual void destroyFederationExecution 
    (std::wstring const & federationExecutionName)
      throw (FederatesCurrentlyJoined,
             FederationExecutionDoesNotExist,
             RTIinternalError) = 0;

    // 4.4
    virtual FederateHandle joinFederationExecution 
    (std::wstring const & federateType,
     std::wstring const & federationExecutionName,
     FederateAmbassador & federateAmbassador,
     LogicalTimeFactory & logicalTimeFactory,
     LogicalTimeIntervalFactory & logicalTimeIntervalFactory)
      throw (FederateAlreadyExecutionMember,
             FederationExecutionDoesNotExist,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 4.5
    virtual void resignFederationExecution
    (ResignAction resignAction)
      throw (OwnershipAcquisitionPending,
             FederateOwnsAttributes,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 4.6
    virtual void registerFederationSynchronizationPoint
    (std::wstring const & label,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual void registerFederationSynchronizationPoint
    (std::wstring const & label,
     UserSuppliedTag const & theUserSuppliedTag,
     FederateHandleSet const & syncSet)
      throw (FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 4.9
    virtual void synchronizationPointAchieved
    (std::wstring const & label)
      throw (SynchronizationPointLabelNotAnnounced,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 4.11
    virtual void requestFederationSave
    (std::wstring const & label)
      throw (FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual void requestFederationSave
    (std::wstring const & label,
     LogicalTime const & theTime)
      throw (LogicalTimeAlreadyPassed,
             InvalidLogicalTime,
             FederateUnableToUseTime,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 4.13
    virtual void federateSaveBegun ()
      throw (SaveNotInitiated,
             FederateNotExecutionMember,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 4.14
    virtual void federateSaveComplete ()
      throw (FederateHasNotBegunSave,
             FederateNotExecutionMember,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual void federateSaveNotComplete()
      throw (FederateHasNotBegunSave,
             FederateNotExecutionMember,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 4.16
    virtual void queryFederationSaveStatus ()
      throw (FederateNotExecutionMember,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 4.18
    virtual void requestFederationRestore
    (std::wstring const & label)
      throw (FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 4.22
    virtual void federateRestoreComplete ()
      throw (RestoreNotRequested,
             FederateNotExecutionMember,
             SaveInProgress,
             RTIinternalError) = 0;

    virtual void federateRestoreNotComplete ()
      throw (RestoreNotRequested,
             FederateNotExecutionMember,
             SaveInProgress,
             RTIinternalError) = 0;

    // 4.24
    virtual void queryFederationRestoreStatus ()
      throw (FederateNotExecutionMember,
             SaveInProgress,
             RTIinternalError) = 0;

    /////////////////////////////////////
    // Declaration Management Services //
    /////////////////////////////////////
  
    // 5.2
    virtual void publishObjectClassAttributes
    (RTI::ObjectClassHandle  const & theClass,
    RTI::AttributeHandleSet const & attributeList)
      throw (RTI::ObjectClassNotDefined,
             RTI::AttributeNotDefined,
             RTI::FederateNotExecutionMember,
             RTI::SaveInProgress,
             RTI::RestoreInProgress,
             RTI::RTIinternalError) = 0;

    // 5.3
    virtual void unpublishObjectClass
    (ObjectClassHandle const & theClass)
      throw (ObjectClassNotDefined,
             OwnershipAcquisitionPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual void unpublishObjectClassAttributes
    (ObjectClassHandle  const & theClass,
     RTI::AttributeHandleSet const & attributeList)
      throw (ObjectClassNotDefined,
             AttributeNotDefined,
             OwnershipAcquisitionPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 5.4
    virtual void publishInteractionClass
    (InteractionClassHandle const & theInteraction)
      throw (InteractionClassNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 5.5
    virtual void unpublishInteractionClass
    (InteractionClassHandle const & theInteraction)
      throw (InteractionClassNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 5.6
    virtual void subscribeObjectClassAttributes
    (ObjectClassHandle  const & theClass,
     RTI::AttributeHandleSet const & attributeList,
     bool active = true)
      throw (ObjectClassNotDefined,
             AttributeNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 5.7
    virtual void unsubscribeObjectClass
    (ObjectClassHandle const & theClass)
      throw (ObjectClassNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual void unsubscribeObjectClassAttributes
    (ObjectClassHandle  const & theClass,
     RTI::AttributeHandleSet const & attributeList)
      throw (ObjectClassNotDefined,
             AttributeNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 5.8
    virtual void subscribeInteractionClass
    (InteractionClassHandle const & theClass,
     bool active = true)
      throw (InteractionClassNotDefined,
             FederateServiceInvocationsAreBeingReportedViaMOM,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 5.9
    virtual void unsubscribeInteractionClass
    (InteractionClassHandle const & theClass)
      throw (InteractionClassNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    ////////////////////////////////
    // Object Management Services //
    ////////////////////////////////
  
    // 6.2
    virtual void reserveObjectInstanceName
    (std::wstring const & theObjectInstanceName)
      throw (IllegalName,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 6.4
    virtual ObjectInstanceHandle registerObjectInstance
    (ObjectClassHandle const & theClass)
      throw (ObjectClassNotDefined,
             ObjectClassNotPublished,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual ObjectInstanceHandle registerObjectInstance
    (ObjectClassHandle const & theClass,
     std::wstring const & theObjectInstanceName)
      throw (ObjectClassNotDefined,
             ObjectClassNotPublished,
             ObjectInstanceNameNotReserved,
             ObjectInstanceNameInUse,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 6.6
    virtual void updateAttributeValues
    (ObjectInstanceHandle const & theObject,
     AttributeHandleValueMap const & theAttributeValues,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             AttributeNotOwned,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual std::auto_ptr< MessageRetractionHandle > updateAttributeValues
    (ObjectInstanceHandle const & theObject,
     AttributeHandleValueMap const & theAttributeValues,
     UserSuppliedTag const & theUserSuppliedTag,
     LogicalTime const & theTime)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             AttributeNotOwned,
             InvalidLogicalTime,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 6.8
    virtual void sendInteraction
    (InteractionClassHandle  const & theInteraction,
     ParameterHandleValueMap const & theParameterValues,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (InteractionClassNotPublished,
             InteractionClassNotDefined,
             InteractionParameterNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual std::auto_ptr< MessageRetractionHandle >  sendInteraction
    (InteractionClassHandle  const & theInteraction,
     ParameterHandleValueMap const & theParameterValues,
     UserSuppliedTag const & theUserSuppliedTag,
     LogicalTime const & theTime)
      throw (InteractionClassNotPublished,
             InteractionClassNotDefined,
             InteractionParameterNotDefined,
             InvalidLogicalTime,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 6.10
    virtual void deleteObjectInstance
    (ObjectInstanceHandle const & theObject,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (DeletePrivilegeNotHeld,
             ObjectInstanceNotKnown,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual std::auto_ptr< MessageRetractionHandle >  deleteObjectInstance
    (ObjectInstanceHandle const & theObject,
     UserSuppliedTag const & theUserSuppliedTag,
     LogicalTime  const & theTime)
      throw (DeletePrivilegeNotHeld,
             ObjectInstanceNotKnown,
             InvalidLogicalTime,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 6.12
    virtual void localDeleteObjectInstance
    (ObjectInstanceHandle const & theObject)
      throw (ObjectInstanceNotKnown,
             FederateOwnsAttributes,
             OwnershipAcquisitionPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 6.13
    virtual void changeAttributeTransportationType
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes,
     TransportationType const & theType)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             AttributeNotOwned,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 6.14
    virtual void changeInteractionTransportationType
    (InteractionClassHandle const & theClass,
     TransportationType const & theType)
      throw (InteractionClassNotDefined,
             InteractionClassNotPublished,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;
  
    // 6.17
    virtual void requestAttributeValueUpdate
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual void requestAttributeValueUpdate
    (ObjectClassHandle const & theClass,
     RTI::AttributeHandleSet const & theAttributes,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (ObjectClassNotDefined,
             AttributeNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    ///////////////////////////////////
    // Ownership Management Services //
    ///////////////////////////////////
    // 7.2
    virtual void unconditionalAttributeOwnershipDivestiture
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             AttributeNotOwned,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 7.3
    virtual void negotiatedAttributeOwnershipDivestiture
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             AttributeNotOwned,
             AttributeAlreadyBeingDivested,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 7.6
    virtual void confirmDivestiture
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & confirmedAttributes,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             AttributeNotOwned,
             AttributeDivestitureWasNotRequested,
             NoAcquisitionPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 7.8
    virtual void attributeOwnershipAcquisition
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & desiredAttributes,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (ObjectInstanceNotKnown,
             ObjectClassNotPublished,
             AttributeNotDefined,
             AttributeNotPublished,
             FederateOwnsAttributes,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 7.9
    virtual void attributeOwnershipAcquisitionIfAvailable
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & desiredAttributes)
      throw (ObjectInstanceNotKnown,
             ObjectClassNotPublished,
             AttributeNotDefined,
             AttributeNotPublished,
             FederateOwnsAttributes,
             AttributeAlreadyBeingAcquired,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 7.12
    virtual std::auto_ptr< RTI::AttributeHandleSet >
    attributeOwnershipDivestitureIfWanted
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             AttributeNotOwned,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 7.13
    virtual void cancelNegotiatedAttributeOwnershipDivestiture
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             AttributeNotOwned,
             AttributeDivestitureWasNotRequested,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 7.14
    virtual void cancelAttributeOwnershipAcquisition
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             AttributeAlreadyOwned,
             AttributeAcquisitionWasNotRequested,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 7.16
    virtual void queryAttributeOwnership
    (ObjectInstanceHandle const & theObject,
     AttributeHandle const & theAttribute)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 7.18
    virtual bool isAttributeOwnedByFederate
    (ObjectInstanceHandle const & theObject,
     AttributeHandle const & theAttribute)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    //////////////////////////////
    // Time Management Services //
    //////////////////////////////
  
    // 8.2
    virtual void enableTimeRegulation
    (LogicalTimeInterval const & theLookahead)
      throw (TimeRegulationAlreadyEnabled,
             InvalidLookahead,
             InTimeAdvancingState,
             RequestForTimeRegulationPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.4
    virtual void disableTimeRegulation ()
      throw (TimeRegulationIsNotEnabled,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.5
    virtual void enableTimeConstrained ()
      throw (TimeConstrainedAlreadyEnabled,
             InTimeAdvancingState,
             RequestForTimeConstrainedPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.7
    virtual void disableTimeConstrained ()
      throw (TimeConstrainedIsNotEnabled,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.8
    virtual void timeAdvanceRequest
    (LogicalTime const & theTime)
      throw (InvalidLogicalTime,
             LogicalTimeAlreadyPassed,
             InTimeAdvancingState,
             RequestForTimeRegulationPending,
             RequestForTimeConstrainedPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.9
    virtual void timeAdvanceRequestAvailable
    (LogicalTime const & theTime)
      throw (InvalidLogicalTime,
             LogicalTimeAlreadyPassed,
             InTimeAdvancingState,
             RequestForTimeRegulationPending,
             RequestForTimeConstrainedPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.10
    virtual void nextMessageRequest
    (LogicalTime const & theTime)
      throw (InvalidLogicalTime,
             LogicalTimeAlreadyPassed,
             InTimeAdvancingState,
             RequestForTimeRegulationPending,
             RequestForTimeConstrainedPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.11
    virtual void nextMessageRequestAvailable
    (LogicalTime const & theTime)
      throw (InvalidLogicalTime,
             LogicalTimeAlreadyPassed,
             InTimeAdvancingState,
             RequestForTimeRegulationPending,
             RequestForTimeConstrainedPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.12
    virtual void flushQueueRequest
    (LogicalTime const & theTime)
      throw (InvalidLogicalTime,
             LogicalTimeAlreadyPassed,
             InTimeAdvancingState,
             RequestForTimeRegulationPending,
             RequestForTimeConstrainedPending,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.14
    virtual void enableAsynchronousDelivery ()
      throw (AsynchronousDeliveryAlreadyEnabled,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.15
    virtual void disableAsynchronousDelivery ()
      throw (AsynchronousDeliveryAlreadyDisabled,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.16
    virtual std::auto_ptr< LogicalTime > queryGALT ()
      throw (FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.17
    virtual std::auto_ptr< LogicalTime > queryLogicalTime ()
      throw (FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.18
    virtual std::auto_ptr< LogicalTime > queryLITS ()
      throw (FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.19
    virtual void modifyLookahead
    (LogicalTimeInterval const & theLookahead)
      throw (TimeRegulationIsNotEnabled,
             InvalidLookahead,
             InTimeAdvancingState,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.20
    virtual std::auto_ptr< LogicalTimeInterval >  queryLookahead ()
      throw (TimeRegulationIsNotEnabled,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.21
    virtual void retract
    (MessageRetractionHandle const & theHandle)
      throw (InvalidRetractionHandle,
             TimeRegulationIsNotEnabled,
             MessageCanNoLongerBeRetracted,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.23
    virtual void changeAttributeOrderType
    (ObjectInstanceHandle const & theObject,
     RTI::AttributeHandleSet const & theAttributes,
     OrderType const & theType)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             AttributeNotOwned,
             FederateNotExecutionMember,
             InvalidOrderType,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 8.24
    virtual void changeInteractionOrderType
    (InteractionClassHandle const & theClass,
     OrderType const & theType)
      throw (InteractionClassNotDefined,
             InteractionClassNotPublished,
             FederateNotExecutionMember,
             InvalidOrderType,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    //////////////////////////////////
    // Data Distribution Management //
    //////////////////////////////////
  
    // 9.2
    virtual RegionHandle createRegion
    (DimensionHandleSet const & theDimensions)
      throw (InvalidDimensionHandle,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.3
    virtual void commitRegionModifications
    (RegionHandleSet const & theRegionHandleSet)
      throw (InvalidRegion,
             RegionNotCreatedByThisFederate,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.4
    virtual void deleteRegion
    (RegionHandle theRegion)
      throw (InvalidRegion,
             RegionNotCreatedByThisFederate,
             RegionInUseForUpdateOrSubscription,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.5
    virtual ObjectInstanceHandle registerObjectInstanceWithRegions
    (ObjectClassHandle const & theClass,
     RTI::AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector)
      throw (ObjectClassNotDefined,
             ObjectClassNotPublished,
             AttributeNotDefined,
             AttributeNotPublished,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             InvalidRegionContext,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual ObjectInstanceHandle registerObjectInstanceWithRegions
    (ObjectClassHandle const & theClass,
     RTI::AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector,
     std::wstring const & theObjectInstanceName)
      throw (ObjectClassNotDefined,
             ObjectClassNotPublished,
             AttributeNotDefined,
             AttributeNotPublished,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             InvalidRegionContext,
             ObjectInstanceNameNotReserved,
             ObjectInstanceNameInUse,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.6
    virtual void associateRegionsForUpdates
    (ObjectInstanceHandle const & theObject,
     AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             InvalidRegionContext,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.7
    virtual void unassociateRegionsForUpdates
    (ObjectInstanceHandle const & theObject,
     AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector)
      throw (ObjectInstanceNotKnown,
             AttributeNotDefined,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.8
    virtual void subscribeObjectClassAttributesWithRegions
    (ObjectClassHandle const & theClass,
     AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector,
     bool active = true)
      throw (ObjectClassNotDefined,
             AttributeNotDefined,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             InvalidRegionContext,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.9
    virtual void unsubscribeObjectClassAttributesWithRegions
    (ObjectClassHandle const & theClass,
     AttributeHandleSetRegionHandleSetPairVector const &
     theAttributeHandleSetRegionHandleSetPairVector)
      throw (ObjectClassNotDefined,
             AttributeNotDefined,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.10
    virtual void subscribeInteractionClassWithRegions
    (InteractionClassHandle const & theClass,
     RegionHandleSet const & theRegionHandleSet,
     bool active = true)
      throw (InteractionClassNotDefined,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             InvalidRegionContext,
             FederateServiceInvocationsAreBeingReportedViaMOM,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.11
    virtual void unsubscribeInteractionClassWithRegions
    (InteractionClassHandle const & theClass,
     RegionHandleSet const & theRegionHandleSet)
      throw (InteractionClassNotDefined,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.12
    virtual void sendInteractionWithRegions
    (InteractionClassHandle  const & theInteraction,
     ParameterHandleValueMap const & theParameterValues,
     RegionHandleSet const & theRegionHandleSet,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (InteractionClassNotDefined,
             InteractionClassNotPublished,
             InteractionParameterNotDefined,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             InvalidRegionContext,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    virtual std::auto_ptr< MessageRetractionHandle >  sendInteractionWithRegions
    (InteractionClassHandle  const & theInteraction,
     ParameterHandleValueMap const & theParameterValues,
     RegionHandleSet const & theRegionHandleSet,
     UserSuppliedTag const & theUserSuppliedTag,
     LogicalTime const & theTime)
      throw (InteractionClassNotDefined,
             InteractionClassNotPublished,
             InteractionParameterNotDefined,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             InvalidRegionContext,
             InvalidLogicalTime,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 9.13
    virtual void requestAttributeValueUpdateWithRegions
    (ObjectClassHandle const & theClass,
     AttributeHandleSetRegionHandleSetPairVector const & theSet,
     UserSuppliedTag const & theUserSuppliedTag)
      throw (ObjectClassNotDefined,
             AttributeNotDefined,
             InvalidRegion,
             RegionNotCreatedByThisFederate,
             InvalidRegionContext,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    //////////////////////////
    // RTI Support Services //
    //////////////////////////
  
    // 10.2
    virtual ObjectClassHandle getObjectClassHandle
    (std::wstring const & theName)
      throw (NameNotFound,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.3
    virtual std::wstring getObjectClassName
    (ObjectClassHandle const & theHandle)
      throw (InvalidObjectClassHandle,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.4
    virtual AttributeHandle getAttributeHandle
    (ObjectClassHandle const & whichClass,
     std::wstring const & theAttributeName)
      throw (InvalidObjectClassHandle,
             NameNotFound,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.5
    virtual std::wstring getAttributeName
    (ObjectClassHandle const & whichClass,
     AttributeHandle const & theHandle)   
      throw (InvalidObjectClassHandle,
             InvalidAttributeHandle,
             AttributeNotDefined,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.6
    virtual InteractionClassHandle getInteractionClassHandle
    (std::wstring const & theName)
      throw (NameNotFound,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.7
    virtual std::wstring getInteractionClassName
    (InteractionClassHandle const & theHandle)
      throw (InvalidInteractionClassHandle,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.8
    virtual ParameterHandle getParameterHandle
    (InteractionClassHandle const & whichClass,
     std::wstring const & theName)
      throw (InvalidInteractionClassHandle,
             NameNotFound,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.9
    virtual std::wstring getParameterName
    (InteractionClassHandle const & whichClass,
     ParameterHandle const & theHandle)   
      throw (InvalidInteractionClassHandle,
             InvalidParameterHandle,
             InteractionParameterNotDefined,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.10
    virtual ObjectInstanceHandle getObjectInstanceHandle
    (std::wstring const & theName)
      throw (ObjectInstanceNotKnown,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.11
    virtual std::wstring getObjectInstanceName
    (ObjectInstanceHandle const & theHandle)
      throw (ObjectInstanceNotKnown,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.12
    virtual DimensionHandle getDimensionHandle
    (std::wstring const & theName)
      throw (NameNotFound,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.13
    virtual std::wstring getDimensionName
    (DimensionHandle const & theHandle)
      throw (InvalidDimensionHandle,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.14
    virtual unsigned long getDimensionUpperBound
    (DimensionHandle const & theHandle)   
      throw (InvalidDimensionHandle,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.15
    virtual DimensionHandleSet getAvailableDimensionsForClassAttribute
    (ObjectClassHandle const & theClass,
     AttributeHandle const & theHandle)   
      throw (InvalidObjectClassHandle,
             InvalidAttributeHandle,
             AttributeNotDefined,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.16
    virtual ObjectClassHandle getKnownObjectClassHandle
    (ObjectInstanceHandle const & theObject)
      throw (ObjectInstanceNotKnown,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.17
    virtual DimensionHandleSet getAvailableDimensionsForInteractionClass
    (InteractionClassHandle const & theClass)
      throw (InvalidInteractionClassHandle,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.18
    virtual TransportationType getTransportationType
    (std::wstring const & transportationName)
      throw (InvalidTransportationName,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.19
    virtual std::wstring getTransportationName
    (TransportationType const & transportationType)
      throw (InvalidTransportationType,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.20
    virtual OrderType getOrderType
    (std::wstring const & orderName)
      throw (InvalidOrderName,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.21
    virtual std::wstring getOrderName
    (OrderType const & orderType)
      throw (InvalidOrderType,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.22
    virtual void enableObjectClassRelevanceAdvisorySwitch ()
      throw (ObjectClassRelevanceAdvisorySwitchIsOn,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.23
    virtual void disableObjectClassRelevanceAdvisorySwitch ()
      throw (ObjectClassRelevanceAdvisorySwitchIsOff,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.24
    virtual void enableAttributeRelevanceAdvisorySwitch ()
      throw (AttributeRelevanceAdvisorySwitchIsOn,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.25
    virtual void disableAttributeRelevanceAdvisorySwitch ()
      throw (AttributeRelevanceAdvisorySwitchIsOff,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.26
    virtual void enableAttributeScopeAdvisorySwitch ()
      throw (AttributeScopeAdvisorySwitchIsOn,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.27
    virtual void disableAttributeScopeAdvisorySwitch ()
      throw (AttributeScopeAdvisorySwitchIsOff,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.28
    virtual void enableInteractionRelevanceAdvisorySwitch ()
      throw (InteractionRelevanceAdvisorySwitchIsOn,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.29
    virtual void disableInteractionRelevanceAdvisorySwitch ()
      throw (InteractionRelevanceAdvisorySwitchIsOff,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.30
    virtual
    DimensionHandleSet getDimensionHandleSet
    (RegionHandle const & theRegionHandle)
      throw (InvalidRegion,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.31
    virtual
    RangeBounds getRangeBounds
    (RegionHandle    const & theRegionHandle,
     DimensionHandle const & theDimensionHandle)
      throw (InvalidRegion,
             RegionDoesNotContainSpecifiedDimension,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.32
    virtual void setRangeBounds
    (RegionHandle    const & theRegionHandle,
     DimensionHandle const & theDimensionHandle,
     RangeBounds     const & theRangeBounds)
      throw (InvalidRegion,
             RegionNotCreatedByThisFederate,
             RegionDoesNotContainSpecifiedDimension,
             InvalidRangeBound,
             FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.33
    virtual unsigned long normalizeFederateHandle
    (FederateHandle const & theFederateHandle)
      throw (InvalidFederateHandle,
             FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.34
    virtual unsigned long normalizeServiceGroup
    (ServiceGroupIndicator const & theServiceGroup)
      throw (FederateNotExecutionMember,
             InvalidServiceGroup,
             RTIinternalError) = 0;

    // 10.37
    virtual bool evokeCallback(double approximateMinimumTimeInSeconds)
      throw (FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.38
    virtual bool evokeMultipleCallbacks(double approximateMinimumTimeInSeconds,
                                        double approximateMaximumTimeInSeconds)
      throw (FederateNotExecutionMember,
             RTIinternalError) = 0;

    // 10.39
    virtual void enableCallbacks ()
      throw (FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

    // 10.40
    virtual void disableCallbacks ()
      throw (FederateNotExecutionMember,
             SaveInProgress,
             RestoreInProgress,
             RTIinternalError) = 0;

  };
}

#endif // RTI_RTIambassador_h
