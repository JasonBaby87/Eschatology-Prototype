#ifndef SCORETRACKER_H_INCLUDED
#define SCORETRACKER_H_INCLUDED

#include "chartPlayer.h"

typedef long long Score;
typedef int Combo;

class ScoreTracker
{
private:
	ChartPlayer* chart;
	Score score;
	Combo combo;
public:
	ScoreTracker(ChartPlayer&);
	Score getScore();
};

#endif // SCORETRACKER_H_INCLUDED
