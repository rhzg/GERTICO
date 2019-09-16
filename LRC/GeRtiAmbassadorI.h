/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GeRtiAmbassadorI.h
**
*******************************************************************************/

#ifndef GeRtiAmbassadorI_H_
#define GeRtiAmbassadorI_H_

#include "LRC/ReceiverLRC.h"
#include "LRC/MomLRC.h"

//Class GeRtiFactory_FederateAmbassador_i
namespace GERTICO
{
  class GeRtiFactory_FederateAmbassador_i : public virtual POA_GeRtiFactory::FederateAmbassador
  {
    PortableServer::POA_var myPOA;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::RegisteredObjectsHolder &registeredObjectsHolder;
    ReceiverLRC *receiverLRC;

  public:

    //Constructor
    GeRtiFactory_FederateAmbassador_i(PortableServer::POA_ptr thePOA, GERTICO::RegisteredObjectsHolder &theRegisteredObjectsHolder, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory);

    //Destructor
    virtual ~GeRtiFactory_FederateAmbassador_i (void);

    PortableServer::POA_ptr _default_POA (void);

    void setReceiver(GERTICO::ReceiverLRC *);

    ////////////////////////////////////
    // Utility Functions              //
    ////////////////////////////////////

    virtual void ping (
        void)
    throw (
      CORBA::SystemException
    );

    ////////////////////////////////////
    // Federation Management Services //
    ////////////////////////////////////
    virtual void confirmSynchronizationPointRegistration (
      const CORBA::WChar *label,
      CORBA::Boolean success,
      GeRtiFactory::SynchronizationPointFailureReason reason
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateInternalError
    );

    virtual void announceSynchronizationPoint (
      const CORBA::WChar *label,
      const GeRtiFactory::UserSuppliedTag & tag
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateInternalError
    );

    virtual void federationSynchronized (
      const CORBA::WChar *label
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateInternalError
    );

    virtual void initiateFederateSave (
        const CORBA::WChar *label
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::UnableToPerformSave,
      GeRtiFactory::FederateInternalError
    );

    virtual void initiateFederateSaveWithTime (
        const CORBA::WChar *label,
        const GeRtiFactory::Time & theTime
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::UnableToPerformSave,
        GeRtiFactory::InvalidFederationTime,
        GeRtiFactory::FederateInternalError
      );

    virtual void federationSaved (
      CORBA::Boolean success,
      GeRtiFactory::SaveFailureReason failureReason
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateInternalError
    );

    virtual void federationSaveStatusResponse (
      const GeRtiFactory::SaveStatusPairSeq & theFederateStatusVector
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateInternalError
    );

    virtual void confirmFederationRestorationRequest (
      const CORBA::WChar *label,
      CORBA::Boolean reason
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateInternalError
    );

    virtual void federationRestoreBegun (
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateInternalError
    );

    virtual void initiateFederateRestore (
      const CORBA::WChar *label,
      GeRtiFactory::GeRtiHandle handle
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::SpecifiedSaveLabelDoesNotExist,
      GeRtiFactory::CouldNotRestore,
      GeRtiFactory::FederateInternalError
    );

    virtual void federationRestored (
      CORBA::Boolean success,
      GeRtiFactory::RestoreFailureReason failureReason
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateInternalError
    );

    virtual void federationRestoreStatusResponse (
      const GeRtiFactory::RestoreStatusPairSeq & theFederateStatusVector
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateInternalError
    );

    ////////////////////////////////
    // Object Management Services //
    ////////////////////////////////
    virtual void objectInstanceNameReservationSucceeded (
      const CORBA::WChar * theObjectInstanceName
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::UnknownName,
      GeRtiFactory::FederateInternalError
    );

    virtual void objectInstanceNameReservationFailed (
      const CORBA::WChar * theObjectInstanceName
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::UnknownName,
      GeRtiFactory::FederateInternalError
    );

    virtual void announceObjectInstance (
      GeRtiFactory::GeRtiHandle theObject,
      GeRtiFactory::GeRtiHandle theObjectClass,
      const GeRtiFactory::Handles &theAttributes,
      const CORBA::WChar *theObjectName
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::CouldNotDiscover,
      GeRtiFactory::ObjectClassNotKnown,
      GeRtiFactory::FederateInternalError
    );

    virtual void discoverObjectInstance (
      GeRtiFactory::GeRtiHandle theObject,
      GeRtiFactory::GeRtiHandle theObjectClass,
      const CORBA::WChar *theObjectName
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::CouldNotDiscover,
      GeRtiFactory::ObjectClassNotKnown,
      GeRtiFactory::FederateInternalError
    );

