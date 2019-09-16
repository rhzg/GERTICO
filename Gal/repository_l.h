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
** File(s)      : repository_l.h
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

#ifndef __Repository_l__included__
#define __Repository_l__included__

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#include "adm.h"
#include "in.h"
#include "lst.h"

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/


class GAL_EXPORT Repository_l: public Adm, In
{
	friend class Appender;
	friend class Layout;
	friend class Param;
	friend class Format;
	friend class Event;
	friend class Logger;
	friend class Repository;

//variables
	protected:

  private:
		int initialized;
		int checkIn;
		class Repository *repository;
		char rcFileName[GAL_FILENAME];

		Lst<class Param> *lstParam;
		Lst<class Format> *lstFormat;
		Lst<class Event> *lstEvent;
		Lst<class Logger> *lstLogger;

		char version[GAL_NAME];

	public:

//functions

	protected:

	private:
    void fillId();
		void fillLogger();
		void fillParam();
		void fillFormat();
		void fillEvent();

		int makeFormatReferences(); 
		int makeEventReferences(); 
		void makeReferences();

		char *findEvent(char *idEvent,class Event **foundEvent);

		char *findLogger(char *idLogger,class Logger **foundLogger);
		char *findLogger(unsigned int idLogger,class Logger **foundLogger);

		void printEventStatistics();
		void findUnusedEventFormatParam();

	public:
		Repository_l(class Repository *repository,char *rcFileName);
		~Repository_l();

		void printRef();

		int fill();

		class Event *getRefEvent(char *id);

};

/****************************************************************************/

#endif

