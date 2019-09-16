/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: GeRtiFedTimeI.cpp,v $
Revision 1.17  2010/07/30 12:48:50  cvsuser
Use more auto_ptr.

Revision 1.16  2010/05/14 13:50:08  mul
Add logical time interval.

Revision 1.15  2010/04/12 12:12:41  mul
Fix string length error.

Revision 1.14  2009/01/07 13:48:47  mul
Changes for dynamic library.

Revision 1.13  2008/11/26 15:24:26  mul
Changes for shared libraries.

Revision 1.12  2008/11/17 15:28:50  mul
Changes for logging.

Revision 1.11  2008/09/30 11:11:31  mul
Add logic for late arriving federates.

Revision 1.10  2008/09/29 11:26:43  mul
Add sync_scope_policy as a user option.

Revision 1.9  2008/03/06 09:46:22  mul
Add local encoded time / encoded time interval.

Revision 1.8  2008/01/30 10:18:12  mul
Changes for ieee1516.

Revision 1.7  2007/12/06 08:02:31  mul
Minor changes.

Revision 1.6  2007/11/26 15:51:57  mul
Changes for verification test.

Revision 1.5  2007/11/22 15:24:34  mul
Minor change.

Revision 1.4  2007/10/17 13:11:13  mul
Changes for delivery.

Revision 1.3  2007/10/08 07:52:01  mul
Fix some factory problems.

Revision 1.2  2007/09/05 15:05:41  mul
Changes for ieee1516.

Revision 1.1  2007/05/09 11:37:59  mul
New generic time.

Revision 1.2  2006/08/10 14:28:05  hzg
using 10 digits as output format

Revision 1.1  2005/07/14 14:55:05  hzg
standard fedtime library distributed with gertico
this replaces the old fedTimeDouble library

Revision 1.4  2005/02/07 10:30:33  mul
Changes due to test cases.

Revision 1.3  2003/11/03 15:51:53  mul
Reusable buffer to prevent memory leak.

Revision 1.2  2003/08/13 07:26:47  mul
unused include

Revision 1.1  2003/07/16 09:53:39  mul
Place FedTime into its own directory.

Revision 1.5  2003/04/29 06:26:15  hzg
Portierung auf Windows

Revision 1.4  2002/09/10 12:52:40  mul
Fix problems with file not found. Changes for linking fedtimeDouble.cpp.

Revision 1.3  2002/07/16 12:22:59  mul
Remove newline from output.

Revision 1.2  2002/07/16 08:57:24  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen


**
*******************************************************************************/

#include <sys/types.h>
#ifdef _WIN32
#include <string>
#else
#include <string>
#include <string.h>
#include <netinet/in.h>
#endif
#include <stdio.h>
#include <limits.h>
#include <iostream>

#include "GeRtiFedTimeI.h"

#ifdef IEEE_1516
GERTICO1516::EncodedLogicalTimeI::EncodedLogicalTimeI(void const *theTime, size_t const &theLen)
{
  memcpy(buff, theTime, theLen);
  len = theLen;
}

void const *GERTICO1516::EncodedLogicalTimeI::data(void) const
{
  return buff;
}

size_t GERTICO1516::EncodedLogicalTimeI::size(void) const
{
  return len;
}
GERTICO1516::EncodedLogicalTimeIntervalI::EncodedLogicalTimeIntervalI(void const *theTime, size_t const &theLen)
{
  memcpy(buff, theTime, theLen);
  len = theLen;
}

GERTICO1516::EncodedLogicalTimeIntervalI::~EncodedLogicalTimeIntervalI(void) throw()
{
}

void const *GERTICO1516::EncodedLogicalTimeIntervalI::data(void) const
{
  return buff;
}

size_t GERTICO1516::EncodedLogicalTimeIntervalI::size(void) const
{
  return len;
}
#endif

GERTICO::GeRtiEncodedLogicalTimeIntervalI::GeRtiEncodedLogicalTimeIntervalI(void const *theTime, size_t const &theLen)
{
  memcpy(buff, theTime, theLen);
  len = theLen;
}

void const *GERTICO::GeRtiEncodedLogicalTimeIntervalI::data(void) const
{
  return buff;
}

size_t GERTICO::GeRtiEncodedLogicalTimeIntervalI::size(void) const
{
  return len;
}

