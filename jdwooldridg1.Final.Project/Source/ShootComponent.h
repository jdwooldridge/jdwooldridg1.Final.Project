#pragma once

#include "ComponentList.h"

class DeviceAndLibraryManager;

class ShootComponent : public Component
{
public:
	ShootComponent(std::shared_ptr<Object> owner)
		: Component(owner)
	{ };
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::shared_ptr<Object> Update();
	bool Finish();
private:
	std::shared_ptr<DeviceAndLibraryManager> devicesAndLibraries;
	GAME_INT firingRate;
};
