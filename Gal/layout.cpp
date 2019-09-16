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
** File(s)      : layout.cpp
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
** Description  : layout
**              :
*****************************************************************************/

#define __THISCLASS__ Layout
#define __CLASSNAME__ "Layout"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "layout.h"
#include "repository.h"
#include <string.h>

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/


/*--------------------------------------------------------------------------*/
/* layout                                                                   */
/*--------------------------------------------------------------------------*/

Layout::Layout(class Repository *repository,char *id,char *fmt)
{
	this->repository=repository;
	strcpy(this->fmt,fmt);
	lstAppender=new Lst<class Appender>(GAL_LST_APPENDER_INIT);
	admAppenderLayout(id);
}

/*--------------------------------------------------------------------------*/
/* ~layout                                                                  */
/*--------------------------------------------------------------------------*/

Layout::~Layout()
{
	if(lstAppender)
		delete lstAppender;
}

/*--------------------------------------------------------------------------*/
/* getNrAppender                                                            */
/*--------------------------------------------------------------------------*/

unsigned int Layout::getNrAppender()
{
	return lstAppender->length;
}

/*--------------------------------------------------------------------------*/
/* addAppender                                                              */
/*--------------------------------------------------------------------------*/

int Layout::addAppender(class Appender *appender)
{
  return lstAppender->add(appender,0);
}

/*--------------------------------------------------------------------------*/
/* removeAppender                                                           */
/*--------------------------------------------------------------------------*/

int Layout::removeAppender(class Appender *appender)
{
	appender->setLayout(NULL);
  return lstAppender->remove(appender);
}

/*--------------------------------------------------------------------------*/
/* removeAllAppender                                                        */
/*--------------------------------------------------------------------------*/

int Layout::removeAllAppender()
{
	class Appender **aa=lstAppender->head;
	unsigned int length=lstAppender->length;
	unsigned int i;
	int rc=0;

	for(i=0;i<length;i++,aa++)
		rc|=removeAppender(*aa);

	return rc;
}


/*--------------------------------------------------------------------------*/
/* makeTxt                                                                  */
/*--------------------------------------------------------------------------*/

