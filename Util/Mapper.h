/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** Mapper.h
**
*******************************************************************************/

#ifndef Mapper_HEADER
#define Mapper_HEADER

#include <xercesc/parsers/XercesDOMParser.hpp>
using namespace xercesc;

#include <string>
// RTI C++ language mapping
#include "LRC/config.h"
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiFedTime.h"
#include "Util/GeRtiTypes.h"

/*
 * Use this class to map the RCI_SOCKET / RTI_IDL types
 */
namespace GERTICO
{
  class Mapper
  {
    static void swapFour(long &out, long const &in);
    static void swapTwo(short &out, short const &in);
  public:
    Mapper();
    virtual ~Mapper();

    static void mapAttributeRegionsSeqFromHandleSetMap(GeRtiFactory::AttributeRegionsSeq &out, GERTICO::HandleSetMap const &in);
    static void mapAttributeSubscribersSeqFromHandleSetMap(GeRtiFactory::AttributeSubscribersSeq &out, GERTICO::HandleSetMap const &in);
    static void mapHandleSetMapFromAttributeSubscribersSeq(GERTICO::HandleSetMap &out, GeRtiFactory::AttributeSubscribersSeq const &in);

    static void mapHandleSetMapFromAttributeRegionsSeq(GERTICO::HandleSetMap &out, GeRtiFactory::AttributeRegionsSeq const &in);

    static void mapHandleSet(GERTICO::HandleSet &out, GeRtiFactory::Handles const &in);
    static void mapHandleSet(GeRtiFactory::Handles &out, GERTICO::HandleSet const &in);

    static void mapHandleSetMapInvert(GERTICO::HandleSetMap &out, GERTICO::HandleSetMap const &in);

    static void mapHandleValue(GeRtiFactory::HandleValue &theHandleValue, GeRtiFactory::GeRtiHandle const &theId, char const *theBuff);

    static void mapSizetULong(size_t &out, CORBA::ULong const &in);
    static void mapULongSizet(CORBA::ULong &out, size_t const &in);

    static void mapUserSuppliedTag(GeRtiFactory::UserSuppliedTag &, char const *);
    static void mapUserSuppliedTag(char **, GeRtiFactory::UserSuppliedTag const &);

    static void mapOctetSequence(char **, GeRtiFactory::OctetSequence const &theOctetSequence);
    static void mapStringFromWstring(std::string &theString, std::wstring const &theWstring);
    static void mapWstringFromChar(std::wstring &theWstring, char const *theBuff);

    static void mapWcharFromWstring(CORBA::WChar **theBuff, std::wstring const &theWstring);
    static void mapWstringFromWchar(std::wstring &theWstring, CORBA::WChar const *theBuff);

    static void nameToLower(std::string &theString);
    static void nameToLower(std::wstring &theWstring);
    static void printAttributeHandleValue(char *theDesc, char *theGalMsg, GeRtiFactory::HandleValue const &theHandleValue);
    static void printGeRtiFactoryAttributeRegionsSeq(char *theDesc, char *theGalMsg, GeRtiFactory::AttributeRegionsSeq const &theAttributeRegionsSeq);
    static void printGeRtiFactoryHandles(char *theDesc, char *theGalMsg, GeRtiFactory::Handles const &theHandles);
    static void printHandleSet(char *theDesc, char *theGalMsg, GERTICO::HandleSet &theHandles);
    static void printUserSuppliedTag(char *theDesc, char *theGalMsg, GeRtiFactory::UserSuppliedTag const &theTag);

#ifdef IEEE_1516
    static void mapHandleValueFromWstring(GeRtiFactory::HandleValue &theHandleValue, GeRtiFactory::GeRtiHandle const &theId, std::wstring const &theWstring);
    static void mapHLAAttributesFromOctetSequence(GeRtiFactory::Handles &theAttributes, GeRtiFactory::OctetSequence const &theOctetSequence);
    static void mapHLAboolean(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, bool const &theBool);
    static void mapHLAfederateState(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, GERTICO::FederateState const &theFederateState);
    static void mapHLAhandle(GeRtiFactory::HandleValue &theHandleValue, GeRtiFactory::GeRtiHandle const &theId, unsigned long const &theHandle);
    static void mapHLAhandleList(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, GERTICO::HandleSet const &theHandleSet);
    static void mapHLAhandleListBool(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, GERTICO::HandleBoolMap const &theHandleBoolMap);
    static void mapHLAinteger32BE(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, CORBA::ULong const &theCount);
    static void mapHLAlogicalTime(GeRtiFactory::HandleValue &theHandleValue, GeRtiFactory::GeRtiHandle const &theId, std::auto_ptr<GERTICO::GeRtiFedTime> &theLogicalTime);
    static void mapHLAlogicalTimeInterval(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval);
    static void mapHLAlongFromOctetSequence(long &theLong, GeRtiFactory::OctetSequence const &theOctetSequence);
    static void mapHLAobjectClassBasedCounts(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, GERTICO::HandleMap const &theHandleMap);
    static void mapHLAtimeManagerState(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, bool const &theBool);
    static void mapHLAunicodeWstring(GeRtiFactory::HandleValue &theHandleValue, const GeRtiFactory::GeRtiHandle &theId, std::wstring const &theWstring);
    static void mapHLAwstring(GeRtiFactory::HandleValue &theHandleOut, GeRtiFactory::GeRtiHandle const &theId, std::wstring const &theWstring);
    static void mapHLAwstringFromOctetSequence(std::wstring &theWstring, GeRtiFactory::OctetSequence const &theOctetSequence);
    static void mapWstringFromXMLCh(std::wstring &theWstring, XMLCh const *theXMLCh);
    static void getOrderType(GeRtiFactory::GeRtiHandle &theOrderingType, GeRtiFactory::OctetSequence const &theOctetSequence);
    static void getTransportationType(GeRtiFactory::GeRtiHandle &theTransportationType, GeRtiFactory::OctetSequence const &theOctetSequence);
    static void printHandleSetMap(char *theDesc, char *theGalMsg, GERTICO::HandleSetMap &theHandles);
#else
    static void getOrderType(GeRtiFactory::GeRtiHandle &theOrderingType, char *theBuff);
    static void getTransportationType(GeRtiFactory::GeRtiHandle &theTransportationType, char *theBuff);
#endif
  };
};

#endif // Mapper_HEADER
