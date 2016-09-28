#pragma once

#include "SDL.h"
#include "SRE/SimpleRenderEngine.hpp"
#include "glm/glm.hpp"
#include "Pools.hpp"
#include "Factory.hpp"

#include "systems/PhysicsSystem.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/PlayerSystem.hpp"

class Game{
    public:
        Game(int width, int height);
        ~Game();

        void init();
        void start();

        Pools pools;
        RenderSystem renderSystem;
        PhysicsSystem physicsSystem;
        InputSystem inputSystem;
        PlayerSystem playerSystem;
        Factory factory;

    private:
        int _screenWidth;
        int _screenHeight;

        bool _gameRunning;


        //tests
        void test_collision();
};
