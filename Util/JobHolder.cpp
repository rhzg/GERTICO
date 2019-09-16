/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Log: JobHolder.cpp,v $
Revision 1.20  2010/03/22 12:45:02  mul
Changes for single callbacks.

Revision 1.19  2010/03/05 12:53:43  mul
Changes for single evoke call.

Revision 1.18  2010/03/02 11:22:42  mul
Changes for single callbacks.

Revision 1.17  2009/06/12 12:11:32  mul
Use thread mutex.

Revision 1.16  2006/12/15 08:42:02  mul
Minor change.

Revision 1.15  2006/08/01 11:22:11  mul
Fix exception handling.

Revision 1.14  2005/05/03 14:57:48  mul
Add save logic to jobs.

Revision 1.13  2005/02/11 14:46:34  mul
Add scoping.

Revision 1.12  2005/02/09 07:39:25  mul
Scoping added for std.

Revision 1.11  2005/01/28 08:42:36  hzg
merging gertico_0_16b_fix into main thread

Revision 1.10.2.1  2005/01/27 10:22:31  hzg
bug fix concerning include and std usage
requred for using ACE-5.4+TAO-1.4

Revision 1.10  2004/09/23 14:54:48  mul
Logic to clear job queue.

Revision 1.9  2003/06/03 11:38:19  mul
Fix delete argument.

Revision 1.8  2003/05/23 08:16:37  mul
Delete mutex in destructor.

Revision 1.7  2003/05/15 15:12:51  hzg
make install as new target

Revision 1.6  2003/04/29 06:26:27  hzg
Portierung auf Windows

Revision 1.5  2003/03/31 12:57:54  mul
Clear both queues in JobHolder in performJobs.

Revision 1.4  2003/03/21 09:03:53  mul
Prevent multi-thread conflicts by doubling the number of job maps.

Revision 1.3  2003/01/29 14:47:46  mul
Add mutex to job handler to make it thread safe.

Revision 1.2  2002/11/28 09:54:28  mul
Remove semaphore calls to prevent blocking.

Revision 1.1  2002/11/18 14:21:44  mul
Add generic job holder.


**
*******************************************************************************/

#include "JobHolder.h"
#include "ace/Thread_Manager.h"

#include <iostream>

//***********************************************
//
GERTICO::JobStatus GERTICO::Job::execute ()
{
  std::cout << "Job::execute: no implementation" << std::endl;
  return done;
}

//***********************************************
//
GERTICO::JobStatus GERTICO::Job::save(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
  std::cout << "Job::save: no implementation" << std::endl;
  return done;
}


//***********************************************
//
GERTICO::JobHolder::JobHolder ()
{
#ifdef JobHolderTraceDEBUG
  std::cout << "JobHolder::JobHolder ()" << std::endl;
#endif
  pm = new ACE_Thread_Mutex ();
  firstJobList = true;
};

//***********************************************
//
GERTICO::JobHolder::~JobHolder ()
{
  clear();
  delete pm;
}

//***********************************************
//
void GERTICO::JobHolder::clear (void)
{
  int i = 0;
  int loop;
  Job *job;
  std::list<Job*> *myJobsPtr;
  std::list<Job*>::iterator aJob;

  pm->acquire ();
  for (loop = 0; loop < 2; loop++)
  {
    // Add uses the other myJobs.
    if (firstJobList)
    {
      i = 1;
    }
    else
    {
      i = 0;
    }
    myJobsPtr = &myJobs[i];

    for (aJob = myJobsPtr->begin();
         aJob != myJobsPtr->end();
         aJob = myJobsPtr->begin())
    {
      job = *aJob;
      myJobsPtr->erase (aJob);
      delete job;
    }

    // Reset control flags.
    if (firstJobList)
    {
      firstJobList = false;
    }
    else
    {
      firstJobList = true;
    }
  }
  pm->release ();
}

