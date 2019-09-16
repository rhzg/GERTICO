/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** OwnershipWorkerThread.cpp
**
*******************************************************************************/

#include "OwnershipWorkerThread.h"
#include "ace/Thread_Manager.h"
#include "Util/Mapper.h"

using namespace GERTICO;

/*********************************** Gal begin ***************************************/

#ifdef GalDebug

#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

static class Repository_l *OWM=(Repository::getSingleInstance())->getRepository_l("GeRtiOWM.res","GeRtiOWM");

static class Event *GeRti_OWM_d=OWM->getRefEvent("GeRti_OWM_d");
static class Event *GeRti_OWM_e=OWM->getRefEvent("GeRti_OWM_e");
static class Event *GeRti_OWM_i=OWM->getRefEvent("GeRti_OWM_i");
static class Event *GeRti_OWM_w=OWM->getRefEvent("GeRti_OWM_w");

#endif

/*********************************** Gal end  ***************************************/

//***********************************************
//
InformAttributOwnership::InformAttributOwnership (
   OwnershipWorkerThread* aWorker,
   GeRtiHandle fedId,
   const GeRtiHandle &theObject,
   const GeRtiHandle &theAttribute,
   const GeRtiHandle &theOwner) : ThreadJob (aWorker)
{
  fed = fedId;
  object = theObject;
  attribute = theAttribute;
  owner = theOwner;
};

//***********************************************
//
JobStatus InformAttributOwnership::execute ()
{
#ifdef GalDebug
                             E2(GeRti_OWM_d, "InformAttributOwnership::execute", "enter");
#endif

  return worker->executeInformAttributOwnership (this);

#ifdef GalDebug
                             E2(GeRti_OWM_d, "InformAttributOwnership::execute", "leave");
#endif
};

//***********************************************
//
AttributeOwnershipRelease::AttributeOwnershipRelease (
   OwnershipWorkerThread* aWorker,
   GeRtiHandle fedId,
   GeRtiHandle theObject,
   AttributeMap theAttributes,
   const GeRtiFactory::UserSuppliedTag &theTag) : ThreadJob (aWorker), attributes(theAttributes)
{
  fed = fedId;
  object = theObject;
  tag = theTag;
};

//***********************************************
//
JobStatus AttributeOwnershipRelease::execute ()
{
#ifdef GalDebug
                             E2(GeRti_OWM_d, "AttributeOwnershipRelease::execute", "enter");
#endif

  return worker->executeAttributeOwnershipRelease (this);

#ifdef GalDebug
                             E2(GeRti_OWM_d, "AttributeOwnershipRelease::execute", "leave");
#endif
};


//***********************************************
//
RequestAttributeOwnershipAssumptionJob::RequestAttributeOwnershipAssumptionJob (
   OwnershipWorkerThread* aWorker,
   GeRtiHandle fedId,
   GeRtiHandle theObject,
   const Handles& theAttributes,
   const GeRtiFactory::UserSuppliedTag &theTag,
   const AttributeStatus &theNewStatus) : ThreadJob (aWorker), attributes(theAttributes)
{
  attributeStatus = theNewStatus;
  fed = fedId;
  object = theObject;
  tag = theTag;
};

//***********************************************
//
RequestAttributeOwnershipAssumptionJob::~RequestAttributeOwnershipAssumptionJob()
{
}

//***********************************************
//
JobStatus RequestAttributeOwnershipAssumptionJob::execute ()
{
#ifdef GalDebug
                             E2(GeRti_OWM_d, "RequestAttributeOwnershipAssumptionJob::execute", "enter");
#endif

  return worker->executeAttributeOwnershipAssumption (this);

#ifdef GalDebug
                             E2(GeRti_OWM_d, "RequestAttributeOwnershipAssumptionJob::execute", "leave");
#endif
};



//***********************************************
//
RequestDivestitureConfirmationJob::RequestDivestitureConfirmationJob (
   OwnershipWorkerThread* aWorker,
   GeRtiHandle fedId,
   GeRtiHandle theObject,
   AttributeMap theAttributes) : ThreadJob (aWorker), attributes(theAttributes)
{
  fed = fedId;
  object = theObject;
};

