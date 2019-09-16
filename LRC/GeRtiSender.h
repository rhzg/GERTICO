/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**
** MODULE
** GeRtiSender - Sender interface for GERTICO
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: GeRtiSender.h,v $
Revision 1.15  2010/05/17 08:06:41  mul
Add logical time interval.

Revision 1.14  2009/05/27 11:35:56  mul
Minor change.

Revision 1.13  2008/10/20 09:35:24  mul
Remove unwanted services.

Revision 1.12  2008/01/30 13:34:19  mul
Changes for ieee1516.

Revision 1.11  2007/09/25 08:31:14  mul
Changes for ddm.

Revision 1.10  2007/09/06 06:34:34  mul
Changes for ieee1516.

Revision 1.9  2007/06/26 08:31:33  mul
Changes for ieee1516.

Revision 1.8  2007/06/08 12:13:01  mul
Changes for ieee1516.

Revision 1.7  2007/05/15 13:25:17  mul
Changes for combined 1.3 and 1516 logic.

Revision 1.6  2007/05/09 13:17:52  mul
Use generic time.

Revision 1.5  2007/03/12 13:22:51  mul
Changed string to wstring.

Revision 1.4  2007/03/06 09:30:18  mul
Changes for ieee conversion.

Revision 1.3  2006/10/23 14:47:16  mul
Changes to region logic.

Revision 1.2  2006/09/19 07:56:42  mul
Fix some program structure problems.

Revision 1.1  2006/08/01 11:38:47  mul
Changes for mom.

 
**
*******************************************************************************/


#ifndef GeRtiSender_HEADER
#define GeRtiSender_HEADER

#include "idl/GeRtiFactoryS.h"

#include "LRC/ReceiverLRC.h"

namespace GERTICO
{
  class GeRtiSender
  {
  public:
    virtual ~GeRtiSender() {};

    bool isJoined(void);
    // Mom services
    virtual bool checkReportServiceInvocation(void) = 0;
#ifdef IEEE_1516
    virtual void sendReportException(const GERTICO::MomException &theMomException) = 0;
#else
    virtual void sendReportAlert(GERTICO::MomAlert const &theMomAlert) = 0;
#endif
    virtual void sendReportServiceInvocation(GERTICO::MomReportServiceInvocation const &theMomReportServiceInvocation) = 0;

    // Hla services
    virtual void createFederationExecution(std::wstring const &theExecutionName, std::wstring const &theFED) = 0;

    virtual void destroyFederationExecution(std::wstring const &theExecutionName) = 0;

    virtual GeRtiFactory::GeRtiHandle joinFederationExecution(std::wstring const &theYourName, std::wstring const &theExecutionName, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory) = 0;

    virtual void resignFederationExecution
    (
      GeRtiFactory::ResignAction theAction
    )
    throw
    (
      GeRtiFactory::FederateOwnsAttributes,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::InvalidResignAction,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::RTIinternalError
    ) = 0;

    ////////////////////////////////////
    // Federation Management Services //
    ////////////////////////////////////

    // 4.6
    virtual void registerFederationSynchronizationPoint
    (       
      std::wstring const &label,
      GeRtiFactory::UserSuppliedTag const &theTag
    )
    throw
    (
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::ConcurrentAccessAttempted,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError
    ) = 0;

    virtual void registerFederationSynchronizationPoint
    (       
      std::wstring const &label,
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
    ) = 0;

	  // 4.9
	  virtual void synchronizationPointAchieved(      
	    std::wstring const &label)
	  throw
    (
	    GeRtiFactory::SynchronizationPointLabelWasNotAnnounced,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError
    ) = 0;

	  // 4.11
	  virtual void requestFederationSave(    
	    std::wstring const &theLabel,
	    GERTICO::GeRtiFedTime const &theTime)
	  throw
    (
	    GeRtiFactory::FederationTimeAlreadyPassed, 
	    GeRtiFactory::InvalidFederationTime,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError
    ) = 0;

