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
	_isMaster = false;
	_sceneLoaded = false;
	_currTime = 0.0;

	_hud = new HUD();

	_camera = new Camera();

}


/**
*@brief	    ImmersiveKidz destructor
*/
ImmersiveKidz::~ImmersiveKidz() {
	sgct::MessageHandler::Instance()->print("Destroying ImmersiveKidz engine\n");
	delete _camera;
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
void ImmersiveKidz::addDrawableObject(DrawableObject *o, std::string f, double seed) {
	
	Illustration *ill = dynamic_cast<Illustration*>(o);
	if(ill) {
		_illustrations.push_back(ill);
	}
	
	_objects.push_back(o);
	_objects.back()->setAnimationFuncByName(f, seed);
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
	
	if(_sceneLoaded) {
		_camera->setCamera();
		for (int i = 0; i < _objects.size(); ++i)
		{
			_objects.at(i)->draw(_currTime);
		}
		_hud->drawBackgroundToNames();
		_hud->drawIllustrationNames(_illustrations);
	} else {
		_loader.menu();
	}

	
	//Draw text for illustrations
	
	
}

/**
*@brief	    Function called from sgct encode
*
*@return     void
*/
void ImmersiveKidz::encode() {
	sgct::SharedData::Instance()->writeDouble( _currTime );
	sgct::SharedData::Instance()->writeDouble( _dt );

	_loader.encode(sgct::SharedData::Instance());
	_camera->encode(sgct::SharedData::Instance());
}

/**
*@brief	    Function called from sgct decode
*
*@return     void
*/
void ImmersiveKidz::decode(){


	_currTime = sgct::SharedData::Instance()->readDouble();
	_dt = sgct::SharedData::Instance()->readDouble();
	
	_loader.decode(sgct::SharedData::Instance());
	_camera->decode(sgct::SharedData::Instance());

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
	if(_sceneLoaded) {
		_camera->keyboardButton(key,state);
		_hud->keyboardButton(key, state, _illustrations);
	} else {
		_loader.keyboardButton(key,state);
	}
}

/**
*@brief	    Function called from sgct setPostSyncPreDrawFunction
*
*@return     void
*/
void ImmersiveKidz::postSyncPreDrawFunction(){
	_camera->update(_dt);
}

/**
*@brief	    Returns the Camera
*
*@return     Camera* Pointer to the ImmersiveKidz enginge Camera object
*/
Camera* ImmersiveKidz::getCamera(){
	return _camera;
}
