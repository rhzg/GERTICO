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
** File(s)      : layout.h
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

#ifndef __Layout__included__
#define __Layout__included__

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#include "appender.h"
#include "lst.h"
#include "adm.h"

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

class Layout: public Adm
{
	friend class Appender;
	friend class Format;
	friend class Event;
	friend class Logger;
	friend class Repository;
	friend class Repository_l;

//variables
	protected:

	private:
		char fmt[GAL_FMT];
		class Repository *repository;
		Lst<class Appender> *lstAppender;

	public:

//functions
	protected:

	private:
		Layout(class Repository *repository,char *id,char *fmt);
		unsigned int getNrAppender();
		int addAppender(class Appender *appender);
		int removeAppender(class Appender *appender);
		int removeAllAppender();

	public:
		~Layout();
		char *makeTxt(class Event *event);
};

/****************************************************************************/

#endif
