/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/exception.i
***********************************************************************/

RTI_INLINE
RTI::exception::
exception() 
{
}

////////////////////////////////////////////////////////////////////////////////
RTI_INLINE
RTI::exception::
exception(RTI::exception const &) 
{
}

////////////////////////////////////////////////////////////////////////////////
RTI_INLINE
RTI::exception & 
RTI::exception::
operator=(exception const &) 
{
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
RTI_INLINE
RTI::exception::
~exception() 
  // throw()
{
}

////////////////////////////////////////////////////////////////////////////////
RTI_INLINE
wchar_t const *
RTI::exception::
what() const
  throw()
{
  return L"";
}

namespace RTI
{
#define RTI_EXCEPTION(A)                                \
  RTI_INLINE A::A(std::wstring const & message) throw() \
    : _msg(message)                                     \
  {                                                     \
}                                                       \
  RTI_INLINE wchar_t const *A::what() const throw()     \
  {                                                     \
    return _msg.c_str();                                \
  }

  RTI_EXCEPTION(AsynchronousDeliveryAlreadyDisabled)
  RTI_EXCEPTION(AsynchronousDeliveryAlreadyEnabled)  
  RTI_EXCEPTION(AttributeAcquisitionWasNotCanceled)  
  RTI_EXCEPTION(AttributeAcquisitionWasNotRequested)
  RTI_EXCEPTION(AttributeAlreadyBeingAcquired)  
  RTI_EXCEPTION(AttributeAlreadyBeingDivested)  
  RTI_EXCEPTION(AttributeAlreadyOwned)
  RTI_EXCEPTION(AttributeDivestitureWasNotRequested)  
  RTI_EXCEPTION(AttributeNotDefined)
  RTI_EXCEPTION(AttributeNotOwned)
  RTI_EXCEPTION(AttributeNotPublished)
  RTI_EXCEPTION(AttributeNotRecognized)
  RTI_EXCEPTION(AttributeNotSubscribed)
  RTI_EXCEPTION(AttributeRelevanceAdvisorySwitchIsOff)
  RTI_EXCEPTION(AttributeRelevanceAdvisorySwitchIsOn)
  RTI_EXCEPTION(AttributeScopeAdvisorySwitchIsOff)
  RTI_EXCEPTION(AttributeScopeAdvisorySwitchIsOn)
  RTI_EXCEPTION(BadInitializationParameter)
  RTI_EXCEPTION(CouldNotDecode)  
  RTI_EXCEPTION(CouldNotDiscover)
  RTI_EXCEPTION(CouldNotOpenFDD)
  RTI_EXCEPTION(CouldNotInitiateRestore)
  RTI_EXCEPTION(DeletePrivilegeNotHeld)
  RTI_EXCEPTION(RequestForTimeConstrainedPending)
  RTI_EXCEPTION(NoRequestToEnableTimeConstrainedWasPending)
  RTI_EXCEPTION(RequestForTimeRegulationPending)
  RTI_EXCEPTION(NoRequestToEnableTimeRegulationWasPending)  
  RTI_EXCEPTION(ErrorReadingFDD)
  RTI_EXCEPTION(FederateAlreadyExecutionMember)
  RTI_EXCEPTION(FederateHasNotBegunSave)
  RTI_EXCEPTION(FederateInternalError)
  RTI_EXCEPTION(FederateNotExecutionMember)
  RTI_EXCEPTION(FederateOwnsAttributes)
  RTI_EXCEPTION(FederateServiceInvocationsAreBeingReportedViaMOM)
  RTI_EXCEPTION(FederateUnableToUseTime)
  RTI_EXCEPTION(FederatesCurrentlyJoined)
  RTI_EXCEPTION(FederationExecutionAlreadyExists)
  RTI_EXCEPTION(FederationExecutionDoesNotExist)
  RTI_EXCEPTION(IllegalName)
  RTI_EXCEPTION(IllegalTimeArithmetic)
  RTI_EXCEPTION(InteractionClassNotDefined)
  RTI_EXCEPTION(InteractionClassNotPublished)
  RTI_EXCEPTION(InteractionClassNotRecognized)
  RTI_EXCEPTION(InteractionClassNotSubscribed)  
  RTI_EXCEPTION(InteractionParameterNotDefined)
  RTI_EXCEPTION(InteractionParameterNotRecognized)
  RTI_EXCEPTION(InteractionRelevanceAdvisorySwitchIsOff)
  RTI_EXCEPTION(InteractionRelevanceAdvisorySwitchIsOn)
  RTI_EXCEPTION(InTimeAdvancingState)
  RTI_EXCEPTION(InvalidAttributeHandle)
  RTI_EXCEPTION(InvalidDimensionHandle)
  RTI_EXCEPTION(InvalidFederateHandle)
  RTI_EXCEPTION(InvalidInteractionClassHandle)
  RTI_EXCEPTION(InvalidLogicalTime)
  RTI_EXCEPTION(InvalidLogicalTimeInterval)  
  RTI_EXCEPTION(InvalidLookahead)
  RTI_EXCEPTION(InvalidObjectClassHandle)
  RTI_EXCEPTION(InvalidOrderName)
  RTI_EXCEPTION(InvalidOrderType)
  RTI_EXCEPTION(InvalidParameterHandle)
  RTI_EXCEPTION(InvalidRangeBound)
  RTI_EXCEPTION(InvalidRegion)
  RTI_EXCEPTION(InvalidRegionContext)
  RTI_EXCEPTION(InvalidRetractionHandle)
  RTI_EXCEPTION(InvalidServiceGroup)
  RTI_EXCEPTION(InvalidTransportationName)
  RTI_EXCEPTION(InvalidTransportationType)
  RTI_EXCEPTION(JoinedFederateIsNotInTimeAdvancingState)
  RTI_EXCEPTION(LogicalTimeAlreadyPassed)
  RTI_EXCEPTION(MessageCanNoLongerBeRetracted)
  RTI_EXCEPTION(NameNotFound)
  RTI_EXCEPTION(NoAcquisitionPending)
  RTI_EXCEPTION(ObjectClassNotDefined)
  RTI_EXCEPTION(ObjectClassNotKnown)
  RTI_EXCEPTION(ObjectClassNotPublished)
  RTI_EXCEPTION(ObjectClassRelevanceAdvisorySwitchIsOff)
  RTI_EXCEPTION(ObjectClassRelevanceAdvisorySwitchIsOn)
  RTI_EXCEPTION(ObjectInstanceNameInUse)
  RTI_EXCEPTION(ObjectInstanceNameNotReserved)
  RTI_EXCEPTION(ObjectInstanceNotKnown)
  RTI_EXCEPTION(OwnershipAcquisitionPending)
  RTI_EXCEPTION(RTIinternalError)
  RTI_EXCEPTION(RegionDoesNotContainSpecifiedDimension)
  RTI_EXCEPTION(RegionInUseForUpdateOrSubscription)
  RTI_EXCEPTION(RegionNotCreatedByThisFederate)
  RTI_EXCEPTION(RestoreInProgress)  
  RTI_EXCEPTION(RestoreNotRequested)
  RTI_EXCEPTION(SaveInProgress)
  RTI_EXCEPTION(SaveNotInitiated)
  RTI_EXCEPTION(SpecifiedSaveLabelDoesNotExist)
  RTI_EXCEPTION(SynchronizationPointLabelNotAnnounced)
  RTI_EXCEPTION(TimeConstrainedAlreadyEnabled)
  RTI_EXCEPTION(TimeConstrainedIsNotEnabled)
  RTI_EXCEPTION(TimeRegulationAlreadyEnabled)
  RTI_EXCEPTION(TimeRegulationIsNotEnabled)
  RTI_EXCEPTION(UnableToPerformSave)
  RTI_EXCEPTION(UnknownName)
  RTI_EXCEPTION(InternalError)
#undef RTI_EXCEPTION
}
