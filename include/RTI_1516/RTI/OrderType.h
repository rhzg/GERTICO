/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/OrderType.h
***********************************************************************/

#ifndef RTI_OrderType_h
#define RTI_OrderType_h

#include <RTI/SpecificConfig.h>
#include <RTI/Typedefs.h> // for RTI::EncodedData
#include <string>

namespace RTI
{
  // Type safe class used to represent type of data order.
  class RTI_EXPORT OrderType
  {
  public:
    OrderType(EncodedData const & theEncodedOrderType);

    OrderType(OrderType const & rhs)
      throw();

    static
    OrderType const
    receive()
      throw();

    static
    OrderType const
    timestamp()
      throw();

    static
    OrderType const
    orderUndef()
      throw();

    OrderType &
    operator=(OrderType const & rhs)
      throw ();

    bool
    operator==(OrderType const & rhs) const
      throw();

    bool
    operator!=(OrderType const & rhs) const
      throw();

    std::wstring
    toString() const;

    EncodedData
    encode() const
      throw();

  private:
    OrderType(unsigned orderType)
      throw();

    unsigned _orderType;
  };
}
#ifdef    RTI_USE_INLINE
#include "RTI/OrderType.i"
#endif // RTI_USE_INLINE

namespace RTI
{
  // These constants save a little typing for users.  
  // They can be used much like a enum, but in a type-safe way
  OrderType const
  RECEIVE =
  OrderType::receive();

  OrderType const
  TIMESTAMP =
  OrderType::timestamp();

  OrderType const
  ORDER_UNDEF =
  OrderType::orderUndef();
}

#endif // RTI_OrderType_h
