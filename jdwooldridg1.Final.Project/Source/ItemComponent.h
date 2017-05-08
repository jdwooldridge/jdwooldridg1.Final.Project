#pragma once

#include <vector>
#include "Component.h"
#include "Definitions.h"

class Object;

class ItemComponent : public Component
{
public:
	ItemComponent(std::shared_ptr<Object>);
	~ItemComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);

	//bool GetPickedUp(){return pickedUp;}
	
	//void SetPickedUp(bool pickedUp){this -> pickedUp = pickedUp;}

	void pickUp() { _owner->setIsDead(true); }

	std::shared_ptr<Object> Update();
	bool Finish();
protected:
	bool pickedUp;
};