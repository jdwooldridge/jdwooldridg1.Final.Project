#pragma once

#include <map>

#include "ComponentList.h"

class InputDevice;

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent(std::shared_ptr<Object> owner)
        : Component(owner)
    { };
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::unique_ptr<Object> Update();
	bool Finish();
private:
	InputDevice* iDevice;
	View* view;
	PhysicsDevice* pDevice;
	std::map<GAME_EVENT, bool> controlPressed;
};