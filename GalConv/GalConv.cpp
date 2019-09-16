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
** File(s)      : GalConv.cpp
** Component(s) : -
** Device(s)    : Windows NT, Visual C++
** Terminology  : -
**              :
** Definition   : 
** Author       : Reinhard Bähre, FhG-IITB
** Date         : 14.01.2003
**              :
** Version      : 1.2 Beta
** Date         :
** Status       : untested
**              :
** Description  : Gal converter
**
** 1.2 leave event at the end in void function with return
**              :
*****************************************************************************/

/*****************************************************************************
****  INCLUDE FILES AND CONSTANT DEFINITIONS                              ****
*****************************************************************************/

#include "GalConv.h"

/*--------------------------------------------------------------------------*/
/* main                                                                     */
/*--------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
	char convFileName[GAL_FILE_NAME];
	char lStd[GAL_ID];
	char h[GAL_TXT];
	enum GAL_CONV_MODE convMode=UNKNOWN;
	unsigned long convOption=0;
	unsigned long optionH;
	class GalConv *galConv;
	char *argp;
	int expectLoggerName=0;
	int expectOption=0;
	static char *help="Gal [-help] [[-lL][-lG][-lLN LoggerName][-lGN LoggerName]] [-convert FileNames] [-clean FileNames]";

	int i;

	if(argc==1)
	{
		printf("Abort: Arguments missed\n");
		printf("%s\n",help);
		exit(1);
	}

  galConv=GalConv::getSingleInstance();

//	convOption|=GAL_COUT;
//	convOption|=GAL_CERR;
//	convOption|=GAL_RETURN_VARIABLE;
//	convOption|=GAL_THROW_VARIABLE;

	sprintf(lStd,"l%s","Std");	// name of standard debug logger

	for(i=1;i<argc;i++)
	{
		argp=argv[i];

		if(*argp=='-')
		{
			expectLoggerName=0;
			for(;;)
			{
				argp++;
				if(*argp=='c')
				{
					if(strcmp(argp,"convert")==0)
					{
						convMode=CONVERT;
						break;
					}
					if(strcmp(argp,"clean")==0)
					{
						convMode=CLEAN;
						break;
					}
				}
				if(*argp=='l')
				{
					convOption&=0xfffff0ff;
					if(strcmp(argp,"lL")==0)
					{
						convOption|=GAL_LOCAL_LOGGER;
						break;
					}
					if(strcmp(argp,"lG")==0)
					{
						convOption|=GAL_GLOBAL_LOGGER;
						break;
					}
					if(strcmp(argp,"lLN")==0)
					{
						convOption|=(GAL_LOCAL_LOGGER|GAL_LOGGER_NAME);
						expectLoggerName=1;
						break;
					}
					if(strcmp(argp,"lGN")==0)
					{
						convOption|=(GAL_GLOBAL_LOGGER|GAL_LOGGER_NAME);
						expectLoggerName=1;
						break;
					}
				}
				if(*argp=='o')
				{
					expectOption=1;
					break;
				}
				if(*argp=='h')
				{
					printf("\n%s\n",help);
					printf("%s","-lL  logger is defined local.  Name = lFileName, default name = lStd\n");
					printf("%s","-lLN logger is defined local.  Name = lLoggerName\n");
					printf("%s","-lG  logger is defined global. Name = lFileName\n");
					printf("%s","-lGN logger is defined global. Name = lLoggerName\n");
					printf("%s","-convert Gal instruments   FileName.cpp.  Result is FileName.conv\n");
					printf("%s\n","-clean   Gal deinstruments FileName.conv. Result is FileName.rconv\n");
					exit(0);
				}

				printf("Abort: Argument error\n");
				printf("%s\n",help);
				exit(1);
			}
			continue;
		}

		if(expectLoggerName)
		{
			sprintf(lStd,"l%s",argp);
			expectLoggerName=0;
			continue;
		}

		if(expectOption)
		{
			sscanf(argp,"%lx",&optionH);
			convOption&=0xffffff00;
			convOption|=(0x000000ff&optionH);
			expectOption=0;
			continue;
		}

		if(convMode==UNKNOWN)
		{
			printf("Abort: Don't know what to do\n");
			printf("GalConv <-lL> <-lLN> <-lG> <-lGN> <-clean> <-convert> <FileName>\n");
			exit(1);
		}

		strcpy(convFileName,argp);
		sprintf(h,"%s file %s",(convMode==CLEAN)?"clean (.conv -> .rconv)":"convert (.cpp -> .conv)",convFileName);
		galConv->outProtMain(h);

		try
		{
			galConv->init(convFileName,convMode,convOption,lStd);
			if(convMode==CLEAN)
				galConv->clean();
			else
				galConv->convert();
		}
		catch(char *t)
		{
			sprintf(h,"  Error in line %u. Reason: %s",galConv->getLineNumber(),t);
			galConv->outProtMain(h);
		}
		catch(const char *t)
		{
			sprintf(h,"  Error in line %u. Reason: %s",galConv->getLineNumber(),t);
			galConv->outProtMain(h);
		}

		if(galConv->cntProt)
		{
			sprintf(h,"  Warnings: %d",galConv->cntProt);
			galConv->outProtMain(h);
		}

		galConv->terminate();
	}

	return 0;
}

class GalConv *GalConv::singleInstance=NULL;
FILE *GalConv::fpProtMain=NULL;
char *GalConv::tab="                           ";
char *GalConv::tag="   // inserted by Gal converter";
char *GalConv::tagInit="insert Gal file .init here";

/*--------------------------------------------------------------------------*/
/* GalConv                                                                  */
/*--------------------------------------------------------------------------*/

