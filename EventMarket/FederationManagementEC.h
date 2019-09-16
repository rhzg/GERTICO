/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** FederationManagementEC.h
**
*******************************************************************************/

#ifndef FederationManagementEC_H_
#define FederationManagementEC_H_

#include <string>

#include "ace/Thread_Manager.h"

#include "idl/GeRtiFactoryS.h"
#include "Util/Federate.h"
#include "Util/GERTICOconf.h"
#include "Util/GeRtiOrb.h"
#include "EventMarket/Jobs.h"
#include "GeRti/GeRtiOwnershipMasterI.h"

#include "EventMarket/EventHandler.h"
#include "EventMarket/GeRtiEventMarketI.h"

#include "SupportingServicesEC.h"
#include "EventMarket/TimeClient.h"

namespace GERTICO
{
  class TransmissionECArg
  {
  public:
    TransmissionECArg(void);
    virtual ~TransmissionECArg(void);
    ACE_Barrier *barrier;
    EventHandler *eventHandler;
  };

  class FederationManagementEC : public virtual POA_GeRtiFactory::EventHubFederation
  {
    ACE_Barrier *barrier;
    ACE_Semaphore *ps;
    ACE_thread_t tid0;
    ACE_thread_t tid1;
    ACE_thread_t tid2;
    CORBA::Object_var gertiObj;
    DOMElement *domElement;
    GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
    GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
    GERTICO::GeRtiOrb &myGeRtiOrb;
    GERTICO::HandleSet federates;
    GERTICO::TimeClient *timeClient;
    GERTICO::TransmissionECArg transmissionArg;
    const GeRtiFactory::GeRtiHandle &privilegeToDeleteId;
    PortableServer::POA_var myPOAReceiver;
    PortableServer::POA_var myPOAbestEffort;
    PortableServer::POA_var myPoaSender;
    bool active;
    double doublePreviousTime;
    std::string federationState;
    std::wstring federationName;
    std::wstring federationSaveLabel;
    std::wstring myEventHub;
    const GERTICOconf &gerticoConf;

    // Time Management
    GeRti_TimeManagement_i *geRti_TimeManagement_i;
    GeRtiFactory::TimeManagement_var timeManagementVar;

    void clear(void);
    bool parseEnv(char *out, char *in);

  public:
    EventHandler *eventHandler;
    GeRtiFactory_EventChannel_i *eventChannel;
    bool notDone;

    FederationManagementEC(std::wstring const &theEventHub, GERTICO::GeRtiOrb &theGeRtiOrb, PortableServer::POA_ptr thePOAReceiver, PortableServer::POA_ptr thePoaBestEffort, PortableServer::POA_ptr thePoaSender, std::wstring const &theFederationName, std::wstring const &theFedFile, GERTICO::NextHandle &theIdHandler, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, GeRtiFactory::GeRtiHandle const &thePrivilegeToDeleteId);
    virtual ~FederationManagementEC(void);

    bool areFederatesJoined(void);
    void deactivate(void);
    bool isActive(void);
    bool noFederatesJoined(void);
    void processLive(void);
    void resignFed (const GeRtiFactory::GeRtiHandle &theFederate, const std::wstring &theFedType);
    void setAlive(GeRtiFactory::GeRtiHandle const &theHandle);
    void wallClockWorker(void);

    void getEventChannelAdmins(GeRtiFactory::EventChannel_out  eventChannelOut, GeRtiFactory::TimeManagement_out theTimeManagement);
    void makeEventHubChannels(GeRtiFactory::HubEventChannelDataSeq const &theHubConsumerAdminDataSeq);
  };
};

#endif /* FederationManagementEC_H_  */
