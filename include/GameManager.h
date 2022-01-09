#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>

#include "../include/Logger.h"
#include "../include/Renderer.h"
#include "../include/Player.h"
#include "../include/Block.h"
#include "../include/Obstacle.h"

const int HORIZON_HEIGHT = 40;

enum GameState {
	QUIT,
	RUNNING,
	PAUSE,
	END
};

class GameManager {
private:
	int mScrWidth, mScrHeight;
	std::string mTitle;
	GameState mGameState;
	float mMaxFPS = 60.0f;
	std::vector<Entity*> mEnts;
	int mScore = 0;

	bool mChecker[2] = { false, false };

	//Obstacles parameters
	int mObsPassage = 150;
	int mObsWidth = 100;
	int mObsSpeed = 4;

	SDL_Window* mWindow = nullptr;
	Renderer* mRenderer = nullptr;
	Player* mPlayer = nullptr;
	Block* mGround = nullptr;
	Obstacle* mObstacle = nullptr;

	void EventHandling();
	void InitializeObjects();
	void ProcessMove();
	void ProcessCollisions();
	void ProcessScore();
	void ReplaceObstacle();
	void Retry();
	bool IsBetween(int x, int a, int b);
	bool IsPlayerCollision();

public:
	GameManager(int w, int h, std::string title);
	~GameManager();
	//Delete copy constructor
	GameManager(GameManager& other) = delete;

	bool Init();
	void Run();
};