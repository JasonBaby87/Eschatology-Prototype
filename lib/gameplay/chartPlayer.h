#ifndef CHARTPLAYER_H_INCLUDED
#define CHARTPLAYER_H_INCLUDED

#include "../global/type.h"
#include "../global/config.h"
#include "../global/state.h"
#include "../utilities/musicPlayer.h"
#include <iostream>

typedef unsigned int Beat; // Time point
typedef ImproperFraction<int> FractionalBeat; // Time point
typedef double BeatDuration; // Duration
typedef Fraction<int,int> BPM;

class Note
{
	Beat beat;
	FractionalBeat division;
};

class ChartPlayer
{
private:
	Milliseconds songOffset;
	vector<Note> notes;
	MusicPlayer* music;
	BPM bpm;
public:
	ChartPlayer(MusicPlayer&, istream&);
	vector<pair<BeatDuration,Note>>& getNotePositions(BeatDuration);
};

#endif // CHARTPLAYER_H_INCLUDED
