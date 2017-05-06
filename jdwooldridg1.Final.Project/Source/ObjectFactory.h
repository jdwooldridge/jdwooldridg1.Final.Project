#pragma once

#include "Object.h"
#include "Definitions.h"

class TiXmlElement;

class ObjectFactory
{
public:
	ObjectFactory(Game*);
	~ObjectFactory();
	std::shared_ptr<Object> create(TiXmlElement*);
	std::unique_ptr<Object> create(std::vector<std::string>, GAME_OBJECTFACTORY_INITIALIZERS);
private:
	Game* game;
};