/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** EventMarket/main.cpp
**
*******************************************************************************/

#include <stdlib.h>
#include <exception>
#include <stdexcept>
#include "ace/Get_Opt.h"

#include "VersionX.h"
#include "Util/GeRtiOrb.h"
#ifdef IEEE_1516
#endif
#include "main.h"
#include "ace/Service_Config.h"
#include "ace/Thread_Manager.h"

/********************************* Gal begin *********************************/
#ifdef GalDebug
#include "Gal/StdAfx.h"
#include "Gal/repository_l.h"
#include "Gal/event.h"

static class Repository_l *rpGal=(Repository::getSingleInstance())->getRepository_l("gertimain.res","gertimain");
static class Event *r_m=rpGal->getRefEvent("r_m");
static class Event *r_d=rpGal->getRefEvent("r_d");
static class Event *r_e=rpGal->getRefEvent("r_e");
static class Event *r_i=rpGal->getRefEvent("r_i");
static class Event *r_w=rpGal->getRefEvent("r_w");
#endif
/*********************************** Gal end *********************************/

struct Arg
{
  ACE_Barrier *barrier;
  GERTICO::GeRtiOrb *myGeRtiOrb;
};

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *bestEffort_worker(void *arg)
{
  Arg *myArg = (Arg *) arg;

  try
  {
    myArg->barrier->wait();
    myArg->myGeRtiOrb->orbSenderBestEffort->run();
  }
  catch(...)
  {
    return(void *) 1;
  }
  return(void *) 0;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void *server_worker(void *arg)
{
  Arg *myArg = (Arg *) arg;

  try
  {
    myArg->barrier->wait();
#ifdef SenderDEBUG
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "server_worker::orb::run");
                           #endif   // inserted by Gal converter
#endif
    myArg->myGeRtiOrb->orbReceiver->run();
/*
    while (doMore)
    {
      if (orb->work_pending())
      {
        orb->perform_work();
        continue;
      }
      usleep(10);
    }
*/
  }
  catch(...)
  {
    return(void *) 1;
  }
  return(void *) 0;
}

mainServer::mainServer() : factory("Factory")
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "mainServer::mainServer::enter");
                           #endif   // inserted by Gal converter
  char *hubName;

  hubName = getenv("HUB_NAME");
  if (hubName)
  {
    GERTICO::Mapper::mapWstringFromChar(ws, hubName);
  }
  else
  {
    GERTICO::Mapper::mapWstringFromChar(ws, "a");
  }
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "mainServer::mainServer::leave");
                           #endif   // inserted by Gal converter
}

mainServer::~mainServer()
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "mainServer::~mainServer::enter");
                           #endif   // inserted by Gal converter
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "mainServer::~mainServer::leave");
                           #endif   // inserted by Gal converter
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
bool mainServer::getGertiDirectory(CosNaming::Name const &theDirectoryName)
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "mainServer::getGertiDirectory::enter");
                           #endif   // inserted by Gal converter
  try
  {
    gertiObj = myGeRtiOrb->getRootContext()->resolve(theDirectoryName);
  }
  catch(CosNaming::NamingContext::NotFound ex)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_e, "mainServer::getGertiDirectory::NamingContext::NotFound");
                           #endif   // inserted by Gal converter
    return true;
  }
  catch(...)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_e, "mainServer::getGertiDirectory::NamingContext::CatchAllException");
                           #endif   // inserted by Gal converter
    return true;
  }

                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "mainServer::getGertiDirectory::leave");
                           #endif   // inserted by Gal converter
  return false;
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
int mainServer::init()
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "mainServer::init::enter");
                           #endif   // inserted by Gal converter
  CORBA::Object_var rti_obj;
  CosNaming::Name bindName;
#ifdef IEEE_1516
  RTI::LogicalTimeFactory *myLogicalTimeFactory;
  RTI::LogicalTimeIntervalFactory *myLogicalTimeIntervalFactory;
#endif
  char *file_xml = "GERTICOconf.xml";
  char buff[256];

  char *gertico = getenv("GERTICO");
  if (gertico == NULL)
  {
    strcpy(buff, file_xml);
  }
  else
  {
    sprintf(buff, "%s/%s", gertico, file_xml);
  }

  string filename(buff);

  // Read configuration file.
  conf = GERTICOconf::parseFromFile(filename);
  if (conf == NULL)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_e, "mainServer::init::CannotParseFromFile");
                           #endif   // inserted by Gal converter
    return 1;
  }

#ifdef IEEE_1516
  int retval = dll.open(conf->logicalTimeLibrary.c_str(), ACE_DEFAULT_SHLIB_MODE, 1);
  if (retval)
  {
    return 1;
  }

  typedef RTI::LogicalTimeFactory * (*fctTime)();
  typedef RTI::LogicalTimeIntervalFactory * (*fctTimeInterval)();
  fctTime d = (fctTime) dll.symbol("getLogicalTimeFactory", 0);
  if (!d)
  {
    return 1;
  }

  fctTimeInterval e = (fctTimeInterval) dll.symbol("getLogicalTimeIntervalFactory", 0);
  if (!e)
  {
    return 1;
  }

  myLogicalTimeFactory = (*d)();
  myLogicalTimeIntervalFactory = (*e)();
  geRtiFedTimeFactory = new GERTICO::GeRtiFedTimeFactory(*myLogicalTimeFactory, *myLogicalTimeIntervalFactory);
  geRtiLogicalTimeIntervalFactory = new GERTICO::GeRtiLogicalTimeIntervalFactory(*myLogicalTimeIntervalFactory);
