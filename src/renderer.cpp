#include "renderer.h"

Renderer::Renderer()
{
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOWPOS_CENTERED, &_window, &_renderer);
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

void Renderer::render()
{
    while (true)
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderPresent(_renderer);
        SDL_Delay(20);
    }
}
