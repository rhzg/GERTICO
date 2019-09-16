#ifdef __GNUC__
# pragma implementation
#endif
//#include "StdAfx.h"
// C++ standard library
#include <cmath>
#include <limits>
#include <iostream>
// RTI C++ language mapping
//#include <RTI/1516.h>
#include <RTI/EncodedLogicalTime.h>
#include <RTI/EncodedLogicalTimeInterval.h>
#include "RTI/VariableLengthValueClass.h"
// project include files
#include "LogicalTimeDouble.h"

// Microsoft has not implemented the swprintf function according
// to the ISO C standard. However, they have a function _snwprintf
// that matches the standardized prototype for swprintf.
#ifdef _WIN32 
#define swprintf _snwprintf
#endif

namespace NAMESPACE {

   class EncodedLogicalTimeDouble : public RTI::EncodedLogicalTime {
   public:
      EncodedLogicalTimeDouble(const void* data, size_t size) :
        _value(data, size) 
      {
      }

      virtual ~EncodedLogicalTimeDouble() throw () {}
    
      virtual void const * data() const
      {
         return _value.data();
      }

      virtual size_t size() const
      {
         return _value.size();
      }

   private:
     RTI::VariableLengthValueClass _value;
     void* _data;
     size_t _size;
   };

   class EncodedLogicalTimeDoubleInterval : public RTI::EncodedLogicalTimeInterval {
   public:
      EncodedLogicalTimeDoubleInterval(const void* data, size_t size) :
         _value(data, size)
      {
      }

      virtual ~EncodedLogicalTimeDoubleInterval() throw () {}
    
      virtual void const * data() const
      {
         return _value.data();
      }

      virtual size_t size() const
      {
         return _value.size();
      }
   private:
      RTI::VariableLengthValueClass _value;
      void* _data;
      size_t _size;
   };


   const double EPSILON = 1.0e-14;
   const double MAX_VALUE = HUGE_VAL;

} // namespace NAMESPACE


NAMESPACE::LogicalTimeDouble::LogicalTimeDouble(double value)
{
   _value = value;
}


NAMESPACE::LogicalTimeDouble::~LogicalTimeDouble()
throw ()
{
}


void NAMESPACE::LogicalTimeDouble::setInitial()
{
   _value = 0;
}


bool NAMESPACE::LogicalTimeDouble::isInitial()
{
   return _value == 0;
}


void NAMESPACE::LogicalTimeDouble::setFinal()
{
   _value = MAX_VALUE;
}


bool NAMESPACE::LogicalTimeDouble::isFinal()
{
   return _value == MAX_VALUE;
}


void NAMESPACE::LogicalTimeDouble::setTo(const RTI::LogicalTime& value)
throw (RTI::InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   _value = p._value;
}


void NAMESPACE::LogicalTimeDouble::increaseBy(const RTI::LogicalTimeInterval& addend)
throw (RTI::IllegalTimeArithmetic, RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(addend);
   _value += p._value;
}


void NAMESPACE::LogicalTimeDouble::decreaseBy(const RTI::LogicalTimeInterval& subtrahend)
throw (RTI::IllegalTimeArithmetic, RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(subtrahend);
   _value -= p._value;
}


std::auto_ptr<RTI::LogicalTimeInterval>
NAMESPACE::LogicalTimeDouble::subtract(const RTI::LogicalTime& subtrahend) const
throw (RTI::InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(subtrahend);
   return std::auto_ptr<RTI::LogicalTimeInterval>(new LogicalTimeIntervalDouble(_value - p._value));
}


bool
NAMESPACE::LogicalTimeDouble::isGreaterThan(const RTI::LogicalTime& value) const
throw (RTI::InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   return _value > p._value;
}


bool
NAMESPACE::LogicalTimeDouble::isLessThan(const RTI::LogicalTime& value) const
throw (RTI::InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   return _value < p._value;
}


bool
NAMESPACE::LogicalTimeDouble::isEqualTo(const RTI::LogicalTime& value) const
throw (RTI::InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   return _value == p._value;
}


