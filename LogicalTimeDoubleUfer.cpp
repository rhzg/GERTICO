/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: LogicalTimeDoubleI.cpp,v $
Revision 1.1  2007/09/06 09:22:09  mul
Changes for ieee1516.

 
**
*******************************************************************************/

#include "RTI/SpecificConfig.h"
#include "RTI/LogicalTime.h"
#include "RTI/LogicalTimeFactory.h"
#include "RTI/LogicalTimeInterval.h"
#include "RTI/LogicalTimeIntervalFactory.h"
#include "RTI/EncodedLogicalTime.h"
#include "RTI/EncodedLogicalTimeInterval.h"
#include "RTI/VariableLengthValueClass.h"

#include "RTI/EncodedLogicalTime.h"
#include "RTI/EncodedLogicalTimeInterval.h"

#include "LogicalTimeDouble.h"

#include <float.h>
#include <iostream>
#include <string>
#include <wchar.h>
#if defined(_WIN32)
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif

#ifdef _WIN32 
#define swprintf _snwprintf
#endif

class EncodedLogicalTimeI : public RTI::EncodedLogicalTime
{
private:
  RTI::VariableLengthValueClass _value;
  void* _data;
  size_t _size;
public:
  EncodedLogicalTimeI(const void* data, size_t size) : _value(data, size) 
  {
  }
  virtual ~EncodedLogicalTimeI() throw () {}
    
  virtual void const * data() const
  {
    return _value.data();
  }
  virtual size_t size() const
  {
    return _value.size();
  }
};

class EncodedLogicalTimeIntervalI : public RTI::EncodedLogicalTimeInterval
{
private:
  RTI::VariableLengthValueClass _value;
  void* _data;
  size_t _size;
public:
  EncodedLogicalTimeIntervalI(const void* data, size_t size) : _value(data, size)
  {
  }
  virtual ~EncodedLogicalTimeIntervalI() throw () {}
    
  virtual void const * data() const
  {
    return _value.data();
  }
  virtual size_t size() const
  {
    return _value.size();
  }
};

LogicalTimeDouble::LogicalTimeDouble(double value) : _value(value)
{
}

LogicalTimeDouble::~LogicalTimeDouble(void)
throw ()
{
}

void LogicalTimeDouble::setInitial(void)
{
  _value = 0.0;
}

