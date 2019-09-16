/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/SaveStatus.h 
***********************************************************************/

#ifndef RTI_SaveStatus_h
#define RTI_SaveStatus_h

#include <RTI/SpecificConfig.h>
#include <string>

namespace RTI
{
  // Type safe class used to represent save status of an individual federate.
  class RTI_EXPORT SaveStatus
  {
  public:
    SaveStatus(SaveStatus const & rhs);

    static
    SaveStatus const
    noSaveInProgress();
  
    static
    SaveStatus const
    federateInstructedToSave();

    static
    SaveStatus const
    federateSaving();

    static
    SaveStatus const
    federateWaitingForFederationToSave();

    SaveStatus &
    operator=(SaveStatus const & rhs);

    bool
    operator==(SaveStatus const & rhs) const;

    bool
    operator!=(SaveStatus const & rhs) const;

    std::wstring
    toString() const;

  private:
    SaveStatus(unsigned _SaveStatus);

    unsigned _SaveStatus;
  };
}

#ifdef    RTI_USE_INLINE
#include "RTI/SaveStatus.i"
#endif // RTI_USE_INLINE

namespace RTI
{
  // These constants save a little typing for users.  
  // They can be used much like a enum, but in a type-safe way
  SaveStatus const
  NO_SAVE_IN_PROGRESS
  = SaveStatus::noSaveInProgress();

  SaveStatus const
  FEDERATE_INSTRUCTED_TO_SAVE
  = SaveStatus::federateInstructedToSave();

  SaveStatus const
  FEDERATE_SAVING
  = SaveStatus::federateSaving();

  SaveStatus const
  FEDERATE_WAITING_FOR_FEDERATION_TO_SAVE
  = SaveStatus::federateWaitingForFederationToSave();
}

#endif // RTI_SaveStatus_h
