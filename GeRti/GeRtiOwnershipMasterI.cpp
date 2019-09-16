/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************

$Author: mul $
$Log: GeRtiOwnershipMasterI.cpp,v $
Revision 1.8  2009/09/23 08:00:21  mul
Remove mutex lock.

Revision 1.7  2009/06/12 12:58:10  mul
Use thread mutex.

Revision 1.6  2009/03/23 14:06:27  mul
Changes to integrate ownership into rti and fed ambassador.

Revision 1.5  2009/02/16 15:18:56  mul
Changes for integrating ownership.

Revision 1.4  2009/01/26 10:41:31  mul
Changes to detect crashed federate.

Revision 1.3  2008/11/05 08:48:51  mul
Refine logging.

Revision 1.2  2008/01/30 14:35:56  mul
Changes for ieee1516.

Revision 1.1  2007/09/25 08:36:55  mul
From Ownership directory.


**
*******************************************************************************/

#include "GeRtiOwnershipMasterI.h"
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiOrb.h"
#include "Util/Mapper.h"
#include "Util/NextHandle.h"

#include <iostream>

using namespace GERTICO;

/********************************* Gal begin ************************************/

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

/********************************* Gal end ************************************/

static char galMsg[512];

//******************************************************
//
GeRtiOwnershipMasterI::GeRtiOwnershipMasterI (
  RunTimeObjectDB &theOwnershipInfo,
  GERTICO::ObjectManagement &theObjectManagement)
: myWorkerThread (theOwnershipInfo,theObjectManagement)
{
#ifdef GalDebug
                            E2(GeRti_OWM_d, "GeRtiOwnershipMasterI", "enter");
#endif
#ifdef GalDebug
                            E2(GeRti_OWM_d, "GeRtiOwnershipMasterI", "leave");
#endif
}

//******************************************************
//
GeRtiOwnershipMasterI::~GeRtiOwnershipMasterI ()
{
#ifdef GalDebug
                            E2(GeRti_OWM_d, "~GeRtiOwnershipMasterI", "enter");
#endif
#ifdef GalDebug
                            E2(GeRti_OWM_d, "~GeRtiOwnershipMasterI", "leave");
#endif
}

//******************************************************
//
void GeRtiOwnershipMasterI::setFederatesHolder(GERTICO::FederatesHolder* theFederatesHolder)
{
  myWorkerThread.setFederatesHolder(theFederatesHolder);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiOwnershipMasterI::managerFederateAdjustModifyAttributeState(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute, std::string &theAttributeState)
{
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::RegisteredObject *registeredObject;

  try
  {
    registeredObject = myWorkerThread.objectManagement.getObject(theObject);
    attributeInfo = registeredObject->getAttribute(theAttribute);
  }
  catch(...)
  {
    return;
  }

#ifdef IEEE_1516
  if (theAttributeState == "HLAowned")
#else
  GERTICO::Mapper::nameToLower(theAttributeState);
  if (theAttributeState == "owned")
#endif
  {
    attributeInfo->setStatusOwned(theFederate);
  }
  else
  {
    if (attributeInfo->ownedByFederate(theFederate))
    {
      attributeInfo->setStatusOwned(0);
    }
  }
}

// ---------------------------------------------------------------------------
// If a publisher owning an attribute, drops this attribute in the next
// publish, it becomes unowned and it is thus available for another federate.
// ---------------------------------------------------------------------------
void GeRtiOwnershipMasterI::processUnpublishOwnershipCandidate(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theDroppedAttributes)
{
  CORBA::ULong len = 0;
  GERTICO::AttributeInfo *attributeInfo;
  GERTICO::Federate *federate;
  GERTICO::FederatesHolder *federatesHolder;
  GERTICO::HandleSet knownObjects;
  GERTICO::HandleSet::iterator itDroppedAttribute;
  GERTICO::HandleSet::iterator itKnownObject;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle privilegeToDeleteId = myWorkerThread.runTimeObjectDB.getPrivilegeToDeleteId();
  GeRtiFactory::Handles ownedAttributes;
  GeRtiFactory::UserSuppliedTag tag;

  GERTICO::Mapper::mapUserSuppliedTag(tag, "publish");

  federatesHolder = myWorkerThread.getFederatesHolder();
  federate = federatesHolder->getFederate(theFederate);
  if (federate)
  {
    federate->getKnownObjects(theClass, knownObjects);
    federate->setAlive();
  }

  // Atomic check.
  for (itKnownObject = knownObjects.begin(); itKnownObject != knownObjects.end(); itKnownObject++)
  {
    try
    {
      registeredObject = myWorkerThread.runTimeObjectDB.getObject(*itKnownObject);
      registeredObject->checkOwnershipAcquisitionPending(theFederate, theDroppedAttributes, privilegeToDeleteId);
    }
    catch (GeRtiFactory::OwnershipAcquisitionPending &)
    {
      throw;
    }
    catch(...)
    {
      continue;
    }
  }

  for (itKnownObject = knownObjects.begin(); itKnownObject != knownObjects.end(); itKnownObject++)
  {
    len = 0;
    try
    {
      registeredObject = myWorkerThread.runTimeObjectDB.getObject(*itKnownObject);
    }
    catch(...)
    {
      continue;
    }

    for (itDroppedAttribute = theDroppedAttributes.begin(); itDroppedAttribute != theDroppedAttributes.end(); itDroppedAttribute++)
    {
      attributeInfo = registeredObject->getAttribute(*itDroppedAttribute);
      if (attributeInfo->ownedByFederate(theFederate))
      {
        attributeInfo->unsetFederate (theFederate);
        ownedAttributes.length(len + 1);
        ownedAttributes[len] = *itDroppedAttribute;
        len += 1;
      }
    }

    len = ownedAttributes.length();
    if (len)
    {
      myWorkerThread.add (new RequestAttributeOwnershipAssumptionJob(
        &myWorkerThread,
        theFederate,
        *itKnownObject,
        ownedAttributes,
        tag,
        unowned));
    }
  }
}

//******************************************************
//
// 7.2
// IEEE
void GeRtiOwnershipMasterI::unconditionalAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle                  theObject,     // supplied C1
    const GeRtiFactory::Handles&           theAttributes) // supplied C4
throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError)
{
  GeRtiFactory::Handles ownedAttributes;
  GERTICO::HandleSetMap acquiringFederatesSetMap;
  GERTICO::HandleSetMap::iterator itAFSM;
  GeRtiFactory::UserSuppliedTag tag;
  unsigned int i;
  unsigned long len = 0;

  // Pre-conditions - atomic checks
  myWorkerThread.objectManagement.checkOwned(fedId, theObject, theAttributes);

  // Process owned attributes.
  for (i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo* info = myWorkerThread.runTimeObjectDB.getObjectAttributeInfo (theObject, theAttributes[i]);
    switch (info->getStatus())
    {
      case divesting:
      case divestConfirm:
      case owned:
      {
        // prepare list for unconditionally release attribute
        ownedAttributes.length(len + 1);
        ownedAttributes[len++] = theAttributes[i];
        info->setStatusOwned(0);
        break;
      }
      case acquiring:
      case acquired:
      {
        // Process acquiring attributes.
        // Get a set of federates.
        itAFSM = acquiringFederatesSetMap.find(info->getFirstAcquiringFederate());
        if (itAFSM != acquiringFederatesSetMap.end())
        {
          GERTICO::HandleSet *handleSetPtr;
          handleSetPtr = &itAFSM->second;
          handleSetPtr->insert(theAttributes[i]);
        }
        else
        {
          GERTICO::HandleSet handleSet;
          handleSet.insert(theAttributes[i]);
          acquiringFederatesSetMap[info->getFirstAcquiringFederate()] = handleSet;
        }
        // forget former owner
        info->setStatusOwned(0);
        break;
      }
    }
  }

  // For each federate send all relevant attributes in one call.
  GERTICO::Mapper::mapUserSuppliedTag(tag, "unconditional");
  for (itAFSM = acquiringFederatesSetMap.begin(); itAFSM != acquiringFederatesSetMap.end(); itAFSM++)
  {
    myWorkerThread.add(new OwnershipAcquisitionNotification(&myWorkerThread, itAFSM->first, theObject, itAFSM->second, tag));
  }

  // attributes are no longer being owned by any federate
  myWorkerThread.add (new RequestAttributeOwnershipAssumptionJob(
    &myWorkerThread,
    fedId,
    theObject,
    ownedAttributes,
    tag,
    unowned));
}

