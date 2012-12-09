#ifndef SOUNDOBJECT_H
#define SOUNDOBJECT_H

#include "sgct.h"
#include "glm/glm.hpp"
#include "Illustration.h"

//include open AL
#ifdef __APPLE__
    #include <OpenAL/al.h>
    #include <ALUT/alut.h>
#else
    #include <AL/al.h>
    #include <AL/alut.h>
#endif

/**
    * @brief      A class for a Sound object of positional 3D audio in SGCT
    *
    * @details    This class has all the neccesary variables and methods for instantiating a sound. Note that it also has got a pointer to an illustration object. 
    * @author     Karl Gyllensten, kargy291@student.liu.se
	* @author     Rickard Englund, ricen256@student.liu.se
    * @date       November 29, 2012
    *
	*/
class SoundObject
{
	friend class AudioHandler;
private:
	ALuint _buffer;
	ALuint _source;
	bool _ambient;
	Illustration* _owner;
	SoundObject(){}
	void update();
public:
	virtual ~SoundObject();
	static SoundObject* CreateFromFile(const char* file,Illustration* owner = 0);
	ALuint getSoundObjectSource();
	ALuint getSoundObjectBuffer();
	bool getSoundObjectAmbient();
};

#endif // SOUNDOBJECT_H