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
** File(s)      : in.h
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

#ifndef __In__included__
#define __In__included__


/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#define LF 10
#define CR 13

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

class In
{

//variables
	protected:

	private:
	public:
		unsigned int line;
		char stringLine[GAL_STRING_LINE];
		FILE *fp;
	
		char version[GAL_VERSION];

//functions

	private:

	protected:
		In();
		~In();
		
		void readLine(); 
    int readTxt(char *searchedTxtId,char *searchedTxtCont);
		void fillVersion() throw (const char*);


	public:

};

/****************************************************************************/

#endif
