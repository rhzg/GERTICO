/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Mom.h,v $
Revision 1.5  2007/09/06 09:13:12  mul
Changes for ieee1516.

Revision 1.4  2006/08/01 11:46:24  mul
Minor changes.

Revision 1.3  2006/04/19 14:52:52  mul
New file.

 
**
*******************************************************************************/


// -*- C++ -*-
//
// $Id: Mom.h,v 1.5 2007/09/06 09:13:12 mul Exp $

#ifndef Mom_H_
#define Mom_H_

#include "string"

#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiTypes.h"

namespace GERTICO
{
  class Mom
  {
  public:
    //Destructor 
    virtual ~Mom(void) {};

    virtual void doMomInteraction(GeRtiFactory::GeRtiEvent &theGeRtiEvent) = 0;
    virtual bool isMomClass(const GeRtiFactory::GeRtiHandle &theClass) = 0;
  };
}
#endif /* Mom_H_  */
