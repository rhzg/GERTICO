/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Log: HlaOwnershipClientMapper.h,v $
Revision 1.8  2007/09/05 15:45:31  mul
Changes for ieee1516.

Revision 1.7  2007/06/25 15:12:08  mul
Changes for ieee1516.

Revision 1.6  2007/06/08 12:06:02  mul
Changes for ieee1516.

Revision 1.5  2007/05/15 13:19:25  mul
Changes for combined 1.3 and 1516 logic.

Revision 1.4  2005/05/03 15:19:26  mul
Add name scoping.

Revision 1.3  2003/08/07 12:06:34  mul
Make mapper a static/global function.

Revision 1.2  2003/04/29 06:26:13  hzg
Portierung auf Windows

Revision 1.1  2002/11/06 15:06:31  hzg
Ownership included


 
**
*******************************************************************************/


#ifndef HlaOwnershipClientMapper_HEADER
#define HlaOwnershipClientMapper_HEADER

#include <map>
#include <string>
#include "LRC/LrcOwnershipClientMapper.h"
#include "include/RTI_1.3/RTI.hh"

class HlaOwnershipClientMapper : public LrcOwnershipClientMapper
{
  RTI::FederateAmbassador *fedAmb;
  RTI::AttributeHandleSet *helperAttributes;

public:
  HlaOwnershipClientMapper (RTI::FederateAmbassador *amb);
  virtual ~HlaOwnershipClientMapper();

  virtual void requestAttributeOwnershipAssumption (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& offeredAttributes, const GeRtiFactory::UserSuppliedTag &theTag);
  virtual void requestDivestitureConfirmation (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& releasedAttributes);
  virtual void attributeOwnershipDivestitureNotification (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& releasedAttributes);
  virtual void attributeOwnershipAcquisitionNotification (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& securedAttributes, const GeRtiFactory::UserSuppliedTag &theTag);
  virtual void attributeOwnershipUnavailable (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& theAttributes);
  virtual void requestAttributeOwnershipRelease (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& candidateAttributes, const GeRtiFactory::UserSuppliedTag &theTag);
  virtual void confirmAttributeOwnershipAcquisitionCancellation (GeRtiFactory::GeRtiHandle theObject, const GeRtiFactory::Handles& theAttributes);
  virtual void informAttributeOwnership (GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle theAttribute, GeRtiFactory::GeRtiHandle theOwner);
  virtual void attributeIsNotOwned (GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle theAttribute);
  virtual void attributeOwnedByRTI (GeRtiFactory::GeRtiHandle theObject, GeRtiFactory::GeRtiHandle theAttribute);
};

#endif
