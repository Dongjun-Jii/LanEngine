#pragma once
#include "Resource.h"
#include "../Utils/Singleton.h"

namespace Lan
{
	class Factory
	{
	public:
		virtual void * Alloc(void * buffer, tsize len, tstring path, tstring extension) = 0;
		virtual void Free(void * resource, size_t n = 1) = 0;
	};

	template<typename T>
	class ResourceFactory final: public Singleton<ResourceFactory<T>>, public Factory
	{
	public:
		friend Singleton<ResourceFactory<T>>;
		virtual void * Alloc(void * buffer, tsize len, tstring path, tstring extension) override;
		virtual void Free(void * resource, tsize n) override;

	private:
		ResourceFactory() = default;
		~ResourceFactory() = default;

	};
}

#include "ResourceFactory.inl"