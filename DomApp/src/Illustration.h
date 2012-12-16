#ifndef ILLUSTRATION_H
#define ILLUSTRATION_H

#include <string>
#include "sgct.h"
#include "Billboard.h"

/**
* @brief  	A class for a childs drawing
*
* @details	Extends the billboard class because a drawing is a billboard, the only difference is the extended metadata.
*
* @author 	Jonas Strandstedt, jonast184@student.liu.se
* @author	Viktor Nilsson, vikni067@student.liu.se
* @date   	November 1, 2012
*    
*/
class Illustration: public Billboard 
{
public:
	Illustration(std::string texturename , glm::vec3 position, glm::vec2 proportionsIn, 
		std::string artist, std::string drawing, std::string desc,DrawableObject *parentObject = 0);

	std::string getName();
	bool getSeen();
	void setSeen(bool state);

private:
	std::string _nameArtist;
	std::string _nameDrawing;
	std::string _description;
	bool _seen;

};


#endif