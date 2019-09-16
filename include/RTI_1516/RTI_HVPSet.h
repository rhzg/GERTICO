/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_HVPSet.h,v $
Revision 1.1  2007/09/06 09:34:57  mul
Changes for ieee1516.

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#ifndef HVPSet_HEADER
#define HVPSet_HEADER
 
#include <vector>

#include <RTI/RTIambassadorFactory.h>
#include "RTI.hh"
#include "baseTypes.hh"
#include "RTItypes.hh"

namespace RTI_V1_3
{

class HandleValuePair
{
public:
  HandleValuePair
  (
    const RTI_V1_3::Handle h,
    const char* buff,
    const RTI_V1_3::ULong valueLength
  );
  ~HandleValuePair ();

  RTI_V1_3::Handle handle;
  RTI_V1_3::ULong valueLength;
  char *value;
};

}

#endif
