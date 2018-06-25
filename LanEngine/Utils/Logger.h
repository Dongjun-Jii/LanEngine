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
		int32 line;

		BreakInfo(const tstring file, int32 line): file(file), line(line) {}
	};

	class LanEngine;

	class Logger final : public Singleton<Logger>
	{
	public:
		friend Singleton<Logger>;
		friend LanEngine;

		void Initialize(bool useConsole, bool useFile = false);

		void Log(LogLevel level, const tstring& tag, const tstring& message, const BreakInfo& breakInfo);
		void Log(LogLevel level, const tstring& message, const BreakInfo& breakInfo);

		void WriteLogFile();

	private:
		Logger() {};
		~Logger();

		bool m_UseConsole;
		bool m_UseFile;
		tstringstream m_LogBuffer;
	};
}

#define LOG_WITH_TAG(level, tag, message) \
	Lan::Logger::GetInstance().Log(level, tag, message, Lan::BreakInfo(__FILE__, __LINE__));

#define LOG(level, message) \
	Lan::Logger::GetInstance().Log(level, message, Lan::BreakInfo(__FILE__, __LINE__));




