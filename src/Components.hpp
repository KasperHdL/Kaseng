#pragma once

#include "glm/glm.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Texture.hpp"
#include "SRE/Shader.hpp"


using namespace glm;
using namespace SRE;

enum Shape{
    Box,
    Circle
};


struct Transform{
    vec2 position;
    vec2 scale;
    float rotation;

    Transform(vec2 position, vec2 scale, float rotation = 0)
        :position(position), scale(scale), rotation(rotation)
    {};
};

struct DynamicBody{
    Transform* transform;
    Shape shape;

    vec2 velocity;
    float rotationVelocity;
    
    float mass;
    float friction;

    vec2 acceleration;
    float rotationAcceleration;

    DynamicBody(Transform* transform,Shape shape = Shape::Box, float mass = 1, float friction = 0.95)
        :transform(transform), shape(shape), mass(mass), friction(friction), acceleration(vec2(0)), velocity(vec2(0)), rotationAcceleration(0), rotationVelocity(0)
    {};
};

struct StaticBody{
    Transform* transform;
    Shape shape;

    float friction;

    StaticBody(Transform* transform, Shape shape = Shape::Box, float friction = 0.95)
        :transform(transform), shape(shape), friction(friction)
    {};

};

struct RenderEntity{
    Transform* transform;
    Shape shape;
    vec4 color;
 
    RenderEntity(Transform* transform, Shape shape, vec4 color)
        :transform(transform), shape(shape), color(color)
    {};
};


struct Quad{
    vec2 v[4];
};

struct Edge{
    vec2 from;
    vec2 to;
    vec2 normal;
};
