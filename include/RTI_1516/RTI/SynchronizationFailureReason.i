/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/SynchronizationFailureReason.i
***********************************************************************/

RTI_INLINE
RTI::SynchronizationFailureReason::
SynchronizationFailureReason(unsigned SynchronizationFailureReason)
  : _SynchronizationFailureReason(SynchronizationFailureReason)
{
}

RTI_INLINE
RTI::SynchronizationFailureReason::
SynchronizationFailureReason(SynchronizationFailureReason const & rhs)
  : _SynchronizationFailureReason(rhs._SynchronizationFailureReason)
{
}

RTI_INLINE
RTI::SynchronizationFailureReason const
RTI::SynchronizationFailureReason::
synchronizationPointLabelNotUnique()
{
  return 1;
}

RTI_INLINE
RTI::SynchronizationFailureReason const
RTI::SynchronizationFailureReason::
synchronizationSetMemberNotJoined()
{
  return 2;
}

RTI_INLINE
RTI::SynchronizationFailureReason const
RTI::SynchronizationFailureReason::
federateResignedDuringSynchronization()
{
  return 3;
}

RTI_INLINE
RTI::SynchronizationFailureReason const
RTI::SynchronizationFailureReason::
rtiDetectedFailureDuringSynchronization()
{
  return 4;
}

RTI_INLINE
RTI::SynchronizationFailureReason const
RTI::SynchronizationFailureReason::
synchronizationTimeCannotBeHonored()
{
  return 5;
}

RTI_INLINE
RTI::SynchronizationFailureReason &
RTI::SynchronizationFailureReason::
operator=(SynchronizationFailureReason const & rhs)
{
  if (this != &rhs)
  {
    _SynchronizationFailureReason = rhs._SynchronizationFailureReason;
  }
  return *this;
}

RTI_INLINE
bool
RTI::SynchronizationFailureReason::
operator==(SynchronizationFailureReason const & rhs) const
{
  return ((_SynchronizationFailureReason == rhs._SynchronizationFailureReason)
          ? true : false);
}

RTI_INLINE
bool
RTI::SynchronizationFailureReason::
operator!=(SynchronizationFailureReason const & rhs) const
{
  return ((_SynchronizationFailureReason != rhs._SynchronizationFailureReason)
          ? true : false);
}

RTI_INLINE
std::wstring
RTI::SynchronizationFailureReason::
toString() const
{
  std::wstring ws;

  switch(_SynchronizationFailureReason)
  {
    case 1:
    {
      ws = L"synchronizationPointLabelNotUnique";
      break;
    }
    case 2:
    {
      ws = L"synchronizationSetMemberNotJoined";
      break;
    }
    case 3:
    {
      ws = L"federateResignedDuringSynchronization";
      break;
    }
    case 4:
    {
      ws = L"rtiDetectedFailureDuringSynchronization";
      break;
    }
    case 5:
    {
      ws = L"synchronizationTimeCannotBeHonored";
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
