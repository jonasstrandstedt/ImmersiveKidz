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

	// pre-animate
	if (_animationFunc != 0)
	{
		glPushMatrix();
		_animationFunc(t, dt, _animationTimer);
	}
	
	//Appllying the transform matrix
	glMultMatrixf(glm::value_ptr(_transform));
	
	// calls the virtual onDraw function.
	onDraw();
	
	// post-animate
	if (_animationFunc != 0)
	{
		glPopMatrix();
	}
}

/**
*@brief	    Sets the animation function by name
*
*@details   Given a name (string) it sets the permanent animation for the object, in case the given animation does not exist nothing happens.
*
*@param		name The name for the wanted animation, example "bounce"
*
*@return     void
*/
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
	// translates the object up and down along the y-axis (never below 0)
	glTranslatef(0.0f,fabsf(sin(t*2))*0.5,0.0f);
}

/**
*@brief	    Translates the object like a pendulum on the x-axis
*
*@return     void
*/
void pendulum(double t, double dt, double at) {
	// translates the object side to side along the x-axis
	glTranslatef(sin(t),0.0f,0.0f);
}

/**
*@brief	    Does nothing
*
*@return     void
*/
void none(double t, double dt, double at) {
	// dafuq?! :D
}