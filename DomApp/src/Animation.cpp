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
*@brief	    Animation reconstruct constructor
*
*@details   Used by the decode function to reconstruct the Animation object on the slaves
*
*@param 	duration	the duration in frames
*@param 	frame	Number of frames animated
*/
Animation::Animation(int duration, int frame) {
	_duration = duration;
	_frame = frame;
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
*@brief	    Decodes the Animation object on the slaves
*
*@details   Decodes the data and recreates a shiny new Animation object
*
*@param		data	The SGCT sharedData object.
*
*@return	An subclass of Animation
*/
Animation* Animation::decode(sgct::SharedData *data) {
	unsigned int type = data->readInt32();
	if (type == JUMP)
	{
		int duration = data->readInt32();
		int frame = data->readInt32();
		float height = data->readFloat();
		return new Jump(duration, frame, height);
	} else { //if (type == STRAFE){
		int duration = data->readInt32();
		int frame = data->readInt32();
		return new Strafe(duration, frame);
	}
}

/**
*@brief	    Jump animation
*
*@details   Make the selected object jump over a duration
*
* @param	duration		The time for how long the animation will be active
*/
Jump::Jump(double duration, float height):Animation(duration)
{
	_height = height;
}
Jump::Jump(int duration, int frame, float height):Animation(duration,frame) 
{
	_height = height;
}

/**
*@brief	    Jump animation function
*/
void Jump::doAnimate()
{
	glTranslatef(0.0f,fabsf(sin((_frame*3.14)/_duration))*_height,0.0f);
}

/**
*@brief	    Encodes the object, reconstructs in the Animation::decode function
*
*@param		data	The SGCT shareddata object
*/
void Jump::encode(sgct::SharedData *data)
{
	data->writeInt32(JUMP);
	data->writeInt32(_duration);
	data->writeInt32(_frame);
	data->writeFloat(_height);
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
Strafe::Strafe(int duration, int frame):Animation(duration,frame) {
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

/**
*@brief	    Encodes the object, reconstructs in the Animation::decode function
*
*@param		data	The SGCT shareddata object
*/
void Strafe::encode(sgct::SharedData *data)
{
	data->writeInt32(STRAFE);
	data->writeInt32(_duration);
	data->writeInt32(_frame);
}
