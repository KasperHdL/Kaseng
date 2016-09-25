#pragma once

#include "../Components.hpp"
#include "../Pools.hpp"
#include "../Utility.hpp"

#include "glm/glm.hpp"

using namespace glm;

class PhysicsSystem{
    public:
        PhysicsSystem(){};
        ~PhysicsSystem(){};

        void start(Pools* pools, vec2 gravity);
        void shutdown();

        void update(float delta);

        vec2 getOverlap(DynamicBody d, StaticBody s);

    private:
        Pools* pools;
        vec2 gravity;

        Edge getEdgeFromBox(mat4 worldTransform, int index);
        Quad getBoxVerticesInWorld(mat4 worldTransform);

        float getDistanceBetweenQuadOnAxis(vec2 ax, Quad a, Quad b);


};

