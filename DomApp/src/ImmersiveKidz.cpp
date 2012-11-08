#include "ImmersiveKidz.h"

ImmersiveKidz* ImmersiveKidz::instance = 0;
ImmersiveKidz* ImmersiveKidz::getInstance(){
	//WARNING _ NOT THREAD SAFE
	if(instance == 0)
		instance = new ImmersiveKidz();
	return instance;
}
/**
*@brief	    ImmersiveKidz constructor
*/
ImmersiveKidz::ImmersiveKidz() {
	sgct::MessageHandler::Instance()->print("Initializing ImmersiveKidz engine\n");

	// initialize all variables
	objects = new std::vector<DrawableObject*>();
	isMaster = false;
	scene_loaded = false;
	curr_time = 0.0;

	camera = new Camera();
}


/**
*@brief	    ImmersiveKidz destructor
*/
ImmersiveKidz::~ImmersiveKidz() {
	sgct::MessageHandler::Instance()->print("Destroying ImmersiveKidz engine\n");
	delete objects;
}

/**
*@brief	    Sets the path to the scene folder
*
*@details   The path must be set relative to the working directory including the trailing slash. When moving to release version this may be changed to a static path.
*
*@param		folder The name of the folder containing the scene
*/
void ImmersiveKidz::setScenePath(std::string folder) {
#ifdef __WIN32__
		scene_path = folder + "/";
#else // mac, linux
		scene_path = folder + "/";
#endif
}
/**
*@brief	    Adds a DrawableObject to the vector
*
*@details   Simply uses the vector push_back functionality so no checks are performed.
*
*@param		o is a subclass of DrawableObject (because DrawableObject is abstract)
*
*@return     void
*/
void ImmersiveKidz::addDrawableObject(DrawableObject *o) {
	objects->push_back(o);
}

/**
*@brief	    Function called from sgct presync
*
*@return     void
*/
void ImmersiveKidz::preSyncFunc() {
	//set the time only on the master
	if( isMaster )
	{
		//get the time in seconds
		dt = sgct::Engine::getTime() - curr_time;
		curr_time = sgct::Engine::getTime();
	}
}

/**
*@brief	    Function called from sgct draw
*
*@return     void
*/
void ImmersiveKidz::draw() {
	camera->setCamera();
	float speed = 50.0f;
	//glRotatef(static_cast<float>( curr_time ) * speed, 0.0f, 1.0f, 0.0f);
	
	for (int i = 0; i < objects->size(); ++i)
	{
		objects->at(i)->draw(curr_time, dt);
	}
	
	/*
	
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
	*/
}

/**
*@brief	    Function called from sgct encode
*
*@return     void
*/
void ImmersiveKidz::encode() {
	sgct::SharedData::Instance()->writeDouble( curr_time );
	sgct::SharedData::Instance()->writeDouble( dt );
	camera->encode(sgct::SharedData::Instance());
}

/**
*@brief	    Function called from sgct decode
*
*@return     void
*/
void ImmersiveKidz::decode(){
	curr_time = sgct::SharedData::Instance()->readDouble();
	dt = sgct::SharedData::Instance()->readDouble();
	camera->decode(sgct::SharedData::Instance());
}

