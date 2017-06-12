#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#include <chrono>

using namespace std;

typedef chrono::milliseconds Milliseconds;
typedef chrono::microseconds Microseconds;
typedef chrono::nanoseconds Nanoseconds;

// Judgements
/** It is an integral type. The lower the value, the better.
	<p>Negative values are for misses and some others.</p>*/
typedef short Judgement;
extern const Judgement MISS = -1;
extern const Judgement WRONG = -2;

#endif // TYPE_H_INCLUDED
