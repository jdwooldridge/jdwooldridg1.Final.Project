#include "ShootComponent.h"

bool ShootComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	return true;
}

std::unique_ptr<Object> ShootComponent::Update()
{
	return nullptr;
}

bool ShootComponent::Finish()
{
	return true;
}
