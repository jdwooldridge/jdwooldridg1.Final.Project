#include "GameAssetLibrary.h"
//#include "BlueLeeverFactory.h"
//#include "BlueOctorokFactory.h"
//#include "RedLeeverFactory.h"
//#include "RedOctorokFactory.h"

GameAssetLibrary::GameAssetLibrary()
{

}

GameAssetLibrary::~GameAssetLibrary()
{

}

//Fill the game asset library with object factories.
bool GameAssetLibrary::Initialize()
{
	//library["Red Octorok"] = (std::shared_ptr<ObjectFactory>)(std::make_shared<RedOctorokFactory>());
	//library["Red Leever"] = (std::shared_ptr<ObjectFactory>)(std::make_shared<RedLeeverFactory>());
	//library["Blue Leever"] = (std::shared_ptr<ObjectFactory>)(std::make_shared<BlueLeeverFactory>());
	//library["Blue Octorok"] = (std::shared_ptr<ObjectFactory>)(std::make_shared<BlueOctorokFactory>());
	return true;
}

//Search for object given the search string.
std::shared_ptr<ObjectFactory> GameAssetLibrary::Search(std::string searchString)
{
	auto iter = library.find(searchString);
	if (iter != library.end())
		return iter->second; //Item found.
	else
		return nullptr; //Item not found.
}