bool LogicalTimeDouble::isInitial(void)
{
  if (_value == 0.0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
  
void LogicalTimeDouble::setFinal(void)
{
  _value = DBL_MAX;
}

bool LogicalTimeDouble::isFinal(void)
{
  if (_value == DBL_MAX)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void LogicalTimeDouble::setTo(RTI::LogicalTime const & value)
        throw (RTI::InvalidLogicalTime)
{
  const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
  _value = p._value;
}

void LogicalTimeDouble::increaseBy(RTI::LogicalTimeInterval const & addend)
        throw (RTI::IllegalTimeArithmetic, RTI::InvalidLogicalTimeInterval)
{
  const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(addend);
  _value += p._value;
}

void LogicalTimeDouble::decreaseBy(RTI::LogicalTimeInterval const & subtrahend)
        throw (RTI::IllegalTimeArithmetic, RTI::InvalidLogicalTimeInterval)
{
  const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(subtrahend);
  _value -= p._value;
}

std::auto_ptr< RTI::LogicalTimeInterval > LogicalTimeDouble::subtract(RTI::LogicalTime const & subtrahend) const
        throw (RTI::InvalidLogicalTime)
{
  const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(subtrahend);
  return std::auto_ptr< RTI::LogicalTimeInterval >(new LogicalTimeIntervalDouble(_value - p._value));
}

bool LogicalTimeDouble::isGreaterThan(RTI::LogicalTime const & value) const
        throw (RTI::InvalidLogicalTime)
{
  const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
  return _value > p._value;
}

bool LogicalTimeDouble::isLessThan(RTI::LogicalTime const & value) const
        throw (RTI::InvalidLogicalTime)
{
  const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
  return _value < p._value;
}

bool LogicalTimeDouble::isEqualTo(RTI::LogicalTime const & value) const
        throw (RTI::InvalidLogicalTime)
{
  const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
  return _value == p._value;
}

bool LogicalTimeDouble::isGreaterThanOrEqualTo(RTI::LogicalTime const & value) const
        throw (RTI::InvalidLogicalTime)
{
  const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
  return _value >= p._value;
}

bool LogicalTimeDouble::isLessThanOrEqualTo(RTI::LogicalTime const & value) const
        throw (RTI::InvalidLogicalTime)
{
  const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
  return _value <= p._value;
}

std::auto_ptr< RTI::EncodedLogicalTime > LogicalTimeDouble::encode(void) const
{
//  char buff[sizeof(double)];

//#if defined(_M_IX86) || defined(i386)
//  *((int*)buff) = htonl(*(((int*)&_value)+1));
//  *(((int*)buff)+1) = htonl(*((int*)&_value));
//#else
//  memcpy(buff, (char*)&_value, sizeof(_value));
//#endif
   double buf;
   const char* src = reinterpret_cast<const char*>(&_value);
   char* dst = reinterpret_cast<char*>(&buf) + sizeof(buf);
   for (size_t i = 0; i < sizeof(buf); ++i)
      *--dst = ~(*src++);
  std::auto_ptr<RTI::EncodedLogicalTime> lt(new EncodedLogicalTimeI(reinterpret_cast<char*>(&buf), sizeof(double)));

//  std::auto_ptr<RTI::EncodedLogicalTime> lt(new EncodedLogicalTimeI(buff, sizeof(double)));
  return lt;
}
  
std::wstring LogicalTimeDouble::toString(void) const
{
  wchar_t wc[512];
  size_t len = 512;

  swprintf(wc, len, L"%.14f", _value);
  std::wstring ws(wc); 
  return ws;
}

LogicalTimeDoubleFactory::~LogicalTimeDoubleFactory()
throw ()
{
}

std::auto_ptr< RTI::LogicalTime > LogicalTimeDoubleFactory::makeInitial()
   throw (RTI::InternalError)
{
   return std::auto_ptr< RTI::LogicalTime >(new LogicalTimeDouble(0.0));
}

std::auto_ptr< RTI::LogicalTime > LogicalTimeDoubleFactory::decode(RTI::EncodedLogicalTime const & encodedLogicalTime)
   throw (RTI::InternalError, RTI::CouldNotDecode)
{
//  double netnum;
//  unsigned char *buff = (unsigned char *)encodedLogicalTime.data();

//memcpy((char*)&netnum, buff, sizeof(netnum));
//std::cout << "LogicalTimeIntervalFactoryDouble::decode 244 " << netnum << std::endl;
//#if defined(_M_IX86) || defined(i386)
//  *(((int*)&netnum)+1) = htonl(*((int*)buff));
//  *((int*)&netnum) = htonl(*(((int*)buff)+1));
//std::cout << "LogicalTimeIntervalFactoryDouble::decode 241 " << netnum << std::endl;
//#else
//  memcpy((char*)&netnum, buff, sizeof(netnum));
//std::cout << "LogicalTimeIntervalFactoryDouble::decode 244 " << netnum << std::endl;
//#endif
   double value = 0;
   if (encodedLogicalTime.size() != sizeof(value))
      throw RTI::CouldNotDecode(L"LogicalTimeDouble size mismatch.");

   const char* src = reinterpret_cast<const char*>(encodedLogicalTime.data());
   char* dst = reinterpret_cast<char*>(&value) + sizeof(value);
   for (size_t i = 0; i < sizeof(value); ++i)
      *--dst = ~(*src++);
  RTI::LogicalTime *lt = new LogicalTimeDouble(value);

//  RTI::LogicalTime *lt = new LogicalTimeDouble(netnum);
  std::auto_ptr<RTI::LogicalTime> ret(lt);
  return ret;
}

LogicalTimeIntervalDouble::LogicalTimeIntervalDouble(double value) : _value(value)
{
}

LogicalTimeIntervalDouble::~LogicalTimeIntervalDouble()
  throw ()
{
}

void LogicalTimeIntervalDouble::setZero()
{
   _value = 0.0;
}

bool LogicalTimeIntervalDouble::isZero()
{
   return _value == 0.0;
}

bool LogicalTimeIntervalDouble::isEpsilon()
{
   return _value == 0.000000001;
}

void LogicalTimeIntervalDouble::setTo(RTI::LogicalTimeInterval const & value)
   throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   _value = p._value;
}

std::auto_ptr< RTI::LogicalTimeInterval > LogicalTimeIntervalDouble::subtract(RTI::LogicalTimeInterval const & subtrahend) const
   throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(subtrahend);
   
   double d = _value - p._value;
   if (d < 0) {
      d = -d;
   }
   return std::auto_ptr< RTI::LogicalTimeInterval >(new LogicalTimeIntervalDouble(d));
}

bool LogicalTimeIntervalDouble::isGreaterThan(RTI::LogicalTimeInterval const & value) const
   throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value > p._value;
}

