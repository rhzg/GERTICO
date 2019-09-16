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
** File(s)      : appender.h
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

#ifndef __Appender__included__
#define __Appender__included__

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#include "logger.h"
#include "event.h"
#include "layout.h"
#include "repository.h"
#include "adm.h"
#include "in.h"
#include "lst.h"

enum GAL_TRIGGER_MODE {tNULL,tPREV,tMIDDLE,tMIDDLEcont,tPOST,tPOSTcont};
enum GAL_TRIGGER_STATE {tRESET,tWAIT,tSTART,tSTOP};

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

class Appender: public Adm, In
{
	friend class Layout;
	friend class Format;
	friend class Event;
	friend class Logger;
	friend class Repository;
	friend class Repository_l;

//variables
	protected:

	private:
		Lst<class Logger> *lstLogger;
		enum GAL_APPENDER logAppender;
		char nameDevice[GAL_NAME];
		char nameTrigger[GAL_NAME];
		enum GAL_TRIGGER_MODE triggerMode;
		enum GAL_TRIGGER_STATE triggerState;
		unsigned long sizeBuffer;
		char *bp;
		char *pBegBuffer;
		char *pStopBuffer;
		char *pEndBuffer;
		int ovBuffer;
		class Layout *layout;
		class Repository *repository;
		enum GAL_LEVEL level;
		unsigned int group;

	public:

//functions

	protected:

	private:
		Appender(class Repository *repository,char *id,int enable,enum GAL_LEVEL level,enum GAL_APPENDER logAppender,char *nameDevice,unsigned long sizeBuffer,char *nameTrigger);

		void configure();
		void flushAndClose();

		unsigned int getNrLogger();
		void setLevel(enum GAL_LEVEL level);

		void out(class Event *event);

		static enum GAL_APPENDER convertOut(char *type);
		static enum GAL_TRIGGER_MODE convertTrigger(char *type);			

		int removeLogger(class Logger *logger);
		int removeAllLogger();
		void setEnable(int enable);

		int addLogger(class Logger *logger);
		void setLayout(class Layout *layout);

		void fillMode(enum GAL_TRIGGER_MODE *mode);
		void fillEvent();

	public:
		~Appender();

};

/****************************************************************************/

#endif
