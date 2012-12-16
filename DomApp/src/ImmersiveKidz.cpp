#include "ImmersiveKidz.h"
#include "AudioHandler.h"

ImmersiveKidz* ImmersiveKidz::_instance = 0;

/**
*@brief	    ImmersiveKidz singleton getInstance class. Returns the instance if already instanciated.
*@return	ImmersiveKidz*
*/
ImmersiveKidz* ImmersiveKidz::getInstance()
{
	//WARNING _ NOT THREAD SAFE
	if(_instance == 0)
		_instance = new ImmersiveKidz();
	return _instance;
}

/**
*@brief	    ImmersiveKidz constructor
*/
ImmersiveKidz::ImmersiveKidz() 
{
	sgct::MessageHandler::Instance()->print("Initializing ImmersiveKidz engine\n");
	
	// initialize all variables
	_isMaster = false;
	_sceneLoaded = false;
	_currTime = 0.0;

}

/**
*@brief	    ImmersiveKidz initialize method. Note that some things is only initialised in master.
*/
void ImmersiveKidz::init()
{
	// init shaders
	sgct::ShaderManager::Instance()->addShader( "SingleBillboard", "data/Shaders/SingleBillboard.vert", "data/Shaders/SingleBillboard.frag" );
	sgct::ShaderManager::Instance()->addShader( "Simple", "data/Shaders/Simple.vert", "data/Shaders/Simple.frag" );
	sgct::ShaderManager::Instance()->addShader( "MultObject", "data/Shaders/MultObject.vert", "data/Shaders/MultObject.frag" );

	//Add font information
	if( !sgct::FontManager::Instance()->AddFont( "Verdana", "verdana.ttf" ) )
			sgct::FontManager::Instance()->GetFont( "Verdana", 14 );

	sgct::TextureManager::Instance()->setAnisotropicFilterSize(4.0f);

	// Allocate and initialize ImmersiveKidz
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	
	_camera = new Camera();
	if(_isMaster)
	{
		_hud = new HUD();
		_hud->init();
		AudioHandler::getInstance()->init();
		AudioHandler::getInstance()->addSound(SoundObject::CreateFromFile("data/audio/boys.wav"));

		AudioHandler::getInstance()->playSound(AudioHandler::getInstance()->getSoundObjectAt(0));
	}
}

/**
*@brief		setMaster method
*
*@param		m	Sets the master to true or false
*/
void ImmersiveKidz::setMaster(bool m) 
{
	_isMaster = m; 
	_loader.setMaster(m); 
}


/**
*@brief	    ImmersiveKidz destructor
*/
ImmersiveKidz::~ImmersiveKidz() 
{
	sgct::MessageHandler::Instance()->print("Destroying ImmersiveKidz engine\n");
	reset();
	delete _camera;
}

/**
*@brief	    Sets the path to the scene folder
*
*@details   The path must be set relative to the working directory including the trailing slash. When moving to release version this may be changed to a static path.
*
*@param		folder The name of the folder containing the scene
*/
void ImmersiveKidz::setScenePath(std::string folder) 
{
#ifdef __WIN32__
		_scenePath = folder + "/";
#else // mac, linux
		_scenePath = folder + "/";
#endif
}

/**
*@brief	    Sets the scene as loaded or not loaded
*
*@param		isLoaded	True if loaded and false if not loaded.
*/
void ImmersiveKidz::setSceneLoaded(bool isLoaded)
{
	_sceneLoaded = isLoaded;
}

/**
*@brief	    Adds a DrawableObject to the vector
*
*@details   Uses the vector push_back functionality so no checks are performed.
*
*@param		o is a subclass of DrawableObject (because DrawableObject is abstract)
*
*/
void ImmersiveKidz::addDrawableObject(DrawableObject *o, std::string f, double animseed)
{
	Illustration *ill = dynamic_cast<Illustration*>(o);
	if(ill) 
	{
		_illustrations.push_back(ill);
	}
	
	_objects.push_back(o);
	o->setAnimationFuncByName(f, animseed);
}

/**
* @brief	    Loads a texture from the specieif path
*
* @param		texture		The relativepath to the texture
*
* @return		Returns true if succes in loading (or previously loaded) the texture, and false if it fails.
*/
bool ImmersiveKidz::loadTexture(std::string texture)
{
	if(texture == "")
		return false;

	if ( _textures.find(texture) == _textures.end())
	{
		_textures.insert(texture);
		return sgct::TextureManager::Instance()->loadTexure(texture, texture, true, 4);
	}
	return true;
}

/**
* @brief	    Initializes all DrawableObjects VBO
*/
void ImmersiveKidz::initObjects() 
{
	sgct::MessageHandler::Instance()->print("Initializing all objects\n");
	for (unsigned int i = 0; i < _objects.size(); ++i)
	{
		_objects.at(i)->initVBO();
	}
}

