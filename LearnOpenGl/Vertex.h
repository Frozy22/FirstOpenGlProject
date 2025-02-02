#pragma once
#include "Vector3.h"
#include "Vector2.h"

struct Vertex
{
public:
	Vector3 position;
	Vector3 normal;
	Vector2 uv;

	Vertex();
	Vertex(Vector3 position, Vector3 normal, Vector2 uv);
};

