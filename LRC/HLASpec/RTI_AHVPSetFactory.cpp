/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: hzg $
$Name $
$Log: RTI_AHVPSetFactory.cpp,v $
Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#include "RTI_AHVPSet.h"

RTI::AttributeHandleValuePairSet* RTI::AttributeSetFactory::create
(
  RTI::ULong count
)
throw
(
  RTI::MemoryExhausted,
  RTI::ValueCountExceeded,
  RTI::HandleValuePairMaximumExceeded
)
{
  RTI::AttributeHandleValuePairSet *ret = new AHVPSet (count);
  return ret;
}
