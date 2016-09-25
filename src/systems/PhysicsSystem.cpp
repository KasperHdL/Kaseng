#include "PhysicsSystem.hpp"
#include <iostream>


void PhysicsSystem::start(Pools* pools, vec2 gravity){
    this->pools = pools;
    this->gravity = gravity;

}


void PhysicsSystem::shutdown(){

}

void PhysicsSystem::update(float delta){

    for(auto& e : pools->dynamicBodies){
        e.acceleration += gravity;
        e.velocity += e.acceleration;
        e.transform->position += e.velocity * delta;

        for(auto& s : pools->staticBodies){
            vec2 overlap = getOverlap(e, s);
            std::cout << overlap.x << " : " << overlap.y << std::endl;
            
            if(overlap != vec2(0)){

                e.transform->position -= overlap;
                e.velocity = vec2(0);
                e.acceleration = vec2(0);

            }

        }
        std::cout << endl << endl;
    }

}


vec2 PhysicsSystem::getOverlap(DynamicBody d, StaticBody s){
    if(d.shape == Shape::Box){

        Quad a = getBoxVerticesInWorld(Utility::getTransform(d.transform));
        Quad b = getBoxVerticesInWorld(Utility::getTransform(s.transform));
       
        vec2 ax1 = normalize(a.b - a.a);
        float d1 = getDistanceBetweenQuadOnAxis(ax1, a, b);

        vec2 ax2 = normalize(a.d - a.a);
        float d2 = getDistanceBetweenQuadOnAxis(ax2, a, b);

        if(d1 < 0 && d2 < 0){
            //collision
            
            std::cout << std::printf("distances 1: %f 2: %f",d1,d2) << endl;
            vec2 delta = normalize(d.transform->position - s.transform->position);

            float dot1 = dot(ax1, delta);
            float dot2 = dot(ax2, delta);
            std::cout << std::printf("dot1 %f dot2 %f",dot1,dot2) << endl;
            


            if(dot1 < 0)
                d1 = -d1;
            if(dot2 < 0)
                d2 = -d2;

            if(abs(d1) < abs(d2))
                return ax1 * d1;
            else
                return ax2 * d2;

        }
    }else{

    }

    return vec2(0);
}


Edge PhysicsSystem::getEdgeFromBox(mat4 worldTransform, int index){

    Edge result;

    vec4 vertices[] =
    {
        vec4(-1,-1,0,1),
        vec4(1,-1,0,1),
        vec4(1,1,0,1),
        vec4(-1,1,0,1),
    };

    result.from = vec2(worldTransform * vertices[index]);
    result.to   = vec2(worldTransform * vertices[(index + 1) % 4]);

    vec2 n = normalize(result.to - result.from);
    result.normal = vec2(-n.y, n.x);

    return result;

}

Quad PhysicsSystem::getBoxVerticesInWorld(mat4 worldTransform){

    vec4 vertices[] =
    {
        vec4(-1,-1,0,1),
        vec4(1,-1,0,1),
        vec4(1,1,0,1),
        vec4(-1,1,0,1),
    };

    Quad quad;
    quad.a = vec2(worldTransform * vertices[0]);
    quad.b = vec2(worldTransform * vertices[1]);
    quad.c = vec2(worldTransform * vertices[2]);
    quad.d = vec2(worldTransform * vertices[3]);

    return quad;
}


float PhysicsSystem::getDistanceBetweenQuadOnAxis(vec2 ax, Quad a, Quad b){

        std::cout << std::printf("axis = (%f, %f)", ax.x, ax.y) << std::endl;


        float projected[] =
        {
            dot(ax, a.a),
            dot(ax, a.b),
            dot(ax, a.c),
            dot(ax, a.d),

            dot(ax, b.a),
            dot(ax, b.b),
            dot(ax, b.c),
            dot(ax, b.d),
        };
        std::cout << std::printf("dots= %f %f %f %f - %f %f %f %f",  projected[0], projected[1], projected[2], projected[3], projected[4], projected[5], projected[6],projected[7]) << std::endl;

        float minmax_a[] =
        {
            glm::min(
                glm::min(projected[0], projected[1]),
                glm::min(projected[2], projected[3])
            ),
            glm::max(
                glm::max(projected[0], projected[1]),
                glm::max(projected[2], projected[3])
            ),
        };

        float minmax_b[] =
        {
            glm::min(
                glm::min(projected[4], projected[5]),
                glm::min(projected[6], projected[7])
            ),
            glm::max(
                glm::max(projected[4], projected[5]),
                glm::max(projected[6], projected[7])
            ),
        };

        std::cout << std::printf("min = %f max = %f - min = %f max = %f",  minmax_a[0], minmax_a[1], minmax_b[0], minmax_b[1]) << std::endl;

        float la = minmax_a[1] - minmax_a[0];
        float lb = minmax_b[1] - minmax_b[0];

        float total1 = glm::max(abs(minmax_a[0] - minmax_b[1]), la);
        float total2 = glm::max(abs(minmax_a[1] - minmax_b[0]), lb);
        std::cout << std::printf("total1 %f total2 %f", total1, total2) << std::endl;

        float total = glm::max(total1, total2);
        std::cout << std::printf("total %f la %f lb %f", total, la, lb) << std::endl;

        return total - (la + lb);
}
