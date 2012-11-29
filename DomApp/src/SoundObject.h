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
    * @brief      A class for handling of 3D audio in SGCT
    *
    * @details    
	*
    * @author     Karl Gyllensten, kargy291@student.liu.se
    * @date       November 20, 2012
    * @version    0.0.1
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
};

#endif // SOUNDOBJECT_H