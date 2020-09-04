#include "pipeline.h"
#include "renderer.h"


#pragma region Processing

void vertexShading(const Renderer* rd, const Vertex* input, Vertex* outPut) {
	matrix_transformPoint(&rd->context->mvp, input->position, &(outPut->position));
	outPut->color = input->color;
}

int fragmentShading(const Renderer* rd, const Fragment* input) {
	return color_toInteger(input->color);
}

#pragma endregion

#pragma region Helper

void computeVertexMassCoordinate(Vertex* triangle, Vector3d coord, float* i, float* j, float* k) {
	Vector3d edge0 = vector3_minus(triangle[1].position, triangle[0].position);
	Vector3d edge1 = vector3_minus(triangle[2].position, triangle[1].position);
	Vector3d edge2 = vector3_minus(triangle[0].position, triangle[2].position);
	float rec_area_x_2 = 1.0f / vector3_cross2d(edge0, edge1);
	*i = vector3_cross2d(vector3_minus(triangle[1].position, coord), edge1) * rec_area_x_2;
	*j = vector3_cross2d(vector3_minus(triangle[2].position, coord), edge2) * rec_area_x_2;
	*k = 1 - *i - *j;
}

void lerpColorWithZ(Color* a, float rec_az, Color* b, float rec_bz, Color* c, float rec_cz, float t) {
	float minus_t = 1 - t;
	c->a = rec_cz * (a->a * rec_az * minus_t + b->a * rec_bz * t);
	c->r = rec_cz * (a->r * rec_az * minus_t + b->r * rec_bz * t);
	c->g = rec_cz * (a->g * rec_az * minus_t + b->g * rec_bz * t);
	c->b = rec_cz * (a->b * rec_az * minus_t + b->b * rec_bz * t);
}

void lerpColorABC(Color* a, Color* b, Color* c, float i, float j, float k, Color* d) {
	d->a = a->a * i + b->a * j + c->a * k;
	d->r = a->r * i + b->r * j + c->r * k;
	d->g = a->g * i + b->g * j + c->g * k;
	d->b = a->b * i + b->b * j + c->b * k;
}

void swapVertex(Vertex* v0, Vertex* v1) {
	Vertex temp = *v0;
	*v0 = *v1;
	*v1 = temp;
}

void setHorizontalLine(int* pixels, void* zbuffer, int pipepleLineState, int x0, int x1, int y, int width, int height, int color) {
	if (x0 < 0) x0 = 0;
	if (x0 >= width) x0 = width - 1;
	for (int x = x0; x <= x1; ++x) {
		pixels[(height - y) * width + x] = color;
	}
}

void drawPixel(Renderer* rd, int x, int y, float z, const Fragment* frag) {
	int width = rd->surface->width, height = rd->surface->height;
	if (rd->surface->zbuffer[y * width + x] < z)
		return;
	rd->surface->zbuffer[y * width + x] = z;
	rd->surface->pixels[(height - y) * width + x] = fragmentShading(rd, frag);
}

