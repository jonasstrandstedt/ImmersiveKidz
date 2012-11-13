#ifndef CAMEERA_H
#define CAMEERA_H

#include <string>
#include "sgct.h"
#include "glm/glm.hpp"
#include "DrawableObject.h"

enum ButtonsToMove{
	Forward		= 'W',
	Backward	= 'S',
	Right		= 'D',
	Left		= 'A',
};

class Camera {
	bool movingForward,movingBackward,movingRight,movingLeft;
	bool mouseState;
	float speed;

	glm::vec3 position;
	glm::vec2 rotation;
	glm::mat4 viewMatrix;
public:
	Camera(glm::vec3 startPosition = glm::vec3(0,0,0));
	~Camera();

	void setCamera();

	void update(float dt);
	
	void keyboardButton(int key,int state);
	void mouseButton(int button,int state);
	void mouseMotion(int dx,int dy);
	
	glm::vec3 getPosition()const;
	glm::vec2 getRotation()const;
	float getSpeed()const;
	void setSpeed(float speed);
};

#endif