//******************************************************
//
// 7.3
// IEEE
void GeRtiOwnershipMasterI::negotiatedAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle                  theObject,
    const GeRtiFactory::Handles&           theAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag)
throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::AttributeAlreadyBeingDivested,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
    )
{
#ifdef IEEE_1516
  GeRtiFactory::Handles ownedAttributes;
  GERTICO::HandleSetMap acquiringFederatesSetMap;
  GERTICO::HandleSetMap::iterator itAFSM;
  unsigned int i;
  unsigned long len = 0;

  // Pre-conditions - atomic checks
  myWorkerThread.objectManagement.checkOwned(fedId, theObject, theAttributes);
  myWorkerThread.objectManagement.checkNotDivesting(theObject, theAttributes);

  AttributeMap acquiredAttributes;
  for (i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo* info = myWorkerThread.runTimeObjectDB.getObjectAttributeInfo (theObject, theAttributes[i]);
    switch (info->getStatus())
    {
      case owned:
      {
        // prepare list for divesting attribute
        ownedAttributes.length(len + 1);
        ownedAttributes[len++] = theAttributes[i];
        info->setStatusDivesting();
        break;
      }
      case acquiring:
      case acquired:
      {
        // collect all acquired attributes
        acquiredAttributes[theAttributes[i]] = info;
        // Process acquiring attributes.
        // Get a set of federates.
        itAFSM = acquiringFederatesSetMap.find(info->getFirstAcquiringFederate());
        if (itAFSM != acquiringFederatesSetMap.end())
        {
          GERTICO::HandleSet *handleSetPtr;
          handleSetPtr = &itAFSM->second;
          handleSetPtr->insert(theAttributes[i]);
        }
        else
        {
          GERTICO::HandleSet handleSet;
          handleSet.insert(theAttributes[i]);
          acquiringFederatesSetMap[info->getFirstAcquiringFederate()] = handleSet;
        }
        info->setStatusDivestConfirm();
        break;
      }
    }
  }

  // schedule the job to handle the negotiated divestiture process for acquired attributes
  if (acquiredAttributes.size())
  {
    myWorkerThread.add (new RequestDivestitureConfirmationJob(
      &myWorkerThread,
      fedId,
      theObject,
      acquiredAttributes));
  }

  myWorkerThread.add (new RequestAttributeOwnershipAssumptionJob(
    &myWorkerThread,
    fedId,
    theObject,
    ownedAttributes,
    theTag,
    divesting));
#else
  GeRtiFactory::Handles ownedAttributes;
  GERTICO::HandleSetMap acquiringFederatesSetMap;
  GERTICO::HandleSetMap::iterator itAFSM;
  unsigned int i;
  unsigned long aLen = 0;
  unsigned long len = 0;

  // Pre-conditions - atomic checks
  myWorkerThread.objectManagement.checkOwned(fedId, theObject, theAttributes);
  myWorkerThread.objectManagement.checkNotDivesting(theObject, theAttributes);

  AttributeMap acquiredAttributes;
  for (i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo* info = myWorkerThread.runTimeObjectDB.getObjectAttributeInfo (theObject, theAttributes[i]);
    switch (info->getStatus())
    {
      case owned:
      {
        // prepare list for divesting attribute
        ownedAttributes.length(len + 1);
        ownedAttributes[len++] = theAttributes[i];
        info->setStatusDivesting();
        break;
      }
      case acquiring:
      case acquired:
      {
        // collect all acquired attributes
        acquiredAttributes[theAttributes[i]] = info;
        // Process acquiring attributes.
        // Get a set of federates.
        itAFSM = acquiringFederatesSetMap.find(info->getFirstAcquiringFederate());
        if (itAFSM != acquiringFederatesSetMap.end())
        {
          GERTICO::HandleSet *handleSetPtr;
          handleSetPtr = &itAFSM->second;
          handleSetPtr->insert(theAttributes[i]);
        }
        else
        {
          GERTICO::HandleSet handleSet;
          handleSet.insert(theAttributes[i]);
          acquiringFederatesSetMap[info->getFirstAcquiringFederate()] = handleSet;
        }
        // forget former owner
        info->setStatusOwned(0);
        break;
      }
    }
  }

  /*
  // For each federate send all relevant attributes in one call.
  for (itAFSM = acquiringFederatesSetMap.begin(); itAFSM != acquiringFederatesSetMap.end(); itAFSM++)
  {
    myWorkerThread.add(new OwnershipAcquisitionNotification(&myWorkerThread, itAFSM->first, theObject, itAFSM->second));
  }
  */

  // schedule the job to handle the negotiated divestiture process for acquired attributes
  myWorkerThread.add (new NegotiatedAttributeOwnershipDivestiture(
    &myWorkerThread,
    fedId,
    theObject,
    acquiredAttributes,
    acquiringFederatesSetMap,
    theTag));


  myWorkerThread.add (new RequestAttributeOwnershipAssumptionJob(
    &myWorkerThread,
    fedId,
    theObject,
    ownedAttributes,
    theTag,
    divesting));
#endif
}

