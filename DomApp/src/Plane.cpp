#include "Plane.h"
#include "ImmersiveKidz.h"


Plane::Plane(glm::vec4 bounds, std::string texture, float y) {
	_bounds = bounds;
	ImmersiveKidz::getInstance()->loadTexture(texture);
	_texture = texture;
	_y = y;
	_transform = glm::translate(_transform, glm::vec3(0.0,y,0.0));
}

void Plane::onDraw() {

	glBindTexture(GL_TEXTURE_2D,sgct::TextureManager::Instance()->getTextureByName(_texture));
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);     
	glVertex3f(_bounds[0],_y,_bounds[1]);
	glTexCoord2f(1,1);     
	glVertex3f(_bounds[2],_y,_bounds[1]);
	glTexCoord2f(1,0);     
	glVertex3f(_bounds[2],_y,_bounds[3]);
	glTexCoord2f(0,0);     
	glVertex3f(_bounds[0],_y,_bounds[3]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
}