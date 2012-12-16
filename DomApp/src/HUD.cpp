#include "HUD.h"
#include "ImmersiveKidz.h"

HUD::HUD()
{
	_textureMinimap = "minimap";
	_selection = 0;
	_offset = 0;
	_minimapWidth = 200;
	_minimapHeight = 200;
	_zoom = static_cast<float>(0.2);
}

/**
* @brief 
* 
* @details 
*/
void HUD::init()
{
	sgct::TextureManager::Instance()->loadTexure("menu", "data/HUD/menu.png", true, 0); //Load HUD(menu) into OpenGL
	sgct::TextureManager::Instance()->loadTexure("minimap", "scenes/Safari/textures/map.png", true, 0); //Load HUD(minimap) into OpenGL
}


/**
* @brief Handles drawing of HUD elements 
* 
* @details The drawing of each component is done in its own functions
*/
void HUD::draw(std::vector<Illustration*> illu)
{
	//Draw menu	
	_drawIllustrationNames(illu);

	//Draw Minimap
	_drawMinimap(illu);
}

/**
*@brief	    Sets the name of the minimap - texture
*
*@param		texture	- A string with the alias of the loaded texture
*/

void HUD::setTextureMinimap(std::string texture) 
{
	_textureMinimap = texture; 
}

/**
*@brief	    Draws the names of the painters
*
*@details	Loops through all illustrations and draws the name of the artist on a new line
*
*@param	illu	A vector containing the illustrations
*/

void HUD::_drawIllustrationNames(std::vector<Illustration*> illu)
{
	_drawBackgroundToNames();
	int textX , textY;
	int winSizeY = sgct::Engine::getWindowPtr()->getVResolution(); //Gives us the hight of the window
	//int winSizeX = sgct::Engine::getWindowPtr()->getHResolution(); //Gives us the width of the window

	textX = 20;
	textY = 15 + _offset;

	for(unsigned int i = 0; i < illu.size(); i++)
	{

		//Set color of menu text
		if(static_cast<int>(i) == _selection) 
		{
			glColor3f(0.0f,0.0f,0.0f);
		} 
		else 
		{
			glColor3f(0.7f,0.7f,0.7f);
		}

		Freetype::print( 	sgct::FontManager::Instance()->GetFont( "SGCTFont", 12 ), 
							static_cast<float>(textX), 
							static_cast<float>(winSizeY - textY), 
							illu[i]->getName().c_str());

		glColor3f(1.0f,1.0f,1.0f);

		//Checks if the illustration has been seen and marks it as seen.
		//Set color of menu-seen-marking
		if(illu[i]->getSeen()) 
		{
			glColor3f(0.0f,0.0f,0.0f);
		} 
		else 
		{
			glColor3f(0.7f,0.7f,0.7f);
		}
		
		Freetype::print( 	sgct::FontManager::Instance()->GetFont( "SGCTFont", 14 ), 
							static_cast<float>(textX - 15), 
							static_cast<float>(winSizeY - textY), 
							"#");

		glColor3f(1.0f,1.0f,1.0f);

		textY = textY + 14;
	};
}

/**
*@brief	    Draws the background to the list of painters
*
*@details	Draws the background to the list of painters
*/

void HUD::_drawBackgroundToNames()
{
	glDisable(GL_DEPTH_TEST);
	glBindTexture( GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByName("menu"));

	int winSizeY = sgct::Engine::getWindowPtr()->getVResolution(); //Gives us the hight of the window
	int winSizeX = sgct::Engine::getWindowPtr()->getHResolution(); //Gives us the width of the window

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	glOrtho(0,winSizeX,0,winSizeY ,-100,100);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glBegin(GL_QUADS);

	//Vertex 1 
	glTexCoord2d(0.0,0.0);
	glVertex3f(0 , static_cast<float>(_minimapWidth) , 0);
	
	//Vertex 2 
	glTexCoord2d(1.0,0.0);
	glVertex3f(static_cast<float>(_minimapWidth) , static_cast<float>(_minimapWidth) , 0);
	
	//Vertex 3 
	glTexCoord2d(1.0,1.0);
	glVertex3f(static_cast<float>(_minimapWidth ), static_cast<float>(winSizeY ), 0);
	
	//Vertex 4 
	glTexCoord2d(0.0,1.0);
	glVertex3f(0 , static_cast<float>(winSizeY) , 0);

	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); 

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glBindTexture( GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
}