/**
*@brief	    Function called from sgct presync
*
*/
void ImmersiveKidz::preSyncFunc()
{
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
*/
void ImmersiveKidz::draw() 
{
	
	if(_sceneLoaded) 
	{
		_camera->setCamera();
		for (unsigned int i = 0; i < _objects.size(); ++i)
		{
			if(!_objects.at(i)->isChild())
				_objects.at(i)->draw(_currTime);
		}

		if( _isMaster ) 
		{
			//Draw text for illustrations
			_hud->draw(_illustrations);
		}
	} else 
	{
		_loader.menu();
	}
}

/**
*@brief	    Function called from sgct encode
*
*/
void ImmersiveKidz::encode() 
{
	sgct::SharedData::Instance()->writeDouble( _currTime );
	sgct::SharedData::Instance()->writeDouble( _dt );

	_loader.encode(sgct::SharedData::Instance());
	_camera->encode(sgct::SharedData::Instance());
	
	std::vector<Animation*> *animvec;
	int counter = 0;
	for(unsigned int i = 0; i < _illustrations.size(); ++i)
	{
		animvec = _illustrations.at(i)->getAnimations();
		if(animvec->size() >0)
			counter++;
	}

	sgct::SharedData::Instance()->writeInt32( counter );
	for(unsigned int i = 0; i < _illustrations.size(); ++i)
	{
		animvec = _illustrations.at(i)->getAnimations();
		if(animvec->size() > 0) {
			sgct::SharedData::Instance()->writeInt32( i );
			animvec->at(0)->encode(sgct::SharedData::Instance());
		}	
	}
}

/**
*@brief	    Function called from sgct decode
*
*/
void ImmersiveKidz::decode()
{
	_currTime = sgct::SharedData::Instance()->readDouble();
	_dt = sgct::SharedData::Instance()->readDouble();
	
	_loader.decode(sgct::SharedData::Instance());
	_camera->decode(sgct::SharedData::Instance());

	unsigned int counter = sgct::SharedData::Instance()->readInt32();	
	for(unsigned int i = 0; i < counter; ++i)
	{
		int id = sgct::SharedData::Instance()->readInt32();
		_illustrations.at(id)->resetAnimations();
		_illustrations.at(id)->addAnimation(Animation::decode(sgct::SharedData::Instance()));
	}
}

/**
* @brief	a method that uses the mouseMotion method in the Camera class
*
* @param	x			the x position of the mouse
* @param	y			the y position of the mouse
* @param	dx			delta x, amount of movement in x-axis
* @param	dy			delta y, amount of movement in y-axis 
*/

void ImmersiveKidz::mouseMotion(int x,int y,int dx,int dy)
{
	if(_camera == 0)
		return;	

	_camera->mouseMotion(dx,dy);

}


/**
* @brief	a method that uses the mouseButton method in the Camera class
*
* @param	button		The button which is interacted with
* @param	state		The state, if the button is pressed or not 
*
*/
void ImmersiveKidz::mouseButton(int button,int state)
{
	if(_camera == 0)
		return;

	_camera->mouseButton(button,state);

}

/**
* @brief	a method that uses the keyboardButton method in either the Camera class, the HUD or the SceneLoader class
*
* @param	key			The key which is interacted with
* @param	state		The state, if the key is pressed or not 
*
*/
void ImmersiveKidz::keyboardButton(int key,int state)
{
	if(_camera == 0)
		return;

	if(key == GLFW_KEY_F5 && state == GLFW_PRESS) 
	{
		reset();
	}

	if(_sceneLoaded)
	{
		_camera->keyboardButton(key,state);
		_hud->keyboardButton(key, state, _illustrations);
	} else 
	{
		_loader.keyboardButton(key,state);
	}
}

/**
*@brief	    Function called from sgct setPostSyncPreDrawFunction, updates the Camera
*
*/
void ImmersiveKidz::postSyncPreDrawFunction()
{
	_camera->update(static_cast<float>(_dt));
	if(_isMaster)
	{
		AudioHandler::getInstance()->update();
	}
}

/**
*@brief	    Returns the Camera
*
*@return     Camera* Pointer to the ImmersiveKidz enginge Camera object
*
*/
Camera* ImmersiveKidz::getCamera()
{
	return _camera;
}

/**
*@brief	    Set the size of the world on the form [minX,minZ,maxX,maxZ]
*
*@param    worldRect	a vec4 on the form [minX,minZ,maxX,maxZ]
*
*/
void ImmersiveKidz::setWorldRect(glm::vec4 worldRect)
{
	_worldRect = worldRect;
}

/**
*@brief	    Returns the size of the world. 
*
*@return    glm::vec4	rect of [minX,minZ,maxX,maxZ] eg, the 2d corner points of the world	
*
*/
glm::vec4 ImmersiveKidz::getWorldRect()
{
	return _worldRect;
}

/**
*@brief	    Resets the vectors and variables concerning the scene
*
*/
void ImmersiveKidz::reset()
{

	for (unsigned int i = 0; i < _objects.size(); ++i)
	{
		delete _objects[i];
	}

	_objects.erase(_objects.begin(), _objects.end());
	_illustrations.erase(_illustrations.begin(), _illustrations.end());

	_scenePath = "";		// set in constructor
	_sceneLoaded = false;
	_worldRect = glm::vec4();
}
