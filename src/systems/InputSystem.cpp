#include "InputSystem.hpp"

void InputSystem::start(Pools* pools){
    this->pools = pools;

}

void InputSystem::shutdown(){

}

void InputSystem::update(SDL_Event* e){
    SDL_Scancode code = e->key.keysym.scancode;
    if(e->type == SDL_KEYDOWN){
        
        for(Player& player : pools->players){
            if(code == player.left_scancode)
                player.left = true;
            else if(code == player.right_scancode)
                player.right = true;
            else if(code == player.jump_scancode)
                player.jump = true;
        }
    }else if(e->type == SDL_KEYUP){
        
        for(Player& player : pools->players){
            if(code == player.left_scancode)
                player.left = false;
            else if(code == player.right_scancode)
                player.right = false;
            else if(code == player.jump_scancode)
                player.jump = false;
        }

    }
    
}
