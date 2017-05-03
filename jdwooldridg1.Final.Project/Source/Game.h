#ifndef GAME_H
#define _GAME_H
#include "SDL.h"
//#include "Definitions.h"
#include "InputDevice.h"
#include "ArtAssetLibrary.h"
#include "View.h"
#include "GameAssetLibrary.h"
#include "PhysicsAssetLibrary.h"
#include "PhysicsDevice.h"
#include "InputDevice.h"
#include "Object.h"
#include "GraphicsDevice.h"
#include "Timer.h"
#include "tinyxml\tinyxml.h"

#include <iostream>
#include <memory>
#include <vector>

class Game {

public:
	Game();
	~Game();
	bool Initialize();
	void Reset();
	bool LoadLevel(std::string, std::string);
	bool Run();
	bool Update();
	void Draw();
	GraphicsDevice* getGraphicsDevice();
	View* getView();
	ArtAssetLibrary* getArtAssetLibrary();
	InputDevice* getInputDevice();
	PhysicsDevice* getPhysicsDevice() { return pDevice.get(); }
	PhysicsAssetLibrary* getPhysicsAssetLibrary() { return pLibrary.get(); }

private:
	std::unique_ptr<GameAssetLibrary> gLibrary;
	std::unique_ptr<ArtAssetLibrary> aLibrary;
	std::unique_ptr<GraphicsDevice> gDevice;
	std::unique_ptr<PhysicsAssetLibrary> pLibrary;
	std::unique_ptr<InputDevice> iDevice;
	std::unique_ptr<Timer> timer;
	std::unique_ptr<PhysicsDevice> pDevice;
	GAME_FLT gameTime;
	std::unique_ptr<View> view;
	std::vector<std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Object>> newObjects;
	bool paused;
	GAME_INT curLevel;
	GAME_FLT dt;
};

#endif // !GAME_H
