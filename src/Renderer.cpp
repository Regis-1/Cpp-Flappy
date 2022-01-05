#include "../include/Renderer.h"

Renderer::Renderer(SDL_Window* window) {
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == nullptr)
		Logger::Error("Renderer could not be initialized!");
	else {
		Logger::Success("Renderer has been initialized.");
		SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(mRenderer);
	}
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;
	Logger::Info("Renderer has been destroyed.");
}

void Renderer::ClearScreen() {
	SDL_RenderClear(mRenderer);
}

void Renderer::UpdateScreen() {
	SDL_RenderPresent(mRenderer);
}

void Renderer::RenderEntities(std::vector<Entity*> ents) {
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xff);
    bool groundDrawn = false;
    for (Entity* ent : ents) {
        if (dynamic_cast<Player*>(ent) != nullptr)
            DrawPlayer(static_cast<Player*>(ent));
        else if (dynamic_cast<Block*>(ent) != nullptr) {
            if (!groundDrawn) {
                DrawGround(static_cast<Block*>(ent));
                groundDrawn = true;
            }
            else
                continue;
        }
    }
    SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderPresent(mRenderer);
}

//PRIVATE METHODS
//midpoint circle algorithm (source github)
void Renderer::DrawCircle(int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(mRenderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(mRenderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(mRenderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(mRenderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(mRenderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(mRenderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(mRenderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(mRenderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void Renderer::DrawPlayer(Player* player) {
    Position pos = player->GetPos();
    DrawCircle(pos.x, pos.y, player->GetSize());
}

void Renderer::DrawGround(Block* ground) {
    Position pos = ground->GetPos();
    Dimension dims = ground->GetDimensions();
    SDL_Rect fillRect = { pos.x, pos.y, dims.w, dims.h };
    SDL_RenderFillRect(mRenderer, &fillRect);
}