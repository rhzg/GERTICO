# ----------------------------------------------------------------------------
#
# Copyright (c) Fraunhofer IITB
# All rights reserved.
#
# ----------------------------------------------------------------------------

include $(GERTICO)/config.incl 


INC = -I$(GERTICO)/Gal

LIB = $(GERTICO)/Gal/libgal.a

OBJ =	appl.o	\
	fkt1.o	\
	fkt2.o	\
	gal.o
	
.cpp.o:
	g++ $(FLAGS) -c $< $(INC)

all: gal 

clean:
	rm -f $(OBJ) gal dependencies.incl

gal: $(OBJ) $(GERTICO)/Gal/libgal.a
	$(CXX) $(LDFLAGS) -o gal $(OBJ) $(LIB)

dependencies.incl:
	$(CXX) $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
