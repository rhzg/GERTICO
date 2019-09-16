/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Log: JobHolder.h,v $
Revision 1.12  2010/03/22 12:44:35  mul
Changes for single callbacks.

Revision 1.11  2010/02/25 07:28:50  mul
Changes for single callbacks.

Revision 1.10  2009/06/12 12:11:32  mul
Use thread mutex.

Revision 1.9  2005/05/03 14:57:48  mul
Add save logic to jobs.

Revision 1.8  2004/09/23 14:54:48  mul
Logic to clear job queue.

Revision 1.7  2003/05/23 08:16:37  mul
Delete mutex in destructor.

Revision 1.6  2003/04/29 06:26:27  hzg
Portierung auf Windows

Revision 1.5  2003/03/21 09:03:53  mul
Prevent multi-thread conflicts by doubling the number of job maps.

Revision 1.4  2003/01/29 14:47:46  mul
Add mutex to job handler to make it thread safe.

Revision 1.3  2002/11/28 09:54:28  mul
Remove semaphore calls to prevent blocking.

Revision 1.2  2002/11/18 14:21:44  mul
Add generic job holder.

Revision 1.1  2002/11/18 14:09:08  mul
Add abstract JobHolder interface.


**
*******************************************************************************/

#ifndef JobHolder_H
#define JobHolder_H

#include "ace/Synch.h"
#include <list>
#include "XercesInclude.h"
#include "HLAparseErrorHandler.h"

namespace GERTICO
{

//****************************************************
//
typedef enum
{
  active,
  done
} JobStatus;

class Job
{
public:

  Job () { };
  virtual ~Job() {};
  virtual JobStatus execute ();
  virtual JobStatus save (DOMDocument &theDOMDocument, DOMElement &theDOMElement);
};



//****************************************************
//
class JobHolder
{
private:
  ACE_Thread_Mutex *pm;
  std::list<Job*> myJobs[2];
  bool firstJobList;

public:

  JobHolder ();
  virtual ~JobHolder ();
  void clear (void);
  bool performJobs(bool const &processAll); // some kind of tick
  void performSave(DOMDocument &theDOMDocument, DOMElement &theDOMElement);

  virtual void add (Job* aJob);
};

}; // workspace GERTICO

#endif // JobHolder_H
