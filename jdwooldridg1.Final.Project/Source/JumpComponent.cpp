#include "JumpComponent.h"

bool JumpComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	return true;
}

std::unique_ptr<Object> JumpComponent::Update()
{
	return nullptr;
}

bool JumpComponent::Finish()
{
	return true;
}