#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <vector>
#include <chrono>

using namespace std;

typedef duration<int,milli> Milliseconds;
typedef duration<long long,micro> Microseconds;
typedef duration<long long,nano> Nanoseconds;

extern Milliseconds globalOffset;
extern Milliseconds visualOffset;

/** The judge windows.
	<p>The smaller the indices the stricter it is. */
extern vector<Nanoseconds> judgeWindows;

#endif // CONFIG_H_INCLUDED
