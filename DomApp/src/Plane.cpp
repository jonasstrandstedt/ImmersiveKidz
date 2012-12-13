#include "Plane.h"
#include "ImmersiveKidz.h"


Plane::Plane(std::string texture, glm::vec2 size, glm::vec3 position, glm::vec3 rotation) {
	_size = size;
	_texture = texture;
	ImmersiveKidz::getInstance()->loadTexture(_texture);
	
	_transform = glm::translate(_transform, position);

	_transform = glm::rotate(_transform, rotation[0], glm::vec3(1,0,0));
	_transform = glm::rotate(_transform, rotation[1], glm::vec3(0,1,0));
	_transform = glm::rotate(_transform, rotation[2], glm::vec3(0,0,1));
	

	_vsize = 4;
	_isize = 6;
	_varray = (Vertex*)malloc(_vsize*sizeof(Vertex));
	_iarray = (int*)malloc(_isize*sizeof(int));

	_varray[0].location[0] = 0;
	_varray[0].location[1] = 0;
	_varray[0].location[2] = 0;
	_varray[1].location[0] = _size[0];
	_varray[1].location[1] = 0;
	_varray[1].location[2] = 0;
	_varray[2].location[0] = _size[0];
	_varray[2].location[1] = 0;
	_varray[2].location[2] = _size[1];
	_varray[3].location[0] = 0;
	_varray[3].location[1] = 0;
	_varray[3].location[2] = _size[1];

	_varray[0].tex[0] = 0;
	_varray[0].tex[1] = 1;
	_varray[1].tex[0] = 1;
	_varray[1].tex[1] = 1;
	_varray[2].tex[0] = 1;
	_varray[2].tex[1] = 0;
	_varray[3].tex[0] = 0;
	_varray[3].tex[1] = 0;

	_iarray[0] = 0;
	_iarray[1] = 1;
	_iarray[2] = 2;
	_iarray[3] = 0;
	_iarray[4] = 2;
	_iarray[5] = 3;
	
}


void Plane::onDraw() {

	glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName(_texture));

	sgct::ShaderManager::Instance()->bindShader( "Simple" );
	
	_drawVBO();


	sgct::ShaderManager::Instance()->unBindShader();
	glBindTexture(GL_TEXTURE_2D,0);
}