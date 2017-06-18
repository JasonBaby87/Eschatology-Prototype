#ifndef CHARTPLAYER_CPP_INCLUDED
#define CHARTPLAYER_CPP_INCLUDED

#include <istream>
#include <list>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cmath>
#include "chartPlayer.h"
#include "../global/exception.h"

Note::Note(Beat b): beat(b)
{

}

bool earlierThan(const Note* a,const Note* b)
{
	return a->beat < b->beat;
}

void ChartPlayer::registerMisses()
{
	while(!notes.empty())
	{
		Time currentTime = chrono::duration_cast<chrono::nanoseconds>
			(chrono::high_resolution_clock::now() - startTime - songOffset - globalOffset).count() / 1e9;

		Note* note = notes.front();
		Time noteTime = static_cast<Time>(note->beat) / bpm * 60;
		Time timeDifference = noteTime - currentTime;

		if (timeDifference >= chrono::duration_cast<chrono::duration<Time>>(-judgeWindows.back()).count())
		{
			break;
		}

        judgements.push_back(MISS);
        delete note;
		notes.pop_front();
	}
}

void ChartPlayer::start()
{
    startTime = chrono::high_resolution_clock::now();
}

ChartPlayer::ChartPlayer(istream& data)
{
	double offsetTime;
	data >> offsetTime >> bpm;
	int offsetMilli = lround(offsetTime * 1000);
	songOffset = static_cast<Milliseconds>(offsetMilli);

    Beat beat;
    while (data >> beat)
	{
		Note* note = new Note(beat);
        notes.push_back(note);
	}

    notes.sort(earlierThan);
}

const vector<pair<BeatDuration,Note*>>
	ChartPlayer::getNotePositions(BeatDuration visibleWindow)
{
	registerMisses();

	vector<pair<BeatDuration,Note*>> result;

	Nanoseconds currentTime = chrono::high_resolution_clock::now() - startTime - songOffset - visualOffset;
	BeatDuration currentBeat = static_cast<BeatDuration>(currentTime.count()) /
		60000000000ll * bpm;

	for (auto it = notes.begin(); it != notes.end(); it++)
	{
		BeatDuration noteBeat = static_cast<double>((*it)->beat);
		BeatDuration beatDiff = noteBeat - currentBeat;
		if (beatDiff > visibleWindow)
		{
			break;
		}

		result.push_back(make_pair(beatDiff, *it));
	}

	return result;
}

void ChartPlayer::hit()
{
	registerMisses();

	Time currentTime = chrono::duration_cast<chrono::nanoseconds>
		(chrono::high_resolution_clock::now() - startTime - songOffset - globalOffset).count() * 1e9;

	if (notes.size() == 0)
	{
		judgements.push_back(WRONG);
		return;
	}

    auto earlier = notes.begin();
    auto later = earlier;

    for (; later != notes.end(); later++)
	{
        earlier = later;
		Time noteTime = static_cast<Time>((*later)->beat) / bpm * 6e10;

		if (noteTime > currentTime)
		{
			break;
		}
	}

	if (later == notes.end())
	{
		later--;
	}

	Time earlierTime = static_cast<Time>((*earlier)->beat) / bpm * 6e10;
	Time laterTime = static_cast<Time>((*later)->beat) / bpm * 6e10;

	auto noteHit = earlier;
	Time hitTime = earlierTime;

    if (abs(laterTime - currentTime) < abs(earlierTime - currentTime))
	{
		noteHit = later;
		hitTime = laterTime;
	}

	Time timeDifference = abs(hitTime - currentTime);

	Judgement judgement =
		lower_bound(judgeWindows.begin(), judgeWindows.end(), Nanoseconds(llround(timeDifference * 1e9)))
		- judgeWindows.begin();

	if (judgement == judgeWindows.size())
	{
		judgements.push_back(WRONG);
		return;
	}

    judgements.push_back(judgement);
    delete *noteHit;
    notes.erase(noteHit);
}

const vector<Judgement>& ChartPlayer::getJudgements()
{
	registerMisses();

	return judgements;
}

#endif // CHARTPLAYER_CPP_INCLUDED
