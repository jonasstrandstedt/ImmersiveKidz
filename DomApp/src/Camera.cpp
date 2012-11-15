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
	movingForward = false;
	movingBackward = false;
	movingRight = false;
	movingLeft = false;
	movingUp = false;
	movingDown = false;
	speed = 3.0;
	rotationSpeed = 0.2;
	mouseState = false;
	this->position = startPosition;
}

/**
* @brief	Sets the camera position 
*
* @return	void 
*/
void Camera::setCamera(){
	glLoadMatrixf(glm::value_ptr(viewMatrix)); //TODO Consider using glMultmatrix instead
}


/**
* @brief	Updates the position and rotation every time step dt. 
*
* @param	
*
* @return	void 
*/
void Camera::update(float dt){
	glm::vec4 dir = glm::vec4(0,0,speed*dt,0);
 	glm::mat4x4 mDir = glm::rotate(glm::mat4(),-rotation[0],glm::vec3(0.0f,1.0f,0.0f));
 	glm::mat4x4 mSide = glm::rotate(glm::mat4(),90.0f,glm::vec3(0.0f,1.0f,0.0f));
 	dir = mDir * dir;
 	glm::vec4 side = mSide * dir;

	if(movingForward && !movingBackward){
		position -= glm::vec3(dir[0],dir[1],dir[2]);
	}
	if(!movingForward && movingBackward){
		position += glm::vec3(dir[0],dir[1],dir[2]);
	}
	if(movingLeft && !movingRight){
		position -= glm::vec3(side[0],side[1],side[2]);
	}
	if(!movingLeft && movingRight){
		position += glm::vec3(side[0],side[1],side[2]);
	}
	if(!movingUp && movingDown){
		position[1] -= speed*dt;
	}
	if(movingUp && !movingDown){
		position[1] += speed*dt;
	}
	
	glm::vec3 headPos = sgct::Engine::getUserPtr()->getPos();

	viewMatrix = glm::mat4();
	viewMatrix = glm::translate(viewMatrix,headPos);
 	viewMatrix = glm::rotate(viewMatrix,rotation[1],glm::vec3(1.0f,0.0f,0.0f));
 	viewMatrix = glm::rotate(viewMatrix,rotation[0],glm::vec3(0.0f,1.0f,0.0f));
	viewMatrix = glm::translate(viewMatrix,-position);
	viewMatrix = glm::translate(viewMatrix,-headPos);
}

Camera::~Camera(void)
{
}

void Camera::keyboardButton(int key,int state){
	if(key == Forward)
		movingForward = state;
	if(key == Backward)
		movingBackward = state;
	if(key == Right)
		movingRight = state;
	if(key == Left)
		movingLeft = state;
	if(key == Up)
		movingUp = state;
	if(key == Down)
		movingDown = state;
}

void Camera::mouseButton(int button,int state){
	if(button == 0){
		mouseState = state;
		sgct::Engine::setMousePointerVisibility(!state);
	}
}

void Camera::mouseMotion(int dx,int dy){
	if(mouseState){
		rotation[0] += dx*rotationSpeed;
		rotation[1] += dy*rotationSpeed;
		
		if(rotation[1]<-89){
			rotation[1] = -89;
		}
		if(rotation[1]>89){
			rotation[1] = 89;
		}
	}
}

/**
* @brief	Returns the camera position
*
* @return	glm::vec3 
*/
glm::vec3 Camera::getPosition()const{
	return position;
}

/**
* @brief	Returns the camera rotation
*
* @return	glm::vec2 
*/
glm::vec2 Camera::getRotation()const{
	return rotation;
}

/**
* @brief	Returns the camera speed 
*
* @return	float 
*/
float Camera::getSpeed()const{
	return speed;
}

/**
* @brief	Sets the camera speed 
*
* @return	void 
*/
void Camera::setSpeed(float speed){
	this->speed = speed;
	if(this->speed < 0)
		this->speed = 0;
}

/**
* @brief	Sends the data to the master.   
*
* @return	void 
*/
void Camera::encode(sgct::SharedData *data){
	data->writeFloat(position[0]);
	data->writeFloat(position[1]);
	data->writeFloat(position[2]);
	data->writeFloat(rotation[0]);
	data->writeFloat(rotation[1]);
}

/**
* @brief	Receives the data to the master.   
*
* @return	void 
*/
void Camera::decode(sgct::SharedData *data){
	position[0]   = data->readFloat();
	position[1]   = data->readFloat();
	position[2]   = data->readFloat();
	rotation[0]   = data->readFloat();
	rotation[1]   = data->readFloat();
}
