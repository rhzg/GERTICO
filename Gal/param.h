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
** File(s)      : param.h
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
** Description  : 
**              :
******************************************************************************/

#ifndef __Param__included__
#define __Param__included__

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#include "event.h"
#include "lst.h"
#include "repository_l.h"
#include "adm.h"

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

class Param: public Adm
{
	friend class Appender;
	friend class Layout;
	friend class Event;
	friend class Logger;
	friend class Repository;
	friend class Repository_l;

//variables
	protected:

	private:
		class Repository *repository;
		class Repository_l *repository_l;

	public:
		char fmt[GAL_CTXT];

//functions
	protected:

	private:
		Param(class Repository *repository,char *id,char *fmt);
		Param(class Repository_l *repository_l,char *id,char *fmt);

	public:
		~Param();

};

/****************************************************************************/

#endif
