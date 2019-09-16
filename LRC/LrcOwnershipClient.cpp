/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**
 
$Author: mul $
$Log: LrcOwnershipClient.cpp,v $
Revision 1.13  2008/11/19 14:10:16  mul
Changes for logging.

Revision 1.12  2007/09/06 06:35:25  mul
Changes for ieee1516.

Revision 1.11  2007/06/26 08:30:58  mul
Changes for ieee1516.

Revision 1.10  2007/06/08 12:12:23  mul
Changes for ieee1516.

Revision 1.9  2006/05/23 11:36:59  mul
Remove extra aoa/aoaif logic.

Revision 1.8  2006/04/21 07:19:25  mul
Fix aoa and aoaia logic.

Revision 1.7  2005/09/20 14:49:49  mul
Fix a memory leak.

Revision 1.6  2005/05/04 11:01:58  mul
Add save logic.

Revision 1.5  2005/02/11 14:49:30  mul
Add scoping.

Revision 1.4  2003/05/28 07:37:21  mul
Use include paths starting in $GERTICO.

Revision 1.3  2003/05/21 08:08:41  hzg
remove debug output

Revision 1.2  2003/04/29 06:26:11  hzg
Portierung auf Windows

Revision 1.1  2002/11/06 15:06:24  hzg
Ownership included

Revision 1.4  2002/10/22 06:17:27  hzg
acquire cancel

Revision 1.3  2002/10/15 13:47:23  hzg
Divestiture

Revision 1.2  2002/10/01 15:23:10  hzg
Ownership transfer

Revision 1.1  2002/09/19 11:30:05  hzg
base system


 
**
*******************************************************************************/

#include "ace/Thread_Manager.h"
#include "Util/GeRtiOrb.h" 
#include "Util/Mapper.h" 
#include "LrcOwnershipClient.h"

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

// Static strings for save/restore.
std::string RequestAttributeOwnershipAssumption::attributeStr("attribute");
std::string RequestAttributeOwnershipAssumption::attributesStr("attributes");
std::string RequestAttributeOwnershipAssumption::objectStr("object");
std::string RequestAttributeOwnershipAssumption::rtiInitiatedServiceStr("rtiInitiatedService");
std::string RequestAttributeOwnershipAssumption::requestAttributeOwnershipAssumptionStr("requestAttributeOwnershipAssumption");
std::string RequestAttributeOwnershipAssumption::tagStr("tag");

std::string RequestDivestitureConfirmation::attributeStr("attribute");
std::string RequestDivestitureConfirmation::attributesStr("attributes");
std::string RequestDivestitureConfirmation::objectStr("object");
std::string RequestDivestitureConfirmation::rtiInitiatedServiceStr("rtiInitiatedService");
std::string RequestDivestitureConfirmation::requestDivestitureConfirmationStr("requestDivestitureConfirmation");

std::string AttributeOwnershipDivestitureNotification::attributeStr("attribute");
std::string AttributeOwnershipDivestitureNotification::attributesStr("attributes");
std::string AttributeOwnershipDivestitureNotification::objectStr("object");
std::string AttributeOwnershipDivestitureNotification::rtiInitiatedServiceStr("rtiInitiatedService");
std::string AttributeOwnershipDivestitureNotification::attributeOwnershipDivestitureNotificationStr("attributeOwnershipDivestitureNotification");

std::string AttributeOwnershipAcquisitionNotification::attributeStr("attribute");
std::string AttributeOwnershipAcquisitionNotification::attributesStr("attributes");
std::string AttributeOwnershipAcquisitionNotification::objectStr("object");
std::string AttributeOwnershipAcquisitionNotification::rtiInitiatedServiceStr("rtiInitiatedService");
std::string AttributeOwnershipAcquisitionNotification::attributeOwnershipAcquisitionNotificationStr("attributeOwnershipDivestitureNotification");

std::string AttributeOwnershipUnavailable::attributeStr("attribute");
std::string AttributeOwnershipUnavailable::attributesStr("attributes");
std::string AttributeOwnershipUnavailable::objectStr("object");
std::string AttributeOwnershipUnavailable::rtiInitiatedServiceStr("rtiInitiatedService");
std::string AttributeOwnershipUnavailable::attributeOwnershipUnavailableStr("attributeOwnershipUnavailable");

