#include "Component.h"

#include "Object.h"

Object::Object()
{
	initialized = false;
}

Object::~Object()
{
	//gDevice = nullptr;
	//iDevice = nullptr;
	//texture = nullptr;
}
//Initialize an object.
bool Object::Initialize(GAME_OBJECTFACTORY_INITIALIZERS presets/*TiXmlElement* root, GraphicsDevice* gDevice, InputDevice* iDevice, std::shared_ptr<Texture> texture*/)
{
	objectType = presets.objectType;
	isDead = false;
	//Initialize every component. Fail if there is one that fails to initialize.
	for (auto comp : components)
	{
		initialized = comp->Initialize(presets);
		if (!initialized)
			return false;
	}
	return true;
}

std::unique_ptr<Object> Object::Update(GAME_FLT)
{
	std::unique_ptr<Object> objectReturn;
	for (auto comp : components)
		comp->Update();
	return objectReturn;
}

void Object::addComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);
}
