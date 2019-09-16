/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** ManagementObjectModel.h
**
*******************************************************************************/

#ifndef ManagementObjectModel_H_
#define ManagementObjectModel_H_

#include "idl/GeRtiFactoryS.h"
//#include "GeRti/GeRtiOwnershipMasterI.h"

//#include "EventMarket/EventHandler.h"
#include "GeRti/DeclarationManagementRTI.h"
//#include "Mom.h"
//#include "ObjectManagement.h"
#include "SupportingServices.h"

namespace GERTICO
{
  class MomFederate
  {
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle momFederateFederate;
    // SetTiming value
    GeRtiFactory::GeRtiHandle reportPeriod;
    // Last count of Manager.Federate update.
    GeRtiFactory::GeRtiHandle wallClockLast;
    bool doNow;
    bool exceptionLogging;
    bool serviceReporting;

  public:
    MomFederate(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theFederateFederate);
    ~MomFederate(void);

    bool checkExceptionLogging(void);
    bool checkReportPeriod(const GeRtiFactory::GeRtiHandle &theWallClockCounter);
    void getMomFederateFederate(GeRtiFactory::GeRtiHandle &theMomFederateFederate);
    void setExceptionLogging(const bool &theExceptionLogging);
    void setServiceReporting(const bool &theServiceReporting);
    void setTiming(const GeRtiFactory::GeRtiHandle &theReportPeriod);
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::MomFederate *> MomFederateMap;

  class MomReportObjectPublicationHandles
  {
  public:
    MomReportObjectPublicationHandles(void);
    virtual ~MomReportObjectPublicationHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle numberOfClasses;
    GeRtiFactory::GeRtiHandle objectClass;
    GeRtiFactory::GeRtiHandle attributeList;
  };

  class MomReportInteractionPublicationHandles
  {
  public:
    MomReportInteractionPublicationHandles(void);
    virtual ~MomReportInteractionPublicationHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle interactionClassList;
  };

  class MomReportObjectSubscriptionHandles
  {
  public:
    MomReportObjectSubscriptionHandles(void);
    virtual ~MomReportObjectSubscriptionHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle numberOfClasses;
    GeRtiFactory::GeRtiHandle objectClass;
    GeRtiFactory::GeRtiHandle active;
    GeRtiFactory::GeRtiHandle attributeList;
  };

  class MomReportInteractionSubscriptionHandles
  {
  public:
    MomReportInteractionSubscriptionHandles(void);
    virtual ~MomReportInteractionSubscriptionHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle interactionClassList;
  };

  class MomReportObjectsHandles
  {
  public:
    MomReportObjectsHandles(void);
    virtual ~MomReportObjectsHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle objectCounts;
  };

  class MomReportUpdatesSentHandles
  {
  public:
    MomReportUpdatesSentHandles(void);
    virtual ~MomReportUpdatesSentHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle transportationType;
    GeRtiFactory::GeRtiHandle updateCounts;
  };

  class MomReportReflectionsReceivedHandles
  {
  public:
    MomReportReflectionsReceivedHandles(void);
    virtual ~MomReportReflectionsReceivedHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle transportationType;
    GeRtiFactory::GeRtiHandle reflectCounts;
  };

  class MomReportInteractionsHandles
  {
  public:
    MomReportInteractionsHandles(void);
    virtual ~MomReportInteractionsHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle transportationType;
    GeRtiFactory::GeRtiHandle interactionCounts;
  };

  class MomReportObjectInformationHandles
  {
  public:
    MomReportObjectInformationHandles(void);
    virtual ~MomReportObjectInformationHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle objectInstance;
    GeRtiFactory::GeRtiHandle objectAttributeList;
    GeRtiFactory::GeRtiHandle registeredClass;
    GeRtiFactory::GeRtiHandle knownClass;
  };

#ifdef IEEE_1516
  class MomExceptionHandles
  {
  public:
    MomExceptionHandles(void);
    virtual ~MomExceptionHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle exceptionService;
    GeRtiFactory::GeRtiHandle exceptionException;
  };
#else
  class MomAlertHandles
  {
  public:
    MomAlertHandles(void);
    virtual ~MomAlertHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle alertSeverity;
    GeRtiFactory::GeRtiHandle alertDescription;
    GeRtiFactory::GeRtiHandle alertID;
  };
#endif

