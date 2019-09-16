/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/EncodedLogicalTimeInterval.h
***********************************************************************/

#ifndef RTI_EncodedLogicalTimeInterval_h
#define RTI_EncodedLogicalTimeInterval_h

#include <RTI/SpecificConfig.h>

namespace RTI
{
  class RTI_EXPORT EncodedLogicalTimeInterval
  {
  public:
    virtual ~EncodedLogicalTimeInterval() throw () {}
    
    virtual void   const * data() const = 0;
    virtual size_t         size() const = 0;
  };
}

#endif // RTI_EncodedLogicalTimeInterval_h
