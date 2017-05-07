/*
* Author:	Jeffery Wooldridge
*			UALR
* 
* Date:		3 May, 2017	
*
* File:		Source.cpp
*
* Purpose:	This is the final project for CPSC 4377 Advanced Game Programming, Cereal Killer.
*/

#include <iostream>
#include <random>
#include <memory>

#include "SDL.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	//========================================
	//Construct Game
	//========================================
	std::unique_ptr<Game> game(std::make_unique<Game>());
	if(!game->Initialize())
	{
		printf( "Game could not Initialize!");
		exit(1);
	}

	//========================================
	//Load Level
	//========================================
	game->Reset();
	std::string levelConfigFile= "./Assets/Config/level1.xml";
	std::string objectConfigFile = "./Assets/Config/level1Assets.xml";
	if(!game->LoadLevel(levelConfigFile, objectConfigFile))
	{
		printf( "Game could not load level %s: ", levelConfigFile.c_str());
		exit(1);
	}

	//========================================
	//Main Game Loop
	//========================================
	bool quit = false;

	//While the user hasn't quit
	while(!game->Run()){	}

	//========================================
	// Clean-up
	//========================================
	if(game)
	{
		game = nullptr;
	}


	return 0;

}