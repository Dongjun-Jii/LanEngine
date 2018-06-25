#pragma once
#include "ResourceFactory.h"

namespace Lan
{
	template<typename T>
	void * ResourceFactory<T>::Alloc(void * buffer, tsize len, tstring path, tstring extension)
	{
		return new T(buffer, len, path, extension);
	}

	template<typename T>
	void ResourceFactory<T>::Free(void * resource, tsize n)
	{
		if (n == 1)
		{
			delete resource;
		}
		else
		{
			delete[] resource;
		}
	}
}