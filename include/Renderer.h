#pragma once
#include <SDL.h>
#include <vector>

#include "../include/Logger.h"
#include "../include/Entity.h"
#include "../include/Player.h"

class Renderer {
private:
	SDL_Renderer* mRenderer = nullptr;

	void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius);
	void DrawPlayer(Player* player);
public:
	Renderer() {};
	Renderer(SDL_Window* window);
	~Renderer();
	//Delete copy constructor
	Renderer(Renderer& other) = delete;

	void ClearScreen();
	void UpdateScreen();
	void RenderEntities(std::vector<Entity*> ents);
};