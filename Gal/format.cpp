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
** File(s)      : format.cpp
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
** Description  : format
**              :
*****************************************************************************/

#define __THISCLASS__ Format
#define __CLASSNAME__ "Format"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "format.h"
#include "string.h"

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/* format                                                                   */
/*--------------------------------------------------------------------------*/

Format::Format(class Repository *repository,char *id,char *ctxt,char *vtxt)
{
	this->repository=repository;
	repository_l=NULL;
	strcpy(this->ctxt,ctxt);
	strcpy(this->vtxt,vtxt);
	strcpy(fmt,"");
	strcpy(hfmt,"");

	admParamFormatLogger(false,id);
}

Format::Format(class Repository_l *repository_l,char *id,char *ctxt,char *vtxt)
{
	this->repository_l=repository_l;
	repository=NULL;
	strcpy(this->ctxt,ctxt);
	strcpy(this->vtxt,vtxt);
	strcpy(fmt,"");
	strcpy(hfmt,"");

	admParamFormatLogger(true,id);
}

/*--------------------------------------------------------------------------*/
/* ~format                                                                  */
/*--------------------------------------------------------------------------*/

Format::~Format()
{
}

/*--------------------------------------------------------------------------*/
/* makeTxt                                                                  */
/*--------------------------------------------------------------------------*/

char *Format::makeTxt(char *txt)
{
	static char ftxt[GAL_TXT];
	char *f=ftxt;
	char *c=hfmt;
	unsigned int clen=strlen(c);
	unsigned int ci;
	char *t=txt;
	unsigned int tlen=strlen(t);
	unsigned int ti=0;

	ftxt[0]=0;

	if((clen==0)||(tlen==0))
		return txt;
	
	for(ci=0;ci<clen;ci++,c++)
	{
		if(ci<clen)
		{
			if(*c==' ')
				continue;
			*f++=*c;
			if(*(c+1)!=' ')
				continue;
		}
		*f++='=';
		for(;ti<tlen;ti++,t++)
		{
			if(*t==' ')
				continue;
			*f++=*t;
			if(*(t+1)!=' ')
				continue;
      *f++=' ';
			ti++;
			t++;
			break;
		}
	}
  *f=0;

	return ftxt;
}

/*****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__