//******************************************************
//
// 7.7
// IEEE
void GeRtiOwnershipMasterI::attributeOwnershipAcquisition (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle        theObject,
    const GeRtiFactory::Handles& desiredAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag)
throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::ObjectClassNotPublished,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotPublished,
        GeRtiFactory::FederateOwnsAttributes,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
    )
{
  CORBA::WChar *wChar = L"";
  GERTICO::Federate *federate;
  GERTICO::FederatesHolder *federatesHolder;
  GeRtiFactory::GeRtiHandle knownObjectClass;

  federatesHolder = myWorkerThread.getFederatesHolder();
  federate = federatesHolder->getFederate(fedId);
  if (federate)
  {
    knownObjectClass = federate->getObjectClass(theObject);
    federate->setAlive();
  }
  else
  {
    throw GeRtiFactory::RTIinternalError(L"getFederatesHolder");
  }

  // Pre-conditions - atomic checks
  myWorkerThread.runTimeObjectDB.checkPublishing(fedId, knownObjectClass, desiredAttributes);
  myWorkerThread.objectManagement.checkNotOwned(fedId, theObject, desiredAttributes);

  // find the object attributes owned elsewere and
  // find unowned attributes
  AttributeMap ownedAttributes;
  GERTICO::HandleSetMap unownedAttributesSetMap;
  GERTICO::HandleSetMap::iterator itUASM;
  AttributeMap divestedAttributes;
  RegisteredObject* obj = myWorkerThread.runTimeObjectDB.getObject (theObject);
  for (unsigned int i=0; i<desiredAttributes.length(); i++)
  {
    AttributeInfo* a;
    try
    {
      a = obj->getAttribute(desiredAttributes[i]);
    }
    catch (GeRtiFactory::AttributeNotDefined&)
    {
      GERTICO::Item *currItem;
      // attribute was not yet managed
      GERTICO::HandleSet hs;
      hs.insert (desiredAttributes[i]);
      // check if class and attribute is valid
      myWorkerThread.runTimeObjectDB.checkClassAttributes (knownObjectClass, hs);
      // create new attribute management data set
      ClassDescr *cd = myWorkerThread.runTimeObjectDB.getObjectClassDescr (knownObjectClass);
      currItem = cd ->getClassItem (desiredAttributes[i]);
      a = new AttributeInfo(fedId, unowned, currItem->getOrdering(), currItem->getTransportation());
      obj->addAttribute (desiredAttributes[i], a);
    }
    switch (a->getStatus())
    {
    case owned:
      if (a->getFederate () == fedId)
        throw FederateOwnsAttributes(wChar);
      else
        ownedAttributes[desiredAttributes[i]] = a;
      a->setStatusAcquiring();
      a->addAcquiringFederate (fedId);
      break;
    case divesting:
      divestedAttributes[desiredAttributes[i]] = a;
#ifdef IEEE_1516
      a->setStatusDivestConfirm();
      a->addAcquiringFederate (fedId);
      break;
#endif
    case undefined:
    case unowned:
      itUASM = unownedAttributesSetMap.find(fedId);
      if (itUASM != unownedAttributesSetMap.end())
      {
        GERTICO::HandleSet *handleSetPtr;
        handleSetPtr = &itUASM->second;
        handleSetPtr->insert(desiredAttributes[i]);
      }
      else
      {
        GERTICO::HandleSet handleSet;
        handleSet.insert(desiredAttributes[i]);
        unownedAttributesSetMap[fedId] = handleSet;
      }
      a->setStatusAcquiring();
      a->addAcquiringFederate (fedId);
      break;
    case acquired:
    case acquiring:
        ownedAttributes[desiredAttributes[i]] = a;
        break;
    default:
      throw GeRtiFactory::RTIinternalError(wChar);
      break;
    }
  }

  // schedule divestiture notification
  if (divestedAttributes.size() > 0)
    myWorkerThread.add (new AttributeOwnershipDivestitureNotification (&myWorkerThread, fedId, theObject, divestedAttributes));

  // schedule inform job for all unowned attributes
  // NB. only one federate entry
  for (itUASM = unownedAttributesSetMap.begin(); itUASM != unownedAttributesSetMap.end(); itUASM++)
  {
    myWorkerThread.add(new OwnershipAcquisitionNotification(&myWorkerThread, fedId, theObject, itUASM->second, theTag));
  }

  //schedule release job for owned attributes
  if (ownedAttributes.size() > 0)
    myWorkerThread.add (new AttributeOwnershipRelease (&myWorkerThread, fedId, theObject, ownedAttributes, theTag));
}

