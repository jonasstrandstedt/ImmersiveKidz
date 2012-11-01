#include "sgct.h"
#include "ImmersiveKidz.h"
#include "Billboard.h"
#include "Illustration.h"
#include "Model.h"

sgct::Engine * gEngine;
ImmersiveKidz *iKidz;

void myInitOGLFun();
void myDrawFun();
void myPreSyncFun();
void myEncodeFun();
void myDecodeFun();

int main( int argc, char* argv[] )
{
	// Allocate
	gEngine = new sgct::Engine( argc, argv );
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

	// Bind your functions
	gEngine->setInitOGLFunction( myInitOGLFun );
	gEngine->setDrawFunction( myDrawFun );
	gEngine->setPreSyncFunction( myPreSyncFun );

	// Init the engine
	if( !gEngine->init() )
	{
		delete gEngine;
		return EXIT_FAILURE;
	}
	
	// set encode and decode 
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

void myInitOGLFun() {
	// Allocate and initialize ImmersiveKidz
	iKidz = new ImmersiveKidz();
	iKidz->setMaster(gEngine->isMaster());
	//iKidz->addDrawableObject(new Model("EXTRA_LIFE.obj", "EXTRA_LIFE.png", 0.002));
	/*
	iKidz->addDrawableObject(new Billboard());
	iKidz->addDrawableObject(new Illustration());
	iKidz->draw();
	*/
	
	iKidz->loadScene();

	glCullFace(GL_BACK);
	glFrontFace(GL_CW); //our polygon winding is counter clockwise
	glEnable(GL_CULL_FACE);
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
	iKidz->encode();
}

void myDecodeFun()
{
	iKidz->decode();
}