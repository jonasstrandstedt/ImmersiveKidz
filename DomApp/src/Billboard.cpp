#include "Billboard.h"
#include "ImmersiveKidz.h"

/**
*@brief	    Constructor to the billboard class
*
*@details	Creates a billboard at a position, sets the proportions and assignes a texture to it.
*
*@param		texturename		Unique name of a texture. Ex: "filename.png".
*@param		position	Contains the positions in world coordinates.
*@param		proportionsIn	The proportions of the billboardsize according to the world unit length. 
*/
Billboard::Billboard(std::string texturename , glm::vec3 position, glm::vec2 proportionsIn)
{
	this->_proportions = proportionsIn;
	this->_position = position;
	ImmersiveKidz::getInstance()->loadTexture(texturename);
	_texture = texturename;
	_proportions = proportionsIn;
	_transform = glm::translate(_transform, position);
	
    _listid = glGenLists(1);
    glNewList(_listid, GL_COMPILE);
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
    glEndList();
};


/**
*@brief	    Gets the position of the billboard
*
*@return	vec3
*
*/
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
void Billboard::onDraw() 
{
	glBindTexture( GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByName(_texture));
	float angle = ImmersiveKidz::getInstance()->getCamera()->getRotation().x;
	
	// Bind shader and set the angle
	sgct::ShaderManager::Instance()->bindShader( "SingleBillboard" );
	int angle_loc = sgct::ShaderManager::Instance()->getShader( "SingleBillboard").getUniformLocation( "angle_x" );
	glUniform1f( angle_loc, angle * 3.14/180);
	
    // Draw one obejct from a display list
    glCallList(_listid);
	
	sgct::ShaderManager::Instance()->unBindShader();
	glBindTexture( GL_TEXTURE_2D, 0);
}