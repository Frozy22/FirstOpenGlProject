#pragma once

#define EXCEPTION_ARGUMENT_OUT_OF_RANGE "Exception: Argument out of range;"

#define CHECK_INDEX_RANGE(min, max, value) if(value < min || value >= max) throw EXCEPTION_ARGUMENT_OUT_OF_RANGE
#define CHECK_INDEX_RANGE(min, value) if(value < min) throw EXCEPTION_ARGUMENT_OUT_OF_RANGE