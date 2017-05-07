#pragma once

#include "ArtAssetLibrary.h"
#include "PhysicsAssetLibrary.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "PhysicsDevice.h"
#include "ObjectFactory.h"
#include "View.h"

class DeviceAndLibraryManager
{
public:
	DeviceAndLibraryManager();
	~DeviceAndLibraryManager();

	bool Initialize();
	bool Shutdown();

	GraphicsDevice* getGraphicsDevice() { return gDevice.get(); }
	InputDevice* getInputDevice() { return iDevice.get(); }
	PhysicsDevice* getPhysicsDevice() { return pDevice.get(); }
	//SoundDevice* getSoundDevice() { return sDevice.get(); }
	View* getView() { return view.get(); }


	//void setGraphicsDevice(std::unique_ptr<GraphicsDevice> gDevice) { this->gDevice = std::move(gDevice); }
	//void setInputDevice(std::unique_ptr<InputDevice> iDevice) { this->iDevice = std::move(iDevice); }
	//void setPhysicsDevice(std::unique_ptr<PhysicsDevice> pDevice) { this->pDevice = std::move(pDevice); }
	////void setSoundDevice(std::unique_ptr<SoundDevice> sDevice) { this->sDevice = std::move(sDevice); }

	//void setArtLibrary(std::unique_ptr<ArtAssetLibrary> aLibrary) { this->aLibrary = std::move(aLibrary); }
	//void setPhysicsLibrary(std::unique_ptr<PhysicsAssetLibrary> pLibrary) { this->pLibrary = std::move(pLibrary); }

	ArtAssetLibrary* getArtLibrary() { return aLibrary.get(); }
	PhysicsAssetLibrary* getPhysicsLibrary() { return pLibrary.get(); }
	ObjectFactory* getObjectFactory() { return objectFactory.get(); }

protected:
	std::unique_ptr<GraphicsDevice> gDevice;
	std::unique_ptr<InputDevice> iDevice;
	std::unique_ptr<PhysicsDevice> pDevice;
	std::unique_ptr<View> view;
	//std::unique_ptr<GameAssetLibrary> gLibrary;
	std::unique_ptr<ArtAssetLibrary> aLibrary;
	std::unique_ptr<PhysicsAssetLibrary> pLibrary;
	std::shared_ptr<ObjectFactory> objectFactory;

	//std::unique_ptr<SoundDevice> sDevice;
};