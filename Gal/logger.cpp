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
** File(s)      : logger.cpp
** Component(s) : -
** Device(s)    : Windows NT, Visual C++
** Terminology  : -
**              :
** Definition   : 
** Author       : Reinhard Baehre, FhG-IITB
** Date         : 13.09.2002
**              :
** Version      : 0.1 Beta
** Date         :
** Status       : untested
**              :
** Description  : logger
**              :
*****************************************************************************/

#define __THISCLASS__ Logger
#define __CLASSNAME__ "Logger"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "logger.h"
#include "event.h"
#include "string.h"

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/* logger                                                                   */
/*--------------------------------------------------------------------------*/

Logger::Logger(class Repository *repository,char *id,int enable,enum GAL_LEVEL level,unsigned int group,char *ctxt)
{
	this->repository=repository;
	repository_l=NULL;
	init(false,id,enable,level,group,ctxt);
}

Logger::Logger(class Repository_l *repository_l,char *id,int enable,enum GAL_LEVEL level,unsigned int group,char *ctxt)
{
	repository=NULL;
	this->repository_l=repository_l;
	init(true,id,enable,level,group,ctxt);
}

void Logger::init(int local,char *id,int enable,enum GAL_LEVEL level,unsigned int group,char *ctxt)
{
	admParamFormatLogger(local,id);
	this->enable=enable;
	this->level=level;
	this->group=group;
	strcpy(this->ctxt,ctxt);
	lstEvent=new Lst<class Event>(GAL_LST_EVENT_INIT);
	lstAppender=new Lst<class Appender>(GAL_LST_APPENDER_INIT);
}

/*--------------------------------------------------------------------------*/
/* ~logger                                                                  */
/*--------------------------------------------------------------------------*/

Logger::~Logger()
{
	if(lstEvent)
		delete lstEvent;
	if(lstAppender)
		delete lstAppender;
}

/*--------------------------------------------------------------------------*/
/* getNrAppender                                                            */
/*--------------------------------------------------------------------------*/

unsigned int Logger::getNrAppender()
{
	return lstAppender->length;
}

/*--------------------------------------------------------------------------*/
/* setLevel                                                                 */
/*--------------------------------------------------------------------------*/

void Logger::setLevel(enum GAL_LEVEL level)
{
  this->level=level;
	testSetEnableEvent();
}

/*--------------------------------------------------------------------------*/
/* testSetEnableEvent                                                       */
/*--------------------------------------------------------------------------*/

void Logger::testSetEnableEvent()
{
	class Appender **aa=lstAppender->head;
	class Appender *a;
	class Event **ee=lstEvent->head;
	class Event *e;
	enum GAL_LEVEL minlevel=lmaxLEVEL;
	enum GAL_LEVEL elevel;
	unsigned int i;

	if(!enable)
	{
		lstEvent->setEnabled(false);
		return;
	}

	for(i=0;i<lstAppender->length;i++,aa++)
	{
		a=*aa;
		if(a->enable)
		{
			if(a->level<minlevel)
				minlevel=a->level;
		}
	}

  if(minlevel<level)
		minlevel=level;

	for(i=0;i<lstEvent->length;i++,ee++)
	{
		e=*ee;
		if(e->enable)
		{
			elevel=e->level;
			if(elevel<minlevel)
			{
				e->enabled=false;
				continue;		
			
			}
			if(elevel>minlevel)
			{
				e->enabled=true;
				continue;		
			}
			e->enabled=(e->group&group)?true:false;
		}
	}
}

/*--------------------------------------------------------------------------*/
/* enable                                                                   */
/*--------------------------------------------------------------------------*/

void Logger::setEnable(int enable)
{
	this->enable=enable;
	if(enable)
		testSetEnableEvent();
	else
		lstEvent->setEnabled(false);
}

/*--------------------------------------------------------------------------*/
/* addEvent                                                                 */
/*--------------------------------------------------------------------------*/

int Logger::addEvent(class Event *event)
{
  return lstEvent->add(event,0);
}

/*--------------------------------------------------------------------------*/
/* addAppender                                                              */
/*--------------------------------------------------------------------------*/

int Logger::addAppender(class Appender *appender)
{
	int rc=0;

  rc=lstAppender->add(appender,0);
	testSetEnableEvent();
  
	return rc;
}

/*--------------------------------------------------------------------------*/
/* removeAppender                                                           */
/*--------------------------------------------------------------------------*/

int Logger::removeAppender(class Appender *appender)
{
	int rc;

  rc=lstAppender->remove(appender);
	testSetEnableEvent();

  return rc;
}

/*--------------------------------------------------------------------------*/
/* out                                                                      */
/*--------------------------------------------------------------------------*/

void Logger::out(class Event *event)
{
	class Appender **aa=lstAppender->head;
	unsigned int length=lstAppender->length;
	unsigned int i;

	for(i=0;i<length;i++,aa++)
	{
		if((*aa)->enable)
		{
			if((*aa)->level<=event->level)
				(*aa)->out(event);
		}
	}
}

/****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__