//******************************************************
//
// 7.8
// IEEE
void GeRtiOwnershipMasterI::attributeOwnershipAcquisitionIfAvailable (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle        theObject,
    const GeRtiFactory::Handles& desiredAttributes)
throw (
        CORBA::SystemException,
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
        GeRtiFactory::RTIinternalError
    )
{
  CORBA::WChar *wChar = L"";
  GERTICO::AttributeInfo *a;
  GERTICO::AttributeMap divestedAttributes;
  GERTICO::AttributeMap ownedAttributes;
  GERTICO::ClassDescr *classDescr;
  GERTICO::Federate *federate;
  GERTICO::FederatesHolder *federatesHolder;
  GERTICO::HandleSetMap unownedAttributesSetMap;
  GERTICO::HandleSetMap::iterator itUASM;
  GeRtiFactory::GeRtiHandle knownObjectClass;
  GeRtiFactory::UserSuppliedTag tag;

  federatesHolder = myWorkerThread.getFederatesHolder();
  federate = federatesHolder->getFederate(fedId);
  if (federate)
  {
    knownObjectClass = federate->getObjectClass(theObject);
    federate->setAlive();
  }
  else
  {
    throw GeRtiFactory::RTIinternalError(L"getFederatesHolder");
  }

  // Pre-conditions - atomic checks
  myWorkerThread.runTimeObjectDB.checkPublishing(fedId, knownObjectClass, desiredAttributes);
  myWorkerThread.objectManagement.checkNotOwned(fedId, theObject, desiredAttributes);
  myWorkerThread.objectManagement.checkNotAcquiring(fedId, theObject, desiredAttributes);

  RegisteredObject* obj = myWorkerThread.runTimeObjectDB.getObject (theObject);
  for (unsigned int i=0; i<desiredAttributes.length(); i++)
  {
    try
    {
      a = obj->getAttribute(desiredAttributes[i]);
    }
    catch(GeRtiFactory::AttributeNotDefined &)
    {
      GERTICO::Item *item;

      classDescr = myWorkerThread.runTimeObjectDB.getObjectClassDescr(knownObjectClass);
      item = classDescr->getClassItem(desiredAttributes[i]);
      a = new GERTICO::AttributeInfo(0, unowned, item->getOrdering(), item->getTransportation());
      obj->addAttribute(desiredAttributes[i], a);
    }

    switch (a->getStatus())
    {
    case owned:
      if (a->getFederate () == fedId)
        throw FederateOwnsAttributes(wChar);
      else
        ownedAttributes[desiredAttributes[i]] = a;
      break;
    case divesting:
      divestedAttributes[desiredAttributes[i]] = a;
#ifdef IEEE_1516
      a->setStatusDivestConfirm();
      a->addAcquiringFederate (fedId);
      break;
#endif
    case undefined:
    case unowned:
      itUASM = unownedAttributesSetMap.find(fedId);
      if (itUASM != unownedAttributesSetMap.end())
      {
        GERTICO::HandleSet *handleSetPtr;
        handleSetPtr = &itUASM->second;
        handleSetPtr->insert(desiredAttributes[i]);
      }
      else
      {
        GERTICO::HandleSet handleSet;
        handleSet.insert(desiredAttributes[i]);
        unownedAttributesSetMap[fedId] = handleSet;
      }
      a->setStatusAcquiring();
      a->addAcquiringFederate (fedId);
      break;
    default:
      break;
    }
  }

  // schedule divestiture notification
  if (divestedAttributes.size() > 0)
  {
    myWorkerThread.add (new AttributeOwnershipDivestitureNotification(&myWorkerThread, fedId, theObject, divestedAttributes));
  }

  // schedule inform job for all unowned attributes
  // NB. only one federate entry
  GERTICO::Mapper::mapUserSuppliedTag(tag, "attributeOwnershipAcquisitionIfAvailable");
  for (itUASM = unownedAttributesSetMap.begin(); itUASM != unownedAttributesSetMap.end(); itUASM++)
  {
    myWorkerThread.add(new OwnershipAcquisitionNotification(&myWorkerThread, fedId, theObject, itUASM->second, tag));
  }

  //schedule release job for owned attributes
  if (ownedAttributes.size() > 0)
    myWorkerThread.add (new AttributeOwnershipUnavailable (&myWorkerThread, fedId, theObject, ownedAttributes));
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::Handles * GeRtiOwnershipMasterI::attributeOwnershipDivestitureIfWanted (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Handles & theAttributes
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
  GeRtiFactory::Handles *ret = NULL;
  GERTICO::Federate *federate;
  GERTICO::FederatesHolder *federatesHolder;
  GERTICO::HandleSet acquiredAttributes;
  GERTICO::HandleSetMap acquiringFederatesSetMap;
  GERTICO::HandleSetMap::iterator itAFSM;
  GeRtiFactory::UserSuppliedTag tag;
  unsigned int i;

  // Pre-conditions - atomic checks
  myWorkerThread.objectManagement.checkOwned(fedId, theObject, theAttributes);

  // Process owned attributes.
  for (i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo* info = myWorkerThread.runTimeObjectDB.getObjectAttributeInfo (theObject, theAttributes[i]);
    switch (info->getStatus())
    {
      case acquiring:
      case acquired:
      {
        // Process acquiring attributes.
        // Get a set of federates.
        itAFSM = acquiringFederatesSetMap.find(info->getFirstAcquiringFederate());
        if (itAFSM != acquiringFederatesSetMap.end())
        {
          GERTICO::HandleSet *handleSetPtr;
          handleSetPtr = &itAFSM->second;
          handleSetPtr->insert(theAttributes[i]);
        }
        else
        {
          GERTICO::HandleSet handleSet;
          handleSet.insert(theAttributes[i]);
          acquiringFederatesSetMap[info->getFirstAcquiringFederate()] = handleSet;
        }
        acquiredAttributes.insert(theAttributes[i]);
        // forget former owner
        info->setStatusOwned(0);
        break;
      }
    }
  }

  // For each federate send all relevant attributes in one call.
  GERTICO::Mapper::mapUserSuppliedTag(tag, "unconditional");
  for (itAFSM = acquiringFederatesSetMap.begin(); itAFSM != acquiringFederatesSetMap.end(); itAFSM++)
  {
    myWorkerThread.add(new OwnershipAcquisitionNotification(&myWorkerThread, itAFSM->first, theObject, itAFSM->second, tag));
  }

  ret = new GeRtiFactory::Handles();
  GERTICO::Mapper::mapHandleSet(*ret, acquiredAttributes);

  federatesHolder = myWorkerThread.getFederatesHolder();
  federate = federatesHolder->getFederate(fedId);
  if (federate)
  {
    federate->setOutScope(theObject, *ret);
    federate->setAlive();
  }

#ifdef GalDebug
                            E2(GeRti_OWM_d, "attributeOwnershipDivestitureIfWanted", "leave");
#endif

  return ret;
}

//******************************************************
//
// 7.11
GeRtiFactory::Handles*
GeRtiOwnershipMasterI::confirmDivestiture(
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle        theObject,
    const GeRtiFactory::Handles& theAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag)
throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::FederateWasNotAskedToReleaseAttribute,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
    )
{
  CORBA::ULong i;
  GERTICO::Federate *federate;
  GERTICO::FederatesHolder *federatesHolder;
  GERTICO::HandleSetMap handleSetMap;
  GERTICO::HandleSetMap::iterator itHSM;

  // Pre-conditions - atomic checks
  myWorkerThread.objectManagement.checkOwned(fedId, theObject, theAttributes);
#ifndef IEEE_1516
  myWorkerThread.runTimeObjectDB.testIfRequestedToRelease(theObject, theAttributes);
#endif

  // allocate maximum buffer
  GeRtiFactory::Handles* releasedAttributes =
    new GeRtiFactory::Handles(theAttributes.length());
  unsigned int size = 0;

  // inform all acquiring federated
  for (i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo* info = myWorkerThread.runTimeObjectDB.getObjectAttributeInfo (theObject, theAttributes[i]);
    info->unsetRequested();
#ifdef IEEE_1516
    if (info->getStatus() == divestConfirm)
#else
    if (info->getStatus() == acquired)
#endif
    {
      // adjust length of buffer
      releasedAttributes->length (size+1);
      (*releasedAttributes)[size] = theAttributes[i];
      size += 1;
      itHSM = handleSetMap.find(info->getFirstAcquiringFederate());
      if (itHSM != handleSetMap.end())
      {
        GERTICO::HandleSet *handleSetPtr;
        handleSetPtr = &itHSM->second;
        handleSetPtr->insert(theAttributes[i]);
      }
      else
      {
        GERTICO::HandleSet handleSet;
        handleSet.insert(theAttributes[i]);
        handleSetMap[info->getFirstAcquiringFederate()] = handleSet;
      }
    }
  }

  for (itHSM = handleSetMap.begin(); itHSM != handleSetMap.end(); itHSM++)
  {
    myWorkerThread.add (new OwnershipAcquisitionNotification (
      &myWorkerThread, itHSM->first, theObject, itHSM->second, theTag));
  }

  federatesHolder = myWorkerThread.getFederatesHolder();
  federate = federatesHolder->getFederate(fedId);
  if (federate)
  {
    federate->setOutScope(theObject, *releasedAttributes);
    federate->setAlive();
  }

#ifdef GalDebug
                            E2(GeRti_OWM_d, "confirmDivestiture", "leave");
#endif
  return releasedAttributes;
}

