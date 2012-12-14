#ifndef PLANE_H
#define PLANE_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "sgct.h"
#include "DrawableObject.h"

/**
* @brief  	A container class for a plane (not an airplane)
*
* @details	The plain created will has its local coordinate 
*			system in the bottom left corner and will be in the xz-plane.
*
* @author 	Jonas Strandstedt, jonast184@student.liu.se
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class Plane: public DrawableObject {
public:
	Plane(std::string texture, glm::vec2 size, glm::vec3 position = glm::vec3(0.0,0.0,0.0), glm::vec3 rotation = glm::vec3(0.0,0.0,0.0));
	void onDraw();
private:
	glm::vec2 _size;
};


#endif