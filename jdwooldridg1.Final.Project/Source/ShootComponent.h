#pragma once

#include "ComponentList.h"

class ShootComponent : public Component
{
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::shared_ptr<Object> Update();
	bool Finish();
};
