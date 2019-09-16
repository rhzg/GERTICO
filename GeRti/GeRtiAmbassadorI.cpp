/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
** GeRtiAmbassadorI.cpp
**
*******************************************************************************/

#include "Util/ConvertTime.h"
#include "Util/GeRtiOrb.h"
#include "Util/Mapper.h"
#include "Util/NextHandle.h"
#include "GeRtiAmbassadorI.h"

/********************************* Gal begin *********************************/   // inserted by Gal converter

#ifdef GalDebug   // inserted by Gal converter
#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

static class Repository_l *DM=(Repository::getSingleInstance())->getRepository_l("GeRtiDM.res","GeRtiDM");

static class Event *GeRti_DM_d=DM->getRefEvent("GeRti_DM_d");
static class Event *GeRti_DM_e=DM->getRefEvent("GeRti_DM_e");
static class Event *GeRti_DM_i=DM->getRefEvent("GeRti_DM_i");
static class Event *GeRti_DM_w=DM->getRefEvent("GeRti_DM_w");

static class Repository_l *DDM=(Repository::getSingleInstance())->getRepository_l("GeRtiDDM.res","GeRtiDDM");

static class Event *GeRti_DDM_d=DDM->getRefEvent("GeRti_DDM_d");
static class Event *GeRti_DDM_e=DDM->getRefEvent("GeRti_DDM_e");
static class Event *GeRti_DDM_i=DDM->getRefEvent("GeRti_DDM_i");
static class Event *GeRti_DDM_w=DDM->getRefEvent("GeRti_DDM_w");

static class Repository_l *FM=(Repository::getSingleInstance())->getRepository_l("GeRtiFM.res","GeRtiFM");

static class Event *GeRti_FM_d=FM->getRefEvent("GeRti_FM_d");
static class Event *GeRti_FM_e=FM->getRefEvent("GeRti_FM_e");
static class Event *GeRti_FM_feds_i=FM->getRefEvent("GeRti_FM_feds_i");
static class Event *GeRti_FM_i=FM->getRefEvent("GeRti_FM_i");
static class Event *GeRti_FM_save_restore_i=FM->getRefEvent("GeRti_FM_save_restore_i");
static class Event *GeRti_FM_sync_i=FM->getRefEvent("GeRti_FM_sync_i");
static class Event *GeRti_FM_w=FM->getRefEvent("GeRti_FM_w");

static class Repository_l *OM=(Repository::getSingleInstance())->getRepository_l("GeRtiOM.res","GeRtiOM");

static class Event *GeRti_OM_d=OM->getRefEvent("GeRti_OM_d");
static class Event *GeRti_OM_e=OM->getRefEvent("GeRti_OM_e");
static class Event *GeRti_OM_i=OM->getRefEvent("GeRti_OM_i");
static class Event *GeRti_OM_w=OM->getRefEvent("GeRti_OM_w");

static class Repository_l *OWM=(Repository::getSingleInstance())->getRepository_l("GeRtiOWM.res","GeRtiOWM");

static class Event *GeRti_OWM_d=OWM->getRefEvent("GeRti_OWM_d");
static class Event *GeRti_OWM_e=OWM->getRefEvent("GeRti_OWM_e");
static class Event *GeRti_OWM_i=OWM->getRefEvent("GeRti_OWM_i");
static class Event *GeRti_OWM_w=OWM->getRefEvent("GeRti_OWM_w");

static class Repository_l *SS=(Repository::getSingleInstance())->getRepository_l("GeRtiSS.res","GeRtiSS");

static class Event *GeRti_SS_d=SS->getRefEvent("GeRti_SS_d");
static class Event *GeRti_SS_e=SS->getRefEvent("GeRti_SS_e");
static class Event *GeRti_SS_i=SS->getRefEvent("GeRti_SS_i");
static class Event *GeRti_SS_w=SS->getRefEvent("GeRti_SS_w");

static class Repository_l *TM=(Repository::getSingleInstance())->getRepository_l("GeRtiTM.res","GeRtiTM");

static class Event *GeRti_TM_d=TM->getRefEvent("GeRti_TM_d");
static class Event *GeRti_TM_e=TM->getRefEvent("GeRti_TM_e");
static class Event *GeRti_TM_i=TM->getRefEvent("GeRti_TM_i");
static class Event *GeRti_TM_w=TM->getRefEvent("GeRti_TM_w");
static class Event *GeRti_TM_mu_d=TM->getRefEvent("GeRti_TM_mu_d");

   // inserted by Gal converter
#endif   // inserted by Gal converter
   // inserted by Gal converter
/*********************************** Gal end *********************************/   // inserted by Gal converter

static char galMsg[512];

// Implementation skeleton constructor
GeRtiFactory_GeRtiAmbassador_i::GeRtiFactory_GeRtiAmbassador_i(PortableServer::POA_ptr thePOA, GERTICO::FederationManagement &theFederationManagement, GERTICO::NextHandle &theIdHandler, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory) : federationManagement(theFederationManagement), geRtiFedTimeFactory(theGeRtiFedTimeFactory), geRtiLogicalTimeIntervalFactory(theGeRtiLogicalTimeIntervalFactory)
{
  fedId = theIdHandler.nextHandle ();
  myPOA = PortableServer::POA::_duplicate(thePOA);
  GeRtiAmVar = _this ();
  privilegeToDeleteId = federationManagement.objectManagement->getPrivilegeToDeleteId();
}

