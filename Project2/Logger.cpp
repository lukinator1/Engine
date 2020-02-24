#include "Logger.h"
Logger::Logger()
{
}
Logger::~Logger()
{
}
void Logger::startUp(){
if (clear) {
	if (EngineLogFile.is_open()) {
		EngineLogFile.close();
	}
	EngineLogFile.open("Enginelogs/EngineLog.txt", std::ofstream::out | std::ofstream::trunc);
	EngineLogFile.close();
	}
	}
void Logger::shutDown()
{
	if (EngineLogFile.is_open()) {
		EngineLogFile.close();
	}
}
void Logger::clearLogs() {
	if (EngineLogFile.is_open() == true) {
		EngineLogFile.close();
	}
		EngineLogFile.open("Enginelogs/EngineLog.txt", std::ofstream::out | std::ofstream::trunc);
		EngineLogFile.close();
}
void Logger::setEngineLoggerSettings(unsigned int mem, unsigned int render, unsigned int misc, unsigned int newverbosity, bool newshowwarnings) {
	engineverbosity = newverbosity;
	enginechannels[0] = mem;
	enginechannels[1] = render;
	enginechannels[2] = misc;
	showwarnings = newshowwarnings;
}
void Logger::engineLog(std::string file, unsigned int line, std::string errormessage, unsigned int verbosity, unsigned int channel, bool iswarning)
{
	if (!EngineLogFile.is_open()) {
		EngineLogFile.open("Enginelogs/EngineLog.txt");
	}
	else {
		if (engineverbosity >= verbosity && (((enginechannels[0] == 1) && channel == 1) || ((enginechannels[1] == 1) && channel == 2) || ((enginechannels[2] == 1) && channel == 3) || (channel == 0))) {
			/*(if (engineverbosity >= verbosity && (enginechannel == channel || enginechannel == 0)) {*/
			if (iswarning && (showwarnings == true)) {
				std::cout << file << std::endl << " Line: " << line << std::endl << "Engine warning!: " << errormessage << std::endl;
				EngineLogFile << file << std::endl << " Line: " << line << std::endl << "Engine warning!: " << errormessage << std::endl;
			}
			else {
				std::cout << file << std::endl << " Line: " << line << std::endl << "Engine ERROR!: " << errormessage << std::endl;
				EngineLogFile << file << std::endl << " Line: " << line << std::endl << "Engine ERROR!: " << errormessage << std::endl;
			}
		}
	}
	EngineLogFile.close();
}
std::ofstream Logger::EngineLogFile;
unsigned int Logger::engineverbosity = 3;
unsigned int Logger::enginechannels[3];
bool Logger::showwarnings = true;
bool Logger::clear = false;