#else
  geRtiFedTimeFactory = new GERTICO::GeRtiFedTimeFactory();
  geRtiLogicalTimeIntervalFactory = new GERTICO::GeRtiLogicalTimeIntervalFactory();
#endif

  name = ACE_OS::strdup(conf->ns->rootEntry);

  try
  {
    myGeRtiOrb = new GERTICO::GeRtiOrb(*conf);
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception");
    return 1;
  }
  catch(...)
  {
    return 1;
  }

  bindName.length(1);
  bindName[0].id = CORBA::string_dup(name);
  bindName[0].kind = CORBA::string_dup("");

  if (getGertiDirectory(bindName))
  {
    return 1;
  }

  gerti_context = CosNaming::NamingContext::_narrow(gertiObj);

  try
  {
    bindName.length(1);
    bindName[0].id = CORBA::string_dup("Factory");
    bindName[0].kind = CORBA::string_dup("");

    rti_obj = gerti_context->resolve(bindName);

    theFactoryVar = GeRtiFactory::TheFactory::_narrow(rti_obj);

    if (CORBA::is_nil(theFactoryVar.in()))
    {
      std::cerr << "getFactory: theFactoryVar" << std::endl;
    }
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception");
    return 1;
  }
  catch(...)
  {
    CORBA::WChar *wChar = L"resolve error";
    throw GeRtiFactory::RTIinternalError(wChar);
  }

  theEventHubFederationFactory = new GeRtiFactory_TheEventHubFederationFactoryEC_i(ws, *myGeRtiOrb, *conf, *geRtiFedTimeFactory, *geRtiLogicalTimeIntervalFactory);

                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "mainServer::init::leave");
                           #endif   // inserted by Gal converter
  return 0;
}

int mainServer::run()
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "mainServer::run::enter");
                           #endif   // inserted by Gal converter
  ACE_Barrier *barrier;
  ACE_thread_t tid;
  ACE_thread_t tid0;
  Arg arg;

  try
  {
    theEventHubFederationFactoryVar = theEventHubFederationFactory->_this();

    theFactoryVar->registerEventHubFactory(ws.c_str(), theEventHubFederationFactoryVar);

                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_m, "Server is running");
                           #endif   // inserted by Gal converter

    barrier = new ACE_Barrier(3);
    arg.barrier = barrier;
    arg.myGeRtiOrb = myGeRtiOrb;
    tid = ACE_Thread_Manager::instance()->spawn(ACE_reinterpret_cast(ACE_THR_FUNC, &server_worker), &arg);
    tid0 = ACE_Thread_Manager::instance()->spawn(ACE_reinterpret_cast(ACE_THR_FUNC, &bestEffort_worker), &arg);
    barrier->wait();
    ACE_Thread_Manager::instance()->wait_grp(tid);
    ACE_Thread_Manager::instance()->wait_grp(tid0);
  }
  catch(CosNaming::NamingContext::NotFound ex)
  {
    ACE_ERROR_RETURN((LM_ERROR, "Unable to bind %s NotFound\n", name), -1);
  }
  catch(CosNaming::NamingContext::InvalidName ex)
  {
    ACE_ERROR_RETURN((LM_ERROR, "Unable to bind %s InvalidName \n", name), -1);
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception");
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_e, "mainServer::run::SystemException");
                           #endif   // inserted by Gal converter
    return 1;
  }
  catch(CORBA::UserException &userex)
  {
    ACE_PRINT_EXCEPTION(userex, "User Exception");
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_e, "mainServer::run::UserException");
                           #endif   // inserted by Gal converter
    return 1;
  }
  catch(...)
  {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_e, "mainServer::run::CatchAllException");
                           #endif   // inserted by Gal converter
    return 1;
  }

                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "mainServer::run::leave");
                           #endif   // inserted by Gal converter
  return 0;
}

void terminateGERTICO()
{
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "terminateGERTICO");
                           #endif   // inserted by Gal converter
  exit(-1);
}

int main(int argc, char* argv[])
{
  char buf[512];
//  std::set_terminate(terminateGERTICO);

/******************************* Gal begin **********************************/
#ifdef GalDebug

  char *t;
  class Repository *repository=Repository::getSingleInstance();

  t=repository->init("HUB.res");
  if(t)
    printf("%s\n",t);

#endif
/******************************* Gal end ************************************/

  mainServer server;

  sprintf(buf, "%s.%s", gerticoVersion, Revision);
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_m,buf);
                             E1(r_m,"Starting Event Hub server");
                           #endif   // inserted by Gal converter

  try
  {
    if (server.init())
    {
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_e, "main::server::init::Exception");
                           #endif   // inserted by Gal converter
      return 1;
    }

    server.run();
  }
  catch(CORBA::UserException &userex)
  {
    ACE_PRINT_EXCEPTION(userex, "User Exception in main");
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_e, "main::server::UserException");
                           #endif   // inserted by Gal converter
    return -1;
  }
  catch(CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION(sysex, "System Exception in main ");
                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_e, "main::server::SystenException");
                           #endif   // inserted by Gal converter
    return -1;
  }

                           #ifdef GalDebug   // inserted by Gal converter
                             E1(r_d, "main::leave");
                           #endif   // inserted by Gal converter
  return 0;
}


