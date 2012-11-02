#include "DrawableObject.h"

/**
*@brief	    DrawableObject main constructor
*
*@details   Defines the animation function to be 0.
*/
DrawableObject::DrawableObject() {
	animation_func = 0;
	animation_timer = 0.0;
}

/**
*@brief	    Animates an object
*
*@details   If the animation function is set the object will animate. TODO: Add some sort of start and stop condition
*
*@return     void
*/
void DrawableObject::animate(double t, double dt) {
	if (animation_func != 0)
	{
		glPushMatrix();
		animation_func(t, dt, animation_timer);
	}
}

/**
*@brief	    If the object animates, pop dat matrix!
*
*@return     void
*/
void DrawableObject::postAnimate() {
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