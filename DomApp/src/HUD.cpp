#include "HUD.h"
#include "ImmersiveKidz.h"

HUD::HUD()
{
	sgct::TextureManager::Instance()->loadTexure("menu", "HUD/menu.png", true, 0); //Load HUD into OpenGL
	sgct::TextureManager::Instance()->loadTexure("minimap", "HUD/minimap.png", true, 0); //Load HUD into OpenGL
	_selection = 0;
};

/**
*@brief	    Draws the names of the painters
*
*@details	Function called from ImmersiveKidz::draw()
*
*@return    void
*/

void HUD::drawIllustrationNames(std::vector<Illustration*> illu)
{
	int x , y;
	int winSizeY = sgct::Engine::getWindowPtr()->getVResolution();//Gives us the hight of the window
	int winSizeX = sgct::Engine::getWindowPtr()->getHResolution();//Gives us the width of the window

	x = 20;
	y = 30;

	for(int i = 0; i < illu.size(); i++)
	{

		//Set color of menu text
		if(i == _selection) {
			glColor3f(0.0f,0.0f,0.0f);
		} else {
			glColor3f(0.7f,0.7f,0.7f);
		}

		Freetype::print( sgct::FontManager::Instance()->
			GetFont( "SGCTFont", 14 ), 0 + x, winSizeY - y, illu[i]->getName().c_str());

		glColor3f(1.0f,1.0f,1.0f);

		//Checks if the illustration has been seen and marks it as seen.
		//Set color of menu-seen-marking
		if(illu[i]->getSeen()) {
			glColor3f(0.0f,0.0f,0.0f);
		} else {
			glColor3f(0.7f,0.7f,0.7f);
		}

		Freetype::print( sgct::FontManager::Instance()->
			GetFont( "SGCTFont", 14 ), -15 + x, winSizeY - y, "#");

		glColor3f(1.0f,1.0f,1.0f);

		y = y + 20;
	};
};

/**
*@brief	    Draws the background to the painters of the illustrations names
*
*@details	Function called from ImmersiveKidz::draw()
*
*@return    void
*/

void HUD::drawBackgroundToNames()
{
	glDisable(GL_DEPTH_TEST);
	glBindTexture( GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByName("menu"));

	int winSizeY = sgct::Engine::getWindowPtr()->getVResolution();//Gives us the hight of the window
	int winSizeX = sgct::Engine::getWindowPtr()->getHResolution();//Gives us the width of the window

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
	glVertex3f(0 , 150 , 0);
	
	//Vertex 2 
	glTexCoord2d(1.0,0.0);
	glVertex3f(150 , 150 , 0);
	
	//Vertex 3 
	glTexCoord2d(1.0,1.0);
	glVertex3f(150 , winSizeY , 0);
	
	//Vertex 4 
	glTexCoord2d(0.0,1.0);
	glVertex3f(0 , winSizeY , 0);

	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); 

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glBindTexture( GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
}

void HUD::drawMinimapBackground()
{
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByName("minimap"));

	int winSizeY = sgct::Engine::getWindowPtr()->getVResolution();//Gives us the hight of the window
	int winSizeX = sgct::Engine::getWindowPtr()->getHResolution();//Gives us the width of the window

	int sizeY = 150;
	int sizeX = 250;

	

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
	glVertex3f(0 , 0 , 0);
	
	//Vertex 2 
	glTexCoord2d(1.0,0.0);
	glVertex3f(sizeX , 0 , 0);
	
	//Vertex 3 
	glTexCoord2d(1.0,1.0);
	glVertex3f(sizeX , sizeY , 0);
	
	//Vertex 4 
	glTexCoord2d(0.0,1.0);
	glVertex3f(0 , sizeY , 0);

	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); 

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glBindTexture( GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);

}

void HUD::drawMinimapPositions(std::vector<Illustration*> illu)
{
	glm::vec4 worldRect = ImmersiveKidz::getInstance()->getWorldRect();
	glm::vec3 camPosition = ImmersiveKidz::getInstance()->getCamera()->getPosition();
	glm::vec2 camRotation = ImmersiveKidz::getInstance()->getCamera()->getRotation();

	glDisable(GL_DEPTH_TEST);
	//Time to draw the positions
	glBindTexture( GL_TEXTURE_2D, 0);


	int winSizeY = sgct::Engine::getWindowPtr()->getVResolution();//Gives us the hight of the window
	int winSizeX = sgct::Engine::getWindowPtr()->getHResolution();//Gives us the width of the window

	int sizeY = 150;
	int sizeX = 250;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	glOrtho(0,winSizeX,0,winSizeY ,-100,100);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glPointSize(20.0f);
	glBegin(GL_POINTS);
	//Draw illustrations on minimap
	for(int i = 0; i < illu.size(); i++)
	{
		
		if(i == _selection)
		{
			glColor3f( 0.0f, 0.0f, 1.0f);	
		}else if(illu[i]->getSeen())
		{
			glColor3f( 0.0f, 1.0f, 0.0f);			
		}else		{
			glColor3f( 1.0f, 0.0f, 0.0f);
		}

		glm::vec3 illuPosition = illu[i]->getPosition();

		float x = (illuPosition.x - worldRect.x) / (worldRect.z - worldRect.x);
		float y = (illuPosition.z - worldRect.y) / (worldRect.w - worldRect.y);


		glVertex2f(x * sizeX  , y * sizeY);


		glColor3f( 1.0f, 1.0f, 1.0f);
	}
	//Draw camera on minimap
	float x = (camPosition.x - worldRect.x) / (worldRect.z - worldRect.x);
	float y = (camPosition.z - worldRect.y) / (worldRect.w - worldRect.y);


	glVertex2f(x * sizeX  , y * sizeY);



	glEnd();

	

	
	

	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); 

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

}


void HUD::mouseButton(int button,int state)
{
	if(button == 0){
		
		std::cout << "button pressed" << std::endl;
		//mouseState = state;
		//ImmersiveKidz::getInstance()->getEngine()->setMousePointerVisibility(!state);
	}
}

void HUD::mouseMotion(int dx,int dy){
	if(mouseState){
		std::cout << dx << std::endl; 
		std::cout << dy << std::endl;
	}
}

void HUD::keyboardButton(int key,int state, std::vector<Illustration*> illu)
{
		if(key == GLFW_KEY_UP && state == GLFW_PRESS) _selection--;
		if(key == GLFW_KEY_DOWN && state == GLFW_PRESS) _selection++;

		if(_selection < 0) _selection = illu.size() -1;
		if(_selection >= illu.size()) _selection = 0;

		if(key == GLFW_KEY_ENTER && state == GLFW_PRESS) 
		{
			illu[_selection]->setSeen(true);
		};
}