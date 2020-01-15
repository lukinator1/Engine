#include "Logger.h"



Logger::Logger()
{
}
Logger::~Logger()
{
}
void Logger::startUp()
{
	EngineLogFile.open("EngineLog.txt", std::ofstream::out | std::ofstream::trunc);
}
void Logger::shutDown()
{
	EngineLogFile.close();
}
//void Logger::EngineLog(const char* format, ...) {
//}
void Logger::setEngineLoggerSettings(int &newverbosity, int &newchannel) {   //todo: check if channel/verbosity are in right range
	engineverbosity = newverbosity;
	enginechannel = newchannel;   
}
void Logger::VerboseEngineLog(std::string & file, std::string & line, std::string & errormessage, int &verbosity, int &channel)
{
	if (engineverbosity >= verbosity && (enginechannel == channel ||  enginechannel == 0)) {
		std::cout << "ERROR!: " << errormessage << file << ": line " << line << "." << std::endl; 
		EngineLogFile << "ERROR!: " << errormessage << ", " << file << ": line " << line << "." << std::endl;
	}
}
