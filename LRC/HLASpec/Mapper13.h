/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Mapper13.h,v $
Revision 1.4  2010/05/17 07:57:12  mul
Add logical time interval.

Revision 1.3  2007/09/05 15:46:02  mul
Changes for ieee1516.

Revision 1.2  2007/05/09 13:12:03  mul
Add generic time mapper functions.

Revision 1.1  2007/05/03 14:46:17  mul
Mapper for HLA 1.3 types.

 
**
*******************************************************************************/


#ifndef Mapper13_HEADER
#define Mapper13_HEADER

// RTI C++ language mapping
#include "include/RTI_1.3/RTI.hh"
#include "LRC/config.h"
#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiFedTimeI.h"
#include "Util/GeRtiTypes.h"

/*
 */
namespace GERTICO
{
  class Mapper13
  {
  public:
    Mapper13(void);
    virtual ~Mapper13(void);

    static void mapAttributeHandleSet(GeRtiFactory::Handles &, const RTI::AttributeHandleSet &);
    static void mapAttributeHandleSet(RTI::AttributeHandleSet &, const GeRtiFactory::Handles &);

    static void mapAttributeHandleValuePairSet(GeRtiFactory::HandleValues &, const RTI::AttributeHandleValuePairSet &);
    static void mapAttributeHandleValuePairSet(RTI::AttributeHandleValuePairSet &, const GeRtiFactory::HandleValues &, const int &theGrouping, const bool theBestEffort);

    static void mapEventRetractionHandle(GeRtiFactory::ERHandle &, const RTI::EventRetractionHandle &);
    static void mapEventRetractionHandle(RTI::EventRetractionHandle &, const GeRtiFactory::ERHandle &);

    static void mapFedTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, std::auto_ptr<GERTICO::GeRtiFedTime> &out, const RTI::FedTime &in);
    static void mapFedTime(RTI::FedTime &out, const std::auto_ptr<GERTICO::GeRtiFedTime> &in);

    static void mapFedTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiFedTime &out, const RTI::FedTime &in);
    static void mapFedTime(RTI::FedTime &out, const GERTICO::GeRtiFedTime &in);

    static void mapFederateHandleSet(GeRtiFactory::Handles &, const RTI::FederateHandleSet &);

    static void mapLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, GERTICO::GeRtiLogicalTimeInterval &out, const RTI::FedTime &in);
    static void mapLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theGeRtiLogicalTimeIntervalFactory, RTI::FedTime &out, const GERTICO::GeRtiLogicalTimeInterval &in);

    static void mapParameterHandleValuePairSet(GeRtiFactory::HandleValues &, const RTI::ParameterHandleValuePairSet &);
    static void mapParameterHandleValuePairSet(RTI::ParameterHandleValuePairSet &, const GeRtiFactory::HandleValues &);

    static void mapUserSuppliedTag(char **, const GeRtiFactory::UserSuppliedTag &);
  };
};

#endif // Mapper13_HEADER