//***********************************************
//
JobStatus RequestDivestitureConfirmationJob::execute ()
{
#ifdef GalDebug
                             E2(GeRti_OWM_d, "RequestDivestitureConfirmationJob::execute", "enterLeave");
#endif

  return worker->executeRequestDivestitureConfirmationJob (this);
};

//***********************************************
//
AttributeOwnershipDivestitureNotification::AttributeOwnershipDivestitureNotification (
   OwnershipWorkerThread* aWorker,
   GeRtiHandle fedId,
   GeRtiHandle theObject,
   AttributeMap theAttributes) : ThreadJob (aWorker), attributes(theAttributes)
{
  fed = fedId;
  object = theObject;
};

//***********************************************
//
JobStatus AttributeOwnershipDivestitureNotification::execute ()
{
#ifdef GalDebug
                             E2(GeRti_OWM_d, "AttributeOwnershipDivestitureNotification::execute", "enter");
#endif

  return worker->executeAttributeOwnershipDivestitureNotification (this);

#ifdef GalDebug
                             E2(GeRti_OWM_d, "AttributeOwnershipDivestitureNotification::execute", "leave");
#endif
};


//***********************************************
//
NegotiatedAttributeOwnershipDivestiture::NegotiatedAttributeOwnershipDivestiture (
   OwnershipWorkerThread* aWorker,
   GeRtiHandle fedId,
   GeRtiHandle theObject,
   AttributeMap& theAttributes,
   GERTICO::HandleSetMap& theAcquiringFederatesSetMap,
   const GeRtiFactory::UserSuppliedTag &theTag) : ThreadJob (aWorker), attributes(theAttributes), acquiringFederatesSetMap(theAcquiringFederatesSetMap)
{
  fed = fedId;
  object = theObject;
  tag = theTag;
};

//***********************************************
//
JobStatus NegotiatedAttributeOwnershipDivestiture::execute ()
{
#ifdef GalDebug
                             E2(GeRti_OWM_d, "NegotiatedAttributeOwnershipDivestiture::execute", "enter");
#endif

  return worker->executeNegotiatedAttributeOwnershipDivestiture (this);

#ifdef GalDebug
                             E2(GeRti_OWM_d, "NegotiatedAttributeOwnershipDivestiture::execute", "leave");
#endif
};


//***********************************************
//
AttributeOwnershipAcquisitionCancellation::AttributeOwnershipAcquisitionCancellation (
   OwnershipWorkerThread* aWorker,
   GeRtiHandle fedId,
   GeRtiHandle theObject,
   const Handles& theAttributes
  ) : ThreadJob (aWorker), attributes(theAttributes)
{
  fed = fedId;
  object = theObject;
};

//***********************************************
//
JobStatus AttributeOwnershipAcquisitionCancellation::execute ()
{
#ifdef GalDebug
                             E2(GeRti_OWM_d, "AttributeOwnershipAcquisitionCancellation::execute", "enter");
#endif

  return worker->executeAttributeOwnershipAcquisitionCancellation (this);

#ifdef GalDebug
                             E2(GeRti_OWM_d, "AttributeOwnershipAcquisitionCancellation::execute", "leave");
#endif
};


//***********************************************
//
AttributeOwnershipUnavailable::AttributeOwnershipUnavailable (
   OwnershipWorkerThread* aWorker,
   GeRtiHandle fedId,
   GeRtiHandle theObject,
   AttributeMap theAttributes) : ThreadJob (aWorker), attributes(theAttributes)
{
  fed = fedId;
  object = theObject;
};

//***********************************************
//
JobStatus AttributeOwnershipUnavailable::execute ()
{
#ifdef GalDebug
                             E2(GeRti_OWM_d, "AttributeOwnershipUnavailable::execute", "enter");
#endif

  return worker->executeAttributeOwnershipUnavailable (this);

#ifdef GalDebug
                             E2(GeRti_OWM_d, "AttributeOwnershipUnavailable::execute", "leave");
#endif
};