//***********************************************
//
bool GERTICO::JobHolder::performJobs(bool const &processAll)
{
#ifdef JobHolderTraceDEBUG
  std::cout << "JobHolder::performJobs entered" << std::endl;
#endif
  bool gotOneJob = false;
  bool lastJob = false;
  int i = 0;
  int ind = 0;
  int len;
  int loop;
  int numActiveJobs;
  Job *job;
  std::list<Job*> *myJobsPtr;
  std::list<Job*> tmpJobsPtr;
  std::list<Job*>::iterator aJob;

  for (loop = 0; loop < 2; loop++)
  {
    if (gotOneJob)
    {
      if (processAll == false)
      {
        break;
      }
    }
    pm->acquire ();
    // Add uses the other myJobs.
    if (firstJobList)
    {
      i = 1;
    }
    else
    {
      i = 0;
    }
    myJobsPtr = &myJobs[i];
    pm->release ();

#ifdef JobHolderTraceDEBUG
std::cout << "JobHolder::performJobs jobs: " << myJobsPtr->size() << std::endl;
#endif

    pm->acquire ();
    lastJob = false;
    ind = 0;
    len = myJobsPtr->size();
    for (aJob = myJobsPtr->begin();
         aJob != myJobsPtr->end();
         aJob = myJobsPtr->begin())
    {
      ind += 1;
      pm->release ();
      job = *aJob;
      try
      {
        if (job->execute() == done)
        {
          gotOneJob = true;
          myJobsPtr->erase (aJob);
          delete job;
          if (processAll == false)
          {
            pm->acquire ();
            break;
          }
        }
        else
        {
          tmpJobsPtr.push_back (*aJob);
          myJobsPtr->erase (aJob);
        }
      }
      catch(...)
      {
        myJobsPtr->erase (aJob);
        delete job;
      }
      pm->acquire ();
    }
    if (loop == 1)
    {
      if (ind == len)
      {
        // We have reached the end of all jobs ie. no further jobs.
        lastJob = true;
      }
    }
    pm->release ();

    numActiveJobs = tmpJobsPtr.size();
    for (aJob = tmpJobsPtr.begin();
         aJob != tmpJobsPtr.end();
         aJob = tmpJobsPtr.begin())
    {
      myJobsPtr->push_back (*aJob);
      tmpJobsPtr.erase (aJob);
    }

    // Reset control flags.
    if (myJobsPtr->size() == numActiveJobs)
    {
      pm->acquire ();
      if (firstJobList)
      {
        firstJobList = false;
      }
      else
      {
        firstJobList = true;
      }
      pm->release ();
    }
  }

  // The last job was processed, no more to process.
  if (lastJob)
  {
    return false;
  }
  else
  {
    return true;
  }
#ifdef JobHolderTraceDEBUG
  std::cout << "JobHolder::performJobs leaving" << std::endl;
#endif
}

//***********************************************
//
void GERTICO::JobHolder::performSave(DOMDocument &theDOMDocument, DOMElement &theDOMElement)
{
#ifdef JobHolderTraceDEBUG
  std::cout << "JobHolder::performJobs entered" << std::endl;
#endif
  int i = 0;
  int loop;
  Job *job;
  std::list<Job*> *myJobsPtr;
  std::list<Job*> tmpJobsPtr;
  std::list<Job*>::iterator aJob;

  for (loop = 0; loop < 2; loop++)
  {
    pm->acquire ();
    // Add uses the other myJobs.
    if (firstJobList)
    {
      i = 1;
    }
    else
    {
      i = 0;
    }
    myJobsPtr = &myJobs[i];
    pm->release ();

#ifdef JobHolderTraceDEBUG
std::cout << "JobHolder::performJobs jobs: " << myJobsPtr->size() << std::endl;
#endif

    pm->acquire ();
    for (aJob = myJobsPtr->begin();
         aJob != myJobsPtr->end();
         aJob = myJobsPtr->begin())
    {
      pm->release ();
      job = *aJob;
      if (job->save(theDOMDocument, theDOMElement) == done)
      {
        myJobsPtr->erase (aJob);
        delete job;
      }
      else
      {
        myJobsPtr->erase (aJob);
        tmpJobsPtr.push_back (*aJob);
      }
      pm->acquire ();
    }
    pm->release ();

    for (aJob = tmpJobsPtr.begin();
         aJob != tmpJobsPtr.end();
         aJob = tmpJobsPtr.begin())
    {
      myJobsPtr->push_back (*aJob);
      tmpJobsPtr.erase (aJob);
    }

    // Reset control flags.
    pm->acquire ();
    if (firstJobList)
    {
      firstJobList = false;
    }
    else
    {
      firstJobList = true;
    }
    pm->release ();
  }

#ifdef JobHolderTraceDEBUG
  std::cout << "JobHolder::performJobs leaving" << std::endl;
#endif
}

//***********************************************
//
void GERTICO::JobHolder::add (Job* aJob)
{
#ifdef JobHolderTraceDEBUG
  std::cout << "JobHolder::add entered" << std::endl;
#endif
  int i = 0;
  std::list<Job*> *myJobsPtr;

//  ACE_OS::sleep (ACE_Time_Value(0,2000));
  pm->acquire ();

  // performJobs uses the other myJobs.
  if (firstJobList)
  {
    i = 0;
  }
  else
  {
    i = 1;
  }
  myJobsPtr = &myJobs[i];

  myJobsPtr->push_back (aJob);
  pm->release ();

#ifdef JobHolderTraceDEBUG
  std::cout << "JobHolder::add jobs: " << myJobsPtr->size() << std::endl;
#endif
}
