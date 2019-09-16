/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_HSet.h,v $
Revision 1.1  2007/09/06 09:34:57  mul
Changes for ieee1516.

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

#include <RTI/RTIambassadorFactory.h>
#include "RTI.hh"
#include "baseTypes.hh"
#include "RTItypes.hh"

namespace RTI_V1_3
{

class HSet : public RTI_V1_3::FederateHandleSet
{
	std::vector <RTI_V1_3::FederateHandle> handles;

public:
  HSet ();
  virtual ~HSet ();

  RTI_V1_3::ULong size () const;
 
  RTI_V1_3::FederateHandle getHandle (RTI_V1_3::ULong i) const
    throw (RTI_V1_3::ArrayIndexOutOfBounds);
 
  void add (RTI_V1_3::FederateHandle h)
    throw (RTI_V1_3::ValueCountExceeded);

  // not guaranteed safe while iterating
  void remove (RTI_V1_3::FederateHandle h)
    throw (RTI_V1_3::ArrayIndexOutOfBounds);
 
  void empty (); // Empty the Set
 
  RTI_V1_3::Boolean isEmpty () const;  //is set empty?
  RTI_V1_3::Boolean isMember (RTI_V1_3::FederateHandle h) const;
};

}

#endif
