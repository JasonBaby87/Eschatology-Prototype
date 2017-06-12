
/*template <typename N>
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
}*/

template <typename N>
N lcm(N a, N b)
{
    return a / gcd(a, b) * b;
}
