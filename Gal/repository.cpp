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
** File(s)      : repository.cpp
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

#define __THISCLASS__ Repository
#define __CLASSNAME__ "Repository"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "repository.h"
#include "repository_l.h"
#include "lst.h"

/*****************************************************************************
****  METHODES / FUNCTIONS                                                ****
*****************************************************************************/

class Repository *Repository::singleInstance=NULL;

/*--------------------------------------------------------------------------*/
/* repository                                                               */
/*--------------------------------------------------------------------------*/

Repository::Repository()
{
  struct timeb tb;
  time_t tt;
	struct tm *tm;

	out=Out::getSingleInstance();
	aProt=aNULL;

	lstRepository_l=new Lst<class Repository_l>(GAL_LST_REPOSITORY_L_INIT);
	lstLogger=new Lst<class Logger>(GAL_LST_LOGGER_INIT);
	lstParam=new Lst<class Param>(GAL_LST_PARAM_INIT);
	lstFormat=new Lst<class Format>(GAL_LST_FORMAT_INIT);
	lstAppender=new Lst<class Appender>(GAL_LST_APPENDER_INIT);
	lstLayout=new Lst<class Layout>(GAL_LST_LAYOUT_INIT);

	ftime(&tb);
	tt=tb.time;
	tm=localtime(&tt);
	refTimeStart=tt-(60*60*tm->tm_hour+60*tm->tm_min+tm->tm_sec);
}

/*--------------------------------------------------------------------------*/
/* ~repository                                                              */
/*--------------------------------------------------------------------------*/

Repository::~Repository()
{
	terminate();
}

/*--------------------------------------------------------------------------*/
/* getSingleInstance                                                        */
/*--------------------------------------------------------------------------*/

class Repository *Repository::getSingleInstance()
{
	if(!singleInstance)
		singleInstance=new Repository();

	return singleInstance;
};

/*--------------------------------------------------------------------------*/
/* printRef                                                                 */
/*--------------------------------------------------------------------------*/

void Repository::printRef()
{
	char txt[GAL_TXT];
	class Repository_l **ll;
	unsigned int length;
	unsigned int i;

	sprintf(txt,"Repository: id=%s ref=0",id);
	Out::ref(txt);

 	lstLogger->printRef("nrLogger");
	lstParam->printRef("nrParam");
 	lstFormat->printRef("nrFormat");
	length=lstRepository_l->length;
	sprintf(txt,"nrRepository_l=%u",length);
	Out::ref(txt);

	Out::ref("");
	ll=lstRepository_l->head;
	for(i=0;i<length;i++,ll++)
	{
		(*ll)->printRef();
		Out::ref("");
	}
}

/*--------------------------------------------------------------------------*/
/* getRepository_l                                                          */	
/*--------------------------------------------------------------------------*/

class Repository_l *Repository::getRepository_l(char *fileName,char *id)
{
	class Repository_l *repository_l;

	repository_l=lstRepository_l->find(id);
	if(!repository_l)
		repository_l=new Repository_l(Repository::getSingleInstance(),fileName);

	return repository_l;
}

/*--------------------------------------------------------------------------*/
/* addRepository_l                                                          */	
/*--------------------------------------------------------------------------*/

int Repository::addRepository_l(class Repository_l *repository_l)
{
  return lstRepository_l->add(repository_l,1);
}

/*--------------------------------------------------------------------------*/
/* findLogger                                                               */
/*--------------------------------------------------------------------------*/

class Logger *Repository::findLogger(char *id)
{
  return lstLogger->find(id);
}

/*--------------------------------------------------------------------------*/
/* findParam                                                                */
/*--------------------------------------------------------------------------*/

class Param *Repository::findParam(char *id)
{
  return lstParam->find(id);
}

/*--------------------------------------------------------------------------*/
/* findFormat                                                               */
/*--------------------------------------------------------------------------*/

class Format *Repository::findFormat(char *id)
{
  return lstFormat->find(id);
}

/********************************** Appender ********************************/

/*--------------------------------------------------------------------------*/
/* addAppender                                                              */
/*--------------------------------------------------------------------------*/

