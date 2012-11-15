#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "sgct.h"

// animate functions
void bounce(double t, double seed);
void pendulum(double t, double seed);
void none(double t, double seed);

/**
* @brief  	An abstract class for objects that can be rendered
*
* @details	The subclasses must implement the draw function.
*
* @author 	Jonas Strandstedt, jonast184@student.liu.se
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class DrawableObject {
public:
	//initializers
	DrawableObject();
	
	void setAnimationFunc(void (*f)(double,double), double seed) { _animationFunc = f; _seed = seed; };
	void setAnimationFuncByName(std::string name, double seed);

	// draw functionality
	void draw(double t);
	virtual void onDraw() = 0;
private:

protected:
	double _seed;
	void (*_animationFunc)(double, double);

	glm::mat4x4 _transform;
};

#endif