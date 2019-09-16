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
** File(s)      : gall.cpp
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

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/


#include "StdAfx.h"

#include "appl.h"

#include "repository.h"

/*--------------------------------------------------------------------------*/
/* main                                                                     */
/*--------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
	class Appl *application;

/************************************ Gal ***********************************/

	char *t;
	class Repository *repository=Repository::getSingleInstance();

	t=repository->init("main.rc.de");
	if(t)
		printf("%s\n",t);

/************************************ Gal ***********************************/
	
	application=new Appl();
	application->run();

	if(application)
		delete application;

/************************************ Gal ***********************************/

	repository->terminate();

/************************************ Gal ***********************************/
	
	return 0;
}