	  virtual void requestFederationSave( 
	    std::wstring const &theLabel)
	  throw
    (
    	GeRtiFactory::FederateNotExecutionMember,
    	GeRtiFactory::ConcurrentAccessAttempted,
    	GeRtiFactory::SaveInProgress,
    	GeRtiFactory::RestoreInProgress,
    	GeRtiFactory::RTIinternalError
    ) = 0;

	  // 4.13
	  virtual void federateSaveBegun()
	  throw
    (
	    GeRtiFactory::SaveNotInitiated,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError
    ) = 0;

	  // 4.14
	  virtual void federateSaveComplete(CORBA::Boolean success)
	  throw
    (
	    GeRtiFactory::SaveNotInitiated,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError
    ) = 0;

    virtual void queryFederationSaveStatus ()
    throw
    (
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError
    ) = 0;

    // 4.16
	  virtual void requestFederationRestore(    
	    std::wstring const &label)
	  throw(
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError) = 0;

	  // 4.20
	  virtual void federateRestoreComplete(
                  CORBA::Boolean success)
	  throw(
    	GeRtiFactory::RestoreNotRequested,
    	GeRtiFactory::FederateNotExecutionMember,
    	GeRtiFactory::ConcurrentAccessAttempted,
    	GeRtiFactory::SaveInProgress,
    	GeRtiFactory::RTIinternalError) = 0;

    virtual void queryFederationRestoreStatus ()
    throw
    (
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RTIinternalError
    ) = 0;

	  /////////////////////////////////////
	  // Declaration Management Services //
	  /////////////////////////////////////

	  // 5.2
	  virtual void publishObjectClass(
      GeRtiFactory::GeRtiHandle theClass,
	    GeRtiFactory::Handles const &attributeList)
	  throw(
	    GeRtiFactory::ObjectClassNotDefined,
	    GeRtiFactory::AttributeNotDefined,
	    GeRtiFactory::OwnershipAcquisitionPending,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError) = 0;

  	// 5.3
	  virtual void unpublishObjectClass(
	    GeRtiFactory::GeRtiHandle theClass)
  	throw(
	    GeRtiFactory::ObjectClassNotDefined, 
	    GeRtiFactory::ObjectClassNotPublished,
  	  GeRtiFactory::OwnershipAcquisitionPending,
	    GeRtiFactory::FederateNotExecutionMember,
  	  GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError) = 0;

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
      GeRtiFactory::RTIinternalError) = 0;

	  // 5.4
	  virtual void publishInteractionClass(
	    GeRtiFactory::GeRtiHandle theInteraction)
	  throw(
	    GeRtiFactory::InteractionClassNotDefined,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError) = 0;

	  // 5.5
	  virtual void unpublishInteractionClass(
	    GeRtiFactory::GeRtiHandle theInteraction)
	  throw(
	    GeRtiFactory::InteractionClassNotDefined,
	    GeRtiFactory::InteractionClassNotPublished,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError) = 0;

	  // 5.6
	  virtual void subscribeObjectClassAttributes(
      GeRtiFactory::GeRtiHandle theClass,
	    GeRtiFactory::Handles const &attributeList,
      CORBA::Boolean active)
	  throw(
	    GeRtiFactory::ObjectClassNotDefined, 
	    GeRtiFactory::AttributeNotDefined,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError) = 0;

	  // 5.7
	  virtual void unsubscribeObjectClass(
	    GeRtiFactory::GeRtiHandle const &theClass)
	  throw(
	    GeRtiFactory::ObjectClassNotDefined,
	    GeRtiFactory::ObjectClassNotSubscribed,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError) = 0;

	  virtual void unsubscribeObjectClassAttributes(
	    GeRtiFactory::GeRtiHandle const &theClass,
      GeRtiFactory::Handles const &theAttributes)
	  throw(
	    GeRtiFactory::ObjectClassNotDefined,
	    GeRtiFactory::AttributeNotDefined,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError) = 0;

