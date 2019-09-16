/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: publisher.h,v $
Revision 1.5  2004/10/04 15:12:45  mul
Remove unused class level.

Revision 1.4  2003/10/10 13:35:50  mul
New ORB init logic.

Revision 1.3  2003/08/20 13:51:42  mul
Use config file settings to locate name service.

Revision 1.2  2003/05/27 15:01:07  mul
Use include paths starting in $GERTICO.

Revision 1.1  2002/09/11 15:12:38  mul
Changed logic for the use of name service: a singleton to get NS root.

Revision 1.5  2002/07/16 08:57:20  hzg
Copyright Hinweis und Versiondaten in Dateien aufgenommen

 
**
*******************************************************************************/


#include <string>
#include "OMT_XML/GERTICOconf.h"
#include "Util/GeRtiOrb.h"
#include "EventMarket/EventHandler.h"
#include "EventMarket/GeRtiSupportingServices.h"

class mainPublisher
{
  GERTICO::GeRtiOrb *myGeRtiOrb;
  GERTICOconf *conf;
  GeRtiEventMarket::MarketSupplierAdmin_ptr supplierAdminVar;
  GeRtiFactory::SupportingServices_var ssVar;

  // arguments from command line.
  char **argv_;

  // # of arguments on the command line.
  int argc_;

  const char *name;
public:
  // Constructor and destructor.
  mainPublisher ();
  virtual ~mainPublisher ();

  // Do some initialisation.
  int getRoot ();

  // Parses the arguments passed on the command line.
  int parse_args (int argc, char **argv);

  // Run.
  int run ();
};
