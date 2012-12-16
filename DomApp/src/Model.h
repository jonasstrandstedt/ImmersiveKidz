#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "sgct.h"
#include "DrawableObject.h"



/**
* @brief  	A container class for a object
*
* @details	A object defined by a wavefront obj model and a png texture.
*
* @author 	Jonas Strandstedt, jonast184@student.liu.se
* @author	Viktor Nilsson, vikni067@student.liu.se
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class Model: public DrawableObject 
{
public:
	Model(std::string filename, std::string texturename, glm::vec3 position = glm::vec3(0.0,0.0,0.0), float scale = 1.0, glm::vec3 rotation = glm::vec3(0.0,0.0,0.0));
	
	void onDraw();
private:
	// Variables used for rendering

	float _scale;
    
	void initVBO(Vertex **varray, int **iarray, int vertexsize, int indexsize);
	void loadObj(const char *filename);
	
};


#endif