#include "../src/HUD.h"

#include "../src/ImmersiveKidz.h"

/**
* @file CameraTests.h
* 
* @author 	Rickard Englund, gefle.rickard@gmail.com
* @date   	November 9, 2012
* @version	0.0.0.1 
*
* @brief Tests the camera class
*
* @detials  A unit test case for the camera class
*
*/

TEST (HUDtest, minimap)
{
	
	HUD *h = new HUD();

	EXPECT_EQ(200,h->getMinimapWidth());

	EXPECT_EQ(200,h->getMinimapWidth());

	EXPECT_EQ(0,h->getSelection());

	//EXPECT_EQ(0.2,h->_zoom); Create a getZoom func


	
	h->setTextureMinimap("testtesttest");
	
	EXPECT_EQ("testtesttest",h->getMinimapTextureName());
	
}