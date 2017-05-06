#include "PhysicsDevice.h"
#include "SpriteComponent.h"
#include "ContactListener.h"
#include "Object.h"
#include <cmath>


PhysicsDevice::PhysicsDevice(GAME_FLT gravityX, GAME_FLT gravityY):gravity(RW2PW(gravityX), RW2PW(gravityY))
{

}
/*PhysicsDevice::~PhysicsDevice()
{
	delete world;
}*/
//**************************************
//Creates a new world on initialization
bool PhysicsDevice::Initialize()
//**************************************
{
	world = new b2World(gravity);
	if (world == NULL) return false;
	ContactListener* c1 = new ContactListener();
	world -> SetContactListener(c1);
	const b2Vec2 vBottomLeft = b2Vec2(RW2PW(0.0f), RW2PW(SCREEN_HEIGHT));
	const b2Vec2 vBottomRight = b2Vec2(RW2PW(SCREEN_WIDTH), RW2PW(SCREEN_HEIGHT));
	b2EdgeShape bottom;
	b2BodyDef bd;
	b2Body* edge = world->CreateBody(&bd);
	bottom.Set(vBottomLeft, vBottomRight);
	edge->CreateFixture(&bottom, 0);
	return true;
}

//**************************************
//Steps the physics world
bool PhysicsDevice::Update(float dt)
//**************************************
{	
	world -> Step(dt, 8, 3);
	return true;
}

//**************************************
//Moves body to a set location & angle
bool PhysicsDevice::SetTransform(Object* object, GAME_VEC position, GAME_FLT angle)
//**************************************
{
	//finds which body this object is attached to.
	//based on value set in UserData field of body
	b2Body* body = FindBody(object);

	//Applies' Box2D transform.
	body -> SetTransform
		(
			GV2PV(UndoAlignCenters(object, position)), 
			RW2PWAngle(angle)
		);
	return true;
	
}
bool PhysicsDevice::SetAngle(Object* object, GAME_FLT angle)
{
	b2Body* body = FindBody(object);
	body -> SetTransform(body -> GetPosition(), RW2PWAngle(angle));
	return true;
}

//**************************************
//Sets angular velocity
bool PhysicsDevice::SetAngularVelocity(Object* object, GAME_FLT angularVelocity)
//**************************************
{
	b2Body* body = FindBody(object);
	body -> SetAngularVelocity(RW2PW(angularVelocity));
	return true;
	
}

//**************************************
//Sets linear velocity.
bool PhysicsDevice::SetLinearVelocity(Object* object, GAME_VEC linearVelocity)
//**************************************
{
	b2Body* body = FindBody(object);
	b2Vec2 b2LVelocity;
	b2LVelocity.x = RW2PW(linearVelocity.x);
	b2LVelocity.y = RW2PW(linearVelocity.y);
	body -> SetLinearVelocity(b2LVelocity);
	return true;
}

//**************************************
//Sets a linear impulse based on passed force vector and center vector
bool PhysicsDevice::SetLinearImpulse(Object* object, GAME_VEC forceVec, GAME_VEC forceCenter)
//**************************************
{
	b2Body* body = FindBody(object);
	body -> ApplyLinearImpulse(GV2PV(forceVec), body -> GetWorldPoint(GV2PV(forceCenter)), true);
	return true;
}

//**************************************
//Sets torque on body based on passed values
bool PhysicsDevice::SetTorque(Object* object, GAME_FLT torque)
//**************************************
{
	b2Body* body = FindBody(object);
	body -> ApplyTorque(RW2PW(torque), true);
	return true;
}

bool PhysicsDevice::SetStatic(Object* object)
{
	b2Body* body = FindBody(object);
	body -> SetType(b2_staticBody);
	return true;
}

bool PhysicsDevice::SetStopPhysics(Object* object)
{
	b2Body* body = FindBody(object);
	body -> SetActive(false);
	return true;	
}

bool PhysicsDevice::ApplyForce(Object* object, GAME_VEC force)
{
	b2Body* body = FindBody(object);
	b2Vec2 b2LForce;
	b2LForce.x = RW2PW(force.x);
	b2LForce.y = RW2PW(force.y);
	body->ApplyForce(b2LForce, body->GetPosition(), true);
	return true;
}

