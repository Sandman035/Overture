#pragma once

#include <core/layer.h>

class TestLayer : public Layer {
    public:
        TestLayer();
        virtual ~TestLayer() = default;

        void update() override;

        void start() override;
};
