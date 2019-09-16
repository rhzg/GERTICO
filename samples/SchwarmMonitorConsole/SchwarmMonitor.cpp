/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Log: SchwarmMonitor.cpp,v $
Revision 1.1  2003/05/16 09:45:34  hzg
initial


 
**
*******************************************************************************/


#include "SchwarmAmbassador.h"

#ifdef _WIN32
#include <time.h>
#else
#include <stream.h>
#include <sys/time.h>
#endif
#include <iostream>
#include <map>

#include <RTI.hh>
#include <fedtime.hh>

#include "Fish.h"
#include "Federate.h"



RTI::Boolean        timeAdvGrant = RTI::RTI_FALSE;
RTI::Boolean        TimeRegulation = RTI::RTI_FALSE;
RTI::Boolean        TimeConstrained = RTI::RTI_FALSE;
//RTI::FedTime&       grantTime=(*(RTI::FedTimeFactory::makeZero()));

//******************************************************************************
//  Swarm Demo Federated
//******************************************************************************


int main(int argc, char** argv)
{


	//******************************************************************************
	//  Parse Arguments
	//******************************************************************************
	unsigned int swarmSize = 10;


	//******************************************************************************
	//  Establish Federation
	//******************************************************************************
	SchwarmAmbassador    fedAmb;         // User-defined
	Federate myFed;
	myFed.join(&fedAmb);


	//******************************************************************************
	//  Subscribe Swarm objects
	//******************************************************************************

	fedAmb.fishClass = myFed.rtiAmb.getObjectClassHandle ("objectRoot.Fisch");
    fedAmb.attributePosX = myFed.rtiAmb.getAttributeHandle ("posX", fedAmb.fishClass);
    fedAmb.attributePosY = myFed.rtiAmb.getAttributeHandle ("posY", fedAmb.fishClass);
    RTI::AttributeHandleSet *attributeList = RTI::AttributeHandleSetFactory::create(2);
    attributeList->add (fedAmb.attributePosX);
    attributeList->add (fedAmb.attributePosY);
    myFed.rtiAmb.subscribeObjectClassAttributes (fedAmb.fishClass, *attributeList);


	//******************************************************************************
	//  Monitor Positions
	//******************************************************************************

	RTI::AttributeHandleValuePairSet* position = RTI::AttributeSetFactory::create(2);
	char* xValue = (char*) malloc(sizeof(double));
	char* yValue = (char*) malloc(sizeof(double));
	position->add (fedAmb.attributePosX, xValue, sizeof(double));
	position->add (fedAmb.attributePosY, yValue, sizeof(double));
	fedAmb.updates = 0;
	while (true)
	{
		myFed.rtiAmb.tick(0.01, 0.1);
		std::cout << "received " << fedAmb.updates << std::endl;
	}




	return 0;
}


