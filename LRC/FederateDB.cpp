/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** FederateDB.cpp
**
*******************************************************************************/

#include "FederateDB.h"

/********************************* Gal begin *********************************/
#ifdef GalDebug

#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

static class Repository_l *FM=(Repository::getSingleInstance())->getRepository_l("GeRtiFM.res","GeRtiFM");

static class Event *GeRti_FM_feds_i=FM->getRefEvent("GeRti_FM_feds_i");
static class Event *GeRti_FM_d=FM->getRefEvent("GeRti_FM_d");
static class Event *GeRti_FM_e=FM->getRefEvent("GeRti_FM_e");
static class Event *GeRti_FM_w=FM->getRefEvent("GeRti_FM_w");

#endif
/*********************************** Gal end *********************************/

GERTICO::FederateDB::FederateDB(void)
{
  char galMsg[512];
  char host[256];

  if (gethostname (host, 256))
  {
    switch (errno)
    {
      case EINVAL:
      {
        strcpy(galMsg, "errno: EINVAL"); 
      }
      case EPERM:
      {
        strcpy(galMsg, "errno: EPERM"); 
      }
      case EFAULT:
      {
        strcpy(galMsg, "errno: EFAULT"); 
      }
#ifdef _WIN32
      case WSAEFAULT:
      {
        strcpy(galMsg, "errno: WSAEFAULT"); 
      }
      case WSANOTINITIALISED:
      {
        strcpy(galMsg, "errno: WSANOTINITIALISED"); 
      }
      case WSAENETDOWN:
      {
        strcpy(galMsg, "errno: WSAENETDOWN"); 
      }
      case WSAEINPROGRESS:
      {
        strcpy(galMsg, "errno: WSAEINPROGRESS"); 
      }
#endif
      default:
      {
        sprintf(galMsg, "errno: %d", errno); 
      }
    }
                           #ifdef GalDebug   // inserted by Gal converter
                              E2(GeRti_FM_e, "gethostname", galMsg);
                           #endif   // inserted by Gal converter
#ifdef IEEE_1516
    std::wstring h(L"unknownHost");
#else
    std::string h("unknownHost");
#endif
    hostName = h;
  }
  else
  {
#ifdef IEEE_1516
    std::wstring h;
    GERTICO::Mapper::mapWstringFromChar(h, host);
#else
    std::string h(host);
#endif
    hostName = h;
  }

  dataDistributionManagementLRC = NULL;
  declarationManagementLRC = NULL;
  joined = false;
  objectManagementLRC = NULL;
  ownership = NULL;
  runTimeObjectDB = NULL;
  supportingServicesLRC = NULL;
  timeManagementLRC = NULL;

  runTimeObjectDB = new GERTICO::RunTimeObjectDB(registeredObjectsHolder, regionsHolder);
  ps = new ACE_Semaphore(1);
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::FederateDB::~FederateDB(void)
{
  delete ps;
  clear();

  if (runTimeObjectDB)
  {
    delete runTimeObjectDB;
    runTimeObjectDB = NULL;
  }
}

// ---------------------------------------------------------------------------
// Keep track of time to delete for each object deleted with time.
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::addDeleteObjectWithTime(GeRtiFactory::GeRtiHandle const &theObject, GERTICO::GeRtiFedTime const &theTime)
{
  GERTICO::DeleteObjectWithTimeMap::iterator itDOWTM;
  std::auto_ptr<GERTICO::GeRtiFedTime> fedTime(timeManagementLRC->geRtiFedTimeFactory.makeZero());
  *fedTime = theTime;

  pm.acquire();
  itDOWTM = deleteObjectWithTimeMap.find(theObject);
  if (itDOWTM != deleteObjectWithTimeMap.end())
  {
    // Have a new timestamp.
    std::auto_ptr<GERTICO::GeRtiFedTime> t(itDOWTM->second);
    deleteObjectWithTimeMap.erase(itDOWTM);
  }
  deleteObjectWithTimeMap[theObject] = fedTime.release();
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::addObjectDiscovered(GeRtiFactory::GeRtiHandle const &theObject)
{
  std::set <GeRtiFactory::GeRtiHandle>::iterator its;

  pm.acquire();
  its = objectsDiscovered.find(theObject);
  if (its == objectsDiscovered.end())
  {
    objectsDiscovered.insert(theObject);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::addObjectReflected(GeRtiFactory::GeRtiHandle const &theObject)
{
  std::set <GeRtiFactory::GeRtiHandle>::iterator its;

  pm.acquire();
  its = objectsReflected.find(theObject);
  if (its == objectsReflected.end())
  {
    objectsReflected.insert(theObject);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::addObjectRemoved(GeRtiFactory::GeRtiHandle const &theObject)
{
  std::set <GeRtiFactory::GeRtiHandle>::iterator its;

  pm.acquire();
  its = objectsRemoved.find(theObject);
  if (its == objectsRemoved.end())
  {
    objectsRemoved.insert(theObject);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::addRegisterObjectInstance(GeRtiFactory::GeRtiHandle const &theObject, GeRtiFactory::GeRtiHandle const &theClass)
{
  std::set <GeRtiFactory::GeRtiHandle>::iterator its;

  pm.acquire();
  its = objectsUpdated.find(theObject);
  if (its == objectsUpdated.end())
  {
    objectsUpdated.insert(theObject);
  }
  pm.release();

  pm.acquire();
  its = objectsRegistered.find(theObject);
  if (its == objectsRegistered.end())
  {
    objectsRegistered.insert(theObject);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::clear(void)
{
  GERTICO::DeleteObjectWithTimeMap::iterator itDOWTM;
  GERTICO::GeRtiFedTime *tmpFedTime;

  for (itDOWTM = deleteObjectWithTimeMap.begin(); itDOWTM != deleteObjectWithTimeMap.end(); itDOWTM = deleteObjectWithTimeMap.begin())
  {
    tmpFedTime = itDOWTM->second;
    deleteObjectWithTimeMap.erase(itDOWTM);
    delete tmpFedTime;
  }

  if (dataDistributionManagementLRC)
  {
    delete dataDistributionManagementLRC;
    dataDistributionManagementLRC = NULL;
  }

  if (declarationManagementLRC)
  {
    delete declarationManagementLRC;
    declarationManagementLRC = NULL;
  }

  if (objectManagementLRC)
  {
    delete objectManagementLRC;
    objectManagementLRC = NULL;
  }

  if (ownership)
  {
    delete ownership;
    ownership = NULL;
  }

  if (timeManagementLRC)
  {
    delete timeManagementLRC;
    timeManagementLRC = NULL;
  }

  if (supportingServicesLRC)
  {
    delete supportingServicesLRC;
    supportingServicesLRC = NULL;
  }
}

// ---------------------------------------------------------------------------
// Force removal of time whenever object deleted earlier than expected.
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::delDeleteObjectWithTime(GeRtiFactory::GeRtiHandle const &theObject)
{
  GERTICO::DeleteObjectWithTimeMap::iterator itDOWTM;
  GERTICO::GeRtiFedTime *tmpFedTime;

  pm.acquire();
  itDOWTM = deleteObjectWithTimeMap.find(theObject);
  if (itDOWTM != deleteObjectWithTimeMap.end())
  {
    tmpFedTime = itDOWTM->second;
    deleteObjectWithTimeMap.erase(itDOWTM);
    delete tmpFedTime;
  }
  pm.release();
}

// ---------------------------------------------------------------------------
// Del object from the map.
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::delObject(GeRtiFactory::GeRtiHandle const &theObject)
{
  std::set <GeRtiFactory::GeRtiHandle>::iterator its;

  // Federate registered and federate deleted object.
  pm.acquire();
  its = objectsUpdated.find(theObject);
  if (its != objectsUpdated.end())
  {
    objectsUpdated.erase(its);
  }
  pm.release();

  // Peer registered and federate deleted object.
  pm.acquire();
  its = objectsReflected.find(theObject);
  if (its != objectsReflected.end())
  {
    objectsReflected.erase(its);
  }
  pm.release();

  // Deleted objects.
  pm.acquire();
  its = objectsDeleted.find(theObject);
  if (its == objectsDeleted.end())
  {
    objectsDeleted.insert(theObject);
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::FederateDB::getObjectsDeleted(void)
{
  CORBA::ULong ret;
  size_t size;

  pm.acquire();
  size = objectsDeleted.size();
  GERTICO::Mapper::mapULongSizet(ret, size);
  pm.release();
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::FederateDB::getObjectsDiscovered(void)
{
  CORBA::ULong ret;
  size_t size;

  pm.acquire();
  size = objectsDiscovered.size();
  GERTICO::Mapper::mapULongSizet(ret, size);
  pm.release();
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::FederateDB::getObjectsReflected(void)
{
  CORBA::ULong ret;
  size_t size;

  pm.acquire();
  size = objectsReflected.size();
  GERTICO::Mapper::mapULongSizet(ret, size);
  pm.release();
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::FederateDB::getObjectsRegistered(void)
{
  CORBA::ULong ret;
  size_t size;

  pm.acquire();
  size = objectsRegistered.size();
  GERTICO::Mapper::mapULongSizet(ret, size);
  pm.release();
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::FederateDB::getObjectsRemoved(void)
{
  CORBA::ULong ret;
  size_t size;

  pm.acquire();
  size = objectsRemoved.size();
  GERTICO::Mapper::mapULongSizet(ret, size);
  pm.release();
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CORBA::ULong GERTICO::FederateDB::getObjectsUpdated(void)
{
  CORBA::ULong ret;
  size_t size;

  pm.acquire();
  size = objectsUpdated.size();
  GERTICO::Mapper::mapULongSizet(ret, size);
  pm.release();
  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool GERTICO::FederateDB::process(void)
{
  bool ret;

  ret = momJobs.performJobs(true);

  return ret;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::processDeleteObjectWithTime(GERTICO::GeRtiFedTime const &theGeRtiFedTime)
{
  GERTICO::DeleteObjectWithTimeMap::iterator itDOWTM;
  GERTICO::GeRtiFedTime *tmpFedTime = NULL;

  if (deleteObjectWithTimeMap.size() == 0)
  {
    return;
  }

  pm.acquire();
  for (itDOWTM = deleteObjectWithTimeMap.begin(); itDOWTM != deleteObjectWithTimeMap.end(); )
  {
    tmpFedTime = itDOWTM->second;
    pm.release();
    if (*tmpFedTime <= theGeRtiFedTime)
    {
      runTimeObjectDB->deleteObjectInstance(itDOWTM->first, federate);
      delObject(itDOWTM->first);
      deleteObjectWithTimeMap.erase(itDOWTM);
      delete tmpFedTime;
      itDOWTM = deleteObjectWithTimeMap.begin();
    }
    else
    {
      itDOWTM++;
    }
    pm.acquire();
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::processDeleteObjectWithTime(GERTICO::GeRtiFedTime const &theGeRtiFedTime, GeRtiFactory::GeRtiHandle const &theObject)
{
  GERTICO::DeleteObjectWithTimeMap::iterator itDOWTM;

  pm.acquire();
  itDOWTM = deleteObjectWithTimeMap.find(theObject);
  if (itDOWTM != deleteObjectWithTimeMap.end())
  {
    std::auto_ptr<GERTICO::GeRtiFedTime> tmpFedTime(itDOWTM->second);
    pm.release();
    if (*tmpFedTime <= theGeRtiFedTime)
    {
      runTimeObjectDB->deleteObjectInstance(theObject, federate);
      delObject(theObject);
      deleteObjectWithTimeMap.erase(itDOWTM);
    }
    else
    {
      // The delete object with times mMap keeps the memory pointer.
      tmpFedTime.release();
    }
    pm.acquire();
  }
  pm.release();
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void GERTICO::FederateDB::reset(void)
{
  pm.acquire();
  objectsReflected.clear();
  objectsUpdated.clear();
  pm.release();
  if (runTimeObjectDB)
  {
    runTimeObjectDB->clear();
  }
  clear();
}
