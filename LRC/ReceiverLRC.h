/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: ReceiverLRC.h,v $
Revision 1.14  2010/05/17 08:05:08  mul
Add logical time interval.

Revision 1.13  2010/03/22 13:04:53  mul
Changes for single callbacks.

Revision 1.12  2010/03/16 15:30:04  mul
Minor change.

Revision 1.11  2010/03/05 13:16:45  mul
Changes for single evoke call.

Revision 1.10  2010/02/25 07:40:10  mul
Changes for single callbacks.

Revision 1.9  2009/09/03 07:12:04  mul
Add intermediate time advance grant.

Revision 1.8  2009/05/27 13:26:09  mul
Changes to fix problems in level four test cases.

Revision 1.7  2009/05/07 12:33:54  mul
Changes for removing token logic in time management.

Revision 1.6  2009/02/16 15:09:03  mul
Changes for adding ownership.

Revision 1.5  2008/08/07 09:33:51  mul
Changes in event channel.

Revision 1.4  2007/09/06 06:40:25  mul
Changes for ieee1516.

Revision 1.3  2007/06/26 08:28:40  mul
Changes for ieee1516.

Revision 1.2  2007/06/08 12:09:51  mul
Changes for ieee1516.

Revision 1.1  2007/05/15 13:33:42  mul
Changes for combined 1.3 and 1516 logic.


**
*******************************************************************************/


#ifndef ReceiverLRC_HEADER
#define ReceiverLRC_HEADER

#include <map>
#include <string>
#include <vector>

#include "LRC/FederateDB.h"
#include "LRC/MomLRC.h"
#include "LRC/LrcOwnershipClient.h"
#ifdef IEEE_1516
#include "LRC/HLA1516/EventHandler.h"
#else
#include "LRC/HLASpec/EventHandler.h"
#endif

namespace GERTICO
{
  class ReceiverLRC
  {
  public:
    GERTICO::FederateDB *federateDB;
    GERTICO::JobHolder restoreJobs;
    LrcOwnershipClient ownClient;
#ifdef IEEE_1516
    GERTICO::EventHandler1516 *eventHandler;
#else
    GERTICO::EventHandler *eventHandler;
#endif

    virtual ~ReceiverLRC(void) {};

