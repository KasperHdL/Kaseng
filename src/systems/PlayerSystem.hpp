#pragma once

#include "../Components.hpp"
#include "../Pools.hpp"

class PlayerSystem{
    public:
        PlayerSystem(){};
        ~PlayerSystem(){};

        void start(Pools* pools);
        void shutdown();

        void update();

    private:
        Pools* pools;
};
