#pragma once

#include <defines.h>

#include <math/math.h>
#include <core/keycodes.h>
#include <core/mousecodes.h>

class Input {
    public:
        static b8 isKeyPressed(const keyCode code);
        //static b8 isKeyJustPressed(const keyCode code);
        static b8 isMouseButtonPressed(const mouseCode code);
        //static b8 isMouseButtonJustPressed(const mouseCode code);

        static Vector2 getMousePos();
        static f32 getMouseX();
        static f32 getMouseY();
};