/**
*@brief	    Draws the minimap background
*
*@return    void
*/
void HUD::_drawMinimapBackground()
{

	glBindTexture(GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByName(_textureMinimap));

	//int winSizeY = sgct::Engine::getWindowPtr()->getVResolution(); //Gives us the hight of the window
	//int winSizeX = sgct::Engine::getWindowPtr()->getHResolution(); //Gives us the width of the window

	glBegin(GL_QUADS);
	glm::vec4 worldRect = ImmersiveKidz::getInstance()->getWorldRect();
	glm::vec3 camPosition = ImmersiveKidz::getInstance()->getCamera()->getPosition();
	
	glm::vec4 zoomMap(	camPosition.x - static_cast<float>(_minimapWidth) * _zoom,
						camPosition.z + 4 - static_cast<float>(_minimapHeight) * _zoom, 
						camPosition.x +  static_cast<float>(_minimapWidth) * _zoom,
						camPosition.z + 4  + static_cast<float>(_minimapHeight) * _zoom);

	float minx = (zoomMap.x - worldRect.x) / (worldRect.z - worldRect.x);
	float maxy = 1-(zoomMap.y - worldRect.y) / (worldRect.w - worldRect.y);

	float maxx = (zoomMap.z - worldRect.x) / (worldRect.z - worldRect.x);
	float miny = 1-(zoomMap.w - worldRect.y) / (worldRect.w - worldRect.y);


	//Vertex 1 
	glTexCoord2d(maxx,maxy);
	glVertex3f(0 , 0 , 0);
	
	//Vertex 2 
	glTexCoord2d(minx,maxy);
	glVertex3f(static_cast<float>(_minimapWidth) , 0 , 0);
	
	//Vertex 3 
	glTexCoord2d(minx,miny);
	glVertex3f(static_cast<float>(_minimapWidth) , static_cast<float>(_minimapHeight) , 0);
	
	//Vertex 4 
	glTexCoord2d(maxx,miny);
	glVertex3f(0 , static_cast<float>(_minimapHeight) , 0);

	glEnd();
	glBindTexture( GL_TEXTURE_2D, 0);

}

