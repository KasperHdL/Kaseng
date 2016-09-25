#include "Factory.hpp"

using namespace glm;
void Factory::start(Pools* pools){
    this->pools = pools;

}

void Factory::shutdown(){

}

void Factory::createPlayer(vec2 position){
    pools->transforms.push_back(Transform(position, vec2(25,25)));
    Transform* transform = &pools->transforms[pools->transforms.size()-1];
    pools->renderEntities.push_back(RenderEntity(transform, Shape::Circle, vec4(0, 0.75, 0.65, 1)));
}

void Factory::createEnemy(vec2 position, vec4 color){
    pools->transforms.push_back(Transform(position, vec2(15,15)));
    Transform* transform = &pools->transforms[pools->transforms.size()-1];

    pools->dynamicBodies.push_back(transform);
    pools->renderEntities.push_back(RenderEntity(transform, Shape::Box, color));
}


void Factory::createWall(vec2 position, vec2 scale){
    pools->transforms.push_back(Transform(position, scale));
    Transform* transform = &pools->transforms[pools->transforms.size()-1];

    pools->staticBodies.push_back(transform);
    pools->renderEntities.push_back(RenderEntity(transform, Shape::Box, vec4(1, 0.8, 0.8, 1)));
}
