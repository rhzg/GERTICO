/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** OwnershipWorkerThread.h
**
*******************************************************************************/

#ifndef OwnershipWorkerThread_H
#define OwnershipWorkerThread_H

#include <list>
#include <ace/Synch.h>
#include "Util/DataModel.h"
#include "Util/JobHolder.h"
#include "Util/RunTimeObjectDB.h"
#include "idl/GeRtiFactoryC.h"
#include "EventMarket/ObjectManagement.h"

using namespace GeRtiFactory;

namespace GERTICO
{

class ThreadJob: public Job
{
protected:
  class OwnershipWorkerThread* worker;

public:
  GeRtiHandle fed;
  GeRtiHandle object;

  ThreadJob (class OwnershipWorkerThread* aWorker) { worker = aWorker; };
  virtual ~ThreadJob() {};
  virtual JobStatus execute () = 0;
};

//***********
//
class InformAttributOwnership: public virtual ThreadJob
{
public:
  GeRtiHandle attribute;
  GeRtiHandle owner;

  InformAttributOwnership (class OwnershipWorkerThread* aWorker, GeRtiHandle fedId, const GeRtiHandle &theObject, const GeRtiHandle &theAttribute, const GeRtiHandle &theOwner);
  virtual ~InformAttributOwnership() {};
  virtual JobStatus execute();
};

//***********
//
class OwnershipAcquisitionNotification: public virtual ThreadJob
{
public:
  GERTICO::HandleSet attributes;
  GeRtiFactory::UserSuppliedTag tag;

  OwnershipAcquisitionNotification(class OwnershipWorkerThread* aWorker, const GeRtiHandle &fedId, const GeRtiHandle &theObject, const GERTICO::HandleSet &theAttributes, const GeRtiFactory::UserSuppliedTag &theTag);
  virtual ~OwnershipAcquisitionNotification() {};
  virtual JobStatus execute();
};

//***********
//
class AttributeOwnershipAcquisitionCancellation: public virtual ThreadJob
{
public:
  Handles attributes;

  AttributeOwnershipAcquisitionCancellation (class OwnershipWorkerThread* aWorker, GeRtiHandle fedId, GeRtiHandle theObject, const Handles& theAttribute);
  virtual ~AttributeOwnershipAcquisitionCancellation() {};
  virtual JobStatus execute();
};

//***********
//
class RequestDivestitureConfirmationJob: public virtual ThreadJob
{
public:
  AttributeMap attributes;

  RequestDivestitureConfirmationJob (class OwnershipWorkerThread* aWorker, GeRtiHandle theFed, GeRtiHandle theObject, AttributeMap theAttributes);
  virtual ~RequestDivestitureConfirmationJob() {};
  virtual JobStatus execute();
};

//***********
//
class AttributeOwnershipDivestitureNotification: public virtual ThreadJob
{
public:
  AttributeMap attributes;

  AttributeOwnershipDivestitureNotification (class OwnershipWorkerThread* aWorker, GeRtiHandle theFed, GeRtiHandle theObject, AttributeMap theAttributes);
  virtual ~AttributeOwnershipDivestitureNotification() {};
  virtual JobStatus execute();
};

//***********
//
class NegotiatedAttributeOwnershipDivestiture: public virtual ThreadJob
{
public:
  AttributeMap attributes;
  GERTICO::HandleSetMap acquiringFederatesSetMap;
  GeRtiFactory::UserSuppliedTag tag;

  NegotiatedAttributeOwnershipDivestiture (class OwnershipWorkerThread* aWorker, GeRtiHandle theFed, GeRtiHandle theObject, AttributeMap& theAttributes, GERTICO::HandleSetMap& theAcquiringFederatesSetMap, const GeRtiFactory::UserSuppliedTag &theTag);
  virtual ~NegotiatedAttributeOwnershipDivestiture() {};
  virtual JobStatus execute();
};

//***********
//
class AttributeOwnershipRelease: public virtual ThreadJob
{
public:
  GeRtiFactory::UserSuppliedTag tag;
  AttributeMap attributes;

  AttributeOwnershipRelease (class OwnershipWorkerThread* aWorker, GeRtiHandle theFed, GeRtiHandle theObject, AttributeMap theAttributes, const GeRtiFactory::UserSuppliedTag &theTag);
  virtual ~AttributeOwnershipRelease() {};
  virtual JobStatus execute();
};

//***********
//
class RequestAttributeOwnershipAssumptionJob: public virtual ThreadJob
{
public:
  GeRtiFactory::UserSuppliedTag tag;
  AttributeStatus attributeStatus;
  Handles attributes;

  RequestAttributeOwnershipAssumptionJob (class OwnershipWorkerThread* aWorker, GeRtiHandle theFed, GeRtiHandle theObject, const Handles& theAttributes, const GeRtiFactory::UserSuppliedTag &theTag, const AttributeStatus &theNewStatus);
  virtual ~RequestAttributeOwnershipAssumptionJob();
  virtual JobStatus execute();
};

//***********
//
class AttributeOwnershipUnavailable: public virtual ThreadJob
{
public:
  AttributeMap attributes;

  AttributeOwnershipUnavailable (class OwnershipWorkerThread* aWorker, GeRtiHandle theFed, GeRtiHandle theObject, AttributeMap theAttributes);
  virtual ~AttributeOwnershipUnavailable() {};
  virtual JobStatus execute();
};


//****************************************************
//
class OwnershipWorkerThread: public JobHolder
{
  ACE_Semaphore workToDo;
  bool running;
  ACE_thread_t workerId;
  GERTICO::FederatesHolder *federatesHolder;

public:
  GERTICO::ObjectManagement &objectManagement;
  RunTimeObjectDB &runTimeObjectDB;

  OwnershipWorkerThread(RunTimeObjectDB &theRunTimeObjectDB, GERTICO::ObjectManagement &theObjectManagement);

  virtual ~OwnershipWorkerThread ();
  GERTICO::FederatesHolder *getFederatesHolder(void) { return federatesHolder; };
  void setFederatesHolder(GERTICO::FederatesHolder* theFederatesHolder) { federatesHolder = theFederatesHolder; };
  virtual void add (Job* aJob);
  void acquire () { workToDo.acquire(); };
  bool isRunning () { return running; };

  JobStatus executeInformAttributOwnership (InformAttributOwnership *job);
  JobStatus executeAttributeOwnershipRelease (AttributeOwnershipRelease *job);
  JobStatus executeAttributeOwnershipUnavailable (AttributeOwnershipUnavailable *job);
  JobStatus executeOwnershipAcquisitionNotification (OwnershipAcquisitionNotification *job);
  JobStatus executeRequestDivestitureConfirmationJob (RequestDivestitureConfirmationJob *job);
  JobStatus executeAttributeOwnershipAssumption (RequestAttributeOwnershipAssumptionJob *job);
  JobStatus executeAttributeOwnershipDivestitureNotification (AttributeOwnershipDivestitureNotification *job);
  JobStatus executeNegotiatedAttributeOwnershipDivestiture (NegotiatedAttributeOwnershipDivestiture *job);
  JobStatus executeAttributeOwnershipAcquisitionCancellation (AttributeOwnershipAcquisitionCancellation *job);
};

}; // workspace GERTICO


#endif // OwnershipWorkerThread_H

