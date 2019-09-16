/***********************************************************************
  IEEE 1516.1 High Level Architecture Interface Specification C++ API
  File: RTI/RangeBounds.i
***********************************************************************/

RTI_INLINE
RTI::RangeBounds::
RangeBounds()
: _lowerBound(0),
  _upperBound(1)
{
}

RTI_INLINE
RTI::RangeBounds::
RangeBounds(unsigned long lowerBound,
            unsigned long upperBound)
: _lowerBound(lowerBound),
  _upperBound(upperBound)
{
}

RTI_INLINE
RTI::RangeBounds::
~RangeBounds()
  throw ()
{
}

RTI_INLINE
RTI::RangeBounds::
RangeBounds(RangeBounds const & rhs)
: _lowerBound(rhs._lowerBound),
  _upperBound(rhs._upperBound)
{
}

RTI_INLINE
RTI::RangeBounds &
RTI::RangeBounds::
operator=(RangeBounds const & rhs)
{
  if (this != &rhs)
  {
    _lowerBound = rhs._lowerBound;
    _upperBound = rhs._upperBound;
  }
  return *this;
}

RTI_INLINE
unsigned long
RTI::RangeBounds::
getLowerBound() const
{
  return _lowerBound;
}

RTI_INLINE
unsigned long
RTI::RangeBounds::
getUpperBound() const
{
  return _upperBound;
}

RTI_INLINE
void
RTI::RangeBounds::
setLowerBound(unsigned long lowerBound)
{
  _lowerBound = lowerBound;
}

RTI_INLINE
void
RTI::RangeBounds::
setUpperBound(unsigned long upperBound)
{
  _upperBound = upperBound;
}
