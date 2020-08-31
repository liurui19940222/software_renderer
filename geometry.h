#pragma once

#include "renderer.h"

Vertex triangle[3] = {
	{{ -1.0f, -1.0f, 0.0f }},
	{{ 1.0f, -1.0f, 0.0f }},
	{{ 0.0f, 1.0f, 0.0f }},
};

#define CH 0.5f

// top->bottom->left->right->front->back 
Vertex cube[36] = {
	// TOP
	{ { -CH, CH, -CH } },
	{ { CH, CH ,CH } },
	{ { -CH, CH ,CH } },
	{ { CH, CH ,CH } },
	{ { -CH, CH ,-CH } },
	{ { CH, CH ,-CH } },

	// Bottom
	{ { -CH, -CH ,CH } },
	{ { CH, -CH ,-CH } },
	{ { -CH, -CH ,-CH } },
	{ { CH, -CH ,-CH } },
	{ { -CH, -CH ,CH } },
	{ { CH, -CH ,CH } },

	// Left
	{ { -CH, CH, -CH } },
	{ { -CH, -CH ,CH } },
	{ { -CH, -CH ,-CH } },
	{ { -CH, -CH ,CH } },
	{ { -CH, CH ,-CH } },
	{ { -CH, CH ,CH } },

	// Right
	{ { CH, -CH ,-CH } },
	{ { CH, CH ,CH } },
	{ { CH, CH ,-CH } },
	{ { CH, CH ,CH } },
	{ { CH, -CH ,-CH } },
	{ { CH, -CH ,CH } },

	// Front
	{ { -CH, -CH, -CH } },
	{ { CH, CH ,-CH } },
	{ { -CH, CH ,-CH } },
	{ { CH, CH ,-CH } },
	{ { -CH, -CH ,-CH } },
	{ { CH, -CH ,-CH } },

	// Back
	{ { -CH, CH ,CH } },
	{ { CH, -CH ,CH } },
	{ { -CH, -CH ,CH } },
	{ { CH, -CH ,CH } },
	{ { -CH, CH ,CH } },
	{ { CH, CH ,CH } },
};