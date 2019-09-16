/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: main.h,v $
Revision 1.8  2004/10/04 15:12:45  mul
Remove unused class level.

Revision 1.7  2004/03/17 13:49:50  mul
Changes due to persistent database logic.

Revision 1.6  2003/10/10 13:36:28  mul
New ORB init logic.

Revision 1.5  2003/08/20 13:51:08  mul
Use config file settings to locate name service.

Revision 1.4  2003/08/14 15:24:45  mul
Use a child POA for gertico objects.

Revision 1.3  2003/05/27 15:01:07  mul
Use include paths starting in $GERTICO.

Revision 1.2  2002/12/20 10:01:56  mul
Minor chnages.

Revision 1.1  2002/09/11 15:12:38  mul
Changed logic for the use of name service: a singleton to get NS root.

Revision 1.5  2002/07/16 08:57:20  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#include <string>
#include "Util/GeRtiOrb.h"
#include "EventMarket/EventHandler.h"
#include "EventMarket/GeRtiEventAdminI.h"
#include "EventMarket/GeRtiSupportingServices.h"

void *server_worker (void *);

class mainServer
{
  ACE_Semaphore *ps;
  EventHandler *eventHandler;
  GERTICO::GeRtiOrb *myGeRtiOrb;
  GeRtiEventMarket_MarketConsumerAdmin_i *consumerAdmin;
  GeRtiEventMarket_MarketSupplierAdmin_i *supplierAdmin;

  GeRtiFactory_SupportingServices_i *ss;

  // DDM
  //GERTICO::RegionManager regionManager;
  GERTICO::PersistentDB *persistentDB;

  // arguments from command line.
  char **argv_;

  // # of arguments on the command line.
  int argc_;

  const char *name;
public:
  // Constructor and destructor.
  mainServer ();
  virtual ~mainServer ();

  // Do some initialisation.
  int init ();

  // Parses the arguments passed on the command line.
  int parse_args (int argc, char **argv);

  // Run the server.
  void run (void);
};
