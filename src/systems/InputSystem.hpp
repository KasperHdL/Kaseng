#pragma once

#include "../Components.hpp"
#include "../Pools.hpp"

#include "SDL.h"

class InputSystem{
    public:
        InputSystem(){};
        ~InputSystem(){};

        void start(Pools* pools);
        void shutdown();

        void update(SDL_Event* e);

    private:
        Pools* pools;

};
