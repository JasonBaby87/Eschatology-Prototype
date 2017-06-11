#ifndef CHARTPLAYER_H_INCLUDED
#define CHARTPLAYER_H_INCLUDED

#include "../global/config.h"
#include "../global/state.h"
#include "../utilities/musicPlayer.h"
#include <iostream>
#include <vector>
#include <list>

typedef unsigned int Beat; // Time point
typedef ImproperFraction<int> FractionalBeat; // Time point
typedef double BeatDuration; // Duration
typedef Fraction<int,int> BPM;

/** A value type class that simply stores when a note is */
class Note
{
public:
	const Beat beat;
	const FractionalBeat division;
	bool alive;
	Note(Beat, FractionalBeat);
};

class ChartPlayer
{
private:
	Milliseconds songOffset;
	list<Note*> notes;
	MusicPlayer* music;
	BPM bpm;
	vector<Judgement> judgements;
public:
	ChartPlayer(MusicPlayer&, istream& data);
	vector<pair<BeatDuration,Note*>>& getNotePositions(BeatDuration);
	void hit();
	vector<Judgement>& getJudgements() const;
};

#endif // CHARTPLAYER_H_INCLUDED
