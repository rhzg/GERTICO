/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: ManagementObjectModelLRC.h,v $
Revision 1.21  2010/05/17 08:05:57  mul
Add logical time interval.

Revision 1.20  2009/05/07 12:35:42  mul
Minor changes.

Revision 1.19  2009/03/19 09:15:44  mul
Changes to optimize reading mom in lrc.

Revision 1.18  2008/01/30 13:31:42  mul
Changes for ieee1516.

Revision 1.17  2007/09/06 06:37:40  mul
Changes for ieee1516.

Revision 1.16  2007/05/15 13:24:14  mul
Changes for combined 1.3 and 1516 logic.

Revision 1.15  2007/05/09 13:16:54  mul
Use generic time.

Revision 1.14  2007/03/12 13:20:30  mul
Changed string to wstring.

Revision 1.13  2007/03/06 09:30:18  mul
Changes for ieee conversion.

Revision 1.12  2007/02/02 13:32:40  mul
Add some more services.

Revision 1.11  2007/01/12 14:46:10  mul
Remove dependency on receiver.

Revision 1.10  2006/09/29 10:03:46  mul
Fix handling of mom jobs.

Revision 1.9  2006/09/28 14:40:35  mul
Fix logic for mom thread.

Revision 1.8  2006/09/19 07:55:19  mul
Fix some program structure problems.

Revision 1.7  2006/09/12 11:35:11  mul
Changes for phase 5 testcases.

Revision 1.6  2006/09/06 15:00:30  mul
Changes for phase 4 testcases.

Revision 1.5  2006/08/08 14:18:07  mul
Changes for mom test cases.

Revision 1.4  2006/08/01 11:37:54  mul
Changes for mom.

Revision 1.3  2006/05/12 13:38:11  mul
Fix logic for mom federate objects.

Revision 1.2  2006/04/19 15:05:38  mul
Changes for MOM.

Revision 1.1  2006/03/30 11:07:18  mul
New files.


**
*******************************************************************************/


// -*- C++ -*-
//
// $Id: ManagementObjectModelLRC.h,v 1.21 2010/05/17 08:05:57 mul Exp $

#ifndef ManagementObjectModelLRC_H_
#define ManagementObjectModelLRC_H_

#include "string"

#include "GeRtiTime/TimeService.h"
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiTypes.h"

#include "FederateDB.h"
#include "MomLRC.h"
#include "ObjectManagementLRC.h"
#include "GeRtiSender.h"
#include "SupportingServicesLRC.h"
#include "EventMarket.h"

namespace GERTICO
{
#ifdef IEEE_1516
  class MomDeleteObjectInstance : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::UserSuppliedTag userSuppliedTag;
    GeRtiFactory::GeRtiHandle objectHandle;

  public:
    MomDeleteObjectInstance(GeRtiFactory::GeRtiHandle const &theObjectHandle, std::string const &theUserSuppliedTag, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomDeleteObjectInstance(void);

    JobStatus execute(void);
  };
#else
  class MomDeleteObjectInstance : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::UserSuppliedTag userSuppliedTag;
    std::wstring objectName;

  public:
    MomDeleteObjectInstance(std::wstring const &theObjectName, std::string const &theUserSuppliedTag, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomDeleteObjectInstance(void);

    JobStatus execute(void);
  };
#endif

#ifdef IEEE_1516
  class MomDeleteObjectInstanceWithTime : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::UserSuppliedTag userSuppliedTag;
    GERTICO::GeRtiFedTime *federationTime;
    GeRtiFactory::GeRtiHandle objectHandle;

  public:
    MomDeleteObjectInstanceWithTime(GeRtiFactory::GeRtiHandle const &theObjectHandle, std::string const &theUserSuppliedTag, GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomDeleteObjectInstanceWithTime(void);

    JobStatus execute(void);
  };
#else
  class MomDeleteObjectInstanceWithTime : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::UserSuppliedTag userSuppliedTag;
    GERTICO::GeRtiFedTime *federationTime;
    std::wstring objectName;

  public:
    MomDeleteObjectInstanceWithTime(std::wstring const &theObjectName, std::string const &theUserSuppliedTag, GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomDeleteObjectInstanceWithTime(void);

    JobStatus execute(void);
  };
#endif

