/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** main.h
**
*******************************************************************************/

#include <string>
#include "GeRtiFactoryI.h"
#include "Util/GeRtiOrb.h"
#include "Util/GERTICOconf.h"

class mainServer
{
#ifdef IEEE_1516
  ACE_DLL dll;
#endif
  CORBA::Object_var gertiObj;
  CosNaming::NamingContext_var gerti_context;
  GERTICO::GeRtiOrb *myGeRtiOrb;
  GERTICOconf *conf;
  GeRtiFactory_Factory_i *gertiFactory;
  GERTICO::GeRtiFedTimeFactory *geRtiFedTimeFactory;
  GERTICO::GeRtiLogicalTimeIntervalFactory *geRtiLogicalTimeIntervalFactory;

  const char *factory;
  const char *name;

  bool addNsDirectory(CosNaming::Name const &theDirectoryName);

public:
  // Constructor and destructor.
  mainServer ();
  virtual ~mainServer ();

  // Do some initialisation.
  int init ();

  // Run the server.
  int run ();
};
