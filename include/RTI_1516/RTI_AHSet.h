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
Revision 1.1  2007/09/06 09:34:57  mul
Changes for ieee1516.

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

#include <RTI/RTIambassadorFactory.h>
#include "RTI.hh"
#include "baseTypes.hh"
#include "RTItypes.hh"

namespace RTI_V1_3
{

class AHSet : public RTI_V1_3::AttributeHandleSet
{
  std::vector <RTI_V1_3::Handle> handles;

public:
  AHSet (RTI_V1_3::ULong count);
  ~AHSet ();

  RTI_V1_3::ULong size () const;
 
  RTI_V1_3::AttributeHandle getHandle (RTI_V1_3::ULong i) const
    throw (RTI_V1_3::ArrayIndexOutOfBounds);
 
  void add (RTI_V1_3::AttributeHandle h)
    throw (RTI_V1_3::ArrayIndexOutOfBounds, RTI_V1_3::AttributeNotDefined);

  // not guaranteed safe while iterating
  void remove (RTI_V1_3::AttributeHandle h)
    throw (RTI_V1_3::AttributeNotDefined);
 
  void empty (); // Empty the Set
 
  RTI_V1_3::Boolean isEmpty () const;  //is set empty?
  RTI_V1_3::Boolean isMember (RTI_V1_3::AttributeHandle h) const;
};

}

#endif
