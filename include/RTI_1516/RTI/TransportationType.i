/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/TransportationType.i
***********************************************************************/

RTI_INLINE
RTI::TransportationType::
TransportationType(unsigned transportationType)
  throw()
  : _transportationType(transportationType)
{
}

RTI_INLINE
RTI::TransportationType::
TransportationType(TransportationType const & rhs)
  throw()
  : _transportationType(rhs._transportationType)
{
}

RTI_INLINE
RTI::TransportationType const
RTI::TransportationType::
transportUndef()
  throw()
{
  return 0;
}

RTI_INLINE
RTI::TransportationType const
RTI::TransportationType::
reliable()
  throw()
{
  return 1;
}

RTI_INLINE
RTI::TransportationType const
RTI::TransportationType::
bestEffort()
  throw()
{
  return 2;
}

RTI_INLINE
RTI::TransportationType &
RTI::TransportationType::
operator =(TransportationType const & rhs)
  throw()
{
  if (this != &rhs)
  {
    _transportationType = rhs._transportationType;
  }
  return *this;
}

RTI_INLINE
bool
RTI::TransportationType::
operator==(TransportationType const & rhs) const
  throw()
{
  return ((_transportationType == rhs._transportationType) ?
		true : false);
}

RTI_INLINE
bool
RTI::TransportationType::
operator!=(TransportationType const & rhs) const
  throw()
{
  return ((_transportationType != rhs._transportationType) ?
		true : false);
}

RTI_INLINE
std::wstring
RTI::TransportationType::
toString() const
{
  std::wstring ws;

  switch(_transportationType)
  {
    case 1:
    {
      ws = L"reliable";
      break;
    }
    case 2:
    {
      ws = L"bestEffort";
      break;
    }
    default:
    {
      ws = L"unknown";
      break;
    }
  }

  return ws;
}