//***********************************************
//
OwnershipAcquisitionNotification::OwnershipAcquisitionNotification (
   OwnershipWorkerThread* aWorker,
   const GeRtiHandle &fedId,
   const GeRtiHandle &theObject,
   const GERTICO::HandleSet &theAttributes,
   const GeRtiFactory::UserSuppliedTag &theTag
   ) : ThreadJob (aWorker), attributes(theAttributes)
{
  fed = fedId;
  object = theObject;
  tag = theTag;
};

//***********************************************
//
JobStatus OwnershipAcquisitionNotification::execute ()
{
#ifdef GalDebug
                             E2(GeRti_OWM_d, "OwnershipAcquisitionNotification::execute", "enter");
#endif

  return worker->executeOwnershipAcquisitionNotification (this);

#ifdef GalDebug
                             E2(GeRti_OWM_d, "OwnershipAcquisitionNotification::execute", "leave");
#endif
};



//***********************************************
//
void ownership_worker (void *arg)
{
  bool ret;

  OwnershipWorkerThread *theWorkerData = (OwnershipWorkerThread*) arg;
  while (theWorkerData->isRunning())
  {
    theWorkerData->acquire();
    ret = theWorkerData->performJobs(true);
  }
}


//***********************************************
//
OwnershipWorkerThread::OwnershipWorkerThread(
  RunTimeObjectDB &theRunTimeObjectDB,
  GERTICO::ObjectManagement &theObjectManagement
) : workToDo (0), runTimeObjectDB(theRunTimeObjectDB), objectManagement(theObjectManagement)
{
  running = true;
  workerId = ACE_Thread_Manager::instance()->spawn (ACE_reinterpret_cast (ACE_THR_FUNC, &ownership_worker), this);
};

//***********************************************
//
OwnershipWorkerThread::~OwnershipWorkerThread ()
{
  running = false;
  workToDo.release();

  JobHolder::clear ();
  ACE_Thread_Manager::instance()->wait_grp (workerId);
};


//***********************************************
//
void OwnershipWorkerThread::add (Job* aJob)
{
  JobHolder::add (aJob);
  workToDo.release();
}


//***********************************************
//
JobStatus OwnershipWorkerThread::executeInformAttributOwnership (InformAttributOwnership* job)
{
  GERTICO::Federate *federate;
#ifdef GalDebug
  char galMsg[512];
#endif
  
  federate = federatesHolder->getFederate(job->fed);

  if (federate == NULL)
  {
#ifdef GalDebug
                             E2(GeRti_OWM_d, "OwnershipWorkerThread::executeInformAttributOwnership", "ClientNotRegistered");
#endif
  }
  else
  {
    try
    {
      switch (job->owner)
      {
      case 0:
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = job->object;
                              ul1 = job->attribute;
                              sprintf(galMsg,"OwnershipWorkerThread::executeInformAttributOwnership(object=%lu,attribute=%lu) enter", ul, ul1);
                              E1mEnd(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

        federate->attributeIsNotOwned(job->object, job->attribute);
        break;
      case 1:
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = job->object;
                              ul1 = job->attribute;
                              sprintf(galMsg,"OwnershipWorkerThread::executeInformAttributOwnership(object=%lu,attribute=%lu) enter", ul, ul1);
                              E1mEnd(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

        federate->attributeOwnedByRTI(job->object, job->attribute);
        break;
      default:
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;
                              unsigned long ul1;
                              unsigned long ul2;

                              ul = job->object;
                              ul1 = job->attribute;
                              ul2 = job->owner;
                              sprintf(galMsg,"OwnershipWorkerThread::executeInformAttributOwnership(object=%lu,attribute=%lu,owner=%lu) enter", ul, ul1, ul2);
                              E1mEnd(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

        federate->informAttributeOwnership(job->object, job->attribute, job->owner);
      }
    }
    catch (CORBA::SystemException &sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception in informAttributeOwnership");
    }
    catch(...)
    {
    }
  }

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "OwnershipWorkerThread::executeInformAttributOwnership", "leave");   // inserted by Gal converter
                            }
#endif

  return done;
}

//***********************************************
//
JobStatus OwnershipWorkerThread::executeAttributeOwnershipRelease (AttributeOwnershipRelease* job)
{
  // iterate through all registered clients...
  Handles releaseAttributes;
  unsigned int length = 0;
  GERTICO::Federate *federate;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itFederate;
#ifdef GalDebug
  char galMsg[512];
#endif

  federatesHolder->getFederates(federates);
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    length = 0;
    releaseAttributes.length (length);
    federate = federatesHolder->getFederate(*itFederate);
    // ... go through attributes to be released ...
    for (AttributeMap::iterator iA = job->attributes.begin();
         iA != job->attributes.end();
     iA++)
    {
      // ... and collect all attributes owned by iterated federate
      if (iA->second->getFederate () == federate->getId())
      {
        if (iA->second->getStatus() == acquiring)
        {
          iA->second->setStatusAcquired();
        }
        iA->second->setRequested();
        releaseAttributes.length (++length);
        releaseAttributes[length-1] = iA->first;
      }
    }
    // if attributes found to be release, send message
    if (releaseAttributes.length() > 0) try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = job->object;
                              sprintf(galMsg,"OwnershipWorkerThread::executeAttributeOwnershipRelease(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], releaseAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], job->tag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

      federate->requestAttributeOwnershipRelease (job->object,releaseAttributes,job->tag);
    }
    catch (CORBA::SystemException &)
    {
      // if CORBA failure assume that server is dead,
      // and emulate release response
      GERTICO::HandleSet handleSet;
      // iterate all release attributes...
      for (unsigned int i=0; i<releaseAttributes.length(); i++)
      {
        handleSet.insert(releaseAttributes[i]);
  // ... and generate Acquisition Notification Job
        add(new OwnershipAcquisitionNotification(this, job->fed, job->object, handleSet, job->tag));
      }
    }
  }

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "OwnershipWorkerThread::executeAttributeOwnershipRelease", "leave");   // inserted by Gal converter
                            }
