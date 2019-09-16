/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/ResignAction.h 
***********************************************************************/

#ifndef RTI_ResignAction_h
#define RTI_ResignAction_h

#include <RTI/SpecificConfig.h>
#include <string>

namespace RTI
{
  // Type safe class used to represent action taken on resign. 
  class RTI_EXPORT ResignAction
  {
  public:
    ResignAction(ResignAction const & rhs);

    static
    ResignAction const
    unconditionallyDivestAttributes();
  
    static
    ResignAction const
    deleteObjects();

    static
    ResignAction const
    cancelPendingOwnershipAcquisitions();

    static
    ResignAction const
    deleteObjectsThenDivest();

    static
    ResignAction const
    cancelThenDeleteThenDivest();

    static
    ResignAction const
    noAction();

    static
    ResignAction const
    undefAction();

    ResignAction &
    operator=(ResignAction const & rhs);

    bool
    operator==(ResignAction const & rhs) const;

    bool
    operator!=(ResignAction const & rhs) const;

    std::wstring
    toString() const;

  private:
    ResignAction(unsigned _resignAction);

    unsigned _resignAction;
  };
}
#ifdef    RTI_USE_INLINE
#include "RTI/ResignAction.i"
#endif // RTI_USE_INLINE

namespace RTI
{
  // These constants save a little typing for users.  
  // They can be used much like a enum, but in a type-safe way
  ResignAction const
  UNCONDITIONALLY_DIVEST_ATTRIBUTES
  = ResignAction::unconditionallyDivestAttributes();

  ResignAction const
  DELETE_OBJECTS
  = ResignAction::deleteObjects();

  ResignAction const
  CANCEL_PENDING_OWNERSHIP_ACQUISITIONS
  = ResignAction::cancelPendingOwnershipAcquisitions();

  ResignAction const
  DELETE_OBJECTS_THEN_DIVEST
  = ResignAction::deleteObjectsThenDivest();

  ResignAction const
  CANCEL_THEN_DELETE_THEN_DIVEST
  = ResignAction::cancelThenDeleteThenDivest();

  ResignAction const
  NO_ACTION
  = ResignAction::noAction();

  ResignAction const
  UNDEF_ACTION
  = ResignAction::undefAction();

}

#endif // RTI_ResignAction_h
