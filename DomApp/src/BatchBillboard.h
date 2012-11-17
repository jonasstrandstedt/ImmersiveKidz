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
    * @details    This class handles the texture , the transformation(translation & scaling) and the proportions of a billboard.
	*			  " The image can be scaled to simulate perspective, rotated two dimensionally, overlapped 
	*				with other objects, and be occluded, but it can only be viewed from a single angle. 
	*				This rendering method is also referred to as billboarding."
	*
    * @author     Anders Nord, andno922@student.liu.se
	* @author     Rickard Englund, ricen256@student.liu.se
    * @date       November 10, 2012
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
};


#endif
