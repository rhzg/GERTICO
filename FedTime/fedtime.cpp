/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: fedtime.cpp,v $
Revision 1.4  2009/01/07 14:53:44  mul
Changes for dynamic library.

Revision 1.3  2007/09/06 09:26:36  mul
Changes for ieee1516.

Revision 1.2  2006/08/10 14:28:05  hzg
using 10 digits as output format

Revision 1.1  2005/07/14 14:55:05  hzg
standard fedtime library distributed with gertico
this replaces the old fedTimeDouble library

Revision 1.4  2005/02/07 10:30:33  mul
Changes due to test cases.

Revision 1.3  2003/11/03 15:51:53  mul
Reusable buffer to prevent memory leak.

Revision 1.2  2003/08/13 07:26:47  mul
unused include

Revision 1.1  2003/07/16 09:53:39  mul
Place FedTime into its own directory.

Revision 1.5  2003/04/29 06:26:15  hzg
Portierung auf Windows

Revision 1.4  2002/09/10 12:52:40  mul
Fix problems with file not found. Changes for linking fedtimeDouble.cpp.

Revision 1.3  2002/07/16 12:22:59  mul
Remove newline from output.

Revision 1.2  2002/07/16 08:57:24  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#include "fedtime.hh"
#include <sys/types.h>
#ifdef _WIN32
#include <string>
#else
#include <string.h>
#include <netinet/in.h>
#endif
#include <stdio.h>
#include <limits.h>

char ch[128];

RTI::FedTime::~FedTime ()
{
}

static double const
RTI_POSITIVE_INFINITY()
{
  return 1.797693e+308;
}

RTIfedTime::RTIfedTime()
  : _zero(0.0),
    _epsilon(0.000000001),
    _positiveInfinity(RTI_POSITIVE_INFINITY())
{
}

RTIfedTime::RTIfedTime(const double & theTime)
  : _fedTime(theTime),
    _zero(0.0),
    _epsilon(0.000000001),
    _positiveInfinity(RTI_POSITIVE_INFINITY())
{
}

RTIfedTime::RTIfedTime(const RTIfedTime & theTime)
  : _fedTime(theTime._fedTime),
    _zero(theTime._zero),
    _epsilon(theTime._epsilon),
    _positiveInfinity(theTime._positiveInfinity)
{
}

RTIfedTime::RTIfedTime(const RTI::FedTime & theTime)
{
  RTIfedTime const & myTime = dynamic_cast<RTIfedTime const &>(theTime);
  _fedTime = myTime._fedTime;
  _zero = myTime._zero;
  _epsilon = myTime._epsilon;
  _positiveInfinity = myTime._positiveInfinity;
}

RTIfedTime::~RTIfedTime()
{
}

void RTIfedTime::setZero()
{
  _fedTime = _zero;
}

RTI::Boolean RTIfedTime::isZero()
{
  if(_fedTime == 0.0)
    return RTI::RTI_TRUE;
  else
    return RTI::RTI_FALSE;
}

void RTIfedTime::setEpsilon()
{
  _fedTime = _epsilon;
}

void RTIfedTime::setPositiveInfinity()
{
  _fedTime = _positiveInfinity;
}

RTI::Boolean RTIfedTime::isPositiveInfinity()
{
  if(_fedTime == _positiveInfinity)
    return RTI::RTI_TRUE;
  else
    return RTI::RTI_FALSE;
}

RTI::FedTime& RTIfedTime::operator += (const RTI::FedTime& theTime)
    throw (RTI::InvalidFederationTime)
{
  RTIfedTime& myTime = (RTIfedTime&)theTime;
  
  _fedTime = _fedTime + myTime._fedTime;
  return *this;
}

RTI::FedTime& RTIfedTime::operator -= (const RTI::FedTime& theTime)
    throw (
      RTI::InvalidFederationTime)
{
  RTIfedTime& myTime = (RTIfedTime&)theTime;
  _fedTime = _fedTime - myTime._fedTime;
  return *this;
}

RTI::Boolean RTIfedTime::operator <= (const RTI::FedTime& theTime) const
    throw (
      RTI::InvalidFederationTime)
{
  RTIfedTime& myTime = (RTIfedTime&)theTime;
  if (_fedTime <= myTime._fedTime)
    return RTI::RTI_TRUE;
  else
    return RTI::RTI_FALSE;
}