    virtual void removeObjectInstance (
      GeRtiFactory::GeRtiHandle theObject,
      const GeRtiFactory::UserSuppliedTag & tag
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::ObjectNotKnown,
      GeRtiFactory::FederateInternalError
    );

    virtual void attributesInScope (
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & theAttributes
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::FederateInternalError
      );

    virtual void attributesOutOfScope (
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & theAttributes
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::FederateInternalError
      );

    virtual void removeObjectInstanceWithTime (
      GeRtiFactory::GeRtiHandle theObject,
      const GeRtiFactory::UserSuppliedTag & tag,
      const GeRtiFactory::Time &theTime,
      const GeRtiFactory::ERHandle &theERHandle
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::ObjectNotKnown,
      GeRtiFactory::FederateInternalError
    );

    virtual void provideAttributeValueUpdate (
      GeRtiFactory::GeRtiHandle theObject,
      const GeRtiFactory::Handles & theAttributes,
      const GeRtiFactory::UserSuppliedTag & theTag
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::ObjectNotKnown,
      GeRtiFactory::AttributeNotKnown,
      GeRtiFactory::AttributeNotOwned,
      GeRtiFactory::FederateInternalError
    );

    virtual void turnUpdatesOnForObjectInstance (
      GeRtiFactory::GeRtiHandle theObject,
      const GeRtiFactory::AttributeSubscribersSeq & theAttributeSubscribers
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::ObjectNotKnown,
      GeRtiFactory::AttributeNotOwned,
      GeRtiFactory::FederateInternalError
    );

    virtual void turnUpdatesOffForObjectInstance (
      GeRtiFactory::GeRtiHandle theObject,
      const GeRtiFactory::AttributeSubscribersSeq & theAttributeSubscribers
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::ObjectNotKnown,
      GeRtiFactory::AttributeNotOwned,
      GeRtiFactory::FederateInternalError
    );

    ////////////////////////////////
    // Object Management Services //
    ////////////////////////////////

    virtual void requestAttributeOwnershipAssumption (
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & offeredAttributes,
        const GeRtiFactory::UserSuppliedTag &theTag
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::AttributeAlreadyOwned,
        GeRtiFactory::AttributeNotPublished,
        GeRtiFactory::FederateInternalError
      );

    virtual void requestDivestitureConfirmation (
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & releasedAttributes
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::AttributeDivestitureWasNotRequested,
        GeRtiFactory::FederateInternalError
      );

    virtual void attributeOwnershipDivestitureNotification (
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & releasedAttributes
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::AttributeDivestitureWasNotRequested,
        GeRtiFactory::FederateInternalError
      );

    virtual void attributeOwnershipAcquisitionNotification (
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & securedAttributes,
        const GeRtiFactory::UserSuppliedTag & theTag
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::AttributeAcquisitionWasNotRequested,
        GeRtiFactory::AttributeAlreadyOwned,
        GeRtiFactory::AttributeNotPublished,
        GeRtiFactory::FederateInternalError
      );

    virtual void attributeOwnershipUnavailable (
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & theAttributes
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeAlreadyOwned,
        GeRtiFactory::AttributeAcquisitionWasNotRequested,
        GeRtiFactory::FederateInternalError
      );

    virtual void requestAttributeOwnershipRelease (
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & candidateAttributes,
        const GeRtiFactory::UserSuppliedTag &theTag
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::FederateInternalError
      );

    virtual void confirmAttributeOwnershipAcquisitionCancellation (
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & theAttributes
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeAlreadyOwned,
        GeRtiFactory::AttributeAcquisitionWasNotCanceled,
        GeRtiFactory::FederateInternalError
      );

    virtual void informAttributeOwnership (
        GeRtiFactory::GeRtiHandle theObject,
        GeRtiFactory::GeRtiHandle theAttribute,
        GeRtiFactory::GeRtiHandle theOwner
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::FederateInternalError
      );

    virtual void attributeIsNotOwned (
        GeRtiFactory::GeRtiHandle theObject,
        GeRtiFactory::GeRtiHandle theAttribute
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::FederateInternalError
      );

    virtual void attributeOwnedByRTI (
        GeRtiFactory::GeRtiHandle theObject,
        GeRtiFactory::GeRtiHandle theAttribute
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotKnown,
        GeRtiFactory::FederateInternalError
      );

    virtual void doMomRequest(
      GeRtiFactory::GeRtiHandle theRequest,
      const GeRtiFactory::HandleValues & data
    )
    throw(
      CORBA::SystemException
    );

    virtual void getMomData(
      GeRtiFactory::GeRtiHandle theRequest,
      const GeRtiFactory::Handles & theAttributes,
      GeRtiFactory::HandleValues_out data
    )
    throw(
      CORBA::SystemException
    );
  };
} // namespace

#endif /* GeRtiAmbassadorI_H_  */
