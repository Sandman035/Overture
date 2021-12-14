#include <entry.h>

#include <core/log.h>
#include <core/asserts.h>
#include <math/math.h>
#include <core/event.h>

class TestEvent : public Event {
    public:
        //TestEvent();
};

void onTestEvent(TestEvent * event) {
    DEBUG("hello there");
}

void test(TestEvent * event) {
    DEBUG("hello again");
}

void applicationLoop()
{
    Vector3 thing(5.0f, 4.0f, 3.0f);
    Vector3 thing2(2.0f, 1.0f, 0.0f);
    Vector3 thing3 = thing + thing2;
    thing3 = thing3 * 2;

    TRACE("%f, %f, %f", thing3.x, thing3.y, thing3.z);

    if(Vector3(0.0f, 0.0f, 0.0f) == Vector3(0.0f, 0.0f, 0.0f))
        ERROR("equal");
    if (Vector3(1.0f, 0.0f, 0.0f) != Vector3(0.0f, 0.0f, 0.0f))
        DEBUG("not equal");
    
    FATAL("hello");
    WARN("hi");
    INFO("fish");
    
    EventBus eventBus;
    eventBus.subscribe(&onTestEvent);
    eventBus.subscribe(&test);
    eventBus.publish(new TestEvent);
}
