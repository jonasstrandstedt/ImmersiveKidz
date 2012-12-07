#include "Skybox.h"
#include "ImmersiveKidz.h"

/**
*@brief Constructor for skybox
*
*@details Default constructor for skybox, does not do any logic. LoadTextures should be used to add textures to the skybox
*/

Skybox::Skybox(){

}

/**
*@brief	    Loads textures to skybox
*
*@details   Loads textures with sgct:s texture manager
*
*@param		textureNames		The names of the skybox textures
*/
void Skybox::loadTextures(std::string textureNames[6])
{
	sgct::TextureManager::Instance()->loadTexure("skybox_xpos",textureNames[CUBEMAP_TEX_X_POSITIVE],true,0);
	sgct::TextureManager::Instance()->loadTexure("skybox_xneg",textureNames[CUBEMAP_TEX_X_NEGATIVE],true,0);
	sgct::TextureManager::Instance()->loadTexure("skybox_ypos",textureNames[CUBEMAP_TEX_Y_POSITIVE],true,0);
	sgct::TextureManager::Instance()->loadTexure("skybox_yneg",textureNames[CUBEMAP_TEX_Y_NEGATIVE],true,0);
	sgct::TextureManager::Instance()->loadTexure("skybox_zpos",textureNames[CUBEMAP_TEX_Z_POSITIVE],true,0);
	sgct::TextureManager::Instance()->loadTexure("skybox_zneg",textureNames[CUBEMAP_TEX_Z_NEGATIVE],true,0);
}

/**
*@brief	    Creates the skybox 
*
*@details   Assigns the textures to each face and defines the skyboxparameters. 
*/
void Skybox::_drawCube(){

		//Back Face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_zneg"));
		glBegin(GL_QUADS);		
		glTexCoord2f(0,1);     
		glVertex3f(1000,1000,1000);
		glTexCoord2f(1,1);
		glVertex3f(-1000,1000,1000);
		glTexCoord2f(1,0);
		glVertex3f(-1000,-1000,1000);
		glTexCoord2f(0,0);
		glVertex3f(1000,-1000,1000);
		glEnd();

		//Left face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_xneg"));
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);   
		glVertex3f(-1000,1000,1000);
		glTexCoord2f(1,1);
		glVertex3f(-1000,1000,-1000);
		glTexCoord2f(1,0);
		glVertex3f(-1000,-1000,-1000);
		glTexCoord2f(0,0);
		glVertex3f(-1000,-1000,1000);
		glEnd();

		//Front face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_zpos"));
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);      
		glVertex3f(1000,1000,-1000);
		glTexCoord2f(0,1);
		glVertex3f(-1000,1000,-1000);
		glTexCoord2f(0,0);
		glVertex3f(-1000,-1000,-1000);
		glTexCoord2f(1,0);
		glVertex3f(1000,-1000,-1000);
		glEnd();

		//Right face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_xpos"));
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);        
		glVertex3f(1000,1000,-1000);
		glTexCoord2f(1,1);
		glVertex3f(1000,1000,1000);
		glTexCoord2f(1,0);
		glVertex3f(1000,-1000,1000);
		glTexCoord2f(0,0);
		glVertex3f(1000,-1000,-1000);
		glEnd();
		//Top face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_ypos"));
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);
		glVertex3f(1000,1000,1000);
		glTexCoord2f(0,1);
		glVertex3f(-1000,1000,1000);
		glTexCoord2f(0,0);
		glVertex3f(-1000,1000,-1000);
		glTexCoord2f(1,0);
		glVertex3f(1000,1000,-1000);
		glEnd();
		//Bottom face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_yneg"));
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);
		glVertex3f(1000,-1000,1000);
		glTexCoord2f(0,1);
		glVertex3f(-1000,-1000,1000);
		glTexCoord2f(0,0);
		glVertex3f(-1000,-1000,-1000);
		glTexCoord2f(1,0);
		glVertex3f(1000,-1000,-1000);
		glEnd();

		glBindTexture(GL_TEXTURE_2D,0);
}


/**
*@brief	    Draws the skybox
*
*@details   Draws the skybox aligned at the center of the camera
*
*@param		textureNames		The names of the skybox textures
*
*@return	void
*/

void Skybox::onDraw()
{
	glPushMatrix();
	glm::vec3 camPos = ImmersiveKidz::getInstance()->getCamera()->getPosition();
	glTranslatef(camPos[0],camPos[1],camPos[2]);
	_drawCube();
	glPopMatrix();
}