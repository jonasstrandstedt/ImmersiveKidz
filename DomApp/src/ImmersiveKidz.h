#ifndef IMMERSIVEKIDS_H
#define IMMERSIVEKIDS_H

#include <iostream>
#include <vector>
#include "sgct.h"
#include "tinyxml2.h"
#include "DrawableObject.h"
#include "Billboard.h"
#include "Illustration.h"
#include "Model.h"
#include "Camera.h"

/**
* @brief  	The ImmersiveKidz engine
*
* @details	The engine class that controls the ImmersiveKidz application. Only allow one instance called from the sgct main class.
*
* @author 	Jonas Strandstedt, jonast184@student.liu.se
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class ImmersiveKidz {
public:
	
	// constructors and destructors
	ImmersiveKidz(sgct::Engine *engine);
	~ImmersiveKidz();
	

	void setMaster(bool m) { isMaster = m; };
	/*void setCurr_time(double t) {curr_time = t;};
	void setDt(double t) {dt = t;};*/
	void setScenePath(std::string folder);

	void addDrawableObject(DrawableObject *o);
	
	void preSyncFunc();
	void draw();
	void encode();
	void decode();
	void postSyncPreDrawFunction();

	void mouseMotion(int x,int y,int dx,int dy);
	void mouseButton(int button,int state);
	void keyboardButton(int key,int state);

	void loadScene(std::string folder);
	


private:
	sgct::Engine *engine;
	// all objects in the scene that can be drawn
	std::vector<DrawableObject*> *objects;

	// instance variables
	bool isMaster;
	std::string scene_path;		// set in constructor
	bool scene_loaded;

	// time and dynamic variables
	double curr_time;
	double dt;
	float mouse_x;
	float mouse_y;

	Camera *camera;
};


#endif