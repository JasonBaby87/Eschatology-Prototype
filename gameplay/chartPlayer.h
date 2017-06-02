#ifndef CHARTPLAYER_H_INCLUDED
#define CHARTPLAYER_H_INCLUDED

#include "../global/types.h"
#include "../global/config.h"
#include "../global/state.h"
#include "../utilities/musicPlayer.h"

typedef unsigned int Beat;
typedef ImproperFraction<int> FractionalBeat;

{
	Beat beat;
	FractionalBeat beat;
};

class ChartPlayer
{
private:
	Milliseconds songOffset;

};

#endif // CHARTPLAYER_H_INCLUDED