char *Repository::addAppender(char *id,int enable,enum GAL_LEVEL level,enum GAL_APPENDER logAppender,char *nameDevice,unsigned long sizeBuffer,char *nameTrigger)
{
	static char txt[GAL_TXT];
	class Appender *appender;

	appender=new Appender(this,id,enable,level,logAppender,nameDevice,sizeBuffer,nameTrigger);
  if(lstAppender->add(appender,1))
	{
		sprintf(txt,"Appender %s already existent",id);
		return txt;
	}
	else
	 	return NULL;
}

/*--------------------------------------------------------------------------*/
/* findAppender                                                             */
/*--------------------------------------------------------------------------*/

char *Repository::findAppender(char *id,class Appender **foundAppender)
{
	static char txt[GAL_TXT];
	class Appender *appender;

	appender=lstAppender->find(id);
	if(!appender)
	{
		sprintf(txt,"Can't find appender %s",id);
		return txt;
	}
	*foundAppender=appender;
	return NULL;
}

/*--------------------------------------------------------------------------*/
/* removeAppender                                                           */
/*--------------------------------------------------------------------------*/

char *Repository::removeAppender(char *id)
{
	static char txt[GAL_TXT];
	char *t;
	class Appender *appender;
	int rc;

	t=findAppender(id,&appender);
	if(t)
		return t;

  if(lstAppender->remove(appender))
	{
		sprintf(txt,"Can't remove appender %s",id);
		return txt;
	}
	rc=appender->removeAllLogger();
	delete appender;

	if(rc)
	{
		sprintf(txt,"Remove all loggers failed for appender %s",id);
		return txt;
	}
	else
		return NULL;
}

/*--------------------------------------------------------------------------*/
/* enableAppender                                                           */
/*--------------------------------------------------------------------------*/

char *Repository::enableAppender(char *id,int enable)
{
	char *t;
	class Appender *appender;

	t=findAppender(id,&appender);
	if(t)
		return t;
	appender->setEnable(enable);
	return NULL;
}

/*--------------------------------------------------------------------------*/
/* setLevelAppender                                                         */
/*--------------------------------------------------------------------------*/

char *Repository::setLevelAppender(char *id,enum GAL_LEVEL level)
{
	char *t;
	class Appender *appender;

	t=findAppender(id,&appender);
	if(t)
		return t;
	appender->setLevel(level);
	return NULL;
}

/********************************** Layout **********************************/

/*--------------------------------------------------------------------------*/
/* addLayout                                                                */
/*--------------------------------------------------------------------------*/

char *Repository::addLayout(char *id,char *fmt)
{
	static char txt[GAL_TXT];
	class Layout *layout;

	layout=new Layout(this,id,fmt);
  if(lstLayout->add(layout,1))
	{
		sprintf(txt,"Layout %s already existent",id);
		return txt;
	}
	else
		return NULL;
}

/*--------------------------------------------------------------------------*/
/* findLayout                                                               */
/*--------------------------------------------------------------------------*/

char *Repository::findLayout(char *id,class Layout **foundLayout)
{
	static char txt[GAL_TXT];
	class Layout *layout;

	layout=lstLayout->find(id);
	if(!layout)
	{
		sprintf(txt,"Can't find layout %s",id);
		return txt;
	}
	*foundLayout=layout;
	return NULL;
}

/*--------------------------------------------------------------------------*/
/* removeLayout                                                             */
/*--------------------------------------------------------------------------*/

char *Repository::removeLayout(char *id)
{
	static char txt[GAL_TXT];
	char *t;
	class Layout *layout;

	t=findLayout(id,&layout);
	if(t)
		return t;

  lstLayout->remove(layout);
	{
		sprintf(txt,"Can't remove layout %s",id);
		return txt;
	}

	return NULL;
}

/********************************** Event **********************************/

/*--------------------------------------------------------------------------*/
/* findEvent                                                                */
/*--------------------------------------------------------------------------*/

char *Repository::findEvent(char *idRepository_l,char *idEvent,class Event **foundEvent)
{
	static char txt[GAL_TXT];
	class Repository_l *repository_l;

	repository_l=lstRepository_l->find(idRepository_l);
	if(!repository_l)
	{
		sprintf(txt,"Can't find repository %s of event %s",idRepository_l,idEvent);
		return txt;
	}
	return repository_l->findEvent(idEvent,foundEvent);
}

