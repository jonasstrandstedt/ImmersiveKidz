#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <string>
#include "sgct.h"
#include "glm/glm.hpp"
#include "DrawableObject.h"

class Billboard: public DrawableObject {

public:
	void draw();
	
private:
	std::string texture;
	glm::mat4x4 transform;
	glm::vec2 proportions;
};


#endif