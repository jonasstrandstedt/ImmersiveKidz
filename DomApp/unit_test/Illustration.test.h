#include "../src/Illustration.h"

#include "../src/ImmersiveKidz.h"

/**
* @file Illustration.h
* 
* @author 	Jonas Strandstedt jonst184@student.liu.se
* @date   	November 29, 2012
*
* @brief Tests the illustration class
*
* @detials  A unit test case for the illustration class
*
*/
TEST (IllustrationTests, Constructors) 
{ 

    Illustration *i = new Illustration("data/HUD/minimap.png", glm::vec3(1.0,1.0,1.0), glm::vec2(1.0,1.0), "Testname", "animal", "description");
	/*
	EXPECT_EQ("Testname",i->getName());
	EXPECT_EQ(false,i->getSeen());
	
	i->setSeen(true);
	EXPECT_EQ(true,i->getSeen());
	*/
}
