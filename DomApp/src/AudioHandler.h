#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H


#include "sgct.h"
#include "glm/glm.hpp"
#include "SoundObject.h"
//include open AL
#ifdef __APPLE__
    #include <OpenAL/al.h>
    #include <ALUT/alut.h>
#else
    #include <AL/al.h>
    #include <AL/alut.h>
#endif

/**
    * @brief      A class for handling of 3D audio in SGCT
    *
    * @details    
	*
    * @author     Karl Gyllensten, kargy291@student.liu.se
    * @date       November 20, 2012
    * @version    0.0.1
    *
	*/
class AudioHandler{
private:
	
	AudioHandler();
	static AudioHandler* _instance;
public:
	static AudioHandler* getInstance();
	void addSound(SoundObject* sound);
	void setAudioSource(ALuint &buffer, ALuint &source, char * filename);
	void myCleanUpFun();
	void init();
	void update();
	void playSound(SoundObject* s);
	void pausSound(SoundObject* s);
	void stopSound(SoundObject* s);
	std::vector<SoundObject*> getSounds();
	
protected:
	std::vector<SoundObject*> sounds;
	std::vector<ALuint> backgroundBuffers;
	std::vector<ALuint> backgroundSources;
	glm::vec4 audioPos;
};


#endif