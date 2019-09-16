/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: LogicalTimeFactoryFactory.h,v $
Revision 1.5  2009/05/25 12:46:32  mul
Fix load dynamic library problem.

Revision 1.4  2009/02/16 10:40:28  mul
Central file for logical time factory factory.

Revision 1.2  2009/02/12 13:10:26  mul
Minor changes.

Revision 1.1  2009/02/11 09:11:07  mul
Fed time library.

Revision 1.1  2008/11/27 08:45:14  mul
New files.



**
*******************************************************************************/

#ifdef _WIN32
#if defined (BUILDING_FEDTIME)
#define RTI_EXPORT __declspec(dllexport)
#else
#define RTI_EXPORT __declspec(dllimport)
#endif
#else
#define RTI_EXPORT
#endif


#include <string>

#include "RTI/LogicalTime.h"
#include "RTI/LogicalTimeFactory.h"
#include "RTI/LogicalTimeIntervalFactory.h"
#include "RTI/EncodedLogicalTime.h"
#include "RTI/EncodedLogicalTimeInterval.h"

extern "C"
{
  RTI::LogicalTimeFactory RTI_EXPORT *getLogicalTimeFactory();
  RTI::LogicalTimeIntervalFactory RTI_EXPORT *getLogicalTimeIntervalFactory();
}
