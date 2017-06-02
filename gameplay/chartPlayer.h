#ifndef CHARTPLAYER_H_INCLUDED
#define CHARTPLAYER_H_INCLUDED

#include "../global/types.h"
#include "../global/config.h"
#include "../global/state.h"
#include "../utilities/musicPlayer.h"

typedef unsigned int Beat;
typedef ImproperFraction<int> FractionalBeat;

class Note
{
	Beat beat;
	FractionalBeat beat;
};

class ChartPlayer
{
private:
	Milliseconds songOffset;
	vector<Note> notes;

};

#endif // CHARTPLAYER_H_INCLUDED
