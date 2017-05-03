#include <string>
#include "ContactListener.h"
#include "Object.h"
#include "ComponentList.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    //Grab the two Physics Bodies involved in the Contact
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	//Cast them to object pointers
	Object* objectA = static_cast<Object*>(bodyA -> GetUserData());
	Object* objectB = static_cast<Object*>(bodyB -> GetUserData());

	//find their types
	std::string objectAType = objectA -> getObjectType();
	std::string objectBType = objectB -> getObjectType();
	
	
		
		
	//If an arrow comes into contact with an octorok or leever, set their isDead properties to true so that they will be destroyed on the next object update iteration.
	if(objectAType == "Bullet" && (objectBType == "Boss" || objectBType == "Box" || objectBType == "Blue Octorok" || objectBType == "Blue Leever"))
	{
		objectA->setIsDead(true);
		objectB->setIsDead(true);
	}

}
