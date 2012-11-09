#import "SceneLoader.h"
#import "ImmersiveKidz.h"
#include "Skybox.h"

SceneLoader::SceneLoader() {
	
	_selection = 0;
	
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
	
void SceneLoader::keyboardButton(int key,int state) {
	if(key == GLFW_KEY_UP && state == GLFW_PRESS) _selection--;
	if(key == GLFW_KEY_DOWN && state == GLFW_PRESS) _selection++;
	
	if(_selection < 0) _selection = _scenes.size() -1;
	if(_selection >= _scenes.size()) _selection = 0;
	

	if(key == GLFW_KEY_ENTER && state == GLFW_PRESS) {
		int loaded = loadScene();
		if(loaded == 0) {
			ImmersiveKidz::getInstance()->setSceneLoaded(true);
		}
	}
}


void SceneLoader::menu() {
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
int SceneLoader::loadScene() {

	std::string folder =_scenes.at(_selection);

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
	
	tinyxml2::XMLDocument document;
	document.LoadFile(scene_xml.c_str());

	tinyxml2::XMLHandle doc(&document);

	if(checkXML(doc) != "(XML) Cant find: ") { 
		std::cout << checkXML(doc) << std::endl; 
		return 1;
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

		ImmersiveKidz::getInstance()->addDrawableObject(new Model(scenePath + filename, scenePath + texture, scale, glm::vec3(rotx, roty, rotz)), animation);
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

		sgct::TextureManager::Instance()->loadTexure(texture, scenePath + texture, true, 0);

		ImmersiveKidz::getInstance()->addDrawableObject(new Billboard(texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey)), animation);
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
			
		sgct::TextureManager::Instance()->loadTexure(texture, scenePath + texture, true, 0);
				
		ImmersiveKidz::getInstance()->addDrawableObject(new Illustration(texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey), name_artist, name_drawing, description), animation);
	}
	return 0;
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
std::string SceneLoader::checkXML(tinyxml2::XMLHandle doc) {

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

