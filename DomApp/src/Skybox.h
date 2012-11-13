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
    * @brief      Skybox class for rendering a skybox.
    *
    * @details    Skybox is a subclass to DrawableObject and overwrites the onDraw method.
	*
    * @author     Karl Gyllensten, kargy291@student.liu.se
    * @date       November 9, 2012
    * @version    0.0.1
    *
	*/
class Skybox: public DrawableObject {

public:
	Skybox(){}
	void loadTextures(std::string textureNames[6]);
	void onDraw();
	
private:
	std::string texturename;
	void drawCube();
};


#endif