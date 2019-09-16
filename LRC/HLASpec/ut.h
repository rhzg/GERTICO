/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************/

#ifndef ut_h
#define ut_h

#define MAX_TXT 1024
#define MAX_BUFF 1024

#include <stdio.h>

#include <RTI.hh>
#include "Util/GeRtiFedTime.h"

namespace GERTICO
{
class ut
{
	public:
    ut();
		~ut();

		static char *convert(unsigned int val);
		static char *convert(int val);
		static char *convert(unsigned long val);
		static char *convert(long val);
		static char *convert(char *val);
		static char *convert(const char *val);
		static char *convert(double val);
		static char *convert(long double val);
		static char *convert(char val);
		static char *convert(void *val);
		static char *convert(const void *val);
		static char *convertLogicalTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiFedTime const &val);

	public:
	  static void printAttributeHandleSet(char *txt,const RTI::AttributeHandleSet& theAttributeHandleSet);
		static void printAttributeHandleValuePairSet(char *txt,const RTI::AttributeHandleValuePairSet& theAttributeHandleValuePairSet);
		static void printParameterHandleValuePairSet(char *txt,const RTI::ParameterHandleValuePairSet& theParameterHandleValuePairSet);
};
};

#endif