#endif

  return done;
}

//***********************************************
//
JobStatus OwnershipWorkerThread::executeAttributeOwnershipUnavailable (AttributeOwnershipUnavailable* job)
{
  CORBA::ULong length;
  GERTICO::Federate *federate;
  Handles attr;
  GeRtiHandle index = 0;
#ifdef GalDebug
  char galMsg[512];
#endif
  size_t size;

  size = job->attributes.size();
  GERTICO::Mapper::mapULongSizet(length, size);
  attr.length(length);
  for (AttributeMap::iterator iA = job->attributes.begin();
       iA != job->attributes.end();
       iA++, index++)
  {
    attr[index] = iA->first;
  }

  federate = federatesHolder->getFederate(job->fed);
  if (federate != NULL)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = job->object;
                              sprintf(galMsg,"OwnershipWorkerThread::executeAttributeOwnershipUnavailable(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], attr);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

    federate->attributeOwnershipUnavailable (job->object, attr);
  }

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "OwnershipWorkerThread::executeAttributeOwnershipUnavailable", "leave");   // inserted by Gal converter
                            }
#endif

  return done;
}

//***********************************************
//
JobStatus OwnershipWorkerThread::executeRequestDivestitureConfirmationJob (RequestDivestitureConfirmationJob* job)
{
  CORBA::ULong length;
  GERTICO::Federate *federate;
  Handles attr;
  GeRtiHandle index = 0;
#ifdef GalDebug
  char galMsg[512];
#endif
  size_t size;

  size = job->attributes.size();
  GERTICO::Mapper::mapULongSizet(length, size);
  attr.length(length);
  for (AttributeMap::iterator iA = job->attributes.begin();
       iA != job->attributes.end();
       iA++, index++)
  {
    attr[index] = iA->first;
  }

  federate = federatesHolder->getFederate(job->fed);
  if (federate != NULL)
  {
    try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = job->object;
                              sprintf(galMsg,"OwnershipWorkerThread::executeRequestDivestitureConfirmationJob(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], attr);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

      federate->requestDivestitureConfirmation (job->object, attr);
    }
    catch(CORBA::SystemException &sysex)
    {
      ACE_PRINT_EXCEPTION(sysex, "requestDivestitureConfirmation");
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      std::cout << "executeRequestDivestitureConfirmationJob ObjectNotKnown" << std::endl;
    }
    catch(GeRtiFactory::AttributeNotKnown &)
    {
      std::cout << "executeRequestDivestitureConfirmationJob AttributeNotKnown" << std::endl;
    }
    catch(GeRtiFactory::AttributeNotOwned &)
    {
      std::cout << "executeRequestDivestitureConfirmationJob AttributeNotOwned" << std::endl;
    }
    catch(GeRtiFactory::AttributeDivestitureWasNotRequested &)
    {
      std::cout << "executeRequestDivestitureConfirmationJob AttributeDivestitureWasNotRequested" << std::endl;
    }
    catch(GeRtiFactory::FederateInternalError &)
    {
      std::cout << "executeRequestDivestitureConfirmationJob FederateInternalError" << std::endl;
    }
  }

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "OwnershipWorkerThread::executeRequestDivestitureConfirmationJob", "leave");   // inserted by Gal converter
                            }
