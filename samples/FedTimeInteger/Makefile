include $(GERTICO)/config.incl

INC =	-I$(GERTICO)/include

LIB =

SHARED_LIB = libIntegerTime.so
SHARED_LINK = g++
SHARED_FLAGS = -Wl,-h -Wl,$(SHARED_LIB) -Wl,-E -Wl,-rpath,$(ACE_ROOT)/ace -shared -Wl,-rpath,$(GERTICO)/lib -lm -lpthread -lrt

OBJ =	IntegerTime.o

.cpp.o:
	g++ $(FLAGS) -c $< $(INC)

all: $(SHARED_LIB)
 
install: $(GERTICO)/lib/$(SHARED_LIB)

$(GERTICO)/lib/$(SHARED_LIB): $(SHARED_LIB)
	cp $(SHARED_LIB) $(GERTICO)/lib

clean:
	rm -f $(OBJ) $(SHARED_LIB) dependencies.incl

$(SHARED_LIB): $(OBJ)
	$(SHARED_LINK) $(SHARED_FLAGS) -o $@ $(OBJ)
	
dependencies.incl:
	g++ $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
