#ifdef _WIN32
#pragma warning(disable : 4786)
#endif

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

#include <math.h>

namespace
{
   class MyEncodedLogicalTime : public EncodedLogicalTime
   {
   private:
     RTI::VariableLengthValueClass _value;
     void* _data;
     size_t _size;
   public:
      MyEncodedLogicalTime(const void* data, size_t size) :
        _value(data, size) 
      {
      }
      virtual ~MyEncodedLogicalTime() throw () {}
    
      virtual void const * data() const
      {
         return _value.data();
      }
      virtual size_t size() const
      {
         return _value.size();
      }
   };

   class MyEncodedLogicalTimeInterval : public EncodedLogicalTimeInterval
   {
   private:
      RTI::VariableLengthValueClass _value;
      void* _data;
      size_t _size;
   public:
      MyEncodedLogicalTimeInterval(const void* data, size_t size) :
         _value(data, size)
      {
      }
      virtual ~MyEncodedLogicalTimeInterval() throw () {}
    
      virtual void const * data() const
      {
         return _value.data();
      }
      virtual size_t size() const
      {
         return _value.size();
      }
   };
}


#ifdef _WIN32
const __int64 MAX_VALUE = 9223372036854775807;
#else
const __int64 MAX_VALUE = 2147483648;
#endif
const __int64 MULTIPLIER = 1000000;

LogicalTimeDouble::LogicalTimeDouble(double value)
{
   long seconds = (long)floor(value);
   long micros = (long)fmod(value * MULTIPLIER, MULTIPLIER);

   _value = seconds * MULTIPLIER + micros;
}

LogicalTimeDouble::LogicalTimeDouble(__int64 value) :
   _value(value)
{
}

LogicalTimeDouble::~LogicalTimeDouble()
   throw ()
{
}

void LogicalTimeDouble::setInitial()
{
   _value = 0;
}

bool LogicalTimeDouble::isInitial()
{
   return _value == 0;
}

void LogicalTimeDouble::setFinal()
{
   _value = MAX_VALUE;
}

bool LogicalTimeDouble::isFinal()
{
   return _value == MAX_VALUE;
}

void LogicalTimeDouble::setTo(LogicalTime const & value)
   throw (InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   _value = p._value;
}

void LogicalTimeDouble::increaseBy(LogicalTimeInterval const & addend)
   throw (IllegalTimeArithmetic, InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(addend);
   _value += p._value;
}

void LogicalTimeDouble::decreaseBy(LogicalTimeInterval const & subtrahend)
   throw (IllegalTimeArithmetic, InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(subtrahend);
   _value -= p._value;
}

std::auto_ptr< LogicalTimeInterval > LogicalTimeDouble::subtract(LogicalTime const & subtrahend) const
   throw (InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(subtrahend);
   return std::auto_ptr< LogicalTimeInterval >(new LogicalTimeIntervalDouble(_value - p._value));
}

bool LogicalTimeDouble::isGreaterThan(LogicalTime const & value) const
   throw (InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   return _value > p._value;
}

bool LogicalTimeDouble::isLessThan(LogicalTime const & value) const
   throw (InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   return _value < p._value;
}

bool LogicalTimeDouble::isEqualTo(LogicalTime const & value) const
throw (InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   return _value == p._value;
}

bool LogicalTimeDouble::isGreaterThanOrEqualTo(LogicalTime const & value) const
throw (InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   return _value >= p._value;
}

bool LogicalTimeDouble::isLessThanOrEqualTo(LogicalTime const & value) const
throw (InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   return _value <= p._value;
}

std::auto_ptr< EncodedLogicalTime > LogicalTimeDouble::encode() const
{
   unsigned char buf[sizeof(_value)];
   int pos = 0;
   buf[pos++] = (_value >> 56) & 0xFF;
   buf[pos++] = (_value >> 48) & 0xFF;
   buf[pos++] = (_value >> 40) & 0xFF;
   buf[pos++] = (_value >> 32) & 0xFF;
   buf[pos++] = (_value >> 24) & 0xFF;
   buf[pos++] = (_value >> 16) & 0xFF;
   buf[pos++] = (_value >>  8) & 0xFF;
   buf[pos++] = (_value >>  0) & 0xFF;
   return std::auto_ptr< EncodedLogicalTime >(new MyEncodedLogicalTime(buf, sizeof(buf)));
}

