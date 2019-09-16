/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: LogicalTimeFactoryFactory.cpp,v $
Revision 1.7  2009/05/25 12:47:11  mul
Fix load dynamic library problem.

Revision 1.6  2009/02/16 15:21:22  mul
Changes for integrating ownership.

Revision 1.5  2009/02/12 13:10:26  mul
Minor changes.

Revision 1.4  2009/02/11 09:11:07  mul
Fed time library.

Revision 1.2  2009/01/26 08:37:31  mul
Remove unwanted printout.

Revision 1.1  2008/11/27 08:45:13  mul
New files.



**
*******************************************************************************/

#include <stdlib.h>
#include <iostream>
#include "include/RTI_1516/LogicalTimeFactoryFactory.h"

#include "LogicalTimeDouble.h"

RTI::LogicalTimeFactory *getLogicalTimeFactory()
{
  return new LogicalTimeDoubleFactory();
}

RTI::LogicalTimeIntervalFactory *getLogicalTimeIntervalFactory()
{
  return new LogicalTimeIntervalDoubleFactory();
}