std::string RequestAttributeOwnershipRelease::attributeStr("attribute");
std::string RequestAttributeOwnershipRelease::attributesStr("attributes");
std::string RequestAttributeOwnershipRelease::objectStr("object");
std::string RequestAttributeOwnershipRelease::rtiInitiatedServiceStr("rtiInitiatedService");
std::string RequestAttributeOwnershipRelease::requestAttributeOwnershipReleaseStr("requestAttributeOwnershipRelease");
std::string RequestAttributeOwnershipRelease::tagStr("tag");

std::string ConfirmAttributeOwnershipAcquisitionCancellation::attributeStr("attribute");
std::string ConfirmAttributeOwnershipAcquisitionCancellation::attributesStr("attributes");
std::string ConfirmAttributeOwnershipAcquisitionCancellation::objectStr("object");
std::string ConfirmAttributeOwnershipAcquisitionCancellation::rtiInitiatedServiceStr("rtiInitiatedService");
std::string ConfirmAttributeOwnershipAcquisitionCancellation::confirmAttributeOwnershipAcquisitionCancellationStr("confirmAttributeOwnershipAcquisitionCancellation");

std::string InformAttributeOwnership::attributeStr("attribute");
std::string InformAttributeOwnership::informAttributeOwnershipStr("informAttributeOwnership");
std::string InformAttributeOwnership::objectStr("object");
std::string InformAttributeOwnership::ownerStr("owner");
std::string InformAttributeOwnership::rtiInitiatedServiceStr("rtiInitiatedService");

std::string AttributeIsNotOwned::attributeIsNotOwnedStr("attributeIsNotOwned");
std::string AttributeIsNotOwned::attributeStr("attribute");
std::string AttributeIsNotOwned::objectStr("object");
std::string AttributeIsNotOwned::rtiInitiatedServiceStr("rtiInitiatedService");

std::string AttributeOwnedByRTI::attributeOwnedByRTIStr("attributeOwnedByRTI");
std::string AttributeOwnedByRTI::attributeStr("attribute");
std::string AttributeOwnedByRTI::objectStr("object");
std::string AttributeOwnedByRTI::rtiInitiatedServiceStr("rtiInitiatedService");

//**********
//
RequestAttributeOwnershipAssumption::RequestAttributeOwnershipAssumption (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _offeredAttributes, const GeRtiFactory::UserSuppliedTag &theTag)
  : offeredAttributes (_offeredAttributes)
{
  client = _client;
  theObject = _theObject;
  tag = theTag;
};

GERTICO::JobStatus RequestAttributeOwnershipAssumption::execute()
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"RequestAttributeOwnershipAssumption::execute(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], offeredAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], tag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  client->requestAttributeOwnershipAssumption (theObject, offeredAttributes, tag);

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "RequestAttributeOwnershipAssumption::execute", "leave");
                            }
                           #endif

  return GERTICO::done;
};

GERTICO::JobStatus RequestAttributeOwnershipAssumption::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  CORBA::ULong i;
  CORBA::ULong length;
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];
  char *cPtr = NULL;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(requestAttributeOwnershipAssumptionStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = offeredAttributes.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", offeredAttributes[i]);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  XMLString::transcode(tagStr.c_str(), tempStr, 99);
  GERTICO::Mapper::mapUserSuppliedTag(&cPtr, tag);
  XMLString::transcode(cPtr, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);
  delete cPtr;
  cPtr = NULL;

  return GERTICO::done;
}

//**********
//
RequestDivestitureConfirmation::RequestDivestitureConfirmation (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _releasedAttributes)
  : releasedAttributes (_releasedAttributes)
{
  client = _client;
  theObject = _theObject;
};

GERTICO::JobStatus RequestDivestitureConfirmation::execute()
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"RequestDivestitureConfirmation::execute(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], releasedAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  client->requestDivestitureConfirmation (theObject, releasedAttributes);

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "RequestDivestitureConfirmation::execute", "leave");
                            }
                           #endif

  return GERTICO::done;
};

