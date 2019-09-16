/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**
** MODULE
** Mapper1516 - Mapper implementation for RTI 1.3 NG V3 CORBA
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Mapper1516.cpp,v $
Revision 1.10  2010/05/17 08:01:40  mul
Add logical time interval.

Revision 1.9  2010/02/25 07:32:58  mul
Changes for single callbacks.

Revision 1.8  2008/11/19 14:08:03  mul
Changes for logging.

Revision 1.7  2008/03/06 09:59:22  mul
Changes for linux.

Revision 1.6  2008/01/30 12:58:49  mul
Changes for ieee1516.

Revision 1.5  2007/11/22 15:00:46  mul
Changes for vc8.

Revision 1.4  2007/10/08 07:55:30  mul
Change memory management.

Revision 1.3  2007/09/25 08:24:08  mul
Changes for ddm.

Revision 1.2  2007/09/05 15:41:47  mul
Changes for ieee1516.

Revision 1.1  2007/06/26 08:25:28  mul
New files for ieee1516.


**
*******************************************************************************/

// C++ standard library
#include <stdexcept>
#include <iostream>
#ifndef _WIN32
#include <netinet/in.h>
#endif
// project include files
#include "Mapper1516.h"
#include "Util/GeRtiFedTimeI.h"
#include "ace/OS_NS_wchar.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EncodedLogicalTimeI::EncodedLogicalTimeI(void *theTimeData, unsigned int const &theLength) : _value(theTimeData, theLength)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EncodedLogicalTimeI::~EncodedLogicalTimeI() throw ()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void const *GERTICO::EncodedLogicalTimeI::data() const
{
  return _value.data();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
size_t GERTICO::EncodedLogicalTimeI::size() const
{
  return _value.size();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EncodedLogicalTimeIntervalI::EncodedLogicalTimeIntervalI(void *theTimeData, unsigned int const &theLength) : _value(theTimeData, theLength)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::EncodedLogicalTimeIntervalI::~EncodedLogicalTimeIntervalI() throw ()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void const *GERTICO::EncodedLogicalTimeIntervalI::data() const
{
  return _value.data();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
size_t GERTICO::EncodedLogicalTimeIntervalI::size() const
{
  return _value.size();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MessageRetractionHandleI::MessageRetractionHandleI(GeRtiFactory::GeRtiHandle const &theSendingFederate, GeRtiFactory::GeRtiHandle const &theSerialNumber)
{
  sendingFederate = theSendingFederate;
  serialNumber = theSerialNumber;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MessageRetractionHandleI::~MessageRetractionHandleI(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::MessageRetractionHandleI::MessageRetractionHandleI(MessageRetractionHandleI const &theMessageRetractionHandleI)
{
  theMessageRetractionHandleI.getSendingFederate(sendingFederate);
  theMessageRetractionHandleI.getSerialNumber(serialNumber);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::MessageRetractionHandleI::getSendingFederate(GeRtiFactory::GeRtiHandle &theSendingFederate) const
{
  theSendingFederate = sendingFederate;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::MessageRetractionHandleI::getSerialNumber(GeRtiFactory::GeRtiHandle &theSerialNumber) const
{
  theSerialNumber = serialNumber;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Mapper1516::Mapper1516(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Mapper1516::~Mapper1516(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapAttributeHandle(GeRtiFactory::GeRtiHandle &out, RTI::AttributeHandle const &in)
{
  out = in.getImplementation();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapAttributeHandle(RTI::AttributeHandle &out, GeRtiFactory::GeRtiHandle const &in)
{
  RTI::AttributeHandle tmp(in);
  out = tmp;
}

void GERTICO::Mapper1516::printAttributeHandleSet (const RTI::AttributeHandleSet& theAttributeHandleSet)
{
  CORBA::ULong ul;
  RTI::AttributeHandleSet::const_iterator i;

  for(i=theAttributeHandleSet.begin();i!=theAttributeHandleSet.end();i++)
  {
    ul = (*i).getImplementation();
  }
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapAttributeHandleSet
(
  GeRtiFactory::Handles &out,
  RTI::AttributeHandleSet const &in
)
{
  CORBA::ULong i;
  CORBA::ULong length;
  RTI::AttributeHandleSet::const_iterator itAttributeHandleSet;

  length = in.size ();
  out.length (length);

  for (i = 0, itAttributeHandleSet = in.begin(); itAttributeHandleSet != in.end(); i++, itAttributeHandleSet++)
  {
    mapAttributeHandle(out[i], *itAttributeHandleSet);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapAttributeHandleSet(RTI::AttributeHandleSet &out, GeRtiFactory::Handles const &in)
{
  CORBA::ULong i;
  CORBA::ULong length;
  RTI::AttributeHandle attributeHandle;

  out.clear();

  length = in.length();
  for (i = 0; i < length; i++)
  {
    mapAttributeHandle(attributeHandle, in[i]);
    out.insert(attributeHandle);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapAttributeHandleSetRegionHandleSetPairVector(GERTICO::HandleSetMap &out, RTI::AttributeHandleSetRegionHandleSetPairVector const &in)
{
  GERTICO::AttributeHandleSetRegionHandleSetPair attributeHandleSetRegionHandleSetPair;
  GERTICO::AttHandleSetRegionHandleSetPairVector::const_iterator itAttributeHandleSetRegionHandleSetPairVector;
  GERTICO::HandleSetMap::iterator itHandleSetMap;
  RTI::AttributeHandleSet *attributes;
  RTI::AttributeHandleSet::iterator itAttributeHandleSet;
  RTI::RegionHandleSet *regions;
  RTI::RegionHandleSet::iterator itRegionHandleSet;
GeRtiFactory::GeRtiHandle a;
GeRtiFactory::GeRtiHandle r;

  for (itAttributeHandleSetRegionHandleSetPairVector = in.begin(); itAttributeHandleSetRegionHandleSetPairVector != in.end(); itAttributeHandleSetRegionHandleSetPairVector++)
  {
    attributeHandleSetRegionHandleSetPair = *itAttributeHandleSetRegionHandleSetPairVector;
    attributes = &attributeHandleSetRegionHandleSetPair.first;
    for (itAttributeHandleSet = attributes->begin(); itAttributeHandleSet != attributes->end(); itAttributeHandleSet++)
    {
      mapAttributeHandle(a, *itAttributeHandleSet);
      regions = &attributeHandleSetRegionHandleSetPair.second;
      for (itRegionHandleSet = regions->begin(); itRegionHandleSet != regions->end(); itRegionHandleSet++)
      {
        mapRegionHandle(r, *itRegionHandleSet);
        itHandleSetMap = out.find(a);
        if (itHandleSetMap != out.end())
        {
          GERTICO::HandleSet *handleSetPtr;
          handleSetPtr = &itHandleSetMap->second;
          handleSetPtr->insert(r);
        }
        else
        {
          GERTICO::HandleSet handleSet;
          handleSet.insert(r);
          out[a] = handleSet;
        }
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapAttributeHandleValueMap(GeRtiFactory::HandleValues &out, RTI::AttributeHandleValueMap const &in)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong length;
  GeRtiFactory::GeRtiHandle attributeHandle;
  RTI::AttributeHandleValueMap::const_iterator itAttributeHandleValueMap;
  char *data;

  length = in.size ();
  out.length (length);
  for (i = 0, itAttributeHandleValueMap = in.begin(); itAttributeHandleValueMap != in.end(); i++, itAttributeHandleValueMap++)
  {
    mapAttributeHandle(attributeHandle, itAttributeHandleValueMap->first);

    length = itAttributeHandleValueMap->second.size();
    data = (char *)itAttributeHandleValueMap->second.data();
    out[i].id = attributeHandle;
    out[i].timestampOrder = 0;
    out[i].bestEffort = 0;
    out[i].value.length(length);
    for (j = 0; j < length; j++)
    {
      out[i].value[j] = data[j];
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapAttributeHandleValueMap(GeRtiFactory::HandleValues &out, const GeRtiFactory::HandleValues &in, const int &theGrouping, const bool theBestEffort)
{
  CORBA::ULong i;
  CORBA::ULong j = 0;
  CORBA::ULong lengthi = in.length ();

  out.length(lengthi);
  out.length(0);
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

    out.length(j + 1);
    // Copy the attribute value.
    out[j] = in[i];
    j += 1;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapDimensionHandle(GeRtiFactory::GeRtiHandle &out, RTI::DimensionHandle const &in)
{
  out = in.getImplementation();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapDimensionHandle(RTI::DimensionHandle &out, GeRtiFactory::GeRtiHandle const &in)
{
  RTI::DimensionHandle tmp(in);
  out = tmp;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapDimensionHandleSet(GERTICO::HandleSet &out, RTI::DimensionHandleSet const &in)
{
  CORBA::ULong i;
  CORBA::ULong length;
  GeRtiFactory::GeRtiHandle dimensionHandle;
  RTI::DimensionHandleSet::const_iterator itDimensionHandleSet;

  length = in.size ();
  for (i = 0, itDimensionHandleSet = in.begin(); itDimensionHandleSet != in.end(); i++, itDimensionHandleSet++)
  {
    mapDimensionHandle(dimensionHandle, *itDimensionHandleSet);
    out.insert(dimensionHandle);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapDimensionHandleSet(RTI::DimensionHandleSet &out, GeRtiFactory::Handles const &in)
{
  CORBA::ULong i;
  CORBA::ULong length;
  RTI::DimensionHandle dimensionHandle;

  length = in.length();
  for (i = 0; i < length; i++)
  {
    mapDimensionHandle(dimensionHandle, in[i]);
    out.insert(dimensionHandle);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapEncodedLogicalTime(RTI::EncodedLogicalTime **out, const GERTICO::GeRtiFedTime &in)
{
  char *buff;

//  if (in.get() == NULL)
//  {
//    *out = NULL;
//    return;
//  }

  buff = new char[in.encodedLength()];
  in.encode(buff);

  GERTICO::EncodedLogicalTimeI *encodedLogicalTimeI = new GERTICO::EncodedLogicalTimeI(buff, in.encodedLength());
  *out = (RTI::EncodedLogicalTime *)encodedLogicalTimeI;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapFederateHandle(RTI::FederateHandle &out, GeRtiFactory::GeRtiHandle const &in)
{
  RTI::FederateHandle tmp(in);
  out = tmp;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapFederateHandle(GeRtiFactory::GeRtiHandle &out, RTI::FederateHandle const &in)
{
  out = in.getImplementation();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapFederateHandleRestoreStatusPairVector(std::auto_ptr<RTI::FederateHandleRestoreStatusPairVector> &out, GeRtiFactory::RestoreStatusPairSeq const &in)
{
  CORBA::ULong i;
  CORBA::ULong length;
  RTI::FederateHandle federateHandle;
  RTI::FederateHandleRestoreStatusPairVector *federateHandleRestoreStatusPairVector;

  federateHandleRestoreStatusPairVector = new RTI::FederateHandleRestoreStatusPairVector;

  length = in.length();
  for (i = 0; i < length; i++)
  {
    mapFederateHandle(federateHandle, in[i].theFederate);

    switch (in[i].theRestoreStatus)
    {
      case GeRtiFactory::noRestoreInProgress:
      {
        RTI::RestoreStatus restoreStatus(RTI::RestoreStatus noRestoreInProgress());
// XXX        federateHandleRestoreStatusPairVector->insert(std::pair<const RTI::FederateHandle, RTI::RestoreStatus>(federateHandle, restoreStatus));
        break;
      }
      case GeRtiFactory::federateRestoreRequestPending:
      {
        RTI::RestoreStatus restoreStatus(RTI::RestoreStatus federateRestoreRequestPending());
        break;
      }
      case GeRtiFactory::federateWaitingForRestoreToBegin:
      {
        RTI::RestoreStatus restoreStatus(RTI::RestoreStatus federateWaitingForRestoreToBegin());
        break;
      }
      case GeRtiFactory::federatePreparedToRestore:
      {
        RTI::RestoreStatus restoreStatus(RTI::RestoreStatus federatePreparedToRestore());
        break;
      }
      case GeRtiFactory::federateRestoring:
      {
        RTI::RestoreStatus restoreStatus(RTI::RestoreStatus federateRestoring());
        break;
      }
      case GeRtiFactory::federateWaitingForFederationToRestore:
      {
        RTI::RestoreStatus restoreStatus(RTI::RestoreStatus federateWaitingForFederationToRestore());
        break;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapFederateHandleSaveStatusPairVector(std::auto_ptr<RTI::FederateHandleSaveStatusPairVector> &out, GeRtiFactory::SaveStatusPairSeq const &in)
{
  CORBA::ULong i;
  CORBA::ULong length;
  RTI::FederateHandle federateHandle;
  RTI::FederateHandleSaveStatusPairVector *federateHandleSaveStatusPairVector;

  federateHandleSaveStatusPairVector = new RTI::FederateHandleSaveStatusPairVector;

  length = in.length();
  for (i = 0; i < length; i++)
  {
    mapFederateHandle(federateHandle, in[i].theFederate);

    switch (in[i].theSaveStatus)
    {
      case GeRtiFactory::noSaveInProgress:
      {
        RTI::SaveStatus restoreStatus(RTI::RestoreStatus noSaveInProgress());
// XXX        federateHandleRestoreStatusPairVector->insert(std::pair<const RTI::FederateHandle, RTI::RestoreStatus>(federateHandle, restoreStatus));
        break;
      }
      case GeRtiFactory::federateInstructedToSave:
      {
        RTI::SaveStatus restoreStatus(RTI::RestoreStatus federateInstructedToSave());
        break;
      }
      case GeRtiFactory::federateSaving:
      {
        RTI::SaveStatus restoreStatus(RTI::RestoreStatus federateSaving());
        break;
      }
      case GeRtiFactory::federateWaitingForFederationToSave:
      {
        RTI::SaveStatus restoreStatus(RTI::RestoreStatus federateWaitingForFederationToSave());
        break;
      }
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapFederateHandleSet(GeRtiFactory::Handles &out, RTI::FederateHandleSet const &in)
{
  CORBA::ULong i;
  CORBA::ULong size;
  RTI::FederateHandleSet::const_iterator itFederateHandleSet;

  size = in.size();
  out.length(size);

  for (itFederateHandleSet = in.begin(), i = 0; itFederateHandleSet != in.end(); itFederateHandleSet++, i++)
  {
    out[i] = itFederateHandleSet->getImplementation();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapInteractionClassHandle(GeRtiFactory::GeRtiHandle &out, RTI::InteractionClassHandle const &in)
{
  out = in.getImplementation();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapInteractionClassHandle(RTI::InteractionClassHandle &out, GeRtiFactory::GeRtiHandle const &in)
{
  RTI::InteractionClassHandle tmp(in);
  out = tmp;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapLogicalTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, std::auto_ptr<GERTICO::GeRtiFedTime> &out, const RTI::LogicalTime &in)
{
  std::auto_ptr<RTI::EncodedLogicalTime> encodedLogicalTime;
  encodedLogicalTime = in.encode();
  out.reset(theGeRtiFedTimeFactory.decode((const char *)encodedLogicalTime->data()));
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> &out, RTI::LogicalTimeInterval const &in)
{
  std::auto_ptr<RTI::EncodedLogicalTimeInterval> encodedLogicalTimeInterval;
  GERTICO::GeRtiEncodedLogicalTimeInterval *gelti;
  encodedLogicalTimeInterval = in.encode();
  gelti = new GERTICO::GeRtiEncodedLogicalTimeIntervalI(encodedLogicalTimeInterval->data(), encodedLogicalTimeInterval->size());
  out.reset(theGeRtiLogicalTimeIntervalFactory.decode(*gelti));
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, RTI::LogicalTimeInterval &out, GERTICO::GeRtiLogicalTimeInterval const &in)
{
  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> gelti;
  std::auto_ptr<RTI::LogicalTimeInterval> lti;
  GERTICO1516::EncodedLogicalTimeIntervalI *elt;

  gelti = in.encode();

  elt = new GERTICO1516::EncodedLogicalTimeIntervalI(gelti->data(), gelti->size());

  lti = theGeRtiLogicalTimeIntervalFactory.logicalTimeIntervalFactory.decode(*elt);
  out = *lti;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapObjectClassHandle(GeRtiFactory::GeRtiHandle &out, RTI::ObjectClassHandle const &in)
{
  out = in.getImplementation();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapObjectClassHandle(RTI::ObjectClassHandle &out, GeRtiFactory::GeRtiHandle const &in)
{
  RTI::ObjectClassHandle tmp(in);
  out = tmp;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapObjectInstanceHandle(GeRtiFactory::GeRtiHandle &out, RTI::ObjectInstanceHandle const &in)
{
  out = in.getImplementation();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapObjectInstanceHandle(RTI::ObjectInstanceHandle &out, GeRtiFactory::GeRtiHandle const &in)
{
  RTI::ObjectInstanceHandle tmp(in);
  out = tmp;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapMessageRetractionHandle(GeRtiFactory::ERHandle &out, RTI::MessageRetractionHandle const &in)
{
  GeRtiFactory::GeRtiHandle sendingFederate;
  GeRtiFactory::GeRtiHandle serialNumber;

  ((GERTICO::MessageRetractionHandleI *)&in)->getSendingFederate(sendingFederate);
  ((GERTICO::MessageRetractionHandleI *)&in)->getSerialNumber(serialNumber);

  out.sendingFederate = sendingFederate;
  out.theSerialNumber = serialNumber;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapMessageRetractionHandle
(
  RTI::MessageRetractionHandle &out,
  GeRtiFactory::ERHandle const &in
)
{
  GERTICO::MessageRetractionHandleI *messageRetractionHandleI = new GERTICO::MessageRetractionHandleI(in.sendingFederate, in.theSerialNumber);

  out = *((RTI::MessageRetractionHandle *)messageRetractionHandleI);

  delete messageRetractionHandleI;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapOrderType(GeRtiFactory::GeRtiHandle &out, RTI::OrderType const &in)
{
  std::wstring ws = L"mapOrderType";

  if (in == RTI::OrderType::timestamp())
  {
    out = 1;
  }
  else if (in == RTI::OrderType::receive())
  {
    out = 0;
  }
  else
  {
    throw RTI::InvalidOrderType(ws.c_str());
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapParameterHandle(GeRtiFactory::GeRtiHandle &out, RTI::ParameterHandle const &in)
{
  out = in.getImplementation();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapParameterHandle(RTI::ParameterHandle &out, GeRtiFactory::GeRtiHandle const &in)
{
  RTI::ParameterHandle tmp(in);
  out = tmp;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapParameterHandleValueMap(GeRtiFactory::HandleValues &out, RTI::ParameterHandleValueMap const &in)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong leni;
  CORBA::ULong lenj;
  GeRtiFactory::GeRtiHandle parameterHandle;
  char *dataPtr;
  MyParameterHandleValueMap::const_iterator itParameterHandleValueMap;

  leni = in.size();
  out.length(leni);
  for (itParameterHandleValueMap = in.begin(), i = 0; itParameterHandleValueMap != in.end(); itParameterHandleValueMap++, i++)
  {
    mapParameterHandle(parameterHandle, itParameterHandleValueMap->first);
    out[i].id = parameterHandle;
    out[i].timestampOrder = 0;
    out[i].bestEffort = 0;
    lenj = itParameterHandleValueMap->second.size();
    out[i].value.length(lenj);
    dataPtr = (char *)itParameterHandleValueMap->second.data();
    for (j = 0; j < lenj; j++)
    {
      out[i].value[j] = dataPtr[j];
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapParameterHandleValueMap(RTI::ParameterHandleValueMap &out, GeRtiFactory::HandleValues const &in)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong leni;
  CORBA::ULong lenj;
  RTI::ParameterHandle parameterHandle;
  MyParameterHandleValueMap::const_iterator itParameterHandleValueMap;

  leni = in.length();
  for (i = 0; i < leni; i++)
  {
    mapParameterHandle(parameterHandle, in[i].id);

    // Copy the attribute value.
    lenj = in[i].value.length();
    char* buff = new char[lenj];
    for (j = 0; j < lenj; j++)
    {
      buff[j] = in[i].value[j];
    }
    RTI::ParameterValue parameterValue(buff, lenj);
    delete buff;
    out[parameterHandle] = parameterValue;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapRangeBounds(RTI::RangeBounds &out, GeRtiFactory::Handles const &in)
{
  CORBA::ULong i;
  CORBA::ULong length;
  unsigned long lowerBound = 0;
  unsigned long upperBound = 0;

  length = in.length();
  if (length > 1)
  {
    i = 0;
    lowerBound = in[i];
    i = 1;
    upperBound = in[i];
  }

  RTI::RangeBounds tmp(lowerBound, upperBound);
  out = tmp;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapRangeBounds(GERTICO::UpperLowerBounds &out, RTI::RangeBounds const &in)
{
  out.lower = in.getLowerBound();
  out.upper = in.getUpperBound();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapRegionHandle(GeRtiFactory::GeRtiHandle &out, RTI::RegionHandle const &in)
{
  out = in.getImplementation();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapRegionHandle(RTI::RegionHandle &out, GeRtiFactory::GeRtiHandle const &in)
{
  RTI::RegionHandle tmp(in);
  out = tmp;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapRegionHandleSet(GERTICO::HandleSet &out, RTI::RegionHandleSet const &in)
{
  CORBA::ULong i;
  CORBA::ULong length;
  RTI::RegionHandleSet::const_iterator itRegionHandleSet;

  length = in.size ();
  for (i = 0, itRegionHandleSet = in.begin(); itRegionHandleSet != in.end(); i++, itRegionHandleSet++)
  {
    RTI::EncodedRegionHandleImplementationType eahit = (*itRegionHandleSet).encode();
    out.insert(*((RTI::RegionHandleReturnType *)eahit.getImplementation().data()));
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapTransportationType(GeRtiFactory::GeRtiHandle &out, RTI::TransportationType const &in)
{
  if (in == RTI::TransportationType::bestEffort())
  {
    out = 1;
  }
  else
  {
    out = 0;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapTransportationType(RTI::TransportationType &out, GeRtiFactory::GeRtiHandle const &in)
{
  if (in)
  {
    RTI::TransportationType transportationType(RTI::TransportationType::bestEffort());
    out = transportationType;
  }
  else
  {
    RTI::TransportationType transportationType(RTI::TransportationType::reliable());
    out = transportationType;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapUserSuppliedTag(GeRtiFactory::UserSuppliedTag &out, RTI::UserSuppliedTag const &in)
{
  CORBA::ULong i;
  char *dPtr = (char *)in.data();
  size_t s = in.size();

  out.length(s);
  for (i = 0; i < s; i++)
  {
    out[i] = dPtr[i];
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapUserSuppliedTag(RTI::UserSuppliedTag &out, GeRtiFactory::UserSuppliedTag const &in)
{
  CORBA::ULong i;
  const size_t max_len = 256;
  size_t len;
  char cBuff[max_len];

  len = in.length();
  if (len > max_len)
  {
    len = max_len;
  }
  for (i = 0; i < len; i++)
  {
    cBuff[i] = in[i];
  }

  RTI::UserSuppliedTag userSuppliedTag(cBuff, len);
  out = userSuppliedTag;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper1516::mapWstringTranscode(XMLCh *out, std::wstring const &in, unsigned long const &theMaxLength)
{
  unsigned int i;
  unsigned int length;

  length = in.size();
  for (i = 0; i < length; i++)
  {
    out[i] = in[i];
  }
}
