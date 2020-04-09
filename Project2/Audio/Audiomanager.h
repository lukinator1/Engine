#pragma once
#include "SDL2/SDL.h"
#include <string>
#include "Audioclip.h"
#include "../Scene.h"
class Audiomanager
{
public:
	void audioStartup();
	void audioUpdate(Scene & currentscene);
	void loadAudio(std::string file);
	void audioShutDown();
	Audiomanager();
	~Audiomanager();
};

