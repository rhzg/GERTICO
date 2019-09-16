/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/Value.h
***********************************************************************/

#ifndef RTI_Value_h
#define RTI_Value_h

#include <RTI/SpecificConfig.h>
  
// The RTI::Value class is used to as a generic value holder that contains a
// pointer to the memory location and the size of the value.  This class is
// used for attributes, parameters, and user supplied tags.  The constructor
// takes a pointer to the data value and the size of the data.  The key methods
// on this class is the data method which returns a constant pointer to the
// value memory location, and the size method which returns the size in bytes
// of the value.  The templatized class ValueImplementationType provides RTI
// implementations the ability to customize their particular implementation.
// The int template type parameter provides the ability to support strong
// typing.

namespace RTI
{
  template < class ValueImplementationType, 
             class ValueReturnType, 
             int i >
  class RTI_EXPORT Value
  {
  public:
    typedef ValueImplementationType ValueImplementation_t;
    typedef ValueReturnType ValueReturn_t;

    Value ();

    Value (void const * data, size_t size);

    ~Value()
      throw ();

    Value(Value const & rhs);

    Value &
    operator=(Value const & rhs);

    void const *
    data() const;
 
    size_t
    size() const;

    //
    // The following methods shall only be used by the RTI implementer
    // BEGIN Implementation Specific Details
    //
    ValueReturnType getImplementation() const;

  private:
    ValueImplementationType _impl;
    // END Implementation Specific Details
  };
}

#ifdef    RTI_USE_INLINE
#include "RTI/Value.i"
#endif // RTI_USE_INLINE

#ifdef    RTI_TEMPLATES_REQUIRE_SOURCE
#include "RTI/Value.cpp"
#endif // RTI_TEMPLATES_REQUIRE_SOURCE

#endif // RTI_Value_h
