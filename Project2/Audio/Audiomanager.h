#pragma once
#include "SDL2/SDL.h"
#include <string>
#include "Audioclip.h"
class Audiomanager
{
public:
	void audioStartup();
	void audioUpdate();
	void loadAudio(std::string file);
	void audioShutDown();
	Audiomanager();
	~Audiomanager();
};

