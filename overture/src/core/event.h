#pragma once

#include <defines.h>

#include <list>
#include <map>

typedef std::list<void (*)()> functionList;

class EventBus {
        void bind(const char* event, void (* function)());
        void call(const char* event); 
    private:
        std::map<const char*, functionList> bindedFunctions;
};