//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
#ifdef IEEE_1516
GERTICO::GeRtiLogicalTimeIntervalI::GeRtiLogicalTimeIntervalI(RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory)
{
  fedTime = theLogicalTimeIntervalFactory.makeZero();
  fedTimeEpsilon = theLogicalTimeIntervalFactory.epsilon();
}
#endif

#ifdef IEEE_1516
GERTICO::GeRtiLogicalTimeIntervalI::GeRtiLogicalTimeIntervalI(RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, unsigned int const &theFlag)
#else
GERTICO::GeRtiLogicalTimeIntervalI::GeRtiLogicalTimeIntervalI(unsigned int const &theFlag)
#endif
{
#ifdef IEEE_1516
  if (theFlag == 0)
  {
    fedTime = theLogicalTimeIntervalFactory.makeZero();
  }
  if (theFlag == 1)
  {
    fedTime = theLogicalTimeIntervalFactory.epsilon();
  }
  fedTimeEpsilon = theLogicalTimeIntervalFactory.epsilon();
#else
  fedTime.reset(RTI::FedTimeFactory::makeZero());
  fedTimeEpsilon.reset(RTI::FedTimeFactory::makeZero());
  fedTimeEpsilon->setEpsilon();
  if (theFlag == 1)
  {
    fedTime->setEpsilon();
  }
#endif
}

#ifdef IEEE_1516
GERTICO::GeRtiLogicalTimeIntervalI::GeRtiLogicalTimeIntervalI(RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, GERTICO::GeRtiEncodedLogicalTimeInterval &theGeRtiEncodedLogicalTimeInterval)
#else
GERTICO::GeRtiLogicalTimeIntervalI::GeRtiLogicalTimeIntervalI(GERTICO::GeRtiEncodedLogicalTimeInterval &theGeRtiEncodedLogicalTimeInterval)
#endif
{
#ifdef IEEE_1516
  RTI::EncodedLogicalTimeInterval *elti = new GERTICO1516::EncodedLogicalTimeIntervalI(theGeRtiEncodedLogicalTimeInterval.data(), theGeRtiEncodedLogicalTimeInterval.size());

  fedTime = theLogicalTimeIntervalFactory.decode(*elti);
  fedTimeEpsilon = theLogicalTimeIntervalFactory.epsilon();
#else
  fedTime.reset(RTI::FedTimeFactory::decode((char *)theGeRtiEncodedLogicalTimeInterval.data()));
  fedTimeEpsilon.reset(RTI::FedTimeFactory::makeZero());
  fedTimeEpsilon->setEpsilon();
#endif
}

GERTICO::GeRtiLogicalTimeIntervalI::~GeRtiLogicalTimeIntervalI()
throw ()
{
}

void GERTICO::GeRtiLogicalTimeIntervalI::setZero(void)
{
  fedTime->setZero();
}

bool GERTICO::GeRtiLogicalTimeIntervalI::isZero()
{
#ifdef IEEE_1516
  return fedTime->isZero();
#else
  if(fedTime->isZero() == RTI::RTI_TRUE)
  {
    return true;
  }
  else
  {
    return false;
  }
#endif
}

bool GERTICO::GeRtiLogicalTimeIntervalI::isEpsilon()
{
#ifdef IEEE_1516
  return fedTime->isEpsilon();
#else
  if(*fedTime == *fedTimeEpsilon)
  {
    return true;
  }
  else
  {
    return false;
  }
#endif
}

GERTICO::GeRtiLogicalTimeInterval& GERTICO::GeRtiLogicalTimeIntervalI::operator-= (const GeRtiLogicalTimeInterval &value)
      throw (GeRtiFactory::InvalidLogicalTimeInterval)
{
#ifdef IEEE_1516
  GERTICO::GeRtiLogicalTimeIntervalI *geRtiLogicalTimeIntervalI = (GERTICO::GeRtiLogicalTimeIntervalI *) &value;

  fedTime = fedTime->subtract(*geRtiLogicalTimeIntervalI->fedTime);
  return *this;
#else
  const GERTICO::GeRtiLogicalTimeIntervalI& myTime = (GERTICO::GeRtiLogicalTimeIntervalI &)value;

  *fedTime -= *myTime.fedTime;
  return *this;
#endif
}

