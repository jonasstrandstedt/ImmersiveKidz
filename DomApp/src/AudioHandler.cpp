#include "AudioHandler.h"
#include "ImmersiveKidz.h"

AudioHandler* AudioHandler::_instance = 0;

/**
*@brief	    AudioHandler singleton getInstance class. Returns the instance if already instanciated.
*@return	AudioHandler*
*/
AudioHandler* AudioHandler::getInstance(){
	//WARNING - NOT THREAD SAFE
	if(_instance == 0)
		_instance = new AudioHandler();
	return _instance;
}

/**
*@brief	    AudioHandler default constructor
*/
AudioHandler::AudioHandler(){}

/**
*@brief	    AudioHandler init class. Initializes alut.
*/
void AudioHandler::init()
{
#ifndef NO_SOUND
	alutInit(NULL, 0);
	//Check for errors if any
	sgct::MessageHandler::Instance()->print("ALUT init: %s\n", alutGetErrorString( alutGetError() ));
#endif
}

/**
*@brief	   Audiohandler add sound method.
*@detailed  Adds a sound to the vector containing soundobjects
*/
void AudioHandler::addSound(SoundObject* sound)
{
#ifndef NO_SOUND
	sounds.push_back(sound);
#endif
}

/**
*@brief	   Audiohandler update method
*@detailed  Updates how the sound will be perceived depending on positions of the camera and sound objects, 
*	the camera alignment and what kind of sound it is. Uses the update function in Sound object.
*/
void AudioHandler::update()
{
#ifndef NO_SOUND
	//set the listeners properties
	glm::vec3 userPos = ImmersiveKidz::getInstance()->getCamera()->getPosition()+sgct::Engine::getUserPtr()->getPos();
	glm::vec4 at(0,0,1,0);
	glm::vec4 up(0,1,0,0);


	glm::vec2 rot = ImmersiveKidz::getInstance()->getCamera()->getRotation();
	glm::mat4 rotations = glm::rotate(glm::mat4(),rot[1],glm::vec3(1.0f,0.0f,0.0f));
 	rotations = glm::rotate(rotations,rot[0],glm::vec3(0.0f,1.0f,0.0f));
	at = rotations * at;
	up = rotations * up;

	ALfloat ori[6] = {at.x,at.y,at.z,up.x,up.y,up.z};


	
	alListener3f(AL_POSITION, userPos.x, userPos.y, userPos.z);
	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION,ori);
	for(unsigned int i = 0; i < sounds.size();i++)
	{
		sounds[i]->update();
	}
	//set the audio source's properties
#endif
}

/**
*@brief		Audiohandler getSoundObjectAt method
*@detailed	Gets the sound object at a specified position in the vector containing all sounds.
*@param i	integer of which position of interest
*@return SoundObject*
*/
SoundObject* AudioHandler::getSoundObjectAt(unsigned int i) 
{
	if(sounds.size() <= i)
		return new SoundObject();
#ifndef NO_SOUND
	return sounds.at(i);
#endif
	return new SoundObject();
}

/**
*@brief		Audiohandler getSounds method
*@detailed	Gets the sound objects vector
*@return std::vector<SoundObject*>
*/
std::vector<SoundObject*> AudioHandler::getSounds()
{
	return sounds;
}


/**
*@brief		Audiohandler playSound method
*@detailed	Plays the sound. If it's a background sound: loop.
*/
void AudioHandler::playSound(SoundObject* s)
{
#ifndef NO_SOUND
	if(s->_ambient)
	{
		alSourcei(s->_source, AL_LOOPING, AL_TRUE);
		alSourcePlay(s->_source);
	}
	else
	{
		alSourcei(s->_source, AL_LOOPING, AL_FALSE);
		alSourcePlay(s->_source);
	}
#endif
}

/**
*@brief		Audiohandler pauseSound method
*@detailed	pauses the sound.
*/
void AudioHandler::pauseSound(SoundObject* s)
{
#ifndef NO_SOUND
	alSourcePause(s->_source);
#endif
}

/**
*@brief		Audiohandler stopSound method
*@detailed	stops the sound.
*/
void AudioHandler::stopSound(SoundObject* s)
{
#ifndef NO_SOUND
	alSourceStop(s->_source);
#endif
}

/**
*@brief		Audiohandler myCleanUpFun
*@detailed	deletes the vector containing the sounds and exits alut.
*/
void AudioHandler::myCleanUpFun()
{
#ifndef NO_SOUND
	while(sounds.size()){
		delete sounds.back();
		sounds.pop_back();
	}
	alutExit();
#endif
}

