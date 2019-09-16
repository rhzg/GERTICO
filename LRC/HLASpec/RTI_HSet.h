/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: hzg $
$Name $
$Log: RTI_HSet.h,v $
Revision 1.2  2003/04/29 06:26:14  hzg
Portierung auf Windows

Revision 1.1  2002/09/10 12:52:40  mul
Fix problems with file not found. Changes for linking fedtimeDouble.cpp.

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#ifndef HSet_HEADER
#define HSet_HEADER
 
#include <vector>
#include "RTI.hh"

class HSet : public RTI::FederateHandleSet
{
	std::vector <RTI::FederateHandle> handles;

public:
  HSet ();
  virtual ~HSet ();

  RTI::ULong size () const;
 
  RTI::FederateHandle getHandle (RTI::ULong i) const
    throw (RTI::ArrayIndexOutOfBounds);
 
  void add (RTI::FederateHandle h)
    throw (RTI::ValueCountExceeded);

  // not guaranteed safe while iterating
  void remove (RTI::FederateHandle h)
    throw (RTI::ArrayIndexOutOfBounds);
 
  void empty (); // Empty the Set
 
  RTI::Boolean isEmpty () const;  //is set empty?
  RTI::Boolean isMember (RTI::FederateHandle h) const;
};

#endif
