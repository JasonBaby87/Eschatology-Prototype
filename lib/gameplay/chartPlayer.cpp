#ifndef CHARTPLAYER_CPP_INCLUDED
#define CHARTPLAYER_CPP_INCLUDED

#include <istream>
#include <vector>
#include "chartPlayer.h"

Note::Note(Beat b): beat(b)
{
	alive = false;
}

ChartPlayer::ChartPlayer(MusicPlayer&, istream& data)
{

}

vector<pair<BeatDuration,Note*>>& ChartPlayer::getNotePositions(BeatDuration)
{

}

void ChartPlayer::hit()
{

}

vector<Judgement>& ChartPlayer::getJudgements() const
{

}




#endif // CHARTPLAYER_CPP_INCLUDED
