/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**
 
$Author: mul $
$Log: OwnershipServiceClient.h,v $
Revision 1.1  2007/09/25 08:26:16  mul
From Ownership directory.

 
**
*******************************************************************************/
 
#ifndef OwnershipServiceClient_H
#define OwnershipServiceClient_H
 
#include "idl/GeRtiFactoryC.h"


namespace GERTICO
{

class OwnershipServiceClient
{
public:

  // missing IEEE
  // - confirmDivestiture
  
  
  
  // 7.4
  // IEEE
  virtual void requestAttributeOwnershipAssumption (
          GeRtiFactory::GeRtiHandle        theObject,         // supplied C1
    const GeRtiFactory::Handles& offeredAttributes, // supplied C4
    const GeRtiFactory::UserSuppliedTag &theTag)            // supplied C4
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::FederateInternalError) = 0;
  
  virtual void requestDivestitureConfirmation (
          GeRtiFactory::GeRtiHandle        theObject,          // supplied C1
    const GeRtiFactory::Handles& releasedAttributes) // supplied C4
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::AttributeDivestitureWasNotRequested,
    GeRtiFactory::FederateInternalError) = 0;
  
  // 7.5
  // IEEE
  virtual void attributeOwnershipDivestitureNotification (
          GeRtiFactory::GeRtiHandle        theObject,          // supplied C1
    const GeRtiFactory::Handles& releasedAttributes) // supplied C4
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::AttributeDivestitureWasNotRequested,
    GeRtiFactory::FederateInternalError) = 0;
  
  // 7.6
  virtual void attributeOwnershipAcquisitionNotification (
    const GeRtiFactory::GeRtiHandle &theObject,
    const GeRtiFactory::Handles& securedAttributes,
    const GeRtiFactory::UserSuppliedTag & theTag)
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeAcquisitionWasNotRequested,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeNotPublished,
    GeRtiFactory::FederateInternalError) = 0;
  
  // 7.9
  // IEEE
  virtual void attributeOwnershipUnavailable (
          GeRtiFactory::GeRtiHandle        theObject,         // supplied C1
    const GeRtiFactory::Handles& theAttributes) // supplied C4
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeAcquisitionWasNotRequested,
    GeRtiFactory::FederateInternalError) = 0;
  
  // 7.10
  // IEEE
  virtual void requestAttributeOwnershipRelease (
          GeRtiFactory::GeRtiHandle        theObject,           // supplied C1
    const GeRtiFactory::Handles& candidateAttributes, // supplied C4
    const GeRtiFactory::UserSuppliedTag &theTag)              // supplied C4
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateInternalError) = 0;
  
  // 7.14
  // IEEE
  virtual void confirmAttributeOwnershipAcquisitionCancellation (
          GeRtiFactory::GeRtiHandle        theObject,         // supplied C1
    const GeRtiFactory::Handles& theAttributes) // supplied C4
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeAlreadyOwned,
    GeRtiFactory::AttributeAcquisitionWasNotCanceled,
    GeRtiFactory::FederateInternalError) = 0;
  
  // 7.16
  // IEEE
  virtual void informAttributeOwnership (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute, // supplied C1
    GeRtiFactory::GeRtiHandle  theOwner)     // supplied C1
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::FederateInternalError) = 0;
  
  virtual void attributeIsNotOwned (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute) // supplied C1
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::FederateInternalError) = 0;
  
  virtual void attributeOwnedByRTI (
    GeRtiFactory::GeRtiHandle    theObject,    // supplied C1
    GeRtiFactory::GeRtiHandle theAttribute) // supplied C1
  throw (
    CORBA::SystemException,
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotKnown,
    GeRtiFactory::FederateInternalError) = 0;
  
};
};

#endif // OwnershipServiceClient_H