bool GERTICO::GeRtiLogicalTimeIntervalI::operator> (const GeRtiLogicalTimeInterval &value) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval)
{
#ifdef IEEE_1516
  GERTICO::GeRtiLogicalTimeIntervalI *geRtiLogicalTimeIntervalI = (GERTICO::GeRtiLogicalTimeIntervalI *) &value;

  if (fedTime->isGreaterThan(*geRtiLogicalTimeIntervalI->fedTime))
  {
    return true;
  }
  else
  {
    return false;
  }
#else
  const GERTICO::GeRtiLogicalTimeIntervalI& myTime = (GERTICO::GeRtiLogicalTimeIntervalI &)value;

  if (*fedTime > *myTime.fedTime)
  {
    return true;
  }
  else
  {
    return false;
  }
#endif
}

bool GERTICO::GeRtiLogicalTimeIntervalI::operator< (const GeRtiLogicalTimeInterval &value) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval)
{
#ifdef IEEE_1516
  GERTICO::GeRtiLogicalTimeIntervalI *geRtiLogicalTimeIntervalI = (GERTICO::GeRtiLogicalTimeIntervalI *) &value;

  if (fedTime->isLessThan(*geRtiLogicalTimeIntervalI->fedTime))
  {
    return true;
  }
  else
  {
    return false;
  }
#else
  const GERTICO::GeRtiLogicalTimeIntervalI& myTime = (GERTICO::GeRtiLogicalTimeIntervalI &)value;

  if (*fedTime < *myTime.fedTime)
  {
    return true;
  }
  else
  {
    return false;
  }
#endif
}

bool GERTICO::GeRtiLogicalTimeIntervalI::operator== (const GeRtiLogicalTimeInterval &value) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval)
{
#ifdef IEEE_1516
  GERTICO::GeRtiLogicalTimeIntervalI *geRtiLogicalTimeIntervalI = (GERTICO::GeRtiLogicalTimeIntervalI *) &value;

  if (fedTime->isEqualTo(*geRtiLogicalTimeIntervalI->fedTime))
  {
    return true;
  }
  else
  {
    return false;
  }
#else
  const GERTICO::GeRtiLogicalTimeIntervalI& myTime = (GERTICO::GeRtiLogicalTimeIntervalI &)value;

  if (*fedTime == *myTime.fedTime)
  {
    return true;
  }
  else
  {
    return false;
  }
#endif
}

bool GERTICO::GeRtiLogicalTimeIntervalI::operator>= (const GeRtiLogicalTimeInterval &value) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval)
{
#ifdef IEEE_1516
  GERTICO::GeRtiLogicalTimeIntervalI *geRtiLogicalTimeIntervalI = (GERTICO::GeRtiLogicalTimeIntervalI *) &value;

  if (fedTime->isGreaterThanOrEqualTo(*geRtiLogicalTimeIntervalI->fedTime))
  {
    return true;
  }
  else
  {
    return false;
  }
#else
  const GERTICO::GeRtiLogicalTimeIntervalI& myTime = (GERTICO::GeRtiLogicalTimeIntervalI &)value;

  if (*fedTime >= *myTime.fedTime)
  {
    return true;
  }
  else
  {
    return false;
  }
#endif
}

bool GERTICO::GeRtiLogicalTimeIntervalI::operator<= (const GeRtiLogicalTimeInterval &value) const
      throw (GeRtiFactory::InvalidLogicalTimeInterval)
{
#ifdef IEEE_1516
  GERTICO::GeRtiLogicalTimeIntervalI *geRtiLogicalTimeIntervalI = (GERTICO::GeRtiLogicalTimeIntervalI *) &value;

  if (fedTime->isLessThanOrEqualTo(*geRtiLogicalTimeIntervalI->fedTime))
  {
    return true;
  }
  else
  {
    return false;
  }
#else
  const GERTICO::GeRtiLogicalTimeIntervalI& myTime = (GERTICO::GeRtiLogicalTimeIntervalI &)value;

  if (*fedTime <= *myTime.fedTime)
  {
    return true;
  }
  else
  {
    return false;
  }
#endif
}

GERTICO::GeRtiLogicalTimeInterval& GERTICO::GeRtiLogicalTimeIntervalI::operator= (const GeRtiLogicalTimeInterval &value)
      throw (GeRtiFactory::InvalidLogicalTimeInterval)
{
  const GERTICO::GeRtiLogicalTimeIntervalI& myTimeInterval = (GERTICO::GeRtiLogicalTimeIntervalI &)value;
#ifdef IEEE_1516
  fedTime->setTo(*myTimeInterval.fedTime);
#else
  *fedTime = *myTimeInterval.fedTime;
#endif
  return *this;
}


