#pragma once
#include "../Logger.h"
#include "SDL2/SDL.h"
#include "openAL/al.h"
#include "openAL/alc.h"
#include <string>
struct Audiodata {
	Uint8* pos;
	Uint8* startpos;
	Uint32 length;
	Uint32 totallength;
};
class Audioclip : public Logger
{
public:
	Audiodata audiodata;
	SDL_AudioSpec wavspec;
	SDL_AudioDeviceID deviceid;
	Uint8 *wavstart;
	Uint32 wavlength;
	bool playing;
	float falloffmin;
	float falloffmax;


	//sample info
	double volume;
	double position;
	bool generateSamples(float* stream, Audiodata audiodata);
	void setPos(double pos);

	void loadAudio(std::string file);
	void setDevice(std::string devicename);
	void pauseAudio();
	void endAudio();
	void setAudioPosition();
	void setVolume();
	void setPitch();
	void loopAudio();
	void Pan();
	void freeAudio();
	void playAudio();
	Audioclip(std::string audiofile);
	Audioclip();
	~Audioclip();
};
