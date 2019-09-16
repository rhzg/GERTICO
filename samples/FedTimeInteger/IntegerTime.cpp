// IntegerTime.cpp: implementation of the FedTime class.
//
//////////////////////////////////////////////////////////////////////

#define MYTIMEAPI
#include "IntegerTime.h"
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#if defined (WIN32)
#include <winsock2.h>
#endif

#if defined(USE_RTTI)
#  define RTTI_CAST dynamic_cast
#else
#  define RTTI_CAST static_cast
#endif

#if defined(USE_NAMESPACES)
using namespace std;
#endif

RTI::FedTime::~FedTime() 
{

}

RTI::FedTime* RTI::FedTimeFactory::makeZero()
throw (
   RTI::MemoryExhausted)
{
  return new IntegerTime(0);
}

RTI::FedTime* RTI::FedTimeFactory::decode(const char *buf)
throw (
   RTI::MemoryExhausted)
{
   long len, time;
   memcpy(&len, buf, sizeof(len));
   len = ntohl(len);
   if (len != 4)
	   std::cout << "Warning: length != 4.  Length = " << len << std::endl;
   memcpy(&time, (char *)(buf+4), sizeof(time));
   time = ntohl(time);
   return new IntegerTime(time);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IntegerTime::IntegerTime() :
   _fedTime(0),
   _zero(0),
   _epsilon(1),
   _positiveInfinity(LONG_MAX)
{
}

IntegerTime::IntegerTime(const RTI::Long& t) :
//   RTI::FedTime::FedTime(),
   _fedTime(t),
   _zero(0),
   _epsilon(1),
   _positiveInfinity(LONG_MAX)
{
}

IntegerTime::IntegerTime(const IntegerTime& other) :
//   RTI::FedTime::FedTime(),
   _fedTime(other._fedTime),
   _zero(other._zero),
   _epsilon(other._epsilon),
   _positiveInfinity(LONG_MAX)
{
}

IntegerTime::IntegerTime(const RTI::FedTime & theTime) //: RTI::FedTime::FedTime()
{
  IntegerTime const & myTime = RTTI_CAST<IntegerTime const &>(theTime);
  _fedTime = myTime._fedTime;
  _zero = myTime._zero;
  _epsilon = myTime._epsilon;
  _positiveInfinity = myTime._positiveInfinity;
}

IntegerTime::~IntegerTime()
{
}

//-----------------------------------------------------------------
// Overloaded functions from RTI::FedTime
//-----------------------------------------------------------------
void IntegerTime::setZero()
{
	_fedTime = _zero;
}

RTI::Boolean IntegerTime::isZero()
{
   if (_fedTime == _zero) {
      return RTI::RTI_TRUE;
   } else {
      return RTI::RTI_FALSE;
   }
}

void IntegerTime::setEpsilon()
{
   _fedTime = _epsilon;
}

void IntegerTime::setPositiveInfinity()
{
   _fedTime = _positiveInfinity;
}

RTI::Boolean IntegerTime::isPositiveInfinity()
{
   if (_fedTime == _positiveInfinity) {
      return RTI::RTI_TRUE;
   } else {
      return RTI::RTI_FALSE;
   }
}

int IntegerTime::encodedLength() const
{
   return(8);
}

void IntegerTime::encode(char *buff) const
{
   long len = htonl(4), time = htonl(_fedTime);
   memcpy(buff, &len, 4);
   memcpy((buff+4), &time, 4);
}

int IntegerTime::getPrintableLength() const
{
  char buff[100];
  return sprintf(buff, "%d",_fedTime)+1;
}

void IntegerTime::getPrintableString(char* buff)
{
    sprintf(buff,"%ld",_fedTime);
}


//-----------------------------------------------------------------
// Overloaded operators from RTI::FedTime
//-----------------------------------------------------------------
RTI::FedTime& IntegerTime::operator+= (const RTI::FedTime& other)
 throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   _fedTime += otherTime._fedTime;
   return *this;
}

RTI::FedTime& IntegerTime::operator-= (const RTI::FedTime& other)
 throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   _fedTime -= otherTime._fedTime;
   return *this;
}


RTI::Boolean IntegerTime::operator<= (const RTI::FedTime& other) const
 throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   if (_fedTime <= otherTime._fedTime) {
      return RTI::RTI_TRUE;
   } else {
      return RTI::RTI_FALSE;
   }
}


RTI::Boolean IntegerTime::operator< (const RTI::FedTime& other) const
 throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   if (_fedTime < otherTime._fedTime) {
      return RTI::RTI_TRUE;
   } else {
      return RTI::RTI_FALSE;
   }
}


RTI::Boolean IntegerTime::operator>= (const RTI::FedTime& other) const
 throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   if (_fedTime >= otherTime._fedTime) {
      return RTI::RTI_TRUE;
   } else {
      return RTI::RTI_FALSE;
   }
}


RTI::Boolean IntegerTime::operator> (const RTI::FedTime& other) const
 throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   if (_fedTime > otherTime._fedTime) {
      return RTI::RTI_TRUE;
   } else {
      return RTI::RTI_FALSE;
   }
}


