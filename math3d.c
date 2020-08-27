#include "math3d.h"
#include <math.h>
#include <windows.h>

#pragma region Vector3d

void vector3_makezero(Vector3d* a) {
	a->x = 0; a->y = 0; a->z = 0;
}

Vector3d vector3_add(Vector3d a, Vector3d b) {
	Vector3d v = { a.x + b.x, a.y + b.y, a.z + b.z };
	return v;
}

Vector3d vector3_minus(Vector3d a, Vector3d b) {
	Vector3d v = { a.x - b.x, a.y - b.y, a.z - b.z };
	return v;
}

float vector3_dot(Vector3d a, Vector3d b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3d vector3_cross(Vector3d a, Vector3d b) {
	Vector3d v = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
	return v;
}

Vector3d vector3_multiply(Vector3d a, float s) {
	Vector3d v = { a.x * s, a.y * s, a.z * s };
	return v;
}

Vector3d vector3_normalize(Vector3d a) {
	float a_magnitute = 1.0f / vector3_magnitude(a);
	Vector3d v = { a.x * a_magnitute, a.y * a_magnitute, a.z * a_magnitute };
	return v;
}

void vector3_makeNormalized(Vector3d* a) {
	float a_magnitute = 1.0f / vector3_magnitude(*a);
	a->x *= a_magnitute;
	a->y *= a_magnitute;
	a->z *= a_magnitute;
}

float vector3_magnitude(Vector3d a) {
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

#pragma endregion

#pragma region Matrix

void matrix_makeIdentity(Matrix4x4* matrix) {
	memset(matrix, 0, sizeof(Matrix4x4));
}

void matrix_scale(Matrix4x4* matrix, float value) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrix->m[i][j] *= value;
		}
	}
}

void matrix_multiply(Matrix4x4* a, Matrix4x4* b, Matrix4x4* result) {
	/*
		c.m00 = a.m00 x b.m00 + a.m01 x b.m10 + a.m02 x b.m20 + a.m03 x b.m30
		c.m01 = a.m00 x b.m01 + a.m01 x b.m11 + a.m02 x b.m21 + a.m03 x b.m31
		c.m02 = a.m00 x b.m02 + a.m01 x b.m12 + a.m02 x b.m22 + a.m03 x b.m32

		c.m10 = a.m10 x b.m00 + a.m11 x b.m10 + a.m12 x b.m20 + a.m13 x b.m30
		c.m20 = a.m20 x b.m00 + a.m21 x b.m10 + a.m22 x b.m20 + a.m23 x b.m30

		c.mij = a.mi0 x b.m0j + a.mi1 x b.m1j + a.mi2 x b.m2j + a.mi3 x b.m3j
	*/
	int x, y;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result->m[i][j] = a->m[i][0] * b->m[0][j] + a->m[i][1] * b->m[1][j] + a->m[i][2] * b->m[2][j] + a->m[i][3] * b->m[3][j];
		}
	}
}

#pragma endregion