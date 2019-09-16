/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/SaveFailureReason.i
***********************************************************************/

RTI_INLINE
RTI::SaveFailureReason::
SaveFailureReason(unsigned saveFailureReason)
: _saveFailureReason(saveFailureReason)
{
}

RTI_INLINE
RTI::SaveFailureReason::
SaveFailureReason(SaveFailureReason const & rhs)
: _saveFailureReason(rhs._saveFailureReason)
{
}

RTI_INLINE
RTI::SaveFailureReason const
RTI::SaveFailureReason::
rtiUnableToSave()
{
  return 1;
}

RTI_INLINE
RTI::SaveFailureReason const
RTI::SaveFailureReason::
federateReportedFailureDuringSave()
{
  return 2;
}

RTI_INLINE
RTI::SaveFailureReason const
RTI::SaveFailureReason::
federateResignedDuringSave()
{
  return 3;
}

RTI_INLINE
RTI::SaveFailureReason const
RTI::SaveFailureReason::
rtiDetectedFailureDuringSave()
{
  return 4;
}

RTI_INLINE
RTI::SaveFailureReason const
RTI::SaveFailureReason::
saveTimeCannotBeHonored()
{
  return 5;
}

RTI_INLINE
RTI::SaveFailureReason &
RTI::SaveFailureReason::
operator=(SaveFailureReason const & rhs)
{
  if (this != &rhs)
  {
    _saveFailureReason = rhs._saveFailureReason;
  }
  return *this;
}

RTI_INLINE
bool
RTI::SaveFailureReason::
operator==(SaveFailureReason const & rhs) const
{
  return ((_saveFailureReason == rhs._saveFailureReason)
          ? true : false);
}

RTI_INLINE
bool
RTI::SaveFailureReason::
operator!=(SaveFailureReason const & rhs) const
{
  return ((_saveFailureReason != rhs._saveFailureReason)
          ? true : false);
}

RTI_INLINE
std::wstring
RTI::SaveFailureReason::
toString() const
{
  std::wstring ws;

  switch(_saveFailureReason)
  {
    case 1:
    {
      ws = L"rtiUnableToSave";
      break;
    }
    case 2:
    {
      ws = L"federateReportedFailureDuringSave";
      break;
    }
    case 3:
    {
      ws = L"federateResignedDuringSave";
      break;
    }
    case 4:
    {
      ws = L"rtiDetectedFailureDuringSave";
      break;
    }
    case 5:
    {
      ws = L"saveTimeCannotBeHonored";
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
