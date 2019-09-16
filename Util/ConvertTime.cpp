/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** ConvertTime.cpp
**
*******************************************************************************/

#include "Util/Mapper.h"
#include "ConvertTime.h"

#define MIN_SLEEP_TIME 10
#define MAX_SLEEP_TIME 1000000

/*
 */
GERTICO::ConvertTime::ConvertTime (void)
{
}

/*
 * Destructor.
 */
GERTICO::ConvertTime::~ConvertTime (void)
{
}

/*
 * Convert from RTI::FedTime to GeRtiFactory::Time.
 */
void GERTICO::ConvertTime::mapIt (GeRtiFactory::Time &out, const GERTICO::GeRtiFedTime &in)
{
  CORBA::ULong len = in.encodedLength ();
  char *tmpBuff;

  tmpBuff = new char[len];

  in.encode (tmpBuff);
  out.length (len);

  for (CORBA::ULong i = 0; i < len; i++)
  {
    out[i] = tmpBuff[i];
  }

  delete[] tmpBuff;
}

// ---------------------------------------------------------------------------
// Convert from GeRtiFactory::Time to RTI::FedTime.
// NB: out must be a valid memory pointer or NULL.
// ---------------------------------------------------------------------------
void GERTICO::ConvertTime::mapItGeRtiFedTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiFedTime **out, const GeRtiFactory::Time &in)
{
  CORBA::ULong len = in.length ();
  unsigned char *tmpBuff;

  /*
   * Will release any old memory.
   */
  if (*out)
  {
    delete *out;
    *out = NULL;
  }

  if (len == 0)
  {
    *out = NULL;
    return;
  }

  tmpBuff = new unsigned char[len];

  for (CORBA::ULong i = 0; i < len; i++)
  {
    tmpBuff[i] = in[i];
  }

  *out = theGeRtiFedTimeFactory.decode((char *)tmpBuff);
  delete[] tmpBuff;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval, const GeRtiFactory::Time &theTime)
{
  CORBA::ULong length;

  length = theTime.length();

  if (length)
  {
    std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> logicalTimeInterval;
    unsigned char *tmpBuff;
    tmpBuff = new unsigned char[length];

    for (CORBA::ULong i = 0; i < length; i++)
    {
      tmpBuff[i] = theTime[i];
    }

    std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeIntervalI> elti(new GERTICO::GeRtiEncodedLogicalTimeIntervalI(tmpBuff, length));

    logicalTimeInterval.reset(theLogicalTimeIntervalFactory.decode(*elti));

    theLogicalTimeInterval = *logicalTimeInterval;
    delete[] tmpBuff;
  }
  else
  {
    theLogicalTimeInterval.setZero();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(GeRtiFactory::Time &theTime, const GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval)
{
  CORBA::ULong length;
  char *tmpBuff;
  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> elti;
  size_t size;

  elti = theLogicalTimeInterval.encode();

  tmpBuff = (char *)elti->data();
  size = elti->size();

  GERTICO::Mapper::mapULongSizet(length, size);
  theTime.length(length);

  for (CORBA::ULong i = 0; i < length; i++)
  {
    theTime[i] = tmpBuff[i];
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval, char *theString)
{
//  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> elti;
  char buf[128];
  size_t length;
  unsigned int ch;
  unsigned long i;
  unsigned long j;

  length = strlen(theString);
  for (i = 0, j = 0; i < length; i += 2, j++)
  {
    sscanf(&theString[i], "%02x", &ch);
    buf[j] = ch;
  }
  length /= 2;

  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> elti(new GERTICO::GeRtiEncodedLogicalTimeIntervalI(buf, length));
  size_t sl = elti->size();

  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> lti(theLogicalTimeIntervalFactory.decode(*elti));
  theLogicalTimeInterval = *lti;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ConvertTime::mapGeRtiLogicalTimeInterval(char *theString, GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval)
{
  CORBA::ULong i;
  CORBA::ULong length;
  unsigned char *tmpBuff;
  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> elti;
  size_t size;

  elti = theLogicalTimeInterval.encode();

  tmpBuff = (unsigned char *)elti->data();
  size = elti->size();

  GERTICO::Mapper::mapULongSizet(length, size);
  for (i = 0; i < length; i++)
  {
    sprintf(&theString[2 * i], "%02x", (unsigned char) tmpBuff[i]);
  }
  theString[2 * length] = '\0';
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ConvertTime::mapIt(GeRtiFactory::Time &theTime, char *theString)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong length;
  size_t size;
  unsigned int ch;

  size = strlen(theString);
  GERTICO::Mapper::mapULongSizet(length, size);
  theTime.length(length/2);
  for (i = 0, j = 0; i < length; i += 2, j++)
  {
    sscanf(&theString[i], "%02x", &ch);
    theTime[j] = ch;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ConvertTime::mapIt(char *theString, const GeRtiFactory::Time &theTime)
{
  unsigned long i;
  unsigned long length;

  length = theTime.length();
  for (i = 0; i < length; i++)
  {
    sprintf(&theString[2 * i], "%02x", theTime[i]);
  }
}

// ---------------------------------------------------------------------------
// Convert from GeRtiFactory::Time to RTI::FedTime.
// ---------------------------------------------------------------------------
void GERTICO::ConvertTime::mapGeRtiFedTimeAutoPtr(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, std::auto_ptr<GERTICO::GeRtiFedTime> &out, const GeRtiFactory::Time &in)
{
  CORBA::ULong len = in.length ();
  unsigned char *tmpBuff;

  /*
   * Will release any old memory.
   */
  if (len == 0)
  {
    out.reset();
    return;
  }

  tmpBuff = new unsigned char[len];

  for (CORBA::ULong i = 0; i < len; i++)
  {
    tmpBuff[i] = in[i];
  }

  out.reset(theGeRtiFedTimeFactory.decode((char *)tmpBuff));
  delete[] tmpBuff;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ConvertTime::mapGeRtiFedTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiFedTime &theFedTime, char *theString)
{
  char buf[128];
  size_t length;
  unsigned int ch;
  unsigned long i;
  unsigned long j;

  length = strlen(theString);
  for (i = 0, j = 0; i < length; i += 2, j++)
  {
    sscanf(&theString[i], "%02x", &ch);
    buf[j] = ch;
  }

  std::auto_ptr<GERTICO::GeRtiFedTime> l(theGeRtiFedTimeFactory.decode(buf));
  theFedTime = *l;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::ConvertTime::mapGeRtiFedTime(char *theString, GERTICO::GeRtiFedTime &theGeRtiFedTime)
{
  char buf[128];
  unsigned long i;
  unsigned long length;

  length = theGeRtiFedTime.encodedLength();
  theGeRtiFedTime.encode(buf);
  for (i = 0; i < length; i++)
  {
    sprintf(&theString[2 * i], "%02x", (unsigned char) buf[i]);
  }
  theString[2 * length] = '\0';
}