  class MomReportServiceInvocationHandles
  {
  public:
    MomReportServiceInvocationHandles(void);
    virtual ~MomReportServiceInvocationHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle service;
    GeRtiFactory::GeRtiHandle initiator;
    GeRtiFactory::GeRtiHandle successIndicator;
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle suppliedArguments;
    GeRtiFactory::GeRtiHandle returnedArguments;
    GeRtiFactory::GeRtiHandle exceptionDescription;
    GeRtiFactory::GeRtiHandle serialNumber;
#else
    GeRtiFactory::GeRtiHandle suppliedArgument1;
    GeRtiFactory::GeRtiHandle suppliedArgument2;
    GeRtiFactory::GeRtiHandle suppliedArgument3;
    GeRtiFactory::GeRtiHandle suppliedArgument4;
    GeRtiFactory::GeRtiHandle suppliedArgument5;
    GeRtiFactory::GeRtiHandle returnedArgument;
    GeRtiFactory::GeRtiHandle exceptionDescription;
    GeRtiFactory::GeRtiHandle exceptionID;
#endif
  };

  class MomResignFederationExecutionHandles
  {
  public:
    MomResignFederationExecutionHandles(void);
    virtual ~MomResignFederationExecutionHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle resignAction;
  };

  class MomFederationTimeHandles
  {
  public:
    MomFederationTimeHandles(void);
    virtual ~MomFederationTimeHandles(void);

    GeRtiFactory::GeRtiHandle momClassId;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle federationTime;
  };

  class MomRequestPublications : public virtual GERTICO::Job
  {
    GERTICO::EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::ObjectManagement &objectManagement;
    GERTICO::MomReportInteractionPublicationHandles &momReportInteractionPublicationHandles;
    GERTICO::MomReportObjectPublicationHandles &momReportObjectPublicationHandles;
    GeRtiFactory::GeRtiEvent geRtiEvent;

  public:
    MomRequestPublications(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportObjectPublicationHandles &theMomReportObjectPublicationHandles, GERTICO::MomReportInteractionPublicationHandles &theMomReportInteractionPublicationHandles, GERTICO::ObjectManagement &theObjectManagement, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    virtual ~MomRequestPublications(void);

    GERTICO::JobStatus execute(void);
  };

  class MomRequestSubscriptions : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::MomReportInteractionSubscriptionHandles &momReportInteractionSubscriptionHandles;
    GERTICO::MomReportObjectSubscriptionHandles &momReportObjectSubscriptionHandles;
    GeRtiFactory::GeRtiEvent geRtiEvent;

  public:
    MomRequestSubscriptions(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportObjectSubscriptionHandles &theMomReportObjectSubscriptionHandles, GERTICO::MomReportInteractionSubscriptionHandles &theMomReportInteractionSubscriptionHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    virtual ~MomRequestSubscriptions(void);

    GERTICO::JobStatus execute(void);
  };

  class MomRequestObjectsOwned : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::ObjectManagement &objectManagement;
    GERTICO::MomReportObjectsHandles &momReportObjectsHandles;
    GeRtiFactory::GeRtiEvent geRtiEvent;

  public:
    MomRequestObjectsOwned(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportObjectsHandles &theMomReportObjectsHandles, GERTICO::ObjectManagement &theObjectManagement, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    virtual ~MomRequestObjectsOwned(void);

    GERTICO::JobStatus execute(void);
  };

  class MomRequestObjectsUpdated : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::ObjectManagement &objectManagement;
    GERTICO::MomReportObjectsHandles &momReportObjectsHandles;
    GeRtiFactory::GeRtiEvent geRtiEvent;

  public:
    MomRequestObjectsUpdated(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportObjectsHandles &theMomReportObjectsHandles, GERTICO::ObjectManagement &theObjectManagement, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    virtual ~MomRequestObjectsUpdated(void);

    GERTICO::JobStatus execute(void);
  };

  class MomRequestObjectsReflected : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::MomReportObjectsHandles &momReportObjectsHandles;
    GeRtiFactory::GeRtiEvent geRtiEvent;

  public:
    MomRequestObjectsReflected(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportObjectsHandles &theMomReportObjectsHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    virtual ~MomRequestObjectsReflected(void);

    GERTICO::JobStatus execute(void);
  };

  class MomRequestUpdatesSent : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::MomReportUpdatesSentHandles &momReportUpdatesSentHandles;
    GeRtiFactory::GeRtiEvent geRtiEvent;

  public:
    MomRequestUpdatesSent(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportUpdatesSentHandles &theMomReportUpdatesSentHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    virtual ~MomRequestUpdatesSent(void);

    GERTICO::JobStatus execute(void);
  };

  class MomRequestReflectionsReceived : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::MomReportReflectionsReceivedHandles &momReportReflectionsReceivedHandles;
    GeRtiFactory::GeRtiEvent geRtiEvent;

  public:
    MomRequestReflectionsReceived(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportReflectionsReceivedHandles &theMomReportUpdatesSentHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    virtual ~MomRequestReflectionsReceived(void);

    GERTICO::JobStatus execute(void);
  };

  class MomRequestInteractionsSent : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::MomReportInteractionsHandles &momReportInteractionsHandles;
    GeRtiFactory::GeRtiEvent geRtiEvent;