GalConv::GalConv()
{
}

/*--------------------------------------------------------------------------*/
/* ~GalConv                                                                 */
/*--------------------------------------------------------------------------*/

GalConv::~GalConv()
{
}

/*--------------------------------------------------------------------------*/
/* getSingleInstance                                                        */
/*--------------------------------------------------------------------------*/

class GalConv *GalConv::getSingleInstance()
{
	if(!singleInstance)
	{
		singleInstance=new GalConv();
		fpProtMain=fopen("GalConv.prot","w");
	}

	return singleInstance;
};

/*--------------------------------------------------------------------------*/
/* getLineNumber                                                            */
/*--------------------------------------------------------------------------*/

unsigned int GalConv::getLineNumber()
{
	return line;
}

/*--------------------------------------------------------------------------*/
/* init                                                                     */
/*--------------------------------------------------------------------------*/

void GalConv::init(char *convFileName,enum GAL_CONV_MODE convMode,unsigned long convOption,char *lStd)
{
	char fileName[GAL_FILE_NAME];
	static char txt[GAL_TXT];

	strcpy(this->convFileName,convFileName);
	this->convOption=convOption;
	strcpy(this->lStd,lStd);

	line=0;
	cntProt=cntRes=0;
	idRepositoryLen=0;

	fpIn=fpOut=fpProt=fpInit=fpRes=fpResH=NULL;

	try
	{
		if(convMode==CONVERT)
		{
			sprintf(fileName,"%s.cpp",convFileName);
			fpIn=openFile(fileName,"r");

			sprintf(fileName,"%s.conv","tmp");
			fpOut=openFile(fileName,"w");

			sprintf(fileName,"%s.res",convFileName);
			fpRes=openFile(fileName,"w");

			sprintf(fileName,"%s.res","tmp");
			fpResH=openFile(fileName,"w");

			sprintf(fileName,"%s.init",convFileName);
			fpInit=openFile(fileName,"w");
		}
		else
		{
			sprintf(fileName,"%s.conv",convFileName);
			fpIn=openFile(fileName,"r");

			sprintf(fileName,"%s.rconv",convFileName);
			fpOut=openFile(fileName,"w");
		}

		sprintf(fileName,"%s.prot",convFileName);
		fpProt=openFile(fileName,"w");
		
	}
	catch(char *t)
	{
		sprintf(txt,"init: %s",t);
		throw txt;
	}

	return;
}


/*--------------------------------------------------------------------------*/
/* openFile                                                                 */
/*--------------------------------------------------------------------------*/

