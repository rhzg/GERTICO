/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Log: Schwarm.cpp,v $
Revision 1.2  2003/11/10 15:11:53  hzg
random generation corrected

Revision 1.1  2003/05/16 09:45:39  hzg
initial


 
**
*******************************************************************************/


#include "SchwarmAmbassador.h"

#ifdef _WIN32
#include <time.h>
#else
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
	//  Publish and Register Swarm objects
	//******************************************************************************

	RTI::ObjectClassHandle fishClass = myFed.rtiAmb.getObjectClassHandle ("objectRoot.Fisch");
    RTI::AttributeHandle attributePosX = myFed.rtiAmb.getAttributeHandle ("posX", fishClass);
    RTI::AttributeHandle attributePosY = myFed.rtiAmb.getAttributeHandle ("posY", fishClass);
    RTI::AttributeHandleSet *attributeList = RTI::AttributeHandleSetFactory::create(2);
    attributeList->add (attributePosX);
    attributeList->add (attributePosY);
    myFed.rtiAmb.publishObjectClass (fishClass, *attributeList);

	std::map<RTI::ObjectHandle,Fish*> swarm;
	for (int i=0; i<swarmSize; i++)
	{
		RTI::ObjectHandle id = myFed.rtiAmb.registerObjectInstance (fishClass);
		swarm[id] = new Fish();
	}

	//******************************************************************************
	//  Update Positions
	//******************************************************************************

	RTI::AttributeHandleValuePairSet* position = RTI::AttributeSetFactory::create(2);

	char* xValue = (char*) malloc(9);
	char* yValue = (char*) malloc(9);
	//position->add (attributePosX, xValue, 9);
	//position->add (attributePosY, yValue, 9);


	Value xDir, yDir;

	while (true)
	{
		std::map<RTI::ObjectHandle,Fish*>::iterator swarmIt;
		for (swarmIt=swarm.begin(); swarmIt!= swarm.end(); swarmIt++)
		{
			xDir.set (10.0*rand()/(RAND_MAX*100.0+1));
			yDir.set (10.0*rand()/(RAND_MAX*100.0+1));
			Fish* f = swarmIt->second;
			f->move(xDir,yDir);

			f->x.encode (xValue);
			f->y.encode (yValue);
			position->empty();
			position->add (attributePosX, xValue, 9);
			position->add (attributePosY, yValue, 9);

			//std::cout << *f << std::endl;
			myFed.rtiAmb.updateAttributeValues(swarmIt->first, *position, NULL );
		}
		myFed.rtiAmb.tick(0.1, 0.1);
	}




	return 0;
}


