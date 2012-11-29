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
	Animation(double duration, std::string type);

	bool animate();
private:
	
protected:
	int _duration;
	int _frame;
	std::string _type;
};

#endif