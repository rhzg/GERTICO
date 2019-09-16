/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** ReceiverI.cpp
**
*******************************************************************************/

#include "idl/GeRtiFactoryS.h"
#include "LRC/GeRtiEventMarketI.h"
#include "LRC/HLA1516/Mapper1516.h"
#include "LRC/HLA1516/ReceiverI.h"
#include "HlaOwnershipClientMapper.h"
#include "Util/Mapper.h"

// Static strings for save/restore.
std::string GERTICO::AnSynPt::announceSynchronizationPointStr("announceSynchronizationPoint");
std::string GERTICO::AnSynPt::labelStr("label");
std::string GERTICO::AnSynPt::rtiInitiatedServiceStr("rtiInitiatedService");
std::string GERTICO::AnSynPt::tagStr("tag");

std::string GERTICO::AttributeScope::attributeScopeStr("attributeScope");
std::string GERTICO::AttributeScope::attributeStr("attribute");
std::string GERTICO::AttributeScope::attributesStr("attributes");
std::string GERTICO::AttributeScope::inScopeStr("inScope");
std::string GERTICO::AttributeScope::objectStr("object");
std::string GERTICO::AttributeScope::rtiInitiatedServiceStr("rtiInitiatedService");

std::string GERTICO::CoSynPt::confirmSychronizationPointRegistrationStr("confirmSychronizationPointRegistration");
std::string GERTICO::CoSynPt::labelStr("label");
std::string GERTICO::CoSynPt::rtiInitiatedServiceStr("rtiInitiatedService");
std::string GERTICO::CoSynPt::successStr("success");

std::string GERTICO::Discover::classStr("class");
std::string GERTICO::Discover::discoverObjectInstanceStr("discoverObjectInstance");
std::string GERTICO::Discover::nameStr("name");
std::string GERTICO::Discover::objectStr("object");
std::string GERTICO::Discover::rtiInitiatedServiceStr("rtiInitiatedService");

std::string GERTICO::FederationRestoreStatusResponseJob::federationRestoreStatusResponseStr("federationRestoreStatusResponse");
std::string GERTICO::FederationRestoreStatusResponseJob::federateStatusPairStr("federateStatusPair");
std::string GERTICO::FederationRestoreStatusResponseJob::federateStatusVectorStr("federateStatusVector");
std::string GERTICO::FederationRestoreStatusResponseJob::federateStr("federate");
std::string GERTICO::FederationRestoreStatusResponseJob::rtiInitiatedServiceStr("rtiInitiatedService");
std::string GERTICO::FederationRestoreStatusResponseJob::statusStr("status");

std::string GERTICO::FederationSaveStatusResponseJob::federationSaveStatusResponseStr("federationSaveStatusResponse");
std::string GERTICO::FederationSaveStatusResponseJob::federateStatusPairStr("federateStatusPair");
std::string GERTICO::FederationSaveStatusResponseJob::federateStatusVectorStr("federateStatusVector");
std::string GERTICO::FederationSaveStatusResponseJob::federateStr("federate");
std::string GERTICO::FederationSaveStatusResponseJob::rtiInitiatedServiceStr("rtiInitiatedService");
std::string GERTICO::FederationSaveStatusResponseJob::statusStr("status");

std::string GERTICO::FedSync::federationSynchronizedStr("federationSynchronized");
std::string GERTICO::FedSync::labelStr("label");
std::string GERTICO::FedSync::rtiInitiatedServiceStr("rtiInitiatedService");

std::string GERTICO::ObjectInstanceNameReservationFailedJob::objectInstanceNameReservationFailedStr("objectInstanceNameReservationFailed");
std::string GERTICO::ObjectInstanceNameReservationFailedJob::objectInstanceNameStr("objectInstanceName");
std::string GERTICO::ObjectInstanceNameReservationFailedJob::rtiInitiatedServiceStr("rtiInitiatedService");

std::string GERTICO::ObjectInstanceNameReservationSucceededJob::objectInstanceNameReservationSucceededStr("objectInstanceNameReservationSucceeded");
std::string GERTICO::ObjectInstanceNameReservationSucceededJob::objectInstanceNameStr("objectInstanceName");
std::string GERTICO::ObjectInstanceNameReservationSucceededJob::rtiInitiatedServiceStr("rtiInitiatedService");

std::string GERTICO::ObjPubOff::attributeStr("attribute");
std::string GERTICO::ObjPubOff::attributesStr("attributes");
std::string GERTICO::ObjPubOff::classStr("class");
std::string GERTICO::ObjPubOff::rtiInitiatedServiceStr("rtiInitiatedService");
std::string GERTICO::ObjPubOff::turnUpdatesOffForObjectInstanceStr("turnUpdatesOffForObjectInstance");

std::string GERTICO::ObjPubOn::attributeStr("attribute");
std::string GERTICO::ObjPubOn::attributesStr("attributes");
std::string GERTICO::ObjPubOn::classStr("class");
std::string GERTICO::ObjPubOn::rtiInitiatedServiceStr("rtiInitiatedService");
std::string GERTICO::ObjPubOn::turnUpdatesOnForObjectInstanceStr("turnUpdatesOnForObjectInstance");

std::string GERTICO::Provide::attributeStr("attribute");
std::string GERTICO::Provide::attributesStr("attributes");
std::string GERTICO::Provide::objectStr("object");
std::string GERTICO::Provide::provideAttributeValueUpdateStr("provideAttributeValueUpdate");
std::string GERTICO::Provide::rtiInitiatedServiceStr("rtiInitiatedService");

std::string GERTICO::PublishTurnOn::classStr("class");
std::string GERTICO::PublishTurnOn::onStr("on");
std::string GERTICO::PublishTurnOn::rtiInitiatedServiceStr("rtiInitiatedService");
std::string GERTICO::PublishTurnOn::turnInteractionsOnStr("turnInteractionsOn");

std::string GERTICO::StReg::classStr("class");
std::string GERTICO::StReg::rtiInitiatedServiceStr("rtiInitiatedService");
std::string GERTICO::StReg::startStr("start");
std::string GERTICO::StReg::stRegistrationForObjectClass("stRegistrationForObject");

std::string GERTICO::ReceiverI1516::rtiInitiatedServicesStr("rtiInitiatedServices");

/********************************** Gal begin ***************************************/


#ifdef GalDebug

#include "Gal/StdAfx.h"
#include "Gal/repository.h"
#include "Gal/event.h"

static class Repository_l *DM=(Repository::getSingleInstance())->getRepository_l("GeRtiDM.res","GeRtiDM");

static class Event *GeRti_DM_d=DM->getRefEvent("GeRti_DM_d");
static class Event *GeRti_DM_e=DM->getRefEvent("GeRti_DM_e");
static class Event *GeRti_DM_i=DM->getRefEvent("GeRti_DM_i");
static class Event *GeRti_DM_w=DM->getRefEvent("GeRti_DM_w");

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

static class Repository_l *TM=(Repository::getSingleInstance())->getRepository_l("GeRtiTM.res","GeRtiTM");

static class Event *GeRti_TM_d=TM->getRefEvent("GeRti_TM_d");
static class Event *GeRti_TM_e=TM->getRefEvent("GeRti_TM_e");
static class Event *GeRti_TM_i=TM->getRefEvent("GeRti_TM_i");
static class Event *GeRti_TM_w=TM->getRefEvent("GeRti_TM_w");
static class Event *GeRti_TM_mu_d=TM->getRefEvent("GeRti_TM_mu_d");

#endif

#define GalHLADebug 1

#ifdef GalHLADebug

#include "Gal/StdAfx.h"   // inserted by Gal converter
#include "Gal/repository_l.h"   // inserted by Gal converter
#include "Gal/event.h"   // inserted by Gal converter

static class Repository_l *rpGal=(Repository::getSingleInstance())->getRepository_l("HLAServices.res","HLAServices");

static class Event *aSP_i0=rpGal->getRefEvent("aSP_i0");
static class Event *aSP_ts=rpGal->getRefEvent("aSP_ts");
static class Event *aIS_i0=rpGal->getRefEvent("aIS_i0");
static class Event *aOS_i0=rpGal->getRefEvent("aOS_i0");
static class Event *aOS_ts=rpGal->getRefEvent("aOS_ts");
static class Event *cSP_i0=rpGal->getRefEvent("cSP_i0");
static class Event *cSP_i1=rpGal->getRefEvent("cSP_i1");
static class Event *d_i0=rpGal->getRefEvent("d_i0");
static class Event *d_ta=rpGal->getRefEvent("d_ta");
static class Event *d_ts=rpGal->getRefEvent("d_ts");
static class Event *fS_i0=rpGal->getRefEvent("fS_i0");
static class Event *fS_ts=rpGal->getRefEvent("fS_ts");
static class Event *oPO_i0=rpGal->getRefEvent("oPO_i0");
static class Event *oPO_ta=rpGal->getRefEvent("oPO_ta");
static class Event *oPO_ts=rpGal->getRefEvent("oPO_ts");
static class Event *oPON_i0=rpGal->getRefEvent("oPON_i0");
static class Event *oPON_ta=rpGal->getRefEvent("oPON_ta");
static class Event *oPON_ts=rpGal->getRefEvent("oPON_ts");
static class Event *p_i0=rpGal->getRefEvent("p_i0");
static class Event *p_ta=rpGal->getRefEvent("p_ta");
static class Event *p_ts=rpGal->getRefEvent("p_ts");
static class Event *pTON_i0=rpGal->getRefEvent("pTON_i0");
static class Event *pTO_i0=rpGal->getRefEvent("pTO_i0");
static class Event *sR_i0=rpGal->getRefEvent("sR_i0");
static class Event *sR_i1=rpGal->getRefEvent("sR_i1");
static class Event *sR_ta=rpGal->getRefEvent("sR_ta");
static class Event *sR_ts=rpGal->getRefEvent("sR_ts");

