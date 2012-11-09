#include "Skybox.h"
#include "ImmersiveKidz.h"



Skybox::Skybox()
{
	this->texturename = texturename;
	//this->100 = 100;
}

void Skybox::loadTextures(std::string textureNames[6])
{
	sgct::TextureManager::Instance()->loadTexure("skybox_xpos",textureNames[CUBEMAP_TEX_X_POSITIVE],true,0);
	sgct::TextureManager::Instance()->loadTexure("skybox_xneg",textureNames[CUBEMAP_TEX_X_NEGATIVE],true,0);
	sgct::TextureManager::Instance()->loadTexure("skybox_ypos",textureNames[CUBEMAP_TEX_Y_POSITIVE],true,0);
	sgct::TextureManager::Instance()->loadTexure("skybox_yneg",textureNames[CUBEMAP_TEX_Y_NEGATIVE],true,0);
	sgct::TextureManager::Instance()->loadTexure("skybox_zpos",textureNames[CUBEMAP_TEX_Z_POSITIVE],true,0);
	sgct::TextureManager::Instance()->loadTexure("skybox_zneg",textureNames[CUBEMAP_TEX_Z_NEGATIVE],true,0);


}


void Skybox::drawCube(){

		//Back Face
		glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName("skybox_zneg"));
		glBegin(GL_QUADS);		
		glTexCoord2f(0,1);      //11,01,00,10
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
		glTexCoord2f(0,1);   //11,10,00,01
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
		glTexCoord2f(1,1);      //11,01,00,10
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
		glTexCoord2f(0,1);        //00,01,11,10
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
		


}

void Skybox::onDraw()
{
	glPushMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glm::vec3 camPos = ImmersiveKidz::getInstance()->getCamera()->getPosition();
	glTranslatef(camPos[0],camPos[1],camPos[2]);
	drawCube();
	//glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glPopMatrix();

}


/*
void setupCubeMap(GLuint& texture) {
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
void setupCubeMap(GLuint& texture, SDL_Surface *xpos, SDL_Surface *xneg, SDL_Surface *ypos, SDL_Surface *yneg, SDL_Surface *zpos, SDL_Surface *zneg) {
	setupCubeMap(texture);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, xpos->w, xpos->h, 0, xpos->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, xpos->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, xneg->w, xneg->h, 0, xneg->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, xneg->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, ypos->w, ypos->h, 0, ypos->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, ypos->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, yneg->w, yneg->h, 0, yneg->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, yneg->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, zpos->w, zpos->h, 0, zpos->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, zpos->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, zneg->w, zneg->h, 0, zneg->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, zneg->pixels);
}

void deleteCubeMap(GLuint& texture) {
	glDeleteTextures(1, &texture);
}
*/