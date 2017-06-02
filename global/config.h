#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <vector>
#include <chrono>

using namespace std;

typedef duration<int,milli> Millisecond;
typedef duration<long long,micro> Microsecond;
typedef duration<long long,nano> Nanosecond;

extern Millisecond globalOffset;
extern Millisecond visualOffset;

/** The judge windows.
	<p>The smaller the indices the stricter it is. */
extern vector<Nanosecond> judgeWindows;

#endif // CONFIG_H_INCLUDED
