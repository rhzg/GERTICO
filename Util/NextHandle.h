/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: NextHandle.h,v $
Revision 1.4  2009/06/12 12:09:15  mul
Use thread mutex.

Revision 1.3  2009/02/03 09:05:31  mul
Changes to make join federation more robust.

Revision 1.2  2004/05/10 07:46:40  mul
Changes due to integrating object management with ownership.

Revision 1.1  2002/09/10 14:04:11  mul
New util module extracted from GERTICO/GeRti and GERTICO/GeRtiTime

Revision 1.2  2002/07/16 08:57:19  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen


**
*******************************************************************************/


#ifndef NextHandle_H_
#define NextHandle_H_

#include "ace/Synch.h"

namespace GERTICO
{
  class NextHandle
  {
    ACE_Thread_Mutex pm;
    unsigned long handle;

  public:
    NextHandle ();
    virtual ~NextHandle ();

    unsigned long nextHandle ();
  };
};

#endif /* NextHandle_H_  */
