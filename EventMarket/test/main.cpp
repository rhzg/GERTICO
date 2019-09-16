/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: hzg $
$Name $
$Log: main.cpp,v $
Revision 1.18  2005/01/28 08:42:32  hzg
merging gertico_0_16b_fix into main thread

Revision 1.17.2.1  2005/01/27 10:22:11  hzg
bug fix concerning include and std usage
requred for using ACE-5.4+TAO-1.4

Revision 1.17  2004/10/04 15:12:45  mul
Remove unused class level.

Revision 1.16  2004/10/01 10:05:09  mul
Minor changes.

Revision 1.15  2004/05/28 12:05:13  mul
Fix includes.

Revision 1.14  2004/04/19 15:02:17  mul
Minor changes.

Revision 1.13  2004/03/17 13:49:50  mul
Changes due to persistent database logic.

Revision 1.12  2003/10/10 13:37:01  mul
New ORB init logic.

Revision 1.11  2003/10/02 08:50:56  mul
Fix usage of supporting services implicit activation.

Revision 1.10  2003/09/23 10:26:09  mul
Extensions for DDM.

Revision 1.9  2003/08/20 13:52:58  mul
Use config file settings to locate name service.

Revision 1.8  2003/08/15 07:56:31  hzg
use DataModel instead of OMT

Revision 1.7  2003/08/14 15:24:45  mul
Use a child POA for gertico objects.

Revision 1.6  2003/08/08 12:58:53  mul
Logic for new fed file parser.

Revision 1.5  2003/05/27 15:01:06  mul
Use include paths starting in $GERTICO.

Revision 1.4  2002/12/20 10:02:38  mul
Fix some minor changes.

Revision 1.3  2002/11/20 08:49:00  hzg
OMT included

Revision 1.2  2002/10/21 12:45:19  mul
Logic to clean up deleted CORBA objects.

Revision 1.1  2002/09/11 15:12:38  mul
Changed logic for the use of name service: a singleton to get NS root.

Revision 1.8  2002/07/24 06:35:48  hzg
NamingService entry EC changed

Revision 1.7  2002/07/23 14:50:34  hzg
Modifications and corrections for RTBenchmark
fine tuning of Makefile logic

Revision 1.6  2002/07/16 08:57:20  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#include "ace/Get_Opt.h"
#include "ace/Thread_Manager.h"
#include "Util/GeRtiOrb.h"
#include "Util/DataModel.h"
#include "OMT_XML/GERTICOconf.h"
#include "main.h"

#include <iostream>
using namespace std;

#define EC "EventChannel"

static ACE_Barrier barrier(2);
GERTICO::GeRtiOrb *theGeRtiOrb;

void *server_worker (void *arg)
{
  ACE_Barrier *myBarrier = (ACE_Barrier *) arg;
 
  try
  {
    myBarrier->wait ();
    cerr << "server_worker orb->run()" << endl;
    theGeRtiOrb->orb->run ();
  }
  catch (...)
  {
    cerr << "Uncaught CORBA exception" << endl;
    return (void *) 1;
  }

  cerr << "server_worker done" << endl;
  return (void *) 0;
}

mainServer::mainServer ()
{
  GERTICOconf *conf;

  char *file_xml = "GERTICOconf.xml";
  char buff[256];
  char nsORBInitRef[512];
 
  ps = new ACE_Semaphore (1);
  char *gertico = getenv ("GERTICO");
  if (gertico == NULL)
  {
    strcpy (buff, file_xml);
  }
  else
  {
    sprintf (buff, "%s/%s", gertico, file_xml);
  }
 
  string filename (buff);
 
  // Read configuration file.
  conf = GERTICOconf::parseFromFile (filename);
 
  name = conf->ns->rootEntry;
  sprintf (nsORBInitRef, "-ORBInitRef NameService=%s/NameService", conf->ns->endPoint);
  argc_ = 1;
  argv_ = new char*[argc_];
  argv_[0] = nsORBInitRef;

  myGeRtiOrb = new GERTICO::GeRtiOrb (argc_, argv_, "gertiorb");
  theGeRtiOrb = myGeRtiOrb;
}

mainServer::~mainServer ()
{
  delete ss;
}

