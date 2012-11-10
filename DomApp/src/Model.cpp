#include "Model.h"

/**
*@brief	    Create a Model object
*
*@details   Create a Model object
*
*@param		filenme Filename of an object file. Ex: "thingy.obj".
*@param		texturename Filename of the texture file. Ex: "image.png"
*@param		scale If the object needs to be scaled before loaded. Defaults to 1.0
*@param		rotation If the object needs to be rotated before loaded. Defaults to 0.0,0.0,0.0
*@param		base_color Sets the default color of the object if no texture is used. Defaults to white
*/
Model::Model(std::string filename, std::string texturename, float scale, glm::vec3 rotation, glm::vec3 base_color) {
	_texture = 0;

	sgct::TextureManager::Instance()->loadTexure(_texture, texturename, texturename, true);
	
	
	loadObj(filename.c_str(), scale, rotation, base_color);
	
	_transform = glm::rotate(_transform, rotation[0], glm::vec3(1,0,0));
	_transform = glm::rotate(_transform, rotation[1], glm::vec3(0,1,0));
	_transform = glm::rotate(_transform, rotation[2], glm::vec3(0,0,1));
}

/**
*@brief	    Draws the Model
*
*@details   Overloads the DrawableObjects draw function
*
*@return     void
*/
void Model::onDraw() {
	glBindTexture( GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByIndex(_texture) );
	
	glBindBuffer(GL_ARRAY_BUFFER, _vBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iBufferID);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// Resetup our pointers.  This doesn't reinitialise any data, only how we walk through it
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

	glDrawElements(GL_TRIANGLES, _isize, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0); 
}

