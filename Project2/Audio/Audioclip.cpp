#include "Audioclip.h"
void audioCallback(void* userdata, Uint8*  stream, int len) {
	Audiodata* aud = (Audiodata *)userdata;

	if (aud->length == 0) {
		return;
	}
	Uint32 length = (Uint32)len;
	if (length > aud->length) {
		length = aud->length;
	}



	SDL_memcpy(stream, aud->pos, length);

	if (aud->volumeoff) {
		for (int i = 0; i < (len * 8); i++) {
			stream[i] = 0;
		}
	}


	aud->pos += length;
	aud->length -= length;
	if (aud->length == 0) {
		aud->pos = aud->startpos;
		aud->length = aud->totallength;
		if (aud->parentclip->loopaudio == false) {
			aud->parentclip->pauseAudio();
		}
	}
}
bool Audioclip::generateSamples(float * stream, Audiodata audiodata)
{
	return false;
}
void Audioclip::setPos(double pos)
{
	position = pos;
}
void Audioclip::loadAudio(std::string file) {
	std::string audiofile = "Audio/Clips/" + file;
	if (SDL_LoadWAV(audiofile.c_str(), &wavspec, &wavstart, &wavlength) == NULL) {
		/*engineLog(__FILE__, __LINE__, "In function loadAudio(string file), audio file failed to load.", 2, 4, false);*/
		std::cout << "Audio file failed to load.";
	}
	audiodata.pos = wavstart;
	audiodata.startpos = wavstart;
	audiodata.length = wavlength;
	audiodata.totallength = wavlength; 
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
void Audioclip::setAudioPosition() {

}
void Audioclip::setVolume() {

}
void Audioclip::setPitch() {

}
void Audioclip::loopAudio() {

}
void Audioclip::Pan() {

}
void Audioclip::freeAudio() {
	SDL_CloseAudioDevice(deviceid);
	SDL_FreeWAV(wavstart);
}
void Audioclip::playAudio() {
	playing = true;
	SDL_LockAudioDevice(deviceid);
	SDL_PauseAudioDevice(deviceid, 0);
	SDL_UnlockAudioDevice(deviceid);
	/*SDL_CloseAudioDevice(deviceid);
	SDL_FreeWAV(wavstart);*/
}
void Audioclip::pauseAudio() {
	playing = false;
	SDL_PauseAudioDevice(deviceid, 1);
}
void Audioclip::endAudio() {
	playing = false;
	SDL_LockAudioDevice(deviceid);
	audiodata.length = audiodata.totallength;
	audiodata.pos = audiodata.startpos;
	SDL_UnlockAudioDevice(deviceid);
	SDL_PauseAudioDevice(deviceid, 1);
}
Audioclip::Audioclip(std::string audiofile)
{
	falloffmin = 18.0f;
	SDL_zero(wavspec);
	wavspec.freq = 44100;
	wavspec.format = AUDIO_S16SYS;
	wavspec.channels = 2;
	wavspec.samples = 2048;
	audiodata.parentclip = this;
	loadAudio(audiofile);
}
Audioclip::Audioclip()
{
	falloffmax = 60.0f;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
	SDL_zero(wavspec);
	wavspec.freq = 44100;
	wavspec.format = AUDIO_S16SYS;
	wavspec.channels = 2;
	wavspec.samples = 2048;
	audiodata.parentclip = this;
}


Audioclip::~Audioclip()
{
}
