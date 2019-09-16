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
** File(s)      : GalConv.h
** Component(s) : -
** Device(s)    : Windows NT, Visual C++
** Terminology  : -
**              :
** Definition   : 
** Author       : Reinhard Bähre, FhG-IITB
** Date         : 14.01.2003
**              :
** Version      : 1.1 Beta
** Date         :
** Status       : untested
**              :
** Description  : Gal converter
**              :
******************************************************************************/

#ifndef __GalConv__included__
#define __GalConv__included__

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#define LF 10
#define CR 13

#define GAL_STRING_LINE 512
#define GAL_FILE_NAME 128
#define GAL_ID 128
#define GAL_ID_MAX 1024
#define GAL_TXT 256

#define GAL_THROW_VARIABLE	0x00000001
#define GAL_RETURN_VARIABLE	0x00000002
#define GAL_COUT						0x00000010
#define GAL_CERR						0x00000020
#define GAL_LOCAL_LOGGER		0x00000100
#define GAL_GLOBAL_LOGGER		0x00000200
#define GAL_LOGGER_NAME			0x00000400

#define GAL_PATH "RES"
#define GAL_VERSION "1.1"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

enum GAL_CONV_STATE{LOOK_FKT_NAME,LOOK_BRACKET_OPEN,LOOK_BRACKET_CLOSE};
enum GAL_CONV_OBJECT{IGNORE,FKT_ENTER,FKT_LEAVE,FKT_RETURN,MSG_CERR,MSG_COUT,FKT_THROW};
enum GAL_CONV_MODE{UNKNOWN,CONVERT,CLEAN};

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

class GalConv
{

//variables
	protected:

	private:
		static class GalConv *singleInstance;

		char convFileName[GAL_FILE_NAME];
		unsigned long convOption;

		static FILE *fpProtMain;

		FILE *fpIn;
		FILE *fpOut;
		FILE *fpProt;
		FILE *fpRes;
		FILE *fpResH;
		FILE *fpInit;

		static char *tab;
		static char *tag;
		static char	*tagInit;

		unsigned int line;
		char stringLine[GAL_STRING_LINE];
		char stringLineWork[GAL_STRING_LINE];

		char idRepository[GAL_ID_MAX][GAL_ID];
		int idRepositoryLen;
		char lStd[GAL_ID];

	public:
		int cntProt;
		int cntRes;

//functions

	private:

		GalConv();
		~GalConv();
		
		FILE *openFile(char *fileName,char *mode);

		void readLine(int *eolReached);
		void writeLine(char *sLine);
		void writeLineEvent(char *sLine);

		enum GAL_CONV_OBJECT testRelevance(char **posArg);
		int testString(char *searchTxt,char **posArg);
		int testChar(char c);
		int cntBracket(int *warning);

		int lineContentsFktName(char *fktName,char *fktNameId);
		void extractIdentifier(char *fktName,char *fktNameId);
		void testExpandIdentifier(char *fktNameId);

		void outEnter(char *fktName,char *fktNameId);
		void outLeave(char *fktName,char *fktNameId);
		void outReturnThrow(enum GAL_CONV_OBJECT obj,int mode,char *fktName,char *fktNameId,unsigned int cnt,char *arg);
		void outCOUTorERR(enum GAL_CONV_OBJECT obj,char *fktName,char *fktNameId,unsigned int cnt,char *arg);
		int analyseArg(char *posAfter,char **arg);

		void outEvent(enum GAL_CONV_OBJECT obj,char *id,int nrArg,char *fktNameId,char *txt);

    void outHeadInitRepository();
		void outInitRepository(char *id);
		void outEndInitRepository();

		void outBegRes();
		void outRes(enum GAL_CONV_OBJECT obj,char *id,int nrArg,char *fktName,char *txt);

		void outFinalConv();
		void outFinalRes();

		void outProt(char *msg);

		int isTxtInserted(char *txt);

	protected:

	public:
		static class GalConv *getSingleInstance();

		unsigned int getLineNumber();

		void init(char *convFileName,enum GAL_CONV_MODE convMode,unsigned long convOption,char *lStd);
		void clean();
		void convert();
		void terminate();

		void outProtMain(char *msg);
};

#endif
