/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_RegionI.h,v $
Revision 1.2  2004/03/17 14:20:21  mul
Minor changes.

Revision 1.1  2003/09/23 15:00:13  mul
Extensions for DDM.

 
**
*******************************************************************************/


#ifndef RTI_RegionI_HEADER
#define RTI_RegionI_HEADER
 
#include <map>
#include <vector>
#include "RTI.hh"

struct dcmp
{
  bool operator()(const RTI::DimensionHandle s1, const RTI::DimensionHandle s2) const
  {
    return s1 < s2;
  }
};

class DimensionI
{
public:
  RTI::ULong lowerBound;
  RTI::ULong upperBound;
  DimensionI (void);
  virtual ~DimensionI (void);
};

typedef std::map <RTI::DimensionHandle, DimensionI, dcmp> DimensionIMap;

class ExtentI
{
public:
  DimensionIMap dimensionIs;

  ExtentI (void);
  virtual ~ExtentI (void);
};

typedef std::vector <ExtentI> ExtentIVector;

class RegionI : public RTI::Region
{
  RTI::SpaceHandle sh;
  RTI::ULong numberOfExtents;

public:
  ExtentIVector extentIs;
  RTI::RegionToken id;

  RegionI (RTI::SpaceHandle, RTI::RegionToken, RTI::ULong);
  virtual ~RegionI (void);
 
  virtual RTI::ULong getRangeLowerBound (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension) const
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  virtual RTI::ULong getRangeUpperBound (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension) const
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  virtual void setRangeLowerBound (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension,
    RTI::ULong           theLowerBound)
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  virtual void setRangeUpperBound (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension,
    RTI::ULong           theUpperBound)
    throw (
      RTI::ArrayIndexOutOfBounds);
 
  virtual RTI::SpaceHandle getSpaceHandle (void) const
    throw (
      );
 
  virtual RTI::ULong getNumberOfExtents (void) const
    throw (
      );
 
  virtual RTI::ULong getRangeLowerBoundNotificationLimit (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension) const
    throw (
      RTI::ArrayIndexOutOfBounds);

  virtual RTI::ULong getRangeUpperBoundNotificationLimit (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension) const
    throw (
      RTI::ArrayIndexOutOfBounds);
};

struct rcmp
{
  bool operator()(const RTI::RegionToken s1, const RTI::RegionToken s2) const
  {
    return s1 < s2;
  }
};

typedef std::map <RTI::RegionToken, RegionI *, rcmp> RegionIMap;

#endif
