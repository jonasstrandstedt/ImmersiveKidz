#ifndef ANIMATION_H
#define ANIMATION_H

#include "sgct.h"

/**
* @brief  	An class for animations
*
* @details	Used for temporary animations that is called from the HUD when buttons [1 - 9] is pressed,
			the animations are added to the animationVector in DrawableObject so that one can call
			several animations to store them on the animation stack.
*
* @author	Viktor Nilsson, vikni067@student.liu.se
*
* @date   	November 29, 2012
*    
*/
class Animation
{
public:
	Animation(double duration);
	Animation(int duration, int frame);

	bool animate();
	virtual void doAnimate() = 0;

	virtual void encode(sgct::SharedData *data) = 0;
	static Animation* decode(sgct::SharedData *data);
private:
	
protected:
	int _duration;
	int _frame;
	enum Type{
		JUMP 		= 0,
		STRAFE
	};
};

class Jump : public Animation
{
public:
	Jump(double duration, float height = 0.5);
	Jump(int duration, int frame, float height = 0.5);
	virtual void doAnimate();
	virtual void encode(sgct::SharedData *data);
private:
	float _height;
};

class Strafe : public Animation
{
public:
	Strafe(double duration);
	Strafe(int duration, int frame);
	virtual void doAnimate();
	virtual void encode(sgct::SharedData *data);
};

#endif