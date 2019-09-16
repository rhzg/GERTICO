/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Mapper1516.h,v $
Revision 1.6  2010/05/17 08:01:18  mul
Add logical time interval.

Revision 1.5  2008/11/19 14:07:39  mul
Changes for logging.

Revision 1.4  2007/10/08 07:54:57  mul
Change memory management.

Revision 1.3  2007/09/25 08:24:09  mul
Changes for ddm.

Revision 1.2  2007/09/05 15:41:47  mul
Changes for ieee1516.

Revision 1.1  2007/06/26 08:25:28  mul
New files for ieee1516.

 
**
*******************************************************************************/


#ifndef Mapper1516_HEADER
#define Mapper1516_HEADER

// RTI 1516 C++ language mapping
#include "RTI/1516.h"
#include "RTI/EncodedLogicalTime.h"
#include "RTI/EncodedLogicalTimeInterval.h"
#include "LRC/config.h"
#include "Util/GeRtiTypes.h"
#include "Util/XercesInclude.h"
#include "idl/GeRtiFactoryS.h"

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
namespace GERTICO
{
  typedef std::map<RTI::AttributeHandle, RTI::AttributeValue> MyAttributeHandleValueMap;
  typedef std::pair<RTI::AttributeHandleSet, RTI::RegionHandleSet> AttributeHandleSetRegionHandleSetPair;
  typedef std::vector<AttributeHandleSetRegionHandleSetPair> AttHandleSetRegionHandleSetPairVector;
  typedef std::map<RTI::ParameterHandle, RTI::ParameterValue> MyParameterHandleValueMap;

  class EncodedLogicalTimeI : RTI::EncodedLogicalTime
  {
    RTI::VariableLengthValueClass _value;

  public:
    EncodedLogicalTimeI(void *theTimeData, unsigned int const &theLength);
    virtual ~EncodedLogicalTimeI() throw ();

    virtual void   const * data() const;
    virtual size_t         size() const;
  };

  class EncodedLogicalTimeIntervalI : RTI::EncodedLogicalTimeInterval
  {
    RTI::VariableLengthValueClass _value;

  public:
    EncodedLogicalTimeIntervalI(void *theTimeData, unsigned int const &theLength);
    virtual ~EncodedLogicalTimeIntervalI() throw ();

    virtual void   const * data() const;
    virtual size_t         size() const;
  };

  class MessageRetractionHandleI : RTI::MessageRetractionHandle
  {
    GeRtiFactory::GeRtiHandle sendingFederate;
    GeRtiFactory::GeRtiHandle serialNumber;
  public:
    MessageRetractionHandleI(GeRtiFactory::GeRtiHandle const &theSendingFederate, GeRtiFactory::GeRtiHandle const &theSerialNumber);
    MessageRetractionHandleI(MessageRetractionHandleI const &theMessageRetractionHandleI);
    virtual ~MessageRetractionHandleI(void);

    void getSendingFederate(GeRtiFactory::GeRtiHandle &theSendingFederate) const;
    void getSerialNumber(GeRtiFactory::GeRtiHandle &theSerialNumber) const;
  };

  class UpperLowerBounds
  {
  public:
    GeRtiFactory::GeRtiHandle lower;
    GeRtiFactory::GeRtiHandle upper;

    UpperLowerBounds(GeRtiFactory::GeRtiHandle const &theLower, GeRtiFactory::GeRtiHandle const &theUpper);
    ~UpperLowerBounds(void);
  };

  // Key is dimension id.
  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::UpperLowerBounds *, cmpHandle> BoundsMap;

  class Mapper1516
  {
  public:
    Mapper1516(void);
    virtual ~Mapper1516(void);

    static void mapAttributeHandle(GeRtiFactory::GeRtiHandle &out, RTI::AttributeHandle const &in);
    static void mapAttributeHandle(RTI::AttributeHandle &out, GeRtiFactory::GeRtiHandle const &in);

    static void mapAttributeHandleSet(GeRtiFactory::Handles &out, RTI::AttributeHandleSet const &in);
    static void mapAttributeHandleSet(RTI::AttributeHandleSet &out, GeRtiFactory::Handles const &in);

    static void mapAttributeHandleSetRegionHandleSetPairVector(GERTICO::HandleSetMap &out, RTI::AttributeHandleSetRegionHandleSetPairVector const &in);

    static void mapAttributeHandleValueMap(GeRtiFactory::HandleValues &out, RTI::AttributeHandleValueMap const &in);
    static void mapAttributeHandleValueMap(GeRtiFactory::HandleValues &out, const GeRtiFactory::HandleValues &in, const int &theGrouping, const bool theBestEffort);

    static void mapFederateHandle(RTI::FederateHandle &out, GeRtiFactory::GeRtiHandle const &in);
    static void mapFederateHandle(GeRtiFactory::GeRtiHandle &out, RTI::FederateHandle const &in);

