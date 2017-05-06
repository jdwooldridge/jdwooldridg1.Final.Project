#pragma once

#ifndef _STRING_
#include <string>
#endif
//class Game;

//Basic Types
typedef unsigned int	Uint32;
typedef float			GAME_FLT;
typedef Uint32			GAME_INT;

typedef struct _GAME_VEC
{
	GAME_FLT x;
	GAME_FLT y;
} GAME_VEC;

//========================================
//Base Game Constants
//========================================
const GAME_INT SCREEN_WIDTH = 800;
const GAME_INT SCREEN_HEIGHT = 600;
const GAME_INT GAME_FPS = 60;
const GAME_INT FRAME_DELAY = 1000 / GAME_FPS;
const GAME_INT LEVEL_WIDTH = 1600;
const GAME_INT LEVEL_HEIGHT = 1200;
const GAME_INT NUM_LEVELS = 3;

enum GAME_OBJECT_SHAPE { GAME_RECTANGLE, GAME_CIRCLE };
enum GAME_BODY_TYPE { GAME_STATIC, GAME_DYNAMIC };

//typedef struct _GAME_PHYSICS
//{
//	//GAME_FLT spinSpeed;
//	GAME_BODY_TYPE bodyType;
//	GAME_OBJECT_SHAPE objectShape;
//	GAME_FLT density;
//	GAME_FLT friction;
//	GAME_FLT restitution;
//	GAME_FLT angularDamping;
//	GAME_FLT linearDamping;
//	//GAME_FLT force;
//	bool physicsOn;
//} GAME_PHYSICS;

//enum OBJECT_TYPE { PLAYER, ENEMY, PLAYER_PROJECTILE, ENEMY_PROJECTILE};

class Game;

typedef struct _GAME_OBJECTFACTORY_INITIALIZERS
{
	std::string objectType;
	GAME_VEC position;
	GAME_FLT angle;
	Game* game; //For grabbing artassetlibrary, view, etc.
	GAME_INT health;
	GAME_BODY_TYPE bodyType;
	GAME_OBJECT_SHAPE objectShape;
	GAME_FLT density;
	GAME_FLT friction;
	GAME_FLT restitution;
	GAME_FLT angularDamping;
	GAME_FLT linearDamping;
	bool physicsOn;
				/*GAME_INT destructTime;//move to new AssetLibraryGame
				std::shared_ptr<ResourceManager> devices;
				std::map<GAME_DIRECTION, bool> gDirection;
				std::shared_ptr<GameObject> joinedObject; //only needed for joint*/
} GAME_OBJECTFACTORY_INITIALIZERS;

//Event Types
enum GAME_EVENT { GAME_NA, GAME_UP, GAME_DOWN, GAME_LEFT, GAME_RIGHT, GAME_QUIT, GAME_SPACE, GAME_PAUSE, GAME_NUM_EVENTS };

//Constants
const GAME_FLT PI = 3.14159f;
const float fPRV = 10.0f;
