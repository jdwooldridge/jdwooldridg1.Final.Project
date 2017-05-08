
#include "DeviceAndLibraryManager.h"
#include "TimedLifeComponent.h";

//Initialize timed life component.
bool TimedLifeComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	health = initializers.health;
	devicesAndLibraries = initializers.devicesAndLibraries;
	goLeft = initializers.goLeft;
	return true;
}

bool TimedLifeComponent::Finish()
{
	return true;
}

//Decrement health and move the owner forward. If health is less than or equal to zero, set is dead to true.
std::shared_ptr<Object> TimedLifeComponent::Update()
{
	//Move away from the originating object.
	GAME_VEC newPosition;
	/*GAME_FLT radians = (2.0f * PI) * pDevice->GetAngle(_owner.get()) / 360.0f - PI / 2.0f;
	GAME_FLT dx = cos(radians);
	GAME_FLT dy = sin(radians);*/

	//Make the object move left if goLeft is true.
	if(goLeft)
		newPosition.x = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).x - 10.0f;
	else //Otherwise move to the right.
		newPosition.x = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).x + 10.0f;
	newPosition.y = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).y;
	devicesAndLibraries->getPhysicsDevice()->SetTransform(_owner.get(), newPosition, 0);
	//newPosition.y = pDevice->GetPosition(_owner.get()).y + 2.0f*dy;
	
	//Decrement health and set isDead to true if health is less than or equal to zero.
	--health;
	if (health <= 0)
		_owner->setIsDead(true);
	return nullptr;
}