#pragma once

#include <defines.h>

#include <glm/glm.hpp>

#include <core/keycodes.h>
#include <core/mousecodes.h>

class Input {
    public:
        static b8 isKeyPressed(const keyCode code);
        //static b8 isKeyJustPressed(const keyCode code);
        static b8 isMouseButtonPressed(const mouseCode code);
        //static b8 isMouseButtonJustPressed(const mouseCode code);

        static glm::vec2 getMousePos();
        static f32 getMouseX();
        static f32 getMouseY();
};
