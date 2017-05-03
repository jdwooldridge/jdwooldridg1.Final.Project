#include <random>
#include "Game.h"
#include "SlideBehaviorComponent.h"

bool SlideBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	aDelta = Component::distance(engine);
	posNeg = 1;
	pDevice = initializers.game->getPhysicsDevice();
	return true;
}


std::unique_ptr<Object>  SlideBehaviorComponent::Update()
{
	//Zero out the velocities.
	pDevice->SetAngularVelocity(_owner.get(), 0.0f);
	pDevice->SetLinearVelocity(_owner.get(), { 0 , 0 });
	GAME_VEC updatedPosition = pDevice->GetPosition(_owner.get());
	//Update the horizontal position
	//_owner->GetComponent<BodyComponent>()->setPositionX(_owner->GetComponent<BodyComponent>()->getPosition().x + 1 * posNeg);
	updatedPosition.x = pDevice->GetPosition(_owner.get()).x + 1 * posNeg;
	pDevice->SetTransform(_owner.get(), updatedPosition, pDevice->GetAngle(_owner.get()));
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