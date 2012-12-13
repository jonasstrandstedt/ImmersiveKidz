#include "MultObject.h"
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
MultObject::MultObject(DrawableObject *obj, std::vector< std::vector<bool> > *mask, int seed, int count, int type, glm::vec2 altitude){
	_texture = obj->getTexture();
	_type = type;

	_angle_loc = -1;
	_campos_loc = -1;
	_billboard_loc = -1;
	
	sgct::ShaderManager::Instance()->bindShader( "MultObject" );
	_attrib_loc = sgct::ShaderManager::Instance()->getShader( "MultObject").getAttribLocation( "position" );
	_float_attrib_loc = sgct::ShaderManager::Instance()->getShader( "MultObject").getAttribLocation( "rotation" );
	_angle_loc = sgct::ShaderManager::Instance()->getShader( "MultObject").getUniformLocation( "angle_x" );
	_campos_loc = sgct::ShaderManager::Instance()->getShader( "MultObject").getUniformLocation( "camera_position" );
	_billboard_loc = sgct::ShaderManager::Instance()->getShader( "MultObject").getUniformLocation( "billboard" );
	sgct::ShaderManager::Instance()->unBindShader();

	int isize;
	int vsize;
	Vertex *varray;
	int *iarray;
	obj->getArrays(&vsize, &isize, &varray, &iarray);

	// check that vertex data is available before creating the vertex array
	if(isize > 0 && vsize > 0 && varray != NULL && iarray != NULL)
	{
		_isize = isize * count;
		_vsize = vsize *count;
		if (_type == DUAL)
		{
			_isize = isize * count*2;
			_vsize = vsize *count*2;
		} 
		_varray = (Vertex*)malloc(_vsize*sizeof(Vertex));
		_iarray = (int*)malloc(_isize*sizeof(int));

		srand(seed);
		glm::vec4 rect = ImmersiveKidz::getInstance()->getWorldRect();
		for(int c = 0; c < count ; c++){

			float posx = 0;
			float posy = 0;
			float posz = 0;

			int maskCount = 0;
			while ( maskCount < 20 )
			{
				float r1 = (double)(rand())/(RAND_MAX+1.0);
				float r2 = (double)rand()/(RAND_MAX+1.0);
				posx = rect.x + r1 * (rect.z - rect.x);
				posy = glm::compRand1(altitude[0], altitude[1]);
				posz  = rect.y + r2 * (rect.w - rect.y);
				int masky = r2 * mask->size();
				int maskx = r1 * mask[0].size();
			
				if ( (*mask)[masky][maskx] == true ) 
				{
					break;
				}
				maskCount++;
			}

			// if the position randomizer fails 20 times in a row, quit trying
			if ( maskCount >= 20 ) break;

			// if the type is SINGLE or BILLBOARD:
			// only one instance of the model is needed
			if(_type == SINGLE || _type == BILLBOARD) 
			{
				for (int i = 0; i < vsize; ++i)
				{
					int v = c * vsize +i;
					_varray[v].location[0] = varray[i].location[0];
					_varray[v].location[1] = varray[i].location[1];
					_varray[v].location[2] = varray[i].location[2];
					_varray[v].tex[0] = varray[i].tex[0];
					_varray[v].tex[1] = varray[i].tex[1];
					_varray[v].normal[0] = varray[i].normal[0];
					_varray[v].normal[1] = varray[i].normal[1];
					_varray[v].normal[2] = varray[i].normal[2];
					_varray[v].colour[0] = 0;
					_varray[v].colour[1] = 0;
					_varray[v].colour[2] = 0;
					_varray[v].colour[3] = 1;

					_varray[v].attribute[0] = posx;
					_varray[v].attribute[1] = posy;
					_varray[v].attribute[2] = posz;
					_varray[v].float_attribute = 0;
				}

			// if the type is DUAL:
			// dublicating the model and adds a rotation angle around the y axis 
			// so the shader can rotate one of the models
			} else if (_type == DUAL) {
				for (int i = 0; i < vsize; ++i)
				{
					int v = c * vsize +i;
					_varray[v].location[0] = varray[i].location[0];
					_varray[v].location[1] = varray[i].location[1];
					_varray[v].location[2] = varray[i].location[2];
					_varray[v].tex[0] = varray[i].tex[0];
					_varray[v].tex[1] = varray[i].tex[1];
					_varray[v].normal[0] = varray[i].normal[0];
					_varray[v].normal[1] = varray[i].normal[1];
					_varray[v].normal[2] = varray[i].normal[2];
					_varray[v].colour[0] = 0;
					_varray[v].colour[1] = 0;
					_varray[v].colour[2] = 0;
					_varray[v].colour[3] = 1;

					_varray[v].attribute[0] = posx;
					_varray[v].attribute[1] = posy;
					_varray[v].attribute[2] = posz;
					_varray[v].float_attribute = 0;
				}
				for (int i = 0; i < vsize; ++i)
				{
					int v = c * vsize +i + vsize * count;
					_varray[v].location[0] = varray[i].location[0];
					_varray[v].location[1] = varray[i].location[1];
					_varray[v].location[2] = varray[i].location[2];
					_varray[v].tex[0] = varray[i].tex[0];
					_varray[v].tex[1] = varray[i].tex[1];
					_varray[v].normal[0] = varray[i].normal[0];
					_varray[v].normal[1] = varray[i].normal[1];
					_varray[v].normal[2] = varray[i].normal[2];
					_varray[v].colour[0] = 0;
					_varray[v].colour[1] = 0;
					_varray[v].colour[2] = 0;
					_varray[v].colour[3] = 1;

					_varray[v].attribute[0] = posx;
					_varray[v].attribute[1] = posy;
					_varray[v].attribute[2] = posz;
					_varray[v].float_attribute = 90*3.14/180;
				}
			}
			for (int i = 0; i < isize; ++i)
			{
				int v = c * isize +i;
				_iarray[v] = iarray[i] + c*vsize;
			}
			if (_type == DUAL)
			{
				for (int i = 0; i < isize; ++i)
				{
					int v = c * isize +i+isize * count;
					_iarray[v] = iarray[i] + c*vsize + vsize * count;
				}
			
			}
		}
	}
	delete obj;
}

/**
*@brief		Using the MultObject shader and the generated VBO to draw the objects
*/
void MultObject::onDraw() {
	
	glBindTexture( GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByName(_texture));
	
	// bind shader and set the angle
	glm::vec3 campos = ImmersiveKidz::getInstance()->getCamera()->getPosition();
	float angle = ImmersiveKidz::getInstance()->getCamera()->getRotation().x;
	sgct::ShaderManager::Instance()->bindShader( "MultObject" );
	
	glUniform1f( _angle_loc, angle *3.14/180);
	glUniform3f( _campos_loc, campos[0], campos[1], campos[2]);
	
	// tells the shader to billboard (face the camera) the vertices or not
	if(_type == BILLBOARD)
		glUniform1i( _billboard_loc, 1);
	else
		glUniform1i( _billboard_loc, 0);

	// draws the VBO from drawableObject
    _drawVBO();
	
	sgct::ShaderManager::Instance()->unBindShader();
	glBindTexture( GL_TEXTURE_2D, 0);
	
}