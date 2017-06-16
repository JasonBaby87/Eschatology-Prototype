#ifndef FRACTION_CPP_INCLUDED
#define FRACTION_CPP_INCLUDED

#include <iostream>
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
ImproperFraction<N>::ImproperFraction(N n, N d): numerator(n), denominator(d)
{
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
const ImproperFraction<N> ImproperFraction<N>::operator+(const ImproperFraction<N>& f) const
{
    int n, d;
    d = lcm(denominator, f.denominator);

	n = numerator * (d / denominator);
	n += f.numerator * (d / f.denominator);

    return ImproperFraction<N>(n, d);
}

template <typename N>
const ImproperFraction<N> ImproperFraction<N>::operator-(const ImproperFraction<N>& f) const
{
    int n, d;
    d = lcm(denominator, f.denominator);

	n = numerator * (d / denominator);
	n -= f.numerator * (d / f.denominator);

    return ImproperFraction<N>(n, d);
}

template <typename N>
ImproperFraction<N>& ImproperFraction<N>::operator+=(const ImproperFraction<N>& n)
{
	*this = *this + ImproperFraction<N>(n);
	return *this;
}

template <typename N>
ImproperFraction<N>& ImproperFraction<N>::operator+=(N n)
{
	*this += ImproperFraction<N>(n);
	return *this;
}

template <typename N>
ImproperFraction<N>& ImproperFraction<N>::operator-=(const ImproperFraction<N>& n)
{
	*this = *this - ImproperFraction<N>(n);
	return *this;
}

template <typename N>
ImproperFraction<N>& ImproperFraction<N>::operator-=(N n)
{
	*this -= ImproperFraction<N>(n);
	return *this;
}

template <typename N>
bool ImproperFraction<N>::operator<(const ImproperFraction<N>& f) const
{
    return static_cast<double>(*this) < static_cast<double>(f);
}

template <typename N>
bool ImproperFraction<N>::operator<(N n) const
{
	return *this < ImproperFraction<N>(n);
}

template <typename N>
bool ImproperFraction<N>::operator>(const ImproperFraction<N>& f) const
{
    return static_cast<double>(*this) > static_cast<double>(f);
}

template <typename N>
bool ImproperFraction<N>::operator>(N n) const
{
	return *this > ImproperFraction<N>(n);
}

template <typename N>
ImproperFraction<N> ImproperFraction<N>::operator++(int)
{
	ImproperFraction<N> result = *this;
	*this += 1;
    return result;
}

template <typename N>
ImproperFraction<N> ImproperFraction<N>::operator--(int)
{
	ImproperFraction<N> result = *this;
	*this -= 1;
    return result;
}

template <typename N>
ImproperFraction<N>::operator N() const
{
	return static_cast<N>(numerator / denominator);
}

template <typename N>
ImproperFraction<N>::operator double() const
{
	return static_cast<double>(numerator) / denominator;
}

template <typename N>
istream& operator<<(ostream& is, const ImproperFraction<N>& f)
{
    is << f.getNumerator() << "/" << f.getDenominator();
}

// Fraction
template <typename N1, typename N2>
Fraction<N1,N2>& Fraction<N1,N2>::reduce()
{
	int temp = fraction.getInteger();
	integer += temp;
	fraction -= temp;

	if (integer > 0 && fraction < 0)
	{
        integer--;
        fraction++;
	}
	else if (integer < 0 && fraction > 0)
	{
		integer++;
		fraction--;
	}
}

template <typename N1, typename N2>
Fraction<N1,N2>::Fraction(N1 i, N2 n, N2 d): integer(i)
{
	fraction = ImproperFraction<N2>(n, d);
	reduce();
}

template <typename N1, typename N2>
N1 Fraction<N1,N2>::getInteger() const
{
	return integer;
}

template <typename N1, typename N2>
const ImproperFraction<N2>& Fraction<N1,N2>::getFraction() const
{
	return fraction;
}

template <typename N1, typename N2>
N2 Fraction<N1,N2>::getNumerator() const
{
	return fraction.getNumerator();
}

template <typename N1, typename N2>
N2 Fraction<N1,N2>::getDenominator() const
{
	return fraction.getDenominator();
}

template <typename N1, typename N2>
Fraction<N1, N2>::operator double() const
{
	return integer + static_cast<double>(fraction);
}

template <typename N1, typename N2>
istream& operator<<(ostream& is, const Fraction<N1,N2>& f)
{
	// TODO
    is << f.getInteger() << " "
		<< f.getNumerator() << "/" << f.getDenominator();
}

template <typename N1, typename N2>
<<<<<<< HEAD
=======
istream& operator>>(istream& is, Fraction<N1,N2>& f)
{
	// TODO
    is >> integer >> fraction;
}

template <typename N1, typename N2>
>>>>>>> refs/remotes/origin/Math
const double operator*(double l, const Fraction<N1,N2>& r)
{
	return l * static_cast<double>(r);
}

#endif // FRACTION_CPP_INCLUDED