/********************************** Logger **********************************/

/*--------------------------------------------------------------------------*/
/* findLogger                                                               */
/*--------------------------------------------------------------------------*/

char *Repository::findLogger(char *idRepository_l,char *idLogger,class Logger **foundLogger)
{
	static char txt[GAL_TXT];
	class Repository_l *repository_l;

	repository_l=lstRepository_l->find(idRepository_l);
	if(!repository_l)
	{
		sprintf(txt,"Can't find repository %s of logger %s",idRepository_l,idLogger);
		return txt;
	}
	return repository_l->findLogger(idLogger,foundLogger);
}

char *Repository::findLogger(char *idLogger,class Logger **foundLogger)
{
	static char txt[GAL_TXT];
	class Logger *logger;

	logger=lstLogger->find(idLogger);
	if(!logger)
	{
		sprintf(txt,"Can't find logger %s in global repository",idLogger);
		return txt;
	}
	*foundLogger=logger;
	return NULL;
}

/*--------------------------------------------------------------------------*/
/* enableLogger                                                             */
/*--------------------------------------------------------------------------*/

char *Repository::enableLogger(char *idRepository_l,char *idLogger,int enable)
{
	static char txt[GAL_TXT];
	static char *t;
	class Logger *logger;

	t=findLogger(idRepository_l,idLogger,&logger);
	if(t)
		return t;

	if(logger->enable==enable)
	{
		sprintf(txt,"Logger %s in repository %s unchanged",idRepository_l,idLogger);
		return txt;
	}
	logger->enable=enable;
	return NULL;
}

char *Repository::enableLogger(char *idLogger,int enable)
{
	static char txt[GAL_TXT];
	char *t;
	class Logger *logger;

	t=findLogger(idLogger,&logger);
	if(t)
		return t;

	if(logger->enable==enable)
	{
		sprintf(txt,"Logger %s in global repository unchanged",idLogger);
		return txt;
	}
	logger->enable=enable;
	return NULL;
}

/*--------------------------------------------------------------------------*/
/* setLevelLogger                                                           */
/*--------------------------------------------------------------------------*/

char *Repository::setLevelLogger(char *idRepository_l,char *idLogger,enum GAL_LEVEL level)
{
	static char *t;
	class Logger *logger;

	t=findLogger(idRepository_l,idLogger,&logger);
	if(t)
		return t;

	logger->setLevel(level);
	return NULL;
}

char *Repository::setLevelLogger(char *idLogger,enum GAL_LEVEL level)
{
	char *t;
	class Logger *logger;

	t=findLogger(idLogger,&logger);
	if(t)
		return t;
	logger->setLevel(level);
	return NULL;
}

/********************************** connect**********************************/

/*--------------------------------------------------------------------------*/
/* connectAppenderLogger                                                    */
/*--------------------------------------------------------------------------*/

char *Repository::connectAppenderLogger(char *idAppender,char *idRepository_l,char *idLogger,int connect)
{
	class Logger *logger;
	class Appender *appender;
	static char txt[GAL_TXT];
	char *t;

	t=findAppender(idAppender,&appender);
	if(t)
		return t;

	t=findLogger(idRepository_l,idLogger,&logger);
	if(t)
		return t;

	if(connect)
	{
		if(appender->addLogger(logger))
		{
			sprintf(txt,"Cannot add logger %s in repository %s to appender %s",idLogger,idRepository_l,idAppender);
			return txt;
		}
		appender->used=true;
	}
	else
	{
		if(appender->removeLogger(logger))
		{
			sprintf(txt,"Cannot remove logger %s in repository %s from appender %s",idLogger,idRepository_l,idAppender);
			return txt;
		}
	}

	return NULL;
}

