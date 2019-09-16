/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: TimeServiceFacI.cpp,v $
Revision 1.10  2009/05/07 12:45:07  mul
Changes for removing token logic in time management.

Revision 1.9  2005/12/19 15:54:57  mul
Separate child poa from singleton.

Revision 1.8  2005/11/17 13:41:55  mul
Fix memory leaks.

Revision 1.7  2005/09/07 12:28:10  mul
Remove name service. Change name scoping.

Revision 1.6  2004/12/14 10:56:19  mul
Clean up.

Revision 1.5  2004/11/22 13:24:34  mul
Simplify time interface.

Revision 1.4  2004/09/24 07:36:15  mul
Add namespace.

Revision 1.3  2003/10/10 13:31:10  mul
New ORB init logic.

Revision 1.2  2002/07/16 08:57:21  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen


**
*******************************************************************************/


#include "TokenHolder.h"
#include "TimeServiceFacI.h"

#include <ace/OS.h>
#include "ace/Synch.h"
#include "ace/Thread_Manager.h"
#include "ace/Thread.h"

// ---------------------------------------------------------------------------
// A thread to asynchronously process tokens.
// ---------------------------------------------------------------------------
void *token_worker(void *arg)
{
  GERTICO::TokenHolder *tokenHolder = (GERTICO::TokenHolder *) arg;

  while (tokenHolder->notDone)
  {
    if (tokenHolder->psToken->acquire () == -1)
    {
      // Do not have the semaphore: error.
      ACE_OS::sleep(1);
      continue;
    }

    tokenHolder->process();
  }

  return NULL;
}

GERTICO::TimeServiceFacI::TimeServiceFacI(TimeServiceClient &theTsc) : tsc(theTsc)
{
}

GERTICO::TimeServiceFacI::~TimeServiceFacI ()
{
  ACE_Thread_Manager::instance()->wait_grp (tid1);
}

GERTICO::TimeService *GERTICO::TimeServiceFacI::createTimeService ()
{
  GERTICO::TokenHolder *tokenHolder;
  tokenHolder = new TokenHolder(tsc, *tsc.geRtiFedTimeFactory, *tsc.geRtiLogicalTimeIntervalFactory);

//  tid1 = ACE_Thread_Manager::instance()->spawn (ACE_reinterpret_cast (ACE_THR_FUNC, &token_worker), tokenHolder, THR_NEW_LWP | THR_JOINABLE);
  TimeService *ts = (TimeService *)tokenHolder;
  return ts;
}
