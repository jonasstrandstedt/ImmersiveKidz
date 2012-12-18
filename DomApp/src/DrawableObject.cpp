#include "DrawableObject.h"
#include "ImmersiveKidz.h"

#ifndef M_PI 
#define M_PI	3.14159265358979323846264338327950288 
#endif 


/**
*@brief	    DrawableObject default constructor
*
*@details   Defines the animation function to be 0 and sets the default values for all other variables.
*/
DrawableObject::DrawableObject(DrawableObject *parent) 
{
	_animationFunc = 0;
	_offset = 0;
	_param = 0;

	_transform = glm::mat4x4();

	_isize = 0;
	_vsize = 0;
	_iarray = NULL;
	_varray = NULL;
	_attrib_loc = -1;
	_float_attrib_loc = -1;

	_isChild = parent != 0;
	if(_isChild){
		parent->_children.push_back(this);
	}
}

/**
*@brief	    Destructor, calls the resetArrays function to clean up memory
*/
DrawableObject::~DrawableObject()
{
	resetArrays();
}

/**
*@brief	    Draws triangles from the vertex array
*
*@details	Can be used from a glBegin(GL_TRIANGLES) context or inside a display list.
*/
void DrawableObject::drawTriangles() 
{
	if(_varray != NULL && _iarray != NULL)
	{
		for (unsigned int i = 0; i < _isize; ++i)
		{
			Vertex v = _varray[_iarray[i]];
			glTexCoord2f(v.tex[0],v.tex[1]);     
			//glNormal3f(v.normal[0],v.normal[1],v.normal[2]);
			//glColor4f(v.colour[0],v.colour[1],v.colour[2],v.colour[3]);
			glVertex3f(v.location[0],v.location[1],v.location[2]);
		}
	}
}

