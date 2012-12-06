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
#include "BatchBillboard.h"
#include "Billboard.h"
#include "Illustration.h"
#include "Model.h"
#include "Plane.h"

#include <glm/gtx/random.hpp>

/**
* @brief  	The scene loader engine
*
* @details	Class that handles the loading of scenes. When first loaded it reads 
*			a specified folder for folders containing a scene.xml. Thos folders are 
*			stored in a vector. When the master loads a scene the slaves can see that
*			they have not loaded the same scene and therefore does so. 
*
* @author 	Jonas Strandstedt, jonst184@student.liu.se
* @author 	Viktor Nilsson, vikni067@student.liu.se
* @author	Anders Nord , andno922@student.liu.se
* @date   	November 15, 2012
* @version	0.0.2
*    
*/
class SceneLoader {
public:
	SceneLoader();
	~SceneLoader(){};
	
	void setMaster(bool master);
	
	void keyboardButton(int key,int state);
	void menu();
	int loadScene();
	
	void encode(sgct::SharedData *data);
	void decode(sgct::SharedData *data);

private:
	std::vector< std::string > _scenes;
	bool _isMaster;
	int _selection;
	int _masterLoaded;
	int _loaded;

	bool _createMask(const char* fileName, std::string maskName);
	std::map<std::string, std::vector <std::vector<bool> > > _mask;
};


#endif