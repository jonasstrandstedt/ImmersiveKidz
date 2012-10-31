#include "ImmersiveKidz.h"

ImmersiveKidz::ImmersiveKidz() {
	sgct::MessageHandler::Instance()->print("Initializing ImmersiveKidz engine\n");

	// initialize all variables
	objects = new std::vector<DrawableObject*>();
	isMaster = false;
	curr_time = 0.0;
};
ImmersiveKidz::~ImmersiveKidz() {
	sgct::MessageHandler::Instance()->print("Destroying ImmersiveKidz engine\n");
	delete objects;
};

void ImmersiveKidz::addDrawableObject(DrawableObject *o) {
	objects->push_back(o);
}

void ImmersiveKidz::preSyncFunc() {
	for (int i = 0; i < objects->size(); ++i)
	{
		objects->at(i)->draw();
	}
}

void ImmersiveKidz::draw() {
	/*
	for (int i = 0; i < objects->size(); ++i)
	{
		objects->at(i)->draw();
	}
	*/
	
	float speed = 50.0f;
	glRotatef(static_cast<float>( curr_time ) * speed, 0.0f, 1.0f, 0.0f);

	//render a single triangle
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); //Red
		glVertex3f(-0.5f, -0.5f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f); //Green
		glVertex3f(0.0f, 0.5f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f); //Blue
		glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();
}