GERTICO::JobStatus RequestDivestitureConfirmation::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
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

  XMLString::transcode(requestDivestitureConfirmationStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = releasedAttributes.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", releasedAttributes[i]);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}

//**********
//
AttributeOwnershipDivestitureNotification::AttributeOwnershipDivestitureNotification (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _releasedAttributes)
  : releasedAttributes (_releasedAttributes)
{
  client = _client;
  theObject = _theObject;
};

GERTICO::JobStatus AttributeOwnershipDivestitureNotification::execute()
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"AttributeOwnershipDivestitureNotification::execute(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], releasedAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  client->attributeOwnershipDivestitureNotification (theObject, releasedAttributes);

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "AttributeOwnershipDivestitureNotification::execute", "leave");
                            }
                           #endif

  return GERTICO::done;
};

GERTICO::JobStatus AttributeOwnershipDivestitureNotification::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
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

  XMLString::transcode(attributeOwnershipDivestitureNotificationStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = releasedAttributes.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", releasedAttributes[i]);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}

//**********
//
AttributeOwnershipAcquisitionNotification::AttributeOwnershipAcquisitionNotification (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _securedAttributes, const GeRtiFactory::UserSuppliedTag &theTag)
  : securedAttributes (_securedAttributes)
{
  client = _client;
  theObject = _theObject;
  tag = theTag;
};

GERTICO::JobStatus AttributeOwnershipAcquisitionNotification::execute()
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"AttributeOwnershipAcquisitionNotification::execute(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], securedAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], tag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  client->attributeOwnershipAcquisitionNotification(theObject, securedAttributes, tag);

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "AttributeOwnershipDivestitureNotification::execute", "leave");
                            }
                           #endif

  return GERTICO::done;
};

GERTICO::JobStatus AttributeOwnershipAcquisitionNotification::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
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

  XMLString::transcode(attributeOwnershipAcquisitionNotificationStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = securedAttributes.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", securedAttributes[i]);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}

//**********
//
AttributeOwnershipUnavailable::AttributeOwnershipUnavailable (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _theAttributes)
  : theAttributes (_theAttributes)
{
  client = _client;
  theObject = _theObject;
};

GERTICO::JobStatus AttributeOwnershipUnavailable::execute()
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"AttributeOwnershipUnavailable::execute(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  client->attributeOwnershipUnavailable (theObject, theAttributes);

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "AttributeOwnershipUnavailable::execute", "leave");
                            }
                           #endif

  return GERTICO::done;
};

GERTICO::JobStatus AttributeOwnershipUnavailable::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
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

  XMLString::transcode(attributeOwnershipUnavailableStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = theAttributes.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", theAttributes[i]);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}

//**********
//
RequestAttributeOwnershipRelease::RequestAttributeOwnershipRelease (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _candidateAttributes, const GeRtiFactory::UserSuppliedTag &theTag)
  : candidateAttributes (_candidateAttributes)
{
  client = _client;
  theObject = _theObject;
  tag = theTag;
};

GERTICO::JobStatus RequestAttributeOwnershipRelease::execute()
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"RequestAttributeOwnershipRelease::execute(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], candidateAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], tag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  client->requestAttributeOwnershipRelease (theObject, candidateAttributes, tag);

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "RequestAttributeOwnershipRelease::execute", "leave");
                            }
                           #endif

  return GERTICO::done;
};

GERTICO::JobStatus RequestAttributeOwnershipRelease::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  CORBA::ULong i;
  CORBA::ULong length;
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  DOMElement* elemLevel2;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];
  char *cPtr = NULL;

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(requestAttributeOwnershipReleaseStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = candidateAttributes.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", candidateAttributes[i]);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  XMLString::transcode(tagStr.c_str(), tempStr, 99);
  GERTICO::Mapper::mapUserSuppliedTag(&cPtr, tag);
  XMLString::transcode(cPtr, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);
  delete cPtr;
  cPtr = NULL;

  return GERTICO::done;
}

//**********
//
ConfirmAttributeOwnershipAcquisitionCancellation::ConfirmAttributeOwnershipAcquisitionCancellation (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _theAttributes)
  : theAttributes (_theAttributes)
{
  client = _client;
  theObject = _theObject;
};

