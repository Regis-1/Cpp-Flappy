#include "../include/Renderer.h"

Renderer::Renderer(SDL_Window* window) {
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == nullptr)
		Logger::Error("Renderer could not be initialized!");
	else {
		Logger::Success("Renderer has been initialized.");
        TTF_Init();
        mFont = TTF_OpenFont("res/lato.ttf", 32);
        if (mFont == nullptr)
            Logger::Error("Font could not be loaded.");
		SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(mRenderer);
	}

    //textures loading
    for (int i = 0; i < TEX_FILES_NUMBER; i++) {
        mSurface = SDL_LoadBMP(("res/" + texFileNames[i] + ".bmp").c_str());
        mTextures[i] = SDL_CreateTextureFromSurface(mRenderer, mSurface);
        if (mTextures[i] == nullptr)
            Logger::Error(("Unable to create " + texFileNames[i] + " texture"));
        else
            Logger::Success(("Texture " + texFileNames[i] + " loaded successfully!"), true);
        SDL_FreeSurface(mSurface);
        mSurface = nullptr;
    }

}

Renderer::~Renderer() {
	SDL_DestroyRenderer(mRenderer);
    SDL_FreeSurface(mSurface);
    SDL_DestroyTexture(mScoreMessage);
    for (SDL_Texture* tex : mTextures) {
        SDL_DestroyTexture(tex);
        tex = nullptr;
    }

	mRenderer = nullptr;
    mSurface = nullptr;
    mScoreMessage = nullptr;
	Logger::Info("Renderer has been destroyed.");
}

void Renderer::ClearScreen() {
    SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(mRenderer);
}

void Renderer::UpdateScreen() {
	SDL_RenderPresent(mRenderer);
}

void Renderer::RenderBackground(int scrWidth, int scrHeight) {
    SDL_Rect texRect = { 0, 0, scrWidth, scrHeight };
    SDL_RenderCopy(mRenderer, mTextures[0], NULL, &texRect);
}

void Renderer::RenderEntities(std::vector<Entity*> ents) {
    bool groundDrawn = false;
    for (int i = 0; i < ents.size(); i++) {
        if (dynamic_cast<Player*>(ents[i]) != nullptr)
            DrawPlayer(static_cast<Player*>(ents[i]));
        else if (dynamic_cast<Block*>(ents[i]) != nullptr) 
            DrawBlock(static_cast<Block*>(ents[i]), mTextures[i+1]);
    }
}

void Renderer::RenderText(std::string msg, int x, int y, int w, int h) {
    SDL_Rect txtRect = { x, y, w, h };
    mSurface = TTF_RenderText_Solid(mFont, msg.c_str(), mColText);
    mScoreMessage = SDL_CreateTextureFromSurface(mRenderer, mSurface);
    SDL_RenderCopy(mRenderer, mScoreMessage, NULL, &txtRect);
    SDL_FreeSurface(mSurface);
    SDL_DestroyTexture(mScoreMessage);
    mSurface = nullptr;
    mScoreMessage = nullptr;
}

//PRIVATE METHODS
void Renderer::DrawPlayer(Player* player) {
    Position pos = player->GetPos();
    int size = player->GetSize();
    SDL_Rect texRect = { pos.x - size, pos.y - size, size * 2, size * 2 };
    SDL_RenderCopy(mRenderer, mTextures[1], NULL, &texRect);
}

void Renderer::DrawBlock(Block* block, SDL_Texture* tex) {
    Position pos = block->GetPos();
    Dimension dims = block->GetDimensions();
    SDL_Rect texRect = { pos.x, pos.y, dims.w, dims.h };
    SDL_RenderCopy(mRenderer, tex, NULL, &texRect);
}