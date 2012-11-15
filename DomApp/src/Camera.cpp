#include "Camera.h"
#include "ImmersiveKidz.h"

/**
* @brief				Default constructor for the Camera
*
* @details				Creates a camera at startPosition, sets the speed 
*
* @param startPosition	the starting poistion of the camera
*/
Camera::Camera(glm::vec3 startPosition)
{
	_movingForward = false;
	_movingBackward = false;
	_movingRight = false;
	_movingLeft = false;
	_movingUp = false;
	_movingDown = false;
	_speed = 3.0;
	_rotationSpeed = 0.2;
	_mouseState = false;
	_position = startPosition;
}


Camera::~Camera(void)
{
}

/**
* @brief	Sets the camera position 
*
* @return	void 
*/
void Camera::setCamera(){
	glLoadMatrixf(glm::value_ptr(_viewMatrix)); //TODO Consider using glMultmatrix instead
}


/**
* @brief	Updates the position and rotation every time step dt. 
*
* @param	dt steptime 
*
* @return	void 
*/
void Camera::update(float dt){
	glm::vec4 dir = glm::vec4(0,0,_speed*dt,0);
 	glm::mat4x4 mDir = glm::rotate(glm::mat4(),-_rotation[0],glm::vec3(0.0f,1.0f,0.0f));
 	glm::mat4x4 mSide = glm::rotate(glm::mat4(),90.0f,glm::vec3(0.0f,1.0f,0.0f));
 	dir = mDir * dir;
 	glm::vec4 side = mSide * dir;

	if(_movingForward && !_movingBackward){
		_position -= glm::vec3(dir[0],dir[1],dir[2]);
	}
	if(!_movingForward && _movingBackward){
		_position += glm::vec3(dir[0],dir[1],dir[2]);
	}
	if(_movingLeft && !_movingRight){
		_position -= glm::vec3(side[0],side[1],side[2]);
	}
	if(!_movingLeft && _movingRight){
		_position += glm::vec3(side[0],side[1],side[2]);
	}
	if(!_movingUp && _movingDown){
		_position[1] -= _speed*dt;
	}
	if(_movingUp && !_movingDown){
		_position[1] += _speed*dt;
	}
	
	glm::vec3 headPos = sgct::Engine::getUserPtr()->getPos();

	_viewMatrix = glm::mat4();
	_viewMatrix = glm::translate(_viewMatrix,headPos);
 	_viewMatrix = glm::rotate(_viewMatrix,_rotation[1],glm::vec3(1.0f,0.0f,0.0f));
 	_viewMatrix = glm::rotate(_viewMatrix,_rotation[0],glm::vec3(0.0f,1.0f,0.0f));
	_viewMatrix = glm::translate(_viewMatrix,-_position);
	_viewMatrix = glm::translate(_viewMatrix,-headPos);
}


/**
* @brief	A method to set the state of a keyboard button
*
* @param	key		The key that is interacted with 
* @param	state	The state, if the button is pressed or not 
*
* @return	void 
*/
void Camera::keyboardButton(int key,int state){
	if(key == Forward)
		_movingForward = state;
	if(key == Backward)
		_movingBackward = state;
	if(key == Right)
		_movingRight = state;
	if(key == Left)
		_movingLeft = state;
	if(key == Up)
		_movingUp = state;
	if(key == Down)
		_movingDown = state;
}

/**
* @brief	A method to set the state of a mouse button
*
* @param	button		The key pressed 
* @param	state		the state, if the button is pressed or not 
*
* @return	void 
*/

void Camera::mouseButton(int button,int state){
	if(button == 0){
		_mouseState = state;
		sgct::Engine::setMousePointerVisibility(!state);
	}
}

/**
* @brief	A method that updates the rotation of the camera with the mouse state 
*
* @param	button		The key pressed 
* @param	state		the state, if the button is pressed or not 
*
* @return	void 
*/
void Camera::mouseMotion(int dx,int dy){
	if(_mouseState){
		_rotation[0] += dx*_rotationSpeed;
		_rotation[1] += dy*_rotationSpeed;
		
		if(_rotation[1]<-89){
			_rotation[1] = -89;
		}
		if(_rotation[1]>89){
			_rotation[1] = 89;
		}
	}
}

/**
* @brief	Returns the camera position
*
* @return	glm::vec3 
*/
glm::vec3 Camera::getPosition()const{
	return _position;
}

/**
* @brief	Returns the camera rotation
*
* @return	glm::vec2 
*/
glm::vec2 Camera::getRotation()const{
	return _rotation;
}

/**
* @brief	Returns the camera speed 
*
* @return	float 
*/
float Camera::getSpeed()const{
	return _speed;
}

/**
* @brief	Sets the camera speed 
*
* @return	void 
*/
void Camera::setSpeed(float speed){
	this->_speed = speed;
	if(this->_speed < 0)
		this->_speed = 0;
}

/**
* @brief	Sends the data to the master.   
*
* @return	void 
*/
void Camera::encode(sgct::SharedData *data){
	data->writeFloat(_position[0]);
	data->writeFloat(_position[1]);
	data->writeFloat(_position[2]);
	data->writeFloat(_rotation[0]);
	data->writeFloat(_rotation[1]);
}

/**
* @brief	Receives the data to the master.   
*
* @return	void 
*/
void Camera::decode(sgct::SharedData *data){
	_position[0]   = data->readFloat();
	_position[1]   = data->readFloat();
	_position[2]   = data->readFloat();
	_rotation[0]   = data->readFloat();
	_rotation[1]   = data->readFloat();
}
