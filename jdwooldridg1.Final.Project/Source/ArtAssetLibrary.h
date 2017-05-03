#ifndef ARTASSETLIBRARY_H
#define ARTASSETLIBRARY_H
#include <iostream>
#include <memory>
#include <map>
#include "SDL.h"
#include "Texture.h"
#include "GraphicsDevice.h"

class ArtAssetLibrary 
{
public:
	ArtAssetLibrary();
	~ArtAssetLibrary();
	bool Initialize(GraphicsDevice*);
	bool AddAsset(std::string, std::string);
	std::shared_ptr<Texture> Search(std::string);

private:
	std::map<std::string, std::shared_ptr<Texture>> library;
	GraphicsDevice* gDevice;
};
#endif // ! ARTASSETLIBRARY_H