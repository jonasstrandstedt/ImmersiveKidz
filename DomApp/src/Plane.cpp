#include "Plane.h"
#include "ImmersiveKidz.h"


Plane::Plane(std::string texture, glm::vec2 size, glm::vec3 position, glm::vec3 rotation) {
	std::cout << "size " << size[0] << ", " << size[1] << std::endl;
	_size = size;
	_texture = texture;
	
	_transform = glm::translate(_transform, position);

	_transform = glm::rotate(_transform, rotation[0], glm::vec3(1,0,0));
	_transform = glm::rotate(_transform, rotation[1], glm::vec3(0,1,0));
	_transform = glm::rotate(_transform, rotation[2], glm::vec3(0,0,1));
	
	
}

void Plane::onDraw() {

	glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName(_texture));
	
	
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);     
	glVertex3f(0,0,0);
	glTexCoord2f(1,1);     
	glVertex3f(_size[0],0,0);
	glTexCoord2f(1,0);     
	glVertex3f(_size[0],0,_size[1]);
	glTexCoord2f(0,0);     
	glVertex3f(0,0,_size[1]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,0);
}