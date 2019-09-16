/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: TimeServiceFacI.h,v $
Revision 1.10  2009/05/07 12:45:08  mul
Changes for removing token logic in time management.

Revision 1.9  2005/12/19 15:54:12  mul
Separate child poa from singleton.

Revision 1.8  2005/11/17 13:41:55  mul
Fix memory leaks.

Revision 1.7  2005/09/07 12:28:10  mul
Remove name service. Change name scoping.

Revision 1.6  2004/12/14 10:56:19  mul
Clean up.

Revision 1.5  2004/11/22 13:24:34  mul
Simplify time interface.

Revision 1.4  2004/09/24 07:36:16  mul
Add namespace.

Revision 1.3  2003/10/10 13:30:40  mul
New ORB init logic.

Revision 1.2  2002/07/16 08:57:21  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen


**
*******************************************************************************/


// -*- C++ -*-
//
// $Id: TimeServiceFacI.h,v 1.10 2009/05/07 12:45:08 mul Exp $

#ifndef TimeServiceFacI_H_
#define TimeServiceFacI_H_

#include "TimeServiceFac.h"
#include "TokenHolder.h"

namespace GERTICO
{
class TimeServiceFacI : virtual public TimeServiceFac
{
  ACE_thread_t tid1;
  TimeServiceClient &tsc;

public:
  TimeServiceFacI(TimeServiceClient &theTsc);
  virtual ~TimeServiceFacI ();

  TimeService *createTimeService ();
};
};

#endif /* TimeServiceFacI_H_  */