//******************************************************
//
// 7.12
// IEEE
void GeRtiOwnershipMasterI::cancelNegotiatedAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle        theObject,     // supplied C1
    const GeRtiFactory::Handles& theAttributes) // supplied C4
throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeNotOwned,
        GeRtiFactory::AttributeDivestitureWasNotRequested,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
    )
{
  // Pre-conditions - atomic checks
  myWorkerThread.objectManagement.checkOwned(fedId, theObject, theAttributes);
  myWorkerThread.objectManagement.checkDivesting(theObject, theAttributes);

  for (unsigned int i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo* info = myWorkerThread.runTimeObjectDB.
      getObjectAttributeInfo (theObject, theAttributes[i]);
    if (info->getStatus() == divesting || info->getStatus() == divestConfirm)
    {
      info->setStatusFlag(owned);
    }
  }
}

//******************************************************
//
// 7.13
// IEEE
void GeRtiOwnershipMasterI::cancelAttributeOwnershipAcquisition (
    GeRtiFactory::GeRtiHandle fedId,
     GeRtiFactory::GeRtiHandle        theObject,     // supplied C1
    const GeRtiFactory::Handles& theAttributes) // supplied C4
throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::AttributeAlreadyOwned,
        GeRtiFactory::AttributeAcquisitionWasNotRequested,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
    )
{
  CORBA::WChar *wChar = L"";

  // Pre-conditions - atomic checks
  try
  {
    myWorkerThread.objectManagement.checkNotOwned(fedId, theObject, theAttributes);
  }
  catch (GeRtiFactory::FederateOwnsAttributes&)
  {
    throw GeRtiFactory::AttributeAlreadyOwned(wChar);
  }

  myWorkerThread.objectManagement.checkFedAcquiring(fedId, theObject, theAttributes);

  for (unsigned int i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo* info = myWorkerThread.runTimeObjectDB.
      getObjectAttributeInfo (theObject, theAttributes[i]);
    if ((info->getStatus() == acquiring) || (info->getStatus() == acquired))
    {
      info->setStatusFlag(owned);
    }
  }
  myWorkerThread.add (new AttributeOwnershipAcquisitionCancellation (&myWorkerThread, fedId, theObject, theAttributes));
}

