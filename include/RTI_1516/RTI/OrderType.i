/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/OrderType.i
***********************************************************************/

RTI_INLINE
RTI::OrderType::
OrderType(unsigned orderType)
  throw()
  : _orderType(orderType)
{
}

RTI_INLINE
RTI::OrderType::
OrderType(OrderType const & rhs)
  throw()
  : _orderType(rhs._orderType)
{
}

RTI_INLINE
RTI::OrderType const
RTI::OrderType::
orderUndef() throw()
{
  return 0;
}

RTI_INLINE
RTI::OrderType const
RTI::OrderType::
receive()
  throw()
{
  return 1;
}

RTI_INLINE
RTI::OrderType const
RTI::OrderType::
timestamp() throw()
{
  return 2;
}

RTI_INLINE
RTI::OrderType &
RTI::OrderType::
operator=(OrderType const & rhs)
  throw()
{
  if (this != &rhs)
  {
    _orderType = rhs._orderType;
  }
  return *this;
}

RTI_INLINE
bool
RTI::OrderType::
operator==(OrderType const & rhs) const
  throw()
{
  return ((_orderType == rhs._orderType) ? true : false);
}

RTI_INLINE
bool
RTI::OrderType::
operator!=(OrderType const & rhs) const
  throw()
{
  return ((_orderType != rhs._orderType) ? true : false);
}

RTI_INLINE
std::wstring
RTI::OrderType::
toString() const
{
  std::wstring ws;

  switch(_orderType)
  {
    case 1:
    {
      ws = L"receive";
      break;
    }
    case 2:
    {
      ws = L"timestamp";
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