  public:
    MomRequestInteractionsSent(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportInteractionsHandles &theMomReportInteractionsHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    virtual ~MomRequestInteractionsSent(void);

    GERTICO::JobStatus execute(void);
  };

  class MomRequestInteractionsReceived : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::MomReportInteractionsHandles &momReportInteractionsHandles;
    GeRtiFactory::GeRtiEvent geRtiEvent;

  public:
    MomRequestInteractionsReceived(GeRtiFactory::GeRtiEvent &theGeRtiEvent, GERTICO::MomReportInteractionsHandles &theMomReportInteractionsHandles, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    virtual ~MomRequestInteractionsReceived(void);

    GERTICO::JobStatus execute(void);
  };

  class MomRequestObjectsInformation : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::MomReportObjectInformationHandles &momReportObjectInformationHandles;
    GERTICO::ObjectManagement &objectManagement;
    GeRtiFactory::GeRtiEvent geRtiEvent;
    GeRtiFactory::GeRtiHandle objectHandle;

  public:
    MomRequestObjectsInformation(GeRtiFactory::GeRtiEvent &theGeRtiEvent, const GeRtiFactory::GeRtiHandle &theObjectHandle, GERTICO::MomReportObjectInformationHandles &theMomReportObjectInformationHandles, GERTICO::ObjectManagement &theObjectManagement, GERTICO::FederatesHolder &theFederatesHolder, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    virtual ~MomRequestObjectsInformation(void);

    GERTICO::JobStatus execute(void);
  };

  /*
  class MomResignFederationExecution : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::MomResignFederationExecutionHandles &momResignFederationExecutionHandles;
    GeRtiFactory::GeRtiEvent geRtiEvent;
    GeRtiFactory::GeRtiHandle objectHandle;

  public:
    MomResignFederationExecution(GeRtiFactory::GeRtiEvent &theGeRtiEvent, const GeRtiFactory::GeRtiHandle &theObjectHandle, GERTICO::MomResignFederationExecutionHandles &theMomResignFederationExecutionHandles, GERTICO::FederatesHolder &theFederatesHolder);
    virtual ~MomResignFederationExecution(void);

    GERTICO::JobStatus execute(void);
  };
  */

  class DoMomRequest : public virtual GERTICO::Job
  {
    GERTICO::FederatesHolder &federatesHolder;
    GeRtiFactory::GeRtiEvent geRtiEvent;
    GeRtiFactory::GeRtiHandle federateParameter;
    GeRtiFactory::GeRtiHandle serviceHandle;

  public:
    DoMomRequest(GeRtiFactory::GeRtiEvent &theGeRtiEvent, const GeRtiFactory::GeRtiHandle &theServiceHandle, const GeRtiFactory::GeRtiHandle &theFederateParameter, GERTICO::FederatesHolder &theFederatesHolder);
    virtual ~DoMomRequest(void);

    GERTICO::JobStatus execute(void);
  };

  class RequestManagerFederatesJob : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::MomFederateMap &momFederateMap;
    GeRtiFactory::GeRtiHandle whichClass;
    GeRtiFactory::Handles handles;

  public:
    RequestManagerFederatesJob(GERTICO::FederatesHolder &theFederatesHolder, GERTICO::MomFederateMap &theMomFederateMap, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    ~RequestManagerFederatesJob(void);

    GERTICO::JobStatus execute(void);
  };

  class RequestManagerFederateJob : public virtual GERTICO::Job
  {
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::ClassDescrHolder &interactionRoot;
    GeRtiFactory::GeRtiHandle managerFederateFEDid;
    GERTICO::MomFederateMap &momFederateMap;
    GeRtiFactory::GeRtiHandle federate;
    GeRtiFactory::GeRtiHandle whichClass;
    GeRtiFactory::Handles handles;
    std::wstring federationFile;

  public:
    RequestManagerFederateJob(GERTICO::FederatesHolder &theFederatesHolder, GERTICO::MomFederateMap &theMomFederateMap, const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes, const GeRtiFactory::GeRtiHandle &theManagerFederateFEDid, const std::wstring theFederationFile, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot);
    ~RequestManagerFederateJob(void);

    GERTICO::JobStatus execute(void);
  };

  class SendEventsJob : public virtual GERTICO::Job
  {
    GeRtiFactory::PushEvent e;
    EventHandler *eventHandler;
    bool reliableFlag;

  public:
    SendEventsJob(GeRtiFactory::PushEvent &theE, EventHandler *theEventHandler, bool const &theReliable);
    virtual ~SendEventsJob(void);

    GERTICO::JobStatus execute(void);
  };

