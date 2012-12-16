#ifndef MULTOBJECT_H
#define MULTOBJECT_H

#include <string>
#include "sgct.h"
#include "glm/glm.hpp"
#include <glm/gtx/random.hpp>
#include "DrawableObject.h"

enum MultType{
	BILLBOARD = 0,
	DUAL,
	SINGLE
};

/**
* @brief  	A container class for a multiplied objekt
*
* @details	The object inserted must have a vertex and triangle list defined, the 
*			constructor of MultObject will fetch the arrays and create a new 
*			internally object that is consisting of multiple objects inside one 
*			triangle list.
*
* @author 	Jonas Strandstedt, jonast184@student.liu.se
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class MultObject: public DrawableObject {
public:
	MultObject(DrawableObject *obj, std::vector< std::vector<bool> > *mask, int seed, int count, int type, glm::vec2 altitude);
	void onDraw();
	const char* getTypeName(int type);
private:
	GLint _angle_loc;
	GLint _campos_loc;
	int _billboard_loc;
	int _type;
};


#endif
