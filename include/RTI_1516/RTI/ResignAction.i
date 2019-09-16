/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/ResignAction.i
***********************************************************************/

RTI_INLINE
RTI::ResignAction::
ResignAction(unsigned resignAction)
  : _resignAction(resignAction)
{
}

RTI_INLINE
RTI::ResignAction::
ResignAction(ResignAction const & rhs)
  : _resignAction(rhs._resignAction)
{
}

RTI_INLINE
RTI::ResignAction const
RTI::ResignAction::
undefAction()
{
  return 0;
}

RTI_INLINE
RTI::ResignAction const
RTI::ResignAction::
unconditionallyDivestAttributes()
{
  return 1;
}

RTI_INLINE
RTI::ResignAction const
RTI::ResignAction::
deleteObjects()
{
  return 2;
}

RTI_INLINE
RTI::ResignAction const
RTI::ResignAction::
cancelPendingOwnershipAcquisitions()
{
  return 3;
}

RTI_INLINE
RTI::ResignAction const
RTI::ResignAction::
deleteObjectsThenDivest()
{
  return 4;
}

RTI_INLINE
RTI::ResignAction const
RTI::ResignAction::
cancelThenDeleteThenDivest()
{
  return 5;
}

RTI_INLINE
RTI::ResignAction const
RTI::ResignAction::
noAction()
{
  return 6;
}

RTI_INLINE
RTI::ResignAction &
RTI::ResignAction::
operator=(ResignAction const & rhs)
{
  if (this != &rhs)
  {
    _resignAction = rhs._resignAction;
  }
  return *this;
}

RTI_INLINE
bool
RTI::ResignAction::
operator==(ResignAction const & rhs) const
{
  return ((_resignAction == rhs._resignAction) ? true : false);
}

RTI_INLINE
bool
RTI::ResignAction::
operator!=(ResignAction const & rhs) const
{
  return ((_resignAction != rhs._resignAction) ? true : false);
}

RTI_INLINE
std::wstring
RTI::ResignAction::
toString() const
{
  std::wstring ws;

  switch(_resignAction)
  {
    case 0:
    {
      ws = L"undefAction";
      break;
    }
    case 1:
    {
      ws = L"unconditionallyDivestAttributes";
      break;
    }
    case 2:
    {
      ws = L"deleteObjects";
      break;
    }
    case 3:
    {
      ws = L"cancelPendingOwnershipAcquisitions";
      break;
    }
    case 4:
    {
      ws = L"deleteObjectsThenDivest";
      break;
    }
    case 5:
    {
      ws = L"cancelThenDeleteThenDivest";
      break;
    }
    case 6:
    {
      ws = L"noAction";
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
