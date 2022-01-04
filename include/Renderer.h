#pragma once
#include <SDL.h>

#include "../include/Logger.h"

class Renderer {
private:
	SDL_Renderer* mRenderer = nullptr;

	void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius);
public:
	Renderer() {};
	Renderer(SDL_Window* window);
	~Renderer();
	//Delete copy constructor
	Renderer(Renderer& other) = delete;

	void ClearScreen();
	void UpdateScreen();
};