#pragma once

#include <random>
#include <memory>

#include "Definitions.h"

class Component;
class GraphicsDevice;
class View;
class Texture;
class InputDevice;

class Object
{
public:
    Object();
    ~Object();
    bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
    std::shared_ptr<Object> Update(GAME_FLT); 
    void addComponent(std::shared_ptr<Component>);
    template<class T>
    std::shared_ptr<T> GetComponent()
    {
        for (auto comp : components)
        {
            std::shared_ptr<T> target;
            if ((target = std::dynamic_pointer_cast<T>(comp)))
            {
                return(target);
            }
        }

        //Return NULL;
        return(std::shared_ptr<T>());
    }
	void setIsDead(bool isDead) { this->isDead = isDead; }
	bool getIsDead() { return isDead; }
	void removeComponents() { components.clear(); };
	std::string getObjectType() { return objectType; }
    //float genRndNum(float, float);

protected:

    bool initialized;
	bool isDead;
    std::vector<std::shared_ptr<Component>> components;
    //static std::random_device rdev;
    //static std::default_random_engine engine;
    //static std::uniform_real_distribution<double> turnRate;
    //static std::uniform_int_distribution<int> distance;
    //GraphicsDevice* gDevice;
    //InputDevice* iDevice;
    //std::shared_ptr<Texture> texture;
    GAME_VEC position;
    GAME_VEC startPosition;
    GAME_FLT angle;
	std::string objectType;
    //bool goBackward;

};