/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************/

//-----------------------------------------------------------------
// Project Include Files
//-----------------------------------------------------------------
 
#include "ut.h" 
#include "Util/GeRtiTypes.h" 

//-----------------------------------------------------------------
// System Include Files
//-----------------------------------------------------------------

/*--------------------------------------------------------------------------*/
/* ut                                                                       */
/*--------------------------------------------------------------------------*/

GERTICO::ut::ut()
{
}

GERTICO::ut::~ut()
{
}

/*--------------------------------------------------------------------------*/
/* convert                                                                  */
/*--------------------------------------------------------------------------*/

char *GERTICO::ut::convert(unsigned int val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%u",val);
	return txt;
}

char *GERTICO::ut::convert(int val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%d",val);
	return txt;
}

char *GERTICO::ut::convert(unsigned long val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%lu",val);
	return txt;
}

char *GERTICO::ut::convert(long val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%ld",val);
	return txt;
}

char *GERTICO::ut::convert(char *val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%s",val);
	return txt;
}

char *GERTICO::ut::convert(const char *val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%s",val);
	return txt;
}

char *GERTICO::ut::convert(double val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%g",val);
	return txt;
}

char *GERTICO::ut::convert(long double val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%Lg",val);
	return txt;
}

char *GERTICO::ut::convert(char val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%c",val);
	return txt;
}

char *GERTICO::ut::convert(void *val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%#lx",(unsigned long)val);
	return txt;
}

char *GERTICO::ut::convert(const void *val)
{
	static char txt[MAX_TXT];
	sprintf(txt,"%#lx",(unsigned long)val);
	return txt;
}

char *GERTICO::ut::convertLogicalTime(GERTICO::GeRtiFedTimeFactory &theGeRtiFedTimeFactory, GERTICO::GeRtiFedTime const &val)
{
	static char txt[MAX_TXT];
  std::auto_ptr<GERTICO::GeRtiFedTime> t(theGeRtiFedTimeFactory.makeZero());
	*t=val;
	int length;

	length=t->getPrintableLength();
	if(length>MAX_TXT)
		strcpy(txt,"text to print exceeds range");
	else
		t->getPrintableString(txt);
	return txt;
}


/*--------------------------------------------------------------------------*/
/* printAttributeHandle                                                     */
/*--------------------------------------------------------------------------*/

void GERTICO::ut::printAttributeHandleSet(char *txt,const RTI::AttributeHandleSet& theAttributeHandleSet)
{
  RTI::AttributeHandle attributeHandle;
  RTI::ULong i;
  RTI::ULong size=theAttributeHandleSet.size();

	sprintf(&txt[strlen(txt)],",%s","handles:");
  for(i=0;i<size;i++)
  {
    attributeHandle=theAttributeHandleSet.getHandle (i);
		sprintf(&txt[strlen(txt)],"%lu,",attributeHandle);
  }
}

void GERTICO::ut::printAttributeHandleValuePairSet(char *txt,const RTI::AttributeHandleValuePairSet& theAttributeHandleValuePairSet)
{
  RTI::AttributeHandle attributeHandle;
  RTI::ULong i;
  RTI::ULong size=theAttributeHandleValuePairSet.size();
	RTI::ULong l;
	RTI::ULong ll;
	RTI::ULong &length=l;
	char buff[MAX_BUFF];
	char txtH[MAX_TXT];
	unsigned char *p;
	int isPrintable;

	sprintf(&txt[strlen(txt)],",%s","handles:");
  for (i=0;i<size;i++)
  {
    attributeHandle=theAttributeHandleValuePairSet.getHandle (i);
		theAttributeHandleValuePairSet.getValue(i,buff,length);
		ll=length;
		if(ll>40)
			ll=40;
		p=(unsigned char *)buff;

		isPrintable=1;	
		for(l=0;l<ll;l++)
		{
			if(*p!=0)
			{
				if(isprint(*p++)==0)
				{
					isPrintable=0;
					break;
				}
			}
		}

		if(isPrintable==0)
			if(ll>10)ll=10;

		p=(unsigned char *)buff;
		for(l=0;l<ll;l++)
		{
			if(isPrintable)
				sprintf(&txtH[l],"%c",*p++);
			else
				sprintf(&txtH[2*l],"%2.2x",*p++);
		}
		if(isPrintable)
		{
			txtH[ll]=0;
			sprintf(&txt[strlen(txt)],"%lu(%s),",attributeHandle,txtH);
		}
		else
		{
			txtH[2*ll]=0;
			sprintf(&txt[strlen(txt)],"%lu(0x%s),",attributeHandle,txtH);
		}
  }
}

void GERTICO::ut::printParameterHandleValuePairSet(char *txt,const RTI::ParameterHandleValuePairSet& theParameterHandleValuePairSet)
{
  RTI::ParameterHandle parameterHandle;
  RTI::ULong i;
  RTI::ULong size=theParameterHandleValuePairSet.size();
	RTI::ULong l;
	RTI::ULong ll;
	RTI::ULong &length=l;
	char buff[MAX_BUFF];
	char txtH[MAX_TXT];
	unsigned char *p;
	int isPrintable;

	sprintf(&txt[strlen(txt)],",%s","handles:");
  for (i=0;i<size;i++)
  {
    parameterHandle=theParameterHandleValuePairSet.getHandle (i);
		theParameterHandleValuePairSet.getValue(i,buff,length);
		ll=length;
		if(ll>40)
			ll=40;		
		p=(unsigned char *)buff;

		isPrintable=1;	
		for(l=0;l<ll;l++)
		{
			if(*p!=0)
			{
				if(isprint(*p++)==0)
				{
					isPrintable=0;
					break;
				}
			}
		}

		if(isPrintable==0)
			if(ll>10)ll=10;
		
		p=(unsigned char *)buff;
		for(l=0;l<ll;l++)
		{
			if(isPrintable)
				sprintf(&txtH[l],"%c",*p++);
			else
				sprintf(&txtH[2*l],"%2.2x",*p++);
		}
		if(isPrintable)
		{
			txtH[ll]=0;
			sprintf(&txt[strlen(txt)],"%lu(%s),",parameterHandle,txtH);
		}
		else
		{
			txtH[2*ll]=0;
			sprintf(&txt[strlen(txt)],"%lu(0x%s),",parameterHandle,txtH);
		}
  }
}	