RTI::Boolean IntegerTime::operator== (const RTI::FedTime& other) const
 throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   if (_fedTime == otherTime._fedTime) {
      return RTI::RTI_TRUE;
   } else {
      return RTI::RTI_FALSE;
   }
}


RTI::FedTime& IntegerTime::operator= (const RTI::FedTime& other)
 throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   _fedTime = otherTime._fedTime;
   return *this;
}


//-----------------------------------------------------------------
// Implementation functions
//-----------------------------------------------------------------
RTI::Long IntegerTime::getTime() const
{
   return _fedTime;
}

//-----------------------------------------------------------------
// Implementation operators
//-----------------------------------------------------------------
RTI::Boolean IntegerTime::operator== (const RTI::Long& t) const
   throw (RTI::InvalidFederationTime)
{
   if (_fedTime == t) {
      return RTI::RTI_TRUE;
   } else {
      return RTI::RTI_FALSE;
   }
}

RTI::Boolean IntegerTime::operator!= (const RTI::FedTime& other) const
   throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   if (_fedTime != otherTime._fedTime) {
      return RTI::RTI_TRUE;
   } else {
      return RTI::RTI_FALSE;
   }
}

RTI::Boolean IntegerTime::operator!= (const RTI::Long& t) const
   throw (RTI::InvalidFederationTime)
{
   if (_fedTime != t) {
      return RTI::RTI_TRUE;
   } else {
      return RTI::RTI_FALSE;
   }
}

RTI::FedTime& IntegerTime::operator= (const IntegerTime& other)
   throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   _fedTime = otherTime._fedTime;
   return *this;
}

RTI::FedTime& IntegerTime::operator= (const RTI::Long& t)
   throw (RTI::InvalidFederationTime)
{
   _fedTime = t;
   return *this;
}

RTI::FedTime& IntegerTime::operator*= (const RTI::FedTime& other)
   throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   _fedTime *= otherTime._fedTime;
   return *this;
}

RTI::FedTime& IntegerTime::operator/= (const RTI::FedTime& other)
   throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   _fedTime /= otherTime._fedTime;
   return *this;
}

RTI::FedTime& IntegerTime::operator+= (const RTI::Long& t)
   throw (RTI::InvalidFederationTime)
{
   _fedTime += t;
   return *this;
}

RTI::FedTime& IntegerTime::operator-= (const RTI::Long& t)
   throw (RTI::InvalidFederationTime)
{
   _fedTime -= t;
   return *this;
}

RTI::FedTime& IntegerTime::operator*= (const RTI::Long& t)
   throw (RTI::InvalidFederationTime)
{
   _fedTime *= t;
   return *this;
}

RTI::FedTime& IntegerTime::operator/= (const RTI::Long& t)
   throw (RTI::InvalidFederationTime)
{
   _fedTime *= t;
   return *this;
}

IntegerTime IntegerTime::operator+ (const RTI::FedTime& other)
   throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   return IntegerTime(_fedTime + otherTime._fedTime);
}

IntegerTime IntegerTime::operator+ (const RTI::Long& t)
   throw (RTI::InvalidFederationTime)
{
   return IntegerTime(_fedTime + t);
}

IntegerTime IntegerTime::operator- (const RTI::FedTime& other)
   throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   return IntegerTime(_fedTime - otherTime._fedTime);
}

IntegerTime IntegerTime::operator- (const RTI::Long& t)
   throw (RTI::InvalidFederationTime)
{
   return IntegerTime(_fedTime - t);
}

IntegerTime IntegerTime::operator* (const RTI::FedTime& other)
   throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   return IntegerTime(_fedTime * otherTime._fedTime);
}

IntegerTime IntegerTime::operator* (const RTI::Long& t)
   throw (RTI::InvalidFederationTime)
{
   return IntegerTime(_fedTime * t);
}

IntegerTime IntegerTime::operator/ (const RTI::FedTime& other)
   throw (RTI::InvalidFederationTime)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   return IntegerTime(_fedTime / otherTime._fedTime);
}

IntegerTime IntegerTime::operator/ (const RTI::Long& t)
   throw (RTI::InvalidFederationTime)
{
   return IntegerTime(_fedTime / t);
}

//-----------------------------------------------------------------
// Implementation member variables
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Global operators
//-----------------------------------------------------------------

IntegerTime operator+ (const RTI::Long& t, const RTI::FedTime& other)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   return IntegerTime(t + otherTime.getTime());
}

IntegerTime operator- (const RTI::Long& t, const RTI::FedTime& other)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   return IntegerTime(t - otherTime.getTime());
}

IntegerTime operator* (const RTI::Long& t, const RTI::FedTime& other)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   return IntegerTime(t * otherTime.getTime());
}

IntegerTime operator/ (const RTI::Long& t, const RTI::FedTime& other)
{
   const IntegerTime& otherTime = RTTI_CAST<const IntegerTime&>(other);
   return IntegerTime(t / otherTime.getTime());
}


// stream operators
char ch[128];

std::ostream& operator << (std::ostream &out, const RTI::FedTime &e)
{
  IntegerTime* f = (IntegerTime*) &e;
  f->getPrintableString (ch);
  return out << ch;
}
