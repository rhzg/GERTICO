  }

  catch(RTI::AsynchronousDeliveryAlreadyDisabled)
	{
		throw RTI_V1_3::AsynchronousDeliveryAlreadyDisabled("");
  }
  catch(RTI::AsynchronousDeliveryAlreadyEnabled)  
	{
		throw RTI_V1_3::AsynchronousDeliveryAlreadyEnabled("");
  }
  catch(RTI::AttributeAcquisitionWasNotCanceled)  
	{
		throw RTI_V1_3::AttributeAcquisitionWasNotCanceled("");
  }
  catch(RTI::AttributeAcquisitionWasNotRequested)
	{
		throw RTI_V1_3::AttributeAcquisitionWasNotRequested("");
  }
  catch(RTI::AttributeAlreadyBeingAcquired)  
	{
		throw RTI_V1_3::AttributeAlreadyBeingAcquired("");
  }
  catch(RTI::AttributeAlreadyBeingDivested)  
	{
		throw RTI_V1_3::AttributeAlreadyBeingDivested("");
  }
  catch(RTI::AttributeAlreadyOwned)
	{
		throw RTI_V1_3::AttributeAlreadyOwned("");
  }
  catch(RTI::AttributeDivestitureWasNotRequested)  
	{
		throw RTI_V1_3::AttributeDivestitureWasNotRequested("");
  }
  catch(RTI::AttributeNotDefined)
	{
		throw RTI_V1_3::AttributeNotDefined("");
  }
  catch(RTI::AttributeNotOwned)
	{
		throw RTI_V1_3::AttributeNotOwned("");
  }
  catch(RTI::AttributeNotPublished)
	{
		throw RTI_V1_3::AttributeNotPublished("");
  }
  catch(RTI::AttributeNotRecognized)
	{
		throw RTI_V1_3::AttributeNotKnown("AttributeNotRecognized");
  }
  catch(RTI::AttributeNotSubscribed)
	{
		throw RTI_V1_3::ObjectClassNotSubscribed("AttributeNotSubscribed");
  }
  catch(RTI::AttributeRelevanceAdvisorySwitchIsOff)
	{
		throw RTI_V1_3::RTIinternalError("AttributeRelevanceAdvisorySwitchIsOff");
  }
  catch(RTI::AttributeRelevanceAdvisorySwitchIsOn)
	{
		throw RTI_V1_3::RTIinternalError("AttributeRelevanceAdvisorySwitchIsOn");
  }
  catch(RTI::AttributeScopeAdvisorySwitchIsOff)
	{
		throw RTI_V1_3::RTIinternalError("AttributeScopeAdvisorySwitchIsOff");
  }
  catch(RTI::AttributeScopeAdvisorySwitchIsOn)
	{
		throw RTI_V1_3::RTIinternalError("AttributeScopeAdvisorySwitchIsOn");
  }
  catch(RTI::BadInitializationParameter)
	{
		throw RTI_V1_3::RTIinternalError("BadInitializationParameter");
  }
  catch(RTI::CouldNotDecode)  
	{
		throw RTI_V1_3::RTIinternalError("CouldNotDecode");
  }
  catch(RTI::CouldNotDiscover)
	{
		throw RTI_V1_3::CouldNotDiscover("");
  }
  catch(RTI::CouldNotOpenFDD)
	{
		throw RTI_V1_3::CouldNotOpenFED("CouldNotOpenFDD");
	}
  catch(RTI::CouldNotInitiateRestore)
	{
		throw RTI_V1_3::CouldNotRestore("CouldNotInitiateRestore");
  }
  catch(RTI::DeletePrivilegeNotHeld)
	{
		throw RTI_V1_3::DeletePrivilegeNotHeld("");
  }
  catch(RTI::RequestForTimeConstrainedPending)
	{
		throw RTI_V1_3::EnableTimeConstrainedPending("RequestForTimeConstrainedPending");
  }
  catch(RTI::NoRequestToEnableTimeConstrainedWasPending)
	{
		throw RTI_V1_3::RTIinternalError("NoRequestToEnableTimeConstrainedWasPending");
  }
  catch(RTI::RequestForTimeRegulationPending)
	{
		throw RTI_V1_3::EnableTimeRegulationPending("RequestForTimeRegulationPending");
  }
  catch(RTI::NoRequestToEnableTimeRegulationWasPending)  
 	{
		throw RTI_V1_3::RTIinternalError("NoRequestToEnableTimeRegulationWasPending");
  }
  catch(RTI::ErrorReadingFDD)
	{
		throw RTI_V1_3::ErrorReadingFED("ErrorReadingFDD");
	}
  catch(RTI::FederateAlreadyExecutionMember)
	{
		throw RTI_V1_3::FederateAlreadyExecutionMember("");
	}
  catch(RTI::FederateHasNotBegunSave)
 	{
		throw RTI_V1_3::SaveNotInitiated("FederateHasNotBegunSave");
  }
  catch(RTI::FederateInternalError)
 	{
		throw RTI_V1_3::RTIinternalError("FederateInternalError");
  }
  catch(RTI::FederateNotExecutionMember)
	{
		throw RTI_V1_3::FederateNotExecutionMember("");
	}
  catch(RTI::FederateOwnsAttributes)
	{
		throw RTI_V1_3::FederateOwnsAttributes("");
	}
  catch(RTI::FederateServiceInvocationsAreBeingReportedViaMOM)
	{
		throw RTI_V1_3::RTIinternalError("FederateServiceInvocationsAreBeingReportedViaMOM");
  }
  catch(RTI::FederateUnableToUseTime)
	{
		throw RTI_V1_3::RTIinternalError("FederateUnableToUseTime");
  }
  catch(RTI::FederatesCurrentlyJoined)
	{
		throw RTI_V1_3::FederatesCurrentlyJoined("");
	}
  catch(RTI::FederationExecutionAlreadyExists)
	{
		throw RTI_V1_3::FederationExecutionAlreadyExists("");
	}
  catch(RTI::FederationExecutionDoesNotExist)
	{
		throw RTI_V1_3::FederationExecutionDoesNotExist("");
	}
  catch(RTI::IllegalName)
	{
		throw RTI_V1_3::RTIinternalError("IllegalName");
  }
  catch(RTI::IllegalTimeArithmetic)
	{
		throw RTI_V1_3::RTIinternalError("IllegalTimeArithmetic");
  }
  catch(RTI::InteractionClassNotDefined)
	{
		throw RTI_V1_3::InteractionClassNotDefined("");
  }
  catch(RTI::InteractionClassNotPublished)
	{
		throw RTI_V1_3::InteractionClassNotPublished("");
  }
  catch(RTI::InteractionClassNotRecognized)
	{
		throw RTI_V1_3::InteractionClassNotKnown("InteractionClassNotRecognized");
  }
  catch(RTI::InteractionClassNotSubscribed)  
	{
		throw RTI_V1_3::InteractionClassNotSubscribed("");
  }
  catch(RTI::InteractionParameterNotDefined)
	{
		throw RTI_V1_3::InteractionParameterNotDefined("");
  }
  catch(RTI::InteractionParameterNotRecognized)
	{
		throw RTI_V1_3::InteractionParameterNotKnown("InteractionParameterNotRecognized");
  }
  catch(RTI::InteractionRelevanceAdvisorySwitchIsOff)
	{
		throw RTI_V1_3::RTIinternalError("InteractionRelevanceAdvisorySwitchIsOff");
  }
  catch(RTI::InteractionRelevanceAdvisorySwitchIsOn)
	{
		throw RTI_V1_3::RTIinternalError("InteractionRelevanceAdvisorySwitchIsOn");
  }
  catch(RTI::InTimeAdvancingState)
	{
		throw RTI_V1_3::TimeAdvanceAlreadyInProgress("InTimeAdvancingState");
  }
  catch(RTI::InvalidAttributeHandle)
	{
		throw RTI_V1_3::RTIinternalError("InvalidAttributeHandle");
  }
  catch(RTI::InvalidDimensionHandle)
	{
		throw RTI_V1_3::DimensionNotDefined("InvalidDimensionHandle");
  }
  catch(RTI::InvalidInteractionClassHandle)
	{
		throw RTI_V1_3::InteractionClassNotDefined("InvalidInteractionClassHandle");
  }
  catch(RTI::InvalidLogicalTime)
	{
		throw RTI_V1_3::InvalidFederationTime("InvalidLogicalTime");
  }
  catch(RTI::InvalidLogicalTimeInterval)  
	{
		throw RTI_V1_3::RTIinternalError("InvalidLogicalTimeInterval");
  }
  catch(RTI::InvalidLookahead)
	{
		throw RTI_V1_3::InvalidLookahead("");
  }
  catch(RTI::InvalidObjectClassHandle)
	{
		throw RTI_V1_3::ObjectClassNotDefined("InvalidObjectClassHandle");
  }
  catch(RTI::InvalidOrderName)
	{
		throw RTI_V1_3::NameNotFound("InvalidOrderName");
  }
  catch(RTI::InvalidOrderType)
	{
		throw RTI_V1_3::InvalidOrderingHandle("InvalidOrderType");
  }
  catch(RTI::InvalidParameterHandle)
	{
		throw RTI_V1_3::RTIinternalError("InvalidParameterHandle");
  }
  catch(RTI::InvalidRangeBound)
	{
		throw RTI_V1_3::RTIinternalError("InvalidRangeBound");
  }
  catch(RTI::InvalidRegion)
	{
		throw RTI_V1_3::RegionNotKnown("InvalidRegion");
  }
  catch(RTI::InvalidRegionContext)
	{
		throw RTI_V1_3::InvalidRegionContext("");
  }
  catch(RTI::InvalidRetractionHandle)
	{
		throw RTI_V1_3::InvalidRetractionHandle("");
  }
  catch(RTI::InvalidServiceGroup)
	{
		throw RTI_V1_3::RTIinternalError("InvalidServiceGroup");
  }
  catch(RTI::InvalidTransportationName)
	{
		throw RTI_V1_3::NameNotFound("InvalidTransportationName");
  }
  catch(RTI::InvalidTransportationType)
	{
		throw RTI_V1_3::InvalidTransportationHandle("InvalidTransportationType");
  }
  catch(RTI::JoinedFederateIsNotInTimeAdvancingState)
	{
		throw RTI_V1_3::RTIinternalError("JoinedFederateIsNotInTimeAdvancingState");
  }
  catch(RTI::LogicalTimeAlreadyPassed)
	{
		throw RTI_V1_3::FederationTimeAlreadyPassed("LogicalTimeAlreadyPassed");
  }
  catch(RTI::MessageCanNoLongerBeRetracted)
	{
		throw RTI_V1_3::RTIinternalError("MessageCanNoLongerBeRetracted");
  }
  catch(RTI::NameNotFound)
	{
		throw RTI_V1_3::NameNotFound("");
  }
  catch(RTI::NoAcquisitionPending)
	{
		throw RTI_V1_3::RTIinternalError("NoAcquisitionPending");
  }
  catch(RTI::ObjectClassNotDefined)
	{
		throw RTI_V1_3::ObjectClassNotDefined("");
  }
  catch(RTI::ObjectClassNotKnown)
	{
		throw RTI_V1_3::ObjectClassNotKnown("");
  }
  catch(RTI::ObjectClassNotPublished)
	{
		throw RTI_V1_3::ObjectClassNotPublished("");
  }
  catch(RTI::ObjectClassRelevanceAdvisorySwitchIsOff)
	{
		throw RTI_V1_3::RTIinternalError("ObjectClassRelevanceAdvisorySwitchIsOff");
  }
  catch(RTI::ObjectClassRelevanceAdvisorySwitchIsOn)
	{
		throw RTI_V1_3::RTIinternalError("ObjectClassRelevanceAdvisorySwitchIsOn");
  }
  catch(RTI::ObjectInstanceNameInUse)
	{
		throw RTI_V1_3::ObjectAlreadyRegistered("ObjectInstanceNameInUse");
  }
  catch(RTI::ObjectInstanceNameNotReserved)
	{
		throw RTI_V1_3::RTIinternalError("ObjectInstanceNameNotReserved");
  }
  catch(RTI::ObjectInstanceNotKnown)
	{
		throw RTI_V1_3::ObjectNotKnown("ObjectInstanceNotKnown");
  }
  catch(RTI::OwnershipAcquisitionPending)
	{
		throw RTI_V1_3::OwnershipAcquisitionPending("");
	}
  catch(RTI::RTIinternalError)
	{
		throw RTI_V1_3::RTIinternalError("");
	}
  catch(RTI::RegionDoesNotContainSpecifiedDimension)
	{
		throw RTI_V1_3::RTIinternalError("RegionDoesNotContainSpecifiedDimension");
  }
  catch(RTI::RegionInUseForUpdateOrSubscription)
	{
		throw RTI_V1_3::RegionInUse("RegionInUseForUpdateOrSubscription");
  }
  catch(RTI::RegionNotCreatedByThisFederate)
	{
		throw RTI_V1_3::RegionNotKnown("RegionNotCreatedByThisFederate");
  }
  catch(RTI::RestoreInProgress)  
	{
		throw RTI_V1_3::RestoreInProgress("");
	}
  catch(RTI::RestoreNotRequested)
	{
		throw RTI_V1_3::RestoreNotRequested("");
	}
  catch(RTI::SaveInProgress)
	{
		throw RTI_V1_3::SaveInProgress("");
	}
  catch(RTI::SaveNotInitiated)
	{
		throw RTI_V1_3::SaveNotInitiated("");
	}
  catch(RTI::SpecifiedSaveLabelDoesNotExist)
	{
		throw RTI_V1_3::SpecifiedSaveLabelDoesNotExist("");
	}
  catch(RTI::SynchronizationPointLabelNotAnnounced)
	{
		throw RTI_V1_3::SynchronizationPointLabelWasNotAnnounced("SynchronizationPointLabelNotAnnounced");
	}
  catch(RTI::TimeConstrainedAlreadyEnabled)
	{
		throw RTI_V1_3::TimeConstrainedAlreadyEnabled("");
  }
  catch(RTI::TimeConstrainedIsNotEnabled)
	{
		throw RTI_V1_3::TimeConstrainedWasNotEnabled("TimeConstrainedIsNotEnabled");
  }
  catch(RTI::TimeRegulationAlreadyEnabled)
	{
		throw RTI_V1_3::TimeRegulationAlreadyEnabled("");
  }
  catch(RTI::TimeRegulationIsNotEnabled)
	{
		throw RTI_V1_3::TimeRegulationWasNotEnabled("TimeRegulationIsNotEnabled");
  }
  catch(RTI::UnableToPerformSave)
	{
		throw RTI_V1_3::UnableToPerformSave("");
  }
  catch(RTI::UnknownName)
	{
		throw RTI_V1_3::RTIinternalError("UnknownName");
  }
	catch(RTI::InternalError& e)
	{
wcout << e.what() << endl;
		throw RTI_V1_3::RTIinternalError(":Pitch internal error");
  }
	catch(RTI::exception& e)
	{
wcout << e.what() << endl;
		throw RTI_V1_3::RTIinternalError(":Undefined pitch RTI exception");
  }
	catch(...)
	{
		throw RTI_V1_3::RTIinternalError(":Undefined pitch exception");
  }
