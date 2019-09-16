/*********************************************************************************
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
**********************************************************************************

$Author: mul $
$Log: GeRtiOwnershipMasterI.h,v $
Revision 1.6  2009/09/23 08:00:21  mul
Remove mutex lock.

Revision 1.5  2009/06/12 12:58:10  mul
Use thread mutex.

Revision 1.4  2009/03/23 14:06:26  mul
Changes to integrate ownership into rti and fed ambassador.

Revision 1.3  2009/02/16 15:18:56  mul
Changes for integrating ownership.

Revision 1.2  2008/01/30 14:35:22  mul
Changes for ieee1516.

Revision 1.1  2007/09/25 08:36:55  mul
From Ownership directory.


**
*******************************************************************************/
//**

#ifndef GeRtiOwnershipMasterI_HEADER
#define GeRtiOwnershipMasterI_HEADER

#include "Util/GeRtiOrb.h"
#include "Util/RunTimeObjectDB.h"
#include "Util/DataModel.h"
#include "idl/GeRtiFactoryS.h"

#include "EventMarket/ObjectManagement.h"
#include "OwnershipWorkerThread.h"

namespace GERTICO
{

class GeRtiOwnershipMasterI
{
  OwnershipWorkerThread myWorkerThread;

public:
  GeRtiOwnershipMasterI(RunTimeObjectDB &theOwnershipInfo, GERTICO::ObjectManagement &theObjectManagement);
  virtual ~GeRtiOwnershipMasterI ();

  void setFederatesHolder(GERTICO::FederatesHolder* theFederatesHolder);

  void managerFederateAdjustModifyAttributeState(GeRtiFactory::GeRtiHandle const &theFederate, GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theAttribute, std::string &theAttributeState);

  void processUnpublishOwnershipCandidate(const GeRtiFactory::GeRtiHandle &theFederate, const GeRtiFactory::GeRtiHandle &theClass, GERTICO::HandleSet &theAttributes);

//***** HLA Spec *********************************

    virtual void unconditionalAttributeOwnershipDivestiture (
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
      );

    virtual void negotiatedAttributeOwnershipDivestiture (
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
      );

    virtual void attributeOwnershipAcquisition (
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
      );

    virtual void attributeOwnershipAcquisitionIfAvailable (
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
      );

    virtual ::GeRtiFactory::Handles * attributeOwnershipDivestitureIfWanted (
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
      );

    virtual ::GeRtiFactory::Handles * confirmDivestiture (
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
      );

    virtual void cancelNegotiatedAttributeOwnershipDivestiture (
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
      );

    virtual void cancelAttributeOwnershipAcquisition (
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
      );

    virtual void queryAttributeOwnership (
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
      );

    virtual CORBA::Boolean isAttributeOwnedByFederate (
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
      );


//************************************************


};

};
#endif // GeRtiOwnershipMasterI_HEADER
