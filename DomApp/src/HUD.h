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
* @date   	November 8, 2012
* @version	0.0.1
*    
*/

class HUD {
public:
	//Constructor
	HUD();
	//~HUD();
	//Functions
	void drawIllustrationNames(std::vector<Illustration*> illu);
	void drawBackgroundToNames();
	void drawMinimapBackground();
	void drawMinimapPositions(std::vector<Illustration*> illu);


	void mouseButton(int button,int state);
	void mouseMotion(int dx,int dy);
	void keyboardButton(int key,int state, std::vector<Illustration*> illu);

	void setTextureMinimap(std::string texture) { _textureMinimap = texture; };

private:

	bool _mouseState;
	int _offset;
	std::string _textureMinimap;
	int _minimapWidth;
	int _minimapHeight;

	int _selection;

};

#endif