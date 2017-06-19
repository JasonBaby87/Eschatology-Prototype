#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include <algorithm>

using namespace std;

template <typename N>
N gcd(N a, N b);

template <typename N>
N lcm(N a, N b);

#include "algorithm.cpp"

#endif // ALGORITHM_H_INCLUDED