RTI::Boolean RTIfedTime::operator < (const RTI::FedTime& theTime) const
    throw (
      RTI::InvalidFederationTime)
{
  RTIfedTime& myTime = (RTIfedTime&)theTime;
  if (_fedTime < myTime._fedTime)
    return RTI::RTI_TRUE;
  else
    return RTI::RTI_FALSE;
}

RTI::Boolean RTIfedTime::operator >= (const RTI::FedTime& theTime) const
    throw (
      RTI::InvalidFederationTime)
{
  RTIfedTime& myTime = (RTIfedTime&)theTime;
  if (_fedTime >= myTime._fedTime)
    return RTI::RTI_TRUE;
  else
    return RTI::RTI_FALSE;
}

RTI::Boolean RTIfedTime::operator > (const RTI::FedTime& theTime) const
    throw (
      RTI::InvalidFederationTime)
{
  RTIfedTime& myTime = (RTIfedTime&)theTime;
  if (_fedTime > myTime._fedTime)
    return RTI::RTI_TRUE;
  else
    return RTI::RTI_FALSE;
}

RTI::Boolean RTIfedTime::operator == (const RTI::FedTime& theTime) const
    throw (
      RTI::InvalidFederationTime)
{
  const RTI::Double& fedTime = ((RTIfedTime&)theTime)._fedTime;
  if (_fedTime == fedTime)
    return RTI::RTI_TRUE;
  else
    return RTI::RTI_FALSE;
}

//-----------------------------------------------------------------
// Implementation operators
//-----------------------------------------------------------------

RTI::Boolean 
RTIfedTime::operator== (const RTI::Double& theTime) const
  throw (RTI::InvalidFederationTime)
{
  if (_fedTime == theTime)
    return RTI::RTI_TRUE;
  else
    return RTI::RTI_FALSE;
}

RTI::Boolean 
RTIfedTime::operator!= (const RTI::FedTime& theTime) const
  throw (RTI::InvalidFederationTime)
{
  const RTI::Double& fedTime = ((RTIfedTime&)theTime)._fedTime;
  if (_fedTime != fedTime)
    return RTI::RTI_TRUE;
  else
    return RTI::RTI_FALSE;
}

RTI::Boolean 
RTIfedTime::operator!= (const RTI::Double& theTime) const
  throw (RTI::InvalidFederationTime)
{
  if (_fedTime != theTime)
    return RTI::RTI_TRUE;
  else
    return RTI::RTI_FALSE;
}

RTI::FedTime& 
RTIfedTime::operator*= (const RTI::FedTime& theTime)
    throw (RTI::InvalidFederationTime)
{
  const RTI::Double& fedTime = ((RTIfedTime&)theTime)._fedTime;
  _fedTime *= fedTime;
  return *this;
}

RTI::FedTime& 
RTIfedTime::operator/= (const RTI::FedTime& theTime)
    throw (RTI::InvalidFederationTime)
{
  const RTI::Double& fedTime = ((RTIfedTime&)theTime)._fedTime;
  _fedTime /= fedTime;
  return *this;
}

RTI::FedTime& 
RTIfedTime::operator+= (const RTI::Double& theTime)
  throw (RTI::InvalidFederationTime)
{
  _fedTime += theTime;
  return *this;
}

RTI::FedTime& 
RTIfedTime::operator-= (const RTI::Double& theTime)
  throw (RTI::InvalidFederationTime)
{
  _fedTime -= theTime;
  return *this;
}

RTI::FedTime& 
RTIfedTime::operator*= (const RTI::Double& theTime)
  throw (RTI::InvalidFederationTime)
{
  _fedTime *= theTime;
  return *this;
}

RTI::FedTime& 
RTIfedTime::operator/= (const RTI::Double& theTime)
  throw (RTI::InvalidFederationTime)
{
  _fedTime /= theTime;
  return *this;
}

RTIfedTime
RTIfedTime::operator+ (const RTI::FedTime& theTime)
  throw (RTI::InvalidFederationTime)
{
  const RTI::Double& fedTime = ((RTIfedTime&)theTime)._fedTime;
  RTIfedTime outTime(_fedTime + fedTime);
  return outTime;
}