bool LogicalTimeIntervalDouble::isLessThan(RTI::LogicalTimeInterval const & value) const
   throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value < p._value;
}

bool LogicalTimeIntervalDouble::isEqualTo(RTI::LogicalTimeInterval const & value) const
   throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value == p._value;
}

bool LogicalTimeIntervalDouble::isGreaterThanOrEqualTo(RTI::LogicalTimeInterval const & value) const
   throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value >= p._value;
}

bool LogicalTimeIntervalDouble::isLessThanOrEqualTo(RTI::LogicalTimeInterval const & value) const
   throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value <= p._value;
}

std::auto_ptr< RTI::EncodedLogicalTimeInterval > LogicalTimeIntervalDouble::encode() const
{
//  char buff[sizeof(double)];

//#if defined(_M_IX86) || defined(i386)
//  *((int*)buff) = htonl(*(((int*)&_value)+1));
//  *(((int*)buff)+1) = htonl(*((int*)&_value));
//#else
//  memcpy(buff, (char*)&_value, sizeof(_value));
//#endif
   double buf;
   const char* src = reinterpret_cast<const char*>(&_value);
   char* dst = reinterpret_cast<char*>(&buf) + sizeof(buf);
   for (size_t i = 0; i < sizeof(buf); ++i)
      *--dst = ~(*src++);
  std::auto_ptr<RTI::EncodedLogicalTimeInterval> lt(new EncodedLogicalTimeIntervalI(reinterpret_cast<char*>(&buf), sizeof(double)));
//  std::auto_ptr<RTI::EncodedLogicalTimeInterval> lt(new EncodedLogicalTimeIntervalI(buff, sizeof(double)));
  return lt;
}

std::wstring LogicalTimeIntervalDouble::toString() const
{
   wchar_t buf[128];
   swprintf(buf, 128, L"LogicalTimeIntervalDouble<%.14f> the right spot!", _value);
   return buf;
}


LogicalTimeFactoryDouble::~LogicalTimeFactoryDouble()
throw ()
{
}

std::auto_ptr< RTI::LogicalTime > LogicalTimeFactoryDouble::makeInitial()
   throw (RTI::InternalError)
{
   return std::auto_ptr< RTI::LogicalTime >(new LogicalTimeDouble(0.0));
}

std::auto_ptr< RTI::LogicalTime > LogicalTimeFactoryDouble::decode(RTI::EncodedLogicalTime const & encodedLogicalTime)
   throw (RTI::InternalError, RTI::CouldNotDecode)
{
//  double netnum;
//  unsigned char *buff = (unsigned char *)encodedLogicalTime.data();

//#if defined(_M_IX86) || defined(i386)
//  *(((int*)&netnum)+1) = htonl(*((int*)buff));
//  *((int*)&netnum) = htonl(*(((int*)buff)+1));
//std::cout << "LogicalTimeIntervalFactoryDouble::decode 372 " << netnum << std::endl;
//#else
//  memcpy((char*)&netnum, buff, sizeof(netnum));
//std::cout << "LogicalTimeIntervalFactoryDouble::decode 375 " << netnum << std::endl;
//#endif
   double value = 0;
   if (encodedLogicalTime.size() != sizeof(value))
      throw RTI::CouldNotDecode(L"LogicalTimeDouble size mismatch.");

   const char* src = reinterpret_cast<const char*>(encodedLogicalTime.data());
   char* dst = reinterpret_cast<char*>(&value) + sizeof(value);
   for (size_t i = 0; i < sizeof(value); ++i)
      *--dst = ~(*src++);
  RTI::LogicalTime *lt = new LogicalTimeDouble(value);

//  RTI::LogicalTime *lt = new LogicalTimeDouble(netnum);
  std::auto_ptr<RTI::LogicalTime> ret(lt);
  return ret;
}

LogicalTimeIntervalDoubleFactory::~LogicalTimeIntervalDoubleFactory()
   throw ()
{
}

std::auto_ptr< RTI::LogicalTimeInterval > LogicalTimeIntervalDoubleFactory::makeZero()
   throw (RTI::InternalError)
{
   return std::auto_ptr< RTI::LogicalTimeInterval >(new LogicalTimeIntervalDouble(0.0));
}

