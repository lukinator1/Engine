#pragma once
#include "../Audio/Audioclip.h"
#include "Component.h"
class ThreeDaudio : public Component
{
public:
	Audioclip audioclip;
	float falloffdistance;
	float fallindistance;
	vector3 listener; 
	bool settotransform;
	void componentAudio(Transforming &t) {
		if ((t.getPosition().Subtract(listener)).Magnitude() <= falloffdistance) {
			audioclip.playAudio();
		}
	}
	ThreeDaudio();
	~ThreeDaudio();
};

