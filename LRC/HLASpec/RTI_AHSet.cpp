/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_AHSet.cpp,v $
Revision 1.6  2007/01/22 12:47:25  mul
Minor change.

Revision 1.5  2007/01/22 12:37:08  mul
Fix access to and exception handling.

Revision 1.4  2006/12/18 10:10:57  mul
Test parameter values.

Revision 1.3  2003/08/26 14:54:02  mul
Fiy a memory leak.

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#include "RTI_AHSet.h"

AHSet::AHSet (RTI::ULong l)
{
}

AHSet::~AHSet ()
{
  empty ();
}

RTI::ULong AHSet::size () const
{
  RTI::ULong ret = handles.size ();

  return ret;
}
 
RTI::Handle AHSet::getHandle (RTI::ULong i) const
    throw (RTI::ArrayIndexOutOfBounds)
{
  RTI::ULong size = handles.size ();

  if (i < 0 || i > size - 1)
  {
    throw RTI::ArrayIndexOutOfBounds("");
  }

  RTI::ULong ret = handles[i];

  return ret;
}
 
void AHSet::add (RTI::Handle h)
    throw (
      RTI::ArrayIndexOutOfBounds,
      RTI::AttributeNotDefined)
{
  if (isMember(h))
  {
    return;
  }

  handles.push_back (h);
}
 
// not guaranteed safe while iterating
void AHSet::remove (RTI::Handle h)
    throw (RTI::AttributeNotDefined)
{
  std::vector <RTI::Handle>::iterator itHandle;

  for (itHandle = handles.begin(); itHandle != handles.end(); itHandle++)
  {
    if (*itHandle == h)
    {
      handles.erase(itHandle);
      return;
    }
  }

  throw RTI::AttributeNotDefined("");
}
 
// Empty the Set.
void AHSet::empty ()
{
  handles.clear ();
}

RTI::Boolean AHSet::isEmpty () const
{
  RTI::ULong size = handles.size ();

  if (size)
  {
    return RTI::RTI_FALSE;
  }

  return RTI::RTI_TRUE;
}

RTI::Boolean AHSet::isMember (RTI::AttributeHandle h) const
{
  std::vector <RTI::Handle> handlesTmp;
  std::vector <RTI::Handle>::iterator itHandle;

  handlesTmp = handles;
  for (itHandle = handlesTmp.begin(); itHandle != handlesTmp.end(); itHandle++)
  {
    if (*itHandle == h)
    {
      return RTI::RTI_TRUE;
    }
  }

  return RTI::RTI_FALSE;
}
