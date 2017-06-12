#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED

#include <ostream>
#include "algorithm.h"

template <typename N>
class ImproperFraction;
template <typename N1, typename N2>
class Fraction;

template <typename N>
class ImproperFraction
{
private:
	friend class Fraction<N,N>;
    N numerator;
    N denominator;
	ImproperFraction<N>& reduce();
public:
    ImproperFraction<N>(N = 0, N = 1);
	N getInteger() const;
	N getNumerator() const;
	N getDenominator() const;
	// Operator overloading when needed
	const ImproperFraction<N> operator+(const ImproperFraction<N>& n) const;
	const ImproperFraction<N> operator-(const ImproperFraction<N>& n) const;
	ImproperFraction<N>& operator+=(const ImproperFraction<N>& n);
	ImproperFraction<N>& operator+=(N n);
	ImproperFraction<N>& operator-=(const ImproperFraction<N>& n);
	ImproperFraction<N>& operator-=(N n);
	bool operator<(N n) const;
	bool operator<(const ImproperFraction<N>& n) const;
	bool operator>(N n) const;
	bool operator>(const ImproperFraction<N>& n) const;
	ImproperFraction<N> operator++(int);
	ImproperFraction<N> operator--(int);
	operator N() const;
	operator double() const;
};


template <typename N>
istream& operator<<(ostream& os, const ImproperFraction<N>& f);

template <typename N1, typename N2>
class Fraction
{
private:
	N1 integer;
	ImproperFraction<N2> fraction;
	Fraction& reduce();
public:
	Fraction(N1 = 0, N2 = 0, N2 = 1);
	N1 getInteger() const;
	N2 getNumerator() const;
	N2 getDenominator() const;
	// Operator overloading when needed
};

template <typename N1, typename N2>
istream& operator<<(ostream& os, const Fraction<N1,N2>& f);

#include "fraction.cpp"

#endif // FRACTION_H_INCLUDED
