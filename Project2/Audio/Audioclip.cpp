#include "Audioclip.h"
void audioCallback(void* userdata, Uint8*  stream, int len) {
	Audiodata* aud = (Audiodata *)userdata;

	if (aud->length == 0) {
		return;
	}
	Uint32 length = (Uint32)len;
	if (length >= aud->length) {
		length = aud->length;
	}
	
	SDL_memcpy(stream, aud->pos, length);

	aud->pos += length;
	aud->length -= length;
}
void Audioclip::loadAudio(std::string file) {
	std::string audiofile = "Audio/Clips/" + file;
	if (SDL_LoadWAV(audiofile.c_str(), &wavspec, &wavstart, &wavlength) == NULL) {
		/*engineLog(__FILE__, __LINE__, "In function loadAudio(string file), audio file failed to load.", 2, 4, false);*/
		std::cout << "Audio file failed to load.";
	}
	audiodata.pos = wavstart;
	audiodata.length = wavlength;
	wavspec.callback = audioCallback;
	wavspec.userdata = &audiodata;
	setDevice("");
	int i = SDL_GetNumAudioDevices(0);
	std::cout << i << std::endl;
	std::string devices[6];
	for (int u = 0; u < i; u++) {
	std::cout << SDL_GetAudioDeviceName(u, 0) << std::endl;
	(devices[u] = SDL_GetAudioDeviceName(u, 0));
	}
}
void Audioclip::setDevice(std::string devicename) {
	if (devicename == "") {
		deviceid = SDL_OpenAudioDevice(NULL, 0, &wavspec, NULL, 0);
	}
	else {
		deviceid = SDL_OpenAudioDevice(devicename.c_str(), 0, &wavspec, NULL, 0);
	}
	if (deviceid == 0) {
		engineLog(__FILE__, __LINE__, "In function loadAudio(string file), there is no avaiable devic to play the file.", 2, 4, false);
		std::cout << "Device failed to load.";
	}
}
void Audioclip::freeAudio() {
	SDL_CloseAudioDevice(deviceid);
	SDL_FreeWAV(wavstart);
}
void Audioclip::playAudio() {
	SDL_PauseAudioDevice(deviceid, 0);
	while (audiodata.length > 0) {
		SDL_Delay(100);
	}
	SDL_CloseAudioDevice(deviceid);
	SDL_FreeWAV(wavstart);
}

Audioclip::Audioclip(std::string audiofile)
{
	loadAudio(audiofile);
}

Audioclip::Audioclip()
{
}


Audioclip::~Audioclip()
{
}
