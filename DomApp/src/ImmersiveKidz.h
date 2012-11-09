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
#include "SceneLoader.h"

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
	

	void setMaster(bool m) { _isMaster = m; };
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
	static ImmersiveKidz* _instance;
	ImmersiveKidz();
	
	// TODO: REMOVE
	sgct::Engine *engine;
	
	// all objects in the scene that can be drawn
	std::vector<DrawableObject*> _objects;
	std::vector<Illustration*> _illustrations;

	// instance variables
	bool _isMaster;
	std::string _scenePath;		// set in constructor
	bool _sceneLoaded;
	

	// time and dynamic variables
	double _currTime;
	double _dt;
	float _mouseX;
	float _mouseY;

	// handlers
	SceneLoader _loader;
	Camera *_camera;
};


#endif