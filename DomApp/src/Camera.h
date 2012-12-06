#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "sgct.h"
#include "glm/glm.hpp"
#include "DrawableObject.h"

/**
* @brief  	A class to handle the logics for the camera
*
* @details	A class to handle the logics for the camera, currently 
*           supports movment similar to a First person shooter where
*           you move front/back with W and S and strafe right and 
*           left with A and D. To change viewing direction the user 
*			needs to hold down left mouse button
*
* @author 	Rickard Englund, gefle.rickard@gmail.com
* @author 	(Jonas Strandstedt), jonst184@student.liu.se
* @date   	November 8, 2012
* @version	0.0.0.1
*    
*/
class Camera {
public:
	Camera(glm::vec3 startPosition = glm::vec3(0,1.5,0));
	~Camera();

	void setCamera();

	void update(float dt);
	
	void keyboardButton(int key,int state);
	void mouseButton(int button,int state);
	void mouseMotion(int dx,int dy);
	
	void setPosition(glm::vec3);
	glm::vec3 getPosition()const;
	glm::vec2 getRotation()const;
	float getSpeed()const;
	void setSpeed(float speed);

	void encode(sgct::SharedData *data);
	void decode(sgct::SharedData *data);

	
	glm::vec2 getLimitsX();
	glm::vec2 getLimitsY();
	glm::vec2 getLimitsZ();
	void setLimitsX(glm::vec2 limits);
	void setLimitsY(glm::vec2 limits);
	void setLimitsZ(glm::vec2 limits);
	
private:
	enum ButtonsToMove{
		_buttonForward 		= 'W',
		_buttonBackward		= 'S',
		_buttonRight 		= 'D',
		_buttonLeft 		= 'A',
		_buttonUp 			= 'Q',
		_buttonDown 		= 'E'
	};

	bool _movingForward,_movingBackward,_movingRight,_movingLeft,_movingUp,_movingDown;
	bool _mouseState;
	float _speed;
	float _rotationSpeed;

	glm::vec3 _position;
	glm::vec2 _rotation;
	glm::mat4 _viewMatrix;
	glm::vec2 _limitsX;
	glm::vec2 _limitsY;
	glm::vec2 _limitsZ;
};

#endif
