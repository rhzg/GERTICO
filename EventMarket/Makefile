# ----------------------------------------------------------------------------
#
# Copyright (c) Fraunhofer IITB
# All rights reserved.
#
# ----------------------------------------------------------------------------

include $(GERTICO)/config.incl 


INC = -I$(ACE_ROOT)/TAO/orbsvcs \
	-I$(ACE_ROOT) \
	-I$(ACE_ROOT)/TAO \
	-I${XERCESCROOT}/include \
	-I$(GERTICO) \
	-I$(GERTICO)/include

LIB_A = $(GERTICO)/lib/libTAO.so \
        $(GERTICO)/lib/libTAO_CosNaming.so \
        $(GERTICO)/lib/libTAO_Messaging.so \
        $(GERTICO)/lib/libTAO_PortableServer.so \
        $(GERTICO)/lib/libTAO_Valuetype.so \
        $(GERTICO)/lib/libACE.so \
        $(GERTICO)/GeRtiTime/libgertitm.a \
        $(XERCESCROOT)/lib/libxerces-c.so \
        $(GERTICO)/idl/librtiidl.a \
        $(GERTICO)/Gal/libgal.a \
        $(GERTICO)/lib/libfedtime.so \
        $(GERTICO)/Util/libgertiut.a

OBJ =	DeclarationManagementEC.o \
	EventHandler.o \
	FederationManagementEC.o \
	FedEventSender.o \
	GeRtiEventMarketI.o \
	GeRtiEventMarketISend.o \
	GeRtiFactoryECI.o \
	Interaction.o \
	Jobs.o \
	ObjectManagement.o \
	SupportingServicesEC.o \
	TimeClient.o

.cpp.o:
	g++ $(FLAGS) -c $< $(INC)

all: eventHub13

install: 

clean:
	rm -f $(OBJ) libgertiem.a dependencies.incl

eventHub13: main.o libgertiem.a
	$(CXX) $(LDFLAGS) main.o $(OBJ) $(LIB_A) -o $@

libgertiem.a: $(OBJ)
	ar cr libgertiem.a $(OBJ)

dependencies.incl:
	$(CXX) $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
