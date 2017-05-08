#include "ItemComponent.h"

ItemComponent::ItemComponent(std::shared_ptr<Object> owner):Component(owner){}

ItemComponent::~ItemComponent(){}

bool ItemComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	pickedUp = false;
	return true;
}

std::shared_ptr<Object> ItemComponent::Update(){return NULL;}
bool ItemComponent::Finish() { return true; }