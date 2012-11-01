#include "ImmersiveKidz.h"

/**
*@brief	    ImmersiveKidz constructor
*
*@details   ImmersiveKidz constructor
*/
ImmersiveKidz::ImmersiveKidz() {
	sgct::MessageHandler::Instance()->print("Initializing ImmersiveKidz engine\n");

	// initialize all variables
	objects = new std::vector<DrawableObject*>();
	isMaster = false;
	curr_time = 0.0;
};


/**
*@brief	    ImmersiveKidz destructor
*
*@details   ImmersiveKidz destructor
*/
ImmersiveKidz::~ImmersiveKidz() {
	sgct::MessageHandler::Instance()->print("Destroying ImmersiveKidz engine\n");
	delete objects;
};

/**
*@brief	    Adds a DrawableObject to the vector
*
*@details   Adds a DrawableObject to the vector
*
*@param		o is a subclass of DrawableObject (because DrawableObject is abstract)
*
*@return     void
*/
void ImmersiveKidz::addDrawableObject(DrawableObject *o) {
	objects->push_back(o);
}

/**
*@brief	    Function called from sgct presync
*
*@details   Function called from sgct presync
*
*@return     void
*/
void ImmersiveKidz::preSyncFunc() {
	//set the time only on the master
	if( isMaster )
	{
		//get the time in seconds
		curr_time = sgct::Engine::getTime();
	}
}

/**
*@brief	    Function called from sgct draw
*
*@details   Function called from sgct draw
*
*@return     void
*/
void ImmersiveKidz::draw() {
	float speed = 50.0f;
	glRotatef(static_cast<float>( curr_time ) * speed, 0.0f, 1.0f, 0.0f);
	
	for (int i = 0; i < objects->size(); ++i)
	{
		objects->at(i)->draw();
	}
	
	/*
	
	float speed = 50.0f;
	glRotatef(static_cast<float>( curr_time ) * speed, 0.0f, 1.0f, 0.0f);

	//render a single triangle
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); //Red
		glVertex3f(-0.5f, -0.5f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f); //Green
		glVertex3f(0.0f, 0.5f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f); //Blue
		glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();
	*/
}

/**
*@brief	    Function called from sgct encode
*
*@details   Function called from sgct encode
*
*@return     void
*/
void ImmersiveKidz::encode() {
	sgct::SharedData::Instance()->writeDouble( curr_time );
	sgct::SharedData::Instance()->writeDouble( dt );
}

/**
*@brief	    Function called from sgct decode
*
*@details   Function called from sgct decode
*
*@return     void
*/
void ImmersiveKidz::decode(){
	curr_time = sgct::SharedData::Instance()->readDouble();
	dt = sgct::SharedData::Instance()->readDouble();
}

int ImmersiveKidz::loadScene() {
	tinyxml2::XMLDocument doc;
	
#ifdef __WIN32__
	doc.LoadFile("../World1/scene.xml");
#else
	doc.LoadFile("World1/scene.xml");
#endif

	tinyxml2::XMLElement* scene = doc.FirstChildElement( "scene" );
	if(scene) {
		tinyxml2::XMLElement* illustrations = scene->FirstChildElement( "illustrations" );
		tinyxml2::XMLNode* item = illustrations->FirstChildElement( "item" );
		for ( item;item; item=item->NextSiblingElement( "item" ) ) {
			std::string name_artist = item->FirstChildElement( "name_artist" )->GetText();
			std::string name_drawing = item->FirstChildElement( "name_drawing" )->GetText();
			std::string texture = item->FirstChildElement( "texture" )->GetText();
			double posx = item->FirstChildElement( "pos" )->DoubleAttribute( "x" );
			double posy = item->FirstChildElement( "pos" )->DoubleAttribute( "y" );
			double posz = item->FirstChildElement( "pos" )->DoubleAttribute( "z" );
			double sizex = item->FirstChildElement( "size" )->DoubleAttribute( "x" );
			double sizey = item->FirstChildElement( "size" )->DoubleAttribute( "y" );
			
			/*
			std::cout << name_artist << std::endl;
			std::cout << name_drawing << std::endl;
			std::cout << texture << std::endl;
			std::cout << posx << " " << posy << " " << posz << std::endl;
			std::cout << sizex << " " << sizey <<  std::endl;
			*/
		}
	}
	else {
		return doc.ErrorID();
	}
}