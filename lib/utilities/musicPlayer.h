#include "../global/config.h"
#include "../global/state.h"

#ifndef MUSICPLAYER_H_INCLUDED
#define MUSICPLAYER_H_INCLUDED

class MusicPlayer
{
	// music file
public:
	void play();
	void pause(); // Won't be used for actual game play (in demo)
	void stop();
	bool isPlaying();
	Nanoseconds playTime();

	MusicPlayer(); // TODO figure out SDL
};

#endif // MUSICPLAYER_H_INCLUDED
