#include <iostream>
#include <sstream>
#include <cstdlib>
#include "lib/math/fraction.h"
#include "lib/math/fraction.cpp"

using namespace std;

#define rep(i, n) for(int i = 0; i < n; i++)

stringstream output;
/** Used to determine if a space is required */
bool firstElement = true;

/** Outputs s with a preceeding space if required. */
template <typename T>
void print(T s);

/** Outputs the next line character. */
void println();

/** Outputs s with a preceeding space if required.
	Then, outputs the next line character.*/
template <typename T>
void println(T s);

/** Actually outputs the result and end the program.*/
void eOP();

int main()
{
	ImproperFraction<int> a(2, 4);

	cout << a;

	eOP();
}

template <typename T>
void print(T s)
{
	if (firstElement)
	{
        output << s;
        firstElement = false;
	}
	else
	{
        output << " " << s;
	}
}

void println()
{
	output << endl;
	firstElement = true;
}

template <typename T>
void println(T s)
{
	print(s);
	println();
}

void eOP()
{
	cout << output.str();
	output.str(string());
	exit(0);
}
