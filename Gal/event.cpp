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
** File(s)      : event.cpp
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
** Description  : event
**              :
*****************************************************************************/

#define __THISCLASS__ Event
#define __CLASSNAME__ "Event"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "event.h"
#include "string.h"

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/

ACE_Thread_Mutex Event::pm;

/*--------------------------------------------------------------------------*/
/* event                                                                    */
/*--------------------------------------------------------------------------*/

Event::Event(class Repository_l *repository_l,char *id,int enable,enum GAL_LEVEL level,unsigned int group,char *ctxt,char *idLogger,char *idFormat)
{
  cnt=0;

  admEvent(id);

  this->repository_l=repository_l;
  this->enable=enable;
  this->level=level;
  this->group=group;

  strcpy(this->ctxt,ctxt);
  txt[0]=0;
  strcpy(this->idLogger,idLogger);
  strcpy(this->idFormat,idFormat);
  logger=NULL;
  format=NULL;

  enabled=false;
  triggerEnable=false;
}

Event::Event()
{
  enabled=false;
}

/*--------------------------------------------------------------------------*/
/* ~event                                                                   */
/*--------------------------------------------------------------------------*/

Event::~Event()
{
}

/*--------------------------------------------------------------------------*/
/* convertLevel                                                             */
/*--------------------------------------------------------------------------*/

enum GAL_LEVEL Event::convertLevel(char *slevel)
{
  enum GAL_LEVEL level;
  size_t len;

  len=strlen(slevel);
  if(len>1)
    throw "level string too long";

  switch(*slevel)
  {
    case 'E':
    case 'e':
      level=lERROR;
      break;
    case 'W':
    case 'w':
      level=lWARN;
      break;
    case 'I':
    case 'i':
      level=lINFO;
      break;
    case 'D':
    case 'd':
      level=lDEBUG;
      break;
    default:
      throw "undefined level";
  }

  return level;
}

char *Event::convertLevel(enum GAL_LEVEL level)
{
  switch(level)
  {
    case lERROR:
      return (char*)"ERROR";
    case lWARN:
      return (char*)"WARNING";
    case lINFO:
      return (char*)"INFO";
    case lDEBUG:
      return (char*)"DEBUG";
    default:
      return (char*)"?";
  }
}


/*--------------------------------------------------------------------------*/
/* p                                                                        */
/*--------------------------------------------------------------------------*/

size_t Event::getSize()
{
  size_t size=strlen(txt);
  if(size>GAL_CTXT_MAX)
    return (size_t)-1;
  else
    return size;
}

void Event::p()
{
  txt[0]=0;
}

void Event::p(unsigned int val)
{
  size_t size=getSize();
  if(size<0)
    return;
  sprintf(&txt[size], "%u",val);
}

void Event::p(int val)
{
  size_t size=getSize();
  if(size<0)
    return;
  sprintf(&txt[size]," %d",val);
}

void Event::p(unsigned long val)
{
  size_t size=getSize();
  if(size<0)
    return;
  sprintf(&txt[size]," %lu",val);
}

void Event::p(long val)
{
  size_t size=getSize();
  if(size<0)
    return;
  sprintf(&txt[size]," %ld",val);
}

void Event::p(char *val)
{
  size_t size=getSize();
  if(size<0)
    return;
  strcat(txt," ");
  strncat(txt,val,GAL_CTXT_MAX);
}

void Event::p(const char *val)
{
  size_t size=getSize();
  if(size<0)
    return;
  strcat(txt," ");
  strncat(txt,val,GAL_CTXT_MAX);
}

void Event::p(double val)
{
  size_t size=getSize();
  if(size<0)
    return;
  sprintf(&txt[size]," %g",val);
}

void Event::p(long double val)
{
  size_t size=getSize();
  if(size<0)
    return;
  sprintf(&txt[size]," %Lg",val);
}

void Event::p(char val)
{
  size_t size=getSize();
  if(size<0)
    return;
  sprintf(&txt[size]," %c",val);
}

void Event::p(void *val)
{
  size_t size=getSize();
  if(size<0)
    return;
  sprintf(&txt[size]," %#lx",(unsigned long)val);
}


/*--------------------------------------------------------------------------*/
/* out                                                                      */
/*--------------------------------------------------------------------------*/

// loggers are only enabled if at least one appender exists and this appender is enabled
    
void Event::out()
{
  cnt++;
  if(strlen(txt)>=(GAL_CTXT_MAX-2))
  {
    char *p=txt+GAL_CTXT_MAX-5;
    *p++='.';
    *p++='.';
    *p++='.';
    *p++=0;
  }
  logger->out(this);
}

/****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__