    virtual void addAnnounceSynchronizationPoint(std::wstring const &theLabel, GeRtiFactory::UserSuppliedTag const &theTag) = 0;
    virtual void addAttributesInScope(GeRtiFactory::GeRtiHandle &,GeRtiFactory::Handles const &) = 0;
    virtual void addAttributeIsNotOwned(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute) = 0;
    virtual void addAttributeOwnedByRTI(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute) = 0;
    virtual void addAttributesOutOfScope(GeRtiFactory::GeRtiHandle &,GeRtiFactory::Handles const &) = 0;
    virtual void addAttributeOwnershipDivestitureNotification(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &releasedAttributes) = 0;
    virtual void addAttributeOwnershipUnavailable(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes) = 0;
    virtual void addConfirmFederationRestorationRequest(std::wstring const &theLabel, bool const &theSuccess) = 0;
    virtual void addConfirmSynchronizationPointRegistration(std::wstring const &theLabel, bool const &theSuccess, GeRtiFactory::SynchronizationPointFailureReason const &theReason) = 0;
    virtual void addConfirmAttributeOwnershipAcquisitionCancellation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes) = 0;
    virtual void addDiscover(std::wstring const &theObjectName, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theObjectClass) = 0;
    virtual void addEventHolder(GeRtiFactory::GertiPushEvent const &theGertiPushEvent) = 0;
    virtual void addFederationRestoreBegun(void) = 0;
    virtual void addFederationRestoreStatusResponse(GeRtiFactory::RestoreStatusPairSeq const &theFederateStatusVector) = 0;
    virtual void addFederationRestored(bool const &, GeRtiFactory::RestoreFailureReason const &theFailureReason) = 0;
    virtual void addFederationSaveStatusResponse(GeRtiFactory::SaveStatusPairSeq const &theFederateStatusVector) = 0;
    virtual void addFederationSaved(bool const &theSuccess, GeRtiFactory::SaveFailureReason const &failureReason) = 0;
    virtual void addFederationSynchronized(std::wstring const &theLabel) = 0;
    virtual void addInformAttributeOwnership(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute, GeRtiFactory::GeRtiHandle const &theOwner) = 0;
    virtual void addInterPubOff(GeRtiFactory::GeRtiHandle const &theInteraction) = 0;
    virtual void addInterPubOn(GeRtiFactory::GeRtiHandle const &theInteraction) = 0;
    virtual void addInitiateFederateRestore(std::wstring const &theLabel, GeRtiFactory::GeRtiHandle const &theFederate) = 0;
    virtual void addInitiateFederateSave(std::wstring const &theLabel) = 0;
    virtual void addInitiateFederateSaveWithTime(std::wstring const &theLabel, GERTICO::GeRtiFedTime const &theTime) = 0;
    virtual void addObjectInstanceNameReservationFailed(std::wstring const &theObjectInstanceName) = 0;
    virtual void addObjectInstanceNameReservationSucceeded(std::wstring const &theObjectInstanceName) = 0;
    virtual void addObjPubOff(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers) = 0;
    virtual void addObjPubOn(GeRtiFactory::GeRtiHandle const &, GERTICO::HandleSetMap const &theAttributeSubscribers) = 0;
    virtual void addAttributeOwnershipAcquisitionNotification(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &securedAttributes, GeRtiFactory::UserSuppliedTag const &theTag) = 0;
    virtual void addProvideAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag) = 0;
    virtual void addRemove(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::UserSuppliedTag const &) = 0;
    virtual void addRemoveWithTime(GeRtiFactory::GeRtiHandle const &, GeRtiFactory::UserSuppliedTag const &, std::auto_ptr<GERTICO::GeRtiFedTime> &, GeRtiFactory::ERHandle const &) = 0;
    virtual void addRequestAttributeOwnershipAssumption(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &offeredAttributes, GeRtiFactory::UserSuppliedTag const &theTag) = 0;
    virtual void addRequestAttributeOwnershipRelease(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &candidateAttributes, GeRtiFactory::UserSuppliedTag const &theTag) = 0;
    virtual void addRequestDivestitureConfirmation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &releasedAttributes) = 0;
    virtual void addRequestRetraction(GeRtiFactory::ERHandle const & theHandle) = 0;
    virtual void addRetractionHandle(GeRtiFactory::ERHandle const &theERHandle, GERTICO::GeRtiFedTime const &theFedTime) = 0;
    virtual void addStartRegistrationForObjectClass(GeRtiFactory::GeRtiHandle const &) = 0;
    virtual void addStopRegistrationForObjectClass(GeRtiFactory::GeRtiHandle const &) = 0;
    virtual void addTimeAdvanceGrant(GERTICO::GeRtiFedTime &theTime) = 0;
    virtual void addTimeAdvanceGrantGalt(GERTICO::GeRtiFedTime const &theTime, GERTICO::GeRtiFedTime const &theGaltTime) = 0;
    virtual void addTimeAdvanceGrantIntermediate(GERTICO::GeRtiFedTime const &theTime) = 0;
    virtual void addTimeConstrainedEnabled(GERTICO::GeRtiFedTime const &) = 0;
    virtual void addTimeRegulationEnabled(GERTICO::GeRtiFedTime const &) = 0;
    virtual bool getAsynchronousDelivery(void) = 0;
    virtual void getFederateState(GERTICO::FederateState &theFederateState) = 0;
    virtual bool getRestoreInProgress(void) = 0;
    virtual bool getSaveInProgress(void) = 0;
    virtual void queryMinNextEventTime(GERTICO::GeRtiFedTime &theTime) = 0;

    // For Mom.
    virtual void doMomRequest(GeRtiFactory::GeRtiHandle theRequest, GeRtiFactory::HandleValues const & data) = 0;
    virtual long getInteractionsReceived(void) = 0;
    virtual void getInteractionsReceivedBestEffort(GERTICO::HandleMap &theInteractions) = 0;
    virtual void getInteractionsReceivedReliable(GERTICO::HandleMap &theInteractions) = 0;
    virtual void getMomData(GeRtiFactory::GeRtiHandle theRequest, GeRtiFactory::Handles const & theAttributes, GeRtiFactory::HandleValues_out data) = 0;
    virtual long getROlength(void) = 0;
    virtual long getReflectionsReceived (void) = 0;
    virtual void getReflectionsReceivedBestEffort(GERTICO::HandleMap &theReflections) = 0;
    virtual void getReflectionsReceivedReliable(GERTICO::HandleMap &theReflections) = 0;
    virtual long getTSOlength(void) = 0;
    virtual void setMomLRC(GERTICO::MomLRC *theMomLRC) = 0;

    // Process queues.
    virtual void reset(void) = 0;
    virtual bool process(bool const &processAll) = 0;

    // Save / Restore
    virtual void federateSaveBegun(void) = 0;
    virtual void restore(DOMElement &theDOMElement) = 0;
    virtual void save(DOMDocument &theDOMDocument, DOMElement &theDOMElement) = 0;

    // Set values.
    virtual void setAsynchronousDelivery(bool const &theAsynchronousDelivery) = 0;
    virtual void setDisableTimeConstrained(void) = 0;
    virtual void setDisableTimeRegulation(void) = 0;
    virtual void setFlushQueueRequest(void) = 0;
    virtual void setGeRtiAmVar(GeRtiFactory::GeRtiAmbassador_var const &theGeRtiAmVar) = 0;
    virtual void setNextEventRequest(bool const &avail) = 0;
    virtual void setTimeAdvanceRequest(bool const &avail) = 0;

    virtual void publishObjectClass(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const &attributeList) = 0;
    virtual void setTimeService(GERTICO::TimeManagementLRC *theTimeManagementLRC) = 0;
    virtual GERTICO::GeRtiFedTime *smallestAvailableTSO(void) = 0;
    virtual void unsubscribeObjectClassWithRegionReceiver(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theRegion) = 0;
    virtual void unsubscribeObjectClassWithRegionsReceiver(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap) = 0;
  };
};

#endif
