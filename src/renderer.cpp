#include "renderer.h"

unsigned int Renderer::ZoomFactor = 1;

Renderer::Renderer(Engine &engine) : _window(nullptr),
                                     _renderer(nullptr),
                                     _eventHandler(),
                                     _engine(engine)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &_window, &_renderer);
    SDL_SetWindowPosition(_window, 20, 50);
    SDL_RenderSetLogicalSize(_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetWindowResizable(_window, SDL_TRUE);
    SDL_SetWindowTitle(_window, "Game of life");
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

void Renderer::render()
{
    // Main loop
    while (true)
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        // Logic update
        _engine.update();

        // Rendering
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);

        for (int i = 0; i < GRID_HEIGHT; i++)
        {
            for (int j = 0; j < GRID_WIDTH; j++)
            {
                drawRect(i, j, _engine.getGrid()[i][j]);
            }
        }
        SDL_RenderPresent(_renderer);

        // Event handling
        _eventHandler.handleEvent();

        // Regulating frameRate
        regulateFrameRate(startTime);
    }
}

void Renderer::regulateFrameRate(const std::chrono::steady_clock::time_point &startTime)
{
    auto endTime = std::chrono::high_resolution_clock::now();
    auto timeTook = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    if (timeTook < EventHandler::GameSpeed)
    {
        SDL_Delay(EventHandler::GameSpeed - timeTook);
    }
}

void Renderer::drawRect(const int &x, const int &y, const uint64_t &color)
{
    if (color == Cell::State::DEAD)
    {
        return;
    }
    auto r = (color & 0xFF000000) >> 24;
    auto g = (color & 0x00FF0000) >> 16;
    auto b = (color & 0x0000FF00) >> 8;
    auto a = (color & 0x000000FF);
    SDL_Rect rect = {x * SCALE, y * SCALE, SCALE, SCALE};
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(_renderer, &rect);
}
