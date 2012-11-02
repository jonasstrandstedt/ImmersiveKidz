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
	myTextureIndex = 0;
	sgct::TextureManager::Instance()->setAnisotropicFilterSize(4.0f);
	sgct::TextureManager::Instance()->loadTexure(myTextureIndex, texturename, texturename, true);
	
	loadObj(filename.c_str(), scale, rotation, base_color);
}
Model::Model(const char *filename, const char *texturename, float scale, glm::vec3 rotation, glm::vec3 base_color) {
	myTextureIndex = 0;
	sgct::TextureManager::Instance()->setAnisotropicFilterSize(4.0f);
	sgct::TextureManager::Instance()->loadTexure(myTextureIndex, texturename, texturename, true);
	
	loadObj(filename, scale, rotation, base_color);
}

/**
*@brief	    Draws the Model
*
*@details   Overloads the DrawableObjects draw function
*
*@return     void
*/
void Model::draw() {
	glBindTexture( GL_TEXTURE_2D, sgct::TextureManager::Instance()->getTextureByIndex(myTextureIndex) );
	
	glBindBuffer(GL_ARRAY_BUFFER, vBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferID);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// Resetup our pointers.  This doesn't reinitialise any data, only how we walk through it
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

	glDrawElements(GL_TRIANGLES, isize, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

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
	vBufferID = 0;
	iBufferID = 0;
	vsize = vertexsize;
	isize = indexsize;

	glGenBuffers(1, &vBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vBufferID);
    glBufferData(GL_ARRAY_BUFFER, vsize*sizeof(Vertex), (*varray), GL_STATIC_DRAW);

	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

    glGenBuffers(1, &iBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize*sizeof(int), (*iarray), GL_STATIC_DRAW);

	if(vBufferID == 0) {
		sgct::MessageHandler::Instance()->print("Vertex buffer not initialized\n");
	}
	if(iBufferID == 0) {
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
	//printf("Loading object\n");
	// debugInit = 1 shows all debug information in the console output
	short debugInit = 0;
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
	float maxtex;
	
	FILE *fi;
	/*	START LINE COUNT */
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
	isize = indicesSize;
	vsize = indicesSize;
	
	// float arrays
	float *tempVertexArray = (float*)malloc(vertexSize*sizeof(float));
	float *tempVertexNormalArray = (float*)malloc(vertexNormalSize*sizeof(float));
	float *tempVertexTextureArray = (float*)malloc(vertexTextureSize*sizeof(float));
	varray = (Vertex*)malloc(vsize*sizeof(Vertex));
	
	// int arrays
	iarray = (int*)malloc(isize*sizeof(int));
	int *tempNormalIndicesArray = (int*)malloc(isize*sizeof(int));
	int *tempTextureIndicesArray = (int*)malloc(isize*sizeof(int));
	//printf("... Array initiated!\n");
	
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
			if (debugInit == 1)
				printf("vertex: %f  %f  %f \n",(tempVertexArray)[i-3],(tempVertexArray)[i-2],(tempVertexArray)[i-1]);
		}
		if (sscanf( line, "vn %f%f%f", &f1, &f2, &f3)) {
			(tempVertexNormalArray)[n] = f1;
			n++;
			(tempVertexNormalArray)[n] = f2;
			n++;
			(tempVertexNormalArray)[n] = f3;
			n++;
			if (debugInit == 1)
				printf("vertexNormal: %f  %f  %f \n",(tempVertexNormalArray)[n-3],(tempVertexNormalArray)[n-2],(tempVertexNormalArray)[n-1]);
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
			if (debugInit == 1)
				printf("vertexTexture: %f  %f  %f \n",(tempVertexTextureArray)[w-3],(tempVertexTextureArray)[w-2],(tempVertexTextureArray)[w-1]);
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
				if (debugInit == 1)
					printf("vi: %i  %i  %i   vn: %i  %i  %i \n",(iarray)[m-3],(iarray)[m-2],(iarray)[m-1],(tempNormalIndicesArray)[m-3],(tempNormalIndicesArray)[m-2],(tempNormalIndicesArray)[m-1]);
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
				if (debugInit == 1)
					printf("vi: %i  %i  %i   vn: %i  %i  %i \n",(iarray)[m-3],(iarray)[m-2],(iarray)[m-1],(tempNormalIndicesArray)[m-3],(tempNormalIndicesArray)[m-2],(tempNormalIndicesArray)[m-1]);
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
	printf("Arraysize: %i, maxtex = %f",vsize, maxtex);
	while (m<vsize) {
		if (debugInit == 1)
			printf("\nAdding vertex %i, startNormal:%i startVertex:%i\n",m,tempNormalIndicesArray[m]*3,(iarray)[m]*3);
		
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
		/*
		Vec3 temp;
		Vec3 normal_temp;
		temp = Vec3((varray)[m].location[0],(varray)[m].location[1],(varray)[m].location[2]);
		normal_temp = Vec3((varray)[m].normal[0],(varray)[m].normal[1],(varray)[m].normal[2]);
		
		// rotare around x
		(varray)[m].location[0] = temp.get_x();
		(varray)[m].location[1] = cos(rotation.get_x())*temp.get_y() - sin(rotation.get_x())*temp.get_z();
		(varray)[m].location[2] = sin(rotation.get_x())*temp.get_y() + cos(rotation.get_x())*temp.get_z();
		
		temp = Vec3((varray)[m].location[0],(varray)[m].location[1],(varray)[m].location[2]);
		normal_temp = Vec3((varray)[m].normal[0],(varray)[m].normal[1],(varray)[m].normal[2]);
		// rotare around y
		(varray)[m].location[0]= cos(rotation.get_y())*temp.get_x() + sin(rotation.get_y())*temp.get_y();
		(varray)[m].location[1] = temp.get_y();
		(varray)[m].location[2] = -sin(rotation.get_y())*temp.get_x() + cos(rotation.get_y())*temp.get_z();
		
		temp = Vec3((varray)[m].location[0],(varray)[m].location[1],(varray)[m].location[2]);
		// rotare around z
		(varray)[m].location[0] = cos(rotation.get_z())*temp.get_x() + sin(rotation.get_z())*temp.get_y();
		(varray)[m].location[1] = -sin(rotation.get_z())*temp.get_x() + cos(rotation.get_z())*temp.get_y();
		(varray)[m].location[2] = temp.get_z();
		
		// rotare around x
		normal_temp = Vec3((varray)[m].normal[0],(varray)[m].normal[1],(varray)[m].normal[2]);
		(varray)[m].normal[0] = normal_temp.get_x();
		(varray)[m].normal[1] = cos(rotation.get_x())*normal_temp.get_z() - sin(rotation.get_x())*normal_temp.get_y();
		(varray)[m].normal[2] = sin(rotation.get_x())*normal_temp.get_z() + cos(rotation.get_x())*normal_temp.get_y();
		// rotare around y
		normal_temp = Vec3((varray)[m].normal[0],(varray)[m].normal[1],(varray)[m].normal[2]);
		(varray)[m].normal[0] = cos(rotation.get_y())*normal_temp.get_x() + sin(rotation.get_y())*normal_temp.get_y();
		(varray)[m].normal[1] = normal_temp.get_y();
		(varray)[m].normal[2] = -sin(rotation.get_y())*normal_temp.get_x() + cos(rotation.get_y())*normal_temp.get_y();
		// rotare around z
		normal_temp = Vec3((varray)[m].normal[0],(varray)[m].normal[1],(varray)[m].normal[2]);
		(varray)[m].normal[0] = cos(rotation.get_z())*normal_temp.get_x() + sin(rotation.get_z())*normal_temp.get_y();
		(varray)[m].normal[1] = -sin(rotation.get_z())*normal_temp.get_x() + cos(rotation.get_z())*normal_temp.get_y();
		(varray)[m].normal[2] = normal_temp.get_z();
		*/
		if (debugInit == 1) {
			printf("normal added: %f %f %f \n",(varray)[m].normal[0],(varray)[m].normal[1],(varray)[m].normal[2]);
			printf("vertex pos added: %f %f %f \n",(varray)[m].location[0],(varray)[m].location[1],(varray)[m].location[2]);
		}
		
		if (vertexTextureSize > 0) {
			(varray)[m].tex[0] = tempVertexTextureArray[textureIndex];
			(varray)[m].tex[1] = tempVertexTextureArray[textureIndex+1];
			//(*varray)[m].tex[0] = tempVertexNormalArray[textureIndex];
			//(*varray)[m].tex[1] = tempVertexNormalArray[textureIndex+1];
		} else {
			(varray)[m].tex[0] = 1.0;
			(varray)[m].tex[1] = 1.0;
		}
		m++;
	}
	//printf("... Array initiated!\n");
	// free up memory
	free(tempVertexArray);
	free(tempVertexNormalArray);
	free(tempNormalIndicesArray);
	free(tempVertexTextureArray);
	free(tempTextureIndicesArray);
	
	
	initVBO(&varray, &iarray, vsize, isize);
}
