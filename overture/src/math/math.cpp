#include <math/math.h>
#include <core/log.h>

Vector3 Vector3::operator+ (const Vector3& n) {
	return Vector3(x+n.x, y+n.y, z+n.z);
}

Vector3 Vector3::operator- (const Vector3& n) {
	return Vector3(x-n.x, y-n.y, z-n.z);
}

template <typename type>
Vector3 Vector3::operator* (const type& n) {
	return Vector3(x*(f32)n, y*(f32)n, z*(f32)n);
}

template <typename type>
Vector3 Vector3::operator/ (const type& n) {
	return Vector3(x/(f32)n, y/(f32)n, z/(f32)n);
}

b8 Vector3::operator== (const Vector3& n) {
	return x==n.x && y==n.y && z==n.z;
}

b8 Vector3::operator!= (const Vector3& n) {
	b8 value = x==n.x && y==n.y && z==n.z;
	return !value;
}

Vector2 Vector2::operator+ (const Vector2& n) {
	return Vector2(x+n.x, y+n.y);
}

Vector2 Vector2::operator- (const Vector2& n) {
	return Vector2(x-n.x, y-n.y);
}

template <typename type>
Vector2 Vector2::operator* (const type& n) {
	return Vector2(x*(f32)n, y*(f32)n);
}

template <typename type>
Vector2 Vector2::operator/ (const type& n) {
	return Vector2(x/(f32)n, y/(f32)n);
}

b8 Vector2::operator== (const Vector2& n) {
	return x==n.x && y==n.y;
}

b8 Vector2::operator!= (const Vector2& n) {
	b8 value = x==n.x && y==n.y;
	return !value;
}

Mat4::Mat4(f32 m0,f32 m4,f32 m8,f32 m12,f32 m1,f32 m5,f32 m9,f32 m13,f32 m2,f32 m6,f32 m10,f32 m14,f32 m3,f32 m7, f32 m11,f32 m15) {
	matrixData[0]=m0;
    matrixData[4]=m4;
    matrixData[8]=m8;
    matrixData[12]=m12;
    
    matrixData[1]=m1;
    matrixData[5]=m5;
    matrixData[9]=m9;
    matrixData[13]=m13;
    
    matrixData[2]=m2;
    matrixData[6]=m6;
    matrixData[10]=m10;
    matrixData[14]=m14;
    
    matrixData[3]=m3;
    matrixData[7]=m7;
    matrixData[11]=m11;
    matrixData[15]=m15;
}

Mat4 Mat4::operator= (const Mat4& n) {
	for (int i = 0; 1 < 16; i++) {
		matrixData[i]=n.matrixData[i];
		DEBUG("%f", n.matrixData[i]);
		DEBUG("%f", matrixData[i]);
	}

	return *this;
}

f32 Mat4::operator[](const i32 n) {
	return matrixData[n];
}

//TODO: fix this
Mat4 Mat4::scale(const Vector3& n) {
	matrixData[0] *= n.x;
	matrixData[5] *= n.y;
	matrixData[10] *= n.z;
	return *this;
}

Mat4 Mat4::translate(const Vector3& n) {
	matrixData[12] +=  n.x;
	matrixData[13] += n.y;
	matrixData[14] += n.z;
	return *this;
}

//TODO: figure this out
Mat4 Mat4::rotate(const Vector3& n) {
	return *this;
}
