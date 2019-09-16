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
** File(s)      : repository.h
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
*****************************************************************************/

#ifndef __Repository__included__
#define __Repository__included__

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#include "logger.h"
#include "param.h"
#include "format.h"
#include "adm.h"
#include "appender.h"
#include "layout.h"
#include "lst.h"
#include "in.h"
#include "out.h"

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/


class GAL_EXPORT Repository: public Adm, In
{
	friend class Appender;
	friend class Layout;
	friend class Param;
	friend class Format;
	friend class Event;
	friend class Logger;
	friend class Repository_l;
	friend class Adm;

//variables
	protected:

	private:
		char id[GAL_NAME];
		static class Repository *singleInstance;
		unsigned long refTimeStart;

// defined by programmer and created after programm start: local definitions (fixed!) 
		Lst<class Repository_l> *lstRepository_l;
// defined by programmer and created after programm start: global definitions (fixed!) 
		Lst<class Logger> *lstLogger;
		Lst<class Param> *lstParam;
		Lst<class Format> *lstFormat;
// under control of remote user: create and delete 
		Lst<class Appender> *lstAppender;
		Lst<class Layout> *lstLayout;

		class Out *out;
		enum GAL_APPENDER aProt;
	
	public:

//functions

	protected:

	private:
		Repository();
// this is done by the programmer
		int addRepository_l(class Repository_l *repository_l);
		class Logger *findLogger(char *id);
		class Param *findParam(char *id);
		class Format *findFormat(char *id);

// this is done by system
		char *findAppender(char *id,class Appender **foundAppender);
		char *findLayout(char *id,class Layout **foundLayout);
		char *findEvent(char *id,char *idEvent,class Event **foundEvent);
		char *findLogger(char *id,char *idLogger,class Logger **foundLogger);
		char *findLogger(char *idLogger,class Logger **foundLogger);
		int removeAllUnusedAppender();
		int removeAllUnusedLayout();

    void fillId();
		void fillProtOut();
		void fillLogger();
		void fillParam();
		void fillFormat();
		void fillAppender();
		void fillLayout();
		void fillConnectAppenderLayout();
		void fillConnectAppenderLoggerGlobal();
		void fillConnectAppenderLoggerLocal();

		void findUnusedEventFormatParam();

	public:
		~Repository();
		static Repository *getSingleInstance();

		void printRef();

		int makeEventFormatReferences();
		void makeReferences();

		class Repository_l *getRepository_l(char *fileName,char *id);

// this is done by the user/observer of the application 

		char *addAppender(char *id,int enable,enum GAL_LEVEL level,enum GAL_APPENDER appender,char *nameDevice,unsigned long sizeBuffer,char *nameTrigger);
		char *removeAppender(char *id);
		char *enableAppender(char *id,int enable);
		char *setLevelAppender(char *id,enum GAL_LEVEL level);

		char *addLayout(char *id,char *fmt);
		char *removeLayout(char *id);

		char *enableLogger(char *idRepository_l,char *idLogger,int enable);
		char *enableLogger(char *idLogger,int enable);
		char *setLevelLogger(char *idRepository_l,char *idLogger,enum GAL_LEVEL level);
		char *setLevelLogger(char *idLogger,enum GAL_LEVEL level);

		char *connectAppenderLogger(char *idAppender,char *idRepository_l,char *idLogger,int connect);
		char *connectAppenderLogger(char *idAppender,char *idLogger,int connect);
		char *connectAppenderLayout(char *idAppender,char *idLayout,int connect);

		int configureLogging(char *confFileName);

		char *init(char *confFileName);
		void terminate();
		void printEventStatistics();
};

/****************************************************************************/

#endif