long LogicalTimeDouble::getSeconds() const
{
   return _value / MULTIPLIER;
}

int LogicalTimeDouble::getMicros() const
{
   return (int)(_value % MULTIPLIER);
}

std::wstring LogicalTimeDouble::toString() const
{
   wchar_t buf[128];
   if (_value == MAX_VALUE) {
      swprintf(buf, 128, L"LogicalTimeDouble<INF>");
   } else {
      swprintf(buf, 128, L"LogicalTimeDouble<%d.%06d>", getSeconds(), getMicros());
   }
   return buf;
}

LogicalTimeDoubleFactory::~LogicalTimeDoubleFactory()
throw ()
{
}

std::auto_ptr< LogicalTime > LogicalTimeDoubleFactory::makeInitial()
   throw (InternalError)
{
   return std::auto_ptr< LogicalTime >(new LogicalTimeDouble((__int64)0));
}

std::auto_ptr< LogicalTime > LogicalTimeDoubleFactory::decode(EncodedLogicalTime const & encodedLogicalTime)
   throw (InternalError, CouldNotDecode)
{
   __int64 value = 0;
   unsigned char* buf = (unsigned char*)encodedLogicalTime.data();
   int pos = 0;
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   return std::auto_ptr< LogicalTime >(new LogicalTimeDouble(value));
}

LogicalTimeFactoryDouble::~LogicalTimeFactoryDouble()
throw ()
{
}

std::auto_ptr< LogicalTime > LogicalTimeFactoryDouble::makeInitial()
   throw (InternalError)
{
   return std::auto_ptr< LogicalTime >(new LogicalTimeDouble((__int64)0));
}

