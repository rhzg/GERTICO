/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: hzg $
$Name $
$Log: RTI_AHVPSet.h,v $
Revision 1.3  2003/04/29 06:26:14  hzg
Portierung auf Windows

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#ifndef AHVPSet_HEADER
#define AHVPSet_HEADER
 
#include <vector>
#include "RTI.hh"
#include "RTI_HVPSet.h"

class AHVPSet : public RTI::AttributeHandleValuePairSet
{
	std::vector <HandleValuePair *> handleValuePairs;

public:
  AHVPSet (RTI::ULong count);
  ~AHVPSet ();

  RTI::ULong size () const;
 
  RTI::Handle getHandle (RTI::ULong i) const
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  RTI::ULong getValueLength (RTI::ULong i) const
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  void getValue (RTI::ULong i, char *buff, RTI::ULong &valueLength) const
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  char *getValuePointer (RTI::ULong i, RTI::ULong &valueLength) const
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  RTI::TransportType getTransportType (RTI::ULong i) const
    throw (
      RTI::ArrayIndexOutOfBounds,
      RTI::InvalidHandleValuePairSetContext);
 
  RTI::OrderType getOrderType (RTI::ULong i) const
    throw (
      RTI::ArrayIndexOutOfBounds,
      RTI::InvalidHandleValuePairSetContext);
 
  RTI::Region *getRegion (RTI::ULong i) const
    throw (
      RTI::ArrayIndexOutOfBounds,
      RTI::InvalidHandleValuePairSetContext);
 
  void add (RTI::Handle h, const char* buff, RTI::ULong valueLength)
    throw (
      RTI::ValueLengthExceeded,
      RTI::ValueCountExceeded);
 
  // not guaranteed safe while iterating
  void remove (RTI::Handle h)
    throw (RTI::ArrayIndexOutOfBounds);
 
  void moveFrom (const RTI::AttributeHandleValuePairSet& ahvps, RTI::ULong &i)
    throw (
      RTI::ValueCountExceeded,
      RTI::ArrayIndexOutOfBounds);
 
  void empty (); // Empty the Set without deallocating space.
 
  RTI::ULong start () const;
  RTI::ULong valid (RTI::ULong i) const;
  RTI::ULong next (RTI::ULong i) const;
};

#endif
