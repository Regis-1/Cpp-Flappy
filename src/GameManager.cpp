#include "../include/GameManager.h"

GameManager::GameManager(int w, int h, std::string title) : mScrWidth(w), mScrHeight(h), mTitle(title) {
	mPlayer = new Player(240, 320, 30, 1.0f);
	mGround = new Block(0, mScrHeight-HORIZON_HEIGHT, mScrWidth, HORIZON_HEIGHT, 0.0f);
	mObstacle = new Obstacle(415, 150, 50, 3.0f, mScrWidth, mScrHeight, HORIZON_HEIGHT);
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
		mScrWidth, mScrHeight, SDL_WINDOW_SHOWN);
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
	delete mGround;

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
	ents.push_back(mGround);
	ents.push_back(mObstacle->GetBlock(0));
	ents.push_back(mObstacle->GetBlock(1));

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