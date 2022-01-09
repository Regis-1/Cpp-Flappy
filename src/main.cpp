#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "../include/Logger.h"
#include "../include/GameManager.h"

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

int main(int argc, char* args[])
{
	srand((unsigned int)time(NULL));

	GameManager gameManager(SCREEN_WIDTH, SCREEN_HEIGHT, "FlappyCpp");

	if (!gameManager.Init()) {
		Logger::Error("Failed to initialize GameManager!");
		return -1;
	}

	gameManager.Run();

	return 0;
}