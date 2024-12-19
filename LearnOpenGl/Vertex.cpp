#include "Vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(Vector3 position, Vector3 normal, Vector2 uv)
{
	this->position = position;
	this->normal = normal;
	this->uv = uv;
}
