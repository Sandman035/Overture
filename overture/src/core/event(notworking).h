#pragma once

#include <defines.h>

#include <list>
#include <map>
#include <typeindex>

class Event {
    protected:
        virtual ~Event();
};

class HandlerFunctionBase {
    public:
        void exec(Event * event) {
            call(event);
        }
    private:
        virtual void call(Event * event) = 0;
};

template <class EventType, class MemberFunction>
class MemberFunctionHandler : public HandlerFunctionBase {
    public:
        MemberFunctionHandler(MemberFunction memberFunction) {_memberFunction = memberFunction;};

        void call(Event * event) {
            (_memberFunction)(static_cast<EventType*>(event));
        }
    
    private:
        MemberFunction _memberFunction;
};

typedef std::list<HandlerFunctionBase*> HandlerList;
class EventBus {
    public:
        template <class EventType>
        void publish(EventType * event) {
            HandlerList * handlers = subscribers[typeid(EventType)];

            if (handlers == nullptr) {
                return;
            }

            for (auto & handler : *handlers) {
                if (handler != nullptr) {
                    handler->exec(event);
                }
            }
        }

        template<class EventType>
        void subscribe(void (memberFunction)(EventType *)) {
            HandlerList * handlers = subscribers[typeid(EventType)];

            if(handlers == nullptr) {
                handlers = new HandlerList();
                subscribers[typeid(EventType)] = handlers;
            }
            MemberFunctionHandler <EventType, void (*)(EventType *)>thingy(memberFunction);
            handlers->push_back(&thingy);
        }
    private:
        std::map<std::type_index, HandlerList*> subscribers;
};