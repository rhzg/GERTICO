/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GeRtiFactoryIEC.h
**
*******************************************************************************/

#ifndef GERTIFACTORYIEC_H_
#define GERTIFACTORYIEC_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
//#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <map>
#include <string>

#include "EventMarket/GeRtiEventMarketI.h"
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiOrb.h"
#include "FederationManagementEC.h"

typedef std::map <std::wstring, GERTICO::FederationManagementEC *> FederationManagementECMap;

//Class GeRtiFactory_Factory_i
class  GeRtiFactory_TheEventHubFederationFactoryEC_i : public virtual POA_GeRtiFactory::TheEventHubFederationFactory
{
  GERTICO::GeRtiFedTimeFactory &geRtiFedTimeFactory;
  GERTICO::GeRtiLogicalTimeIntervalFactory &geRtiLogicalTimeIntervalFactory;
  GERTICO::GeRtiOrb &myGeRtiOrb;
  GERTICO::NextHandle idHandler;
  bool createInProgress;
  const GERTICOconf &conf;
  std::wstring myEventHub;

  void doEventHubCreateFederation(CORBA::WChar const *fedNameWstring);

public:
  static ACE_Thread_Mutex spm;
  //Constructor
  GeRtiFactory_TheEventHubFederationFactoryEC_i(std::wstring const &theHubName, GERTICO::GeRtiOrb &theGeRtiOrb, GERTICOconf const &theGERTICOconf, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory);

  //Destructor
  virtual ~GeRtiFactory_TheEventHubFederationFactoryEC_i(void);

  static FederationManagementECMap federationManagementECs;

  virtual void createFederationExecution
  (
    CORBA::WChar const *fedName,
    GeRtiFactory::GeRtiHandle momInteractionRoot,
    GeRtiFactory::GeRtiHandle momObjectRoot,
    GeRtiFactory::GeRtiHandle interactionRoot,
    GeRtiFactory::GeRtiHandle objectRoot,
    GeRtiFactory::GeRtiHandle privilegeToDeleteId,
    GeRtiFactory::EventHubFederation_out theEventHubFederation,
    GeRtiFactory::EventChannel_out theEventChannelReference
  )
  throw
  (
    GeRtiFactory::FederationExecutionAlreadyExists,
    GeRtiFactory::RTIinternalError,
    CORBA::SystemException
  );

  virtual void destroyFederationExecution(
    CORBA::WChar const *fedName);
};

#endif /* GERTIFACTORYIEC_H_  */
