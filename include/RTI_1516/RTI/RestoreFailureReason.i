/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/RestoreFailureReason.i
***********************************************************************/

RTI_INLINE
RTI::RestoreFailureReason::
RestoreFailureReason(unsigned RestoreFailureReason)
  : _RestoreFailureReason(RestoreFailureReason)
{
}

RTI_INLINE
RTI::RestoreFailureReason::
RestoreFailureReason(RestoreFailureReason const & rhs)
  : _RestoreFailureReason(rhs._RestoreFailureReason)
{
}

RTI_INLINE
RTI::RestoreFailureReason const
RTI::RestoreFailureReason::
rtiUnableToRestore()
{
  return 1;
}

RTI_INLINE
RTI::RestoreFailureReason const
RTI::RestoreFailureReason::
federateReportedFailureDuringRestore()
{
  return 2;
}

RTI_INLINE
RTI::RestoreFailureReason const
RTI::RestoreFailureReason::
federateResignedDuringRestore()
{
  return 3;
}

RTI_INLINE
RTI::RestoreFailureReason const
RTI::RestoreFailureReason::
rtiDetectedFailureDuringRestore()
{
  return 4;
}

RTI_INLINE
RTI::RestoreFailureReason &
RTI::RestoreFailureReason::
operator=(RestoreFailureReason const & rhs)
{
  if (this != &rhs)
  {
    _RestoreFailureReason = rhs._RestoreFailureReason;
  }
  return *this;
}

RTI_INLINE
bool
RTI::RestoreFailureReason::
operator==(RestoreFailureReason const & rhs) const
{
  return ((_RestoreFailureReason == rhs._RestoreFailureReason)
          ? true : false);
}

RTI_INLINE
bool
RTI::RestoreFailureReason::
operator!=(RestoreFailureReason const & rhs) const
{
  return ((_RestoreFailureReason != rhs._RestoreFailureReason)
          ? true : false);
}

RTI_INLINE
std::wstring
RTI::RestoreFailureReason::toString() const
{
  std::wstring ws;

  switch(_RestoreFailureReason)
  {
    case 1:
    {
      ws = L"rtiUnableToRestore";
      break;
    }
    case 2:
    {
      ws = L"federateReportedFailureDuringRestore";
      break;
    }
    case 3:
    {
      ws = L"federateResignedDuringRestore";
      break;
    }
    case 4:
    {
      ws = L"rtiDetectedFailureDuringRestore";
      break;
    }
    default:
    {
      ws = L"Unknown";
      break;
    }
  }

  return ws;
}
