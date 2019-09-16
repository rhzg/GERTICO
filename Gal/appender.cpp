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
** File(s)      : appender.cpp
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
** Description  : appender
**              :
*****************************************************************************/

#define __THISCLASS__ Appender
#define __CLASSNAME__ "Appender"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "appender.h"
#include "layout.h"
#include <string.h>

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/* appender                                                                 */
/*--------------------------------------------------------------------------*/

Appender::Appender(class Repository *repository,char *id,int enable,enum GAL_LEVEL level,enum GAL_APPENDER logAppender,char *nameDevice,unsigned long sizeBuffer,char *nameTrigger)
{
	this->repository=repository;
	this->enable=enable;
	this->level=level;
	this->logAppender=logAppender;
	strcpy(this->nameDevice,nameDevice);
	strcpy(this->nameTrigger,nameTrigger);
	this->sizeBuffer=sizeBuffer;
	layout=NULL;
	lstLogger=new Lst<class Logger>(GAL_LST_LOGGER_INIT);
	admAppenderLayout(id);
	fp=NULL;

	triggerState=tRESET;
}

/*--------------------------------------------------------------------------*/
/* ~appender                                                                */
/*--------------------------------------------------------------------------*/

Appender::~Appender()
{
	if(lstLogger)
		delete lstLogger;

	if(fp!=NULL)
		flushAndClose();
}

/*--------------------------------------------------------------------------*/
/* flushAndClose                                                            */
/*--------------------------------------------------------------------------*/

void Appender::flushAndClose()
{
	char *p;

	switch(logAppender)
	{
		case aSTDOUT:
			break;

		case aFILE:
			if(fp)
			{
				fflush(fp);
				Out::closeDevice(fp);
			}
			break;

		case aBUFFER:
			fp=Out::openDevice(nameDevice);
			if(fp)
			{
				if(ovBuffer)
				{
					p=bp;
					do
					{
						p+=GAL_MSG_TXT;
						if(p>pEndBuffer)
							p=pBegBuffer;
						fprintf(fp,"%s\n",p);
					}while(p!=bp);
				}
				else
				{
					for(p=pBegBuffer;p<=bp;p+=GAL_MSG_TXT)
						fprintf(fp,"%s\n",p);
				}
				Out::closeDevice(fp);
			}
			break;
		case aNULL:
		default:
			break;
	}

	fp=NULL;

}

/*--------------------------------------------------------------------------*/
/* configure                                                                */
/*--------------------------------------------------------------------------*/

void Appender::configure()
{
	static char txt[GAL_TXT];

	switch(logAppender)
	{
		case aSTDOUT:
			fp=NULL;
			bp=NULL;
			break;
		case aFILE:
			bp=NULL;
			fp=Out::openDevice(nameDevice);
			if(fp==NULL)
			{
				sprintf(txt,"Can't open log file %s for write",nameDevice);
				throw txt;
			}
			break;
		case aBUFFER:
			ovBuffer=false;
			pBegBuffer=bp=(char *)calloc((size_t)GAL_MSG_TXT,sizeBuffer);
			if(bp==NULL)
			{
				sprintf(txt,"Can't allocate memory for buffer log file %s",nameDevice);
				throw txt;
			}
			pEndBuffer=pBegBuffer+(GAL_MSG_TXT*(sizeBuffer-1));
			pStopBuffer=NULL;

			if(*nameTrigger)
			{
				line=0;
				fp=fopen(nameTrigger,"r");
				if(fp==NULL)
				{
					sprintf(txt,"Can't open trigger file %s for read",nameTrigger);
					throw txt;
				}
				else
				{
					try
					{
						fillVersion();
						fillMode(&triggerMode);
						fillEvent();

						triggerState=(triggerMode==tPOST)?tWAIT:tSTART;
					}
					catch(char *s)
					{
						fclose(fp);
						sprintf(txt,"File=%s Error in line %u typ %s",nameTrigger,line,s);
						throw txt;
					}
					catch(const char *s)
					{
						fclose(fp);
						sprintf(txt,"File=%s Error in line %u typ %s",nameTrigger,line,s);
						throw txt;
					}

					fclose(fp);
				}
			}
			fp=NULL;
			break;
		default:
			logAppender=aNULL;
			break;
	}
}

/*--------------------------------------------------------------------------*/
/* getNrLogger                                                              */
/*--------------------------------------------------------------------------*/

unsigned int Appender::getNrLogger()
{
	return lstLogger->length;
}

/*--------------------------------------------------------------------------*/
/* setLevel                                                                 */
/*--------------------------------------------------------------------------*/

void Appender::setLevel(enum GAL_LEVEL level)
{
	class Logger **ll=lstLogger->head;
	unsigned int length=lstLogger->length;
	unsigned int i;

  this->level=level;

	for(i=0;i<length;i++,ll++)
		(*ll)->testSetEnableEvent();
}

/*--------------------------------------------------------------------------*/
/* enable                                                                   */
/*--------------------------------------------------------------------------*/

void Appender::setEnable(int enable)
{
	class Logger **ll=lstLogger->head;
	unsigned int length=lstLogger->length;
	unsigned int i;

	this->enable=enable;

	for(i=0;i<length;i++,ll++)
		(*ll)->testSetEnableEvent();
}

/*--------------------------------------------------------------------------*/
/* addLogger                                                                */
/*--------------------------------------------------------------------------*/

