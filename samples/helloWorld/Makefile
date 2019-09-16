include $(GERTICO)/config.incl

LIBS =	$(GERTICO)/lib/libRTI-NG.so \
	$(GERTICO)/lib/libTAO_AnyTypeCode.so \
	$(GERTICO)/lib/libTAO_Messaging.so \
	$(GERTICO)/lib/libTAO_PortableServer.so \
	$(GERTICO)/lib/libTAO_TypeCodeFactory.so \
	$(GERTICO)/lib/libgertitm.a \
	$(GERTICO)/lib/libgertiut.a \
	$(GERTICO)/lib/librtiidl.a \
	$(GERTICO)/lib/librtimap.a \
	$(GERTICO)/lib/libTAO.so \
	$(GERTICO)/lib/libACE.so \
	$(GERTICO)/lib/libTAO_CosNaming.so \
	$(GERTICO)/lib/libxerces-c.so \
	$(GERTICO)/lib/libfedtime.so \
	$(GERTICO)/lib/libgal.a

CXXFLAGS = $(FLAGS) \
	-I$(GERTICO)/include/RTI_1.3 

OBJ =   Country.o \
	HelloWorld.o \
	HwFederateAmbassador.o

all: helloWorld

helloWorld: $(OBJ) $(LIBS)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LIBS) -o $@

test: 
	run_test.pl

clean:
	rm -f $(OBJ) helloWorld dependencies.incl

dependencies.incl:
	$(CXX) $(CXXFLAGS) -MM *.cpp >$@

include dependencies.incl
