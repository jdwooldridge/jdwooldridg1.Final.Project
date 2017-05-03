#ifndef PHYSICSASSETLIBRARY_H
#define PHYSICSASSETLIBRARY_H

#include <string>
#include <map>
#include <iostream>
#include "Definitions.h"

class PhysicsAssetLibrary{
public:
	//void Print();
			//Asset Name, Asset Factory
	GAME_OBJECTFACTORY_INITIALIZERS Search(std::string name);
	//bool Initialize(std::string path);
	bool Initialize();
	bool AddAsset(std::string name, GAME_OBJECTFACTORY_INITIALIZERS initializers);

protected:
	std::map<std::string, GAME_OBJECTFACTORY_INITIALIZERS> library;
	

private:
};


#endif