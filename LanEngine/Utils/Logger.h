#pragma once
#include "../Defines.h"
#include "Utils.h"
#ifndef LOG_MIN_LEVEL
#define LOG_MIN_LEVEL 1
#endif

namespace Lan
{
	enum LogLevel
	{
		Info,
		Warning,
		Error,
		Debug
	};

	struct BreakInfo
	{
		tstring file;
		int line;

		BreakInfo(const tstring file, int line): file(file), line(line) {}
	};

	class LanEngine;

	class Logger final : public Singleton<Logger>
	{
	public:
		friend Singleton<Logger>;
		friend LanEngine;

		void initialize(bool useConsole, bool useFile = false);

		void log(LogLevel level, const tstring& tag, const tstring& message, const BreakInfo& breakInfo);
		void log(LogLevel level, const tstring& message, const BreakInfo& breakInfo);

		void writeLogFile();

	private:
		Logger() {};
		~Logger();

		bool m_UseConsole;
		bool m_UseFile;
		tstringstream m_LogBuffer;
	};
}

#define LOG_WITH_TAG(level, tag, message) \
	Lan::Logger::getInstance().log(level, tag, message, Lan::BreakInfo(__FILE__, __LINE__));

#define LOG(level, message) \
	Lan::Logger::getInstance().log(level, message, Lan::BreakInfo(__FILE__, __LINE__));




