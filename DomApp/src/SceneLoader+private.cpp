#include "SceneLoader.h"
#include "ImmersiveKidz.h"

/**
*@brief	    Used by loadScene to load the planes
*
*@param		parent	The parent node, should be "scene"
*
*@return     void
*/
void SceneLoader::_loadPlanes(tinyxml2::XMLElement* parent) 
{
	std::string scenePath = ImmersiveKidz::getInstance()->getScenePath();
	scenePath = "scenes/" + scenePath;

	tinyxml2::XMLElement* plane = parent->FirstChildElement( "plane" );
	if(plane)
	{
		for(;plane; plane = plane->NextSiblingElement( "plane" ))
		{
			std::string texture = "";
			tinyxml2::XMLElement* textureElement = plane->FirstChildElement( "texture");
			if(textureElement) 
			{
				texture = textureElement->GetText();

				std::string animation = "none";
				double animseed = 0;
				tinyxml2::XMLElement* aniElement = plane->FirstChildElement( "animation" );
				if(aniElement) 
				{
					animation = (aniElement->Attribute( "name" ) != NULL) ? aniElement->Attribute( "name" ) : "none";
					animseed = aniElement->DoubleAttribute( "seed" );
				}			
				
				double width = 1;
				double height = 1;
				tinyxml2::XMLElement* sizeElement = plane->FirstChildElement( "size" );
				if(sizeElement)
				{
					width = (sizeElement->DoubleAttribute( "width" ) > 0.0000001) ? sizeElement->DoubleAttribute( "width" ) : 1.0;
					height = (sizeElement->DoubleAttribute( "height" ) > 0.0000001) ? sizeElement->DoubleAttribute( "height" ) : 1.0;

				}

				double x = 0;
				double y = 0;
				double z = 0;
				tinyxml2::XMLElement* positionElement = plane->FirstChildElement( "pos" );
				if(positionElement)
				{
					x = positionElement->DoubleAttribute( "x" );
					y = positionElement->DoubleAttribute( "y" );
					z = positionElement->DoubleAttribute( "z" );

				}

				double rotx = 0;
				double roty = 0;
				double rotz = 0;
				tinyxml2::XMLElement* rotElement = plane->FirstChildElement( "rot" );
				if(rotElement)
				{
					rotx = rotElement->DoubleAttribute( "x" );
					roty = rotElement->DoubleAttribute( "y" );
					rotz = rotElement->DoubleAttribute( "z" );
				}

				ImmersiveKidz::getInstance()->loadTexture(scenePath + texture);
				Plane *obj = new Plane(scenePath + texture, glm::vec2(width, height), glm::vec3(x,y,z), glm::vec3(rotx,roty,rotz));
				tinyxml2::XMLElement* multElement = plane->FirstChildElement( "mult" );
				if(multElement)
					_loadMult(obj,multElement);
				else 
					ImmersiveKidz::getInstance()->addDrawableObject(obj, animation, animseed);
			}
		}
	}
}

