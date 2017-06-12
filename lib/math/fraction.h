#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED

template <typename N>
class ImproperFraction
{
private:
    N numerator;
    N denominator;
protected:
    ImproperFraction& reduce();
public:
    ImproperFraction(N = 0, N = 1);
	N getInteger() const;
	N getNumerator() const;
	N getDenominator() const;
	// Operator overloading when needed
};

template <typename N1, N2>
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

#endif // FRACTION_H_INCLUDED