GERTICO::JobStatus ConfirmAttributeOwnershipAcquisitionCancellation::execute()
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"ConfirmAttributeOwnershipAcquisitionCancellation::execute(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  client->confirmAttributeOwnershipAcquisitionCancellation (theObject, theAttributes);

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "ConfirmAttributeOwnershipAcquisitionCancellation::execute", "leave");
                            }
                           #endif

  return GERTICO::done;
};

GERTICO::JobStatus ConfirmAttributeOwnershipAcquisitionCancellation::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
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

  XMLString::transcode(confirmAttributeOwnershipAcquisitionCancellationStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributesStr.c_str(), tempStr, 99);
  elemLevel2 = theDOMDocument.createElement(tempStr);
  elemLevel1->appendChild(elemLevel2);

  length = theAttributes.length();
  for (i = 0; i < length; i++)
  {
    XMLString::transcode(attributeStr.c_str(), tempStr, 99);
    sprintf(buf, "%lu", theAttributes[i]);
    XMLString::transcode(buf, tempStr1, 99);
    elemLevel2->setAttribute(tempStr, tempStr1);
  }

  return GERTICO::done;
}

//**********
//
InformAttributeOwnership::InformAttributeOwnership (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, GeRtiFactory::GeRtiHandle _theAttribute, GeRtiFactory::GeRtiHandle _theOwner)
{
  client = _client;
  theObject = _theObject;
  theAttribute = _theAttribute;
  theOwner = _theOwner;
};

GERTICO::JobStatus InformAttributeOwnership::execute()
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;
                              unsigned long ul1;
                              unsigned long ul2;

                              ul = theObject;
                              ul1 = theAttribute;
                              ul2 = theOwner;
                              sprintf(galMsg,"InformAttributeOwnership::execute(object=%lu,attribute=%lu,owner=%lu) enter", ul, ul1, ul2);
                              E1mEnd(GeRti_OWM_d, galMsg);
                            }
                           #endif

  client->informAttributeOwnership (theObject, theAttribute, theOwner);

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "InformAttributeOwnership::execute", "leave");
                            }
                           #endif

  return GERTICO::done;
};

GERTICO::JobStatus InformAttributeOwnership::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(informAttributeOwnershipStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributeStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theAttribute);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(ownerStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theOwner);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

//**********
//
AttributeIsNotOwned::AttributeIsNotOwned (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, GeRtiFactory::GeRtiHandle _theAttribute)
{
  client = _client;
  theObject = _theObject;
  theAttribute = _theAttribute;
};

GERTICO::JobStatus AttributeIsNotOwned::execute()
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;
                              unsigned long ul1;

                              ul = theObject;
                              ul1 = theAttribute;
                              sprintf(galMsg,"AttributeIsNotOwned::execute(object=%lu,attribute=%lu) enter", ul, ul1);
                              E1mEnd(GeRti_OWM_d, galMsg);
                            }
                           #endif

  client->attributeIsNotOwned (theObject, theAttribute);

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "AttributeIsNotOwned::execute", "leave");
                            }
                           #endif

  return GERTICO::done;
};

GERTICO::JobStatus AttributeIsNotOwned::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(attributeIsNotOwnedStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributeStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theAttribute);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}

//**********
//
AttributeOwnedByRTI::AttributeOwnedByRTI (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, GeRtiFactory::GeRtiHandle _theAttribute)
{
  client = _client;
  theObject = _theObject;
  theAttribute = _theAttribute;
};

GERTICO::JobStatus AttributeOwnedByRTI::execute()
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;
                              unsigned long ul1;

                              ul = theObject;
                              ul1 = theAttribute;
                              sprintf(galMsg,"AttributeOwnedByRTI::execute(object=%lu,attribute=%lu) enter", ul, ul1);
                              E1mEnd(GeRti_OWM_d, galMsg);
                            }
                           #endif

  client->attributeOwnedByRTI (theObject, theAttribute);

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "AttributeOwnedByRTI::execute", "leave");
                            }
                           #endif

  return GERTICO::done;
};