//**************************************
//Gets Angular velocity of body
GAME_FLT PhysicsDevice::GetAngularVelocity(Object* object)
//**************************************
{
	b2Body* body = FindBody(object);
	return (PW2RWAngle(body -> GetAngularVelocity()));
}
GAME_VEC PhysicsDevice::GetLinearVelocity(Object* object)
{
	b2Body* body = FindBody(object);
	return(PV2GV(body -> GetLinearVelocity()));
}

//**************************************
//Gets bodies' position
GAME_VEC PhysicsDevice::GetPosition(Object* object)
//**************************************
{
	//b2Body* body = FindBody(object);
	////PV2GV = Physics vector to Game vector (b2vec2 to GAME_VEC)
	//return (PV2GV(body -> GetPosition()));
	return (AlignCenters(object));
}

//**************************************
//Gets bodies' angle
GAME_FLT PhysicsDevice::GetAngle(Object* object)
//**************************************
{
	b2Body* body = FindBody(object);
	return (PW2RWAngle(body -> GetAngle()));
}

GAME_VEC PhysicsDevice::GetVelocity(Object* object)
{
	b2Body* body = FindBody(object);
	return (PV2GV(body -> GetLinearVelocity()));
}

//**************************************
//Creates a body and fixture for a passed in object
//based on passed in values
bool PhysicsDevice::createFixture(Object* object, GAME_OBJECTFACTORY_INITIALIZERS initializers)
//**************************************
{
	std::shared_ptr<SpriteComponent> compRenderer = object -> GetComponent<SpriteComponent>();
	//new body definition
	b2BodyDef* bd = new b2BodyDef;
	//made need one or the other, depending on what was passed.
	b2PolygonShape pShape;
	b2CircleShape cShape;

	//Fixture definition
	b2FixtureDef shapefd;
	
	//Set userData field with passed in object pointer.
	bd -> userData = object;
	

	//set body type
	switch (initializers.bodyType)
	{
	case GAME_STATIC:
		bd -> type = b2_staticBody;
		break;
	case GAME_DYNAMIC:
		bd -> type = b2_dynamicBody;
		break;
	}

	//********Adjust postion because SDL is top left, while box2d is center*************
	Texture* texture = object -> GetComponent<SpriteComponent>() -> GetTexture();
	//subtract off half the width.
	initializers.position.x += (texture -> getWidth()/2);
	//subtract off half the height
	initializers.position.y += (texture -> getHeight()/2);
	//**********************************************************************************

	// set starting position & angle
	bd -> position.Set(RW2PW(initializers.position.x), RW2PW(initializers.position.y));
	bd -> angle = RW2PWAngle(initializers.angle);

	//add the body to the world
	b2Body* body = world -> CreateBody(bd);

	//Set damping values on the body
	body -> SetAngularDamping(initializers.angularDamping);
	body -> SetLinearDamping(initializers.linearDamping);

	//Set fixture's shape
	switch (initializers.objectShape)
	{
	case GAME_RECTANGLE:
		//rectangle's dimensions
		pShape.SetAsBox(RW2PW(compRenderer -> GetTexture() -> getWidth()/2.0f), RW2PW(compRenderer -> GetTexture() -> getHeight()/2.0f));
		shapefd.shape = &pShape;
		break;
	case GAME_CIRCLE:
		//circle radius based on object's width.
		GAME_FLT width = compRenderer -> GetTexture() -> getWidth()/2.0f;
		GAME_FLT height = compRenderer -> GetTexture() -> getHeight()/2.0f;

		if (width > height)	cShape.m_radius = (RW2PW(width));
		else cShape.m_radius = (RW2PW(height));
		shapefd.shape = &cShape;
		break;
	}

	//set fixture values based on passed in values.
	shapefd.density = initializers.density;
	shapefd.friction = initializers.friction;
	shapefd.restitution = initializers.restitution;

	//create the fixture on the body.
	body -> CreateFixture(&shapefd);
	body -> SetActive(initializers.physicsOn);
	
	return true;
	
}

//**************************************
//Removes an object from the World
bool PhysicsDevice::RemoveObject(Object* object)
//**************************************
{
	//Find the body based on the passed object
	b2Body* body = FindBody(object);
	DestroyJoint(body);
	
	//check to see if we have a body.
	if(body == NULL)
	{return false;}
	else
	{
		//delete the body from the world
		world -> DestroyBody(body);
		return true;
	}

}

