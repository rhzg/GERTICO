/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Log: SchwarmAmbassador.cpp,v $
Revision 1.2  2007/02/28 09:17:18  mul
Changes to satisfy linker.

Revision 1.1  2003/05/16 09:45:39  hzg
initial


 
**
*******************************************************************************/



//-----------------------------------------------------------------
// Project Include Files
//-----------------------------------------------------------------
#include "SchwarmAmbassador.h"

//-----------------------------------------------------------------
// System Include Files
//-----------------------------------------------------------------
#ifndef _MSC_VER
#include <stdio.h>
#include <stdlib.h>
#else
#endif
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <fedtime.hh>



SchwarmAmbassador::SchwarmAmbassador()
{
   cerr << "FED_HW: SchwarmAmbassador::SchwarmAmbassador constructor called in FED" << endl;
}

SchwarmAmbassador::~SchwarmAmbassador()
throw(RTI::FederateInternalError)
{
   cerr << "FED_HW: SchwarmAmbassador::~SchwarmAmbassador destructor called in FED" << endl;
}

////////////////////////////////////
// Federation Management Services //
////////////////////////////////////

void SchwarmAmbassador::synchronizationPointRegistrationSucceeded (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
  synchronizationPointRegistrationSucceededFlag = true;
}

void SchwarmAmbassador::synchronizationPointRegistrationFailed (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: synchronizationPointRegistrationFailed not supported in FED"
        << endl;
}

void SchwarmAmbassador::announceSynchronizationPoint (
  const char *label, // supplied C4
  const char *tag)   // supplied C4
throw (
  RTI::FederateInternalError)
{
  announceSynchronizationPointFlag = true;
}

void SchwarmAmbassador::federationSynchronized (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
   federationSynchronizedFlag = true;
}


void SchwarmAmbassador::initiateFederateSave (
  const char *label) // supplied C4
throw (
  RTI::UnableToPerformSave,
  RTI::FederateInternalError)
{
   initiateSaveFlag = true;
   saveLabel = strdup (label);
}


void SchwarmAmbassador::federationSaved ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationSaved not supported in FED" << endl;
}


void SchwarmAmbassador::federationNotSaved ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationNotSaved not supported in FED" << endl;
}


void SchwarmAmbassador::requestFederationRestoreSucceeded (
  const char *label) // supplied C4
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestFederationRestoreSucceeded not supported in FED" << endl;
}


void SchwarmAmbassador::requestFederationRestoreFailed (
  const char *label) // supplied C4
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestFederationRestoreFailed not supported in FED" << endl;
}


void SchwarmAmbassador::requestFederationRestoreFailed (
  const char *label,
  const char *reason) // supplied C4
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestFederationRestoreFailed not supported in FED" << endl;
}


void SchwarmAmbassador::federationRestoreBegun ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationRestoreBegun not supported in FED" << endl;
}


void SchwarmAmbassador::initiateFederateRestore (
  const char               *label,   // supplied C4
        RTI::FederateHandle handle)  // supplied C1
throw (
  RTI::SpecifiedSaveLabelDoesNotExist,
  RTI::CouldNotRestore,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: initiateFederateRestore not supported in FED" << endl;
}


void SchwarmAmbassador::federationRestored ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationRestored not supported in FED" << endl;
}


void SchwarmAmbassador::federationNotRestored ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationNotRestored not supported in FED" << endl;
}


/////////////////////////////////////
// Declaration Management Services //
/////////////////////////////////////

void SchwarmAmbassador::startRegistrationForObjectClass (
        RTI::ObjectClassHandle   theClass)      // supplied C1
throw (
  RTI::ObjectClassNotPublished,
  RTI::FederateInternalError)
{
   startRegistrationFlag = true;
   objectClassHandle = theClass;
}


void SchwarmAmbassador::stopRegistrationForObjectClass (
        RTI::ObjectClassHandle   theClass)      // supplied C1
throw (
  RTI::ObjectClassNotPublished,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: stopRegistrationForObjectClass not supported" << endl;
}