int Appender::addLogger(class Logger *logger)
{
  if(lstLogger->add(logger,0))
		return 1;
	if(logger->addAppender(this))
		return 1;
	return 0;
}

/*--------------------------------------------------------------------------*/
/* removeLogger                                                             */
/*--------------------------------------------------------------------------*/

int Appender::removeLogger(class Logger *logger)
{
  if(lstLogger->remove(logger))
		return 1;
	if(logger->removeAppender(this))
		return 1;
	return 0;
}

/*--------------------------------------------------------------------------*/
/* removeAllLogger                                                          */
/*--------------------------------------------------------------------------*/

int Appender::removeAllLogger()
{
	class Logger **ll=lstLogger->head;
	unsigned int length=lstLogger->length;
	unsigned int i;
	int rc=0;

	for(i=0;i<length;i++,ll++)
		rc|=removeLogger(*ll);

	return rc;
}

/*--------------------------------------------------------------------------*/
/* out                                                                      */
/*--------------------------------------------------------------------------*/

void Appender::out(class Event *event)
{
	char *t;

	if(layout)
	{
		t=layout->makeTxt(event);

		switch(logAppender)
		{
			case aBUFFER:
				switch(triggerState)
				{
				case tRESET:
					break;
				case tWAIT:
					if(!event->triggerEnable)
						break;
					triggerState=tSTART;
				case tSTART:
					strcpy(bp,t);
					switch(triggerMode)
					{
						case tPREV:
							if(event->triggerEnable)
							{
								triggerState=tSTOP;
								strcat(bp," ***TRIGGER***");
							}
							break;
						case tMIDDLE:
							if(event->triggerEnable)
							{
								triggerMode=tMIDDLEcont;
								strcat(bp," ***TRIGGER***");
								pStopBuffer=bp+(GAL_MSG_TXT*(sizeBuffer/2));
								if(pStopBuffer>pEndBuffer)
									pStopBuffer-=(GAL_MSG_TXT*sizeBuffer);
							}
							break;
						case tMIDDLEcont:
							if(bp==pStopBuffer)
								triggerState=tSTOP;
							break;
						case tPOST:
							strcat(bp," ***TRIGGER***");
							triggerMode=tPOSTcont;
							break;
						case tPOSTcont:
							if(bp==pEndBuffer)
								triggerState=tSTOP;
							break;
						default:
							break;
					}

					if(triggerState==tSTOP)
					{
						flushAndClose();
						break;
					}

					if(bp==pEndBuffer)
					{
						ovBuffer=true;
						bp=pBegBuffer;
						break;
					}
					else
						bp+=GAL_MSG_TXT;

					break;
				case tSTOP:
					break;
				default:
					break;
				}
				break;

			case aFILE:
				Out::event(fp,t);
				break;

			case aSTDOUT:
				Out::event(t);
				break;

			case aNULL:
			default:
				break;
		}
	}
}

/*--------------------------------------------------------------------------*/
/* convertOut                                                               */
/*--------------------------------------------------------------------------*/

enum GAL_APPENDER Appender::convertOut(char *type)
{
	enum GAL_APPENDER a;

	if(strcmp(type,"FILE")==0)
		a=aFILE;
	else
	{
		if(strcmp(type,"STDOUT")==0)
			a=aSTDOUT;
		else
		{
			if(strcmp(type,"BUFFER")==0)
				a=aBUFFER;
			else
			{
				a=aNULL;
				throw "output device undefined";
			}
		}
	}

	return a;
}


/*--------------------------------------------------------------------------*/
/* convertTrigger                                                           */
/*--------------------------------------------------------------------------*/

enum GAL_TRIGGER_MODE Appender::convertTrigger(char *type)
{
	enum GAL_TRIGGER_MODE t;

	if(strcmp(type,"PREV")==0)
		t=tPREV;
	else
	{
		if(strcmp(type,"MIDDLE")==0)
			t=tMIDDLE;
		else
		{
			if(strcmp(type,"POST")==0)
				t=tPOST;
			else
			{
				t=tNULL;
				throw "trigger mode undefined";
			}
		}
	}

	return t;
}


/*--------------------------------------------------------------------------*/
/* setLayout                                                                */
/*--------------------------------------------------------------------------*/

void Appender::setLayout(class Layout *layout)
{
	this->layout=layout;
}


/*--------------------------------------------------------------------------*/
/* fillMode                                                                 */
/*--------------------------------------------------------------------------*/

void Appender::fillMode(enum GAL_TRIGGER_MODE *mode)
{
	char type[GAL_NAME];

	readLine();
	if(sscanf(stringLine,"mode=%s\n",type)!=1)
		throw "type";
	
	*mode=Appender::convertTrigger(type);
}

/*--------------------------------------------------------------------------*/
/* fillEvent                                                                */
/*--------------------------------------------------------------------------*/

void Appender::fillEvent()
{
	unsigned int i;
	char idEvent[GAL_NAME];
	char idRepository[GAL_NAME];
	class Event *event;
	unsigned int length;
	char *t;

	readLine();
	if(sscanf(stringLine,"nrEvent=%u\n",&length)!=1)
		throw "nrTrigger";

	for(i=0;i<length;i++)
	{
		readLine();
		if(sscanf(stringLine,"idRepository=%s idEvent=%s",idRepository,idEvent)!=2)
			throw "TriggerData";

		t=repository->findEvent(idRepository,idEvent,&event);
		if(t)
			throw t;
		
		event->triggerEnable=true;
	}
}

/*****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__
