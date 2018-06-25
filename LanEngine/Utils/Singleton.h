#pragma once

namespace Lan
{
	template<typename T>
	class Singleton
	{
	public:
		static void CreateInstance();
		static T& GetInstance();
		static void DestroyInstance();

	protected:
		Singleton() {};
		virtual ~Singleton() {};

	private:
		static T* s_Instance;
	};
}

#include "Singleton.inl"