int mainServer::init ()
{
  CORBA::Object_var gertiObj;
  CosNaming::Name bindName;
  CosNaming::NamingContext_ptr namingContext;

  bindName.length (3);
  bindName.length (1);
  bindName[0].id = CORBA::string_dup (name);
  bindName[0].kind = CORBA::string_dup ("");

  try
  {
    gertiObj = myGeRtiOrb->getRootContext()->resolve (bindName);
  }
  catch (CosNaming::NamingContext::NotFound ex)
  {
    try
    {
      gertiObj = myGeRtiOrb->getRootContext()->bind_new_context (bindName);
    }
    catch (...)
    {
      cout << "catch (...) bind_new_context" << endl;
      return 1;
    }
  }
  catch (...)
  {
    cout << "init catch(...): NS resolve " << name << " context" << endl;
    return 1;
  }

  bindName.length (2);
  bindName[1].id = CORBA::string_dup ("ECtest");
  bindName[1].kind = CORBA::string_dup ("");

  try
  {
    gertiObj = myGeRtiOrb->getRootContext()->resolve (bindName);
    namingContext = CosNaming::NamingContext::_narrow (gertiObj);
  }
  catch (CosNaming::NamingContext::NotFound ex)
  {
    try
    {
      gertiObj = myGeRtiOrb->getRootContext()->bind_new_context (bindName);
    }
    catch (...)
    {
      cout << "catch (...) bind_new_context" << endl;
      return 1;
    }
  }
  catch (...)
  {
    cout << "init catch(...): NS resolve " << name << " context" << endl;
    return 1;
  }

  // read OMT File
  string fedFile ("HelloWorld.fed");
  string federationName ("A");
  GERTICO::NextHandle idHandler;
  persistentDB = new GERTICO::PersistentDB (*myGeRtiOrb, fedFile, federationName, idHandler, namingContext);

  eventHandler = new EventHandler (*persistentDB, *ps);
  consumerAdmin = new GeRtiEventMarket_MarketConsumerAdmin_i (*myGeRtiOrb, eventHandler);
  supplierAdmin = new GeRtiEventMarket_MarketSupplierAdmin_i (*myGeRtiOrb, eventHandler);
  ss = new GeRtiFactory_SupportingServices_i (*myGeRtiOrb, *persistentDB);

  try
  {
    bindName.length (3);
    bindName[2].id = CORBA::string_dup ("consumerAdmin");
    bindName[2].kind = CORBA::string_dup ("");
    myGeRtiOrb->getRootContext()->rebind (bindName, consumerAdmin->consumerAdminPtr);

    bindName[2].id = CORBA::string_dup ("supplierAdmin");
    bindName[2].kind = CORBA::string_dup ("");
    myGeRtiOrb->getRootContext()->rebind (bindName, supplierAdmin->supplierAdminPtr);

    bindName[2].id = CORBA::string_dup ("supportServices");
    bindName[2].kind = CORBA::string_dup ("");
    myGeRtiOrb->getRootContext()->rebind (bindName, GeRtiFactory::SupportingServices::_duplicate (ss->ssPtr));
  }
  catch (CosNaming::NamingContext::NotFound ex)
  {
    ACE_ERROR_RETURN ((LM_ERROR, "Unable to bind %s NotFound\n", argv_[1]), -1);
    cout << "NotFound," << endl;
  }
  catch (CosNaming::NamingContext::InvalidName ex)
  {
    ACE_ERROR_RETURN ((LM_ERROR, "Unable to bind %s InvalidName \n", argv_[1]), -1);
    cout << "InvalidName" << endl;
  }
  catch (CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION (sysex, "System Exception");
    cout << "System Exception" << endl;
    return 1;
  }
  catch (CORBA::UserException &userex)
  {
    ACE_PRINT_EXCEPTION (userex, "User Exception");
    cout << "User Exception" << endl;
    return 1;
  }
  catch (...)
  {
    cout << "catch (...)" << endl;
    return 1;
  }
  return 0;
}

// Parses the command line arguments and returns an error status.
int mainServer::parse_args (int argc, char **argv)
{
  int i;

/*
  if (argc != 1)
  {
    cout << "Usage: " << argv[0] << endl;
    return 1;
  }
*/

  argc_ = argc;
  argv_ = new char *[argc];
  for (i = 0; i < argc; i++)
    argv_[i] = argv[i];

  // Indicates successful parsing of command line.
  return 0;
}

void mainServer::run (void)
{
  int i;

  for (i = 0; i < 10; )
  {
    cout << "Process" << endl;
    eventHandler->f_processEvents ();
    sleep (1);
  }
}

int main (int argc, char* argv[])
{
  mainServer server;

  cout << "Starting GERTICO server" << endl;

  if (server.parse_args (argc, argv))
  {
    return 1;
  }

  try
  {
    if (server.init ())
    {
      return 1;
    }

    ACE_Thread_Manager::instance()->spawn (ACE_reinterpret_cast (ACE_THR_FUNC, &server_worker), &barrier);
    barrier.wait ();
    ACE_OS::sleep (1);

    server.run ();
  }
  catch (CORBA::UserException &userex)
  {
    //ACE_UNUSED_ARG (userex);
    ACE_PRINT_EXCEPTION (userex, "User Exception in main");
    return -1;
  }
  catch (CORBA::SystemException &sysex)
  {
    //ACE_UNUSED_ARG (sysex);
    ACE_PRINT_EXCEPTION (sysex, "System Exception in main ");
    return -1;
  }

  return 0;
}
