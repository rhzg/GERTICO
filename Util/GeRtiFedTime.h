/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: GeRtiFedTime.h,v $
Revision 1.4  2010/05/14 13:50:51  mul
Add logical time interval.

Revision 1.3  2008/11/26 15:26:33  mul
Changes for shared libraries.

Revision 1.2  2007/09/05 15:04:53  mul
Changes for ieee1516.

Revision 1.1  2007/05/09 11:37:59  mul
New generic time.

 
**
*******************************************************************************/

#ifndef GeRtiFedTime_H_
#define GeRtiFedTime_H_

#include "idl/GeRtiFactoryS.h"

#ifdef IEEE_1516
#include "RTI/LogicalTime.h"
#include "RTI/LogicalTimeFactory.h"
#include "RTI/LogicalTimeIntervalFactory.h"
#endif

namespace GERTICO
{
  class GeRtiEncodedLogicalTimeInterval
  {
  public:
    virtual ~GeRtiEncodedLogicalTimeInterval() throw () {}
    
    virtual void   const * data() const = 0;
    virtual size_t         size() const = 0;
  };

  class GeRtiLogicalTimeInterval
  {
  public:
    virtual
    ~GeRtiLogicalTimeInterval()
    throw () {};

    virtual
    void
    setZero(void) = 0;

    virtual
    bool
    isZero() = 0;
  
    virtual
    bool
    isEpsilon() = 0;

    virtual GeRtiLogicalTimeInterval& operator-= (const GeRtiLogicalTimeInterval&)
      throw (GeRtiFactory::InvalidLogicalTimeInterval) = 0;

    virtual bool operator> (const GeRtiLogicalTimeInterval&) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval) = 0;

    virtual bool operator< (const GeRtiLogicalTimeInterval&) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval) = 0;

    virtual bool operator== (const GeRtiLogicalTimeInterval&) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval) = 0;

    virtual bool operator>= (const GeRtiLogicalTimeInterval&) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval) = 0;

    virtual bool operator<= (const GeRtiLogicalTimeInterval&) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval) = 0;
    
    virtual GeRtiLogicalTimeInterval& operator= (const GeRtiLogicalTimeInterval&)
      throw (
        GeRtiFactory::InvalidLogicalTimeInterval) = 0;

    virtual
    std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval>
    encode() const = 0;

    virtual int getPrintableLength() const = 0;

    virtual void getPrintableString(char*) = 0;
  };

  class  GeRtiFedTime {
  public:
    virtual ~GeRtiFedTime();

    virtual void setZero() = 0;

    virtual bool isZero() = 0;
  
    virtual void setEpsilon() = 0;

    virtual void setPositiveInfinity() = 0;

    virtual bool isPositiveInfinity() = 0;
  
    virtual GeRtiFedTime& operator+= (GeRtiLogicalTimeInterval const &)
      throw (
        GeRtiFactory::InvalidFederationTime) = 0;

    virtual GeRtiFedTime& operator-= (GeRtiLogicalTimeInterval const &)
      throw (
        GeRtiFactory::InvalidFederationTime) = 0;
  
    virtual std::auto_ptr<GeRtiLogicalTimeInterval> operator- (GeRtiFedTime const & subtrahend) const
      throw (GeRtiFactory::InvalidFederationTime) = 0;

    virtual bool operator<= (const GeRtiFedTime&) const
      throw (
        GeRtiFactory::InvalidFederationTime) = 0;

    virtual bool operator< (const GeRtiFedTime&) const
      throw (
        GeRtiFactory::InvalidFederationTime) = 0;

    virtual bool operator>= (const GeRtiFedTime&) const
      throw (
        GeRtiFactory::InvalidFederationTime) = 0;
  
    virtual bool operator> (const GeRtiFedTime&) const
      throw (
        GeRtiFactory::InvalidFederationTime) = 0;

    virtual bool operator== (const GeRtiFedTime&) const
      throw (
        GeRtiFactory::InvalidFederationTime) = 0;
  
    virtual GeRtiFedTime& operator= (const GeRtiFedTime&)
      throw (
        GeRtiFactory::InvalidFederationTime) = 0;

    //return bytes needed to encode
    virtual int encodedLength() const = 0;
  
    //encode into suppled buffer
    virtual void encode(char *buff) const = 0;
  
    virtual int getPrintableLength() const = 0;

    virtual void getPrintableString(char*) = 0;
  
  };

  class  GeRtiLogicalTimeIntervalFactory {
  public:
#ifdef IEEE_1516
    RTI::LogicalTimeIntervalFactory &logicalTimeIntervalFactory;

    GeRtiLogicalTimeIntervalFactory(RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory);
#else
    GeRtiLogicalTimeIntervalFactory(void);
#endif
    GeRtiLogicalTimeInterval* epsilon()
      throw (
        GeRtiFactory::MemoryExhausted);
    
    GeRtiLogicalTimeInterval* makeZero()
      throw (
        GeRtiFactory::MemoryExhausted);

    GeRtiLogicalTimeInterval* decode(GERTICO::GeRtiEncodedLogicalTimeInterval &theGeRtiEncodedLogicalTimeInterval)
      throw (
        GeRtiFactory::MemoryExhausted);
  };

  class  GeRtiFedTimeFactory {
  public:
#ifdef IEEE_1516
    RTI::LogicalTimeFactory &logicalTimeFactory;
    RTI::LogicalTimeIntervalFactory &logicalTimeIntervalFactory;

    GeRtiFedTimeFactory(RTI::LogicalTimeFactory &theLogicalTimeFactory, RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory);
#endif

    GeRtiFedTime* makeZero()
      throw (
        GeRtiFactory::MemoryExhausted);

    GeRtiFedTime* decode(const char *buf)
      throw (
        GeRtiFactory::MemoryExhausted);
  };
};

#endif