#endif

  return done;
}

//***********************************************
//
JobStatus OwnershipWorkerThread::executeAttributeOwnershipAssumption (RequestAttributeOwnershipAssumptionJob* job)
{
  CORBA::ULong len;
  CORBA::ULong oAlen;
  GERTICO::Federate *federate;
  GeRtiFactory::GeRtiHandle knownClass;
  GERTICO::HandleSet federates;
  GERTICO::HandleSet::iterator itA;
  GERTICO::HandleSet::iterator itFederate;
  GERTICO::FedPubAttributeMap::iterator itAM;
  GERTICO::PubAttributeDB *currAttributeDB;
  PublishedClass* publishedClass;
  GeRtiFactory::GeRtiHandle privilegeToDeleteId = objectManagement.getPrivilegeToDeleteId();
  GeRtiFactory::Handles offeredAttributes;
  GERTICO::RegisteredObject* theObject = objectManagement.getObject(job->object);
#ifdef GalDebug
  char galMsg[512];
#endif
  unsigned int i;

  // mark all offered attributes with desired attribute status
  len = job->attributes.length();
  for (i=0; i<job->attributes.length(); i++)
  {
    GeRtiHandle a = job->attributes[i];
    theObject->getAttribute(a)->setStatusFlag(job->attributeStatus);
    if (job->attributeStatus == unowned)
    {
      // Zero means RTI is owner.
      theObject->getAttribute(a)->setStatusOwned(0);
    }
  }

  federate = federatesHolder->getFederate(job->fed);
  if (federate)
  {
    // The divesting federate should not have any in scope.
    if (job->attributeStatus == unowned)
    {
      if (federate)
      {
        federate->setOutScope(job->object, job->attributes);
      }
    }
  }

  federatesHolder->getFederates(federates);

  // If unowned, notify federates about out of scope.
  if (job->attributeStatus == unowned)
  {
    for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
    {
      if (job->fed != *itFederate)
      {
        federate = federatesHolder->getFederate(*itFederate);
        if (federate)
        {
          GERTICO::HandleSet items;

          // Get known class
          try
          {
            knownClass = federate->getObjectClass(job->object);
          }
          catch(GeRtiFactory::ObjectNotKnown &)
          {
            continue;
          }
          for (i = 0; i < len; i++)
          {
            items.insert(job->attributes[i]);
          }
          federate->attributesOutOfScope(job->object, items);
          federate->attributesOutOfScopeRemote(job->object, items, true);
        }
      }
    }
  }

  // Find federates publishing the object class.
  for (itFederate = federates.begin(); itFederate != federates.end(); itFederate++)
  {
    // Do not take divesting federate
    if (job->fed == *itFederate)
    {
      continue;
    }

    federate = federatesHolder->getFederate(*itFederate);
    if (federate == NULL)
    {
      continue;
    }

    // Get known class
    try
    {
      knownClass = federate->getObjectClass(job->object);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      continue;
    }

    // Get the publish information for the known class
    publishedClass = runTimeObjectDB.getPublishedClass(knownClass);
    if (publishedClass == NULL)
    {
      continue;
    }
    itAM = publishedClass->fedPubAttributeMap.find(*itFederate);
    if (itAM != publishedClass->fedPubAttributeMap.end())
    {
      currAttributeDB = &itAM->second;
      oAlen = 0;
      offeredAttributes.length(oAlen);

      // send assumption only for published attributes
      len = job->attributes.length();
      for (unsigned int i=0; i < len; i++)
      {
        GeRtiHandle a = job->attributes[i];
        if (a == privilegeToDeleteId)
        {
          offeredAttributes.length(oAlen + 1);
          offeredAttributes[oAlen] = a;
          oAlen += 1;
          continue;
        }

        itA = currAttributeDB->attributeSet.find(a);
        if (itA != currAttributeDB->attributeSet.end())
        {
          offeredAttributes.length(oAlen + 1);
          offeredAttributes[oAlen] = a;
          oAlen += 1;
        }
      }

      // At least one common attribute found.
      if (oAlen)
      {
        GERTICO::Federate *federateAM;
        federateAM = federate = federatesHolder->getFederate(itAM->first);
        if (federateAM != NULL)
        {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = job->object;
                              sprintf(galMsg,"OwnershipWorkerThread::executeAttributeOwnershipAssumption(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], offeredAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], job->tag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

          federateAM->requestAttributeOwnershipAssumption(job->object, offeredAttributes, job->tag);
        }
      }
    }
  }

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "OwnershipWorkerThread::executeAttributeOwnershipAssumption", "leave");   // inserted by Gal converter
                            }