GERTICO::JobStatus AttributeOwnedByRTI::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  DOMElement* elemLevel0;
  DOMElement* elemLevel1;
  XMLCh tempStr[100];
  XMLCh tempStr1[100];
  char buf[100];

  XMLString::transcode(rtiInitiatedServiceStr.c_str(), tempStr, 99);
  elemLevel0 = theDOMDocument.createElement(tempStr);
  theDOMElement.appendChild(elemLevel0);

  XMLString::transcode(attributeOwnedByRTIStr.c_str(), tempStr, 99);
  elemLevel1 = theDOMDocument.createElement(tempStr);
  elemLevel0->appendChild(elemLevel1);

  XMLString::transcode(objectStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theObject);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  XMLString::transcode(attributeStr.c_str(), tempStr, 99);
  sprintf(buf, "%lu", theAttribute);
  XMLString::transcode(buf, tempStr1, 99);
  elemLevel1->setAttribute(tempStr, tempStr1);

  return GERTICO::done;
}







//******************************************************************************

LrcOwnershipClient::LrcOwnershipClient () 
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void LrcOwnershipClient::setJobHolder(GERTICO::JobHolder* jh)
{
  // this
  aJobHolder = jh;
}

// ---------------------------------------------------------------------------
// 7.4
// IEEE
// ---------------------------------------------------------------------------
void LrcOwnershipClient::requestAttributeOwnershipAssumption (
          GeRtiFactory::GeRtiHandle        theObject,
    const GeRtiFactory::Handles& offeredAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::FederateInternalError) 
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"LrcOwnershipClient::requestAttributeOwnershipAssumption(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], offeredAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], theTag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  aJobHolder->add (new RequestAttributeOwnershipAssumption (client, theObject, offeredAttributes, theTag));

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "LrcOwnershipClient::requestAttributeOwnershipAssumption", "leave");
                            }
                           #endif
}  
  
void LrcOwnershipClient::requestDivestitureConfirmation (
          GeRtiFactory::GeRtiHandle        theObject,          // supplied C1
    const GeRtiFactory::Handles& releasedAttributes) // supplied C4
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::AttributeDivestitureWasNotRequested,
    GeRtiFactory::FederateInternalError) 
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"LrcOwnershipClient::requestAttributeOwnershipAssumption(object=%lu) enter", ul);
                              E1mEnd(GeRti_OWM_d, galMsg);
                            }
                           #endif

  aJobHolder->add (new RequestDivestitureConfirmation (client, theObject, releasedAttributes));

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "LrcOwnershipClient::requestDivestitureConfirmation", "leave");
                            }
                           #endif
}  
  
// 7.5
// IEEE
void LrcOwnershipClient::attributeOwnershipDivestitureNotification (
          GeRtiFactory::GeRtiHandle        theObject,          // supplied C1
    const GeRtiFactory::Handles& releasedAttributes) // supplied C4
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::AttributeDivestitureWasNotRequested,
    GeRtiFactory::FederateInternalError) 
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"LrcOwnershipClient::attributeOwnershipDivestitureNotification(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], releasedAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  aJobHolder->add (new AttributeOwnershipDivestitureNotification (client, theObject, releasedAttributes));

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "LrcOwnershipClient::attributeOwnershipDivestitureNotification", "leave");
                            }
                           #endif
}  
  
// 7.6
void LrcOwnershipClient::attributeOwnershipAcquisitionNotification (
    const GeRtiFactory::GeRtiHandle &theObject,
    const GeRtiFactory::Handles& securedAttributes,
    const GeRtiFactory::UserSuppliedTag & theTag)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeAcquisitionWasNotRequested,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::FederateInternalError) 
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"LrcOwnershipClient::attributeOwnershipAcquisitionNotification(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], securedAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], theTag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  aJobHolder->add(new AttributeOwnershipAcquisitionNotification(client, theObject, securedAttributes, theTag));

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "LrcOwnershipClient::attributeOwnershipAcquisitionNotification", "leave");
                            }
                           #endif
}  
  
// 7.9
// IEEE
void LrcOwnershipClient::attributeOwnershipUnavailable (
          GeRtiFactory::GeRtiHandle        theObject,         // supplied C1
    const GeRtiFactory::Handles& theAttributes) // supplied C4
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeAcquisitionWasNotRequested,
    GeRtiFactory::FederateInternalError) 
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"LrcOwnershipClient::attributeOwnershipUnavailable(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  aJobHolder->add (new AttributeOwnershipUnavailable (client, theObject, theAttributes));

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "LrcOwnershipClient::attributeOwnershipUnavailable", "leave");
                            }
                           #endif
}  
  
