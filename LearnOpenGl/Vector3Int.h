#pragma once
#include "Hashes.h"

struct Vector3Int
{
public:
	int x = 0;
	int y = 0;
	int z = 0;

	Vector3Int();
	Vector3Int(int x, int y, int z);

	bool operator==(const Vector3Int&) const = default;
};

MAKE_HASHABLE(Vector3Int, v.x, v.y, v.z);