bool
NAMESPACE::LogicalTimeDouble::isGreaterThanOrEqualTo(const RTI::LogicalTime& value) const
throw (RTI::InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   return _value >= p._value;
}


bool
NAMESPACE::LogicalTimeDouble::isLessThanOrEqualTo(const RTI::LogicalTime& value) const
throw (RTI::InvalidLogicalTime)
{
   const LogicalTimeDouble& p = dynamic_cast<const LogicalTimeDouble&>(value);
   return _value <= p._value;
}


std::auto_ptr<RTI::EncodedLogicalTime>
NAMESPACE::LogicalTimeDouble::encode() const
{
   //std::cerr << "Encoding C++ logical time " << _value << std::endl;
   double buf;
   const char* src = reinterpret_cast<const char*>(&_value);
   char* dst = reinterpret_cast<char*>(&buf) + sizeof(buf);
   for (size_t i = 0; i < sizeof(buf); ++i)
      *--dst = ~(*src++);
   return std::auto_ptr<RTI::EncodedLogicalTime>(new EncodedLogicalTimeDouble(&buf, sizeof(buf)));
}


std::wstring
NAMESPACE::LogicalTimeDouble::toString() const
{
   wchar_t buf[128];
   if (_value == MAX_VALUE) {
      swprintf(buf, 128, L"LogicalTimeDouble<INF>");
   } else {
      swprintf(buf, 128, L"LogicalTimeDouble<%f>", getValue());
   }
   return buf;
}


double
NAMESPACE::LogicalTimeDouble::toDouble() const
throw ()
{
   return getValue();
}


double
NAMESPACE::LogicalTimeDouble::getValue() const
throw ()
{
   return _value;
}


NAMESPACE::LogicalTimeDoubleFactory::~LogicalTimeDoubleFactory()
throw ()
{
}


std::auto_ptr<RTI::LogicalTime>
NAMESPACE::LogicalTimeDoubleFactory::makeInitial()
throw (RTI::InternalError)
{
   return std::auto_ptr<RTI::LogicalTime>(new LogicalTimeDouble(0));
}


std::auto_ptr<RTI::LogicalTime>
NAMESPACE::LogicalTimeDoubleFactory::decode(RTI::EncodedLogicalTime const & encodedLogicalTime)
throw (RTI::InternalError, RTI::CouldNotDecode)
{
   double value = 0;
   if (encodedLogicalTime.size() != sizeof(value))
      throw RTI::CouldNotDecode(L"LogicalTimeDouble size mismatch.");

   const char* src = reinterpret_cast<const char*>(encodedLogicalTime.data());
   char* dst = reinterpret_cast<char*>(&value) + sizeof(value);
   for (size_t i = 0; i < sizeof(value); ++i)
      *--dst = ~(*src++);

   //std::cerr << "Decoded C++ logical time = " << value << std::endl;
   return std::auto_ptr<RTI::LogicalTime>(new LogicalTimeDouble(value));
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

NAMESPACE::LogicalTimeIntervalDouble::LogicalTimeIntervalDouble(double value)
{
   _value = value;
}

   
NAMESPACE::LogicalTimeIntervalDouble::~LogicalTimeIntervalDouble()
  throw ()
{
}


void
NAMESPACE::LogicalTimeIntervalDouble::setZero()
{
   _value = 0;
}


bool
NAMESPACE::LogicalTimeIntervalDouble::isZero()
{
   return _value == 0;
}


bool
NAMESPACE::LogicalTimeIntervalDouble::isEpsilon()
{
   return _value == EPSILON;
}


void
NAMESPACE::LogicalTimeIntervalDouble::setTo(const RTI::LogicalTimeInterval& value)
throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   _value = p._value;
}


std::auto_ptr<RTI::LogicalTimeInterval>
NAMESPACE::LogicalTimeIntervalDouble::subtract(const RTI::LogicalTimeInterval& subtrahend) const
throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(subtrahend);
   
   double d = _value - p._value;
   if (d < 0) {
      d = -d;
   }
   return std::auto_ptr<RTI::LogicalTimeInterval>(new LogicalTimeIntervalDouble(d));
}


