/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: RTI_RegionI.cpp,v $
Revision 1.1  2003/09/23 15:00:12  mul
Extensions for DDM.

 
**
*******************************************************************************/


#include "RTI_RegionI.h"

DimensionI::DimensionI (void)
{
  lowerBound = 0;
  upperBound = 0;
}
 
DimensionI::~DimensionI (void)
{
}

ExtentI::ExtentI (void)
{
}

ExtentI::~ExtentI (void)
{
}

RegionI::RegionI (RTI::SpaceHandle theSpace, RTI::RegionToken theId, RTI::ULong theNumberOfExtents)
{
  ExtentI extentI;
  unsigned int i;
  unsigned int size;

  sh = theSpace;
  numberOfExtents = theNumberOfExtents;
  id = theId;

  for (i = 0; i < numberOfExtents; i++)
  {
    extentIs.push_back (extentI);
  }

  size = extentIs.size ();
}
 
RegionI::~RegionI (void)
{
}
 
RTI::ULong RegionI::getRangeLowerBound (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension) const
    throw (
      RTI::ArrayIndexOutOfBounds)
{
  DimensionIMap::const_iterator itD;
  RTI::ULong ret = 0;
  unsigned int size;

  size = extentIs.size ();
  if (theExtent >= size)
  {
    throw RTI::ArrayIndexOutOfBounds ("");
  }

  const ExtentI *extentI = &extentIs[theExtent];

  itD = extentI->dimensionIs.find (theDimension);
  if (itD != extentI->dimensionIs.end ())
  {
    ret = itD->second.lowerBound;
  }

  return ret;
}
 
RTI::ULong RegionI::getRangeUpperBound (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension) const
    throw (
      RTI::ArrayIndexOutOfBounds)
{
  DimensionIMap::const_iterator itD;
  RTI::ULong ret = 0;
  unsigned int size;

  size = extentIs.size ();
  if (theExtent >= size)
  {
    throw RTI::ArrayIndexOutOfBounds ("");
  }

  const ExtentI *extentI = &extentIs[theExtent];

  itD = extentI->dimensionIs.find (theDimension);
  if (itD != extentI->dimensionIs.end ())
  {
    ret = itD->second.upperBound;
  }

  return ret;
}
 
void RegionI::setRangeLowerBound (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension,
    RTI::ULong           theLowerBound)
    throw (
      RTI::ArrayIndexOutOfBounds)
{
  DimensionI dimensionI;
  DimensionIMap::iterator itD;
  unsigned int size;
  
  size = extentIs.size ();
  if (theExtent >= size)
  {
    throw RTI::ArrayIndexOutOfBounds ("");
  }

  ExtentI *extentI = &extentIs[theExtent];

  itD = extentI->dimensionIs.find (theDimension);
  if (itD != extentI->dimensionIs.end ())
  {
    itD->second.lowerBound = theLowerBound;
  }
  else
  {
    dimensionI.lowerBound = theLowerBound;
    extentI->dimensionIs[theDimension] = dimensionI;
  }
}
 
void RegionI::setRangeUpperBound (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension,
    RTI::ULong           theUpperBound)
    throw (
      RTI::ArrayIndexOutOfBounds)
{
  DimensionI dimensionI;
  DimensionIMap::iterator itD;
  unsigned int size;

  size = extentIs.size ();
  if (theExtent >= size)
  {
    throw RTI::ArrayIndexOutOfBounds ("");
  }

  ExtentI *extentI = &extentIs[theExtent];
  
  itD = extentI->dimensionIs.find (theDimension);
  if (itD != extentI->dimensionIs.end ())
  {
    itD->second.upperBound = theUpperBound;
  }
  else
  {
    dimensionI.upperBound = theUpperBound;
    extentI->dimensionIs[theDimension] = dimensionI;
  }
}
 
RTI::SpaceHandle RegionI::getSpaceHandle (void) const
    throw (
      )
{
  return sh;
}
 
RTI::ULong RegionI::getNumberOfExtents (void) const
    throw (
      )
{
  return numberOfExtents;
}
 
RTI::ULong RegionI::getRangeLowerBoundNotificationLimit (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension) const
    throw (
      RTI::ArrayIndexOutOfBounds)
{
  RTI::ULong ret = 0;
  return ret;
}

RTI::ULong RegionI::getRangeUpperBoundNotificationLimit (
    RTI::ExtentIndex     theExtent,
    RTI::DimensionHandle theDimension) const
    throw (
      RTI::ArrayIndexOutOfBounds)
{
  RTI::ULong ret = 0;
  return ret;
}
