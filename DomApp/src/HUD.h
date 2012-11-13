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

	void mouseButton(int button,int state);
	void mouseMotion(int dx,int dy);

	private:
	bool mouseState;
	float speed;

	glm::vec3 position;
	glm::vec2 rotation;

private:





};

#endif