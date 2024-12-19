#include "BitMaskExpandable.h"
#include "Exceptions.h"

pair<int, int> ExpandableBitMask::ConvertIndex(int index) const
{
	CHECK_INDEX_RANGE(0, index);

	int maskIndex = index / INT_BITS_COUNT;
	int bitIndex = index % INT_BITS_COUNT;

	return make_pair(maskIndex, bitIndex);
}

bool ExpandableBitMask::Get(int index) const
{
	auto pair = ConvertIndex(index);

	if (masks.size() <= pair.first)
		return false;

	return (masks[pair.first] & (1 << pair.second)) != 0;
}

void ExpandableBitMask::Set(int index, bool flag)
{
	auto pair = ConvertIndex(index);

	if (masks.size() <= pair.first)
		masks.resize(pair.first + 1, 0);

	int value = 1 << pair.second;

	if (flag)
		masks[pair.first] |= value;
	else
		masks[pair.first] &= ~value;
}

bool ExpandableBitMask::HasAny()
{
	for (int mask : masks)
	{
		if (mask != 0)
			return true;
	}

	return false;
}

void ExpandableBitMask::Clear()
{
	masks.clear();
}