void SchwarmAmbassador::turnInteractionsOn (
  RTI::InteractionClassHandle theHandle) // supplied C1
throw (
  RTI::InteractionClassNotPublished,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: turnInteractionsOn not supported" << endl;
}

void SchwarmAmbassador::turnInteractionsOff (
  RTI::InteractionClassHandle theHandle) // supplied C1
throw (
  RTI::InteractionClassNotPublished,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: turnInteractionsOff not supported" << endl;
}

////////////////////////////////
// Object Management Services //
////////////////////////////////

void SchwarmAmbassador::discoverObjectInstance (
  RTI::ObjectHandle          theObject,      // supplied C1
  RTI::ObjectClassHandle     theObjectClass, // supplied C1
  const char *          theObjectName)  // supplied C4
throw (
  RTI::CouldNotDiscover,
  RTI::ObjectClassNotKnown,
  RTI::FederateInternalError)
{
cout << " SchwarmAmbassador::discoverObjectInstance (obj = " << theObject << ", class = " << theObjectClass << ")" << endl;
   waiting = false;
   discoverObjectInstanceFlag = true;
   objectHandle = theObject;
   objectClassHandle = theObjectClass;
}

void SchwarmAmbassador::reflectAttributeValues (
        RTI::ObjectHandle                 theObject,     // supplied C1
  const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
  const RTI::FedTime&                     theTime,       // supplied C1
  const char                             *theTag,        // supplied C4
        RTI::EventRetractionHandle        theHandle)     // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateOwnsAttributes,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError)
{
//   cout << "SchwarmAmbassador::reflectAttributeValues (theObject=" 
//        << theObject << ", t=" << theTime << ")" << endl;
   for (RTI::ULong i=0; i < theAttributes.size(); i++)
   {
     cout << "attribute " << i << endl;
   }
   if (theObject != expectedObject)
   {
//     cerr << "FED_HW: reflectAttributeValues received unexpected update for " 
//          << theObject << ", with time" << theTime << " at time " << grantTime << endl;
   }
   if (theTime <= grantTime)
   {
//     cerr << "FED_HW: reflectAttributeValues received update for " 
//          << theObject << ", with time" << theTime << " at time " << grantTime << endl;
   }  
}

void SchwarmAmbassador::reflectAttributeValues (
        RTI::ObjectHandle                 theObject,     // supplied C1
  const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
  const char                             *theTag)        // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateOwnsAttributes,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: reflectAttributeValues not supported" << endl;
}

void SchwarmAmbassador::receiveInteraction (
        RTI::InteractionClassHandle       theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet& theParameters,  // supplied C4
  const RTI::FedTime&                     theTime,        // supplied C4
  const char                             *theTag,         // supplied C4
        RTI::EventRetractionHandle        theHandle)      // supplied C1
throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: receiveInteraction not supported" << endl;
}

void SchwarmAmbassador::receiveInteraction (
        RTI::InteractionClassHandle       theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet& theParameters,  // supplied C4
  const char                             *theTag)         // supplied C4
throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: receiveInteraction not supported" << endl;
}

void SchwarmAmbassador::removeObjectInstance (
        RTI::ObjectHandle          theObject, // supplied C1
  const RTI::FedTime&              theTime,   // supplied C4
  const char                      *theTag,    // supplied C4
        RTI::EventRetractionHandle theHandle) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: removeObjectInstance not supported" << endl;
}

void SchwarmAmbassador::removeObjectInstance (
        RTI::ObjectHandle          theObject, // supplied C1
  const char                      *theTag)    // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: removeObjectInstance not supported" << endl;
}

void SchwarmAmbassador::attributesInScope (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributesInScope not supported in FED" << endl;
}

void SchwarmAmbassador::attributesOutOfScope (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributesOutOfScope not supported in FED" << endl;
}

void SchwarmAmbassador::provideAttributeValueUpdate (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: provideAttributeValueUpdate not supported" << endl;
}

void SchwarmAmbassador::turnUpdatesOnForObjectInstance (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: turnUpdatesOnForObjectInstance not supported" << endl;
}

