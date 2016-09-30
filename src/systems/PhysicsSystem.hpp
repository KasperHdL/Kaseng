#pragma once

#include "../Components.hpp"
#include "../Pools.hpp"
#include "../Utility.hpp"

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

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

        Quad getBoxVerticesInWorld(mat4 worldTransform);

        float getDistanceOnProjectedAxis(vec2 ax, vec2 a[], int a_length, vec2 b[], int b_length);


};

