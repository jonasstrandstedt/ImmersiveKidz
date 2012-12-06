#ifndef _RUN_TESTS_AT_STARTUP_

#ifdef _RUN_TESTS_
int runUnitTests(int argc, char **argv);
#endif

#include "sgct.h"
#include "ImmersiveKidz.h"

sgct::Engine * gEngine;
ImmersiveKidz *iKidz;

void myInitOGLFun();
void myDrawFun();
void myPreSyncFun();
void myEncodeFun();
void myDecodeFun();
void myPostSyncPreDrawFunction();

void myKeyboardFun(int,int);
void myMouseMotionFun(int,int);
void myMouseButtonFun(int,int);

int prevMouseX = -1;
int prevMouseY = -1;
bool stereo = true;
float eyeSeparation = 0.0f;

int main( int argc, char* argv[] )
{
#ifdef _RUN_TESTS_
	if(runUnitTests(argc, argv ))
	{
		std::cin.get();
	}
#endif

	// Allocate
	gEngine = new sgct::Engine( argc, argv );
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

	// Bind your functions
	gEngine->setInitOGLFunction( myInitOGLFun );
	gEngine->setDrawFunction( myDrawFun );
	gEngine->setPreSyncFunction( myPreSyncFun );
	gEngine->setKeyboardCallbackFunction(myKeyboardFun);
	gEngine->setMousePosCallbackFunction(myMouseMotionFun);
	gEngine->setMouseButtonCallbackFunction(myMouseButtonFun);
	gEngine->setPostSyncPreDrawFunction(myPostSyncPreDrawFunction);
	
	// Init the sgct engine
	if( !gEngine->init() )
	{
		delete gEngine;
		return EXIT_FAILURE;
	}
	
	// set encode and decode (after init to prevent segmentationfault from decode function)
	sgct::SharedData::Instance()->setEncodeFunction(myEncodeFun);
	sgct::SharedData::Instance()->setDecodeFunction(myDecodeFun);

	// Main loop
	gEngine->render();

	// Clean up (de-allocate)
	delete iKidz;
	sgct::TextureManager::Destroy();
	delete gEngine;

	// Exit program
	exit( EXIT_SUCCESS );
}

void myInitOGLFun()
{
	//sets far plane bigger than 100f which is default
	gEngine->setNearAndFarClippingPlanes(gEngine->getNearClippingPlane(),600.0);	

	// get the eye spearation to allow use of toggle
	eyeSeparation = gEngine->getUserPtr()->getEyeSeparation();

	// init the ImmeriveKidz engine
	iKidz = ImmersiveKidz::getInstance();
	iKidz->setMaster(gEngine->isMaster());
	iKidz->init();
	
}


void myDrawFun()
{
	iKidz->draw();
}

void myPreSyncFun()
{
	iKidz->preSyncFunc();
}

void myEncodeFun()
{
	sgct::SharedData::Instance()->writeBool( stereo );
	iKidz->encode();
}

void myDecodeFun() 
{
	stereo = sgct::SharedData::Instance()->readBool();
	iKidz->decode();
}


void myKeyboardFun(int key,int state)
{
	iKidz->keyboardButton(key,state);

	if(gEngine->isMaster() && state == GLFW_PRESS) 
	{
		if(key == 'P') gEngine->takeScreenshot();
		if(key == 'X') stereo = !stereo;
	}
}

void myMouseMotionFun(int x,int y)
{
	if(prevMouseX == -1)
	{
		prevMouseX = x;
		prevMouseY = y;
		return;
	}
	int dx,dy;
	dx = x - prevMouseX;
	dy = y - prevMouseY;
	iKidz->mouseMotion(x,y,dx,dy);
	prevMouseX = x;
	prevMouseY = y;
}

void myMouseButtonFun(int button,int state)
{
	iKidz->mouseButton(button,state);
}

void myPostSyncPreDrawFunction()
{
	stereo ? gEngine->getUserPtr()->setEyeSeparation( eyeSeparation ) : gEngine->getUserPtr()->setEyeSeparation( 0.0f );
	iKidz->postSyncPreDrawFunction();
}

#endif
