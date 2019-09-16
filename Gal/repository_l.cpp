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
** File(s)      : repository_l.cpp
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
** Description  : repository 
**              :
*****************************************************************************/

#define __THISCLASS__ Repository_l
#define __CLASSNAME__ "Repository_l"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "repository_l.h"
#include "repository.h"
#include "logger.h"

/*****************************************************************************
****  METHODES / FUNCTIONS                                                ****
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/* repository_l                                                             */
/*--------------------------------------------------------------------------*/

Repository_l::Repository_l(class Repository *repository,char *rcFileName)
{
	checkIn=false;

	lstEvent=new Lst<class Event>(GAL_LST_EVENT_INIT);
	lstLogger=new Lst<class Logger>(GAL_LST_LOGGER_INIT);
	lstParam=new Lst<class Param>(GAL_LST_PARAM_INIT);
	lstFormat=new Lst<class Format>(GAL_LST_FORMAT_INIT);

	this->repository=repository;
	strcpy(this->rcFileName,rcFileName);
	admRepository_l();
	initialized=false;
}

/*--------------------------------------------------------------------------*/
/* ~repository_l                                                            */
/*--------------------------------------------------------------------------*/

Repository_l::~Repository_l()
{

	if(lstLogger)
	{
		lstLogger->freeElm();
		delete lstLogger;
	}
	if(lstEvent)
	{
		lstEvent->freeElm();
		delete lstEvent;
	}
	if(lstParam)
	{
		lstParam->freeElm();
		delete lstParam;
	}
	if(lstFormat)
	{
		lstFormat->freeElm();
		delete lstFormat;
	}
}

/*--------------------------------------------------------------------------*/
/* printEventStatistics                                                     */
/*--------------------------------------------------------------------------*/

void Repository_l::printEventStatistics()
{
	unsigned int i;
	class Event **ee=lstEvent->head;
	class Event *event;
	unsigned int length=lstEvent->length;
	char txt[GAL_TXT];

	sprintf(txt,"%8s",id);
	Out::stat(txt);

	for(i=0;i<length;i++)
	{
		event=*ee++;
		sprintf(txt,"%8s %8lu",event->id,event->cnt);
		Out::stat(txt);
	}
	Out::stat("");
}

/*--------------------------------------------------------------------------*/
/* printRef                                                                 */
/*--------------------------------------------------------------------------*/

void Repository_l::printRef()
{
	char txt[GAL_TXT];

	sprintf(txt,"Repository_l: id=%s ref=%u",id,refGallIndex);
	Out::ref(txt);

 	lstLogger->printRef("nrLogger");
	lstParam->printRef("nrParam");
 	lstFormat->printRef("nrFormat");
 	lstEvent->printRef("nrEvent");
}

/*--------------------------------------------------------------------------*/
/* findUnusedEventFormatParam                                               */
/*--------------------------------------------------------------------------*/

void Repository_l::findUnusedEventFormatParam()
{
	char txt[GAL_TXT];

	sprintf(txt,"Local repository %s (Logger)",id);
	lstLogger->findUnused(txt);
	sprintf(txt,"Local repository %s (Param)",id);
	lstParam->findUnused(txt);
	sprintf(txt,"Local repository %s (Format)",id);
	lstFormat->findUnused(txt);
	sprintf(txt,"Local repository %s (Event)",id);
	lstEvent->findUnused(txt);
}

/*--------------------------------------------------------------------------*/
/* fill                                                                     */
/*--------------------------------------------------------------------------*/

