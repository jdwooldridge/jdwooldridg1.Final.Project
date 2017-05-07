#include "DeviceAndLibraryManager.h"

DeviceAndLibraryManager::DeviceAndLibraryManager() {}
DeviceAndLibraryManager::~DeviceAndLibraryManager() {}


bool DeviceAndLibraryManager::Initialize()
{
	gDevice = std::make_unique<GraphicsDevice>(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!gDevice->Initialize(false)) //Initialize graphics device; throw error if it is not possible.
	{
		std::cout << "Could not initialize graphics device!" << std::endl;
		return false;
	}

	aLibrary = std::make_unique<ArtAssetLibrary>();
	if (!aLibrary->Initialize(gDevice.get())) //Initialize art library; throw error if it is not possible.
	{
		std::cout << "Could not initialize art library!" << std::endl;
		return false;
	}
	//if (!gLibrary->Initialize()) //Initialize game asset library; throw error if it is not possible.
	//{
	//	std::cout << "Could not initialize game asset library!" << std::endl;
	//	return false;
	//}
	iDevice = std::make_unique<InputDevice>();
	if (!iDevice->Initialize()) //Initialize input device; throw error if it is not possible.
	{
		std::cout << "Could not initialize input device!" << std::endl;
		return false;
	}

	view = std::make_unique<View>();
	if (!view->Initialize(iDevice.get(), 0, SCREEN_HEIGHT - 250)) //Initialize view; throw error if it is not possible.
	{
		std::cout << "Could not initialize game view!" << std::endl;
		return false;
	}

	pDevice = std::make_unique<PhysicsDevice>(0, 9.8f);
	if (!pDevice->Initialize())
	{
		std::cout << "Could not initialize physics device!" << std::endl;
		return false;
	}

	pLibrary = std::make_unique<PhysicsAssetLibrary>();
	if (!pLibrary->Initialize())
	{
		std::cout << "Could not initialize physics asset library!" << std::endl;
		return false;
	}

	objectFactory = std::make_shared<ObjectFactory>();

	return true;
}

bool DeviceAndLibraryManager::Shutdown()
{
	iDevice = nullptr;

	//sLibrary->Finish();
	//sLibrary = NULL;

	gDevice->ShutDown();
	gDevice = NULL;

	//sDevice->Shutdown();
	//sDevice = NULL;

	pDevice = NULL;


	aLibrary = NULL;

	pLibrary = NULL;

	//oLibrary = NULL;

	//nLibrary = NULL;

	objectFactory = NULL;
	return true;
}