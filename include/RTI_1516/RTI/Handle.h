/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/Handle.h
***********************************************************************/

#ifndef RTI_Handle_h
#define RTI_Handle_h

#include <RTI/SpecificConfig.h>
#include <string>

// The RTI::Handle class is used to provide the common interface to the 
// various RTI handle types used in the API.  This interface includes a
// constructor, assignment, equality, inequality, and less than operators.  The
// encode method returns a type safe EncodedHandleType instance that can be
// used to exchange handles between federates as attributes and parameters.  The
// constructor takes a EncodedHandleType which enables the type safe creation
// of a RTIhandle from encoded data passed to a federate.  The template
// parameter class HandleImplementationType provides RTI implementations 
// the ability to customize a private class member for their particular 
// implementation.  The HandleReturnType is the type returned from the 
// getImplementation method.  The int template type parameter provides the
// ability to support strong typing.

namespace RTI
{
  template <class HandleImplementationType,
            class EncodedHandleImplementationType,
            class HandleReturnType,
            int   i>
  class RTI_EXPORT Handle
  {
  public:
    typedef HandleImplementationType        HandleImplementation_t;
    typedef EncodedHandleImplementationType EncodedHandleImplementation_t;
    typedef HandleReturnType  HandleReturn_t;

    explicit
    Handle();

    explicit
    Handle(EncodedHandleImplementationType encodedHandle);
 
    ~Handle()
      throw();

    Handle(Handle const & rhs);

    Handle &
    operator=(Handle const & rhs);

    bool operator==(Handle const & rhs) const;
    bool operator!=(Handle const & rhs) const;
    bool operator< (Handle const & rhs) const;

    EncodedHandleImplementationType encode() const;

    std::wstring toString() const;

    //
    // The following methods shall only be used by the RTI implementer
    // BEGIN Implementation Specific Details
    //
    HandleReturnType getImplementation() const;

    explicit
    Handle(HandleImplementationType impl);

  private:
    
    HandleImplementationType _impl;

    // END Implementation Specific Details
  };
}

#ifdef    RTI_USE_INLINE
#include "RTI/Handle.i"
#endif // RTI_USE_INLINE

#ifdef    RTI_TEMPLATES_REQUIRE_SOURCE
#include "RTI/Handle.cpp"
#endif // RTI_TEMPLATES_REQUIRE_SOURCE

#endif // RTI_Handle_h
