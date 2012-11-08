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
#include "HUD.h"

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
	
	~ImmersiveKidz();
	

	void setMaster(bool m) { isMaster = m; };
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
	
	void setEngine(sgct::Engine *engine);
	sgct::Engine *getEngine();

	Camera* getCamera();
	static ImmersiveKidz* getInstance();
private:
	static ImmersiveKidz* instance;
	ImmersiveKidz();
	sgct::Engine *engine;
	// all objects in the scene that can be drawn
	std::vector<DrawableObject*> *objects;
	std::vector<Illustration*> *illustrations;

	// instance variables
	HUD	_hud;
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