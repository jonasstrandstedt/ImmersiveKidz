#include "DrawableObject.h"

/**
*@brief	    DrawableObject main constructor
*
*@details   Defines the animation function to be 0.
*/
DrawableObject::DrawableObject() {
	animation_func = 0;
	animation_timer = 0.0;
	
	transform = glm::mat4x4();
}


/**
*@brief	    Animates an object
*
*@details   If the animation function is set the object will animate. TODO: Add some sort of start and stop condition
*
*@return     void
*/
void DrawableObject::draw(double t, double dt) {
	if (animation_func != 0)
	{
		glPushMatrix();
		animation_func(t, dt, animation_timer);
	}
	
	

	//Apllying the transform matrix
	glMultMatrixf(glm::value_ptr(transform));
	
	onDraw();
	
	if (animation_func != 0)
	{
		glPopMatrix();
	}
}


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