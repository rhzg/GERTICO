#ifndef FedTime_h
#define FedTime_h

#include "baseTypes.hh"
#include "RTItypes.hh"

#include <sys/types.h>
#include <string.h>

#ifdef IEEE_1516
//namespace RTI_V1_3
//{
#endif

//class RTI_EXPORT_FEDTIME RTIfedTime : public RTI_V1_3::FedTime {
class RTI_EXPORT RTIfedTime  : public RTI_V1_3::FedTime {

//-----------------------------------------------------------------
// Constructors and Destructors
//-----------------------------------------------------------------
public:
  RTIfedTime();
  RTIfedTime(const RTI_V1_3::Double&);
  RTIfedTime(const RTI_V1_3::FedTime&);
  RTIfedTime(const RTIfedTime&);
  virtual ~RTIfedTime();

//-----------------------------------------------------------------
// Overloaded functions from RTI_V1_3::FedTime
//-----------------------------------------------------------------
public:
  virtual void                setZero();
  virtual RTI_V1_3::Boolean        isZero();
  virtual void                setEpsilon();
  virtual void                setPositiveInfinity();
  virtual RTI_V1_3::Boolean        isPositiveInfinity();
  virtual int                 encodedLength() const;
  virtual void                encode(char *buff) const;
  virtual int                 getPrintableLength() const;
  virtual void                getPrintableString(char*);

//-----------------------------------------------------------------
// Overloaded operators from RTI_V1_3::FedTime
//-----------------------------------------------------------------
public:
  virtual RTI_V1_3::FedTime& operator+= (const RTI_V1_3::FedTime&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::FedTime& operator-= (const RTI_V1_3::FedTime&)
    throw (RTI_V1_3::InvalidFederationTime);
  
  virtual RTI_V1_3::Boolean operator<= (const RTI_V1_3::FedTime&) const
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::Boolean operator< (const RTI_V1_3::FedTime&) const
    throw (RTI_V1_3::InvalidFederationTime);

   virtual RTI_V1_3::Boolean operator>= (const RTI_V1_3::FedTime&) const
    throw (RTI_V1_3::InvalidFederationTime);
  
  virtual RTI_V1_3::Boolean operator> (const RTI_V1_3::FedTime&) const
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::Boolean operator== (const RTI_V1_3::FedTime&) const
    throw (RTI_V1_3::InvalidFederationTime);
  
  virtual RTI_V1_3::FedTime& operator= (const RTI_V1_3::FedTime&)
    throw (RTI_V1_3::InvalidFederationTime);

//-----------------------------------------------------------------
// Implementation functions
//-----------------------------------------------------------------
public:
  virtual RTI_V1_3::Double         getTime() const;

//-----------------------------------------------------------------
// Implementation operators
//-----------------------------------------------------------------
  virtual RTI_V1_3::Boolean operator== (const RTI_V1_3::Double&) const
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::Boolean operator!= (const RTI_V1_3::FedTime&) const
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::Boolean operator!= (const RTI_V1_3::Double&) const
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::FedTime& operator= (const RTIfedTime&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::FedTime& operator= (const RTI_V1_3::Double&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::FedTime& operator*= (const RTI_V1_3::FedTime&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::FedTime& operator/= (const RTI_V1_3::FedTime&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::FedTime& operator+= (const RTI_V1_3::Double&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::FedTime& operator-= (const RTI_V1_3::Double&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::FedTime& operator*= (const RTI_V1_3::Double&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTI_V1_3::FedTime& operator/= (const RTI_V1_3::Double&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTIfedTime operator+ (const RTI_V1_3::FedTime&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTIfedTime operator+ (const RTI_V1_3::Double&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTIfedTime operator- (const RTI_V1_3::FedTime&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTIfedTime operator- (const RTI_V1_3::Double&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTIfedTime operator* (const RTI_V1_3::FedTime&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTIfedTime operator* (const RTI_V1_3::Double&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTIfedTime operator/ (const RTI_V1_3::FedTime&)
    throw (RTI_V1_3::InvalidFederationTime);

  virtual RTIfedTime operator/ (const RTI_V1_3::Double&)
    throw (RTI_V1_3::InvalidFederationTime);
  
//-----------------------------------------------------------------
// Implementation friends
//-----------------------------------------------------------------
public:
  //
  // RTI_STD was added for the RTI 1.3NG to allow the use of the Standard C++ 
  // ostream or to use the legacy ostream.  The issue concerns whether ostream
  // is in the global namespace or in namespace std.
  //
//  friend std::ostream RTI_EXPORT & operator<< (std::ostream&, const RTI_V1_3::FedTime&);

//-----------------------------------------------------------------
// Implementation member variables
//-----------------------------------------------------------------
private:
  RTI_V1_3::Double                 _fedTime;
  RTI_V1_3::Double                 _zero;
  RTI_V1_3::Double                 _epsilon;
  RTI_V1_3::Double                 _positiveInfinity;
};

//-----------------------------------------------------------------
// Global operators
//-----------------------------------------------------------------

RTIfedTime operator+ (const RTI_V1_3::Double&, const RTI_V1_3::FedTime&);
RTIfedTime operator- (const RTI_V1_3::Double&, const RTI_V1_3::FedTime&);
RTIfedTime operator* (const RTI_V1_3::Double&, const RTI_V1_3::FedTime&);
RTIfedTime operator/ (const RTI_V1_3::Double&, const RTI_V1_3::FedTime&);

#ifdef IEEE_1516
//}
#endif

#endif
