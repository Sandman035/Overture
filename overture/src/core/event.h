#pragma once

#include <list>
#include <map>
#include <typeindex>

class Event { 
protected: 
	virtual ~Event() {}; 
}; 

class HandlerFunctionBase { 
public: 
	virtual ~HandlerFunctionBase() {}; 
	void exec(Event* event) {call(event);} 
	
private: 
	virtual void call(Event * event) = 0; 
}; 

class MemberFunctionHandler : public HandlerFunctionBase {
    public:
        MemberFunctionHandler(void (*memberFunction)(Event*)) {_memberFunction = *memberFunction;};

        void call(Event * event) {
            (_memberFunction)(event);
        }

    private:
        void (*_memberFunction)(Event*);
};

typedef std::list<HandlerFunctionBase*> HandlerList;
class EventBus {
    public:
        template <class EventType>
        void publish(EventType * event) {
            HandlerList * handlers = subscribers[typeid(EventType)];

            for(auto & handler : *handlers) {
                if (handler != nullptr) {
                    handler->exec(event);
                }
            }
        }
        
        template<class EventType>
        void subscribe(void (*memberFunction)(EventType *)) {
            HandlerList * handlers = subscribers[typeid(EventType)];

            if(handlers == nullptr) {
                handlers = new HandlerList();
                subscribers[typeid(EventType)] = handlers;
            }
            MemberFunctionHandler thingy((const MemberFunctionHandler &)memberFunction);
            handlers->push_back((HandlerFunctionBase *)&thingy);
        }
    private:
        std::map<std::type_index, HandlerList*> subscribers;
};