#ifndef LogicalTimeDouble_HEADER
#define LogicalTimeDouble_HEADER
#ifdef __GNUC__
# pragma interface
#endif
// C++ standard library
#include <string>
// RTI C++ language mapping
#include <RTI/exception.h>
#include <RTI/LogicalTime.h>
#include <RTI/LogicalTimeFactory.h>
#include <RTI/LogicalTimeInterval.h>
#include <RTI/LogicalTimeIntervalFactory.h>
#include <RTI/EncodedLogicalTime.h>
#include <RTI/EncodedLogicalTimeInterval.h>
// project include files
//#include "config.h"

#ifdef _WIN32
#if defined (BUILDING_FEDTIME)
#define FEDTIME_EXPORT __declspec(dllexport)
#else
#define FEDTIME_EXPORT __declspec(dllimport)
#endif
#else
#define FEDTIME_EXPORT
#endif

namespace NAMESPACE {

class FEDTIME_EXPORT LogicalTimeDouble : public RTI::LogicalTime {
public:
   LogicalTimeDouble(double value);

   virtual ~LogicalTimeDouble()
   throw ();

   virtual void setInitial();

   virtual bool isInitial();

   virtual void setFinal();

   virtual bool isFinal();
   
   virtual void setTo(const RTI::LogicalTime& value)
   throw (RTI::InvalidLogicalTime);

   virtual void increaseBy(const RTI::LogicalTimeInterval& addend)
   throw (RTI::IllegalTimeArithmetic, RTI::InvalidLogicalTimeInterval);

   virtual void decreaseBy(const RTI::LogicalTimeInterval& subtrahend)
   throw (RTI::IllegalTimeArithmetic, RTI::InvalidLogicalTimeInterval);

   virtual std::auto_ptr<RTI::LogicalTimeInterval> subtract(const RTI::LogicalTime& subtrahend) const
   throw (RTI::InvalidLogicalTime);

   virtual bool isGreaterThan(const RTI::LogicalTime& value) const
   throw (RTI::InvalidLogicalTime);

   virtual bool isLessThan(const RTI::LogicalTime& value) const
   throw (RTI::InvalidLogicalTime);

   virtual bool isEqualTo(const RTI::LogicalTime& value) const
   throw (RTI::InvalidLogicalTime);

   virtual bool isGreaterThanOrEqualTo(const RTI::LogicalTime& value) const
   throw (RTI::InvalidLogicalTime);

   virtual bool isLessThanOrEqualTo(const RTI::LogicalTime& value) const
   throw (RTI::InvalidLogicalTime);

   virtual std::auto_ptr<RTI::EncodedLogicalTime> encode() const;

   virtual std::wstring toString() const;

   virtual double toDouble() const
   throw ();

   virtual double getValue() const
   throw ();

private:
   double _value;

   friend class LogicalTimeDoubleFactory;
};


class FEDTIME_EXPORT LogicalTimeDoubleFactory : public RTI::LogicalTimeFactory {
public:
   virtual ~LogicalTimeDoubleFactory()
   throw ();
 
   virtual std::auto_ptr<RTI::LogicalTime> makeInitial()
   throw (RTI::InternalError);
 
   virtual std::auto_ptr<RTI::LogicalTime> decode(RTI::EncodedLogicalTime const & encodedLogicalTime)
   throw (RTI::InternalError, RTI::CouldNotDecode);
};


class FEDTIME_EXPORT LogicalTimeIntervalDouble : public RTI::LogicalTimeInterval {
public:
   LogicalTimeIntervalDouble(double value);

   virtual ~LogicalTimeIntervalDouble()
   throw ();
   
   virtual void setZero();
   
   virtual bool isZero();
   
   virtual bool isEpsilon();

   virtual void setTo(const RTI::LogicalTimeInterval& value)
   throw (RTI::InvalidLogicalTimeInterval);
   
   virtual std::auto_ptr<RTI::LogicalTimeInterval> subtract(const RTI::LogicalTimeInterval& subtrahend) const
   throw (RTI::InvalidLogicalTimeInterval);
   
   virtual bool isGreaterThan(const RTI::LogicalTimeInterval& value) const
   throw (RTI::InvalidLogicalTimeInterval);
   
   virtual bool isLessThan(const RTI::LogicalTimeInterval& value) const
   throw (RTI::InvalidLogicalTimeInterval);
   
   virtual bool isEqualTo(const RTI::LogicalTimeInterval& value) const
   throw (RTI::InvalidLogicalTimeInterval);
   
   virtual bool isGreaterThanOrEqualTo(const RTI::LogicalTimeInterval& value) const
   throw (RTI::InvalidLogicalTimeInterval);

   virtual bool isLessThanOrEqualTo(const RTI::LogicalTimeInterval& value) const
   throw (RTI::InvalidLogicalTimeInterval);

   virtual std::auto_ptr<RTI::EncodedLogicalTimeInterval> encode() const;

   virtual std::wstring toString() const;

   virtual double toDouble() const
   throw ();

   virtual double getValue() const
   throw ();

private:
   double _value;

   friend class LogicalTimeDouble;
   friend class LogicalTimeIntervalDoubleFactory;
};


class FEDTIME_EXPORT LogicalTimeIntervalDoubleFactory : public RTI::LogicalTimeIntervalFactory {
public:
   virtual ~LogicalTimeIntervalDoubleFactory()
   throw ();
 
   virtual std::auto_ptr<RTI::LogicalTimeInterval> makeZero()
   throw (RTI::InternalError);
 
   virtual std::auto_ptr<RTI::LogicalTimeInterval> epsilon()
   throw (RTI::InternalError);
 
   virtual std::auto_ptr<RTI::LogicalTimeInterval> decode(RTI::EncodedLogicalTimeInterval const & encodedLogicalTimeInterval)
   throw (RTI::CouldNotDecode);
};

} // namespace NAMESPACE

#endif // LogicalTimeDouble_HEADER