std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> GERTICO::GeRtiLogicalTimeIntervalI::encode() const
{
#ifdef IEEE_1516
  std::auto_ptr< RTI::EncodedLogicalTimeInterval > relti;

  relti = fedTime->encode();

  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> elti(new GERTICO::GeRtiEncodedLogicalTimeIntervalI(relti->data(), relti->size()));
  return elti;
#else
  char buff[512];
  int len;

  fedTime->encode(buff);
  len = fedTime->encodedLength();

  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> elti(new GERTICO::GeRtiEncodedLogicalTimeIntervalI(buff, len));
  return elti;
#endif
}

int GERTICO::GeRtiLogicalTimeIntervalI::getPrintableLength() const
{
#ifdef IEEE_1516
  std::wstring ws = fedTime->toString();
  return ws.size() * 2 + 1;
#else
  int len;
  len = fedTime->getPrintableLength();
  return len;
#endif
}

void GERTICO::GeRtiLogicalTimeIntervalI::getPrintableString(char*buf)
{
#ifdef IEEE_1516
  std::wstring ws = fedTime->toString();

  sprintf(buf, "%ls", ws.c_str()); 
#else
  fedTime->getPrintableString(buf);
#endif
}


//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************

GERTICO::GeRtiFedTime::~GeRtiFedTime ()
{
}

#ifdef IEEE_1516
GERTICO::GeRtiFedTimeI::GeRtiFedTimeI(RTI::LogicalTimeFactory &theLogicalTimeFactory, RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory) : logicalTimeFactory(theLogicalTimeFactory), logicalTimeIntervalFactory(theLogicalTimeIntervalFactory)
#else
GERTICO::GeRtiFedTimeI::GeRtiFedTimeI()
#endif
{
#ifdef IEEE_1516
  fedTime = logicalTimeFactory.makeInitial();
#else
  fedTime.reset(RTI::FedTimeFactory::makeZero());
#endif
}

#ifdef IEEE_1516
GERTICO::GeRtiFedTimeI::GeRtiFedTimeI(RTI::LogicalTimeFactory &theLogicalTimeFactory, RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, GERTICO::GeRtiFedTime const & theTime) : logicalTimeFactory(theLogicalTimeFactory), logicalTimeIntervalFactory(theLogicalTimeIntervalFactory)
#else
GERTICO::GeRtiFedTimeI::GeRtiFedTimeI(GERTICO::GeRtiFedTime const & theTime)
#endif
{
  char *c;
  int len;

  len = theTime.encodedLength();
  c = new char[len + 1];
  theTime.encode(c);
#ifdef IEEE_1516
  GERTICO1516::EncodedLogicalTimeI *encodedLogicalTimeI = new GERTICO1516::EncodedLogicalTimeI(c, len);
  fedTime = logicalTimeFactory.decode(*encodedLogicalTimeI);
  delete encodedLogicalTimeI;
#else
  fedTime.reset(RTI::FedTimeFactory::decode(c));
#endif
  delete []c;
}

#ifdef IEEE_1516
GERTICO::GeRtiFedTimeI::GeRtiFedTimeI(RTI::LogicalTimeFactory &theLogicalTimeFactory, RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, GeRtiFedTimeI const & theTime) : logicalTimeFactory(theLogicalTimeFactory), logicalTimeIntervalFactory(theLogicalTimeIntervalFactory)
#else
GERTICO::GeRtiFedTimeI::GeRtiFedTimeI(GeRtiFedTimeI const & theTime)
#endif
{
  char *c;
  int len;

  len = theTime.encodedLength();
  c = new char[len + 1];
  theTime.encode(c);
#ifdef IEEE_1516
  std::auto_ptr< RTI::LogicalTimeInterval > lti(logicalTimeIntervalFactory.makeZero());
  GERTICO1516::EncodedLogicalTimeI *encodedLogicalTimeI = new GERTICO1516::EncodedLogicalTimeI(c, len);
  fedTime = logicalTimeFactory.decode(*encodedLogicalTimeI);
  delete encodedLogicalTimeI;
#else
  fedTime.reset(RTI::FedTimeFactory::decode(c));
#endif
  delete []c;
}

