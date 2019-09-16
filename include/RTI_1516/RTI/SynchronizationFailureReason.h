/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/SynchronizationFailureReason.h
***********************************************************************/

#ifndef RTI_SynchronizationFailureReason_h
#define RTI_SynchronizationFailureReason_h

#include <RTI/SpecificConfig.h>
#include <string>

namespace RTI
{
  // Type safe class used to represent type of data order.
  class RTI_EXPORT SynchronizationFailureReason
  {
  public:
    SynchronizationFailureReason(SynchronizationFailureReason const & rhs);

    static
    SynchronizationFailureReason const
    synchronizationPointLabelNotUnique();

    static
    SynchronizationFailureReason const
    synchronizationSetMemberNotJoined();

    static
    SynchronizationFailureReason const 
    federateResignedDuringSynchronization();

    static
    SynchronizationFailureReason const
    rtiDetectedFailureDuringSynchronization();

    static
    SynchronizationFailureReason const
    synchronizationTimeCannotBeHonored();

    SynchronizationFailureReason &
    operator=(SynchronizationFailureReason const & rhs);

    bool
    operator==(SynchronizationFailureReason const & rhs) const;

    bool
    operator!=(SynchronizationFailureReason const & rhs) const;

    std::wstring
    toString() const;

  private:
    SynchronizationFailureReason(unsigned SynchronizationFailureReason);

    unsigned _SynchronizationFailureReason;
  };
}

#ifdef    RTI_USE_INLINE
#include "RTI/SynchronizationFailureReason.i"
#endif // RTI_USE_INLINE

namespace RTI
{
  // These constants Synchronization a little typing for users.  
  // They can be used much like a enum, but in a type-safe way
  SynchronizationFailureReason const
  SYNCHRONIZATION_POINT_LABEL_NOT_UNIQUE =
  SynchronizationFailureReason::synchronizationPointLabelNotUnique();

  SynchronizationFailureReason const
  SYNCHRONIZATION_SET_MEMBER_NOT_JOINED =
  SynchronizationFailureReason::synchronizationSetMemberNotJoined();

  SynchronizationFailureReason const
  FEDERATE_RESIGNED_DURING_SYNCHRONIZATION = 
  SynchronizationFailureReason::federateResignedDuringSynchronization();

  SynchronizationFailureReason const
  RTI_DETECTED_FAILURE_DURING_SYNCHRONIZATION =
  SynchronizationFailureReason::rtiDetectedFailureDuringSynchronization();

  SynchronizationFailureReason const
  SYNCHRONIZATION_TIME_CANNOT_BE_HONORED =
  SynchronizationFailureReason::synchronizationTimeCannotBeHonored();
}

#endif // RTI_SynchronizationFailureReason_h
