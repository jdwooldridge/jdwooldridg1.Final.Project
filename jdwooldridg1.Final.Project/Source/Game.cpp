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

	curLevel = 1;
	curLevelConfig = "./Assets/Config/level" + std::to_string(curLevel) + ".xml";
	curLevelAssets = "./Assets/Config/level" + std::to_string(curLevel) + "Assets.xml";
	devicesAndLibraries = NULL;
	gameTime = 0;
	paused = false;
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

//Update every object in the objects vector and remove ones that are dead. Also update the UI display at the top of the screen.
bool Game::Update()
{
	//Update the physics device.
	devicesAndLibraries->getPhysicsDevice()->Update(dt);

	//Check for dead objects and remove them.
	for (std::vector<std::shared_ptr<Object>>::iterator object = objects.begin(); object != objects.end(); ++object)
	{
		devicesAndLibraries->getGraphicsDevice()->Text2Screen("Lives: " + std::to_string(devicesAndLibraries->getLives()), SCREEN_WIDTH - 10, 10); //Update lives display.
		devicesAndLibraries->getGraphicsDevice()->Text2Screen("Score: " + std::to_string(devicesAndLibraries->getScore()), SCREEN_WIDTH - 10, 50); //Update score display.
		//Perform the following actions if the current object is the player.
		if ((*object)->getObjectType() == "John")
		{
			devicesAndLibraries->getGraphicsDevice()->Text2Screen("Health: " + std::to_string((*object)->GetComponent<HealthComponent>()->GetHealth()), 10, 10); //Update player's health display.
			if ((*object)->getIsDead()) //Reload level and decrement lives by one if player dies.
			{
				devicesAndLibraries->setLives(devicesAndLibraries->getLives() - 1);
				LoadLevel(curLevelConfig, curLevelAssets);
				std::cout << "YOU DIED.";
			}
		}
		//Perform the following actions if the current object is the boss.
		if ((*object)->getObjectType() == "Boss")
		{
			devicesAndLibraries->getGraphicsDevice()->Text2Screen("Enemy: " + std::to_string((*object)->GetComponent<HealthComponent>()->GetHealth()), 10, 50); //Update the boss's health display.
			if((*object)->getIsDead()) //Go onto the next level if the boss dies.
			{
				++curLevel;
				curLevelConfig = "./Assets/Config/level" + std::to_string(curLevel) + ".xml";
				curLevelAssets = "./Assets/Config/level" + std::to_string(curLevel) + "Assets.xml";
				LoadLevel(curLevelConfig, curLevelAssets);
				std::cout << "LEVEL COMPLETE";
			}
			if(devicesAndLibraries->getView()->getPosition().x + SCREEN_WIDTH == (*object)->GetComponent<BodyComponent>()->getPosition().x) //Change background music to boss theme if the boss comes into view.
				devicesAndLibraries->getSoundDevice()->SetBackground("Boss");
		}
		//Change background music to boss theme if the boss comes into view.
		/*if ((*object)->getObjectType() == "Boss" && devicesAndLibraries->getView()->getPosition().x + SCREEN_WIDTH >= (*object)->GetComponent<BodyComponent>()->getPosition().x)
		{
			devicesAndLibraries->getSoundDevice()->SetBackground("Boss");
		}*/
		//If any other object dies.
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
	if (devicesAndLibraries->getLives() <= 0)
	{
		printf("GAME OVER");
		return true;
	}
	//If Q is pressed, quit the game.
	if (devicesAndLibraries->getInputDevice()->GetEvent(GAME_QUIT))
		return true;
	//If P is pressed, pause/unpause the game.
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
	//Load graphics.
	TiXmlElement* objRoot = objConf.FirstChildElement("Objects");
	TiXmlElement* objElem = objRoot->FirstChildElement("Creature");
	while (objElem)
	{
		std::string name = objElem->Attribute("name");
		std::string path = objElem->Attribute("sprite");

		devicesAndLibraries->getArtLibrary()->AddAsset(name, path);
		objElem = objElem->NextSiblingElement("Creature");
	}

	//Load the sounds.
	objRoot = objRoot->NextSiblingElement("Sounds");
	objElem = objRoot->FirstChildElement("Sound");
	while (objElem)
	{
		std::string name = objElem->Attribute("name");
		std::string path = objElem->Attribute("path");
		bool isBg;
		objElem ->QueryBoolAttribute("background", &isBg);
		if (isBg)
			devicesAndLibraries->getSoundAssetLibrary()->AddBackgroundMusic(name, path);
		else
			devicesAndLibraries->getSoundAssetLibrary()->AddSoundEffect(name, path);
		objElem = objElem->NextSiblingElement("Sound");
	}

	TiXmlElement* lvlRoot = lvlConfig.FirstChildElement("Level1");

	//Set the background image for this level.
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

	devicesAndLibraries->getSoundDevice()->SetBackground("Theme");
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