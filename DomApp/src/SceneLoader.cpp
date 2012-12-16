#include "SceneLoader.h"
#include "ImmersiveKidz.h"
#include "Skybox.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "png.h"



/**
*@brief	    Scenloader constructor
*
*@details   Reads the set path for folders containing a scene.xml file and adds those folders to a vector
*
*@return     void
*/
SceneLoader::SceneLoader() 
{
	
	_selection = 0;
	_isMaster = false;
	_loaded = -1;
	_masterLoaded = -1;
	
	const char* PATH = "scenes";
	DIR *dir = opendir(PATH);
	
	struct dirent *entry = readdir(dir);
	
	while (entry != NULL)
	{
		if (entry->d_type == DT_DIR) 
		{
			std::string sceneXML = PATH;
			sceneXML += "/";
			sceneXML += entry->d_name;
			sceneXML += "/scene.xml";
			const char *filename = sceneXML.c_str();
			std::ifstream ifile(filename);
			if(ifile) 
			{
				_scenes.push_back(entry->d_name);
				ifile.close();
			}
		}
		entry = readdir(dir);
	}
	
}

/**
*@brief	    Sets if the node if master or slave
*
*@param		master : if set to true then the node is master over the other slave-nodes
*
*@return     void
*/

void SceneLoader::setMaster(bool master) 
{ 
	_isMaster = master; 
}

