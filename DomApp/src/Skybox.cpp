#include "Skybox.h"



Skybox::Skybox(std::string texturename, int size)
{
	this->texturename = texturename;
	this->size = size;
}



void Skybox::drawCube(int size){

		
		glBegin(GL_QUADS);
		
		//Front face
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,-size/2,size/2);
		glVertex3f(size/2,-size/2,size/2);

		//Left face
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(-size/2,-size/2,size/2);

		//Back face
		glVertex3f(size/2,size/2,-size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(size/2,-size/2,-size/2);

		//Right face
		glVertex3f(size/2,size/2,-size/2);
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(size/2,-size/2,size/2);
		glVertex3f(size/2,-size/2,-size/2);

		//Top face
		glVertex3f(size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,size/2);
		glVertex3f(-size/2,size/2,-size/2);
		glVertex3f(size/2,size/2,-size/2);

		//Bottom face
		glVertex3f(size/2,-size/2,size/2);
		glVertex3f(-size/2,-size/2,size/2);
		glVertex3f(-size/2,-size/2,-size/2);
		glVertex3f(size/2,-size/2,-size/2);

		glEnd();


}

void Skybox::draw()
{
	drawCube(size);
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