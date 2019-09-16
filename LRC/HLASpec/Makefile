include $(GERTICO)/config.incl 

LDLIBS = -L.. -lGeRTI_v1_0_CORBA \
	-L$(GERTICO)/lib -lACE -lTAO_CosNaming -lTAO \
	-L$(GERTICO)/GeRtiTime -lgertitm \
	-L$(GERTICO)/idl -lrtiidl

CXXFLAGS = $(FLAGS) \
	-I$(GERTICO)/include/RTI_1.3 \
	-I$(GERTICO) \
	-I${XERCESCROOT}/include \
	-I$(TAO_ROOT)/orbsvcs \
	-I$(TAO_ROOT)/orbsvcs/orbsvcs \
	-I$(ACE_ROOT) \
	-I$(TAO_ROOT)

IDSTRING = $(shell fgrep ID_STRING config.h | sed 's/\#define ID_STRING "\(.*\)"/\1/')

LIB = librtimap.a

OBJ =	ut.o \
	EventHandler.o \
	Mapper13.o \
	RTI_AHSet.o \
	RTI_AHVPSet.o \
	RTI_AHSetFactory.o \
	RTI_AHVPSetFactory.o \
	RTI_Exceptions.o \
	RTI_HSet.o \
	RTI_HSetFactory.o \
	RTI_HVPSet.o \
	RTI_PHVPSet.o \
	RTI_PHVPSetFactory.o \
	RTI_RegionI.o \
	RTIambServices.o \
	ReceiverI.o \
	HlaOwnershipClientMapper.o

all: $(LIB) 

install: $(GERTICO)/lib/librtimap.a

$(GERTICO)/lib/librtimap.a: librtimap.a
	cp librtimap.a $(GERTICO)/lib

$(LIB): $(OBJ)
	ar -r $@ $(OBJ)

clean:
	rm -f $(LIB) $(OBJ) app dependencies.incl

dependencies.incl:
	$(CXX) $(CXXFLAGS) -MM *.cpp >$@

include dependencies.incl