FILE *GalConv::openFile(char *fileName,char *mode)
{
	FILE *fp;
	static char fName[GAL_FILE_NAME];
	static char txt[GAL_TXT];

#ifdef WIN32
	sprintf(fName,"%s\\%s",GAL_PATH,fileName);
#else
	sprintf(fName,"%s/%s",GAL_PATH,fileName);
#endif

	fp=fopen(fName,mode);
	if(fp==0)
	{
		sprintf(txt,"Can't open file %s for %s",fileName,mode);
		throw txt;
	}
	return fp;
}

/*--------------------------------------------------------------------------*/
/* clean                                                                    */
/*--------------------------------------------------------------------------*/

void GalConv::clean()
{
	int eolReached=0;

	while(eolReached==0)
	{
		readLine(&eolReached);
		if(!isTxtInserted(tag))
			writeLine(stringLine);
	}
}

/*--------------------------------------------------------------------------*/
/* isTxtInserted                                                            */
/*--------------------------------------------------------------------------*/

int GalConv::isTxtInserted(char *txt)
{
	static int len=strlen(txt);
  char *p=stringLineWork;

	while(*p!=0)
	{
		if(strncmp(p,txt,len)==0)
			return 1;
		p++;
	}
	return 0;
}

/*--------------------------------------------------------------------------*/
/* convert                                                                  */
/*--------------------------------------------------------------------------*/

void GalConv::convert()
{
	char *arg;
	char *posAfter;
	int eolReached=0;
	int mode;
	enum GAL_CONV_OBJECT rc;
	char fktName[GAL_ID];
	char fktNameId[GAL_ID];
	int lineLevelBracket;
	unsigned int cntReturn;
	unsigned int cntThrow;
	unsigned int cntMsg;
	int levelBracket=0;
	int warning;
	enum GAL_CONV_STATE state=LOOK_FKT_NAME;
	int validFktName=0;
	int lastWasReturn=0;

	cntThrow=0;
	cntReturn=0;
	cntMsg=0;

	strcpy(fktName,"GAL");
	strcpy(fktNameId,"GAL");

	outHeadInitRepository();
	outBegRes();

	while(eolReached==0)
	{
		readLine(&eolReached);
		lineLevelBracket=cntBracket(&warning);
		levelBracket+=lineLevelBracket;

		switch(state)
		{
		case LOOK_FKT_NAME:
		case LOOK_BRACKET_OPEN:
			if(lineContentsFktName(fktName,fktNameId))
			{
				if(lineLevelBracket==0)
				{
					state=LOOK_BRACKET_OPEN;
					validFktName=1;
					break;
				}
			}
			if(levelBracket==1)
			{
				cntThrow=0;
				cntReturn=0;
				cntMsg=0;
				if(!validFktName)
					outProt("Bracket ( problem before?");
				if(warning)
					outProt("Bracket { problem?");
				writeLine(stringLine);
				outEnter(fktName,fktNameId);
				state=LOOK_BRACKET_CLOSE;
				continue;
			}
			break;
		case LOOK_BRACKET_CLOSE:
			rc=testRelevance(&posAfter);
			if(rc!=IGNORE)
			{
				lastWasReturn=0;
				mode=analyseArg(posAfter,&arg);
				if(mode==0)
					continue;
				switch(rc)
				{
					case FKT_THROW:
						outReturnThrow(FKT_THROW,mode,fktName,fktNameId,cntThrow,arg);
						cntThrow++;
						continue;
					case FKT_RETURN:	
						lastWasReturn=1;
						outReturnThrow(FKT_RETURN,mode,fktName,fktNameId,cntReturn,arg);
						cntReturn++;
						continue;
					case MSG_COUT:
					case MSG_CERR:
						outCOUTorERR(rc,fktName,fktNameId,cntMsg,arg);
						cntMsg++;
						continue;
				}
			}

			if(levelBracket==0)
			{
				if(warning)
					outProt("Bracket } problem?");
				if(!lastWasReturn)
					outLeave(fktName,fktNameId);
				state=LOOK_FKT_NAME;
				validFktName=0;
			}
			else
				lastWasReturn=0;
			break;
		default:
			break;
		}

		writeLine(stringLine);
	}

	outEndInitRepository();

	outFinalConv();
	outFinalRes();
}

