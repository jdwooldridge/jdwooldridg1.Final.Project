#include "Component.h"

std::random_device                      Component::rdev;
std::default_random_engine              Component::engine(Component::rdev());
std::uniform_real_distribution<double>  Component::turnRate(-1.5, 1.5);
std::uniform_int_distribution<int>      Component::distance(10, 100);

Component::Component(std::shared_ptr<Object> owner) : _owner(owner) {}

Component::~Component() {}