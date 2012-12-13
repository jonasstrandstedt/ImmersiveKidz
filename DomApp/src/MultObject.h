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

class MultObject: public DrawableObject {

public:
	MultObject(DrawableObject *obj, std::vector< std::vector<bool> > *mask, int seed, int count, int type, glm::vec2 altitude);
	void onDraw();
protected:
	std::string _texture;
private:
	GLuint _listid;
	bool _billboard;
	GLint _angle_loc;
	GLint _campos_loc;
	int _billboard_loc;
	int _type;
};


#endif
