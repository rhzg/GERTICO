/*****************************************************************************
**                                                                          **
** IITB, Karlsruhe                                                          **
**                                                                          **
******************************************************************************
**                                                                          **
** Project      : GERTICO                                                   **
** Sub-Project  : logging system                                            **
**                                                                          **
*****************************************************************************/

/*
** File(s)      : in.cpp
** Component(s) : -
** Device(s)    : Windows NT, Visual C++
** Terminology  : -
**              :
** Definition   : 
** Author       : Reinhard Baehre, FhG-IITB
** Date         : 13.09.2002
**              :
** Version      : 0.1 Beta
** Date         :
** Status       : untested
**              :
** Description  : in
**              :
*****************************************************************************/

#define __THISCLASS__ In
#define __CLASSNAME__ "In"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "in.h"
#include <string.h>

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/* In                                                                       */
/*--------------------------------------------------------------------------*/

In::In()
{
}

/*--------------------------------------------------------------------------*/
/* ~In                                                                      */
/*--------------------------------------------------------------------------*/

In::~In()
{
}

/*--------------------------------------------------------------------------*/
/* readLine                                                                 */
/*--------------------------------------------------------------------------*/

void In::readLine()
{
	int i;
	int c;
	char *p=stringLine;

	line++;

	*p=0;
	for(i=0;i<(GAL_STRING_LINE-1);i++)
	{
		c=getc(fp);
		if(c==EOF)
		{
			throw "Unexspected end of line";
		}
		if(c==LF)
		{
			*p=0;
			return;
		}
		*p++=(char)c;
	}
	*p=0;
	throw "Max line length exceeded";
}

/*--------------------------------------------------------------------------*/
/* readTxt                                                                  */
/*--------------------------------------------------------------------------*/

int In::readTxt(char *searchedTxtId,char *searchedTxtCont)
{
	int found=0;
	int lenST=strlen(searchedTxtId);
	int lenS=strlen(stringLine); 
  char *p=stringLine;
	char *pEnd=p+lenS;

	for(;p<pEnd;)
	{
		if(strncmp(p,searchedTxtId,lenST)==0)
		{
			found=1;
			break;
		}
		p++;
	}
	if(!found)
	{
		*searchedTxtCont=0;
		return 2;
	}

	p+=lenST;

	if(*p++!='"')
		return 1;

	while((*p!='"')&&(p<=pEnd))
		*searchedTxtCont++=*p++;
	*searchedTxtCont=0;

	if(*p!='"')
		return 1;

	return 0;
}

/*--------------------------------------------------------------------------*/
/* fillVersion                                                              */
/*--------------------------------------------------------------------------*/

void In::fillVersion() throw (const char*)
{
	readLine();
	if(sscanf(stringLine,"version=%s\n",version)!=1)
		throw "version";
}


/*****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__
