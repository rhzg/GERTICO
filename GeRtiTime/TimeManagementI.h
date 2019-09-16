/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** TimeManagementI.h
**
*******************************************************************************/

#ifndef TIMEMANAGEMENTI_H_
#define TIMEMANAGEMENTI_H_

#include <map>
#include "GeRtiTime/TimeService.h"
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiOrb.h"
#include "Util/GeRtiTypes.h"

#include "ace/Synch.h"

class GeRti_TimeManagement_i : public virtual POA_GeRtiFactory::TimeManagement
{
  GERTICO::GeRtiFedTimeFactory *geRtiFedTimeFactory;
  GERTICO::GeRtiLogicalTimeIntervalFactory *geRtiLogicalTimeIntervalFactory;
  GERTICO::TimeService &timeService;
  PortableServer::POA_var myPOA;

public:

  //Constructor
  GeRti_TimeManagement_i(PortableServer::POA_ptr thePOA, GERTICO::TimeService &theTimeService, GERTICO::GeRtiFedTimeFactory *theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory *theGeRtiLogicalTimeIntervalFactory);

  //Destructor
  virtual ~GeRti_TimeManagement_i(void);

  PortableServer::POA_ptr _default_POA(void);

  virtual void disableTimeRegulation (
    GeRtiFactory::GeRtiHandle theFederate)
    throw (
      CORBA::SystemException,
      GeRtiFactory::TimeRegulationIsNotEnabled,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError
    );

  virtual void disableTimeConstrained (
    GeRtiFactory::GeRtiHandle theFederate)
    throw (
      CORBA::SystemException,
      GeRtiFactory::TimeConstrainedWasNotEnabled,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError,
      GeRtiFactory::ConcurrentAccessAttempted
    );

  virtual void queryGALT (
    GeRtiFactory::GeRtiHandle theFederate,
    GeRtiFactory::Time_out theTime
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError
    );

  virtual void queryLITS (
    GeRtiFactory::GeRtiHandle theFederate,
    GeRtiFactory::Time_out theTime
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError
    );

  virtual void queryLookahead (
    GeRtiFactory::GeRtiHandle theFederate,
    GeRtiFactory::Time_out theTime
    )
    throw (
      CORBA::SystemException,
      GeRtiFactory::FederateNotExecutionMember,
      GeRtiFactory::SaveInProgress,
      GeRtiFactory::RestoreInProgress,
      GeRtiFactory::RTIinternalError
    );
};

#endif /* TIMEMANAGEMENTI_H_  */
