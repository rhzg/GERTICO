using namespace RTI;

// The __int64 datatype is only available with Microsofts compilers.
#ifndef _MSC_VER
typedef long long __int64;
#endif

#ifdef _WIN32
#if defined (BUILDING_FEDTIME)
#define FEDTIME_EXPORT __declspec(dllexport)
#else
#define FEDTIME_EXPORT __declspec(dllimport)
#endif
#else
#define FEDTIME_EXPORT
#endif

// Microsoft has not implemented the swprintf function according
// to the ISO C standard. However, they have a function _snwprintf
// that matches the standardized prototype for swprintf.
#ifdef _WIN32 
#define swprintf _snwprintf
#endif

class FEDTIME_EXPORT LogicalTimeDouble : public LogicalTime
{
public:
   LogicalTimeDouble(double value);

   virtual ~LogicalTimeDouble()
      throw ();

   virtual void setInitial();

   virtual bool isInitial();

   virtual void setFinal();

   virtual bool isFinal();

   virtual long getSeconds() const;
   virtual int getMicros() const;
   
   virtual void setTo(LogicalTime const & value)
      throw (InvalidLogicalTime);

   virtual void increaseBy(LogicalTimeInterval const & addend)
      throw (IllegalTimeArithmetic, InvalidLogicalTimeInterval);

   virtual void decreaseBy(LogicalTimeInterval const & subtrahend)
      throw (IllegalTimeArithmetic, InvalidLogicalTimeInterval);

   virtual std::auto_ptr< LogicalTimeInterval > subtract(LogicalTime const & subtrahend) const
      throw (InvalidLogicalTime);

   virtual bool isGreaterThan(LogicalTime const & value) const
      throw (InvalidLogicalTime);

   virtual bool isLessThan(LogicalTime const & value) const
      throw (InvalidLogicalTime);

   virtual bool isEqualTo(LogicalTime const & value) const
   throw (InvalidLogicalTime);

   virtual bool isGreaterThanOrEqualTo(LogicalTime const & value) const
   throw (InvalidLogicalTime);

   virtual bool isLessThanOrEqualTo(LogicalTime const & value) const
   throw (InvalidLogicalTime);

   virtual std::auto_ptr< EncodedLogicalTime > encode() const;

   virtual std::wstring toString() const;
private:
   explicit LogicalTimeDouble(__int64 value);

   __int64 _value;

   friend class LogicalTimeDoubleFactory;
   friend class LogicalTimeFactoryDouble;
};

class FEDTIME_EXPORT LogicalTimeDoubleFactory : public LogicalTimeFactory
{
public:
   virtual ~LogicalTimeDoubleFactory()
      throw ();
 
   virtual std::auto_ptr< LogicalTime > makeInitial()
      throw (InternalError);
 
   virtual std::auto_ptr< LogicalTime > decode(EncodedLogicalTime const & encodedLogicalTime)
      throw (InternalError, CouldNotDecode);
};

class FEDTIME_EXPORT LogicalTimeFactoryDouble : public LogicalTimeFactory
{
public:
   virtual ~LogicalTimeFactoryDouble()
      throw ();
 
   virtual std::auto_ptr< LogicalTime > makeInitial()
      throw (InternalError);
 
   virtual std::auto_ptr< LogicalTime > decode(EncodedLogicalTime const & encodedLogicalTime)
      throw (InternalError, CouldNotDecode);
};

class FEDTIME_EXPORT LogicalTimeIntervalDouble : public LogicalTimeInterval
{
public:
   LogicalTimeIntervalDouble(double value);

   virtual ~LogicalTimeIntervalDouble()
      throw ();
   
   virtual void setZero();
   
   virtual bool isZero();
   
   virtual bool isEpsilon();

   virtual long getSeconds() const;
   virtual int getMicros() const;

   virtual void setTo(LogicalTimeInterval const & value)
      throw (InvalidLogicalTimeInterval);
   
   virtual std::auto_ptr< LogicalTimeInterval > subtract(LogicalTimeInterval const & subtrahend) const
      throw (InvalidLogicalTimeInterval);
   
   virtual bool isGreaterThan(LogicalTimeInterval const & value) const
      throw (InvalidLogicalTimeInterval);
   
   virtual bool isLessThan(LogicalTimeInterval const & value) const
      throw (InvalidLogicalTimeInterval);
   
   virtual bool isEqualTo(LogicalTimeInterval const & value) const
      throw (InvalidLogicalTimeInterval);
   
   virtual bool isGreaterThanOrEqualTo(LogicalTimeInterval const & value) const
      throw (InvalidLogicalTimeInterval);
   
   virtual bool isLessThanOrEqualTo(LogicalTimeInterval const & value) const
      throw (InvalidLogicalTimeInterval);
   
   virtual std::auto_ptr< EncodedLogicalTimeInterval > encode() const;
   
   virtual std::wstring toString() const;
private:
   explicit LogicalTimeIntervalDouble(__int64 value);
      
   __int64 _value;

   friend class LogicalTimeDouble;
   friend class LogicalTimeIntervalDoubleFactory;
   friend class LogicalTimeIntervalFactoryDouble;
};

class FEDTIME_EXPORT LogicalTimeIntervalDoubleFactory : public LogicalTimeIntervalFactory
{
public:
   virtual ~LogicalTimeIntervalDoubleFactory()
      throw ();
 
   virtual std::auto_ptr< LogicalTimeInterval > makeZero()
      throw (InternalError);
 
   virtual std::auto_ptr< LogicalTimeInterval > epsilon()
      throw (InternalError);
 
   virtual std::auto_ptr< LogicalTimeInterval > decode(EncodedLogicalTimeInterval const & encodedLogicalTimeInterval)
     // throw (InternalError, CouldNotDecode);
     throw ();
};

class FEDTIME_EXPORT LogicalTimeIntervalFactoryDouble : public LogicalTimeIntervalFactory
{
public:
   virtual ~LogicalTimeIntervalFactoryDouble()
      throw ();
 
   virtual std::auto_ptr< LogicalTimeInterval > makeZero()
      throw (InternalError);
 
   virtual std::auto_ptr< LogicalTimeInterval > epsilon()
      throw (InternalError);
 
   virtual std::auto_ptr< LogicalTimeInterval > decode(EncodedLogicalTimeInterval const & encodedLogicalTimeInterval)
     // throw (InternalError, CouldNotDecode);
     throw ();
};

