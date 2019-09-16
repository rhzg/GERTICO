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
	-I${GERTICO}/include \
	-I$(GERTICO)

OBJ =	ClassDescr.o \
	ConvertTime.o \
	DataModel.o \
	Exception.o \
	Fed.o \
	FedParser.o \
	Federate.o \
	GERTICOconfImpl.o \
	GeRtiOrb.o \
	GeRtiFedTimeI.o \
	HLAparseErrorHandler.o \
	Item.o \
	JobHolder.o \
	Mapper.o \
	NextHandle.o \
	PrintFilter.o \
	PrintErrorHandler.o \
	Publisher.o \
	Region.o \
	RegisteredObject.o \
	RTI_Exception.o \
	RunTimeObjectDB.o \
	Space.o \
	Subscriber.o

.cpp.o:
	g++ $(FLAGS)  -c $< $(INC)

all: libgertiut.a 

install: $(GERTICO)/lib/libgertiut.a

$(GERTICO)/lib/libgertiut.a: libgertiut.a
	cp libgertiut.a $(GERTICO)/lib

clean:
	rm -f $(OBJ) libgertiut.a dependencies.incl

libgertiut.a: $(OBJ)
	ar cr libgertiut.a $(OBJ)

dependencies.incl:
	$(CXX) $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
