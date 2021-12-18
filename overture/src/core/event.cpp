#include <core/event.h>

void EventBus::bind(const char* event, void (*function)()) {
    bindedFunctions[event].push_back(function);
}

void EventBus::call(const char* event) {
    for (auto & i : bindedFunctions[event]) {
        i();
    }
}