//**************************************
//Destroys a  physics joint from outside the physics device
bool PhysicsDevice::DestroyJoint(Object* object)
//**************************************
{
	b2Body* body = FindBody(object);
	
	//destroy joints associated with body.
	return DestroyJoint(body);
}

//**************************************
//Destroys the joint from within the device
bool PhysicsDevice::DestroyJoint(b2Body* body)
//**************************************
{
	bool jointFound = false;
	//destroy joints associated with body.
	for(b2JointEdge* j = body -> GetJointList(); j != NULL; j = j -> next)
	{
		world -> DestroyJoint(j -> joint);
		jointFound = true;
	}
	return jointFound;
}

//**************************************
//Uses the user data field in the body and compares the memory location
//to the memory location of the passed object pointer.
//Returns the body that has the same memory location in the user data field
b2Body* PhysicsDevice::FindBody(Object* object)
//**************************************
{
	//loop through the bodies
	for (b2Body* body = world -> GetBodyList(); body; body = body -> GetNext())
	{
		//when we have a match, return it.
		if(object == body -> GetUserData())
		{
			return body;
		}
	}
	//if there was no match, return NULL
	return NULL;
}

//**************************************
//Converts passed GAME_VEC to b2Vec2
b2Vec2 PhysicsDevice::GV2PV(GAME_VEC gameVec)
//**************************************
{
	return b2Vec2(RW2PW(gameVec.x), RW2PW(gameVec.y));
}

//**************************************
//converts passed b2Vec2 to GAME_VEC
GAME_VEC PhysicsDevice::PV2GV(b2Vec2 physicsVec)
//**************************************
{
	GAME_VEC temp;
	temp.x = PW2RW(physicsVec.x);
	temp.y = PW2RW(physicsVec.y);
	return temp;
}

//**************************************
//Creates a revolute joint using the passed objects and anchor points
bool PhysicsDevice::CreatRevolvingJoint(Object* object1, Object* object2, GAME_VEC anchor1, GAME_VEC anchor2)
//**************************************
{
	//find corresponding bodies for objects
	b2Body* bodyA = FindBody(object1);
	b2Body* bodyB = FindBody(object2);
	if(bodyA == NULL || bodyB == NULL)
	{
		return false;
	}

	//joint definition
	b2RevoluteJointDef revoluteJointDef;

	//assign bodies to definition
	revoluteJointDef.bodyA = bodyA;
	revoluteJointDef.bodyB = bodyB;

	//They cannot collide
	revoluteJointDef.collideConnected = false;

	//set anchor points
	revoluteJointDef.localAnchorA.Set(RW2PW(anchor1.x), RW2PW(anchor1.y));
	revoluteJointDef.localAnchorB.Set(RW2PW(anchor2.x), RW2PW(anchor2.y));

	//Joint starts at angle zero
	revoluteJointDef.referenceAngle = 0;

	//Add the joint to the world. If successful will return True, othewise false.
	return (b2RevoluteJoint*)world -> CreateJoint(&revoluteJointDef);
	
}

//**************************************
//adjusts postion based on the fact that SDL is top left and Box2d uses the center of an object for position.
GAME_VEC PhysicsDevice::AlignCenters(Object* object)
//**************************************
{
	b2Body* body = FindBody(object);
	b2Vec2 physPosition = body -> GetPosition();
	GAME_VEC position;
	Texture* texture = object -> GetComponent<SpriteComponent>() -> GetTexture();

		//subtract off half the width.
		position.x = PW2RW(physPosition.x) - (texture -> getWidth()/2);
		//subtract off half the height
		position.y = PW2RW(physPosition.y) - (texture -> getHeight()/2);

	return (position);
}

//Perform the opposite of the preceding function (used for setting the body's position).
GAME_VEC PhysicsDevice::UndoAlignCenters(Object* object, GAME_VEC position)
{
	b2Body* body = FindBody(object);
	Texture* texture = object->GetComponent<SpriteComponent>()->GetTexture();

	//subtract off half the width.
	position.x += texture->getWidth() / 2;
	//subtract off half the height
	position.y += texture->getHeight() / 2;

	return (position);
}