#ifdef IEEE_1516
GERTICO::GeRtiFedTimeI::GeRtiFedTimeI(RTI::LogicalTimeFactory &theLogicalTimeFactory, RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, char const *buf, size_t const &theLen) : logicalTimeFactory(theLogicalTimeFactory), logicalTimeIntervalFactory(theLogicalTimeIntervalFactory)
#else
GERTICO::GeRtiFedTimeI::GeRtiFedTimeI(char const *buf, size_t const &theLen)
#endif
{
#ifdef IEEE_1516
  GERTICO1516::EncodedLogicalTimeI *encodedLogicalTimeI = new GERTICO1516::EncodedLogicalTimeI(buf, theLen);
  fedTime = logicalTimeFactory.decode(*encodedLogicalTimeI);
  delete encodedLogicalTimeI;
#else
  fedTime.reset(RTI::FedTimeFactory::decode(buf));
#endif
}

GERTICO::GeRtiFedTimeI::~GeRtiFedTimeI()
{
}

void GERTICO::GeRtiFedTimeI::setZero()
{
#ifdef IEEE_1516
  fedTime->setInitial();
#else
  fedTime->setZero();
#endif
}

bool GERTICO::GeRtiFedTimeI::isZero()
{
#ifdef IEEE_1516
  return fedTime->isInitial();
#else
  if(fedTime->isZero() == RTI::RTI_TRUE)
    return true;
  else
    return false;
#endif
}

void GERTICO::GeRtiFedTimeI::setEpsilon()
{
#ifdef IEEE_1516
  std::auto_ptr<RTI::LogicalTimeInterval> logicalTimeInterval = logicalTimeIntervalFactory.epsilon();
  fedTime = logicalTimeFactory.makeInitial();
  fedTime->increaseBy(*logicalTimeInterval);
#else
  fedTime->setEpsilon();
#endif
}

void GERTICO::GeRtiFedTimeI::setPositiveInfinity()
{
#ifdef IEEE_1516
  fedTime->setFinal();
#else
  fedTime->setPositiveInfinity();
#endif
}

bool GERTICO::GeRtiFedTimeI::isPositiveInfinity()
{
#ifdef IEEE_1516
  return fedTime->isFinal();
#else
  if(fedTime->isPositiveInfinity() == RTI::RTI_TRUE)
    return true;
  else
    return false;
#endif
}

GERTICO::GeRtiFedTime& GERTICO::GeRtiFedTimeI::operator += (GERTICO::GeRtiLogicalTimeInterval const &theTime)
    throw (GeRtiFactory::InvalidFederationTime)
{
#ifdef IEEE_1516
  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> gETI = theTime.encode();

  RTI::EncodedLogicalTimeInterval *encodedLogicalTimeIntervalI = new GERTICO1516::EncodedLogicalTimeIntervalI(gETI->data(), gETI->size());
  std::auto_ptr<RTI::LogicalTimeInterval> logicalTimeInterval = logicalTimeIntervalFactory.decode(*encodedLogicalTimeIntervalI);
  delete encodedLogicalTimeIntervalI;
  fedTime->increaseBy(*logicalTimeInterval);
  return *this;
#else
  const GERTICO::GeRtiFedTimeI& myTime = (GERTICO::GeRtiFedTimeI &)theTime;

  *fedTime += *myTime.fedTime;
  return *this;
#endif
}

GERTICO::GeRtiFedTime& GERTICO::GeRtiFedTimeI::operator -= (GERTICO::GeRtiLogicalTimeInterval const &theTime)
    throw (
      GeRtiFactory::InvalidFederationTime)
{
#ifdef IEEE_1516
  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> gETI = theTime.encode();

  RTI::EncodedLogicalTimeInterval *encodedLogicalTimeInterval = new GERTICO1516::EncodedLogicalTimeIntervalI(gETI->data(), gETI->size());
  std::auto_ptr<RTI::LogicalTimeInterval> logicalTimeInterval = logicalTimeIntervalFactory.decode(*encodedLogicalTimeInterval);
  delete encodedLogicalTimeInterval;
  fedTime->decreaseBy(*logicalTimeInterval);
  return *this;
#else
  const GERTICO::GeRtiFedTimeI& myTime = (GERTICO::GeRtiFedTimeI &)theTime;

  *fedTime -= *myTime.fedTime;
  return *this;
#endif
}

