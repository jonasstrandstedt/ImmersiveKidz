#include "../src/Camera.h"

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


TEST (CameraTests, Speed) { 
    Camera *c = new Camera(glm::vec3(1,1.5,3));
	
	c->setSpeed(1);
	EXPECT_EQ(1,c->getSpeed());

	c->setSpeed(1.5);
	EXPECT_EQ(1.5,c->getSpeed());
	
	c->setSpeed(-1);
	EXPECT_EQ(0,c->getSpeed());
	
	c->setSpeed(0);
	EXPECT_EQ(0,c->getSpeed());

	c->setSpeed(3);
	EXPECT_EQ(3,c->getSpeed());
}

TEST (CameraTests, Movements) { 
    Camera *c = new Camera(glm::vec3(1,1.5,3));

	EXPECT_EQ(glm::vec3(1,1.5,3),c->getPosition());
	
	c->setSpeed(1);
	EXPECT_EQ(1,c->getSpeed());

	c->keyboardButton('W',0);
	c->update(1);
	EXPECT_EQ(glm::vec3(1,1.5,3),c->getPosition());
	
	c->keyboardButton('W',1);
	c->update(1);
	EXPECT_EQ(glm::vec3(1,1.5,2),c->getPosition());
	
	c->keyboardButton('S',1);
	c->update(1);
	EXPECT_EQ(glm::vec3(1,1.5,2),c->getPosition());
	
	c->keyboardButton('W',0);
	c->update(1);
	EXPECT_EQ(glm::vec3(1,1.5,3),c->getPosition());
	
	c->keyboardButton('S',0);
	c->update(1);
	EXPECT_EQ(glm::vec3(1,1.5,3),c->getPosition());
}