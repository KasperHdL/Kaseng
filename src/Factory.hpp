#pragma once

#include "Components.hpp"
#include "Pools.hpp"
#include "glm/glm.hpp"

#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"

#include "SDL_keycode.h"

using namespace glm;

class Factory{
    public:

        Factory(){};
        ~Factory(){};

        void start(Pools* pools);
        void shutdown();

        void createPlayer(vec2 position);
        void createEnemy(vec2 position, vec4 color);
        void createWall(vec2 position, vec2 scale, float rotation = 0);


    private:

        Pools* pools;

};
