#ifndef __RENDERER_H__
#define __RENDERER_H__

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include "SDL.h"

class Renderer
{
    SDL_Window *_window;
    SDL_Renderer *_renderer;

public:
    Renderer();
    ~Renderer();

    void render();
};

#endif