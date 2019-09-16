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
** File(s)      : fkt1.cpp
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
** Description  : test application
**              :
*****************************************************************************/

#define __THISCLASS__ Fkt1
#define __CLASSNAME__ "Fkt1"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

/************************************** Gal *********************************/

#include "StdAfx.h"

#include "repository_l.h"
#include "event.h"

static class Repository_l *repository_l=new Repository_l(Repository::getSingleInstance(),"fkt1.rc.de");

static class Event *Event1=repository_l->getRefEvent("ex");
static class Event *Event2=repository_l->getRefEvent("exy");
static class Event *Event3=repository_l->getRefEvent("exyz");

/*************************************** Gal ********************************/

#include "fkt1.h"

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/* fkt1                                                                     */
/*--------------------------------------------------------------------------*/

Fkt1::Fkt1()
{
}

/*--------------------------------------------------------------------------*/
/* ~Fkt1                                                                    */
/*--------------------------------------------------------------------------*/

Fkt1::~Fkt1()
{
}

/*--------------------------------------------------------------------------*/
/* method                                                                   */
/*--------------------------------------------------------------------------*/

void Fkt1::method()
{
	int intVal=1;
	unsigned int uVal=0;
	long longVal=2;
	static char *name="baehre";
	void *p;

	E1(Event1,intVal);
	E2(Event2,name,longVal);
	E0(Event2);
	p=(void *)&uVal;
	E1(Event3,p);
}

/*****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__
