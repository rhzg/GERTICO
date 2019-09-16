/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/RTIambassadorFactory.h
***********************************************************************/

#ifndef RTI_RTIambassadorFactory_h
#define RTI_RTIambassadorFactory_h

#include "RTI/exception.h"
#include "RTI/RTIambassador.h"
/*
namespace RTI
{
  class RTIinternalError;
  class BadInitializationParameter;
  class RTIambassador;
}
*/
/*
namespace std
{
  template <class T> class auto_ptr;
}
*/

#include <RTI/SpecificConfig.h>
#include <vector>
#include <string>

namespace RTI
{
  class RTI_EXPORT RTIambassadorFactory
  {
  public:
    RTIambassadorFactory();
    
    virtual
    ~RTIambassadorFactory()
      throw ();
    
    // 10.35
    std::auto_ptr< RTIambassador >
    createRTIambassador(std::vector< std::wstring > & args)
      throw (BadInitializationParameter,
             RTIinternalError);
  };
}

#endif // RTI_RTIambassadorFactory_h
