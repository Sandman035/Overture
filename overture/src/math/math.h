#pragma once

#include <defines.h>

class Vector3 {
    public:
        f32 x, y, z;

        Vector3();
        Vector3(f32 x, f32 y, f32 z): x(x), y(y), z(z) {};

        Vector3 dot(Vector3);

        Vector3 operator+ (const Vector3& n);

        Vector3 operator- (const Vector3& n);

        template <typename type>
        Vector3 operator* (const type& n);

        template <typename type>
        Vector3 operator/ (const type& n);

        b8 operator== (const Vector3& n);

        b8 operator!= (const Vector3& n);
};

class Vector2 {
    public:
        f32 x, y;

        Vector2();
        Vector2(f32 x, f32 y): x(x), y(y) {};

        Vector2 dot(Vector2);

        Vector2 operator+ (const Vector2& n);

        Vector2 operator- (const Vector2& n);

        template <typename type>
        Vector2 operator* (const type& n);

        template <typename type>
        Vector2 operator/ (const type& n);

        b8 operator== (const Vector2& n);

        b8 operator!= (const Vector2& n);
};

class Mat4 {
	public:
		f32 matrixData[16]={0};

		Mat4() = default;
		Mat4(f32 m0,f32 m4,f32 m8,f32 m12,f32 m1,f32 m5,f32 m9,f32 m13,f32 m2,f32 m6,f32 m10,f32 m14,f32 m3,f32 m7, f32 m11,f32 m15);

		Mat4 operator= (const Mat4& n);
		f32 operator[] (const i32 n);
		Mat4 scale(const Vector3& n);
		Mat4 translate(const Vector3& n);
		Mat4 rotate(const Vector3& n);
};
