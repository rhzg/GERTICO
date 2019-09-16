/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_AHSet.h,v $
Revision 1.5  2005/02/11 14:49:52  mul
Add scoping.

Revision 1.4  2003/04/29 06:26:14  hzg
Portierung auf Windows

Revision 1.3  2002/12/19 13:32:46  hzg
*** empty log message ***

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#ifndef AHSet_HEADER
#define AHSet_HEADER
 
#include <vector>

#include "RTI.hh"

class AHSet : public RTI::AttributeHandleSet
{
  std::vector <RTI::Handle> handles;

public:
  AHSet (RTI::ULong count);
  ~AHSet ();

  RTI::ULong size () const;
 
  RTI::AttributeHandle getHandle (RTI::ULong i) const
    throw (RTI::ArrayIndexOutOfBounds);
 
  void add (RTI::AttributeHandle h)
    throw (RTI::ArrayIndexOutOfBounds, RTI::AttributeNotDefined);

  // not guaranteed safe while iterating
  void remove (RTI::AttributeHandle h)
    throw (RTI::AttributeNotDefined);
 
  void empty (); // Empty the Set
 
  RTI::Boolean isEmpty () const;  //is set empty?
  RTI::Boolean isMember (RTI::AttributeHandle h) const;
};

#endif
