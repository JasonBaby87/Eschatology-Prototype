#ifndef CONFIG_CPP_INCLUDED
#define CONFIG_CPP_INCLUDED

#include <istream>
#include <chrono>
#include <cmath>
#include "type.h"
#include "config.h"

using namespace std;

void loadConfigurations(istream& is)
{
    Time doubleTime;

	is >> doubleTime;
	globalOffset = Milliseconds(lround(doubleTime * 1e3));

	is >> doubleTime;
	visualOffset = Milliseconds(lround(doubleTime * 1e3));

	judgeWindows.clear();
	Judgement numOfJudgements;
	Nanoseconds judgeWindow;

	is >> numOfJudgements;
	for (Judgement i = 0; i < numOfJudgements; i++)
	{
		is >> doubleTime;
		judgeWindow = Nanoseconds(llround(doubleTime * 1e9));
        judgeWindows.push_back(judgeWindow);
	}
}

#endif // CONFIG_CPP_INCLUDED