/*--------------------------------------------------------------------------*/
/* terminate                                                                */
/*--------------------------------------------------------------------------*/

void GalConv::terminate()
{
	if(fpIn)
		fclose(fpIn);
	
	if(fpOut)
		fclose(fpOut);

	if(fpRes)
		fclose(fpRes);

	if(fpResH)
		fclose(fpResH);

	if(fpProt)
		fclose(fpProt);

	if(fpInit)
		fclose(fpInit);
}

/*--------------------------------------------------------------------------*/
/* readLine                                                                 */
/*--------------------------------------------------------------------------*/

void GalConv::readLine(int *eolReached)
{
	int i;
	int c;
	char *p=stringLine;

	line++;

	*p=0;
	for(i=0;i<(GAL_STRING_LINE-1);i++)
	{
		c=getc(fpIn);
		if(c==EOF)
		{
			*p=0;
			*eolReached=1;
			strcpy(stringLineWork,stringLine);
			return;
		}
		if(c==LF)
		{
			*p=0;
			strcpy(stringLineWork,stringLine);
			return;
		}
		*p++=(char)c;
	}
	*p=0;
	throw "line too long";
}

/*--------------------------------------------------------------------------*/
/* writeLine                                                                */
/*--------------------------------------------------------------------------*/

void GalConv::writeLine(char *sLine)
{
	fprintf(fpOut,"%s\n",sLine);
}

/*--------------------------------------------------------------------------*/
/* writeLineEvent                                                           */
/*--------------------------------------------------------------------------*/

void GalConv::writeLineEvent(char *sLine)
{
	char h[GAL_STRING_LINE];

	sprintf(h,"%s#ifdef GalDebug%s",tab,tag);
	writeLine(h);
	writeLine(sLine);
	sprintf(h,"%s#endif%s",tab,tag);
	writeLine(h);
}

/*--------------------------------------------------------------------------*/
/* testRelevanve                                                            */
/*--------------------------------------------------------------------------*/

enum GAL_CONV_OBJECT GalConv::testRelevance(char **posArg)
{
	if(testString("throw",posArg))
		return FKT_THROW;	

	if(testString("return",posArg))
		return FKT_RETURN;

	if(convOption&GAL_COUT)
	{
		if(testString("cout",posArg))
			return MSG_COUT;
	}

	if(convOption&GAL_CERR)
	{
		if(testString("cerr",posArg))
			return MSG_CERR;
	}

	return IGNORE;	
}

/*--------------------------------------------------------------------------*/
/* testString                                                               */
/*--------------------------------------------------------------------------*/

int GalConv::testString(char *searchTxt,char **posArg)
{
	int found=0;
	int lenST=strlen(searchTxt);
  char *p=stringLineWork;
	char h[GAL_TXT];
	char *pArg;

	while(*p!=0)
	{
		if(strncmp(p,searchTxt,lenST)==0)
		{
			pArg=p+lenST;
			if(!testChar(*pArg))
			{
				if(p==stringLineWork)
				{
					found=1;
					break;
				}
//				if(!testChar(*(p-1)))
				if(*(p-1)==' ')
				{
					found=1;
					break;
				}
			}
		}
		p++;
	}

	if(!found)
		return 0;

	*posArg=pArg;

	if(p!=stringLineWork)
	{
		do{
			p--;
			if(testChar(*p))
			{
				sprintf(h,"relevant code before key word <%s> ?",searchTxt);
				outProt(h);
				return 2;
			}
		}
		while(p!=stringLineWork);
	}

	return 1;
}

/*--------------------------------------------------------------------------*/
/* testChar                                                                 */
/*--------------------------------------------------------------------------*/

int GalConv::testChar(char c)
{
	return (isalnum(c)||(c=='_')||(c=='"')||(c=='/'))?1:0;
}

/*--------------------------------------------------------------------------*/
/* cntBracket                                                               */
/*--------------------------------------------------------------------------*/

