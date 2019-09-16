/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/1516.h
***********************************************************************/

//
// This file is simply a convenience provided for those developers that would
// like to include everything all at once
//

#ifndef RTI_1516_h
#define RTI_1516_h

// This file contains platform specific configuration info.
#include <RTI/SpecificConfig.h>

// These file include declarations/definitions for ISO 14882 standard C++
// classes, renamed for portability.
#include <string>
#include <set>
#include <map>
#include <vector>
#include <memory>

// This file contains standard RTI type declarations/definitions.
#include <RTI/exception.h>
#include <RTI/Handle.h>
#include <RTI/Value.h>
#include <RTI/ResignAction.h>
#include <RTI/TransportationType.h>
#include <RTI/OrderType.h>
#include <RTI/SaveFailureReason.h>
#include <RTI/SaveStatus.h>
#include <RTI/SynchronizationFailureReason.h>
#include <RTI/RestoreStatus.h>
#include <RTI/RestoreFailureReason.h>
#include <RTI/ServiceGroupIndicator.h>
#include <RTI/RangeBounds.h>

// This file has RTI implementation specific declarations/definitions.
#include <RTI/SpecificTypedefs.h>

// This file contains standard RTI type declarations/definitions which depend on
// RTI implementation specific declarations/definitions.
#include <RTI/Typedefs.h>
#include <RTI/LogicalTime.h>
#include <RTI/LogicalTimeFactory.h>
#include <RTI/LogicalTimeInterval.h>
#include <RTI/LogicalTimeIntervalFactory.h>

namespace RTI
{
  static char const * const VERSION = "1516.1.5";
}

#include <RTI/FederateAmbassador.h>
#include <RTI/RTIambassador.h>

// This file provides RTI implementation specific decalarations and definitions
// that need to follow the other header files.
#include <RTI/SpecificPostamble.h>

#endif // RTI_1516_h