  class ManagementObjectModel : public virtual GERTICO::Mom
  {
    ACE_Semaphore &ps;
    ACE_Thread_Mutex pm;
    GERTICO::ClassDescrHolder &interactionRoot;
    GERTICO::ClassDescrHolder &objectRoot;
    GERTICO::DeclarationManagementRTI &declarationManagement;
    EventHandler *eventHandler;
    GERTICO::FederatesHolder &federatesHolder;
    GERTICO::HandleSet momClasses;
    GERTICO::HandleSet managerFederationAttributes;
    GERTICO::JobHolder &federationJobs;
    GERTICO::MomFederateMap momFederateMap;
    GERTICO::ObjectManagement &objectManagement;
    GERTICO::GeRtiOwnershipMasterI &ownershipMaster;
    GERTICO::SupportingServices &supportingServices;
    GeRtiFactory::GeRtiHandle managerFederation;
    std::wstring federationFile;
    std::wstring federationName;
    std::wstring lastSaveName;
#ifdef IEEE_1516
    std::auto_ptr<GERTICO::GeRtiFedTime> lastSaveTime;
#else
    std::string lastSaveTime;
#endif
    std::wstring nextSaveName;
#ifdef IEEE_1516
    std::auto_ptr<GERTICO::GeRtiFedTime> nextSaveTime;
#else
    std::string nextSaveTime;
#endif
    long counter;
    // Number of call of wallClockWorker (NB. 1 s granularity).
    GeRtiFactory::GeRtiHandle wallClockCounter;

    void adjustModifyAttributeState(GeRtiFactory::GeRtiEvent const &theGeRtiEvent);
    void adjustSetExceptionLogging(GeRtiFactory::GeRtiEvent &theGeRtiEvent);
    void adjustSetServiceReporting(GeRtiFactory::GeRtiEvent &theGeRtiEvent);
    void adjustSetTiming(GeRtiFactory::GeRtiEvent &theGeRtiEvent);
    void changeAttributeOrderType(const GeRtiFactory::GeRtiEvent &theEvent);
    void changeAttributeTransportationType(const GeRtiFactory::GeRtiEvent &theGeRtiEvent);
    void changeInteractionOrderType(const GeRtiFactory::GeRtiEvent &theGeRtiEvent);
    void changeInteractionTransportationType(const GeRtiFactory::GeRtiEvent &theGeRtiEvent);
    void getAttributes(GeRtiFactory::Handles &theAttributes, char *theBuff);
    void getFederate(GeRtiFactory::GeRtiHandle &theFederate, GeRtiFactory::GeRtiEvent &theGeRtiEvent);
    void otherManagerFederateSubscribedAttributes(GERTICO::HandleSet &theAttributes);
    void requestManagerFederates(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes);
    void requestManagerFederationUpdate(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes);
    void reverseChecklist(GERTICO::HandleSet &theItems, GeRtiFactory::GeRtiEvent &theGeRtiEvent);
    void sendAlert(const GeRtiFactory::GeRtiHandle &theFederate, const std::string &theAlertSeverity, const std::string &theAlertDescription);
    void unconditionalAttributeOwnershipDivestiture(const GeRtiFactory::GeRtiEvent &theGeRtiEvent);

  public:
#ifdef IEEE_1516
    // MOM Objects.
    // Manager.
    GeRtiFactory::GeRtiHandle managerObject;

    // Manager.Federate
    GeRtiFactory::GeRtiHandle managerFederateObject;

    // Federate attributes
    GERTICO::HandleSet managerFederateAttributes;
    GeRtiFactory::GeRtiHandle managerFederateFederateHandle;
    GeRtiFactory::GeRtiHandle managerFederateFederateType;
    GeRtiFactory::GeRtiHandle managerFederateFederateHost;
    GeRtiFactory::GeRtiHandle managerFederateRTIversion;
    GeRtiFactory::GeRtiHandle managerFederateFDDid;
    GeRtiFactory::GeRtiHandle managerFederateTimeConstrained;
    GeRtiFactory::GeRtiHandle managerFederateTimeRegulating;
    GeRtiFactory::GeRtiHandle managerFederateAsynchronousDelivery;
    GeRtiFactory::GeRtiHandle managerFederateFederateState;
    GeRtiFactory::GeRtiHandle managerFederateTimeManagerState;
    GeRtiFactory::GeRtiHandle managerFederateLogicalTime;
    GeRtiFactory::GeRtiHandle managerFederateLookahead;
    GeRtiFactory::GeRtiHandle managerFederateGALT;
    GeRtiFactory::GeRtiHandle managerFederateLITS;
    GeRtiFactory::GeRtiHandle managerFederateROlength;
    GeRtiFactory::GeRtiHandle managerFederateTSOlength;
    GeRtiFactory::GeRtiHandle managerFederateReflectionsReceived;
    GeRtiFactory::GeRtiHandle managerFederateUpdatesSent;
    GeRtiFactory::GeRtiHandle managerFederateInteractionsReceived;
    GeRtiFactory::GeRtiHandle managerFederateInteractionsSent;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesThatCanBeDeleted;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesUpdated;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesReflected;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesDeleted;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesRemoved;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesRegistered;
    GeRtiFactory::GeRtiHandle managerFederateObjectInstancesDiscovered;