int GalConv::cntBracket(int *warning)
{
  char *p=stringLineWork;
	int warn=0;
	int cnt=0;

	while(*p!=0)
	{
		switch(*p++)
		{
		case '{':
			cnt++;
			break;
		case '}':
			cnt--;
			break;
		case ' ':
			break;
		default:
			warn=1;
			break;
		}
	}

	*warning=warn;
	return cnt;
}

/*--------------------------------------------------------------------------*/
/* lineContentsFktName                                                      */
/*--------------------------------------------------------------------------*/

int GalConv::lineContentsFktName(char *fktName,char *fktNameId)
{
  char *p=stringLineWork;
	char *pBeg=NULL;
	char *pEnd=NULL;

	while(*p!=0)
	{
		if(pBeg)
		{
			if(*p=='(')
				pEnd=p;
		}
		if(*p==':')
			pBeg=p+1;
		if(pBeg&&pEnd)
			break;
		p++;
	}

	if((!pBeg)||(!pEnd))
		return 0;

	*pEnd=0;
	
	p=pEnd-1;
	while((*p==' ')&&(p!=pBeg))
	{
		*p=0;
		pEnd--;
		p--;
	}

	p=pBeg;
	while(((*p==' ')||(*p=='~'))&&(p!=pEnd))
	{
		p++;
		pBeg=p;
	}

	strcpy(fktName,pBeg);
	extractIdentifier(fktName,fktNameId);
	
	return 1;
}

/*--------------------------------------------------------------------------*/
/* extractIdentifier                                                        */
/*--------------------------------------------------------------------------*/

void GalConv::extractIdentifier(char *fktName,char *fktNameId)
{
	char *s=fktName;
	char *d=fktNameId;
	char c;
	int flag=0;

	c=*s++;
	*d++=c;
	while(c=*s++)
	{
		if(c=='_')
		{
			flag=1;
			continue;
		}
		if(flag)
		{
			*d++=c;
			flag=0;
			continue;
		}
		if(isupper(c)||isdigit(c))
			*d++=c;
	}
	*d=0;

	testExpandIdentifier(fktNameId);
}

/*--------------------------------------------------------------------------*/
/* testExpandIdentifier                                                     */
/*--------------------------------------------------------------------------*/

void GalConv::testExpandIdentifier(char *fktNameId)
{
	char fktNameIdExp[GAL_ID];
	int i;
	int found=1;
	int expand=0;

	strcpy(fktNameIdExp,fktNameId);
	while(found)
	{
		found=0;
		for(i=0;i<idRepositoryLen;i++)
		{
			if(strcmp(fktNameIdExp,&idRepository[i][0])==0)
			{
				found=1;
				break;
			}
		}
		if(found)
		{
			expand++;
			sprintf(fktNameIdExp,"%s_%d",fktNameId,expand);
		}
	}
	
	if(expand)
		strcpy(fktNameId,fktNameIdExp); 
	strcpy(&idRepository[idRepositoryLen][0],fktNameId);
	idRepositoryLen++;
}

/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* outEnter                                                                 */
/*--------------------------------------------------------------------------*/

void GalConv::outEnter(char *fktName,char *fktNameId)
{
	char sLine[GAL_STRING_LINE];
	char id[GAL_ID];

	sprintf(id,"%s_e",fktNameId);
	sprintf(sLine,"  %sE0(%s);%s",tab,id,tag);
	writeLineEvent(sLine);

	outEvent(FKT_ENTER,id,0,fktName,"enter");
}

/*--------------------------------------------------------------------------*/
/* outLeave                                                                 */
/*--------------------------------------------------------------------------*/

void GalConv::outLeave(char *fktName,char *fktNameId)
{
	char sLine[GAL_STRING_LINE];
	char id[GAL_ID];

	sprintf(id,"%s_l",fktNameId);
	sprintf(sLine,"  %sE0(%s);%s",tab,id,tag);
	writeLineEvent(sLine);

	outEvent(FKT_LEAVE,id,0,fktName,"leave");
}

/*--------------------------------------------------------------------------*/
/* outReturnThrow                                                           */
/*--------------------------------------------------------------------------*/

