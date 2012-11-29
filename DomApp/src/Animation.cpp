#include "Animation.h"


/**
*@brief	    Animation default constructor
*
*@details   Defines the animation with frameduration and its animation type
*
*@param duration	the duration in frames
*/
Animation::Animation(double duration)
{
	_duration = duration * 60;
	_frame = 0;
	
}

/**
*@brief	    Animate function
*
*@details   Checks if the current _frame is at the maximum _duration and animate it with doAnimate();
*
*/
bool Animation::animate()
{
	if ( _frame >= _duration)
	{
		return false;
	}

	doAnimate();

	_frame++;
	return true;
}

/**
*@brief	    Jump animation
*
*@details   Make the selected object jump over a duration
*
* @param	duration		The time for how long the animation will be active
*/
Jump::Jump(double duration):Animation(duration)
{

}

/**
*@brief	    Jump animation function
*
*@details   The animation function for jump
*
*/
void Jump::doAnimate()
{
	glTranslatef(0.0f,fabsf(sin((_frame*3.14)/_duration))*0.5,0.0f);
}

/**
*@brief	    Strafe animation
*
*@details   Make the selected object strafe over a duration
*
* @param	duration		The time for how long the animation will be active
*/
Strafe::Strafe(double duration):Animation(duration)
{

}

/**
*@brief	    Strafe animation function
*
*@details   The animation function for strafe
*
*/
void Strafe::doAnimate()
{
	glTranslatef(sin((_frame*3.14)/_duration),0.0f,0.0f);
}
