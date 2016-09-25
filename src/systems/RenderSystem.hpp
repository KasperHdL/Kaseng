#pragma once

#include <iostream>
#include "../Components.hpp"
#include "../Pools.hpp"
#include "../Utility.hpp"

#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Camera.hpp"
#include "SRE/Texture.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"

#include "glm/glm.hpp"

class RenderSystem{
    public:
        RenderSystem(){};
        ~RenderSystem(){};

        void start(Pools* pools, glm::vec4 bgColor);
        void shutdown();

        void render();
        

    private:
        SimpleRenderEngine* sre;
        glm::vec4 bgColor;
        Pools* pools;

        Mesh* box;
        Mesh* circle;
};
