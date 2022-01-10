#pragma once

class Renderer {
    public:
        void init();
        void shutdown();

        void onResize();
        void drawFrame();
};
