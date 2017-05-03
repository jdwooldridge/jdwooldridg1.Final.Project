#include "ArtAssetLibrary.h"

ArtAssetLibrary::ArtAssetLibrary()
{

}

ArtAssetLibrary::~ArtAssetLibrary()
{

}

//Set graphics device for art asset library.
bool ArtAssetLibrary::Initialize(GraphicsDevice* gDevice)
{
	this->gDevice = gDevice;
	return true;
}

//Adds a texture to the library based on the object's name and the path to its sprite.
bool ArtAssetLibrary::AddAsset(std::string name, std::string path)
{
	//Texture variable
	Texture* tempTexture;

	//Make a new texture and assign
	tempTexture = new Texture();
	if (!tempTexture->load(gDevice->getRenderer(), path))
		return false;
	//add to library
	library[name] = std::make_shared<Texture>(*tempTexture);
	return true;
}

//This function takes a string and finds the appropriate art asset in the library
//it returns the art object's texture.
std::shared_ptr<Texture> ArtAssetLibrary::Search(std::string searchString)
{
	return (library.find(searchString)->second);
}