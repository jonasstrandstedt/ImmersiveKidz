#include "SceneLoader.h"
#include "ImmersiveKidz.h"
#include "Skybox.h"


/**
*@brief	    Scenloader constructor
*
*@details   Reads the set path for folders containing a scene.xml file and adds those folders to a vector
*
*@return     void
*/
SceneLoader::SceneLoader() {
	
	_selection = 0;
	_isMaster = false;
	_loaded = -1;
	_masterLoaded = -1;
	
	const char* PATH = ".";
	DIR *dir = opendir(PATH);
	
	struct dirent *entry = readdir(dir);
	
	while (entry != NULL)
	{
		if (entry->d_type == DT_DIR) {
			std::string sceneXML = "";
			sceneXML += entry->d_name;
			sceneXML += "/scene.xml";
			const char *filename = sceneXML.c_str();
			std::ifstream ifile(filename);
			if(ifile) {
				_scenes.push_back(entry->d_name);
				ifile.close();
			}
		}
		entry = readdir(dir);
	}
	
}

/**
*@brief	    Reads the keyboard for menu management
*
*@details   Moves the selection up and down with the arrow keys and when the user presses enter the selected scene is loaded.
*
*@param		key The keyboard key, example 'A' or GLFW_KEY_UP
*@param		state The state of the pressed button, example GLFW_PRESS
*
*@return     void
*/
void SceneLoader::keyboardButton(int key,int state) {
	if(_isMaster) {
		if(key == GLFW_KEY_UP && state == GLFW_PRESS) _selection--;
		if(key == GLFW_KEY_DOWN && state == GLFW_PRESS) _selection++;
		
		if(_selection < 0) _selection = _scenes.size() -1;
		if(_selection >= _scenes.size()) _selection = 0;
		

		if(key == GLFW_KEY_ENTER && state == GLFW_PRESS) {
			_loaded = loadScene();
			if(_loaded != -1) {
				ImmersiveKidz::getInstance()->setSceneLoaded(true);

			}
		}
	}
}

/**
*@brief	    Draws the menu for the master and loads the scene when selected for the nodes
*
*@details   When the master has loaded a scene it is checked here wheather the master has loaded the same scene as the node and if not the node loads the same as the master.
*
*@return     void
*/
void SceneLoader::menu() {
	if(_isMaster) {
		int h = sgct::Engine::getWindowPtr()->getVResolution();
	
		for(int i = 0; i < _scenes.size(); i++) {
		
			if(i == _selection) {
				glColor3f(1.0f,0.0f,0.0f);
			} else {
				glColor3f(1.0f,1.0f,1.0f);
			}
		
			Freetype::print(sgct::FontManager::Instance()->GetFont( "SGCTFont", 14 ), 50.0f, h-30-20*i, _scenes.at(i).c_str());

			glColor3f(1.0f,1.0f,1.0f);
		
		}
	} else {
		if(_loaded != _masterLoaded && _masterLoaded != -1) {
			_loaded = loadScene();
			if(_loaded != -1) {
				ImmersiveKidz::getInstance()->setSceneLoaded(true);
			}
		}
	}
}


