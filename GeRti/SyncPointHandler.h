/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: SyncPointHandler.h,v $
Revision 1.18  2009/06/12 12:55:02  mul
Use thread mutex.

Revision 1.17  2007/09/06 09:14:42  mul
Changes for ieee1516.

Revision 1.16  2007/06/26 08:35:49  mul
Changes for ieee1516.

Revision 1.15  2007/03/12 13:25:39  mul
Changed string to wstring.

Revision 1.14  2007/02/02 13:37:25  mul
Minor changes.

Revision 1.13  2006/11/28 15:48:08  mul
Use federates holder.

Revision 1.12  2006/08/30 11:50:06  mul
Add federates holder.

Revision 1.11  2005/09/09 11:55:03  mul
Files from EventMarket directory.

Revision 1.6  2005/08/03 13:37:47  mul
Add concurrent access logic.

Revision 1.5  2005/02/09 07:39:08  mul
Scoping added for std.

Revision 1.4  2005/01/28 08:42:31  hzg
merging gertico_0_16b_fix into main thread

Revision 1.3  2004/12/14 11:28:44  mul
Minor changes for verification test.

Revision 1.2.2.1  2005/01/27 10:22:08  hzg
bug fix concerning include and std usage
requred for using ACE-5.4+TAO-1.4

Revision 1.2  2004/07/16 13:13:21  mul
Changes due to verfication test.

Revision 1.1  2004/05/27 11:58:04  mul
Changes due to subscriber integration.


**
*******************************************************************************/


#ifndef SyncPointHandler_H_
#define SyncPointHandler_H_

#include <map>
#include <string>
#include "idl/GeRtiFactoryS.h"
#include "Util/Federate.h"

#include "ace/Synch.h"

namespace GERTICO
{
  class SyncPointFederate
  {
    GeRtiFactory::GeRtiHandle fed;
    bool syncPointAchieved;
    bool syncPointAnnounced;

  public:
    SyncPointFederate (const GeRtiFactory::GeRtiHandle &);
    virtual ~SyncPointFederate (void);

    GeRtiFactory::GeRtiHandle getFed (void);
    bool getSyncPointAchieved (void);
    void setSyncPointAchieved (void);
    bool getSyncPointAnnounced (void);
    void setSyncPointAnnounced (void);
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, GERTICO::SyncPointFederate *> cSyncPointFederateMap;

  class SyncPoint
  {
    GeRtiFactory::UserSuppliedTag tag;
    bool syncPointConfirmed;
    bool designated;
    bool distributingFederationSynchronized;
    bool synchronized;

  public:
    bool confirmed;
    cSyncPointFederateMap syncPointfederates;
    GeRtiFactory::GeRtiHandle originalRegisterer;
    std::wstring label;

    SyncPoint(const std::wstring &theLabel, const GeRtiFactory::UserSuppliedTag &theTag, const GeRtiFactory::GeRtiHandle &theFederate);
    virtual ~SyncPoint (void);

    GeRtiFactory::GeRtiHandle getFed (void);
    void addSyncPointFederate (const GeRtiFactory::GeRtiHandle &);
    bool isDesignated (void);
    bool isDistributingFederationSynchronized(void);
    bool isSynchronized (void);
    void processSyncPointAchieved(GERTICO::FederatesHolder &theFederatesHolder, ACE_Thread_Mutex &);
    void processSyncPointRegistration(GERTICO::FederatesHolder &theFederatesHolder, ACE_Thread_Mutex &);
    void resignFederate (const GeRtiFactory::GeRtiHandle &);
    void setDesignated (void);
    bool synchronizationPointAchieved (const GeRtiFactory::GeRtiHandle &theFederate);
  };

  typedef std::map <std::wstring, GERTICO::SyncPoint *> SyncPointMap;

  // More than one failure can happen at any point in time.
  class SyncPointData
  {
  public:
    std::wstring label;
    GeRtiFactory::SynchronizationPointFailureReason reason;
  };

  typedef std::map <GeRtiFactory::GeRtiHandle, SyncPointData> SyncFailedMap;

  class SyncPointHandler
  {
    ACE_Thread_Mutex pm;
    GERTICO::FederatesHolder &federatesHolder;
    SyncFailedMap failures;
    SyncPointMap syncPoints;

    void processSynchronizationPointAchieved (void);
    void processSynchronizationPointFailures (void);
    void processSynchronizationPointRegistration (void);

  public:
    SyncPointHandler(GERTICO::FederatesHolder &theFederatesHolder);
    virtual ~SyncPointHandler (void);

    void addFederate (const GeRtiFactory::GeRtiHandle &theFed);
    int process (void);
    void registerSynchronizationPoint(const std::wstring &, const GeRtiFactory::UserSuppliedTag &, const GeRtiFactory::Handles &, const GeRtiFactory::GeRtiHandle &);
    void resignFed (const GeRtiFactory::GeRtiHandle &);
    void synchronizationPointAchieved(const std::wstring &, const GeRtiFactory::GeRtiHandle &);
  };
};

#endif /* SyncPointHandler_H_  */
