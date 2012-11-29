#include "../src/Billboard.h"

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

TEST (BillboardTest, Billtest)
{
	
	Billboard *b = new Billboard(std::string("testString"), glm::vec3(0, 0, 0), glm::vec2(0 , 0));

	EXPECT_EQ(glm::vec3(0, 0, 0),b->getPosition());

	EXPECT_EQ(glm::vec2(0 , 0),b->getProportions());

	EXPECT_EQ("testString",b->getTexture());

}