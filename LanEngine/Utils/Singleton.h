#pragma once

namespace Lan
{
	template<typename T>
	class Singleton
	{
	public:
		static void createInstance();
		static T& getInstance();
		static void destroyInstance();

	protected:
		Singleton() {};
		virtual ~Singleton() {};

	private:
		static T* s_Instance;
	};
}

#include "Singleton.inl"