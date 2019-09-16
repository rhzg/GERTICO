/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: Exception.cpp,v $
Revision 1.1  2004/04/19 14:37:04  mul
Add programs for DOM writer.


**
*******************************************************************************/


#include "Exception.h"

GERTICO::ErrorReadingFED::ErrorReadingFED (const std::string &theError) : error (theError)
{
}

GERTICO::ErrorReadingFED::~ErrorReadingFED (void)
{
}

void GERTICO::ErrorReadingFED::getError (std::string &theError)
{
  theError = error;
}
