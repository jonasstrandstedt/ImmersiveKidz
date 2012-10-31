#ifndef ILLUSTRATION_H
#define ILLUSTRATION_H

#include <string>
#include "sgct.h"
#include "Billboard.h"

class Illustration: public Billboard {

public:

	void draw();
	
private:
	std::string name_artist;
	std::string name_drawing;
	std::string description;
	bool seen;

};


#endif