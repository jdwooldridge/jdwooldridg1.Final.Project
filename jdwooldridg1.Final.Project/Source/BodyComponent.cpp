#include "Game.h"
#include "PhysicsDevice.h"
#include "BodyComponent.h"

bool BodyComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	startPosition.x = initializers.position.x;
	startPosition.y = initializers.position.y;
	position.x = initializers.position.x;
	position.y = initializers.position.y;
	angle = initializers.angle;

	devicesAndLibraries = initializers.devicesAndLibraries;

	//Create fixture.
	if (!devicesAndLibraries->getPhysicsDevice()->createFixture(_owner.get(), initializers))
	{
		printf("Error: Failed to create object fixture!");
		return false;
	}

	return true;
}

std::shared_ptr<Object> BodyComponent::Update()
{
	GAME_VEC newPosition = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get());
	position.x = newPosition.x;
	position.y = newPosition.y;
	angle = devicesAndLibraries->getPhysicsDevice()->GetAngle(_owner.get());
	return nullptr;
}

bool BodyComponent::Finish()
{
	if (!devicesAndLibraries->getPhysicsDevice()->RemoveObject(_owner.get()))
	{
		printf("Object could not be removed from the physics world!");
		return false;
	}
	return true;
}

GAME_VEC BodyComponent::getPosition()
{
	return position;
}

GAME_VEC BodyComponent::getStartPosition()
{
	return startPosition;
}

GAME_FLT BodyComponent::getAngle()
{
	return angle;
}

void BodyComponent::setAngle(GAME_FLT angle)
{
	this->angle = angle;
}

void BodyComponent::setPositionX(GAME_FLT x)
{
	this->position.x = x;
}

void BodyComponent::setPositionY(GAME_FLT y)
{
	this->position.y = y;
}

//**************************************
//adjusts the position based on the view.
//GAME_VEC RendererComponent::GetUpdatedPosition(std::shared_ptr<Object> owner)
////**************************************
//{
//	GAME_VEC updatedPosition;
//	//adjust position.
//	updatedPosition.x =
//		position.x
//		+ devices->GetGraphicsDevice()->GetView()->getPosition().x;
//	updatedPosition.y =
//		position.y
//		+ devices->GetGraphicsDevice()->GetView()->getPosition().y;
//
//	return updatedPosition;
//}

