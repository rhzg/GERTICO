/*******************************************************************************
**
** Copyright (c) Fraunhofer IITB
** All rights reserved.
**
********************************************************************************
**

$Log: BossFish.cpp,v $
Revision 1.4  2010/07/23 11:06:28  mul
Minor change.

Revision 1.3  2004/05/28 11:53:26  mul
Remove DOS line endings.

Revision 1.2  2003/11/27 12:26:18  hzg
warnings eliminated

Revision 1.1  2003/11/27 12:20:46  hzg
Fish swarm by boss concept

Revision 1.1  2003/05/16 09:45:34  hzg
initial


 
**
*******************************************************************************/


#include "SchwarmAmbassador.h"

#ifdef _WIN32
#include <time.h>
#else
#include <stdio.h>
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
	if (argc > 1)
	{
		sscanf (argv[1],"%d", &swarmSize);
	}  


	//******************************************************************************
	//  Establish Federation
	//******************************************************************************
	SchwarmAmbassador    fedAmb;         // User-defined
	Federate myFed;
	myFed.join(&fedAmb);


	//******************************************************************************
	//  Get Required Handles and prepare attribute list
	//******************************************************************************

	fedAmb.fishClass = myFed.rtiAmb.getObjectClassHandle ("objectRoot.Fisch");
    fedAmb.attributePosX = myFed.rtiAmb.getAttributeHandle ("posX", fedAmb.fishClass);
    fedAmb.attributePosY = myFed.rtiAmb.getAttributeHandle ("posY", fedAmb.fishClass);
    RTI::AttributeHandleSet *attributeList = RTI::AttributeHandleSetFactory::create(2);
    attributeList->add (fedAmb.attributePosX);
    attributeList->add (fedAmb.attributePosY);

	//******************************************************************************
	//  Subscribe Swarm class
	//******************************************************************************

    myFed.rtiAmb.subscribeObjectClassAttributes (fedAmb.fishClass, *attributeList);

	//******************************************************************************
	//  Publish Swarm class
	//******************************************************************************

    myFed.rtiAmb.publishObjectClass (fedAmb.fishClass, *attributeList);

	//******************************************************************************
	//  Give the RTI the chance to anounce existing fish objects
	//******************************************************************************

	fedAmb.theBossId = 0;
	fedAmb.theBoss = 0;
	myFed.rtiAmb.tick(0.5, 1.0);

	//******************************************************************************
	//  If no boss is detected, I create the boss fish
	//  otherwise I create a number of follower fish objects
	//******************************************************************************

	bool playingBoss = false;
	std::map<RTI::ObjectHandle,Fish*> swarm;
	if (fedAmb.theBoss == 0)
	{
		std::cout << "I'm the boss!" << std::endl;
		fedAmb.theBossId = myFed.rtiAmb.registerObjectInstance (fedAmb.fishClass);
		fedAmb.theBoss = new Fish();
		playingBoss = true;
	}
	else
	{
		std::cout << "I'm handle the followers!" << std::endl;
		for (unsigned int i=0; i<swarmSize; i++)
		{
			RTI::ObjectHandle id = myFed.rtiAmb.registerObjectInstance (fedAmb.fishClass);
			swarm[id] = new Fish();
		}
	}

	//******************************************************************************
	//  Update Positions
	//******************************************************************************

	RTI::AttributeHandleValuePairSet* position = RTI::AttributeSetFactory::create(2);

	char* xValue = (char*) malloc(9);
	char* yValue = (char*) malloc(9);

	Value xDir, yDir;

	while (true)
	{
		if (playingBoss)
		{
			// I'm responsible for the boss
			// make some random movement
			xDir.set (2.0*rand()/(RAND_MAX*100.0+1));
			yDir.set (2.0*rand()/(RAND_MAX*100.0+1));
			fedAmb.theBoss->move(xDir,yDir);

			fedAmb.theBoss->x.encode (xValue);
			fedAmb.theBoss->y.encode (yValue);
			position->empty();
			position->add (fedAmb.attributePosX, xValue, 9);
			position->add (fedAmb.attributePosY, yValue, 9);

			myFed.rtiAmb.updateAttributeValues(fedAmb.theBossId, *position, NULL );
		}
		else
		{
			// now move my swarm
			std::map<RTI::ObjectHandle,Fish*>::iterator swarmIt;
			for (swarmIt=swarm.begin(); swarmIt!= swarm.end(); swarmIt++)
			{
				Fish* f = swarmIt->second;

				xDir.set ((fedAmb.theBoss->x.get() - f->x.get())/10 - 0.015+(3.0*rand()/(RAND_MAX*100.0)));
				yDir.set ((fedAmb.theBoss->y.get() - f->y.get())/10 - 0.015+(3.0*rand()/(RAND_MAX*100.0)));

				f->move(xDir,yDir);

				f->x.encode (xValue);
				f->y.encode (yValue);
				position->empty();
				position->add (fedAmb.attributePosX, xValue, 9);
				position->add (fedAmb.attributePosY, yValue, 9);

				//std::cout << *f << std::endl;
				myFed.rtiAmb.updateAttributeValues(swarmIt->first, *position, NULL );
			}
		}
		myFed.rtiAmb.tick(0.05, 0.5);
	}

	return 0;
}


