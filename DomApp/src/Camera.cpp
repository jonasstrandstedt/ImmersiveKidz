
#include "Camera.h"

Camera::Camera(sgct::Engine *engine)
{
	movingForward = false;
	movingBackward = false;
	movingRight = false;
	movingLeft = false;
	speed = 1.0;
	mouseState = false;
	this->engine = engine;
}

void Camera::setCamera(){
	glLoadMatrixf(glm::value_ptr(viewMatrix)); //TODO Consider using glMultmatrix instead
}

void Camera::update(float dt){
	glm::vec4 dir = glm::vec4(0,0,speed*dt,0);
 	glm::mat4x4 mDir = glm::rotate(glm::mat4(),-rotation[0],glm::vec3(0.0f,1.0f,0.0f));
 	glm::mat4x4 mSide = glm::rotate(glm::mat4(),90.0f,glm::vec3(0.0f,1.0f,0.0f));
 	dir = mDir * dir;
 	glm::vec4 side = mSide * dir;

	if(movingForward && !movingBackward){
		position += glm::vec3(dir[0],dir[1],dir[2]);
	}
	if(!movingForward && movingBackward){
		position -= glm::vec3(dir[0],dir[1],dir[2]);
	}
	if(movingLeft && !movingRight){
		position += glm::vec3(side[0],side[1],side[2]);
	}
	if(!movingLeft && movingRight){
		position -= glm::vec3(side[0],side[1],side[2]);
	}
	/*if(moveUp && !moveDown){
		pos -= glm::vec3(0,moveSpeed,0);
	}
	if(!moveUp && moveDown){
		pos += glm::vec3(0,moveSpeed,0);
	}*/



	
	viewMatrix = glm::mat4();
 	viewMatrix = glm::rotate(viewMatrix,rotation[1],glm::vec3(1.0f,0.0f,0.0f));
 	viewMatrix = glm::rotate(viewMatrix,rotation[0],glm::vec3(0.0f,1.0f,0.0f));
	viewMatrix = glm::translate(viewMatrix,position);
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
}

void Camera::mouseButton(int button,int state){
	if(button == 0){
		mouseState = state;
		engine->setMousePointerVisibility(!state);
	}
}

void Camera::mouseMotion(int dx,int dy){
	if(mouseState){
		rotation[0] += dx;
		rotation[1] += dy;
	}
}
