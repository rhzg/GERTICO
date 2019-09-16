include $(GERTICO)/config.incl

INC = -I$(ACE_ROOT)/TAO/orbsvcs \
	-I$(ACE_ROOT) \
	-I$(ACE_ROOT)/TAO \
	-I$(GERTICO) \
	-I${XERCESCROOT}/include \
	-I$(GERTICO)/include

LIB =	$(GERTICO)/lib/libTAO.so \
	$(GERTICO)/lib/libACE.so \
	$(GERTICO)/lib/libTAO_CosNaming.so \
	$(GERTICO)/OMT_XML/libOMT_XML.a \
	$(XERCESCROOT)/lib/libxerces-c.so \
	$(GERTICO)/idl/librtiidl.a \
	$(GERTICO)/Util/libgertiut.a \
	$(GERTICO)/FedTime/$(FEDTIMELIB) \
	$(GERTICO)/RTI_Exceptions/libRTI_Exceptions.a

OBJ =	TimeServiceFacI.o \
	TimeManagementI.o \
	TokenHolder.o

.cpp.o:
	g++ $(FLAGS) -c $< $(INC)

all: libgertitm.a

install: $(GERTICO)/lib/libgertitm.a

$(GERTICO)/lib/libgertitm.a: libgertitm.a
	cp libgertitm.a $(GERTICO)/lib

clean:
	rm -f $(OBJ) libgertitm.a TimeClient.o $(IDL_OBJ) dependencies.incl

libgertitm.a: $(OBJ)
	ar cr libgertitm.a $(OBJ)

dependencies.incl:
	g++ $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
