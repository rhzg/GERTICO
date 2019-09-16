/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/SaveFailureReason.h
***********************************************************************/

#ifndef RTI_SaveFailureReason_h
#define RTI_SaveFailureReason_h

#include <RTI/SpecificConfig.h>
#include <string>

namespace RTI
{
  // Type safe class used to represent type of data order.
  class RTI_EXPORT SaveFailureReason
  {
  public:
    SaveFailureReason(SaveFailureReason const & rhs);
    
    static
    SaveFailureReason const
    rtiUnableToSave();

    static
    SaveFailureReason const
    federateReportedFailureDuringSave();

    static
    SaveFailureReason const
    federateResignedDuringSave();

    static
    SaveFailureReason const
    rtiDetectedFailureDuringSave();

    static
    SaveFailureReason const
    saveTimeCannotBeHonored();

    SaveFailureReason &
    operator=(SaveFailureReason const & rhs);

    bool
    operator==(SaveFailureReason const & rhs) const;

    bool
    operator!=(SaveFailureReason const & rhs) const;

    std::wstring
    toString() const;

  private:
    SaveFailureReason(unsigned saveFailureReason);

    unsigned _saveFailureReason;
  };
}

#ifdef    RTI_USE_INLINE
#include "RTI/SaveFailureReason.i"
#endif // RTI_USE_INLINE

namespace RTI
{
  // These constants save a little typing for users.  
  // They can be used much like a enum, but in a type-safe way
  SaveFailureReason const
  RTI_UNABLE_TO_SAVE =
  SaveFailureReason::rtiUnableToSave();

  SaveFailureReason const
  FEDERATE_REPORTED_FAILURE_DURING_SAVE =
  SaveFailureReason::federateReportedFailureDuringSave();

  SaveFailureReason const
  FEDERATE_RESIGNED_DURING_SAVE = 
  SaveFailureReason::federateResignedDuringSave();

  SaveFailureReason const
  RTI_DETECTED_FAILURE_DURING_SAVE =
  SaveFailureReason::rtiDetectedFailureDuringSave();

  SaveFailureReason const
  SAVE_TIME_CANNOT_BE_HONORED =
  SaveFailureReason::saveTimeCannotBeHonored();
}

#endif // RTI_SaveFailureReason_h
