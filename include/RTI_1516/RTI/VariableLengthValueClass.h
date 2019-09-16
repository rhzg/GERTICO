/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/VariableLengthValueClass.h
***********************************************************************/

#ifndef RTI_VariableLengthValueClass_h
#define RTI_VariableLengthValueClass_h

#include <RTI/SpecificConfig.h>

namespace RTI
{
  class RTI_EXPORT VariableLengthValueClass
  {
  public:
    VariableLengthValueClass();
    VariableLengthValueClass(void const * inData, size_t inSize);
    VariableLengthValueClass(VariableLengthValueClass const & rhs);

    ~VariableLengthValueClass();

    VariableLengthValueClass &
    operator=(VariableLengthValueClass const & rhs);

    void   const * data() const;
    size_t         size() const;

  private:
    size_t _size;
    char * _data;
  };
}

#ifdef    RTI_USE_INLINE
#include "RTI/VariableLengthValueClass.i"
#endif // RTI_USE_INLINE

#endif // RTI_VariableLengthValueClass_h
