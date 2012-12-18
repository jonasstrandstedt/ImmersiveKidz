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
				if(textureElement->GetText() != NULL) texture = textureElement->GetText();
				else	continue;

				std::string animation = "none";
				float animoffset = 0.0;
				float animparam = 0.0;
				tinyxml2::XMLElement* aniElement = plane->FirstChildElement( "animation" );
				if(aniElement) 
				{
					if(aniElement->Attribute( "name" ) != NULL ) animation = aniElement->Attribute( "name" );
					if(aniElement->FloatAttribute( "offset" ) > 0.0) animoffset = aniElement->FloatAttribute( "offset" );
					if(aniElement->FloatAttribute( "param" ) > 0.0) animparam = aniElement->FloatAttribute( "param" );
				}			
				
				float width = 1.0;
				float height = 1.0;
				tinyxml2::XMLElement* sizeElement = plane->FirstChildElement( "size" );
				if(sizeElement)
				{
					if(sizeElement->FloatAttribute( "width" ) > 0.0000001) width = sizeElement->FloatAttribute( "width" );
					if(sizeElement->FloatAttribute( "height" ) > 0.0000001) height = sizeElement->FloatAttribute( "height" );

				}

				float x = 0.0;
				float y = 0.0;
				float z = 0.0;
				tinyxml2::XMLElement* positionElement = plane->FirstChildElement( "pos" );
				if(positionElement)
				{
					if(positionElement->Attribute( "x" ) != NULL) x = positionElement->FloatAttribute( "x" );
					if(positionElement->Attribute( "y" ) != NULL) y = positionElement->FloatAttribute( "y" );
					if(positionElement->Attribute( "z" ) != NULL) z = positionElement->FloatAttribute( "z" );

				}

				float rotx = 0.0;
				float roty = 0.0;
				float rotz = 0.0;
				tinyxml2::XMLElement* rotElement = plane->FirstChildElement( "rot" );
				if(rotElement)
				{
					if(rotElement->Attribute( "x" ) != NULL) rotx = rotElement->FloatAttribute( "x" );
					if(rotElement->Attribute( "y" ) != NULL) roty = rotElement->FloatAttribute( "y" );
					if(rotElement->Attribute( "z" ) != NULL) rotz = rotElement->FloatAttribute( "z" );
				}

				ImmersiveKidz::getInstance()->loadTexture(scenePath + texture);
				Plane *obj = new Plane(scenePath + texture, glm::vec2(width, height), glm::vec3(x,y,z), glm::vec3(rotx,roty,rotz));
				tinyxml2::XMLElement* multElement = plane->FirstChildElement( "mult" );
				if(multElement)
					_loadMult(obj,multElement);
				else 
					ImmersiveKidz::getInstance()->addDrawableObject(obj, animation, animoffset, animparam);
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
				if(fileElement->GetText() != NULL) filename = fileElement->GetText();
				else	continue;
			}
			else	continue;

			std::string texture = "";
			tinyxml2::XMLElement* textureElement = model->FirstChildElement( "texture");
			if(textureElement) 
			{
				if(textureElement->GetText() != NULL) texture = textureElement->GetText();
				else	continue;
			}
			else	continue;
	
			std::string animation = "none";
			float animoffset = 0.0;
			float animparam = 0.0;
			tinyxml2::XMLElement* aniElement = model->FirstChildElement( "animation" );
			if(aniElement) 
			{
				if(aniElement->Attribute( "name" ) != NULL) animation = aniElement->Attribute( "name" );
				if(aniElement->FloatAttribute( "offset" ) > 0.0) animoffset = aniElement->FloatAttribute( "offset" );
				if(aniElement->FloatAttribute( "param" ) > 0.0) animparam = aniElement->FloatAttribute( "param" );
			}

			float x = 0;
			float y = 0;
			float z = 0;
			tinyxml2::XMLElement* positionElement = model->FirstChildElement( "pos" );
			if(positionElement)
			{
				if(positionElement->Attribute( "x" ) != NULL) x = positionElement->FloatAttribute( "x" );
				if(positionElement->Attribute( "y" ) != NULL) y = positionElement->FloatAttribute( "y" );
				if(positionElement->Attribute( "z" ) != NULL) z = positionElement->FloatAttribute( "z" );
			}

			float scale = 1.0;
			tinyxml2::XMLElement* scaleElement = model->FirstChildElement( "scale" );
			if(scaleElement)
			{
				if(scaleElement->FloatAttribute( "val" ) > 0.0) scale = scaleElement->FloatAttribute( "val" );
			}

			float rotx = 0.0;
			float roty = 0.0;
			float rotz = 0.0;
			tinyxml2::XMLElement* rotElement = model->FirstChildElement( "rot" );
			if(rotElement)
			{
				if(rotElement->Attribute( "x" ) != NULL) rotx = rotElement->FloatAttribute( "x" );
				if(rotElement->Attribute( "y" ) != NULL) roty = rotElement->FloatAttribute( "y" );
				if(rotElement->Attribute( "z" ) != NULL) rotz = rotElement->FloatAttribute( "z" );
			}

			ImmersiveKidz::getInstance()->loadTexture(scenePath + texture);
			Model *obj = new Model(scenePath + filename, scenePath + texture, glm::vec3(x, y, z), scale, glm::vec3(rotx, roty, rotz));
			tinyxml2::XMLElement* multElement = model->FirstChildElement( "mult" );
			if(multElement)
				_loadMult(obj,multElement);
			else 
				ImmersiveKidz::getInstance()->addDrawableObject(obj, animation, animoffset, animparam);
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
void SceneLoader::_loadBillboards(tinyxml2::XMLElement* parent,DrawableObject *parentObject) 
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
				if(textureElement->GetText() != NULL) texture = textureElement->GetText();
				else	continue;
			}
			else	continue;
	
			std::string animation = "none";
			float animoffset = 0.0;
			float animparam = 0.0;
			tinyxml2::XMLElement* aniElement = billboard->FirstChildElement( "animation" );
			if(aniElement) 
			{
				if(aniElement->Attribute( "name" ) != NULL) animation = aniElement->Attribute( "name" );
				if(aniElement->FloatAttribute( "offset" ) > 0.0) animoffset = aniElement->FloatAttribute( "offset" );
				if(aniElement->FloatAttribute( "param" ) > 0.0) animparam = aniElement->FloatAttribute( "param" );
			}

			float x = 0.0;
			float y = 0.0;
			float z  = 0.0;
			tinyxml2::XMLElement* positionElement = billboard->FirstChildElement( "pos" );
			if(positionElement)
			{
				if(positionElement->Attribute( "x" ) != NULL) x = positionElement->FloatAttribute( "x" );
				if(positionElement->Attribute( "y" ) != NULL) y = positionElement->FloatAttribute( "y" );
				if(positionElement->Attribute( "z" ) != NULL) z = positionElement->FloatAttribute( "z" );
			}

			float sizex = 1.0;
			float sizey = 1.0;
			tinyxml2::XMLElement* sizeElement = billboard->FirstChildElement( "size" );
			if(sizeElement)
			{
				if(sizeElement->FloatAttribute( "width" ) > 0.0) sizex = sizeElement->FloatAttribute( "width" );
				if(sizeElement->FloatAttribute( "height" ) > 0.0) sizey = sizeElement->FloatAttribute( "height" );
			}


			ImmersiveKidz::getInstance()->loadTexture(scenePath + texture);
			Billboard *obj = new Billboard(scenePath+texture, glm::vec3(x , y , z),glm::vec2(sizex , sizey),parentObject);
			tinyxml2::XMLElement* multElement = billboard->FirstChildElement( "mult" );
			if(multElement)
				_loadMult(obj,multElement);
			else 
				ImmersiveKidz::getInstance()->addDrawableObject(obj, animation, animoffset, animparam);

			_loadBillboards(billboard,obj);
			_loadIllustrations(billboard,obj);
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
void SceneLoader::_loadIllustrations(tinyxml2::XMLElement* parent,DrawableObject *parentObject) 
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
				if(textureElement->GetText() != NULL) texture = textureElement->GetText();
				else	continue;
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
			float animoffset = 0.0;
			float animparam = 0.0;
			tinyxml2::XMLElement* aniElement = illustration->FirstChildElement( "animation" );
			if(aniElement) 
			{
				if(aniElement->Attribute( "name" ) != NULL) animation = aniElement->Attribute( "name" );
				if(aniElement->FloatAttribute( "offset" ) > 0.0) animoffset = aniElement->FloatAttribute( "offset" );
				if(aniElement->FloatAttribute( "param" ) > 0.0) animparam = aniElement->FloatAttribute( "param" );
			}

			
			srand(static_cast<unsigned int>(time(NULL)));
			float x = static_cast<float>(20*(rand()/RAND_MAX-0.5));
			float y = 0.0;
			float z  = static_cast<float>(20*(rand()/RAND_MAX-0.5));
			tinyxml2::XMLElement* positionElement = illustration->FirstChildElement( "pos" );
			if(positionElement)
			{
				if(positionElement->Attribute( "x" ) != NULL) x = positionElement->FloatAttribute( "x" );
				if(positionElement->Attribute( "y" ) != NULL) y = positionElement->FloatAttribute( "y" );
				if(positionElement->Attribute( "z" ) != NULL) z = positionElement->FloatAttribute( "z" );
			}

			float sizex = 1.0;
			float sizey = 1.0;
			tinyxml2::XMLElement* sizeElement = illustration->FirstChildElement( "size" );
			if(sizeElement)
			{
				if(sizeElement->FloatAttribute( "width" ) > 0.0) sizex = sizeElement->FloatAttribute( "width" );
				if(sizeElement->FloatAttribute( "height" ) > 0.0) sizey = sizeElement->FloatAttribute( "height" );
			}
			Illustration *obj = new Illustration(scenePath + texture, glm::vec3(x , y , z), glm::vec2(sizex , sizey), name_artist, name_drawing, description,parentObject);
			ImmersiveKidz::getInstance()->addDrawableObject(obj, animation, animoffset, animparam);
			
			_loadBillboards(illustration,obj);
			_loadIllustrations(illustration,obj);
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