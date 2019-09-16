/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_HSetFactory.cpp,v $
Revision 1.1  2002/09/10 12:52:40  mul
Fix problems with file not found. Changes for linking fedtimeDouble.cpp.

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#include "RTI_HSet.h"

RTI::FederateHandleSet *RTI::FederateHandleSetFactory::create
(
  RTI::ULong count
)
throw
(
  RTI::MemoryExhausted,
  RTI::ValueCountExceeded
)
{
  RTI::FederateHandleSet *ret = new HSet ();

  return ret;
}
