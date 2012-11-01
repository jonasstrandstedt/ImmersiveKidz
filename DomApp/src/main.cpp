#include "sgct.h"
#include "ImmersiveKidz.h"
#include "Billboard.h"
#include "Illustration.h"

sgct::Engine * gEngine;
ImmersiveKidz *iKidz = 0;

void myDrawFun();
void myPreSyncFun();
void myEncodeFun();
void myDecodeFun();

double curr_time = 0.0;

int main( int argc, char* argv[] )
{
	// Allocate
	gEngine = new sgct::Engine( argc, argv );

	// Bind your functions
	gEngine->setDrawFunction( myDrawFun );
	gEngine->setPreSyncFunction( myPreSyncFun );
	sgct::SharedData::Instance()->setEncodeFunction(myEncodeFun);
	sgct::SharedData::Instance()->setDecodeFunction(myDecodeFun);

	// Init the engine
	if( !gEngine->init() )
	{
		delete gEngine;
		return EXIT_FAILURE;
	}

	// Allocate and initialize ImmersiveKidz
	iKidz = new ImmersiveKidz();
	iKidz->setMaster(gEngine->isMaster());
	/*
	iKidz->addDrawableObject(new Billboard());
	iKidz->addDrawableObject(new Illustration());
	iKidz->draw();
	*/
	
	// Main loop
	gEngine->render();

	// Clean up (de-allocate)
	delete iKidz;
	delete gEngine;

	// Exit program
	exit( EXIT_SUCCESS );
}

void myDrawFun()
{
	iKidz->draw();
}

void myPreSyncFun()
{
	//set the time only on the master
	if( gEngine->isMaster() )
	{
		//get the time in seconds
		iKidz->setCurr_time(sgct::Engine::getTime());
	}
}

void myEncodeFun()
{
	sgct::SharedData::Instance()->writeDouble( iKidz->getCurr_time() );
}

void myDecodeFun()
{
	double temp_d = sgct::SharedData::Instance()->readDouble();
	if (iKidz != 0)
	{
		iKidz->setCurr_time(temp_d);
	}
}