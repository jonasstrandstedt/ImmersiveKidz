#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <string>
#include "sgct.h"
#include "glm/glm.hpp"
#include "DrawableObject.h"


/**
    * @brief      Short class description.
    *
    * @details    Verbose description of class details.
	*
    * @author     Fred McClurg, fred-mcclurg@uiowa.edu
	* @author     hej, hej-mcclurg@uiowa.edu
    * @date       June 10, 2020
    * @version    1.2.0.1 (alpha)
    *
	*/
class Billboard: public DrawableObject {

public:
	Billboard(){};
	Billboard(std::string texturename , glm::vec3 position, glm::vec2 proportionsIn);

	void draw();
	
protected:
	std::string texture;
	glm::mat4x4 transform;
	glm::vec2 proportions;
};


#endif
