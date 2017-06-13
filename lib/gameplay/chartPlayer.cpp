#ifndef CHARTPLAYER_CPP_INCLUDED
#define CHARTPLAYER_CPP_INCLUDED

#include <istream>
#include <list>
#include <vector>
#include <chrono>
#include "chartPlayer.h"
#include "../global/exception.h"

Note::Note(Beat b): beat(b)
{

}

void ChartPlayer::registerMisses()
{
	throw NotImplementedException();
}

ChartPlayer::ChartPlayer(MusicPlayer& music, istream& data): music(music)
{
	data >> songOffset >> bpm;
    Beat beat;
    while (data >> beat)
	{
		Note* note = new Note(beat);
        notes.push_back(note);
	}

    sort(notes.begin(), notes.end(), earlierThan);
}

vector<pair<BeatDuration,Note*>>& ChartPlayer::getNotePositions(BeatDuration)
{
	registerMisses();

	vector<pair<BeatDuration,Note*>> result;

	Nanoseconds currentTime = music.playTime() - songOffset - visualOffset;
	BeatDuration currentBeat = static_cast<BeatDuration>(currentTime.count()) /
		60000000000l * bpm;

	for (auto it = notes.begin(); it != notes.end(); it++)
	{
		// TODO more thing D: need to calculate how far away each notes are
		result.push_back(*it);
		// TODO check stuff
		throw NotImplementedException("Beat Duration not checked.");
	}

	return result;
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
