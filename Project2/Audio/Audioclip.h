#pragma once
#include "../Logger.h"
#include "SDL2/SDL.h"
#include <string>
struct Audiodata {
	Uint8* pos;
	Uint32 length;
};
class Audioclip : public Logger
{
public:
	Audiodata audiodata;
	SDL_AudioSpec wavspec;
	SDL_AudioDeviceID deviceid;
	Uint8 *wavstart;
	Uint32 wavlength;
	void loadAudio(std::string file);
	void setDevice(std::string devicename);
	void freeAudio();
	void playAudio();
	Audioclip(std::string audiofile);
	Audioclip();
	~Audioclip();
};