std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> GERTICO::GeRtiFedTimeI::operator- (GERTICO::GeRtiFedTime const & subtrahend) const
      throw (GeRtiFactory::InvalidFederationTime)
{
  const GERTICO::GeRtiFedTimeI& myTime = (GERTICO::GeRtiFedTimeI &)subtrahend;
#ifdef IEEE_1516
  std::auto_ptr<RTI::LogicalTimeInterval> lti = fedTime->subtract(*myTime.fedTime);
  std::auto_ptr<RTI::EncodedLogicalTimeInterval> elti = lti->encode();

  GERTICO::GeRtiEncodedLogicalTimeIntervalI *gelti = new GERTICO::GeRtiEncodedLogicalTimeIntervalI(elti->data(), elti->size());
  std::auto_ptr<GeRtiLogicalTimeInterval> glti(new GeRtiLogicalTimeIntervalI(logicalTimeIntervalFactory, *gelti));
  delete gelti;

  return glti;
#else
  char buff[512];
  std::auto_ptr<RTI::FedTime> tmpFedTime(RTI::FedTimeFactory::makeZero());

  *tmpFedTime = *fedTime;
  *tmpFedTime -= *myTime.fedTime;

  tmpFedTime->encode(buff);

  GERTICO::GeRtiEncodedLogicalTimeIntervalI *gelti = new GERTICO::GeRtiEncodedLogicalTimeIntervalI(buff, tmpFedTime->encodedLength());
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> glti(new GeRtiLogicalTimeIntervalI(*gelti));
  delete gelti;

  return glti;
#endif
}

bool GERTICO::GeRtiFedTimeI::operator <= (const GERTICO::GeRtiFedTime& theTime) const
    throw (
      GeRtiFactory::InvalidFederationTime)
{
#ifdef IEEE_1516
  char *c;
  int len;

  len = theTime.encodedLength();
  c = new char[len + 1];
  theTime.encode(c);
  RTI::EncodedLogicalTime *encodedLogicalTimeI = new GERTICO1516::EncodedLogicalTimeI(c, len);
  std::auto_ptr<RTI::LogicalTime> logicalTime = logicalTimeFactory.decode(*encodedLogicalTimeI);
  delete encodedLogicalTimeI;
  delete []c;
  return fedTime->isLessThanOrEqualTo(*logicalTime);
#else
  const GERTICO::GeRtiFedTimeI& myTime = (GERTICO::GeRtiFedTimeI &)theTime;

  if ((*fedTime <= *myTime.fedTime) == RTI::RTI_TRUE)
    return true;
  else
    return false;
#endif
}

bool GERTICO::GeRtiFedTimeI::operator < (const GERTICO::GeRtiFedTime& theTime) const
    throw (
      GeRtiFactory::InvalidFederationTime)
{
#ifdef IEEE_1516
  char *c;
  int len;

  len = theTime.encodedLength();
  c = new char[len + 1];
  theTime.encode(c);

  double netnum;

#if defined(_M_IX86) || defined(i386)
  *(((int*)&netnum)+1) = htonl(*((int*)c));
  *((int*)&netnum) = htonl(*(((int*)c)+1));

#else
  memcpy((char*)&netnum, c, sizeof(netnum));
#endif

  RTI::EncodedLogicalTime *encodedLogicalTimeI = new GERTICO1516::EncodedLogicalTimeI(c, len);
  std::auto_ptr<RTI::LogicalTime> logicalTime = logicalTimeFactory.decode(*encodedLogicalTimeI);
  delete encodedLogicalTimeI;
  delete []c;
  return fedTime->isLessThan(*logicalTime);
#else
  const GERTICO::GeRtiFedTimeI& myTime = (GERTICO::GeRtiFedTimeI &)theTime;

  if ((*fedTime < *myTime.fedTime) == RTI::RTI_TRUE)
    return true;
  else
    return false;
#endif
}

bool GERTICO::GeRtiFedTimeI::operator >= (const GERTICO::GeRtiFedTime& theTime) const
    throw (
      GeRtiFactory::InvalidFederationTime)
{
#ifdef IEEE_1516
  char *c;
  int len;

  len = theTime.encodedLength();
  c = new char[len + 1];
  theTime.encode(c);
  RTI::EncodedLogicalTime *encodedLogicalTimeI = new GERTICO1516::EncodedLogicalTimeI(c, len);
  std::auto_ptr<RTI::LogicalTime> logicalTime = logicalTimeFactory.decode(*encodedLogicalTimeI);
  delete encodedLogicalTimeI;
  delete []c;
  return fedTime->isGreaterThanOrEqualTo(*logicalTime);
#else
  const GERTICO::GeRtiFedTimeI& myTime = (GERTICO::GeRtiFedTimeI &)theTime;

  if ((*fedTime >= *myTime.fedTime) == RTI::RTI_TRUE)
    return true;
  else
    return false;
#endif
}