char *Layout::makeTxt(class Event *event)
{
	static char msgTxt[GAL_MSG_TXT];
	unsigned int i;
	char *p;
  struct timeb tb;
	time_t tt;
	char *t;
#ifndef WIN32
	struct timeval tv;
  struct timezone tz;
#endif

	msgTxt[0]=0;
	for(i=0,p=fmt;i<strlen(fmt);i++)
	{
		if(*p++=='%')
		{
			switch(*p++)
			{
//beep
				case 'B':
					sprintf(&msgTxt[strlen(msgTxt)],"beep");
				case 'b':
					printf("%c",(char)7);
					break;

//event
				case 'e':
				case 'E':
					switch(*p++)
					{
						case 'C':
							sprintf(&msgTxt[strlen(msgTxt)],"%s=",event->format->ctxt);
						case 'c':
							sprintf(&msgTxt[strlen(msgTxt)],"<%s> ",event->ctxt);
							break;
						case 'L':
							sprintf(&msgTxt[strlen(msgTxt)],"level=");
						case 'l':
							sprintf(&msgTxt[strlen(msgTxt)],"%s ",Event::convertLevel(event->level));
							break;
						case 'V':
							if(event->txt[0])
								sprintf(&msgTxt[strlen(msgTxt)],"observ=<%s> ",event->format->makeTxt(event->txt));
							break;
						case 'v':
							if(event->txt[0])
								sprintf(&msgTxt[strlen(msgTxt)],"<%s> ",event->txt);
							break;
						case 't':
							if(event->txt[0])
								sprintf(&msgTxt[strlen(msgTxt)],"%s",event->txt);
							break;
						case 'R':
							sprintf(&msgTxt[strlen(msgTxt)],"ref=");
						case 'r':
							sprintf(&msgTxt[strlen(msgTxt)],"%u/%u ",event->refGallRepository,event->refGallIndex);
							break;
						case 'I':
							sprintf(&msgTxt[strlen(msgTxt)],"ident=");
						case 'i':
							sprintf(&msgTxt[strlen(msgTxt)],"%s ",event->id);
							break;
						default:
							break;
					}
					break;

//format
				case 'F':
					sprintf(&msgTxt[strlen(msgTxt)],"format=");
				case 'f':
					sprintf(&msgTxt[strlen(msgTxt)],"%s ",event->format->id);
					break;

//logger
				case 'l':
				case 'L':
					switch(*p++)
					{
						case 'C':
							sprintf(&msgTxt[strlen(msgTxt)],"logger=");
						case 'c':
							sprintf(&msgTxt[strlen(msgTxt)],"<%s> ",event->logger->ctxt);
							break;
						case 'I':
							sprintf(&msgTxt[strlen(msgTxt)],"ident=");
						case 'i':
							sprintf(&msgTxt[strlen(msgTxt)],"%s ",event->logger->id);	
							break;
						default:
							break;
						}
						break;

//process
				case 'P':
				case 'p':
					switch(*p++)
					{
						case 'I':
							sprintf(&msgTxt[strlen(msgTxt)],"pid=");
 						case 'i':
							sprintf(&msgTxt[strlen(msgTxt)],"%d ",_getpid());
							break;
#ifndef WIN32
						case 'P':
							sprintf(&msgTxt[strlen(msgTxt)],"ppid=");
						case 'p':
							sprintf(&msgTxt[strlen(msgTxt)],"%d ",getppid());
							break;
						case 'G':
							sprintf(&msgTxt[strlen(msgTxt)],"gid=");
 						case 'g':
							sprintf(&msgTxt[strlen(msgTxt)],"%u ",getgid());
							break;
						case 'E':
							sprintf(&msgTxt[strlen(msgTxt)],"egid=");
 						case 'e':
							sprintf(&msgTxt[strlen(msgTxt)],"%u ",getegid());
							break;
						case 'U':
							sprintf(&msgTxt[strlen(msgTxt)],"uid=");
 						case 'u':
							sprintf(&msgTxt[strlen(msgTxt)],"%u ",getuid());
							break;
						case 'F':
							sprintf(&msgTxt[strlen(msgTxt)],"euid=");
						case 'f':
							sprintf(&msgTxt[strlen(msgTxt)],"%u ",geteuid());
							break;
						case 'R':
							sprintf(&msgTxt[strlen(msgTxt)],"pgrp=");
 						case 'r':
							sprintf(&msgTxt[strlen(msgTxt)],"%d ",getpgrp());
							break;
#endif
					}
					break;

//repository;
				case 'r':
				case 'R':
					switch(*p++)
					{
						case 'L':
							sprintf(&msgTxt[strlen(msgTxt)],"class/module=");
						case 'l':
							sprintf(&msgTxt[strlen(msgTxt)],"%s ",event->repository_l->id);
							break;
						case 'G':
							sprintf(&msgTxt[strlen(msgTxt)],"program=");
						case 'g':
							sprintf(&msgTxt[strlen(msgTxt)],"<%s> ",repository->id);
							break;
						default:
							break;
						}
						break;


//time and date
				case 't':
				case 'T':
					switch(*p++)
					{
						case 'A':
							sprintf(&msgTxt[strlen(msgTxt)],"time=");
						case 'a':
							ftime(&tb);
							sprintf(&msgTxt[strlen(msgTxt)],"%lu:%.3lu ",(unsigned long)tb.time,(unsigned long)tb.millitm);
							break;
						case 'R':
							sprintf(&msgTxt[strlen(msgTxt)],"timeOfDay=");
						case 'r':
							ftime(&tb);
							sprintf(&msgTxt[strlen(msgTxt)],"%lu:%.3lu ",(unsigned long)tb.time-repository->refTimeStart,(unsigned long)tb.millitm);
							break;
						case 'D':
							sprintf(&msgTxt[strlen(msgTxt)],"dateAndTime=");
						case 'd':
							time(&tt);
							t=ctime(&tt);
							*(t+strlen(t)-1)=0;
							sprintf(&msgTxt[strlen(msgTxt)],"<%s> ",t);
							break;
#ifndef WIN32					
						case 'T':
							sprintf(&msgTxt[strlen(msgTxt)],"timeOfDay=");
						case 't':
							gettimeofday(&tv,&tz);
							sprintf(&msgTxt[strlen(msgTxt)],"%ld:%.3ld ",(unsigned long)tv.tv_sec,(unsigned long)tv.tv_usec);
							break;
#endif		
						default:
							break;
					}
				  break;

//layout
				case 'Y':
					sprintf(&msgTxt[strlen(msgTxt)],"layout=");
 				case 'y':
					sprintf(&msgTxt[strlen(msgTxt)],"%s ",id);
					break;

				default:
					break;
			}
		}
	}

	msgTxt[strlen(msgTxt)]=0;

	return msgTxt;
}


/*****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__


