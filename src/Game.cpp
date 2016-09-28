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
    inputSystem.start(&pools);
    playerSystem.start(&pools);

    factory.createPlayer(vec2(_screenWidth-20,200));
    /*
    for(int i = 0; i < 20;i ++){
        float r = ((float)i / 20);
        factory.createEnemy(vec2(r * _screenWidth, 200), vec4(r, r, r, 1));
    }
    */

    test_collision();
}

void Game::start(){
    Uint64 tNow = SDL_GetPerformanceCounter();
    Uint64 tLast = 0;
    float delta = 0;


    float renderCount = 0;

    float renderRate = 1/60;

    while(_gameRunning){
        tLast = tNow;
        tNow = SDL_GetPerformanceCounter();

        delta = clamp<float>((tNow - tLast) / (float) SDL_GetPerformanceFrequency(), 0, 1);

        renderCount += delta;

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            //debug quit
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            _gameRunning = false;
                        break;
                    }
                break;
            }
            //input
            inputSystem.update(&event);
        }

        playerSystem.update();
        
        //physics
        physicsSystem.update(delta); 

        //entities update
        
        if(renderCount >= renderRate){
            renderSystem.render();
            renderCount = 0;
        }
        
    }

}

void Game::test_collision(){

    //physics test
    
    float qw = _screenWidth/4;
    float qh = _screenHeight/4;

    //normal
    factory.createEnemy(vec2(qw,qh *4), vec4(1,1,1, 1));
    factory.createWall(vec2(qw,qh*3), vec2(100, 10));

    //upside down
    factory.createEnemy(vec2(qw,qh*2), vec4(1,1,1, 1));
    factory.createWall(vec2(qw,qh), vec2(100, 10),glm::pi<float>());

    //cross
    factory.createEnemy(vec2(qw*2,qh*4), vec4(1,1,1, 1));
    factory.createWall(vec2(qw*2,qh*3), vec2(100, 10),3.14/4);
    factory.createWall(vec2(qw*2,qh*3), vec2(100, 10),-3.14/4);

    //upside down cross
    factory.createEnemy(vec2(qw*2,qh*2), vec4(1,1,1, 1));
    factory.createWall(vec2(qw*2,qh), vec2(100, 10),-3.14 + 3.14/4);
    factory.createWall(vec2(qw*2,qh), vec2(100, 10),-3.14 + -3.14/4);

    //tilt positive
    factory.createEnemy(vec2(qw*3,qh*4), vec4(1,1,1, 1));
    factory.createWall(vec2(qw*3,qh*3), vec2(50, 10),3.14/4);

    //tilt negative
    factory.createWall(vec2(qw*3,qh*2), vec2(50, 10),3.14/4);



    //high speed
    factory.createEnemy(vec2(10,qh*4), vec4(1,1,1, 1));
    factory.createWall(vec2(_screenWidth,10), vec2(_screenWidth, 10),0);

}
