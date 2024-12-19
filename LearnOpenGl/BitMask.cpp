#include "BitMask.h"
#include "Exceptions.h"

bool BitMask::Get(int index) const
{
	CHECK_INDEX_RANGE(0, INT_BITS_COUNT, index);

	return (mask & (1 << index)) != 0;
}

void BitMask::Set(int index, bool flag)
{
	CHECK_INDEX_RANGE(0, INT_BITS_COUNT, index);

	int value = 1 << index;

	if (flag)
		mask |= value;
	else
		mask &= ~value;
}

bool BitMask::HasAny() const
{
	return mask != 0;
}

void BitMask::Clear()
{
	mask = 0;
}
