/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_HSet.cpp,v $
Revision 1.5  2007/01/22 12:37:09  mul
Fix access to and exception handling.

Revision 1.4  2006/12/18 10:10:57  mul
Test parameter values.

Revision 1.3  2003/08/26 14:55:44  mul
Fixed a memory leak.

Revision 1.2  2003/04/29 06:26:14  hzg
Portierung auf Windows

Revision 1.1  2002/09/10 12:52:40  mul
Fix problems with file not found. Changes for linking fedtimeDouble.cpp.

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#include "RTI_HSet.h"

HSet::HSet ()
{
}

HSet::~HSet ()
{
  empty ();
}

RTI::ULong HSet::size () const
{
  RTI::ULong ret = handles.size ();

  return ret;
}
 
RTI::FederateHandle HSet::getHandle (RTI::ULong i) const
    throw (RTI::ArrayIndexOutOfBounds)
{
  RTI::ULong size = handles.size();

  if (i < 0 || i > size - 1)
  {
    throw RTI::ArrayIndexOutOfBounds("");
  }

  RTI::ULong ret = handles[i];

  return ret;
}
 
void HSet::add (RTI::FederateHandle h)
    throw (RTI::ValueCountExceeded)
{
  handles.push_back (h);
}
 
// not guaranteed safe while iterating
void HSet::remove (RTI::FederateHandle h)
    throw (RTI::ArrayIndexOutOfBounds)
{
  RTI::ULong size = handles.size ();
  std::vector <RTI::FederateHandle>::iterator it;

  for (it = handles.begin(); it != handles.end(); it++)
  {
    if (h == *it)
    {
      handles.erase (it);
      break;
    }
  }
}
 
// Empty the Set.
void HSet::empty ()
{
  handles.clear ();
}

RTI::Boolean HSet::isEmpty () const
{
  RTI::ULong size = handles.size ();

  if (size)
  {
    return RTI::RTI_FALSE;
  }

  return RTI::RTI_TRUE;
}

RTI::Boolean HSet::isMember (RTI::FederateHandle h) const
{
	std::vector <RTI::FederateHandle> handlesTmp;
  RTI::ULong size = handles.size ();
  std::vector <RTI::FederateHandle>::iterator it;

  handlesTmp = handles;
  for (it = handlesTmp.begin(); it != handlesTmp.end(); it++)
  {
    if (h == *it)
    {
      return RTI::RTI_TRUE;
    }
  }

  return RTI::RTI_FALSE;
}
