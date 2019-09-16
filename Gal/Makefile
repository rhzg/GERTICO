# ----------------------------------------------------------------------------
#
# Copyright (c) Fraunhofer IITB
# All rights reserved.
#
# ----------------------------------------------------------------------------

include $(GERTICO)/config.incl 


INC = -I$(ACE_ROOT)

LIB =

OBJ =	event.o \
	format.o \
	logger.o \
	appender.o \
	layout.o \
	repository.o \
	repository_l.o \
	adm.o \
	out.o	\
	in.o	\
	param.o

.cpp.o:
	g++ -fpermissive $(FLAGS) -c $< $(INC)

all: libgal.a

install: $(GERTICO)/lib/libgal.a

$(GERTICO)/lib/libgal.a: libgal.a
	cp libgal.a $(GERTICO)/lib

clean:
	rm -f $(OBJ) libgal.a dependencies.incl

libgal.a: $(OBJ)
	ar cr libgal.a $(OBJ)

dependencies.incl:
	$(CXX) $(FLAGS) $(INC) -MM *.cpp >$@
 
include dependencies.incl
