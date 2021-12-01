#include <core/log.h>
#include <core/asserts.h>
#include <math/math.h>

int main(int argc, char const *argv[])
{
    Vector3 thing(5.0f, 4.0f, 3.0f);
    Vector3 thing2(2.0f, 1.0f, 0.0f);
    Vector3 thing3 = thing + thing2;
    thing3 = thing3 * 2;

    DEBUG("%f, %f, %f", thing3.x, thing3.y, thing3.z);

    if(Vector3(0.0f, 0.0f, 0.0f) == Vector3(0.0f, 0.0f, 0.0f))
        DEBUG("equal");
    if (Vector3(1.0f, 0.0f, 0.0f) != Vector3(0.0f, 0.0f, 0.0f))
        DEBUG("not equal")

    return 0;
}
