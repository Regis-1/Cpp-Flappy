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