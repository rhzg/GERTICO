/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_HVPSet.cpp,v $
Revision 1.4  2010/05/17 07:56:24  mul
Minor change.

Revision 1.3  2002/07/26 13:40:00  hzg
Buffer dynamically allocated

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/

#include <string.h>
#include "RTI_AHVPSet.h"

HandleValuePair::HandleValuePair
(
  const RTI::Handle h,
  const char* buff,
  const RTI::ULong vLength
)
{
  handle = h;
  valueLength = vLength;
  value = new char[vLength];
  memcpy (value, buff, vLength);
}

HandleValuePair::~HandleValuePair ()
{
  delete[] value;
}
