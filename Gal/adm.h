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
** File(s)      : adm.h
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

#ifndef __Adm__included__
#define __Adm__included__

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#include "global.h"

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

class Adm
{

//variables
	protected:
		
	private:

	public:
		int local;
		int enable;
		int used;
		char id[GAL_NAME];
		unsigned int refGallIndex;
		unsigned int refGallRepository;

//functions
	protected:

		Adm();
		~Adm();

		void admEvent(char *id);
		void admParamFormatLogger(int local,char *id);
		void admAppenderLayout(char *id);
		void admRepository_l();

	private:

	public:

};

/****************************************************************************/

#endif
