#include "Animation.h"


/**
*@brief	    Animation default constructor
*
*@details   Defines the animation with frameduration and its animation type
*
*@param duration	the duration in frames
*
*@param type	the animation type name
*/
Animation::Animation(double duration, std::string type)
{
	_duration = duration * 60;
	_frame = 0;
	_type = type;
}

/**
*@brief	    Animate function
*
*@details   Checks if the current _frame is at the maximum _duration and animate it depending on its _type
*
*/
bool Animation::animate()
{
	if ( _frame >= _duration)
	{
		return false;
	}

	if ( _type == "jump" ) glTranslatef(0.0f,fabsf(sin((_frame*3.14)/_duration))*0.5,0.0f);
	if ( _type == "strafe" ) glTranslatef(sin((_frame*3.14)/_duration),0.0f,0.0f);

	_frame++;
	return true;
}

