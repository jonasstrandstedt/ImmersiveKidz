#include "Skybox.h"
#include "ImmersiveKidz.h"


/**
*@brief	    Loads textures to skybox
*
*@details   Loads textures and assigns them to sgct:s texture manager
*
*@param		textureNames
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
*
*/
void Skybox::drawCube(){

		//Back Face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_zneg"));
		glBegin(GL_QUADS);		
		glTexCoord2f(0,1);     
		glVertex3f(50,50,50);
		glTexCoord2f(1,1);
		glVertex3f(-50,50,50);
		glTexCoord2f(1,0);
		glVertex3f(-50,-50,50);
		glTexCoord2f(0,0);
		glVertex3f(50,-50,50);
		glEnd();

		//Left face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_xneg"));
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);   
		glVertex3f(-50,50,50);
		glTexCoord2f(1,1);
		glVertex3f(-50,50,-50);
		glTexCoord2f(1,0);
		glVertex3f(-50,-50,-50);
		glTexCoord2f(0,0);
		glVertex3f(-50,-50,50);
		glEnd();

		//Front face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_zpos"));
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);      
		glVertex3f(50,50,-50);
		glTexCoord2f(0,1);
		glVertex3f(-50,50,-50);
		glTexCoord2f(0,0);
		glVertex3f(-50,-50,-50);
		glTexCoord2f(1,0);
		glVertex3f(50,-50,-50);
		glEnd();

		//Right face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_xpos"));
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);        
		glVertex3f(50,50,-50);
		glTexCoord2f(1,1);
		glVertex3f(50,50,50);
		glTexCoord2f(1,0);
		glVertex3f(50,-50,50);
		glTexCoord2f(0,0);
		glVertex3f(50,-50,-50);
		glEnd();
		//Top face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_ypos"));
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);
		glVertex3f(50,50,50);
		glTexCoord2f(0,1);
		glVertex3f(-50,50,50);
		glTexCoord2f(0,0);
		glVertex3f(-50,50,-50);
		glTexCoord2f(1,0);
		glVertex3f(50,50,-50);
		glEnd();
		//Bottom face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_yneg"));
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);
		glVertex3f(50,-50,50);
		glTexCoord2f(0,1);
		glVertex3f(-50,-50,50);
		glTexCoord2f(0,0);
		glVertex3f(-50,-50,-50);
		glTexCoord2f(1,0);
		glVertex3f(50,-50,-50);
		glEnd();

		glBindTexture(GL_TEXTURE_2D,0);
}


/**
*@brief	    Draws the skybox
*
*@details   Draws the skybox at the center of the camera
*
*@param		textureNames
*/

void Skybox::onDraw()
{
	glPushMatrix();
	glm::vec3 camPos = ImmersiveKidz::getInstance()->getCamera()->getPosition();
	glTranslatef(camPos[0],camPos[1],camPos[2]);
	drawCube();
	glPopMatrix();

}