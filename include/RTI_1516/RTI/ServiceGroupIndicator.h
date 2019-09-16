/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/ServiceGroupIndicator.h 
***********************************************************************/

#ifndef RTI_ServiceGroupIndicator_h
#define RTI_ServiceGroupIndicator_h

#include <RTI/SpecificConfig.h>
#include <string>

namespace RTI
{
  // Type safe class used to represent the service group
  class RTI_EXPORT ServiceGroupIndicator
  {
  public:
    ServiceGroupIndicator(ServiceGroupIndicator const & rhs);

    static
    ServiceGroupIndicator const
    federationManagement();
  
    static
    ServiceGroupIndicator const
    declarationManagement();

    static
    ServiceGroupIndicator const
    objectManagement();

    static
    ServiceGroupIndicator const
    ownershipManagement();

    static
    ServiceGroupIndicator const
    timeManagement();

    static
    ServiceGroupIndicator const
    dataDistributionManagement();

    static
    ServiceGroupIndicator const
    supportServices();

    ServiceGroupIndicator &
    operator=(ServiceGroupIndicator const & rhs);

    bool
    operator==(ServiceGroupIndicator const & rhs) const;

    bool
    operator!=(ServiceGroupIndicator const & rhs) const;

    std::wstring
    toString() const;

  private:
    ServiceGroupIndicator(unsigned _ServiceGroupIndicator);

    unsigned _ServiceGroupIndicator;
  };
}

#ifdef    RTI_USE_INLINE
#include "RTI/ServiceGroupIndicator.i"
#endif // RTI_USE_INLINE

namespace RTI
{
  // These constants save a little typing for users.  
  // They can be used much like a enum, but in a type-safe way
  ServiceGroupIndicator const
  FEDERATION_MANAGEMENT
  = ServiceGroupIndicator::federationManagement();

  ServiceGroupIndicator const
  DECLARATION_MANAGEMENT
  = ServiceGroupIndicator::declarationManagement();

  ServiceGroupIndicator const
  OBJECT_MANAGEMENT
  = ServiceGroupIndicator::objectManagement();

  ServiceGroupIndicator const
  OWNERSHIP_MANAGEMENT
  = ServiceGroupIndicator::ownershipManagement();

  ServiceGroupIndicator const
  TIME_MANAGEMENT
  = ServiceGroupIndicator::timeManagement();

  ServiceGroupIndicator const
  DATA_DISTRIBUTION_MANAGEMENT
  = ServiceGroupIndicator::dataDistributionManagement();

  ServiceGroupIndicator const
  SUPPORT_SERVICES
  = ServiceGroupIndicator::supportServices();
}

#endif // RTI_ServiceGroupIndicator_h
