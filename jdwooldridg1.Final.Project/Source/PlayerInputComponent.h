#pragma once

#include <map>

#include "ComponentList.h"

class DeviceAndLibraryManager;

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent(std::shared_ptr<Object> owner)
        : Component(owner)
    { };
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::shared_ptr<Object> Update();
	bool Finish();
private:
	GAME_INT reloadTime;
	std::shared_ptr<DeviceAndLibraryManager> devicesAndLibraries;
	std::map<GAME_EVENT, bool> controlPressed;
};