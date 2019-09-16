#ifndef FedTimeDoubleI_h
#define FedTimeDoubleI_h

#include <memory>

//#include "RTI/SpecificConfig.h"
#include "RTI/LogicalTime.h"
#include "RTI/LogicalTimeFactory.h"
#include "RTI/LogicalTimeInterval.h"
#include "RTI/LogicalTimeIntervalFactory.h"
//#include "RTI/EncodedLogicalTime.h"
//#include "RTI/EncodedLogicalTimeInterval.h"


// Microsoft has not implemented the swprintf function according
// to the ISO C standard. However, they have a function _snwprintf
// that matches the standardized prototype for swprintf.
#ifdef _WIN32 
#define swprintf _snwprintf
#if defined (BUILDING_FEDTIME)
#define FEDTIME_EXPORT __declspec(dllexport)
#else
#define FEDTIME_EXPORT __declspec(dllimport)
#endif
#else
#define FEDTIME_EXPORT
#endif

class FEDTIME_EXPORT LogicalTimeDouble : public RTI::LogicalTime
{
public:
   LogicalTimeDouble(double value);

   virtual ~LogicalTimeDouble()
      throw ();

   virtual void setInitial();

   virtual bool isInitial();

   virtual void setFinal();

   virtual bool isFinal();

   virtual void setTo(RTI::LogicalTime const & value)
      throw (RTI::InvalidLogicalTime);

   virtual void increaseBy(RTI::LogicalTimeInterval const & addend)
      throw (RTI::IllegalTimeArithmetic, RTI::InvalidLogicalTimeInterval);

   virtual void decreaseBy(RTI::LogicalTimeInterval const & subtrahend)
      throw (RTI::IllegalTimeArithmetic, RTI::InvalidLogicalTimeInterval);

   virtual std::auto_ptr< RTI::LogicalTimeInterval > subtract(RTI::LogicalTime const & subtrahend) const
      throw (RTI::InvalidLogicalTime);

   virtual bool isGreaterThan(RTI::LogicalTime const & value) const
      throw (RTI::InvalidLogicalTime);

   virtual bool isLessThan(RTI::LogicalTime const & value) const
      throw (RTI::InvalidLogicalTime);

   virtual bool isEqualTo(RTI::LogicalTime const & value) const
   throw (RTI::InvalidLogicalTime);

   virtual bool isGreaterThanOrEqualTo(RTI::LogicalTime const & value) const
   throw (RTI::InvalidLogicalTime);

   virtual bool isLessThanOrEqualTo(RTI::LogicalTime const & value) const
   throw (RTI::InvalidLogicalTime);

   virtual std::auto_ptr< RTI::EncodedLogicalTime > encode() const;

   virtual std::wstring toString() const;
private:
   double _value;

   friend class LogicalTimeDoubleFactory;
   friend class LogicalTimeFactoryDouble;
};

class FEDTIME_EXPORT LogicalTimeDoubleFactory : public RTI::LogicalTimeFactory
{
public:
   virtual ~LogicalTimeDoubleFactory()
      throw ();
 
   virtual std::auto_ptr< RTI::LogicalTime > makeInitial()
      throw (RTI::InternalError);
 
   virtual std::auto_ptr< RTI::LogicalTime > decode(RTI::EncodedLogicalTime const & encodedLogicalTime)
      throw (RTI::InternalError, RTI::CouldNotDecode);
};

class FEDTIME_EXPORT LogicalTimeFactoryDouble : public RTI::LogicalTimeFactory
{
public:
   virtual ~LogicalTimeFactoryDouble()
      throw ();
 
   virtual std::auto_ptr< RTI::LogicalTime > makeInitial()
      throw (RTI::InternalError);
 
   virtual std::auto_ptr< RTI::LogicalTime > decode(RTI::EncodedLogicalTime const & encodedLogicalTime)
      throw (RTI::InternalError, RTI::CouldNotDecode);
};

class FEDTIME_EXPORT LogicalTimeIntervalDouble : public RTI::LogicalTimeInterval
{
public:
   LogicalTimeIntervalDouble(double value);

   virtual ~LogicalTimeIntervalDouble()
      throw ();
   
   virtual void setZero();
   
   virtual bool isZero();
   
   virtual bool isEpsilon();

   virtual void setTo(RTI::LogicalTimeInterval const & value)
      throw (RTI::InvalidLogicalTimeInterval);
   
   virtual std::auto_ptr< RTI::LogicalTimeInterval > subtract(RTI::LogicalTimeInterval const & subtrahend) const
      throw (RTI::InvalidLogicalTimeInterval);
   
   virtual bool isGreaterThan(RTI::LogicalTimeInterval const & value) const
      throw (RTI::InvalidLogicalTimeInterval);
   
   virtual bool isLessThan(RTI::LogicalTimeInterval const & value) const
      throw (RTI::InvalidLogicalTimeInterval);
   
   virtual bool isEqualTo(RTI::LogicalTimeInterval const & value) const
      throw (RTI::InvalidLogicalTimeInterval);
   
   virtual bool isGreaterThanOrEqualTo(RTI::LogicalTimeInterval const & value) const
      throw (RTI::InvalidLogicalTimeInterval);
   
   virtual bool isLessThanOrEqualTo(RTI::LogicalTimeInterval const & value) const
      throw (RTI::InvalidLogicalTimeInterval);
   
   virtual std::auto_ptr< RTI::EncodedLogicalTimeInterval > encode() const;
   
   virtual std::wstring toString() const;
private:
   double _value;

   friend class LogicalTimeDouble;
   friend class LogicalTimeIntervalDoubleFactory;
   friend class LogicalTimeIntervalFactoryDouble;
};

class FEDTIME_EXPORT LogicalTimeIntervalDoubleFactory : public RTI::LogicalTimeIntervalFactory
{
public:
   virtual ~LogicalTimeIntervalDoubleFactory()
      throw ();
 
   virtual std::auto_ptr< RTI::LogicalTimeInterval > makeZero()
      throw (RTI::InternalError);
 
   virtual std::auto_ptr< RTI::LogicalTimeInterval > epsilon()
      throw (RTI::InternalError);
 
   virtual std::auto_ptr< RTI::LogicalTimeInterval > decode(RTI::EncodedLogicalTimeInterval const & encodedLogicalTimeInterval)
     // throw (InternalError, CouldNotDecode);
     throw ();
};

class FEDTIME_EXPORT LogicalTimeIntervalFactoryDouble : public RTI::LogicalTimeIntervalFactory
{
public:
   virtual ~LogicalTimeIntervalFactoryDouble()
      throw ();
 
   virtual std::auto_ptr< RTI::LogicalTimeInterval > makeZero()
      throw (RTI::InternalError);
 
   virtual std::auto_ptr< RTI::LogicalTimeInterval > epsilon()
      throw (RTI::InternalError);
 
   virtual std::auto_ptr< RTI::LogicalTimeInterval > decode(RTI::EncodedLogicalTimeInterval const & encodedLogicalTimeInterval)
     // throw (InternalError, CouldNotDecode);
     throw ();
};

#endif