void GalConv::outReturnThrow(enum GAL_CONV_OBJECT obj,int mode,char *fktName,char *fktNameId,unsigned int cnt,char *arg)
{
	char sLine[GAL_STRING_LINE];
	char id[GAL_ID];
	char txt[GAL_TXT];
	int modeVar;
	int nrArg=0;

	if(obj==FKT_THROW)
	{
		sprintf(txt,"throw %s",arg);
		modeVar=convOption&GAL_THROW_VARIABLE;
		sprintf(id,"%s_t%u",fktNameId,cnt);
	}
	else
	{
		sprintf(txt,"leave");
		modeVar=convOption&GAL_RETURN_VARIABLE;
		sprintf(id,"%s_l%u",fktNameId,cnt);
	}

	switch(mode)
	{
// text
		case 1:
			nrArg=0;
			break;
// function
		case 2:
			nrArg=0;
			break;
// variable
		case 3:
			nrArg=modeVar?1:0;
			break;
		default:
			outProt("unknown mode");
			return;
	}

	sprintf(sLine,"%s%c%s",tab,'{',tag);
	writeLine(sLine);
	
	if(nrArg)
		sprintf(sLine,"  %sE1(%s,%s);%s",tab,id,arg,tag);
	else
		sprintf(sLine,"  %sE0(%s);%s",tab,id,tag);

	writeLineEvent(sLine);
	writeLine(stringLine);

	sprintf(sLine,"%s%c%s",tab,'}',tag);
	writeLine(sLine);

	outEvent(obj,id,nrArg,fktName,txt);

	return;
}

/*--------------------------------------------------------------------------*/
/* outCOUTorERR                                                             */
/*--------------------------------------------------------------------------*/

void GalConv::outCOUTorERR(enum GAL_CONV_OBJECT obj,char *fktName,char *fktNameId,unsigned int cnt,char *arg)
{
	char sLine[GAL_STRING_LINE];
	char id[GAL_ID];
	char txt[GAL_TXT];

	sprintf(txt,"%s",(obj==MSG_COUT)?"info message":"error message");
	sprintf(id,"%s_m%u",fktNameId,cnt);

	sprintf(sLine,"%s%c%s",tab,'{',tag);
	writeLine(sLine);

	sprintf(sLine,"  %sE1mBegin(%s){GalOs %s;E1mEnd(%s,GalOs.str());}%s",tab,id,arg,id,tag);
	writeLineEvent(sLine);

	sprintf(sLine,"%s%c%s",tab,'}',tag);
	writeLine(sLine);

	outEvent(obj,id,1,fktName,txt);

	return;
}

/*--------------------------------------------------------------------------*/
/* analyseArg                                                               */
/*--------------------------------------------------------------------------*/

int GalConv::analyseArg(char *posAfter,char **arg)
{
  char *p=posAfter;
	char *q;
	int ret;

	while(*p==' ')
		p++;

	ret=0;
	q=p;
	for(;*q!=0;q++)
	{
		if(*q==';')
		{
			*q=0;
			ret=1;
			break;
		}
	}

	if(ret==0)
	{
		outProt("can't process key word");
		return 0;
	}

	if(*p=='"')
	{
    p++;
		while(*p==' ')
			p++;
		q=p+strlen(p)-1;

		while((*q==' ')||(*q=='"'))
		{
			*q=0;
			q--;
		}	
		ret=1;
	}
	else
	{
		ret=3;
		q=p;
		for(;*q!=0;q++)
		{
			if(*q=='(')
			{
				ret=2;
				break;
			}
		}
	}

	*arg=p;
	return ret;
}


/************************** Repository (cpp) ********************************/

/*--------------------------------------------------------------------------*/
/* outEvent                                                                 */
/*--------------------------------------------------------------------------*/

void GalConv::outEvent(enum GAL_CONV_OBJECT obj,char *id,int nrArg,char *fktName,char *txt)
{
	outInitRepository(id);
	outRes(obj,id,nrArg,fktName,txt);
}

/*--------------------------------------------------------------------------*/
/* outBegInitRepository                                                     */
/*--------------------------------------------------------------------------*/

