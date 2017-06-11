#include "../global/config.h"
#include "../global/state.h"

#ifndef MUSICPLAYER_H_INCLUDED
#define MUSICPLAYER_H_INCLUDED

class MusicPlayer
{
	// music file
public:
	void play();
	void pause();
	void stop();
	bool isPlaying();
	Nanoseconds playTime();
};

#endif // MUSICPLAYER_H_INCLUDED
