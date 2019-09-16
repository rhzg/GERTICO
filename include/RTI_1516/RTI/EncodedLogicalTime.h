/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/EncodedLogicalTime.h
***********************************************************************/

#ifndef RTI_EncodedLogicalTime_h
#define RTI_EncodedLogicalTime_h

#include <RTI/SpecificConfig.h>

namespace RTI
{
  class RTI_EXPORT EncodedLogicalTime
  {
  public:
    virtual ~EncodedLogicalTime() throw () {};
    
    virtual void   const * data() const = 0;
    virtual size_t         size() const = 0;
  };
}

#endif // RTI_EncodedLogicalTime_h