/**
*@brief	    Initialize the model vertex buffer object
*
*@details   Given Vertex array and index array generates the buffers.
*
*@param		varray Pointer to vertex array
*@param		iarray Pointer to index array
*@param		vertexsize Integer for the vertex array size
*@param		indexsize Integer for the index array size
*
*@return     void
*/
void Model::initVBO(Vertex **varray, int **iarray, int vertexsize, int indexsize) {
	_vBufferID = 0;
	_iBufferID = 0;
	_vsize = vertexsize;
	_isize = indexsize;

	glGenBuffers(1, &_vBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, _vBufferID);
    glBufferData(GL_ARRAY_BUFFER, _vsize*sizeof(Vertex), (*varray), GL_STATIC_DRAW);

	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

    glGenBuffers(1, &_iBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _isize*sizeof(int), (*iarray), GL_STATIC_DRAW);

	if(_vBufferID == 0) {
		sgct::MessageHandler::Instance()->print("Vertex buffer not initialized\n");
	}
	if(_iBufferID == 0) {
		sgct::MessageHandler::Instance()->print("Index buffer not initialized\n");
	}

	// in case of error, print it
    GLuint errorID = glGetError();
    if(errorID != GL_NO_ERROR) {
		sgct::MessageHandler::Instance()->print(" OpenGL error: ");
		sgct::MessageHandler::Instance()->print((const char*)gluErrorString(errorID));
		sgct::MessageHandler::Instance()->print("\nAttempting to proceed anyway. Expect rendering errors or a crash.\n");
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

/**
*@brief	    Loads an object file model
*
*@details   Loads an object from an wavefront object file. 
*
*@param		filenme Filename of an object file. Ex: "thingy.obj".
*@param		scale If the object needs to be scaled before loaded. Defaults to 1.0
*@param		rotation If the object needs to be rotated before loaded. Defaults to 0.0,0.0,0.0
*@param		base_color Sets the default color of the object if no texture is used. Defaults to white
*
*@return     void
*/
void Model::loadObj(const char *filename, float scale, glm::vec3 rotation, glm::vec3 base_color) {
	Vertex *varray;
	int *iarray;
	// temporary 
	int vertexSize = 0;
	int vertexNormalSize = 0;
	int vertexTextureSize = 0;
	int indicesSize = 0;
	
	float f1,f2,f3,f4,f5,f6,f7,f8,f9;
	int i1,i2,i3,i4,i5,i6,i7,i8,i9;
	char line[150];
	float maxtex = 0.0;
	
	FILE *fi;
	// START LINE COUNT
	fi = fopen(filename, "r");
	if (fi==NULL) {
		printf("null object");
	}
	while (fgets(line,150,fi)!=NULL)
	{
		if (sscanf( line, "v %f%f%f", &f1, &f2, &f3)) {
			vertexSize+=3;
		}
		if (sscanf( line, "vn %f%f%f", &f1, &f2, &f3)) {
			vertexNormalSize+=3;
		}
		if (sscanf( line, "vt %f%f%f", &f1, &f2, &f3)) {
			vertexTextureSize+=3;
		}
		if (vertexTextureSize > 0) {
			if (sscanf( line, "f %i/%i/%i %i/%i/%i %i/%i/%i", &i1, &i2, &i3, &i4, &i5, &i6, &i7, &i8, &i9)) {
				indicesSize+=3;
			}
		} else {
			if (sscanf( line, "f %i//%i %i//%i %i//%i", &i1, &i2, &i3, &i4, &i5, &i6)) {
				indicesSize+=3;
			}
		}
	}
	/*	END LINE COUNT */
	
	// allocate memory for all arrays
	_isize = indicesSize;
	_vsize = indicesSize;
	
	// float arrays
	float *tempVertexArray = (float*)malloc(vertexSize*sizeof(float));
	float *tempVertexNormalArray = (float*)malloc(vertexNormalSize*sizeof(float));
	float *tempVertexTextureArray = (float*)malloc(vertexTextureSize*sizeof(float));
	varray = (Vertex*)malloc(_vsize*sizeof(Vertex));
	
	// int arrays
	iarray = (int*)malloc(_isize*sizeof(int));
	int *tempNormalIndicesArray = (int*)malloc(_isize*sizeof(int));
	int *tempTextureIndicesArray = (int*)malloc(_isize*sizeof(int));
	
	// keeping track of the array indexes
	int i = 0;
	int n = 0;
	int m = 0;
	int w = 0;
	
	// Go back to beginning of file
	fseek(fi, 0, SEEK_SET);
	
	while (fgets(line,150,fi)!=NULL)
	{
		if (sscanf( line, "v %f%f%f", &f1, &f2, &f3)) {
			(tempVertexArray)[i] = f1;
			i++;
			(tempVertexArray)[i] = f2;
			i++;
			(tempVertexArray)[i] = f3;
			i++;
		}
		if (sscanf( line, "vn %f%f%f", &f1, &f2, &f3)) {
			(tempVertexNormalArray)[n] = f1;
			n++;
			(tempVertexNormalArray)[n] = f2;
			n++;
			(tempVertexNormalArray)[n] = f3;
			n++;
		}
		
		if (sscanf( line, "vt %f%f%f", &f1, &f2, &f3)) {
			(tempVertexTextureArray)[w] = f1;
			maxtex = ((tempVertexTextureArray)[w] > maxtex) ? (tempVertexTextureArray)[w] : maxtex;
			w++;
			(tempVertexTextureArray)[w] = f2;
			maxtex = ((tempVertexTextureArray)[w] > maxtex) ? (tempVertexTextureArray)[w] : maxtex;
			w++;
			(tempVertexTextureArray)[w] = f3;
			maxtex = ((tempVertexTextureArray)[w] > maxtex) ? (tempVertexTextureArray)[w] : maxtex;
			w++;
		}
		
		if (vertexTextureSize > 0) {
			if (sscanf( line, "f %i/%i/%i %i/%i/%i %i/%i/%i", &i1, &i2, &i3, &i4, &i5, &i6, &i7, &i8, &i9)) {
				(iarray)[m] = i1-1;
				(tempTextureIndicesArray)[m] = i2-1;
				(tempNormalIndicesArray)[m] = i3-1;
				m++;
				(iarray)[m] = i4-1;
				(tempTextureIndicesArray)[m] = i5-1;
				(tempNormalIndicesArray)[m] = i6-1;
				m++;
				(iarray)[m] = i7-1;
				(tempTextureIndicesArray)[m] = i8-1;
				(tempNormalIndicesArray)[m] = i9-1;
				m++;
			}
		} else {
			if (sscanf( line, "f %i//%i %i//%i %i//%i", &i1, &i2, &i3, &i4, &i5, &i6)) {
				(iarray)[m] = i1-1;
				(tempNormalIndicesArray)[m] = i2-1;
				m++;
				(iarray)[m] = i3-1;
				(tempNormalIndicesArray)[m] = i4-1;
				m++;
				(iarray)[m] = i5-1;
				(tempNormalIndicesArray)[m] = i6-1;
				m++;
			}	
		}
	}
	fclose(fi);
	// end of file read
	
	// creating the vertex array
	i=0;n=0;m=0;
	int normalIndex = 0;
	int textureIndex = 0;
	int vertexIndex = 0;
	while (m<_vsize) {
		normalIndex = tempNormalIndicesArray[m]*3;
		textureIndex = tempTextureIndicesArray[m]*3;
		vertexIndex = (iarray)[m]*3;
		(iarray)[m] = m;
		
		int q = 0;
		while (q < 3) {
			varray[m].location[q] = tempVertexArray[vertexIndex+q]*scale;
			(varray)[m].normal[q] = tempVertexNormalArray[normalIndex+q];
			q++;
		}	
		(varray)[m].colour[0] = base_color[0];
		(varray)[m].colour[1] = base_color[1];
		(varray)[m].colour[2] = base_color[2];
		(varray)[m].colour[3] = 1.0;

		if (vertexTextureSize > 0) {
			(varray)[m].tex[0] = tempVertexTextureArray[textureIndex];
			(varray)[m].tex[1] = tempVertexTextureArray[textureIndex+1];
		} else {
			(varray)[m].tex[0] = 1.0;
			(varray)[m].tex[1] = 1.0;
		}
		m++;
	}
	
	// free up memory
	free(tempVertexArray);
	free(tempVertexNormalArray);
	free(tempNormalIndicesArray);
	free(tempVertexTextureArray);
	free(tempTextureIndicesArray);
	
	initVBO(&varray, &iarray, _vsize, _isize);
}
