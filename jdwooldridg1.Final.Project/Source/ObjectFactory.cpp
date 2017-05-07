#include <iostream>

#include "tinyxml\tinyxml.h"

#include "DeviceAndLibraryManager.h"
#include "ComponentList.h"
#include "ObjectFactory.h"

std::shared_ptr<Object> ObjectFactory::create(TiXmlElement* lvlRoot, std::shared_ptr<DeviceAndLibraryManager> devicesAndLibraries)
{
	std::shared_ptr<Object> newObject = std::make_shared<Object>();
	GAME_OBJECTFACTORY_INITIALIZERS presets;

	presets.devicesAndLibraries = devicesAndLibraries;
	presets.objectType = lvlRoot->Attribute("name");

	TiXmlElement* comp = lvlRoot->FirstChildElement("Component");
	std::vector<std::string> componentList;

	while (comp)
	{
		std::string componentName = comp->Attribute("name");
		componentList.push_back(componentName);

		if (componentName ==  "Body")
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
		}

		else if (componentName == "Health" || componentName == "Timed")
		{
			comp->QueryUnsignedAttribute("amount", &presets.health);
		}

		comp = comp->NextSiblingElement("Component");
	}
	
	return std::move(create(componentList, presets));
}

std::shared_ptr<Object> ObjectFactory::create(std::vector<std::string> componentList, GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	//Create object.
	std::shared_ptr<Object> newObject = std::make_shared<Object>();

	for (auto component : componentList)
	{
		if (component == "Body")
			newObject->addComponent(std::make_shared<BodyComponent>(newObject));
		else if (component == "Sprite")
			newObject->addComponent(std::make_shared<SpriteComponent>(newObject));
		else if (component == "Slide")
			newObject->addComponent(std::make_shared<SlideBehaviorComponent>(newObject));
		else if (component == "Input")
			newObject->addComponent(std::make_shared<PlayerInputComponent>(newObject));
		else if (component == "Health")
			newObject->addComponent(std::make_shared<HealthComponent>(newObject));
		else if (component == "Timed")
			newObject->addComponent(std::make_shared<TimedLifeComponent>(newObject));
	}
	if (!newObject->Initialize(initializers))
	{
		std::cout << "Failed to initialize object!" << std::endl;
		return nullptr;
	}
	else
		return newObject;
}
