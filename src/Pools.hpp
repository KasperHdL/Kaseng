#pragma once

#include "glm/glm.hpp"
#include <vector>
#include "Components.hpp"

using namespace std;

class Pools{
    public:
        
        vector<Transform> transforms;
        vector<DynamicBody> dynamicBodies;
        vector<StaticBody> staticBodies;
        vector<RenderEntity> renderEntities;

        Pools(){};
        ~Pools(){};

        void start(int reserve_transforms = 256, int reserve_renderEntities = 256, int reserve_physicsBodies = 32, int reserve_staticBodies = 128);
        void shutdown();

};
