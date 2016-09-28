#pragma once

#include "glm/glm.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Texture.hpp"
#include "SRE/Shader.hpp"
#include <map>
#include "SDL_keyboard.h"


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

//Physics Bodies
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

struct Player{
    bool left = false, right = false, jump = false;
    SDL_Keycode left_keycode,
                right_keycode,
                jump_keycode;

    float runForce = 0.2f, jumpForce = 0.5f;

    DynamicBody* body;

    Player(SDL_Keycode left, SDL_Keycode right, SDL_Keycode jump, DynamicBody* body)
        :left_keycode(left), right_keycode(right), jump_keycode(jump), body(body)
    {};
};

struct Quad{
    vec2 v[4];
};