#endif

  return done;
}

//***********************************************
//
JobStatus OwnershipWorkerThread::executeOwnershipAcquisitionNotification (OwnershipAcquisitionNotification* job)
{
  CORBA::ULong length;
  GERTICO::Federate *federate;
  GERTICO::HandleSet regions;
  GERTICO::HandleSet::iterator iA;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::RegisteredObject *registeredObject;
#ifdef GalDebug
  char galMsg[512];
#endif
  size_t size;

  federate = federatesHolder->getFederate(job->fed);
  if (federate == NULL)
  {
#ifdef GalDebug
                             E2(GeRti_OWM_d, "OwnershipWorkerThread::executeOwnershipAcquisitionNotification", "ClientNotRegistered");
#endif
  }
  else
  {
    Handles h;
    size = job->attributes.size();
    GERTICO::Mapper::mapULongSizet(length, size);
    h.length(length);
    unsigned int i=0;
    unsigned long ul=0;
    try
    {
      registeredObject = objectManagement.getObject(job->object);
    }
    catch(GeRtiFactory::ObjectNotKnown &)
    {
      // Internal error.
      return done;
    }
    if (federate)
    {
      for (iA = job->attributes.begin(); iA != job->attributes.end(); iA++, i++)
      {
        h[i] = *iA;
        ul = *iA;
        ul = job->object;
        AttributeInfo* info = registeredObject->getAttribute(*iA);
        if (info->getStatus() == owned) continue; // this attribute has already been assigned
        info->setStatusOwned(job->fed);
        // myWorkerThread.runTimeObjectDB.setAttributesToOwned (fedId, theObject, ownedAttributes);
        federate->getObjectAttributeRegions(job->object, *iA, regions);
        for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
        {
          info->associateRegion(job->fed, *itRegion);
          federate->unassociateAttributeRegionForUpdates(job->object, *iA, *itRegion);
        }
      }
    }

    try
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = job->object;
                              sprintf(galMsg,"OwnershipWorkerThread::executeOwnershipAcquisitionNotification(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], h);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], job->tag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

      federate->attributeOwnershipAcquisitionNotification(job->object, h, job->tag);
    }
    catch (GeRtiFactory::ObjectNotKnown &)
    {
        std::cout << "ObjectNotKnown not known: " << std::endl;
    }
    catch (GeRtiFactory::AttributeNotKnown &)
    {
        std::cout << "Attribute not known: " << std::endl;
    }
    catch (GeRtiFactory::AttributeAcquisitionWasNotRequested &)
    {
        std::cout << "Attribute Acquisition Was Not Requested: " << std::endl;
    }
    catch (GeRtiFactory::AttributeAlreadyOwned &)
    {
        std::cout << "Attribute Already Owned: " << std::endl;
    }
    catch (GeRtiFactory::AttributeNotPublished &)
    {
        std::cout << "Attribute Not Published: " << std::endl;
    }
    catch (GeRtiFactory::FederateInternalError &)
    {
        std::cout << "Federate Internal Error: " << std::endl;
    }
    catch (CORBA::SystemException &sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception in attributeOwnershipAcquisitionNotification");
    }

    objectManagement.doOwnershipAcquisitionNotification(job->fed, *registeredObject, job->attributes, false);
  }

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "OwnershipWorkerThread::executeOwnershipAcquisitionNotification", "leave");   // inserted by Gal converter
                            }
