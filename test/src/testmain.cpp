#include <test.h>
#include <core/log.h>

int main(int argc, char const *argv[])
{
    doshit();
    FATAL("hi");
    ERROR("hello");
    WARN("Wasup");
    INFO("hello, world!");
    DEBUG("triangle");
    TRACE("what?");
    return 0;
}
