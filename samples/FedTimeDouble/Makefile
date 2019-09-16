include $(GERTICO)/config.incl

INC =	-I$(GERTICO)/include

LIB =

SHARED_LIB = libfedtime.so
SHARED_LINK = g++
SHARED_FLAGS = -Wl,-h -Wl,$(SHARED_LIB) -Wl,-E -Wl,-rpath,$(ACE_ROOT)/ace -shared -Wl,-rpath,$(GERTICO)/lib -lm -lpthread -lrt

OBJ =	fedtimeDouble.o

.cpp.o:
	g++ $(FLAGS) -c $< $(INC)

all: libFedtimeDouble.a $(SHARED_LIB)
 
install: $(GERTICO)/lib/libFedtimeDouble.a

$(GERTICO)/lib/libFedtimeDouble.a: libFedtimeDouble.a
	cp libFedtimeDouble.a $(GERTICO)/lib

clean:
	rm -f $(OBJ) $(GERTICO)/lib/libFedtimeDouble.a libFedtimeDouble.a dependencies.incl

libFedtimeDouble.a: $(OBJ)
	ar cr libFedtimeDouble.a $(OBJ)

$(SHARED_LIB): $(OBJ)
	$(SHARED_LINK) $(SHARED_FLAGS) -o $@ $(OBJ)
	
dependencies.incl:
	g++ $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