// Implementation skeleton destructor
GeRtiFactory_GeRtiAmbassador_i::~GeRtiFactory_GeRtiAmbassador_i (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::convertInteraction(GeRtiFactory::InteractionClassData_out &theInteractionData, GERTICO::AttributeDatum &theInteractionDatum)
{
  theInteractionData->name = CORBA::wstring_dup(theInteractionDatum.name.c_str());
  theInteractionData->theOrderType = theInteractionDatum.theOrderType;
  theInteractionData->theTransportationType = theInteractionDatum.theTransportationType;
  GERTICO::Mapper::mapHandleSet(theInteractionData->theDimensions, theInteractionDatum.theDimensions);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::convertParameter(GeRtiFactory::ParametersClassData_out &theParameterData, GeRtiFactory::GeRtiHandle const &theClass, GERTICO::LRCparameterFlagsMap &theLRCparameterFlagsMap)
{
  CORBA::ULong i;
  CORBA::ULong ul;
  GERTICO::LRCparameterFlagsMap::iterator itLRCparameterFlagsMap;

  GERTICO::Mapper::mapULongSizet(ul, theLRCparameterFlagsMap.size());
  theParameterData->length(ul);
  for (i = 0, itLRCparameterFlagsMap = theLRCparameterFlagsMap.begin(); itLRCparameterFlagsMap != theLRCparameterFlagsMap.end(); itLRCparameterFlagsMap++, i++)
  {
    theParameterData[i].theId = itLRCparameterFlagsMap->first;
    theParameterData[i].name = CORBA::wstring_dup(itLRCparameterFlagsMap->second.name.c_str());
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::convert(GeRtiFactory::ItemsClassData_out &theAttributes, GERTICO::LRCattributeFlagsMap &theLRCattributeFlagsMap)
{
  CORBA::ULong i;
  CORBA::ULong ul;
  GERTICO::LRCattributeFlagsMap::iterator itLRCattributeFlagsMap;

  GERTICO::Mapper::mapULongSizet(ul, theLRCattributeFlagsMap.size());
  theAttributes->length(ul);
  for (i = 0, itLRCattributeFlagsMap = theLRCattributeFlagsMap.begin(); itLRCattributeFlagsMap != theLRCattributeFlagsMap.end(); itLRCattributeFlagsMap++, i++)
  {
    theAttributes[i].theId = itLRCattributeFlagsMap->first;
    theAttributes[i].name = CORBA::wstring_dup(itLRCattributeFlagsMap->second.name.c_str());
    theAttributes[i].theOrderType = itLRCattributeFlagsMap->second.ordering;
    theAttributes[i].theTransportationType = itLRCattributeFlagsMap->second.transportation;
    GERTICO::Mapper::mapHandleSet(theAttributes[i].theDimensions, itLRCattributeFlagsMap->second.dimensions);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::deactivateObject(void)
{
  PortableServer::ObjectId_var objectId = myPOA->servant_to_id(this);
  myPOA->deactivate_object(objectId.in());
}

PortableServer::POA_ptr GeRtiFactory_GeRtiAmbassador_i::_default_POA (void)
{
  return PortableServer::POA::_duplicate(myPOA);
}

unsigned long GeRtiFactory_GeRtiAmbassador_i::getId ()
{
  return fedId;
}

void GeRtiFactory_GeRtiAmbassador_i::publishObjectClass (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::Handles & attributeList
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::OwnershipAcquisitionPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = fedId;
                              ul = theClass;
                              sprintf(galMsg, "Federate=%lu,Class=%lu", f, ul);
                              E2(GeRti_DM_i, "publishObjectClass", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributeList);
                              E2(GeRti_DM_i, "publishObjectClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::HandleSet attributeSet;
  GERTICO::HandleSet::iterator itAttribute;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  len = attributeList.length();
  for (i = 0; i < len; i++)
  {
    attributeSet.insert(attributeList[i]);
  }
  // Implicitly published.
  itAttribute = attributeSet.find(privilegeToDeleteId);
  if (itAttribute == attributeSet.end())
  {
    attributeSet.insert(privilegeToDeleteId);
  }

  federationManagement.declarationManagementRTI->publishObjectClass (fedId, theClass, attributeSet);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DM_i, "publishObjectClass", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::unpublishObjectClass (
    GeRtiFactory::GeRtiHandle theClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::OwnershipAcquisitionPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = fedId;
                              ul = theClass;
                              sprintf(galMsg, "federate=%lu,Class=%lu", f, ul);
                              E2(GeRti_DM_i, "unpublishObjectClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.declarationManagementRTI->unpublishObjectClass (fedId, theClass);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                            E2(GeRti_DM_i, "unpublishObjectClass", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::unpublishObjectClassAttributes (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::Handles & attributeList
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::OwnershipAcquisitionPending,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "federate=%lu,Class=%lu", f, ul);
                            E2(GeRti_DM_i, "unpublishObjectClassAttributes", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributeList);
                            E2(GeRti_DM_i, "unpublishObjectClassAttributes", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSet attributeSet;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore();

  GERTICO::Mapper::mapHandleSet(attributeSet, attributeList);
  federationManagement.declarationManagementRTI->unpublishObjectClassAttributes(fedId, theClass, attributeSet);

  // Allow other thread to continue;
  federationManagement.ps->release();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DM_i, "unpublishObjectClassAttributes", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::subscribeObjectClassAttributes (GeRtiFactory::GeRtiHandle theClass, const GeRtiFactory::Handles & attributeList, CORBA::Boolean active)
throw
(
  CORBA::SystemException,
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            if (active)
                            {
                              sprintf(galMsg, "federate=%lu,class=%lu,active", f, ul);
                            }
                            else
                            {
                              sprintf(galMsg, "federate=%lu,class=%lu,passive", f, ul);
                            }
                            E2(GeRti_DM_i, "subscribeObjectClassAttributes", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributeList);
                            E2(GeRti_DM_i, "subscribeObjectClassAttributes", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  GERTICO::HandleSet attSet;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSet(attSet, attributeList);

  federationManagement.declarationManagementRTI->subscribeObjectClassAttributes(fedId, theClass, attSet, active);

  federationManagement.managementObjectModel->discoverManagerFederation(fedId, theClass);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DM_i, "subscribeObjectClassAttributes", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::unsubscribeObjectClass (GeRtiFactory::GeRtiHandle theClass)
throw
(
  CORBA::SystemException,
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::ObjectClassNotSubscribed,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "federate=%lu,class=%lu", f, ul);
                            E2(GeRti_DM_i, "unsubscribeObjectClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  // Empty set!
  GERTICO::HandleSet attributeSet;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  // Default region denoted by an id of 0.
  federationManagement.declarationManagementRTI->unsubscribeObjectClass(fedId, theClass, attributeSet);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DM_i, "unsubscribeObjectClass", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::unsubscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle theClass, const GeRtiFactory::Handles & attributeList)
throw
(
  CORBA::SystemException,
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
  GERTICO::HandleSet attributeSet;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "federate=%lu,Class=%lu", f, ul);
                            E2(GeRti_DM_i, "unsubscribeObjectClassAttributes", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributeList);
                            E2(GeRti_DM_i, "unsubscribeObjectClassAttributes", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSet(attributeSet, attributeList);

  // Default region denoted by an id of 0.
  federationManagement.declarationManagementRTI->unsubscribeObjectClass(fedId, theClass, attributeSet);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DM_i, "unsubscribeObjectClassAttributes", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::reserveObjectInstanceName (
    const CORBA::WChar * theObjectInstanceName
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::IllegalName,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,name=%ls", f, theObjectInstanceName);
                            E2(GeRti_OM_i, "reserveObjectInstanceName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  std::wstring ws;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapWstringFromWchar(ws, theObjectInstanceName);

  federationManagement.objectManagement->reserveObjectInstanceName(fedId, ws);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                            E2(GeRti_OM_i, "reserveObjectInstanceName", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::registerObjectInstanceWithName (
    GeRtiFactory::GeRtiHandle theClass,
    const CORBA::WChar *theObjectName
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::ObjectAlreadyRegistered,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "federate=%lu,class=%lu,name=%ls", f, ul, theObjectName);
                            E2(GeRti_OM_i, "registerObjectInstanceWithName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GeRtiFactory::GeRtiHandle theObject;
  std::wstring sName;

  GERTICO::Mapper::mapWstringFromWchar(sName, theObjectName);

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  theObject = federationManagement.objectManagement->registerObjectInstance (fedId, theClass, sName);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "Object=%lu", ul);
                              E2(GeRti_OM_i, "registerObjectInstanceWithName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return theObject;
}

GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::registerObjectInstance (
    GeRtiFactory::GeRtiHandle theClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "federate=%lu,class=%lu", f, ul);
                            E2(GeRti_OM_i, "registerObjectInstance", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GeRtiFactory::GeRtiHandle federate;
  GeRtiFactory::GeRtiHandle theObject;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federate = fedId;
  if (federationManagement.managementObjectModel->isMomFederateClass(theClass))
  {
    federate = 1;
  }

  theObject = federationManagement.objectManagement->registerObjectInstance (federate, theClass);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "Object=%lu", ul);
                              E2(GeRti_OM_i, "registerObjectInstance", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return theObject;
}

void GeRtiFactory_GeRtiAmbassador_i::deleteObjectInstance (
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::UserSuppliedTag & theTag
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::DeletePrivilegeNotHeld,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theObject;
                            sprintf(galMsg, "federate=%lu,object=%lu", f, ul);
                            E2(GeRti_OM_i, "deleteObjectInstance", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                            E2(GeRti_OM_i, "deleteObjectInstance", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  // Delete the object.
  federationManagement.objectManagement->deleteObjectInstance (fedId, theObject, theTag);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_i, "deleteObjectInstance", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::deleteObjectInstanceWithTime (
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Time &theTime,
    const GeRtiFactory::UserSuppliedTag & theTag,
    GeRtiFactory::GeRtiHandle theSerialNumber
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::DeletePrivilegeNotHeld,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
//                            char timeBuff[512];
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = theObject;
                            ul1 = theSerialNumber;
                            sprintf(galMsg, "federate=%lu,object=%lu,theSerialNumber=%lu", f, ul, ul1);
                            E2(GeRti_OM_i, "deleteObjectInstanceWithTime", galMsg);   // inserted by Gal converter
//                            geRtiFedTime->getPrintableString(timeBuff);
//                            E2(GeRti_OM_i, "deleteObjectInstanceWithTime", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                            E2(GeRti_OM_i, "deleteObjectInstanceWithTime", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.objectManagement->deleteObjectInstance (fedId, theObject, theTime, theTag, theSerialNumber);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_i, "deleteObjectInstanceWithTime", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::requestObjectAttributeValueUpdate (
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Handles & theAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theObject;
                            sprintf(galMsg, "federate=%lu,Object=%lu", f, ul);
                            E2(GeRti_OM_i, "requestObjectAttributeValueUpdate", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theAttributes);
                            E2(GeRti_OM_i, "requestObjectAttributeValueUpdate", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                            E2(GeRti_OM_i, "requestObjectAttributeValueUpdate", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSet attributeSet;
  GERTICO::RegisteredObject *registeredObject;
  GeRtiFactory::GeRtiHandle objectClass;
  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  registeredObject = federationManagement.objectManagement->getObject(theObject);
  objectClass = registeredObject->getClassId();

  GERTICO::Mapper::mapHandleSet(attributeSet, theAttributes);
  if (federationManagement.managementObjectModel->requestObjectAttributeValueUpdate(theObject, attributeSet))
  {
    federationManagement.ps->release ();
    return;
  }

  federationManagement.objectManagement->requestObjectAttributeValueUpdate(fedId, theObject, theAttributes, theTag);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_i, "requestObjectAttributeValueUpdate", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::requestClassAttributeValueUpdate (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::Handles & theAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag
)
throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "federate=%lu,class=%lu", f, ul);
                            E2(GeRti_OM_i, "requestClassAttributeValueUpdate", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, theAttributes);
                            E2(GeRti_DM_i, "requestClassAttributeValueUpdate", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                            E2(GeRti_OM_i, "requestClassAttributeValueUpdate", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSet attributeSet;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSet(attributeSet, theAttributes);
  if (federationManagement.managementObjectModel->requestClassAttributeValueUpdate(theClass, attributeSet))
  {
    federationManagement.ps->release ();
    return;
  }

  federationManagement.objectManagement->requestClassAttributeValueUpdate(fedId, theClass, theAttributes, theTag);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_i, "requestClassAttributeValueUpdate", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::localDeleteObjectInstance (
    GeRtiFactory::GeRtiHandle theObject
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::FederateOwnsAttributes,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theObject;
                            sprintf(galMsg, "federate=%lu,object=%lu", f, ul);
                            E2(GeRti_OM_i, "localDeleteObjectInstance", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.objectManagement->localDeleteObjectInstance (fedId, theObject);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_OM_i, "localDeleteObjectInstance", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::enableClassRelevanceAdvisorySwitch (
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu", f);
                            E2(GeRti_SS_i, "enableClassRelevanceAdvisorySwitch", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.supportingServices->enableClassRelevanceAdvisorySwitch(fedId);

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_SS_i, "enableClassRelevanceAdvisorySwitch", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::disableClassRelevanceAdvisorySwitch (

  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu", f);
                            E2(GeRti_SS_i, "disableClassRelevanceAdvisorySwitch", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.supportingServices->disableClassRelevanceAdvisorySwitch(fedId);

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_SS_i, "disableClassRelevanceAdvisorySwitch", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::enableAttributeScopeAdvisorySwitch (
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )

{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu", f);
                            E2(GeRti_SS_i, "enableAttributeScopeAdvisorySwitch", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.supportingServices->enableAttributeScopeAdvisorySwitch(fedId);

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_SS_i, "enableAttributeScopeAdvisorySwitch", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}
void GeRtiFactory_GeRtiAmbassador_i::disableAttributeScopeAdvisorySwitch (

  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu", f);
                            E2(GeRti_SS_i, "disableAttributeScopeAdvisorySwitch", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.supportingServices->disableAttributeScopeAdvisorySwitch(fedId);

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_SS_i, "disableAttributeScopeAdvisorySwitch", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}


void GeRtiFactory_GeRtiAmbassador_i::registerFederationSynchronizationPointWithDesignators (
    const CORBA::WChar *theLabel,
    const GeRtiFactory::UserSuppliedTag & theTag,
    const GeRtiFactory::Handles & designators
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  std::wstring label;

  federationManagement.setAlive(fedId);
  GERTICO::Mapper::mapWstringFromWchar(label, theLabel);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,label=%ls", f, theLabel);
                            E2(GeRti_FM_sync_i, "registerFederationSynchronizationPointWithDesignators", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                            E2(GeRti_FM_sync_i, "registerFederationSynchronizationPointWithDesignators", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryHandles("designators=", galMsg, designators);
                            E2(GeRti_FM_sync_i, "registerFederationSynchronizationPointWithDesignators", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.registerSynchronizationPoint(fedId, label, theTag, designators);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_sync_i, "registerFederationSynchronizationPointWithDesignators", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::registerFederationSynchronizationPoint (
    const CORBA::WChar *theLabel,
    const GeRtiFactory::UserSuppliedTag & theTag
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  GeRtiFactory::Handles dummy;
  std::wstring label;

  federationManagement.setAlive(fedId);
  GERTICO::Mapper::mapWstringFromWchar(label, theLabel);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_sync_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,label=%ls", f, theLabel);
                            E2(GeRti_FM_sync_i, "registerFederationSynchronizationPoint", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                            E2(GeRti_FM_sync_i, "registerFederationSynchronizationPoint", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.registerSynchronizationPoint(fedId, label, theTag, dummy);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_sync_i, "registerFederationSynchronizationPoint", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::synchronizationPointAchieved (
    const CORBA::WChar *theLabel
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SynchronizationPointLabelWasNotAnnounced,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_sync_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,label=%ls", f, theLabel);
                            E2(GeRti_FM_sync_i, "synchronizationPointAchieved", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  std::wstring label;

  GERTICO::Mapper::mapWstringFromWchar(label, theLabel);

  federationManagement.setAlive(fedId);
  federationManagement.synchronizationPointAchieved(label, fedId);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_sync_i, "synchronizationPointAchieved", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::requestFederationSaveWithTime (
    const CORBA::WChar *theLabel,
    const GeRtiFactory::Time &theTime
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederationTimeAlreadyPassed,
    GeRtiFactory::InvalidFederationTime,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  char buff[1024];
  std::wstring label;
  std::auto_ptr<GERTICO::GeRtiFedTime> fedTime;

  GERTICO::Mapper::mapWstringFromWchar(label, theLabel);
  GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, fedTime, theTime);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_save_restore_i)
                            {
                            unsigned long f;

                            f = fedId;
                            fedTime->getPrintableString(buff);
                            sprintf(galMsg, "federate=%lu,logicalTime=%s,label=%ls", f, buff, theLabel);
                            E2(GeRti_FM_save_restore_i, "requestFederationSaveWithTime", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.requestFederationSave(fedId, label, *fedTime);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_save_restore_i, "requestFederationSaveWithTime", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::requestFederationSave (
    const CORBA::WChar *theLabel
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  std::wstring label;

  GERTICO::Mapper::mapWstringFromWchar(label, theLabel);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_save_restore_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,label=%ls", f, theLabel);
                            E2(GeRti_FM_save_restore_i, "requestFederationSave", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.requestFederationSave(fedId, label);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_save_restore_i, "requestFederationSave", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::federateSaveBegun (
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SaveNotInitiated,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_save_restore_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu", f);
                            E2(GeRti_FM_save_restore_i, "federateSaveBegun", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.federateSaveBegun (fedId);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_save_restore_i, "federateSaveBegun", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::federateSaveComplete (
    CORBA::Boolean theSuccess,
    const char *theSaveData
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SaveNotInitiated,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_save_restore_i)
                            {
                            unsigned long f;

                            f = fedId;
                            if (theSuccess)
                            {
                              sprintf(galMsg, "federate=%lu,sucess", f);
                            }
                            else
                            {
                              sprintf(galMsg, "federate=%lu,failure", f);
                            }
                            E2(GeRti_FM_save_restore_i, "federateSaveComplete", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  std::string s(theSaveData);
  federationManagement.setAlive(fedId);
  federationManagement.federateSaveComplete(fedId, theSuccess, s);

  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_save_restore_i, "federateSaveComplete", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::queryFederationSaveStatus()
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_save_restore_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu", f);
                            E2(GeRti_FM_save_restore_i, "queryFederationSaveStatus", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  federationManagement.setAlive(fedId);
  // XXX Need to set a job to return the save status
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::requestFederationRestore (
    const CORBA::WChar *theLabel
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  std::wstring label;

  GERTICO::Mapper::mapWstringFromWchar(label, theLabel);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_save_restore_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,label=%ls", f, theLabel);
                            E2(GeRti_FM_save_restore_i, "requestFederationRestore", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.requestFederationRestore(fedId, label);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_save_restore_i, "requestFederationRestore", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::federateRestoreComplete (
    CORBA::Boolean success
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RestoreNotRequested,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_save_restore_i)
                            {
                            unsigned long f;

                            f = fedId;
                            if (success)
                            {
                              sprintf(galMsg, "federate=%lu,sucess", f);
                            }
                            else
                            {
                              sprintf(galMsg, "federate=%lu,failure", f);
                            }
                            E2(GeRti_FM_save_restore_i, "federateRestoreComplete", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.federateRestoreComplete (fedId, success);

  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_save_restore_i, "federateRestoreComplete", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::queryFederationRestoreStatus()
  throw (
    CORBA::SystemException,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_save_restore_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu", f);
                            E2(GeRti_FM_save_restore_i, "queryFederationRestoreStatus", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  federationManagement.setAlive(fedId);
  // XXX Need to set a job to return the restore status
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::requestFederateSaveStart (
    const CORBA::WChar *theLabel,
    const GeRtiFactory::Time & theTime,
    CORBA::Boolean timeBoolean
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::StartNotAllowed,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  std::auto_ptr<GERTICO::GeRtiFedTime> fedTime;
  bool timeUsed = false;
  std::wstring label;

  GERTICO::Mapper::mapWstringFromWchar(label, theLabel);

  if (timeBoolean)
  {
    GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(geRtiFedTimeFactory, fedTime, theTime);
  }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_save_restore_i)
                            {
                            char buff[1024];
                            unsigned long f;

                            f = fedId;
                            if (timeBoolean)
                            {
                              fedTime->getPrintableString(buff);
                              sprintf(galMsg, "federate=%lu,label=%ls,Time=%s", f, theLabel,buff);
                            }
                            else
                            {
                              sprintf(galMsg, "federate=%lu,label=%ls", f, theLabel);
                            }
                            E2(GeRti_FM_save_restore_i, "requestFederateSaveStart", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  if (timeBoolean)
  {
    timeUsed = true;
  }
  federationManagement.setAlive(fedId);
  federationManagement.requestFederateSaveStart(fedId, label, theTime, timeUsed);

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_FM_save_restore_i, "requestFederateSaveStart", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}
    //////////////////////////
    // Ownership Management //
    //////////////////////////

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getPrivilegeToDeleteId ()
  throw (CORBA::SystemException)
{
  return federationManagement.runTimeObjectDB->getPrivilegeToDeleteId();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::unconditionalAttributeOwnershipDivestiture (
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
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = fedId;
                              ul = theObject;
                              sprintf(galMsg, "unconditionalAttributeOwnershipDivestiture(federate=%lu,object=%lu", f, ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_i, galMsg);
                            }
                           #endif
  federationManagement.setAlive(fedId);
  federationManagement.ownershipMaster->unconditionalAttributeOwnershipDivestiture(fedId, theObject, theAttributes);
                           #ifdef GalDebug
                            E2(GeRti_OWM_i, "unconditionalAttributeOwnershipDivestiture", "leave");   // inserted by Gal converter
                           #endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::negotiatedAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Handles & theAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag
  )
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
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = fedId;
                              ul = theObject;
                              sprintf(galMsg, "negotiatedAttributeOwnershipDivestiture(federate=%lu,object=%lu", f, ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], theTag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_i, galMsg);
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.ownershipMaster->negotiatedAttributeOwnershipDivestiture(fedId, theObject, theAttributes, theTag);

                           #ifdef GalDebug
                            E2(GeRti_OWM_i, "negotiatedAttributeOwnershipDivestiture", "leave");
                           #endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::attributeOwnershipAcquisition (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Handles & desiredAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag
  )
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
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = fedId;
                              ul = theObject;
                              sprintf(galMsg, "attributeOwnershipAcquisition(federate=%lu,object=%lu", f, ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], desiredAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], theTag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_i, galMsg);
                            }
                           #endif
  federationManagement.setAlive(fedId);
  federationManagement.ownershipMaster->attributeOwnershipAcquisition(fedId, theObject, desiredAttributes, theTag);
                           #ifdef GalDebug
                            E2(GeRti_OWM_i, "attributeOwnershipAcquisition", "leave");
                           #endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::attributeOwnershipAcquisitionIfAvailable (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Handles & desiredAttributes
  )
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
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = fedId;
                              ul = theObject;
                              sprintf(galMsg, "attributeOwnershipAcquisitionIfAvailable(federate=%lu,object=%lu", f, ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], desiredAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_i, galMsg);
                            }
                           #endif
  federationManagement.setAlive(fedId);
  federationManagement.ownershipMaster->attributeOwnershipAcquisitionIfAvailable(fedId, theObject, desiredAttributes);
                           #ifdef GalDebug
                            E2(GeRti_OWM_i, "attributeOwnershipAcquisitionIfAvailable", "leave");
                           #endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::Handles * GeRtiFactory_GeRtiAmbassador_i::attributeOwnershipDivestitureIfWanted (
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
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = fedId;
                              ul = theObject;
                              sprintf(galMsg, "attributeOwnershipDivestitureIfWanted(federate=%lu,object=%lu", f, ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              strcat(galMsg, ") enterLeave");
                              E1(GeRti_OWM_i, galMsg);
                            }
                           #endif
  federationManagement.setAlive(fedId);
  return federationManagement.ownershipMaster->attributeOwnershipDivestitureIfWanted(fedId, theObject, theAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::Handles * GeRtiFactory_GeRtiAmbassador_i::confirmDivestiture (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Handles & theAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag
  )
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
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = fedId;
                              ul = theObject;
                              sprintf(galMsg, "confirmDivestiture(federate=%lu,object=%lu", f, ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], theTag);
                              strcat(galMsg, ") enterLeave");
                              E1(GeRti_OWM_i, galMsg);
                            }
                           #endif
  federationManagement.setAlive(fedId);
  return federationManagement.ownershipMaster->confirmDivestiture(fedId, theObject, theAttributes, theTag);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::cancelNegotiatedAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Handles & theAttributes
  )
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
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = fedId;
                              ul = theObject;
                              sprintf(galMsg, "cancelNegotiatedAttributeOwnershipDivestiture(federate=%lu,object=%lu", f, ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_i, galMsg);
                            }
                           #endif
  federationManagement.setAlive(fedId);
  federationManagement.ownershipMaster->cancelNegotiatedAttributeOwnershipDivestiture(fedId, theObject, theAttributes);
                           #ifdef GalDebug
                            E2(GeRti_OWM_i, "cancelNegotiatedAttributeOwnershipDivestiture", "leave");
                           #endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::cancelAttributeOwnershipAcquisition (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::Handles & theAttributes
  )
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
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              unsigned long f;
                              unsigned long ul;

                              f = fedId;
                              ul = theObject;
                              sprintf(galMsg, "cancelAttributeOwnershipAcquisition(federate=%lu,object=%lu", f, ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_i, galMsg);
                            }
                           #endif
  federationManagement.setAlive(fedId);
  federationManagement.ownershipMaster->cancelAttributeOwnershipAcquisition(fedId, theObject, theAttributes);
                           #ifdef GalDebug
                            E2(GeRti_OWM_i, "cancelAttributeOwnershipAcquisition", "leave");
                           #endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::queryAttributeOwnership (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle theObject,
    GeRtiFactory::GeRtiHandle theAttribute
  )
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
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              unsigned long f;
                              unsigned long ul;
                              unsigned long ul1;

                              f = fedId;
                              ul = theObject;
                              ul1 = theAttribute;
                              sprintf(galMsg, "queryAttributeOwnership(federate=%lu,object=%lu,attribute=%lu) enter", f, ul,ul1);
                              E1(GeRti_OWM_i, galMsg);
                            }
                           #endif
  federationManagement.setAlive(fedId);
  federationManagement.ownershipMaster->queryAttributeOwnership(fedId, theObject, theAttribute);
                           #ifdef GalDebug
                            E2(GeRti_OWM_i, "queryAttributeOwnership", "leave");
                           #endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::Boolean GeRtiFactory_GeRtiAmbassador_i::isAttributeOwnedByFederate (
    GeRtiFactory::GeRtiHandle fedId,
    GeRtiFactory::GeRtiHandle theObject,
    GeRtiFactory::GeRtiHandle theAttribute
  )
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
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_i)
                            {
                              unsigned long f;
                              unsigned long ul;
                              unsigned long ul1;

                              f = fedId;
                              ul = theObject;
                              ul1 = theAttribute;
                              sprintf(galMsg, "isAttributeOwnedByFederate(federate=%lu,object=%lu,attribute=%lu) enterLeave", f, ul,ul1);
                              E1(GeRti_OWM_i, galMsg);
                            }
                           #endif
  federationManagement.setAlive(fedId);
  return federationManagement.ownershipMaster->isAttributeOwnedByFederate(fedId, theObject, theAttribute);
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::processUnpublishOwnershipCandidate
(
  GeRtiFactory::GeRtiHandle theFederate,
  GeRtiFactory::GeRtiHandle theClass,
  const GeRtiFactory::Handles & theAttributes
)
throw
(
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
)
{
  GERTICO::HandleSet attributes;
  GERTICO::Mapper::mapHandleSet(attributes, theAttributes);

  federationManagement.ownershipMaster->processUnpublishOwnershipCandidate(theFederate, theClass, attributes);
}

    /////////////////////////////////////
    // Declaration Management Services //
    /////////////////////////////////////
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::createRegion (
    GeRtiFactory::GeRtiHandle theSpace,
    CORBA::ULong numberOfExtents,
    const GeRtiFactory::Handles & theDimensions
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SpaceNotDefined,
    GeRtiFactory::InvalidExtents,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
#ifndef IEEE_1516
                            unsigned long ul;
                            unsigned long ul1;
#endif

                            f = fedId;
#ifdef IEEE_1516
                            sprintf(galMsg, "federate=%lu", f);
#else
                            ul = theSpace;
                            ul1 = numberOfExtents;
                            sprintf(galMsg, "federate=%lu,space=%lu,numberOfExtents=%lu", f, ul, ul1);
#endif
                            E2(GeRti_DDM_i, "createRegion", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryHandles("dimensions=", galMsg, theDimensions);
                            E2(GeRti_DDM_i, "createRegion", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSet dimensions;
  GeRtiFactory::GeRtiHandle id;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSet(dimensions, theDimensions);
  id = federationManagement.dataDistributionManagement->createRegion(fedId, theSpace, numberOfExtents, dimensions);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long ul2;
                            ul2 = id;
                            sprintf(galMsg, "region=%lu", ul2);
                            E2(GeRti_DDM_i, "createRegion", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::modifyRegion (
    GeRtiFactory::GeRtiHandle theRegion,
    const GeRtiFactory::Extents & theExtents
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidExtents,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theRegion;
                            sprintf(galMsg, "federate=%lu,region=%lu", f, ul);
                            E2(GeRti_DDM_i, "modifyRegion", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.dataDistributionManagement->modifyRegion (fedId, theRegion, theExtents);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "modifyRegion", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::deleteRegion (
    GeRtiFactory::GeRtiHandle theRegion
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::RegionInUse,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theRegion;
                            sprintf(galMsg, "federate=%lu,region=%lu", f, ul);
                            E2(GeRti_DDM_i, "deleteRegion", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.dataDistributionManagement->deleteRegion (fedId, theRegion);

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "deleteRegion", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::registerObjectInstanceWithNameWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions,
    const CORBA::WChar *theObjectName
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::ObjectClassNotPublished,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::ObjectAlreadyRegistered,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
  GERTICO::HandleSetMap attRegMap;
  GeRtiFactory::GeRtiHandle theObject;
  std::wstring sName;

  GERTICO::Mapper::mapWstringFromWchar(sName, theObjectName);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "Federate=%lu,Class=%lu,Name=%ls", f, ul, theObjectName);
                            E2(GeRti_DDM_i, "registerObjectInstanceWithNameWithRegion", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryAttributeRegionsSeq("attributeRegions=", galMsg, theAttributeRegions);
                            E2(GeRti_DDM_i, "registerObjectInstanceWithNameWithRegion", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSetMapFromAttributeRegionsSeq(attRegMap, theAttributeRegions);
  theObject = federationManagement.dataDistributionManagement->registerObjectInstanceWithRegion(fedId, theClass, sName, attRegMap);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "Object=%lu", ul);
                              E2(GeRti_DDM_i, "registerObjectInstanceWithNameWithRegion", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  return theObject;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::registerObjectInstanceWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions
  )
  throw (
  CORBA::SystemException,
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::ObjectClassNotPublished,
  GeRtiFactory::AttributeNotDefined,
  GeRtiFactory::AttributeNotPublished,
  GeRtiFactory::RegionNotKnown,
  GeRtiFactory::InvalidRegionContext,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::SaveInProgress,
  GeRtiFactory::RestoreInProgress,
  GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "Federate=%lu,Class=%lu", f, ul);
                            E2(GeRti_DDM_i, "registerObjectInstanceWithRegions", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryAttributeRegionsSeq("attributeRegions=", galMsg, theAttributeRegions);
                            E2(GeRti_DDM_i, "registerObjectInstanceWithRegions", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSetMap attRegMap;
  GeRtiFactory::GeRtiHandle theObject;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSetMapFromAttributeRegionsSeq(attRegMap, theAttributeRegions);
  theObject = federationManagement.dataDistributionManagement->registerObjectInstanceWithRegion(fedId, theClass, attRegMap);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg, "object=%lu", ul);
                              E2(GeRti_DDM_i, "registerObjectInstanceWithRegion", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  return theObject;
}

void GeRtiFactory_GeRtiAmbassador_i::subscribeObjectClassAttributesWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions,
    CORBA::Boolean active
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            if (active)
                            {
                              sprintf(galMsg, "Federate=%lu,Class=%lu,active", f, ul);
                            }
                            else
                            {
                              sprintf(galMsg, "Federate=%lu,Class=%lu,passive", f, ul);
                            }
                            E2(GeRti_DDM_i, "subscribeObjectClassAttributesWithRegions", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryAttributeRegionsSeq("attributeRegions=", galMsg, theAttributeRegions);
                            E2(GeRti_DDM_i, "subscribeObjectClassAttributesWithRegions", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSetMap attRegMap;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSetMapFromAttributeRegionsSeq(attRegMap, theAttributeRegions);
  federationManagement.dataDistributionManagement->subscribeObjectClassAttributesWithRegions(fedId, theClass, attRegMap, active);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "subscribeObjectClassAttributesWithRegion", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::unsubscribeObjectClassWithRegion (
    GeRtiFactory::GeRtiHandle theClass,
    GeRtiFactory::GeRtiHandle theRegion
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::ObjectClassNotSubscribed,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = theClass;
                            ul1 = theRegion;
                            sprintf(galMsg, "federate=%lu,class=%lu,region=%lu", f, ul, ul1);
                            E2(GeRti_DDM_i, "unsubscribeObjectClassWithRegion", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.dataDistributionManagement->unsubscribeObjectClassWithRegion(fedId, theClass, theRegion);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "unsubscribeObjectClassWithRegion", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::unsubscribeObjectClassWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::ObjectClassNotSubscribed,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "Federate=%lu,Class=%lu", f, ul);
                            E2(GeRti_DDM_i, "unsubscribeObjectClassWithRegions", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryAttributeRegionsSeq("attributeRegions=", galMsg, theAttributeRegions);
                            E2(GeRti_DDM_i, "unsubscribeObjectClassWithRegions", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSetMap attRegMap;
  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSetMapFromAttributeRegionsSeq(attRegMap, theAttributeRegions);
  federationManagement.dataDistributionManagement->unsubscribeObjectClassWithRegions(fedId, theClass, attRegMap);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "unsubscribeObjectClassWithRegions", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::subscribeInteractionClassWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    CORBA::Boolean active,
    const GeRtiFactory::Handles &theRegions
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::FederateLoggingServiceCalls,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            if (active)
                            {
                              sprintf(galMsg, "Federate=%lu,Class=%lu,active", f, ul);
                            }
                            else
                            {
                              sprintf(galMsg, "Federate=%lu,Class=%lu,passive", f, ul);
                            }
                            E2(GeRti_DDM_i, "subscribeInteractionClassWithRegions", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryHandles("regions=", galMsg, theRegions);
                            E2(GeRti_DDM_i, "subscribeInteractionClassWithRegions", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSet regions;
  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSet(regions, theRegions);
  federationManagement.dataDistributionManagement->subscribeInteractionClass(fedId, theClass, active, regions);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "subscribeInteractionClassWithRegion", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::unsubscribeInteractionClassWithRegions (
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::Handles & theRegions
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::InteractionClassNotSubscribed,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "Federate=%lu,Class=%lu", f, ul);
                            E2(GeRti_DDM_i, "unsubscribeInteractionClassWithRegion", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryHandles("regions=", galMsg, theRegions);
                            E2(GeRti_DDM_i, "unsubscribeInteractionClassWithRegions", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSet regions;
  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSet(regions, theRegions);
  federationManagement.dataDistributionManagement->unsubscribeInteractionClassWithRegions(fedId, theClass, regions);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "unsubscribeInteractionClassWithRegion", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

void GeRtiFactory_GeRtiAmbassador_i::requestAttributeValueUpdateWithRegions
(
    GeRtiFactory::GeRtiHandle theClass,
    const GeRtiFactory::AttributeRegionsSeq & theAttributeRegions,
    const GeRtiFactory::UserSuppliedTag & theTag
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "federate=%lu,class=%lu", f, ul);
                            E2(GeRti_DDM_i, "requestAttributeValueUpdateWithRegion", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, theTag);
                            E2(GeRti_DDM_i, "requestAttributeValueUpdateWithRegions", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryAttributeRegionsSeq("attributeRegions=", galMsg, theAttributeRegions);
                            E2(GeRti_DDM_i, "requestAttributeValueUpdateWithRegions", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSetMap attributeRegionsSet;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSetMapFromAttributeRegionsSeq(attributeRegionsSet, theAttributeRegions);
#ifdef IEEE_1516
  try
  {
#endif
    federationManagement.dataDistributionManagement->requestAttributeValueUpdateWithRegions(fedId, theClass, attributeRegionsSet, theTag);
#ifdef IEEE_1516
  }
  catch(GeRtiFactory::InvalidRegionContext &)
  {
    CORBA::WChar *wChar = L"requestAttributeValueUpdateWithRegions";
    throw GeRtiFactory::RegionNotKnown(wChar);
  }
#endif

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "requestAttributeValueUpdateWithRegion", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::associateRegionsForUpdates (
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theObject;
                            sprintf(galMsg, "federate=%lu,object=%lu", f, ul);
                            E2(GeRti_DDM_i, "associateRegionForUpdates", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryAttributeRegionsSeq("attributeRegions=", galMsg, theAttributeRegions);
                            E2(GeRti_DDM_i, "associateRegionsForUpdates", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSetMap attributeRegionsSet;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSetMapFromAttributeRegionsSeq(attributeRegionsSet, theAttributeRegions);
  federationManagement.dataDistributionManagement->associateRegionsForUpdates(fedId, theObject, attributeRegionsSet);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "associateRegionForUpdates", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::unassociateRegionForUpdates (
    GeRtiFactory::GeRtiHandle theRegion,
    GeRtiFactory::GeRtiHandle theObject
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = theRegion;
                            ul1 = theObject;
                            sprintf(galMsg, "federate=%lu,region=%lu,object=%lu", f, ul, ul1);
                            E2(GeRti_DDM_i, "unassociateRegionForUpdates", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  federationManagement.dataDistributionManagement->unassociateRegionForUpdates (fedId, theRegion, theObject);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "unassociateRegionForUpdates", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::unassociateRegionsForUpdates (
    GeRtiFactory::GeRtiHandle theObject,
    const GeRtiFactory::AttributeRegionsSeq &theAttributeRegions
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::InvalidRegionContext,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DDM_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theObject;
                            sprintf(galMsg, "federate=%lu,object=%lu", f, ul);
                            E2(GeRti_DDM_i, "unassociateRegionForUpdates", galMsg);   // inserted by Gal converter
                            GERTICO::Mapper::printGeRtiFactoryAttributeRegionsSeq("attributeRegions=", galMsg, theAttributeRegions);
                            E2(GeRti_DDM_i, "unassociateRegionsForUpdates", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GERTICO::HandleSetMap attributeRegionsSet;

  federationManagement.setAlive(fedId);
  // Check save/restore status and possibly throw an exception.
  federationManagement.checkSaveRestore ();

  GERTICO::Mapper::mapHandleSetMapFromAttributeRegionsSeq(attributeRegionsSet, theAttributeRegions);
  federationManagement.dataDistributionManagement->unassociateRegionsForUpdates(fedId, attributeRegionsSet, theObject);

  // Allow other thread to continue;
  federationManagement.ps->release ();

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "unassociateRegionForUpdates", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getObjectClass (
    GeRtiFactory::GeRtiHandle theObject
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theObject;
                            sprintf(galMsg, "federate=%lu,object=%lu", f, ul);
                            E2(GeRti_SS_i, "getObjectClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  GeRtiFactory::GeRtiHandle ret;

  federationManagement.setAlive(fedId);
  ret = federationManagement.supportingServices->getObjectClass(fedId, theObject);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                              unsigned long ul;

                              ul = ret;
                              sprintf(galMsg, "class=%lu", ul);
                              E2(GeRti_SS_i, "getObjectClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getAttributeHandle (
    const CORBA::WChar *theName,
    GeRtiFactory::GeRtiHandle whichClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  )

{
  CORBA::WChar *wChar = L"";
  bool foundClass = false;
  bool foundItem = false;
  GeRtiFactory::GeRtiHandle ret = 0;
  std::wstring name;

  // Recursive search.
  GERTICO::Mapper::mapWstringFromWchar(name, theName);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = whichClass;
                            sprintf(galMsg, "federate=%lu,class=%lu,name=%ls", f, ul, theName);
                            E2(GeRti_SS_i, "getAttributeHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.supportingServices->getObjectClassItem(name, whichClass, ret, foundItem, foundClass);
  if (foundClass == false)
  {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = whichClass;
                            sprintf(galMsg, "federate=%lu,class=%lu,name=%ls", f, ul, theName);
                            E2(GeRti_SS_i, "getAttributeHandle:ObjectClassNotDefined", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::ObjectClassNotDefined(wChar);
  }
  if (foundItem == false)
  {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = whichClass;
                            sprintf(galMsg, "federate=%lu,class=%lu,name=%ls", f, ul, theName);
                            E2(GeRti_SS_i, "getAttributeHandle:NameNotFound", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::NameNotFound(wChar);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                              unsigned long ul;

                              ul = ret;
                              sprintf(galMsg, "class=%lu", ul);
                              E2(GeRti_SS_i, "getAttributeHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

CORBA::WChar *GeRtiFactory_GeRtiAmbassador_i::getAttributeName (
    GeRtiFactory::GeRtiHandle handle,
    GeRtiFactory::GeRtiHandle whichClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )

{
  bool foundClass = false;
  bool foundItem = false;
  CORBA::WChar *ret;
  CORBA::WChar *wChar = L"getAttributeName";
  std::wstring name;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = handle;
                            ul1 = whichClass;
                            sprintf(galMsg, "federate=%lu,handle=%lu,class=%lu", f, ul, ul1);
                            E2(GeRti_SS_i, "getAttributeName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.supportingServices->getObjectClassItem(handle, whichClass, name, foundItem, foundClass);
  if (foundClass == false)
  {
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = handle;
                            ul1 = whichClass;
                            sprintf(galMsg, "federate=%lu,handle=%lu,class=%lu", f, ul, ul1);
                            E2(GeRti_SS_i, "getAttributeName;ObjectClassNotDefined", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::ObjectClassNotDefined(wChar);
  }
  if (foundItem == false)
  {
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = handle;
                            ul1 = whichClass;
                            sprintf(galMsg, "federate=%lu,handle=%lu,class=%lu", f, ul, ul1);
                            E2(GeRti_SS_i, "getAttributeName;AttributeNotDefined", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::AttributeNotDefined(wChar);
  }
  GERTICO::Mapper::mapWcharFromWstring(&ret, name);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            sprintf(galMsg, "name=%ls", name.c_str());
                            E2(GeRti_SS_i, "getAttributeName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getObjectInstanceHandle
(
  const CORBA::WChar *theName
)
throw
(
  CORBA::SystemException,
  GeRtiFactory::ObjectNotKnown,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::RTIinternalError,
  GeRtiFactory::ConcurrentAccessAttempted
)
{
  CORBA::WChar *wChar = L"getObjectInstanceHandle";
  GERTICO::RegisteredObject *currObject;
  unsigned long ret;
  std::wstring ws;

  GERTICO::Mapper::mapWstringFromWchar(ws, theName);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,name=%ls", f, theName);
                            E2(GeRti_SS_i, "getObjectInstanceHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  currObject = federationManagement.supportingServices->getObjectByName(ws);
  if (currObject == NULL)
  {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,name=%ls", f, theName);
                            E2(GeRti_SS_i, "getObjectInstanceHandle:ObjectNotKnown", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::ObjectNotKnown(wChar);
  }

  ret = currObject->getId ();

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long ul;
                            ul = ret;
                            sprintf(galMsg, "class=%lu", ul);
                            E2(GeRti_SS_i, "getObjectInstanceHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

CORBA::WChar *GeRtiFactory_GeRtiAmbassador_i::getObjectInstanceName (
    GeRtiFactory::GeRtiHandle handle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )

{
  CORBA::WChar *ret;
  CORBA::WChar *wChar = L"getObjectInstanceName";
  GERTICO::RegisteredObject *currObject;
  std::wstring ws;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = handle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_i, "getObjectInstanceName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  currObject = federationManagement.supportingServices->getObjectById(handle);
  if (currObject == NULL)
  {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = handle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_i, "getObjectInstanceName:ObjectNotKnown", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::ObjectNotKnown(wChar);
  }

  currObject->getName(ws);
  GERTICO::Mapper::mapWcharFromWstring(&ret, ws);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            sprintf(galMsg, "name=%ls", ws.c_str());
                            E2(GeRti_SS_i, "getObjectInstanceName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getInteractionClassHandle
(
  const CORBA::WChar *theName,
  GeRtiFactory::Handles_out parents,
  GeRtiFactory::InteractionClassData_out interactionData,
  GeRtiFactory::ParametersClassData_out parameters
)
throw
(
  CORBA::SystemException,
  GeRtiFactory::NameNotFound,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError
)
{
  CORBA::WChar *wChar = L"getInteractionClassHandle";
  GERTICO::LRCparameterFlagsMap lrcParameterFlagsMap;
  GERTICO::AttributeDatum interactionDatum;
  GeRtiFactory::GeRtiHandle currClass;
  GeRtiFactory::GeRtiHandle ret;
  GeRtiFactory::GeRtiHandle size;
  std::wstring name;
  std::wstring ws;

  parents = new GeRtiFactory::Handles();
  interactionData = new GeRtiFactory::InteractionClassData();
  parameters = new GeRtiFactory::ParametersClassData();

  GERTICO::Mapper::mapWstringFromWchar(name, theName);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,name=%ls", f, theName);
                            E2(GeRti_SS_i, "getInteractionClassHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  ret = federationManagement.supportingServices->getInteractionClassHandle(name);
  if (ret == 0)
  {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,name=%ls", f, theName);
                            E2(GeRti_SS_i, "getInteractionClassHandle:NameNotFound", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::NameNotFound(wChar);
  }

  currClass = ret;
  for (size = 0;; size++)
  {
    currClass = federationManagement.supportingServices->getInteractionParent(currClass);
    if (currClass == 0)
    {
      break;
    }
    else
    {
      parents->length(size + 1);
      parents[size] = currClass;
    }
  }
  ws = federationManagement.supportingServices->findInteractionName(ret, interactionDatum);
  convertInteraction(interactionData, interactionDatum);

  if (federationManagement.supportingServices->getLRCparameterFlags(ret, lrcParameterFlagsMap) == 0)
  {
    convertParameter(parameters, ret, lrcParameterFlagsMap);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long ul;
                            ul = ret;
                            sprintf(galMsg, "class=%lu", ul);
                            E2(GeRti_SS_i, "getInteractionClassHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

CORBA::WChar *GeRtiFactory_GeRtiAmbassador_i::getInteractionClassName
(
  GeRtiFactory::GeRtiHandle handle,
  GeRtiFactory::Handles_out parents,
  GeRtiFactory::InteractionClassData_out interactionData,
  GeRtiFactory::ParametersClassData_out parameters
)
throw
(
  CORBA::SystemException,
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError
)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long ul;
                            unsigned long f;

                            f = fedId;
                            ul = handle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_i, "getInteractionClassName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  CORBA::WChar *ret;
  CORBA::WChar *wChar = L"";
  GERTICO::LRCparameterFlagsMap lrcParameterFlagsMap;
  GERTICO::AttributeDatum interactionDatum;
  GeRtiFactory::GeRtiHandle currClass;
  GeRtiFactory::GeRtiHandle size;
  std::wstring ws;

  parents = new GeRtiFactory::Handles();
  interactionData = new GeRtiFactory::InteractionClassData();
  parameters = new GeRtiFactory::ParametersClassData();

  federationManagement.setAlive(fedId);
  ws = federationManagement.supportingServices->findInteractionName(handle, interactionDatum);
  if (ws.size() == 0)
  {
                            unsigned long ul;
                            unsigned long f;

                            f = fedId;
                            ul = handle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_i, "getInteractionClassName:InteractionClassNotDefined", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::InteractionClassNotDefined(wChar);
  }

  currClass = handle;
  for (size = 0;; size++)
  {
    currClass = federationManagement.supportingServices->getInteractionParent(currClass);
    if (currClass == 0)
    {
      break;
    }
    else
    {
      parents->length(size + 1);
      parents[size] = currClass;
    }
  }

  GERTICO::Mapper::mapWcharFromWstring(&ret, ws);
  convertInteraction(interactionData, interactionDatum);

  if (federationManagement.supportingServices->getLRCparameterFlags(handle, lrcParameterFlagsMap) == 0)
  {
    convertParameter(parameters, handle, lrcParameterFlagsMap);
  }
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            sprintf(galMsg, "name=%ls", ws.c_str());
                            E2(GeRti_SS_i, "getInteractionClassName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getObjectClassHandle
(
  const CORBA::WChar *theName,
  GeRtiFactory::Handles_out parents,
  GeRtiFactory::ItemsClassData_out attributes
)
throw
(
  CORBA::SystemException,
  GeRtiFactory::NameNotFound,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::ConcurrentAccessAttempted,
  GeRtiFactory::RTIinternalError
)
{
  CORBA::WChar *wChar = L"getObjectClassHandle";
  GERTICO::LRCattributeFlagsMap lrcAttributeFlagsMap;
  GeRtiFactory::GeRtiHandle currClass;
  GeRtiFactory::GeRtiHandle size;
  int ret;
  std::wstring buff;
  std::wstring name;

  parents = new GeRtiFactory::Handles();
  attributes = new GeRtiFactory::ItemsClassData();

  GERTICO::Mapper::mapWstringFromWchar(name, theName);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,name=%ls", f, theName);
                            E2(GeRti_SS_i, "getObjectClassHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

#ifdef IEEE_1516
  std::wstring firstPart(name, 0, 14);
  std::wstring objectRoot = L"HLAobjectRoot.";
#else
  GERTICO::Mapper::nameToLower(name);
  std::wstring firstPart(name, 0, 11);
  std::wstring objectRoot = L"objectroot.";
#endif

  if (firstPart == objectRoot)
  {
#ifdef IEEE_1516
    std::wstring tmp(name, 14, std::wstring::npos);
#else
    std::wstring tmp(name, 11, std::wstring::npos);
#endif
    buff = tmp;
  }
  else
  {
    buff = name;
  }

  federationManagement.setAlive(fedId);
  ret = federationManagement.supportingServices->findObjectClassHandle(buff);
  if (ret == 0)
  {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,name=%ls", f, theName);
                            E2(GeRti_SS_i, "getObjectClassHandle:NameNotFound", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::NameNotFound(theName);
  }

  currClass = ret;
  for (size = 0;; size++)
  {
    currClass = federationManagement.supportingServices->getObjectParent(currClass);
    if (currClass == 0)
    {
      break;
    }
    else
    {
      parents->length(size + 1);
      parents[size] = currClass;
    }
  }

  federationManagement.supportingServices->getLRCattributeFlags(ret, lrcAttributeFlagsMap);
  convert(attributes, lrcAttributeFlagsMap);
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long ul;

                            ul = ret;
                            sprintf(galMsg, "class=%lu", ul);
                            E2(GeRti_SS_i, "getObjectClassHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::WChar *GeRtiFactory_GeRtiAmbassador_i::getObjectClassName (
  GeRtiFactory::GeRtiHandle handle,
  GeRtiFactory::Handles_out parents,
  GeRtiFactory::ItemsClassData_out attributes
)
throw (
  CORBA::SystemException,
  GeRtiFactory::ObjectClassNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::RTIinternalError,
  GeRtiFactory::ConcurrentAccessAttempted
)
{
  CORBA::WChar *ret;
  CORBA::WChar *wChar = L"getObjectClassName";
  GERTICO::LRCattributeFlagsMap lrcAttributeFlagsMap;
  GeRtiFactory::GeRtiHandle currClass;
  GeRtiFactory::GeRtiHandle size;
  std::wstring ws;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long ul;
                            unsigned long f;

                            f = fedId;
                            ul = handle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_i, "getObjectClassName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  ws = federationManagement.supportingServices->findObjectClassName(handle);
  if (ws.size() == 0)
  {
                            unsigned long ul;
                            unsigned long f;

                            f = fedId;
                            ul = handle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_i, "getObjectClassName:ObjectClassNotDefined", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::ObjectClassNotDefined(wChar);
  }

  parents = new GeRtiFactory::Handles();
  attributes = new GeRtiFactory::ItemsClassData();

  currClass = handle;
  for (size = 0;; size++)
  {
    currClass = federationManagement.supportingServices->getObjectParent(currClass);
    if (currClass == 0)
    {
      break;
    }
    else
    {
      parents->length(size + 1);
      parents[size] = currClass;
    }
  }

  federationManagement.supportingServices->getLRCattributeFlags(handle, lrcAttributeFlagsMap);
  convert(attributes, lrcAttributeFlagsMap);

  GERTICO::Mapper::mapWcharFromWstring(&ret, ws);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            sprintf(galMsg, "name=%ls", ws.c_str());
                            E2(GeRti_SS_i, "getObjectClassName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getParameterHandle
(
  const CORBA::WChar *theName,
  GeRtiFactory::GeRtiHandle whichClass
)
throw
(
  CORBA::SystemException,
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::NameNotFound,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::RTIinternalError
)
{
  CORBA::WChar *wChar = L"getParameterHandle";
  GeRtiFactory::GeRtiHandle ret = 0;
  bool foundClass = false;
  bool foundItem = false;
  std::wstring name;

  GERTICO::Mapper::mapWstringFromWchar(name, theName);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = whichClass;
                            sprintf(galMsg, "federate=%lu,name=%ls,class=%lu", f, theName, ul);
                            E2(GeRti_SS_i, "getParameterHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  // Recursive search.
  federationManagement.supportingServices->getParameterHandle(name, whichClass, ret, foundItem, foundClass);
  if (foundClass == false)
  {
    throw GeRtiFactory::InteractionClassNotDefined(wChar);
  }
  if (foundItem == false)
  {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = whichClass;
                            sprintf(galMsg, "federate=%lu,name=%ls,class=%lu", f, theName, ul);
                            E2(GeRti_SS_i, "getParameterHandle:NameNotFound", galMsg);   // inserted by Gal converter
    throw GeRtiFactory::NameNotFound(wChar);
  }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long ul1;

                            ul1 = ret;
                            sprintf(galMsg, "=%lu", ul1);
                            E2(GeRti_SS_i, "return", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::WChar *GeRtiFactory_GeRtiAmbassador_i::getParameterName
(
  GeRtiFactory::GeRtiHandle handle,
  GeRtiFactory::GeRtiHandle whichClass
)
throw
(
  CORBA::SystemException,
  GeRtiFactory::InteractionClassNotDefined,
  GeRtiFactory::InteractionParameterNotDefined,
  GeRtiFactory::FederateNotExecutionMember,
  GeRtiFactory::RTIinternalError
)
{
  bool foundClass = false;
  bool foundItem = false;
  CORBA::WChar *ret;
  CORBA::WChar *wChar = L"getParameterName";
  std::wstring ws;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = handle;
                            ul1 = whichClass;
                            sprintf(galMsg, "federate=%lu,handle=%lu,class=%lu", f, ul, ul1);
                            E2(GeRti_SS_i, "getParameterName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.supportingServices->getParameterName(handle, whichClass, ws, foundItem, foundClass);
  if (foundClass == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = handle;
                            ul1 = whichClass;
                            sprintf(galMsg, "federate=%lu,handle=%lu,class=%lu", f, ul, ul1);
                            E2(GeRti_SS_e, "getParameterName:InteractionClassNotDefined", galMsg);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::InteractionClassNotDefined(wChar);
  }
  if (foundItem == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = handle;
                            ul1 = whichClass;
                            sprintf(galMsg, "federate=%lu,handle=%lu,class=%lu", f, ul, ul1);
                            E2(GeRti_SS_e, "getParameterName:InteractionClassNotDefined", galMsg);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::InteractionParameterNotDefined(wChar);
  }
  GERTICO::Mapper::mapWcharFromWstring(&ret, ws);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            sprintf(galMsg, "name=%ls", ws.c_str());
                            E2(GeRti_SS_i, "getParameterName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getRoutingSpaceHandle (
    const CORBA::WChar *theName
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  CORBA::WChar *wChar = L"getRoutingSpaceHandle";
  GeRtiFactory::GeRtiHandle ret;
  std::wstring name;

  GERTICO::Mapper::mapWstringFromWchar(name, theName);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;

                            f = fedId;
                            sprintf(galMsg, "federate=%lu,name=%ls", f, theName);
                            E2(GeRti_SS_i, "getRoutingSpaceHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  ret = federationManagement.supportingServices->getRoutingSpaceHandle(name);

  if (ret)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_SS_i, "getRoutingSpaceHandle", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    return ret;
  }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_e)
                            {
                            unsigned long ul1;

                            ul1 = ret;
                            sprintf(galMsg, "space=%lu", ul1);
                             E2(GeRti_SS_e, "getRoutingSpaceHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  throw GeRtiFactory::NameNotFound(wChar);
}

CORBA::WChar *GeRtiFactory_GeRtiAmbassador_i::getRoutingSpaceName (
    GeRtiFactory::GeRtiHandle theHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SpaceNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theHandle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_i, "getRoutingSpaceName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  CORBA::WChar *ret;
  CORBA::WChar *wChar = L"getRoutingSpaceName";
  std::wstring ws;

  federationManagement.setAlive(fedId);
  ws = federationManagement.supportingServices->getRoutingSpaceName(theHandle);
  GERTICO::Mapper::mapWcharFromWstring(&ret, ws);

  if (ret == NULL)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theHandle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_e, "getRoutingSpaceName:SpaceNotDefined", galMsg);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::SpaceNotDefined(wChar);
  }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            sprintf(galMsg, "name=%ls", ws.c_str());
                            E2(GeRti_SS_i, "getRoutingSpaceName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return ret;
}

GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getDimensionHandle (
    const CORBA::WChar *theName,
    GeRtiFactory::GeRtiHandle whichSpace
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::NameNotFound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  CORBA::WChar *wChar = L"getDimensionHandle";
  GeRtiFactory::GeRtiHandle ret;
  std::wstring name;

  GERTICO::Mapper::mapWstringFromWchar(name, theName);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
#ifndef IEEE_1516
                            unsigned long ul;
#endif

                            f = fedId;
#ifndef IEEE_1516
                            ul = whichSpace;
#endif
#ifdef IEEE_1516
                            sprintf(galMsg, "federate=%lu,name=%ls", f, theName);
#else
                            sprintf(galMsg, "federate=%lu,name=%ls,space=%lu", f, theName, ul);
#endif
                            E2(GeRti_SS_i, "getDimensionHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  ret = federationManagement.supportingServices->getDimensionHandle(name, whichSpace);

  if (ret)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_SS_i, "getDimensionHandle", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    return ret;
  }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_e)
                            {
                            unsigned long ul1;

                            ul1 = ret;
                            sprintf(galMsg, "space=%lu", ul1);
                            E2(GeRti_SS_e, "getDimensionHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  throw GeRtiFactory::NameNotFound(wChar);
}

CORBA::WChar *GeRtiFactory_GeRtiAmbassador_i::getDimensionName (
    GeRtiFactory::GeRtiHandle theHandle,
    GeRtiFactory::GeRtiHandle whichSpace
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::SpaceNotDefined,
    GeRtiFactory::DimensionNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  CORBA::WChar *tmpName;
  CORBA::WChar *wChar = L"getDimensionName";
  std::wstring dimension;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;
#ifndef IEEE_1516
                            unsigned long ul1;
#endif

                            f = fedId;
                            ul = theHandle;
#ifdef IEEE_1516
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
#else
                            ul1 = whichSpace;
                            sprintf(galMsg, "federate=%lu,handle=%lu,space=%lu", f, ul, ul1);
#endif
                            E2(GeRti_SS_i, "getDimensionName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.supportingServices->getDimensionName(dimension, theHandle, whichSpace);
  if (dimension.size() == 0)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_SS_i, "getDimensionName", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::SpaceNotDefined(wChar);
  }
  GERTICO::Mapper::mapWcharFromWstring(&tmpName, dimension);

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            sprintf(galMsg, "name=%ls", dimension.c_str());
                            E2(GeRti_SS_i, "getDimensionName", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return tmpName;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getDimensionUpperBound (
    GeRtiFactory::GeRtiHandle theHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::DimensionNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  )
{
  GeRtiFactory::GeRtiHandle ret = 0;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theHandle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_i, "getDimensionUpperBound", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  federationManagement.setAlive(fedId);
  // XXX
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::Handles * GeRtiFactory_GeRtiAmbassador_i::getAvailableDimensionsForClassAttribute (
    GeRtiFactory::GeRtiHandle theClass,
    GeRtiFactory::GeRtiHandle theHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  )
{
  GeRtiFactory::Handles *ret = NULL;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = theClass;
                            ul1 = theHandle;
                            sprintf(galMsg, "federate=%lu,class=%lu,handle=%lu", f, ul, ul1);
                            E2(GeRti_SS_i, "getAvailableDimensionsForClassAttribute", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  federationManagement.setAlive(fedId);
  // XXX
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::Handles * GeRtiFactory_GeRtiAmbassador_i::getAvailableDimensionsForInteractionClass (
    GeRtiFactory::GeRtiHandle theClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError
  )
{
  GeRtiFactory::Handles *ret = NULL;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theClass;
                            sprintf(galMsg, "federate=%lu,class=%lu", f, ul);
                            E2(GeRti_SS_i, "getAvailableDimensionsForInteractionClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  federationManagement.setAlive(fedId);
  // XXX
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getAttributeRoutingSpaceHandle (
    GeRtiFactory::GeRtiHandle theHandle,
    GeRtiFactory::GeRtiHandle whichClass
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectClassNotDefined,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  CORBA::WChar *wChar = L"";
  GeRtiFactory::GeRtiHandle retSpace;
  bool classFound = false;
  bool attributeFound = false;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = theHandle;
                            ul1 = whichClass;
                            sprintf(galMsg, "federate=%lu,handle=%lu,class=%lu", f, ul, ul1);
                            E2(GeRti_SS_i, "getAttributeRoutingSpaceHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.supportingServices->getAttributeRoutingSpaceHandle(theHandle, whichClass, retSpace, classFound, attributeFound);

  if (classFound == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_SS_i, "getAttributeRoutingSpaceHandle", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::ObjectClassNotDefined(wChar);
  }

  if (attributeFound == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_SS_i, "getAttributeRoutingSpaceHandle", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::AttributeNotDefined(wChar);
  }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                              unsigned long ul1;

                              ul1 = retSpace;
                              sprintf(galMsg, "space=%lu", ul1);
                              E2(GeRti_SS_i, "getAttributeRoutingSpaceHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return retSpace;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::GeRtiHandle GeRtiFactory_GeRtiAmbassador_i::getInteractionRoutingSpaceHandle (
    GeRtiFactory::GeRtiHandle theHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::InteractionClassNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::RTIinternalError,
    GeRtiFactory::ConcurrentAccessAttempted
  )
{
  CORBA::WChar *wChar = L"getInteractionRoutingSpaceHandle";
  bool theClassFound = false;
  GeRtiFactory::GeRtiHandle retSpace;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theHandle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_i, "getInteractionRoutingSpaceHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.declarationManagementRTI->getInteractionRoutingSpaceHandle (theHandle, retSpace, theClassFound);

  if (theClassFound == false)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theHandle;
                            sprintf(galMsg, "federate=%lu,handle=%lu", f, ul);
                            E2(GeRti_SS_i, "getInteractionRoutingSpaceHandle:InteractionClassNotDefined", galMsg);   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    throw GeRtiFactory::InteractionClassNotDefined(wChar);
  }

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long ul1;

                            ul1 = retSpace;
                            sprintf(galMsg, "space=%lu", ul1);
                            E2(GeRti_SS_i, "getInteractionRoutingSpaceHandle", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  return retSpace;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::Handles * GeRtiFactory_GeRtiAmbassador_i::getDimensionHandleSet (
    GeRtiFactory::GeRtiHandle theRegionHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
  GeRtiFactory::Handles *ret = NULL;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;

                            f = fedId;
                            ul = theRegionHandle;
                            sprintf(galMsg, "federate=%lu,regionHandle=%lu", f, ul);
                            E2(GeRti_SS_i, "getDimensionHandleSet", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  federationManagement.setAlive(fedId);
  // XXX
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GeRtiFactory::Handles * GeRtiFactory_GeRtiAmbassador_i::getRangeBounds (
    GeRtiFactory::GeRtiHandle theRegionHandle,
    GeRtiFactory::GeRtiHandle theDimensionHandle
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::RegionDoesNotContainSpecifiedDimension,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
  GeRtiFactory::Handles *ret = NULL;

                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;

                            f = fedId;
                            ul = theRegionHandle;
                            ul1 = theDimensionHandle;
                            sprintf(galMsg, "federate=%lu,regionHandle=%lu,dimensionHandle=%lu", f, ul, ul1);
                            E2(GeRti_SS_i, "getRangeBounds", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  federationManagement.setAlive(fedId);
  // XXX
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GeRtiFactory_GeRtiAmbassador_i::setRangeBounds (
    GeRtiFactory::GeRtiHandle theRegionHandle,
    GeRtiFactory::GeRtiHandle theDimensionHandle,
    GeRtiFactory::GeRtiHandle theLowerBound,
    GeRtiFactory::GeRtiHandle theUpperBound
  )
  throw (
    CORBA::SystemException,
    GeRtiFactory::RegionNotKnown,
    GeRtiFactory::RegionNotCreatedByThisFederate,
    GeRtiFactory::RegionDoesNotContainSpecifiedDimension,
    GeRtiFactory::InvalidRangeBound,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError
  )
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_SS_i)
                            {
                            unsigned long f;
                            unsigned long ul;
                            unsigned long ul1;
                            unsigned long ul2;
                            unsigned long ul3;

                            f = fedId;
                            ul = theRegionHandle;
                            ul1 = theDimensionHandle;
                            ul2 = theLowerBound;
                            ul3 = theUpperBound;
                            sprintf(galMsg, "federate=%lu,regionHandle=%lu,dimensionHandle=%lu,lowerBound=%lu,upperBound=%lu", f, ul, ul1, ul2, ul3);
                            E2(GeRti_SS_i, "setRangeBounds", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter

  federationManagement.setAlive(fedId);
  federationManagement.supportingServices->setRangeBounds(theRegionHandle, theDimensionHandle, theLowerBound, theUpperBound);

                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DDM_i, "setRangeBounds", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}
