#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "sgct.h"
#include "Animation.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

typedef struct
{
	GLfloat location[3];
	GLfloat tex[2];
	GLfloat normal[3];
	GLfloat colour[4];
	GLfloat attribute[3];
	GLfloat float_attribute;
	//GLubyte padding[4]; // Pads the struct out to 64 bytes for performance increase
} Vertex;

// Animation functions
void bounce(double t, double offset, double param);
void pendulum(double t, double offset, double param);
void fly(double t, double offset, double param);
void orbit(double t, double offset, double param);

/**
* @brief  	An abstract class for objects that can be rendered
*
* @details	The subclasses must implement the draw function.
*
* @author 	Jonas Strandstedt, jonast184@student.liu.se
* @author	Viktor Nilsson, vikni067@student.liu.se
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class DrawableObject 
{
public:
	//initializers
	DrawableObject(DrawableObject *parent = 0);
	~DrawableObject();

	// draw functionality
	void draw(double t);
	virtual void onDraw() = 0;
	void drawTriangles();
	void initVBO();
	void getArrays(int *isize, int *vsize, Vertex **varray, int **iarray);
	void resetArrays();

	// permanent animations
	void setAnimationFunc(void (*f)(double,double,double), double offset, double param);
	void setAnimationFuncByName(std::string name, double seed, double param);

	// Add temporary animation
	void addAnimation(Animation *type);
	std::vector<Animation*> *getAnimations();
	void resetAnimations();

	std::string getTexture();
	bool isChild()const;

private:

	GLuint _vBufferID;
	GLuint _iBufferID;
	
protected:
	double _offset;
	double _param;
	void (*_animationFunc)(double, double, double);
	void _drawVBO();

	glm::mat4x4 _transform;
	std::string _texture;

	// arrays with all triangles and indices
	unsigned int _isize;
	unsigned int _vsize;
	Vertex *_varray;
	int *_iarray;
    int _attrib_loc;
    int _float_attrib_loc;
	bool _isChild;

	// Animation vector for temporary animations, e.g. illustrations
	std::vector<Animation*> _animationVector;

	std::vector<DrawableObject*> _children;
};

#endif