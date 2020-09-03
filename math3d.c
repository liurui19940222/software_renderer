#include "math3d.h"
#include "debug.h"
#include <math.h>
#include <windows.h>
#include <stdio.h>

#pragma region Vector3d

const Vector3d vector3_one = { 1.0f, 1.0f, 1.0f };
const Vector3d vector3_up = { 0.0f, 1.0f, 0.0f };
const Vector3d vector3_down = { 0.0f, -1.0f, 0.0f };

void vector3_makezero(Vector3d* a) {
	a->x = 0; a->y = 0; a->z = 0;
}

Vector3d vector3_negative(Vector3d a) {
	Vector3d v = { -a.x, -a.y, -a.z };
	return v;
}

void vector3_swap(Vector3d* a, Vector3d* b) {
	float temp = a->x;
	a->x = b->x;
	b->x = temp;
	temp = a->y;
	a->y = b->y;
	b->y = temp;
	temp = a->z;
	a->z = b->z;
	b->z = temp;
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

void homogeneous2vector3(Vector4d* v4, Vector3d* v3) {
	float qw = 1.0f / v4->w;
	v3->x = v4->x * qw;
	v3->y = v4->y * qw;
	v3->z = v4->z * qw;
}

#pragma endregion

#pragma region Matrix

void matrix_makeIdentity(Matrix4x4* matrix) {
	memset(matrix, 0, sizeof(Matrix4x4));
	matrix->m[0][0] = 1;
	matrix->m[1][1] = 1;
	matrix->m[2][2] = 1;
	matrix->m[3][3] = 1;
}

void matrix_makeTransport(Matrix4x4* matrix) {
	float temp;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			temp = matrix->m[i][j];
			matrix->m[i][j] = matrix->m[j][i];
			matrix->m[j][i] = temp;
		}
	}
}

void matrix_transpose(Matrix4x4* matrix, Matrix4x4* result) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result->m[i][j] = matrix->m[j][i];
		}
	}
}

void matrix_multiplyValue(Matrix4x4* matrix, float value) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrix->m[i][j] *= value;
		}
	}
}

void matrix_transformPoint(Matrix4x4* matrix, Vector3d point, Vector3d* result) {
	Vector4d homo;
	homo.x = matrix->m[0][0] * point.x + matrix->m[0][1] * point.y + matrix->m[0][2] * point.z + matrix->m[0][3];
	homo.y = matrix->m[1][0] * point.x + matrix->m[1][1] * point.y + matrix->m[1][2] * point.z + matrix->m[1][3];
	homo.z = matrix->m[2][0] * point.x + matrix->m[2][1] * point.y + matrix->m[2][2] * point.z + matrix->m[2][3];
	homo.w = matrix->m[3][0] * point.x + matrix->m[3][1] * point.y + matrix->m[3][2] * point.z + matrix->m[3][3];
	homogeneous2vector3(&homo, result);
}

void matrix_transformVector(Matrix4x4* matrix, Vector3d vector, Vector3d* result) {
	result->x = matrix->m[0][0] * vector.x + matrix->m[0][1] * vector.y + matrix->m[0][2] * vector.z;
	result->y = matrix->m[1][0] * vector.x + matrix->m[1][1] * vector.y + matrix->m[1][2] * vector.z;
	result->z = matrix->m[2][0] * vector.x + matrix->m[2][1] * vector.y + matrix->m[2][2] * vector.z;
}

void matrix_multiply(Matrix4x4* a, Matrix4x4* b, Matrix4x4* result) {
	matrix_makeIdentity(result);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result->m[i][j] = a->m[i][0] * b->m[0][j] + a->m[i][1] * b->m[1][j] + a->m[i][2] * b->m[2][j] + a->m[i][3] * b->m[3][j];
		}
	}
}

void matrix_translate(Vector3d pos, Matrix4x4* result) {
	matrix_makeIdentity(result);
	result->m[0][3] = pos.x;
	result->m[1][3] = pos.y;
	result->m[2][3] = pos.z;
}

