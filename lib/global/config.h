#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <vector>
#include "type.h"

using namespace std;

extern Milliseconds globalOffset();
extern Milliseconds visualOffset();

/** The judge windows.
	<p>The smaller the indices the stricter it is. */
extern vector<Nanoseconds> judgeWindows();

#endif // CONFIG_H_INCLUDED
