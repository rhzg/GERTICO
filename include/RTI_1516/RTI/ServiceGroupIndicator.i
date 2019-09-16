/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/ServiceGroupIndicator.i
***********************************************************************/

RTI_INLINE
RTI::ServiceGroupIndicator::
ServiceGroupIndicator(unsigned ServiceGroupIndicator)
  : _ServiceGroupIndicator(ServiceGroupIndicator)
{
}

RTI_INLINE
RTI::ServiceGroupIndicator::
ServiceGroupIndicator(ServiceGroupIndicator const & rhs)
  : _ServiceGroupIndicator(rhs._ServiceGroupIndicator)
{
}

RTI_INLINE
RTI::ServiceGroupIndicator const
RTI::ServiceGroupIndicator::
federationManagement()
{
  return 1;
}

RTI_INLINE
RTI::ServiceGroupIndicator const
RTI::ServiceGroupIndicator::
declarationManagement()
{
  return 2;
}

RTI_INLINE
RTI::ServiceGroupIndicator const
RTI::ServiceGroupIndicator::
objectManagement()
{
  return 3;
}

RTI_INLINE
RTI::ServiceGroupIndicator const
RTI::ServiceGroupIndicator::
ownershipManagement()
{
  return 4;
}

RTI_INLINE
RTI::ServiceGroupIndicator const
RTI::ServiceGroupIndicator::
timeManagement()
{
  return 5;
}

RTI_INLINE
RTI::ServiceGroupIndicator const
RTI::ServiceGroupIndicator::
dataDistributionManagement()
{
  return 6;
}

RTI_INLINE
RTI::ServiceGroupIndicator const
RTI::ServiceGroupIndicator::
supportServices()
{
  return 7;
}

RTI_INLINE
RTI::ServiceGroupIndicator &
RTI::ServiceGroupIndicator::
operator=(ServiceGroupIndicator const & rhs)
{
  if (this != &rhs)
  {
    _ServiceGroupIndicator = rhs._ServiceGroupIndicator;
  }
  return *this;
}

RTI_INLINE
bool
RTI::ServiceGroupIndicator::
operator==(ServiceGroupIndicator const & rhs) const
{
  return ((_ServiceGroupIndicator == rhs._ServiceGroupIndicator) ? true : false);
}

RTI_INLINE
bool
RTI::ServiceGroupIndicator::
operator!=(ServiceGroupIndicator const & rhs) const
{
  return ((_ServiceGroupIndicator != rhs._ServiceGroupIndicator) ? true : false);
}

RTI_INLINE
std::wstring
RTI::ServiceGroupIndicator::
toString() const
{
  std::wstring ws;

  switch(_ServiceGroupIndicator)
  {
    case 1:
    {
      ws = L"federationManagement";
      break;
    }
    case 2:
    {
      ws = L"declarationManagement";
      break;
    }
    case 3:
    {
      ws = L"objectManagement";
      break;
    }
    case 4:
    {
      ws = L"ownershipManagement";
      break;
    }
    case 5:
    {
      ws = L"timeManagement";
      break;
    }
    case 6:
    {
      ws = L"dataDistributionManagement";
      break;
    }
    case 7:
    {
      ws = L"supportServices";
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
