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
	void setAnimationFunc(void (*f)(double,double,double)) { animation_func = f; };

	void setAnimationFuncByName(std::string name) { 
		if ( name == "bounce" ) setAnimationFunc(bounce);
		if ( name == "pendulum" ) setAnimationFunc(pendulum);
		if ( name == "none" ) setAnimationFunc(none);
	};

	// draw functionality
	void draw(double t, double dt);
	virtual void onDraw() = 0;
private:

protected:
	double animation_timer;
	void (*animation_func)(double, double, double);

	glm::mat4x4 transform;
};

#endif