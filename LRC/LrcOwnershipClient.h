/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**
 
$Author: mul $
$Log: LrcOwnershipClient.h,v $
Revision 1.14  2007/09/25 08:30:53  mul
Changes for ddm.

Revision 1.13  2007/09/06 06:35:24  mul
Changes for ieee1516.

Revision 1.12  2007/06/26 08:30:58  mul
Changes for ieee1516.

Revision 1.11  2007/06/08 12:12:09  mul
Changes for ieee1516.

Revision 1.10  2006/05/23 11:36:59  mul
Remove extra aoa/aoaif logic.

Revision 1.9  2006/04/21 07:18:44  mul
Fix aoa and aoaia logic.

Revision 1.8  2005/09/20 14:49:50  mul
Fix a memory leak.

Revision 1.7  2005/05/04 11:01:19  mul
Add save logic.

Revision 1.6  2005/02/11 14:49:30  mul
Add scoping.

Revision 1.5  2003/05/28 07:37:21  mul
Use include paths starting in $GERTICO.

Revision 1.4  2003/03/21 09:55:12  mul
Add scoping to exceptions.

Revision 1.3  2002/11/19 16:01:44  hzg
Static data model used in OMT_XML

Revision 1.2  2002/11/18 14:18:30  hzg
OwnershipWorker moved to Util/JobHolder

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
 
#ifndef LrcOwnershipClient_H
#define LrcOwnershipClient_H
 
#include "idl/GeRtiFactoryC.h"
#include "LRC/OwnershipServiceClient.h"
#include "Util/GeRtiTypes.h"
#include "Util/JobHolder.h" 
#include "LrcOwnershipClientMapper.h"

//**********
//
class RequestAttributeOwnershipAssumption : public GERTICO::Job
{
  LrcOwnershipClientMapper* client;
  GeRtiFactory::GeRtiHandle theObject;
  GeRtiFactory::Handles offeredAttributes;
  GeRtiFactory::UserSuppliedTag tag;

  // Save/restore.
  static std::string attributeStr;
  static std::string attributesStr;
  static std::string objectStr;
  static std::string rtiInitiatedServiceStr;
  static std::string requestAttributeOwnershipAssumptionStr;
  static std::string tagStr;

public:
  RequestAttributeOwnershipAssumption (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _offeredAttributes, const GeRtiFactory::UserSuppliedTag &theTag);
  virtual GERTICO::JobStatus execute();
  virtual GERTICO::JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};

//**********
//
class RequestDivestitureConfirmation : public GERTICO::Job
{
  LrcOwnershipClientMapper* client;
  GeRtiFactory::GeRtiHandle theObject;
  GeRtiFactory::Handles releasedAttributes;

  // Save/restore.
  static std::string requestDivestitureConfirmationStr;
  static std::string attributeStr;
  static std::string attributesStr;
  static std::string objectStr;
  static std::string rtiInitiatedServiceStr;

public:
  RequestDivestitureConfirmation (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _releasedAttributes);
  virtual GERTICO::JobStatus execute();
  virtual GERTICO::JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};

//**********
//
class AttributeOwnershipDivestitureNotification : public GERTICO::Job
{
  LrcOwnershipClientMapper* client;
  GeRtiFactory::GeRtiHandle theObject;
  GeRtiFactory::Handles releasedAttributes;

  // Save/restore.
  static std::string attributeOwnershipDivestitureNotificationStr;
  static std::string attributeStr;
  static std::string attributesStr;
  static std::string objectStr;
  static std::string rtiInitiatedServiceStr;

public:
  AttributeOwnershipDivestitureNotification (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _releasedAttributes);
  virtual GERTICO::JobStatus execute();
  virtual GERTICO::JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};

//**********
//
class AttributeOwnershipAcquisitionNotification : public GERTICO::Job
{
  LrcOwnershipClientMapper* client;
  GeRtiFactory::GeRtiHandle theObject;
  GeRtiFactory::Handles securedAttributes;
  GeRtiFactory::UserSuppliedTag tag;

