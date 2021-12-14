#pragma once

#include <defines.h>
#include <core/log.h>

#include <iostream>

#include <list>
#include <typeindex>
#include <map>

class Event {
    protected:
        virtual ~Event() {};
};

struct MemberFunction
{
    void (*function)(/*have it so it can call the event*/);
};

//TODO: clean this shit up
//It's a mess because I was writing my own code and also referencing someone else non functioning code

typedef std::list<MemberFunction*> HandlerList;
class EventBus {
    public:
        template<class EventType>
        void publish(EventType * event) {
            HandlerList handlers = subscribers[typeid(EventType)];

            for(auto const i : handlers) { //Get Segfault here! for list?
                //handlers->function(event);
                DEBUG("function executed!"); 
            }
        }
        
        template<class EventType>
        void subscribe(void (*memberFunction)(EventType *)) {
            HandlerList * handlers = &subscribers[typeid(EventType)];

            if(handlers == nullptr) {
                handlers = new HandlerList;
                subscribers[typeid(EventType)] = *handlers;
            }
            MemberFunction *_memberFunction;
            //_memberFunction->function = memberFunction;
            handlers->push_back(_memberFunction);
            subscribers[typeid(EventType)] = *handlers;
        }
    private:
        std::map<std::type_index, HandlerList> subscribers;
};