    // Manager.Federation
    GeRtiFactory::GeRtiHandle managerFederationClass;
    GeRtiFactory::GeRtiHandle managerFederationFederationName;
    GeRtiFactory::GeRtiHandle managerFederationFederatesInFederation;
    GeRtiFactory::GeRtiHandle managerFederationRTIversion;
    GeRtiFactory::GeRtiHandle managerFederationFDDid;
    GeRtiFactory::GeRtiHandle managerFederationLastSaveName;
    GeRtiFactory::GeRtiHandle managerFederationLastSaveTime;
    GeRtiFactory::GeRtiHandle managerFederationNextSaveName;
    GeRtiFactory::GeRtiHandle managerFederationNextSaveTime;
#else
    // MOM Objects.
    // Manager.
    GeRtiFactory::GeRtiHandle managerObject;

    // Manager.Federate
    GeRtiFactory::GeRtiHandle managerFederateObjectClass;

    // Federate attributes
    GERTICO::HandleSet managerFederateAttributes;
    GeRtiFactory::GeRtiHandle managerFederateFederateHandle;
    GeRtiFactory::GeRtiHandle managerFederateFederateType;
    GeRtiFactory::GeRtiHandle managerFederateFederateHost;
    GeRtiFactory::GeRtiHandle managerFederateRTIversion;
    GeRtiFactory::GeRtiHandle managerFederateFEDid;
    GeRtiFactory::GeRtiHandle managerFederateTimeConstrained;
    GeRtiFactory::GeRtiHandle managerFederateTimeRegulating;
    GeRtiFactory::GeRtiHandle managerFederateAsynchronousDelivery;
    GeRtiFactory::GeRtiHandle managerFederateFederateState;
    GeRtiFactory::GeRtiHandle managerFederateTimeManagerState;
    GeRtiFactory::GeRtiHandle managerFederateFederateTime;
    GeRtiFactory::GeRtiHandle managerFederateLookahead;
    GeRtiFactory::GeRtiHandle managerFederateLBTS;
    GeRtiFactory::GeRtiHandle managerFederateMinNextEventTime;
    GeRtiFactory::GeRtiHandle managerFederateROlength;
    GeRtiFactory::GeRtiHandle managerFederateTSOlength;
    GeRtiFactory::GeRtiHandle managerFederateReflectionsReceived;
    GeRtiFactory::GeRtiHandle managerFederateUpdatesSent;
    GeRtiFactory::GeRtiHandle managerFederateInteractionsReceived;
    GeRtiFactory::GeRtiHandle managerFederateInteractionsSent;
    GeRtiFactory::GeRtiHandle managerFederateObjectsOwned;
    GeRtiFactory::GeRtiHandle managerFederateObjectsUpdated;
    GeRtiFactory::GeRtiHandle managerFederateObjectsReflected;

    // Manager.Federation
    GeRtiFactory::GeRtiHandle managerFederationClass;
    GeRtiFactory::GeRtiHandle managerFederationFederationName;
    GeRtiFactory::GeRtiHandle managerFederationFederatesInFederation;
    GeRtiFactory::GeRtiHandle managerFederationRTIversion;
    GeRtiFactory::GeRtiHandle managerFederationFEDid;
    GeRtiFactory::GeRtiHandle managerFederationLastSaveName;
    GeRtiFactory::GeRtiHandle managerFederationLastSaveTime;
    GeRtiFactory::GeRtiHandle managerFederationNextSaveName;
    GeRtiFactory::GeRtiHandle managerFederationNextSaveTime;
#endif

    // MOM Interactions
    // Manager
    GeRtiFactory::GeRtiHandle managerInteractionRoot;

    // Manager.Federate
    GeRtiFactory::GeRtiHandle managerInteractionFederate;
    GeRtiFactory::GeRtiHandle managerInteractionFederateFederate;

    // Adjust
    // Manager.Federate.Adjust.SetTiming
    GeRtiFactory::GeRtiHandle managerFederateAdjustSetTiming;
      GeRtiFactory::GeRtiHandle managerFederateAdjustSetTimingReportPeriod;
    // Manager.Federate.Adjust.ModifyAttributeState
    GeRtiFactory::GeRtiHandle managerFederateAdjustModifyAttributeState;
      GeRtiFactory::GeRtiHandle managerFederateAdjustModifyAttributeStateObjectInstance;
      GeRtiFactory::GeRtiHandle managerFederateAdjustModifyAttributeStateAttribute;
      GeRtiFactory::GeRtiHandle managerFederateAdjustModifyAttributeStateAttributeState;
    // Manager.Federate.Adjust.SetServiceReporting
    GeRtiFactory::GeRtiHandle managerFederateAdjustSetServiceReporting;
      GeRtiFactory::GeRtiHandle managerFederateAdjustSetServiceReportingState;
    // Manager.Federate.Adjust.SetExceptionLogging
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateAdjustSetExceptionReporting;
      GeRtiFactory::GeRtiHandle managerFederateAdjustSetExceptionReportingState;
#else
    GeRtiFactory::GeRtiHandle managerFederateAdjustSetExceptionLogging;
      GeRtiFactory::GeRtiHandle managerFederateAdjustSetExceptionLoggingState;
#endif

