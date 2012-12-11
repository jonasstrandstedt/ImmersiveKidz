#include "SoundObject.h"
#include "AudioHandler.h"
#include "ImmersiveKidz.h"



/**
*@brief	    SoundObject creation method. 
*
*@detailed	The method reads a .wav-file and with it, instanciates a Sound object. If it's a background object it won't get a owner. 
*
*@return	SoundObject*
*/
SoundObject* SoundObject::CreateFromFile(const char* fileName, Illustration* owner){

	SoundObject* s = new SoundObject();
#ifndef NO_SOUND
	s->_buffer = AL_NONE;
	alGenBuffers(1, &s->_buffer);
	alGenSources(1, &s->_source);
 
	s->_buffer = alutCreateBufferFromFile(fileName);
	if(s->_buffer == AL_NONE )
	{
		sgct::MessageHandler::Instance()->print("Failed to read audio file '%s', error: %s\n", fileName, alutGetErrorString( alutGetError() ));
	}
	alSourcei(s->_source, AL_BUFFER, s->_buffer);
	s->_owner = owner;

	s->_ambient = owner == 0;
	
	alSourcef(s->_source, AL_PITCH, 1.0f);
	alSourcef(s->_source, AL_GAIN, 1.0f);
	alSource3f(s->_source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);

#endif
	return s;
}


/**
*@brief	    SoundObject update method.
*
*@detailed	Updates the position of the sound. If it is a background sound it follows the camera. Otherwise it gets the owners position. 
*/
void SoundObject::update(){

#ifndef NO_SOUND
	glm::vec3 pos;
	if(_ambient){
		pos = sgct::Engine::getUserPtr()->getPos() + ImmersiveKidz::getInstance()->getCamera()->getPosition();
	}
	else{
		pos = _owner->getPosition();
	}
	alSource3f(_source, AL_POSITION, pos.x, pos.y, pos.z);

#endif
}


/**
*@brief	    SoundObject destructor
*/
SoundObject::~SoundObject()
{
#ifndef NO_SOUND
	alDeleteSources(1, &_buffer);
	alDeleteBuffers(1, &_buffer);
#endif
}


/**
*@brief	    Returns the value of the sound buffer. 
*
*@return	ALuint
*/
ALuint SoundObject::getSoundObjectBuffer()
{
	return _buffer;
}

/**
*@brief	    Returns the value of the sound source. 
*
*@return	ALuint
*/
ALuint SoundObject::getSoundObjectSource()
{
	return _source;
}

/**
*@brief	    Returns the value of the bool that tells if it's a background sound or not. 
*
*@return	bool
*/
bool SoundObject::getSoundObjectAmbient()
{
	return _ambient;
}