int Repository_l::fill()
{
	static char *fn="Repository_l::fill";
	char ftxt[GAL_TXT];
	char txt[GAL_TXT];
	char rcFileNamePath[GAL_PATH_FILENAME];
	char *t;

	if(initialized)
	{
		Out::warning(fn,"cannot be called twice");
		return 1;
	}
	initialized=true;

	line=0;

	fp=fopen(rcFileName,"r");
	if(!fp)
	{
		t=getenv("GERTICO");
		if(t==NULL)
		{
			sprintf(ftxt,"Can't open local file %s. Can't open environment variable GERTICO",rcFileName);
			Out::error(fn,ftxt);
			return 1;
		}
#ifdef WIN32
		sprintf(rcFileNamePath,"%s\\GalRes\\%s",t,rcFileName);
#else
		sprintf(rcFileNamePath,"%s/GalRes/%s",t,rcFileName);
#endif
		fp=fopen(rcFileNamePath,"r");
		if(!fp)
		{
			sprintf(ftxt,"Can't open file %s.",rcFileNamePath);
			Out::error(fn,ftxt);
			return 1;
		}
	}

  try
	{
		fillVersion();
		fillId();
		if(repository->addRepository_l(this))
		{
			sprintf(txt,"Local repository with id %s already defined",id);
			throw txt;
		}
		fillLogger();
		fillParam();
		fillFormat();
		fillEvent();

		fclose(fp);
	}
	catch(char *s)
	{
		fclose(fp);
		sprintf(ftxt,"File=%s Error in line %u typ %s",rcFileName,line,s);
		Out::error(fn,ftxt);
		return 1;
	}
	catch(const char *s)
	{
		fclose(fp);
		sprintf(ftxt,"File=%s Error in line %u typ %s",rcFileName,line,s);
		Out::error(fn,ftxt);
		return 1;
	}

	checkIn=true;
	return 0;
}
 

/*--------------------------------------------------------------------------*/
/* fillId                                                                   */
/*--------------------------------------------------------------------------*/

void Repository_l::fillId()
{
	readLine();
	if(sscanf(stringLine,"id=%s\n",id)!=1)
		throw "id";
}

/*--------------------------------------------------------------------------*/
/* fillLogger                                                               */
/*--------------------------------------------------------------------------*/

void Repository_l::fillLogger()
{
	unsigned int i;
	char id[GAL_NAME];
	char ctxt[GAL_CTXT];
	class Logger *logger;
	unsigned int length;
	unsigned int enable;
	char slevel[GAL_LEVEL_GROUP];
	enum GAL_LEVEL level;
	unsigned int group;
		
// Logger
	
	readLine();
	if(sscanf(stringLine,"nrLogger=%u\n",&length)!=1)
		throw "nrLogger";

	for(i=0;i<length;i++)
	{
		readLine();
		if(sscanf(stringLine,"id=%s enable=%d level=%s group=%x",id,&enable,slevel,&group)!=4)
			throw "LoggerData";

		level=Event::convertLevel(slevel);

		if(readTxt("ctxt=",ctxt))
			throw "LoggerData(ctxt)";
		logger=new Logger(this,id,enable,level,group,ctxt);
		if(lstLogger->add(logger,1))
			throw "Can't add logger to local repository";
	}
}

/*--------------------------------------------------------------------------*/
/* fillParam                                                                */
/*--------------------------------------------------------------------------*/

void Repository_l::fillParam()
{
	unsigned int i;
	char id[GAL_NAME];
	class Param *param;
	char fmt[GAL_CTXT];
	unsigned int length;

	readLine();
	if(sscanf(stringLine,"nrObserver=%u\n",&length)!=1)
		throw "nrObserver";

	for(i=0;i<length;i++)
	{
		readLine();
		if(sscanf(stringLine,"id=%s fmt=%s\n",id,fmt)!=2)
			throw "ObserverData";
		param=new Param(this,id,fmt);
		if(lstParam->add(param,1))
			throw "Can't add param to local repository";
	}
}

/*--------------------------------------------------------------------------*/
/* fillFormat                                                               */
/*--------------------------------------------------------------------------*/

void Repository_l::fillFormat()
{
	unsigned int i;
	char id[GAL_NAME];
	class Format *format;
	char ctxt[GAL_CTXT];
	char vtxt[GAL_CTXT];
	unsigned int length;

	readLine();
	if(sscanf(stringLine,"nrFormat=%u\n",&length)!=1)
		throw "nrFormat";

	for(i=0;i<length;i++)
	{
		readLine();
		if(sscanf(stringLine,"id=%s\n",id)!=1)
			throw "FormatData";
		if(readTxt("ctxt=",ctxt))
			throw "FormatData(ctxt)";
		if(readTxt("vtxt=",vtxt)==1)
			throw "FormatData(vtxt)";
		format=new Format(this,id,ctxt,vtxt);
		if(lstFormat->add(format,1))
			throw "Can't add format to local repository";
	}
}

