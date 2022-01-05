#include "../include/GameManager.h"

GameManager::GameManager(int w, int h, std::string title) : mWidth(w), mHeight(h), mTitle(title) {
	mPlayer = new Player(240, 320, 30, 18.0f);
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
	delete mPlayer;
	delete mRenderer;

	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_Quit();
	Logger::Info("GameManager has been destroyed.");
}

void GameManager::Run() {
	float maxTimeInterval = 1000.0 / mMaxFPS;
	uint32_t t1, t2 = 0, deltaTime;
	
	//TODO: change this implicit creation
	std::vector<Entity*> ents;
	ents.push_back(mPlayer);

	//GAME LOOP
	while (!mQuit) {
		t1 = SDL_GetTicks();
		deltaTime = t1 - t2;
		if (deltaTime > maxTimeInterval) {
			t2 = t1;
			//std::cout << "FPS: " << 1000.0 / deltaTime << std::endl;
			EventHandling();
			ProcessLogic(deltaTime);
			mRenderer->RenderEntities(ents);
		}
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

void GameManager::ProcessLogic(uint32_t dt) {
	mPlayer->Move(dt);
}