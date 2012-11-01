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
	void setDt(double t) {dt = t;};

	void addDrawableObject(DrawableObject *o);
	
	void preSyncFunc();
	void draw();
	void encode();
	void decode();
	
private:
	std::vector<DrawableObject*> *objects;
	double curr_time;
	double dt;
	float mouse_x;
	float mouse_y;
	bool isMaster;
	
	
};


#endif