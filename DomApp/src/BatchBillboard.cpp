#include "BatchBillboard.h"
#include "ImmersiveKidz.h"

/**
*@brief	    Constructor to the billboard class
*
*@details	Create a batch of billboards/quads with one texture. The positions for each billboard is randomly generated between pos_min and pos_max.
*
*@param		texturename		Unique name of a texture. Ex: "texture.png".
*@param		pos_min  		the minimum position on which billboards will be rendered 	   
*@param		pos_max  	    the maximum position on which billboards will be rendered
*@param		seed  			A seed to be used for c++ random function so that it will generate the same random positions each run
*@param		count  			The number of billboards to create
*@param		proportionsIn	The proportions of the billboard size according to the world unit length. 
*@param		billboard		if true each quad will be rotated at each frame so that it faces the camera. If false all billboards will be rendered as two perpendicular quads  
*/
BatchBillboard::BatchBillboard(std::string texturename, std::vector<std::vector<bool>> *mask, int seed, int count, glm::vec2 proportionsIn, bool billboard){
	ImmersiveKidz::getInstance()->loadTexture(texturename);
	_texture = texturename;
	_billboard = billboard;

	int pos_loc = -1;
	sgct::ShaderManager::Instance()->bindShader( "BatchBillboard_turn" );
	pos_loc = sgct::ShaderManager::Instance()->getShader( "BatchBillboard_turn").getAttribLocation( "billboard_position" );
	sgct::ShaderManager::Instance()->unBindShader();

	_angle_loc = sgct::ShaderManager::Instance()->getShader( "BatchBillboard_turn").getUniformLocation( "angle_x" );
	_campos_loc = sgct::ShaderManager::Instance()->getShader( "BatchBillboard_turn").getUniformLocation( "camera_position" );


	srand(seed);
    _listid = glGenLists(1);
    glNewList(_listid, GL_COMPILE);
	glBegin(GL_QUADS);
	for(int c = 1; c <= count ; c++){
		
		glm::vec4 rect = ImmersiveKidz::getInstance()->getWorldRect();

		float posx = 0;
		float posy = 0;
		float posz = 0;

		int maskCount = 0;
		while ( maskCount < 20 )
		{
			float r1 = (double)rand()/(RAND_MAX+1.0);
			float r2 = (double)rand()/(RAND_MAX+1.0);
			posx = rect.x + r1 * (rect.z - rect.x);
			posy = 0;
			posz  = rect.y + r2 * (rect.w - rect.y);
			int masky = r2 * mask->size();
			int maskx = r1 * mask[0].size();
			
			if ( (*mask)[masky][maskx] == true ) 
			{
				(*mask)[masky][maskx] = false;
				break;
			}

			maskCount++;
		}
		if ( maskCount >= 20 ) break;

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

			glVertexAttrib3f( pos_loc, posx, posy, posz);
			
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
*@brief		Using the OpenGL draw list compiled in the constructor to render all billboards
*
*@details	Using the OpenGL draw list compiled in the constructor to render all billboards
*/
void BatchBillboard::onDraw() {
	glBindTexture( GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByName(_texture));
	
	// bind shader and set the angle
	if(_billboard) {
		glm::vec3 campos = ImmersiveKidz::getInstance()->getCamera()->getPosition();
		float angle = ImmersiveKidz::getInstance()->getCamera()->getRotation().x;
		sgct::ShaderManager::Instance()->bindShader( "BatchBillboard_turn" );
		
		glUniform1f( _angle_loc, angle *3.14/180);
		glUniform3f( _campos_loc, campos[0], campos[1], campos[2]);
	} else {
		sgct::ShaderManager::Instance()->bindShader( "BatchBillboard_still" );
	}
	
    glCallList(_listid);
	
	sgct::ShaderManager::Instance()->unBindShader();
	glBindTexture( GL_TEXTURE_2D, 0);
}