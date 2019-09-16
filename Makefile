# ----------------------------------------------------------------------------
#
# Copyright (c) Fraunhofer IITB
# All rights reserved.
#
# ----------------------------------------------------------------------------

# External Libraries
ACElib = libACE.so
ACEversion = 5.8.1
TAOlib = libTAO.so
TAOversion = 1.8.1
TAO_AnyTypeCode = libTAO_AnyTypeCode.so
TAO_CodecFactory = libTAO_CodecFactory.so
TAO_Codeset = libTAO_Codeset.so
TAO_CosNaming_Serv = libTAO_CosNaming_Serv.so
TAO_CosNaming_Skel = libTAO_CosNaming_Skel.so
TAO_CosNamingLib = libTAO_CosNaming.so
TAO_IFR_Client = libTAO_IFR_Client.so
TAO_ImR_Client = libTAO_ImR_Client.so
TAO_IORInterceptor = libTAO_IORInterceptor.so
TAO_Messaging = libTAO_Messaging.so
TAO_ObjRefTemplate = libTAO_ObjRefTemplate.so
TAO_PI_Server = libTAO_PI_Server.so
TAO_PI = libTAO_PI.so
TAO_PortableServer = libTAO_PortableServer.so
TAO_Svc_Utils = libTAO_Svc_Utils.so
TAO_TypeCodeFactory = libTAO_TypeCodeFactory.so
TAO_Valuetype = libTAO_Valuetype.so
TAO_IORTable = libTAO_IORTable.so
XERCESlib = libxerces-c.so
XERCESversion = 28


all: directories external
	(cd FedTime; $(MAKE) all)
	(cd Gal; $(MAKE) all)
	(cd idl; $(MAKE) all)
	(cd Util; $(MAKE) all)
	(cd OMT_XML; $(MAKE) all)
	(cd GeRtiTime; $(MAKE) all)
	(cd EventMarket; $(MAKE) all)
	(cd GeRti; $(MAKE) all)
	(cd LRC; $(MAKE) all)

install: all external
	(cd FedTime; $(MAKE) install)
	(cd Gal; $(MAKE) install)
	(cd idl; $(MAKE) install)
	(cd Util; $(MAKE) install)
	(cd GeRtiTime; $(MAKE) install)
	(cd EventMarket; $(MAKE) install)
	(cd LRC; $(MAKE) install)

external: lib/$(TAOlib).$(TAOversion) \
	lib/$(ACElib).$(ACEversion) \
	lib/$(TAO_AnyTypeCode).$(TAOversion) \
	lib/$(TAO_CodecFactory).$(TAOversion) \
	lib/$(TAO_Codeset).$(TAOversion) \
	lib/$(TAO_CosNaming_Serv).$(TAOversion) \
	lib/$(TAO_CosNaming_Skel).$(TAOversion) \
	lib/$(TAO_CosNamingLib).$(TAOversion) \
	lib/$(TAO_IFR_Client).$(TAOversion) \
	lib/$(TAO_ImR_Client).$(TAOversion) \
	lib/$(TAO_IORInterceptor).$(TAOversion) \
	lib/$(TAO_Messaging).$(TAOversion) \
	lib/$(TAO_ObjRefTemplate).$(TAOversion) \
	lib/$(TAO_PI_Server).$(TAOversion) \
	lib/$(TAO_PI).$(TAOversion) \
	lib/$(XERCESlib).$(XERCESversion) \
	lib/$(TAO_PortableServer).$(TAOversion) \
	lib/$(TAO_IORTable).$(TAOversion) \
	lib/$(TAO_Svc_Utils).$(TAOversion) \
	lib/$(TAO_TypeCodeFactory).$(TAOversion) \
	lib/$(TAO_Valuetype).$(TAOversion) \
	bin/Naming_Service bin/tao_nslist

directories: lib bin

lib: 
	mkdir lib
bin:
	mkdir bin

bin/Naming_Service: $(TAO_ROOT)/orbsvcs/Naming_Service/Naming_Service
	cp $(TAO_ROOT)/orbsvcs/Naming_Service/Naming_Service bin

