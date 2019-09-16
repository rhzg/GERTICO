/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/VariableLengthValueClass.i
***********************************************************************/

#include <string.h>

RTI_INLINE
RTI::VariableLengthValueClass::
VariableLengthValueClass()
: _size (0),
  _data (new char[1])
{
}

RTI_INLINE
RTI::VariableLengthValueClass::
VariableLengthValueClass(void const * inData,
                         size_t inSize)
: _size (inSize),
  _data (new char[inSize])
{
  memcpy (_data,inData,_size);
}

RTI_INLINE
RTI::VariableLengthValueClass::
~VariableLengthValueClass()
{
  delete [] _data;
}

RTI_INLINE
RTI::VariableLengthValueClass::
VariableLengthValueClass (VariableLengthValueClass const & rhs)
: _size (rhs.size()),
  _data (new char[rhs.size()])
{
  memcpy (_data,rhs.data(),_size);
}   

RTI_INLINE
RTI::VariableLengthValueClass & 
RTI::VariableLengthValueClass::
operator=(VariableLengthValueClass const & rhs)
{
  if (this == & rhs) 
  {
    return *this;
  }
  
  delete [] _data;
  _size = rhs.size();
  _data = new char[_size];
  memcpy(_data,rhs.data(),_size);
  return *this;
}

RTI_INLINE
void const * 
RTI::VariableLengthValueClass::
data() const
{
  return _data;
}

RTI_INLINE
size_t
RTI::VariableLengthValueClass::
size() const
{
  return _size;
}
