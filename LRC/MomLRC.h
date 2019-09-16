/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: MomLRC.h,v $
Revision 1.4  2007/09/06 06:38:08  mul
Changes for ieee1516.

Revision 1.3  2006/08/01 11:37:17  mul
Changes for mom.

Revision 1.2  2006/04/19 15:04:50  mul
Changes for MOM.

Revision 1.1  2006/04/19 14:55:06  mul
New file.

 
**
*******************************************************************************/


// -*- C++ -*-
//
// $Id: MomLRC.h,v 1.4 2007/09/06 06:38:08 mul Exp $

#ifndef MomLRC_H_
#define MomLRC_H_

#include "string"

#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiTypes.h"

namespace GERTICO
{
  class MomLRC
  {
  public:
    //Destructor 
    virtual ~MomLRC(void) {};

    virtual void doMomRequest(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::HandleValues & data) = 0;
    virtual void getMomData(GeRtiFactory::GeRtiHandle theRequest, const GeRtiFactory::Handles & theAttributes, GeRtiFactory::HandleValues_out data) = 0;
  };
}
#endif /* MomLRC_H_  */