  class MomDisableAsynchronousDelivery : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;

  public:
    MomDisableAsynchronousDelivery(GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomDisableAsynchronousDelivery(void);

    JobStatus execute(void);
  };

  class MomDisableTimeConstrained : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;

  public:
    MomDisableTimeConstrained(GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomDisableTimeConstrained(void);

    JobStatus execute(void);
  };

  class MomDisableTimeRegulation : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;

  public:
    MomDisableTimeRegulation(GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomDisableTimeRegulation(void);

    JobStatus execute(void);
  };

  class MomEnableAsynchronousDelivery : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;

  public:
    MomEnableAsynchronousDelivery(GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomEnableAsynchronousDelivery(void);

    JobStatus execute(void);
  };

  class MomEnableTimeConstrained : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;

  public:
    MomEnableTimeConstrained(GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomEnableTimeConstrained(void);

    JobStatus execute(void);
  };

  class MomEnableTimeRegulation : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
#ifndef IEEE_1516
    GERTICO::GeRtiFedTime *federationTime;
#endif
    GERTICO::GeRtiLogicalTimeInterval *lookahead;

  public:
#ifdef IEEE_1516
    MomEnableTimeRegulation(GERTICO::GeRtiLogicalTimeInterval *theLookahead, GERTICO::GeRtiSender &theGeRtiSender);
#else
    MomEnableTimeRegulation(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiLogicalTimeInterval *theLookahead, GERTICO::GeRtiSender &theGeRtiSender);
#endif
    virtual ~MomEnableTimeRegulation(void);