/**
*@brief	    Loads a scene from a specified world
*
*@details   Loads a scene from a specified folder and parses the scene.xml. Calls setScenePath to update the scene_path in case files are required by other functions.
*
*@param		folder The folder that contains the scene
*
*@return     void
*/
void ImmersiveKidz::loadScene(std::string folder) {

	setScenePath(folder);
	std::string scene_xml = scene_path + "scene.xml";
	
	tinyxml2::XMLDocument document;
	document.LoadFile(scene_xml.c_str());

	tinyxml2::XMLHandle doc(&document);

	tinyxml2::XMLElement* scene = doc.FirstChildElement( "scene" ).ToElement();
	if(scene) {
		tinyxml2::XMLElement* models = scene->FirstChildElement( "models" );
		if(models) {
			tinyxml2::XMLNode* item = models->FirstChildElement( "item" );
			
			for ( item;item; item=item->NextSiblingElement( "item" ) ) {
				std::string filename = item->FirstChildElement( "filename" )->GetText();
				std::string texture = item->FirstChildElement( "texture" )->GetText();
				std::string animation = item->FirstChildElement( "animation" )->GetText();
				double posx = item->FirstChildElement( "pos" )->DoubleAttribute( "x" );
				double posy = item->FirstChildElement( "pos" )->DoubleAttribute( "y" );
				double posz = item->FirstChildElement( "pos" )->DoubleAttribute( "z" );
				double scale = item->FirstChildElement( "scale" )->DoubleAttribute( "val" );
				double rotx = item->FirstChildElement( "rot" )->DoubleAttribute( "x" );
				double roty = item->FirstChildElement( "rot" )->DoubleAttribute( "y" );
				double rotz = item->FirstChildElement( "rot" )->DoubleAttribute( "z" );
				double r = item->FirstChildElement( "base_color" )->DoubleAttribute( "r" );
				double g = item->FirstChildElement( "base_color" )->DoubleAttribute( "g" );
				double b = item->FirstChildElement( "base_color" )->DoubleAttribute( "b" );

				addDrawableObject(new Model(scene_path + filename, scene_path + texture, scale, glm::vec3(rotx, roty, rotz)));
				objects->back()->setAnimationFuncByName(animation);
			}
		}

		tinyxml2::XMLElement* billboards = scene->FirstChildElement( "billboards" );
		if(billboards) {
			tinyxml2::XMLNode* item = billboards->FirstChildElement( "item" );
			for ( item;item; item=item->NextSiblingElement( "item" ) ) {
				std::string texture = item->FirstChildElement( "texture" )->GetText();
				std::string animation = item->FirstChildElement( "animation" )->GetText();
				double posx = item->FirstChildElement( "pos" )->DoubleAttribute( "x" );
				double posy = item->FirstChildElement( "pos" )->DoubleAttribute( "y" );
				double posz = item->FirstChildElement( "pos" )->DoubleAttribute( "z" );
				double sizex = item->FirstChildElement( "size" )->DoubleAttribute( "x" );
				double sizey = item->FirstChildElement( "size" )->DoubleAttribute( "y" );

				sgct::TextureManager::Instance()->loadTexure(texture, scene_path + texture, true, 0);
				addDrawableObject(new Billboard(texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey)));
				objects->back()->setAnimationFuncByName(animation);
			}
		}

		tinyxml2::XMLElement* illustrations = scene->FirstChildElement( "illustrations" );
		if(illustrations) {
			tinyxml2::XMLNode* item = illustrations->FirstChildElement( "item" );
			for ( item;item; item=item->NextSiblingElement( "item" ) ) {
				std::string name_artist = item->FirstChildElement( "name_artist" )->GetText();
				std::string name_drawing = item->FirstChildElement( "name_drawing" )->GetText();
				std::string description = item->FirstChildElement( "description" )->GetText();
				std::string animation = item->FirstChildElement( "animation" )->GetText();
				std::string texture = item->FirstChildElement( "texture" )->GetText();
				double posx = item->FirstChildElement( "pos" )->DoubleAttribute( "x" );
				double posy = item->FirstChildElement( "pos" )->DoubleAttribute( "y" );
				double posz = item->FirstChildElement( "pos" )->DoubleAttribute( "z" );
				double sizex = item->FirstChildElement( "size" )->DoubleAttribute( "x" );
				double sizey = item->FirstChildElement( "size" )->DoubleAttribute( "y" );
			
				sgct::TextureManager::Instance()->loadTexure(texture, scene_path + texture, true, 0);
				addDrawableObject(new Illustration(texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey), name_artist, name_drawing, description));
				objects->back()->setAnimationFuncByName(animation);
			}
		}
	}
}


void ImmersiveKidz::mouseMotion(int x,int y,int dx,int dy){
	if(camera == 0)
		return;
	camera->mouseMotion(dx,dy);
}

void ImmersiveKidz::mouseButton(int button,int state){
	if(camera == 0)
		return;
	camera->mouseButton(button,state);
}

void ImmersiveKidz::keyboardButton(int key,int state){
	if(camera == 0)
		return;
	camera->keyboardButton(key,state);
}

void ImmersiveKidz::postSyncPreDrawFunction(){
	camera->update(dt);
}

void ImmersiveKidz::setEngine(sgct::Engine *engine){
	this->engine = engine;
}

sgct::Engine* ImmersiveKidz::getEngine(){
	return engine;
}


Camera* ImmersiveKidz::getCamera(){
	return camera;
}
