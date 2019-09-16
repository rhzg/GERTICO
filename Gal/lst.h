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
** File(s)      : lst.h
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
** Description  : 
**              :
******************************************************************************/

#ifndef __Lst__included__
#define __Lst__included__

#include "out.h"
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

template<class T>class Lst
{
	friend class Appender;
	friend class Layout;
	friend class Param;
	friend class Format;
	friend class Event;
	friend class Logger;
	friend class Repository;
	friend class Repository_l;
	friend class Adm;

//variables
	protected:

  private:
		unsigned int maxLength;
		unsigned int maxLengthIncrement;
		T **head;
		unsigned int length;

	public:

//functions
	protected:
		
	private:

	public:
		Lst(unsigned int maxLength);
		~Lst();
		void freeElm();

		void printRef(char *header);

		int add(T *p,int isNew);
		int remove(T *p);
		T *find(char *id);
    void makeRef();
    void makeRef(unsigned int refGallRepository);
		void setEnabled(int enabled);
		void findUnused(char *fn);
};

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/* lst                                                                      */
/*--------------------------------------------------------------------------*/

template<class T>Lst<T>::Lst(unsigned int maxLengthInit)
{
	char *fn="Lst:Lst";

	length=0;
	maxLength=maxLengthIncrement=maxLengthInit;
	if(maxLength)
	{
	  head=(T **)calloc(maxLength,sizeof(T *));
		if(!head)
			Out::abort(fn,"No memory");
	}
	else
		head=NULL;
}

/*--------------------------------------------------------------------------*/
/* ~lst                                                                     */
/*--------------------------------------------------------------------------*/

template<class T>Lst<T>::~Lst()
{
	if(head)
		free(head);
}

/*--------------------------------------------------------------------------*/
/* printRef                                                                 */
/*--------------------------------------------------------------------------*/

template<class T>void Lst<T>::printRef(char *header)
{
	unsigned int i;
	T **ll=head;
	T *l;
	char txt[GAL_TXT];

	sprintf(txt,"%s=%u",header,length);
	Out::ref(txt);

	for(i=0;i<length;i++,ll++)
	{
		l=*ll;
		sprintf(txt,"id=%s ref=%u/%u",l->id,l->refGallRepository,l->refGallIndex);

		Out::ref(txt);
	}
}

/*--------------------------------------------------------------------------*/
/* freeElm                                                                  */
/*--------------------------------------------------------------------------*/

template<class T>void Lst<T>::freeElm()
{
	unsigned int i;
	T **ll=head;

	for(i=0;i<length;i++,ll++)
	{
		if(*ll)
			delete(*ll);
	}
}

/*--------------------------------------------------------------------------*/
/* add                                                                      */
/*--------------------------------------------------------------------------*/

template<class T>int Lst<T>::add(T *t,int mode)
{
	char *fn="Lst::add";
	unsigned int i;
	char txt[100];
	T **ll=head;
	T **oldHead;
	T **llo;

	if(!t)
	{
		Out::error(fn,"Null pointer not allowed");
		return 1;
	}
	
	for(i=0;i<length;i++,ll++)
	{
		switch(mode)
		{
			case 0:
				if((*ll)==t)
				{
					Out::error(fn,"Element reference already in list");
					return 1;
				}
				break;
			case 1:
				if(!strcmp((*ll)->id,t->id))
				{
sprintf(txt,"Element id=%s is already defined",t->id);
					Out::error(fn,txt);
					return 1;
				}
				break;
			default:
				Out::error(fn,"mode undefined");
				return 1;
		}
	}

	if(length==maxLength)
	{
		oldHead=head;
		maxLength+=maxLengthIncrement;
		ll=head=(T **)calloc(maxLength,sizeof(T *));
		if(!head)
			Out::abort(fn,"No memory");

		if(oldHead)
		{
			llo=oldHead;
			for(i=0;i<length;i++)
				*ll++=*llo++;
			free(oldHead); 
		}
	}

	*(head+length)=t;
  length++;
	return 0;
}

/*--------------------------------------------------------------------------*/
/* remove                                                                   */
/*--------------------------------------------------------------------------*/

template<class T>int Lst<T>::remove(T *t)
{
	char *fn="Lst::remove";
	unsigned int i;
	T **ll=head;

	if(!t)
	{
		Out::error(fn,"Null pointer not allowed");
		return 1;
	}

	for(i=0;i<length;i++,ll++)
	{
		if(*ll==t)
		{
			length--;
			*ll=*(head+length);
			return 1;
		}
	}
	Out::error(fn,"Element not in list");
	return 0;
}

/*--------------------------------------------------------------------------*/
/* find                                                                     */
/*--------------------------------------------------------------------------*/

template<class T>T *Lst<T>::find(char *id)
{
	unsigned int i;
	T **ll=head;

	for(i=0;i<length;i++,ll++)
	{
		if(strcmp((*ll)->id,id)==0)
			return *ll;
	}
	return NULL;
}

/*--------------------------------------------------------------------------*/
/* makeRef                                                                  */
/*--------------------------------------------------------------------------*/

template<class T>void Lst<T>::makeRef()
{
	unsigned int i;
	T **ll=head;

	for(i=0;i<length;i++,ll++)
		(*ll)->refGallIndex=i+1;
}

template<class T>void Lst<T>::makeRef(unsigned int refGallRepository)
{
	unsigned int i;
	T **ll=head;

	for(i=0;i<length;i++,ll++)
	{
		(*ll)->refGallRepository=refGallRepository;
		(*ll)->refGallIndex=i+1;
	}
}

/*--------------------------------------------------------------------------*/
/* enable                                                                   */
/*--------------------------------------------------------------------------*/

template<class T>void Lst<T>::setEnabled(int enabled)
{
	unsigned int i;
	T **ll=head;

	for(i=0;i<length;i++,ll++)
		(*ll)->enabled=enabled;
}

/*--------------------------------------------------------------------------*/
/* findUnused                                                               */
/*--------------------------------------------------------------------------*/

template<class T>void Lst<T>::findUnused(char *fn)
{
	unsigned int i;
	T **ll=head;
	char txt[GAL_TXT];

	for(i=0;i<length;i++,ll++)
	{
		if(!(*ll)->used)
		{
			sprintf(txt,"%s unused",(*ll)->id);
			Out::warning(fn,txt);
		}
	}
}

/*****************************************************************************/

#endif