    // Request
    GeRtiFactory::GeRtiHandle managerFederateRequestPublications;
    GeRtiFactory::GeRtiHandle managerFederateRequestSubscriptions;
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateRequestObjectsInstancesThatCanBeDeleted;
#else
    GeRtiFactory::GeRtiHandle managerFederateRequestObjectsOwned;
#endif
    GeRtiFactory::GeRtiHandle managerFederateRequestObjectsUpdated;
    GeRtiFactory::GeRtiHandle managerFederateRequestObjectsReflected;
    GeRtiFactory::GeRtiHandle managerFederateRequestUpdatesSent;
    GeRtiFactory::GeRtiHandle managerFederateRequestInteractionsSent;
    GeRtiFactory::GeRtiHandle managerFederateRequestReflectionsReceived;
    GeRtiFactory::GeRtiHandle managerFederateRequestInteractionsReceived;
    GeRtiFactory::GeRtiHandle managerFederateRequestObjectInformation;
      GeRtiFactory::GeRtiHandle managerFederateRequestObjectInformationObjectInstance;
    GeRtiFactory::GeRtiHandle managerFederateRequestSynchronizationPoints;
    GeRtiFactory::GeRtiHandle managerFederateRequestSynchronizationPointStatus;

    // Report
    // Manager.Federate.Report.ReportObjectPublication
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateReportObjectClassPublication;
#else
    GeRtiFactory::GeRtiHandle managerFederateReportObjectPublication;
#endif
    GeRtiFactory::GeRtiHandle managerFederateReportObjectPublicationNumberOfClasses;
    GeRtiFactory::GeRtiHandle managerFederateReportObjectPublicationObjectClass;
    GeRtiFactory::GeRtiHandle managerFederateReportObjectPublicationAttributeList;
    GERTICO::MomReportObjectPublicationHandles momReportObjectPublicationHandles;

    // Manager.Federate.Report.ReportInteractionPublication
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionPublication;
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionPublicationInteractionClassList;
    GERTICO::MomReportInteractionPublicationHandles momReportInteractionPublicationHandles;

    // Manager.Federate.Report.ReportObjectSubscription
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateReportObjectClassSubscription;
#else
    GeRtiFactory::GeRtiHandle managerFederateReportObjectSubscription;
#endif
    GeRtiFactory::GeRtiHandle managerFederateReportObjectSubscriptionNumberOfClasses;
    GeRtiFactory::GeRtiHandle managerFederateReportObjectSubscriptionObjectClass;
    GeRtiFactory::GeRtiHandle managerFederateReportObjectSubscriptionAttributeList;
    GeRtiFactory::GeRtiHandle managerFederateReportObjectSubscriptionActive;
    GERTICO::MomReportObjectSubscriptionHandles momReportObjectSubscriptionHandles;

    // Manager.Federate.Report.ReportInteractionSubscription
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionSubscription;
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionSubscriptionInteractionClassList;
    GERTICO::MomReportInteractionSubscriptionHandles momReportInteractionSubscriptionHandles;

    // Manager.Federate.Report.ReportObjectsOwned
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateReportObjectInstancesThatCanBeDeleted;
#else
    GeRtiFactory::GeRtiHandle managerFederateReportObjectsOwned;
#endif
    GeRtiFactory::GeRtiHandle managerFederateReportObjectsOwnedObjectCounts;
    GERTICO::MomReportObjectsHandles momReportObjectsOwnedHandles;

    // Manager.Federate.Report.ReportObjectsUpdated
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateReportObjectInstancessUpdated;
#else
    GeRtiFactory::GeRtiHandle managerFederateReportObjectsUpdated;
#endif
    GeRtiFactory::GeRtiHandle managerFederateReportObjectsUpdatedObjectCounts;
    GERTICO::MomReportObjectsHandles momReportObjectsUpdatedHandles;

    // Manager.Federate.Report.ReportObjectsReflected
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateReportObjectInstancessReflected;
#else
    GeRtiFactory::GeRtiHandle managerFederateReportObjectsReflected;
#endif
    GeRtiFactory::GeRtiHandle managerFederateReportObjectsReflectedObjectCounts;
    GERTICO::MomReportObjectsHandles momReportObjectsReflectedHandles;

