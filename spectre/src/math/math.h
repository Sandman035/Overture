#include <defines.h>

template <typename number>
number clamp(number n, number min, number max);

class Vector3 {
    public:
        f32 x, y, z;

        Vector3(f32 x, f32 y, f32 z);
};

class Vector2 {
    public:
        f32 x, y;

        Vector2(f32 x, f32 y);
};