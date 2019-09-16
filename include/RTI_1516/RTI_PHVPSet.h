/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_PHVPSet.h,v $
Revision 1.1  2007/09/06 09:34:58  mul
Changes for ieee1516.

Revision 1.5  2005/02/11 14:49:53  mul
Add scoping.

Revision 1.4  2003/04/29 06:26:14  hzg
Portierung auf Windows

Revision 1.3  2002/12/19 13:32:46  hzg
*** empty log message ***

Revision 1.2  2002/07/16 08:57:23  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#ifndef PHVPSet_HEADER
#define PHVPSet_HEADER
 
#include <vector>

#include "RTI_HVPSet.h"

namespace RTI_V1_3
{

class PHVPSet : public RTI_V1_3::ParameterHandleValuePairSet
{
  std::vector <HandleValuePair *> handleValuePairs;

public:
  PHVPSet (RTI_V1_3::ULong count);
  ~PHVPSet ();

  RTI_V1_3::ULong size () const;
 
  RTI_V1_3::Handle getHandle (
    RTI_V1_3::ULong i) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  RTI_V1_3::ULong getValueLength (
    RTI_V1_3::ULong i) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  void getValue (
    RTI_V1_3::ULong i,
    char*      buff,
    RTI_V1_3::ULong&     valueLength) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  char *getValuePointer (
    RTI_V1_3::ULong i,
    RTI_V1_3::ULong&     valueLength) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  RTI_V1_3::TransportType getTransportType (void) const
    throw ( RTI_V1_3::InvalidHandleValuePairSetContext);
 
  RTI_V1_3::OrderType getOrderType (void) const
    throw ( RTI_V1_3::InvalidHandleValuePairSetContext);
 
  RTI_V1_3::Region *getRegion (void) const
    throw ( RTI_V1_3::InvalidHandleValuePairSetContext);
 
  void add (
    RTI_V1_3::Handle      h,
    const char* buff,
    RTI_V1_3::ULong       valueLength)
    throw (
      RTI_V1_3::ValueLengthExceeded,
      RTI_V1_3::ValueCountExceeded);
 
  void remove (          // not guaranteed safe while iterating
    RTI_V1_3::Handle      h)
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  void moveFrom (
	  const RTI_V1_3::ParameterHandleValuePairSet& phvps,
    RTI_V1_3::ULong&               i)
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
