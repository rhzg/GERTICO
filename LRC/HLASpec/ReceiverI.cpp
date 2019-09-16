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
#include "ReceiverI.h"
#include "HlaOwnershipClientMapper.h"
#include "Util/Mapper.h"
#include "Mapper13.h"

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

std::string GERTICO::FedSync::federationSynchronizedStr("federationSynchronized");
std::string GERTICO::FedSync::labelStr("label");
std::string GERTICO::FedSync::rtiInitiatedServiceStr("rtiInitiatedService");

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

std::string GERTICO::ReceiverI::rtiInitiatedServicesStr("rtiInitiatedServices");

/********************************** Gal begin ***************************************/


#ifdef GalDebug
#define GalHLADebug 1

#include "Gal/StdAfx.h"
#include "Gal/repository.h"
#include "Gal/event.h"

#include "ut.h"

static class Repository_l *DM=(Repository::getSingleInstance())->getRepository_l("GeRtiDM.res","GeRtiDM");

static class Event *GeRti_DM_d=DM->getRefEvent("GeRti_DM_d");
static class Event *GeRti_DM_e=DM->getRefEvent("GeRti_DM_e");
static class Event *GeRti_DM_i=DM->getRefEvent("GeRti_DM_i");
static class Event *GeRti_DM_w=DM->getRefEvent("GeRti_DM_w");

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

static char galMsg[MAX_TXT];

#endif


