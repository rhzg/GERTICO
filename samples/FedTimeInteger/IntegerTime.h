#ifndef IntegerTime_h
#define IntegerTime_h

#include <iostream>
#include <RTI.hh>
#include <sys/types.h>

#if !defined (WIN32)
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#endif

#ifdef _WIN32
#if !defined (MYTIMEAPI)
#define MYTIMEEXPORT __declspec(dllimport)
#else
#define MYTIMEEXPORT __declspec(dllexport)
#endif
#else
#define MYTIMEEXPORT
#endif

class MYTIMEEXPORT IntegerTime : public RTI::FedTime {
//-----------------------------------------------------------------
// Constructors and Destructors
//-----------------------------------------------------------------
public:
  IntegerTime();
  IntegerTime(const RTI::Long&);
  IntegerTime(const RTI::FedTime&);
  IntegerTime(const IntegerTime&);
  virtual ~IntegerTime();

//-----------------------------------------------------------------
// Overloaded functions from RTI::FedTime
//-----------------------------------------------------------------
public:
  virtual void                setZero();
  virtual RTI::Boolean        isZero();
  virtual void                setEpsilon();
  virtual void                setPositiveInfinity();
  virtual RTI::Boolean        isPositiveInfinity();
  virtual int                 encodedLength() const;
  virtual void                encode(char *buff) const;
  virtual int                 getPrintableLength() const;
  virtual void                getPrintableString(char*);

//-----------------------------------------------------------------
// Overloaded operators from RTI::FedTime
//-----------------------------------------------------------------
public:
  virtual RTI::FedTime& operator+= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator-= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);
  
  virtual RTI::Boolean operator<= (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator< (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

   virtual RTI::Boolean operator>= (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);
  
  virtual RTI::Boolean operator> (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator== (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);
  
  virtual RTI::FedTime& operator= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

//-----------------------------------------------------------------
// Implementation functions
//-----------------------------------------------------------------
public:
  virtual RTI::Long         getTime() const;

//-----------------------------------------------------------------
// Implementation operators
//-----------------------------------------------------------------
  virtual RTI::Boolean operator== (const RTI::Long&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator!= (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator!= (const RTI::Long&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator= (const IntegerTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator= (const RTI::Long&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator*= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator/= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator+= (const RTI::Long&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator-= (const RTI::Long&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator*= (const RTI::Long&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator/= (const RTI::Long&)
    throw (RTI::InvalidFederationTime);

  virtual IntegerTime operator+ (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual IntegerTime operator+ (const RTI::Long&)
    throw (RTI::InvalidFederationTime);

  virtual IntegerTime operator- (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual IntegerTime operator- (const RTI::Long&)
    throw (RTI::InvalidFederationTime);

  virtual IntegerTime operator* (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual IntegerTime operator* (const RTI::Long&)
    throw (RTI::InvalidFederationTime);

  virtual IntegerTime operator/ (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual IntegerTime operator/ (const RTI::Long&)
    throw (RTI::InvalidFederationTime);
  
//-----------------------------------------------------------------
// Implementation friends
//-----------------------------------------------------------------
public:
  friend std::ostream MYTIMEEXPORT & operator<< (std::ostream&, const RTI::FedTime&);

//-----------------------------------------------------------------
// Implementation member variables
//-----------------------------------------------------------------
private:
  RTI::Long                 _fedTime;
  RTI::Long                 _zero;
  RTI::Long                 _epsilon;
  RTI::Long                 _positiveInfinity;
};

//-----------------------------------------------------------------
// Global operators
//-----------------------------------------------------------------

IntegerTime operator+ (const RTI::Long&, const RTI::FedTime&);
IntegerTime operator- (const RTI::Long&, const RTI::FedTime&);
IntegerTime operator* (const RTI::Long&, const RTI::FedTime&);
IntegerTime operator/ (const RTI::Long&, const RTI::FedTime&);

#endif