std::auto_ptr< RTI::LogicalTimeInterval > LogicalTimeIntervalDoubleFactory::epsilon()
   throw (RTI::InternalError)
{
   return std::auto_ptr< RTI::LogicalTimeInterval >(new LogicalTimeIntervalDouble(0.000000001));
}

std::auto_ptr< RTI::LogicalTimeInterval > LogicalTimeIntervalDoubleFactory::decode(RTI::EncodedLogicalTimeInterval const & encodedLogicalTimeInterval)
  // throw (InternalError, CouldNotDecode)
  throw ()
{
//  double netnum;
//  unsigned char *buff = (unsigned char *)encodedLogicalTimeInterval.data();

//#if defined(_M_IX86) || defined(i386)
//  *(((int*)&netnum)+1) = htonl(*((int*)buff));
//  *((int*)&netnum) = htonl(*(((int*)buff)+1));
//std::cout << "LogicalTimeIntervalFactoryDouble::decode 406 " << netnum << std::endl;
//#else
//  memcpy((char*)&netnum, buff, sizeof(netnum));
//std::cout << "LogicalTimeIntervalFactoryDouble::decode 409 " << netnum << std::endl;
//#endif
   double value = 0;
   if (encodedLogicalTimeInterval.size() != sizeof(value))
      throw RTI::CouldNotDecode(L"LogicalTimeDouble size mismatch.");

   const char* src = reinterpret_cast<const char*>(encodedLogicalTimeInterval.data());
   char* dst = reinterpret_cast<char*>(&value) + sizeof(value);
   for (size_t i = 0; i < sizeof(value); ++i)
      *--dst = ~(*src++);
  RTI::LogicalTimeInterval *lt = new LogicalTimeIntervalDouble(value);

//  RTI::LogicalTimeInterval *lt = new LogicalTimeIntervalDouble(netnum);
  std::auto_ptr<RTI::LogicalTimeInterval > ret(lt);
  return ret;
}

LogicalTimeIntervalFactoryDouble::~LogicalTimeIntervalFactoryDouble()
   throw ()
{
}

std::auto_ptr< RTI::LogicalTimeInterval > LogicalTimeIntervalFactoryDouble::makeZero()
   throw (RTI::InternalError)
{
   return std::auto_ptr< RTI::LogicalTimeInterval >(new LogicalTimeIntervalDouble(0.0));
}

std::auto_ptr< RTI::LogicalTimeInterval > LogicalTimeIntervalFactoryDouble::epsilon()
   throw (RTI::InternalError)
{
   return std::auto_ptr< RTI::LogicalTimeInterval >(new LogicalTimeIntervalDouble(0.000000001));
}

std::auto_ptr< RTI::LogicalTimeInterval > LogicalTimeIntervalFactoryDouble::decode(RTI::EncodedLogicalTimeInterval const & encodedLogicalTimeInterval)
  // throw (InternalError, CouldNotDecode)
  throw ()
{
//  double netnum;
//  unsigned char *buff = (unsigned char *)encodedLogicalTimeInterval.data();

//#if defined(_M_IX86) || defined(i386)
//  *(((int*)&netnum)+1) = htonl(*((int*)buff));
//  *((int*)&netnum) = htonl(*(((int*)buff)+1));
//std::cout << "LogicalTimeIntervalFactoryDouble::decode 442 " << netnum << std::endl;
//#else
//  memcpy((char*)&netnum, buff, sizeof(netnum));
//std::cout << "LogicalTimeIntervalFactoryDouble::decode 445 " << netnum << std::endl;
//#endif
   double value = 0;
   if (encodedLogicalTimeInterval.size() != sizeof(value))
      throw RTI::CouldNotDecode(L"LogicalTimeDouble size mismatch.");

   const char* src = reinterpret_cast<const char*>(encodedLogicalTimeInterval.data());
   char* dst = reinterpret_cast<char*>(&value) + sizeof(value);
   for (size_t i = 0; i < sizeof(value); ++i)
      *--dst = ~(*src++);
  RTI::LogicalTimeInterval *lt = new LogicalTimeIntervalDouble(value);

//  RTI::LogicalTimeInterval *lt = new LogicalTimeIntervalDouble(netnum);
  std::auto_ptr<RTI::LogicalTimeInterval > ret(lt);
  return ret;
}
