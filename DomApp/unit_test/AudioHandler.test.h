#include "../src/AudioHandler.h"
#include "../src/SoundObject.h"

#include "../src/ImmersiveKidz.h"

/**
* @file CameraTests.h
* 
* @author 	Karl Gyllensten, kargy291@student.liu.se
* @date   	December 9, 2012
* @version	0.0.0.1 
*
* @brief Test for the Audiohandler class
*
* @detials  A unit test case for the Audiohandler class
*
*/

TEST (AudioHandler, audiohandler)
{
	SoundObject *s = SoundObject::CreateFromFile("boys.wav");
    SoundObject sound1 = *s;
	AudioHandler::getInstance()->addSound(SoundObject::CreateFromFile("boys.wav"));
	s = AudioHandler::getInstance()->getSoundObjectAt(0);
	SoundObject sound2 = *s;

	EXPECT_EQ(sound1.getSoundObjectBuffer(),sound2.getSoundObjectBuffer());
	EXPECT_EQ(sound1.getSoundObjectSource(),sound2.getSoundObjectSource());
	EXPECT_EQ(sound1.getSoundObjectAmbient(),sound2.getSoundObjectAmbient());
}