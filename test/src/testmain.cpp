#include <test.h>
#include <core/log.h>
#include <core/asserts.h>

int main(int argc, char const *argv[])
{
    doshit();
    FATAL("hi");
    ERROR("hello");
    WARN("Wasup");
    INFO("hello, world!");
    DEBUG("triangle");
    TRACE("what?");

    ASSERT_MSG(1 == 0, "wtf is wrong with you");

    return 0;
}
