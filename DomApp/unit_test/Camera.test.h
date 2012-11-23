#include "../src/Camera.h"

#include "../src/ImmersiveKidz.h";

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


TEST (CameraTests, Speed) 
{ 

    Camera *c = new Camera(glm::vec3(1,1.5,3));
	c->setLimitsX(glm::vec2(-10,10));
	c->setLimitsY(glm::vec2(-10,10));
	c->setLimitsZ(glm::vec2(-10,10));
	
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

TEST (CameraTests, Movements) 
{ 
    Camera *c = new Camera(glm::vec3(1,1.5,3));
	c->setLimitsX(glm::vec2(-10,10));
	c->setLimitsY(glm::vec2(-10,10));
	c->setLimitsZ(glm::vec2(-10,10));

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

	c->keyboardButton('Q',1);
	c->update(1);
	EXPECT_EQ(glm::vec3(1,2.5,3),c->getPosition());
	
	c->keyboardButton('Q',0);
	c->keyboardButton('E',1);
	c->update(1);
	c->update(1);
	EXPECT_EQ(glm::vec3(1,0.5,3),c->getPosition());
	c->keyboardButton('E',0);
	
	c->keyboardButton('A',1);
	c->update(1);
	c->update(1);
	EXPECT_EQ(glm::vec3(-1,0.5,3),c->getPosition());
	c->keyboardButton('E',0);
	
	c->keyboardButton('A',0);
	c->keyboardButton('D',1);
	c->update(1);
	c->update(1);
	EXPECT_EQ(glm::vec3(1,0.5,3),c->getPosition());
	c->keyboardButton('D',0);

	
	c->keyboardButton('W',1);
	c->update(200);
	EXPECT_EQ(glm::vec3(1,0.5,-10),c->getPosition());
	c->keyboardButton('W',0);
}