/**
*@brief	    Reads the keyboard for menu management
*
*@details   Moves the selection up and down with the arrow keys and when the user presses enter the selected scene is loaded.
*
*@param	key			The keyboard key, example 'A' or GLFW_KEY_UP
*@param	state		The state of the pressed button, example GLFW_PRESS
*
*@return     void
*/
void SceneLoader::keyboardButton(int key,int state) 
{
	if(_isMaster) 
	{
		if(key == GLFW_KEY_UP && state == GLFW_PRESS) _selection--;
		if(key == GLFW_KEY_DOWN && state == GLFW_PRESS) _selection++;
		
		if(_selection < 0) _selection = static_cast<int>(_scenes.size()) -1;
		if(_selection >=  static_cast<int>(_scenes.size())) _selection = 0;
		

		if((key == GLFW_KEY_ENTER || key == GLFW_KEY_KP_ENTER) && state == GLFW_PRESS) 
		{
			_loaded = loadScene();
			if(_loaded != -1) 
			{
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
void SceneLoader::menu() 
{
	if(_isMaster) 
	{
		int h = sgct::Engine::getWindowPtr()->getVResolution();
	
		for(unsigned int i = 0; i < _scenes.size(); i++) 
		{
		
			if(i == (unsigned int) _selection) 
			{
				glColor3f(1.0,0.0,0.0);
			} else 
			{
				glColor3f(1.0,1.0,1.0);
			}
		
			Freetype::print(	sgct::FontManager::Instance()->GetFont( "SGCTFont", 14 ),
								50.0, 
								static_cast<float>(static_cast<float>(h)-30.0-20.0*static_cast<float>(i)),
								_scenes.at(i).c_str());

			glColor3f(1.0,1.0,1.0);
		
		}
	} else 
	{
		if(_loaded != _masterLoaded && _masterLoaded != -1) 
		{
			_loaded = loadScene();
			if(_loaded != -1) 
			{
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
int SceneLoader::loadScene() 
{

	ImmersiveKidz::getInstance()->reset();

	std::string folder =_scenes.at(_selection);
	sgct::MessageHandler::Instance()->print("Loading scene %s\n", folder.c_str());

	ImmersiveKidz::getInstance()->setScenePath(folder);
	std::string scenePath = ImmersiveKidz::getInstance()->getScenePath();
	scenePath = "scenes/" + scenePath;
	
	std::string scene_xml = scenePath + "scene.xml";
	
	tinyxml2::XMLDocument doc;
	doc.LoadFile(scene_xml.c_str());

	tinyxml2::XMLHandle hDoc(&doc);

	tinyxml2::XMLElement* scene = doc.FirstChildElement( "scene" );
	if(scene)
	{
		_mask["default"].clear();
		_mask["default"].push_back(std::vector<bool>());
		_mask["default"][0].push_back(true);


		tinyxml2::XMLElement* world = scene->FirstChildElement( "world" );
		if(world)
		{

			tinyxml2::XMLElement* skyboxElement = world->FirstChildElement( "skybox" );
			if(skyboxElement) {

				std::string skybox_name = "skybox";

				if(skyboxElement->Attribute( "name" ) != NULL ) skybox_name = skyboxElement->Attribute( "name" );
				

				Skybox* skybox = new Skybox();
				std::string skyboxTextures[6];
				skyboxTextures[CUBEMAP_TEX_X_POSITIVE] = scenePath + skybox_name + "_xpos.png";
				skyboxTextures[CUBEMAP_TEX_X_NEGATIVE] = scenePath + skybox_name + "_xneg.png";
				skyboxTextures[CUBEMAP_TEX_Y_POSITIVE] = scenePath + skybox_name + "_ypos.png";
				skyboxTextures[CUBEMAP_TEX_Y_NEGATIVE] = scenePath + skybox_name + "_yneg.png";
				skyboxTextures[CUBEMAP_TEX_Z_POSITIVE] = scenePath + skybox_name + "_zpos.png";
				skyboxTextures[CUBEMAP_TEX_Z_NEGATIVE] = scenePath + skybox_name + "_zneg.png";
				skybox->loadTextures(skyboxTextures);
				ImmersiveKidz::getInstance()->addDrawableObject(skybox);
			}

			tinyxml2::XMLElement* camera = world->FirstChildElement( "camera" );
			if(camera)
			{
				Camera *cam = ImmersiveKidz::getInstance()->getCamera();
				tinyxml2::XMLElement* start = camera->FirstChildElement( "start" );
				if(start)
				{
					if(!start->Attribute("x") || !start->Attribute("y") || !start->Attribute("z"))
					{
						cam->setPosition(glm::vec3(0.0,0.0,0.0));
						std::cerr << "Warning: Couldn't find <start> attributes in XML-file!" << std::endl;
					}
					else cam->setPosition(glm::vec3(start->FloatAttribute("x"),start->FloatAttribute("y"),start->FloatAttribute("z")));
				}
				tinyxml2::XMLElement* limitx = camera->FirstChildElement( "limitx" );
				if(limitx)
				{
					if(!limitx->Attribute("min") || !limitx->Attribute("max"))
					{
						cam->setLimitsX(glm::vec2(0.0,0.0));
						std::cerr << "Warning: Couldn't find <limitx> attributes in XML-file!" << std::endl;
					}
					else cam->setLimitsX(glm::vec2(limitx->FloatAttribute("min"),limitx->FloatAttribute("max")));
				}
				tinyxml2::XMLElement* limity = camera->FirstChildElement( "limity" );
				if(limity)
				{
					if(!limity->Attribute("min") || !limity->Attribute("max"))
					{
						cam->setLimitsY(glm::vec2(0.0,0.0));
						std::cerr << "Warning: Couldn't find <limity> attributes in XML-file!" << std::endl;
					}
					else cam->setLimitsY(glm::vec2(limity->FloatAttribute("min"),limity->FloatAttribute("max")));
				}
				tinyxml2::XMLElement* limitz = camera->FirstChildElement( "limitz" );
				if(limitz)
				{
					if(!limitz->Attribute("min") || !limitz->Attribute("max"))
					{
						cam->setLimitsZ(glm::vec2(0.0,0.0));
						std::cerr << "Warning: Couldn't find <limitz> attributes in XML-file!" << std::endl;
					}
					else cam->setLimitsZ(glm::vec2(limitz->FloatAttribute("min"),limitz->FloatAttribute("max")));
				}
				
				
				tinyxml2::XMLElement* rotationSpeed = camera->FirstChildElement( "rotation" );
				if(rotationSpeed)
				{
					if(rotationSpeed->FloatAttribute("maxSpeed") > 0.0) cam->setRotationSpeed(rotationSpeed->FloatAttribute("maxSpeed"));
					if(rotationSpeed->FloatAttribute("acceleration") > 0.0) cam->setRotatioAcceleration(rotationSpeed->FloatAttribute("acceleration"));
					if(rotationSpeed->FloatAttribute("deacceleration") > 0.0) cam->setRotatioDeacceleration(rotationSpeed->FloatAttribute("deacceleration"));
				}

				tinyxml2::XMLElement* movementSpeed = camera->FirstChildElement( "movement" );
				if(movementSpeed)
				{
					if(movementSpeed->FloatAttribute("maxSpeed") > 0.0) cam->setSpeed(movementSpeed->FloatAttribute("maxSpeed"));
					if(movementSpeed->FloatAttribute("acceleration") > 0.0) cam->setAcceleration(movementSpeed->FloatAttribute("acceleration"));
					if(movementSpeed->FloatAttribute("deacceleration") > 0.0) cam->setDeacceleration(movementSpeed->FloatAttribute("deacceleration"));
				}

			}

			tinyxml2::XMLElement* plane = world->FirstChildElement( "plane" );
			if(plane)
			{
					std::string texture = "";
					tinyxml2::XMLElement* textureElement = plane->FirstChildElement( "texture");
					if(textureElement) 
					{
						texture = textureElement->GetText();
					
						float width = 512;
						float height = 512;
						tinyxml2::XMLElement* sizeElement = plane->FirstChildElement( "size" );
						if(sizeElement)
						{
							if(sizeElement->FloatAttribute( "width" ) > 0.0000001) width = sizeElement->FloatAttribute( "width" );
							if(sizeElement->FloatAttribute( "height" ) > 0.0000001) height = sizeElement->FloatAttribute( "height" );

						}

						float x = 0.0;
						float y = 0.0;
						float z = 0.0;
						tinyxml2::XMLElement* positionElement = plane->FirstChildElement( "pos" );
						if(positionElement)
						{
							if(positionElement->Attribute( "x" ) != NULL) x = positionElement->FloatAttribute( "x" );
							if(positionElement->Attribute( "y" ) != NULL) y = positionElement->FloatAttribute( "y" );
							if(positionElement->Attribute( "z" ) != NULL) z = positionElement->FloatAttribute( "z" );

						}

						float rotx = 0.0;
						float roty = 0.0;
						float rotz = 0.0;
						tinyxml2::XMLElement* rotElement = plane->FirstChildElement( "rot" );
						if(rotElement)
						{
							if(rotElement->Attribute( "x" ) != NULL) rotx = rotElement->FloatAttribute( "x" );
							if(rotElement->Attribute( "y" ) != NULL) roty = rotElement->FloatAttribute( "y" );
							if(rotElement->Attribute( "z" ) != NULL) rotz = rotElement->FloatAttribute( "z" );
						}

						ImmersiveKidz::getInstance()->setWorldRect(glm::vec4(x,z,x+width,z+height));
						ImmersiveKidz::getInstance()->loadTexture(scenePath + texture);
						ImmersiveKidz::getInstance()->addDrawableObject(new Plane(scenePath + texture, glm::vec2(width, height), glm::vec3(x,y,z), glm::vec3(rotx,roty,rotz)));
					}
			} else {
				ImmersiveKidz::getInstance()->setWorldRect(glm::vec4(-256,-256,256,256));
			}

			tinyxml2::XMLElement* maskElement = world->FirstChildElement( "mask" );
			if(maskElement)
			{
				for(;maskElement; maskElement = maskElement->NextSiblingElement( "mask" ))
				{
					std::string maskName = maskElement->Attribute( "name" );
					std::string fileName = maskElement->GetText();

					if ( !_createMask((scenePath + fileName).c_str(), maskName) ) 
					{
						_mask[maskName].clear();
						_mask[maskName].push_back(std::vector<bool>());
						_mask[maskName][0].push_back(true);
					}
				}
			}

		}
		else ImmersiveKidz::getInstance()->setWorldRect(glm::vec4(-256,-256,256,256));

		_loadPlanes(scene);
		_loadModels(scene);
		_loadBillboards(scene);
		_loadIllustrations(scene);
		
		ImmersiveKidz::getInstance()->initObjects();
	}
	return _selection;
}

/**
*@brief	    The master encodes data
*
*@param		data		Pointer to the sgct SharedData objects
*
*@return    void
*/
void SceneLoader::encode(sgct::SharedData *data)
{
	data->writeInt32(_selection);
	data->writeInt32(_loaded);
}

/**
*@brief	    The slaves decodes data
*
*@param		data		Pointer to the sgct SharedData objects
*
*@return    void
*/
void SceneLoader::decode(sgct::SharedData *data)
{
	_selection	= data->readInt32();
	_masterLoaded	= data->readInt32();
	
}

bool SceneLoader::_createMask(const char* fileName, std::string maskName)
{
		int x, y;

		int width, height;
		//png_byte color_type;
		//png_byte bit_depth;

		png_structp png_ptr;
		png_infop info_ptr;
		//int number_of_passes;
		png_bytep * row_pointers;
        char header[8]; 

        /* Open file and test for it being a png */
        FILE *fp = fopen(fileName, "rb");
        if (!fp)
                return false;
        if(fread(header, 1, 8, fp) == 0)
           	return false;
        
        if (png_sig_cmp((png_const_bytep)header, 0, 8))
                return false;

        /* Initialize stuff */
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
               return false;

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                return false;

        if (setjmp(png_jmpbuf(png_ptr)))
                return false;

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        width = png_get_image_width(png_ptr, info_ptr);
        height = png_get_image_height(png_ptr, info_ptr);
        //color_type = png_get_color_type(png_ptr, info_ptr);
        //bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        //number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);


        /* Read file */
        if (setjmp(png_jmpbuf(png_ptr)))
                return false;

        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (y=0; y<height; y++)
                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers);

        fclose(fp);


		int c = 3;
		switch(png_get_color_type(png_ptr, info_ptr))
		{
			case PNG_COLOR_TYPE_GRAY:
				c = 1;
				break;
			case PNG_COLOR_TYPE_RGB:
				c = 3;
				break;
			case PNG_COLOR_TYPE_RGBA:
				c = 4;
				break;

		}


		for (y=0; y<height; y++) 
		{
			png_byte* row = row_pointers[y];
			_mask[maskName].push_back(std::vector<bool>());
			for (x=0; x<width; x++) {
					png_byte* ptr = &(row[x*c]);
					_mask[maskName][y].push_back(ptr[0] == 255);
			}
		}

		return true;
}
