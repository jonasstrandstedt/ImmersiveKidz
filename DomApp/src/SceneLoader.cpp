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
		
		if(_selection < 0) _selection = _scenes.size() -1;
		if(_selection >= _scenes.size()) _selection = 0;
		

		if(key == GLFW_KEY_ENTER && state == GLFW_PRESS) 
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
		
			if(i == _selection) 
			{
				glColor3f(1.0f,0.0f,0.0f);
			} else 
			{
				glColor3f(1.0f,1.0f,1.0f);
			}
		
			Freetype::print(sgct::FontManager::Instance()->GetFont( "SGCTFont", 14 ), 50.0f, h-30-20*i, _scenes.at(i).c_str());

			glColor3f(1.0f,1.0f,1.0f);
		
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

	std::string folder =_scenes.at(_selection);
	sgct::MessageHandler::Instance()->print("Loading scene %s\n", folder.c_str());

	ImmersiveKidz::getInstance()->setScenePath(folder);
	std::string scenePath = ImmersiveKidz::getInstance()->getScenePath();
	scenePath = "scenes/" + scenePath;
	
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
	if(scene)
	{
		tinyxml2::XMLElement* world = scene->FirstChildElement( "world" );
		if(world)
		{
			tinyxml2::XMLElement* camera = world->FirstChildElement( "camera" );
			if(camera)
			{
				Camera *cam = ImmersiveKidz::getInstance()->getCamera();
				tinyxml2::XMLElement* start = camera->FirstChildElement( "start" );
				if(start)
				{
					cam->setPosition(glm::vec3(start->DoubleAttribute("x"),start->DoubleAttribute("y"),start->DoubleAttribute("z")));
				}
				tinyxml2::XMLElement* limitx = camera->FirstChildElement( "limitx" );
				if(limitx)
				{
					cam->setLimitsX(glm::vec2(limitx->DoubleAttribute("min"),limitx->DoubleAttribute("max")));
				}
				tinyxml2::XMLElement* limity = camera->FirstChildElement( "limity" );
				if(limity)
				{
					cam->setLimitsY(glm::vec2(limity->DoubleAttribute("min"),limity->DoubleAttribute("max")));
				}
				tinyxml2::XMLElement* limitz = camera->FirstChildElement( "limitz" );
				if(limitz)
				{
					cam->setLimitsZ(glm::vec2(limitz->DoubleAttribute("min"),limitz->DoubleAttribute("max")));
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
					
						double width = 1;
						double height = 1;

						tinyxml2::XMLElement* sizeElement = plane->FirstChildElement( "size" );
						if(sizeElement)
						{
							width = sizeElement->DoubleAttribute( "width" );
							height = sizeElement->DoubleAttribute( "height" );

						}

						double x = 0;
						double y = 0;
						double z = 0;
						tinyxml2::XMLElement* positionElement = plane->FirstChildElement( "pos" );
						if(positionElement)
						{
							x = positionElement->DoubleAttribute( "x" );
							y = positionElement->DoubleAttribute( "y" );
							z = positionElement->DoubleAttribute( "z" );

						}

						double rotx = 0;
						double roty = 0;
						double rotz = 0;
						tinyxml2::XMLElement* rotElement = plane->FirstChildElement( "rot" );
						if(rotElement)
						{
							rotx = rotElement->DoubleAttribute( "x" );
							roty = rotElement->DoubleAttribute( "y" );
							rotz = rotElement->DoubleAttribute( "z" );
						}

						ImmersiveKidz::getInstance()->setWorldRect(glm::vec4(x,z,x+width,z+height));
						ImmersiveKidz::getInstance()->loadTexture(scenePath + texture);
						ImmersiveKidz::getInstance()->addDrawableObject(new Plane(scenePath + texture, glm::vec2(width, height), glm::vec3(x,y,z), glm::vec3(rotx,roty,rotz)));
					}
			}

			_mask["default"].clear();
			_mask["default"].push_back(std::vector<bool>());
			_mask["default"][0].push_back(true);

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


		tinyxml2::XMLElement* plane = scene->FirstChildElement( "plane" );
		if(plane)
		{
			for(;plane; plane = plane->NextSiblingElement( "plane" ))
			{
				std::string texture = "";
				tinyxml2::XMLElement* textureElement = plane->FirstChildElement( "texture");
				if(textureElement) 
				{
					texture = textureElement->GetText();				
					
					double width = 1;
					double height = 1;
					tinyxml2::XMLElement* sizeElement = plane->FirstChildElement( "size" );
					if(sizeElement)
					{
						width = sizeElement->DoubleAttribute( "width" );
						height = sizeElement->DoubleAttribute( "height" );

					}

					double x = 0;
					double y = 0;
					double z = 0;
					tinyxml2::XMLElement* positionElement = plane->FirstChildElement( "pos" );
					if(positionElement)
					{
						x = positionElement->DoubleAttribute( "x" );
						y = positionElement->DoubleAttribute( "y" );
						z = positionElement->DoubleAttribute( "z" );

					}

					double rotx = 0;
					double roty = 0;
					double rotz = 0;
					tinyxml2::XMLElement* rotElement = plane->FirstChildElement( "rot" );
					if(rotElement)
					{
						rotx = rotElement->DoubleAttribute( "x" );
						roty = rotElement->DoubleAttribute( "y" );
						rotz = rotElement->DoubleAttribute( "z" );
					}

					ImmersiveKidz::getInstance()->loadTexture(scenePath + texture);
					ImmersiveKidz::getInstance()->addDrawableObject(new Plane(scenePath + texture, glm::vec2(width, height), glm::vec3(x,y,z), glm::vec3(rotx,roty,rotz)));
				}
			}
		}


		tinyxml2::XMLElement* model = scene->FirstChildElement( "model" );
		if(model)
		{
			for(;model; model = model->NextSiblingElement( "model" ))
			{
				std::string filename = "";
				tinyxml2::XMLElement* fileElement = model->FirstChildElement( "filename" );
				if(fileElement) 
				{
					filename = fileElement->GetText();
				}
				else	continue;

				std::string texture = "";
				tinyxml2::XMLElement* textureElement = model->FirstChildElement( "texture");
				if(textureElement) 
				{
					texture = textureElement->GetText();
				}
				else	continue;
		
				std::string animation = "none";
				double animseed = 0;
				tinyxml2::XMLElement* aniElement = model->FirstChildElement( "animation" );
				if(aniElement) 
				{
					animation = aniElement->Attribute( "name" );
					animseed = aniElement->DoubleAttribute( "seed" );
				}

				srand(time(NULL));
				double posx = 20*((double)rand()/RAND_MAX-0.5);
				double posy = 0;
				double posz  = 20*((double)rand()/RAND_MAX-0.5);
				tinyxml2::XMLElement* posElement = model->FirstChildElement( "pos" );
				if(posElement)
				{
					posx = posElement->DoubleAttribute( "x" );
					posy = posElement->DoubleAttribute( "y" );
					posz = posElement->DoubleAttribute( "z" );
				}

				double scale = 1;
				tinyxml2::XMLElement* scaleElement = model->FirstChildElement( "scale" );
				if(scaleElement)
				{
					scale = scaleElement->DoubleAttribute( "val" );
				}

				double rotx = 0;
				double roty = 0;
				double rotz = 0;
				tinyxml2::XMLElement* rotElement = model->FirstChildElement( "rot" );
				if(rotElement)
				{
					rotx = rotElement->DoubleAttribute( "x" );
					roty = rotElement->DoubleAttribute( "y" );
					rotz = rotElement->DoubleAttribute( "z" );
				}

				ImmersiveKidz::getInstance()->addDrawableObject(new Model(scenePath + filename, scenePath + texture, glm::vec3(posx, posy, posz), scale, glm::vec3(rotx, roty, rotz)), animation, animseed);
			}
		}

		tinyxml2::XMLElement* billboard = scene->FirstChildElement( "billboard" );
		if(billboard)
		{
			for(;billboard; billboard = billboard->NextSiblingElement( "billboard" ))
			{
				std::string texture = "";
				tinyxml2::XMLElement* textureElement = billboard->FirstChildElement( "texture");
				if(textureElement)
				{
					texture = textureElement->GetText();
				}
				else	continue;
		
				std::string animation = "none";
				double animseed = 0;
				tinyxml2::XMLElement* aniElement = billboard->FirstChildElement( "animation" );
				if(aniElement) 
				{
					animation = aniElement->Attribute( "name" );
					animseed = aniElement->DoubleAttribute( "seed" );
				}

				srand(time(NULL));
				double posx = 20*((double)rand()/RAND_MAX-0.5);
				double posy = 0;
				double posz  = 20*((double)rand()/RAND_MAX-0.5);
				tinyxml2::XMLElement* posElement = billboard->FirstChildElement( "pos" );
				if(posElement)
				{
					posx = posElement->DoubleAttribute( "x" );
					posy = posElement->DoubleAttribute( "y" );
					posz = posElement->DoubleAttribute( "z" );
				}

				double sizex = 1;
				double sizey = 1;
				tinyxml2::XMLElement* rotElement = billboard->FirstChildElement( "size" );
				if(rotElement)
				{
					sizex = rotElement->DoubleAttribute( "x" );
					sizey = rotElement->DoubleAttribute( "z" );
				}

				tinyxml2::XMLElement* multElement = billboard->FirstChildElement( "mult" );
				if(multElement)
				{
					int count = multElement->IntAttribute( "count" );
					int seed = multElement->IntAttribute( "seed" );

					tinyxml2::XMLElement* maskElement = billboard->FirstChildElement( "mask" );
					std::string mask = "default";
					if(maskElement) 
					{
						mask = maskElement->Attribute( "name" );
						if ( _mask.count(mask) == 0 ) mask = "default";
					}
					bool billboard = false;
					const char* bb = multElement->Attribute( "billboard" );
					if(bb) 
					{
						std::string bbstring = bb;
						if(bbstring == "yes") billboard = true;
					}


					ImmersiveKidz::getInstance()->addDrawableObject(new BatchBillboard(scenePath + texture, &_mask[mask], seed, count, glm::vec2(sizex , sizey), billboard), animation, animseed);
					
				}
				else 
				{
					ImmersiveKidz::getInstance()->addDrawableObject(new Billboard(scenePath + texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey)), animation, animseed);
				}
			}
		}

		tinyxml2::XMLElement* illustration = scene->FirstChildElement( "illustration" );
		if(illustration)
		{
			for(;illustration; illustration = illustration->NextSiblingElement( "illustration" ))
			{
				std::string name_artist = "Unnamed artist";
				tinyxml2::XMLElement* artistElement = illustration->FirstChildElement( "name_artist" );
				if(artistElement) 
				{
					name_artist = artistElement->GetText();
				}

				std::string name_drawing = "Unnamed drawing";
				tinyxml2::XMLElement* drawingeElement = illustration->FirstChildElement( "name_drawing" );
				if(drawingeElement) 
				{
					name_drawing = drawingeElement->GetText();
				}

				std::string description = "Unnamed description";
				tinyxml2::XMLElement* descElement = illustration->FirstChildElement( "description" );
				if(descElement)
				{
					description = descElement->GetText();
				}					
		
				std::string animation = "none";
				double animseed = 0;
				tinyxml2::XMLElement* aniElement = illustration->FirstChildElement( "animation" );
				if(aniElement) 
				{
					animation = aniElement->Attribute( "name" );
					animseed = aniElement->DoubleAttribute( "seed" );
				}

				std::string texture = "";
				tinyxml2::XMLElement* textureElement = illustration->FirstChildElement( "texture");
				if(textureElement) 
				{
					texture = textureElement->GetText();
				}
				else	continue;

				srand(time(NULL));
				double posx = 20*((double)rand()/RAND_MAX-0.5);
				double posy = 0;
				double posz  = 20*((double)rand()/RAND_MAX-0.5);
				tinyxml2::XMLElement* posElement = illustration->FirstChildElement( "pos" );
				if(posElement)
				{
					posx = posElement->DoubleAttribute( "x" );
					posy = posElement->DoubleAttribute( "y" );
					posz = posElement->DoubleAttribute( "z" );
				}

				double sizex = 1;
				double sizey = 1;
				tinyxml2::XMLElement* rotElement = illustration->FirstChildElement( "size" );
				if(rotElement)
				{
					sizex = rotElement->DoubleAttribute( "x" );
					sizey = rotElement->DoubleAttribute( "z" );
				}
			
				ImmersiveKidz::getInstance()->addDrawableObject(new Illustration(scenePath + texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey), name_artist, name_drawing, description), animation, animseed);
			}
		}
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
		png_byte color_type;
		png_byte bit_depth;

		png_structp png_ptr;
		png_infop info_ptr;
		int number_of_passes;
		png_bytep * row_pointers;
        char header[8]; 

        /* Open file and test for it being a png */
        FILE *fp = fopen(fileName, "rb");
        if (!fp)
                return false;
        fread(header, 1, 8, fp);
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
        color_type = png_get_color_type(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        number_of_passes = png_set_interlace_handling(png_ptr);
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
		switch(png_get_color_type(png_ptr, info_ptr)){
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


		for (y=0; y<height; y++) {
			png_byte* row = row_pointers[y];
			_mask[maskName].push_back(std::vector<bool>());
			for (x=0; x<width; x++) {
					png_byte* ptr = &(row[x*c]);
					_mask[maskName][y].push_back(ptr[0] == 255);
			}
		}

		return true;
}
