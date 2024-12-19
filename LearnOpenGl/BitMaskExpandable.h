#pragma once
#include <vector>
#include <utility>

#define INT_BITS_COUNT sizeof(int) * 8

using namespace std;

class ExpandableBitMask
{
private:
	vector<int> masks;

	pair<int, int> ConvertIndex(int index) const;

public:
	bool Get(int index) const;
	void Set(int index, bool flag);

	bool HasAny();

	void Clear();
};

