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
** File(s)      : out.h
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

#ifndef __Out__included__
#define __Out__included__


/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#include "global.h"

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

class Out
{
	friend class Appender;
	friend class Layout;
	friend class Format;
	friend class Event;
	friend class Repository;
	friend class Repository_l;
	friend class Adm;

//variables
	protected:

	private:
		static FILE *fpGall;
		static FILE *fpGallRef;
		static class Out *singleInstance;
		static unsigned int cntError;
		static unsigned int cntWarning;
		static unsigned int cntInfo;
		static unsigned int cntEvent;
	public:

//functions

	private:
		Out();

		static FILE *openDevice(char *name);
		static void closeDevice(FILE *fp);
		char *setProtOut(enum GAL_APPENDER protAppender);
		static void closeRefOut();

	protected:

	public:
		static class Out *getSingleInstance();
		~Out();

		static void abort(char *fn,char *txt);
		static void error(char *fn,char *txt);
		static void warning(char *fn,char *txt);
		static void info(char *fn,char *txt);

		static void ref(char *txt);
		static void stat(char *txt);
		static void event(char *txt);
		static void event(FILE *fp,char *txt);
};

/****************************************************************************/

#endif