  // Save/restore.
  static std::string attributeOwnershipAcquisitionNotificationStr;
  static std::string attributeStr;
  static std::string attributesStr;
  static std::string objectStr;
  static std::string rtiInitiatedServiceStr;

public:
  AttributeOwnershipAcquisitionNotification (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _securedAttributes, const GeRtiFactory::UserSuppliedTag &theTag);
  virtual GERTICO::JobStatus execute();
  virtual GERTICO::JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};

//**********
//
class AttributeOwnershipUnavailable : public GERTICO::Job
{
  LrcOwnershipClientMapper* client;
  GeRtiFactory::GeRtiHandle theObject;
  GeRtiFactory::Handles theAttributes;

  // Save/restore.
  static std::string attributeOwnershipUnavailableStr;
  static std::string attributeStr;
  static std::string attributesStr;
  static std::string objectStr;
  static std::string rtiInitiatedServiceStr;

public:
  AttributeOwnershipUnavailable (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _theAttributes);
  virtual GERTICO::JobStatus execute();
  virtual GERTICO::JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};

//**********
//
class RequestAttributeOwnershipRelease : public GERTICO::Job
{
  LrcOwnershipClientMapper* client;
  GeRtiFactory::GeRtiHandle theObject;
  GeRtiFactory::Handles candidateAttributes;
  GeRtiFactory::UserSuppliedTag tag;

  // Save/restore.
  static std::string attributeStr;
  static std::string attributesStr;
  static std::string objectStr;
  static std::string rtiInitiatedServiceStr;
  static std::string requestAttributeOwnershipReleaseStr;
  static std::string tagStr;

public:
  RequestAttributeOwnershipRelease (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _candidateAttributes, const GeRtiFactory::UserSuppliedTag &theTag);
  virtual GERTICO::JobStatus execute();
  virtual GERTICO::JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};

//**********
//
class ConfirmAttributeOwnershipAcquisitionCancellation : public GERTICO::Job
{
  LrcOwnershipClientMapper* client;
  GeRtiFactory::GeRtiHandle theObject;
  GeRtiFactory::Handles theAttributes;

  // Save/restore.
  static std::string attributeStr;
  static std::string attributesStr;
  static std::string confirmAttributeOwnershipAcquisitionCancellationStr;
  static std::string objectStr;
  static std::string rtiInitiatedServiceStr;

public:
  ConfirmAttributeOwnershipAcquisitionCancellation (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, const GeRtiFactory::Handles& _theAttributes);
  virtual GERTICO::JobStatus execute();
  virtual GERTICO::JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};

//**********
//
class InformAttributeOwnership : public GERTICO::Job
{
  LrcOwnershipClientMapper* client;
  GeRtiFactory::GeRtiHandle theObject;
  GeRtiFactory::GeRtiHandle theAttribute;
  GeRtiFactory::GeRtiHandle theOwner;

  // Save/restore.
  static std::string attributeStr;
  static std::string informAttributeOwnershipStr;
  static std::string objectStr;
  static std::string ownerStr;
  static std::string rtiInitiatedServiceStr;

public:
  InformAttributeOwnership (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, GeRtiFactory::GeRtiHandle _theAttribute, GeRtiFactory::GeRtiHandle _theOwner);
  virtual GERTICO::JobStatus execute();
  virtual GERTICO::JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};

//**********
//
class AttributeIsNotOwned : public GERTICO::Job
{
  LrcOwnershipClientMapper* client;
  GeRtiFactory::GeRtiHandle theObject;
  GeRtiFactory::GeRtiHandle theAttribute;

  // Save/restore.
  static std::string attributeIsNotOwnedStr;
  static std::string attributeStr;
  static std::string objectStr;
  static std::string rtiInitiatedServiceStr;

public:
  AttributeIsNotOwned (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, GeRtiFactory::GeRtiHandle _theAttribute);
  virtual GERTICO::JobStatus execute();
  virtual GERTICO::JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};