    // Manager.Federate.Report.ReportUpdatesSent
    GeRtiFactory::GeRtiHandle managerFederateReportUpdatesSent;
    GeRtiFactory::GeRtiHandle managerFederateReportUpdatesSentTransportationType;
    GeRtiFactory::GeRtiHandle managerFederateReportUpdatesSentUpdateCounts;
    GERTICO::MomReportUpdatesSentHandles momReportUpdatesSentHandles;

    // Manager.Federate.Report.ReportReflectionsReceived
    GeRtiFactory::GeRtiHandle managerFederateReportReflectionsReceived;
    GeRtiFactory::GeRtiHandle managerFederateReportReflectionsReceivedTransportationType;
    GeRtiFactory::GeRtiHandle managerFederateReportReflectionsReceivedReflectCounts;
    GERTICO::MomReportReflectionsReceivedHandles momReportReflectionsReceivedHandles;

    // Manager.Federate.Report.ReportInteractionsSent
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionsSent;
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionsSentTransportationType;
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionsSentInteractionCounts;
    GERTICO::MomReportInteractionsHandles momReportInteractionsSentHandles;

    // Manager.Federate.Report.ReportInteractionsReceived
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionsReceived;
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionsReceivedTransportationType;
    GeRtiFactory::GeRtiHandle managerFederateReportInteractionsReceivedInteractionCounts;
    GERTICO::MomReportInteractionsHandles momReportInteractionsReceivedHandles;

    // Manager.Federate.Report.ReportObjectInformation
#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateReportObjectInstanceInformation;
#else
    GeRtiFactory::GeRtiHandle managerFederateReportObjectInformation;
#endif
    GeRtiFactory::GeRtiHandle managerFederateReportObjectInformationObjectInstance;
    GeRtiFactory::GeRtiHandle managerFederateReportObjectInformationOwnedAttributeList;
    GeRtiFactory::GeRtiHandle managerFederateReportObjectInformationRegisteredClass;
    GeRtiFactory::GeRtiHandle managerFederateReportObjectInformationKnownClass;
    GERTICO::MomReportObjectInformationHandles momReportObjectInformationHandles;

#ifdef IEEE_1516
    // Manager.Federate.Report.Exception
    GeRtiFactory::GeRtiHandle managerFederateReportException;
    GeRtiFactory::GeRtiHandle managerFederateReportExceptionService;
    GeRtiFactory::GeRtiHandle managerFederateReportExceptionException;
    GERTICO::MomExceptionHandles momExceptionHandles;
#else
    // Manager.Federate.Report.Alert
    GeRtiFactory::GeRtiHandle managerFederateReportAlert;
    GeRtiFactory::GeRtiHandle managerFederateReportAlertAlertSeverity;
    GeRtiFactory::GeRtiHandle managerFederateReportAlertAlertDescription;
    GeRtiFactory::GeRtiHandle managerFederateReportAlertAlertID;
    GERTICO::MomAlertHandles momAlertHandles;
#endif

    // Manager.Federate.Report.ReportServiceInvocation
    GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocation;
    GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationService;
    GeRtiFactory::GeRtiHandle managerFederateReportServiceInvocationInitiator;
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
    GERTICO::MomReportServiceInvocationHandles momReportServiceInvocationHandles;

#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateReportMOMexception;

    GeRtiFactory::GeRtiHandle managerFederateReportSynchronizationPoints;

    GeRtiFactory::GeRtiHandle managerFederateReportSynchronizationPointStatus;
#endif

    // Service
    GeRtiFactory::GeRtiHandle managerFederateServiceResignFederationExecution;
      GeRtiFactory::GeRtiHandle managerFederateServiceResignFederationExecutionResignAction;
    GERTICO::MomResignFederationExecutionHandles momResignFederationExecutionHandles;

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
#ifdef IEEE_1516
      GeRtiFactory::GeRtiHandle managerFederateServiceUnsubscribeObjectClassAttributeList;
#endif

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

    // Change attribute transportation type
    GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeTransportationType;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeTransportationTypeObjectInstance;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeTransportationTypeAttributeList;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeTransportationTypeTransportationType;

    // Change attribute order type
    GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeOrderType;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeOrderTypeObjectInstance;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeOrderTypeAttributeList;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeAttributeOrderTypeOrderingType;

    // Change interaction transportation type
    GeRtiFactory::GeRtiHandle managerFederateServiceChangeInteractionTransportationType;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeInteractionTransportationTypeInteractionClass;
      GeRtiFactory::GeRtiHandle managerFederateServiceChangeInteractionTransportationTypeTransportationType;

    // Change interaction order type
    GeRtiFactory::GeRtiHandle managerFederateServiceChangeInteractionOrderType;
    GeRtiFactory::GeRtiHandle managerFederateServiceChangeInteractionOrderTypeInteractionClass;
    GeRtiFactory::GeRtiHandle managerFederateServiceChangeInteractionOrderTypeOrderingType;

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
    GERTICO::MomFederationTimeHandles momTimeAdvanceRequestHandles;

