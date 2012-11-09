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

	if(checkXML(doc) != "(XML) Cant find: ") { 
		std::cout << checkXML(doc) << std::endl; 
		return;
	}

	tinyxml2::XMLElement* scene = doc.FirstChildElement( "scene" ).ToElement();
	tinyxml2::XMLElement* models = scene->FirstChildElement( "models" );
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

	tinyxml2::XMLElement* billboards = scene->FirstChildElement( "billboards" );
	item = billboards->FirstChildElement( "item" );
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

	tinyxml2::XMLElement* illustrations = scene->FirstChildElement( "illustrations" );
	item = illustrations->FirstChildElement( "item" );
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

/**
*@brief	    Load a document
*
*@details   Loads a document as an XMLHandle from loadScene(), error checks all elements and if they dont exist
			it will append error string with the element that cant be found.
*
*@param		doc the XMLHandle document (.xml)
*
*@return    string
*/
std::string ImmersiveKidz::checkXML(tinyxml2::XMLHandle doc) {

	std::string error = "(XML) Cant find: ";

	tinyxml2::XMLElement* scene = doc.FirstChildElement( "scene" ).ToElement();
	if(scene) {
		tinyxml2::XMLElement* models = scene->FirstChildElement( "models" );
		if(models) {
			tinyxml2::XMLNode* item = models->FirstChildElement( "item" );
			if(item) {
				for ( item;item; item=item->NextSiblingElement( "item" ) ) {

					tinyxml2::XMLElement* filename = item->FirstChildElement( "filename" );
					if(!filename) error.append("models->item->filename ");
					tinyxml2::XMLElement* texture = item->FirstChildElement( "texture" );
					if(!texture) error.append("models->item->texture ");
					tinyxml2::XMLElement* animation = item->FirstChildElement( "animation" );
					if(!animation) error.append("models->item->animation ");
					tinyxml2::XMLElement* pos = item->FirstChildElement( "pos" );
					if(!pos) error.append("models->item->pos ");
					tinyxml2::XMLElement* scale = item->FirstChildElement( "scale" );
					if(!scale) error.append("models->item->scale ");
					tinyxml2::XMLElement* rot = item->FirstChildElement( "rot" );
					if(!rot) error.append("models->item->rot ");
					tinyxml2::XMLElement* color = item->FirstChildElement( "base_color" );
					if(!color) error.append("models->item->color ");
				}
			} else error.append("models->item ");
		} else error.append("models ");

		tinyxml2::XMLElement* billboards = scene->FirstChildElement( "billboards" );
		if(billboards) {
			tinyxml2::XMLNode* item = billboards->FirstChildElement( "item" );
			if(item) {
				for ( item;item; item=item->NextSiblingElement( "item" ) ) {

					tinyxml2::XMLElement* texture = item->FirstChildElement( "texture" );
					if(!texture) error.append("billboards->item->texture ");
					tinyxml2::XMLElement* animation = item->FirstChildElement( "animation" );
					if(!animation) error.append("billboards->item->animation ");
					tinyxml2::XMLElement* pos = item->FirstChildElement( "pos" );
					if(!pos) error.append("billboards->item->pos ");
					tinyxml2::XMLElement* size = item->FirstChildElement( "size" );
					if(!size) error.append("billboards->item->size ");
				}
			} else error.append("billboards->item ");
		} else error.append("billboards ");

		tinyxml2::XMLElement* illustrations = scene->FirstChildElement( "illustrations" );
		if(illustrations) {
			tinyxml2::XMLNode* item = illustrations->FirstChildElement( "item" );
			if(item) { 
				for ( item;item; item=item->NextSiblingElement( "item" ) ) {

					tinyxml2::XMLElement* name_artist = item->FirstChildElement( "name_artist" );
					if(!name_artist) error.append("illustrations->item->name_artist ");
					tinyxml2::XMLElement* name_drawing = item->FirstChildElement( "name_drawing" );
					if(!name_drawing) error.append("illustrations->item->name_drawing ");
					tinyxml2::XMLElement* description = item->FirstChildElement( "description" );
					if(!description) error.append("illustrations->item->description ");
					tinyxml2::XMLElement* texture = item->FirstChildElement( "texture" );
					if(!texture) error.append("illustrations->item->texture ");
					tinyxml2::XMLElement* animation = item->FirstChildElement( "animation" );
					if(!animation) error.append("illustrations->item->animation ");
					tinyxml2::XMLElement* pos = item->FirstChildElement( "pos" );
					if(!pos) error.append("illustrations->item->pos ");
					tinyxml2::XMLElement* size = item->FirstChildElement( "size" );
					if(!size) error.append("illustrations->item->size ");
				}
			} else error.append("illustrations->item ");
		} else error.append("illustrations ");
	} else error.append("scene "); 

	return error;
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
