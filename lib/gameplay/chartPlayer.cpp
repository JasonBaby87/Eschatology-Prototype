#ifndef CHARTPLAYER_CPP_INCLUDED
#define CHARTPLAYER_CPP_INCLUDED

#include <istream>
#include <vector>
#include "chartPlayer.h"
#include "../global/exception.h"

Note::Note(Beat b): beat(b)
{
	alive = false;
}

ChartPlayer::ChartPlayer(MusicPlayer&, istream& data)
{
	throw NotImplementedException();
}

vector<pair<BeatDuration,Note*>>& ChartPlayer::getNotePositions(BeatDuration)
{
	throw NotImplementedException();
}

void ChartPlayer::hit()
{
	throw NotImplementedException();
}

vector<Judgement>& ChartPlayer::getJudgements() const
{
	throw NotImplementedException();
}

#endif // CHARTPLAYER_CPP_INCLUDED
