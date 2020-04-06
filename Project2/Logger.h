#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
class Logger
{
public: //todo: truncate filename, put function name in log, audio channel
	/*enum Channels {
		Memorymanager,
		Rendering,
		Miscellaneous
	};*/
	static std::ofstream EngineLogFile; //configuration file?
	static unsigned int engineverbosity;
	/*static unsigned int enginechannel;*/
	static unsigned int enginechannels[4];  //0 = all, 1 = memorymanager, // 2 = rendering, 3 = other/miscellaneous, 4 = audio
	static bool showwarnings;
	static bool clear;
	static bool haltlogs;

	Logger();
	~Logger();
	void startUp();
	void shutDown();

	void clearLogs();

	//void setVerbosity(int &newverbosity);
	void setEngineLoggerSettings(int mem, int render, int misc, int newverbosity, bool newshowwarnings);
	void setLoggerVerbosity(int newverbosity);
	static void engineLog(std::string file, unsigned int line, std::string errormessage, int verbosity, int channel, bool iswarning); //timestamp
	//void EngineLog(const char* format, ...);
};