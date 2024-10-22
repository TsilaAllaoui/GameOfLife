#ifndef __RENDERER_H__
#define __RENDERER_H__

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define SCALE 10

#include "SDL.h"
#include "eventHandler.h"
#include "engine.h"
#include <chrono>

class Renderer
{
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    EventHandler _eventHandler;
    Engine &_engine;

public:
    Renderer(Engine &);
    ~Renderer();

    void render();
    void regulateFrameRate(const std::chrono::steady_clock::time_point &startTime);
    void drawRect(const int &x, const int &y, const uint64_t &color = 0xFFFFFFFF);

    static unsigned int ZoomFactor;
};

#endif