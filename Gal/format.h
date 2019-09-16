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
** File(s)      : format.h
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

#ifndef __Format__included__
#define __Format__included__

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

class Format: public Adm
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
		char ctxt[GAL_CTXT];
		char vtxt[GAL_CTXT];

	public:
		char hfmt[GAL_CTXT];
		char fmt[GAL_CTXT];

//functions
	protected: 

	private:
		Format(class Repository *repository,char *id,char *ctxt,char *vtxt);
		Format(class Repository_l *repository_l,char *id,char *ctxt,char *vtxt);

		char *makeTxt(char *txt);

	public:
		~Format();
};

/****************************************************************************/

#endif
