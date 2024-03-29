/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/RangeBounds.h
***********************************************************************/

#ifndef RTI_RangeBounds_h
#define RTI_RangeBounds_h

#include <RTI/SpecificConfig.h>

namespace RTI
{
  class RTI_EXPORT RangeBounds
  {
  public:
    RangeBounds();

    RangeBounds(unsigned long lowerBound,
                unsigned long upperBound);

    ~RangeBounds()
      throw ();

    RangeBounds(RangeBounds const & rhs);

    RangeBounds &
    operator=(RangeBounds const & rhs);

    unsigned long
    getLowerBound() const;

    unsigned long
    getUpperBound() const;

    void 
    setLowerBound(unsigned long lowerBound);

    void
    setUpperBound(unsigned long upperBound);

  private:
    unsigned long _lowerBound;
    unsigned long _upperBound;
  };
}

#ifdef    RTI_USE_INLINE
#include "RTI/RangeBounds.i"
#endif // RTI_USE_INLINE

#endif // RTI_RangeBounds_h
