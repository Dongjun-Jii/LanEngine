#pragma once
#include "Resource.h"
#include "../Utils/Singleton.h"

namespace Lan
{
	class Factory
	{
	public:
		virtual void * alloc(void * buffer, tsize len, tstring path, tstring extension) = 0;
		virtual void free(void * resource, size_t n = 1) = 0;
	};

	template<typename T>
	class ResourceFactory final: public Singleton<ResourceFactory<T>>, public Factory
	{
	public:
		friend Singleton<ResourceFactory<T>>;
		virtual void * alloc(void * buffer, tsize len, tstring path, tstring extension) override;
		//virtual void ** alloc(int8 ** buffer, tsize n) override;
		virtual void free(void * resource, tsize n) override;

	private:
		ResourceFactory() = default;
		~ResourceFactory() = default;

	};
}

#include "ResourceFactory.inl"