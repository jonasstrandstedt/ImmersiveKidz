#include "Billboard.h"
#include "ImmersiveKidz.h"

/**
*@brief	    Brief description
*
*@details   Detailed description (Extends the brief description)
*
*@param		texturename Unique name of a texture. Ex: "texture.png".
*@param		position Contains the positions in world coordinates.
*@param		proportionsIn The proportions of the billboardsize according to the world unit length. 
*/
Billboard::Billboard(std::string texturename , glm::vec3 position, glm::vec2 proportionsIn)
{
	this->_proportions = proportionsIn;
	this->_position = position;
	_transform = glm::translate(_transform, position);
	sgct::TextureManager::Instance()->loadTexure(_texture, texturename, texturename, true);
	_proportions = proportionsIn;
	_transform = glm::translate(_transform, position);
};

glm::vec3 Billboard::getPosition()
{
	return _position;
}

/**
*@brief		Draws the Billboard. 
*
*@details	Draws a texture on a Billboard(Quad perpendicual to the camera position).
*
*@return    void
*/
void Billboard::onDraw() {
	
	//sgct::MessageHandler::Instance()->print("Billboard draw\n");

	glBindTexture( GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByIndex(_texture));


	glPushMatrix();
	float angle = ImmersiveKidz::getInstance()->getCamera()->getRotation().x;
	//Rotate Billboard towards the camera position.
	glRotatef(-angle, 0.0 , 1.0 , 0.0);
	

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);

	//Vertex 1 
	glTexCoord2d(0.0,0.0);
	glVertex3f(-0.5 * _proportions[0] , 0 , 0);
	
	//Vertex 2 
	glTexCoord2d(1.0,0.0);
	glVertex3f(0.5 * _proportions[0] , 0 , 0);
	
	//Vertex 3 
	glTexCoord2d(1.0,1.0);
	glVertex3f(0.5 * _proportions[0] , _proportions[1] , 0);
	
	//Vertex 4 
	glTexCoord2d(0.0,1.0);
	glVertex3f(-0.5 * _proportions[0] , _proportions[1] , 0);

	glEnd();
	glDisable (GL_BLEND);

	glPopMatrix();
}