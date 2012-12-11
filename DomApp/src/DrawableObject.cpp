#include "DrawableObject.h"

/**
*@brief	    DrawableObject default constructor
*
*@details   Defines the animation function to be 0.
*/
DrawableObject::DrawableObject() 
{
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
void DrawableObject::draw(double t) 
{
	bool pop = false;
	// pre-animate
	if ( _animationFunc != 0 )
	{
		pop = true;
		glPushMatrix();
		_animationFunc(t, _seed);
	}
	else if ( !_animationVector.empty() )
	{
		pop = true;
		glPushMatrix();
		if ( ! (*_animationVector.begin())->animate() ) 
		{
			delete _animationVector[0];
			_animationVector.erase(_animationVector.begin());
		}
	}

	glPushMatrix();
	//Appllying the transform matrix
	glMultMatrixf(glm::value_ptr(_transform));
	
	// calls the virtual onDraw function.
	onDraw();
	glPopMatrix();
	// post-animate
	if ( pop )
	{
		glPopMatrix();
	}
	
}

/**
*@brief	    Add animation
*
*@details   Add a temporary animation depending on the given Animation type
*
*@param		type		the animation type
*
*@return     void
*/
void DrawableObject::addAnimation(Animation *type)
{
	_animationVector.push_back(type);
}
	
std::vector<Animation*>* DrawableObject::getAnimations() 
{
	return &_animationVector;
}

void DrawableObject::resetAnimations() {

	for (unsigned int i = 0; i < _animationVector.size(); ++i)
	{
		delete _animationVector[i];
	}

	_animationVector.erase(_animationVector.begin(),_animationVector.end());
}

void DrawableObject::setAnimations(std::vector<Animation*> animations) 
{
	_animationVector = animations;
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
void DrawableObject::setAnimationFuncByName(std::string name, double seed) 
{ 
	if ( name == "bounce" ) setAnimationFunc(bounce, seed);
	if ( name == "pendulum" ) setAnimationFunc(pendulum, seed);
	if ( name == "fly" ) setAnimationFunc(fly, seed);
}

/**
*@brief	    Translates the object up and down
*
*@return     void
*/
void bounce(double t, double seed) 
{
	t += seed;
	glTranslatef(0.0f,fabsf(sin(t*2))*0.5,0.0f);
}

/**
*@brief	    Translates the object like a pendulum on the x-axis
*
*@return     void
*/
void pendulum(double t, double seed) 
{
	t += seed;
	glTranslatef(sin(t),0.0f,0.0f);
}

/**
*@brief	    Translates the object in a "8" shape up and down.
*
*@return     void
*/
void fly(double t, double seed) 
{
	t += seed;
	glTranslatef(sin(t),fabs(sin(t*0.8))*0.5,cos(t*0.5)*1.5);
}