/********************************** Gal end ***************************************/

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AnSynPt::AnSynPt(const std::wstring &theLabel, const GeRtiFactory::UserSuppliedTag &theTag, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : joined(theJoined), fedAmb(theFedAmb), label(theLabel)
{
  tag = new GeRtiFactory::UserSuppliedTag(theTag);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AnSynPt::~AnSynPt(void)
{
  delete tag;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::AnSynPt::execute(void)
{
  char *cptr;
  std::string l;

  GERTICO::Mapper13::mapUserSuppliedTag(&cptr, *tag);

  GERTICO::Mapper::mapStringFromWstring(l, label);
  try
  {
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aSP_i0)
                            {
                              sprintf(galMsg,"label=%s,tag=%s",l.c_str(), cptr);
                              E1mEnd(aSP_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      fedAmb.announceSynchronizationPoint(l.c_str(), cptr);
    }
  }
  catch(RTI::FederateInternalError &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aSP_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  delete []cptr;

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
  char *cptr;
  std::string l;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(announceSynchronizationPointStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  GERTICO::Mapper::mapStringFromWstring(l, label);
  XMLString::transcode(labelStr.c_str(), tempStr, 99);
  XMLString::transcode(l.c_str(), tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(tagStr.c_str(), tempStr, 99);
  GERTICO::Mapper13::mapUserSuppliedTag(&cptr, *tag);
  XMLString::transcode(cptr, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::AttributeScope::AttributeScope(const GeRtiFactory::GeRtiHandle &theObject, const GeRtiFactory::Handles &theAttributes, const bool &theIn, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : joined(theJoined), fedAmb(theFedAmb)
{
  myObject = theObject;
  myAttributes = theAttributes;
  inScope = theIn;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::AttributeScope::execute(void)
{
  RTI::AttributeHandleSet *ahs;

  ahs = RTI::AttributeHandleSetFactory::create(myAttributes.length());
  GERTICO::Mapper13::mapAttributeHandleSet(*ahs, myAttributes);
  try
  {
    if (joined)
    {
      if (inScope)
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aIS_i0)
                            {
                              sprintf(galMsg,"object=%lu",myObject);
                              ut::printAttributeHandleSet(galMsg,*ahs);
                              E1mEnd(aIS_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
        fedAmb.attributesInScope(myObject, *ahs);
      }
      else
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(aOS_i0)
                            {
                              sprintf(galMsg,"object=%lu",myObject);
                              ut::printAttributeHandleSet(galMsg,*ahs);
                              E1mEnd(aOS_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
        fedAmb.attributesOutOfScope(myObject, *ahs);
      }
    }
  }
  catch(RTI::FederateInternalError &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(aOS_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  delete ahs;

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
  unsigned long length;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(attributeScopeStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", myObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = myAttributes.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", myAttributes[i]);
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
GERTICO::CoSynPt::CoSynPt(const std::wstring &theLabel, const bool &b, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : label(theLabel), joined(theJoined), fedAmb(theFedAmb)
{
  success = b;
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
    std::string l;
    GERTICO::Mapper::mapStringFromWstring(l, label);
    if (success)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cSP_i0)
                            {
                              sprintf(galMsg,"label=%s",l.c_str());
                              E1mEnd(cSP_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      fedAmb.synchronizationPointRegistrationSucceeded(l.c_str());
    }
    else
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(cSP_i1)
                            {
                              sprintf(galMsg,"label=%s",l.c_str());
                              E1mEnd(cSP_i1,galMsg);
                            }
                           #endif   // inserted by Gal converter
      fedAmb.synchronizationPointRegistrationFailed(l.c_str());
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
GERTICO::Discover::Discover(const std::wstring &myName, unsigned long myObjectId, unsigned long myClassId, GERTICO::ObjectManagementLRC &theObjectManagementLRC, RTI::FederateAmbassador &theFedAmb, bool &theJoined) :   objectManagementLRC(theObjectManagementLRC), name(myName), joined(theJoined), fedAmb(theFedAmb)
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
  try
  {
    // if object is already known do nothing
    objectManagementLRC.discoverObjectInstance(objectId, classId, name);
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(d_i0)
                            {
                              sprintf(galMsg,"object=%lu,class=%lu,name=%s",objectId, classId, name.c_str());
                              E1mEnd(d_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      std::string s;
      GERTICO::Mapper::mapStringFromWstring(s, name);
      fedAmb.discoverObjectInstance(objectId, classId, s.c_str());
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
GERTICO::FedSync::FedSync(const std::wstring &theLabel, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : label(theLabel), joined(theJoined), fedAmb(theFedAmb)
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
  std::string l;
  GERTICO::Mapper::mapStringFromWstring(l, label);
  try
  {
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(fS_i0)
                            {
                              sprintf(galMsg,"label=%s",l.c_str());
                              E1mEnd(fS_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      fedAmb.federationSynchronized(l.c_str());
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
GERTICO::ObjPubOff::ObjPubOff (const unsigned long &id, const GeRtiFactory::Handles &ahs, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : attributeList (ahs), joined(theJoined), fedAmb(theFedAmb)
{
  classId = id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjPubOff::~ObjPubOff (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ObjPubOff::execute(void)
{
  CORBA::ULong length;
  RTI::AttributeHandleSet *ahs = NULL;

  try
  {
    length = attributeList.length();
    ahs = RTI::AttributeHandleSetFactory::create(length);
    GERTICO::Mapper13::mapAttributeHandleSet(*ahs, attributeList);
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(oPO_i0)
                            {
                              sprintf(galMsg,"object=%lu",classId);
                              ut::printAttributeHandleSet(galMsg,*ahs);
                              E1mEnd(oPO_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      fedAmb.turnUpdatesOffForObjectInstance(classId, *ahs);
    }
  }
  catch (RTI::ObjectNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPO_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::AttributeNotOwned)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPO_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::FederateInternalError)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPO_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  delete ahs;

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
    sprintf(buf, "%lu", attributeList[i]);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjPubOn::ObjPubOn (const unsigned long &id, const GeRtiFactory::Handles &ahs, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : attributeList (ahs), joined(theJoined), fedAmb(theFedAmb)
{
  classId = id;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ObjPubOn::~ObjPubOn (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::ObjPubOn::execute(void)
{
  CORBA::ULong length;
  RTI::AttributeHandleSet *ahs = NULL;

  try
  {
    length = attributeList.length();
    ahs = RTI::AttributeHandleSetFactory::create(length);
    GERTICO::Mapper13::mapAttributeHandleSet(*ahs, attributeList);
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(oPON_i0)
                            {
                              sprintf(galMsg,"object=%lu",classId);
                              ut::printAttributeHandleSet(galMsg,*ahs);
                              E1mEnd(oPON_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      fedAmb.turnUpdatesOnForObjectInstance(classId, *ahs);
    }
  }
  catch (RTI::ObjectNotKnown)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPON_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::AttributeNotOwned)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPON_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::FederateInternalError)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(oPON_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  delete ahs;

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
    sprintf(buf, "%lu", attributeList[i]);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Provide::Provide (const unsigned long &myObjectId, const GeRtiFactory::Handles &ahs, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : attributeHandles (ahs), joined(theJoined), fedAmb(theFedAmb)
{
  objectId = myObjectId;
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Provide::~Provide (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::Provide::execute(void)
{
  CORBA::ULong length;
  RTI::AttributeHandleSet *ahs;

  try
  {
    length = attributeHandles.length ();
    ahs = RTI::AttributeHandleSetFactory::create(length);
    GERTICO::Mapper13::mapAttributeHandleSet(*ahs, attributeHandles);
    if (joined)
    {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(p_i0)
                            {
                              sprintf(galMsg,"object=%lu",objectId);
                              ut::printAttributeHandleSet(galMsg,*ahs);
                              E1mEnd(p_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
      fedAmb.provideAttributeValueUpdate(objectId, *ahs);
    }
  }
  catch (RTI::ObjectNotKnown &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(p_ta,"ObjectNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::AttributeNotKnown &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(p_ta,"AttributeNotKnown");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::AttributeNotOwned &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(p_ta,"AttributeNotOwned");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }
  catch (RTI::FederateInternalError &)
  {
                           #ifdef GalHLADebug   // inserted by Gal converter
                             E1(p_ts,"FederateInternalError");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  }

  delete ahs;

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
    sprintf(buf, "%lu", attributeHandles[i]);
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
GERTICO::PublishTurnOn::~PublishTurnOn (void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::PublishTurnOn::execute(void)
{
  if (joined)
  {
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
        fedAmb.turnInteractionsOn(classId);
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
        fedAmb.turnInteractionsOff(classId);
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
GERTICO::StReg::StReg(unsigned long id, const bool &theStart, RTI::FederateAmbassador &theFedAmb, bool &theJoined) : joined(theJoined), fedAmb(theFedAmb)
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
      if (start)
      {
                           #ifdef GalHLADebug   // inserted by Gal converter
                            E1mBegin(sR_i0)
                            {
                              sprintf(galMsg,"class=%lu",classId);
                              E1mEnd(sR_i0,galMsg);
                            }
                           #endif   // inserted by Gal converter
        fedAmb.startRegistrationForObjectClass(classId);
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
        fedAmb.stopRegistrationForObjectClass(classId);
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
GERTICO::ConfirmFederationRestorationRequestJob::ConfirmFederationRestorationRequestJob(GERTICO::EventHandler &theEventHandler, std::wstring const &theLabel, bool const &myReason, bool &theJoined) : eventHandler(theEventHandler), joined(theJoined)
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
    eventHandler.processConfirmFederationRestorationRequest(label, reason);
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
GERTICO::EventRoJob::EventRoJob(GERTICO::EventHandler &theEventHandler, unsigned int const &theNumberOfJobs, bool &theJoined) : eventHandler(theEventHandler), joined(theJoined)
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
    if (eventHandler.processEventRo(false) == false)
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
GERTICO::FederationRestoreBegunJob::FederationRestoreBegunJob(GERTICO::EventHandler &theEventHandler, bool &theJoined) : eventHandler(theEventHandler), joined(theJoined)
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
    eventHandler.processFederationRestoreBegun();
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
GERTICO::FederationRestoredLrcJob::FederationRestoredLrcJob(GERTICO::EventHandler &theEventHandler, bool const &theSuccess, GeRtiFactory::RestoreFailureReason const &theFailureReason, bool &theJoined) : eventHandler(theEventHandler), joined(theJoined)
{
  failureReason = theFailureReason;
  success = theSuccess;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationRestoredLrcJob::~FederationRestoredLrcJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationRestoredLrcJob::execute(void)
{
  if (joined)
  {
    eventHandler.processFederationRestored(success, failureReason);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationRestoredLrcJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationSavedLrcJob::FederationSavedLrcJob(GERTICO::EventHandler &theEventHandler, bool const &theSuccess, GeRtiFactory::SaveFailureReason const &theFailureReason, bool &theJoined) : eventHandler(theEventHandler), joined(theJoined)
{
  failureReason = theFailureReason;
  success = theSuccess;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederationSavedLrcJob::~FederationSavedLrcJob(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationSavedLrcJob::execute(void)
{
  if (joined)
  {
    eventHandler.processFederationSaved(success, failureReason);
  }

  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::JobStatus GERTICO::FederationSavedLrcJob::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  return GERTICO::done;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::InitiateFederateRestoreJob::InitiateFederateRestoreJob(GERTICO::EventHandler &theEventHandler, std::wstring const &theLabel, GeRtiFactory::GeRtiHandle const &theFederate, bool &theJoined) : eventHandler(theEventHandler), joined(theJoined)
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
    eventHandler.processInitiateFederateRestore(label, federate);
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
GERTICO::InitiateFederateSaveJob::InitiateFederateSaveJob(GERTICO::EventHandler &theEventHandler, bool &theJoined) : eventHandler(theEventHandler), joined(theJoined)
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
    if (eventHandler.processInitiateFederateSave() == 0)
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
GERTICO::RequestRetractionJob::RequestRetractionJob(GERTICO::EventHandler &theEventHandler, GeRtiFactory::ERHandle const &theHandle, bool &theJoined) : eventHandler(theEventHandler), joined(theJoined)
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
    eventHandler.processRequestRetraction(erHandle);
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
GERTICO::TimedConstrainedEnabledJob::TimedConstrainedEnabledJob(GERTICO::EventHandler &theEventHandler, GERTICO::GeRtiFedTime const &theFedTime, bool &theJoined, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory) : eventHandler(theEventHandler), geRtiFedTimeFactory(theGeRtiFedTimeFactory), joined(theJoined)
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
    eventHandler.processTimeConEnabled(*myConstrainedTime);
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
GERTICO::TimeRegulationEnabledJob::TimeRegulationEnabledJob(GERTICO::EventHandler &theEventHandler, GERTICO::GeRtiFedTime const &theFedTime, bool &theJoined, GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory) : eventHandler(theEventHandler), geRtiFedTimeFactory(theGeRtiFedTimeFactory), joined(theJoined)
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
    if (eventHandler.processTimeRegEnabled(*myRegulationTime) == 2)
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
GERTICO::TimedEventJob::TimedEventJob(GERTICO::EventHandler &theEventHandler, unsigned int const &theNumberOfJobs, bool &theJoined) : eventHandler(theEventHandler), joined(theJoined)
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
    if (eventHandler.processTimedEvent() == 0)
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
GERTICO::ReceiverI::ReceiverI(void)
{
  asynchronousDelivery = false;
  eventHandler = NULL;
  momLRC = NULL;
  ownClient.client = NULL;

  eventHandler = new GERTICO::EventHandler(asynchronousDelivery);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::ReceiverI::~ReceiverI (void)
{
//  clear();
  if (eventHandler)
  {
    delete eventHandler;
    eventHandler = NULL;
  }

  if (ownClient.client)
  {
    delete ownClient.client;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addAnnounceSynchronizationPoint(std::wstring const &theLabel, GeRtiFactory::UserSuppliedTag const &theTag)
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
void GERTICO::ReceiverI::addAttributeIsNotOwned(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
  ownClient.attributeIsNotOwned(theObject, theAttribute);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addAttributeOwnedByRTI(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute)
{
  ownClient.attributeOwnedByRTI(theObject, theAttribute);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addAttributeOwnershipDivestitureNotification(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &releasedAttributes)
{
  RegisteredObject* obj =  federateDB->registeredObjectsHolder.getObject(theObject);
  for (unsigned int i=0; i<releasedAttributes.length(); i++)
  {
    AttributeInfo* info = obj->getAttribute (releasedAttributes[i]);
    info->setStatusUnowned();
  }
  ownClient.attributeOwnershipDivestitureNotification(theObject, releasedAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addAttributeOwnershipAcquisitionNotification(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &securedAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
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
  ownClient.attributeOwnershipAcquisitionNotification(theObject, securedAttributes, theTag);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addAttributeOwnershipUnavailable(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
  ownClient.attributeOwnershipUnavailable(theObject, theAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addAttributesInScope (GeRtiFactory::GeRtiHandle &theObject, GeRtiFactory::Handles const &theAttributes)
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
void GERTICO::ReceiverI::addAttributesOutOfScope (GeRtiFactory::GeRtiHandle &theObject, GeRtiFactory::Handles const &theAttributes)
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
void GERTICO::ReceiverI::addConfirmAttributeOwnershipAcquisitionCancellation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes)
{
  ownClient.confirmAttributeOwnershipAcquisitionCancellation(theObject, theAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addConfirmFederationRestorationRequest (std::wstring const &theLabel, bool const &theSuccess)
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
void GERTICO::ReceiverI::addConfirmSynchronizationPointRegistration(std::wstring const &theLabel, bool const &theSuccess, GeRtiFactory::SynchronizationPointFailureReason const &theReason)
{
  if (federateDB->joined == false)
  {
    return;
  }

  CoSynPt *newCoSynPt = new CoSynPt(theLabel, theSuccess, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newCoSynPt);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addDiscover(std::wstring const &theObjectName, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theObjectClass)
{
  std::set <GeRtiFactory::GeRtiHandle>::iterator its;

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
void GERTICO::ReceiverI::addEventHolder(GeRtiFactory::GertiPushEvent const &theGertiPushEvent)
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

  len = theGertiPushEvent.e.length ();
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
void GERTICO::ReceiverI::addFederationRestoreBegun (void)
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
void GERTICO::ReceiverI::addFederationRestored(bool const &theSuccess, GeRtiFactory::RestoreFailureReason const &theFailureReason)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    GERTICO::FederationRestoredLrcJob *federationRestoredJob = new GERTICO::FederationRestoredLrcJob(*eventHandler, theSuccess, theFailureReason, federateDB->joined);
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
void GERTICO::ReceiverI::addFederationRestoreStatusResponse(const GeRtiFactory::RestoreStatusPairSeq &theFederateStatusVector)
{
  if (federateDB->joined == false)
  {
    return;
  }

  // Dummy function for HLA 1.3
  throw GeRtiFactory::FederateInternalError(L"Not for HLA 1.3");
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addFederationSaved(bool const &theSuccess, GeRtiFactory::SaveFailureReason const &theFailureReason)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    GERTICO::FederationSavedLrcJob *federationSavedJob = new GERTICO::FederationSavedLrcJob(*eventHandler, theSuccess, theFailureReason, federateDB->joined);
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
void GERTICO::ReceiverI::addFederationSaveStatusResponse(const GeRtiFactory::SaveStatusPairSeq & theFederateStatusVector)
{
  if (federateDB->joined == false)
  {
    return;
  }

  // Dummy function for HLA 1.3
  throw GeRtiFactory::FederateInternalError(L"Not for HLA 1.3");
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addFederationSynchronized(std::wstring const &theLabel)
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
void GERTICO::ReceiverI::addInformAttributeOwnership(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute, GeRtiFactory::GeRtiHandle const &theOwner)
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

  ownClient.informAttributeOwnership(theObject, theAttribute, theOwner);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addInterPubOff(GeRtiFactory::GeRtiHandle const &theInteraction)
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

  federateDB->declarationManagementLRC->turnInteractionsOff(theInteraction);

  PublishTurnOn *newPublishTurnOn = new PublishTurnOn(theInteraction, false, *myFedAmb, federateDB->joined, *federateDB->supportingServicesLRC);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newPublishTurnOn);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addInterPubOn(GeRtiFactory::GeRtiHandle const &theInteraction)
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

  federateDB->declarationManagementLRC->turnInteractionsOn(theInteraction);

  PublishTurnOn *newPublishTurnOn = new PublishTurnOn(theInteraction, true, *myFedAmb, federateDB->joined, *federateDB->supportingServicesLRC);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newPublishTurnOn);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addInitiateFederateRestore(std::wstring const &theLabel, GeRtiFactory::GeRtiHandle const &theFederate)
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
void GERTICO::ReceiverI::addInitiateFederateSave(std::wstring const &theLabel)
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
void GERTICO::ReceiverI::addInitiateFederateSaveWithTime(std::wstring const &theLabel, GERTICO::GeRtiFedTime const &theTime)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    if (eventHandler->timeManagementLRC->isTimeConstrained())
    {
      GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);

      pm.acquire();
      eventHandler->addInitiateFederateSaveWithTime(theLabel, theTime);
      rtiInitiatedServiceJobs.add(timedEventJob);
      pm.release();
    }
    else
    {
      GERTICO::InitiateFederateSaveJob *initiateFederateSaveJob = new GERTICO::InitiateFederateSaveJob(*eventHandler, federateDB->joined);

      pm.acquire();
      eventHandler->addInitiateFederateSave(theLabel);
      rtiInitiatedServiceJobs.add(initiateFederateSaveJob);
      pm.release();
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addObjectInstanceNameReservationFailed(std::wstring const &theObjectInstanceName)
{
  if (federateDB->joined == false)
  {
    return;
  }

  // Dummy function for HLA 1.3
  throw GeRtiFactory::FederateInternalError(L"Not for HLA 1.3");
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addObjectInstanceNameReservationSucceeded(std::wstring const &theObjectInstanceName)
{
  if (federateDB->joined == false)
  {
    return;
  }

  // Dummy function for HLA 1.3
  throw GeRtiFactory::FederateInternalError(L"Not for HLA 1.3");
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addObjPubOff(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers)
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
void GERTICO::ReceiverI::addObjPubOn(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::HandleSetMap const &theAttributeSubscribers)
{
  GeRtiFactory::Handles attributes;

  if (federateDB->joined == false)
  {
    return;
  }

  federateDB->objectManagementLRC->turnUpdatesOnForObjectInstance(theObject, theAttributeSubscribers, attributes);

  if (federateDB->supportingServicesLRC->getAttributeRelevanceAdvisorySwitch())
  {
//  if (attributes.length())
//  {
    ObjPubOn *newObjPubOn = new ObjPubOn(theObject, attributes, *myFedAmb, federateDB->joined);

    pm.acquire();
    rtiInitiatedServiceJobs.add(newObjPubOn);
    pm.release();
//  }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addProvideAttributeValueUpdate(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &theAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
  if (federateDB->joined == false)
  {
    return;
  }

  Provide *newProvide = new Provide(theObject, theAttributes, *myFedAmb, federateDB->joined);

  pm.acquire();
  rtiInitiatedServiceJobs.add(newProvide);
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addRemove (GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theTag)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    eventHandler->addRemove(theObject, theTag);
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
void GERTICO::ReceiverI::addRemoveWithTime (GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::UserSuppliedTag const &theTag, std::auto_ptr<GERTICO::GeRtiFedTime> &theTime, GeRtiFactory::ERHandle const &erh)
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
void GERTICO::ReceiverI::addRequestAttributeOwnershipAssumption(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &offeredAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
  ownClient.requestAttributeOwnershipAssumption(theObject, offeredAttributes, theTag);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addRequestAttributeOwnershipRelease(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &candidateAttributes, GeRtiFactory::UserSuppliedTag const &theTag)
{
  ownClient.requestAttributeOwnershipRelease(theObject, candidateAttributes, theTag);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addRequestDivestitureConfirmation(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::Handles const &releasedAttributes)
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
  ownClient.requestDivestitureConfirmation(theObject, releasedAttributes);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addRequestRetraction (GeRtiFactory::ERHandle const & theHandle)
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
void GERTICO::ReceiverI::addRetractionHandle(GeRtiFactory::ERHandle const &theERHandle, GERTICO::GeRtiFedTime const &theFedTime)
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
void GERTICO::ReceiverI::addStartRegistrationForObjectClass (GeRtiFactory::GeRtiHandle const &theClass)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DM_i, "addStartRegistrationForObjectClass", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  GERTICO::HandleSet::iterator itPublishClass;

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
                             E2(GeRti_DM_i, "addStartRegistrationForObjectClass", "LeaveA");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
    return;
  }

  pm.acquire();
  rtiInitiatedServiceJobs.add(newStReg);
  pm.release();
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DM_i, "addStartRegistrationForObjectClass", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addStopRegistrationForObjectClass (GeRtiFactory::GeRtiHandle const &theClass)
{
  GERTICO::HandleSet::iterator itPublishClass;

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
void GERTICO::ReceiverI::addTimeAdvanceGrant(GERTICO::GeRtiFedTime &GeRtiFedTime)
{
  if (federateDB->joined == false)
  {
    return;
  }

  if (eventHandler)
  {
    eventHandler->addTimeAdvanceGrant(GeRtiFedTime);
    GERTICO::TimedEventJob *timedEventJob = new GERTICO::TimedEventJob(*eventHandler, 1, federateDB->joined);
    pm.acquire();
    rtiInitiatedServiceJobs.add(timedEventJob);
    pm.release();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addTimeAdvanceGrantGalt(const GERTICO::GeRtiFedTime &theFedTime, const GERTICO::GeRtiFedTime &theGaltFedTime)
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
void GERTICO::ReceiverI::addTimeAdvanceGrantIntermediate(GERTICO::GeRtiFedTime const &theFedTime)
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
void GERTICO::ReceiverI::reset(void)
{
  if (eventHandler)
  {
    eventHandler->clear();
  }

  pm.acquire();
  rtiInitiatedServiceJobs.clear();
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
void GERTICO::ReceiverI::doMomRequest(GeRtiFactory::GeRtiHandle theRequest, GeRtiFactory::HandleValues const & data)
{
  momLRC->doMomRequest(theRequest, data);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::doDm(GeRtiFactory::GertiDmEvent const &theGertiDmEvent)
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
void GERTICO::ReceiverI::doTm(GeRtiFactory::GertiTmEvent const &theGertiTmEvent)
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
void GERTICO::ReceiverI::federateSaveBegun(void)
{
  eventHandler->federateSaveBegun();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ReceiverI::getAsynchronousDelivery(void)
{
  return asynchronousDelivery;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::getFederateState(GERTICO::FederateState &theFederateState)
{
  eventHandler->getFederateState(theFederateState);
}

// ---------------------------------------------------------------------------
// For Mom.
// ---------------------------------------------------------------------------
long GERTICO::ReceiverI::getInteractionsReceived (void)
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
void GERTICO::ReceiverI::getInteractionsReceivedBestEffort(GERTICO::HandleMap &theInteractions)
{
  if (eventHandler)
  {
    eventHandler->getInteractionsReceivedBestEffort(theInteractions);
  }
}

// ---------------------------------------------------------------------------
// For Mom.
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::getInteractionsReceivedReliable(GERTICO::HandleMap &theInteractions)
{
  if (eventHandler)
  {
    eventHandler->getInteractionsReceivedReliable(theInteractions);
  }
}

// ---------------------------------------------------------------------------
// For Mom.
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::getMomData(GeRtiFactory::GeRtiHandle theRequest, GeRtiFactory::Handles const & theAttributes, GeRtiFactory::HandleValues_out data)
{
  momLRC->getMomData(theRequest, theAttributes, data);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::ReceiverI::getROlength (void)
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
long GERTICO::ReceiverI::getReflectionsReceived (void)
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
void GERTICO::ReceiverI::getReflectionsReceivedBestEffort(GERTICO::HandleMap &theReflections)
{
  if (eventHandler)
  {
    eventHandler->getReflectionsReceivedBestEffort(theReflections);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::getReflectionsReceivedReliable(GERTICO::HandleMap &theReflections)
{
  if (eventHandler)
  {
    eventHandler->getReflectionsReceivedReliable(theReflections);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ReceiverI::getRestoreInProgress(void)
{
  return eventHandler->getRestoreInProgress();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::ReceiverI::getSaveInProgress(void)
{
  return eventHandler->getSaveInProgress();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
long GERTICO::ReceiverI::getTSOlength (void)
{
  long l = 0;

  if (eventHandler)
  {
    l = eventHandler->getTSOlength();
  }
  return l;
}

// ---------------------------------------------------------------------------
// Process all the stored call information.
// ---------------------------------------------------------------------------
bool GERTICO::ReceiverI::process(bool const &processAll)
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
void GERTICO::ReceiverI::publishObjectClass(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::Handles const & attributeList)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DM_i, "ReceiverI::publishObjectClass", "Enter");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
  federateDB->declarationManagementLRC->publishObjectClassSet.insert(theClass);
                           #ifdef GalDebug   // inserted by Gal converter
                             E2(GeRti_DM_i, "ReceiverI::publishObjectClass", "Leave");   // inserted by Gal converter
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::queryMinNextEventTime(GERTICO::GeRtiFedTime &theTime)
{
  if (eventHandler)
  {
    eventHandler->queryMinNextEventTime(theTime);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::restore(DOMElement &theDOMElement)
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
void GERTICO::ReceiverI::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
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
void GERTICO::ReceiverI::setAsynchronousDelivery(bool const &theAsynchronousDelivery)
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
void GERTICO::ReceiverI::setDisableTimeConstrained(void)
{
  if (eventHandler)
  {
    eventHandler->setDisableTimeConstrainedd();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::setDisableTimeRegulation(void)
{
  if (eventHandler)
  {
    eventHandler->setDisableTimeRegulation();
  }
}


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::setFlushQueueRequest(void)
{
  if (eventHandler)
  {
    eventHandler->setFlushQueueRequest();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::setGeRtiAmVar(GeRtiFactory::GeRtiAmbassador_var const &theGeRtiAmVar)
{
  if (eventHandler)
  {
    eventHandler->setGeRtiAmVar(theGeRtiAmVar);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::setNextEventRequest(bool const &avail)
{
  if (eventHandler)
  {
    eventHandler->setNextEventRequest(avail);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::setTimeAdvanceRequest(bool const &avail)
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
void GERTICO::ReceiverI::initiate(RTI::FederateAmbassador *theFederateAmbassador)
{
  myFedAmb = theFederateAmbassador;

// DOES NOT WORK!
//  if (eventHandler)
//  {
//    delete eventHandler;
//  }
  eventHandler = new GERTICO::EventHandler(asynchronousDelivery);
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
void GERTICO::ReceiverI::setTimeService(GERTICO::TimeManagementLRC *theTimeManagementLRC)
{
  eventHandler->setTimeService(theTimeManagementLRC);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::setMomLRC(GERTICO::MomLRC *theMomLRC)
{
  momLRC = theMomLRC;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::addTimeConstrainedEnabled(GERTICO::GeRtiFedTime const &theFedTime)
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
void GERTICO::ReceiverI::addTimeRegulationEnabled(GERTICO::GeRtiFedTime const &theFedTime)
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
GERTICO::GeRtiFedTime *GERTICO::ReceiverI::smallestAvailableTSO (void)
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
void GERTICO::ReceiverI::unsubscribeObjectClassWithRegionReceiver(GeRtiFactory::GeRtiHandle const &theClass, GeRtiFactory::GeRtiHandle const &theRegion)
{
  if (eventHandler)
  {
    eventHandler->unsubscribeObjectClassWithRegion(theClass, theRegion);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ReceiverI::unsubscribeObjectClassWithRegionsReceiver(GeRtiFactory::GeRtiHandle const &theClass, GERTICO::HandleSetMap &theAttRegMap)
{
  // Dummy function for HLA 1.3
  throw GeRtiFactory::FederateInternalError(L"Not for HLA 1.3");
}