void matrix_rotateX(float x, Matrix4x4* result) {
	float theta = x * _DEG_2_RAD_;
	float sinx = sinf(theta);
	float cosx = cosf(theta);
	matrix_makeIdentity(result);
	result->m[1][1] = cosx;
	result->m[1][2] = -sinx;
	result->m[2][1] = sinx;
	result->m[2][2] = cosx;
}

void matrix_rotateY(float y, Matrix4x4* result) {
	float theta = y * _DEG_2_RAD_;
	float siny = sinf(theta);
	float cosy = cosf(theta);
	matrix_makeIdentity(result);
	result->m[0][0] = cosy;
	result->m[0][2] = siny;
	result->m[2][0] = -siny;
	result->m[2][2] = cosy;
}

void matrix_rotateZ(float z, Matrix4x4* result) {
	float theta = z * _DEG_2_RAD_;
	float sinz = sinf(theta);
	float cosz = cosf(theta);
	matrix_makeIdentity(result);
	result->m[0][0] = cosz;
	result->m[0][1] = -sinz;
	result->m[1][0] = sinz;
	result->m[1][1] = cosz;
}

void matrix_rotate(Vector3d eulerAngles, Matrix4x4* result) {
	float thetax = eulerAngles.x * _DEG_2_RAD_;
	float thetay = eulerAngles.y * _DEG_2_RAD_;
	float thetaz = eulerAngles.z * _DEG_2_RAD_;
	float sinx = sinf(thetax);
	float cosx = cosf(thetax);
	float siny = sinf(thetay);
	float cosy = cosf(thetay);
	float sinz = sinf(thetaz);
	float cosz = cosf(thetaz);
	matrix_makeIdentity(result);
	// z->x->y
	result->m[0][0] = cosy * cosz - sinx * siny * sinz;
	result->m[0][1] = -sinz * cosx;
	result->m[0][2] = cosz * siny + sinx * sinz * cosy;
	result->m[1][0] = sinz * cosy + sinx * siny * cosz;
	result->m[1][1] = cosx * cosz;
	result->m[1][2] = siny * sinz - sinx * cosy * cosz;
	result->m[2][0] = -siny * cosx;
	result->m[2][1] = sinx;
	result->m[2][2] = cosx * cosy;

	// test
	//Matrix4x4 a, b, c, result2, result3;
	//matrix_rotateX(eulerAngles.x, &a);
	//matrix_rotateY(eulerAngles.y, &b);
	//matrix_rotateZ(eulerAngles.z, &c);
	//matrix_multiply(&c, &a, &result2);
	//matrix_multiply(&result2, &b, &result3);

	//float total = 0;
	//for (int i = 0; i < 4; ++i) {
	//	for (int j = 0; j < 4; ++j) {
	//		total += (result3.m[i][j] - result->m[i][j]);
	//	}
	//}
	//printf("offset:%f\n", total);
	//log_matrix(result);
	//log_matrix(&result3);
}

void matrix_scale(Vector3d scale, Matrix4x4* result) {
	matrix_makeIdentity(result);
	result->m[0][0] = scale.x;
	result->m[1][1] = scale.y;
	result->m[2][2] = scale.z;
}

void matrix_model(Vector3d pos, Vector3d eulerAngles, Vector3d scale, Matrix4x4* result) {
	Matrix4x4 m1, m2, m3;
	matrix_rotate(eulerAngles, &m1);
	matrix_scale(scale, &m2);
	matrix_multiply(&m1, &m2, &m3);
	matrix_translate(pos, &m1);
	matrix_multiply(&m1, &m3, result);
}

