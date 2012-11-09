#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <stdio.h>

#include "sgct.h"
#include "tinyxml2.h"
#include "DrawableObject.h"
#include "Billboard.h"
#include "Illustration.h"
#include "Model.h"

/**
* @brief  	The scene loader engine
*
* @details	Class that handles the loading of scenes
*
* @author 	Jonas Strandstedt, jonast184@student.liu.se
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class SceneLoader {
public:
	SceneLoader();
	~SceneLoader() {};
	
	void keyboardButton(int key,int state);
	void menu();
	int loadScene();
	std::string checkXML(tinyxml2::XMLHandle doc);

private:
	
	std::vector< std::string > _scenes;
	int _selection;
};


#endif