//**********
//
class AttributeOwnedByRTI : public GERTICO::Job
{
  LrcOwnershipClientMapper* client;
  GeRtiFactory::GeRtiHandle theObject;
  GeRtiFactory::GeRtiHandle theAttribute;

  // Save/restore.
  static std::string attributeOwnedByRTIStr;
  static std::string attributeStr;
  static std::string objectStr;
  static std::string rtiInitiatedServiceStr;

public:
  AttributeOwnedByRTI (LrcOwnershipClientMapper* _client, GeRtiFactory::GeRtiHandle _theObject, GeRtiFactory::GeRtiHandle _theAttribute);
  virtual GERTICO::JobStatus execute();
  virtual GERTICO::JobStatus save(DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};










//******************************************************************************
//
class LrcOwnershipClient: public GERTICO::OwnershipServiceClient
{
  GERTICO::JobHolder* aJobHolder;
public:
  LrcOwnershipClientMapper* client;


  LrcOwnershipClient();
  virtual ~LrcOwnershipClient() {};

  void setJobHolder(GERTICO::JobHolder* jh);


  // missing IEEE
  // - confirmDivestiture
  
  // 7.4
  // IEEE
  virtual void requestAttributeOwnershipAssumption (
          GeRtiFactory::GeRtiHandle        theObject,
    const GeRtiFactory::Handles& offeredAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::FederateInternalError);
  
  virtual void requestDivestitureConfirmation (
          GeRtiFactory::GeRtiHandle        theObject,          // supplied C1
    const GeRtiFactory::Handles& releasedAttributes) // supplied C4
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::AttributeDivestitureWasNotRequested,
    GeRtiFactory::FederateInternalError);
  
  // 7.5
  // IEEE
  virtual void attributeOwnershipDivestitureNotification (
          GeRtiFactory::GeRtiHandle        theObject,          // supplied C1
    const GeRtiFactory::Handles& releasedAttributes) // supplied C4
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::AttributeDivestitureWasNotRequested,
    GeRtiFactory::FederateInternalError);
  
  // 7.6
  virtual void attributeOwnershipAcquisitionNotification (
    const GeRtiFactory::GeRtiHandle &theObject,
    const GeRtiFactory::Handles& securedAttributes,
    const GeRtiFactory::UserSuppliedTag & theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeAcquisitionWasNotRequested,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::FederateInternalError);
  
  // 7.9
  // IEEE
  virtual void attributeOwnershipUnavailable (
          GeRtiFactory::GeRtiHandle        theObject,         // supplied C1
    const GeRtiFactory::Handles& theAttributes) // supplied C4
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeAcquisitionWasNotRequested,
    GeRtiFactory::FederateInternalError);
  
  // 7.10
  // IEEE
  virtual void requestAttributeOwnershipRelease (
          GeRtiFactory::GeRtiHandle        theObject,
    const GeRtiFactory::Handles& candidateAttributes,
    const GeRtiFactory::UserSuppliedTag &theTag)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateInternalError);
  
  // 7.14
  // IEEE
  virtual void confirmAttributeOwnershipAcquisitionCancellation (
          GeRtiFactory::GeRtiHandle        theObject,         // supplied C1
    const GeRtiFactory::Handles& theAttributes) // supplied C4
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeAcquisitionWasNotCanceled,
    GeRtiFactory::FederateInternalError);
  
  // 7.16
  // IEEE
  virtual void informAttributeOwnership (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute, // supplied C1
    GeRtiFactory::GeRtiHandle  theOwner)     // supplied C1
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::FederateInternalError);
  
  virtual void attributeIsNotOwned (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute) // supplied C1
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::FederateInternalError);
  
  virtual void attributeOwnedByRTI (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute) // supplied C1
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::FederateInternalError);
  
};


#endif // LrcOwnershipClient_H
