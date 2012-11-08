#include "ImmersiveKidz.h"

ImmersiveKidz* ImmersiveKidz::_instance = 0;
ImmersiveKidz* ImmersiveKidz::getInstance(){
	//WARNING _ NOT THREAD SAFE
	if(_instance == 0)
		_instance = new ImmersiveKidz();
	return _instance;
}
/**
*@brief	    ImmersiveKidz constructor
*/
ImmersiveKidz::ImmersiveKidz() {
	sgct::MessageHandler::Instance()->print("Initializing ImmersiveKidz engine\n");

	// initialize all variables
	//objects = new std::vector<DrawableObject*>();
	//illustrations = new std::vector<Illustration*>();
	_isMaster = false;
	_sceneLoaded = false;
	_currTime = 0.0;

	_camera = new Camera();
}


/**
*@brief	    ImmersiveKidz destructor
*/
ImmersiveKidz::~ImmersiveKidz() {
	sgct::MessageHandler::Instance()->print("Destroying ImmersiveKidz engine\n");
	//delete _objects;
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
		_scenePath = folder + "/";
#else // mac, linux
		_scenePath = folder + "/";
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
	
	Illustration *ill = dynamic_cast<Illustration*>(o);
	if(ill) {
		_illustrations.push_back(ill);
	}
	
	_objects.push_back(o);
}

/**
*@brief	    Function called from sgct presync
*
*@return     void
*/
void ImmersiveKidz::preSyncFunc() {
	//set the time only on the master
	if( _isMaster )
	{
		//get the time in seconds
		_dt = sgct::Engine::getTime() - _currTime;
		_currTime = sgct::Engine::getTime();
	}
}

/**
*@brief	    Function called from sgct draw
*
*@return     void
*/
void ImmersiveKidz::draw() {
	_camera->setCamera();
	float speed = 50.0f;
	//glRotatef(static_cast<float>( curr_time ) * speed, 0.0f, 1.0f, 0.0f);
	
	for (int i = 0; i < _objects.size(); ++i)
	{
		_objects.at(i)->draw(_currTime, _dt);
	}
}

/**
*@brief	    Function called from sgct encode
*
*@return     void
*/
void ImmersiveKidz::encode() {
	_camera->encode(sgct::SharedData::Instance());
	sgct::SharedData::Instance()->writeDouble( _currTime );
	sgct::SharedData::Instance()->writeDouble( _dt );
}

/**
*@brief	    Function called from sgct decode
*
*@return     void
*/
void ImmersiveKidz::decode(){
	_camera->decode(sgct::SharedData::Instance());
	_currTime = sgct::SharedData::Instance()->readDouble();
	_dt = sgct::SharedData::Instance()->readDouble();
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
	std::string scene_xml = _scenePath + "scene.xml";
	
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

				addDrawableObject(new Model(_scenePath + filename, _scenePath + texture, scale, glm::vec3(rotx, roty, rotz)));
				_objects.back()->setAnimationFuncByName(animation);
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

				sgct::TextureManager::Instance()->loadTexure(texture, _scenePath + texture, true, 0);
				addDrawableObject(new Billboard(texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey)));
				_objects.back()->setAnimationFuncByName(animation);
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
			
				sgct::TextureManager::Instance()->loadTexure(texture, _scenePath + texture, true, 0);
				
				addDrawableObject(new Illustration(texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey), name_artist, name_drawing, description));
				_objects.back()->setAnimationFuncByName(animation);
			}
		}
	}
}


void ImmersiveKidz::mouseMotion(int x,int y,int dx,int dy){
	if(_camera == 0)
		return;
	_camera->mouseMotion(dx,dy);
}

void ImmersiveKidz::mouseButton(int button,int state){
	if(_camera == 0)
		return;
	_camera->mouseButton(button,state);
}

void ImmersiveKidz::keyboardButton(int key,int state){
	if(_camera == 0)
		return;
	_camera->keyboardButton(key,state);
}

void ImmersiveKidz::postSyncPreDrawFunction(){
	_camera->update(_dt);
}

void ImmersiveKidz::setEngine(sgct::Engine *engine){
	this->engine = engine;
}

sgct::Engine* ImmersiveKidz::getEngine(){
	return engine;
}


Camera* ImmersiveKidz::getCamera(){
	return _camera;
}
