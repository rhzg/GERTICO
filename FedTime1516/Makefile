include $(GERTICO)/config.incl

INC =	-I$(GERTICO) -I$(GERTICO)/include/RTI_1516

LIB =

SHARED_LIB = libfedtime1516.so
SHARED_LINK = g++
SHARED_FLAGS = -Wl,-h -Wl,$(SHARED_LIB) -Wl,-E -Wl,-rpath,$(ACE_ROOT)/ace -shared -Wl,-rpath,$(GERTICO)/lib -lm -lpthread -lrt

OBJ =	LogicalTimeDouble.o LogicalTimeFactoryFactory.o

.cpp.o:
	g++ $(FLAGS) -DIEEE_1516 -c $< $(INC)

all: libFedtimeDouble.a $(GERTICO)/lib/$(SHARED_LIB)
 
install: $(GERTICO)/lib/libFedtimeDouble.a $(GERTICO)/lib/$(SHARED_LIB)

$(GERTICO)/lib/libFedtimeDouble.a: libFedtimeDouble.a
	cp libFedtimeDouble.a $(GERTICO)/lib

$(GERTICO)/lib/$(SHARED_LIB): $(SHARED_LIB)
	cp $(SHARED_LIB) $(GERTICO)/lib

clean:
	rm -f $(OBJ) $(GERTICO)/lib/libFedtimeDouble.a libFedtimeDouble.a dependencies.incl

libFedtimeDouble.a: $(OBJ)
	ar cr libFedtimeDouble.a $(OBJ)

$(SHARED_LIB): $(OBJ)
	$(SHARED_LINK) $(SHARED_FLAGS) -o $@ $(OBJ)
	
dependencies.incl:
	g++ $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
