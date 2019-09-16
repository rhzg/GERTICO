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
** File(s)      : logger.h
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

#ifndef __Logger__included__
#define __Logger__included__

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#include "event.h"
#include "appender.h"
#include "lst.h"
#include "repository_l.h"
#include "adm.h"

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

class Logger: public Adm
{
	friend class Appender;
	friend class Layout;
	friend class Format;
	friend class Event;
	friend class Repository;
	friend class Repository_l;

//variables
	protected:

	private:
		char ctxt[GAL_CTXT];
		class Repository *repository;
		class Repository_l *repository_l;
		Lst<class Event> *lstEvent;
		Lst<class Appender> *lstAppender;
		enum GAL_LEVEL level;
		unsigned int group;

	public:

//functions
	protected:

	private:
		Logger(class Repository *repository,char *id,int enable,enum GAL_LEVEL level,unsigned int group,char *ctxt);
		Logger(class Repository_l *repository_l,char *id,int enable,enum GAL_LEVEL level,unsigned int group,char *ctxt);

		void init(int local,char *id,int enable,enum GAL_LEVEL level,unsigned int group,char *ctxt);

		unsigned int getNrAppender();
		void setLevel(enum GAL_LEVEL level);
		void testSetEnableEvent();

		void setEnable(int enable);
		
		int addEvent(class Event *event);

		int addAppender(class Appender *appender);
		int removeAppender(class Appender *appender);

		void out(class Event *event);

	public:
		~Logger();
};

/****************************************************************************/

#endif
