/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Log: OwnershipManagementLRC.cpp,v $
Revision 1.9  2009/09/03 07:15:49  mul
Use local cache to get attribute owned status.

Revision 1.8  2009/05/27 11:38:32  mul
Change data access for registered objects.

Revision 1.7  2009/03/23 13:46:28  mul
Integrate ownership into rti and fed ambassador.

Revision 1.6  2009/02/16 15:10:27  mul
Changes for integrating ownership.

Revision 1.5  2008/11/19 14:09:53  mul
Changes for logging.

Revision 1.4  2008/04/28 23:58:51  mul
Changed gal logging.

Revision 1.3  2007/09/25 08:30:11  mul
Changes for ddm.

Revision 1.2  2007/09/06 06:39:55  mul
Changes for ieee1516.

Revision 1.1  2007/06/26 08:29:02  mul
Changes for ieee1516.


**
*******************************************************************************/

#include "LRC/OwnershipManagementLRC.h"
#include "Util/Mapper.h"

using namespace GERTICO;

/******************************** Gal begin ***********************************/

#ifdef GalDebug

#include "Gal/repository_l.h"
#include "Gal/event.h"

static class Repository_l *OWM=(Repository::getSingleInstance())->getRepository_l("GeRtiOWM.res","GeRtiOWM");

static class Event *GeRti_OWM_d=OWM->getRefEvent("GeRti_OWM_d");
static class Event *GeRti_OWM_e=OWM->getRefEvent("GeRti_OWM_e");
static class Event *GeRti_OWM_i=OWM->getRefEvent("GeRti_OWM_i");
static class Event *GeRti_OWM_w=OWM->getRefEvent("GeRti_OWM_w");

static char galMsg[512];

#endif

/******************************** Gal end ***********************************/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
OwnershipService::OwnershipService(GeRtiFactory::GeRtiHandle const &fedId, RegisteredObjectsHolder &theRegisteredObjectsHolder, GeRtiFactory::GeRtiAmbassador_ptr theOwnershipMasterPtr) : registeredObjectsHolder(theRegisteredObjectsHolder)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_d, "OwnershipService::OwnershipService", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  myFedId = fedId;
  myServerVar = GeRtiFactory::GeRtiAmbassador::_duplicate(theOwnershipMasterPtr);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_d, "OwnershipService::OwnershipService", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
OwnershipService::~OwnershipService(void)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_d, "OwnershipService::~OwnershipService", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_d, "OwnershipService::~OwnershipService", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

//******************** HLA like Methods *******************************

