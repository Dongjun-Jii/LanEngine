#include "Defines.h"
#include "Utils.h"
#include <chrono>
#include <ctime>
#include <cstdio>

namespace Lan
{
	Logger::~Logger()
	{
		writeLogFile();
	}

	void Logger::initialize(bool useConsole, bool useFile)
	{
		m_UseConsole = useConsole;
		m_UseFile = useFile;
	}

	void Logger::log(LogLevel level, const tstring& message, const BreakInfo& breakInfo)
	{
		log(level, "LanEngine", message, breakInfo);
	}

	void Logger::log(LogLevel level, const tstring& tag, const tstring& message, const BreakInfo& breakInfo)
	{
		tstringstream logText;
		switch (level)
		{
		case LogLevel::Info:
			logText << "[Info]";
			break;
		case LogLevel::Warning:
			logText << "[Warning]";
			break;
		case LogLevel::Error:
			logText << "[Error]";
			break;
		case LogLevel::Debug:
			logText << "[Debug]";
			break;
		}

		logText << "[" << tag << "]" << message << std::endl;
		logText << "File : " << breakInfo.file << std::endl;
		logText << "Line : " << breakInfo.line << std::endl;

		switch (level)
		{
		case LogLevel::Info:
#if LOG_MIN_LEVEL <= 1
			if (m_UseConsole)
			{
				std::cout << logText.str();
			}
			else
			{
				OutputDebugStringA(logText.str().c_str());
			}
			m_LogBuffer << logText.str();
#endif
			break;
		case LogLevel::Warning:
#if LOG_MIN_LEVEL <= 2
			if (m_UseConsole)
			{
				std::cout << logText.str();
			}
			else
			{
				OutputDebugStringA(logText.str().c_str());
			}
			m_LogBuffer << logText.str();
#endif
			break;
		case LogLevel::Error:
#if LOG_MIN_LEVEL <= 3
			if (m_UseConsole)
			{
				std::cout << logText.str();
			}
			else
			{
				OutputDebugStringA(logText.str().c_str());
			}
			m_LogBuffer << logText.str();
#endif
			break;
		case LogLevel::Debug:
#if LOG_MIN_LEVEL <= 4
			if (m_UseConsole)
			{
				std::cout << logText.str();
			}
			else
			{
				OutputDebugStringA(logText.str().c_str());
			}
			m_LogBuffer << logText.str();
#endif
			break;
		}
	}

	void Logger::writeLogFile()
	{
		if (!(m_LogBuffer.beg == m_LogBuffer.cur) && m_UseFile)
		{
			//현재 시간 확인
			std::chrono::system_clock::time_point curTimePoint = std::chrono::system_clock::now();
			time_t curTimet = std::chrono::system_clock::to_time_t(curTimePoint);
			tm* curTime = new tm();
			localtime_s(curTime, &curTimet);

			try
			{
				char curTimeBuffer[60] = { 0 };
				//현재 시간에 따라 파일이름 결정
				strftime(curTimeBuffer, sizeof(curTimeBuffer), "Log%y-%m-%d-%H-%M-%S.txt", curTime);
				tfstream logFileStream;
				logFileStream.exceptions(std::ios::failbit | std::ios::eofbit | std::ios::badbit);
				std::cout << "Log-" << curTimeBuffer << "\n" << m_LogBuffer.str() << std::endl;

				//파일 생성
				logFileStream.open(curTimeBuffer);

				//파일에 로그 작성
				logFileStream << m_LogBuffer.str() << std::endl;

				//로그 파일 닫기
				m_LogBuffer.clear();
				logFileStream.close();
			}
			catch (const std::ios_base::failure& e)
			{
				LOG(LogLevel::Error, e.what());
			}

			delete curTime;
		}
	}
}