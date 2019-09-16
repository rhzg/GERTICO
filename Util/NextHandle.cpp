/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: NextHandle.cpp,v $
Revision 1.6  2009/02/03 09:05:31  mul
Changes to make join federation more robust.

Revision 1.5  2006/05/11 10:05:29  hzg
start handle ids at 10

Revision 1.4  2004/05/10 07:46:40  mul
Changes due to integrating object management with ownership.

Revision 1.3  2004/03/17 12:56:10  mul
Remove iostream.

Revision 1.2  2003/04/30 15:30:35  hzg
SuSE 8.1 port

Revision 1.1  2002/09/10 14:04:11  mul
New util module extracted from GERTICO/GeRti and GERTICO/GeRtiTime

Revision 1.3  2002/07/16 08:57:19  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen


**
*******************************************************************************/


#include "NextHandle.h"

GERTICO::NextHandle::NextHandle ()
{
  handle = 10;
}

GERTICO::NextHandle::~NextHandle ()
{
}

unsigned long GERTICO::NextHandle::nextHandle ()
{
  pm.acquire();
  handle += 1;
  pm.release();

  return handle;
}
