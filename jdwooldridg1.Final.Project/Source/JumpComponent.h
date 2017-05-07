#pragma once

#include "ComponentList.h"

class JumpComponent : public Component
{
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::shared_ptr<Object> Update();
	bool Finish();
};