RTIfedTime
RTIfedTime::operator+ (const RTI::Double& theTime)
  throw (RTI::InvalidFederationTime)
{
  RTIfedTime outTime(_fedTime + theTime);
  return outTime;
}

RTIfedTime
RTIfedTime::operator- (const RTI::FedTime& theTime)
  throw (RTI::InvalidFederationTime)
{
  const RTI::Double& fedTime = ((RTIfedTime&)theTime)._fedTime;
  RTIfedTime outTime(_fedTime - fedTime);
  return outTime;
}

RTIfedTime
RTIfedTime::operator- (const RTI::Double& theTime)
  throw (RTI::InvalidFederationTime)
{
  RTIfedTime outTime(_fedTime - theTime);
  return outTime;
}

RTIfedTime
RTIfedTime::operator* (const RTI::FedTime& theTime)
  throw (RTI::InvalidFederationTime)
{
  const RTI::Double& fedTime = ((RTIfedTime&)theTime)._fedTime;
  RTIfedTime outTime(_fedTime * fedTime);
  return outTime;
}

RTIfedTime
RTIfedTime::operator* (const RTI::Double& theTime)
  throw (RTI::InvalidFederationTime)
{
  RTIfedTime outTime(_fedTime * theTime);
  return outTime;
}

RTIfedTime
RTIfedTime::operator/ (const RTI::FedTime& theTime)
  throw (RTI::InvalidFederationTime)
{
  const RTI::Double& fedTime = ((RTIfedTime&)theTime)._fedTime;
  RTIfedTime outTime(_fedTime / fedTime);
  return outTime;
}

RTIfedTime
RTIfedTime::operator/ (const RTI::Double& theTime)
  throw (RTI::InvalidFederationTime)
{
  RTIfedTime outTime(_fedTime / theTime);
  return outTime;
}

RTI::FedTime & RTIfedTime::operator = (const RTI::FedTime& theTime)
 throw (RTI::InvalidFederationTime)
{
  RTIfedTime const & myTime = dynamic_cast<RTIfedTime const &>(theTime);
  _fedTime = myTime._fedTime;
 return *this;
}

RTI::FedTime & RTIfedTime::operator = (const RTIfedTime& theTime)
 throw (RTI::InvalidFederationTime)
{
  _fedTime = theTime._fedTime;
 return *this;
}


RTI::FedTime& 
RTIfedTime::operator= (const RTI::Double& theTime)
  throw (RTI::InvalidFederationTime)
{
  _fedTime = theTime;
  return *this;
}

  //return bytes needed to encode
int RTIfedTime::encodedLength() const
{
  return sizeof(RTI::Double);
}

//encode into suppled buffer
void 
RTIfedTime::encode(char *buff) const
{
  RTI::Double netnum = _fedTime;

  memcpy(buff, (char*)&netnum, sizeof(netnum));
}
  
// stream operators
std::ostream& operator << (std::ostream &out, const RTI::FedTime &e)
{
//  char *ch = new char[128];
  RTIfedTime f (e);
  f.getPrintableString (ch);
  return out << ch;
}

int RTIfedTime::getPrintableLength() const
{ 
  char buff[512];
  sprintf(buff, "%.10f", _fedTime);
  return strlen(buff) +1;

}

void RTIfedTime::getPrintableString(char* buf) 
{
  if(_fedTime == _positiveInfinity)
  {
    strcpy(buf, "Inf");
  }
  else
  {
    sprintf(buf, "%.10f", _fedTime);
  }
}

//
// Implementation specific services
//
RTI::Double RTIfedTime::getTime() const
{
  return _fedTime;
}

RTI::FedTime *
RTI::FedTimeFactory::makeZero()
  throw(RTI::MemoryExhausted)
{
  return new RTIfedTime(0);
}
 
RTI::FedTime *
RTI::FedTimeFactory::decode(const char* buff)
  throw(RTI::MemoryExhausted)
{
  RTI::Double netnum;
  memcpy((char*)&netnum, buff, sizeof(netnum));
  return new RTIfedTime(netnum);
}
