#include "Pools.hpp"

void Pools::start(int reserve_transforms, int reserve_renderEntities, int reserve_dynamicBodies, int reserve_staticBodies, int reserve_players){
    transforms.reserve(reserve_transforms);
    renderEntities.reserve(reserve_renderEntities);

    dynamicBodies.reserve(reserve_dynamicBodies);
    staticBodies.reserve(reserve_staticBodies);

    players.reserve(reserve_players);
}

void Pools::shutdown(){
    transforms.clear();

    dynamicBodies.clear();
    staticBodies.clear();
    renderEntities.clear();

    for(auto& el : dynamicBodies)
        delete el.transform;

    for(auto& el : staticBodies)
        delete el.transform;

    for(auto& el : renderEntities)
        delete el.transform;



    players.clear();
} 

