/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GeRtiFactoryI.h
**
*******************************************************************************/

#ifndef GERTIFACTORYI_H_
#define GERTIFACTORYI_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
//#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <map>
#include <string>

#include "GeRtiAmbassadorI.h"
#include "EventMarket/GeRtiFactoryECI.h"
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiOrb.h"
#include "FederationManagement.h"

//Class GeRtiFactory_FederationManagement_i
class  GeRtiFactory_FederationManagement_i : public virtual POA_GeRtiFactory::FederationManagement
{
  ACE_Thread_Mutex pm;
  ACE_thread_t tid0;
  ACE_thread_t tid2;
  FederatesMap federates;
  FederatesMap federatesDeleted;
  GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
  GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
  GERTICO::GeRtiOrb &myGeRtiOrb;
  GERTICO::NextHandle idHandler;
  PortableServer::POA_var myPOA;
  PortableServer::POA_var myPoaBestEffort;
  PortableServer::POA_var myPoaSender;
  PortableServer::POAManager_var myPoaBestEffortMgr;
  PortableServer::POAManager_var myPoaReceiverMgr;
  PortableServer::POAManager_var myPoaSenderMgr;
  PortableServer::POAManager_var nilMgr;
  bool active;
  std::wstring myName;

public:
  GeRtiFactory::FederationManagement_var FederationManagementVar;
  GERTICO::FederationManagement *federationManagement;

  //Constructor
  GeRtiFactory_FederationManagement_i(GERTICO::GeRtiOrb &theGeRtiOrb, std::wstring const &theFedName, std::wstring const &theFedFile, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory);

  //Destructor
  virtual ~GeRtiFactory_FederationManagement_i (void);

  // These two functions make it easy to activate/deactivate the CORBA object
  void activateObject(void);
  void deactivateObject(void);
  void doEventHubDestroyFederation(const CORBA::WChar *fedNameWstring);

  void garbageCollection(void);
  void getEventHubCreateData(CORBA::ULong &theMomInteractionRoot, CORBA::ULong &theMomObjectRoot, CORBA::ULong &theInteractionRoot, CORBA::ULong &theObjectRoot, CORBA::ULong &thePrivilegeToDeleteId);

  bool isActive(void);

  PortableServer::POA_ptr _default_POA (void);

  void Term (void);

  virtual GeRtiFactory::GeRtiHandle joinFederationExecution (
    const CORBA::WChar *federateType,
    const CORBA::WChar *eventHubName,
    GeRtiFactory::FederateAmbassador_ptr federateAmbassadorReference,
    GeRtiFactory::GeRtiRestore_ptr geRtiRestoreReference,
    GeRtiFactory::EventHubFederation_out myEventHubFederation
  )
  throw (
    GeRtiFactory::FederateAlreadyExecutionMember,
    GeRtiFactory::FederationExecutionDoesNotExist,
    GeRtiFactory::CouldNotOpenFED,
    GeRtiFactory::ErrorReadingFED,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    CORBA::SystemException
  );

  virtual void getMom (
    GeRtiFactory::Handles_out momHandles
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ErrorReadingFED
  );

  virtual void joinFederationExecutionFinished (
      GeRtiFactory::GeRtiHandle federate
    )
    throw (
      CORBA::SystemException
    );

virtual GeRtiFactory::GeRtiAmbassador_ptr getGeRtiAmbassador (
    GeRtiFactory::GeRtiHandle theHandle
  )
  throw (
    CORBA::SystemException
  );

  virtual void resignFederationExecution (
    GeRtiFactory::ResignAction resignAction,
    GeRtiFactory::GeRtiHandle federate
  )
  throw (
    GeRtiFactory::FederateOwnsAttributes,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::InvalidResignAction,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::RTIinternalError,
    CORBA::SystemException
  );

  virtual void destroyFederationExecution
  (
    const CORBA::WChar *fedName
  )
  throw
  (
    CORBA::SystemException,
    GeRtiFactory::FederationExecutionDoesNotExist,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::FederatesCurrentlyJoined,
    GeRtiFactory::RTIinternalError
  );

  virtual void terminate (
  )
  throw (
    CORBA::SystemException
  );
};

typedef std::map <std::wstring, GeRtiFactory_FederationManagement_i *> FederationManagementMap;

class HubFederationReferences
{
public:
  GeRtiFactory::EventHubFederation_var eventHubFederationVar;
  GeRtiFactory::EventChannel_var eventChannelVar;
};

// Key is federation name.
typedef std::map <std::wstring, HubFederationReferences *> FederationReferencesMap;

class HubReferences
{
public:
  GeRtiFactory::TheEventHubFederationFactory_ptr theEventHubFederationFactoryPtr;
  FederationReferencesMap federationReferencesMap;
};

typedef std::map <std::wstring, HubReferences *> EventHubMap;

//Class GeRtiFactory_Factory_i
class  GeRtiFactory_Factory_i : public virtual POA_GeRtiFactory::TheFactory
{
  CosNaming::NamingContext_var myNamingContext;
  GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
  GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
  GERTICO::GeRtiOrb &myGeRtiOrb;
  GeRtiFactory_TheEventHubFederationFactoryEC_i *theEventHubFederationFactory;
  GeRtiFactory::TheEventHubFederationFactory_var theEventHubFederationFactoryVar;
  bool createInProgress;
  const GERTICOconf &conf;
  std::wstring myEventHub;

  void allocFederation(std::wstring const &theFedName, std::wstring const &theFedFile);
  void doEventHubCreateFederation(std::wstring const &fedNameWstring);

public:
  static ACE_Thread_Mutex spm;
  //Constructor
  GeRtiFactory_Factory_i(GERTICO::GeRtiOrb &theGeRtiOrb, CosNaming::NamingContext_var &namingContext, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory);

  //Destructor
  virtual ~GeRtiFactory_Factory_i (void);

  static FederationManagementMap fedMan;
  static EventHubMap eventHubs;

virtual void createFederationExecution
(
  const CORBA::WChar *fedName,
  const CORBA::WChar *fedFile
)
throw
(
  GeRtiFactory::FederationExecutionAlreadyExists,
  GeRtiFactory::CouldNotOpenFED,
  GeRtiFactory::ErrorReadingFED,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError,
  CORBA::SystemException
);

virtual ::GeRtiFactory::FederationManagement_ptr getFederationManagement (
  const CORBA::WChar *fedName
)
throw (
  CORBA::SystemException,
  GeRtiFactory::FederationExecutionDoesNotExist,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError
);

virtual void registerEventHubFactory (
  const CORBA::WChar * hubName,
  GeRtiFactory::TheEventHubFederationFactory_ptr geRtiEventHubFederationFactory
)
throw (
  CORBA::SystemException,
  GeRtiFactory::EventHubAlreadyExists,
  GeRtiFactory::RTIinternalError
);
};

#endif /* GERTIFACTORYI_H_  */
