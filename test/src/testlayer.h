#pragma once

#include <core/layer.h>
#include <renderer/Vulkan/vulkan_renderer.h>

class TestLayer : public Layer {
    public:
        TestLayer();
        virtual ~TestLayer() = default;

        void update() override;

        void start() override;

		VulkanRenderer renderer;
};
