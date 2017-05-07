#include "Definitions.h"

#include "tinyxml\tinystr.h"

#include "Game.h"


Game::Game()
{
	/*gDevice._Myptr() = new GraphicsDevice(SCREEN_WIDTH, SCREEN_HEIGHT);
	aLibrary._Myptr() = new ArtAssetLibrary();
	timer._Myptr() = new Timer();
	view._Myptr() = new View();
	gLibrary._Myptr() = new GameAssetLibrary();
	iDevice._Myptr() = new InputDevice();*/

	timer = std::make_unique<Timer>();

	devicesAndLibraries = NULL;
	gameTime = 0;
	paused = false;
	curLevel = 1;
	score = 0;
	dt = 1 / GAME_FPS;
}

Game::~Game()
{
	if (devicesAndLibraries)
	{
		devicesAndLibraries->Shutdown();
		devicesAndLibraries = NULL;
	}
}

bool Game::Initialize()
{
	if (!timer->Initialize()) //Initialize timer; throw error if it is not possible.
	{
		std::cout << "Could not initialize timer!" << std::endl;
		return false;
	}
	return true;
}

//Update every object in the objects vector, along with the view.
bool Game::Update()
{
	//Update the physics device.
	devicesAndLibraries->getPhysicsDevice()->Update(dt);

	//Check for dead objects and remove them.
	for (std::vector<std::shared_ptr<Object>>::iterator object = objects.begin(); object != objects.end(); ++object)
	{
		//if it is dead
		if ((*object)->getObjectType() == "John" && (*object)->getIsDead())
			std::cout << "YOU DIED.";
		if ((*object)->getIsDead())
		{
			//Remove the object's sprite.
			devicesAndLibraries->getGraphicsDevice()->removeSprite((*object)->GetComponent<SpriteComponent>().get());
			//stop the physics on it
			devicesAndLibraries->getPhysicsDevice()->SetStopPhysics((*object).get());
			//close off the componenets.
			(*object)->removeComponents();
			//remove object from the vector.
			objects.erase(object);
			//back up to previous item because this one was deleted.
			--object;
		}
	}

	//add any objects created in the previous iteration
	if (!newObjects.empty())
	{
		objects.insert(objects.end(), newObjects.begin(), newObjects.end());
		newObjects.clear();
	}

	for (auto&& object : objects) //Iterate over every object and update them.
	{
		std::shared_ptr<Object> temp = object->Update(gameTime);
		//if it returned an object, add it to the list to be added.
		if (temp != nullptr)
		{
			newObjects.push_back(temp);
		}
	}
	return true;
}

//Perform updating and drawing of objects, amongst other things.
bool Game::Run()
{
	if (devicesAndLibraries->getInputDevice()->GetEvent(GAME_QUIT))
		return true;
	if (devicesAndLibraries->getInputDevice()->GetEvent(GAME_PAUSE))
		paused = !paused;
	timer->start();
	devicesAndLibraries->getInputDevice()->Update();
	if (!paused)
	{
		Update(); //Update objects.
		Draw(); //Draw objects.
		++gameTime; //Increment game time.
	}

	timer->fpsRegulate();
	return false;
}

//Draw every object.
void Game::Draw()
{
	devicesAndLibraries->getGraphicsDevice()->Begin();
	devicesAndLibraries->getGraphicsDevice()->Draw();
	devicesAndLibraries->getGraphicsDevice()->Present();
}

bool Game::LoadLevel(std::string levelConfigFile, std::string objectConfigFile)
{
	Reset();

	//Make device manager
	devicesAndLibraries = std::make_unique<DeviceAndLibraryManager>();
	devicesAndLibraries->Initialize();

	//Load files.
	TiXmlDocument lvlConfig(levelConfigFile.c_str());
	TiXmlDocument objConf(objectConfigFile.c_str());

	//Don't do anything if the config files cannot be loaded.
	if (!lvlConfig.LoadFile()) {
		std::cout << "Error: Could not load level XML file!";
		return false;
	}

	if (!objConf.LoadFile()) {
		std::cout << "Error: Could not load object XML file!";
		return false;
	}

	TiXmlElement* objRoot = objConf.FirstChildElement("Objects");
	objRoot = objRoot->FirstChildElement("Creature");
	while (objRoot)
	{
		std::string name = objRoot->Attribute("name");
		std::string path = objRoot->Attribute("sprite");

		devicesAndLibraries->getArtLibrary()->AddAsset(name, path);
		objRoot = objRoot->NextSiblingElement("Creature");
	}

	TiXmlElement* lvlRoot = lvlConfig.FirstChildElement("Level1");

	//Set the background for this level.
	std::string bgPath = lvlRoot->Attribute("background");
	devicesAndLibraries->getGraphicsDevice()->setBackground(bgPath);

	lvlRoot = lvlRoot->FirstChildElement("GameAsset");

	while (lvlRoot)
	{ 
		std::shared_ptr<Object> tmp = devicesAndLibraries->getObjectFactory()->create(lvlRoot, devicesAndLibraries); //Create the object.
		if (tmp == NULL)
		{
			std::cout << "Error: Could not initialize object!";
			return false;
		}
		else
			objects.push_back(tmp); //Push this object onto the objects vector.
		lvlRoot = lvlRoot->NextSiblingElement("GameAsset");
	}
	return true;
}

//Purge the objects vector.
void Game::Reset()
{
	if (!objects.empty())
	{
		for (auto object : objects)
			devicesAndLibraries->getPhysicsDevice()->RemoveObject(object.get());
		objects.clear();
	}
	if (devicesAndLibraries)
		devicesAndLibraries->Shutdown();
	devicesAndLibraries = NULL;
}