void SchwarmAmbassador::turnUpdatesOffForObjectInstance (
        RTI::ObjectHandle        theObject,      // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: turnUpdatesOffForObjectInstance not supported" << endl;
}

///////////////////////////////////
// Ownership Management Services //
///////////////////////////////////

void SchwarmAmbassador::requestAttributeOwnershipAssumption (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& offeredAttributes, // supplied C4
  const char                    *theTag)            // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeNotPublished,
  RTI::FederateInternalError)
{
   requestAttributeOwnershipAssumptionFlag = true;
   objectHandle = theObject;
   tag = strdup (theTag);
}

void SchwarmAmbassador::attributeOwnershipDivestitureNotification (
        RTI::ObjectHandle        theObject,          // supplied C1
  const RTI::AttributeHandleSet& releasedAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::AttributeDivestitureWasNotRequested,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeOwnershipDivestitureNotification not supported in FED"
        << endl;
}

void SchwarmAmbassador::attributeOwnershipAcquisitionNotification (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& securedAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAcquisitionWasNotRequested,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeNotPublished,
  RTI::FederateInternalError)
{
  attributeOwnershipAcquisitionNotificationFlag = true;
   cerr << "FED_HW: attributeOwnershipAcquisitionNotification not supported in FED"
        << endl;
}

void SchwarmAmbassador::attributeOwnershipUnavailable (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeAcquisitionWasNotRequested,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeOwnershipUnavailable not supported in FED" << endl;
}

void SchwarmAmbassador::requestAttributeOwnershipRelease (
        RTI::ObjectHandle        theObject,           // supplied C1
  const RTI::AttributeHandleSet& candidateAttributes, // supplied C4
  const char                    *theTag)              // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
   waiting = false;
   objectHandle = theObject;
}

void SchwarmAmbassador::confirmAttributeOwnershipAcquisitionCancellation (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeAcquisitionWasNotCanceled,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: confirmAttributeOwnershipAcquisitionCancellation not"
        << " supported in FED" << endl;
}

void SchwarmAmbassador::informAttributeOwnership (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute, // supplied C1
  RTI::FederateHandle  theOwner)     // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: informAttributeOwnership not supported in FED" << endl;
}

 void SchwarmAmbassador::attributeIsNotOwned (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeIsNotOwned not supported in FED" << endl;
}

void SchwarmAmbassador::attributeOwnedByRTI (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeOwnedByRTI not supported in FED" << endl;
}

//////////////////////////////
// Time Management Services //
//////////////////////////////

void SchwarmAmbassador::timeRegulationEnabled (
 const  RTI::FedTime& theFederateTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::EnableTimeRegulationWasNotPending,
  RTI::FederateInternalError)
{
//   cout << "FED_HW: Time granted (timeRegulationEnabled) to: "
//        << theFederateTime << endl;
   grantTime = theFederateTime;
   timeAdvGrant = RTI::RTI_TRUE;
   timeRegulationEnabledFlag = true;
}

void SchwarmAmbassador::timeConstrainedEnabled (
  const RTI::FedTime& theFederateTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::EnableTimeConstrainedWasNotPending,
  RTI::FederateInternalError)
{
//   cout << "FED_HW: Time granted (timeConstrainedEnabled) to: "
//        << theFederateTime << endl;
   grantTime = theFederateTime;
   timeAdvGrant = RTI::RTI_TRUE;
   enableTimeConstrainedFlag = true;
}

void SchwarmAmbassador::timeAdvanceGrant (
  const RTI::FedTime& theTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::TimeAdvanceWasNotInProgress,
  RTI::FederateInternalError)
{
//   cout << "FED_HW: Time granted (timeAdvanceGrant) to: "
//        << theTime << endl;
   grantTime = theTime;
   timeAdvGrant = RTI::RTI_TRUE;
}

void SchwarmAmbassador::requestRetraction (
  RTI::EventRetractionHandle theHandle) // supplied C1
throw (
  RTI::EventNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestRetraction not supported in FED" << endl;
}

