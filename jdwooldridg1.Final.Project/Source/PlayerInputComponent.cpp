#include "InputDevice.h";
#include "Definitions.h"
#include "DeviceAndLibraryManager.h"
#include "PlayerInputComponent.h"

bool PlayerInputComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS presets)
{
	devicesAndLibraries = presets.devicesAndLibraries;
	reloadTime = 0;
	for (int i = 0; i < GAME_NUM_EVENTS; ++i)
	{
		GAME_EVENT event = static_cast<GAME_EVENT>(i);
		controlPressed[event] = true;
	}
	return true;
}

std::shared_ptr<Object> PlayerInputComponent::Update()
{
	std::shared_ptr<Object> returnObj = nullptr;
	GAME_VEC linearVelocity = { 0, 0 };
	GAME_VEC force = { 0, 0 };
	GAME_VEC updatedPosition;
	//Move up.
	if (devicesAndLibraries->getInputDevice()->GetEvent(GAME_UP))
	{
		linearVelocity.y = -2.0f;
		devicesAndLibraries->getPhysicsDevice()->SetLinearVelocity(_owner.get(), linearVelocity);
		force = devicesAndLibraries->getPhysicsDevice()->GetLinearVelocity(_owner.get());
		updatedPosition.x = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).x + force.x;
		updatedPosition.y = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).y + force.y;
		devicesAndLibraries->getPhysicsDevice()->SetTransform(_owner.get(), updatedPosition, devicesAndLibraries->getPhysicsDevice()->GetAngle(_owner.get()));
	}
	//Move down.
	if (devicesAndLibraries->getInputDevice()->GetEvent(GAME_DOWN))
	{
		linearVelocity.y = 2.0f;
		devicesAndLibraries->getPhysicsDevice()->SetLinearVelocity(_owner.get(), linearVelocity);
		force = devicesAndLibraries->getPhysicsDevice()->GetLinearVelocity(_owner.get());
		updatedPosition.x = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).x + force.x;
		updatedPosition.y = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).y + force.y;
		devicesAndLibraries->getPhysicsDevice()->SetTransform(_owner.get(), updatedPosition, devicesAndLibraries->getPhysicsDevice()->GetAngle(_owner.get()));
	}
	//Move to the left.
	if (devicesAndLibraries->getInputDevice()->GetEvent(GAME_LEFT))
	{
		_owner->GetComponent<SpriteComponent>()->setFlip(SDL_FLIP_HORIZONTAL);
		linearVelocity.x = -2.0f;
		devicesAndLibraries->getPhysicsDevice()->SetLinearVelocity(_owner.get(), linearVelocity);
		force = devicesAndLibraries->getPhysicsDevice()->GetLinearVelocity(_owner.get());
		updatedPosition.x = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).x + force.x;
		updatedPosition.y = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).y + force.y;
		devicesAndLibraries->getPhysicsDevice()->SetTransform(_owner.get(), updatedPosition, devicesAndLibraries->getPhysicsDevice()->GetAngle(_owner.get()));
	}
	//Move to the right.
	if (devicesAndLibraries->getInputDevice()->GetEvent(GAME_RIGHT))
	{
		_owner->GetComponent<SpriteComponent>()->setFlip(SDL_FLIP_NONE);
		linearVelocity.x = 2.0f;//(float)cosf((devicesAndLibraries->getPhysicsDevice->GetAngle(_owner.get())*PI / 180) - (PI / 2)) * 2.0f;
		devicesAndLibraries->getPhysicsDevice()->SetLinearVelocity(_owner.get(), linearVelocity);
		force = devicesAndLibraries->getPhysicsDevice()->GetLinearVelocity(_owner.get());
		updatedPosition.x = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).x + force.x;
		updatedPosition.y = devicesAndLibraries->getPhysicsDevice()->GetPosition(_owner.get()).y + force.y;
		devicesAndLibraries->getPhysicsDevice()->SetTransform(_owner.get(), updatedPosition, devicesAndLibraries->getPhysicsDevice()->GetAngle(_owner.get()));
	}
	//Fire a bullet if spacebar is pressed and the reload time is zero.
	if (devicesAndLibraries->getInputDevice()->GetEvent(GAME_SPACE) && reloadTime == 0)
	{
		std::vector<std::string> componentList;
		GAME_OBJECTFACTORY_INITIALIZERS initializers;
		//Make the bullet go right if the bullet is facing right.
		if (_owner->GetComponent<SpriteComponent>()->getFlip() == SDL_FLIP_NONE)
		{
			initializers.position.x = _owner->GetComponent<BodyComponent>()->getPosition().x + 20;
			initializers.goLeft = false;
		}
		//Make the bullet go left if John is facing left.
		else if (_owner->GetComponent<SpriteComponent>()->getFlip() == SDL_FLIP_HORIZONTAL)
		{
			initializers.position.x = _owner->GetComponent<BodyComponent>()->getPosition().x - 20;
			initializers.goLeft = true;
		}
		initializers.position.y = _owner->GetComponent<BodyComponent>()->getPosition().y + _owner->GetComponent<SpriteComponent>()->GetTexture()->getWidth();
		initializers.angle = 0.0f;
		initializers.objectShape = GAME_RECTANGLE;
		initializers.bodyType = GAME_DYNAMIC;
		initializers.friction = 0.8f;
		initializers.angularDamping = 10.0f;
		initializers.density = 0.5f;
		initializers.linearDamping = 0.5f;
		initializers.restitution = 3.0f;
		initializers.physicsOn = true;
		initializers.devicesAndLibraries = devicesAndLibraries;
		initializers.health = 20;
		initializers.damageAmt = 10;
		initializers.objectType = "Bullet";
		componentList.push_back("Sprite");
		componentList.push_back("Body");
		componentList.push_back("Timed");
		componentList.push_back("Damage");
		
		devicesAndLibraries->getSoundDevice()->PlaySound("Fire", 0);
		reloadTime = 25;

		returnObj = devicesAndLibraries->getObjectFactory()->create(componentList, initializers);
	}

	//BORDER SCROLLING

	GAME_INT borderDistance = 250;

	//Scroll right if John comes within a certain distance of the right edge of the screen.
	if (_owner->GetComponent<BodyComponent>()->getPosition().x  - devicesAndLibraries->getView()->getPosition().x > SCREEN_WIDTH - borderDistance)
	{
			devicesAndLibraries->getView()->setPositionX(devicesAndLibraries->getView()->getPosition().x + 1);
			_owner->GetComponent<BodyComponent>()->setPositionX((SCREEN_WIDTH + devicesAndLibraries->getView()->getPosition().x) - borderDistance);
	}

	//Ensure the player cannot backtrack/go to the left out of the view.
	if (_owner->GetComponent<BodyComponent>()->getPosition().x < devicesAndLibraries->getView()->getPosition().x)
		_owner->GetComponent<BodyComponent>()->setPositionX(devicesAndLibraries->getView()->getPosition().x);

	//Ensure that the player cannot go below Y=600.
	if (_owner->GetComponent<BodyComponent>()->getPosition().y < 600)
		_owner->GetComponent<BodyComponent>()->setPositionY(600);

	//Ensure that the player cannot go beyond the bottom of the screen.
	if (_owner->GetComponent<BodyComponent>()->getPosition().y > SCREEN_WIDTH)
		_owner->GetComponent<BodyComponent>()->setPositionY(SCREEN_WIDTH);

	if(reloadTime > 0)
		--reloadTime;

	return returnObj;
}

bool PlayerInputComponent::Finish()
{
	return true;
}