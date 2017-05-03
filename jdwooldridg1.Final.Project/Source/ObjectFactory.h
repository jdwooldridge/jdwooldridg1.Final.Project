#pragma once

#include "Object.h"
#include "Definitions.h"

class TiXmlElement;

class ObjectFactory
{
public:
	std::shared_ptr<Object> create(TiXmlElement*, Game*);
};