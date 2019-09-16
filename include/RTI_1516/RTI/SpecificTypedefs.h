/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/SpecificTypedefs.h
***********************************************************************/

// Purpose: This file contains definitions for RTI types that are specific to
// the RTI implementation. The parameterized classes RTI::Handle and RTI::Value
// enable the RTI implementation to insert a private member. The private
// member declaration must be exposed in this header file. These
// implementation specific declarations and definitions should not be
// utilized since it is non-standard with respect to RTI implementations.

#ifndef RTI_SpecificTypedefs_h
#define RTI_SpecificTypedefs_h

//
// The following typedefs are an  of specific implementations that could
// be used by an RTI implementation.  RTI implementators are free to change
// these typedefs.
//

#include <RTI/SpecificConfig.h>

//
// This class is an  of something that is RTI implementor specific.
//
#include <RTI/VariableLengthValueClass.h>

namespace RTI
{
  typedef VariableLengthValueClass AttributeValueImplementationType;
  typedef VariableLengthValueClass ParameterValueImplementationType;
  typedef VariableLengthValueClass UserSuppliedTagImplementationType;
  typedef VariableLengthValueClass EncodedDataImplementationType;

  typedef VariableLengthValueClass AttributeValueReturnType;
  typedef VariableLengthValueClass ParameterValueReturnType;
  typedef VariableLengthValueClass UserSuppliedTagReturnType;
  typedef VariableLengthValueClass EncodedDataReturnType;

  template < class T, class T2, int i > class Value;
  typedef Value< EncodedDataImplementationType, EncodedDataReturnType, 4 > EncodedData;

  //class FederateHandleImplementation;
  class FederateHandleFactory;
  typedef long FederateHandleImplementationType;
  typedef EncodedData EncodedFederateHandleImplementationType;
  typedef long FederateHandleReturnType;
  
  //
  // For the remaining handles, long will be used as an  implementation
  //
  class ObjectClassHandleFactory;
  typedef long ObjectClassHandleImplementationType;
  typedef EncodedData EncodedObjectClassHandleImplementationType;
  typedef long ObjectClassHandleReturnType;
  
  class InteractionClassHandleFactory;
  typedef long InteractionClassHandleImplementationType;
  typedef EncodedData EncodedInteractionClassHandleImplementationType;
  typedef long InteractionClassHandleReturnType;
  
  class ObjectInstanceHandleFactory;
  typedef long ObjectInstanceHandleImplementationType;
  typedef EncodedData EncodedObjectInstanceHandleImplementationType;
  typedef long ObjectInstanceHandleReturnType;
  
  class AttributeHandleFactory;
  typedef long AttributeHandleImplementationType;
  typedef EncodedData EncodedAttributeHandleImplementationType;
  typedef long AttributeHandleReturnType;
  
  class ParameterHandleFactory;
  typedef long ParameterHandleImplementationType;
  typedef EncodedData EncodedParameterHandleImplementationType;
  typedef long ParameterHandleReturnType;
  
  class DimensionHandleFactory;
  typedef long DimensionHandleImplementationType;
  typedef EncodedData EncodedDimensionHandleImplementationType;
  typedef long DimensionHandleReturnType;
  
  class MessageRetractionHandleFactory;
  typedef VariableLengthValueClass MessageRetractionHandleImplementationType;
  typedef EncodedData EncodedMessageRetractionHandleImplementationType;
  typedef VariableLengthValueClass MessageRetractionHandleReturnType;
  
  class RegionHandleFactory;
  typedef long RegionHandleImplementationType;
  typedef EncodedData EncodedRegionHandleImplementationType;
  typedef long RegionHandleReturnType;
}  

//
// More RTI implementor-specific declarations
//
/*
bool operator==(RTI::FederateHandleImplementation const & lhs,
                RTI::FederateHandleImplementation const & rhs);
bool operator!=(RTI::FederateHandleImplementation const & lhs,
                RTI::FederateHandleImplementation const & rhs);
bool operator< (RTI::FederateHandleImplementation const & lhs,
                RTI::FederateHandleImplementation const & rhs);
*/
#endif // RTI_SpecificTypedefs_h
