#include "RenderSystem.hpp"

using namespace glm;

void RenderSystem::start(Pools* pools, vec4 bgColor){
    this->pools = pools;
    this->bgColor = bgColor;

    sre = SimpleRenderEngine::instance;

    box = Mesh::createCube();
    circle = Mesh::createSphere();

}

void RenderSystem::shutdown(){

}

void RenderSystem::render(){
    sre->clearScreen(bgColor);
    sre->getCamera()->setWindowCoordinates();
        
    for(auto& e : pools->renderEntities){
        Shader* shader = Shader::getUnlit();
        shader->setVector("color", e.color);

        mat4 transform = Utility::getTransform(e.transform);

        if(e.shape == Shape::Box)
            sre->draw(box, transform, shader);
        else if(e.shape == Shape::Circle)
            sre->draw(circle, transform, shader);
    }

    sre->swapWindow();
}
