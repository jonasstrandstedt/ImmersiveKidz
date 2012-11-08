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
	_nameArtist = artist;
	_nameDrawing = drawing;
	_description = desc;

	_seen = false;
}
