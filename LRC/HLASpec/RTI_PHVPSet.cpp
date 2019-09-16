/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_PHVPSet.cpp,v $
Revision 1.9  2010/05/17 07:56:03  mul
Minor change.

Revision 1.8  2007/01/22 12:37:09  mul
Fix access to and exception handling.

Revision 1.7  2006/12/18 10:10:57  mul
Test parameter values.

Revision 1.6  2005/02/11 14:49:53  mul
Add scoping.

Revision 1.5  2005/01/18 12:29:26  hzg
valueLength set

Revision 1.4  2003/08/26 14:55:21  mul
Fixed a memory leak.

Revision 1.3  2003/04/29 06:26:14  hzg
Portierung auf Windows

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#include <string.h>
#include "RTI_PHVPSet.h"

PHVPSet::PHVPSet (RTI::ULong l)
{
}

PHVPSet::~PHVPSet ()
{
  empty ();
}

RTI::ULong PHVPSet::size () const
{
  RTI::ULong ret = handleValuePairs.size ();

  return ret;
}
 
RTI::Handle PHVPSet::getHandle (RTI::ULong i) const
    throw (RTI::ArrayIndexOutOfBounds)
{
  RTI::ULong size = handleValuePairs.size();

  if (i < 0 || i > size - 1)
  {
    throw RTI::ArrayIndexOutOfBounds("");
  }

  RTI::ULong ret = (handleValuePairs[i])->handle;

  return ret;
}

RTI::ULong PHVPSet::getValueLength (RTI::ULong i) const
    throw (
      RTI::ArrayIndexOutOfBounds)
{
  unsigned long len = handleValuePairs.size ();

  if (i + 1 > len)
  {
    throw RTI::ArrayIndexOutOfBounds ("");
  }
  RTI::ULong ret = (handleValuePairs[i])->valueLength;
 
  return ret;
}

void PHVPSet::getValue (RTI::ULong i, char *buff, RTI::ULong &valueLength) const    throw (
      RTI::ArrayIndexOutOfBounds)
{
  unsigned long len = handleValuePairs.size ();

  if (i + 1 > len)
  {
    throw RTI::ArrayIndexOutOfBounds ("");
  }
  memcpy (buff, (handleValuePairs[i])->value, (handleValuePairs[i])->valueLength);
  valueLength = (handleValuePairs[i])->valueLength;
}

char *PHVPSet::getValuePointer (RTI::ULong i, RTI::ULong &valueLength) const
    throw (
      RTI::ArrayIndexOutOfBounds)
{
  char *ret = (handleValuePairs[i])->value;
  valueLength = (handleValuePairs[i])->valueLength;
 
  return ret;
}

RTI::TransportType PHVPSet::getTransportType (void) const
    throw (RTI::InvalidHandleValuePairSetContext)
{
  RTI::TransportType ret = 0;
 
  return ret;
}

RTI::OrderType PHVPSet::getOrderType (void) const
    throw (RTI::InvalidHandleValuePairSetContext)
{
  RTI::OrderType ret = 0;
 
  return ret;
}
 
RTI::Region *PHVPSet::getRegion (void) const
    throw (RTI::InvalidHandleValuePairSetContext)
{
  RTI::Region *ret = NULL;
 
  return ret;
}
 
void PHVPSet::add
(
  RTI::Handle h,
  const char* buff,
  RTI::ULong valueLength
)
throw
(
  RTI::ValueLengthExceeded,
  RTI::ValueCountExceeded
)
{
  HandleValuePair *newHandleValuePair = new HandleValuePair (h, buff, valueLength);
  handleValuePairs.push_back (newHandleValuePair);
}
 
// not guaranteed safe while iterating
void PHVPSet::remove
(
  RTI::Handle h
)
throw
(
  RTI::ArrayIndexOutOfBounds
)
{
  std::vector <HandleValuePair *>::iterator itHandle;

  for (itHandle = handleValuePairs.begin(); itHandle != handleValuePairs.end(); itHandle++)
  {
    if ((*itHandle)->handle != h)
    {
      continue;
    }
    handleValuePairs.erase(itHandle);
  }
}

void PHVPSet::moveFrom (const RTI::ParameterHandleValuePairSet& phvps, RTI::ULong &i)    throw (
      RTI::ValueCountExceeded,
      RTI::ArrayIndexOutOfBounds)
{
}
 
// Empty the Set.
void PHVPSet::empty ()
{
  HandleValuePair *curr;
  std::vector <HandleValuePair *>::iterator it;
 
  for (it = handleValuePairs.begin ();
       it != handleValuePairs.end ();
       it = handleValuePairs.begin ())
  {
    curr = *it;
    delete curr;
    handleValuePairs.erase (it);
  }
}

RTI::ULong PHVPSet::start () const
{
  RTI::ULong size = handleValuePairs.size ();
 
  if (size == 0)
  {
    return size + 1;
  }
 
  return 0;
}

RTI::ULong PHVPSet::valid (RTI::ULong i) const
{
  RTI::ULong size = handleValuePairs.size ();
 
  if (0 <= i && i < size)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
 
RTI::ULong PHVPSet::next (RTI::ULong i) const
{
  return i + 1;
}
