#include "math3d.h"
#include "debug.h"
#include <math.h>
#include <windows.h>
#include <stdio.h>

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
	matrix->m[0][0] = 1;
	matrix->m[1][1] = 1;
	matrix->m[2][2] = 1;
	matrix->m[3][3] = 1;
}

void matrix_makeTransport(Matrix4x4* matrix) {
	int temp;
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

void matrix_multiply(Matrix4x4* a, Matrix4x4* b, Matrix4x4* result) {
	/*
		c.m00 = a.m00 x b.m00 + a.m01 x b.m10 + a.m02 x b.m20 + a.m03 x b.m30
		c.m01 = a.m00 x b.m01 + a.m01 x b.m11 + a.m02 x b.m21 + a.m03 x b.m31
		c.m02 = a.m00 x b.m02 + a.m01 x b.m12 + a.m02 x b.m22 + a.m03 x b.m32

		c.m10 = a.m10 x b.m00 + a.m11 x b.m10 + a.m12 x b.m20 + a.m13 x b.m30
		c.m20 = a.m20 x b.m00 + a.m21 x b.m10 + a.m22 x b.m20 + a.m23 x b.m30

		c.mij = a.mi0 x b.m0j + a.mi1 x b.m1j + a.mi2 x b.m2j + a.mi3 x b.m3j
	*/
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
	float sinx = sinf(x);
	float cosx = cosf(x);
	matrix_makeIdentity(result);
	result->m[1][1] = cosx;
	result->m[1][2] = -sinx;
	result->m[2][1] = sinx;
	result->m[2][2] = cosx;
}

void matrix_rotateY(float y, Matrix4x4* result) {
	float siny = sinf(y);
	float cosy = cosf(y);
	matrix_makeIdentity(result);
	result->m[0][0] = cosy;
	result->m[0][2] = siny;
	result->m[2][0] = -siny;
	result->m[2][2] = cosy;
}

void matrix_rotateZ(float z, Matrix4x4* result) {
	float sinz = sinf(z);
	float cosz = cosf(z);
	matrix_makeIdentity(result);
	result->m[0][0] = cosz;
	result->m[0][1] = -sinz;
	result->m[1][0] = sinz;
	result->m[1][1] = cosz;
}

void matrix_rotate(Vector3d eulerAngles, Matrix4x4* result) {
	matrix_makeIdentity(result);
	float sinx = sinf(eulerAngles.x);
	float cosx = cosf(eulerAngles.x);
	float siny = sinf(eulerAngles.y);
	float cosy = cosf(eulerAngles.y);
	float sinz = sinf(eulerAngles.z);
	float cosz = cosf(eulerAngles.z);
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
	Vector3d negative = { -eyePos.x, -eyePos.y, -eyePos.z };
	vector3_makeNormalized(&eyeForward);
	vector3_makeNormalized(&eyeUpward);
	Vector3d eyeRightward = {0, 0, 0};
	vector3_cross(eyeUpward, eyeForward, &eyeRightward);
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
	matrix_translate(negative, &translate);
	matrix_multiply(&rotate, &translate, result);
}

void matrix_perspective(float fov, float aspect, float planeNear, float planeFar, Matrix4x4* result) {

}

void matrix_orthographic(float top, float bottom, float left, float right, float front, float back, Matrix4x4* result) {
	matrix_makeIdentity(result);
	float w = right - left;
	float h = top - bottom;
	float depth = front - back;
	result->m[0][0] = 2.0f / w;
	result->m[1][1] = 2.0f / h;
	result->m[2][2] = 1.0f / depth;
	result->m[0][3] = -(left + right) / w;
	result->m[1][3] = -(top + bottom) / h;
	result->m[2][3] = -back / depth;
}

void matrix_mvp(Matrix4x4* m, Matrix4x4* v, Matrix4x4* p, Matrix4x4* mvp) {
	Matrix4x4 vp;
	matrix_multiply(p, v, &vp);
	matrix_multiply(&vp, m, &mvp);
}

#pragma endregion