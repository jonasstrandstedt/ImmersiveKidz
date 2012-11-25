#include "BatchBillboard.h"
#include "ImmersiveKidz.h"

/**
*@brief	    Constructor to the billboard class
*
*@details	Creates a billboard at a position, sets the proportions and assignes a texture to it.
*
*@param		texturename		Unique name of a texture. Ex: "texture.png".
*@param		position	Contains the positions in world coordinates.
*@param		proportionsIn	The proportions of the billboardsize according to the world unit length. 
*/
BatchBillboard::BatchBillboard(std::string texturename, glm::vec3 pos_min, glm::vec3 pos_max, int seed, int count, glm::vec2 proportionsIn, bool billboard){
	ImmersiveKidz::getInstance()->loadTexture(texturename);
	_texture = texturename;
	_billboard = billboard;
	
	int pos_loc = -1;
	sgct::ShaderManager::Instance()->bindShader( "BatchBillboard_turn" );
	pos_loc = sgct::ShaderManager::Instance()->getShader( "BatchBillboard_turn").getAttribLocation( "billboard_position" );
	sgct::ShaderManager::Instance()->unBindShader();

	//std::cout << "Pos loc = " << pos_loc << std::endl;

	srand(seed);
    _listid = glGenLists(1);
    glNewList(_listid, GL_COMPILE);
	glBegin(GL_QUADS);
	for(int c = 1; c <= count ; c++){
		
		float posx = glm::compRand1(pos_min[0],pos_max[0]); 
		float posy = 0;
		float posz  = glm::compRand1(pos_min[2],pos_max[2]);

		if( ! billboard) {
			//Vertex 1 
			glTexCoord2d(0.0,0.0);
			glVertex3f(posx -0.5 * proportionsIn[0] , posy , posz);
			
			//Vertex 2 
			glTexCoord2d(1.0,0.0);
			glVertex3f(posx + 0.5 * proportionsIn[0] , posy , posz);
			
			//Vertex 3 
			glTexCoord2d(1.0,1.0);
			glVertex3f(posx + 0.5 * proportionsIn[0] , posy+proportionsIn[1] , posz);
			
			//Vertex 4 
			glTexCoord2d(0.0,1.0);
			glVertex3f(posx - 0.5 * proportionsIn[0] , posy+proportionsIn[1] , posz);


			//Vertex 1 
			glTexCoord2d(0.0,0.0);
			glVertex3f(posx , posy , posz -0.5 * proportionsIn[0]);
			
			//Vertex 2 
			glTexCoord2d(1.0,0.0);
			glVertex3f(posx , posy , posz + 0.5 * proportionsIn[0]);
			
			//Vertex 3 
			glTexCoord2d(1.0,1.0);
			glVertex3f(posx ,posy+ proportionsIn[1] , posz + 0.5 * proportionsIn[0]);
			
			//Vertex 4 
			glTexCoord2d(0.0,1.0);
			glVertex3f(posx, posy+proportionsIn[1] , posz - 0.5 * proportionsIn[0] );
		} else {

			//float arr[] = {posx, posy, posz};
			//glVertexAttrib3fv( pos_loc, arr);

			glVertexAttrib3f( pos_loc, posx, posy, posz);
			//glColor3f(posx, posy, posz);

			//Vertex 1 
			glTexCoord2d(0.0,0.0);
			glVertex3f(-0.5 * proportionsIn[0] , 0 , 0);
			//Vertex 2 
			glTexCoord2d(1.0,0.0);
			//glColor3f(posx, posy, posz);
			glVertex3f(0 + 0.5 * proportionsIn[0] , 0 , 0);
			//Vertex 3 
			glTexCoord2d(1.0,1.0);
			//glColor3f(posx, posy, posz);
			glVertex3f(0 + 0.5 * proportionsIn[0] , 0+proportionsIn[1] , 0);
			//Vertex 4 
			glTexCoord2d(0.0,1.0);
			//glColor3f(posx, posy, posz);
			glVertex3f(0 - 0.5 * proportionsIn[0] , 0+proportionsIn[1] , 0);

		}
	}
	

	glEnd();
    glEndList();
};

/**
*@brief		Draws the Billboard. 
*
*@details	Draws a texture on a Billboard(Quad perpendicual to the camera position).
*
*@return    void
*/
void BatchBillboard::onDraw() {
	glBindTexture( GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByName(_texture));
	
	// bind shader and set the angle
	if(_billboard) {
		glm::vec3 campos = ImmersiveKidz::getInstance()->getCamera()->getPosition();
		float angle = ImmersiveKidz::getInstance()->getCamera()->getRotation().x;
		sgct::ShaderManager::Instance()->bindShader( "BatchBillboard_turn" );
		int angle_loc = sgct::ShaderManager::Instance()->getShader( "BatchBillboard_turn").getUniformLocation( "angle_x" );
		glUniform1f( angle_loc, angle *3.14/180);
		int campos_loc = sgct::ShaderManager::Instance()->getShader( "BatchBillboard_turn").getUniformLocation( "camera_position" );
		glUniform3f( campos_loc, campos[0], campos[1], campos[2]);
		//std::cout << "pos: (" << campos[0] << "," << campos[1] << "," << campos[2] << ")" << std::endl;
	} else {
		sgct::ShaderManager::Instance()->bindShader( "BatchBillboard_still" );
	}
	
	
    // Draw one obejct from a display list
    glCallList(_listid);
	
	sgct::ShaderManager::Instance()->unBindShader();
	glBindTexture( GL_TEXTURE_2D, 0);
}