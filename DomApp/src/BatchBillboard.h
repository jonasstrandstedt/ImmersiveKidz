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
    * @date       November 17, 2012
    * @version    0.0.1
    *
	*/
class BatchBillboard: public DrawableObject {

public:
	BatchBillboard(std::string texturename, glm::vec3 pos_min, glm::vec3 pos_max, int seed, int count, glm::vec2 proportionsIn, bool billboard = false);
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
