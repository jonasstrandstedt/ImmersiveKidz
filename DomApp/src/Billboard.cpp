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
	_texture = texturename;
	ImmersiveKidz::getInstance()->loadTexture(_texture);
	_proportions = proportionsIn;
	_transform = glm::translate(_transform, position);
	
	_listid = 0;
    
	_vsize = 4;
	_isize = 6;
    _varray = (Vertex*)malloc(_vsize*sizeof(Vertex));
    _iarray = (int*)malloc(_isize*sizeof(int));
	
	_varray[0].location[0] = -0.5 * _proportions[0];
	_varray[0].location[1] = 0;
	_varray[0].location[2] = 0;
	_varray[1].location[0] = 0.5 * _proportions[0];
	_varray[1].location[1] = 0;
	_varray[1].location[2] = 0;
	_varray[2].location[0] = 0.5 * _proportions[0];
	_varray[2].location[1] = _proportions[1];
	_varray[2].location[2] = 0;
	_varray[3].location[0] = -0.5 * _proportions[0];
	_varray[3].location[1] = _proportions[1];
	_varray[3].location[2] = 0;
	
	_varray[0].tex[0] = 0;
	_varray[0].tex[1] = 0;
	_varray[1].tex[0] = 1;
	_varray[1].tex[1] = 0;
	_varray[2].tex[0] = 1;
	_varray[2].tex[1] = 1;
	_varray[3].tex[0] = 0;
	_varray[3].tex[1] = 1;

	_iarray[0] = 0;
	_iarray[1] = 1;
	_iarray[2] = 2;
	_iarray[3] = 0;
	_iarray[4] = 2;
	_iarray[5] = 3;

	for (int i = 0; i < 4; ++i)
	{
		_varray[i].normal[0] = 1;
		_varray[i].normal[1] = 0;
		_varray[i].normal[2] = 0;
		_varray[i].colour[0] = 1;
		_varray[i].colour[1] = 1;
		_varray[i].colour[2] = 1;
		_varray[i].colour[3] = 1;
		_varray[i].attribute[0] = position[0];
		_varray[i].attribute[1] = position[1];
		_varray[i].attribute[2] = position[2];
		_varray[i].float_attribute = 0;
	}
}

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
	_drawVBO();
	
	sgct::ShaderManager::Instance()->unBindShader();
	glBindTexture( GL_TEXTURE_2D, 0);

}