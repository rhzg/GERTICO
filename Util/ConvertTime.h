/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: ConvertTime.h,v $
Revision 1.3  2010/05/14 13:52:49  mul
Add logical time interval.

Revision 1.2  2009/09/03 06:59:54  mul
Minor changes.

Revision 1.1  2009/05/07 12:17:33  mul
Moved location of time conversion routines.


**
*******************************************************************************/


// -*- C++ -*-
//
// $Id: ConvertTime.h,v 1.3 2010/05/14 13:52:49 mul Exp $

#ifndef ConvertTime_H_
#define ConvertTime_H_

#include <map>

#include "idl/GeRtiFactoryS.h"
#include "Util/GeRtiFedTimeI.h"
#include "Util/GeRtiTypes.h"

namespace GERTICO
{
  class ConvertTime
  {
  public:
    static void mapIt(GeRtiFactory::Time &theTime, const GERTICO::GeRtiFedTime &theFedTime);
    static void mapGeRtiFedTimeAutoPtr(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, std::auto_ptr<GERTICO::GeRtiFedTime> &theFedTime, const GeRtiFactory::Time &theTime);
    static void mapItGeRtiFedTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiFedTime **theFedTime, const GeRtiFactory::Time &theTime);
    static void mapGeRtiLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval, const GeRtiFactory::Time &theTime);
    static void mapGeRtiLogicalTimeInterval(GeRtiFactory::Time &theTime, const GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval);

    // For save/restore.
    static void mapIt(GeRtiFactory::Time &theTime, char *theString);
    static void mapIt(char *theString, const GeRtiFactory::Time &theTime);
    static void mapGeRtiFedTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiFedTime &theGeRtiFedTime, char *theString);
    static void mapGeRtiFedTime(char *theString, GERTICO::GeRtiFedTime &theGeRtiFedTime);
    static void mapGeRtiLogicalTimeInterval(GERTICO::GeRtiLogicalTimeIntervalFactory &theLogicalTimeIntervalFactory, GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval, char *theString);
    static void mapGeRtiLogicalTimeInterval(char *theString, GERTICO::GeRtiLogicalTimeInterval &theLogicalTimeInterval);

    ConvertTime (void);
    virtual ~ConvertTime (void);

  };
};

#endif /* ConvertTime_H_  */
