/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: hzg $
$Name $
$Log: RTI_HVPSet.h,v $
Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#ifndef HVPSet_HEADER
#define HVPSet_HEADER
 
#include <vector>
#include "RTI.hh"

class HandleValuePair
{
public:
  HandleValuePair
  (
    const RTI::Handle h,
    const char* buff,
    const RTI::ULong valueLength
  );
  ~HandleValuePair ();

  RTI::Handle handle;
  RTI::ULong valueLength;
  char *value;
};

#endif
