#pragma once

#include "ComponentList.h"

class Object;

class DamageComponent : public Component
{
public:
	DamageComponent(std::shared_ptr<Object> owner)
		: Component(owner)
	{ };
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::shared_ptr<Object> Update() { return nullptr; }
	bool Finish() { return true; }
	GAME_INT getDamageAmt() { return damageAmt; }
private:
	GAME_INT damageAmt;
};