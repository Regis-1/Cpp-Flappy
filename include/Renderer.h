#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "../include/Logger.h"
#include "../include/Entity.h"
#include "../include/Player.h"
#include "../include/Block.h"

const int TEX_FILES_NUMBER = 5;
const std::string texFileNames[TEX_FILES_NUMBER] = { "background", "player", "ground", "pipeUpper", "pipeLower" };

class Renderer {
private:
	SDL_Renderer* mRenderer = nullptr;
	TTF_Font* mFont = nullptr;
	SDL_Surface* mSurface = nullptr;
	SDL_Texture* mScoreMessage = nullptr;
	SDL_Texture* mTextures[TEX_FILES_NUMBER] = { nullptr };
	SDL_Color mColText = { 255, 0, 0 };

	void DrawPlayer(Player* player);
	void DrawBlock(Block* block, SDL_Texture* tex);
public:
	Renderer() {};
	Renderer(SDL_Window* window);
	~Renderer();
	//Delete copy constructor
	Renderer(Renderer& other) = delete;

	void ClearScreen();
	void UpdateScreen();
	void RenderBackground(int scrWidth, int scrHeight);
	void RenderEntities(std::vector<Entity*> ents);
	void RenderText(std::string msg, int x, int y, int w, int h);
};