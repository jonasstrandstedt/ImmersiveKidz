#include "Illustration.h"

/**
*@brief	    Draws the Illustration
*
*@details   Overloads the DrawableObjects draw function
*
*@return     void
*/

Illustration::Illustration(std::string texturename , glm::vec3 position, glm::vec2 proportionsIn, std::string artist, std::string drawing, std::string desc): Billboard(texturename, position, proportionsIn) 
{

	name_artist = artist;
	name_drawing = drawing;
	description = desc;

	seen = false;
};

std::string Illustration::getName()
{
	return name_artist;
};


