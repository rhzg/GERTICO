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
** File(s)      : appl.cpp
** Component(s) : -
** Device(s)    : Windows NT, Visual C++
** Terminology  : -
**              :
** Definition   : 
** Author       : Reinhard B�hre, FhG-IITB
** Date         : 13.09.2002
**              :
** Version      : 0.1 Beta
** Date         :
** Status       : untested
**              :
** Description  : test application
**              :
*****************************************************************************/

#define __THISCLASS__ Appl
#define __CLASSNAME__ "Appl"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "appl.h"
#include "fkt1.h"
#include "fkt2.h"

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/* appl                                                                     */
/*--------------------------------------------------------------------------*/

Appl::Appl()
{
	fkt1=new Fkt1();
	fkt2=new Fkt2();
}

/*--------------------------------------------------------------------------*/
/* ~appl                                                                    */
/*--------------------------------------------------------------------------*/

Appl::~Appl()
{
	if(fkt1)
		delete fkt1;
	if(fkt2)
		delete fkt2;
}

/*--------------------------------------------------------------------------*/
/* run                                                                      */
/*--------------------------------------------------------------------------*/

void Appl::run()
{
	int i;
  struct timeb tb;
	unsigned int ms;
	unsigned long s;

/*	ftime(&tb);
	ms=tb.millitm;
	s=tb.time;
	printf("%lu:%u\n",s,ms);
*/

	for(i=0;i<10;i++)
		fkt1->method();

	fkt2->method();

	for(i=0;i<10;i++)
		fkt1->method();

/*
	ftime(&tb);
	ms=tb.millitm;
	s=tb.time;
	printf("%lu:%u\n",s,ms);
*/
}



/****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__
