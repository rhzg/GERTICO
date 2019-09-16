/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/TransportationType.h
***********************************************************************/

#ifndef RTI_TransportationType_h
#define RTI_TransportationType_h

#include <RTI/SpecificConfig.h>
#include <RTI/Typedefs.h> // for RTI::EncodedData
#include <string>

namespace RTI
{
  // Type safe class used to represent type of data transportation.
  class RTI_EXPORT TransportationType
  {
  public:
    TransportationType(EncodedData const & rhs);
    
    TransportationType(TransportationType const & rhs)
      throw ();
    
    static
    TransportationType const
    reliable()
      throw();
    
    static
    TransportationType const
    bestEffort()
      throw();

    static
    TransportationType const
    transportUndef()
      throw();
  
    TransportationType &
    operator =(TransportationType const & rhs)
      throw();
    
    bool
    operator ==(TransportationType const & rhs) const
      throw();
    
    bool
    operator !=(TransportationType const & rhs) const
      throw();
    
    std::wstring
    toString() const;
    
    EncodedData
    encode() const
      throw();
    
  private:
    TransportationType(unsigned transportationType)
      throw();
    
    unsigned _transportationType;
  };
}

#ifdef    RTI_USE_INLINE
#include "RTI/TransportationType.i"
#endif // RTI_USE_INLINE

namespace RTI
{
  // These constants save a little typing for users.  
  // They can be used much like a enum, but in a type-safe way
  TransportationType const
  RELIABLE = 
  TransportationType::reliable();
  
  TransportationType const
  BEST_EFFORT = 
  TransportationType::bestEffort();

  TransportationType const
  TRANSPORT_UNDEF = 
  TransportationType::transportUndef();
}

#endif // RTI_TransportationType_h
