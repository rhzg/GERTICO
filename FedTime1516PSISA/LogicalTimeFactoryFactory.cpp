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
Revision 1.4  2009/05/25 12:47:33  mul
Fix load dynamic library problem.

Revision 1.3  2009/02/16 15:20:16  mul
Changes for integrating ownership.

Revision 1.2  2009/02/11 15:42:44  mul
Minor changes.

Revision 1.1  2009/01/22 14:54:11  mul
New directory for PSISA time implementation.

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
  return new NAMESPACE::LogicalTimeDoubleFactory();
}

RTI::LogicalTimeIntervalFactory *getLogicalTimeIntervalFactory()
{
  return new NAMESPACE::LogicalTimeIntervalDoubleFactory();
}