void drawline(Renderer* rd, Vertex* vertices) {
	Surface* surface = rd->surface;
	int* pixels = (int*)rd->surface->pixels;
	int width = surface->width;
	int height = surface->height;
	float pixelx, pixely, rec_z, t;
	Fragment fragment;
	Vector3d p0, p1;
	if (fdistance(vertices[1].position.y, vertices[0].position.y) > fdistance(vertices[1].position.x, vertices[0].position.x)) {
		if (vertices[1].position.y < vertices[0].position.y) {
			swapVertex(&vertices[0], &vertices[1]);
		}
		p0 = vertices[0].position;
		p1 = vertices[1].position;
		float rec_z0 = 1.0f / p0.z;
		float rec_z1 = 1.0f / p1.z;
		float rm = (p1.x - p0.x) / (p1.y - p0.y);
		int y0 = max(0, (int)(p0.y + 0.5f));
		int y1 = min(height, (int)(p1.y + 0.5f));
		for (int x, y = y0; y < y1; ++y) {
			x = p0.x + (y - p0.y) * rm;
			if (x < 0 || x >= width)
				continue;
			t = (y - p0.y) / (p1.y - p0.y);
			rec_z = 1.0f / lerp(rec_z0, rec_z1, t);
			lerpColorWithZ(&vertices[0].color, rec_z0, &vertices[1].color, rec_z1, &fragment.color, rec_z, t);
			drawPixel(rd, x, y, rec_z, &fragment);
		}
	}
	else {
		if (vertices[1].position.x < vertices[0].position.x) {
			swapVertex(&vertices[0], &vertices[1]);
		}
		p0 = vertices[0].position;
		p1 = vertices[1].position;
		float rec_z0 = 1.0f / p0.z;
		float rec_z1 = 1.0f / p1.z;
		float m = (p1.y - p0.y) / (p1.x - p0.x);
		int x0 = max(0, (int)(p0.x + 0.5f));
		int x1 = min(surface->width, (int)(p1.x + 0.5f));
		for (int x = x0, y; x < x1; ++x) {
			y = p0.y + (x - p0.x) * m;
			if (y < 0 || y >= surface->height)
				continue;
			t = (x - p0.x) / (p1.x - p0.x);
			rec_z = 1.0f / lerp(rec_z0, rec_z1, t);
			lerpColorWithZ(&vertices[0].color, rec_z0, &vertices[1].color, rec_z1, &fragment.color, rec_z, t);
			drawPixel(rd, x, y, rec_z, &fragment);
		}
	}
}

void drawTriangleFlat(Renderer* rd, Vertex* vertices, BOOL flatTop) {
	int width = rd->surface->width, height = rd->surface->height;
	int* pixels = rd->surface->pixels;
	float m0 = (vertices[2].position.y - vertices[0].position.y) / (vertices[2].position.x - vertices[0].position.x);
	float m1 = (vertices[2].position.y - vertices[1].position.y) / (vertices[2].position.x - vertices[1].position.x);
	int x0, x1, y0, y1, xstep;
	if (flatTop) {
		y1 = min(height - 1, vertices[0].position.y);
		y0 = max(0, vertices[2].position.y);
		xstep = -1;
	}
	else {
		y0 = min(height - 1, vertices[0].position.y);
		y1 = max(0, vertices[2].position.y);
		xstep = 1;
	}
	float t, rec_z, i, j, k;
	float rec_z0 = vertices[0].position.z;
	float rec_z1 = vertices[1].position.z;
	Fragment fragment;
	Vector3d point;
	for (int y = y0 + 1; y <= y1; ++y) {
		x0 = _Round_F_((y - vertices[0].position.y) / m0 + vertices[0].position.x);
		x1 = _Round_F_((y - vertices[1].position.y) / m1 + vertices[1].position.x);
		clamp(x0, 0, width - 1);
		clamp(x1, 0, width - 1);
		for (int x = x0; x != x1; x += xstep) {
			t = (x - vertices[0].position.x) / (vertices[1].position.x - vertices[0].position.x);
			point.z = lerp(vertices[0].position.z, vertices[1].position.z, t);
			point.x = x;
			point.y = y;
			rec_z = 1.0f / lerp(rec_z0, rec_z1, t);
			computeVertexMassCoordinate(vertices, point, &i, &j, &k);
			lerpColorABC(&vertices[0].color, &vertices[1].color, &vertices[2].color, i, j, k, &fragment.color);
			pixels[(height - y) * width + x] = fragmentShading(rd, &fragment);
		}
	}
}

