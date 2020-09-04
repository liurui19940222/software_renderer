#pragma once

#define _PI_ 3.1415926535f
#define _DEG_2_RAD_ (_PI_ / 180.0f)
#define _RAD_2_DEG_ (180.0f / _PI_)
#define _Round_F_(fvalue) (int)(fvalue + 0.5f)

typedef struct S_Vector2d {
	union {
		float m[2];
		struct {
			float x, y;
		};
	};
} Vector2d;


typedef struct S_Vector3d {
	union {
		float m[3];
		struct {
			float x, y, z;
		};
	};
} Vector3d;


const Vector3d vector3_one;
const Vector3d vector3_up;
const Vector3d vector3_down;

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

typedef struct S_Color
{
	union {
		float m[4];
		struct {
			float a, r, g, b;
		};
	};
} Color;

struct Vertex;

#pragma region Vector3d

void vector3_makezero(Vector3d* a);

Vector3d vector3_negative(Vector3d a);

void vector3_swap(Vector3d* a, Vector3d* b);

Vector3d vector3_add(Vector3d a, Vector3d b);

Vector3d vector3_minus(Vector3d a, Vector3d b);

float vector3_dot(Vector3d a, Vector3d b);

Vector3d vector3_cross(Vector3d a, Vector3d b);

float vector3_cross2d(Vector3d a, Vector3d b);

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

#pragma region Color

int color_toInteger(Color color);

Color color_fromInteger(int icolor);

#pragma endregion


#pragma region Helper

inline float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

inline float clamp(float a, float min, float max) {
	a = a < min ? min : a;
	return a > max ? max : a;
}

float crossProduct2d(float x0, float y0, float x1, float y1);

void computeMassCoordinate(Vector3d* triangle, Vector3d coord, float* i, float* j, float* k);

float fdistance(float a, float b);

void transform_viewport(Vector3d ndcCoordination, float screenHalfWidth, float screenHalfHeight, Vector3d* result);

#pragma endregion 


