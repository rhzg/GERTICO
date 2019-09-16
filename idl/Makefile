# ----------------------------------------------------------------------------
#
# Copyright (c) Fraunhofer IITB
# All rights reserved.
#
# ----------------------------------------------------------------------------
 
include $(GERTICO)/config.incl

IDL = $(ACE_ROOT)/TAO/TAO_IDL/tao_idl

#IDL_ARG = -I$(ACE_ROOT)/TAO/orbsvcs/orbsvcs -I../GeRtiTime -Ge 2 -Sc 
IDL_ARG =

INC = -I$(ACE_ROOT) -I$(ACE_ROOT)/TAO/orbsvcs -I$(ACE_ROOT)/TAO

IDL_Factory = GeRtiFactoryC.cpp GeRtiFactoryC.h GeRtiFactoryS.cpp GeRtiFactoryS.h

IDL_OBJ =	GeRtiFactoryC.o GeRtiFactoryS.o

all: idl librtiidl.a install

install: $(GERTICO)/lib/librtiidl.a

$(GERTICO)/lib/librtiidl.a: librtiidl.a
	cp librtiidl.a $(GERTICO)/lib

clean:
	rm -f librtiidl.a $(IDL_Factory) $(IDL_OBJ) \
	GeRtiFactoryC.i GeRtiFactoryC.inl \
	GeRtiFactoryS.i GeRtiFactoryS.inl \
	GeRtiFactoryS_T.cpp GeRtiFactoryS_T.h GeRtiFactoryS_T.i GeRtiFactoryS_T.inl

#$(IDL_Factory): GeRtiFactoryS_T.inl

#GeRtiFactoryS_T.inl: GeRtiFactory.idl
GeRtiFactoryC.cpp GeRtiFactoryC.h GeRtiFactoryS.cpp GeRtiFactoryS.h: GeRtiFactory.idl
	$(IDL) $(IDL_ARG) GeRtiFactory.idl

#idl: $(IDL_Factory)
idl: GeRtiFactoryC.cpp GeRtiFactoryC.h GeRtiFactoryS.cpp GeRtiFactoryS.h

librtiidl.a: $(IDL_OBJ)
	ar cru $@ $(IDL_OBJ)

.cpp.o:
	g++ $(FLAGS) -c $< $(INC)


