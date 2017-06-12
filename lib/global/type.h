#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#include <chrono>

using namespace std;

typedef chrono::milliseconds Milliseconds;
typedef chrono::microseconds Microseconds;
typedef chrono::nanoseconds Nanoseconds;
/** It is an unsigned integral type. The lower the value, the better. */
typedef unsigned short Judgement;

#endif // TYPE_H_INCLUDED
