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
	//OBS!!!
	//Billboard calls OpenGL in constructor
    /*Illustration *i = new Illustration("data/HUD/minimap.png", glm::vec3(1.0,1.0,1.0), glm::vec2(1.0,1.0), "Testname", "animal", "description");
	
	EXPECT_EQ("Testname",i->getName());
	EXPECT_EQ(0,i->getSeen()); // 0 == false*/
}

TEST (IllustrationTests, Seen) 
{ 

   /* Illustration *i = new Illustration("data/HUD/minimap.png", glm::vec3(1.0,1.0,1.0), glm::vec2(1.0,1.0), "Testname", "animal", "description");
	EXPECT_EQ(0,i->getSeen()); // 0 == false
	
	i->setSeen(1); // 1 == true
	EXPECT_EQ(1,i->getSeen()); // 1 == true
	
	i->setSeen(0); // 0 == false
	EXPECT_EQ(0,i->getSeen()); // 0 == false*/
}