/*--------------------------------------------------------------------------*/
/* fillEvent                                                                */
/*--------------------------------------------------------------------------*/

void Repository_l::fillEvent()
{
	unsigned int i;
	char id[GAL_NAME];
	char ctxt[GAL_CTXT];
	char ctxtHead[GAL_CTXT];
	char ctxtHeadNew[GAL_CTXT];
	char txt[GAL_CTXT];
	char idLogger[GAL_NAME];
	char idFormat[GAL_NAME];
	class Event *event;
	unsigned int length;
	unsigned int enable;
	char slevel[GAL_LEVEL_GROUP];
	enum GAL_LEVEL level;
	unsigned int group;
	int rc;

	readLine();
	if(sscanf(stringLine,"nrEvent=%u\n",&length)!=1)
		throw "nrEvent";

	strcpy(ctxtHead,"");
	for(i=0;i<length;i++)
	{
		readLine();
		if(sscanf(stringLine,"id=%s enable=%d level=%s group=%x idLogger=%s idFormat=%s\n",id,&enable,slevel,&group,idLogger,idFormat)!=6)
			throw "EventData";

		level=Event::convertLevel(slevel);
				
		if(readTxt("ctxt=",ctxt))
			throw "EventData(ctxt)";

		rc=readTxt("ctxtHead=",ctxtHeadNew);
		if(rc==1)
			throw "EventData(ctxtHead)";
		if(rc==0)
			strcpy(ctxtHead,ctxtHeadNew);

		if(strcmp(ctxtHead,"")==0)
			strcpy(txt,ctxt);
		else
		{
			if(strcmp(ctxt,"")==0)
				sprintf(txt,"%s",ctxtHead);
			else
				sprintf(txt,"%s: %s",ctxtHead,ctxt);
		}

		event=new Event(this,id,enable,level,group,txt,idLogger,idFormat);
	
		if(lstEvent->add(event,1))
			throw "Can't add event to repository";
	}
}

/*--------------------------------------------------------------------------*/
/* getRefEvent                                                              */
/*--------------------------------------------------------------------------*/

class Event *Repository_l::getRefEvent(char *id)
{
	static Event defEvent; // enabled ist false !!!
	char *fn="Repository_l::getRefEvent";
	char txt[GAL_TXT];
	class Event *event;

	if(initialized==false)
		fill();
	
	event=lstEvent->find(id);
	if(event)
	{
		event->used=true;
		return event;
	}

	sprintf(txt,"Can't find event with id %s in repository %s",id,this->id);
	Out::warning(fn,txt);

	return &defEvent;
}

/*--------------------------------------------------------------------------*/
/* makeFormatReferences                                                     */
/*--------------------------------------------------------------------------*/

int Repository_l::makeFormatReferences()
{
	char *fn="Repository_l::makeFormatReferences";
	char ftxt[GAL_TXT];
	unsigned int i;
	class Param *param;
	class Format **ff=lstFormat->head;
	class Format *format;
	unsigned int length=lstFormat->length;
	char id[GAL_TXT];
	char *pid;
	unsigned int j;
	char *f;
	int flag=0;

	for(i=0;i<length;i++)
	{
		format=*ff++;
		strcpy(ftxt,format->vtxt);
		strcat(ftxt," ");
		f=ftxt;

		pid=id;
		id[0]=0;
		flag=0;
		for(j=0;j<strlen(ftxt);j++,f++)
		{
			if(*f==' ')
				continue;
			*pid++=*f;
			if(*(f+1)!=' ')
				continue;
			*pid=0;

			param=lstParam->find(id); // local
			if(param==NULL)
			{
				param=repository->findParam(id); // gobal
				if(param==NULL)
				{
					sprintf(ftxt,"Can't find param references %s for idFormat=%s",id,format->id);
					Out::error(fn,ftxt);
					return 1;
				}
			}
			param->used=true;

			flag=1;
			strcat(format->hfmt,id);
			strcat(format->hfmt," ");
			strcat(format->fmt,param->fmt);
			strcat(format->fmt," ");

			pid=id;
			id[0]=0;
		}
		if(flag)
			format->fmt[strlen(format->fmt)-1]=0;
	}

	return 0;
}

