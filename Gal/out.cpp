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
** File(s)      : out.cpp
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
** Description  : out
**              :
*****************************************************************************/

#define __THISCLASS__ Out
#define __CLASSNAME__ "Out"

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "StdAfx.h"

#include "out.h"
#include "appender.h"

/*****************************************************************************
****  METHODS / FUNCTIONS                                                 ****
*****************************************************************************/

class Out *Out::singleInstance=NULL;
FILE *Out::fpGall=NULL;
FILE *Out::fpGallRef=NULL;
unsigned int Out::cntError=0;
unsigned int Out::cntWarning=0;
unsigned int Out::cntInfo=0;
unsigned int Out::cntEvent=0;

/*--------------------------------------------------------------------------*/
/* out                                                                      */
/*--------------------------------------------------------------------------*/

Out::Out()
{
	if(fpGall)
		fclose(fpGall);
	if(fpGallRef)
		fclose(fpGallRef);
}

/*--------------------------------------------------------------------------*/
/* ~out                                                                     */
/*--------------------------------------------------------------------------*/

Out::~Out()
{
	if(fpGall)
		fclose(fpGall);
//	printf("\nErrors: %u Warnings: %u Infos: %u Events: %u\n\n",
//		cntError,cntWarning,cntInfo,cntEvent);
}

/*--------------------------------------------------------------------------*/
/* getSingleInstance                                                        */
/*--------------------------------------------------------------------------*/

class Out *Out::getSingleInstance()
{
	if(!singleInstance)
	{
		singleInstance=new Out();
		fpGall=fopen("gal.prot.out","w");
		fpGallRef=fopen("gal.ref.out","w");
	}
	return singleInstance;
}

/*--------------------------------------------------------------------------*/
/* closeRefOut                                                              */
/*--------------------------------------------------------------------------*/

void Out::closeRefOut()
{
	if(fpGallRef)
	{
		fclose(fpGallRef);
		fpGallRef=NULL;
	}
}

/*--------------------------------------------------------------------------*/
/* setProtOut                                                               */
/*--------------------------------------------------------------------------*/

char *Out::setProtOut(enum GAL_APPENDER aProt)
{
	static int initialized=0;
	FILE *fp;
	char c;

	if(initialized)
		return "Out is initialized";
	initialized=1;

	if(!fpGall)
		return "Could not open gal.prot.out in the past";

	if(aProt==aFILE)
	{
		fclose(fpGall),
		fpGall=fopen("gal.prot.out","a");
		if(fpGall)
			return NULL;
		else
			return "Cannot open file gal.prot.out";
	}

	fclose(fpGall);
	fpGall=NULL;

	fp=fopen("gal.prot.out","r");
	if(!fp)
		return "Cannot open file gal.prot.out";

  c=(char)getc(fp);
	while(c!=EOF)
	{
		printf("%c",c);
	  c=(char)getc(fp);
	}

	fclose(fp);

	return NULL;
}

/*--------------------------------------------------------------------------*/
/* abort                                                                    */
/*--------------------------------------------------------------------------*/

void Out::abort(char *fn,char *txt)
{
	cntError++;
	if(!fpGall)
		printf("Error: %s: %s\n",fn,txt);
	else
		fprintf(fpGall,"Error: %s: %s\n",fn,txt);

	printf("%c",7);
	exit(1);
}

/*--------------------------------------------------------------------------*/
/* error                                                                    */
/*--------------------------------------------------------------------------*/

void Out::error(char *fn,char *txt)
{
	cntError++;
	if(!fpGall)
		printf("Error: %s: %s\n",fn,txt);
	else
		fprintf(fpGall,"Error in function %s: %s\n",fn,txt);

	printf("%c",7);
}

/*--------------------------------------------------------------------------*/
/* warning                                                                  */
/*--------------------------------------------------------------------------*/

void Out::warning(char *fn,char *txt)
{
	cntWarning++;
	if(!fpGall)
		printf("Warning: %s: %s\n",fn,txt);
	else
		fprintf(fpGall,"Warning: %s: %s\n",fn,txt);
}

/*--------------------------------------------------------------------------*/
/* info                                                                     */
/*--------------------------------------------------------------------------*/

void Out::info(char *fn,char *txt)
{
	cntInfo++;
	if(!fpGall)
		printf("Info: %s: %s\n",fn,txt);
	else
		fprintf(fpGall,"Info fn=%s: %s\n",fn,txt);
}

/*--------------------------------------------------------------------------*/
/* stat                                                                     */
/*--------------------------------------------------------------------------*/

void Out::stat(char *txt)
{
	if(fpGall)
		fprintf(fpGall,"%s\n",txt);
	else
		printf("%s\n",txt);
}

/*--------------------------------------------------------------------------*/
/* ref                                                                      */
/*--------------------------------------------------------------------------*/

void Out::ref(char *txt)
{
	if(fpGallRef)
		fprintf(fpGallRef,"%s\n",txt);
	else
		printf("%s\n",txt);
}

/*--------------------------------------------------------------------------*/
/* openDevice                                                               */
/*--------------------------------------------------------------------------*/

FILE *Out::openDevice(char *name)
{
	FILE *fp;
	char outFile[GAL_FILENAME];

	strcpy(outFile,name);
	if(*name)
		strcat(outFile,".");
	strcat(outFile,"gal.log.out");
	fp=fopen(outFile,"w");

	return fp;
}

/*--------------------------------------------------------------------------*/
/* closeDevice                                                              */
/*--------------------------------------------------------------------------*/

void Out::closeDevice(FILE *fp)
{
	if(fp)
		fclose(fp);
}

/*--------------------------------------------------------------------------*/
/* event                                                                    */
/*--------------------------------------------------------------------------*/

void Out::event(char *txt)
{
	cntEvent++;
	printf("%s\n",txt);
}

void Out::event(FILE *fp,char *txt)
{
	cntEvent++;
	fprintf(fp,"%s\n",txt);
}

/*****************************************************************************/

#undef __THISCLASS__
#undef __CLASSNAME__
