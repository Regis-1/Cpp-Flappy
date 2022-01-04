#include "GameManager.h"

GameManager::GameManager(int w, int h, std::string title) : mWidth(w), mHeight(h), mTitle(title) {

}

bool GameManager::Init() {
	//SDL Initialization
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Logger::Error("SDL could not initialize.");
		return false;
	}
	Logger::Success("SDL has been initialized.");

	//Window initialization
	mWindow = SDL_CreateWindow(mTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		mWidth, mHeight, SDL_WINDOW_SHOWN);
	if (mWindow == nullptr) {
		Logger::Error("Window could not be initialized.");
		return false;
	}
	Logger::Success("Window has been initialized.");

	//Renderer initialization
	mRenderer = new Renderer(mWindow);

	return true;
}

GameManager::~GameManager() {
	delete mRenderer;

	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_Quit();
	Logger::Info("GameManager has been destroyed.");
}

void GameManager::Run() {
	//GAME LOOP
	while (!mQuit) {
		EventHandling();
		Render();
	}
}

//PRIVATE METHODS
void GameManager::EventHandling() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)
			mQuit = true;
	}
}

void GameManager::Render() {
	//mRenderer->ClearScreen();
	mRenderer->UpdateScreen();
}