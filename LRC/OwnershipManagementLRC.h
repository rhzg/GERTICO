/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Log: OwnershipManagementLRC.h,v $
Revision 1.7  2009/09/03 07:15:49  mul
Use local cache to get attribute owned status.

Revision 1.6  2009/05/27 11:38:32  mul
Change data access for registered objects.

Revision 1.5  2009/03/23 13:46:28  mul
Integrate ownership into rti and fed ambassador.

Revision 1.4  2009/02/16 15:10:27  mul
Changes for integrating ownership.

Revision 1.3  2007/09/25 08:29:47  mul
Changes for ddm.

Revision 1.2  2007/09/06 06:39:54  mul
Changes for ieee1516.

Revision 1.1  2007/06/26 08:29:01  mul
Changes for ieee1516.


**
*******************************************************************************/

#ifndef OwnershipService_H
#define OwnershipService_H

#include <map>

#include "Util/GeRtiTypes.h"
#include "Util/GeRtiOrb.h"
#include "Util/RegisteredObject.h"

#include "idl/GeRtiFactoryC.h"

namespace GERTICO
{

//****************************************************
//
class OwnershipService
{
  GeRtiFactory::GeRtiAmbassador_var myServerVar;
  GeRtiFactory::GeRtiHandle myFedId;

  //OwnershipServiceClient* myServiceClient;

  // locally store information
  RegisteredObjectsHolder &registeredObjectsHolder;

public:
  OwnershipService(GeRtiFactory::GeRtiHandle const &fedId, RegisteredObjectsHolder &theRegisteredObjectsHolder, GeRtiFactory::GeRtiAmbassador_ptr theOwnershipMasterPtr);
  virtual ~OwnershipService(void);


  // missing IEEE
  // - confirmDivestiture
  // - attributeOwnershipDivestitureIfWanted


  // 7.2
  // IEEE
  void unconditionalAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle   theObject,
    GeRtiFactory::Handles const & theAttributes)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::AttributeNotOwned,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 7.3
  // IEEE
  void negotiatedAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle   theObject,
    GeRtiFactory::Handles const & theAttributes,
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
    GeRtiFactory::RTIinternalError);

  // 7.7
  // IEEE
  void attributeOwnershipAcquisition (
    GeRtiFactory::GeRtiHandle   theObject,
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
    GeRtiFactory::RTIinternalError);

  // 7.8
  // IEEE
  void attributeOwnershipAcquisitionIfAvailable (
    GeRtiFactory::GeRtiHandle   theObject,
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
    GeRtiFactory::RTIinternalError);

  void attributeOwnershipDivestitureIfWanted(
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
    GeRtiFactory::RTIinternalError);

  // 7.11
  GeRtiFactory::Handles*
  confirmDivestiture (
    GeRtiFactory::GeRtiHandle   theObject,
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
    GeRtiFactory::RTIinternalError);

  // 7.12
  // IEEE
  void cancelNegotiatedAttributeOwnershipDivestiture (
    GeRtiFactory::GeRtiHandle   theObject,
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
    GeRtiFactory::RTIinternalError);

  // 7.13
  // IEEE
  void cancelAttributeOwnershipAcquisition (
    GeRtiFactory::GeRtiHandle   theObject,
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
    GeRtiFactory::RTIinternalError);

  // 7.15
  // IEEE
  void queryAttributeOwnership (
    GeRtiFactory::GeRtiHandle theObject,
    GeRtiFactory::GeRtiHandle theAttribute)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);

  // 7.17
  // IEEE
  bool
  isAttributeOwnedByFederate (
    GeRtiFactory::GeRtiHandle theObject,
    GeRtiFactory::GeRtiHandle theAttribute)
  throw (
    GeRtiFactory::ObjectNotKnown,
    GeRtiFactory::AttributeNotDefined,
    GeRtiFactory::FederateNotExecutionMember,
    GeRtiFactory::ConcurrentAccessAttempted,
    GeRtiFactory::SaveInProgress,
    GeRtiFactory::RestoreInProgress,
    GeRtiFactory::RTIinternalError);


};
//
//****************************************************
};
#endif // OwnershipService_H