bool GERTICO::GeRtiFedTimeI::operator > (const GERTICO::GeRtiFedTime& theTime) const
    throw (
      GeRtiFactory::InvalidFederationTime)
{
#ifdef IEEE_1516
  char *c;
  int len;

  len = theTime.encodedLength();
  c = new char[len + 1];
  theTime.encode(c);
  RTI::EncodedLogicalTime *encodedLogicalTimeI = new GERTICO1516::EncodedLogicalTimeI(c, len);
  std::auto_ptr<RTI::LogicalTime> logicalTime = logicalTimeFactory.decode(*encodedLogicalTimeI);
  delete encodedLogicalTimeI;
  delete []c;
  return fedTime->isGreaterThan(*logicalTime);
#else
  const GERTICO::GeRtiFedTimeI& myTime = (GERTICO::GeRtiFedTimeI &)theTime;

  if ((*fedTime > *myTime.fedTime) == RTI::RTI_TRUE)
    return true;
  else
    return false;
#endif
}

bool GERTICO::GeRtiFedTimeI::operator == (const GERTICO::GeRtiFedTime& theTime) const
    throw (
      GeRtiFactory::InvalidFederationTime)
{
#ifdef IEEE_1516
  char *c;
  int len;

  len = theTime.encodedLength();
  c = new char[len + 1];
  theTime.encode(c);
  RTI::EncodedLogicalTime *encodedLogicalTimeI = new GERTICO1516::EncodedLogicalTimeI(c, len);
  std::auto_ptr<RTI::LogicalTime> logicalTime = logicalTimeFactory.decode(*encodedLogicalTimeI);
  delete encodedLogicalTimeI;
  delete []c;
  return fedTime->isEqualTo(*logicalTime);
#else
  const GERTICO::GeRtiFedTimeI& myTime = (GERTICO::GeRtiFedTimeI &)theTime;

  if ((*fedTime == *myTime.fedTime) == RTI::RTI_TRUE)
    return true;
  else
    return false;
#endif
}

GERTICO::GeRtiFedTime& GERTICO::GeRtiFedTimeI::operator= (const GERTICO::GeRtiFedTime &theTime)
      throw (GeRtiFactory::InvalidFederationTime)
{
  const GERTICO::GeRtiFedTimeI& myTime = (GERTICO::GeRtiFedTimeI &)theTime;
#ifdef IEEE_1516
  fedTime->setTo(*myTime.fedTime);
#else
  *fedTime = *myTime.fedTime;
#endif
  return *this;
}

//-----------------------------------------------------------------
// Implementation operators
//-----------------------------------------------------------------

//return bytes needed to encode
int GERTICO::GeRtiFedTimeI::encodedLength() const
{
#ifdef IEEE_1516
  std::auto_ptr< RTI::EncodedLogicalTime > elc = fedTime->encode();
  return elc->size();
#else
  return fedTime->encodedLength();
#endif
}

//encode into suppled buffer
void
GERTICO::GeRtiFedTimeI::encode(char *buff) const
{
#ifdef IEEE_1516
  int len;
  std::auto_ptr< RTI::EncodedLogicalTime > elc = fedTime->encode();
  len = elc->size();
  memcpy(buff, elc->data(), len);
#else
  fedTime->encode(buff);
#endif
}

// stream operators
/*
std::ostream& operator << (std::ostream &out, const GERTICO::GeRtiFedTime &e)
{
  GERTICO::GeRtiFedTimeI myTime(e);

  myTime.getPrintableString (ch);
  return out << ch;
}
*/

int GERTICO::GeRtiFedTimeI::getPrintableLength() const
{
#ifdef IEEE_1516
  std::wstring ws = fedTime->toString();
  return ws.size() * 2 + 1;
#else
  int len;
  len = fedTime->getPrintableLength();
  return len;
#endif
}

