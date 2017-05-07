#pragma once

#include <memory>
#include "Object.h"
#include "Definitions.h"

class TiXmlElement;
class DeviceAndLibraryManager;

class ObjectFactory
{
public:
	std::shared_ptr<Object> create(TiXmlElement*, std::shared_ptr<DeviceAndLibraryManager>);
	std::shared_ptr<Object> create(std::vector<std::string>, GAME_OBJECTFACTORY_INITIALIZERS);
};