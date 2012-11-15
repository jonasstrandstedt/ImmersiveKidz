#ifndef IMMERSIVEKIDS_H
#define IMMERSIVEKIDS_H

#include <iostream>
#include <vector>
#include "sgct.h"
#include "DrawableObject.h"
#include "Billboard.h"
#include "Illustration.h"
#include "Model.h"
#include "Camera.h"
#include "HUD.h"
#include "SceneLoader.h"


/**
* @brief  	The ImmersiveKidz engine
*
* @details	The engine class that controls the ImmersiveKidz application. Only 
*			allow one instance called from the sgct main class.
*
* @author 	Jonas Strandstedt, jonst184@student.liu.se
* @date   	November 1, 2012
* @version	0.0.1
*    
*/
class ImmersiveKidz {
public:
	
	~ImmersiveKidz();
	

	void setMaster(bool m) { _isMaster = m; _loader.setMaster(m); };
	void setScenePath(std::string folder);
	void setSceneLoaded(bool isLoaded) { _sceneLoaded = isLoaded; };
	void addDrawableObject(DrawableObject *o, std::string f = "none");

	void preSyncFunc();
	void draw();
	void encode();
	void decode();
	void postSyncPreDrawFunction();

	void mouseMotion(int x,int y,int dx,int dy);
	void mouseButton(int button,int state);
	void keyboardButton(int key,int state);

	Camera* getCamera();
	static ImmersiveKidz* getInstance();
	
	std::string getScenePath() { return _scenePath; };
private:
	static ImmersiveKidz* _instance;
	ImmersiveKidz();
	
	// TODO: REMOVE
	sgct::Engine *engine;
	
	// all objects in the scene that can be drawn
	std::vector<DrawableObject*> _objects;
	std::vector<Illustration*> _illustrations;

	// instance variables

	HUD	*_hud;
	bool isMaster;
	std::string scene_path;		// set in constructor
	bool scene_loaded;

	bool _isMaster;
	std::string _scenePath;		// set in constructor
	bool _sceneLoaded;
	

	// time and dynamic variables
	double _currTime;
	double _dt;

	// handlers
	SceneLoader _loader;
	Camera *_camera;

};


#endif