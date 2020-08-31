#pragma once

typedef struct S_Vector3d {
	union {
		float m[3];
		struct {
			float x, y, z;
		};
	};
} Vector3d;

typedef struct S_Vector4d {
	union {
		float m[4];
		struct {
			float x, y, z, w;
		};
	};
} Vector4d;


typedef struct S_Matrix4x4
{
	float m[4][4];
} Matrix4x4;

#pragma region Vector3d

void vector3_makezero(Vector3d* a);

void vector3_swap(Vector3d* a, Vector3d* b);

Vector3d vector3_add(Vector3d a, Vector3d b);

Vector3d vector3_minus(Vector3d a, Vector3d b);

float vector3_dot(Vector3d a, Vector3d b);

Vector3d vector3_cross(Vector3d a, Vector3d b);

Vector3d vector3_multiply(Vector3d a, float s);

Vector3d vector3_normalize(Vector3d a);

void vector3_makeNormalized(Vector3d* a);

float vector3_magnitude(Vector3d a);

void homogeneous2vector3(Vector4d* v4, Vector3d* v3);

#pragma endregion

#pragma region Matrix

void matrix_makeIdentity(Matrix4x4* matrix);

void matrix_makeTransport(Matrix4x4* matrix);

void matrix_transpose(Matrix4x4* matrix, Matrix4x4* result);

void matrix_multiplyValue(Matrix4x4* matrix, float value);

void matrix_transformPoint(Matrix4x4* matrix, Vector3d point, Vector3d* result);

void matrix_transformVector(Matrix4x4* matrix, Vector3d vector, Vector3d* result);

void matrix_multiply(Matrix4x4* a, Matrix4x4* b, Matrix4x4* result);

void matrix_translate(Vector3d pos, Matrix4x4* result);

void matrix_rotateX(float x, Matrix4x4* result);

void matrix_rotateY(float y, Matrix4x4* result);

void matrix_rotateZ(float z, Matrix4x4* result);

void matrix_rotate(Vector3d eulerAngles, Matrix4x4* result);

void matrix_scale(Vector3d scale, Matrix4x4* result);

void matrix_model(Vector3d pos, Vector3d eulerAngles, Vector3d scale, Matrix4x4* result);

void matrix_view(Vector3d eyePos, Vector3d eyeForward, Vector3d eyeUpward, Matrix4x4* result);

void matrix_perspective(float fov, float aspect, float planeNear, float planeFar, Matrix4x4* result);

void matrix_orthographic(float top, float bottom, float left, float right, float planeNear, float planeFar, Matrix4x4* result);

void matrix_ortho2d(float size, float aspect, float planeNear, float planeFar, Matrix4x4* result);

void matrix_mvp(Matrix4x4* m, Matrix4x4* v, Matrix4x4* p, Matrix4x4* mvp);

#pragma endregion

#pragma region Helper

float fdistance(float a, float b);

void transform_viewport(Vector3d ndcCoordination, float screenHalfWidth, float screenHalfHeight, Vector3d* result);

#pragma endregion 