/**
*@brief	    Loads a scene from a specified world
*
*@details   Loads a scene from a specified folder and parses the scene.xml. Calls setScenePath to update the sceneÅath in case files are required by other functions.
*
*@return     int The selection loaded, -1 in case of error
*/
int SceneLoader::loadScene() {

	std::string folder =_scenes.at(_selection);
	sgct::MessageHandler::Instance()->print("Loading scene %s\n", folder.c_str());

	ImmersiveKidz::getInstance()->setScenePath(folder);
	std::string scenePath = ImmersiveKidz::getInstance()->getScenePath();
	
	std::string scene_xml = scenePath + "scene.xml";
	
	Skybox* skybox = new Skybox();
	std::string skyboxTextures[6];
	skyboxTextures[CUBEMAP_TEX_X_POSITIVE] = scenePath + "skybox_xpos.png";
	skyboxTextures[CUBEMAP_TEX_X_NEGATIVE] = scenePath + "skybox_xneg.png";
	skyboxTextures[CUBEMAP_TEX_Y_POSITIVE] = scenePath + "skybox_ypos.png";
	skyboxTextures[CUBEMAP_TEX_Y_NEGATIVE] = scenePath + "skybox_yneg.png";
	skyboxTextures[CUBEMAP_TEX_Z_POSITIVE] = scenePath + "skybox_zpos.png";
	skyboxTextures[CUBEMAP_TEX_Z_NEGATIVE] = scenePath + "skybox_zneg.png";
	skybox->loadTextures(skyboxTextures);
	ImmersiveKidz::getInstance()->addDrawableObject(skybox);

	
	tinyxml2::XMLDocument doc;
	doc.LoadFile(scene_xml.c_str());

	tinyxml2::XMLHandle hDoc(&doc);

	tinyxml2::XMLElement* scene = doc.FirstChildElement( "scene" );
	if(scene){
		tinyxml2::XMLElement* item;

		tinyxml2::XMLElement* models = scene->FirstChildElement( "models" );
		if(models){
			item = models->FirstChildElement( "item" );
			for(item;item; item = item->NextSiblingElement( "item" )){
				std::string filename = "";
				tinyxml2::XMLElement* fileElement = item->FirstChildElement( "filename" );
				if(fileElement) {
					filename = fileElement->GetText();
				}
				else	continue;

				std::string texture = "";
				tinyxml2::XMLElement* textureElement = item->FirstChildElement( "texture");
				if(textureElement) {
					texture = textureElement->GetText();
				}
				else	continue;
		
				std::string animation = "none";
				double seed = 0;
				tinyxml2::XMLElement* aniElement = item->FirstChildElement( "animation" );
				if(aniElement) {
					animation = aniElement->Attribute( "name" );
					seed = aniElement->DoubleAttribute( "seed" );
				}

				double posx = 20*((double)rand()/RAND_MAX-0.5);
				double posy = 0;
				double posz  = 20*((double)rand()/RAND_MAX-0.5);
				tinyxml2::XMLElement* posElement = item->FirstChildElement( "pos" );
				if(posElement){
					posx = posElement->DoubleAttribute( "x" );
					posy = posElement->DoubleAttribute( "y" );
					posz = posElement->DoubleAttribute( "z" );
				}

				double scale = 1;
				tinyxml2::XMLElement* scaleElement = item->FirstChildElement( "scale" );
				if(scaleElement){
					scale = scaleElement->DoubleAttribute( "val" );
				}

				double rotx = 0;
				double roty = 0;
				double rotz = 0;
				tinyxml2::XMLElement* rotElement = item->FirstChildElement( "rot" );
				if(rotElement){
					rotx = rotElement->DoubleAttribute( "x" );
					roty = rotElement->DoubleAttribute( "y" );
					rotz = rotElement->DoubleAttribute( "z" );
				}

				double r = 1;
				double g = 1;
				double b = 1;
				tinyxml2::XMLElement* colorElement = item->FirstChildElement( "base_color" );
				if(colorElement){
					r = colorElement->DoubleAttribute( "r" );
					g = colorElement->DoubleAttribute( "g" );
					b = colorElement->DoubleAttribute( "b" );
				}

				sgct::MessageHandler::Instance()->print("Adding model\n");
				ImmersiveKidz::getInstance()->addDrawableObject(new Model(scenePath + filename, scenePath + texture, scale, glm::vec3(rotx, roty, rotz)), animation, seed);
			}
		}

		tinyxml2::XMLElement* billboards = scene->FirstChildElement( "billboards" );
		if(billboards){
			item = billboards->FirstChildElement( "item" );
			for(item;item; item = item->NextSiblingElement( "item" )){
				std::string texture = "";
				tinyxml2::XMLElement* textureElement = item->FirstChildElement( "texture");
				if(textureElement) {
					texture = textureElement->GetText();
				}
				else	continue;
		
				std::string animation = "none";
				double seed = 0;
				tinyxml2::XMLElement* aniElement = item->FirstChildElement( "animation" );
				if(aniElement) {
					animation = aniElement->Attribute( "name" );
					seed = aniElement->DoubleAttribute( "seed" );
				}

				double posx = 20*((double)rand()/RAND_MAX-0.5);
				double posy = 0;
				double posz  = 20*((double)rand()/RAND_MAX-0.5);
				tinyxml2::XMLElement* posElement = item->FirstChildElement( "pos" );
				if(posElement){
					posx = posElement->DoubleAttribute( "x" );
					posy = posElement->DoubleAttribute( "y" );
					posz = posElement->DoubleAttribute( "z" );
				}

				double sizex = 1;
				double sizey = 1;
				tinyxml2::XMLElement* rotElement = item->FirstChildElement( "size" );
				if(rotElement){
					sizex = rotElement->DoubleAttribute( "x" );
					sizey = rotElement->DoubleAttribute( "y" );
				}

				sgct::MessageHandler::Instance()->print("Adding billboard\n");
				ImmersiveKidz::getInstance()->addDrawableObject(new Billboard(scenePath + texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey)), animation, seed);
			}
		}

		tinyxml2::XMLElement* illustrations = scene->FirstChildElement( "illustrations" );
		if(illustrations){
			item = illustrations->FirstChildElement( "item" );
			for(item;item; item = item->NextSiblingElement( "item" )){
				std::string name_artist = "Dolan";
				tinyxml2::XMLElement* artistElement = item->FirstChildElement( "name_artist" );
				if(artistElement) {
					name_artist = artistElement->GetText();
				}

				std::string name_drawing = "Goobey";
				tinyxml2::XMLElement* drawingeElement = item->FirstChildElement( "name_drawing" );
				if(drawingeElement) {
					name_drawing = drawingeElement->GetText();
				}

				std::string description = "Goobey pls";
				tinyxml2::XMLElement* descElement = item->FirstChildElement( "description" );
				if(descElement) {
					description = descElement->GetText();
				}					
		
				std::string animation = "none";
				double seed = 0;
				tinyxml2::XMLElement* aniElement = item->FirstChildElement( "animation" );
				if(aniElement) {
					animation = aniElement->Attribute( "name" );
					seed = aniElement->DoubleAttribute( "seed" );
				}

				std::string texture = "";
				tinyxml2::XMLElement* textureElement = item->FirstChildElement( "texture");
				if(textureElement) {
					texture = textureElement->GetText();
				}
				else	continue;

				double posx = 20*((double)rand()/RAND_MAX-0.5);
				double posy = 0;
				double posz  = 20*((double)rand()/RAND_MAX-0.5);
				tinyxml2::XMLElement* posElement = item->FirstChildElement( "pos" );
				if(posElement){
					posx = posElement->DoubleAttribute( "x" );
					posy = posElement->DoubleAttribute( "y" );
					posz = posElement->DoubleAttribute( "z" );
				}

				double sizex = 1;
				double sizey = 1;
				tinyxml2::XMLElement* rotElement = item->FirstChildElement( "size" );
				if(rotElement){
					sizex = rotElement->DoubleAttribute( "x" );
					sizey = rotElement->DoubleAttribute( "y" );
				}
			
				sgct::MessageHandler::Instance()->print("Adding illustration\n");	
				ImmersiveKidz::getInstance()->addDrawableObject(new Illustration(scenePath + texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey), name_artist, name_drawing, description), animation, seed);
			}
		}
	}
	

	return _selection;
}

/**
*@brief	    The master encodes data
*
*@param		data Pointer to the sgct SharedData objects
*
*@return    void
*/
void SceneLoader::encode(sgct::SharedData *data){
	data->writeInt32(_selection);
	data->writeInt32(_loaded);
}

/**
*@brief	    The slaves decodes data
*
*@param		data Pointer to the sgct SharedData objects
*
*@return    void
*/
void SceneLoader::decode(sgct::SharedData *data){
	_selection	= data->readInt32();
	_masterLoaded	= data->readInt32();
	
}
