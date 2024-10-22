#include "eventHandler.h"

unsigned int EventHandler::GameSpeed = 1000 / 1;

EventHandler::EventHandler() : _event()
{
}

void EventHandler::handleEvent()
{
    while (SDL_PollEvent(&_event))
    {
        if (_event.type == SDL_KEYDOWN)
        {
            if (_event.key.keysym.sym == SDLK_ESCAPE)
            {
                exit(0);
            }
            else if (_event.key.keysym.sym == SDLK_PLUS || _event.key.keysym.sym == SDLK_KP_PLUS)
            {
                GameSpeed -= 100;
            }
            else if (_event.key.keysym.sym == SDLK_MINUS || _event.key.keysym.sym == SDLK_KP_MINUS)
            {
                GameSpeed += 100;
            }
        }
    }
}
