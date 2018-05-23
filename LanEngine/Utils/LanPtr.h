#pragma once
#include "../Defines.h"

namespace Lan
{
	template<typename T>
	class LanPtr
	{
	public:
		LanPtr();

		template<typename... Args>
		LanPtr(Args&&... args);

		LanPtr(T* ptr);
		LanPtr(T& dst);
		LanPtr(T&& dst);

		LanPtr(const LanPtr<T>& other);
		LanPtr(LanPtr<T>&& other);

		virtual ~LanPtr();

		LanPtr<T>& operator=(const LanPtr<T>& other);
		LanPtr<T>& operator=(LanPtr<T>&& other);

		bool operator==(const LanPtr<T>& other) const;

		T& operator->();
		T& operator*();

		bool isNull() const;
		void setNull();

		template <typename C>
		LanPtr<C> static_convert();

		template <typename C>
		LanPtr<C> dynamic_convert();
	private:
		T * * m_Ptr;
		bool m_HasOwnership;
	};
}

#include "LanPtr.inl"