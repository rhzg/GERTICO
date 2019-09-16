/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: hzg $
$Name $
$Log: RTI_AHSetFactory.cpp,v $
Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#include "RTI_AHSet.h"

RTI::AttributeHandleSet* RTI::AttributeHandleSetFactory::create
(
  RTI::ULong count
)
throw
(
  RTI::MemoryExhausted,
  RTI::ValueCountExceeded
)
{
  RTI::AttributeHandleSet *ret = new AHSet (count);

  return ret;
}
