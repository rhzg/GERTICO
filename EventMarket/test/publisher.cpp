/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: hzg $
$Name $
$Log: publisher.cpp,v $
Revision 1.8  2005/01/28 08:42:32  hzg
merging gertico_0_16b_fix into main thread

Revision 1.7.2.1  2005/01/27 10:22:11  hzg
bug fix concerning include and std usage
requred for using ACE-5.4+TAO-1.4

Revision 1.7  2003/10/10 13:36:07  mul
New ORB init logic.

Revision 1.6  2003/08/20 13:55:14  mul
Use config file settings to locate name service.

Revision 1.5  2003/08/14 15:24:45  mul
Use a child POA for gertico objects.

Revision 1.4  2003/06/10 13:26:55  hzg
sleep

Revision 1.3  2003/05/27 15:01:07  mul
Use include paths starting in $GERTICO.

Revision 1.2  2002/12/20 10:01:33  mul
Fix some minor problems.

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
#include "publisher.h"

#include <iostream>
using namespace std;

mainPublisher::mainPublisher ()
{
  char *file_xml = "GERTICOconf.xml";
  char buff[256];
  char nsORBInitRef[512];
 
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
}

mainPublisher::~mainPublisher ()
{
}

// Parses the command line arguments and returns an error status.
int mainPublisher::parse_args (int argc, char **argv)
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

int mainPublisher::run ()
{
  CosNaming::Name bindName;
  GeRtiEventMarket::Events e;
  GeRtiEventMarket::ProxyPushConsumer_ptr ps;
  unsigned long h;

  cout << "A" << endl;
  h = ssVar->getObjectClassHandle ("Country");
  cout << "h " << h << endl;
  ps = supplierAdminVar->obtain_push_consumer (h);

  e.length (1);
  e[0].type = GeRtiEventMarket::obj;
  e[0].source = 101;
  e[0].timestamp = 10.1;
  e[0].data.length (1);
  e[0].data[0].id = 7;
  e[0].data[0].value.length (1);
  e[0].data[0].value[0] = 9;
  e[0].obj = 9;
  e[0]._cxx_class = h;
  try
  {
    cout << "Server is running" << endl;

    for (int i = 0; i < 100000; i++)
    {
      ps->push (e);
      ACE_OS::sleep (ACE_Time_Value(0,500));
    }
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

int mainPublisher::getRoot ()
{
  CosNaming::Name bindName;
  CORBA::Object_ptr gertiObj;

  bindName.length (3);
  bindName[0].id = CORBA::string_dup (name);
  bindName[0].kind = CORBA::string_dup ("");
  bindName[1].id = CORBA::string_dup ("ECtest");
  bindName[1].kind = CORBA::string_dup ("");
  bindName[2].id = CORBA::string_dup ("supportServices");
  bindName[2].kind = CORBA::string_dup ("");

  try
  {
    gertiObj = myGeRtiOrb->getRootContext()->resolve (bindName);
    ssVar = GeRtiFactory::SupportingServices::_narrow (gertiObj);
  }
  catch (CosNaming::NamingContext::NotFound ex)
  {
    cout << "getRoot: catch (CosNaming::NamingContext::NotFound)" << endl;
    return 1;
  }
  catch (...)
  {
    cout << "getRoot: catch (...)" << endl;
    return 1;
  }


  bindName[2].id = CORBA::string_dup ("supplierAdmin");
  bindName[2].kind = CORBA::string_dup ("");

  try
  {
    gertiObj = myGeRtiOrb->getRootContext()->resolve (bindName);
    supplierAdminVar = GeRtiEventMarket::MarketSupplierAdmin::_narrow (gertiObj);
  }
  catch (CosNaming::NamingContext::NotFound ex)
  {
    cout << "getRoot: catch (CosNaming::NamingContext::NotFound)" << endl;
    return 1;
  }
  catch (...)
  {
    cout << "getRoot: catch (...)" << endl;
    return 1;
  }

  return 0;
}

int main (int argc, char* argv[])
{
  mainPublisher publisher;
  string fedFile ("HelloWorld.fed");

  cout << "Starting event channel publisher" << endl;

  if (publisher.parse_args (argc, argv))
  {
    return 1;
  }

  try
  {
    if (publisher.getRoot ())
    {
      return 1;
    }

    cout << "Running ..." << endl;
    publisher.run ();
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