/**
*@brief	    Initialize the model vertex buffer object
*
*@return     void
*/
void DrawableObject::initVBO()
{
	ImmersiveKidz::getInstance()->loadTexture(_texture);
	_vBufferID = 0;
	_iBufferID = 0;

	if(_vsize > 0 && _isize > 0 && _varray != NULL && _iarray != NULL) {
		glGenBuffers(1, &_vBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _vBufferID);
		glBufferData(GL_ARRAY_BUFFER, _vsize*sizeof(Vertex), _varray, GL_STATIC_DRAW);

		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
		glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
    	
    	// checks if the shader attributes is set and in that case fetches the location
    	if (_attrib_loc != -1)
    	{
    		glVertexAttribPointer(_attrib_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(48));
    	}
    	if (_float_attrib_loc != -1)
    	{
    		glVertexAttribPointer(_float_attrib_loc, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(60));
    	}

		glGenBuffers(1, &_iBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _isize*sizeof(int), _iarray, GL_STATIC_DRAW);

		if(_vBufferID == 0)
		{
			sgct::MessageHandler::Instance()->print("Vertex buffer not initialized\n");
		}
		if(_iBufferID == 0) 
		{
			sgct::MessageHandler::Instance()->print("Index buffer not initialized\n");
		}

		// in case of error, print it
		GLuint errorID = glGetError();
		if(errorID != GL_NO_ERROR)
		{
			sgct::MessageHandler::Instance()->print(" OpenGL error: ");
			sgct::MessageHandler::Instance()->print((const char*)gluErrorString(errorID));
			sgct::MessageHandler::Instance()->print("\nAttempting to proceed anyway. Expect rendering errors or a crash.\n");
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}

	for (unsigned int i = 0; i < _children.size(); ++i)
	{
		_children.at(i)->initVBO();
	}

	//resetArrays();
}

/**
*@brief	    Draws the VBO, called from the subclasses onDraw function where the proper shader is defined.
*/
void DrawableObject::_drawVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, _vBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iBufferID);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// checks if the shader attributes is set and in that case fetches the location
	if (_attrib_loc != -1)
	{
		glEnableVertexAttribArray(_attrib_loc);
	}
	if (_float_attrib_loc != -1)
	{
		glEnableVertexAttribArray(_float_attrib_loc);
	}

	    // Resetup our pointers.  This doesn't reinitialise any data, only how we walk through it
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
	if (_attrib_loc != -1)
	{
		glVertexAttribPointer(_attrib_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(48));
	}
	if (_float_attrib_loc != -1)
	{
		glVertexAttribPointer(_float_attrib_loc, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(60));
	}

	glDrawElements(GL_TRIANGLES, _isize, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/**
*@brief	    Resets the vertex and index arrays and sets them to NULL
*
*/
void DrawableObject::resetArrays() {
	if(_varray != NULL && _iarray != NULL)
	{
		free(_varray);
		free(_iarray);
		_iarray = NULL;
		_varray = NULL;
	}
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
		_animationFunc(t, _offset, _param);
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
	for(int i = 0;i<_children.size();i++){
		_children[i]->draw(t);
	}

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

/**
*@brief	    Removes all the temporary animations
*/
void DrawableObject::resetAnimations() {

	for (unsigned int i = 0; i < _animationVector.size(); ++i)
	{
		delete _animationVector[i];
	}

	_animationVector.erase(_animationVector.begin(),_animationVector.end());
}

/**
*@brief	    Sets the animation function s
*/
void DrawableObject::setAnimationFunc(void (*f)(double,double,double), double offset, double param) 
{ 
	_animationFunc = f; 
	_offset = offset; 
	_param = param;
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
void DrawableObject::setAnimationFuncByName(std::string name, double offset, double param) 
{ 
	if ( name == "bounce" ) setAnimationFunc(bounce, offset,param);
	if ( name == "pendulum" ) setAnimationFunc(pendulum, offset,param);
	if ( name == "fly" ) setAnimationFunc(fly, offset, param);
	if ( name == "orbit" ) setAnimationFunc(orbit, offset,param);
}

/**
*@brief	    Gets the texture
*
*@return	The name of the texture in the SGCT texture manager
*/
std::string DrawableObject::getTexture() {
	return _texture;
}

/**
*@brief	    Returns (as pointers) all vertex and index array data
*
*@param		vsize 	Pointer to an integer
*@param		isize 	Pointer to an integer
*@param		varray 	Pointer to a vertex array
*@param		iarray	Pointer to an integer array
*
*/
void DrawableObject::getArrays(int *vsize, int *isize, Vertex **varray, int **iarray) 
{
	*isize = _isize;
	*vsize = _vsize;
	*varray = _varray;
	*iarray = _iarray;
}

/**
*@brief	    Translates the object up and down
*
*@return     void
*/
void bounce(double t, double offset, double param) 
{
	t += offset;
	glTranslatef(	static_cast<float>(0.0),
					static_cast<float>(fabs(sin(t*2.0))*0.5),
					static_cast<float>(0.0));
}

/**
*@brief	    Translates the object like a pendulum on the x-axis
*
*@return     void
*/
void pendulum(double t, double offset, double param) 
{
	t += offset;
	glTranslatef(	static_cast<float>(sin(t)),
					static_cast<float>(0.0),
					static_cast<float>(0.0));
}

/**
*@brief	    Translates the object in a "8" shape up and down.
*
*@return     void
*/
void fly(double t, double offset, double param) 
{
	t += offset;
	glTranslatef(	static_cast<float>(sin(t)),
					static_cast<float>(fabs(sin(t*0.8))*0.5),
					static_cast<float>(cos(t*0.5)*1.5));
}

/**
*@brief	    ḿakes the object go in orbit
*
*/
void orbit(double t, double offset, double param) 
{
	t += offset;

	double orbit_length = 2.0*param*M_PI;
	double speed = 500.0;

	glRotatef(t*speed / orbit_length, 0,1,0);
	glTranslatef(0,0,param);
	glRotatef(-t*speed / orbit_length, 0,1,0);
}



/**
*@brief returns true if the object is a child to another object
*
*/
bool DrawableObject::isChild()const{
	return _isChild;
}