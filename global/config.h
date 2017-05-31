#include <vector>

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED


typedef int Millisecond;
typedef long long Nanosecond;

extern Millisecond globalOffset;
extern Millisecond visualOffset;

/** The judge windows.
	<p>The smaller the indices the stricter it is. */
extern vector<Nanosecond> judgeWindows;

#endif // CONFIG_H_INCLUDED
