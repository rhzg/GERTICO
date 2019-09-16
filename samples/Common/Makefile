# ----------------------------------------------------------------------------
#
# Copyright (c) Fraunhofer IITB
# All rights reserved.
#
# ----------------------------------------------------------------------------

include $(GERTICO)/config.incl 


INC =

LIB =

OBJ =	Federate.o \
	Fish.o

FLAGS += -I$(GERTICO)/include/RTI_1.3

.cpp.o:
	g++ $(FLAGS) -c $< $(INC)

all: common.a

clean:
	rm -f $(OBJ) libgal.a dependencies.incl

common.a: $(OBJ)
	ar cr common.a $(OBJ)

dependencies.incl:
	$(CXX) $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
