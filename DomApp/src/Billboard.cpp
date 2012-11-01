#include "Billboard.h"

/**
*@file Billboard.cpp
*
*@brief		
*
*@details
*
*@param		texturename Unique name of a texture. Ex: "texture.png".
*@param		position Contains the positions in world coordinates.
*@param		proportions The proportions of the billboardsize according to the world unit length. 
*/
Billboard::Billboard(std::string texturename , glm::vec3 position, glm::vec2 proportionsIn)
{
	texture = texturename;

	this->proportions = proportionsIn;

	transform = glm::mat4x4(1);
	transform = glm::translate(transform, position);


};


void Billboard::draw() {
	
	sgct::MessageHandler::Instance()->print("Billboard draw\n");



}