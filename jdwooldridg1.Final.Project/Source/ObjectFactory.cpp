#include <iostream>

#include "tinyxml\tinyxml.h"

#include "ComponentList.h"
#include "ObjectFactory.h"

std::shared_ptr<Object> ObjectFactory::create(TiXmlElement* lvlRoot, Game* game)
{
	std::shared_ptr<Object> newObject = std::make_shared<Object>();
	GAME_OBJECTFACTORY_INITIALIZERS presets;

	presets.objectType = lvlRoot->Attribute("name");

	TiXmlElement* comp = lvlRoot->FirstChildElement("Component");
	while (comp)
	{

		if (strcmp(comp->Attribute("name"), "Body") == 0)
		{
			comp->QueryFloatAttribute("x", &presets.position.x);
			comp->QueryFloatAttribute("y", &presets.position.y);
			comp->QueryFloatAttribute("angle", &presets.angle);
			if (strcmp(comp->Attribute("type"), "GAME_DYNAMIC") == 0)
				presets.bodyType = GAME_DYNAMIC;
			else if (strcmp(comp->Attribute("type"), "GAME_STATIC") == 0)
				presets.bodyType = GAME_STATIC;
			if (strcmp(comp->Attribute("shape"), "GAME_RECTANGLE") == 0)
				presets.objectShape = GAME_RECTANGLE;
			else if (strcmp(comp->Attribute("shape"), "GAME_CIRCLE") == 0)
				presets.objectShape = GAME_CIRCLE;
			comp->QueryFloatAttribute("density", &presets.density);
			comp->QueryFloatAttribute("friction", &presets.friction);
			comp->QueryFloatAttribute("restitution", &presets.restitution);
			comp->QueryFloatAttribute("angularDamping", &presets.angularDamping);
			comp->QueryFloatAttribute("linearDamping", &presets.linearDamping);
			comp->QueryBoolAttribute("physicsOn", &presets.physicsOn);
			newObject->addComponent(std::make_shared<BodyComponent>(newObject));
		}
		else if (strcmp(comp->Attribute("name"), "Slide") == 0)
		{
			//comp->QueryBoolAttribute("vertical", &presets.vertical);
			newObject->addComponent(std::make_shared<SlideBehaviorComponent>(newObject));
		}
		else if (strcmp(comp->Attribute("name"), "Input") == 0)
			newObject->addComponent(std::make_shared<PlayerInputComponent>(newObject));
		
		else if (strcmp(comp->Attribute("name"), "Sprite") == 0)
			newObject->addComponent(std::make_shared<SpriteComponent>(newObject));

		comp = comp->NextSiblingElement("Component");
	}
	presets.game = game;
	if (newObject->Initialize(presets))
		return newObject;
	else
	{
		std::cout << "Object did not initialize!" << std::endl;
		return NULL;
	}
	//return std::unique_ptr<Object>();
}
