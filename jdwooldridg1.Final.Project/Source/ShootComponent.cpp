#include "DeviceAndLibraryManager.h"
#include "ShootComponent.h"

bool ShootComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	firingRate = 0;
	devicesAndLibraries = initializers.devicesAndLibraries;
	return true;
}
//Fire a projectile.
std::shared_ptr<Object> ShootComponent::Update()
{
	std::shared_ptr<Object> returnObj;
	if (firingRate == 0)
	{
		std::vector<std::string> componentList;
		GAME_OBJECTFACTORY_INITIALIZERS initializers;

		initializers.position.x = _owner->GetComponent<BodyComponent>()->getPosition().x - 20;
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
		initializers.damageAmt = 10;
		initializers.health = 20;
		initializers.goLeft = true;
		initializers.objectType = "Cereal";
		componentList.push_back("Sprite");
		componentList.push_back("Body");
		componentList.push_back("Timed");
		componentList.push_back("Damage");
		//devicesAndLibraries->getSoundDevice()->PlaySound("EnemyFire", 0);
		firingRate = 50;

		returnObj = devicesAndLibraries->getObjectFactory()->create(componentList, initializers);
	}
	if (firingRate > 0)
		--firingRate;

	return returnObj;
}

bool ShootComponent::Finish()
{
	return true;
}
