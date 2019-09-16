/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Log: LrcOwnershipClientMapper.h,v $
Revision 1.6  2007/09/06 06:35:49  mul
Changes for ieee1516.

Revision 1.5  2007/06/26 08:30:28  mul
Changes for ieee1516.

Revision 1.4  2007/06/08 12:11:42  mul
Changes for ieee1516.

Revision 1.3  2005/09/07 12:36:27  mul
Change name scoping. Remove some calls to name service.

Revision 1.2  2003/05/28 07:37:21  mul
Use include paths starting in $GERTICO.

Revision 1.1  2002/11/06 15:06:24  hzg
Ownership included

 
**
*******************************************************************************/


#ifndef LrcOwnershipClientMapper_HEADER
#define LrcOwnershipClientMapper_HEADER

#include "idl/GeRtiFactoryS.h"

class LrcOwnershipClientMapper
{
public:
  virtual void requestAttributeOwnershipAssumption (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& offeredAttributes, const GeRtiFactory::UserSuppliedTag &theTag) = 0;
  virtual void requestDivestitureConfirmation (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& releasedAttributes) = 0;
  virtual void attributeOwnershipDivestitureNotification (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& releasedAttributes) = 0;
  virtual void attributeOwnershipAcquisitionNotification (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& securedAttributes, const GeRtiFactory::UserSuppliedTag & theTag) = 0;
  virtual void attributeOwnershipUnavailable (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& theAttributes) = 0;
  virtual void requestAttributeOwnershipRelease (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& candidateAttributes, const GeRtiFactory::UserSuppliedTag &theTag) = 0;
  virtual void confirmAttributeOwnershipAcquisitionCancellation (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& theAttributes) = 0;
  virtual void informAttributeOwnership (GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle theAttribute, GeRtiFactory::GeRtiHandle theOwner) = 0;
  virtual void attributeIsNotOwned (GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle theAttribute) = 0;
  virtual void attributeOwnedByRTI (GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle theAttribute) = 0;
  
};

#endif