#endif

  return done;
}

//***********************************************
//
JobStatus OwnershipWorkerThread::executeAttributeOwnershipDivestitureNotification (AttributeOwnershipDivestitureNotification* job)
{

  typedef std::map <GeRtiFactory::GeRtiHandle, GeRtiFactory::Handles> FedAttributes;
  GERTICO::Federate *federate;
  FedAttributes fA ;
  FedAttributes::iterator ifA;
  GeRtiFactory::Handles h;
#ifdef GalDebug
  char galMsg[512];
#endif

  // sort all attributes to owning federates
  for (AttributeMap::iterator iA = job->attributes.begin();
       iA != job->attributes.end();
       iA++)
  {
    AttributeInfo* info = objectManagement.getObject(job->object)->getAttribute(iA->first);

    ifA = fA.find(info->getFederate ());
    if (ifA == fA.end())
    {
       h.length(1);
       h[0] = iA->first;
       fA[info->getFederate()] = h;
    }
    else
    {
       GeRtiFactory::Handles *h;
       h = &(ifA->second);
       h->length(h->length()+1);
       (*h)[h->length()-1] = iA->first;
    }
  };

  // inform owning federates about divesting notifications
  for (ifA = fA.begin(); ifA != fA.end(); ifA++)
  {
    federate = federatesHolder->getFederate(ifA->first);
    if (federate != NULL)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = job->object;
                              sprintf(galMsg,"OwnershipWorkerThread::executeAttributeOwnershipDivestitureNotification(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], ifA->second);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

#ifdef IEEE_1516
      federate->requestDivestitureConfirmation(job->object, ifA->second);
#else
      federate->attributeOwnershipDivestitureNotification(job->object, ifA->second);
#endif
    }
  }

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "OwnershipWorkerThread::executeAttributeOwnershipDivestitureNotification", "leave");   // inserted by Gal converter
                            }
#endif

  return done;
}

