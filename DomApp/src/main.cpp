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

int main( int argc, char* argv[] )
{
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


	// Init the engine
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

void myInitOGLFun() {
	//Add font information
	if( !sgct::FontManager::Instance()->AddFont( "Verdana", "verdana.ttf" ) )
			sgct::FontManager::Instance()->GetFont( "Verdana", 14 );

	// Allocate and initialize ImmersiveKidz
	iKidz = ImmersiveKidz::getInstance();
	iKidz->setEngine(gEngine);
	iKidz->setMaster(gEngine->isMaster());
	
	iKidz->loadScene("world1");

	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW); //our polygon winding is counter clockwise
	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
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


void myKeyboardFun(int key,int state){
	iKidz->keyboardButton(key,state);
}

void myMouseMotionFun(int x,int y){
	if(prevMouseX == -1){
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

void myMouseButtonFun(int button,int state){
	iKidz->mouseButton(button,state);
}


void myPostSyncPreDrawFunction(){
	iKidz->postSyncPreDrawFunction();
}