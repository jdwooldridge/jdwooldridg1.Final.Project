#include <random>
#include "DeviceAndLibraryManager.h"
#include "SlideBehaviorComponent.h"

bool SlideBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	aDelta = Component::distance(engine);
	posNeg = 1;
	devicesAndLibraries = initializers.devicesAndLibraries;
	return true;
}


std::shared_ptr<Object>  SlideBehaviorComponent::Update()
{
	//Zero out the velocities.
	devicesAndLibraries->getPhysicsDevice()->SetAngularVelocity(_owner.get(), 0.0f);
	devicesAndLibraries->getPhysicsDevice()->SetLinearVelocity(_owner.get(), { 0 , 0 });
	GAME_VEC updatedPosition = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get());
	//Update the horizontal position
	//_owner->GetComponent<BodyComponent>()->setPositionX(_owner->GetComponent<BodyComponent>()->getPosition().x + 1 * posNeg);
	updatedPosition.x = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).x + 1 * posNeg;
	devicesAndLibraries->getPhysicsDevice()->SetTransform(_owner.get(), updatedPosition, devicesAndLibraries->getPhysicsDevice()->GetAngle(_owner.get()));
	// if we have gone far enough. . . switch directions
	if (updatedPosition.x > _owner->GetComponent<BodyComponent>()->getStartPosition().x + aDelta || updatedPosition.x < _owner->GetComponent<BodyComponent>()->getStartPosition().x - aDelta)
	{
		posNeg *= -1;
	}
	return nullptr;
}

bool SlideBehaviorComponent::Finish()
{
	return true;
}