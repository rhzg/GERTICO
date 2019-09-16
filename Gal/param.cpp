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
** File(s)      : param.cpp
** Component(s) : -
** Device(s)    : Windows NT, Visual C++
** Terminology  : -
**              :
** Definition   : 
** Author       : Reinhard Bähre, FhG-IITB
** Date         : 13.09.2002
**              :
** Version      : 0.1 Beta
** Date         :
** Status       : untested
**              :
** Description  : param
**              :
*****************************************************************************/

#define __THISCLASS__ Param
#define __CLASSNAME__ "Param"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "param.h"

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/* param                                                                    */
/*--------------------------------------------------------------------------*/

Param::Param(class Repository *repository,char *id,char *fmt)
{
	this->repository=repository;
	repository_l=NULL;
	strcpy(this->id,id);
	strcpy(this->fmt,fmt);
	admParamFormatLogger(false,id);
}

Param::Param(class Repository_l *repository_l,char *id,char *fmt)
{
	this->repository_l=repository_l;
	repository=NULL;
	strcpy(this->id,id);
	strcpy(this->fmt,fmt);
	admParamFormatLogger(true,id);
}

/*--------------------------------------------------------------------------*/
/* ~param                                                                   */
/*--------------------------------------------------------------------------*/

Param::~Param()
{
}

/*****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__


