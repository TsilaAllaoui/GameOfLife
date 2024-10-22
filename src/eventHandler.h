#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

#include "SDL.h"

class EventHandler
{
    SDL_Event _event;

public:
    EventHandler();
    void handleEvent();
    static unsigned int GameSpeed;
};

#endif
