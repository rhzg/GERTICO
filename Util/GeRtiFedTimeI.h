/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: GeRtiFedTimeI.h,v $
Revision 1.11  2010/07/30 12:48:03  cvsuser
Use more auto_ptr.

Revision 1.10  2010/05/14 13:32:00  mul
Add logical time interval.

Revision 1.9  2009/02/03 09:05:51  mul
Minor changes.

Revision 1.8  2008/11/26 15:24:26  mul
Changes for shared libraries.

Revision 1.7  2008/03/06 09:34:54  mul
Changes for linux.

Revision 1.6  2008/02/07 09:22:37  mul
Change encoded time logic.

Revision 1.5  2007/11/26 15:51:57  mul
Changes for verification test.

Revision 1.4  2007/10/17 13:11:14  mul
Changes for delivery.

Revision 1.3  2007/10/08 07:51:16  mul
Fix some factory problems.

Revision 1.2  2007/09/05 15:05:41  mul
Changes for ieee1516.

Revision 1.1  2007/05/09 11:38:00  mul
New generic time.


**
*******************************************************************************/

#ifndef GeRtiFedTimeI_h
#define GeRtiFedTimeI_h

#include <memory>
#include <sys/types.h>
#include <string.h>
#include "GeRtiFedTime.h"
#ifdef IEEE_1516
#include "RTI/LogicalTime.h"
#include "RTI/LogicalTimeFactory.h"
#include "RTI/LogicalTimeIntervalFactory.h"
#include "RTI/EncodedLogicalTime.h"
#include "RTI/EncodedLogicalTimeInterval.h"
#else
#include "include/RTI_1.3/fedtime.hh"
#endif

#ifdef IEEE_1516
namespace GERTICO1516
{
  class EncodedLogicalTimeI : public RTI::EncodedLogicalTime
  {
    size_t len;
    unsigned char buff[256];

    //-----------------------------------------------------------------
    // Implementation specific functions.
    //-----------------------------------------------------------------

    public:
    //-----------------------------------------------------------------
    // Constructors and Destructors
    //-----------------------------------------------------------------
      EncodedLogicalTimeI(void const *theTime, size_t const &theLen);
      virtual ~EncodedLogicalTimeI(void) throw() {};

    //-----------------------------------------------------------------
    // Overloaded functions.
    //-----------------------------------------------------------------
    void   const *data(void) const;
    size_t        size(void) const;
  };

  class EncodedLogicalTimeIntervalI : public RTI::EncodedLogicalTimeInterval
  {
    size_t len;
    unsigned char buff[256];

    //-----------------------------------------------------------------
    // Implementation specific functions.
    //-----------------------------------------------------------------

    public:
    //-----------------------------------------------------------------
    // Constructors and Destructors
    //-----------------------------------------------------------------
      EncodedLogicalTimeIntervalI(void const *theTime, size_t const &theLen);
      virtual ~EncodedLogicalTimeIntervalI(void) throw();

    //-----------------------------------------------------------------
    // Overloaded functions.
    //-----------------------------------------------------------------
    void   const *data(void) const;
    size_t        size(void) const;
  };
};
#endif

namespace GERTICO
{
  class GeRtiEncodedLogicalTimeIntervalI : public GERTICO::GeRtiEncodedLogicalTimeInterval
  {
    size_t len;
    unsigned char buff[256];

    //-----------------------------------------------------------------
    // Implementation specific functions.
    //-----------------------------------------------------------------

  public:
    //-----------------------------------------------------------------
    // Constructors and Destructors
    //-----------------------------------------------------------------
    GeRtiEncodedLogicalTimeIntervalI(void const *theTime, size_t const &theLen);
    virtual ~GeRtiEncodedLogicalTimeIntervalI() throw () {}
    
    //-----------------------------------------------------------------
    // Overloaded functions.
    //-----------------------------------------------------------------
    virtual void   const * data() const;
    virtual size_t         size() const;
  };

  class GeRtiLogicalTimeIntervalI : public GERTICO::GeRtiLogicalTimeInterval
  {
//    RTI::LogicalTimeIntervalFactory &logicalTimeIntervalFactory;
  public:
#ifdef IEEE_1516
    GeRtiLogicalTimeIntervalI(RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory);
    GeRtiLogicalTimeIntervalI(RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, unsigned int const &theFlag);
    GeRtiLogicalTimeIntervalI(RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, GERTICO::GeRtiEncodedLogicalTimeInterval &theGeRtiEncodedLogicalTimeInterval);
#else
    GeRtiLogicalTimeIntervalI(unsigned int const &theFlag);
    GeRtiLogicalTimeIntervalI(GERTICO::GeRtiEncodedLogicalTimeInterval &theGeRtiEncodedLogicalTimeInterval);
#endif
    virtual
    ~GeRtiLogicalTimeIntervalI()
    throw ();

    virtual
    void setZero(void);

    virtual
    bool isZero();
  
    virtual
    bool isEpsilon();