void matrix_view(Vector3d eyePos, Vector3d eyeForward, Vector3d eyeUpward, Matrix4x4* result) {
	Matrix4x4 translate, rotate;
	eyePos = vector3_negative(eyePos);
	vector3_makeNormalized(&eyeForward);
	vector3_makeNormalized(&eyeUpward);
	Vector3d eyeRightward = vector3_cross(eyeUpward, eyeForward);
	vector3_makeNormalized(&eyeRightward);
	eyeUpward = vector3_cross(vector3_negative(eyeRightward), eyeForward);
	vector3_makeNormalized(&eyeUpward);
	matrix_makeIdentity(&rotate);
	rotate.m[0][0] = eyeRightward.x;
	rotate.m[0][1] = eyeRightward.y;
	rotate.m[0][2] = eyeRightward.z;
	rotate.m[1][0] = eyeUpward.x;
	rotate.m[1][1] = eyeUpward.y;
	rotate.m[1][2] = eyeUpward.z;
	rotate.m[2][0] = eyeForward.x;
	rotate.m[2][1] = eyeForward.y;
	rotate.m[2][2] = eyeForward.z;
	matrix_translate(eyePos, &translate);
	matrix_multiply(&rotate, &translate, result);
}

void matrix_orthographic(float top, float bottom, float left, float right, float planeNear, float planeFar, Matrix4x4* result) {
	matrix_makeIdentity(result);
	float w = right - left;
	float h = top - bottom;
	float depth = planeFar - planeNear;
	result->m[0][0] = 2.0f / w;
	result->m[1][1] = 2.0f / h;
	result->m[2][2] = 1.0f / depth;
	result->m[0][3] = -(left + right) / w;
	result->m[1][3] = -(top + bottom) / h;
	result->m[2][3] = -planeNear / depth;
}

void matrix_ortho2d(float size, float aspect, float planeNear, float planeFar, Matrix4x4* result) {
	float halfWidth = size * aspect;
	float halfHeight = size;
	matrix_orthographic(halfHeight, -halfHeight, -halfWidth, halfWidth, planeNear, planeFar, result);
}

void matrix_perspective(float fov, float aspect, float planeNear, float planeFar, Matrix4x4* result) {
	matrix_makeIdentity(result);
	float cota = 1.0f / tanf(fov * 0.5f);
	float depth = planeFar - planeNear;
	result->m[0][0] = (1.0f / aspect) * cota;
	result->m[1][1] = cota;
	result->m[2][2] = planeFar / depth;
	result->m[2][3] = -planeFar * planeNear / depth;
	result->m[3][2] = 1.0f;
}

void matrix_mvp(Matrix4x4* m, Matrix4x4* v, Matrix4x4* p, Matrix4x4* mvp) {
	matrix_makeIdentity(mvp);
	Matrix4x4 vp;
	matrix_multiply(p, v, &vp);
	matrix_multiply(&vp, m, mvp);
}

#pragma endregion

#pragma region Color

int color_toInteger(Color color) {
	int a = (int)(color.a * 255.0f);
	int r = (int)(color.r * 255.0f);
	int g = (int)(color.g * 255.0f);
	int b = (int)(color.b * 255.0f);
	return (a << 24) | ((r << 16) & 0xFF0000) | ((g << 8) & 0xFF00) | (b & 0xFF);
}

#define _REC_255_ 0.0039216f

Color color_fromInteger(int icolor) {
	Color color = {
		(icolor >> 24) * _REC_255_,
		((icolor >> 16) & 0xFF) * _REC_255_,
		((icolor >> 8) & 0xFF) * _REC_255_,
		(icolor & 0xFF) * _REC_255_
	};
	return color;
}

#pragma endregion

#pragma region Helper

float fdistance(float a, float b) {
	return a > b ? (a - b) : (b - a);
}

void transform_viewport(Vector3d ndcCoordination, float screenHalfWidth, float screenHalfHeight, Vector3d* result) {
	result->x = ndcCoordination.x * screenHalfWidth + screenHalfWidth;
	result->y = ndcCoordination.y * screenHalfHeight + screenHalfHeight;
}

#pragma endregion 