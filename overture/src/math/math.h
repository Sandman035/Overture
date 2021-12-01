#pragma once

#include <defines.h>

class Vector3 {
    public:
        f32 x, y, z;

        Vector3();
        Vector3(f32 x, f32 y, f32 z): x(x), y(y), z(z) {};

        Vector3 dot(Vector3);

        Vector3 operator+ (const Vector3& n) {
            return Vector3(x+n.x, y+n.y, z+n.z);
        }

        Vector3 operator- (const Vector3& n) {
            return Vector3(x-n.x, y-n.y, z-n.z);
        }

        template <typename type>
        Vector3 operator* (const type& n) {
            return Vector3(x*(f32)n, y*(f32)n, z*(f32)n);
        }

        template <typename type>
        Vector3 operator/ (const type& n) {
            return Vector3(x/(float)n, y/(f32)n, z/(f32)n);
        }

        b8 operator== (const Vector3& n) {
            return x==n.x && y==n.y && z==n.z;
        }

        b8 operator!= (const Vector3& n) {
            b8 value = x==n.x && y==n.y && z==n.z;
            return !value;
        }
};

class Vector2 {
    public:
        f32 x, y;

        Vector2();
        Vector2(f32 x, f32 y): x(x), y(y) {};

        Vector2 dot(Vector2);

        Vector2 operator+ (const Vector2& n) {
            return Vector2(x+n.x, y+n.y);
        }

        Vector2 operator- (const Vector2& n) {
            return Vector2(x-n.x, y-n.y);
        }

        template <typename type>
        Vector2 operator* (const type& n) {
            return Vector2(x*(f32)n, y*(f32)n);
        }

        template <typename type>
        Vector2 operator/ (const type& n) {
            return Vector2(x/(float)n, y/(f32)n);
        }

        b8 operator== (const Vector2& n) {
            return x==n.x && y==n.y;
        }

        b8 operator!= (const Vector2& n) {
            b8 value = x==n.x && y==n.y;
            return !value;
        }
};