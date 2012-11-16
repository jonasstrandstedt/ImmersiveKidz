#ifndef PLANE_H
#define PLANE_H

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
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class Plane: public DrawableObject {
public:
	Plane(glm::vec4 bounds, std::string texture, float y = 0.0);
	void onDraw();
private:
	std::string _texture;
	glm::vec4 _bounds;
	float _y;
};


#endif