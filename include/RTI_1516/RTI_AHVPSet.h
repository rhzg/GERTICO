/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_AHVPSet.h,v $
Revision 1.1  2007/09/06 09:34:57  mul
Changes for ieee1516.

Revision 1.3  2003/04/29 06:26:14  hzg
Portierung auf Windows

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#ifndef AHVPSet_HEADER
#define AHVPSet_HEADER
 
#include <vector>

#include "RTI_HVPSet.h"

namespace RTI_V1_3
{

class AHVPSet : public RTI_V1_3::AttributeHandleValuePairSet
{
	std::vector <HandleValuePair *> handleValuePairs;

public:
  AHVPSet (RTI_V1_3::ULong count);
  ~AHVPSet ();

  RTI_V1_3::ULong size () const;
 
  RTI_V1_3::Handle getHandle (RTI_V1_3::ULong i) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  RTI_V1_3::ULong getValueLength (RTI_V1_3::ULong i) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  void getValue (RTI_V1_3::ULong i, char *buff, RTI_V1_3::ULong &valueLength) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  char *getValuePointer (RTI_V1_3::ULong i, RTI_V1_3::ULong &valueLength) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  RTI_V1_3::TransportType getTransportType (RTI_V1_3::ULong i) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds,
      RTI_V1_3::InvalidHandleValuePairSetContext);
 
  RTI_V1_3::OrderType getOrderType (RTI_V1_3::ULong i) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds,
      RTI_V1_3::InvalidHandleValuePairSetContext);
 
  RTI_V1_3::Region *getRegion (RTI_V1_3::ULong i) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds,
      RTI_V1_3::InvalidHandleValuePairSetContext);
 
  void add (RTI_V1_3::Handle h, const char* buff, RTI_V1_3::ULong valueLength)
    throw (
      RTI_V1_3::ValueLengthExceeded,
      RTI_V1_3::ValueCountExceeded);
 
  // not guaranteed safe while iterating
  void remove (RTI_V1_3::Handle h)
    throw (RTI_V1_3::ArrayIndexOutOfBounds);
 
  void moveFrom (const RTI_V1_3::AttributeHandleValuePairSet& ahvps, RTI_V1_3::ULong &i)
    throw (
      RTI_V1_3::ValueCountExceeded,
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  void empty (); // Empty the Set without deallocating space.
 
  RTI_V1_3::ULong start () const;
  RTI_V1_3::ULong valid (RTI_V1_3::ULong i) const;
  RTI_V1_3::ULong next (RTI_V1_3::ULong i) const;
};

}

#endif
