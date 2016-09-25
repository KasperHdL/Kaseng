#pragma once

#include "Components.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Utility{
    public:
        static mat4 getTransform(Transform* transform){

            mat4 t = translate(mat4(1), vec3(transform->position, 0));
            mat4 r = glm::rotate(t, transform->rotation, vec3(0,0,1));
            mat4 s = scale(r, vec3(transform->scale, 0.1f));

            return s;
        }


};