void drawing_drawTriangle(Renderer* rd, Vertex* vertices) {
	Vertex newVertex[3];

	// sort vertices by pos.y on the Y Axis.
	if (vertices[0].position.y < vertices[1].position.y) {
		swapVertex(&vertices[0], &vertices[1]);
	}
	if (vertices[1].position.y < vertices[2].position.y) {
		swapVertex(&vertices[1], &vertices[2]);
	}
	if (vertices[0].position.y < vertices[1].position.y) {
		swapVertex(&vertices[0], &vertices[1]);
	}

	// judge whether it a flat or uneven triangle is.
	if (vertices[0].position.y == vertices[1].position.y) {
		if (vertices[0].position.x < vertices[1].position.x) {
			swapVertex(&vertices[0], &vertices[1]);
		}
		drawTriangleFlat(rd, vertices, TRUE);
	}
	else if (vertices[1].position.y == vertices[2].position.y) {
		if (vertices[1].position.x > vertices[2].position.x) {
			swapVertex(&vertices[1], &vertices[2]);
		}
		newVertex[0] = vertices[1];
		newVertex[1] = vertices[2];
		newVertex[2] = vertices[0];
		drawTriangleFlat(rd, newVertex, FALSE);
	}
	// slice it into two flat triangles.
	else {
		Vertex insertVertex;
		float m = (vertices[2].position.y - vertices[0].position.y) / (vertices[2].position.x - vertices[0].position.x);
		Vector3d p0_2_p1 = vector3_minus(vertices[1].position, vertices[0].position);
		insertVertex.position.y = -vector3_dot(p0_2_p1, vector3_down) / vector3_dot(vector3_down, vector3_down) + vertices[0].position.y;
		insertVertex.position.x = (insertVertex.position.y - vertices[0].position.y) / m + vertices[0].position.x;
		if (vertices[1].position.x > vertices[2].position.x) {
			newVertex[0] = insertVertex;
			newVertex[1] = vertices[1];
			newVertex[2] = vertices[0];
			drawTriangleFlat(rd, newVertex, FALSE);

			newVertex[0] = vertices[1];
			newVertex[1] = insertVertex;
			newVertex[2] = vertices[2];
			drawTriangleFlat(rd, newVertex, TRUE);
		}
		else {
			newVertex[0] = vertices[1];
			newVertex[1] = insertVertex;
			newVertex[2] = vertices[0];
			drawTriangleFlat(rd, newVertex, FALSE);

			newVertex[0] = insertVertex;
			newVertex[1] = vertices[1];
			newVertex[2] = vertices[2];
			drawTriangleFlat(rd, newVertex, TRUE);
		}
	}
}

#pragma endregion


void pipe_postLine(Renderer* rd, Vertex* vertices) {
	Surface* surface = rd->surface;
	RenderingContext* context = rd->context;
	Vector3d point0, point1;
	matrix_transformPoint(&context->mvp, vertices[0].position, &point0);
	matrix_transformPoint(&context->mvp, vertices[1].position, &point1);
	transform_viewport(point0, surface->halfWidth, surface->halfHeight, &point0);
	transform_viewport(point1, surface->halfWidth, surface->halfHeight, &point1);
	drawline(surface->pixels, surface->zbuffer, context->state, surface->width, surface->height, point0, point1, color_toInteger(vertices[0].color));
}

void pipe_postMesh(Renderer* rd, Vertex* vertices, int triangleCount) {
	RenderingContext* context = rd->context;
	Surface* surface = rd->surface;
	int vertexCount = triangleCount * 3;
	Vertex* vertexShadingResult = (Vertex*)malloc(vertexCount * sizeof(Vertex));

	for (int i = 0; i < vertexCount; ++i) {
		vertexShading(rd, &vertices[i], &vertexShadingResult[i]);
		transform_viewport(vertexShadingResult[i].position, surface->halfWidth, surface->halfHeight, &(vertexShadingResult[i].position));
	}

	if (srd_isEnabled(context, SRD_WIRE_MODE)) {
		Vertex line[2];
		for (int i = 0; i < vertexCount; i += 3) {
			line[0] = vertexShadingResult[i];
			line[1] = vertexShadingResult[i + 1];
			drawline(rd, line);

			line[0] = vertexShadingResult[i + 1];
			line[1] = vertexShadingResult[i + 2];
			drawline(rd, line);

			line[0] = vertexShadingResult[i + 2];
			line[1] = vertexShadingResult[i];
			drawline(rd, line);
		}
	}
	else {
		Vertex triangle[3];
		for (int i = 0; i < vertexCount; i += 3) {
			triangle[0] = vertexShadingResult[i];
			triangle[1] = vertexShadingResult[i + 1];
			triangle[2] = vertexShadingResult[i + 2];
			drawing_drawTriangle(rd, triangle);
		}
	}

	free(vertexShadingResult);
}