char *Repository::connectAppenderLogger(char *idAppender,char *idLogger,int connect)
{
	class Logger *logger;
	class Appender *appender;
	static char txt[GAL_TXT];
	char *t;

	t=findAppender(idAppender,&appender);
	if(t)
		return t;

	t=findLogger(idLogger,&logger);
	if(t)
		return t;

	if(connect)
	{
		if(appender->addLogger(logger))
		{
			sprintf(txt,"Cannot add logger %s in global repository to appender %s",idLogger,idAppender);
			return txt;
		}
		appender->used=true;
	}
	else
	{
		if(appender->removeLogger(logger))
		{
			sprintf(txt,"Cannot remove logger %s in global repository from appender %s",idLogger,idAppender);
			return txt;
		}
	}

	return NULL;
}

/*--------------------------------------------------------------------------*/
/* connectAppenderLayout                                                    */
/*--------------------------------------------------------------------------*/

char *Repository::connectAppenderLayout(char *idAppender,char *idLayout,int connect)
{
	class Layout *layout;
	class Appender *appender;
	char *t;
	static char txt[GAL_TXT];
		
	t=findAppender(idAppender,&appender);
	if(t)
		return t;

	t=findLayout(idLayout,&layout);
	if(t)
		return t;

	if(connect)
	{
		if(appender->layout)
		{
			if(appender->layout->removeAppender(appender))
			{
				sprintf(txt,"Cannot remove layout %s from appender %s",idLayout,idAppender);
				return txt;
			}
		}
		if(layout->addAppender(appender))
		{
			sprintf(txt,"Cannot add layout %s to appender %s",idLayout,idAppender);
			return txt;
		}
		appender->setLayout(layout);
		layout->used=true;
	}
	else
	{
		if(appender->layout!=layout)
		{
			sprintf(txt,"Layout %s doesn't belong to appender %s",idLayout,idAppender);
			return txt;
		}
		if(appender->layout->removeAppender(appender))
		{
			sprintf(txt,"Cannot remove layout %s from appender %s",idLayout,idAppender);
			return txt;
		}
		appender->setLayout(NULL);
	}

	return NULL;
}

/********************************** utilities *******************************/

/*--------------------------------------------------------------------------*/
/* init                                                                     */
/*--------------------------------------------------------------------------*/

char *Repository::init(char *confFileName)
{
	static int initialized=0;
	char *tf="Gal initialization failed";
	static char txt[GAL_TXT];
	char *t;
	int errFlag=0;

	if(initialized)
		return NULL;

	initialized=1;

 	strcpy(txt,tf);

	if(configureLogging(confFileName))
	{
		errFlag=1;
	}
	else
	{
		makeReferences();
		printRef();
		Out::closeRefOut();

		findUnusedEventFormatParam();
	}

	t=out->setProtOut(aProt);
	if(t)
	{
		strcat(txt,": ");
		strcat(txt,t);
		errFlag=1;
	}

	return errFlag?txt:NULL;

}

/*--------------------------------------------------------------------------*/
/* terminate                                                                */
/*--------------------------------------------------------------------------*/

