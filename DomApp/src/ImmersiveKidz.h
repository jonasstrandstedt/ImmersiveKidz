#ifndef IMMERSIVEKIDS_H
#define IMMERSIVEKIDS_H

#include "sgct.h"
#include "DrawableObject.h"
#include <vector>

class ImmersiveKidz {
public:
	
	// constructors and destructors
	ImmersiveKidz();
	~ImmersiveKidz();
	

	void setMaster(bool m) { isMaster = m; };
	void setCurr_time(double t) {curr_time = t;};

	void addDrawableObject(DrawableObject *o);
	
	void preSyncFunc();
	void draw();

	double getCurr_time() { return curr_time; };
	
private:
	std::vector<DrawableObject*> *objects;
	double curr_time;
	float mouse_x;
	float mouse_y;
	bool isMaster;
	
	
};


#endif