bin/tao_nslist: $(ACE_ROOT)/bin/tao_nslist
	cp $(ACE_ROOT)/bin/tao_nslist bin

lib/$(TAOlib).$(TAOversion):  $(ACE_ROOT)/lib/$(TAOlib).$(TAOversion)
	cp  $(ACE_ROOT)/lib/$(TAOlib).$(TAOversion) lib
	rm -f lib/$(TAOlib)
	ln -s $(TAOlib).$(TAOversion) lib/$(TAOlib)

lib/$(ACElib).$(ACEversion): $(ACE_ROOT)/lib/$(ACElib)
	cp $(ACE_ROOT)/lib/$(ACElib).$(ACEversion) lib
	rm -f lib/$(ACElib)
	ln -s $(ACElib).$(ACEversion) lib/$(ACElib)

lib/$(TAO_Svc_Utils).$(TAOversion):  $(ACE_ROOT)/lib/$(TAO_Svc_Utils)
	cp  $(ACE_ROOT)/lib/$(TAO_Svc_Utils).$(TAOversion) lib
	rm -f lib/$(TAO_Svc_Utils)
	ln -s $(TAO_Svc_Utils).$(TAOversion) lib/$(TAO_Svc_Utils)

lib/$(TAO_TypeCodeFactory).$(TAOversion):  $(ACE_ROOT)/lib/$(TAO_TypeCodeFactory)
	cp  $(ACE_ROOT)/lib/$(TAO_TypeCodeFactory).$(TAOversion) lib
	rm -f lib/$(TAO_TypeCodeFactory)
	ln -s $(TAO_TypeCodeFactory).$(TAOversion) lib/$(TAO_TypeCodeFactory)

lib/$(TAO_Valuetype).$(TAOversion):  $(ACE_ROOT)/lib/$(TAO_Valuetype)
	cp  $(ACE_ROOT)/lib/$(TAO_Valuetype).$(TAOversion) lib
	rm -f lib/$(TAO_Valuetype)
	ln -s $(TAO_Valuetype).$(TAOversion) lib/$(TAO_Valuetype)

lib/$(TAO_AnyTypeCode).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_AnyTypeCode)
	cp $(ACE_ROOT)/lib/$(TAO_AnyTypeCode).$(TAOversion) lib
	rm -f lib/$(TAO_AnyTypeCode)
	ln -s $(TAO_AnyTypeCode).$(TAOversion) lib/$(TAO_AnyTypeCode)

lib/$(TAO_CodecFactory).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_CodecFactory)
	cp $(ACE_ROOT)/lib/$(TAO_CodecFactory).$(TAOversion) lib
	rm -f lib/$(TAO_CodecFactory)
	ln -s $(TAO_CodecFactory).$(TAOversion) lib/$(TAO_CodecFactory)

lib/$(TAO_Codeset).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_Codeset)
	cp $(ACE_ROOT)/lib/$(TAO_Codeset).$(TAOversion) lib
	rm -f lib/$(TAO_Codeset)
	ln -s $(TAO_Codeset).$(TAOversion) lib/$(TAO_Codeset)

lib/$(TAO_CosNaming_Serv).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_CosNaming_Serv)
	cp $(ACE_ROOT)/lib/$(TAO_CosNaming_Serv).$(TAOversion) lib
	rm -f lib/$(TAO_CosNaming_Serv)
	ln -s $(TAO_CosNaming_Serv).$(TAOversion) lib/$(TAO_CosNaming_Serv)

lib/$(TAO_CosNaming_Skel).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_CosNaming_Skel)
	cp $(ACE_ROOT)/lib/$(TAO_CosNaming_Skel).$(TAOversion) lib
	rm -f lib/$(TAO_CosNaming_Skel)
	ln -s $(TAO_CosNaming_Skel).$(TAOversion) lib/$(TAO_CosNaming_Skel)

lib/$(TAO_CosNamingLib).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_CosNamingLib)
	cp $(ACE_ROOT)/lib/$(TAO_CosNamingLib).$(TAOversion) lib
	rm -f lib/$(TAO_CosNamingLib)
	ln -s $(TAO_CosNamingLib).$(TAOversion) lib/$(TAO_CosNamingLib)

