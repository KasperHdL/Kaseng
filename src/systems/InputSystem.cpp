#include "InputSystem.hpp"
#include <iostream>

void InputSystem::start(Pools* pools){
    this->pools = pools;

}

void InputSystem::shutdown(){

}

void InputSystem::update(SDL_Event* e){
    SDL_Keycode code = e->key.keysym.sym;
    if(e->type == SDL_KEYDOWN){
        for(Player& player : pools->players){
            if(code == player.left_keycode)
                player.left = true;
            else if(code == player.right_keycode)
                player.right = true;
            else if(code == player.jump_keycode)
                player.jump = true;
        }
    }else if(e->type == SDL_KEYUP){
        
        for(Player& player : pools->players){
            if(code == player.left_keycode)
                player.left = false;
            else if(code == player.right_keycode)
                player.right = false;
            else if(code == player.jump_keycode)
                player.jump = false;
        }

    }
    
}