/*--------------------------------------------------------------------------*/
/* makeEventReferences                                                      */
/*--------------------------------------------------------------------------*/

int Repository_l::makeEventReferences()
{
	char *fn="Repository_l::makeReferences";
	char ftxt[GAL_TXT];
	unsigned int i;
	class Logger *logger;
	class Format *format;
	class Event **ee=lstEvent->head;
	class Event *event;
	unsigned int length=lstEvent->length;

	for(i=0;i<length;i++)
	{
		event=*ee++;
		logger=lstLogger->find(event->idLogger); // local
		if(logger==NULL)
		{
			logger=repository->findLogger(event->idLogger); // gobal
			if(logger==NULL)
			{
				sprintf(ftxt,"Can't find logger reference %s for event %s",event->idLogger,event->id);
				Out::error(fn,ftxt);
				return 1;
			}
		}
		logger->used=true;

		event->logger=logger;
		logger->addEvent(event);

		format=lstFormat->find(event->idFormat);
		if(format==NULL)
		{
			format=repository->findFormat(event->idFormat);
			if(format==NULL)
			{
				sprintf(ftxt,"Can't find format reference %s for event %s",event->idFormat,event->id);
				Out::error(fn,ftxt);
				return 1;
			}
		}
		format->used=true;

		event->format=format;
	}

	return 0;
}

/*--------------------------------------------------------------------------*/
/* makeReferences                                                           */
/*--------------------------------------------------------------------------*/

void Repository_l::makeReferences()
{
	lstLogger->makeRef(refGallIndex);
	lstParam->makeRef(refGallIndex);
	lstFormat->makeRef(refGallIndex);
	lstEvent->makeRef(refGallIndex);
}

/*--------------------------------------------------------------------------*/
/* findEvent                                                               */
/*--------------------------------------------------------------------------*/

char *Repository_l::findEvent(char *idEvent,class Event **foundEvent)
{
	static char txt[GAL_TXT];
	class Event *Event;

	if(!checkIn)
	{
		sprintf(txt,"Repository %s not ok",id);
		return txt;
	}
	Event=lstEvent->find(idEvent);
	if(!Event)
	{
		sprintf(txt,"Can't find Event %s in repository %s",idEvent,id);
		return txt;
	}
	*foundEvent=Event;
	return NULL;
}

/*--------------------------------------------------------------------------*/
/* findLogger                                                               */
/*--------------------------------------------------------------------------*/

char *Repository_l::findLogger(char *idLogger,class Logger **foundLogger)
{
	static char txt[GAL_TXT];
	class Logger *logger;

	if(!checkIn)
	{
		sprintf(txt,"Repository %s not ok",id);
		return txt;
	}
	logger=lstLogger->find(idLogger);
	if(!logger)
	{
		sprintf(txt,"Can't find logger %s in repository %s",idLogger,id);
		return txt;
	}
	*foundLogger=logger;
	return NULL;
}

char *Repository_l::findLogger(unsigned int idLogger,class Logger **foundLogger)
{
	static char txt[GAL_TXT];

	if(!checkIn)
	{
		sprintf(txt,"Repository with index %u not ok",refGallIndex);
		return txt;
	}
	if((idLogger>(lstLogger->length))||(idLogger==0))
	{
		sprintf(txt,"Logger with index %u in repository with index %u not existent",idLogger,refGallIndex);
		return txt;
	}
	*foundLogger=*(lstLogger->head+idLogger-1);
	return NULL;
}

/*****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__

