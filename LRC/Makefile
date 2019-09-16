include $(GERTICO)/config.incl


CXXFLAGS += \
	$(FLAGS) \
	-I$(GERTICO)/include \
	-I$(ACE_ROOT) \
	-I$(TAO_ROOT) \
	-I$(TAO_ROOT)/orbsvcs \
	-I$(TAO_ROOT)/orbsvcs/orbsvcs \
	-I${XERCESCROOT}/include \
	-I$(GERTICO)

IDSTRING = $(shell fgrep ID_STRING config.h | sed 's/\#define ID_STRING "\(.*\)"/\1/')
LIB = libRTI-NG.a


SHARED_LIB = libRTI-NG.so
SHARED_LINK = g++
SHARED_FLAGS = -Wl,-h -Wl,$(SHARED_LIB) -Wl,-E -Wl,-rpath,$(ACE_ROOT)/ace -shared -Wl,-rpath,$(GERTICO)/lib

LIB_A = -lm -lpthread -lrt \
	$(GERTICO)/lib/libTAO.so \
	$(GERTICO)/lib/libACE.so \
	$(GERTICO)/lib/libTAO_CosNaming.so \
	$(XERCESCROOT)/lib/libxerces-c.so \
	$(GERTICO)/FedTime/$(FEDTIMELIB) \
	-Wl,-whole-archive $(GERTICO)/GeRtiTime/libgertitm.a \
	-Wl,-whole-archive $(GERTICO)/Util/libgertiut.a \
	-Wl,-whole-archive $(GERTICO)/idl/librtiidl.a \
	-Wl,-whole-archive $(GERTICO)/LRC/HLASpec/librtimap.a \
	-Wl,-whole-archive $(GERTICO)/Gal/libgal.a

OBJ =	DeclarationManagementLRC.o \
	DataDistributionManagementLRC.o \
	EventMarket.o \
	FederateDB.o \
	GeRtiAmbassadorI.o \
	GeRtiEventMarketI.o \
	GeRtiRestoreI.o \
	ManagementObjectModelLRC.o \
	ObjectManagementLRC.o \
	OwnershipManagementLRC.o \
	Sender.o \
	SupportingServicesLRC.o \
	TimeManagementLRC.o \
	LrcOwnershipClient.o

all: $(LIB) sub $(SHARED_LIB) 

install: $(GERTICO)/lib/$(LIB) $(GERTICO)/lib/$(SHARED_LIB)
	(cd HLASpec; $(MAKE) install)

$(GERTICO)/lib/$(LIB): $(LIB)
	cp $(LIB) $(GERTICO)/lib

$(GERTICO)/lib/$(SHARED_LIB): $(SHARED_LIB)
	cp $(SHARED_LIB) $(GERTICO)/lib

$(LIB): $(OBJ)
	ar -r $@ $(OBJ)
	
$(SHARED_LIB): $(OBJ) $(GERTICO)/GeRtiTime/libgertitm.a \
	$(GERTICO)/Util/libgertiut.a $(GERTICO)/idl/librtiidl.a \
	$(GERTICO)/LRC/HLASpec/librtimap.a $(GERTICO)/Gal/libgal.a
	$(SHARED_LINK) $(SHARED_FLAGS) -o $@ $(OBJ)
	
clean:
	rm -f $(OBJ) $(LIB) $(GERTICO)/lib/$(LIB) dependencies.incl $(SHARED_LIB)
	(cd HLASpec; $(MAKE) clean)

distclean: clean
	rm -f $(LIB)

sub:
	(cd HLASpec; $(MAKE) all)

dependencies.incl:
	$(CXX) $(CXXFLAGS) -MM *.cpp >$@

include dependencies.incl
