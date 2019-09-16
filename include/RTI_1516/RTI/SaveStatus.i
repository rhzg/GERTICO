/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/SaveStatus.i
***********************************************************************/

RTI_INLINE
RTI::SaveStatus::
SaveStatus(unsigned SaveStatus)
  : _SaveStatus(SaveStatus)
{
}

RTI_INLINE
RTI::SaveStatus::
SaveStatus(SaveStatus const & rhs)
  : _SaveStatus(rhs._SaveStatus)
{
}

RTI_INLINE
RTI::SaveStatus const
RTI::SaveStatus::
noSaveInProgress()
{
  return 1;
}

RTI_INLINE
RTI::SaveStatus const
RTI::SaveStatus::
federateInstructedToSave()
{
  return 2;
}

RTI_INLINE
RTI::SaveStatus const
RTI::SaveStatus::
federateSaving()
{
  return 3;
}

RTI_INLINE
RTI::SaveStatus const
RTI::SaveStatus::
federateWaitingForFederationToSave()
{
  return 4;
}

RTI_INLINE
RTI::SaveStatus &
RTI::SaveStatus::
operator=(SaveStatus const & rhs)
{
  if (this != &rhs)
  {
    _SaveStatus = rhs._SaveStatus;
  }
  return *this;
}

RTI_INLINE
bool
RTI::SaveStatus::
operator==(SaveStatus const & rhs) const
{
  return ((_SaveStatus == rhs._SaveStatus) ? true : false);
}

RTI_INLINE
bool
RTI::SaveStatus::
operator!=(SaveStatus const & rhs) const
{
  return ((_SaveStatus != rhs._SaveStatus) ? true : false);
}

RTI_INLINE
std::wstring
RTI::SaveStatus::
toString() const
{
  std::wstring ws;

  switch(_SaveStatus)
  {
    case 1:
    {
      ws = L"noSaveInProgress";
      break;
    }
    case 2:
    {
      ws = L"federateInstructedToSave";
      break;
    }
    case 3:
    {
      ws = L"federateSaving";
      break;
    }
    case 4:
    {
      ws = L"federateWaitingForFederationToSave";
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
