#ifndef HUD_H
#define HUD_H

#include "Illustration.h"

/**
* @brief  	The Heads Up Display (Interface)
*
* @details	 
*			
*
* @author 	Anders Nord, andno922@student.liu.se
* @author	Viktor Nilsson, vikni067@student.liu.se
* @date   	November 8, 2012
* @version	0.0.1
*    
*/

class HUD 
{
public:
	HUD();

	void draw(std::vector<Illustration*> illu);

	void keyboardButton(int key,int state, std::vector<Illustration*> illu);

	void setTextureMinimap(std::string texture) { _textureMinimap = texture; };

private:

	void _drawIllustrationNames(std::vector<Illustration*> illu);
	void _drawBackgroundToNames();
	void _drawMinimapBackground();
	void _drawMinimap(std::vector<Illustration*> illu);


	bool _mouseState;
	int _offset;
	std::string _textureMinimap;
	int _minimapWidth;
	int _minimapHeight;

	int _selection;

};

#endif