include $(GERTICO)/config.incl

LIBS =	$(GERTICO)/lib/libRTI-NG.so \
	$(GERTICO)/samples/Common/common.a \
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
	-I$(GERTICO)/include/RTI_1.3 \
	-I$(GERTICO)/samples/Common

OBJ =   SchwarmAmbassador.o \
	BossFish.o

all: bossFish

bossFish: $(OBJ) $(LIBS)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LIBS) -o $@

clean:
	rm -f $(OBJ) swarmMonitor dependencies.incl

dependencies.incl:
	$(CXX) $(CXXFLAGS) -MM *.cpp >$@

include dependencies.incl