    static void mapFederateHandleRestoreStatusPairVector(std::auto_ptr<RTI::FederateHandleRestoreStatusPairVector> &out, GeRtiFactory::RestoreStatusPairSeq const &in);

    static void mapFederateHandleSaveStatusPairVector(std::auto_ptr<RTI::FederateHandleSaveStatusPairVector> &out, GeRtiFactory::SaveStatusPairSeq const &in);

    static void mapFederateHandleSet(GeRtiFactory::Handles &out, RTI::FederateHandleSet const &in);

    static void mapDimensionHandle(GeRtiFactory::GeRtiHandle &out, RTI::DimensionHandle const &in);
    static void mapDimensionHandle(RTI::DimensionHandle &out, GeRtiFactory::GeRtiHandle const &in);

    static void mapDimensionHandleSet(GERTICO::HandleSet &out, RTI::DimensionHandleSet const &in);
    static void mapDimensionHandleSet(RTI::DimensionHandleSet &out, GeRtiFactory::Handles const &in);

    static void mapEncodedLogicalTime(RTI::EncodedLogicalTime **out, const GERTICO::GeRtiFedTime &in);

    static void mapInteractionClassHandle(GeRtiFactory::GeRtiHandle &out, RTI::InteractionClassHandle const &in);
    static void mapInteractionClassHandle(RTI::InteractionClassHandle &out, GeRtiFactory::GeRtiHandle const &in);

    static void mapLogicalTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, std::auto_ptr<GERTICO::GeRtiFedTime> &out, const RTI::LogicalTime &in);

    static void mapLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, std::auto_ptr<GERTICO::GeRtiLogicalTimeInterval> &out, RTI::LogicalTimeInterval const &in);
    static void mapLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, RTI::LogicalTimeInterval &out, GERTICO::GeRtiLogicalTimeInterval const &in);

    static void mapMessageRetractionHandle(GeRtiFactory::ERHandle &out, RTI::MessageRetractionHandle const &in);
    static void mapMessageRetractionHandle(RTI::MessageRetractionHandle &out, GeRtiFactory::ERHandle const &in);

    static void mapObjectClassHandle(GeRtiFactory::GeRtiHandle &out, RTI::ObjectClassHandle const &in);
    static void mapObjectClassHandle(RTI::ObjectClassHandle &out, GeRtiFactory::GeRtiHandle const &in);

    static void mapObjectInstanceHandle(GeRtiFactory::GeRtiHandle &out, RTI::ObjectInstanceHandle const &in);
    static void mapObjectInstanceHandle(RTI::ObjectInstanceHandle &out, GeRtiFactory::GeRtiHandle const &in);

    static void mapOrderType(GeRtiFactory::GeRtiHandle &out, RTI::OrderType const &in);

    static void mapParameterHandle(GeRtiFactory::GeRtiHandle &out, RTI::ParameterHandle const &in);
    static void mapParameterHandle(RTI::ParameterHandle &out, GeRtiFactory::GeRtiHandle const &in);

    static void mapParameterHandleValueMap(GeRtiFactory::HandleValues &out, RTI::ParameterHandleValueMap const &in);
    static void mapParameterHandleValueMap(RTI::ParameterHandleValueMap &out, GeRtiFactory::HandleValues const &in);

    static void mapRangeBounds(GERTICO::UpperLowerBounds &out, RTI::RangeBounds const &in);
    static void mapRangeBounds(RTI::RangeBounds &out, GeRtiFactory::Handles const &in);

    static void mapRegionHandle(GeRtiFactory::GeRtiHandle &out, RTI::RegionHandle const &in);
    static void mapRegionHandle(RTI::RegionHandle &out, GeRtiFactory::GeRtiHandle const &in);

    static void mapRegionHandleSet(GERTICO::HandleSet &out, RTI::RegionHandleSet const &in);
    static void mapRegionHandleSet(RTI::RegionHandleSet &out, GERTICO::HandleSet const &in);

    static void mapTransportationType(GeRtiFactory::GeRtiHandle &out, RTI::TransportationType const &in);
    static void mapTransportationType(RTI::TransportationType &out, GeRtiFactory::GeRtiHandle const &in);

    static void mapUserSuppliedTag(GeRtiFactory::UserSuppliedTag &out, RTI::UserSuppliedTag const &in);
    static void mapUserSuppliedTag(RTI::UserSuppliedTag &out, GeRtiFactory::UserSuppliedTag const &in);

    static void mapWstringTranscode(XMLCh *out, std::wstring const &in, unsigned long const &theMaxLength);
	  static void printAttributeHandleSet(const RTI::AttributeHandleSet& theAttributeHandleSet);
  };
};

#endif // Mapper1516_HEADER
