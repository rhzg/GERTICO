#ifndef FedTime_h
#define FedTime_h

#include <RTI.hh>
#include <sys/types.h>
#include <string.h>

#if !defined (MYTIMEAPI)
#define MYTIMEEXPORT __declspec(dllimport)
#else
#define MYTIMEEXPORT __declspec(dllexport)
#endif

class MYTIMEEXPORT RTIfedTime : public RTI::FedTime {
//-----------------------------------------------------------------
// Constructors and Destructors
//-----------------------------------------------------------------
public:
  RTIfedTime();
  RTIfedTime(const RTI::Double&);
  RTIfedTime(const RTI::FedTime&);
  RTIfedTime(const RTIfedTime&);
  virtual ~RTIfedTime();

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
  virtual RTI::Double         getTime() const;

//-----------------------------------------------------------------
// Implementation operators
//-----------------------------------------------------------------
  virtual RTI::Boolean operator== (const RTI::Double&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator!= (const RTI::FedTime&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::Boolean operator!= (const RTI::Double&) const
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator= (const RTIfedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator= (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator*= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator/= (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator+= (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator-= (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator*= (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTI::FedTime& operator/= (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator+ (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator+ (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator- (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator- (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator* (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator* (const RTI::Double&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator/ (const RTI::FedTime&)
    throw (RTI::InvalidFederationTime);

  virtual RTIfedTime operator/ (const RTI::Double&)
    throw (RTI::InvalidFederationTime);
  
//-----------------------------------------------------------------
// Implementation friends
//-----------------------------------------------------------------
public:
  friend RTI_STD::ostream MYTIMEEXPORT & operator<< (RTI_STD::ostream&, const RTI::FedTime&);

//-----------------------------------------------------------------
// Implementation member variables
//-----------------------------------------------------------------
private:
  RTI::Double                 _fedTime;
  RTI::Double                 _zero;
  RTI::Double                 _epsilon;
  RTI::Double                 _positiveInfinity;
};

//-----------------------------------------------------------------
// Global operators
//-----------------------------------------------------------------

RTIfedTime operator+ (const RTI::Double&, const RTI::FedTime&);
RTIfedTime operator- (const RTI::Double&, const RTI::FedTime&);
RTIfedTime operator* (const RTI::Double&, const RTI::FedTime&);
RTIfedTime operator/ (const RTI::Double&, const RTI::FedTime&);

#endif