//******************************************************
//
// 7.15
// IEEE
void GeRtiOwnershipMasterI::queryAttributeOwnership (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute) // supplied C1
throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
    )
{
  ClassDescr *classDescr;
  GERTICO::Item *item;

  AttributeInfo *attributeInfo;
  GERTICO::RegisteredObject *object;
  GeRtiFactory::GeRtiHandle attributeOwner;

  /*
  GERTICO::AttributeInfo *a;
  GERTICO::AttributeMap divestedAttributes;
  GERTICO::AttributeMap ownedAttributes;
  GERTICO::ClassDescr *classDescr;
  GERTICO::HandleSetMap unownedAttributesSetMap;
  GERTICO::HandleSetMap::iterator itUASM;
  */
  GeRtiFactory::GeRtiHandle knownObjectClass;
  GERTICO::FederatesHolder *federatesHolder;
  GERTICO::Federate *federate;

  // check known class info
  federatesHolder = myWorkerThread.getFederatesHolder();
  federate = federatesHolder->getFederate(fedId);
  if (federate)
  {
    knownObjectClass = federate->getObjectClass(theObject);
    federate->setAlive();
  }
  else
  {
    throw GeRtiFactory::RTIinternalError(L"getFederatesHolder");
  }
  classDescr = myWorkerThread.runTimeObjectDB.getObjectClassDescr(knownObjectClass);
  item = classDescr->getClassItem(theAttribute);
  if (item == NULL)
  {
    throw GeRtiFactory::AttributeNotDefined(L"queryAttributeOwnership");
  }
  // get ownership inof
  object = myWorkerThread.runTimeObjectDB.getObject(theObject);
  try
  {
    attributeInfo = object->getAttribute(theAttribute);
    attributeOwner = attributeInfo->getFederate();
  }
  catch(GeRtiFactory::AttributeNotDefined)
  {
    attributeOwner = 0;
  }

  myWorkerThread.add (new InformAttributOwnership (&myWorkerThread, fedId, theObject, theAttribute, attributeOwner));
}

