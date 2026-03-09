#ifndef H_UTILS
#define H_UTILS

#include <cstdlib>

#include <vector>

inline auto rand_n(std::size_t max) -> std::size_t { return rand() % max; }

template <typename T> inline auto vec_choose(std::vector<T> &vec) -> T & { return vec[rand_n(vec.size())]; }

#endif