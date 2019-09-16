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

LIBS =	$(GERTICO)/lib/libTAO.so \
	$(GERTICO)/lib/libACE.so \
	$(GERTICO)/lib/libTAO_CosNaming.so \
	$(GERTICO)/EventMarket/libgertiem.a \
	$(GERTICO)/GeRtiTime/libgertitm.a \
	$(GERTICO)/OMT_XML/libOMT_XML.a \
	$(GERTICO)/Ownership/libgertiown.a \
	$(GERTICO)/Util/libgertiut.a \
	$(XERCESCROOT)/lib/libxerces-c.so \
	$(GERTICO)/idl/librtiidl.a \
	$(GERTICO)/Gal/libgal.a \
	$(GERTICO)/FedTime/$(FEDTIMELIB) \
	$(GERTICO)/RTI_Exceptions/libRTI_Exceptions.a

OBJ =	main.o
OBJ1 =	publisher.o
OBJ2 =	subscriber.o

.cpp.o:
	g++ $(FLAGS) -c $< $(INC)

all: eventChannel publisher subscriber

clean:
	rm -f $(OBJ) $(OBJ1) $(OBJ2) eventChannel publisher subscriber dependencies.incl

eventChannel: $(OBJ) $(LIBS)
	$(CXX) $(LDFLAGS) -o eventChannel $(OBJ) $(LIBS)

publisher: $(OBJ1)
	$(CXX) $(LDFLAGS) -o publisher $(OBJ1) $(LIBS)

subscriber: $(OBJ2)
	$(CXX) $(LDFLAGS) -o subscriber $(OBJ2) $(LIBS)

dependencies.incl:
	$(CXX) $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
