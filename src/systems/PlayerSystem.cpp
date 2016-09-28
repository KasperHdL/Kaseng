#include "PlayerSystem.hpp"
#include <iostream>

void PlayerSystem::start(Pools* pools){
    this->pools = pools;
}

void PlayerSystem::shutdown(){

}

void PlayerSystem::update(){
    for(Player& player : pools->players){
        DynamicBody* body = player.body;

        float v = 0, h = 0;
        if(player.left)
            h = -1;
        else if(player.right)
            h = 1;

        if(player.jump)
            v = 1;

        //std::cout << std::printf("input(%f,%f) add vec2(%f, %f)", h, v, h * player.runForce, v * player.jumpForce) << std::endl;
        body->acceleration += vec2(h * player.runForce, v * player.jumpForce);
    }
}
