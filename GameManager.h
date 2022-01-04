#pragma once
#include <SDL.h>

#include "Logger.h"
#include "Renderer.h"

class GameManager {
private:
	int mWidth, mHeight;
	std::string mTitle;
	bool mQuit = false;

	SDL_Window* mWindow = nullptr;
	Renderer* mRenderer = nullptr;

	void EventHandling();
	void Render();

public:
	GameManager(int w, int h, std::string title);
	~GameManager();
	//Delete copy constructor
	GameManager(GameManager& other) = delete;

	bool Init();
	void Run();
};