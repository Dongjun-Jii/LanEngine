#include "LanPtr.h"

namespace Lan
{
	template<typename T>
	LanPtr<T>::LanPtr() :
		m_HasOwnership(false),
		m_Ptr(new T*())
	{
		*m_Ptr = nullptr;
	}

	template<typename T>
	template<typename... Args>
	LanPtr<T>::LanPtr(Args&&... args) :
		m_HasOwnership(true),
		m_Ptr(new T*())
	{
		*m_Ptr = new T(args...);
	}

	template<typename T>
	LanPtr<T>::LanPtr(T* ptr) :
		m_HasOwnership(false),
		m_Ptr(new T*())
	{
		*m_Ptr = ptr;
	}

	template<typename T>
	LanPtr<T>::LanPtr(T& dst) :
		m_HasOwnership(false),
		m_Ptr(new T*())
	{
		*m_Ptr = &dst;
	}

	template<typename T>
	LanPtr<T>::LanPtr(T&& dst) :
		m_HasOwnership(dst.m_HasOwnership),
		m_Ptr(new T*())
	{
		*m_Ptr = new T(dst);
	}

	template<typename T>
	LanPtr<T>::LanPtr(const LanPtr<T>& other) :
		m_HasOwnership(false),
		m_Ptr(new T*())
	{
		*m_Ptr = *other.m_Ptr;
	}

	template<typename T>
	LanPtr<T>::LanPtr(LanPtr<T>&& other) :
		m_HasOwnership(other.m_HasOwnership),
		m_Ptr(other.m_Ptr)
	{
		other.m_Ptr = nullptr;
	}

	template<typename T>
	LanPtr<T>::~LanPtr()
	{
		if (m_HasOwnership && *m_Ptr)
		{

		}

		if (m_Ptr)
		{
			delete m_Ptr;
		}
	}

	template<typename T>
	LanPtr<T>& LanPtr<T>::operator=(const LanPtr<T>& other)
	{
		m_HasOwnership = false;
		*m_Ptr = *other.m_Ptr;
		return *this;
	}

	template<typename T>
	LanPtr<T>& LanPtr<T>::operator=(LanPtr<T>&& other)
	{
		m_HasOwnership = false;
		*m_Ptr = *other.m_Ptr;
		return *this;
	}

	template<typename T>
	bool LanPtr<T>::operator==(const LanPtr<T>& other) const
	{
		return (*m_Ptr) == (*other.m_Ptr);
	}

	template<typename T>
	T& LanPtr<T>::operator->()
	{
		if (isNull())
		{
			throw std::bad_typeid("Use Null Lan Pointer");
		}
		return **m_Ptr;
	}

	template<typename T>
	T& LanPtr<T>::operator*()
	{
		if (isNull())
		{
			throw std::bad_typeid("Use Null Lan Pointer");
		}
		return **m_Ptr;
	}

	template<typename T>
	bool LanPtr<T>::isNull() const
	{
		return (*m_Ptr == nullptr);
	}

	template<typename T>
	void LanPtr<T>::setNull()
	{
		if (m_HasOwnership)
		{
			*m_Ptr = nullptr;
		}
	}

}