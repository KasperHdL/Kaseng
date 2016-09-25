#include "Game.hpp"
#include <SRE/Shader.hpp>


using namespace glm;

Game::Game(int width, int height)
    :_screenWidth(width), _screenHeight(height)
{
    _gameRunning = true;

}

Game::~Game(){}

void Game::init(){
    pools.start(1024,1024,512);

    factory.start(&pools);
    physicsSystem.start(&pools, vec2(0,-0.1));
    renderSystem.start(&pools, vec4(0.15,0.1,0.05,1));

    factory.createPlayer(vec2(100,100));

    for(int i = 0; i < 20;i ++){
        float r = ((float)i / 20);
        factory.createEnemy(vec2(r * _screenWidth, 200), vec4(r, r, r, 1));
    }

    factory.createWall(vec2(_screenWidth / 2, 10), vec2(_screenWidth / 2, 10));
}

void Game::start(){
    Uint64 tNow = SDL_GetPerformanceCounter();
    Uint64 tLast = 0;
    float delta = 0;


    float renderCount = 0;
    float physicsCount = 0;
    float updateCount = 0;

    float renderRate = 1/60;
    float physicsRate = 1/240;
    float updateRate = 1/120;

    while(_gameRunning){
        tLast = tNow;
        tNow = SDL_GetPerformanceCounter();

        delta = clamp<float>((tNow - tLast) / (float) SDL_GetPerformanceFrequency(), 0, 1);

        renderCount += delta;
        physicsCount += delta;
        updateCount += delta;

        //debug quit
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            _gameRunning = false;
                        break;
                    }
                break;
            }
        }

        //input
        
        //physics
        if(physicsCount >= physicsRate){
            physicsSystem.update(physicsCount); 
            physicsCount = 0;
        }

        //entities update
        
        if(renderCount >= renderRate){
            renderSystem.render();
            renderCount = 0;
        }
        
    }

}
