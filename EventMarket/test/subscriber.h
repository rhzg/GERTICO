/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Author: mul $
$Name $
$Log: subscriber.h,v $
Revision 1.7  2004/10/04 15:12:45  mul
Remove unused class level.

Revision 1.6  2003/10/10 13:34:57  mul
New ORB init logic.

Revision 1.5  2003/08/20 13:49:16  mul
Use config file settings to locate name service.

Revision 1.4  2003/08/14 15:24:46  mul
Use a child POA for gertico objects.

Revision 1.3  2003/05/27 15:01:07  mul
Use include paths starting in $GERTICO.

Revision 1.2  2002/12/20 09:57:51  mul
Minor changes.

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

class  PushConsumer_i : public virtual POA_GeRtiEventMarket::PushConsumer
{
  GERTICO::GeRtiOrb &myGeRtiOrb;
public:
 
  //Constructor
  PushConsumer_i (GERTICO::GeRtiOrb &);
 
  //Destructor
  virtual ~PushConsumer_i (void);
 
  PortableServer::POA_ptr _default_POA (void);

  virtual void push (
    const GeRtiEventMarket::Events & e
  )
  throw (
    CORBA::SystemException
  );
 
  virtual void disconnect_push_consumer (
  )
  throw (
    CORBA::SystemException
  );
};

class mainSubscriber
{
  GERTICO::GeRtiOrb *myGeRtiOrb;
  GERTICOconf *conf;
  GeRtiEventMarket::MarketConsumerAdmin_var consumerAdminVar;
  PushConsumer_i *pc;
  GeRtiEventMarket::PushConsumer_ptr pcPtr;
  GeRtiFactory::SupportingServices_var ssVar;

  // arguments from command line.
  char **argv_;

  // # of arguments on the command line.
  int argc_;

  const char *name;
public:
  // Constructor and destructor.
  mainSubscriber ();
  virtual ~mainSubscriber ();

  // Do some initialisation.
  int init ();

  // Parses the arguments passed on the command line.
  int parse_args (int argc, char **argv);

  // Run.
  int run ();
};
