#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <string>
#include "sgct.h"
#include "glm/glm.hpp"
#include "DrawableObject.h"


/**
    * @brief      A class for Billboards.
    *
    * @details    This class handles the texture , the transformation(translation & scaling) and the proportions of a billboard.
	*			  " The image can be scaled to simulate perspective, rotated two dimensionally, overlapped 
	*				with other objects, and be occluded, but it can only be viewed from a single angle. 
	*				This rendering method is also referred to as billboarding."
	*
    * @author     Anders Nord, andno922@student.liu.se
	* @author     Rickard Englund, ricen256@student.liu.se
    * @date       November 10, 2012
    * @version    0.0.1
    *
	*/
class Billboard: public DrawableObject {

public:
	Billboard(std::string texturename , glm::vec3 position, glm::vec2 proportionsIn);

	void onDraw();
	
protected:
	glm::vec3 _position;
	unsigned int _texture;
	glm::vec2 _proportions;
};


#endif