/**
*@brief	    Draws the minimap
*
*@param	illu	A vector containing the illustrations
*
*@return    void
*/
void HUD::_drawMinimap(std::vector<Illustration*> illu)
{
	
	//glm::vec4 worldRect = ImmersiveKidz::getInstance()->getWorldRect();
	glm::vec3 camPosition = ImmersiveKidz::getInstance()->getCamera()->getPosition();
	glm::vec2 camRotation = ImmersiveKidz::getInstance()->getCamera()->getRotation();

	glDisable(GL_DEPTH_TEST);

	int winSizeY = sgct::Engine::getWindowPtr()->getVResolution();//Gives us the hight of the window
	int winSizeX = sgct::Engine::getWindowPtr()->getHResolution();//Gives us the width of the window
	
	
	float fov = 20;

	//Create a wordrect but in zoomed format, contains (xmin,ymin,xmax,ymax) * zoomfactor relative to the minimap
	/*
	glm::vec4 zoomRect(		camPosition.x - _minimapWidth * _zoom,
							camPosition.z + 4 - _minimapHeight * _zoom, 
							camPosition.x +  _minimapWidth * _zoom,
							camPosition.z +4  + _minimapHeight * _zoom);
							*/
	glm::vec4 zoomRect(	camPosition.x - static_cast<float>(_minimapWidth) * _zoom,
						camPosition.z + 4 - static_cast<float>(_minimapHeight) * _zoom, 
						camPosition.x +  static_cast<float>(_minimapWidth) * _zoom,
						camPosition.z + 4  + static_cast<float>(_minimapHeight) * _zoom);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	glOrtho(0,winSizeX,0,winSizeY ,-100,100);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the background to the minimap
	_drawMinimapBackground();

	//Draw the illustrations on the minimap
	glPointSize(5.0f);
	glBegin(GL_POINTS);

	//Draw illustrations on minimap
	for(unsigned int i = 0; i < illu.size(); i++)
	{
		if(static_cast<int>(i) == _selection)
		{
			glColor3f( 0.0f, 0.0f, 1.0f);	
		}else if(illu[i]->getSeen())
		{
			glColor3f( 0.0f, 1.0f, 0.0f);			
		}else{
			glColor3f( 1.0f, 0.0f, 0.0f);
		}
		
		glm::vec3 illuPosition = illu[i]->getPosition();

		float illux = 1-(illuPosition.x - zoomRect.x) / (zoomRect.z - zoomRect.x);
		float illuy = (illuPosition.z - zoomRect.y) / (zoomRect.w - zoomRect.y);

		if(illux >= 0 && illux <= 1 && illuy >= 0 && illuy <= 1)
			glVertex2f(illux * static_cast<float>(_minimapWidth), illuy * static_cast<float>(_minimapHeight));

		glColor3f( 1.0f, 1.0f, 1.0f);
	}
	//Set camera to black
	glColor3f(1,1,1);
	//Cameradot in middle of the map
	glVertex2f(static_cast<float>(_minimapWidth /2),static_cast<float>(_minimapHeight /2));
	glEnd();
	glBegin(GL_LINE_LOOP);

	
	glm::vec4 dir1 = glm::rotate(glm::mat4(),camRotation.x+fov,glm::vec3(0.0f,1.0f,0.0f)) * glm::vec4(0,0,-30,0);
	glm::vec4 dir2 = glm::rotate(glm::mat4(),camRotation.x-fov,glm::vec3(0.0f,1.0f,0.0f)) * glm::vec4(0,0,-30,0);
	
	//Paints the cameralines.
	glVertex2f(static_cast<float>(_minimapWidth /2),static_cast<float>(_minimapHeight /2));
	glVertex2f(static_cast<float>(_minimapWidth/2) + dir1.x , static_cast<float>(_minimapHeight/2) + dir1.z );
	glEnd();
	glBegin(GL_LINE_LOOP);

	glVertex2f(static_cast<float>(_minimapWidth /2),static_cast<float>(_minimapHeight /2));
	glVertex2f(static_cast<float>(_minimapWidth/2) + dir2.x , static_cast<float>(_minimapHeight/2) + dir2.z );

	glEnd();
	glColor3f(1,1,1);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); 

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

}

/**
* @brief	A method to set the state of a keyboard button
*
* @param	key			The key that is interacted with 
* @param	state		The state, if the button is pressed or not 
* @param    illu		A vector containing the illustrations		
*/

void HUD::keyboardButton(int key,int state, std::vector<Illustration*> illu) 
{
	//Changes selected illustration in the list
	if(key == GLFW_KEY_UP && state == GLFW_PRESS) _selection--;
	if(key == GLFW_KEY_DOWN && state == GLFW_PRESS) _selection++;

	//Zoomes in & out on the minimap
	if(_zoom > 0.11)
		if(key == GLFW_KEY_KP_SUBTRACT && state == GLFW_PRESS) _zoom = _zoom - static_cast<float>(0.1);
	if(_zoom <= 1)
		if(key == GLFW_KEY_KP_ADD && state == GLFW_PRESS) _zoom = _zoom + static_cast<float>(0.1);
	
	//Gives the selected illustration a specific animation
	if(key == '1' && state == GLFW_PRESS) illu[_selection]->addAnimation(new Jump(1.0));
	if(key == '2' && state == GLFW_PRESS) illu[_selection]->addAnimation(new Jump(1.0, 1.0));
	if(key == '3' && state == GLFW_PRESS) illu[_selection]->addAnimation(new Strafe(1));

	if(_selection < 0) _selection = 0;
	if(_selection >= static_cast<int>(illu.size())) _selection = static_cast<int>(illu.size()) -1;

	if(key == GLFW_KEY_ENTER && state == GLFW_PRESS) 
	{
		illu[_selection]->setSeen(true);
	};

	int winSizeY = sgct::Engine::getWindowPtr()->getVResolution(); //Gives us the hight of the window
	int list_height = winSizeY - _minimapHeight;

	// check if need to increase offset for animal list
	if(list_height - ( 15 + _selection *14 + _offset) < 0) 
	{
		_offset -= 14*4;
	}

	// check if need to decrease offset for animal list
	if((-15-_selection *14 - _offset) > -15)
	{
		_offset += 14*4;

		if(_offset > 0) 
		{
			_offset = 0;
		}
	}
}