void GalConv::outHeadInitRepository()
{
	time_t tt;
	char *t;
	char h[GAL_STRING_LINE];

	sprintf(h,"%s","/********************************* Gal begin *********************************/");
	fprintf(fpInit,"%s%s\n",h,tag);

	fprintf(fpInit,"%s\n",tag);
	sprintf(h,"// Version: %s",GAL_VERSION);
	fprintf(fpInit,"%s%s\n",h,tag);
	time(&tt);
	t=ctime(&tt);
	*(t+strlen(t)-1)=0;
	sprintf(h,"// Date/Time: %s",t);
	fprintf(fpInit,"%s%s\n",h,tag);
	
	fprintf(fpInit,"%s\n",tag);
	sprintf(h,"%s","#ifdef GalDebug");
	fprintf(fpInit,"%s%s\n",h,tag);
	sprintf(h,"#include %cStdAfx.h%c",'"','"');
	fprintf(fpInit,"%s%s\n",h,tag);
	sprintf(h,"#include %crepository_l.h%c",'"','"');
	fprintf(fpInit,"%s%s\n",h,tag);
	sprintf(h,"#include %cevent.h%c",'"','"');
	fprintf(fpInit,"%s%s\n",h,tag);
	sprintf(h,"#include <strstream.h>");
	fprintf(fpInit,"%s%s\n",h,tag);

	fprintf(fpInit,"%s\n",tag);
	sprintf(h,"static char GalBuffer[256];");
	fprintf(fpInit,"%s%s\n",h,tag);
	sprintf(h,"static class ostrstream GalOs(GalBuffer,256);");
	fprintf(fpInit,"%s%s\n",h,tag);

// GalOs << xyz;  instead of cout or cerr following E1(a,os.str());

	fprintf(fpInit,"%s\n",tag);
	sprintf(h,"static class Repository_l *rpGal=new Repository_l(Repository::getSingleInstance(),%c%s.res%c);",'"',convFileName,'"');
	fprintf(fpInit,"%s%s\n",h,tag);
	fprintf(fpInit,"%s\n",tag);
}

/*--------------------------------------------------------------------------*/
/* outInitRepository                                                        */
/*--------------------------------------------------------------------------*/

void GalConv::outInitRepository(char *id)
{
	char h[GAL_STRING_LINE];

	sprintf(h,"static class Event *%s=rpGal->getRefEvent(%c%s%c);",id,'"',id,'"');
	fprintf(fpInit,"%s%s\n",h,tag);
}

/*--------------------------------------------------------------------------*/
/* outEndInitRepository                                                     */
/*--------------------------------------------------------------------------*/

void GalConv::outEndInitRepository()
{
	char h[GAL_STRING_LINE];

	fprintf(fpInit,"%s\n",tag);
	sprintf(h,"%s","#endif");
	fprintf(fpInit,"%s%s\n",h,tag);
	fprintf(fpInit,"%s\n",tag);
	sprintf(h,"%s","/*********************************** Gal end *********************************/");
	fprintf(fpInit,"%s%s\n",h,tag);
}

/************************** Repository (res) ********************************/

/*--------------------------------------------------------------------------*/
/* outBegRes                                                                */
/*--------------------------------------------------------------------------*/

void GalConv::outBegRes()
{
	fprintf(fpRes,"version=1.0\n");
	fprintf(fpRes,"id=%s\n",convFileName);

	if(convOption&(GAL_LOCAL_LOGGER|GAL_GLOBAL_LOGGER))
	{
		if(!(convOption&GAL_LOGGER_NAME))
			sprintf(lStd,"l%s",convFileName);
	}	

	if(convOption&GAL_GLOBAL_LOGGER)
		fprintf(fpRes,"nrLogger=0\n");
	else
	{
		fprintf(fpRes,"nrLogger=1\n");
		fprintf(fpRes,"id=%s enable=0 level=D group=ff ctxt=%c%s Standard Debug Logger%c\n",lStd,'"',convFileName,'"');
	}

	if(convOption&(GAL_COUT|GAL_CERR))
	{
		fprintf(fpRes,"nrObserver=1\n");
		fprintf(fpRes,"id=message fmt=%%s\n");
		fprintf(fpRes,"nrFormat=2\n");
		fprintf(fpRes,"id=f1m ctxt=%cmessage%c vtxt=%cmessage%c\n",'"','"','"','"');
	}
	else
	{
		fprintf(fpRes,"nrObserver=0\n");
		fprintf(fpRes,"nrFormat=1\n");
	}

	fprintf(fpRes,"id=f0 ctxt=%cstep%c\n",'"','"');
}

