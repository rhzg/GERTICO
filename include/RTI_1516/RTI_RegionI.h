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
Revision 1.1  2007/09/06 09:34:59  mul
Changes for ieee1516.

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

#include <RTI/RTIambassadorFactory.h>
#include "RTI.hh"
#include "baseTypes.hh"
#include "RTItypes.hh"

namespace RTI_V1_3
{

struct dcmp
{
  bool operator()(const RTI_V1_3::DimensionHandle s1, const RTI_V1_3::DimensionHandle s2) const
  {
    return s1 < s2;
  }
};

class DimensionI
{
public:
  RTI_V1_3::ULong lowerBound;
  RTI_V1_3::ULong upperBound;
#ifdef IEEE_1516
  RTI_V1_3::DimensionHandle dimensionHandle;
#endif
  DimensionI (void);
  virtual ~DimensionI (void);
};

typedef std::map <RTI_V1_3::DimensionHandle, DimensionI, dcmp> DimensionIMap;

class ExtentI
{
public:
  DimensionIMap dimensionIs;

  ExtentI (void);
  virtual ~ExtentI (void);
};

typedef std::vector <ExtentI> ExtentIVector;

class RegionI : public RTI_V1_3::Region
{
  RTI_V1_3::SpaceHandle sh;
  RTI_V1_3::ULong numberOfExtents;

public:
  ExtentIVector extentIs;
  RTI_V1_3::RegionToken id;
	long idRegionIEEE_1;
	long idRegionIEEE_2;

  RegionI (RTI_V1_3::SpaceHandle, RTI_V1_3::RegionToken, RTI_V1_3::ULong,long id_1,long id_2);
  virtual ~RegionI (void);
 
  virtual RTI_V1_3::ULong getRangeLowerBound (
    RTI_V1_3::ExtentIndex     theExtent,
    RTI_V1_3::DimensionHandle theDimension) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  virtual RTI_V1_3::ULong getRangeUpperBound (
    RTI_V1_3::ExtentIndex     theExtent,
    RTI_V1_3::DimensionHandle theDimension) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  virtual void setRangeLowerBound (
    RTI_V1_3::ExtentIndex     theExtent,
    RTI_V1_3::DimensionHandle theDimension,
    RTI_V1_3::ULong           theLowerBound)
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  virtual void setRangeUpperBound (
    RTI_V1_3::ExtentIndex     theExtent,
    RTI_V1_3::DimensionHandle theDimension,
    RTI_V1_3::ULong           theUpperBound)
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
 
  virtual RTI_V1_3::SpaceHandle getSpaceHandle (void) const
    throw (
      );
 
  virtual RTI_V1_3::ULong getNumberOfExtents (void) const
    throw (
      );

#ifdef IEEE_1516
  virtual RTI_V1_3::RegionToken getRegionToken (void) const
    throw (
      );

	virtual int getRegionIEEE(RTI_V1_3::ExtentIndex theExtent,long *regionHandleIEEE) const
		throw (
			);

  virtual int getRangeBoundsForIEEE (
		RTI_V1_3::ExtentIndex	theExtent,
		int dimension,
	 	RTI_V1_3::DimensionHandle *theDimension,
		RTI_V1_3::ULong *lowerBound,
		RTI_V1_3::ULong *upperBound) const
    throw (
      );

#endif

  virtual RTI_V1_3::ULong getRangeLowerBoundNotificationLimit (
    RTI_V1_3::ExtentIndex     theExtent,
    RTI_V1_3::DimensionHandle theDimension) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);

  virtual RTI_V1_3::ULong getRangeUpperBoundNotificationLimit (
    RTI_V1_3::ExtentIndex     theExtent,
    RTI_V1_3::DimensionHandle theDimension) const
    throw (
      RTI_V1_3::ArrayIndexOutOfBounds);
};

struct rcmp
{
  bool operator()(const RTI_V1_3::RegionToken s1, const RTI_V1_3::RegionToken s2) const
  {
    return s1 < s2;
  }
};

typedef std::map <RTI_V1_3::RegionToken, RegionI *, rcmp> RegionIMap;

}

#endif
