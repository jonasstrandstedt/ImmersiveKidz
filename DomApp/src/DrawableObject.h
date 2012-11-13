#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "sgct.h"

// animate functions
void bounce(double t, double dt, double at);
void pendulum(double t, double dt, double at);
void none(double t, double dt, double at);

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
	
	void setAnimationFunc(void (*f)(double,double,double)) { _animationFunc = f; };
	void setAnimationFuncByName(std::string name);

	// draw functionality
	void draw(double t, double dt);
	virtual void onDraw() = 0;
private:

protected:
	double _animationTimer;
	void (*_animationFunc)(double, double, double);

	glm::mat4x4 _transform;
};

#endif