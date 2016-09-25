#include "Pools.hpp"

void Pools::start(int reserve_transforms, int reserve_renderEntities, int reserve_dynamicBodies, int reserve_staticBodies){
    transforms.reserve(reserve_transforms);
    renderEntities.reserve(reserve_renderEntities);

    dynamicBodies.reserve(reserve_dynamicBodies);
    staticBodies.reserve(reserve_staticBodies);
}

void Pools::shutdown(){
    transforms.clear();
    dynamicBodies.clear();
} 

