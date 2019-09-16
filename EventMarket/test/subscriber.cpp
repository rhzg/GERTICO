/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: subscriber.cpp,v $
Revision 1.12  2003/10/10 13:35:26  mul
New ORB init logic.

Revision 1.11  2003/10/07 07:49:27  hzg
GeRtiFactory::RTIinternalError with reason string

Revision 1.10  2003/10/02 08:49:15  mul
Add test of non-zero childPOA.

Revision 1.9  2003/08/20 13:59:04  mul
Use config file settings to locate name service.

Revision 1.8  2003/08/14 15:24:45  mul
Use a child POA for gertico objects.

Revision 1.7  2003/05/27 15:01:07  mul
Use include paths starting in $GERTICO.

Revision 1.6  2003/05/20 08:40:11  mul
Remove old style logging.

Revision 1.5  2003/02/11 14:22:35  mul
Extend supporting services test for getParameterName.

Revision 1.4  2002/12/20 10:01:01  mul
Fix some minor problems.

Revision 1.3  2002/10/02 10:39:05  mul
Fix logic for tags in updates.

Revision 1.2  2002/09/24 10:13:44  mul
Fix recursive search of attribute/parameter names.

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
#include "subscriber.h"

// Implementation skeleton constructor
PushConsumer_i::PushConsumer_i (GERTICO::GeRtiOrb &theGeRtiOrb) : myGeRtiOrb (theGeRtiOrb)
{
}
 
// Implementation skeleton destructor
PushConsumer_i::~PushConsumer_i (void)
{
}

PortableServer::POA_ptr PushConsumer_i::_default_POA (void)
{
  return PortableServer::POA::_duplicate (myGeRtiOrb.childPOA);
}
 
void PushConsumer_i::push
(
  const GeRtiEventMarket::Events & e
)
throw
(
  CORBA::SystemException
)
{
CORBA::ULong len;
static CORBA::ULong Sum = 0;
len = e.length();
Sum += len;

#ifdef GeRtiEventMarketDEBUG
std::cout << "################### " << len << std::std::endl;
for (CORBA::ULong i=0; i<len; i++)
{
  std::cout << "###################======= " << e[i].data.length() << std::endl;
  for (CORBA::ULong j=0; j<e[i].data.length(); j++)
  {
    std::cout << "###################=======$$$$$$$ " << e[i].data[j].value.length()
<< std::endl;
  }
}
#endif
}
 
void PushConsumer_i::disconnect_push_consumer (
)
throw
(
  CORBA::SystemException
)
 
{
  //Add your implementation here
}

mainSubscriber::mainSubscriber ()
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

  pc = new PushConsumer_i (*myGeRtiOrb);
}

mainSubscriber::~mainSubscriber ()
{
}

int mainSubscriber::init ()
{
  CORBA::Object_ptr gertiObj;
  CosNaming::Name bindName;

  bindName.length (3);
  bindName[0].id = CORBA::string_dup (name);
  bindName[0].kind = CORBA::string_dup ("");
  bindName[1].id = CORBA::string_dup ("ECtest");
  bindName[1].kind = CORBA::string_dup ("");

  bindName[2].id = CORBA::string_dup ("supportServices");
  try
  {
    gertiObj = myGeRtiOrb->getRootContext()->resolve (bindName);
    ssVar = GeRtiFactory::SupportingServices::_narrow (gertiObj);
  }
  catch (CosNaming::NamingContext::NotFound ex)
  {
    std::cout << "init: catch (CosNaming::NamingContext::NotFound)" << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cout << "init: catch (...)" << std::endl;
    return 1;
  }

  bindName[2].id = CORBA::string_dup ("consumerAdmin");
  try
  {
    gertiObj = myGeRtiOrb->getRootContext()->resolve (bindName);
    consumerAdminVar = GeRtiEventMarket::MarketConsumerAdmin::_narrow (gertiObj);
  }
  catch (CosNaming::NamingContext::NotFound ex)
  {
    std::cout << "init: catch (CosNaming::NamingContext::NotFound)" << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cout << "init: catch (...)" << std::endl;
    return 1;
  }

  pcPtr = pc->_this ();

  return 0;
}

// Parses the command line arguments and returns an error status.
int mainSubscriber::parse_args (int argc, char **argv)
{
  int i;

  argc_ = argc;
  argv_ = new char *[argc];
  for (i = 0; i < argc; i++)
    argv_[i] = argv[i];

  // Indicates successful parsing of command line.
  return 0;
}