    GeRtiFactory::GeRtiHandle managerFederateServiceTimeAdvanceRequestAvailable;
#ifdef IEEE_1516
      GeRtiFactory::GeRtiHandle managerFederateServiceTimeAdvanceRequestAvailableTimeStamp;
#else
      GeRtiFactory::GeRtiHandle managerFederateServiceTimeAdvanceRequestAvailableFederationTime;
#endif
    GERTICO::MomFederationTimeHandles momTimeAdvanceRequestAvailableHandles;

#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederateServiceNextMessageRequest;
      GeRtiFactory::GeRtiHandle managerFederateServiceNextMessageRequestTimeStamp;
    GERTICO::MomFederationTimeHandles momNextMessageRequestHandles;

    GeRtiFactory::GeRtiHandle managerFederateServiceNextMessageRequestAvailable;
      GeRtiFactory::GeRtiHandle managerFederateServiceNextMessageRequestAvailableTimeStamp;
    GERTICO::MomFederationTimeHandles momNextMessageRequestAvailableHandles;

    GeRtiFactory::GeRtiHandle managerFederateServiceFlushQueueRequest;
      GeRtiFactory::GeRtiHandle managerFederateServiceFlushQueueRequestTimeStamp;
    GERTICO::MomFederationTimeHandles  momFlushQueueRequestHandles;
#else
    GeRtiFactory::GeRtiHandle managerFederateServiceNextEventRequest;
      GeRtiFactory::GeRtiHandle managerFederateServiceNextEventRequestFederationTime;
    GERTICO::MomFederationTimeHandles momNextEventRequestHandles;

    GeRtiFactory::GeRtiHandle managerFederateServiceNextEventRequestAvailable;
      GeRtiFactory::GeRtiHandle managerFederateServiceNextEventRequestAvailableFederationTime;
    GERTICO::MomFederationTimeHandles momNextEventRequestAvailableHandles;

    GeRtiFactory::GeRtiHandle managerFederateServiceFlushQueueRequest;
      GeRtiFactory::GeRtiHandle managerFederateServiceFlushQueueRequestFederationTime;
    GERTICO::MomFederationTimeHandles  momFlushQueueRequestHandles;
#endif

#ifdef IEEE_1516
    GeRtiFactory::GeRtiHandle managerFederationAdjustSetSwitches;
#endif

    void testFoundValues(std::wstring const &theMomName, bool const &theFoundItem, bool const &theFoundClass) throw
    (
      GeRtiFactory::ErrorReadingFED
    );

    ManagementObjectModel(GERTICO::DeclarationManagementRTI &theDeclarationManagement, GERTICO::ObjectManagement &theObjectManagement, GERTICO::GeRtiOwnershipMasterI &theGeRtiOwnershipMasterI, GERTICO::SupportingServices &theSupportingServices, EventHandler *theEventHandler, GERTICO::ClassDescrHolder &theInteractionRoot, GERTICO::ClassDescrHolder &theObjectRoot, GERTICO::FederatesHolder &theFederatesHolder, GERTICO::JobHolder &theFederationJobs, ACE_Semaphore &thePs);
    virtual ~ManagementObjectModel(void);

    void discoverManagerFederation(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass);
    void doMomInteraction(GeRtiFactory::GeRtiEvent &theGeRtiEvent);
    void getFederationName(std::wstring &theFederationName);
    void getLastSaveName(std::wstring &theLastSaveName);
    void getMomManagerInteractionRoot(GeRtiFactory::GeRtiHandle &theMomManagerInteractionRoot);
    void getSetServiceReportingParams(bool &theBool, GeRtiFactory::GeRtiEvent &theGeRtiEvent, GeRtiFactory::GeRtiEvent &theUnonwedGeRtiEvent);
    bool isMomClass(const GeRtiFactory::GeRtiHandle &theClass);
    bool isMomFederateClass(const GeRtiFactory::GeRtiHandle &theClass);
    void joinFederationExecutionMom(const GeRtiFactory::GeRtiHandle &theFederate);
    bool requestClassAttributeValueUpdate(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes);
    bool requestObjectAttributeValueUpdate(const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes);
    void resignFederationExecutionMom(const GeRtiFactory::GeRtiHandle &theFederate);
    void setFederationFile(const std::wstring &theFederationFile);
    void setFederationName(const std::wstring &theFederationName);
    void setNextSaveName(const std::wstring &theName);
#ifdef IEEE_1516
    void setNextSaveTime(std::auto_ptr<GERTICO::GeRtiFedTime> &theTime);
#else
    void setNextSaveTime(const std::string &theTime);
#endif
    void wallClockWorker(void);
  };
};

#endif /* ManagementObjectModel_H_  */
