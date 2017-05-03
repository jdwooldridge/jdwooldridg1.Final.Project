#ifndef PHYSICSDEVICE_H
#define PHYSICSDEVICE_H

#include "Definitions.h"
#include "Box2D.h"
#include "Texture.h"
#include "PhysicsAssetLibrary.h"
#include "Object.h"

class Object;

class PhysicsDevice{
public:
	PhysicsDevice(GAME_FLT gravityX, GAME_FLT gravityY);
	//~PhysicsDevice();
	bool Initialize();
	bool Update(float dt);
	bool createFixture(Object* object, GAME_OBJECTFACTORY_INITIALIZERS initializers);

	bool SetTransform(Object* object, GAME_VEC position, GAME_FLT angle);
	bool SetLinearVelocity(Object* object, GAME_VEC linearVelociy);
	bool SetAngularVelocity(Object* object, GAME_FLT angularVelocity);
	bool SetTorque(Object* object, GAME_FLT torque);
	bool SetLinearImpulse(Object* object, GAME_VEC forceVec, GAME_VEC forceCenter);
	bool SetStatic(Object* object);
	bool SetStopPhysics(Object* object);
	bool SetAngle(Object* object, GAME_FLT angle);
	bool ApplyForce(Object* object, GAME_VEC force);

	GAME_FLT GetAngularVelocity(Object* object);
	GAME_VEC GetPosition(Object* object);
	GAME_FLT GetAngle(Object* object);
	GAME_VEC GetVelocity(Object* object);
	GAME_VEC GetLinearVelocity(Object* object);
	b2World* getWorld(){ return world; }
	
	bool CreatRevolvingJoint(Object* object1, Object* object2, GAME_VEC anchor1, GAME_VEC anchor2);

	
	b2Body* FindBody(Object* Object);
	b2Vec2 GV2PV(GAME_VEC gameVec);
	GAME_VEC PV2GV(b2Vec2 physicsVec);
	bool RemoveObject(Object* object);
	bool DestroyJoint(Object* object);
		
	b2World* world;
	
	inline float PW2RW(GAME_FLT x){return x*fPRV;}
	inline float RW2PW(GAME_FLT x){return x/fPRV;}
	inline float RW2PW(GAME_INT x){return (float)x/fPRV;}
	inline float RW2PWAngle(GAME_FLT x){return((float)x*(2.0f*3.14159f)/360.0f);} //degrees to radians
	inline float PW2RWAngle(GAME_FLT x){return((float)x*360.0f/(2.0f*3.14159f));} //radians to degrees
private:
	bool DestroyJoint(b2Body* body);
	const b2Vec2 gravity;
	GAME_VEC AlignCenters(Object* object);
	GAME_VEC UndoAlignCenters(Object*, GAME_VEC);

};
#endif