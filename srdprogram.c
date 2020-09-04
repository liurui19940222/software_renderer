#pragma once

#include <windows.h>
#include <stdio.h>
#include "srdprogram.h"
#include "math3d.h"
#include "geometry.h"
#include "input.h"
#include "pipeline.h"

Vertex* mesh;
int triangleSize = sizeof(Vertex) * 3;
int triCount;

void program_init() {
	mesh = triangle;
	triCount = sizeof(triangle) / triangleSize;

	Vector3d p = { 0.6f, 0.85f, 0 };
	Vector3d tri[3] = { triangle[0].position, triangle[1].position, triangle[2].position };
	float i, j, k;
	computeMassCoordinate(tri, p, &i, &j, &k);
	Vector3d q = vector3_add(vector3_multiply(tri[0], i), vector3_multiply(tri[1], j));
	q = vector3_add(q, vector3_multiply(tri[2], k));
}

Vector3d euler = { 0, 0, 0 };

void program_render(Renderer* rd) {
	float halfW = rd->surface->width * 0.5f, halfH = rd->surface->height * 0.5f;
	float aspect = halfW / halfH;
	//euler.x += 0.16f;
	//euler.y += 0.16f;
	//euler.z += 0.16f;
	
	//if (input_isKeyPressed('A')) {z
	//	angle += 0.16;
	//}
	//if (input_isKeyPressed('D')) {
	//	angle -= 0.16;
	//}

	if (input_getKeyDown('W')) {
		if (srd_isEnabled(rd->context, SRD_WIRE_MODE)) {
			srd_disable(rd->context, SRD_WIRE_MODE);
		}
		else {
			srd_enable(rd->context, SRD_WIRE_MODE);
		}
	}

	Vector3d eyePos = { 0.0f, 3.0f, -5.0f };
	Vector3d eyeForward = { 0.0f, -0.6f, 1.0f };
	Vector3d eyeUpward = { 0.0f, 1.0f, 0.0f };
	Matrix4x4 m, v, p;
	matrix_rotate(euler, &m);
	matrix_view(eyePos, eyeForward, eyeUpward, &v);
	matrix_perspective(45, aspect, 0.0f, 100.0f, &p);
	//matrix_ortho2d(1.0f, aspect, 1.0f, 0.1f, &p);
	srd_setMVP(rd->context, &m, &v, &p);

	pipe_postMesh(rd, mesh, triCount);
}
