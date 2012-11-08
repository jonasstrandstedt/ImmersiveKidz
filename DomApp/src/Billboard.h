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
    * @author     Fred McClurg, fred-mcclurg@uiowa.edu
	* @author     hej, hej-mcclurg@uiowa.edu
    * @date       June 10, 2020
    * @version    1.2.0.1 (alpha)
    *
	*/
class Billboard: public DrawableObject {

public:
	Billboard(std::string texturename , glm::vec3 position, glm::vec2 proportionsIn);

	void onDraw();
	
protected:
	std::string texture;
	glm::vec2 proportions;
};


#endif