bool
NAMESPACE::LogicalTimeIntervalDouble::isGreaterThan(const RTI::LogicalTimeInterval& value) const
throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value > p._value;
}


bool
NAMESPACE::LogicalTimeIntervalDouble::isLessThan(const RTI::LogicalTimeInterval& value) const
throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value < p._value;
}


bool
NAMESPACE::LogicalTimeIntervalDouble::isEqualTo(const RTI::LogicalTimeInterval& value) const
throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value == p._value;
}


bool
NAMESPACE::LogicalTimeIntervalDouble::isGreaterThanOrEqualTo(const RTI::LogicalTimeInterval& value) const
throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value >= p._value;
}


bool
NAMESPACE::LogicalTimeIntervalDouble::isLessThanOrEqualTo(const RTI::LogicalTimeInterval& value) const
throw (RTI::InvalidLogicalTimeInterval)
{
   const LogicalTimeIntervalDouble& p = dynamic_cast<const LogicalTimeIntervalDouble&>(value);
   return _value <= p._value;
}


std::auto_ptr<RTI::EncodedLogicalTimeInterval>
NAMESPACE::LogicalTimeIntervalDouble::encode() const
{
   //std::cerr << "Encoding C++ logical time interval = " << _value << std::endl;
   double buf;
   const char* src = reinterpret_cast<const char*>(&_value);
   char* dst = reinterpret_cast<char*>(&buf) + sizeof(buf);
   for (size_t i = 0; i < sizeof(buf); ++i)
      *--dst = ~(*src++);
   return std::auto_ptr<RTI::EncodedLogicalTimeInterval>(new EncodedLogicalTimeDoubleInterval(&buf, sizeof(buf)));
}


std::wstring
NAMESPACE::LogicalTimeIntervalDouble::toString() const
{
   wchar_t buf[128];
   swprintf(buf, 128, L"LogicalTimeIntervalDouble<%f>", getValue());
   return buf;
}


double
NAMESPACE::LogicalTimeIntervalDouble::toDouble() const
throw ()
{
   return getValue();
}


double
NAMESPACE::LogicalTimeIntervalDouble::getValue() const
throw ()
{
   return _value;
}


NAMESPACE::LogicalTimeIntervalDoubleFactory::~LogicalTimeIntervalDoubleFactory()
throw ()
{
}


std::auto_ptr<RTI::LogicalTimeInterval>
NAMESPACE::LogicalTimeIntervalDoubleFactory::makeZero()
throw (RTI::InternalError)
{
   return std::auto_ptr<RTI::LogicalTimeInterval>(new LogicalTimeIntervalDouble(0));
}


std::auto_ptr<RTI::LogicalTimeInterval>
NAMESPACE::LogicalTimeIntervalDoubleFactory::epsilon()
throw (RTI::InternalError)
{
   return std::auto_ptr<RTI::LogicalTimeInterval>(new LogicalTimeIntervalDouble(EPSILON));
}


std::auto_ptr<RTI::LogicalTimeInterval>
NAMESPACE::LogicalTimeIntervalDoubleFactory::decode(RTI::EncodedLogicalTimeInterval const & encodedLogicalTimeInterval)
  throw (RTI::CouldNotDecode)
{
   double value = 0;
   if (encodedLogicalTimeInterval.size() != sizeof(value))
      throw RTI::CouldNotDecode(L"LogicalTimeDouble size mismatch.");

   const char* src = reinterpret_cast<const char*>(encodedLogicalTimeInterval.data());
   char* dst = reinterpret_cast<char*>(&value) + sizeof(value);
   for (size_t i = 0; i < sizeof(value); ++i)
      *--dst = ~(*src++);
   //std::cerr << "Decoded C++ logical time interval = " << value << std::endl;

   return std::auto_ptr<RTI::LogicalTimeInterval>(new LogicalTimeIntervalDouble(value));
}
