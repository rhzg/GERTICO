/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** GeRtiOrb.h
**
*******************************************************************************/

#ifndef GeRtiOrb_H_
#define GeRtiOrb_H_
#include <string>
#include "orbsvcs/Naming_Service/Naming_Service.h"
#include "Util/GERTICOconf.h"

namespace GERTICO
{
  class GeRtiOrb
  {
    CosNaming::NamingContext_var root_context;
    static unsigned int GERTICO_ORB_init_counter;

  public:
    // constructor
    GeRtiOrb(GERTICOconf &conf);

    // destructor
    virtual ~GeRtiOrb(void);

    // member variables
    CORBA::ORB_ptr orbReceiver;
    CORBA::ORB_ptr orbSenderBestEffort;
    CORBA::ORB_ptr orbSenderReliable;
    PortableServer::POA_var poaRootReceiver;
    PortableServer::POA_var poaRootSenderBestEffort;
    PortableServer::POA_var poaRootSenderReliable;
    PortableServer::POAManager_var mgrReceiver;
    PortableServer::POAManager_var mgrSenderBestEffort;
    PortableServer::POAManager_var mgrSenderReliable;

    // methods
    CosNaming::NamingContext_ptr getRootContext();
  };
};

#endif /* GeRtiOrb_H_  */
