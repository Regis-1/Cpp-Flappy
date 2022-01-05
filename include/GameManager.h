#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>

#include "../include/Logger.h"
#include "../include/Renderer.h"
#include "../include/Player.h"
#include "../include/Block.h"

const int HORIZON_HEIGHT = 40;

class GameManager {
private:
	int mScrWidth, mScrHeight;
	std::string mTitle;
	bool mQuit = false;
	float mMaxFPS = 60.0f;

	SDL_Window* mWindow = nullptr;
	Renderer* mRenderer = nullptr;
	Player* mPlayer = nullptr;
	Block* mGround = nullptr;

	void EventHandling();
	void ProcessLogic(uint32_t dt);

public:
	GameManager(int w, int h, std::string title);
	~GameManager();
	//Delete copy constructor
	GameManager(GameManager& other) = delete;

	bool Init();
	void Run();
};