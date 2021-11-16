#include <defines.h>

template <typename number>
number clamp(number n, number min, number max);

class Vector3 {
    public:
        Vector3(float x, float y, float z);
        Vector3(int x, int y, int z);

        float x;
        float y;
        float z;
};

class Vector2 {
    public:
        float x;
        float y;
};