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
#include "RTI.hh"
#include "RTI_HVPSet.h"

class PHVPSet : public RTI::ParameterHandleValuePairSet
{
  std::vector <HandleValuePair *> handleValuePairs;

public:
  PHVPSet (RTI::ULong count);
  ~PHVPSet ();

  RTI::ULong size () const;
 
  RTI::Handle getHandle (
    RTI::ULong i) const
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  RTI::ULong getValueLength (
    RTI::ULong i) const
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  void getValue (
    RTI::ULong i,
    char*      buff,
    RTI::ULong&     valueLength) const
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  char *getValuePointer (
    RTI::ULong i,
    RTI::ULong&     valueLength) const
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  RTI::TransportType getTransportType (void) const
    throw ( RTI::InvalidHandleValuePairSetContext);
 
  RTI::OrderType getOrderType (void) const
    throw ( RTI::InvalidHandleValuePairSetContext);
 
  RTI::Region *getRegion (void) const
    throw ( RTI::InvalidHandleValuePairSetContext);
 
  void add (
    RTI::Handle      h,
    const char* buff,
    RTI::ULong       valueLength)
    throw (
      RTI::ValueLengthExceeded,
      RTI::ValueCountExceeded);
 
  void remove (          // not guaranteed safe while iterating
    RTI::Handle      h)
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  void moveFrom (
	  const RTI::ParameterHandleValuePairSet& phvps,
    RTI::ULong&               i)
    throw (
      RTI::ValueCountExceeded,
      RTI::ArrayIndexOutOfBounds);
 
  void empty (); // Empty the Set without deallocating space.
 
  RTI::ULong start () const;
  RTI::ULong valid (RTI::ULong i) const;
  RTI::ULong next (RTI::ULong i) const;
};

#endif