    virtual GeRtiLogicalTimeInterval& operator-= (const GeRtiLogicalTimeInterval&)
      throw (GeRtiFactory::InvalidLogicalTimeInterval);

    virtual bool operator> (const GeRtiLogicalTimeInterval&) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval);

    virtual bool operator< (const GeRtiLogicalTimeInterval&) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval);

    virtual bool operator== (const GeRtiLogicalTimeInterval&) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval);

    virtual bool operator>= (const GeRtiLogicalTimeInterval&) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval);

    virtual bool operator<= (const GeRtiLogicalTimeInterval&) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval);
    
    virtual GERTICO::GeRtiLogicalTimeInterval& operator= (const GeRtiLogicalTimeInterval&)
      throw (GeRtiFactory::InvalidLogicalTimeInterval);

    virtual
    std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> encode() const;

    virtual int getPrintableLength() const;

    virtual void getPrintableString(char*);

  //-----------------------------------------------------------------
  // Implementation member variables
  //-----------------------------------------------------------------
  private:
#ifdef IEEE_1516
    std::auto_ptr<RTI::LogicalTimeInterval> fedTime;
    std::auto_ptr<RTI::LogicalTimeInterval> fedTimeEpsilon;
#else
    std::auto_ptr<RTI::FedTime> fedTime;
    std::auto_ptr<RTI::FedTime> fedTimeEpsilon;
#endif
  };

  class  GeRtiFedTimeI : public GERTICO::GeRtiFedTime {
  //-----------------------------------------------------------------
  // Constructors and Destructors
  //-----------------------------------------------------------------
  public:
#ifdef IEEE_1516
    GeRtiFedTimeI(RTI::LogicalTimeFactory &theLogicalTimeFactory, RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory);
    GeRtiFedTimeI(RTI::LogicalTimeFactory &theLogicalTimeFactory, RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, GERTICO::GeRtiFedTime const &theTime);
    GeRtiFedTimeI(RTI::LogicalTimeFactory &theLogicalTimeFactory, RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, GeRtiFedTimeI const &theTime);
    GeRtiFedTimeI(RTI::LogicalTimeFactory &theLogicalTimeFactory, RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, char const *buf, size_t const &theLen);
#else
    GeRtiFedTimeI(void);
    GeRtiFedTimeI(GERTICO::GeRtiFedTime const &theTime);
    GeRtiFedTimeI(GeRtiFedTimeI const &theTime);
    GeRtiFedTimeI(char const *buf, size_t const &theLen);
#endif
    virtual ~GeRtiFedTimeI();

  //-----------------------------------------------------------------
  // Overloaded functions from RTI::FedTime
  //-----------------------------------------------------------------
  public:
    virtual void                setZero();
    virtual bool        isZero();
    virtual void                setEpsilon();
    virtual void                setPositiveInfinity();
    virtual bool        isPositiveInfinity();
    virtual int                 encodedLength() const;
    virtual void                encode(char *buff) const;
    virtual int                 getPrintableLength() const;
    virtual void                getPrintableString(char*);

  //-----------------------------------------------------------------
  // Overloaded operators from RTI::FedTime
  //-----------------------------------------------------------------
  public:
    virtual GERTICO::GeRtiFedTime& operator+= (GERTICO::GeRtiLogicalTimeInterval const &)
      throw (GeRtiFactory::InvalidFederationTime);

    virtual GERTICO::GeRtiFedTime& operator-= (GERTICO::GeRtiLogicalTimeInterval const &)
      throw (GeRtiFactory::InvalidFederationTime);

    virtual std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> operator- (GERTICO::GeRtiFedTime const & subtrahend) const
      throw (GeRtiFactory::InvalidFederationTime);

    virtual bool operator<= (const GERTICO::GeRtiFedTime&) const
      throw (GeRtiFactory::InvalidFederationTime);

    virtual bool operator< (const GERTICO::GeRtiFedTime&) const
      throw (GeRtiFactory::InvalidFederationTime);

    virtual bool operator>= (const GERTICO::GeRtiFedTime&) const
      throw (GeRtiFactory::InvalidFederationTime);

    virtual bool operator> (const GERTICO::GeRtiFedTime&) const
      throw (GeRtiFactory::InvalidFederationTime);

    virtual bool operator== (const GERTICO::GeRtiFedTime&) const
      throw (GeRtiFactory::InvalidFederationTime);

    virtual GERTICO::GeRtiFedTime& operator= (const GERTICO::GeRtiFedTime&)
      throw (GeRtiFactory::InvalidFederationTime);

  //-----------------------------------------------------------------
  // Implementation member variables
  //-----------------------------------------------------------------
  private:
#ifdef IEEE_1516
    RTI::LogicalTimeFactory &logicalTimeFactory;
    RTI::LogicalTimeIntervalFactory &logicalTimeIntervalFactory;

    std::auto_ptr<RTI::LogicalTime> fedTime;
#else
    std::auto_ptr<RTI::FedTime> fedTime;
#endif
  };
};

#endif
