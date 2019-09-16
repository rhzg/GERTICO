# ----------------------------------------------------------------------------
#
# Copyright (c) Fraunhofer IITB
# All rights reserved.
#
# ----------------------------------------------------------------------------

include $(GERTICO)/config.incl 


INC = -I$(ACE_ROOT) \
	-I$(ACE_ROOT)/TAO \
	-I$(ACE_ROOT)/TAO/orbsvcs \
	-I$(ACE_ROOT)/TAO/orbsvcs/orbsvcs \
	-I$(GERTICO) \
	-I${XERCESCROOT}/include \
	-I$(GERTICO)/include

LIB_A = $(GERTICO)/lib/libTAO.so \
	$(GERTICO)/lib/libTAO_CosNaming.so \
	$(GERTICO)/lib/libTAO_Messaging.so \
	$(GERTICO)/lib/libTAO_PortableServer.so \
	$(GERTICO)/lib/libTAO_Valuetype.so \
	$(GERTICO)/lib/libACE.so \
	$(GERTICO)/EventMarket/libgertiem.a \
	$(GERTICO)/GeRtiTime/libgertitm.a \
	$(XERCESCROOT)/lib/libxerces-c.so \
	$(GERTICO)/idl/librtiidl.a \
	$(GERTICO)/Gal/libgal.a \
	$(GERTICO)/lib/libfedtime.so \
	$(GERTICO)/Util/libgertiut.a

OBJ =	DataDistributionManagement.o \
	DeclarationManagementRTI.o \
	FederationManagement.o \
	GeRtiAmbassadorI.o \
	GeRtiFactoryI.o \
	GeRtiOwnershipMasterI.o \
	ManagementObjectModel.o \
	OwnershipWorkerThread.o \
	SupportingServices.o \
	SyncPointHandler.o \
	main.o

.cpp.o:
	g++ $(FLAGS) -c $< $(INC)

all: $(GERTICO)/bin/gerti13

$(GERTICO)/bin/gerti13: $(OBJ) ${LIB_A}
	$(CXX) $(LDFLAGS) -o $(GERTICO)/bin/gerti13 $(OBJ) $(LIB_A)

clean:
	rm -f $(OBJ) $(GERTICO)/bin/gerti13 dependencies.incl

dependencies.incl:
	$(CXX) $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