#define MAX_TXT 1024
static char galMsg[MAX_TXT];

#endif


/********************************** Gal end ***************************************/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AnSynPt::AnSynPt(const std::wstring &theLabel, const GeRtiFactory::UserSuppliedTag &theTag, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : tag(theTag), fedAmb(theFedAmb), joined(theJoined), label(theLabel)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AnSynPt::~AnSynPt(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::AnSynPt::execute(void)
{
  RTI::UserSuppliedTag t;

  try
  {
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aSP_i0)
                            {
                              std::string l;
                              GERTICO::Mapper::mapStringFromWstring(l, label);
                              sprintf(galMsg,"label=%s",l.c_str());
                              E1mEnd(aSP_i0,galMsg);
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E2(aSP_i0, "announceSynchronizationPoint", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      GERTICO::Mapper1516::mapUserSuppliedTag(t, tag);
      fedAmb.announceSynchronizationPoint(label, t);
    }
  }
  catch(RTI::FederateInternalError &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aSP_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::AnSynPt::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(announceSynchronizationPointStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(labelStr.c_str(), tempStr, 99);
  GERTICO::Mapper1516::mapWstringTranscode(tempStr1, label, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(tagStr.c_str(), tempStr, 99);
  GERTICO::Mapper1516::mapWstringTranscode(tempStr1, label, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AttributeScope::AttributeScope(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes, const bool &theIn, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : fedAmb(theFedAmb), joined(theJoined)
{
  myObject = theObject;
  attributes = theAttributes;
  inScope = theIn;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::AttributeScope::execute(void)
{
  RTI::AttributeHandleSet *attributeHandleSetPtr = new RTI::AttributeHandleSet();
  RTI::ObjectInstanceHandle object;
  std::auto_ptr<RTI::AttributeHandleSet> ahs(attributeHandleSetPtr);

  try
  {
    if (joined)
    {
      GERTICO::Mapper1516::mapObjectInstanceHandle(object, myObject);
      GERTICO::Mapper1516::mapAttributeHandleSet(*ahs, attributes);

      if (inScope)
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aIS_i0)
                            {
                              unsigned long ul;

                              ul = myObject;
                              sprintf(galMsg,"object=%lu",ul);
                              E1mEnd(aIS_i0,galMsg);
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributes);
                              E2(aIS_i0, "attributesInScope", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
        fedAmb.attributesInScope(object, ahs);
      }
      else
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOS_i0)
                            {
                              unsigned long ul;

                              ul = myObject;
                              sprintf(galMsg,"object=%lu",ul);
                              E1mEnd(aOS_i0,galMsg);
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributes);
                              E2(aOS_i0, "attributesOutOfScope", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
        fedAmb.attributesOutOfScope(object, ahs);
      }
    }
  }
  catch(RTI::FederateInternalError &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOS_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::AttributeScope::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];
  unsigned long i;
  unsigned long l;
  unsigned long length;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(attributeScopeStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  l = myObject;
  sprintf(buf, "%lu", l);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = attributes.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    l = attributes[i];
    sprintf(buf, "%lu", l);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  XMLString::transcode(inScopeStr.c_str(), tempStr, 99);
  if (inScope)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AttributeScope::~AttributeScope(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::CoSynPt::CoSynPt(const std::wstring &theLabel, const bool &theSuccess, const GeRtiFactory::SynchronizationPointFailureReason &theReason, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : fedAmb(theFedAmb), joined(theJoined), label(theLabel)
{
  success = theSuccess;
  reason = theReason;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::CoSynPt::~CoSynPt(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::CoSynPt::execute(void)
{
  if (joined)
  {
    if (success)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cSP_i0)
                            {
                              std::string l;
                              GERTICO::Mapper::mapStringFromWstring(l, label);
                              sprintf(galMsg,"label=%s",l.c_str());
                              E1mEnd(cSP_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      fedAmb.synchronizationPointRegistrationSucceeded(label);
    }
    else
    {
      RTI::SynchronizationFailureReason rtiReason(RTI::SynchronizationFailureReason::synchronizationPointLabelNotUnique());
      switch(reason)
      {
        case GeRtiFactory::synchronizationPointLabelNotUnique:
        {
          rtiReason = RTI::SynchronizationFailureReason::synchronizationPointLabelNotUnique();
          break;
        }
        case GeRtiFactory::synchronizationSetMemberNotJoined:
        {
          rtiReason = RTI::SynchronizationFailureReason::synchronizationSetMemberNotJoined();
          break;
        }
        case GeRtiFactory::federateResignedDuringSynchronization:
        {
          rtiReason = RTI::SynchronizationFailureReason::federateResignedDuringSynchronization();
          break;
        }
        case GeRtiFactory::rtiDetectedFailureDuringSynchronization:
        {
          rtiReason = RTI::SynchronizationFailureReason::rtiDetectedFailureDuringSynchronization();
          break;
        }
        case GeRtiFactory::synchronizationTimeCannotBeHonored:
        {
          rtiReason = RTI::SynchronizationFailureReason::synchronizationTimeCannotBeHonored();
          break;
        }
      }
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cSP_i1)
                            {
                              std::string l;
                              GERTICO::Mapper::mapStringFromWstring(l, label);
                              sprintf(galMsg,"label=%s",l.c_str());
                              E1mEnd(cSP_i1,galMsg);
                            }
                           #endif   // inserted by Gal converter
      fedAmb.synchronizationPointRegistrationFailed(label, rtiReason);
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::CoSynPt::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];
  std::string l;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(confirmSychronizationPointRegistrationStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  GERTICO::Mapper::mapStringFromWstring(l, label);
  XMLString::transcode(labelStr.c_str(), tempStr, 99);
  XMLString::transcode(l.c_str(), tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(successStr.c_str(), tempStr, 99);
  if (success)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Discover::Discover(const std::wstring &myName, unsigned long myObjectId, unsigned long myClassId, GERTICO::ObjectManagementLRC &theObjectManagementLRC, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : objectManagementLRC(theObjectManagementLRC), fedAmb(theFedAmb), joined(theJoined), name(myName)
{
  objectId = myObjectId;
  classId = myClassId;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Discover::~Discover()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::Discover::execute(void)
{
  RTI::ObjectClassHandle objectClass;
  RTI::ObjectInstanceHandle object;

  try
  {
    if (joined)
    {
      // if object is already known do nothing
      objectManagementLRC.discoverObjectInstance(objectId, classId, name);
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(d_i0)
                            {
                              std::string l;
                              GERTICO::Mapper::mapStringFromWstring(l, name);
                              sprintf(galMsg,"object=%lu,class=%lu,name=%s",objectId, classId, l.c_str());
                              E1mEnd(d_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      GERTICO::Mapper1516::mapObjectInstanceHandle(object, objectId);
      GERTICO::Mapper1516::mapObjectClassHandle(objectClass, classId);
      fedAmb.discoverObjectInstance(object, objectClass, name);
    }
  }
  catch(RTI::CouldNotDiscover &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(d_ta,"CouldNotDiscover");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::ObjectClassNotKnown &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(d_ta,"ObjectClassNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::FederateInternalError &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(d_ts, "FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::Discover::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];
  std::string s;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(discoverObjectInstanceStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", objectId);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(classStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", classId);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(nameStr.c_str(), tempStr, 99);
  GERTICO::Mapper::mapStringFromWstring(s, name);
  XMLString::transcode(s.c_str(), tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationRestoreStatusResponseJob::FederationRestoreStatusResponseJob(const GeRtiFactory::RestoreStatusPairSeq &theFederateStatusVector, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : federateStatusVector(theFederateStatusVector), fedAmb(theFedAmb), joined(theJoined)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationRestoreStatusResponseJob::~FederationRestoreStatusResponseJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationRestoreStatusResponseJob::execute(void)
{
  std::auto_ptr<RTI::FederateHandleRestoreStatusPairVector> RtiFederateStatusVector;

  try
  {
    if (joined)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              E2(GeRti_FM_i, "federationRestoreStatusResponse", "Enter");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      GERTICO::Mapper1516::mapFederateHandleRestoreStatusPairVector(RtiFederateStatusVector, federateStatusVector);
      fedAmb.federationRestoreStatusResponse(RtiFederateStatusVector);
    }
  }
  catch(RTI::FederateInternalError &)
  {
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationRestoreStatusResponseJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  CORBA::ULong i;
  CORBA::ULong length;
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  DOMElement* elemLevel3;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  unsigned long l;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(federationRestoreStatusResponseStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(federateStatusVectorStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = federateStatusVector.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(federateStatusPairStr.c_str(), tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode(federateStr.c_str(), tempStr, 99);
    l = federateStatusVector[i].theFederate;
    sprintf (buf, "%lu", l);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    XMLString::transcode(statusStr.c_str(), tempStr, 99);
    switch (federateStatusVector[i].theRestoreStatus)
    {
      case GeRtiFactory::noRestoreInProgress:
      {
        strcpy(buf, "noRestoreInProgress");
        break;
      }
      case GeRtiFactory::federateRestoreRequestPending:
      {
        strcpy(buf, "federateRestoreRequestPending");
        break;
      }
      case GeRtiFactory::federateWaitingForRestoreToBegin:
      {
        strcpy(buf, "federateWaitingForRestoreToBegin");
        break;
      }
      case GeRtiFactory::federatePreparedToRestore:
      {
        strcpy(buf, "federatePreparedToRestore");
        break;
      }
      case GeRtiFactory::federateRestoring:
      {
        strcpy(buf, "federateRestoring");
        break;
      }
      case GeRtiFactory::federateWaitingForFederationToRestore:
      {
        strcpy(buf, "federateWaitingForFederationToRestore");
        break;
      }
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationSaveStatusResponseJob::FederationSaveStatusResponseJob(const GeRtiFactory::SaveStatusPairSeq &theFederateStatusVector, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : federateStatusVector(theFederateStatusVector), fedAmb(theFedAmb), joined(theJoined)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationSaveStatusResponseJob::~FederationSaveStatusResponseJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationSaveStatusResponseJob::execute(void)
{
  std::auto_ptr<RTI::FederateHandleSaveStatusPairVector> RtiFederateStatusVector;

  try
  {
    if (joined)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_FM_i)
                            {
                              E2(GeRti_FM_i, "federationSaveStatusResponse", "Enter");   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      GERTICO::Mapper1516::mapFederateHandleSaveStatusPairVector(RtiFederateStatusVector, federateStatusVector);
      fedAmb.federationSaveStatusResponse(RtiFederateStatusVector);
    }
  }
  catch(RTI::FederateInternalError &)
  {
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationSaveStatusResponseJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  CORBA::ULong i;
  CORBA::ULong length;
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  DOMElement* elemLevel3;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[128];
  unsigned long l;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(federationSaveStatusResponseStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(federateStatusVectorStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = federateStatusVector.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(federateStatusPairStr.c_str(), tempStr, 99);
    elemLevel3 = theDOMDocument.createElement(tempStr);
    elemLevel2->appendChild(elemLevel3);

    XMLString::transcode(federateStr.c_str(), tempStr, 99);
    l = federateStatusVector[i].theFederate;
    sprintf (buf, "%lu", l);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);

    XMLString::transcode(statusStr.c_str(), tempStr, 99);
    switch (federateStatusVector[i].theSaveStatus)
    {
      case GeRtiFactory::noSaveInProgress:
      {
        strcpy(buf, "noSaveInProgress");
        break;
      }
      case GeRtiFactory::federateInstructedToSave:
      {
        strcpy(buf, "federateInstructedToSave");
        break;
      }
      case GeRtiFactory::federateSaving:
      {
        strcpy(buf, "federateSaving");
        break;
      }
      case GeRtiFactory::federateWaitingForFederationToSave:
      {
        strcpy(buf, "federateWaitingForFederationToSave");
        break;
      }
    }
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel3->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FedSync::FedSync(const std::wstring &theLabel, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : fedAmb(theFedAmb), joined(theJoined), label(theLabel)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FedSync::~FedSync(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FedSync::execute(void)
{
  try
  {
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(fS_i0)
                            {
                              std::string l;
                              GERTICO::Mapper::mapStringFromWstring(l, label);
                              sprintf(galMsg,"label=%s",l.c_str());
                              E1mEnd(fS_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      fedAmb.federationSynchronized(label);
    }
  }
  catch(RTI::FederateInternalError &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(fS_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FedSync::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  std::string l;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(federationSynchronizedStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  GERTICO::Mapper::mapStringFromWstring(l, label);
  XMLString::transcode(labelStr.c_str(), tempStr, 99);
  XMLString::transcode(l.c_str(), tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectInstanceNameReservationFailedJob::ObjectInstanceNameReservationFailedJob(const std::wstring &theObjectInstanceName, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : fedAmb(theFedAmb), joined(theJoined), objectInstanceName(theObjectInstanceName)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectInstanceNameReservationFailedJob::~ObjectInstanceNameReservationFailedJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ObjectInstanceNameReservationFailedJob::execute(void)
{
  try
  {
    if (joined)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              sprintf(galMsg, "Name=%ls", objectInstanceName.c_str());
                              E2(GeRti_OM_i, "objectInstanceNameReservationFailed", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      fedAmb.objectInstanceNameReservationFailed(objectInstanceName);
    }
  }
  catch(RTI::FederateInternalError &)
  {
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ObjectInstanceNameReservationFailedJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  std::string l;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(objectInstanceNameReservationFailedStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectInstanceNameStr.c_str(), tempStr, 99);
  GERTICO::Mapper::mapStringFromWstring(l, objectInstanceName);
  XMLString::transcode(l.c_str(), tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectInstanceNameReservationSucceededJob::ObjectInstanceNameReservationSucceededJob(const std::wstring &theObjectInstanceName, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : fedAmb(theFedAmb), joined(theJoined), objectInstanceName(theObjectInstanceName)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjectInstanceNameReservationSucceededJob::~ObjectInstanceNameReservationSucceededJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ObjectInstanceNameReservationSucceededJob::execute(void)
{
  try
  {
    if (joined)
    {
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_OM_i)
                            {
                              sprintf(galMsg, "Name=%ls", objectInstanceName.c_str());
                              E2(GeRti_OM_i, "objectInstanceNameReservationSucceeded", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      fedAmb.objectInstanceNameReservationSucceeded(objectInstanceName);
    }
  }
  catch(RTI::FederateInternalError &)
  {
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ObjectInstanceNameReservationSucceededJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  std::string l;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(objectInstanceNameReservationSucceededStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectInstanceNameStr.c_str(), tempStr, 99);
  GERTICO::Mapper::mapStringFromWstring(l, objectInstanceName);
  XMLString::transcode(l.c_str(), tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjPubOff::ObjPubOff(const unsigned long &id, const GeRtiFactory::Handles &ahs, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : attributeList(ahs), fedAmb(theFedAmb), joined(theJoined)
{
  classId = id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjPubOff::~ObjPubOff(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ObjPubOff::execute(void)
{
  RTI::AttributeHandleSet *attributeHandleSetPtr = new RTI::AttributeHandleSet();
  RTI::ObjectInstanceHandle object;
  std::auto_ptr<RTI::AttributeHandleSet> ahs(attributeHandleSetPtr);

  GERTICO::Mapper1516::mapObjectInstanceHandle(object, classId);
  GERTICO::Mapper1516::mapAttributeHandleSet(*ahs, attributeList);

  try
  {
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(oPO_i0)
                            {
                              sprintf(galMsg,"object=%lu",classId);
                              E1mEnd(oPO_i0,galMsg);
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributeList);
                              E2(oPO_i0, "turnUpdatesOffForObjectInstance", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      fedAmb.turnUpdatesOffForObjectInstance(object, ahs);
    }
  }
  catch(RTI::ObjectInstanceNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPO_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::AttributeNotOwned)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPO_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::FederateInternalError)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPO_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ObjPubOff::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  CORBA::ULong i;
  CORBA::ULong length;
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];
  unsigned long l;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(turnUpdatesOffForObjectInstanceStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(classStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", classId);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = attributeList.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    l = attributeList[i];
    sprintf(buf, "%lu", l);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjPubOn::ObjPubOn(const unsigned long &id, const GeRtiFactory::Handles &ahs, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : attributeList(ahs), fedAmb(theFedAmb), joined(theJoined)
{
  classId = id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjPubOn::~ObjPubOn(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ObjPubOn::execute(void)
{
  RTI::AttributeHandleSet *attributeHandleSetPtr = new RTI::AttributeHandleSet();
  RTI::ObjectInstanceHandle object;
  std::auto_ptr<RTI::AttributeHandleSet> ahs(attributeHandleSetPtr);

  GERTICO::Mapper1516::mapObjectInstanceHandle(object, classId);
  GERTICO::Mapper1516::mapAttributeHandleSet(*ahs, attributeList);

  try
  {
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(oPON_i0)
                            {
                              sprintf(galMsg,"object=%lu",classId);
                              E1mEnd(oPON_i0,galMsg);
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributeList);
                              E2(oPON_i0, "turnUpdatesOnForObjectInstance", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      fedAmb.turnUpdatesOnForObjectInstance(object, ahs);
    }
  }
  catch(RTI::ObjectInstanceNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPON_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::AttributeNotOwned)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPON_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::FederateInternalError)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPON_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ObjPubOn::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  CORBA::ULong i;
  CORBA::ULong length;
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];
  unsigned long l;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(turnUpdatesOnForObjectInstanceStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(classStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", classId);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = attributeList.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    l = attributeList[i];
    sprintf(buf, "%lu", l);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Provide::Provide(const unsigned long &theObjectId, const GeRtiFactory::Handles &theAttributes, const GeRtiFactory::UserSuppliedTag &theTag, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : attributeHandles(theAttributes), fedAmb(theFedAmb), joined(theJoined)
{
  objectId = theObjectId;
  tag = theTag;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Provide::~Provide(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::Provide::execute(void)
{
  RTI::AttributeHandleSet *attributeHandleSetPtr = new RTI::AttributeHandleSet();
  RTI::ObjectInstanceHandle object;
  RTI::UserSuppliedTag userSuppliedTag;
  std::auto_ptr<RTI::AttributeHandleSet> ahs(attributeHandleSetPtr);

  GERTICO::Mapper1516::mapObjectInstanceHandle(object, objectId);
  GERTICO::Mapper1516::mapAttributeHandleSet(*ahs, attributeHandles);
  GERTICO::Mapper1516::mapUserSuppliedTag(userSuppliedTag, tag);

  try
  {
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(p_i0)
                            {
                              sprintf(galMsg,"object=%lu",objectId);
                              E1mEnd(p_i0,galMsg);
                              GERTICO::Mapper::printUserSuppliedTag("tag=", galMsg, tag);
                              E2(aSP_i0, "provideAttributeValueUpdate", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributeHandles);
                              E2(aOS_i0, "provideAttributeValueUpdate", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
      fedAmb.provideAttributeValueUpdate(object, ahs, userSuppliedTag);
    }
  }
  catch(RTI::ObjectInstanceNotKnown &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(p_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::AttributeNotRecognized &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(p_ta,"AttributeNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::AttributeNotOwned &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(p_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::FederateInternalError &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(p_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::Provide::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  CORBA::ULong i;
  CORBA::ULong length;
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];
  unsigned long l;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(provideAttributeValueUpdateStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", objectId);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = attributeHandles.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    l = attributeHandles[i];
    sprintf(buf, "%lu", l);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublishTurnOn::PublishTurnOn(const unsigned long &id, const bool &theOn, RTI::FederateAmbassador &theFedAmb, bool &theJoined, GERTICO::SupportingServicesLRC &theSupportingServicesLRC) : supportingServicesLRC(theSupportingServicesLRC), fedAmb(theFedAmb), joined(theJoined)
{
  classId = id;
  on = theOn;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::PublishTurnOn::~PublishTurnOn(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::PublishTurnOn::execute(void)
{
  if (joined)
  {
    RTI::InteractionClassHandle myClass;
    GERTICO::Mapper1516::mapInteractionClassHandle(myClass, classId);

    if (supportingServicesLRC.getInteractionRelevanceAdvisorySwitch())
    {
      if (on)
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pTON_i0)
                            {
                              sprintf(galMsg,"handle=%lu",classId);
                              E1mEnd(pTON_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
        fedAmb.turnInteractionsOn(myClass);
      }
      else
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(pTO_i0)
                            {
                              sprintf(galMsg,"handle=%lu",classId);
                              E1mEnd(pTO_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
        fedAmb.turnInteractionsOff(myClass);
      }
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::PublishTurnOn::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(turnInteractionsOnStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(classStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", classId);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(onStr.c_str(), tempStr, 99);
  if (on)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::StReg::StReg(unsigned long id, const bool &theStart, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : fedAmb(theFedAmb), joined(theJoined)
{
  classId = id;
  start = theStart;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::StReg::~StReg(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::StReg::execute(void)
{
  try
  {
    if (joined)
    {
      RTI::ObjectClassHandle myClass;
      GERTICO::Mapper1516::mapObjectClassHandle(myClass, classId);

      if (start)
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sR_i0)
                            {
                              sprintf(galMsg,"class=%lu",classId);
                              E1mEnd(sR_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
        fedAmb.startRegistrationForObjectClass(myClass);
      }
      else
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sR_i1)
                            {
                              sprintf(galMsg,"class=%lu",classId);
                              E1mEnd(sR_i1,galMsg);
                            }
                           #endif   // inserted by Gal converter
        fedAmb.stopRegistrationForObjectClass(myClass);
      }
    }
  }
  catch(RTI::ObjectClassNotPublished &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sR_ta,"ObjectClassNotPublished");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch(RTI::FederateInternalError &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(sR_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::StReg::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(stRegistrationForObjectClass.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(classStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", classId);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(startStr.c_str(), tempStr, 99);
  if (start)
  {
    strcpy(buf, "1");
  }
  else
  {
    strcpy(buf, "0");
  }
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ConfirmFederationRestorationRequestJob::ConfirmFederationRestorationRequestJob(GERTICO::EventHandler1516 &theEventHandler1516, std::wstring const &theLabel, bool const &myReason, bool &theJoined) : eventHandler1516(theEventHandler1516), joined(theJoined)
{
  label = theLabel;
  reason = myReason;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ConfirmFederationRestorationRequestJob::~ConfirmFederationRestorationRequestJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ConfirmFederationRestorationRequestJob::execute(void)
{
  if (joined)
  {
    eventHandler1516.processConfirmFederationRestorationRequest(label, reason);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ConfirmFederationRestorationRequestJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventRoJob::EventRoJob(GERTICO::EventHandler1516 &theEventHandler1516, unsigned int const &theNumberOfJobs, bool &theJoined) : eventHandler1516(theEventHandler1516), joined(theJoined)
{
  numberOfJobs = theNumberOfJobs;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EventRoJob::~EventRoJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::EventRoJob::execute(void)
{
  if (joined)
  {
    if (eventHandler1516.processEventRo(false) == false)
    {
      return GERTICO::active;
    }

    numberOfJobs -= 1;

    if (numberOfJobs)
    {
      return GERTICO::active;
    }
    else
    {
      return GERTICO::done;
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::EventRoJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationRestoreBegunJob::FederationRestoreBegunJob(GERTICO::EventHandler1516 &theEventHandler1516, bool &theJoined) : eventHandler1516(theEventHandler1516), joined(theJoined)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationRestoreBegunJob::~FederationRestoreBegunJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationRestoreBegunJob::execute(void)
{
  if (joined)
  {
    eventHandler1516.processFederationRestoreBegun();
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationRestoreBegunJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationRestoredLRCJob::FederationRestoredLRCJob(GERTICO::EventHandler1516 &theEventHandler1516, bool const &theSuccess, GeRtiFactory::RestoreFailureReason const &theFailureReason, bool &theJoined) : eventHandler1516(theEventHandler1516), joined(theJoined)
{
  failureReason = theFailureReason;
  success = theSuccess;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationRestoredLRCJob::~FederationRestoredLRCJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationRestoredLRCJob::execute(void)
{
  if (joined)
  {
    eventHandler1516.processFederationRestored(success, failureReason);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationRestoredLRCJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationSavedLRCJob::FederationSavedLRCJob(GERTICO::EventHandler1516 &theEventHandler1516, bool const &theSuccess, GeRtiFactory::SaveFailureReason const &theFailureReason, bool &theJoined) : eventHandler1516(theEventHandler1516), joined(theJoined)
{
  failureReason = theFailureReason;
  success = theSuccess;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationSavedLRCJob::~FederationSavedLRCJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationSavedLRCJob::execute(void)
{
  if (joined)
  {
    eventHandler1516.processFederationSaved(success, failureReason);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationSavedLRCJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InitiateFederateRestoreJob::InitiateFederateRestoreJob(GERTICO::EventHandler1516 &theEventHandler1516, std::wstring const &theLabel, GeRtiFactory::GeRtiHandle const &theFederate, bool &theJoined) : eventHandler1516(theEventHandler1516), joined(theJoined)
{
  label = theLabel;
  federate = theFederate;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InitiateFederateRestoreJob::~InitiateFederateRestoreJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::InitiateFederateRestoreJob::execute(void)
{
  if (joined)
  {
    eventHandler1516.processInitiateFederateRestore(label, federate);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::InitiateFederateRestoreJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InitiateFederateSaveJob::InitiateFederateSaveJob(GERTICO::EventHandler1516 &theEventHandler1516, bool &theJoined) : eventHandler1516(theEventHandler1516), joined(theJoined)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InitiateFederateSaveJob::~InitiateFederateSaveJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::InitiateFederateSaveJob::execute(void)
{
  if (joined)
  {
    if (eventHandler1516.processInitiateFederateSave() == 0)
    {
      return GERTICO::active;
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::InitiateFederateSaveJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RequestRetractionJob::RequestRetractionJob(GERTICO::EventHandler1516 &theEventHandler1516, GeRtiFactory::ERHandle const &theHandle, bool &theJoined) : eventHandler1516(theEventHandler1516), joined(theJoined)
{
  erHandle = theHandle;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::RequestRetractionJob::~RequestRetractionJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::RequestRetractionJob::execute(void)
{
  if (joined)
  {
    eventHandler1516.processRequestRetraction(erHandle);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::RequestRetractionJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TimedConstrainedEnabledJob::TimedConstrainedEnabledJob(GERTICO::EventHandler1516 &theEventHandler1516, GERTICO::GeRtiFedTime const &theFedTime, bool &theJoined, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory) : eventHandler1516(theEventHandler1516), geRtiFedTimeFactory(theGeRtiFedTimeFactory), joined(theJoined)
{
  myConstrainedTime.reset(geRtiFedTimeFactory.makeZero());
  *myConstrainedTime = theFedTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TimedConstrainedEnabledJob::~TimedConstrainedEnabledJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::TimedConstrainedEnabledJob::execute(void)
{
  if (joined)
  {
    eventHandler1516.processTimeConEnabled(*myConstrainedTime);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::TimedConstrainedEnabledJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TimeRegulationEnabledJob::TimeRegulationEnabledJob(GERTICO::EventHandler1516 &theEventHandler1516, GERTICO::GeRtiFedTime const &theFedTime, bool &theJoined, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory) : eventHandler1516(theEventHandler1516), geRtiFedTimeFactory(theGeRtiFedTimeFactory), joined(theJoined)
{
  myRegulationTime.reset(geRtiFedTimeFactory.makeZero());
  *myRegulationTime = theFedTime;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TimeRegulationEnabledJob::~TimeRegulationEnabledJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::TimeRegulationEnabledJob::execute(void)
{
  if (joined)
  {
    if (eventHandler1516.processTimeRegEnabled(*myRegulationTime) == 2)
    {
      return GERTICO::active;
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::TimeRegulationEnabledJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TimedEventJob::TimedEventJob(GERTICO::EventHandler1516 &theEventHandler1516, unsigned int const &theNumberOfJobs, bool &theJoined) : eventHandler1516(theEventHandler1516), joined(theJoined)
{
  numberOfJobs = theNumberOfJobs;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::TimedEventJob::~TimedEventJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::TimedEventJob::execute(void)
{
  if (joined)
  {
    if (eventHandler1516.processTimedEvent() == 0)
    {
      return GERTICO::active;
    }

    numberOfJobs -= 1;

    if (numberOfJobs)
    {
      return GERTICO::active;
    }
    else
    {
      return GERTICO::done;
    }
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::TimedEventJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ReceiverI1516::ReceiverI1516(void)
{
  asynchronousDelivery = false;
  eventHandler = NULL;
  momLRC = NULL;
  ownClient.client = NULL;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ReceiverI1516::~ReceiverI1516(void)
{
//  clear();
  if (ownClient.client)
  {
    delete ownClient.client;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addAnnounceSynchronizationPoint(const std::wstring &theLabel, const GeRtiFactory::UserSuppliedTag &theTag)
{
  if (federateDB->joined == false)
  {
    return;
  }

  AnSynPt *newAnSynPt = new AnSynPt(theLabel, theTag, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newAnSynPt);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addAttributeIsNotOwned(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
  pm.acquire();
  ownClient.attributeIsNotOwned(theObject, theAttribute);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addAttributeOwnedByRTI(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
  pm.acquire();
  ownClient.attributeOwnedByRTI(theObject, theAttribute);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addAttributeOwnershipDivestitureNotification(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &releasedAttributes)
{
  RegisteredObject* obj =  federateDB->registeredObjectsHolder.getObject(theObject);
  for (unsigned int i=0; i<releasedAttributes.length(); i++)
  {
    AttributeInfo* info = obj->getAttribute (releasedAttributes[i]);
    info->setStatusUnowned();
  }
  pm.acquire();
  ownClient.attributeOwnershipDivestitureNotification(theObject, releasedAttributes);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addAttributeOwnershipAcquisitionNotification(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &securedAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
  RegisteredObject* obj;
  obj = federateDB->registeredObjectsHolder.getObject(theObject);

  for (unsigned int i=0; i<securedAttributes.length(); i++)
  {
    AttributeInfo* info;
    try
    {
      info = obj->getAttribute(securedAttributes[i]);
    }
    catch(GeRtiFactory::AttributeNotDefined ex)
    {
      info = new AttributeInfo();
      obj->addAttribute(securedAttributes[i], info);
    }
    info->setStatusOwned(federateDB->federate);
  }
  pm.acquire();
  ownClient.attributeOwnershipAcquisitionNotification(theObject, securedAttributes, theTag);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addAttributeOwnershipUnavailable(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
  pm.acquire();
  ownClient.attributeOwnershipUnavailable(theObject, theAttributes);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addAttributesInScope(GeRtiFactory::GeRtiHandle &theObject,const GeRtiFactory::Handles &theAttributes)
{
  if (federateDB->joined == false)
  {
    return;
  }

  AttributeScope *newAttributeScope = new AttributeScope(theObject, theAttributes, true, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newAttributeScope);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addAttributesOutOfScope(GeRtiFactory::GeRtiHandle &theObject,const GeRtiFactory::Handles &theAttributes)
{
  if (federateDB->joined == false)
  {
    return;
  }

  AttributeScope *newAttributeScope = new AttributeScope(theObject, theAttributes, false, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newAttributeScope);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addConfirmAttributeOwnershipAcquisitionCancellation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
  pm.acquire();
  ownClient.confirmAttributeOwnershipAcquisitionCancellation(theObject, theAttributes);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addConfirmFederationRestorationRequest(const std::wstring &theLabel, const bool &theSuccess)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    GERTICO::ConfirmFederationRestorationRequestJob *confirmFederationRestorationRequestJob = new GERTICO::ConfirmFederationRestorationRequestJob(*eventHandler, theLabel, theSuccess, federateDB->joined);

    pm.acquire();
    rtiInitiatedServiceJobs.add(confirmFederationRestorationRequestJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addConfirmSynchronizationPointRegistration(const std::wstring &theLabel, const bool &theSuccess, const GeRtiFactory::SynchronizationPointFailureReason &theReason)
{
  if (federateDB->joined == false)
  {
    return;
  }

  CoSynPt *newCoSynPt = new CoSynPt(theLabel, theSuccess, theReason, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newCoSynPt);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addDiscover(const std::wstring &theObjectName, const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::GeRtiHandle &theObjectClass)
{
  if (federateDB->joined == false)
  {
    return;
  }

  Discover *newDiscover = new Discover(theObjectName, theObject, theObjectClass, *federateDB->objectManagementLRC, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newDiscover);
  pm.release();

  federateDB->addObjectReflected(theObject);

  federateDB->addObjectDiscovered(theObject);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addEventHolder(GeRtiFactory::GertiPushEvent const &theGertiPushEvent)
{
  CORBA::Long d;
  CORBA::ULong ind;
  CORBA::ULong len;
  unsigned int numberRO;
  unsigned int numberTSO;

  if (federateDB->joined == false)
  {
    return;
  }

  len = theGertiPushEvent.e.length();
  for (ind = 0; ind < len; ind++)
  {
    if (eventHandler)
    {
      d = theGertiPushEvent.e[ind]._d();
      switch(d)
      {
        case 0:
        {
          eventHandler->addEventHolder(theGertiPushEvent.e[ind].e(), numberRO, numberTSO);
          if (numberRO)
          {
            GERTICO::EventRoJob *eventRoJob = new GERTICO::EventRoJob(*eventHandler, numberRO, federateDB->joined);
            pm.acquire();
            rtiInitiatedServiceJobs.add(eventRoJob);
            pm.release();
          }
          if (numberTSO)
          {
            GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, numberTSO, federateDB->joined);
            pm.acquire();
            rtiInitiatedServiceJobs.add(timedEventJob);
            pm.release();
          }
          break;
        }
        case 1:
        {
          doTm(theGertiPushEvent.e[ind].tmEvent());
        }
        case 2:
        {
          doDm(theGertiPushEvent.e[ind].dmEvent());
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addFederationRestoreBegun(void)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    GERTICO::FederationRestoreBegunJob *timedConstrainedEnabledJob = new GERTICO::FederationRestoreBegunJob(*eventHandler, federateDB->joined);

    pm.acquire();
    rtiInitiatedServiceJobs.add(timedConstrainedEnabledJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addFederationRestoreStatusResponse(const GeRtiFactory::RestoreStatusPairSeq &theFederateStatusVector)
{
  if (federateDB->joined == false)
  {
    return;
  }

  FederationRestoreStatusResponseJob *federationRestoreStatusResponseJob = new FederationRestoreStatusResponseJob(theFederateStatusVector, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(federationRestoreStatusResponseJob);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addFederationRestored(const bool &theSuccess, const GeRtiFactory::RestoreFailureReason &theFailureReason)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    GERTICO::FederationRestoredLRCJob *federationRestoredJob = new GERTICO::FederationRestoredLRCJob(*eventHandler, theSuccess, theFailureReason, federateDB->joined);
    GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);

    pm.acquire();
    rtiInitiatedServiceJobs.add(federationRestoredJob);
    rtiInitiatedServiceJobs.add(timedEventJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addFederationSaveStatusResponse(GeRtiFactory::SaveStatusPairSeq const &theFederateStatusVector)
{
  if (federateDB->joined == false)
  {
    return;
  }

  FederationSaveStatusResponseJob *federationSaveStatusResponseJob = new FederationSaveStatusResponseJob(theFederateStatusVector, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(federationSaveStatusResponseJob);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addFederationSaved(bool const &theSuccess, GeRtiFactory::SaveFailureReason const &theFailureReason)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    GERTICO::FederationSavedLRCJob *federationSavedJob = new GERTICO::FederationSavedLRCJob(*eventHandler, theSuccess, theFailureReason, federateDB->joined);
    GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);

    pm.acquire();
    rtiInitiatedServiceJobs.add(federationSavedJob);
    rtiInitiatedServiceJobs.add(timedEventJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addFederationSynchronized(const std::wstring &theLabel)
{
  if (federateDB->joined == false)
  {
    return;
  }

  FedSync *currFedSync = new FedSync(theLabel, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(currFedSync);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addInformAttributeOwnership(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute, GeRtiFactory::GeRtiHandle const &theOwner)
{
  RegisteredObject* obj;
  obj = federateDB->registeredObjectsHolder.getObject(theObject);

  AttributeInfo* info;
  try
  {
    info = obj->getAttribute(theAttribute);
  }
  catch(GeRtiFactory::AttributeNotDefined &)
  {
    info = new AttributeInfo();
    obj->addAttribute(theAttribute, info);
  }
  info->setStatusOwned(theOwner);

  pm.acquire();
  ownClient.informAttributeOwnership(theObject, theAttribute, theOwner);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addInitiateFederateRestore(const std::wstring &theLabel, const GeRtiFactory::GeRtiHandle &theFederate)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    GERTICO::InitiateFederateRestoreJob *initiateFederateRestoreJob = new GERTICO::InitiateFederateRestoreJob(*eventHandler, theLabel, theFederate, federateDB->joined);

    pm.acquire();
    rtiInitiatedServiceJobs.add(initiateFederateRestoreJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addInitiateFederateSave(const std::wstring &theLabel)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    GERTICO::InitiateFederateSaveJob *initiateFederateSaveJob = new GERTICO::InitiateFederateSaveJob(*eventHandler, federateDB->joined);

    pm.acquire();
    eventHandler->addInitiateFederateSave(theLabel);
    rtiInitiatedServiceJobs.add(initiateFederateSaveJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addInitiateFederateSaveWithTime(std::wstring const &theLabel, GERTICO::GeRtiFedTime const &theTime)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);

    pm.acquire();
    eventHandler->addInitiateFederateSaveWithTime(theLabel, theTime);
    rtiInitiatedServiceJobs.add(timedEventJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addInterPubOff(GeRtiFactory::GeRtiHandle const &theInteraction)
{
  if (federateDB->joined == false)
  {
    return;
  }

  // If the user has not called publish, do not send turn off.
  if (federateDB->declarationManagementLRC->isPublishingInteraction(theInteraction) == false)
  {
    return;
  }

  federateDB->declarationManagementLRC->turnInteractionsOff(theInteraction);

  PublishTurnOn *newPublishTurnOn = new PublishTurnOn(theInteraction, false, *myFedAmb, federateDB->joined, *federateDB->supportingServicesLRC);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newPublishTurnOn);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addInterPubOn(const GeRtiFactory::GeRtiHandle &theInteraction)
{
  if (federateDB->joined == false)
  {
    return;
  }

  // If the user has not called publish, do not send turn on.
  if (federateDB->declarationManagementLRC->isPublishingInteraction(theInteraction) == false)
  {
    return;
  }

  federateDB->declarationManagementLRC->turnInteractionsOn(theInteraction);

  PublishTurnOn *newPublishTurnOn = new PublishTurnOn(theInteraction, true, *myFedAmb, federateDB->joined, *federateDB->supportingServicesLRC);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newPublishTurnOn);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addObjectInstanceNameReservationFailed(std::wstring const &theObjectInstanceName)
{
  if (federateDB->joined == false)
  {
    return;
  }

  ObjectInstanceNameReservationFailedJob *objectInstanceNameReservationFailedJob = new ObjectInstanceNameReservationFailedJob(theObjectInstanceName, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(objectInstanceNameReservationFailedJob);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addObjectInstanceNameReservationSucceeded(std::wstring const &theObjectInstanceName)
{
  if (federateDB->joined == false)
  {
    return;
  }

  ObjectInstanceNameReservationSucceededJob *objectInstanceNameReservationSucceededJob = new ObjectInstanceNameReservationSucceededJob(theObjectInstanceName, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(objectInstanceNameReservationSucceededJob);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addObjPubOff(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers)
{
  GeRtiFactory::Handles attributes;

  if (federateDB->joined == false)
  {
    return;
  }

  federateDB->objectManagementLRC->turnUpdatesOffForObjectInstance(theObject, theAttributeSubscribers, attributes);
  if (federateDB->supportingServicesLRC->getAttributeRelevanceAdvisorySwitch())
  {
    if (attributes.length())
    {
      GERTICO::ObjPubOff *newObjPubOff = new GERTICO::ObjPubOff(theObject, attributes, *myFedAmb, federateDB->joined);

      pm.acquire();
      rtiInitiatedServiceJobs.add(newObjPubOff);
      pm.release();
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addObjPubOn(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers)
{
  GeRtiFactory::Handles attributes;

  if (federateDB->joined == false)
  {
    return;
  }

  federateDB->objectManagementLRC->turnUpdatesOnForObjectInstance(theObject, theAttributeSubscribers, attributes);

  if (federateDB->supportingServicesLRC->getAttributeRelevanceAdvisorySwitch())
  {
    if (attributes.length())
    {
      ObjPubOn *newObjPubOn = new ObjPubOn(theObject, attributes, *myFedAmb, federateDB->joined);

      pm.acquire();
      rtiInitiatedServiceJobs.add(newObjPubOn);
      pm.release();
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addProvideAttributeValueUpdate(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes, const GeRtiFactory::UserSuppliedTag &theTag)
{
  if (federateDB->joined == false)
  {
    return;
  }

  Provide *newProvide = new Provide(theObject, theAttributes, theTag, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newProvide);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addRemove(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theTag)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    eventHandler->addRemove(theObject, theTag, false);
    GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);
    pm.acquire();
    rtiInitiatedServiceJobs.add(timedEventJob);
    pm.release();
  }

  // Removed objects.
  federateDB->addObjectRemoved(theObject);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addRemoveWithTime(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::UserSuppliedTag &theTag, std::auto_ptr<GERTICO::GeRtiFedTime> &theTime, const GeRtiFactory::ERHandle &erh)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    eventHandler->addRemoveWithTime(theObject, theTag, theTime, erh);
    GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);
    pm.acquire();
    rtiInitiatedServiceJobs.add(timedEventJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addRequestAttributeOwnershipAssumption(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &offeredAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
  pm.acquire();
  ownClient.requestAttributeOwnershipAssumption(theObject, offeredAttributes, theTag);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addRequestAttributeOwnershipRelease(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &candidateAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
  pm.acquire();
  ownClient.requestAttributeOwnershipRelease(theObject, candidateAttributes, theTag);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addRequestDivestitureConfirmation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &releasedAttributes)
{
  RegisteredObject* obj =  federateDB->registeredObjectsHolder.getObject(theObject);
  for (unsigned int i=0; i<releasedAttributes.length(); i++)
  {
    AttributeInfo *info;
    try
    {
      info = obj->getAttribute(releasedAttributes[i]);
    }
    catch (GeRtiFactory::AttributeNotDefined ex)
    {
      info = new AttributeInfo();
      obj->addAttribute (releasedAttributes[i], info);
    }
#ifndef IEEE_1516
    info->setStatusUnowned();
#endif
  }
  pm.acquire();
  ownClient.requestDivestitureConfirmation(theObject, releasedAttributes);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addRequestRetraction(GeRtiFactory::ERHandle const &theHandle)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    GERTICO::RequestRetractionJob *requestRetractionJob = new GERTICO::RequestRetractionJob(*eventHandler, theHandle, federateDB->joined);
    pm.acquire();
    rtiInitiatedServiceJobs.add(requestRetractionJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addRetractionHandle(GeRtiFactory::ERHandle const &theERHandle, GERTICO::GeRtiFedTime const &theFedTime)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    eventHandler->addRetractionHandle(theERHandle, theFedTime);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addStartRegistrationForObjectClass(const GeRtiFactory::GeRtiHandle &theClass)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_d)
                            {
                              unsigned long ul;

                              ul = theClass;
                              sprintf(galMsg, "Class=%lu", ul);
                              E2(GeRti_DM_d, "addStartRegistrationForObjectClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  GERTICO::HandleSetMap::iterator itPublishClass;

  if (federateDB->joined == false)
  {
    return;
  }

  StReg *newStReg = new StReg(theClass, true, *myFedAmb, federateDB->joined);

  // If the user has not called publish, do not send start.
  itPublishClass = federateDB->declarationManagementLRC->publishObjectClassSet.find(theClass);
  if (itPublishClass == federateDB->declarationManagementLRC->publishObjectClassSet.end())
  {
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_DM_d, "addStartRegistrationForObjectClass", "Empty");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    return;
  }

  pm.acquire();
  rtiInitiatedServiceJobs.add(newStReg);
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_DM_d, "addStartRegistrationForObjectClass", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addStopRegistrationForObjectClass(const GeRtiFactory::GeRtiHandle &theClass)
{
  GERTICO::HandleSetMap::iterator itPublishClass;

  if (federateDB->joined == false)
  {
    return;
  }

  StReg *newStReg = new StReg(theClass, false, *myFedAmb, federateDB->joined);

  // If the user has not called publish, do not send stop.
  itPublishClass = federateDB->declarationManagementLRC->publishObjectClassSet.find(theClass);
  if (itPublishClass == federateDB->declarationManagementLRC->publishObjectClassSet.end())
  {
    return;
  }

  pm.acquire();
  rtiInitiatedServiceJobs.add(newStReg);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addTimeAdvanceGrant(GERTICO::GeRtiFedTime &theFedTime)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    eventHandler->addTimeAdvanceGrant(theFedTime);
    GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);
    pm.acquire();
    rtiInitiatedServiceJobs.add(timedEventJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addTimeAdvanceGrantGalt(const GERTICO::GeRtiFedTime &theFedTime, const GERTICO::GeRtiFedTime &theGaltFedTime)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    eventHandler->addTimeAdvanceGrantGalt(theFedTime, theGaltFedTime);
    GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);
    pm.acquire();
    rtiInitiatedServiceJobs.add(timedEventJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addTimeAdvanceGrantIntermediate(const GERTICO::GeRtiFedTime &theFedTime)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    eventHandler->addTimeAdvanceGrantIntermediate(theFedTime);
    GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);
    pm.acquire();
    rtiInitiatedServiceJobs.add(timedEventJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::reset(void)
{
  if (eventHandler)
  {
    eventHandler->clear();
  }
  else
  {
    eventHandler = new GERTICO::EventHandler1516(asynchronousDelivery);
  }

  pm.acquire();
  rtiInitiatedServiceJobs.clear();
//  federateDB->objectManagementLRC->reset(); NOT RIGHT TIME!
  pm.release();
  asynchronousDelivery = false;
  if (federateDB->runTimeObjectDB)
  {
    delete federateDB->runTimeObjectDB;
    federateDB->runTimeObjectDB = NULL;
  }
  federateDB->runTimeObjectDB = new GERTICO::RunTimeObjectDB(federateDB->registeredObjectsHolder, federateDB->regionsHolder);
  eventHandler->setRunTimeObjectDB(federateDB->runTimeObjectDB);

  federateDB->reset();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::doMomRequest(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::HandleValues & data)
{
  momLRC->doMomRequest(theRequest, data);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::doDm(GeRtiFactory::GertiDmEvent const &theGertiDmEvent)
{
  if (!eventHandler)
  {
    return;
  }

  switch(theGertiDmEvent.service)
  {
    case 10:
    {
      addStartRegistrationForObjectClass(theGertiDmEvent.theHandle);
      break;
    }
    case 11:
    {
      addStopRegistrationForObjectClass(theGertiDmEvent.theHandle);
      break;
    }
    case 12:
    {
      addInterPubOn(theGertiDmEvent.theHandle);
      break;
    }
    case 13:
    {
      addInterPubOff(theGertiDmEvent.theHandle);
      break;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::doTm(GeRtiFactory::GertiTmEvent const &theGertiTmEvent)
{
  if (!eventHandler)
  {
    return;
  }

  switch(theGertiTmEvent.service)
  {
    case 1:
    {
      std::auto_ptr<GERTICO::GeRtiFedTime> t;

      GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(eventHandler->timeManagementLRC->geRtiFedTimeFactory, t, theGertiTmEvent.timestamp);
      addTimeRegulationEnabled(*t);
      break;
    }
    case 4:
    {
      std::auto_ptr<GERTICO::GeRtiFedTime> t;

      GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(eventHandler->timeManagementLRC->geRtiFedTimeFactory, t, theGertiTmEvent.timestamp);
      addTimeConstrainedEnabled(*t);
      break;
    }
    case 11:
    {
      std::auto_ptr<GERTICO::GeRtiFedTime> t;

      if (theGertiTmEvent.timestamp.length())
      {
        GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(eventHandler->timeManagementLRC->geRtiFedTimeFactory, t, theGertiTmEvent.timestamp);
        if (theGertiTmEvent.timestampTwo.length())
        {
          std::auto_ptr<GERTICO::GeRtiFedTime> tGalt;

          GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(eventHandler->timeManagementLRC->geRtiFedTimeFactory, tGalt, theGertiTmEvent.timestampTwo);
          addTimeAdvanceGrantGalt(*t, *tGalt);
        }
        else
        {
          addTimeAdvanceGrant(*t);
        }
      }
      else
      {
        if (theGertiTmEvent.timestampTwo.length())
        {
          std::auto_ptr<GERTICO::GeRtiFedTime> tGalt;

          GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(eventHandler->timeManagementLRC->geRtiFedTimeFactory, tGalt, theGertiTmEvent.timestampTwo);
          addTimeAdvanceGrantIntermediate(*tGalt);
        }
      }
      break;
    }
    case 14:
    {
      GeRtiFactory::ERHandle eRHandle;

      eRHandle.theSerialNumber = theGertiTmEvent.theHandle;
      eRHandle.sendingFederate = theGertiTmEvent.sourceId;
      addRequestRetraction(eRHandle);
      break;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::federateSaveBegun(void)
{
  if (eventHandler)
  {
    // Only set a flag.
    eventHandler->federateSaveBegun();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ReceiverI1516::getAsynchronousDelivery(void)
{
  return asynchronousDelivery;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::getFederateState(GERTICO::FederateState &theFederateState)
{
  if (eventHandler)
  {
    eventHandler->getFederateState(theFederateState);
  }
}

// ---------------------------------------------------------------------------
// For Mom.
// ---------------------------------------------------------------------------
long GERTICO::ReceiverI1516::getInteractionsReceived(void)
{
  long l = 0;
  if (eventHandler)
  {
    l = eventHandler->getInteractionsReceived();
  }

  return l;
}

// ---------------------------------------------------------------------------
// For Mom.
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::getInteractionsReceivedBestEffort(GERTICO::HandleMap &theInteractions)
{
  if (eventHandler)
  {
    eventHandler->getInteractionsReceivedBestEffort(theInteractions);
  }
}

// ---------------------------------------------------------------------------
// For Mom.
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::getInteractionsReceivedReliable(GERTICO::HandleMap &theInteractions)
{
  if (eventHandler)
  {
    eventHandler->getInteractionsReceivedReliable(theInteractions);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::GeRtiFedTime *GERTICO::ReceiverI1516::getLITS(void)
{
  GERTICO::GeRtiFedTime *t = NULL;

  if (eventHandler)
  {
    t = eventHandler->getLITS();
  }
  return t;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::getMomData(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::Handles & theAttributes, GeRtiFactory::HandleValues_out data)
{
  momLRC->getMomData(theRequest, theAttributes, data);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::ReceiverI1516::getObjectsReflected(void)
{
  long l;

  l = federateDB->getObjectsReflected();
  return l;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::ReceiverI1516::getObjectsUpdated(void)
{
  long l;

  l = federateDB->getObjectsUpdated();
  return l;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::ReceiverI1516::getROlength(void)
{
  long l = 0;

  if (eventHandler)
  {
    l = eventHandler->getROlength();
  }
  return l;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::ReceiverI1516::getReflectionsReceived(void)
{
  long l = 0;

  if (eventHandler)
  {
    l = eventHandler->getReflectionsReceived();
  }
  return l;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::getReflectionsReceivedBestEffort(GERTICO::HandleMap &theReflections)
{
  if (eventHandler)
  {
    eventHandler->getReflectionsReceivedBestEffort(theReflections);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::getReflectionsReceivedReliable(GERTICO::HandleMap &theReflections)
{
  if (eventHandler)
  {
    eventHandler->getReflectionsReceivedReliable(theReflections);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ReceiverI1516::getRestoreInProgress(void)
{
  return eventHandler->getRestoreInProgress();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ReceiverI1516::getSaveInProgress(void)
{
  return eventHandler->getSaveInProgress();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::ReceiverI1516::getTSOlength(void)
{
  long l = 0;

  if (eventHandler)
  {
    l = eventHandler->getTSOlength();
  }
  return l;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::mapper(GERTICO::HandleSet &theHandleSet, const GeRtiFactory::Handles &theHandles)
{
  CORBA::ULong i;
  CORBA::ULong len;

  theHandleSet.clear();

  len = theHandles.length();
  for (i = 0; i < len; i++)
  {
    theHandleSet.insert(theHandles[i]);
  }
}

// ---------------------------------------------------------------------------
// Process all the stored call information.
// ---------------------------------------------------------------------------
bool GERTICO::ReceiverI1516::process(bool const &processAll)
{
  bool ret = false;

  pm.acquire();
  ret = rtiInitiatedServiceJobs.performJobs(processAll);
  pm.release();
  if (ret)
  {
    return true;
  }
  ret = restoreJobs.performJobs(processAll);
//  if (eventHandler)
//  {
//    eventHandler->processEventHolder();
//  }
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::publishObjectClass(const GeRtiFactory::GeRtiHandle &theClass, const GeRtiFactory::Handles& attributeList)
{
                           #ifdef GalDebug   // inserted by Gal converter
                            E1mBegin(GeRti_DM_d)
                            {
                              unsigned long ul;

                              ul = theClass;
                              sprintf(galMsg, "Class=%lu", ul);
                              E2(GeRti_DM_d, "publishObjectClass", galMsg);   // inserted by Gal converter
                              GERTICO::Mapper::printGeRtiFactoryHandles("attributes=", galMsg, attributeList);
                              E2(GeRti_DM_d, "publishObjectClass", galMsg);   // inserted by Gal converter
                            }
                           #endif   // inserted by Gal converter
  CORBA::ULong i;
  CORBA::ULong len;
  GERTICO::HandleSet::iterator itAttribute;
  GERTICO::HandleSetMap::iterator itpublishObjectClassSet;

  itpublishObjectClassSet = federateDB->declarationManagementLRC->publishObjectClassSet.find(theClass);
  if (itpublishObjectClassSet != federateDB->declarationManagementLRC->publishObjectClassSet.end())
  {
    len = attributeList.length();
    for (i = 0; i < len; i++)
    {
      itAttribute = itpublishObjectClassSet->second.find(attributeList[i]);
      if (itAttribute == itpublishObjectClassSet->second.end())
      {
        itpublishObjectClassSet->second.insert(attributeList[i]);
      }
    }
  }
  else
  {
    GERTICO::HandleSet attributes;
    GERTICO::Mapper::mapHandleSet(attributes, attributeList);
    federateDB->declarationManagementLRC->publishObjectClassSet[theClass] = attributes;
  }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_DM_d, "publishObjectClass", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::queryMinNextEventTime(GERTICO::GeRtiFedTime &theTime)
{
  if (eventHandler)
  {
    eventHandler->queryMinNextEventTime(theTime);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::restore(DOMElement &theDOMElement)
{
  if (eventHandler)
  {
    eventHandler->restore(theDOMElement);
  }
//  rtiInitiatedServiceJobs.restore(theDOMElement);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  XMLCh tempStr[100];

  if (eventHandler)
  {
    eventHandler->save(theDOMDocument, theDOMElement);
  }

  XMLString::transcode(rtiInitiatedServicesStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  pm.acquire();
  rtiInitiatedServiceJobs.performSave(theDOMDocument, theDOMElement);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::setAsynchronousDelivery(bool const &theAsynchronousDelivery)
{
  CORBA::WChar *wChar = L"";

  // Check for double call of the service.
  if (asynchronousDelivery == theAsynchronousDelivery)
  {
    // Double call.
    if (asynchronousDelivery)
    {
      throw GeRtiFactory::AsynchronousDeliveryAlreadyEnabled(wChar);
    }
    else
    {
      throw GeRtiFactory::AsynchronousDeliveryAlreadyDisabled(wChar);
    }
  }

  // Set new value.
  asynchronousDelivery = theAsynchronousDelivery;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::initiate(RTI::FederateAmbassador *theFederateAmbassador)
{
  myFedAmb = theFederateAmbassador;

// DOES NOT WORK!
//  if (eventHandler)
//  {
//    delete eventHandler;
//  }
  if (eventHandler == NULL)
  {
    eventHandler = new GERTICO::EventHandler1516(asynchronousDelivery);
  }
  if (eventHandler)
  {
    eventHandler->setFederateAmbassador(theFederateAmbassador);
  }

  if (ownClient.client)
  {
    delete ownClient.client;
  }
  ownClient.client = new HlaOwnershipClientMapper(theFederateAmbassador);
  ownClient.setJobHolder(&rtiInitiatedServiceJobs);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::setTimeService(GERTICO::TimeManagementLRC *theTimeManagementLRC)
{
  eventHandler->setTimeService(theTimeManagementLRC);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::setMomLRC(GERTICO::MomLRC *theMomLRC)
{
  momLRC = theMomLRC;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::setDisableTimeConstrained(void)
{
  if (eventHandler)
  {
    eventHandler->setDisableTimeConstrainedd();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::setDisableTimeRegulation(void)
{
  if (eventHandler)
  {
    eventHandler->setDisableTimeRegulation();
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::setFederate(const GeRtiFactory::GeRtiHandle &theFederate)
{
  federate = theFederate;
  if (eventHandler)
  {
    eventHandler->setFederate(theFederate);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::setFlushQueueRequest(void)
{
  if (eventHandler)
  {
    eventHandler->setFlushQueueRequest();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::setGeRtiAmVar(const GeRtiFactory::GeRtiAmbassador_var &theGeRtiAmVar)
{
  if (eventHandler)
  {
    eventHandler->setGeRtiAmVar(theGeRtiAmVar);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::setNextEventRequest(const bool &vBool)
{
  if (eventHandler)
  {
    eventHandler->setNextEventRequest(vBool);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::setTimeAdvanceRequest(const bool &avail)
{
  if (eventHandler)
  {
    GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);
    eventHandler->setTimeAdvanceRequest(avail);

    // May be a local TAG.
    pm.acquire();
    rtiInitiatedServiceJobs.add(timedEventJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addTimeConstrainedEnabled(GERTICO::GeRtiFedTime const &theFedTime)
{
  if (eventHandler)
  {
    GERTICO::TimedConstrainedEnabledJob *timedConstrainedEnabledJob = new GERTICO::TimedConstrainedEnabledJob(*eventHandler, theFedTime, federateDB->joined, eventHandler->timeManagementLRC->geRtiFedTimeFactory);

    pm.acquire();
    rtiInitiatedServiceJobs.add(timedConstrainedEnabledJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::addTimeRegulationEnabled(GERTICO::GeRtiFedTime const &theFedTime)
{
  if (eventHandler)
  {
    GERTICO::TimeRegulationEnabledJob *timeRegulationEnabledJob = new GERTICO::TimeRegulationEnabledJob(*eventHandler, theFedTime, federateDB->joined, eventHandler->timeManagementLRC->geRtiFedTimeFactory);

    pm.acquire();
    rtiInitiatedServiceJobs.add(timeRegulationEnabledJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::GeRtiFedTime *GERTICO::ReceiverI1516::smallestAvailableTSO(void)
{
  GERTICO::GeRtiFedTime *t = NULL;

  if (eventHandler)
  {
    t = eventHandler->smallestAvailableTSO();
  }
  return t;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::subscribeObjectClassAttributes(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap)
{
  GERTICO::HandleSetMap handleSetMap;
  GERTICO::HandleSetMap::iterator itHandleSetMap;
  GERTICO::Mapper::mapHandleSetMapInvert(handleSetMap, theAttRegMap);
  if (eventHandler)
  {
    for (itHandleSetMap = handleSetMap.begin(); itHandleSetMap != handleSetMap.end(); itHandleSetMap++)
    {
      eventHandler->subscribeObjectClassAttributes(theClass, itHandleSetMap->first, itHandleSetMap->second);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::unsubscribeObjectClassWithRegionReceiver(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theRegion)
{
  // Dummy function for IEEE 1516
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI1516::unsubscribeObjectClassWithRegionsReceiver(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap)
{
  if (eventHandler)
  {
    eventHandler->unsubscribeObjectClassWithRegions(theClass, theAttRegMap);
  }
}