/**
*@brief	    Used by loadScene to load the models
*
*@param		parent	The parent node, should be "scene"
*
*@return     void
*/
void SceneLoader::_loadModels(tinyxml2::XMLElement* parent) 
{
	std::string scenePath = ImmersiveKidz::getInstance()->getScenePath();
	scenePath = "scenes/" + scenePath;

	tinyxml2::XMLElement* model = parent->FirstChildElement( "model" );
	if(model)
	{
		for(;model; model = model->NextSiblingElement( "model" ))
		{
			std::string filename = "";
			tinyxml2::XMLElement* fileElement = model->FirstChildElement( "filename" );
			if(fileElement) 
			{
				filename = fileElement->GetText();
			}
			else	continue;

			std::string texture = "";
			tinyxml2::XMLElement* textureElement = model->FirstChildElement( "texture");
			if(textureElement) 
			{
				texture = textureElement->GetText();
			}
			else	continue;
	
			std::string animation = "none";
			double animseed = 0;
			tinyxml2::XMLElement* aniElement = model->FirstChildElement( "animation" );
			if(aniElement) 
			{
				animation = (aniElement->Attribute( "name" ) != NULL) ? aniElement->Attribute( "name" ) : "none";
				animseed = aniElement->DoubleAttribute( "seed" );
			}

			srand(time(NULL));
			double posx = 20*((double)rand()/RAND_MAX-0.5);
			double posy = 0;
			double posz  = 20*((double)rand()/RAND_MAX-0.5);
			tinyxml2::XMLElement* posElement = model->FirstChildElement( "pos" );
			if(posElement)
			{
				posx = posElement->DoubleAttribute( "x" );
				posy = posElement->DoubleAttribute( "y" );
				posz = posElement->DoubleAttribute( "z" );
			}

			double scale = 1;
			tinyxml2::XMLElement* scaleElement = model->FirstChildElement( "scale" );
			if(scaleElement)
			{
				scale = scaleElement->DoubleAttribute( "val" );
			}

			double rotx = 0;
			double roty = 0;
			double rotz = 0;
			tinyxml2::XMLElement* rotElement = model->FirstChildElement( "rot" );
			if(rotElement)
			{
				rotx = rotElement->DoubleAttribute( "x" );
				roty = rotElement->DoubleAttribute( "y" );
				rotz = rotElement->DoubleAttribute( "z" );
			}

			ImmersiveKidz::getInstance()->loadTexture(scenePath + texture);
			Model *obj = new Model(scenePath + filename, scenePath + texture, glm::vec3(posx, posy, posz), scale, glm::vec3(rotx, roty, rotz));
			tinyxml2::XMLElement* multElement = model->FirstChildElement( "mult" );
			if(multElement)
				_loadMult(obj,multElement);
			else 
				ImmersiveKidz::getInstance()->addDrawableObject(obj, animation, animseed);
		}
	}
}

/**
*@brief	    Used by loadScene to load the billboards
*
*@param		parent	The parent node, should be "scene"
*
*@return     void
*/
void SceneLoader::_loadBillboards(tinyxml2::XMLElement* parent) 
{
	std::string scenePath = ImmersiveKidz::getInstance()->getScenePath();
	scenePath = "scenes/" + scenePath;

	tinyxml2::XMLElement* billboard = parent->FirstChildElement( "billboard" );
	if(billboard)
	{
		for(;billboard; billboard = billboard->NextSiblingElement( "billboard" ))
		{
			std::string texture = "";
			tinyxml2::XMLElement* textureElement = billboard->FirstChildElement( "texture");
			if(textureElement)
			{
				texture = textureElement->GetText();
			}
			else	continue;
	
			std::string animation = "none";
			double animseed = 0;
			tinyxml2::XMLElement* aniElement = billboard->FirstChildElement( "animation" );
			if(aniElement) 
			{
				animation = (aniElement->Attribute( "name" ) != NULL) ? aniElement->Attribute( "name" ) : "none";
				animseed = aniElement->DoubleAttribute( "seed" );
			}

			srand(time(NULL));
			double posx = 20*((double)rand()/RAND_MAX-0.5);
			double posy = 0;
			double posz  = 20*((double)rand()/RAND_MAX-0.5);
			tinyxml2::XMLElement* posElement = billboard->FirstChildElement( "pos" );
			if(posElement)
			{
				posx = posElement->DoubleAttribute( "x" );
				posy = posElement->DoubleAttribute( "y" );
				posz = posElement->DoubleAttribute( "z" );
			}

			double sizex = 1;
			double sizey = 1;
			tinyxml2::XMLElement* rotElement = billboard->FirstChildElement( "size" );
			if(rotElement)
			{
				sizex = rotElement->DoubleAttribute( "x" );
				sizey = rotElement->DoubleAttribute( "z" );
			}


			ImmersiveKidz::getInstance()->loadTexture(scenePath + texture);
			Billboard *obj = new Billboard(scenePath+texture, glm::vec3(posx , posy , posz),glm::vec2(sizex , sizey));
			tinyxml2::XMLElement* multElement = billboard->FirstChildElement( "mult" );
			if(multElement)
				_loadMult(obj,multElement);
			else 
				ImmersiveKidz::getInstance()->addDrawableObject(obj, animation, animseed);
		}
	}
}