std::auto_ptr< LogicalTime > LogicalTimeFactoryDouble::decode(EncodedLogicalTime const & encodedLogicalTime)
   throw (InternalError, CouldNotDecode)
{
   __int64 value = 0;
   unsigned char* buf = (unsigned char*)encodedLogicalTime.data();
   int pos = 0;
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   return std::auto_ptr< LogicalTime >(new LogicalTimeDouble(value));
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

LogicalTimeIntervalDouble::LogicalTimeIntervalDouble(double value)
{
   long seconds = (long)floor(value);
   long micros = (long)fmod(value * MULTIPLIER, MULTIPLIER);

   _value = seconds * MULTIPLIER + micros;
}

LogicalTimeIntervalDouble::LogicalTimeIntervalDouble(__int64 value) :
   _value(value)
{
}
   
LogicalTimeIntervalDouble::~LogicalTimeIntervalDouble()
  throw ()
{
}

void LogicalTimeIntervalDouble::setZero()
{
   _value = 0;
}

bool LogicalTimeIntervalDouble::isZero()
{
   return _value == 0;
}

bool LogicalTimeIntervalDouble::isEpsilon()
{
   return _value == 1;
}

long LogicalTimeIntervalDouble::getSeconds() const
{
   return _value / MULTIPLIER;
}

int LogicalTimeIntervalDouble::getMicros() const
{
   return (int)(_value % MULTIPLIER);
}

void LogicalTimeIntervalDouble::setTo(LogicalTimeInterval const & value)
   throw (InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   _value = p._value;
}

std::auto_ptr< LogicalTimeInterval > LogicalTimeIntervalDouble::subtract(LogicalTimeInterval const & subtrahend) const
   throw (InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(subtrahend);
   
   __int64 d = _value - p._value;
   if (d < 0) {
      d = -d;
   }
   return std::auto_ptr< LogicalTimeInterval >(new LogicalTimeIntervalDouble(d));
}

bool LogicalTimeIntervalDouble::isGreaterThan(LogicalTimeInterval const & value) const
   throw (InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value > p._value;
}

bool LogicalTimeIntervalDouble::isLessThan(LogicalTimeInterval const & value) const
   throw (InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value < p._value;
}

bool LogicalTimeIntervalDouble::isEqualTo(LogicalTimeInterval const & value) const
   throw (InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value == p._value;
}

bool LogicalTimeIntervalDouble::isGreaterThanOrEqualTo(LogicalTimeInterval const & value) const
   throw (InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value >= p._value;
}

bool LogicalTimeIntervalDouble::isLessThanOrEqualTo(LogicalTimeInterval const & value) const
   throw (InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value <= p._value;
}

std::auto_ptr< EncodedLogicalTimeInterval > LogicalTimeIntervalDouble::encode() const
{
   unsigned char buf[sizeof(_value)];
   int pos = 0;
   buf[pos++] = (_value >> 56) & 0xFF;
   buf[pos++] = (_value >> 48) & 0xFF;
   buf[pos++] = (_value >> 40) & 0xFF;
   buf[pos++] = (_value >> 32) & 0xFF;
   buf[pos++] = (_value >> 24) & 0xFF;
   buf[pos++] = (_value >> 16) & 0xFF;
   buf[pos++] = (_value >>  8) & 0xFF;
   buf[pos++] = (_value >>  0) & 0xFF;
   return std::auto_ptr< EncodedLogicalTimeInterval >(new MyEncodedLogicalTimeInterval(buf, sizeof(buf)));
}

std::wstring LogicalTimeIntervalDouble::toString() const
{
   wchar_t buf[128];
   swprintf(buf, 128, L"LogicalTimeIntervalDouble<%d.%06d>", getSeconds(), getMicros());
   return buf;
}

LogicalTimeIntervalDoubleFactory::~LogicalTimeIntervalDoubleFactory()
   throw ()
{
}

std::auto_ptr< LogicalTimeInterval > LogicalTimeIntervalDoubleFactory::makeZero()
   throw (InternalError)
{
   return std::auto_ptr< LogicalTimeInterval >(new LogicalTimeIntervalDouble((__int64)0));
}

std::auto_ptr< LogicalTimeInterval > LogicalTimeIntervalDoubleFactory::epsilon()
   throw (InternalError)
{
   return std::auto_ptr< LogicalTimeInterval >(new LogicalTimeIntervalDouble((__int64)1));
}

std::auto_ptr< LogicalTimeInterval > LogicalTimeIntervalDoubleFactory::decode(EncodedLogicalTimeInterval const & encodedLogicalTimeInterval)
  // throw (InternalError, CouldNotDecode)
  throw ()
{
   __int64 value = 0;
   unsigned char* buf = (unsigned char*)encodedLogicalTimeInterval.data();
   int pos = 0;
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   return std::auto_ptr< LogicalTimeInterval >(new LogicalTimeIntervalDouble(value));
}

LogicalTimeIntervalFactoryDouble::~LogicalTimeIntervalFactoryDouble()
   throw ()
{
}

std::auto_ptr< LogicalTimeInterval > LogicalTimeIntervalFactoryDouble::makeZero()
   throw (InternalError)
{
   return std::auto_ptr< LogicalTimeInterval >(new LogicalTimeIntervalDouble((__int64)0));
}

std::auto_ptr< LogicalTimeInterval > LogicalTimeIntervalFactoryDouble::epsilon()
   throw (InternalError)
{
   return std::auto_ptr< LogicalTimeInterval >(new LogicalTimeIntervalDouble((__int64)1));
}

std::auto_ptr< LogicalTimeInterval > LogicalTimeIntervalFactoryDouble::decode(EncodedLogicalTimeInterval const & encodedLogicalTimeInterval)
  // throw (InternalError, CouldNotDecode)
  throw ()
{
   __int64 value = 0;
   unsigned char* buf = (unsigned char*)encodedLogicalTimeInterval.data();
   int pos = 0;
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   value = (value << 8) | buf[pos++];
   return std::auto_ptr< LogicalTimeInterval >(new LogicalTimeIntervalDouble(value));
}
