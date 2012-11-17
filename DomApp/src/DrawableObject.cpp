#include "DrawableObject.h"

/**
*@brief	    DrawableObject default constructor
*
*@details   Defines the animation function to be 0.
*/
DrawableObject::DrawableObject() {
	_animationFunc = 0;
	_seed = 0;
	
	_transform = glm::mat4x4();
}


/**
*@brief	    Animates an object
*
*@details   If the animation function is set the object will animate. TODO: Add some sort of start and stop condition
*
*@param t	 The time 
*
*@return     void
*/
void DrawableObject::draw(double t) {

	// pre-animate
	if (_animationFunc != 0)
	{
		glPushMatrix();
		_animationFunc(t, _seed);
	}
	glPushMatrix();
	//Appllying the transform matrix
	glMultMatrixf(glm::value_ptr(_transform));
	
	// calls the virtual onDraw function.
	onDraw();
	glPopMatrix();
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
*@param		name		The name for the wanted animation, example "bounce"
*
*@return     void
*/
void DrawableObject::setAnimationFuncByName(std::string name, double seed) { 
	if ( name == "bounce" ) setAnimationFunc(bounce, seed);
	if ( name == "pendulum" ) setAnimationFunc(pendulum, seed);
	//if ( name == "none" ) setAnimationFunc(none, seed);
};

/**
*@brief	    Translates the object up and down
*
*@return     void
*/
void bounce(double t, double seed) {
	// translates the object up and down along the y-axis (never below 0)
	t += seed;
	glTranslatef(0.0f,fabsf(sin(t*2))*0.5,0.0f);
}

/**
*@brief	    Translates the object like a pendulum on the x-axis
*
*@return     void
*/
void pendulum(double t, double seed) {
	// translates the object side to side along the x-axis
	t += seed;
	glTranslatef(sin(t),0.0f,0.0f);
}

/**
*@brief	    Does nothing
*
*@param t
*@param seed
*
*@return     void
*/
void none(double t, double seed) {
	// dafuq?! :D
}