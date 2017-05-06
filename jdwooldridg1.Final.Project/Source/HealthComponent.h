#pragma once

#include "ComponentList.h"
#include "Definitions.h"
//class ResourceManager;

class PhysicsDevice;

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

	bool KillObject();

	std::unique_ptr<Object> Update();
	bool Finish();
protected:
	GAME_INT health;
	PhysicsDevice* pDevice;
	//std::shared_ptr<ResourceManager> devices;
};