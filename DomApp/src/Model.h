#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "sgct.h"
#include "DrawableObject.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

typedef struct
{
	GLfloat location[3];
	GLfloat tex[2];
	GLfloat normal[3];
	GLfloat colour[4];
	GLubyte padding[16]; // Pads the struct out to 64 bytes for performance increase
} Vertex;

/**
* @brief  	A container class for a object
*
* @details	A object defined by a wavefront obj model and a png texture.
*
* @author 	Jonas Strandstedt, jonast184@student.liu.se
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class Model: public DrawableObject {
public:
	Model(const char *filename, const char *texturename, float scale = 1.0, glm::vec3 rotation = glm::vec3(0.0,0.0,0.0), glm::vec3 base_color = glm::vec3(1.0,1.0,1.0));
	~Model() {};
	
	void draw();
	
	void initVBO(Vertex **varray, int **iarray, int vertexsize, int indexsize);
	void loadObj(const char *filename, float scale = 1.0, glm::vec3 rotation = glm::vec3(0.0,0.0,0.0), glm::vec3 base_color = glm::vec3(1.0,1.0,1.0));
		
	
private:
	// Variables used for rendering
	GLuint vBufferID;
    GLuint iBufferID;
	int isize;
	int vsize;
	unsigned int myTextureIndex;
    

};


#endif