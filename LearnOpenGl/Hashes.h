#pragma once
#include <cstddef>
#include <functional>

inline void hash_combine(size_t& seed) {}

template <typename T, typename... Rest>
void hash_combine(size_t& seed, const T& v, const Rest&... rest)
{
    seed ^= std::hash<T>{}(v)+0x9e3779b9 + (seed << 6) + (seed >> 2);
    (hash_combine(seed, rest), ...);
}

#define MAKE_HASHABLE(type, ...) \
    namespace std {\
        template<> struct hash<type> {\
            size_t operator()(const type &v) const {\
                size_t ret = 0;\
                hash_combine(ret, __VA_ARGS__);\
                return ret;\
            }\
        };\
    }