/*--------------------------------------------------------------------------*/
/* outRes                                                                   */
/*--------------------------------------------------------------------------*/

void GalConv::outRes(enum GAL_CONV_OBJECT obj,char *id,int nrArg,char *fktName,char *txt)
{
	static char oldFktName[GAL_ID];
	char *p=txt;
	char level;
	char fmtT[GAL_ID];

	while(*p!=0)
	{
		if(*p=='"')
			*p=' ';
		p++;
	}

	switch(obj)
	{
	case MSG_COUT:
		level='I';
		strcpy(fmtT,"f1m");
		break;
	case MSG_CERR:
		level='E';
		strcpy(fmtT,"f1m");
		break;
	default:
		level='D';
		sprintf(fmtT,"f%d",nrArg);
		break;
	}

	cntRes++;

	if(strcmp(oldFktName,fktName)==0)
	  fprintf(fpResH,"id=%s enable=1 level=%c group=ff idLogger=%s idFormat=%s ctxt=%c%s%c\n",id,level,lStd,fmtT,'"',txt,'"');
	else
	  fprintf(fpResH,"id=%s enable=1 level=%c group=ff idLogger=%s idFormat=%s ctxtHead=%c%s%c ctxt=%c%s%c\n",id,level,lStd,fmtT,'"',fktName,'"','"',txt,'"');

	strcpy(oldFktName,fktName);
}

/*--------------------------------------------------------------------------*/
/* outEndRes                                                                */
/*--------------------------------------------------------------------------*/

void GalConv::outFinalRes()
{
	char fileName[GAL_FILE_NAME];
	int eolReached=0;
	int c;

	fclose(fpResH);
	fclose(fpIn);
	fpResH=fpIn=NULL;

	sprintf(fileName,"%s.res","tmp");
	fpIn=openFile(fileName,"r");

	fprintf(fpRes,"nrEvent=%d\n",cntRes);

	while((c=getc(fpIn))!=EOF)
	{
		if(putc(c,fpRes)==EOF)
			throw "file problem";
	}
}

/*--------------------------------------------------------------------------*/
/* outFinalConv                                                             */
/*--------------------------------------------------------------------------*/

void GalConv::outFinalConv()
{
	char fileName[GAL_FILE_NAME];
	int eolReached=0;
	int c;
	int flag=0;

	fclose(fpOut);
	fclose(fpIn);
	fclose(fpInit);
	fpOut=fpIn=fpInit=NULL;
	
	sprintf(fileName,"%s.conv","tmp");
	fpIn=openFile(fileName,"r");

	sprintf(fileName,"%s.init",convFileName);
	fpInit=openFile(fileName,"r");

	sprintf(fileName,"%s.conv",convFileName);
	fpOut=openFile(fileName,"w");

	while(eolReached==0)
	{
		readLine(&eolReached);
		if(!isTxtInserted(tagInit))
			fprintf(fpOut,"%s\n",stringLine);
		else
		{
			if(flag)
				throw "Gal init tag inserted twice";
			fprintf(fpOut,"%s\n",stringLine);
			flag=1;
			while((c=getc(fpInit))!=EOF)
			{
				if(putc(c,fpOut)==EOF)
					throw "file problem";
			}
		}
	}
	if(flag==0)
		throw "Gal init tag not found";
}

/********************************* Protocol ********************************/

/*--------------------------------------------------------------------------*/
/* outProt                                                                  */
/*--------------------------------------------------------------------------*/

void GalConv::outProt(char *msg)
{
	cntProt++;
	fprintf(fpProt,"line=%d string=<%s>: %s\n",line,stringLine,msg);
}

/*--------------------------------------------------------------------------*/
/* outProtMain                                                              */
/*--------------------------------------------------------------------------*/

void GalConv::outProtMain(char *msg)
{
	fprintf(fpProtMain,"%s\n",msg);
	printf("%s\n",msg);
}

