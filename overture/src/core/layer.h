#pragma once

#include <defines.h>

#include <string>

class Layer {
    public:
        Layer(const std::string& name = "Layer") : name(name) {};
        virtual ~Layer() = default;

        virtual void start() {}
        virtual void update() {}
		virtual void end() {}

        const std::string& getName() const { return name; }
    
    private:
        std::string name;
};