void Repository::terminate()
{
	printEventStatistics();

	if(lstLogger)
	{
		lstLogger->freeElm();
		delete lstLogger;
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
	if(lstAppender)
	{
	 	lstAppender->freeElm();
		delete lstAppender;
	}
	if(lstLayout)
	{
		lstLayout->freeElm();
		delete lstLayout;
	}
	if(lstRepository_l)
	{
		lstRepository_l->freeElm();
		delete lstRepository_l;
	}

	if(out)
		delete out;
}

/*--------------------------------------------------------------------------*/
/* printEventStatistics                                                     */
/*--------------------------------------------------------------------------*/

void Repository::printEventStatistics()
{
	class Repository_l **ll=lstRepository_l->head;
	unsigned int length=lstRepository_l->length;
	unsigned int i;

	for(i=0;i<length;i++,ll++)
		(*ll)->printEventStatistics();
}

/*--------------------------------------------------------------------------*/
/* findUnusedEventFormatParam                                               */
/*--------------------------------------------------------------------------*/

void Repository::findUnusedEventFormatParam()
{
	class Repository_l **ll=lstRepository_l->head;
	unsigned int length=lstRepository_l->length;
	unsigned int i;

	lstAppender->findUnused("Global Repository (Appender)");
	lstLayout->findUnused("Global Repository (Layout)");
	lstLogger->findUnused("Global Repository (Logger)");
	lstParam->findUnused("Global Repository (Observer)");
	lstFormat->findUnused("Global Repository (Format)");

	for(i=0;i<length;i++,ll++)
		(*ll)->findUnusedEventFormatParam();
}

/*--------------------------------------------------------------------------*/
/* configureLogging                                                         */
/*--------------------------------------------------------------------------*/

int Repository::configureLogging(char *confFileName)
{
	static char *fn="Repository::configureLogging";
	char ftxt[GAL_TXT];
	class Appender **aa;
	unsigned int length;
	unsigned int i;
	char confFileNamePath[GAL_PATH_FILENAME];
	char *t;

	line=0;

	fp=fopen(confFileName,"r");
	if(!fp)
	{
		t=getenv("GERTICO");
		if(t==NULL)
		{
			sprintf(ftxt,"Can't open local file %s. Can't open environment variable GERTICO",confFileName);
			Out::error(fn,ftxt);
			return 1;
		}
#ifdef WIN32
		sprintf(confFileNamePath,"%s\\GalRes\\%s",t,confFileName);
#else
		sprintf(confFileNamePath,"%s/GalRes/%s",t,confFileName);
#endif
		fp=fopen(confFileNamePath,"r");
		if(!fp)
		{
			sprintf(ftxt,"Can't open file %s",confFileNamePath);
			Out::error(fn,ftxt);
			return 1;
		}
	}

  try
	{
		fillVersion();
		fillId();
		fillProtOut();
		fillLogger();
		fillParam();
		fillFormat();

		if(makeEventFormatReferences())
			return 1;

		fillAppender();
		fillLayout();
		fillConnectAppenderLayout();
		fillConnectAppenderLoggerGlobal();
		fillConnectAppenderLoggerLocal();

		fclose(fp);

		aa=lstAppender->head;
		length=lstAppender->length;

		for(i=0;i<length;i++,aa++)
			(*aa)->configure();
	}
	catch(char *s)
	{
		fclose(fp);
		sprintf(ftxt,"File=%s Error in line %u: %s",confFileName,line,s);
		Out::error(fn,ftxt);
		return 1;
	}
	catch(const char *s)
	{
		fclose(fp);
		sprintf(ftxt,"File=%s Error in line %u: %s",confFileName,line,s);
		Out::error(fn,ftxt);
		return 1;
	}

	return 0;
}

/*--------------------------------------------------------------------------*/
/* fillId                                                                   */
/*--------------------------------------------------------------------------*/

void Repository::fillId()
{
	readLine();
	if(sscanf(stringLine,"id=%s\n",id)!=1)
		throw "id";
}

/*--------------------------------------------------------------------------*/
/* fillProtOut                                                              */
/*--------------------------------------------------------------------------*/

void Repository::fillProtOut()
{
	char type[GAL_NAME];

	readLine();
	if(sscanf(stringLine,"out=%s\n",type)!=1)
		throw "out";

	aProt=Appender::convertOut(type);

	if(!((aProt==aFILE)||(aProt==aSTDOUT)))
		throw "out";
}

/*--------------------------------------------------------------------------*/
/* fillLogger                                                               */
/*--------------------------------------------------------------------------*/

void Repository::fillLogger()
{
	unsigned int i;
	char id[GAL_NAME];
	char ctxt[GAL_CTXT];
	class Logger *logger;
	unsigned int length;
	char slevel[GAL_LEVEL_GROUP];
	unsigned int enable;
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
			throw "Can't add logger to global repository";
	}
}

/*--------------------------------------------------------------------------*/
/* fillParam                                                                */
/*--------------------------------------------------------------------------*/

void Repository::fillParam()
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
		if(sscanf(stringLine,"id=%s fmt=%s\n",id,fmt)!=1)
			throw "ObserverData";
		param=new Param(this,id,fmt);
		if(lstParam->add(param,1))
			throw "Can't add param to global repository";
	}
}

/*--------------------------------------------------------------------------*/
/* fillFormat                                                               */
/*--------------------------------------------------------------------------*/

void Repository::fillFormat()
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
			throw "Can't add format to global repository";
	}
}

/*--------------------------------------------------------------------------*/
/* fillAppender                                                             */
/*--------------------------------------------------------------------------*/

