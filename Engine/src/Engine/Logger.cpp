#include "Logger.h"



Logger::Logger()
{
}


Logger::~Logger()
{
}


//void Logger::EngineLog(const char* format, ...) {
//}
void Logger::setEngineLoggerSettings(int &newverbosity, int &newchannel) {
	engineverbosity = newverbosity;
	enginechannel = newchannel;
}
//convert to enum
void Logger::VerboseEngineLog(std::string & file, std::string & line, std::string & errormessage, int &verbosity, int &channel)
{
	if (engineverbosity >= verbosity && (enginechannel == channel ||  enginechannel == 0)) {
		std::cout << "ERROR!: " << errormessage << file << ": line " << line << ".";
	}
}
