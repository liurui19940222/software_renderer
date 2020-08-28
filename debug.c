#include "debug.h"
#include <stdio.h>

void log_vector(Vector3d* vec) {
	printf("[%f, %f, %f]\n", vec->x, vec->y, vec->z);
}

void log_matrix(Matrix4x4* matrix) {
	printf("[%f\t %f\t %f\t %f]\n[%f\t %f\t %f\t %f]\n[%f\t %f\t %f\t %f]\n[%f\t %f\t %f\t %f]\n",
		matrix->m[0][0], matrix->m[0][1], matrix->m[0][2], matrix->m[0][3],
		matrix->m[1][0], matrix->m[1][1], matrix->m[1][2], matrix->m[1][3],
		matrix->m[2][0], matrix->m[2][1], matrix->m[2][2], matrix->m[2][3],
		matrix->m[3][0], matrix->m[3][1], matrix->m[3][2], matrix->m[3][3]
	);
}