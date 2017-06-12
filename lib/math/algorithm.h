#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include <algorithm>

using namespace std;

template <typename N>
N gcd(N a, N b)
{
	if (a == 0)
	{
		return b;
	}
	if (b == 0)
	{
		return a;
	}
	while (a != 0)
	{
        b %= a;
        swap(a, b);
	}
	return b;
}

template <typename N>
N lcm(N a, N b);


#endif // ALGORITHM_H_INCLUDED
