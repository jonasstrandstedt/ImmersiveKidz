#include "AudioHandler.h"
#include "ImmersiveKidz.h"

AudioHandler* AudioHandler::_instance = 0;
AudioHandler* AudioHandler::getInstance(){
	//WARNING - NOT THREAD SAFE
	if(_instance == 0)
		_instance = new AudioHandler();
	return _instance;
}
AudioHandler::AudioHandler()
{
	
}
void AudioHandler::init()
{
	alutInit(NULL, 0);
	//Check for errors if any
	sgct::MessageHandler::Instance()->print("ALUT init: %s\n", alutGetErrorString( alutGetError() ));
}
void AudioHandler::addSound(SoundObject* sound)
{
	sounds.push_back(sound);
}

void AudioHandler::update()
{
	//set the listeners properties
	glm::vec3 userPos = ImmersiveKidz::getInstance()->getCamera()->getPosition()+sgct::Engine::getUserPtr()->getPos();
	ALfloat ori[6] = {1,0,0,0,1,0};
	
	alListener3f(AL_POSITION, userPos.x, userPos.y, userPos.z);
	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	//alListenerfv(AL_ORIENTATION,ori);
	for(int i = 0; i < sounds.size();i++)
	{
		sounds[i]->update();
	}
	//set the audio source's properties

}

std::vector<SoundObject*> AudioHandler::getSounds()
{
	return sounds;
}

void AudioHandler::playSound(SoundObject* s)
{
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
}

void AudioHandler::pausSound(SoundObject* s)
{
	alSourcePause(s->_source);
}

void AudioHandler::stopSound(SoundObject* s)
{
	alSourceStop(s->_source);
}


void AudioHandler::myCleanUpFun()
{
	while(sounds.size()){
		delete sounds.back();
		sounds.pop_back();
	}
	alutExit();
}

