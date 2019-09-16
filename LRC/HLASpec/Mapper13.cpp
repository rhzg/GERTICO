/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**
** MODULE
** Mapper13 - Mapper implementation for RTI 1.3 NG V3 CORBA
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Mapper13.cpp,v $
Revision 1.6  2010/05/17 07:57:46  mul
Add logical time interval.

Revision 1.5  2008/03/06 09:50:26  mul
Change wrong length call.

Revision 1.4  2007/11/12 12:50:55  mul
Changes for vc8.

Revision 1.3  2007/09/05 15:46:02  mul
Changes for ieee1516.

Revision 1.2  2007/05/09 13:12:24  mul
Add generic time mapper functions.

Revision 1.1  2007/05/03 14:46:17  mul
Mapper for HLA 1.3 types.

 
**
*******************************************************************************/


// C++ standard library
#include <stdexcept>
// project include files
#include "Mapper13.h"
#include "ace/OS_NS_wchar.h"
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Mapper13::Mapper13(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Mapper13::~Mapper13(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapAttributeHandleSet
(
  RTI::AttributeHandleSet &out,
  const GeRtiFactory::Handles &in
)
{
  CORBA::ULong i;
  CORBA::ULong length;

  length = in.length ();
  for (i = 0; i < length; i++)
  {
    out.add (in[i]);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapAttributeHandleValuePairSet (
  RTI::AttributeHandleValuePairSet &out,
  const GeRtiFactory::HandleValues &in,
  const int &theGrouping,
  const bool theBestEffort
)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi = in.length ();
  CORBA::ULong lengthj;

  // For each incoming attribute.
  for (i = 0; i < lengthi; i++)
  {
    switch (theGrouping)
    {
      case 0:
      {
        if (in[i].timestampOrder == 1)
        {
          continue;
        }
        break;
      }
      case 1:
      {
        if (in[i].timestampOrder == 0)
        {
          continue;
        }
        break;
      }
    }
    if (theBestEffort)
    {
      if (in[i].bestEffort == 0)
      {
        continue;
      }
    }
    else
    {
      if (in[i].bestEffort == 1)
      {
        continue;
      }
    }
    // Copy the attribute value.
    lengthj = in[i].value.length ();
    char* buff = new char[lengthj];
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = in[i].value[j];
    }
    out.add (in[i].id, buff, lengthj);
    delete[] buff;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapEventRetractionHandle
(
  RTI::EventRetractionHandle &out,
  const GeRtiFactory::ERHandle &in
)
{
  out.theSerialNumber = in.theSerialNumber;
  out.sendingFederate = in.sendingFederate;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapFedTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, std::auto_ptr<GERTICO::GeRtiFedTime> &out, const RTI::FedTime &in)
{
  int length = in.encodedLength();
  char* buff = new char[length];

  in.encode(buff);
  std::auto_ptr<GERTICO::GeRtiFedTime> tmp(theGeRtiFedTimeFactory.decode(buff));
  out = tmp;
  delete[] buff;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapFedTime(RTI::FedTime &out, const std::auto_ptr<GERTICO::GeRtiFedTime> &in)
{
  int length = in->encodedLength();
  char* buff = new char[length];

  in->encode(buff);
  out = *(RTI::FedTimeFactory::decode(buff));
  delete[] buff;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapFedTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiFedTime &out, const RTI::FedTime &in)
{
  int length = in.encodedLength();
  char* buff = new char[length];

  in.encode(buff);
  std::auto_ptr<GERTICO::GeRtiFedTime> tmp(theGeRtiFedTimeFactory.decode(buff));
  out = *tmp;
  delete[] buff;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapFedTime(RTI::FedTime &out, const GERTICO::GeRtiFedTime &in)
{
  int length = in.encodedLength();
  char* buff = new char[length];

  in.encode(buff);
  out = *(RTI::FedTimeFactory::decode(buff));
  delete[] buff;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapParameterHandleValuePairSet (
  RTI::ParameterHandleValuePairSet &out,
  const GeRtiFactory::HandleValues &in
)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi = in.length();
  CORBA::ULong lengthj;

  for (i = 0; i < lengthi; i++)
  {
    lengthj = in[i].value.length ();
    char* buff = new char[lengthj];
    for (j = 0; j < lengthj; j++)
    {
      buff[j] = in[i].value[j];
    }
    out.add (in[i].id, buff, lengthj);
    delete[] buff;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapUserSuppliedTag
(
  char **out,
  const GeRtiFactory::UserSuppliedTag &in
)
{
  CORBA::ULong i;
  CORBA::ULong length = in.length();
  *out = new char[length + 1];
  for (i = 0; i < length; i++)
  {
    (*out)[i] = in[i];
  }

  (*out)[length] = '\0';
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapAttributeHandleSet
(
  GeRtiFactory::Handles &out,
  const RTI::AttributeHandleSet &in
)
{
  CORBA::ULong i;
  CORBA::ULong length;

  length = in.size ();
  out.length (length);
  for (i = 0; i < length; i++)
  {
    out[i] = in.getHandle (i);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapFederateHandleSet
(
  GeRtiFactory::Handles &out,
  const RTI::FederateHandleSet &in
)
{
  CORBA::ULong i;
  CORBA::ULong length;

  length = in.size ();
  out.length (length);
  for (i = 0; i < length; i++)
  {
    out[i] = in.getHandle (i);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, GERTICO::GeRtiLogicalTimeInterval &out, const RTI::FedTime &in)
{
  int length = in.encodedLength();
  char* buff = new char[length];

  in.encode(buff);
  GERTICO::GeRtiEncodedLogicalTimeInterval *elti = new GERTICO::GeRtiEncodedLogicalTimeIntervalI(buff, length);
  std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> tmp(theGeRtiLogicalTimeIntervalFactory.decode(*elti));
  out = *tmp;
  delete[] buff;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, RTI::FedTime &out, const GERTICO::GeRtiLogicalTimeInterval &in)
{
  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> elti;

  elti = in.encode();
  out = *(RTI::FedTimeFactory::decode((char *)elti->data()));
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapEventRetractionHandle (GeRtiFactory::ERHandle &out, const RTI::EventRetractionHandle &in)
{
  out.theSerialNumber = in.theSerialNumber;
  out.sendingFederate = in.sendingFederate;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapAttributeHandleValuePairSet
(
  GeRtiFactory::HandleValues &out,
  const RTI::AttributeHandleValuePairSet &in
)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  RTI::ULong lengthjr;

  lengthi = in.size ();
  out.length (lengthi);
  for (i = 0; i < lengthi; i++)
  {
    out[i].id = in.getHandle (i);
    // Will be set in gerti.
    out[i].timestampOrder = 0;
    lengthj = in.getValueLength (i);
    out[i].value.length (lengthj);
    lengthjr = lengthj;
    char* buff = new char[lengthj];
    in.getValue (i, buff, lengthjr);
    for (j = 0; j < lengthj; j++)
    {
      out[i].value[j] = buff[j];
    }
	delete[] buff;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper13::mapParameterHandleValuePairSet
(
  GeRtiFactory::HandleValues &out,
  const RTI::ParameterHandleValuePairSet &in
)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  RTI::ULong lengthjr;

  lengthi = in.size ();
  out.length (lengthi);
  for (i = 0; i < lengthi; i++)
  {
    out[i].id = in.getHandle (i);
    lengthj = in.getValueLength (i);
    out[i].value.length (lengthj);
    lengthjr = lengthj;
    char* buff = new char[lengthj];
    in.getValue (i, buff, lengthjr);
    for (j = 0; j < lengthj; j++)
    {
      out[i].value[j] = buff[j];
    }
	delete[] buff;
  }
}
