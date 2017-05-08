#include <string>
#include "DeviceAndLibraryManager.h"
#include "ContactListener.h"
#include "Object.h"
#include "ComponentList.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	//Grab the two Physics Bodies involved in the Contact
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	//Cast them to object pointers
	Object* objectA = static_cast<Object*>(bodyA->GetUserData());
	Object* objectB = static_cast<Object*>(bodyB->GetUserData());

	//find their types
	std::string objectAType = objectA->getObjectType();
	std::string objectBType = objectB->getObjectType();

	std::shared_ptr<DeviceAndLibraryManager> devicesAndLibraries = objectA->GetComponent<BodyComponent>()->GetDevices();


	//Decrease the health of an enemy should a bullet come into contact with it.
	if (objectAType == "Bullet" && (objectBType == "Boss" || objectBType == "Box" || objectBType == "Bowl" || objectBType == "Spoon"))
	{
		objectB->GetComponent<HealthComponent>()->SetHealth(objectA->GetComponent<HealthComponent>()->GetHealth() - objectA->GetComponent<DamageComponent>()->getDamageAmt());
		objectA->setIsDead(true);
		printf("Bullet hit enemy.\n");
		devicesAndLibraries->getSoundDevice()->PlaySound("EnemyHit", 0);
	}
	else if (objectBType == "Bullet" && (objectAType == "Boss" || objectAType == "Box" || objectAType == "Bowl" || objectAType == "Spoon"))
	{
		objectA->GetComponent<HealthComponent>()->SetHealth(objectA->GetComponent<HealthComponent>()->GetHealth() - objectB->GetComponent<DamageComponent>()->getDamageAmt());
		objectB->setIsDead(true);
		printf("Bullet hit enemy.\n");
		devicesAndLibraries->getSoundDevice()->PlaySound("EnemyHit", 0);
	}

	//Decrease John's health if he comes into contact with an enemy.
	else if ((objectAType == "Boss" || objectAType == "Box" || objectAType == "Bowl" || objectAType == "Spoon") && objectBType == "John")
	{
		if (objectB->GetComponent<HealthComponent>()->getImmunity() == 0)
		{
			objectB->GetComponent<HealthComponent>()->SetHealth(objectB->GetComponent<HealthComponent>()->GetHealth() - objectA->GetComponent<DamageComponent>()->getDamageAmt());
			objectB->GetComponent<HealthComponent>()->setImmunity(60);
			devicesAndLibraries->getSoundDevice()->PlaySound("Hit", 0);
			printf("Enemy hit John.\n");
		}
	}
	else if ((objectBType == "Boss" || objectBType == "Box" || objectBType == "Bowl" || objectBType == "Spoon") && objectAType == "John")
	{
		if (objectA->GetComponent<HealthComponent>()->getImmunity() == 0)
		{
			objectA->GetComponent<HealthComponent>()->SetHealth(objectA->GetComponent<HealthComponent>()->GetHealth() - objectB->GetComponent<DamageComponent>()->getDamageAmt());
			objectA->GetComponent<HealthComponent>()->setImmunity(60);
			devicesAndLibraries->getSoundDevice()->PlaySound("Hit", 0);
			printf("Enemy hit John.\n");
		}
	}
	
	//Pick up an item if John comes into contact with one.
	else if (objectAType == "John")
	{
		if (objectB->GetComponent<ItemComponent>())
			PickUpItem(objectA, objectB, devicesAndLibraries.get());
	}
	else if (objectBType == "John")
	{
		if (objectA->GetComponent<ItemComponent>())
			PickUpItem(objectB, objectA, devicesAndLibraries.get());
	}
}

void ContactListener::PickUpItem(Object* player, Object* item, DeviceAndLibraryManager* devicesAndLibraries)
{
	//Increase the score if a coin is being picked up.
	if (item->getObjectType() == "Coin")
	{
		devicesAndLibraries->setScore(devicesAndLibraries->getScore() + 10);
		devicesAndLibraries->getSoundDevice()->PlaySound("GetCoin", 0);

	}
	//Increase John's health if he picks up chips.
	else if (item->getObjectType() == "Chips")
	{
		player->GetComponent<HealthComponent>()->SetHealth(player->GetComponent<HealthComponent>()->GetHealth() + 10);
		devicesAndLibraries->getSoundDevice()->PlaySound("GetChips", 0);
	}
	//Increase lives if John picks up pizza.
	else if (item->getObjectType() == "Pizza")
	{
		devicesAndLibraries->setLives(devicesAndLibraries->getLives() + 1);
		devicesAndLibraries->getSoundDevice()->PlaySound("GetPizza", 0);
	}

	item->setIsDead(true);
}