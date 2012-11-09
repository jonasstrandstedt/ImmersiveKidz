#ifndef SKYBOX_H
#define SKYBOX_H

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
class Skybox: public DrawableObject {

public:
	Skybox(std::string texturename, int size);

	void draw();
	
private:
	std::string texturename;
	int size;
	void drawCube(int size);
	//void initSkybox();
};


#endif