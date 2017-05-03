#pragma once
#include <iostream>
#include <memory>
#include <map>
#include "ObjectFactory.h"

class GameAssetLibrary
{
public:
	GameAssetLibrary();
	~GameAssetLibrary();
	bool Initialize();
	std::shared_ptr<ObjectFactory> Search(std::string);
	
private:
	std::map<std::string, std::shared_ptr<ObjectFactory>> library;
};