#pragma once

#include <defines.h>

#include <string>

class Renderer {
    public:
        virtual void init() = 0;
        virtual void shutdown() = 0;

        //virtual void onResize();
        virtual void drawFrame() = 0;

		//virtual void initTextureFromFile(const std::string& relativePath, b8 flipVertically) = 0;
};