int mainSubscriber::run ()
{
  CosNaming::Name bindName;
  GeRtiEventMarket::ProxyPushSupplier_ptr ps;
  char *name;
  unsigned long h;
  unsigned long h1;
  unsigned long h2;

  h = ssVar->getInteractionClassHandle ("Manager.Federate");  
  std::cout << "h " << h << std::endl;
  h1 = ssVar->getParameterHandle ("Federate", h);  
  std::cout << "h1 " << h1 << std::endl;
  name = ssVar->getParameterName (h1, h);  
  std::cout << "name " << name << std::endl;
  h = ssVar->getObjectClassHandle ("Country");
  std::cout << "h " << h << std::endl;
  h1 = ssVar->getAttributeHandle ("Name", h);
  std::cout << "h1 " << h1 << std::endl;
  h1 = ssVar->getAttributeHandle ("Population", h);
  std::cout << "h1 " << h1 << std::endl;
  name = ssVar->getAttributeName (h1, h);
  std::cout << "name " << name << std::endl;
  try
  {
    h2 = ssVar->getAttributeHandle ("dirt", h);
  }
  catch (GeRtiFactory::NameNotFound)
  {
    std::cout << "Test passed" << std::endl;
  }
  try
  {
    name = ssVar->getAttributeName (9999, h);
  }
  catch (GeRtiFactory::AttributeNotDefined)
  {
    std::cout << "Test passed" << std::endl;
  }
  h1 = ssVar->getRoutingSpaceHandle ("thefinalfrontier");
  std::cout << "thefinalfrontier " << h1 << std::endl;
  name = ssVar->getRoutingSpaceName (h1);
  std::cout << "name " << name << std::endl;
  h2 = ssVar->getDimensionHandle ("x", h1);
  std::cout << "x " << h2 << std::endl;
  name = ssVar->getDimensionName (h2, h1);
  std::cout << "name " << name << std::endl;
  h2 = ssVar->getDimensionHandle ("y", h1);
  std::cout << "y " << h2 << std::endl;
  name = ssVar->getDimensionName (h2, h1);
  std::cout << "name " << name << std::endl;
  h2 = ssVar->getDimensionHandle ("z", h1);
  std::cout << "z " << h2 << std::endl;
  name = ssVar->getDimensionName (h2, h1);
  std::cout << "name " << name << std::endl;
  h2 = ssVar->getDimensionHandle ("time", h1);
  std::cout << "time " << h2 << std::endl;
  name = ssVar->getDimensionName (h2, h1);
  std::cout << "name " << name << std::endl;
  ps = consumerAdminVar->obtain_push_supplier (h, 100);
  ps->connect_push_consumer (pcPtr);

  try
  {
    std::cout << "Server is running" << std::endl;

    myGeRtiOrb->orb->run ();
  }
  catch (CosNaming::NamingContext::NotFound ex)
  {
    ACE_ERROR_RETURN ((LM_ERROR, "Unable to bind %s NotFound\n", argv_[1]), -1);
    std::cout << "NotFound," << std::endl;
  }
  catch (CosNaming::NamingContext::InvalidName ex)
  {
    ACE_ERROR_RETURN ((LM_ERROR, "Unable to bind %s InvalidName \n", argv_[1]), -1);
    std::cout << "InvalidName" << std::endl;
  }
  catch (CORBA::SystemException &sysex)
  {
    ACE_PRINT_EXCEPTION (sysex, "System Exception");
    std::cout << "System Exception" << std::endl;
    return 1;
  }
  catch (CORBA::UserException &userex)
  {
    ACE_PRINT_EXCEPTION (userex, "User Exception");
    std::cout << "User Exception" << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cout << "catch (...)" << std::endl;
    return 1;
  }

  return 0;
}

int main (int argc, char* argv[])
{
  mainSubscriber subscriber;
  string fedFile ("HelloWorld.fed");

  std::cout << "Starting event channel subscriber" << std::endl;

  if (subscriber.parse_args (argc, argv))
  {
    return 1;
  }

  try
  {
    if (subscriber.init () == -1)
    {
      return 1;
    }

    std::cout << "Running ..." << std::endl;
    subscriber.run ();
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
