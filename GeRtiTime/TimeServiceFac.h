/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: TimeServiceFac.h,v $
Revision 1.5  2005/09/07 12:28:10  mul
Remove name service. Change name scoping.

Revision 1.4  2004/09/24 07:36:42  mul
Add namespace.

Revision 1.3  2003/07/15 14:30:33  mul
Changes for RTI::FedTime.

Revision 1.2  2002/07/16 08:57:21  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


// -*- C++ -*-
//
// $Id: TimeServiceFac.h,v 1.5 2005/09/07 12:28:10 mul Exp $

#ifndef TimeServiceFac_H_
#define TimeServiceFac_H_

#include "TimeService.h"

namespace GERTICO
{
class TimeServiceFac
{
public:
  virtual ~TimeServiceFac () { ; };
  virtual TimeService *createTimeService () = 0;
};
};

#endif /* TimeServiceFac_H_  */
