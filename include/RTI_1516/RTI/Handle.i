/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/Handle.i
***********************************************************************/

template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
RTI::Handle<HandleImplementationType,
           EncodedHandleImplementationType,
           HandleReturnType,
           i >::
Handle ()
{
}

template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
RTI::Handle<HandleImplementationType,
           EncodedHandleImplementationType,
           HandleReturnType,
           i >::
Handle (HandleImplementationType impl)
  : _impl(impl)
{
}


template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
RTI::Handle<HandleImplementationType,
           EncodedHandleImplementationType,
           HandleReturnType,
           i >::
Handle(EncodedHandleImplementationType encodedHandle)
{
  memcpy(&_impl,encodedHandle.data(), encodedHandle.size());
}

template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
RTI::Handle<HandleImplementationType,
            EncodedHandleImplementationType,
           HandleReturnType,
            i >::
Handle (Handle const & rhs)
  : _impl(rhs._impl)
{
}


template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
RTI::Handle<HandleImplementationType,
           EncodedHandleImplementationType,
           HandleReturnType,
           i >::

~Handle ()
  throw()  
{
}


template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
RTI::Handle<HandleImplementationType,
           EncodedHandleImplementationType,
           HandleReturnType,
           i > &
RTI::Handle<HandleImplementationType,
           EncodedHandleImplementationType,
           HandleReturnType,
           i >::
operator= (Handle const & rhs)
{
  if (&rhs != this)
  {
    _impl = rhs._impl;
  }
  return *this;
}


template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
bool
RTI::Handle<HandleImplementationType,
            EncodedHandleImplementationType,
            HandleReturnType,
            i >::
operator== (Handle const & rhs) const
{
  return _impl == rhs._impl;
}


template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
bool
RTI::Handle<HandleImplementationType,
           EncodedHandleImplementationType,
           HandleReturnType,
           i >::
operator!= (Handle const & rhs) const
{
  return _impl != rhs._impl;
}


template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
bool
RTI::Handle<HandleImplementationType,
           EncodedHandleImplementationType,
           HandleReturnType,
           i >::
operator< (Handle const & rhs) const
{
  return _impl < rhs._impl;
}


template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
EncodedHandleImplementationType
RTI::Handle<HandleImplementationType,
            EncodedHandleImplementationType,
            HandleReturnType,
            i >::
encode() const
{
  return EncodedHandleImplementationType(&_impl,
			    sizeof(HandleImplementationType));
}

template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
std::wstring
RTI::Handle<HandleImplementationType,
           EncodedHandleImplementationType,
           HandleReturnType,
           i >::
toString() const
{
  std::wstring ws;
  wchar_t wtxt[512];
  swprintf(wtxt,512,L"%d",_impl);
  ws = wtxt;
  return ws;
}

template<class HandleImplementationType,
         class EncodedHandleImplementationType,
         class HandleReturnType,
         int   i>
HandleReturnType
RTI::Handle<HandleImplementationType,
           EncodedHandleImplementationType,
           HandleReturnType,
           i >::
getImplementation() const
{
  return _impl;
}
