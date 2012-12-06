#include "Camera.h"
#include "ImmersiveKidz.h"

/**
* @brief				Default constructor for the Camera
*
* @details				Creates a camera at startPosition, sets the speed 
*
* @param startPosition		the starting poistion of the camera, defaults to vec3(0,1.5,0)
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
	_rotationSpeed = 0.033;
	_mouseState = false;
	_position = startPosition;
	
	_limitsX.x = -10;
	_limitsX.y = 10;
	_limitsY.x = 0.04;
	_limitsY.y = 10;
	_limitsZ.x = -10;
	_limitsZ.y = 10;

	_velocity = glm::vec3(0,0,0);
}

/**
* @brief				Destructor for the Camera object
*/
Camera::~Camera(void)
{
}

/**
* @brief	Sets the camera position 
*
* @return	void 
*/
void Camera::setCamera()
{
	glLoadMatrixf(glm::value_ptr(_viewMatrix)); //TODO Consider using glMultmatrix instead
}


/**
* @brief	Updates the position and rotation every time step dt. 
*
* @param	dt	  The steptime, the time since the last drawn frame. 
*
* @return	void 
*/
void Camera::update(float dt)
{
	glm::vec4 dir = glm::vec4(0,0,1,0);
 	glm::mat4x4 mDir = glm::rotate(glm::mat4(),-_rotation[0],glm::vec3(0.0f,1.0f,0.0f));
 	glm::mat4x4 mSide = glm::rotate(glm::mat4(),90.0f,glm::vec3(0.0f,1.0f,0.0f));
 	dir = mDir * dir;
 	glm::vec4 side = mSide * dir;

	glm::vec3 force;
	if(_movingForward && !_movingBackward)
	{
		force -= glm::vec3(dir[0],dir[1],dir[2]);
	}
	if(!_movingForward && _movingBackward)
	{
		force += glm::vec3(dir[0],dir[1],dir[2]);
	}
	if(_movingLeft && !_movingRight)
	{
		force -= glm::vec3(side[0],side[1],side[2]);
	}
	if(!_movingLeft && _movingRight)
	{
		force += glm::vec3(side[0],side[1],side[2]);
	}
	if(!_movingUp && _movingDown)
	{
		force += glm::vec3(0,1,0);
	}
	if(_movingUp && !_movingDown)
	{
		force -= glm::vec3(0,1,0);
	}

	_velocity += force*(dt*7.5f); //mass = 1;
	_position += _velocity*dt;

	_velocity *= 1 - dt;
	float m = glm::length(_velocity);
	if(m<0.0001)
		_velocity = glm::vec3(0,0,0);
	if(m>_speed)
		_velocity *= _speed/m;

	glm::vec3 headPos = sgct::Engine::getUserPtr()->getPos();

	glm::vec4 worldRect = ImmersiveKidz::getInstance()->getWorldRect();
	if(_position.x+headPos.x < _limitsX.x) _position.x = _limitsX.x-headPos.x;
	if(_position.x+headPos.x > _limitsX.y) _position.x = _limitsX.y-headPos.x;
	if(_position.y+headPos.y < _limitsY.x) _position.y = _limitsY.x-headPos.y;
	if(_position.y+headPos.y > _limitsY.y) _position.y = _limitsY.y-headPos.y;
	if(_position.z+headPos.z < _limitsZ.x) _position.z = _limitsZ.x-headPos.z;
	if(_position.z+headPos.z > _limitsZ.y) _position.z = _limitsZ.y-headPos.z;

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
* @param	key			The key that is interacted with 
* @param	state		The state, if the button is pressed or not 
*
* @return	void 
*/
void Camera::keyboardButton(int key,int state)
{
	if(key == _buttonForward)
		_movingForward = state;
	if(key == _buttonBackward)
		_movingBackward = state;
	if(key == _buttonRight)
		_movingRight = state;
	if(key == _buttonLeft)
		_movingLeft = state;
	if(key == _buttonUp)
		_movingUp = state;
	if(key == _buttonDown)
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

void Camera::mouseButton(int button,int state)
{
	if(button == 0)
	{
		_mouseState = state;
		sgct::Engine::setMousePointerVisibility(!state);
	}
}

/**
* @brief	A method that updates the rotation of the camera with the mouse state 
*
* @param	dx		delta x. The change in x
* @param	dy		delta y. The change in y 
*
* @return	void 
*/
void Camera::mouseMotion(int dx,int dy)
{
	if(_mouseState)
	{
		_rotation[0] += dx*_rotationSpeed;
		_rotation[1] += dy*_rotationSpeed;
		
		if(_rotation[1]<-89)
		{
			_rotation[1] = -89;
		}
		if(_rotation[1]>89)
		{
			_rotation[1] = 89;
		}
	}
}

/**
* @brief	Sets the camera position
*
* @param	position The position for the camera
*
* @return	void
*/
void Camera::setPosition(glm::vec3 position)
{
	_position = position;
}

/**
* @brief	Returns the camera position
*
* @return	glm::vec3 
*/
glm::vec3 Camera::getPosition() const
{
	return _position;
}

/**
* @brief	Returns the camera rotation
*
* @return	glm::vec2 
*/
glm::vec2 Camera::getRotation() const
{
	return _rotation;
}

/**
* @brief	Returns the camera speed 
*
* @return	float 
*/
float Camera::getSpeed() const
{
	return _speed;
}

/**
* @brief	Sets the camera speed 
*
* @param	speed 	The camera speed, must be larger than 0
*
* @return	void 
*/
void Camera::setSpeed(float speed)
{
	this->_speed = speed;
	if(this->_speed < 0)
		this->_speed = 0;
}

/**
* @brief	Sends the data to the master.
*
* @param	data 	The SGCT shared data object
*
* @return	void 
*/
void Camera::encode(sgct::SharedData *data)
{
	data->writeFloat(_position[0]);
	data->writeFloat(_position[1]);
	data->writeFloat(_position[2]);
	data->writeFloat(_rotation[0]);
	data->writeFloat(_rotation[1]);
}

/**
* @brief	Receives the data from the master.
*
* @param	data 	The SGCT shared data object   
*
* @return	void 
*/
void Camera::decode(sgct::SharedData *data)
{
	_position[0]   = data->readFloat();
	_position[1]   = data->readFloat();
	_position[2]   = data->readFloat();
	_rotation[0]   = data->readFloat();
	_rotation[1]   = data->readFloat();
}


/**
* @brief	Get the Camera limts for the x-axis  
*
* @return	vec2 	The limits, vec2[0] is min and vec2[1] is max 
*/
glm::vec2 Camera::getLimitsX()
{
	return _limitsX;
}

/**
* @brief	Get the Camera limts for the y-axis  
*
* @return	vec2 	The limits, vec2[0] is min and vec2[1] is max 
*/
glm::vec2 Camera::getLimitsY()
{
	return _limitsY;
}

/**
* @brief	Get the Camera limts for the z-axis  
*
* @return	vec2 	The limits, vec2[0] is min and vec2[1] is max 
*/
glm::vec2 Camera::getLimitsZ()
{
	return _limitsZ;
}

/**
* @brief	Set the Camera limts for the x-axis  
*
* @param	limits 	The limitx for the axis. limits[0] is min and limits[1] is max
*
* @return	void 
*/
void Camera::setLimitsX(glm::vec2 limits)
{
	this->_limitsX = limits;
}

/**
* @brief	Set the Camera limts for the y-axis  
*
* @param	limits 	The limitx for the axis. limits[0] is min and limits[1] is max
*
* @return	void 
*/
void Camera::setLimitsY(glm::vec2 limits)
{
	this->_limitsY = limits;
}

/**
* @brief	Set the Camera limts for the z-axis  
*
* @param	limits 	The limitx for the axis. limits[0] is min and limits[1] is max
*
* @return	void 
*/
void Camera::setLimitsZ(glm::vec2 limits)
{
	this->_limitsZ = limits;
}
