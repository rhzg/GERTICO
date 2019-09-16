/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** GeRtiAmbassadorI.h
**
*******************************************************************************/

#ifndef GERTIAMBASSADOR_H_
#define GERTIAMBASSADOR_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
//#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "idl/GeRtiFactoryS.h"
#include "Util/ClassDescr.h"
#include "Util/GeRtiOrb.h"
#include "FederationManagement.h"

class  GeRtiFactory_GeRtiAmbassador_i : public virtual POA_GeRtiFactory::GeRtiAmbassador
{
  GERTICO::FederationManagement &federationManagement;
  GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
  GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
  PortableServer::POA_var myPOA;
  GeRtiFactory::GeRtiHandle fedId;
  GeRtiFactory::GeRtiHandle privilegeToDeleteId;

  // Data at interaction level.
  void convertInteraction(GeRtiFactory::InteractionClassData_out &theInteractionData, GERTICO::AttributeDatum &theInteractionDatum);
  // Data at parameter level.
  void convertParameter(GeRtiFactory::ParametersClassData_out &theParameterData, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::LRCparameterFlagsMap &theLRCparameterFlagsMap);
  // Data at attribute level.
  void convert(GeRtiFactory::ItemsClassData_out &theAttributes, GERTICO::LRCattributeFlagsMap &theLRCattributeFlagsMap);

public:
  GeRtiFactory::GeRtiAmbassador_var GeRtiAmVar;

  //Constructor
  GeRtiFactory_GeRtiAmbassador_i(PortableServer::POA_ptr thePOA, GERTICO::FederationManagement &theFederationManagement, GERTICO::NextHandle &theIdHandler, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory);

  //Destructor
  virtual ~GeRtiFactory_GeRtiAmbassador_i (void);

  void deactivateObject(void);
  PortableServer::POA_ptr _default_POA (void);