    JobStatus execute(void);
  };

  class MomFederateRestoreComplete : public virtual GERTICO::Job
  {
    CORBA::Boolean successIndicator;
    GERTICO::GeRtiSender &geRtiSender;

  public:
    MomFederateRestoreComplete(CORBA::Boolean &theBoolean, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomFederateRestoreComplete(void);

    JobStatus execute(void);
  };

  class MomFederateSaveBegun : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;

  public:
    MomFederateSaveBegun(GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomFederateSaveBegun(void);

    JobStatus execute(void);
  };

  class MomFederateSaveComplete : public virtual GERTICO::Job
  {
    CORBA::Boolean successIndicator;
    GERTICO::GeRtiSender &geRtiSender;

  public:
    MomFederateSaveComplete(CORBA::Boolean &theSuccessIndicator, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomFederateSaveComplete(void);

    JobStatus execute(void);
  };

  class MomFlushQueueRequest : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GERTICO::GeRtiFedTime *federationTime;

  public:
    MomFlushQueueRequest(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomFlushQueueRequest(void);

    JobStatus execute(void);
  };

#ifdef IEEE_1516
  class MomLocalDeleteObjectInstance : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle objectHandle;

  public:
    MomLocalDeleteObjectInstance(GeRtiFactory::GeRtiHandle const &theObjecthandle, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomLocalDeleteObjectInstance(void);

    JobStatus execute(void);
  };
#else
  class MomLocalDeleteObjectInstance : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    std::wstring objectName;

  public:
    MomLocalDeleteObjectInstance(std::wstring const &theObjectName, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomLocalDeleteObjectInstance(void);

    JobStatus execute(void);
  };
#endif

#ifdef IEEE_1516
  class MomChangeAttributeTransportationType : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle objectHandle;
    GeRtiFactory::GeRtiHandle transportType;
    GeRtiFactory::Handles attributes;

  public:
    MomChangeAttributeTransportationType(GeRtiFactory::GeRtiHandle const &theObjecthandle, GeRtiFactory::Handles &theAttributes, GeRtiFactory::GeRtiHandle const &theTransportationType, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomChangeAttributeTransportationType(void);

    JobStatus execute(void);
  };
#else
  class MomChangeAttributeTransportationType : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle transportType;
    GeRtiFactory::Handles attributes;
    std::wstring objectName;

  public:
    MomChangeAttributeTransportationType(std::wstring const &theObjectName, GeRtiFactory::Handles &theAttributes, GeRtiFactory::GeRtiHandle const &theTransportationType, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomChangeAttributeTransportationType(void);

    JobStatus execute(void);
  };
#endif

#ifdef IEEE_1516
  class MomChangeAttributeOrderType : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle objectHandle;
    GeRtiFactory::GeRtiHandle orderType;
    GeRtiFactory::Handles attributes;

  public:
    MomChangeAttributeOrderType(GeRtiFactory::GeRtiHandle const &theObjecthandle, GeRtiFactory::Handles &theAttributes, GeRtiFactory::GeRtiHandle const &theOrderType, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomChangeAttributeOrderType(void);

    JobStatus execute(void);
  };
#else
  class MomChangeAttributeOrderType : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle orderType;
    GeRtiFactory::Handles attributes;
    std::wstring objectName;

  public:
    MomChangeAttributeOrderType(std::wstring const &theObjectName, GeRtiFactory::Handles &theAttributes, GeRtiFactory::GeRtiHandle const &theOrderType, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomChangeAttributeOrderType(void);

    JobStatus execute(void);
  };
#endif

  class MomModifyLookahead : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GERTICO::GeRtiLogicalTimeInterval *lookahead;

  public:
    MomModifyLookahead(GERTICO::GeRtiLogicalTimeInterval *theLookahead, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomModifyLookahead(void);

    JobStatus execute(void);
  };

  class MomNextEventRequest : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GERTICO::GeRtiFedTime *federationTime;

  public:
    MomNextEventRequest(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomNextEventRequest(void);

    JobStatus execute(void);
  };

  class MomNextEventRequestAvailable : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GERTICO::GeRtiFedTime *federateTime;

  public:
    MomNextEventRequestAvailable(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomNextEventRequestAvailable(void);

    JobStatus execute(void);
  };

  class MomPublishInteractionClass : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle interactionClass;

  public:
    MomPublishInteractionClass(const GeRtiFactory::GeRtiHandle &theInteractionClass, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomPublishInteractionClass(void);

    JobStatus execute(void);
  };

  class MomPublishObjectClass : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle objectClass;
    GeRtiFactory::Handles attributes;

  public:
    MomPublishObjectClass(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::Handles &theAttributes, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomPublishObjectClass(void);

    JobStatus execute(void);
  };

  class MomResignFederationExecution : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::ResignAction resignAction;

  public:
    MomResignFederationExecution(GeRtiFactory::ResignAction &theResignAction, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomResignFederationExecution(void);

    JobStatus execute(void);
  };

  class MomSubscribeInteractionClass : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle interactionClass;
    CORBA::Boolean active;

    // Save/restore.
    static std::string activeStr;
    static std::string interactionClassStr;

  public:
    MomSubscribeInteractionClass(const GeRtiFactory::GeRtiHandle &theInteractionClass, const CORBA::Boolean &theActive, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomSubscribeInteractionClass(void);

    JobStatus execute(void);
  };

  class MomSubscribeObjectClassAttributes : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle objectClass;
    GeRtiFactory::Handles attributes;
    CORBA::Boolean active;

  public:
    MomSubscribeObjectClassAttributes(const GeRtiFactory::GeRtiHandle &theObjectClass, const GeRtiFactory::Handles &theAttributes, const CORBA::Boolean &theActive, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomSubscribeObjectClassAttributes(void);

    JobStatus execute(void);
  };

  class MomSynchronizationPointAchieved : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    std::wstring label;

  public:
    MomSynchronizationPointAchieved(const std::wstring &theLabel, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomSynchronizationPointAchieved(void);

    JobStatus execute(void);
  };

  class MomTimeAdvanceRequest : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GERTICO::GeRtiFedTime *federationTime;

  public:
    MomTimeAdvanceRequest(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomTimeAdvanceRequest(void);

    JobStatus execute(void);
  };

  class MomTimeAdvanceRequestAvailable : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GERTICO::GeRtiFedTime *federationTime;

  public:
    MomTimeAdvanceRequestAvailable(GERTICO::GeRtiFedTime *theFederationTime, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomTimeAdvanceRequestAvailable(void);

    JobStatus execute(void);
  };

#ifdef IEEE_1516
  class MomUnconditionalAttributeOwnershipDivestiture : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::Handles attributes;
    GeRtiFactory::GeRtiHandle objectHandle;

  public:
    MomUnconditionalAttributeOwnershipDivestiture(GeRtiFactory::GeRtiHandle const &theObjectName, GeRtiFactory::Handles const &theAttributes, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomUnconditionalAttributeOwnershipDivestiture(void);

    JobStatus execute(void);
  };
#else
  class MomUnconditionalAttributeOwnershipDivestiture : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::Handles attributes;
    std::wstring objectName;

  public:
    MomUnconditionalAttributeOwnershipDivestiture(std::wstring const &theObjectName, GeRtiFactory::Handles const &theAttributes, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomUnconditionalAttributeOwnershipDivestiture(void);

    JobStatus execute(void);
  };
#endif

  class MomUnpublishInteractionClass : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle interactionClass;

  public:
    MomUnpublishInteractionClass(const GeRtiFactory::GeRtiHandle &theInteractionClass, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomUnpublishInteractionClass(void);

    JobStatus execute(void);
  };

  class MomUnpublishObjectClass : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle objectClass;

  public:
    MomUnpublishObjectClass(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomUnpublishObjectClass(void);

    JobStatus execute(void);
  };

  class MomUnsubscribeInteractionClass : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle interactionClass;

  public:
    MomUnsubscribeInteractionClass(const GeRtiFactory::GeRtiHandle &theInteractionClass, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomUnsubscribeInteractionClass(void);

    JobStatus execute(void);
  };

  class MomUnsubscribeObjectClass : public virtual GERTICO::Job
  {
    GERTICO::GeRtiSender &geRtiSender;
    GeRtiFactory::GeRtiHandle objectClass;

  public:
    MomUnsubscribeObjectClass(const GeRtiFactory::GeRtiHandle &theObjectClass, GERTICO::GeRtiSender &theGeRtiSender);
    virtual ~MomUnsubscribeObjectClass(void);

    JobStatus execute(void);
  };

  class ManagementObjectModelLRC : public virtual GERTICO::MomLRC
  {
    ACE_Semaphore &ps;
    GERTICO::EventMarket &eventMarket;
    GERTICO::FederateDB &federateDB;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
    GERTICO::GeRtiSender *geRtiSender;
    bool serviceReporting;

    void adjustModifyAttributeState(const GeRtiFactory::HandleValues &theData);
    void adjustSetServiceReporting(const GeRtiFactory::HandleValues &theData);
    void getOrderType(GeRtiFactory::GeRtiHandle &theOrderingType, char *theBuff);
#ifdef IEEE_1516
    void getResignAction(GeRtiFactory::ResignAction &theResignAction, unsigned long const &theUlong);
#else
    void getAttributes(GeRtiFactory::Handles &theAttributes, char *theBuff);
    void getBoolean(CORBA::Boolean &theBoolean, char *theBuff);
    void getResignAction(GeRtiFactory::ResignAction &theResignAction, char *theBuff);
#endif
    bool getTransportationType(GeRtiFactory::GeRtiHandle &theTransportationType, char *theBuff);
    void serviceDeleteObjectInstance(const GeRtiFactory::HandleValues &theData);
    void serviceDisableAsynchronousDelivery(const GeRtiFactory::HandleValues &theData);
    void serviceDisableTimeConstrained(const GeRtiFactory::HandleValues &theData);
    void serviceDisableTimeRegulation(const GeRtiFactory::HandleValues &theData);
    void serviceEnableAsynchronousDelivery(const GeRtiFactory::HandleValues &theData);
    void serviceEnableTimeConstrained(const GeRtiFactory::HandleValues &theData);
    void serviceEnableTimeRegulation(const GeRtiFactory::HandleValues &theData);
    void serviceFederateRestoreComplete(const GeRtiFactory::HandleValues &theData);
    void serviceFederateSaveBegun(const GeRtiFactory::HandleValues &theData);
    void serviceFederateSaveComplete(const GeRtiFactory::HandleValues &theData);
    void serviceFlushQueueRequest(const GeRtiFactory::HandleValues &theData);
    void serviceLocalDeleteObjectInstance(const GeRtiFactory::HandleValues &theData);
    void serviceChangeAttributeTransportationType(const GeRtiFactory::HandleValues &theData);
    void serviceChangeAttributeOrderType(const GeRtiFactory::HandleValues &theData);
    void serviceChangeInteractionTransportationType(const GeRtiFactory::HandleValues &theData);
    void serviceChangeChangeInteractionOrderType(const GeRtiFactory::HandleValues &theData);
    void serviceModifyLookahead(const GeRtiFactory::HandleValues &theData);
    void serviceNextEventRequest(const GeRtiFactory::HandleValues &theData);
    void serviceNextEventRequestAvailable(const GeRtiFactory::HandleValues &theData);
    void servicePublishInteractionClass(const GeRtiFactory::HandleValues &theData);
    void servicePublishObjectClass(const GeRtiFactory::HandleValues &theData);
    void serviceResignFederationExecution(const GeRtiFactory::HandleValues &theData);
    void serviceSubscribeInteractionClass(const GeRtiFactory::HandleValues &theData);
    void serviceSubscribeObjectClassAttributes(const GeRtiFactory::HandleValues &theData);
    void serviceSynchronizationPointAchieved(const GeRtiFactory::HandleValues &theData);
    void serviceTimeAdvanceRequest(const GeRtiFactory::HandleValues &theData);
    void serviceTimeAdvanceRequestAvailable(const GeRtiFactory::HandleValues &theData);
    void serviceUnconditionalAttributeOwnershipDivestiture(const GeRtiFactory::HandleValues &theData);
    void serviceUnpublishInteractionClass(const GeRtiFactory::HandleValues &theData);
    void serviceUnpublishObjectClass(const GeRtiFactory::HandleValues &theData);
    void serviceUnsubscribeInteractionClass(const GeRtiFactory::HandleValues &theData);
    void serviceUnsubscribeObjectClass(const GeRtiFactory::HandleValues &theData);

  public:
    GeRtiFactory::GeRtiHandle managerObject;
    GeRtiFactory::GeRtiHandle managerFederateObjectClass;

    // Federate attributes
    GeRtiFactory::GeRtiHandle managerFederateFederateHandle;
    GeRtiFactory::GeRtiHandle managerFederateFederateType;
    GeRtiFactory::GeRtiHandle managerFederateFederateHost;
    GeRtiFactory::GeRtiHandle managerFederateRTIversion;
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateFDDid;
#else
    GeRtiFactory::GeRtiHandle managerFederateFEDid;
#endif
    GeRtiFactory::GeRtiHandle managerFederateTimeConstrained;
    GeRtiFactory::GeRtiHandle managerFederateTimeRegulating;
    GeRtiFactory::GeRtiHandle managerFederateAsynchronousDelivery;
    GeRtiFactory::GeRtiHandle managerFederateFederateState;
    GeRtiFactory::GeRtiHandle managerFederateTimeManagerState;
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateLogicalTime;
#else
    GeRtiFactory::GeRtiHandle managerFederateFederateTime;
#endif
    GeRtiFactory::GeRtiHandle managerFederateLookahead;
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateGALT;
    GeRtiFactory::GeRtiHandle managerFederateLITS;
#else
    GeRtiFactory::GeRtiHandle managerFederateLBTS;
    GeRtiFactory::GeRtiHandle managerFederateMinNextEventTime;
#endif
    GeRtiFactory::GeRtiHandle managerFederateROlength;
    GeRtiFactory::GeRtiHandle managerFederateTSOlength;
    GeRtiFactory::GeRtiHandle managerFederateReflectionsReceived;
    GeRtiFactory::GeRtiHandle managerFederateUpdatesSent;
    GeRtiFactory::GeRtiHandle managerFederateInteractionsReceived;
    GeRtiFactory::GeRtiHandle managerFederateInteractionsSent;
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesThatCanBeDeleted;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesUpdated;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesReflected;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesDeleted;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesRemoved;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesRegistered;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesDiscovered;
    // managerFederateTimeGrantedTime;
    // managerFederateTimetimeGrantedTime;
#else
    GeRtiFactory::GeRtiHandle managerFederateObjectsOwned;
    GeRtiFactory::GeRtiHandle managerFederateObjectsUpdated;
    GeRtiFactory::GeRtiHandle managerFederateObjectsReflected;
#endif

    // MOM Interactions.
    GeRtiFactory::GeRtiHandle managerInteractionFederate;
    GeRtiFactory::GeRtiHandle managerInteractionFederateFederate;

    // Federate Adjust
    GeRtiFactory::GeRtiHandle managerFederateAdjustSetTiming;
    GeRtiFactory::GeRtiHandle managerFederateAdjustModifyAttributeState;
      GeRtiFactory::GeRtiHandle managerFederateAdjustModifyAttributeStateObjectInstance;
      GeRtiFactory::GeRtiHandle managerFederateAdjustModifyAttributeStateAttribute;
      GeRtiFactory::GeRtiHandle managerFederateAdjustModifyAttributeStateAttributeState;
    GeRtiFactory::GeRtiHandle managerFederateAdjustSetServiceReporting;
      GeRtiFactory::GeRtiHandle managerFederateAdjustSetServiceReportingState;
    GeRtiFactory::GeRtiHandle managerFederateAdjustSetExceptionLogging;

    // Federate Report
//    GeRtiFactory::GeRtiHandle managerFederateReportObjectPublication;
//    GeRtiFactory::GeRtiHandle managerFederateReportInteractionPublication;
//    GeRtiFactory::GeRtiHandle managerFederateReportObjectSubscription;
//    GeRtiFactory::GeRtiHandle managerFederateReportInteractionSubscription;
//    GeRtiFactory::GeRtiHandle managerFederateReportObjectsOwned;
//    GeRtiFactory::GeRtiHandle managerFederateReportObjectsUpdated;
//    GeRtiFactory::GeRtiHandle managerFederateReportObjectsReflected;
//    GeRtiFactory::GeRtiHandle managerFederateReportUpdatesSent;
    GeRtiFactory::GeRtiHandle managerFederateReportReflectionsReceived;
      GeRtiFactory::GeRtiHandle managerFederateReportReflectionsReceivedTransportationType;
      GeRtiFactory::GeRtiHandle managerFederateReportReflectionsReceivedReflectCounts;
//    GeRtiFactory::GeRtiHandle managerFederateReportInteractionsSent;
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionsReceived;
      GeRtiFactory::GeRtiHandle managerFederateReportInteractionsReceivedTransportationType;
      GeRtiFactory::GeRtiHandle managerFederateReportInteractionsReceivedInteractionCounts;
//    GeRtiFactory::GeRtiHandle managerFederateReportObjectInformation;
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateReportException;
      GeRtiFactory::GeRtiHandle managerFederateReportExceptionService;
      GeRtiFactory::GeRtiHandle managerFederateReportExceptionException;
#else
    GeRtiFactory::GeRtiHandle managerFederateReportAlert;
      GeRtiFactory::GeRtiHandle managerFederateReportAlertAlertSeverity;
      GeRtiFactory::GeRtiHandle managerFederateReportAlertAlertDescription;
      GeRtiFactory::GeRtiHandle managerFederateReportAlertAlertID;
#endif
    GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocation;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationService;
#ifndef IEEE_1516
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationInitiator;
#endif
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationSuccessIndicator;
#ifdef IEEE_1516
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationSuppliedArguments;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationReturnedArguments;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationException;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationSerialNumber;
#else
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationSuppliedArgument1;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationSuppliedArgument2;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationSuppliedArgument3;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationSuppliedArgument4;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationSuppliedArgument5;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationReturnedArgument;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationExceptionDescription;
      GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationExceptionID;
#endif

    // Federate Service
    GeRtiFactory::GeRtiHandle managerFederateServiceResignFederationExecution;
      GeRtiFactory::GeRtiHandle managerFederateServiceResignFederationExecutionResignAction;

    GeRtiFactory::GeRtiHandle managerFederateServiceSynchronizationPointAchieved;
      GeRtiFactory::GeRtiHandle managerFederateServiceSynchronizationPointAchievedLabel;

    GeRtiFactory::GeRtiHandle managerFederateServiceFederateSaveBegun;

    GeRtiFactory::GeRtiHandle managerFederateServiceFederateSaveComplete;
      GeRtiFactory::GeRtiHandle managerFederateServiceFederateSaveCompleteSuccessIndicator;

    GeRtiFactory::GeRtiHandle managerFederateServiceFederateRestoreComplete;
      GeRtiFactory::GeRtiHandle managerFederateServiceFederateRestoreCompleteSuccessIndicator;

#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateServicePublishObjectClassAttributes;
#else
    GeRtiFactory::GeRtiHandle managerFederateServicePublishObjectClass;
#endif
      GeRtiFactory::GeRtiHandle managerFederateServicePublishObjectClassObjectClass;
      GeRtiFactory::GeRtiHandle managerFederateServicePublishObjectClassAttributeList;

#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateServiceUnpublishObjectClassAttributes;
#else
    GeRtiFactory::GeRtiHandle managerFederateServiceUnpublishObjectClass;
#endif
      GeRtiFactory::GeRtiHandle managerFederateServiceUnpublishObjectClassObjectClass;

    GeRtiFactory::GeRtiHandle managerFederateServicePublishInteractionClass;
      GeRtiFactory::GeRtiHandle managerFederateServicePublishInteractionClassInteractionClass;

    GeRtiFactory::GeRtiHandle managerFederateServiceUnpublishInteractionClass;
      GeRtiFactory::GeRtiHandle managerFederateServiceUnpublishInteractionClassInteractionClass;

    GeRtiFactory::GeRtiHandle managerFederateServiceSubscribeObjectClassAttributes;
      GeRtiFactory::GeRtiHandle managerFederateServiceSubscribeObjectClassAttributesObjectClass;
      GeRtiFactory::GeRtiHandle managerFederateServiceSubscribeObjectClassAttributesAttributeList;
      GeRtiFactory::GeRtiHandle managerFederateServiceSubscribeObjectClassAttributesActive;

#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateServiceUnsubscribeObjectClassAttributes;
#else
    GeRtiFactory::GeRtiHandle managerFederateServiceUnsubscribeObjectClass;
#endif
      GeRtiFactory::GeRtiHandle managerFederateServiceUnsubscribeObjectClassObjectClass;

    GeRtiFactory::GeRtiHandle managerFederateServiceSubscribeInteractionClass;
      GeRtiFactory::GeRtiHandle managerFederateServiceSubscribeInteractionClassInteractionClass;
      GeRtiFactory::GeRtiHandle managerFederateServiceSubscribeInteractionClassActive;

    GeRtiFactory::GeRtiHandle managerFederateServiceUnsubscribeInteractionClass;
      GeRtiFactory::GeRtiHandle managerFederateServiceUnsubscribeInteractionClassInteractionClass;

    GeRtiFactory::GeRtiHandle managerFederateServiceDeleteObjectInstance;
      GeRtiFactory::GeRtiHandle managerFederateServiceDeleteObjectInstanceObjectInstance;
      GeRtiFactory::GeRtiHandle managerFederateServiceDeleteObjectInstanceTag;
#ifdef IEEE_1516
      GeRtiFactory::GeRtiHandle managerFederateServiceDeleteObjectInstanceTimeStamp;
#else
      GeRtiFactory::GeRtiHandle managerFederateServiceDeleteObjectInstanceFederationTime;
#endif

    GeRtiFactory::GeRtiHandle managerFederateServiceLocalDeleteObjectInstance;
      GeRtiFactory::GeRtiHandle managerFederateServiceLocalDeleteObjectInstanceObjectInstance;

    GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeTransportationType;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeTransportationTypeObjectInstance;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeTransportationTypeAttributeList;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeTransportationTypeTransportationType;

    GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeOrderType;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeOrderTypeObjectInstance;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeOrderTypeAttributeList;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeOrderTypeOrderingType;

    GeRtiFactory::GeRtiHandle managerFederateServiceChangeInteractionTransportationType;

    GeRtiFactory::GeRtiHandle managerFederateServiceChangeInteractionOrderType;

    GeRtiFactory::GeRtiHandle managerFederateServiceUnconditionalAttributeOwnershipDivestiture;
      GeRtiFactory::GeRtiHandle managerFederateServiceUnconditionalAttributeOwnershipDivestitureObjectInstance;
      GeRtiFactory::GeRtiHandle managerFederateServiceUnconditionalAttributeOwnershipDivestitureAttributeList;

    GeRtiFactory::GeRtiHandle managerFederateServiceEnableTimeRegulation;
#ifndef IEEE_1516
      GeRtiFactory::GeRtiHandle managerFederateServiceEnableTimeRegulationFederationTime;
#endif
      GeRtiFactory::GeRtiHandle managerFederateServiceEnableTimeRegulationLookahead;

    GeRtiFactory::GeRtiHandle managerFederateServiceDisableTimeRegulation;

    GeRtiFactory::GeRtiHandle managerFederateServiceEnableTimeConstrained;

    GeRtiFactory::GeRtiHandle managerFederateServiceDisableTimeConstrained;

    GeRtiFactory::GeRtiHandle managerFederateServiceEnableAsynchronousDelivery;

    GeRtiFactory::GeRtiHandle managerFederateServiceDisableAsynchronousDelivery;

    GeRtiFactory::GeRtiHandle managerFederateServiceModifyLookahead;
      GeRtiFactory::GeRtiHandle managerFederateServiceModifyLookaheadLookahead;

    GeRtiFactory::GeRtiHandle managerFederateServiceTimeAdvanceRequest;
#ifdef IEEE_1516
      GeRtiFactory::GeRtiHandle managerFederateServiceTimeAdvanceRequestTimeStamp;
#else
      GeRtiFactory::GeRtiHandle managerFederateServiceTimeAdvanceRequestFederationTime;
#endif

    GeRtiFactory::GeRtiHandle managerFederateServiceTimeAdvanceRequestAvailable;
#ifdef IEEE_1516
      GeRtiFactory::GeRtiHandle managerFederateServiceTimeAdvanceRequestAvailableTimeStamp;
#else
      GeRtiFactory::GeRtiHandle managerFederateServiceTimeAdvanceRequestAvailableFederationTime;
#endif

#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateServiceNextMessageRequest;
      GeRtiFactory::GeRtiHandle managerFederateServiceNextMessageRequestTimeStamp;
#else
    GeRtiFactory::GeRtiHandle managerFederateServiceNextEventRequest;
      GeRtiFactory::GeRtiHandle managerFederateServiceNextEventRequestFederationTime;
#endif

#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateServiceNextMessageRequestAvailable;
      GeRtiFactory::GeRtiHandle managerFederateServiceNextMessageRequestAvailableTimeStamp;
#else
    GeRtiFactory::GeRtiHandle managerFederateServiceNextEventRequestAvailable;
      GeRtiFactory::GeRtiHandle managerFederateServiceNextEventRequestAvailableFederationTime;
#endif

    GeRtiFactory::GeRtiHandle managerFederateServiceFlushQueueRequest;
#ifdef IEEE_1516
      GeRtiFactory::GeRtiHandle managerFederateServiceFlushQueueRequestTimeStamp;
#else
      GeRtiFactory::GeRtiHandle managerFederateServiceFlushQueueRequestFederationTime;
#endif

    std::string managerFederateName;
    GERTICO::ReceiverLRC &receiverLRC;

    //Constructor
    ManagementObjectModelLRC(GERTICO::FederateDB &theFederateDB, GERTICO::GeRtiSender *theGeRtiSender, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, GERTICO::EventMarket &theEventMarket, GERTICO::ReceiverLRC &theReceiverLRC, ACE_Semaphore &thePs);

    //Destructor
    virtual ~ManagementObjectModelLRC(void);

    bool checkReportServiceInvocation(void);
    void doMomRequest(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::HandleValues & data);
    void getMomData(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::Handles & theAttributes, GeRtiFactory::HandleValues_out data);
#ifdef IEEE_1516
    void sendReportException(const GERTICO::MomException &theMomException);
#else
    void sendReportAlert(const GERTICO::MomAlert &theMomAlert);
#endif
    void sendReportServiceInvocation(const GERTICO::MomReportServiceInvocation &theMomReportServiceInvocation);
  };
}
#endif /* ManagementObjectModelLRC_H_  */
