#import "SceneLoader.h"
#import "ImmersiveKidz.h"

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
	

	if(key == GLFW_KEY_ENTER && state == GLFW_PRESS) loadScene();
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

void SceneLoader::loadScene() {
	ImmersiveKidz::getInstance()->loadScene(_scenes.at(_selection));
}