// 7.10
// IEEE
void LrcOwnershipClient::requestAttributeOwnershipRelease (
          GeRtiFactory::GeRtiHandle        theObject,
    const GeRtiFactory::Handles& candidateAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag)
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateInternalError) 
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"LrcOwnershipClient::requestAttributeOwnershipRelease(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], candidateAttributes);
                              GERTICO::Mapper::printUserSuppliedTag(",tag=", &galMsg[strlen(galMsg)], theTag);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  aJobHolder->add (new RequestAttributeOwnershipRelease (client, theObject, candidateAttributes, theTag));

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "LrcOwnershipClient::requestAttributeOwnershipRelease", "leave");
                            }
                           #endif
}  
  
// 7.14
// IEEE
void LrcOwnershipClient::confirmAttributeOwnershipAcquisitionCancellation (
          GeRtiFactory::GeRtiHandle        theObject,         // supplied C1
    const GeRtiFactory::Handles& theAttributes) // supplied C4
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeAcquisitionWasNotCanceled,
    GeRtiFactory::FederateInternalError) 
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;

                              ul = theObject;
                              sprintf(galMsg,"LrcOwnershipClient::confirmAttributeOwnershipAcquisitionCancellation(object=%lu", ul);
                              GERTICO::Mapper::printGeRtiFactoryHandles(",attributes=", &galMsg[strlen(galMsg)], theAttributes);
                              strcat(galMsg, ") enter");
                              E1(GeRti_OWM_d, galMsg);
                            }
                           #endif

  aJobHolder->add (new ConfirmAttributeOwnershipAcquisitionCancellation (client, theObject, theAttributes));

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "LrcOwnershipClient::confirmAttributeOwnershipAcquisitionCancellation", "leave");
                            }
                           #endif
}  
  
// 7.16
// IEEE
void LrcOwnershipClient::informAttributeOwnership (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute, // supplied C1
    GeRtiFactory::GeRtiHandle  theOwner)     // supplied C1
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::FederateInternalError) 
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;
                              unsigned long ul1;
                              unsigned long ul2;

                              ul = theObject;
                              ul1 = theAttribute;
                              ul2 = theOwner;
                              sprintf(galMsg,"LrcOwnershipClient::informAttributeOwnership(object=%lu,attribute=%lu,owner=%lu) enter", ul, ul1, ul2);
                              E1mEnd(GeRti_OWM_d, galMsg);
                            }
                           #endif

  aJobHolder->add (new InformAttributeOwnership (client, theObject, theAttribute, theOwner));

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "LrcOwnershipClient::informAttributeOwnership", "leave");
                            }
                           #endif
}  
  
void LrcOwnershipClient::attributeIsNotOwned (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute) // supplied C1
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::FederateInternalError) 
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;
                              unsigned long ul1;

                              ul = theObject;
                              ul1 = theAttribute;
                              sprintf(galMsg,"LrcOwnershipClient::attributeIsNotOwned(object=%lu,attribute=%lu) enter", ul, ul1);
                              E1mEnd(GeRti_OWM_d, galMsg);
                            }
                           #endif

  aJobHolder->add (new AttributeIsNotOwned (client, theObject, theAttribute));

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "LrcOwnershipClient::attributeIsNotOwned", "leave");
                            }
                           #endif
}  
  
void LrcOwnershipClient::attributeOwnedByRTI (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute) // supplied C1
throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::FederateInternalError) 
{
                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              char galMsg[512];
                              unsigned long ul;
                              unsigned long ul1;

                              ul = theObject;
                              ul1 = theAttribute;
                              sprintf(galMsg,"LrcOwnershipClient::attributeOwnedByRTI(object=%lu,attribute=%lu) enter", ul, ul1);
                              E1mEnd(GeRti_OWM_d, galMsg);
                            }
                           #endif

  aJobHolder->add (new AttributeOwnedByRTI (client, theObject, theAttribute));

                           #ifdef GalDebug
                            E1mBegin(GeRti_OWM_d)
                            {
                              E2(GeRti_OWM_d, "LrcOwnershipClient::attributeOwnedByRTI", "leave");
                            }
                           #endif
}  
  
