#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

/**
* @brief  	An abstract class for objects that can be rendered
*
* @details	The subclasses must implement the draw function.
*
* @author 	Jonas Strandstedt, jonast184@student.liu.se
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class DrawableObject {
public:
	virtual void draw() = 0;
private:
};

#endif