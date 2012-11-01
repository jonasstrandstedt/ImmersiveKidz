#include "Billboard.h"

/**
*@brief	    Brief description
*
*@details   Detailed description (Extends the brief description)
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

/**
*@brief	  Brief description
*
*@details Detailed description (Extends the brief description)
*
*@return     void
*
*
*/
void Billboard::draw() {
	
	sgct::MessageHandler::Instance()->print("Billboard draw\n");



}