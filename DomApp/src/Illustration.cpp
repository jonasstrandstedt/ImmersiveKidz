#include "Illustration.h"

/**
*@brief	    Draws the Illustration
*
*@details   Overloads the DrawableObjects draw function
*
*@return     void
*/

Illustration::Illustration(std::string texturename , glm::vec3 position, glm::vec2 proportionsIn, std::string artist, std::string drawing, std::string desc) 
{
	texture = texturename;

	this->proportions = proportionsIn;

	transform = glm::mat4x4(1);
	transform = glm::translate(transform, position);

	name_artist = artist;
	name_drawing = drawing;
	description = desc;

	seen = false;

};