  unsigned long getId ();

virtual void publishObjectClass (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::Handles & attributeList
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::OwnershipAcquisitionPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void unpublishObjectClass (
    GeRtiFactory::GeRtiHandle theClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::OwnershipAcquisitionPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void unpublishObjectClassAttributes (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::Handles & attributeList
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::OwnershipAcquisitionPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

virtual void subscribeObjectClassAttributes (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::Handles & attributeList,
    CORBA::Boolean active
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

virtual void unsubscribeObjectClass (
    GeRtiFactory::GeRtiHandle theClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotSubscribed,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

virtual void unsubscribeObjectClassAttributes (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::Handles & attributeList
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

virtual void reserveObjectInstanceName (
    const CORBA::WChar * theObjectInstanceName
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::IllegalName,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

virtual GeRtiFactory::GeRtiHandle registerObjectInstanceWithName (
    GeRtiFactory::GeRtiHandle theClass,
    const CORBA::WChar *theObjectName
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::ObjectAlreadyRegistered,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual GeRtiFactory::GeRtiHandle registerObjectInstance (
    GeRtiFactory::GeRtiHandle theClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void deleteObjectInstance (
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::UserSuppliedTag & theTag
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::DeletePrivilegeNotHeld,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void deleteObjectInstanceWithTime (
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Time &theTime,
    const GeRtiFactory::UserSuppliedTag & theTag,
    GeRtiFactory::GeRtiHandle theSerialNumber
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::DeletePrivilegeNotHeld,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void requestObjectAttributeValueUpdate (
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Handles & theAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void requestClassAttributeValueUpdate (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::Handles & theAttributes,
    const GeRtiFactory::UserSuppliedTag & theTag
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void localDeleteObjectInstance (
    GeRtiFactory::GeRtiHandle theObject
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::FederateOwnsAttributes,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void enableClassRelevanceAdvisorySwitch (
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void disableClassRelevanceAdvisorySwitch (

  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void enableAttributeScopeAdvisorySwitch (
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void disableAttributeScopeAdvisorySwitch (

  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void registerFederationSynchronizationPointWithDesignators (
    const CORBA::WChar *theLabel,
    const GeRtiFactory::UserSuppliedTag & theTag,
    const GeRtiFactory::Handles & designators
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void registerFederationSynchronizationPoint (
    const CORBA::WChar *theLabel,
    const GeRtiFactory::UserSuppliedTag & theTag
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void synchronizationPointAchieved (
    const CORBA::WChar *theLabel
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SynchronizationPointLabelWasNotAnnounced,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void requestFederationSaveWithTime (
    const CORBA::WChar *theLabel,
    const GeRtiFactory::Time &theTime
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederationTimeAlreadyPassed,
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void requestFederationSave (
    const CORBA::WChar *theLabel
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void federateSaveBegun (
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SaveNotInitiated,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void federateSaveComplete (
    CORBA::Boolean success,
    const char * saveData
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SaveNotInitiated,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void queryFederationSaveStatus (
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

virtual void requestFederationRestore (
    const CORBA::WChar *theLabel
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

    virtual void federateRestoreComplete (
        CORBA::Boolean
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::RestoreNotRequested,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual void queryFederationRestoreStatus (
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual void requestFederateSaveStart (
        const CORBA::WChar *theLabel,
        const GeRtiFactory::Time & theTime,
        CORBA::Boolean timeBoolean
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::StartNotAllowed,
        GeRtiFactory::ConcurrentAccessAttempted
      );

    //////////////////////////
    // Ownership Management //
    //////////////////////////
    virtual GeRtiFactory::GeRtiHandle getPrivilegeToDeleteId (
      )
      throw (
        CORBA::SystemException
      );

    virtual void unconditionalAttributeOwnershipDivestiture (
        GeRtiFactory::GeRtiHandle fedId,
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & theAttributes
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual void negotiatedAttributeOwnershipDivestiture (
        GeRtiFactory::GeRtiHandle fedId,
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & theAttributes,
        const GeRtiFactory::UserSuppliedTag &theTag
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::AttributeAlreadyBeingDivested,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual void attributeOwnershipAcquisition (
        GeRtiFactory::GeRtiHandle fedId,
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & desiredAttributes,
        const GeRtiFactory::UserSuppliedTag &theTag
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::ObjectClassNotPublished,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotPublished,
        GeRtiFactory::FederateOwnsAttributes,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual void attributeOwnershipAcquisitionIfAvailable (
        GeRtiFactory::GeRtiHandle fedId,
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & desiredAttributes
      )
      throw (
        CORBA::SystemException,
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
        GeRtiFactory::RTIinternalError
      );

    virtual ::GeRtiFactory::Handles * attributeOwnershipDivestitureIfWanted (
        GeRtiFactory::GeRtiHandle fedId,
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & theAttributes
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual ::GeRtiFactory::Handles * confirmDivestiture (
        GeRtiFactory::GeRtiHandle fedId,
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & theAttributes,
        const GeRtiFactory::UserSuppliedTag &theTag
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::FederateWasNotAskedToReleaseAttribute,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual void cancelNegotiatedAttributeOwnershipDivestiture (
        GeRtiFactory::GeRtiHandle fedId,
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & theAttributes
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::AttributeDivestitureWasNotRequested,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual void cancelAttributeOwnershipAcquisition (
        GeRtiFactory::GeRtiHandle fedId,
        GeRtiFactory::GeRtiHandle theObject,
        const GeRtiFactory::Handles & theAttributes
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeAlreadyOwned,
        GeRtiFactory::AttributeAcquisitionWasNotRequested,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual void queryAttributeOwnership (
        GeRtiFactory::GeRtiHandle fedId,
        GeRtiFactory::GeRtiHandle theObject,
        GeRtiFactory::GeRtiHandle theAttribute
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual CORBA::Boolean isAttributeOwnedByFederate (
        GeRtiFactory::GeRtiHandle fedId,
        GeRtiFactory::GeRtiHandle theObject,
        GeRtiFactory::GeRtiHandle theAttribute
      )
      throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

    virtual void processUnpublishOwnershipCandidate (
        GeRtiFactory::GeRtiHandle theFederate,
        GeRtiFactory::GeRtiHandle theClass,
        const GeRtiFactory::Handles & theAttributes
      )
      throw (
        GeRtiFactory::ObjectClassNotDefined,
		    GeRtiFactory::AttributeNotDefined,
		    GeRtiFactory::FederateNotExecutionMember,
		    GeRtiFactory::SaveInProgress,
		    GeRtiFactory::RestoreInProgress,
		    GeRtiFactory::RTIinternalError
      );

    /////////////////////////////////////
    // Declaration Management Services //
    /////////////////////////////////////
    virtual GeRtiFactory::GeRtiHandle createRegion (
      GeRtiFactory::GeRtiHandle theSpace,
      CORBA::ULong numberOfExtents,
      const GeRtiFactory::Handles & theDimensions
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::SpaceNotDefined,
      GeRtiFactory::InvalidExtents,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError,
      GeRtiFactory::ConcurrentAccessAttempted
    );

  virtual void modifyRegion (
      GeRtiFactory::GeRtiHandle theRegion,
      const GeRtiFactory::Extents & theExtents
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::RegionNotKnown,
      GeRtiFactory::InvalidExtents,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError,
      GeRtiFactory::ConcurrentAccessAttempted
    );

  virtual void deleteRegion (
      GeRtiFactory::GeRtiHandle theRegion
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::RegionNotKnown,
      GeRtiFactory::RegionInUse,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError,
      GeRtiFactory::ConcurrentAccessAttempted);

  virtual GeRtiFactory::GeRtiHandle registerObjectInstanceWithNameWithRegions (
      GeRtiFactory::GeRtiHandle theClass,
      const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions,
      const CORBA::WChar *theObjectName
    )
    throw (
      CORBA::SystemException,
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
      GeRtiFactory::RTIinternalError
    );

  virtual GeRtiFactory::GeRtiHandle registerObjectInstanceWithRegions (
      GeRtiFactory::GeRtiHandle theClass,
      const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions
    )
    throw (
      CORBA::SystemException,
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
      GeRtiFactory::RTIinternalError
    );

  virtual void associateRegionsForUpdates (
      GeRtiFactory::GeRtiHandle theObject,
      const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions
    )
    throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::InvalidRegionContext,
        GeRtiFactory::RegionNotKnown,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

  virtual void unassociateRegionForUpdates (
      GeRtiFactory::GeRtiHandle theRegion,
      GeRtiFactory::GeRtiHandle theObject
    )
    throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::InvalidRegionContext,
        GeRtiFactory::RegionNotKnown,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

  virtual void unassociateRegionsForUpdates (
      GeRtiFactory::GeRtiHandle theObject,
      const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions
    )
    throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::InvalidRegionContext,
        GeRtiFactory::RegionNotKnown,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
      );

virtual void subscribeObjectClassAttributesWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions,
    CORBA::Boolean active
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

virtual void unsubscribeObjectClassWithRegion (
    GeRtiFactory::GeRtiHandle theClass,
    GeRtiFactory::GeRtiHandle theRegion
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::ObjectClassNotSubscribed,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

virtual void unsubscribeObjectClassWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::ObjectClassNotSubscribed,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

virtual void subscribeInteractionClassWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    CORBA::Boolean active,
    const GeRtiFactory::Handles &theRegions
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::FederateLoggingServiceCalls,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void unsubscribeInteractionClassWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::Handles & theRegions
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotSubscribed,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

virtual void requestAttributeValueUpdateWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::AttributeRegionsSeq & theAttributeRegions,
    const GeRtiFactory::UserSuppliedTag & theTag
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual GeRtiFactory::GeRtiHandle getObjectClass (
    GeRtiFactory::GeRtiHandle theObject
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual GeRtiFactory::GeRtiHandle getAttributeHandle (
    const CORBA::WChar *theName,
    GeRtiFactory::GeRtiHandle whichClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  );

  virtual CORBA::WChar *getAttributeName (
    GeRtiFactory::GeRtiHandle handle,
    GeRtiFactory::GeRtiHandle whichClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual GeRtiFactory::GeRtiHandle getObjectInstanceHandle (
    const CORBA::WChar *theName
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual CORBA::WChar *getObjectInstanceName (
    GeRtiFactory::GeRtiHandle handle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual GeRtiFactory::GeRtiHandle getInteractionClassHandle (
    const CORBA::WChar *theName,
    GeRtiFactory::Handles_out parents,
    GeRtiFactory::InteractionClassData_out interactionData,
    GeRtiFactory::ParametersClassData_out parameters
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError
  );

  virtual CORBA::WChar *getInteractionClassName (
    GeRtiFactory::GeRtiHandle handle,
    GeRtiFactory::Handles_out parents,
    GeRtiFactory::InteractionClassData_out interactionData,
    GeRtiFactory::ParametersClassData_out parameters
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError
  );

  virtual GeRtiFactory::GeRtiHandle getObjectClassHandle (
    const CORBA::WChar *theName,
    GeRtiFactory::Handles_out parents,
    GeRtiFactory::ItemsClassData_out attributes
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError
  );

  virtual CORBA::WChar *getObjectClassName (
    GeRtiFactory::GeRtiHandle handle,
    GeRtiFactory::Handles_out parents,
    GeRtiFactory::ItemsClassData_out attributes
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual GeRtiFactory::GeRtiHandle getParameterHandle (
    const CORBA::WChar *theName,
    GeRtiFactory::GeRtiHandle whichClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  );

  virtual CORBA::WChar *getParameterName (
    GeRtiFactory::GeRtiHandle theHandle,
    GeRtiFactory::GeRtiHandle whichClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionParameterNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  );

  virtual GeRtiFactory::GeRtiHandle getRoutingSpaceHandle (
    const CORBA::WChar *theName
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual CORBA::WChar *getRoutingSpaceName (
    GeRtiFactory::GeRtiHandle theHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SpaceNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual GeRtiFactory::GeRtiHandle getDimensionHandle (
    const CORBA::WChar *theName,
    GeRtiFactory::GeRtiHandle whichSpace
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual CORBA::WChar *getDimensionName (
    GeRtiFactory::GeRtiHandle theHandle,
    GeRtiFactory::GeRtiHandle whichSpace
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SpaceNotDefined,
    GeRtiFactory::DimensionNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual GeRtiFactory::GeRtiHandle getDimensionUpperBound (
    GeRtiFactory::GeRtiHandle theHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::DimensionNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  );

  virtual ::GeRtiFactory::Handles * getAvailableDimensionsForClassAttribute (
    GeRtiFactory::GeRtiHandle theClass,
    GeRtiFactory::GeRtiHandle theHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  );

  virtual ::GeRtiFactory::Handles * getAvailableDimensionsForInteractionClass (
    GeRtiFactory::GeRtiHandle theClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  );

  virtual GeRtiFactory::GeRtiHandle getAttributeRoutingSpaceHandle (
    GeRtiFactory::GeRtiHandle theHandle,
    GeRtiFactory::GeRtiHandle whichClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual GeRtiFactory::GeRtiHandle getInteractionRoutingSpaceHandle (
    GeRtiFactory::GeRtiHandle theHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  );

  virtual ::GeRtiFactory::Handles * getDimensionHandleSet (
    GeRtiFactory::GeRtiHandle theRegionHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

  virtual ::GeRtiFactory::Handles * getRangeBounds (
    GeRtiFactory::GeRtiHandle theRegionHandle,
    GeRtiFactory::GeRtiHandle theDimensionHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::RegionDoesNotContainSpecifiedDimension,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  );

  virtual void setRangeBounds (
    GeRtiFactory::GeRtiHandle theRegionHandle,
    GeRtiFactory::GeRtiHandle theDimensionHandle,
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
    GeRtiFactory::RTIinternalError
  );
};

typedef std::map <GeRtiFactory::GeRtiHandle, GeRtiFactory_GeRtiAmbassador_i *> FederatesMap;

#endif /* GERTIAMBASSADOR_H_ */