//***********************************************
//
JobStatus OwnershipWorkerThread::executeNegotiatedAttributeOwnershipDivestiture (NegotiatedAttributeOwnershipDivestiture* job)
{
  CORBA::ULong i;
  CORBA::ULong length;
  GERTICO::Federate *federate;
  GERTICO::HandleSetMap::iterator itAFSM;
  GERTICO::HandleSet::iterator iA;
  GERTICO::HandleSet::iterator itRegion;
  GERTICO::HandleSet regions;
  GERTICO::RegisteredObject *registeredObject;
#ifdef GalDebug
  char galMsg[512];
#endif
  size_t size;

  // For each federate send all relevant attributes in one call.
  for (itAFSM = job->acquiringFederatesSetMap.begin(); itAFSM != job->acquiringFederatesSetMap.end(); itAFSM++)
  {
    federate = federatesHolder->getFederate(itAFSM->first);

    if (federate != NULL)
    {
      Handles h;
      size = itAFSM->second.size();
      GERTICO::Mapper::mapULongSizet(length, size);
      h.length(length);
      i=0;
      for (iA = itAFSM->second.begin(); iA != itAFSM->second.end(); iA++, i++)
      {
        h[i] = *iA;
      }
      try
      {
        registeredObject = objectManagement.getObject(job->object);
      }
      catch(GeRtiFactory::ObjectNotKnown &)
      {
        // Internal error.
        continue;
      }
      try
      {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = job->object;
                              sprintf(galMsg,"OwnershipWorkerThread::executeNegotiatedAttributeOwnershipDivestiture(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], h);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], job->tag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

        federate->attributeOwnershipAcquisitionNotification(job->object, h, job->tag);
        for (iA = itAFSM->second.begin(); iA != itAFSM->second.end(); iA++)
        {
          AttributeInfo* info = registeredObject->getAttribute(*iA);
          info->setStatusOwned(itAFSM->first);
          federate->getObjectAttributeRegions(job->object, *iA, regions);
          for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
          {
            info->associateRegion(job->fed, *itRegion);
            federate->unassociateAttributeRegionForUpdates(job->object, *iA, *itRegion);
          }
        }
      }
      catch (GeRtiFactory::ObjectNotKnown &)
      {
          std::cout << "ObjectNotKnown not known: " << std::endl;
      }
      catch (GeRtiFactory::AttributeNotKnown &)
      {
          std::cout << "Attribute not known: " << std::endl;
      }
      catch (GeRtiFactory::AttributeAcquisitionWasNotRequested &)
      {
          std::cout << "Attribute Acquisition Was Not Requested: " << std::endl;
      }
      catch (GeRtiFactory::AttributeAlreadyOwned &)
      {
          std::cout << "Attribute Already Owned: " << std::endl;
      }
      catch (GeRtiFactory::AttributeNotPublished &)
      {
          std::cout << "Attribute Not Published: " << std::endl;
      }
      catch (GeRtiFactory::FederateInternalError &)
      {
          std::cout << "Federate Internal Error: " << std::endl;
      }
      catch (CORBA::SystemException &sysex)
      {
        ACE_PRINT_EXCEPTION (sysex, "System Exception in attributeOwnershipDivestiture");
      }
      objectManagement.doOwnershipAcquisitionNotification(itAFSM->first, *registeredObject, itAFSM->second, false);
    }
  }

  // find all attributes which are succesfully divested
  GeRtiFactory::Handles divestedAttributes;
  GERTICO::AttributeMap::iterator itDA;
  size = job->attributes.size();
  GERTICO::Mapper::mapULongSizet(length, size);
  divestedAttributes.length(length);
  i=0;
  for (itDA = job->attributes.begin(); itDA != job->attributes.end(); itDA++)
  {
    AttributeInfo* info = objectManagement.getObject(job->object)->getAttribute(itDA->first);
    size = job->attributes.size();
    GERTICO::Mapper::mapULongSizet(length, size);
    divestedAttributes.length(length);
    if (!info->ownedByFederate(job->fed))
    {
      divestedAttributes.length(i+1);
      divestedAttributes[i++] = itDA->first;
    }
  }
  federate = federatesHolder->getFederate(job->fed);
  try
  {
    if (divestedAttributes.length() > 0)
    {
      if (federate)
      {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = job->object;
                              sprintf(galMsg,"OwnershipWorkerThread::attributeOwnershipDivestitureNotification(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], divestedAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

        federate->attributeOwnershipDivestitureNotification(job->object, divestedAttributes);
      }
    }
  }
  catch (...)
  {
    std::cout << "internal error in executeNegotiatedAttributeOwnershipDivestiture" << std::endl;
  }

  length = divestedAttributes.length();
  if (federate)
  {
    for (i = 0; i < length; i++)
    {
      federate->getObjectAttributeRegions(job->object, divestedAttributes[i], regions);
      for (itRegion = regions.begin(); itRegion != regions.end(); itRegion++)
      {
        federate->unassociateAttributeRegionForUpdates(job->object, divestedAttributes[i], *itRegion);
      }
    }
  }

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "OwnershipWorkerThread::executeAttributeOwnershipDivestitureNotification", "leave");   // inserted by Gal converter
                            }
#endif

  return done;
}

//***********************************************
//
JobStatus OwnershipWorkerThread::executeAttributeOwnershipAcquisitionCancellation (AttributeOwnershipAcquisitionCancellation* job)
{
  GERTICO::Federate *federate;
#ifdef GalDebug
  char galMsg[512];
#endif

  federate = federatesHolder->getFederate(job->fed);

  // .. and send cancellation notification
  if (federate != NULL)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = job->object;
                              sprintf(galMsg,"OwnershipWorkerThread::executeAttributeOwnershipAcquisitionCancellation(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], job->attributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

    federate->confirmAttributeOwnershipAcquisitionCancellation (job->object, job->attributes);
  }

#ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "OwnershipWorkerThread::executeAttributeOwnershipAcquisitionCancellation", "leave");   // inserted by Gal converter
                            }
#endif

  return done;
}
