#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED

#include <iostream>
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
	const ImproperFraction<N> operator-() const;
	const ImproperFraction<N> operator++(int);
	const ImproperFraction<N> operator--(int);
	operator N() const;
	operator double() const;
};


template <typename N>
ostream& operator<<(ostream& os, const ImproperFraction<N>& f);

template <typename N>
istream& operator>>(istream& is, ImproperFraction<N>& f);

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
	const ImproperFraction<N2>& getFraction() const;
	N2 getNumerator() const;
	N2 getDenominator() const;
	// Operator overloading when needed
	operator double() const;
};

template <typename N1, typename N2>
ostream& operator<<(ostream& os, const Fraction<N1,N2>& f);

template <typename N1, typename N2>
istream& operator>>(istream& is, Fraction<N1,N2>& f);

template <typename N1, typename N2>
const double operator*(double l, const Fraction<N1,N2>& r);

#include "fraction.cpp"

#endif // FRACTION_H_INCLUDED
