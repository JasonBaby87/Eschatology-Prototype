#ifndef SCORETRACKER_H_INCLUDED
#define SCORETRACKER_H_INCLUDED

#include "chartPlayer.h"

typedef long long Score;

class ScoreTracker
{
private:
	ChartPlayer* chart;
	Score score;
	int tracked;
public:
	ScoreTracker(ChartPlayer&);
	Score getScore();
};

#endif // SCORETRACKER_H_INCLUDED
