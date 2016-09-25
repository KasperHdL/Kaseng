#pragma once

#include "Components.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Utility{
    public:
        static mat4 getTransform(Transform* transform){

            mat4 t = translate(mat4(1), vec3(transform->position, 0));
            //TODO add rotation
            mat4 s = scale(t, vec3(transform->scale, 0.1f));

            return s;
        }


};
