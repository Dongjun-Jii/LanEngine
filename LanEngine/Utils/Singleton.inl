#include "../Defines.h"
#include "Singleton.h"
#include "Logger.h"

namespace Lan
{
	template<typename T>
	T* Lan::Singleton<T>::s_Instance = nullptr;

	template<typename T>
	void Singleton<T>::CreateInstance()
	{
		if (s_Instance != nullptr)
		{
			LOG(LogLevel::Warning, "이미 초기화된 싱글턴 객체 초기화 시도");
		}
		else
		{
			s_Instance = new T();
		}
	}

	template<typename T>
	T& Singleton<T>::GetInstance()
	{
		if (s_Instance == nullptr)
		{
			LOG(LogLevel::Warning, "미초기화 상태의 싱글턴 객체 접근 시도. CreateInstance() 함수를 먼저 호출하시오");
			s_Instance = new T();
		}

		return *s_Instance;
	}

	template<typename T>
	void Singleton<T>::DestroyInstance()
	{
		if (s_Instance == nullptr)
		{
			LOG(LogLevel::Warning, "미초기화 상태의 싱글턴 객체 할당 해제 시도. CreateInstance() 함수를 먼저 호출하시오");
		}
		else
		{
			delete s_Instance;
			s_Instance = nullptr;
		}
	}
}