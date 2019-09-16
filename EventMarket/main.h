/*******************************************************************************
**
** Copyright (c) Fraunhofer IOSB
** All rights reserved.
**
** main.h
**
*******************************************************************************/

#include <string>
#include "GeRtiFactoryECI.h"
#include "Util/GeRtiOrb.h"
#include "Util/GERTICOconf.h"

class mainServer
{
#ifdef IEEE_1516
  ACE_DLL dll;
#endif
  CosNaming::NamingContext_var gerti_context;
  CORBA::Object_var gertiObj;
  GERTICO::GeRtiOrb *myGeRtiOrb;
  GERTICOconf *conf;
  GeRtiFactory::TheFactory_var theFactoryVar;
  GeRtiFactory_TheEventHubFederationFactoryEC_i *theEventHubFederationFactory;
  GeRtiFactory::TheEventHubFederationFactory_var theEventHubFederationFactoryVar;
  GERTICO::GeRtiFedTimeFactory *geRtiFedTimeFactory;
  GERTICO::GeRtiLogicalTimeIntervalFactory *geRtiLogicalTimeIntervalFactory;
  std::wstring ws;

  const char *factory;
  const char *name;

  bool getGertiDirectory(CosNaming::Name const &theDirectoryName);

public:
  // Constructor and destructor.
  mainServer();
  virtual ~mainServer();

  // Do some initialisation.
  int init();

  // Run the server.
  int run();
};
