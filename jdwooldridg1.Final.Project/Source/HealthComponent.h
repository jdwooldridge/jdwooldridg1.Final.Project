#pragma once

#include "ComponentList.h"
#include "Definitions.h"
//class ResourceManager;

class DeviceAndLibraryManager;

class HealthComponent : public Component
{
public:
	HealthComponent(std::shared_ptr<Object> owner)
		: Component(owner)
	{ };
	//~HealthComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS presets);

	GAME_INT GetHealth() { return health; }

	void SetHealth(GAME_INT health) { this->health = health; }

	GAME_INT getImmunity() { return immunity; }

	void setImmunity(GAME_INT immunity) { this->immunity = immunity; }

	bool KillObject();

	std::shared_ptr<Object> Update();
	bool Finish();
protected:
	GAME_INT health;
	GAME_INT immunity;
	std::shared_ptr<DeviceAndLibraryManager> deviceAndLibraries;
	//std::shared_ptr<ResourceManager> devices;
};