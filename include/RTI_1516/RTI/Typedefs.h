/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/Typedefs.h
***********************************************************************/

// Purpose: This file contains the standard RTI types that are defined in 
// namespace RTI.  These definitions/declarations are standard for all RTI
// implementations.
//
// The types declared here require the use of some RTI Specific types.

#ifndef RTI_Typedefs_h
#define RTI_Typedefs_h

#include "RTI/SaveStatus.h"
#include "RTI/RestoreStatus.h"

// The following type definitions use standard C++ classes for containers
// that are used in the RTI API.

#include <set>
#include <map>
#include <vector>
#include <RTI/SpecificTypedefs.h>

namespace RTI
{
  template < class T, class T2, int i > class Value;

  typedef Value< AttributeValueImplementationType, AttributeValueReturnType,  1 > AttributeValue;
  typedef Value< ParameterValueImplementationType, ParameterValueReturnType,  2 > ParameterValue;
  typedef Value< UserSuppliedTagImplementationType, UserSuppliedTagReturnType, 3 > UserSuppliedTag;
  typedef Value< EncodedDataImplementationType, EncodedDataReturnType,     4 > EncodedData;

  template <class HandleImplementationType,
            class EncodedHandleImplementationType,
            class HandleReturnType,
            int   i>
            class Handle;

  //
  // The existence of these typedefs is required by the API Specification.
  // However, their particular definition is implementation-specific.
  //
  typedef RTI::Handle< FederateHandleImplementationType,
                  EncodedFederateHandleImplementationType,
                  FederateHandleReturnType,
                  1 >
    FederateHandle;

  typedef RTI::Handle< ObjectClassHandleImplementationType,
                  EncodedObjectClassHandleImplementationType,
                  ObjectClassHandleReturnType,
                  2 >
    ObjectClassHandle;
  
  typedef RTI::Handle< InteractionClassHandleImplementationType,
                  EncodedInteractionClassHandleImplementationType,
                  InteractionClassHandleReturnType,
                  3 >
    InteractionClassHandle;
  
  typedef RTI::Handle< ObjectInstanceHandleImplementationType,
                  EncodedObjectInstanceHandleImplementationType,
                  ObjectInstanceHandleReturnType,
                  4 >
    ObjectInstanceHandle;
  
  typedef RTI::Handle< AttributeHandleImplementationType,
                  EncodedAttributeHandleImplementationType,
                  AttributeHandleReturnType,
                  5 >
    AttributeHandle;
  
  typedef RTI::Handle< ParameterHandleImplementationType,
                  EncodedParameterHandleImplementationType,
                  ParameterHandleReturnType,
                  6 >
    ParameterHandle;
  
  typedef RTI::Handle< DimensionHandleImplementationType,
                  EncodedDimensionHandleImplementationType,
                  DimensionHandleReturnType,
                  7 >
    DimensionHandle;
  
  typedef RTI::Handle< MessageRetractionHandleImplementationType,
                  EncodedMessageRetractionHandleImplementationType,
                  MessageRetractionHandleReturnType,
                  8 >
    MessageRetractionHandle;
  
  typedef RTI::Handle< RegionHandleImplementationType,
                  EncodedRegionHandleImplementationType,
                  RegionHandleReturnType,
                  9 >
    RegionHandle;

  typedef std::set< AttributeHandle > AttributeHandleSet;
  typedef std::set< FederateHandle  > FederateHandleSet;
  typedef std::set< DimensionHandle > DimensionHandleSet;
  typedef std::set< RegionHandle    > RegionHandleSet;

  // RTI::AttributeHandleValueMap implements a constrained set of 
  // (attribute handle and value) pairs
  typedef std::map< AttributeHandle, AttributeValue >
  AttributeHandleValueMap;

  // RTI::ParameterHandleValueMap implements a constrained set of 
  // (parameter handle and value) pairs
  typedef std::map< ParameterHandle, ParameterValue >
  ParameterHandleValueMap;

  // RTI::AttributeHandleSetRegionHandleSetPairVector implements a collection of
  // (attribute handle set and region set) pairs
  typedef std::pair< AttributeHandleSet, RegionHandleSet >
  AttributeHandleSetRegionHandleSetPair;
  
  typedef std::vector< AttributeHandleSetRegionHandleSetPair >
  AttributeHandleSetRegionHandleSetPairVector;
  
  // RTI::FederateHandleSaveStatusPairVector implements a collection of
  // (federate handle and save status) pairs
  typedef std::pair< FederateHandle, SaveStatus >
  FederateHandleSaveStatusPair;
  
  typedef std::vector< FederateHandleSaveStatusPair >
  FederateHandleSaveStatusPairVector;
  
  // RTI::FederateHandleRestoreStatusPairVector implements a collection of
  // (federate handle and restore status) pairs
  typedef std::pair< FederateHandle, RestoreStatus >
  FederateHandleRestoreStatusPair;
  
  typedef std::vector< FederateHandleRestoreStatusPair >
  FederateHandleRestoreStatusPairVector;
}

#endif // RTI_Typedefs_h
