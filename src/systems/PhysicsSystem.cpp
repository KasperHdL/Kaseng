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
        e.acceleration *= e.friction;
        e.velocity += e.acceleration;
        e.transform->position += e.velocity * delta;

        e.rotationVelocity = e.rotationAcceleration;
        e.transform->rotation += e.rotationVelocity * delta;

        for(auto& s : pools->staticBodies){
            vec2 overlap = getOverlap(e, s);
            
            if(overlap != vec2(0)){
                vec2 perp = glm::cross(vec3(normalize(overlap),0),vec3(0,0,1));

                e.transform->position += overlap;
                e.velocity = perp * dot(perp, e.velocity) * s.friction;
                e.acceleration = perp * dot(perp, e.acceleration) * e.friction;

            }

        }
    }

}


vec2 PhysicsSystem::getOverlap(DynamicBody d, StaticBody s){
    if(d.shape == Shape::Box){

        Quad a = getBoxVerticesInWorld(Utility::getTransform(d.transform));
        Quad b = getBoxVerticesInWorld(Utility::getTransform(s.transform));
        
        vec2 ax1 = normalize(a.v[1] - a.v[0]);
        vec2 ax2 = normalize(a.v[2] - a.v[1]);
        vec2 ax3 = normalize(b.v[1] - b.v[0]);
        vec2 ax4 = normalize(b.v[2] - b.v[1]);

        float d1 = getDistanceOnProjectedAxis(ax1, a.v, 4, b.v, 4);
        if(d1 > 0)return vec2(0);

        float d2 = getDistanceOnProjectedAxis(ax2, a.v, 4, b.v, 4);
        if(d2 > 0) return vec2(0);

        float d3 = -9999;
        float d4 = -9999;

        if(ax3 != ax1 && ax3 != ax2)
            d3 = getDistanceOnProjectedAxis(ax3, a.v, 4, b.v, 4);

        if(d3 > 0) return vec2(0);
        if(ax4 != ax1 && ax4 != ax2)
            d4 = getDistanceOnProjectedAxis(ax4, a.v, 4, b.v, 4);
        if(d4 > 0) return vec2(0);

        //collision

        vec2 delta = normalize(d.transform->position - s.transform->position);

        d1 = -d1;
        d2 = -d2;
        d3 = -d3;
        d4 = -d4;

        //return the smallest overlap (dot(delta, ax?) is used to ensure the offset will be in the right direction)
        if(d1 < d2 && d1 < d3 && d1 < d4)
            return glm::sign(dot(delta, ax1)) * ax1 * d1;
        else if(d2 < d1 && d2 < d3 && d2 < d4)
            return glm::sign(dot(delta, ax2)) * ax2 * d2;
        else if(d3 < d1 && d3 < d2 && d3 < d4)
            return glm::sign(dot(delta, ax3)) * ax3 * d3;
        else
            return glm::sign(dot(delta, ax4)) * ax4 * d4;

    }else if(d.shape == Shape::Circle){
        Quad a = getBoxVerticesInWorld(Utility::getTransform(s.transform));
        vec2 circlePos = d.transform->position;

        vec2 ax1 = normalize(a.v[1] - a.v[0]);
        vec2 ax2 = normalize(a.v[2] - a.v[1]);
        vec2 ax3 = glm::rotate(ax1, 45.0f);
        vec2 ax4 = glm::rotate(ax2, 45.0f);
  
        vec2 cPoints1[] =
        {
            circlePos + ax1 * d.transform->scale.x,
            circlePos - ax1 * d.transform->scale.x
        };

        vec2 cPoints2[] =
        {
            circlePos + ax2 * d.transform->scale.x,
            circlePos - ax2 * d.transform->scale.x
        };

        vec2 cPoints3[] =
        {
            circlePos + ax3 * d.transform->scale.x,
            circlePos - ax3 * d.transform->scale.x
        };

        vec2 cPoints4[] =
        {
            circlePos + ax4 * d.transform->scale.x,
            circlePos - ax4 * d.transform->scale.x
        };


        float d1 = getDistanceOnProjectedAxis(ax1, a.v, 4, cPoints1, 2);
        if(d1 > 0)return vec2(0);
        float d2 = getDistanceOnProjectedAxis(ax2, a.v, 4, cPoints2, 2);
        if(d2 > 0)return vec2(0);
        float d3 = getDistanceOnProjectedAxis(ax3, a.v, 4, cPoints3, 2);
        if(d3 > 0)return vec2(0);
        float d4 = getDistanceOnProjectedAxis(ax4, a.v, 4, cPoints4, 2);
        if(d4 > 0)return vec2(0);

        vec2 delta = normalize(d.transform->position - s.transform->position);

        d1 = -d1;
        d2 = -d2;
        d3 = -d3;
        d4 = -d4;

        //return the smallest overlap (dot(delta, ax?) is used to ensure the offset will be in the right direction)
        if(d1 < d2 && d1 < d3 && d1 < d4)
            return dot(delta, ax1) * ax1 * d1;
        else if(d2 < d1 && d2 < d3 && d2 < d4)
            return dot(delta, ax2) * ax2 * d2;
        else if(d3 < d1 && d3 < d2 && d3 < d4)
            return dot(delta, ax3) * ax3 * d3;
        else
            return dot(delta, ax4) * ax4 * d4;

    }

    return vec2(0);
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
    for(int i = 0; i < 4; i++)
        quad.v[i] = vec2(worldTransform * vertices[i]);

    return quad;
}


float PhysicsSystem::getDistanceOnProjectedAxis(vec2 ax, vec2 a[], int a_length, vec2 b[], int b_length){
    //project points on axis
    float proj_a[a_length], proj_b[b_length];

    for(int i = 0; i < a_length;i++)
        proj_a[i] = dot(ax, a[i]);
    for(int i = 0; i < b_length; i++)
        proj_b[i] = dot(ax, b[i]);

    //find min max for a & b
    float min_a = proj_a[0], max_a = proj_a[0];
    float min_b = proj_b[0], max_b = proj_b[0];

    for(int i = 1; i < a_length; i++){
        if(min_a > proj_a[i])
            min_a = proj_a[i];
        if(max_a < proj_a[i])
            max_a = proj_a[i];
    }

    for(int i = 1; i < b_length; i++){
        if(min_b > proj_b[i])
            min_b = proj_b[i];
        if(max_b < proj_b[i])
            max_b = proj_b[i];
    }

    //calc length for a & b on the projected axis
    float projLength_a = max_a - min_a;
    float projLength_b = max_b - min_b;

    //calc length between extremes for a & b
    float totalLength1 = glm::max(abs(min_a - max_b), projLength_a);
    float totalLength2 = glm::max(abs(max_a - min_b), projLength_b);

    //max length
    float maxLength = glm::max(totalLength1, totalLength2);

    //return the distance(will be negative if overlapping)
    return maxLength - (projLength_a + projLength_b);
}