void GERTICO::GeRtiFedTimeI::getPrintableString(char* buf)
{
#ifdef IEEE_1516
//  const wchar_t *ptr;
  std::wstring ws = fedTime->toString();
//  unsigned int i;
//  unsigned int len;

//  len = ws.size();
//  ptr = ws.c_str();
//  for (i = 0; i < len; i++)
//  {
//    buf[i] = ptr[i];
//  }
//  buf[len] = '\0';
  sprintf(buf,"%ls",ws.c_str()); 
#else
  fedTime->getPrintableString(buf);
#endif
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************

#ifdef IEEE_1516
GERTICO::GeRtiLogicalTimeIntervalFactory::GeRtiLogicalTimeIntervalFactory(RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory) : logicalTimeIntervalFactory(theLogicalTimeIntervalFactory)
#else
GERTICO::GeRtiLogicalTimeIntervalFactory::GeRtiLogicalTimeIntervalFactory(void)
#endif
{
}

GERTICO::GeRtiLogicalTimeInterval* GERTICO::GeRtiLogicalTimeIntervalFactory::makeZero()
      throw(GeRtiFactory::MemoryExhausted)
{
  GERTICO::GeRtiLogicalTimeIntervalI *lti;
  unsigned int flag = 0;

#ifdef IEEE_1516
  lti = new GERTICO::GeRtiLogicalTimeIntervalI(logicalTimeIntervalFactory, flag);
#else
  lti = new GERTICO::GeRtiLogicalTimeIntervalI(0);
#endif

  return lti;
}

GERTICO::GeRtiLogicalTimeInterval* GERTICO::GeRtiLogicalTimeIntervalFactory::epsilon()
      throw(GeRtiFactory::MemoryExhausted)
{
  GERTICO::GeRtiLogicalTimeIntervalI *lti;
  unsigned int flag = 1;

#ifdef IEEE_1516
  lti = new GERTICO::GeRtiLogicalTimeIntervalI(logicalTimeIntervalFactory, flag);
#else
  lti = new GERTICO::GeRtiLogicalTimeIntervalI(1);
#endif

  return lti;
}

GERTICO::GeRtiLogicalTimeInterval* GERTICO::GeRtiLogicalTimeIntervalFactory::decode(GERTICO::GeRtiEncodedLogicalTimeInterval &theGeRtiEncodedLogicalTimeInterval)
      throw(GeRtiFactory::MemoryExhausted)
{
  GERTICO::GeRtiLogicalTimeIntervalI *lti;
  unsigned int flag = 1;

#ifdef IEEE_1516
  lti = new GERTICO::GeRtiLogicalTimeIntervalI(logicalTimeIntervalFactory, theGeRtiEncodedLogicalTimeInterval);
  char buff[512];
  lti->getPrintableString(buff);

#else
  lti = new GERTICO::GeRtiLogicalTimeIntervalI(theGeRtiEncodedLogicalTimeInterval);
#endif

  return lti;
}

//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************

#ifdef IEEE_1516
GERTICO::GeRtiFedTimeFactory::GeRtiFedTimeFactory(RTI::LogicalTimeFactory &theLogicalTimeFactory, RTI::LogicalTimeIntervalFactory &theLogicalTimeIntervalFactory) : logicalTimeFactory(theLogicalTimeFactory), logicalTimeIntervalFactory(theLogicalTimeIntervalFactory)
{
}
#endif

GERTICO::GeRtiFedTime *
GERTICO::GeRtiFedTimeFactory::makeZero()
  throw(GeRtiFactory::MemoryExhausted)
{
#ifdef IEEE_1516
  return new GERTICO::GeRtiFedTimeI(logicalTimeFactory, logicalTimeIntervalFactory);
#else
  return new GERTICO::GeRtiFedTimeI();
#endif
}

GERTICO::GeRtiFedTime *
GERTICO::GeRtiFedTimeFactory::decode(const char* buff)
  throw(GeRtiFactory::MemoryExhausted)
{
  unsigned int len;
  len = 8;
#ifdef IEEE_1516
  GERTICO::GeRtiFedTimeI *geRtiFedTimeI = new GERTICO::GeRtiFedTimeI(logicalTimeFactory, logicalTimeIntervalFactory, buff, len);
#else
  GERTICO::GeRtiFedTimeI *geRtiFedTimeI = new GERTICO::GeRtiFedTimeI(buff, len);
#endif

  return geRtiFedTimeI;
}
