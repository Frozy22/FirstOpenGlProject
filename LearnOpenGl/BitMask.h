#pragma once

#define INT_BITS_COUNT sizeof(int) * 8

class BitMask
{
private:
	int mask;

public:
	bool Get(int index) const;
	void Set(int index, bool flag);

	bool HasAny() const;

	void Clear();
};

