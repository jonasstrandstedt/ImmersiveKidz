#ifndef SKYBOX_H
#define SKYBOX_H

#include "sgct.h"
#include "glm/glm.hpp"
#include "DrawableObject.h"

#define CUBEMAP_TEX_X_POSITIVE 0
#define CUBEMAP_TEX_X_NEGATIVE 1
#define CUBEMAP_TEX_Y_POSITIVE 2
#define CUBEMAP_TEX_Y_NEGATIVE 3
#define CUBEMAP_TEX_Z_POSITIVE 4
#define CUBEMAP_TEX_Z_NEGATIVE 5




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
	Skybox();
	void loadTextures(std::string textureNames[6]);
	void onDraw();
	
private:
	std::string texturename;
	void drawCube();
	//;
};


#endif