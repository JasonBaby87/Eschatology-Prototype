/**
	Author:			Kuo, Tai-Yuan
	Student ID#:	B05705031
	Date:			[insert date]
	File Name:		[insert file name]
	Description:	[insert description]
*/
#include <iostream>
#include <sstream>
#include <cstdlib>

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
	// TODO insert your program here

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
