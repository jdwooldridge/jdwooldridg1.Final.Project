#pragma once

#ifndef _MEMORY_
#include <memory>
#endif
#ifndef _RANDOM_
#include <random>
#endif

#include "Definitions.h"
#include "Object.h"


class Component
{
public:
	Component(std::shared_ptr<Object> owner);
	~Component();
	virtual bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS) = 0;
	virtual std::unique_ptr<Object> Update() = 0;
	virtual bool Finish() = 0;
protected:
	std::shared_ptr<Object> _owner;
	static std::random_device rdev;
	static std::default_random_engine engine;
	static std::uniform_real_distribution<double> turnRate;
	static std::uniform_int_distribution<int> distance;

};