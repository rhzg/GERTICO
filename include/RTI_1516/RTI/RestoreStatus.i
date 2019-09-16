/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/RestoreStatus.i
***********************************************************************/

RTI_INLINE
RTI::RestoreStatus::
RestoreStatus(unsigned RestoreStatus)
  : _RestoreStatus(RestoreStatus)
{
}

RTI_INLINE
RTI::RestoreStatus::
RestoreStatus(RestoreStatus const & rhs)
  : _RestoreStatus(rhs._RestoreStatus)
{
}

RTI_INLINE
RTI::RestoreStatus const
RTI::RestoreStatus::
noRestoreInProgress()
{
  return 1;
}

RTI_INLINE
RTI::RestoreStatus const
RTI::RestoreStatus::
federateRestoreRequestPending()
{
  return 2;
}

RTI_INLINE
RTI::RestoreStatus const
RTI::RestoreStatus::
federateWaitingForRestoreToBegin()
{
  return 3;
}

RTI_INLINE
RTI::RestoreStatus const
RTI::RestoreStatus::
federatePreparedToRestore()
{
  return 4;
}

RTI_INLINE
RTI::RestoreStatus const
RTI::RestoreStatus::
federateRestoring()
{
  return 5;
}

RTI_INLINE
RTI::RestoreStatus const
RTI::RestoreStatus::
federateWaitingForFederationToRestore()
{
  return 6;
}


RTI_INLINE
RTI::RestoreStatus &
RTI::RestoreStatus::
operator=(RestoreStatus const & rhs)
{
  if (this != &rhs)
  {
    _RestoreStatus = rhs._RestoreStatus;
  }
  return *this;
}

RTI_INLINE
bool
RTI::RestoreStatus::
operator==(RestoreStatus const & rhs) const
{
  return ((_RestoreStatus == rhs._RestoreStatus) ? true : false);
}

RTI_INLINE
bool
RTI::RestoreStatus::
operator!=(RestoreStatus const & rhs) const
{
  return ((_RestoreStatus != rhs._RestoreStatus) ? true : false);
}

RTI_INLINE
std::wstring
RTI::RestoreStatus::
toString() const
{
  std::wstring ws;

  switch(_RestoreStatus)
  {
    case 1:
    {
      ws = L"noRestoreInProgress";
      break;
    }
    case 2:
    {
      ws = L"federateRestoreRequestPending";
      break;
    }
    case 3:
    {
      ws = L"federateWaitingForRestoreToBegin";
      break;
    }
    case 4:
    {
      ws = L"federatePreparedToRestore";
      break;
    }
    case 5:
    {
      ws = L"federateRestoring";
      break;
    }
    case 6:
    {
      ws = L"federateWaitingForFederationToRestore";
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