// ---------------------------------------------------------------------------
// 7.2
// IEEE
// ---------------------------------------------------------------------------
void OwnershipService::unconditionalAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle                  theObject,
    GeRtiFactory::Handles const &           theAttributes)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "object=%lu", ul);
                              E2(GeRti_OWM_i, "unconditionalAttributeOwnershipDivestiture", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theAttributes);
                              E2(GeRti_OWM_i, "unconditionalAttributeOwnershipDivestiture", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  RegisteredObject *registeredObject;

  // Check if object is locally known.
  registeredObject = registeredObjectsHolder.getObject(theObject);

  // Remote call.
  myServerVar->unconditionalAttributeOwnershipDivestiture (myFedId, theObject, theAttributes);
  for (unsigned int i=0; i<theAttributes.length(); i++)
  {
    AttributeInfo* info = registeredObject->getAttribute(theAttributes[i]);
    info->setStatusUnowned();
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_i, "unconditionalAttributeOwnershipDivestiture", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// 7.3
// IEEE
// ---------------------------------------------------------------------------
void OwnershipService::negotiatedAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle                  theObject,
    GeRtiFactory::Handles const &           theAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::AttributeAlreadyBeingDivested,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "object=%lu", ul);
                              E2(GeRti_OWM_i, "negotiatedAttributeOwnershipDivestiture", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theAttributes);
                              E2(GeRti_OWM_i, "negotiatedAttributeOwnershipDivestiture", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                              E2(GeRti_OWM_i, "negotiatedAttributeOwnershipDivestiture", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  myServerVar->negotiatedAttributeOwnershipDivestiture (myFedId, theObject, theAttributes, theTag);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_i, "negotiatedAttributeOwnershipDivestiture", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// 7.7
// IEEE
// ---------------------------------------------------------------------------
void OwnershipService::attributeOwnershipAcquisition (
    GeRtiFactory::GeRtiHandle        theObject,
    GeRtiFactory::Handles const & desiredAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::FederateOwnsAttributes,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "object=%lu", ul);
                              E2(GeRti_OWM_i, "attributeOwnershipAcquisition", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("desiredAttributes=", galMsg, desiredAttributes);
                              E2(GeRti_OWM_i, "attributeOwnershipAcquisition", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                              E2(GeRti_OWM_i, "attributeOwnershipAcquisition", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::GeRtiHandle objectClass;

  RegisteredObject *registeredObject;
  registeredObject = registeredObjectsHolder.getObject(theObject);
  objectClass = registeredObject->getClassId();
  myServerVar->attributeOwnershipAcquisition (myFedId, theObject, desiredAttributes, theTag);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_i, "attributeOwnershipAcquisition", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// 7.8
// IEEE
// ---------------------------------------------------------------------------
void OwnershipService::attributeOwnershipAcquisitionIfAvailable (
    GeRtiFactory::GeRtiHandle        theObject,
    GeRtiFactory::Handles const & desiredAttributes)
throw (
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
    GeRtiFactory::RTIinternalError)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "object=%lu", ul);
                              E2(GeRti_OWM_i, "attributeOwnershipAcquisitionIfAvailable", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("desiredAttributes=", galMsg, desiredAttributes);
                              E2(GeRti_OWM_i, "attributeOwnershipAcquisitionIfAvailable", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  GeRtiFactory::GeRtiHandle objectClass;

  RegisteredObject *registeredObject;
  registeredObject = registeredObjectsHolder.getObject(theObject);
  objectClass = registeredObject->getClassId();
  myServerVar->attributeOwnershipAcquisitionIfAvailable (myFedId, theObject, desiredAttributes);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_i, "attributeOwnershipAcquisitionIfAvailable", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void OwnershipService::attributeOwnershipDivestitureIfWanted(
    GeRtiFactory::GeRtiHandle const theObject,
    GeRtiFactory::Handles const &theAttributes,
    GeRtiFactory::Handles &theDivestedAttributes
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "object=%lu", ul);
                              E2(GeRti_OWM_i, "attributeOwnershipDivestitureIfWanted", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theAttributes);
                              E2(GeRti_OWM_i, "attributeOwnershipDivestitureIfWanted", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("divestedAttributes=", galMsg, theDivestedAttributes);
                              E2(GeRti_OWM_i, "attributeOwnershipDivestitureIfWanted", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  CORBA::ULong len;
  GeRtiFactory::GeRtiHandle objectClass;
  GeRtiFactory::Handles *h;

  RegisteredObject *registeredObject;
  registeredObject = registeredObjectsHolder.getObject(theObject);
  objectClass = registeredObject->getClassId();
  h = myServerVar->attributeOwnershipDivestitureIfWanted (myFedId, theObject, theAttributes);

  theDivestedAttributes = *h;

  len = h->length();
  for (i = 0; i < len; i++)
  {
    registeredObject->unownAttribute(myFedId, (*h)[i]);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_i, "attributeOwnershipDivestitureIfWanted", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// 7.11
// ---------------------------------------------------------------------------
GeRtiFactory::Handles*
OwnershipService::confirmDivestiture(
    GeRtiFactory::GeRtiHandle        theObject,
    GeRtiFactory::Handles const & theAttributes,
    GeRtiFactory::UserSuppliedTag const &theTag)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateWasNotAskedToReleaseAttribute,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "object=%lu", ul);
                              E2(GeRti_OWM_i, "confirmDivestiture", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theAttributes);
                              E2(GeRti_OWM_i, "confirmDivestiture", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                              E2(GeRti_OWM_i, "confirmDivestiture", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  CORBA::ULong len;
  GeRtiFactory::Handles *h;
  RegisteredObject *registeredObject;

  h = myServerVar->confirmDivestiture(myFedId, theObject, theAttributes, theTag);

  registeredObject = registeredObjectsHolder.getObject(theObject);
  len = h->length();
  for (i = 0; i < len; i++)
  {
    registeredObject->unownAttribute(myFedId, (*h)[i]);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_i, "confirmDivestiture", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return h;
}

// ---------------------------------------------------------------------------
// 7.12
// IEEE
// ---------------------------------------------------------------------------
void OwnershipService::cancelNegotiatedAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle        theObject,
    GeRtiFactory::Handles const & theAttributes)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::AttributeDivestitureWasNotRequested,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "object=%lu", ul);
                              E2(GeRti_OWM_i, "cancelNegotiatedAttributeOwnershipDivestiture", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theAttributes);
                              E2(GeRti_OWM_i, "cancelNegotiatedAttributeOwnershipDivestiture", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  myServerVar->cancelNegotiatedAttributeOwnershipDivestiture (myFedId, theObject, theAttributes);

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_i, "cancelNegotiatedAttributeOwnershipDivestiture", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// 7.13
// IEEE
// ---------------------------------------------------------------------------
void OwnershipService::cancelAttributeOwnershipAcquisition (
    GeRtiFactory::GeRtiHandle        theObject,
    GeRtiFactory::Handles const & theAttributes)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeAcquisitionWasNotRequested,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "object=%lu", ul);
                              E2(GeRti_OWM_i, "cancelAttributeOwnershipAcquisition", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theAttributes);
                              E2(GeRti_OWM_i, "cancelAttributeOwnershipAcquisition", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  myServerVar->cancelAttributeOwnershipAcquisition (myFedId, theObject, theAttributes);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_i, "cancelAttributeOwnershipAcquisition", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// 7.15
// IEEE
// ---------------------------------------------------------------------------
void OwnershipService::queryAttributeOwnership (
    GeRtiFactory::GeRtiHandle    theObject,
    GeRtiFactory::GeRtiHandle theAttribute)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = theObject;
                              ul1 = theAttribute;
                              sprintf(galMsg, "object=%lu,attribute=%lu", ul, ul1);
                              E2(GeRti_OWM_i, "queryAttributeOwnership", galMsg);   // inserted by Gal converter
                             }
                           #endif   // inserted by Gal converter
   // try to access status info
   myServerVar->queryAttributeOwnership (myFedId, theObject, theAttribute);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_i, "queryAttributeOwnership", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
// 7.17
// IEEE
// ---------------------------------------------------------------------------
bool OwnershipService::isAttributeOwnedByFederate (
    GeRtiFactory::GeRtiHandle    theObject,
    GeRtiFactory::GeRtiHandle theAttribute)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OWM_d)
                            {
                              unsigned long ul;
                              unsigned long ul1;

                              ul = theObject;
                              ul1 = theAttribute;
                              sprintf(galMsg, "object=%lu,attribute=%lu", ul, ul1);
                              E2(GeRti_OWM_i, "isAttributeOwnedByFederate", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  RegisteredObject* registeredObject;
  GERTICO::AttributeInfo *attributeInfo;
  bool ret = false;

  try
  {
    // Maybe have object in local cache.
    registeredObject = registeredObjectsHolder.getObject(theObject);
    attributeInfo = registeredObject->getAttribute(theAttribute);
    ret = attributeInfo->ownedByFederate(myFedId);
  }
  catch (GeRtiFactory::ObjectNotKnown &)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_d, "isOwned", "ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    // Remote call to get status.
    if (myServerVar->isAttributeOwnedByFederate(myFedId, theObject, theAttribute))
    {
      ret = true;
    }
  }
  catch (GeRtiFactory::AttributeNotDefined &)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_d, "isOwned", "AttributeNotDefined");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    // Remote call to get status.
    if (myServerVar->isAttributeOwnedByFederate(myFedId, theObject, theAttribute))
    {
      ret = true;
    }
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OWM_i, "isOwned", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  return ret;
}
