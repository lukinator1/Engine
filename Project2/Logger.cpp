#include "Logger.h"
Logger::Logger()
{
}
Logger::~Logger()
{
}
void Logger::startUp()/*int * channels, int verbosity, bool warn)*/
{
	/*engineverbosity = 3;
	enginechannel = 0;
	showwarnings = true;
	EngineLogFile.open("Enginelogs/EngineLog.txt", std::ofstream::out | std::ofstream::trunc);
	setEngineLoggerSettings(0, 3, true);
	engineverbosity = verbosity;
		for (int i = 0; i < 4; i++) {
			enginechannels[i] = channeler[i];
		}
	showwarnings = warn;*/
	if (clear) {
		EngineLogFile.open("Enginelogs/EngineLog.txt", std::ofstream::out | std::ofstream::trunc);
	}
	else {
		EngineLogFile.open("Enginelogs/EngineLog.txt", std::ofstream::out | std::ofstream::app);
	}
	time_t currenttime = time(nullptr);
	char time [200];
	ctime_s(time, sizeof(time), &currenttime);
	EngineLogFile << "Current date + time: " << time << std::endl;
	EngineLogFile.close();
}
void Logger::shutDown()
{
	EngineLogFile.close();
}
void Logger::clearLogs() {
	EngineLogFile.open("Enginelogs/EngineLog.txt", std::ofstream::trunc);
	EngineLogFile.close();
}
void Logger::setEngineLoggerSettings(int mem, int render, int misc, int newverbosity, bool newshowwarnings) {
/*void Logger::setEngineLoggerSettings(int newchannel, int newverbosity, bool newshowwarnings) { */
	engineverbosity = newverbosity;
	/*enginechannel = newchannel;*/
	enginechannels[0] = mem;
	enginechannels[1] = render;
	enginechannels[2] = misc;
	showwarnings = newshowwarnings;
}
/*void Logger::setLoggerVerbosity(int newverbosity) {
	/*void Logger::setEngineLoggerSettings(int newchannel, int newverbosity, bool newshowwarnings) { 
	if (newverbosity < 1 || newverbosity > 3) {
		std::cout << "Error, verbosity must be between 1 and 3 inclusive." << std::endl;
		return;
	}
	engineverbosity = newverbosity;
	/*enginechannel = newchannel;
}
void Logger::setActiveChannels(int mem, int render, int misc) {
	/*void Logger::setEngineLoggerSettings(int newchannel, int newverbosity, bool newshowwarnings) { 
	/*enginechannel = newchannel;
	enginechannels[0] = mem;
	enginechannels[1] = render;
	enginechannels[2] = misc;
}*/
void Logger::engineLog(std::string file, unsigned int line, std::string errormessage, int verbosity, int channel, bool iswarning)
{
	EngineLogFile.open("Enginelogs/EngineLog.txt", std::ofstream::out | std::ofstream::app);
	if (engineverbosity >= verbosity && ( ((enginechannels[0] == 1) && channel == 1) || ((enginechannels[1] == 1) && channel == 2) || ((enginechannels[2] == 1) && channel == 3) || (channel == 0))) {
	/*if (engineverbosity >= verbosity && (enginechannel == channel || enginechannel == 0)) { */
		if (iswarning && (showwarnings == true)) {
			std::cout << file << std::endl << " Line: " << line << std::endl << "Engine warning!: " << errormessage << std::endl;
			EngineLogFile << file << std::endl << " Line: " << line << std::endl << "Engine warning!: " << errormessage << std::endl;
		}
		else {
			std::cout << file << std::endl << " Line: " << line << std::endl << "Engine ERROR!: " << errormessage << std::endl;
			EngineLogFile << file << std::endl << " Line: " << line << std::endl << "Engine ERROR!: " << errormessage << std::endl;
		}
	}
	EngineLogFile.close();
}
std::ofstream Logger::EngineLogFile;
unsigned int Logger::engineverbosity = 3;
/*unsigned int Logger::enginechannel = 0;*/  //0 = all, 1 = memorymanager
unsigned int Logger::enginechannels[3] = { 1, 1, 1 };
bool Logger::showwarnings = true;
bool Logger::clear = false;