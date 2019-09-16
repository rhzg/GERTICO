/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
**  GeRtiOrb.cpp
**
*******************************************************************************/

#include <ace/OS.h>
#include "tao/Messaging/Messaging.h"
#include <tao/TAO_Internal.h>
#include "GeRtiOrb.h"

#include <iostream>

unsigned int GERTICO::GeRtiOrb::GERTICO_ORB_init_counter = 0;

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::GeRtiOrb::GeRtiOrb(GERTICOconf &conf)
{
  CORBA::Any orb_level;
  CORBA::Any orb_levelSender;
  CORBA::Object_var objectPolicyBestEffort;
  CORBA::Object_var objectPolicySender;
  CORBA::Object_var objectPolicyManagerBestEffort;
  CORBA::Object_var objectPolicyManagerSender;
  CORBA::PolicyList policy_listBestEffort;
  CORBA::PolicyList policy_listSender;
  char **argvBestEffort_;
  char **argvReceiver_;
  char **argvSender_;
  char dummy[16];
  char hostname[256];
  char ORBInitRef[256];
  char nsORBInitRef[256];
  char orbid[64];
  int argcBestEffort_;
  int argcReceiver_;
  int argcSender_;
  root_context = NULL;

  ACE_OS::hostname(hostname,256);
  strcpy(dummy, "dummy");

  // Orb init
  argcReceiver_ = 3;
  argvReceiver_ = new char*[argcReceiver_];
  argvReceiver_[0] = dummy;
  strcpy(ORBInitRef, "-ORBInitRef");
  argvReceiver_[1] = ORBInitRef;
  ACE_OS::sprintf(nsORBInitRef, "NameService=%s/NameService", conf.ns->endPoint);
  argvReceiver_[2] = nsORBInitRef;
  ACE_OS::sprintf(orbid, "orb:%d", GERTICO_ORB_init_counter++);
  orbReceiver = CORBA::ORB_init(argcReceiver_, argvReceiver_, orbid);

  argcSender_ = 3;
  argvSender_ = new char*[argcSender_];
  argvSender_[0] = dummy;
  strcpy(ORBInitRef, "-ORBInitRef");
  argvSender_[1] = ORBInitRef;
  ACE_OS::sprintf(nsORBInitRef, "NameService=%s/NameService", conf.ns->endPoint);
  argvSender_[2] = nsORBInitRef;
  ACE_OS::sprintf(orbid, "orb:%d", GERTICO_ORB_init_counter++);
  orbSenderReliable = CORBA::ORB_init(argcSender_, argvSender_, orbid);

  argcBestEffort_ = 3;
  argvBestEffort_ = new char*[argcBestEffort_];
  argvBestEffort_[0] = dummy;
  strcpy(ORBInitRef, "-ORBInitRef");
  argvBestEffort_[1] = ORBInitRef;
  ACE_OS::sprintf(nsORBInitRef, "NameService=%s/NameService", conf.ns->endPoint);
  argvBestEffort_[2] = nsORBInitRef;
//  argvBestEffort_[2] = CORBA::string_dup("-ORBListenEndpoints");
//  argvBestEffort_[3] = CORBA::string_alloc(100);
//  ACE_OS::sprintf(argvBestEffort_[3], "iiop://%s:1306", hostname);
  ACE_OS::sprintf(orbid, "orb:%d", GERTICO_ORB_init_counter++);
  orbSenderBestEffort = CORBA::ORB_init(argcBestEffort_, argvBestEffort_, orbid);

  // Set sync scope
  objectPolicyManagerBestEffort = orbSenderBestEffort->resolve_initial_references("ORBPolicyManager");
  CORBA::PolicyManager_var policy_managerBestEffort = CORBA::PolicyManager::_narrow(objectPolicyManagerBestEffort.in());
  objectPolicyBestEffort = orbSenderBestEffort->resolve_initial_references("PolicyCurrent");
  CORBA::PolicyCurrent_var policy_currentBestEffort = CORBA::PolicyCurrent::_narrow(objectPolicyBestEffort.in());
  orb_level <<= Messaging::SYNC_NONE;
  policy_listBestEffort.length(0);
  policy_managerBestEffort->set_policy_overrides(policy_listBestEffort, CORBA::SET_OVERRIDE);
  policy_listBestEffort.length(1);
  policy_listBestEffort[0] = orbSenderBestEffort->create_policy(Messaging::SYNC_SCOPE_POLICY_TYPE, orb_level);
  policy_managerBestEffort->set_policy_overrides(policy_listBestEffort, CORBA::ADD_OVERRIDE);
//  policy_managerBestEffort->set_policy_overrides(policy_listBestEffort, CORBA::SET_OVERRIDE);
  // We are now done with these policies.
  policy_listBestEffort[0]->destroy();

  objectPolicyManagerSender = orbSenderReliable->resolve_initial_references("ORBPolicyManager");
  CORBA::PolicyManager_var policy_managerSender = CORBA::PolicyManager::_narrow(objectPolicyManagerSender.in());
  objectPolicySender = orbSenderReliable->resolve_initial_references("PolicyCurrent");
  CORBA::PolicyCurrent_var policy_currentSender = CORBA::PolicyCurrent::_narrow(objectPolicySender.in());
  if (conf.syncScope == "SYNC_NONE")
  {
    orb_levelSender <<= Messaging::SYNC_NONE;
  }
  if (conf.syncScope == "SYNC_WITH_TRANSPORT")
  {
    orb_levelSender <<= Messaging::SYNC_WITH_TRANSPORT;
  }
  if (conf.syncScope == "SYNC_WITH_SERVER")
  {
    orb_levelSender <<= Messaging::SYNC_WITH_SERVER;
  }
  if (conf.syncScope == "SYNC_WITH_TARGET")
  {
    orb_levelSender <<= Messaging::SYNC_WITH_TARGET;
  }
  policy_listSender.length(0);
  policy_managerSender->set_policy_overrides(policy_listSender, CORBA::SET_OVERRIDE);
  policy_listSender.length(1);
  policy_listSender[0] = orbSenderReliable->create_policy(Messaging::SYNC_SCOPE_POLICY_TYPE, orb_levelSender);
  policy_managerSender->set_policy_overrides(policy_listSender, CORBA::ADD_OVERRIDE);
//  policy_managerSender->set_policy_overrides(policy_listSender, CORBA::SET_OVERRIDE);
  // We are now done with these policies.
  policy_listSender[0]->destroy();

  // ORB receiver
  CORBA::Object_var obj = orbReceiver->resolve_initial_references("RootPOA");
  poaRootReceiver = PortableServer::POA::_narrow(obj);

  mgrReceiver = poaRootReceiver->the_POAManager();
  mgrReceiver->activate();

  // ORB sender
  CORBA::Object_var objSender = orbSenderReliable->resolve_initial_references("RootPOA");
  poaRootSenderReliable = PortableServer::POA::_narrow(objSender);

  mgrSenderReliable = poaRootSenderReliable->the_POAManager();
  mgrSenderReliable->activate();

  // ORB best effort
  CORBA::Object_var objBestEffort = orbSenderBestEffort->resolve_initial_references("RootPOA");
  poaRootSenderBestEffort = PortableServer::POA::_narrow(objBestEffort);

  mgrSenderBestEffort = poaRootSenderBestEffort->the_POAManager();
  mgrSenderBestEffort->activate();

  try
  {
    // Resolve the Naming Service
    CORBA::Object_var naming_obj = orbReceiver->resolve_initial_references("NameService");

    if (CORBA::is_nil(naming_obj))
    {
      std::cout << "UNABLE TO RESOLVE THE NAME SERVICE" << std::endl;
      return;
    }

    root_context = CosNaming::NamingContext::_narrow(naming_obj);

  }
  catch(...)
  {
    root_context = NULL;
    std::cout << "UNABLE TO NARROW THE NAME SERVICE" << std::endl;
    throw;
  }
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
GERTICO::GeRtiOrb::~GeRtiOrb(void)
{
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CosNaming::NamingContext_ptr GERTICO::GeRtiOrb::getRootContext()
{
  return root_context;
}
