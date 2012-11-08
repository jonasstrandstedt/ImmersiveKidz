#include "DrawableObject.h"

/**
*@brief	    DrawableObject main constructor
*
*@details   Defines the animation function to be 0.
*/
DrawableObject::DrawableObject() {
	_animationFunc = 0;
	_animationTimer = 0.0;
	
	_transform = glm::mat4x4();
}


/**
*@brief	    Animates an object
*
*@details   If the animation function is set the object will animate. TODO: Add some sort of start and stop condition
*
*@return     void
*/
void DrawableObject::draw(double t, double dt) {
	if (_animationFunc != 0)
	{
		glPushMatrix();
		_animationFunc(t, dt, _animationTimer);
	}
	
	

	//Apllying the transform matrix
	glMultMatrixf(glm::value_ptr(_transform));
	
	onDraw();
	
	if (_animationFunc != 0)
	{
		glPopMatrix();
	}
}

void DrawableObject::setAnimationFuncByName(std::string name) { 
	if ( name == "bounce" ) setAnimationFunc(bounce);
	if ( name == "pendulum" ) setAnimationFunc(pendulum);
	if ( name == "none" ) setAnimationFunc(none);
};

/**
*@brief	    Translates the object up and down
*
*@return     void
*/
void bounce(double t, double dt, double at) {
	glTranslatef(0.0f,fabsf(sin(t*2))*0.5,0.0f);
}

/**
*@brief	    Translates the object like a pendulum on the x-axis
*
*@return     void
*/
void pendulum(double t, double dt, double at) {
	glTranslatef(sin(t),0.0f,0.0f);
}

/**
*@brief	    Does nothing
*
*@return     void
*/
void none(double t, double dt, double at) {
}