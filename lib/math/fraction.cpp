#ifndef FRACTION_CPP_INCLUDED
#define FRACTION_CPP_INCLUDED

#include <ostream>
#include "fraction.h"
#include "algorithm.h"

// ImproperFraction
template <typename N>
ImproperFraction<N>& ImproperFraction<N>::reduce()
{
	N divisor = gcd(numerator, denominator);
	numerator /= divisor;
	denominator /= divisor;

	if (denominator < 0)
	{
        numerator = -numerator;
        denominator = -denominator;
	}
}

template <typename N>
ImproperFraction<N>::ImproperFraction(N n, N d)
{
	numerator = n;
	denominator = d;
	reduce();
}

template <typename N>
N ImproperFraction<N>::getInteger() const
{
	return numerator / denominator;
}

template <typename N>
N ImproperFraction<N>::getNumerator() const
{
	return numerator;
}

template <typename N>
N ImproperFraction<N>::getDenominator() const
{
	return denominator;
}

// Operator overloading when needed
template <typename N>
istream& operator<<(ostream& is, const ImproperFraction<N>& f)
{
    is << f.getNumerator() << "/" << f.getDenominator();
}

// Fraction
template <typename N1, typename N2>
Fraction<N1,N2>& Fraction<N1,N2>::reduce()
{

}

template <typename N1, typename N2>
Fraction<N1,N2>::Fraction(N1 a, N2 b, N2 c)
{

}

template <typename N1, typename N2>
N1 Fraction<N1,N2>::getInteger() const
{

}

template <typename N1, typename N2>
N2 Fraction<N1,N2>::getNumerator() const
{

}

template <typename N1, typename N2>
N2 Fraction<N1,N2>::getDenominator() const
{

}

template <typename N1, typename N2>
istream& operator<<(ostream& is, const Fraction<N1,N2>& f)
{
    is << f.getInteger() << " "
		<< f.getNumerator() << "/" << f.getDenominator();
}

#endif // FRACTION_CPP_INCLUDED