void Repository::fillAppender()
{
	unsigned int i;
        unsigned int j;
	char id[GAL_NAME];
	char type[GAL_NAME];
	char nameDevice[GAL_FILENAME];
	char nameTrigger[GAL_FILENAME];
	enum GAL_APPENDER aProt;
        unsigned int len;
	unsigned int length;
	unsigned int enable;
	char slevel[GAL_LEVEL_GROUP];;
	enum GAL_LEVEL level;
	unsigned long size;
	char *t;

	readLine();
	if(sscanf(stringLine,"nrAppender=%u\n",&length)!=1)
		throw "nrAppender";

	for(i=0;i<length;i++)
	{
		readLine();
		if(sscanf(stringLine,"id=%s enable=%d level=%s out=%s",id,&enable,slevel,type)!=4)
			throw "AppenderData";

		level=Event::convertLevel(slevel);

		aProt=Appender::convertOut(type);

		switch(aProt)
		{
			case aFILE:
				if(sscanf(stringLine,"id=%s enable=%u level=%s out=%s name=%s",id,&enable,slevel,type,nameDevice)!=5)
					throw "name";
// Unix/Windows directory level separator.
len = strlen(nameDevice);
for (j = 0; j < len; j++)
{
#ifdef WIN32
  if (nameDevice[j] == '/')
    nameDevice[j] = '\\';
#else
  if (nameDevice[j] == '\\')
    nameDevice[j] = '/';
#endif
}
				t=addAppender(id,enable,level,aFILE,nameDevice,0,"");
				break;
			case aSTDOUT:
			  t=addAppender(id,enable,level,aSTDOUT,"",0,"");
				break;
			case aBUFFER:
				if(sscanf(stringLine,"id=%s enable=%u level=%s out=%s name=%s size=%lu trigger=%s",id,&enable,slevel,type,nameDevice,&size,nameTrigger)!=7)
					throw "name/size";
// Unix/Windows directory level separator.
len = strlen(nameDevice);
for (j = 0; j < len; j++)
{
#ifdef WIN32
  if (nameDevice[j] == '/')
    nameDevice[j] = '\\';
#else
  if (nameDevice[j] == '\\')
    nameDevice[j] = '/';
#endif
}
len = strlen(nameTrigger);
for (j = 0; j < len; j++)
{
#ifdef WIN32
  if (nameTrigger[j] == '/')
    nameTrigger[j] = '\\';
#else
  if (nameTrigger[j] == '\\')
    nameTrigger[j] = '/';
#endif
}


			  t=addAppender(id,enable,level,aBUFFER,nameDevice,size,nameTrigger);
				break;
			default:
				throw "out";
				break;
		}

		if(t)throw t;
	}
}

/*--------------------------------------------------------------------------*/
/* fillLayout                                                               */
/*--------------------------------------------------------------------------*/

void Repository::fillLayout()
{
	unsigned int i;
	char id[GAL_NAME];
	char fmt[GAL_TXT];
	unsigned int length;
	char *t;
		
	readLine();
	if(sscanf(stringLine,"nrLayout=%u\n",&length)!=1)
		throw "nrLayout";

	for(i=0;i<length;i++)
	{
		readLine();
		if(sscanf(stringLine,"id=%s",id)!=1)
			throw "LayoutId";
		if(readTxt("fmt=",fmt))
			throw "LayoutData";

		t=addLayout(id,fmt);
		if(t)throw t;
	}
}

/*--------------------------------------------------------------------------*/
/* fillConnectAppenderLayout                                                */
/*--------------------------------------------------------------------------*/

void Repository::fillConnectAppenderLayout()
{
	unsigned int i;
	char idAppender[GAL_NAME];
	char idLayout[GAL_NAME];
	unsigned int length;
	char *t;
		
	readLine();
	if(sscanf(stringLine,"nrConnectAppenderLayout=%u\n",&length)!=1)
		throw "nrConnectAppenderLayout";

	for(i=0;i<length;i++)
	{
		readLine();
		if(sscanf(stringLine,"idAppender=%s idLayout=%s",idAppender,idLayout)!=2)
			throw "ConnectAppenderLayoutData";
    t=connectAppenderLayout(idAppender,idLayout,true);
		if(t)throw t;
	}
}