	  // 5.8
	  virtual void subscribeInteractionClass(
	    GeRtiFactory::GeRtiHandle theClass,
	    CORBA::Boolean active)
	  throw(
	    GeRtiFactory::InteractionClassNotDefined,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::FederateLoggingServiceCalls,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError) = 0;

	  // 5.9
	  virtual void unsubscribeInteractionClass(
	    GeRtiFactory::GeRtiHandle theClass)
	  throw(
	    GeRtiFactory::InteractionClassNotDefined,
	    GeRtiFactory::InteractionClassNotSubscribed,
	    GeRtiFactory::FederateNotExecutionMember,
	    GeRtiFactory::ConcurrentAccessAttempted,
	    GeRtiFactory::SaveInProgress,
	    GeRtiFactory::RestoreInProgress,
	    GeRtiFactory::RTIinternalError) = 0;

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
    GeRtiFactory::RTIinternalError) = 0;

	// 6.2
	virtual GeRtiFactory::GeRtiHandle
	registerObjectInstance(
    GeRtiFactory::GeRtiHandle theClass,
	  std::wstring const &theObject)
	throw(
	  GeRtiFactory::ObjectClassNotDefined,
	  GeRtiFactory::ObjectClassNotPublished,
	  GeRtiFactory::ObjectAlreadyRegistered,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	virtual GeRtiFactory::GeRtiHandle
	registerObjectInstance(
        	GeRtiFactory::GeRtiHandle theClass)
	throw(
	  GeRtiFactory::ObjectClassNotDefined,
	  GeRtiFactory::ObjectClassNotPublished,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 6.4
	virtual GeRtiFactory::ERHandle
	updateAttributeValues(
	  GeRtiFactory::GeRtiHandle const &theObject,
	  GeRtiFactory::HandleValues &theAttributes,
	  GERTICO::GeRtiFedTime const &theTime,
	  GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::AttributeNotOwned,
	  GeRtiFactory::InvalidFederationTime,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	virtual void updateAttributeValues(
	  GeRtiFactory::GeRtiHandle const &theObject,
	  GeRtiFactory::HandleValues &theAttributes,
	  GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::AttributeNotOwned,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 6.6
	virtual GeRtiFactory::ERHandle
	sendInteraction(
          GeRtiFactory::GeRtiHandle const &theInteraction,
	  GeRtiFactory::HandleValues const &theParameters,
	  GERTICO::GeRtiFedTime const &theTime,
	  GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::InteractionClassNotPublished,
	  GeRtiFactory::InteractionParameterNotDefined,
	  GeRtiFactory::InvalidFederationTime,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	virtual void sendInteraction(
    GeRtiFactory::GeRtiHandle const &theInteraction,
	  GeRtiFactory::HandleValues const &theParameters,
	  GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::InteractionClassNotPublished,
	  GeRtiFactory::InteractionParameterNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 6.8
	virtual GeRtiFactory::ERHandle
	deleteObjectInstance(
          GeRtiFactory::GeRtiHandle theObject,
	  GERTICO::GeRtiFedTime const &theTime,
	  GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::DeletePrivilegeNotHeld,
	  GeRtiFactory::InvalidFederationTime,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	virtual void deleteObjectInstance(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::DeletePrivilegeNotHeld,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 6.10
	virtual void localDeleteObjectInstance(
	  GeRtiFactory::GeRtiHandle    theObject)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::FederateOwnsAttributes,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 6.11
	virtual void changeAttributeTransportationType(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::Handles const &theAttributes,
    GeRtiFactory::GeRtiHandle theType)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::AttributeNotOwned,
	  GeRtiFactory::InvalidTransportationHandle,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 6.12
	virtual void changeInteractionTransportationType(
	  GeRtiFactory::GeRtiHandle theClass,
	  GeRtiFactory::GeRtiHandle   theType)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::InteractionClassNotPublished,
	  GeRtiFactory::InvalidTransportationHandle,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 6.15
	virtual void requestObjectAttributeValueUpdate(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::Handles const &theAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	virtual void requestClassAttributeValueUpdate(
    GeRtiFactory::GeRtiHandle theClass,
	  GeRtiFactory::Handles const &theAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::ObjectClassNotDefined, 
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	///////////////////////////////////
	// Ownership Management Services //
	///////////////////////////////////

	// 7.2
	virtual void unconditionalAttributeOwnershipDivestiture(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::Handles const &theAttributes)
	throw(
	  GeRtiFactory::ObjectNotKnown, 
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::AttributeNotOwned,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 7.3
	virtual void negotiatedAttributeOwnershipDivestiture(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::Handles const &theAttributes,
	  GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::AttributeNotOwned,
	  GeRtiFactory::AttributeAlreadyBeingDivested,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 7.7
	virtual void attributeOwnershipAcquisition(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::Handles const &desiredAttributes,
	  GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::ObjectClassNotPublished,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::AttributeNotPublished,
	  GeRtiFactory::FederateOwnsAttributes,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 7.8
	virtual void attributeOwnershipAcquisitionIfAvailable(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::Handles const &desiredAttributes)
	throw(
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
	  GeRtiFactory::RTIinternalError) = 0;

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
      GeRtiFactory::RTIinternalError) = 0;

	// 7.11
	virtual GeRtiFactory::Handles*
	confirmDivestiture(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::Handles const &theAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::AttributeNotOwned,
	  GeRtiFactory::FederateWasNotAskedToReleaseAttribute,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 7.12
	virtual void cancelNegotiatedAttributeOwnershipDivestiture(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::Handles const &theAttributes)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::AttributeNotOwned,
	  GeRtiFactory::AttributeDivestitureWasNotRequested,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 7.13
	virtual void cancelAttributeOwnershipAcquisition(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::Handles const &theAttributes)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::AttributeAlreadyOwned,
	  GeRtiFactory::AttributeAcquisitionWasNotRequested,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 7.15
	virtual void queryAttributeOwnership(
	  GeRtiFactory::GeRtiHandle    theObject,
	  GeRtiFactory::GeRtiHandle theAttribute)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 7.17
	virtual CORBA::Boolean
	isAttributeOwnedByFederate(
	  GeRtiFactory::GeRtiHandle    theObject,
	  GeRtiFactory::GeRtiHandle theAttribute)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	//////////////////////////////
	// Time Management Services //
	//////////////////////////////

	// 8.2
	virtual void enableTimeRegulation(
#ifndef IEEE_1516
	  GERTICO::GeRtiFedTime const &theFederateTime,
#endif
	  GERTICO::GeRtiLogicalTimeInterval const &theLookahead)
	throw(
	  GeRtiFactory::TimeRegulationAlreadyEnabled,
	  GeRtiFactory::EnableTimeRegulationPending,
	  GeRtiFactory::TimeAdvanceAlreadyInProgress,
	  GeRtiFactory::InvalidFederationTime,
	  GeRtiFactory::InvalidLookahead,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.4
	virtual void disableTimeRegulation()
	throw(
	  GeRtiFactory::TimeRegulationWasNotEnabled,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.5
	virtual void enableTimeConstrained()
	throw(
	  GeRtiFactory::TimeConstrainedAlreadyEnabled,
	  GeRtiFactory::EnableTimeConstrainedPending,
	  GeRtiFactory::TimeAdvanceAlreadyInProgress,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.7
	virtual void disableTimeConstrained()
	throw(
	  GeRtiFactory::TimeConstrainedWasNotEnabled,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.8
	virtual void timeAdvanceRequest(
	 GERTICO::GeRtiFedTime const &theTime)
	throw(
	  GeRtiFactory::InvalidFederationTime,
	  GeRtiFactory::FederationTimeAlreadyPassed,
	  GeRtiFactory::TimeAdvanceAlreadyInProgress,
	  GeRtiFactory::EnableTimeRegulationPending,
	  GeRtiFactory::EnableTimeConstrainedPending,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.9
	virtual void timeAdvanceRequestAvailable(
	GERTICO::GeRtiFedTime const &theTime)
	  throw(
    	GeRtiFactory::InvalidFederationTime,
    	GeRtiFactory::FederationTimeAlreadyPassed,
    	GeRtiFactory::TimeAdvanceAlreadyInProgress,
    	GeRtiFactory::EnableTimeRegulationPending,
    	GeRtiFactory::EnableTimeConstrainedPending,
    	GeRtiFactory::FederateNotExecutionMember,
    	GeRtiFactory::ConcurrentAccessAttempted,
    	GeRtiFactory::SaveInProgress,
    	GeRtiFactory::RestoreInProgress,
    	GeRtiFactory::RTIinternalError) = 0;

	// 8.10
	virtual void nextEventRequest(
	  GERTICO::GeRtiFedTime const &theTime)
	throw(
	  GeRtiFactory::InvalidFederationTime,
	  GeRtiFactory::FederationTimeAlreadyPassed,
	  GeRtiFactory::TimeAdvanceAlreadyInProgress,
	  GeRtiFactory::EnableTimeRegulationPending,
	  GeRtiFactory::EnableTimeConstrainedPending,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.11
	virtual void nextEventRequestAvailable(
	  GERTICO::GeRtiFedTime const &theTime)
	throw(
	  GeRtiFactory::InvalidFederationTime,
	  GeRtiFactory::FederationTimeAlreadyPassed,
	  GeRtiFactory::TimeAdvanceAlreadyInProgress,
	  GeRtiFactory::EnableTimeRegulationPending,
	  GeRtiFactory::EnableTimeConstrainedPending,  
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.12
	virtual void flushQueueRequest(
	  GERTICO::GeRtiFedTime const &theTime)
	throw(
	  GeRtiFactory::InvalidFederationTime,
	  GeRtiFactory::FederationTimeAlreadyPassed,
	  GeRtiFactory::TimeAdvanceAlreadyInProgress,
	  GeRtiFactory::EnableTimeRegulationPending,
	  GeRtiFactory::EnableTimeConstrainedPending,  
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.14
	virtual void enableAsynchronousDelivery()
	  throw(
    	GeRtiFactory::AsynchronousDeliveryAlreadyEnabled,
    	GeRtiFactory::FederateNotExecutionMember,
    	GeRtiFactory::ConcurrentAccessAttempted,
    	GeRtiFactory::SaveInProgress,
    	GeRtiFactory::RestoreInProgress,
    	GeRtiFactory::RTIinternalError) = 0;

	// 8.15
	virtual void disableAsynchronousDelivery()
	  throw(
    	GeRtiFactory::AsynchronousDeliveryAlreadyDisabled,
    	GeRtiFactory::FederateNotExecutionMember,
    	GeRtiFactory::ConcurrentAccessAttempted,
    	GeRtiFactory::SaveInProgress,
    	GeRtiFactory::RestoreInProgress,
    	GeRtiFactory::RTIinternalError) = 0;

	// 8.16
	virtual void queryLBTS(
	  GERTICO::GeRtiFedTime& theTime)
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.17
	virtual void queryFederateTime(
	  GERTICO::GeRtiFedTime& theTime)
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.18
	virtual void queryMinNextEventTime(
	  GERTICO::GeRtiFedTime& theTime)
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.19
	virtual void modifyLookahead(
	  GERTICO::GeRtiLogicalTimeInterval const &theLookahead)
	throw(
	  GeRtiFactory::InvalidLookahead,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.20
	virtual void queryLookahead(
	   GERTICO::GeRtiLogicalTimeInterval& theTime)
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.21
	virtual void retract(
	  GeRtiFactory::ERHandle const &theERHandle)
	throw(
	  GeRtiFactory::InvalidRetractionHandle,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.23
	virtual void changeAttributeOrderType(
    GeRtiFactory::GeRtiHandle theObject,
	  GeRtiFactory::Handles const &theAttributes,
    GeRtiFactory::GeRtiHandle theType)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::AttributeNotOwned,
	  GeRtiFactory::InvalidOrderingHandle,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 8.24
	virtual void changeInteractionOrderType(
	  GeRtiFactory::GeRtiHandle theClass,
	  GeRtiFactory::GeRtiHandle         theType)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::InteractionClassNotPublished,
	  GeRtiFactory::InvalidOrderingHandle,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	//////////////////////////////////
	// Data Distribution Management //
	//////////////////////////////////

	// 9.2
	virtual GeRtiFactory::GeRtiHandle
	createRegion(
	  GeRtiFactory::GeRtiHandle const &theSpace,
	  CORBA::ULong const &numberOfExtents,
    GERTICO::HandleSet const &theDimensions)
	throw(
	  GeRtiFactory::SpaceNotDefined,
	  GeRtiFactory::InvalidExtents,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.3
	virtual void notifyAboutRegionModification(
	  GeRtiFactory::GeRtiHandle const &theRegion,
    GeRtiFactory::Extents &theExtents)
	throw(
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::InvalidExtents,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.4
	virtual void deleteRegion(
	  GeRtiFactory::GeRtiHandle const &theRegion)
	throw(
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::RegionInUse,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.5
	virtual GeRtiFactory::GeRtiHandle
	registerObjectInstanceWithRegion(
    GeRtiFactory::GeRtiHandle const &theClass,
    std::wstring const &theObject,
    GERTICO::HandleSetMap &theAttRegMap)
	throw(
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
	  GeRtiFactory::RTIinternalError) = 0;

	virtual GeRtiFactory::GeRtiHandle
	registerObjectInstanceWithRegion(
	  GeRtiFactory::GeRtiHandle const &theClass,
	  GERTICO::HandleSetMap &theAttRegMap)
	throw(
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
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.6
	virtual void associateRegionForUpdates(
        	GeRtiFactory::GeRtiHandle  theObject,
	  GERTICO::HandleSetMap &theAttRegMap)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::InvalidRegionContext,
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.7
	virtual void unassociateRegionForUpdates(
	  GeRtiFactory::GeRtiHandle       &theRegion,
	  GeRtiFactory::GeRtiHandle  theObject)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::InvalidRegionContext,
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	virtual void unassociateRegionsForUpdates(
	  GeRtiFactory::GeRtiHandle  theObject,
	  GERTICO::HandleSetMap &theAttRegMap)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::InvalidRegionContext,
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.8
	virtual void subscribeObjectClassAttributesWithRegion(
    GeRtiFactory::GeRtiHandle theClass,
    GERTICO::HandleSetMap &theAttRegMap,
    bool const &active)
	throw(
	  GeRtiFactory::ObjectClassNotDefined,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::InvalidRegionContext,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.9
	virtual void unsubscribeObjectClassWithRegion(
	  GeRtiFactory::GeRtiHandle theClass,
	  GeRtiFactory::GeRtiHandle &theRegion)
	throw(
	  GeRtiFactory::ObjectClassNotDefined,
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::ObjectClassNotSubscribed,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	virtual void unsubscribeObjectClassWithRegions(
	  GeRtiFactory::GeRtiHandle theClass,
	  GERTICO::HandleSetMap &theAttRegMap)
	throw(
	  GeRtiFactory::ObjectClassNotDefined,
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::ObjectClassNotSubscribed,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.10
	virtual void subscribeInteractionClassWithRegion(
	  GeRtiFactory::GeRtiHandle theClass,
	  GERTICO::HandleSet &theRegions,
	  bool const &active)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::InvalidRegionContext,
	  GeRtiFactory::FederateLoggingServiceCalls,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.11
	virtual void unsubscribeInteractionClassWithRegion(
	  GeRtiFactory::GeRtiHandle theClass,
	  GERTICO::HandleSet &theRegion)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::InteractionClassNotSubscribed,
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.12
	virtual GeRtiFactory::ERHandle
	sendInteractionWithRegion(
          GeRtiFactory::GeRtiHandle const &theInteraction,
	  GeRtiFactory::HandleValues const &theParameters,
	  GERTICO::GeRtiFedTime const &theTime,
	  GeRtiFactory::UserSuppliedTag const &theTag,
	  GERTICO::HandleSet const &theRegions)
	throw(
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
	  GeRtiFactory::RTIinternalError) = 0;

	virtual void sendInteractionWithRegion(
          GeRtiFactory::GeRtiHandle const &theInteraction,
	  GeRtiFactory::HandleValues const &theParameters,
	  GeRtiFactory::UserSuppliedTag const &theTag,
	  GERTICO::HandleSet const &theRegions)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::InteractionClassNotPublished,
	  GeRtiFactory::InteractionParameterNotDefined,
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::InvalidRegionContext,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 9.13
	virtual void requestClassAttributeValueUpdateWithRegion(
    GeRtiFactory::GeRtiHandle theClass,
	  GERTICO::HandleSetMap &theAttRegMap,
    GeRtiFactory::UserSuppliedTag const &theTag)
	throw(
	  GeRtiFactory::ObjectClassNotDefined, 
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::RegionNotKnown,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	//////////////////////////
	// RTI Support Services //
	//////////////////////////

	// 10.2
	virtual GeRtiFactory::GeRtiHandle
	getObjectClassHandle(
	  std::wstring const &theName)
	throw(
	  GeRtiFactory::NameNotFound,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.3
	virtual std::wstring
	getObjectClassName(
	  GeRtiFactory::GeRtiHandle const &theHandle)
	throw(
	  GeRtiFactory::ObjectClassNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.4
	virtual GeRtiFactory::GeRtiHandle
	getAttributeHandle(
	  std::wstring const &theName,
    GeRtiFactory::GeRtiHandle const &whichClass)
	throw(
	  GeRtiFactory::ObjectClassNotDefined,
	  GeRtiFactory::NameNotFound,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.5
  virtual std::wstring
	getAttributeName(
	  GeRtiFactory::GeRtiHandle const &theHandle,
	  GeRtiFactory::GeRtiHandle const &whichClass)
	throw(
	  GeRtiFactory::ObjectClassNotDefined,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.6
	virtual GeRtiFactory::GeRtiHandle
	getInteractionClassHandle(
	  std::wstring const &theName)
	throw(
	  GeRtiFactory::NameNotFound,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.7
	virtual std::wstring
	getInteractionClassName(
	  GeRtiFactory::GeRtiHandle const &theHandle)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.8
	virtual GeRtiFactory::GeRtiHandle
	getParameterHandle(
	  std::wstring const &theName,
    GeRtiFactory::GeRtiHandle const &whichClass)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::NameNotFound,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.9
	virtual std::wstring
	getParameterName(
	  GeRtiFactory::GeRtiHandle const &theHandle,
	  GeRtiFactory::GeRtiHandle const &whichClass)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::InteractionParameterNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.10
	virtual GeRtiFactory::GeRtiHandle
	getObjectInstanceHandle(
	  std::wstring const &theName)
	throw(
    	GeRtiFactory::ObjectNotKnown,
    	GeRtiFactory::FederateNotExecutionMember,
    	GeRtiFactory::ConcurrentAccessAttempted,
    	GeRtiFactory::RTIinternalError) = 0;

	// 10.11
	virtual std::wstring
	getObjectInstanceName(
	  GeRtiFactory::GeRtiHandle const &theHandle)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.12
	virtual GeRtiFactory::GeRtiHandle
	getRoutingSpaceHandle(
	  std::wstring const &theName)
	throw(
	  GeRtiFactory::NameNotFound,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.13
	virtual std::wstring
	getRoutingSpaceName(
	   //
	   // This const was removed for the RTI 1.3 NG to work around a limitation of
	   // the Sun 4.2 C++ compiler regarding template instantiation.  The const
	   // is unnecessary.
	   //
	   /* const */ GeRtiFactory::GeRtiHandle theHandle)
	throw(
	  GeRtiFactory::SpaceNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.14
	virtual GeRtiFactory::GeRtiHandle
	getDimensionHandle(
	  std::wstring const &theName,
    GeRtiFactory::GeRtiHandle const &whichSpace)
	throw(
	  GeRtiFactory::SpaceNotDefined,
	  GeRtiFactory::NameNotFound,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.15
	virtual std::wstring
	getDimensionName(
	  GeRtiFactory::GeRtiHandle theHandle,
	  GeRtiFactory::GeRtiHandle     whichSpace)
	throw(
	  GeRtiFactory::SpaceNotDefined,
	  GeRtiFactory::DimensionNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

  virtual GeRtiFactory::GeRtiHandle getDimensionUpperBound(
    GeRtiFactory::GeRtiHandle const &theHandle)
  throw(
    GeRtiFactory::DimensionNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError) = 0;

  virtual void getAvailableDimensionsForClassAttribute(
    GeRtiFactory::GeRtiHandle const & theClass,
    GeRtiFactory::GeRtiHandle const & theHandle,
    GeRtiFactory::Handles &theDimensions)   
  throw(
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError) = 0;

  virtual void getAvailableDimensionsForInteractionClass(
    GeRtiFactory::GeRtiHandle const &theClass,
    GeRtiFactory::Handles &theDimensions
  )
  throw (
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  ) = 0;

  // 10.16
	virtual GeRtiFactory::GeRtiHandle
	getAttributeRoutingSpaceHandle(
	  GeRtiFactory::GeRtiHandle   theHandle,
	  GeRtiFactory::GeRtiHandle whichClass)
	throw(
	  GeRtiFactory::ObjectClassNotDefined,
	  GeRtiFactory::AttributeNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.17
	virtual GeRtiFactory::GeRtiHandle
	getObjectClass(
	  GeRtiFactory::GeRtiHandle theObject)
	throw(
	  GeRtiFactory::ObjectNotKnown,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.18
	virtual GeRtiFactory::GeRtiHandle
	getInteractionRoutingSpaceHandle(
	  GeRtiFactory::GeRtiHandle   theHandle)
	throw(
	  GeRtiFactory::InteractionClassNotDefined,
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::RTIinternalError) = 0;

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
    GeRtiFactory::RTIinternalError) = 0;

  virtual void getRangeBounds (
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
    GeRtiFactory::RTIinternalError) = 0;

  virtual void setRangeBounds (
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
    GeRtiFactory::RTIinternalError) = 0;

  // 10.23
	virtual void enableClassRelevanceAdvisorySwitch()
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.24
	virtual void disableClassRelevanceAdvisorySwitch()
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.25
	virtual void enableAttributeRelevanceAdvisorySwitch()
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.26
	virtual void disableAttributeRelevanceAdvisorySwitch()
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.27
	virtual void enableAttributeScopeAdvisorySwitch()
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.28
	virtual void disableAttributeScopeAdvisorySwitch()
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.29
	virtual void enableInteractionRelevanceAdvisorySwitch()
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 10.30
	virtual void disableInteractionRelevanceAdvisorySwitch()
	throw(
	  GeRtiFactory::FederateNotExecutionMember,
	  GeRtiFactory::ConcurrentAccessAttempted,
	  GeRtiFactory::SaveInProgress,
	  GeRtiFactory::RestoreInProgress,
	  GeRtiFactory::RTIinternalError) = 0;

	// 
	virtual CORBA::Boolean tick() = 0;

	virtual CORBA::Boolean
	tick(
	  double const &minimum,
	  double const &maximum) = 0;
};

}

#endif // GeRtiSender_HEADER
