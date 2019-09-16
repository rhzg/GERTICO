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
** File(s)      : event.h
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

#ifndef __Event__included__
#define __Event__included__

/*****************************************************************************
****  INCLUDES/DEFINITIONS                                                ****
*****************************************************************************/

#define E1mBegin(e) if(e->enabled)
#define E1mEnd(e,p1) e->pm.acquire();e->p();e->p(p1);e->out();e->pm.release();

#define E0(e) if(e->enabled){e->pm.acquire();e->p();e->out();e->pm.release();}
#define E1(e,p1) if(e->enabled){e->pm.acquire();e->p();e->p(p1);e->out();e->pm.release();}
#define E2(e,p1,p2) if(e->enabled){e->pm.acquire();e->p();e->p(p1);e->p(p2);e->out();e->pm.release();}
#define E3(e,p1,p2,p3) if(e->enabled){e->pm.acquire();e->p();e->p(p1);e->p(p2);e->p(p3);e->out();pm.release();}
#define E4(e,p1,p2,p3,p4) if(e->enabled){e->pm.acquire();e->p();e->p(p1);e->p(p2);e->p(p3);e->p(p4);e->out();pm.release();}
#define E5(e,p1,p2,p3,p4,p5) if(e->enabled){e->pm.acquire();e->p();e->p(p1);e->p(p2);e->p(p3);e->p(p4);e->p(p5);e->out();e->pm.release();}
#define E6(e,p1,p2,p3,p4,p5,p6) if(e->enabled){e->pm.acquire();e->p();e->p(p1);e->p(p2);e->p(p3);e->p(p4);e->p(p5);e->p(p6);e->out();e->pm.release();}
#define E7(e,p1,p2,p3,p4,p5,p6,p7) if(e->enabled){e->pm.acquire();e->p();e->p(p1);e->p(p2);e->p(p3);e->p(p4);e->p(p5);e->p(p6);e->p(p7);e->out();e->pm.release();}
#define E8(e,p1,p2,p3,p4,p5,p6,p7,p8) if(e->enabled){e->pm.acquire();e->p();e->p(p1);e->p(p2);e->p(p3);e->p(p4);e->p(p5);e->p(p6);e->p(p7);e->p(p8);e->out();e->pm.release();}
#define E9(e,p1,p2,p3,p4,p5,p6,p7,p8,p9) if(e->enabled){e->pm.acquire();e->p();e->p(p1);e->p(p2);e->p(p3);e->p(p4);e->p(p5);e->p(p6);e->p(p7);e->p(p8);e->p(p9);e->out();e->pm.release();}

#include "ace/Synch.h"

#include "logger.h"
#include "format.h"
#include "adm.h"

/*****************************************************************************
****  CLASS DEFINITIONS                                                   ****
*****************************************************************************/

class GAL_EXPORT Event: public Adm
{
	friend class Appender;
	friend class Layout;
	friend class Format;
	friend class Logger;
	friend class Repository;
	friend class Repository_l;

//variables
	protected:

	private:
		unsigned long cnt;
		char ctxt[GAL_CTXT];
		char idLogger[GAL_NAME];
		char idFormat[GAL_NAME];
		class Repository_l *repository_l;
		class Logger *logger;
		enum GAL_LEVEL level;
		unsigned int group;

	public:
    static ACE_Thread_Mutex pm;
		int enabled;
		char txt[GAL_TXT];
		class Format *format;
		int triggerEnable;

//functions
	protected:

	private:
		Event(class Repository_l *repository_l,char *id,int enable,enum GAL_LEVEL level,unsigned int group,char *ctxt,char *idLogger,char *idFormat);

		static enum GAL_LEVEL convertLevel(char *slevel);			
		static char *convertLevel(enum GAL_LEVEL level);			

		size_t getSize();

	public:
		Event();
		~Event();

		void p();
		void p(unsigned int val);
		void p(int val);
		void p(unsigned long val);
		void p(long val);
		void p(char *val);
		void p(const char *val);
		void p(double val);
		void p(long double val);
		void p(char val);
		void p(void *val);

		void out();		
};

/****************************************************************************/

#endif
