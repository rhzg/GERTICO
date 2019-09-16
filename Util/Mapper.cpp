/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** Mapper.cpp
**
*******************************************************************************/

// C++ standard library
#include <stdexcept>
#ifndef _WIN32
#include <netinet/in.h>
#endif

// project include files
#include "iostream"
#include "Mapper.h"
#include "ace/OS_NS_wchar.h"
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Mapper::Mapper ()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::Mapper::~Mapper ()
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapAttributeRegionsSeqFromHandleSetMap(GeRtiFactory::AttributeRegionsSeq &out, GERTICO::HandleSetMap const &in)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong length;
  size_t len;
  GERTICO::HandleSet::const_iterator itHandleSet;
  GERTICO::HandleSetMap::const_iterator itHandleSetMap;

  len = in.size();
  mapULongSizet(length, len);
  out.length(length);
  for (itHandleSetMap = in.begin(), i = 0; itHandleSetMap != in.end(); itHandleSetMap++, i++)
  {
    out[i].theAttribute = itHandleSetMap->first;
    len = itHandleSetMap->second.size();
    mapULongSizet(length, len);
    out[i].theRegions.length(length);
    for (itHandleSet = itHandleSetMap->second.begin(), j = 0; itHandleSet != itHandleSetMap->second.end(); itHandleSet++, j++)
    {
      out[i].theRegions[j] = *itHandleSet;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapAttributeSubscribersSeqFromHandleSetMap(GeRtiFactory::AttributeSubscribersSeq &out, GERTICO::HandleSetMap const &in)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong length;
  size_t size;
  GERTICO::HandleSet::const_iterator itHandleSet;
  GERTICO::HandleSetMap::const_iterator itHandleSetMap;

  size = in.size();
  mapULongSizet(length, size);
  out.length(length);
  for (itHandleSetMap = in.begin(), i = 0; itHandleSetMap != in.end(); itHandleSetMap++, i++)
  {
    out[i].theAttribute = itHandleSetMap->first;
    size = itHandleSetMap->second.size();
    mapULongSizet(length, size);
    out[i].theSubscribers.length(length);
    for (itHandleSet = itHandleSetMap->second.begin(), j = 0; itHandleSet != itHandleSetMap->second.end(); itHandleSet++, j++)
    {
      out[i].theSubscribers[j] = *itHandleSet;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHandleSetMapFromAttributeSubscribersSeq(GERTICO::HandleSetMap &out, GeRtiFactory::AttributeSubscribersSeq const &in)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong lengthi;
  CORBA::ULong lengthj;
  GERTICO::HandleSet subscribers;
  GERTICO::HandleSet::const_iterator itHandleSet;
  GERTICO::HandleSetMap::const_iterator itHandleSetMap;

  lengthi = in.length();
  for (i = 0; i < lengthi; i++)
  {
    lengthj = in[i].theSubscribers.length();
    for (j = 0; j < lengthj; j++)
    {
      subscribers.insert(in[i].theSubscribers[j]);
    }
    out[in[i].theAttribute] = subscribers;
    subscribers.clear();
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHandleSet(GERTICO::HandleSet &out, GeRtiFactory::Handles const &in)
{
  CORBA::ULong i;
  CORBA::ULong len = in.length();

  out.clear();

  for (i = 0; i < len; i++)
  {
    out.insert(in[i]);
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHandleSet(GeRtiFactory::Handles &out, GERTICO::HandleSet const &in)
{
  CORBA::ULong i;
  CORBA::ULong length;
  size_t len = in.size();
  GERTICO::HandleSet::const_iterator itHandleSet;

  mapULongSizet(length, len);
  out.length(length);
  for (itHandleSet = in.begin(), i = 0; itHandleSet != in.end(); itHandleSet++, i++)
  {
    out[i] = *itHandleSet;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHandleSetMapFromAttributeRegionsSeq(GERTICO::HandleSetMap &out, GeRtiFactory::AttributeRegionsSeq const &in)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong iLen;
  CORBA::ULong jLen;
  GERTICO::HandleSet::iterator itReg;
  GERTICO::HandleSetMap::iterator itAtt;

  iLen = in.length();
  for (i = 0; i < iLen; i++)
  {
    itAtt = out.find(in[i].theAttribute);
    if (itAtt != out.end())
    {
      GERTICO::HandleSet *regionPtr;

      regionPtr = &itAtt->second;
      jLen = in[i].theRegions.length();
      for (j = 0; j < jLen; j++)
      {
        regionPtr->insert(in[i].theRegions[j]);
      }
    }
    else
    {
      GERTICO::HandleSet regions;

      jLen = in[i].theRegions.length();
      for (j = 0; j < jLen; j++)
      {
        regions.insert(in[i].theRegions[j]);
      }
      out[in[i].theAttribute] = regions;
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHandleSetMapInvert(GERTICO::HandleSetMap &out, GERTICO::HandleSetMap const &in)
{
  const GERTICO::HandleSet *handleSetPtr;
  GERTICO::HandleSet::const_iterator itHandleSet;
  GERTICO::HandleSetMap::const_iterator itHandleSetMap;
  GERTICO::HandleSetMap::iterator itHandleSetMapOut;

  for (itHandleSetMap = in.begin(); itHandleSetMap != in.end(); itHandleSetMap++)
  {
    handleSetPtr = &itHandleSetMap->second;
    for (itHandleSet = handleSetPtr->begin(); itHandleSet != handleSetPtr->end(); itHandleSet++)
    {
      itHandleSetMapOut = out.find(*itHandleSet);
      if (itHandleSetMapOut != out.end())
      {
        GERTICO::HandleSet *handleSetPtrOut;

        handleSetPtrOut = &itHandleSetMapOut->second;
        handleSetPtrOut->insert(itHandleSetMap->first);
      }
      else
      {
        GERTICO::HandleSet handleSetOut;

        handleSetOut.insert(itHandleSetMap->first);
        out[*itHandleSet] = handleSetOut;
      }
    }
  }
}

// ---------------------------------------------------------------------------
// Only for NULL terminated char strings.
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHandleValue(GeRtiFactory::HandleValue &theHandleValue, GeRtiFactory::GeRtiHandle const &theId, char const *theBuff)
{
  CORBA::ULong i;
  CORBA::ULong length;
  size_t len;

  theHandleValue.id = theId;

  theHandleValue.timestampOrder = 0;
  theHandleValue.bestEffort = 0;

  len = strlen(theBuff);
  mapULongSizet(length, len);
  theHandleValue.value.length(length + 1);
  for (i = 0; i < length; i++)
  {
    theHandleValue.value[i] = theBuff[i];
  }
  theHandleValue.value[length] = '\0';
}

// ---------------------------------------------------------------------------
// Primitive function to avoid warnings throughout the project.
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapSizetULong(size_t &out, CORBA::ULong const &in)
{
  out = in;
}

// ---------------------------------------------------------------------------
// Primitive function to avoid warnings throughout the project.
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapULongSizet(CORBA::ULong &out, size_t const &in)
{
  out = (CORBA::ULong) in;
}

#ifdef IEEE_1516
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHandleValueFromWstring(GeRtiFactory::HandleValue &theHandleValue, GeRtiFactory::GeRtiHandle const &theId, std::wstring const &theWstring)
{
  CORBA::ULong pos;
  long i;
  long length;
  long netLong;
  short netShort;
  short s;
  const wchar_t *wPtr;

  theHandleValue.id = theId;

  theHandleValue.timestampOrder = 0;
  theHandleValue.bestEffort = 0;

  pos = 0;
  length = theWstring.size();
  swapFour(netLong, length);
  theHandleValue.value.length(sizeof(long) + sizeof(short) * (length + 1));
  memcpy(&theHandleValue.value[pos], &netLong, sizeof(long));
  pos += 4;
  wPtr = theWstring.c_str();
  for (i = 0; i < length; i++)
  {
    s = wPtr[i];
    swapTwo(netShort, s);
    memcpy(&theHandleValue.value[pos], &netShort, sizeof(short));
    pos += 2;
  }

  // The null value.
  s = wPtr[length];
  swapTwo(netShort, s);
  memcpy(&theHandleValue.value[pos], &netShort, sizeof(short));
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAAttributesFromOctetSequence(GeRtiFactory::Handles &theAttributes, GeRtiFactory::OctetSequence const &theOctetSequence)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong length = theOctetSequence.length();
  long locnum;
  unsigned long num;
  unsigned long pos = 0;
  union
  {
    char c[4];
    long l;
  } c4;

  for (i = 0; i < 4; i++)
  {
    c4.c[i] = theOctetSequence[i];
  }
  pos += 4;
  swapFour(locnum, c4.l);
  num = locnum;

  if ((4 + num * 4) != length)
  {
    return;
  }

  theAttributes.length(num);
  for (i = 0; i < num; i++)
  {
    for (j = 0; j < 4; j++)
    {
      c4.c[i] = theOctetSequence[pos + 4 * i + j];
    }
    swapFour(locnum, c4.l);
    theAttributes[i] = locnum;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAwstring(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, std::wstring const &theWstring)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAwstringFromOctetSequence(std::wstring &theWstring, GeRtiFactory::OctetSequence const &theOctetSequence)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong length = theOctetSequence.length();
  long locnum;
  short locShort;
  unsigned long num;
  unsigned long offset = 0;
  union
  {
    char c[2];
    wchar_t wc;
  } c2;
  union
  {
    char c[4];
    long l;
  } c4;
  wchar_t *wArray;

  for (i = 0; i < 4; i++)
  {
    c4.c[i] = theOctetSequence[i];
  }
  offset += 4;
  swapFour(locnum, c4.l);
  num = locnum;

  if ((4 + num * 2) != length)
  {
    return;
  }

  wArray = new wchar_t[num + 1];
  for (i = 0; i < num; i++)
  {
    for (j = 0; j < 2; j++)
    {
      c2.c[i] = theOctetSequence[offset + 2 * i + j];
    }
    swapTwo(locShort, c2.wc);
    wArray[i] = locShort;
  }
  wArray[num] = 0;
  theWstring = wArray;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAboolean(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, bool const &theBool)
{
  CORBA::ULong i;
  CORBA::ULong length;

  theHandleOut.id = theId;

  theHandleOut.timestampOrder = 0;
  theHandleOut.bestEffort = 0;

  if (theBool)
  {
    i = 1;
  }
  else
  {
    i = 0;
  }
  length = 4;
  theHandleOut.value.length(length);
  theHandleOut.value[0] = i >> 24;
  theHandleOut.value[1] = i >> 16;
  theHandleOut.value[2] = i >> 8;
  theHandleOut.value[3] = i;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAfederateState(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, GERTICO::FederateState const &theFederateState)
{
  long netLong;
  long federateStateValue;

  theHandleOut.id = theId;

  theHandleOut.timestampOrder = 0;
  theHandleOut.bestEffort = 0;

  switch(theFederateState)
  {
    case Running:
    {
      federateStateValue = 1;
      break;
    }
    case SavePending:
    {
      break;
    }
    case Saving:
    {
      federateStateValue = 3;
      break;
    }
    case RestorePending:
    {
      break;
    }
    case Restoring:
    {
      federateStateValue = 5;
      break;
    }
  }

  swapFour(netLong, federateStateValue);
  theHandleOut.value.length(sizeof(long));
  memcpy(&theHandleOut.value[0], &netLong, sizeof(long));
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAhandle(GeRtiFactory::HandleValue &theHandleValue, const GeRtiFactory::GeRtiHandle &theId, unsigned long const &thehandle)
{
  CORBA::ULong i;

  theHandleValue.id = theId;

  theHandleValue.timestampOrder = 0;
  theHandleValue.bestEffort = 0;

  theHandleValue.value.length(8);
  i = 4;
  theHandleValue.value[0] = i >> 24;
  theHandleValue.value[1] = i >> 16;
  theHandleValue.value[2] = i >> 8;
  theHandleValue.value[3] = i;
  i = thehandle;
  theHandleValue.value[4] = i >> 24;
  theHandleValue.value[5] = i >> 16;
  theHandleValue.value[6] = i >> 8;
  theHandleValue.value[7] = i;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAhandleList(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, GERTICO::HandleSet const &theHandleSet)
{
  GERTICO::HandleSet::const_iterator itHandleSet;
  CORBA::ULong pos;
  long l;
  long len;
  long netLong;

  theHandleOut.id = theId;

  theHandleOut.timestampOrder = 0;
  theHandleOut.bestEffort = 0;

  pos = 0;
  len = theHandleSet.size();
  swapFour(netLong, len);
  theHandleOut.value.length(sizeof(long) * (2 * len + 1));
  memcpy(&theHandleOut.value[pos], &netLong, sizeof(long));
  for (itHandleSet = theHandleSet.begin(); itHandleSet != theHandleSet.end(); itHandleSet++)
  {
    l = *itHandleSet;
    swapFour(netLong, l);
    pos += 4;
    memcpy(&theHandleOut.value[pos], &netLong, sizeof(long));
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAhandleListBool(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, GERTICO::HandleBoolMap const &theHandleBoolMap)
{
  GERTICO::HandleBoolMap::const_iterator itHandleBoolMap;
  CORBA::ULong pos;
  long len;
  long netLong;
  long l;

  theHandleOut.id = theId;

  theHandleOut.timestampOrder = 0;
  theHandleOut.bestEffort = 0;

  pos = 0;
  len = theHandleBoolMap.size();
  swapFour(netLong, len);
  theHandleOut.value.length(sizeof(long) * (2 * len + 1));
  memcpy(&theHandleOut.value[pos], &netLong, sizeof(long));
  for (itHandleBoolMap = theHandleBoolMap.begin(); itHandleBoolMap != theHandleBoolMap.end(); itHandleBoolMap++)
  {
    l = itHandleBoolMap->first;
    swapFour(netLong, l);
    pos += 4;
    memcpy(&theHandleOut.value[pos], &netLong, sizeof(long));
    if (itHandleBoolMap->second)
    {
      l = 1;
    }
    else
    {
      l = 0;
    }
    swapFour(netLong, l);
    pos += 4;
    memcpy(&theHandleOut.value[pos], &netLong, sizeof(long));
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAinteger32BE(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, CORBA::ULong const &theHLAinteger32BE)
{
  CORBA::ULong i;
  CORBA::ULong length;

  theHandleOut.id = theId;

  theHandleOut.timestampOrder = 0;
  theHandleOut.bestEffort = 0;

  length = 4;
  i = theHLAinteger32BE;
  theHandleOut.value.length(length);
  theHandleOut.value[0] = i >> 24;
  theHandleOut.value[1] = i >> 16;
  theHandleOut.value[2] = i >> 8;
  theHandleOut.value[3] = i;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAlogicalTime(GeRtiFactory::HandleValue &theHandleValue, GeRtiFactory::GeRtiHandle const &theId, std::auto_ptr<GERTICO::GeRtiFedTime> &theLogicalTime)
{
  CORBA::ULong i;
  CORBA::ULong length;
  char t[128];

  theHandleValue.id = theId;

  theHandleValue.timestampOrder = 0;
  theHandleValue.bestEffort = 0;

  if (theLogicalTime.get())
  {
    length = theLogicalTime->encodedLength();
    theHandleValue.value.length(length + 4);
    theHandleValue.value[0] = length >> 24;
    theHandleValue.value[1] = length >> 16;
    theHandleValue.value[2] = length >> 8;
    theHandleValue.value[3] = length;
    theLogicalTime->encode(t);
    for (i = 0; i < length; i++)
    {
      theHandleValue.value[i + 4] = t[i];
    }
  }
  else
  {
    length = 0;
    theHandleValue.value.length(4);
    theHandleValue.value[0] = length >> 24;
    theHandleValue.value[1] = length >> 16;
    theHandleValue.value[2] = length >> 8;
    theHandleValue.value[3] = length;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAlogicalTimeInterval(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval)
{
  CORBA::ULong length;
  size_t size;
  unsigned char *tmpBuff;
  std::auto_ptr<GERTICO::GeRtiEncodedLogicalTimeInterval> elti;

  theHandleOut.id = theId;

  theHandleOut.timestampOrder = 0;
  theHandleOut.bestEffort = 0;

  elti = theLogicalTimeInterval.encode();

  tmpBuff = (unsigned char *)elti->data();
  size = elti->size();

  mapULongSizet(length, size);
  theHandleOut.value.length(length);
  memcpy(&theHandleOut.value[0], tmpBuff, length);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAlongFromOctetSequence(long &theLong, GeRtiFactory::OctetSequence const &theOctetSequence)
{
  int i;
  long l;
  unsigned char buff[4];

  for (i = 0; i < 4; i++)
  {
    buff[i] = theOctetSequence[i];
  }
  memcpy(&l, buff, 4);
  swapFour(theLong, l);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAobjectClassBasedCounts(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, GERTICO::HandleMap const &theHandleMap)
{
  GERTICO::HandleMap::const_iterator itHandleMap;
  CORBA::ULong pos;
  long len;
  long netLong;
  long l;

  theHandleOut.id = theId;

  theHandleOut.timestampOrder = 0;
  theHandleOut.bestEffort = 0;

  pos = 0;
  len = theHandleMap.size();
  swapFour(netLong, len);
  theHandleOut.value.length(sizeof(long) * (2 * len + 1));
  memcpy(&theHandleOut.value[pos], &netLong, sizeof(long));
  for (itHandleMap = theHandleMap.begin(); itHandleMap != theHandleMap.end(); itHandleMap++)
  {
    l = itHandleMap->first;
    swapFour(netLong, l);
    pos += 4;
    memcpy(&theHandleOut.value[pos], &netLong, sizeof(long));
    l = itHandleMap->second;
    swapFour(netLong, l);
    pos += 4;
    memcpy(&theHandleOut.value[pos], &netLong, sizeof(long));
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAtimeManagerState(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, bool const &theBool)
{
  long netLong;
  long boolValue;

  theHandleOut.id = theId;

  theHandleOut.timestampOrder = 0;
  theHandleOut.bestEffort = 0;

  if (theBool)
  {
    boolValue = 1;
  }
  else
  {
    boolValue = 0;
  }
  swapFour(netLong, boolValue);
  theHandleOut.value.length(sizeof(long));
  memcpy(&theHandleOut.value[0], &netLong, sizeof(long));
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapHLAunicodeWstring(GeRtiFactory::HandleValue &theHandleValue, const GeRtiFactory::GeRtiHandle &theId, std::wstring const &theWstring)
{
  CORBA::ULong i;
  CORBA::ULong len;
  short netshort;

  theHandleValue.id = theId;

  theHandleValue.timestampOrder = 0;
  theHandleValue.bestEffort = 0;

  len = theWstring.size() + 1;
  theHandleValue.value.length(4 + (2 * len));
  theHandleValue.value[0] = len >> 24;
  theHandleValue.value[1] = len >> 16;
  theHandleValue.value[2] = len >> 8;
  theHandleValue.value[3] = len;
  len -= 1;
  for (i = 0; i < len; i++)
  {
	  netshort = theWstring[i];
    theHandleValue.value[4 + (2 * i)] = netshort >> 8;
    theHandleValue.value[4 + ((2 * i) + 1)] = netshort;
  }
  theHandleValue.value[4 + (2 * len)] = 0;
  theHandleValue.value[4 + ((2 * len) + 1)] = 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::getOrderType(GeRtiFactory::GeRtiHandle &theOrderingType, GeRtiFactory::OctetSequence const &theOctetSequence)
{
  std::wstring ws;

  GERTICO::Mapper::mapHLAwstringFromOctetSequence(ws, theOctetSequence);

  if (ws == L"Reliable")
  {
    theOrderingType = 1;
  }
  else
  {
    theOrderingType = 0;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::getTransportationType(GeRtiFactory::GeRtiHandle &theTransportationType, GeRtiFactory::OctetSequence const &theOctetSequence)
{
  std::wstring ws;

  GERTICO::Mapper::mapHLAwstringFromOctetSequence(ws, theOctetSequence);

  if (ws == L"Best Effort")
  {
    theTransportationType = 1;
  }
  else
  {
    theTransportationType = 0;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapWstringFromXMLCh(std::wstring &theWstring, XMLCh const *theXMLCh)
{
  int i;
  int len;
  wchar_t wc[512];

  len = XMLString::stringLen(theXMLCh);
  for (i = 0; i < len; i++)
  {
    wc[i] = theXMLCh[i];
  }
  wc[len] = 0;

  theWstring = wc;
}
#else
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::getOrderType(GeRtiFactory::GeRtiHandle &theOrderingType, char *theBuff)
{
  CORBA::ULong i;
  CORBA::ULong length;
  size_t len;

  len = strlen(theBuff);
  mapULongSizet(length, len);
  for (i = 0; i < length; i++)
  {
    theBuff[i] = tolower(theBuff[i]);
  }

  if (strcmp(theBuff, "timestamp") == 0)
  {
    theOrderingType = 1;
  }
  else
  {
    theOrderingType = 0;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::getTransportationType(GeRtiFactory::GeRtiHandle &theTransportationType, char *theBuff)
{
  CORBA::ULong i;
  CORBA::ULong length;
  size_t len;

  len = strlen(theBuff);
  mapULongSizet(length, len);
  for (i = 0; i < length; i++)
  {
    theBuff[i] = tolower(theBuff[i]);
  }

  if (strcmp(theBuff, "best effort") == 0)
  {
    theTransportationType = 1;
  }
  else
  {
    theTransportationType = 0;
  }
}
#endif

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapUserSuppliedTag
(
  GeRtiFactory::UserSuppliedTag &out,
  const char *in
)
{
  CORBA::ULong i;
  CORBA::ULong length;
  size_t len;

  if (in == NULL)
  {
    len = 0;
  }
  else
  {
    len = strlen(in);
  }
  mapULongSizet(length, len);
  out.length(length);
  for (i = 0; i < length; i++)
  {
    out[i] = in[i];
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapUserSuppliedTag(char **out, GeRtiFactory::UserSuppliedTag const &in)
{
  CORBA::ULong i;
  CORBA::ULong length;

  length = in.length();
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
void GERTICO::Mapper::mapOctetSequence(char **out, GeRtiFactory::OctetSequence const &theOctetSequence)
{
  CORBA::ULong i;
  CORBA::ULong length = theOctetSequence.length();
  *out = new char[length + 1];
  for (i = 0; i < length; i++)
  {
    (*out)[i] = theOctetSequence[i];
  }

  (*out)[length] = '\0';
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapStringFromWstring(std::string &theString, std::wstring const &theWstring)
{
  CORBA::ULong i;
  size_t len;
  char c[1024];
  const wchar_t *ptr;

  // Also allow for NULL char!
  len = theWstring.size() + 1;
  ptr = theWstring.c_str();
  for (i = 0; i < len; i++)
  {
    c[i] = (char)ptr[i];
  }
  theString = c;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapWstringFromChar(std::wstring &theWstring, char const *theBuff)
{
  CORBA::ULong i;
  size_t len;
  wchar_t *buff;

  // Also allow for NULL char!
  len = strlen(theBuff) + 1;
  buff = new wchar_t[len];
  for (i = 0; i < len; i++)
  {
    buff[i] = theBuff[i];
  }
  theWstring = buff;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapWcharFromWstring(CORBA::WChar **theBuff, std::wstring const &theWstring)
{
  CORBA::ULong i;
  CORBA::ULong length;
  size_t len;
  const wchar_t *ptr;

  // Also allow for NULL char!
  len = theWstring.size() + 1;
  mapULongSizet(length, len);
  *theBuff = CORBA::wstring_alloc(length);
  ptr = theWstring.c_str();
  for (i = 0; i < length; i++)
  {
    (*theBuff)[i] = ptr[i];
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::mapWstringFromWchar(std::wstring &theWstring, CORBA::WChar const *theBuff)
{
  CORBA::ULong i;
  CORBA::ULong len = 0;
  wchar_t *wc;

  // Also allow for NULL char!
  len = ACE_OS::wslen(theBuff) + 1;
  wc = new wchar_t[len];

  for (i = 0; i < len; i++)
  {
    wc[i] = theBuff[i];
  }

  theWstring = wc;
  delete []wc;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::nameToLower(std::string &theString)
{
#ifndef IEEE_1516
  CORBA::ULong i;
  CORBA::ULong length;
  char c[256];
  size_t len;

  strcpy(c, theString.c_str ());

  len = strlen(c);
  mapULongSizet(length, len);
  for (i = 0; i < length; i++)
  {
    c[i] = tolower(c[i]);
  }

  theString = c;
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::nameToLower(std::wstring &theWstring)
{
#ifndef IEEE_1516
  char c[512];
  wchar_t wc[512];
  unsigned long i;
  size_t len;

  len = theWstring.size() + 1;
  for (i = 0; i < len; i++)
  {
    c[i] = (char)theWstring[i];
  }

  for (i = 0; i < len; i++)
  {
    wc[i] = tolower(c[i]);
  }

  theWstring = wc;
#endif
}

void GERTICO::Mapper::printAttributeHandleValue(char *theDesc, char *theGalMsg, GeRtiFactory::HandleValue const &theHandleValue)
{
  bool isPrintable = true;
  bool tooLong = false;
  size_t ind;
  int j;
  int lenj;

  strcpy(theGalMsg, theDesc);

  ind = strlen(theGalMsg);
  sprintf(&theGalMsg[ind], "attribute=%d,value=", theHandleValue.id);

  isPrintable = true;
  lenj = theHandleValue.value.length();

  // Prevent buffer overflow
  if (lenj > 64)
  {
    lenj = 64;
    tooLong = true;
  }
  for (j = 0; j < lenj; j++)
  {
    if (theHandleValue.value[j] == 0)
    {
      continue;
    }
    if (isprint(theHandleValue.value[j]))
    {
      continue;
    }
    isPrintable = false;
  }

  if (isPrintable)
  {
    ind = strlen(theGalMsg);
  }

  for (j = 0; j < lenj; j++)
  {
    if (isPrintable)
    {
      theGalMsg[ind] = theHandleValue.value[j];
      ind += 1;
      theGalMsg[ind] = '\0';
    }
    else
    {
      ind = strlen(theGalMsg);
      sprintf(&theGalMsg[ind], "%2.2x", theHandleValue.value[j]);
    }
  }

  // Tell user that not everything is printed
  if (tooLong)
  {
    theGalMsg[lenj] = '.';
    theGalMsg[lenj + 1] = '.';
    theGalMsg[lenj + 2] = '.';
    theGalMsg[lenj + 3] = '\0';
  }
}

void GERTICO::Mapper::printGeRtiFactoryAttributeRegionsSeq(char *theDesc, char *theGalMsg, GeRtiFactory::AttributeRegionsSeq const &theAttributeRegionsSeq)
{
  CORBA::ULong i;
  CORBA::ULong j;
  CORBA::ULong iLen;
  CORBA::ULong jLen;
  size_t sLen;
  bool firstTimei = true;
  bool firstTimej = true;

  strcpy(theGalMsg, theDesc);
  iLen = theAttributeRegionsSeq.length();
  for (i = 0; i < iLen; i++)
  {
    sLen = strlen(theGalMsg);
    if (firstTimei)
    {
      sprintf(&theGalMsg[sLen],"a=%d,", theAttributeRegionsSeq[i].theAttribute);
      firstTimei = false;
    }
    else
    {
      sprintf(&theGalMsg[sLen],",a=%d,", theAttributeRegionsSeq[i].theAttribute);
    }
    firstTimej = true;
    jLen = theAttributeRegionsSeq[i].theRegions.length();
    for (j = 0; j < jLen; j++)
    {
      sLen = strlen(theGalMsg);
      if (firstTimej)
      {
        sprintf(&theGalMsg[sLen],"r=%d", theAttributeRegionsSeq[i].theRegions[j]);
        firstTimej = false;
      }
      else
      {
        sprintf(&theGalMsg[sLen],",%d", theAttributeRegionsSeq[i].theRegions[j]);
      }
    }
  }
}

void GERTICO::Mapper::printGeRtiFactoryHandles(char *theDesc, char *theGalMsg, GeRtiFactory::Handles const &theHandles)
{
  bool firstTime = true;
  int i;
  int len = theHandles.length();

  strcpy(theGalMsg, theDesc);
  for (i = 0; i < len; i++)
  {
    size_t lenStr = strlen(theGalMsg);
    if (firstTime)
    {
      sprintf(&theGalMsg[lenStr],"%d", theHandles[i]);
      firstTime = false;
    }
    else
    {
      sprintf(&theGalMsg[lenStr],",%d", theHandles[i]);
    }
  }
}

void GERTICO::Mapper::printHandleSet(char *theDesc, char *theGalMsg, GERTICO::HandleSet &theHandles)
{
  GERTICO::HandleSet::iterator itHandle;
  bool firstTime = true;

  strcpy(theGalMsg, theDesc);
  for (itHandle = theHandles.begin(); itHandle != theHandles.end(); itHandle++)
  {
    size_t len = strlen(theGalMsg);
    if (firstTime)
    {
      sprintf(&theGalMsg[len],"%d", *itHandle);
      firstTime = false;
    }
    else
    {
      sprintf(&theGalMsg[len],",%d", *itHandle);
    }
  }
}

#ifdef IEEE_1516
void GERTICO::Mapper::printHandleSetMap(char *theDesc, char *theGalMsg, GERTICO::HandleSetMap &theHandles)
{
  GERTICO::HandleSet::iterator itHandle;
  GERTICO::HandleSetMap::iterator itHandleMap;
  bool firstTime = true;
  bool firstTime1 = true;
  int len;

  strcpy(theGalMsg, theDesc);
  for (itHandleMap = theHandles.begin(); itHandleMap != theHandles.end(); itHandleMap++)
  {
    len = strlen(theGalMsg);
    if (firstTime)
    {
      sprintf(&theGalMsg[len],"%d", itHandleMap->first);
      firstTime = false;
    }
    else
    {
      sprintf(&theGalMsg[len],";%d", itHandleMap->first);
    }

    firstTime1 = true;
    for (itHandle = itHandleMap->second.begin(); itHandle != itHandleMap->second.end(); itHandle++)
    {
      len = strlen(theGalMsg);
      if (firstTime1)
      {
        sprintf(&theGalMsg[len],"%d", *itHandle);
        firstTime1 = false;
      }
      else
      {
        sprintf(&theGalMsg[len],",%d", *itHandle);
      }
    }
  }
}
#endif

void GERTICO::Mapper::printUserSuppliedTag(char *theDesc, char *theGalMsg, GeRtiFactory::UserSuppliedTag const &theHandleValues)
{
  bool isPrintable = true;
  int i;
  CORBA::ULong ind;
  int len = theHandleValues.length();
  size_t size;

  strcpy(theGalMsg, theDesc);
  for (i = 0; i < len; i++)
  {
    if (theHandleValues[i] == 0)
    {
      continue;
    }
    if (isprint(theHandleValues[i]))
    {
      continue;
    }
    isPrintable = false;
  }

  if (isPrintable)
  {
    size = strlen(theGalMsg);
    mapULongSizet(ind, size);
  }

  for (i = 0; i < len; i++)
  {
    if (isPrintable)
    {
      theGalMsg[ind] = theHandleValues[i];
      ind += 1;
      theGalMsg[ind] = '\0';
    }
    else
    {
      size = strlen(theGalMsg);
      mapULongSizet(ind, size);
      sprintf(&theGalMsg[ind], "%2.2x", theHandleValues[i]);
    }
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::swapFour(long &out, long const &in)
{
#if defined(_M_IX86) || defined(i386)
  out = htonl(in);
#else
  memcpy((char*)&out, (char*)&in, sizeof(long));
#endif
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::Mapper::swapTwo(short &out, short const &in)
{
#if defined(_M_IX86) || defined(i386)
  out = htons(in);
#else
  memcpy((char*)&out, (char*)&in, sizeof(short));
#endif
}
