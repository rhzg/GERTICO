/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/Value.i
***********************************************************************/

template<class ValueImplementationType, class ValueReturnType, int i>
RTI_INLINE
RTI::Value<ValueImplementationType, ValueReturnType, i>::
Value ()
{
}

template<class ValueImplementationType, class ValueReturnType, int i>
RTI_INLINE
RTI::Value<ValueImplementationType, ValueReturnType, i>::
Value (void const * data,
       size_t size)
  : _impl(data,size)
{
}

template<class ValueImplementationType, class ValueReturnType, int i>
RTI_INLINE
RTI::Value<ValueImplementationType, ValueReturnType, i>::
~Value () throw()
{
}

template<class ValueImplementationType, class ValueReturnType, int i>
RTI_INLINE
RTI::Value<ValueImplementationType, ValueReturnType, i>::
Value(Value const & rhs)
  : _impl(rhs._impl)
{
}
/*
template<class ValueImplementationType, class ValueReturnType, int i>
RTI_INLINE
RTI::Value<ValueImplementationType, ValueReturnType, i>::
Value(ValueImplementationType const & impl)
  : _impl(impl)
{
}
*/
template<class ValueImplementationType, class ValueReturnType, int i>
RTI_INLINE
RTI::Value<ValueImplementationType, ValueReturnType, i> &
RTI::Value<ValueImplementationType, ValueReturnType, i>::
operator=(Value const & rhs)
{
  _impl = rhs._impl;
  return *this;
}

template<class ValueImplementationType, class ValueReturnType, int i>
RTI_INLINE
void const *
RTI::Value<ValueImplementationType, ValueReturnType, i>::
data () const
{
  return _impl.data();
}

template<class ValueImplementationType, class ValueReturnType, int i>
RTI_INLINE
size_t
RTI::Value<ValueImplementationType, ValueReturnType, i>::
size() const
{
  return _impl.size();
}

template<class ValueImplementationType, class ValueReturnType, int i>
RTI_INLINE
ValueReturnType
RTI::Value<ValueImplementationType, ValueReturnType, i>::
getImplementation() const
{
  return _impl;
}
