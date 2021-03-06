#include "HealthComponent.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "DeviceAndLibraryManager.h"

//HealthComponent::~HealthComponent() {}

//**************************************
//gets health and resource manager from passed presets, the object starts out alive.
bool HealthComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS presets)
//**************************************
{
	//devices = presets.devices;
	health = presets.health;
	immunity = 0;
	deviceAndLibraries = presets.devicesAndLibraries;
	return true;
}

//**************************************
//This "KillObject" is for items that leave a sprite that is dead 
//and does not interact with the world
//bool HealthComponent::KillObject(std::string deathSprite)
////**************************************
//{
//	//Stop the physics of the object
//	pDevice->SetStopPhysics(_owner.get());
//
//	//grab the renderer
//	std::shared_ptr<SpriteComponent> compRenderer = _owner -> GetComponent<SpriteComponent>();
//	//change the sprite
//	//compRenderer->SetTexture(devices->GetArtLibrary()->Search(deathSprite));
//	return true;
//}
//**************************************
//For objects that disappear from the game.
bool HealthComponent::KillObject()
//**************************************
{
	//this will cause it to be elimanted on the next game update
	_owner->setIsDead(true);
	return true;
}

//**************************************
//checks for death and deals with it
std::shared_ptr<Object> HealthComponent::Update()
//**************************************
{
	if (immunity > 0)
		--immunity;
	//if dead
	if (health <= 0)
	{
		//kill it
		KillObject();
	}
	return NULL;
}
bool HealthComponent::Finish() { return true; }