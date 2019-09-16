/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/RestoreFailureReason.h
***********************************************************************/

#ifndef RTI_RestoreFailureReason_h
#define RTI_RestoreFailureReason_h

#include <RTI/SpecificConfig.h>
#include <string>

namespace RTI
{
  // Type safe class used to represent the reason a restore failed
  class RTI_EXPORT RestoreFailureReason
  {
  public:
    RestoreFailureReason(RestoreFailureReason const & rhs);

    static
    RestoreFailureReason const
    rtiUnableToRestore();

    static
    RestoreFailureReason const
    federateReportedFailureDuringRestore();

    static
    RestoreFailureReason const
    federateResignedDuringRestore();

    static
    RestoreFailureReason const
    rtiDetectedFailureDuringRestore();

    RestoreFailureReason &
    operator=(RestoreFailureReason const & rhs);

    bool
    operator==(RestoreFailureReason const & rhs) const;

    bool
    operator!=(RestoreFailureReason const & rhs) const;

    std::wstring
    toString() const;

  private:
    RestoreFailureReason(unsigned RestoreFailureReason);

    unsigned _RestoreFailureReason;
  };
}

#ifdef    RTI_USE_INLINE
#include "RTI/RestoreFailureReason.i"
#endif // RTI_USE_INLINE

namespace RTI
{
  // These constants Restore a little typing for users.  
  // They can be used much like a enum, but in a type-safe way
  RestoreFailureReason const
  RTI_UNABLE_TO_RESTORE =
  RestoreFailureReason::rtiUnableToRestore();

  RestoreFailureReason const
  FEDERATE_REPORTED_FAILURE_DURING_RESTORE =
  RestoreFailureReason::federateReportedFailureDuringRestore();

  RestoreFailureReason const
  FEDERATE_RESIGNED_DURING_RESTORE =
  RestoreFailureReason::federateResignedDuringRestore();

  RestoreFailureReason const
  RTI_DETECTED_FAILURE_DURING_RESTORE =
  RestoreFailureReason::rtiDetectedFailureDuringRestore();
}

#endif // RTI_RestoreFailureReason_h