lib/$(TAO_IFR_Client).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_IFR_Client)
	cp $(ACE_ROOT)/lib/$(TAO_IFR_Client).$(TAOversion) lib
	rm -f lib/$(TAO_IFR_Client)
	ln -s $(TAO_IFR_Client).$(TAOversion) lib/$(TAO_IFR_Client)

lib/$(TAO_ImR_Client).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_ImR_Client)
	cp $(ACE_ROOT)/lib/$(TAO_ImR_Client).$(TAOversion) lib
	rm -f lib/$(TAO_ImR_Client)
	ln -s $(TAO_ImR_Client).$(TAOversion) lib/$(TAO_ImR_Client)

lib/$(TAO_IORInterceptor).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_IORInterceptor)
	cp $(ACE_ROOT)/lib/$(TAO_IORInterceptor).$(TAOversion) lib
	rm -f lib/$(TAO_IORInterceptor)
	ln -s $(TAO_IORInterceptor).$(TAOversion) lib/$(TAO_IORInterceptor)

lib/$(TAO_Messaging).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_Messaging)
	cp $(ACE_ROOT)/lib/$(TAO_Messaging).$(TAOversion) lib
	rm -f lib/$(TAO_Messaging)
	ln -s $(TAO_Messaging).$(TAOversion) lib/$(TAO_Messaging)

lib/$(TAO_ObjRefTemplate).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_ObjRefTemplate)
	cp $(ACE_ROOT)/lib/$(TAO_ObjRefTemplate).$(TAOversion) lib
	rm -f lib/$(TAO_ObjRefTemplate)
	ln -s $(TAO_ObjRefTemplate).$(TAOversion) lib/$(TAO_ObjRefTemplate)

lib/$(TAO_PI_Server).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_PI_Server)
	cp $(ACE_ROOT)/lib/$(TAO_PI_Server).$(TAOversion) lib
	rm -f lib/$(TAO_PI_Server)
	ln -s $(TAO_PI_Server).$(TAOversion) lib/$(TAO_PI_Server)

lib/$(TAO_PI).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_PI)
	cp $(ACE_ROOT)/lib/$(TAO_PI).$(TAOversion) lib
	rm -f lib/$(TAO_PI)
	ln -s $(TAO_PI).$(TAOversion) lib/$(TAO_PI)

lib/$(TAO_PortableServer).$(TAOversion): $(ACE_ROOT)/lib/$(TAO_PortableServer)
	cp $(ACE_ROOT)/lib/$(TAO_PortableServer).$(TAOversion) lib
	rm -f lib/$(TAO_PortableServer)
	ln -s $(TAO_PortableServer).$(TAOversion) lib/$(TAO_PortableServer)

lib/$(TAO_IORTable).$(TAOversion):  $(ACE_ROOT)/lib/$(TAO_IORTable)
	cp  $(ACE_ROOT)/lib/$(TAO_IORTable).$(TAOversion) lib
	rm -f lib/$(TAO_IORTable)
	ln -s $(TAO_IORTable).$(TAOversion) lib/$(TAO_IORTable)

lib/$(XERCESlib).$(XERCESversion): $(XERCESCROOT)/lib/$(XERCESlib)
	cp $(XERCESCROOT)/lib/$(XERCESlib).$(XERCESversion) lib
	rm -f lib/$(XERCESlib)
	ln -s $(XERCESlib).$(XERCESversion) lib/$(XERCESlib)
	
samples: install
	(cd samples; $(MAKE) all)

clean:
	(cd FedTime; $(MAKE) clean)
	(cd Gal; $(MAKE) clean)
	(cd Util; $(MAKE) clean)
	(cd GeRtiTime; $(MAKE) clean)
	(cd OMT_XML; $(MAKE) clean)
	(cd EventMarket; $(MAKE) clean)
	(cd GeRti; $(MAKE) clean)
	(cd LRC; $(MAKE) clean)
	(cd samples; $(MAKE) clean)
	(cd idl; $(MAKE) clean)
	rm -f $(external)
