#pragma once

namespace wand
{
	class Logger
	{
	public:
		static void Init(std::string logDir);
		// Game logging
		static void Log(std::string message);
		// Engine logging
		static void EngineLog(std::string subsystem, std::string message);

	private:
		static std::string sLogPath;
	};
}