/*--------------------------------------------------------------------------*/
/* fillConnectAppenderLoggerGlobal                                          */
/*--------------------------------------------------------------------------*/

void Repository::fillConnectAppenderLoggerGlobal()
{
	unsigned int i;
	char idAppender[GAL_NAME];
	char idLogger[GAL_NAME];
	unsigned int length;
	char *t;
		
	readLine();
	if(sscanf(stringLine,"nrConnectAppenderLoggerGlobal=%u\n",&length)!=1)
		throw "nrConnectAppenderLoggerGlobal";

	for(i=0;i<length;i++)
	{
		readLine();
		if(sscanf(stringLine,"idAppender=%s idLogger=%s",idAppender,idLogger)!=2)
			throw "ConnectAppenderLoggerGlobalData";
    t=connectAppenderLogger(idAppender,idLogger,true);
		if(t)
			Out::warning("ConnectAppenderLoggerGlobal",t);
	}
}

/*--------------------------------------------------------------------------*/
/* fillConnectAppenderLoggerLocal                                           */
/*--------------------------------------------------------------------------*/

void Repository::fillConnectAppenderLoggerLocal()
{
	unsigned int i;
	char idAppender[GAL_NAME];
	char idRepository[GAL_NAME];
	char idLogger[GAL_NAME];
	unsigned int length;
	char *t;
		
	readLine();
	if(sscanf(stringLine,"nrConnectAppenderLoggerLocal=%u\n",&length)!=1)
		throw "nrConnectAppenderLoggerLocal";

	for(i=0;i<length;i++)
	{
		readLine();
		if(sscanf(stringLine,"idAppender=%s idRepository=%s idLogger=%s",idAppender,idRepository,idLogger)!=3)
			throw "ConnectAppenderLoggerLocalData";
    t=connectAppenderLogger(idAppender,idRepository,idLogger,true);
		if(t)
			Out::warning("ConnectAppenderLoggerLocal",t);
	}
}

/*--------------------------------------------------------------------------*/
/* removeAllUnusedAppender                                                  */
/*--------------------------------------------------------------------------*/

int Repository::removeAllUnusedAppender()
{
	class Appender **aa=lstAppender->head;
	unsigned int length=lstAppender->length;
	class Appender *a;
	unsigned int i;
	int rc=0;

	for(i=0;i<length;i++,aa++)
	{
		a=*aa;
		if(!a->getNrLogger())
			rc|=lstAppender->remove(a);
	}
	return rc;
}

/*--------------------------------------------------------------------------*/
/* removeAllUnusedLayout                                                    */
/*--------------------------------------------------------------------------*/

int Repository::removeAllUnusedLayout()
{
	class Layout **ll=lstLayout->head;
	unsigned int length=lstLayout->length;
	class Layout *l;
	unsigned int i;
	int rc=0;

	for(i=0;i<length;i++,ll++)
	{
		l=*ll;
		if(!l->getNrAppender())
			rc|=lstLayout->remove(l);
	}
	return rc;
}

/*--------------------------------------------------------------------------*/
/* makeEventReferences                                                      */
/*--------------------------------------------------------------------------*/

int Repository::makeEventFormatReferences()
{
	class Repository_l **ll=lstRepository_l->head;
	unsigned int length=lstRepository_l->length;
	unsigned int i;
	int rc=0;

	for(i=0;i<length;i++,ll++)
	{
		if((*ll)->checkIn)
		{
			rc|=(*ll)->makeFormatReferences();
			rc|=(*ll)->makeEventReferences();
		}
	}
	return rc;
}

/*--------------------------------------------------------------------------*/
/* makeReferences                                                           */
/*--------------------------------------------------------------------------*/

void Repository::makeReferences()
{
	class Repository_l **ll=lstRepository_l->head;
	unsigned int length=lstRepository_l->length;
	unsigned int i;

	lstLogger->makeRef();
	lstParam->makeRef();
	lstFormat->makeRef();
	lstRepository_l->makeRef();

	for(i=0;i<length;i++,ll++)
	{
		if((*ll)->checkIn)
			(*ll)->makeReferences();
	}
}

/*****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__

