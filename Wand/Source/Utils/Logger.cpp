#include "WandPCH.h"
#include "Logger.h"

namespace wand
{
	std::string Logger::sLogPath = "";

	void Logger::Init(std::string logDir)
	{
		// Set the log filepath according to the given directory
		sLogPath = logDir + "log.txt";
		// Create a new log file or overwrite the existing one
		std::ofstream file(sLogPath, std::ios::trunc);
	}

	void Logger::Log(std::string message)
	{
		// Open the log file and append a new message
		std::ofstream file(sLogPath, std::ios_base::app);
		file << message;
	}

	void Logger::EngineLog(std::string subsystem, std::string message)
	{
		// Open the log file and append a new message
		std::ofstream file(sLogPath, std::ios_base::app);
		file << "Wand(" << subsystem << "): " << message;
	}
}
