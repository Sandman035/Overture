#include <entry.h>

#include <core/log.h>
#include <core/asserts.h>
#include <math/math.h>
#include <core/event.h>

#include <platform/window.h>

void eventTest() {
    DEBUG("this fucking worked");
}

void event2() {
    DEBUG("this too works");
}

void event56() {
    DEBUG("I'm surprized");
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
    eventBus.bind("test", &eventTest);
    eventBus.bind("test", &event2);
    eventBus.bind("test2", &event56);
    eventBus.call("test");
    eventBus.call("test2");
    eventBus.call("test3");

    WindowProperties props;
    props.width = 1920;
    props.height = 1080;
    
    Window window;

    window.init(props);
    window.run();
}