//******************************************************
//
// 7.17
// IEEE
CORBA::Boolean GeRtiOwnershipMasterI::isAttributeOwnedByFederate (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle    theObject,     // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute)  // supplied C1
throw (
        CORBA::SystemException,
        GeRtiFactory::ObjectNotKnown,
        GeRtiFactory::AttributeNotDefined,
        GeRtiFactory::FederateNotExecutionMember,
        GeRtiFactory::ConcurrentAccessAttempted,
        GeRtiFactory::SaveInProgress,
        GeRtiFactory::RestoreInProgress,
        GeRtiFactory::RTIinternalError
    )
{
  GERTICO::AttributeInfo *info;

  GeRtiFactory::GeRtiHandle knownObjectClass;
  GERTICO::FederatesHolder *federatesHolder;
  GERTICO::Federate *federate;
  ClassDescr *classDescr;
  GERTICO::Item *item;

  // check known class info
  federatesHolder = myWorkerThread.getFederatesHolder();
  federate = federatesHolder->getFederate(fedId);
  if (federate)
  {
    knownObjectClass = federate->getObjectClass(theObject);
    federate->setAlive();
  }
  else
  {
    throw GeRtiFactory::RTIinternalError(L"getFederatesHolder");
  }
  classDescr = myWorkerThread.runTimeObjectDB.getObjectClassDescr(knownObjectClass);
  item = classDescr->getClassItem(theAttribute);
  if (item == NULL)
  {
    throw GeRtiFactory::AttributeNotDefined(L"isAttributeOwnedByFederate");
  }

  try
  {
    // Get stored attribute status - based on published set of attributes.
    info = myWorkerThread.runTimeObjectDB.getObjectAttributeInfo(theObject, theAttribute);
    if (info->ownedByFederate(fedId))
    {
#ifdef GalDebug
                            E2(GeRti_OWM_d, "isAttributeOwnedByFederate", "Owned");
#endif
      return 1;
    }
  }
  catch(GeRtiFactory::AttributeNotDefined &)
  {
    // Attribute may or may not be in the class since non-published attributes
    // are not managed.
    myWorkerThread.objectManagement.checkUnmanagedAttribute(theObject, theAttribute);
  }

#ifdef GalDebug
                            E2(GeRti_OWM_d, "isAttributeOwnedByFederate", "NotOwned");
#endif
  // Attribute is not owned
  return 0;
}

