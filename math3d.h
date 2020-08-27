#pragma once

typedef struct S_Vector3d {
	float x, y, z;
} Vector3d;

typedef struct S_Matrix4x4
{
	float m[4][4];
} Matrix4x4;

#pragma region Vector3d

void vector3_makezero(Vector3d* a);

Vector3d vector3_add(Vector3d a, Vector3d b);

Vector3d vector3_minus(Vector3d a, Vector3d b);

float vector3_dot(Vector3d a, Vector3d b);

Vector3d vector3_cross(Vector3d a, Vector3d b);

Vector3d vector3_multiply(Vector3d a, float s);

Vector3d vector3_normalize(Vector3d a);

void vector3_makeNormalized(Vector3d* a);

float vector3_magnitude(Vector3d a);

#pragma endregion

#pragma region Matrix

void matrix_makeIdentity(Matrix4x4* matrix);

void matrix_scale(Matrix4x4* matrix, float value);

void matrix_multiply(Matrix4x4* a, Matrix4x4* b, Matrix4x4* result);

#pragma endregion



