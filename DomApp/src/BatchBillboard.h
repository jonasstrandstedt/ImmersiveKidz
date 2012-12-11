#ifndef BATCHBILLBOARD_H
#define BATCHBILLBOARD_H

#include <string>
#include "sgct.h"
#include "glm/glm.hpp"
#include <glm/gtx/random.hpp>
#include "DrawableObject.h"


/**
    * @brief      A class for Billboards.
    *
    * @details    This class handles rendering of objects that are used several times in one scene. It 
	*
    * @author     Jonas Strandstedt, jonst184@student.liu.se
	* @author 	  Viktor Nilsson, vikni067@student.liu.se
    * @date       November 17, 2012
    * @version    0.0.1
    *
	*/
class BatchBillboard: public DrawableObject {

public:
	BatchBillboard(std::string texturename, std::vector <std::vector<bool> > *mask, int seed, int count, glm::vec2 proportionsIn, bool billboard = false, glm::vec2 altitude = glm::vec2());
	void onDraw();
protected:
	std::string _texture;
private:
	GLuint _listid;
	bool _billboard;
	GLint _angle_loc;
	GLint _campos_loc;
};


#endif
