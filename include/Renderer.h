#pragma once
#include <SDL.h>
#include <vector>

#include "../include/Logger.h"
#include "../include/Entity.h"
#include "../include/Player.h"
#include "../include/Block.h"

struct ColorAlpha {
	int r, g, b, a;
};

class Renderer {
private:
	SDL_Renderer* mRenderer = nullptr;

	const ColorAlpha mColBackground = { 0xff, 0xff, 0xff, 0xff };
	const ColorAlpha mColPlayer = { 0x00, 0x00, 0x00, 0xff };
	const ColorAlpha mColGround = { 0x00, 0xff, 0x00, 0xff };
	const ColorAlpha mColObstacle = { 0xcc, 0xcc, 0xcc, 0xff };

	void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius);
	void DrawPlayer(Player* player);
	void DrawBlock(Block* block);

	void SetRenderColor(ColorAlpha col);
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