/**
*@brief	    Used by loadScene to load the illustrations
*
*@param		parent	The parent node, should be "scene"
*
*@return     void
*/
void SceneLoader::_loadIllustrations(tinyxml2::XMLElement* parent) 
{
	std::string scenePath = ImmersiveKidz::getInstance()->getScenePath();
	scenePath = "scenes/" + scenePath;

	tinyxml2::XMLElement* illustration = parent->FirstChildElement( "illustration" );
	if(illustration)
	{
		for(;illustration; illustration = illustration->NextSiblingElement( "illustration" ))
		{
			std::string texture = "";
			tinyxml2::XMLElement* textureElement = illustration->FirstChildElement( "texture");
			if(textureElement) 
			{
				texture = textureElement->GetText();
			}
			else	continue;

			std::string name_artist = "Unnamed artist";
			tinyxml2::XMLElement* artistElement = illustration->FirstChildElement( "name_artist" );
			if(artistElement) 
			{
				name_artist = artistElement->GetText();
			}

			std::string name_drawing = "Unnamed drawing";
			tinyxml2::XMLElement* drawingeElement = illustration->FirstChildElement( "name_drawing" );
			if(drawingeElement) 
			{
				name_drawing = drawingeElement->GetText();
			}

			std::string description = "Unnamed description";
			tinyxml2::XMLElement* descElement = illustration->FirstChildElement( "description" );
			if(descElement)
			{
				description = descElement->GetText();
			}					
	
			std::string animation = "none";
			double animseed = 0;
			tinyxml2::XMLElement* aniElement = illustration->FirstChildElement( "animation" );
			if(aniElement) 
			{
				animation = (aniElement->Attribute( "name" ) != NULL) ? aniElement->Attribute( "name" ) : "none";
				animseed = aniElement->DoubleAttribute( "seed" );
			}

			
			srand(time(NULL));
			double posx = 20*((double)rand()/RAND_MAX-0.5);
			double posy = 0;
			double posz  = 20*((double)rand()/RAND_MAX-0.5);
			tinyxml2::XMLElement* posElement = illustration->FirstChildElement( "pos" );
			if(posElement)
			{
				posx = posElement->DoubleAttribute( "x" );
				posy = posElement->DoubleAttribute( "y" );
				posz = posElement->DoubleAttribute( "z" );
			}

			double sizex = 1;
			double sizey = 1;
			tinyxml2::XMLElement* rotElement = illustration->FirstChildElement( "size" );
			if(rotElement)
			{
				sizex = rotElement->DoubleAttribute( "x" );
				sizey = rotElement->DoubleAttribute( "z" );
			}
		
			ImmersiveKidz::getInstance()->addDrawableObject(new Illustration(scenePath + texture, glm::vec3(posx , posy , posz), glm::vec2(sizex , sizey), name_artist, name_drawing, description), animation, animseed);
		}
	}
}

/**
*@brief	    Used by the _load* functions to multiply the object
*
*@param		obj		The DrawableObject that is going to be multiplied
*@param		parent	The parent node, should be objects mult element
*
*@return     void
*/
void SceneLoader::_loadMult(DrawableObject *obj, tinyxml2::XMLElement* multElement) {

	int count = multElement->IntAttribute( "count" );
	int seed = multElement->IntAttribute( "seed" );

	tinyxml2::XMLElement* maskElement =  multElement->Parent()->FirstChildElement( "mask" );
	std::string mask = "default";
	if(maskElement) 
	{
		mask = maskElement->Attribute( "name" );
		if ( _mask.count(mask) == 0 ) mask = "default";
	}
	bool bool_billboard = false;
	int type = SINGLE;
	const char* bb = multElement->Attribute( "type" );
	if(bb) 
	{
		std::string bbstring = bb;
		if(bbstring == "dual") type = DUAL;
		if(bbstring == "billboard") type = BILLBOARD;
	}

	glm::vec2 altitude = glm::vec2();
	tinyxml2::XMLElement* altitudeElement = multElement->Parent()->FirstChildElement( "altitude" );
	if (altitudeElement)
	{
		altitude[0] = altitudeElement->FloatAttribute( "min" );
		altitude[1] = altitudeElement->FloatAttribute( "max" );
	}

	// creates the multobject and adds it to the ImmersiveKidz engine, the DrawableObject is freed from multObjects constructor
	ImmersiveKidz::getInstance()->addDrawableObject(
		new MultObject(
			obj,&_mask[mask], seed, count, type, altitude
		)
	);
}