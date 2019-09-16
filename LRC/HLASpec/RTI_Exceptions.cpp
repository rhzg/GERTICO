/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_Exceptions.cpp,v $
Revision 1.4  2007/09/05 15:47:27  mul
Changes for ieee1516.

Revision 1.1.1.1  2003/07/23 13:12:13  mul
First version

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/

#ifndef IEEE_1516
#include "include/RTI_1.3/RTI.hh"

const char *RTI::ArrayIndexOutOfBounds::_ex = "ArrayIndexOutOfBounds";
const char *RTI::AsynchronousDeliveryAlreadyDisabled::_ex = "AsynchronousDeliveryAlreadyDisabled";
const char *RTI::AsynchronousDeliveryAlreadyEnabled::_ex = "AsynchronousDeliveryAlreadyEnabled";
const char *RTI::AttributeAcquisitionWasNotRequested::_ex = "AttributeAcquisitionWasNotRequested";
const char *RTI::AttributeAcquisitionWasNotCanceled::_ex = "AttributeAcquisitionWasNotCanceled";
const char *RTI::AttributeAlreadyBeingAcquired::_ex = "AttributeAlreadyBeingAcquired";
const char *RTI::AttributeAlreadyBeingDivested::_ex = "AttributeAlreadyBeingDivested";
const char *RTI::AttributeAlreadyOwned::_ex = "AttributeAlreadyOwned";
const char *RTI::AttributeDivestitureWasNotRequested::_ex = "AttributeDivestitureWasNotRequested";
const char *RTI::AttributeNotDefined::_ex = "AttributeNotDefined";
const char *RTI::AttributeNotKnown::_ex = "AttributeNotKnown";
const char *RTI::AttributeNotOwned::_ex = "AttributeNotOwned";
const char *RTI::AttributeNotPublished::_ex = "AttributeNotPublished";
const char *RTI::ConcurrentAccessAttempted::_ex = "ConcurrentAccessAttempted";
const char *RTI::CouldNotDiscover::_ex = "CouldNotDiscover";
const char *RTI::CouldNotOpenFED::_ex = "CouldNotOpenFED";
const char *RTI::CouldNotRestore::_ex = "CouldNotRestore";
const char *RTI::DeletePrivilegeNotHeld::_ex = "DeletePrivilegeNotHeld";
const char *RTI::DimensionNotDefined::_ex = "DimensionNotDefined";
const char *RTI::EnableTimeConstrainedPending::_ex = "EnableTimeConstrainedPending";
const char *RTI::EnableTimeConstrainedWasNotPending::_ex = "EnableTimeConstrainedWasNotPending";
const char *RTI::EnableTimeRegulationPending::_ex = "EnableTimeRegulationPending";
const char *RTI::EnableTimeRegulationWasNotPending::_ex = "EnableTimeRegulationWasNotPending";
const char *RTI::ErrorReadingFED::_ex = "ErrorReadingFED";
const char *RTI::EventNotKnown::_ex = "EventNotKnown";
const char *RTI::FederateAlreadyExecutionMember::_ex = "FederateAlreadyExecutionMember";
const char *RTI::FederateInternalError::_ex = "FederateInternalError";
const char *RTI::FederateLoggingServiceCalls::_ex = "FederateLoggingServiceCalls";
const char *RTI::FederateNotExecutionMember::_ex = "FederateNotExecutionMember";
const char *RTI::FederateOwnsAttributes::_ex = "FederateOwnsAttributes";
const char *RTI::FederateWasNotAskedToReleaseAttribute::_ex = "FederateWasNotAskedToReleaseAttribute";
const char *RTI::FederatesCurrentlyJoined::_ex = "FederatesCurrentlyJoined";
const char *RTI::FederationExecutionAlreadyExists::_ex = "FederationExecutionAlreadyExists";
const char *RTI::FederationExecutionDoesNotExist::_ex = "FederationExecutionDoesNotExist";
const char *RTI::FederationTimeAlreadyPassed::_ex = "FederationTimeAlreadyPassed";
const char *RTI::HandleValuePairMaximumExceeded::_ex = "HandleValuePairMaximumExceeded";
const char *RTI::InteractionClassNotDefined::_ex = "InteractionClassNotDefined";
const char *RTI::InteractionClassNotKnown::_ex = "InteractionClassNotKnown";
const char *RTI::InteractionClassNotPublished::_ex = "InteractionClassNotPublished";
const char *RTI::InteractionClassNotSubscribed::_ex = "InteractionClassNotSubscribed";
const char *RTI::InteractionParameterNotDefined::_ex = "InteractionParameterNotDefined";
const char *RTI::InteractionParameterNotKnown::_ex = "InteractionParameterNotKnown";
const char *RTI::InvalidExtents::_ex = "InvalidExtents";
const char *RTI::InvalidFederationTime::_ex = "InvalidFederationTime";
const char *RTI::InvalidHandleValuePairSetContext::_ex = "InvalidHandleValuePairSetContext";
const char *RTI::InvalidLookahead::_ex = "InvalidLookahead";
const char *RTI::InvalidOrderingHandle::_ex = "InvalidOrderingHandle";
const char *RTI::InvalidRegionContext::_ex = "InvalidRegionContext";
const char *RTI::InvalidResignAction::_ex = "InvalidResignAction";
const char *RTI::InvalidRetractionHandle::_ex = "InvalidRetractionHandle";
const char *RTI::InvalidTransportationHandle::_ex = "InvalidTransportationHandle";
const char *RTI::MemoryExhausted::_ex = "MemoryExhausted";
const char *RTI::NameNotFound::_ex = "NameNotFound";
const char *RTI::ObjectClassNotDefined::_ex = "ObjectClassNotDefined";
const char *RTI::ObjectClassNotKnown::_ex = "ObjectClassNotKnown";
const char *RTI::ObjectClassNotPublished::_ex = "ObjectClassNotPublished";
const char *RTI::ObjectClassNotSubscribed::_ex = "ObjectClassNotSubscribed";
const char *RTI::ObjectNotKnown::_ex = "ObjectNotKnown";
const char *RTI::ObjectAlreadyRegistered::_ex = "ObjectAlreadyRegistered";
const char *RTI::OwnershipAcquisitionPending::_ex = "OwnershipAcquisitionPending";
const char *RTI::RegionInUse::_ex = "RegionInUse";
const char *RTI::RegionNotKnown::_ex = "RegionNotKnown";
const char *RTI::RestoreInProgress::_ex = "RestoreInProgress";
const char *RTI::RestoreNotRequested::_ex = "RestoreNotRequested";
const char *RTI::RTIinternalError::_ex = "RTIinternalError";
const char *RTI::SpaceNotDefined::_ex = "SpaceNotDefined";
const char *RTI::SaveInProgress::_ex = "SaveInProgress";
const char *RTI::SaveNotInitiated::_ex = "SaveNotInitiated";
const char *RTI::SpecifiedSaveLabelDoesNotExist::_ex = "SpecifiedSaveLabelDoesNotExist";
const char *RTI::SynchronizationPointLabelWasNotAnnounced::_ex = "SynchronizationPointLabelWasNotAnnounced";
const char *RTI::TimeAdvanceAlreadyInProgress::_ex = "TimeAdvanceAlreadyInProgress";
const char *RTI::TimeAdvanceWasNotInProgress::_ex = "TimeAdvanceWasNotInProgress";
const char *RTI::TimeConstrainedAlreadyEnabled::_ex = "TimeConstrainedAlreadyEnabled";
const char *RTI::TimeConstrainedWasNotEnabled::_ex = "TimeConstrainedWasNotEnabled";
const char *RTI::TimeRegulationAlreadyEnabled::_ex = "TimeRegulationAlreadyEnabled";
const char *RTI::TimeRegulationWasNotEnabled::_ex = "TimeRegulationWasNotEnabled";
const char *RTI::UnableToPerformSave::_ex = "UnableToPerformSave";
const char *RTI::ValueCountExceeded::_ex = "ValueCountExceeded";
const char *RTI::ValueLengthExceeded::_ex = "ValueLengthExceeded";
#endif
