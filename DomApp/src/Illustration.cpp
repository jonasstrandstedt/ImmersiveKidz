#include "Illustration.h"

/**
*@brief	    Illustration constructor
*
*@return     void
*/
Illustration::Illustration(std::string texturename , glm::vec3 position, glm::vec2 proportionsIn, std::string artist, std::string drawing, std::string desc): Billboard(texturename, position, proportionsIn) 
{
	_nameArtist = artist;
	_nameDrawing = drawing;
	_description = desc;

	_seen = false;
};

std::string Illustration::getName()
{
	return _nameArtist;
};


//Returns a value which tells if the illustration has been seen
bool Illustration::getSeen()
{
	return _seen;
};

void Illustration::setSeen(bool state)
{
	_seen = state;
};



