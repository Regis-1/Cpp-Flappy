#include "../include/GameManager.h"

GameManager::GameManager(int w, int h, std::string title) : mScrWidth(w), mScrHeight(h), mTitle(title) {
	InitializeObjects();
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
	mEnts.clear();
	delete mPlayer;
	delete mRenderer;
	delete mGround;
	delete mObstacle;

	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_Quit();
	Logger::Info("GameManager has been destroyed.");
}

void GameManager::Run() {
	float maxTimeInterval = 1000.0f / mMaxFPS;
	uint32_t t1, t2 = 0, deltaTime;
	mGameState = GameState::RUNNING;

	//GAME LOOP
	while (mGameState != GameState::QUIT) {
		t1 = SDL_GetTicks();
		deltaTime = t1 - t2;
		if (deltaTime > maxTimeInterval) {
			t2 = t1;
			EventHandling();
			if (mGameState == GameState::RUNNING) {
				ProcessMove();
				mRenderer->ClearScreen();
				mRenderer->RenderBackground(mScrWidth, mScrHeight);
				mRenderer->RenderEntities(mEnts);
				mRenderer->RenderText("Score: "+std::to_string(mScore), 4, 4, 90, 30);
				mRenderer->UpdateScreen();
				ProcessCollisions();
				ProcessScore();
			}
		}
	}
}

//PRIVATE METHODS
void GameManager::EventHandling() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)
			mGameState = GameState::QUIT;
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				mGameState = GameState::QUIT;
				break;

			case SDLK_SPACE:
				mPlayer->SetV0(-12);
				break;

			case SDLK_p:
				if(mGameState == GameState::PAUSE)
					mGameState = mGameState == GameState::PAUSE ? GameState::RUNNING : GameState::PAUSE;
				break;
			
			case SDLK_r:
				if (mGameState == GameState::END)
					Retry();
				break;
			}

		}
	}
}

void GameManager::InitializeObjects() {
	mPlayer = new Player(180, 320, 30);
	mGround = new Block(0, mScrHeight - HORIZON_HEIGHT, mScrWidth, HORIZON_HEIGHT, 0);
	mObstacle = new Obstacle(mScrWidth, mObsPassage, mObsWidth, mObsSpeed, mScrWidth, mScrHeight, HORIZON_HEIGHT);

	mEnts.push_back(mPlayer);
	mEnts.push_back(mGround);
	mEnts.push_back(mObstacle->GetBlock(0));
	mEnts.push_back(mObstacle->GetBlock(1));
}

void GameManager::ProcessMove() {
	mPlayer->Move();
	mObstacle->Move();

	if (mObstacle->IsRemovable()) {
		ReplaceObstacle();
		//Score checking variables reset
		mChecker[0] = false;
		mChecker[1] = false;
	}
}

void GameManager::ProcessCollisions() {
	if (IsPlayerCollision()) {
		mGameState = GameState::END;
	}
}

void GameManager::ProcessScore() {
	Position pos = mObstacle->GetBlock(0)->GetPos();
	Dimension dims = mObstacle->GetBlock(0)->GetDimensions();
	Position playerPos = mPlayer->GetPos();
	int size = mPlayer->GetSize();

	if (pos.x + dims.w <= playerPos.x - size)
		mChecker[0] = true;
	else
		mChecker[0] = false;

	if (mChecker[0] && !mChecker[1])
		mScore++;

	mChecker[1] = mChecker[0];
}

void GameManager::ReplaceObstacle() {
	mEnts.pop_back();
	mEnts.pop_back();
	delete mObstacle;
	mObstacle = new Obstacle(mScrWidth, mObsPassage, mObsWidth, mObsSpeed,
		mScrWidth, mScrHeight, HORIZON_HEIGHT);
	mEnts.push_back(mObstacle->GetBlock(0));
	mEnts.push_back(mObstacle->GetBlock(1));
}

void GameManager::Retry() {
	mEnts.clear();
	delete mPlayer;
	delete mGround;
	delete mObstacle;

	InitializeObjects();
	mScore = 0;

	mGameState = GameState::RUNNING;
}

bool GameManager::IsPlayerCollision() {
	Position playerPos = mPlayer->GetPos();
	int playerSize = mPlayer->GetSize();

	Position otherPos;
	Dimension otherDims;
	int passage = mObstacle->GetPassage();

	//Ground
	otherPos = mGround->GetPos();
	otherDims = mGround->GetDimensions();
	if (playerPos.y - playerSize < 0 || playerPos.y + playerSize > otherPos.y)
		return true;

	//Upper block
	otherPos = mObstacle->GetBlock(0)->GetPos();
	otherDims = mObstacle->GetBlock(0)->GetDimensions();
	if ((playerPos.y - playerSize < otherDims.h) &&
		(IsBetween(playerPos.x + playerSize, otherPos.x, otherPos.x + otherDims.w) ||
			IsBetween(playerPos.x - playerSize, otherPos.x, otherPos.x + otherDims.w)))
		return true;

	//Lower block
	otherPos = mObstacle->GetBlock(1)->GetPos();
	if ((playerPos.y + playerSize > otherDims.h + passage) &&
		(IsBetween(playerPos.x + playerSize, otherPos.x, otherPos.x + otherDims.w) ||
			IsBetween(playerPos.x - playerSize, otherPos.x, otherPos.x + otherDims.w)))
		return true;

	return false;
}

bool GameManager::IsBetween(int x, int a, int b) {
	if (x > a && x < b)
		return true;

	return false;
}