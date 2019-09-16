include $(GERTICO)/config.incl 

LDLIBS = -L.. -lGeRTI_v1_0_CORBA \
	-L$(GERTICO)/lib -lACE -lTAO_CosNaming -lTAO \
	-L$(GERTICO)/GeRtiTime -lgerti1516tm \
	-L$(GERTICO)/idl -lrtiidl

CXXFLAGS = $(FLAGS) -DIEEE_1516 \
	-I$(GERTICO)/include \
	-I$(GERTICO)/include/RTI_1516 \
	-I$(GERTICO) \
	-I${XERCESCROOT}/include \
	-I$(TAO_ROOT)/orbsvcs \
	-I$(TAO_ROOT)/orbsvcs/orbsvcs \
	-I$(ACE_ROOT) \
	-I$(TAO_ROOT)

IDSTRING = $(shell fgrep ID_STRING config.h | sed 's/\#define ID_STRING "\(.*\)"/\1/')

LIB = librtimap1516.a

OBJ =	EventHandler.o \
	HlaOwnershipClientMapper.o \
	Mapper1516.o \
	ReceiverI.o \
	RTIAmbassadorFactory.o \
	RTIambServices.o

all: $(LIB) 

install: $(GERTICO)/lib/librtimap1516.a

$(GERTICO)/lib/librtimap1516.a: librtimap1516.a
	cp librtimap1516.a $(GERTICO)/lib

$(LIB): $(OBJ)
	ar -r $@ $(OBJ)

clean:
	rm -f $(LIB) $(OBJ) app dependencies.incl

dependencies.incl:
	$(CXX) $(CXXFLAGS) -MM *.cpp >$@

include dependencies.incl
